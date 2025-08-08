#define IFX_CFG_USE_COMPILER_INTRINSICS   1   /* 컴파일러 built-in 사용 */
#define IFXCPU_INLINE                     1   /* iLLD 모든 API inline */
#include "auto_parking.h"
#include "main.h"
// 주차 공간 측정 상태

volatile ParkingState parking_state = PARKING_STATE_SEARCHING;

// 주차 공간 폭 측정 관련 변수
volatile uint32_t count_enc = 0;
int width_half_enc = 0;
float parking_v = 75.0;

void Parking_Init ()
{
    uint16 password = IfxScuWdt_getSafetyWatchdogPasswordInline();
    IfxScuWdt_clearSafetyEndinitInline(password);

    MODULE_P15.IOCR8.B.PC8 = 0x02;

    /* EICR.EXIS 레지스터 설정 : ESR2, 1번 신호 */
    MODULE_SCU.EICR[2].B.EXIS1 = 0;
    /* rising, falling edge 트리거 설정 */
    MODULE_SCU.EICR[2].B.REN1 = 0;
    MODULE_SCU.EICR[2].B.FEN1 = 1;
    /* Enable Trigger Pulse */
    MODULE_SCU.EICR[2].B.EIEN1 = 1;
    /* Determination of output channel for trigger event (Register INP) */
    MODULE_SCU.EICR[2].B.INP1 = 0;

    /* Configure Output channels, outputgating unit OGU (Register IGPy) */
    MODULE_SCU.IGCR[0].B.IGP0 = 1;

    volatile Ifx_SRC_SRCR *src;
    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.SCU.SCUERU[0]);
    src->B.SRPN = ISR_PRIORITY_ERU_INT0;
    src->B.TOS = 0;
    src->B.CLRR = 1; /* clear request */
    src->B.SRE = 0; /* interrupt enable, 나는 인터럽트 비활성화 상태로 시작 */
    IfxScuWdt_setSafetyEndinitInline(password);
}

// 인터럽트 활성화/비활성화 함수 (인라인 함수로 정의)
static inline void Enable_Enc_Interrupt (void)
{
    MODULE_SRC.SCU.SCUERU[0].B.SRE = 1; // Service Request Enable
}

static inline void Disable_Enc_Interrupt (void)
{
    MODULE_SRC.SCU.SCUERU[0].B.SRE = 0; // Service Request Disable
}

static inline float safe_read_left (void)
{
    float v;
    while (!IfxCpu_acquireMutex(&distLock))
        ;
    INV_LINE(&left_distance);
    __dsync();               // ▶︎ 배리어: 캐시 invalidate 前 준비
    v = left_distance;
    __isync();               // ▶︎ 캐시 invalidate 후 확정
    IfxCpu_releaseMutex(&distLock);
    return v;

}

static inline float safe_read_right (void)
{
    float v;
    while (!IfxCpu_acquireMutex(&distLock))
        ;
    INV_LINE(&right_distance);
    __dsync();               // ▶︎ 배리어: 캐시 invalidate 前 준비
    v = right_distance;
    __isync();               // ▶︎ 캐시 invalidate 후 확정
    IfxCpu_releaseMutex(&distLock);
    return v;

}

static inline float safe_read_rear (void)
{
    float v;
    while (!IfxCpu_acquireMutex(&distLock))
        ;
    INV_LINE(&rear_distance);
    __dsync();               // ▶︎ 배리어: 캐시 invalidate 前 준비
    v = rear_distance;
    __isync();               // ▶︎ 캐시 invalidate 후 확정
    IfxCpu_releaseMutex(&distLock);
    return v;

}

void calc_parking_distance (void)
{
    parking_state = PARKING_STATE_SEARCHING;
    VEL_flag = 0;
    while (parking_state != PARKING_STATE_FINISH)
    {
        leftTurn = 1;
        rightTurn = 1;
        switch (parking_state)
        {
            //자리 찾으러 가기
            case PARKING_STATE_SEARCHING :
            {
                //멀어->거리측정 시작
                float left = safe_read_left();
                if (left > START_THRESHOLD_CM)
                {

                    parking_state = PARKING_STATE_MEASURING;
                    my_printf("Parking space detected! Start measuring width...Ultra_left = %.2fcm\n", left);
                    count_enc = 0;
                    Enable_Enc_Interrupt();
                }
                //찾는중
                else
                {
                    my_printf("Searching... Distance = %.2f cm\n", safe_read_left());
                }
                //delay_ms(200);
                break;
            }
                //거리 측정 중
            case PARKING_STATE_MEASURING :
            {
                // 처음엔 벽과의 거리가 짧다가 나중에 멀어지면?
                // 현재 거리가 25cm 미만으로 들어오면 측정 종료
                float left = safe_read_left();
                if (left < END_THRESHOLD_CM)
                {
                    Disable_Enc_Interrupt();

                    float32 parking_width_cm = ((float32) count_enc * WHEEL_CIRCUM) / (4 * ENC_DISK);
                    my_printf("Measurement complete! Ultra_left = %.2f cm, Parking space width: %.2f cm\n", left,
                            parking_width_cm);
                    if (parking_width_cm > WIDTH_THRESHOLD_CM)
                    {
//                           width_half_enc = count_enc;
//                           count_enc = 0;

                        //Enable_Enc_Interrupt();

                        Motor_movChA_PWM(SEARCHING_SPEED, BACK_DIR); /* ChA = 왼쪽 휠 */
                        Motor_movChB_PWM(SEARCHING_SPEED, BACK_DIR); /* ChB = 오른쪽 휠 */
                        delay_ms(730);

                        Motor_movChB_PWM(ROTATE_SPEED, BACK_DIR);
                        Motor_movChA_PWM(0, FRONT_DIR);

                        delay_ms(1050);

                        Motor_movChB_PWM(0, FRONT_DIR);
                        // 후진, 회전, 주차 함수 짜면 추가하기
                        parking_state = PARKING_STATE_PARKING;
                        parking_v = 75.0;
                    }
                    else
                    {
                        my_printf("Parking space is too narrow. Resuming search...\n");
                        // 공간 좁으면 다시 탐색 상태로 복귀
                        parking_state = PARKING_STATE_SEARCHING;
                    }
                }
                else
                {
                    my_printf("Still measuring... Distance = %.2f cm\n", safe_read_left());
                }
                break;
            }
            case PARKING_STATE_PARKING :
            {
//                if (parking_v > PARKING_SPEED) {
//                    parking_v--;
//                }
                float rear = safe_read_rear();
                Ultrabuzzer(rear); //후면 기준 부저 알림
                //set_buzzer(rear_distance);
                my_printf("start go back\n");
                Motor_movChA_PWM(PARKING_SPEED, BACK_DIR); /* ChA = 왼쪽 휠 */
                Motor_movChB_PWM(PARKING_SPEED, BACK_DIR); /* ChB = 오른쪽 휠 */
                my_printf("rear: %.2f\n", rear);
                if (rear < 10.0f) /* 너무 가까우면 즉시 정지 */
                {
                    Motor_stopChA();
                    Motor_stopChB();
                    setBeepCycle(1);
                    HazzardLight = 1; // 비상 깜빡이 ON
                    delay_ms(2000);
                    setBeepCycle(0);
                    HazzardLight = 0; // 비상 깜빡이 OFF
                    parking_state = PARKING_STATE_FINISH;
                }
                break;
            }
            case PARKING_STATE_FINISH :
                /* Vehicle is parked */
                break;
        }

    }
    leftTurn = 0;
    rightTurn = 0;
    VEL_flag = 1;
}

IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_ERU_INT0);
void SCUERU_Int0_Handler (void)
{
    __enable();
    count_enc++;
}

