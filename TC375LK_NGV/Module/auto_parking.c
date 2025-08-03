#include "auto_parking.h"
#include "Buzzer.h"

extern float right_distance;
extern float left_distance;
extern float rear_distance;
// 주차 공간 측정 상태

volatile ParkingState parking_state = PARKING_STATE_SEARCHING;

// 주차 공간 폭 측정 관련 변수
uint64 space_measure_start_us = 0; // 시작 시간을 us 단위로 저장


void calc_parking_distance (float distance)
{
    switch (parking_state)
    {
        //자리 찾으러 가기
        case PARKING_STATE_SEARCHING :
            if (distance > START_THRESHOLD_CM)
            {
                parking_state = PARKING_STATE_MEASURING;
                space_measure_start_us = getTimeUs();
                my_printf("Parking space detected! Start measuring width...Distance = %.2fcm\n", distance);
            }
            else
            {
                my_printf("Searching... Distance = %.2f cm\n", distance);
            }
            break;
            //거리 측정 중
        case PARKING_STATE_MEASURING :
            // 현재 거리가 25cm 미만으로 들어오면 측정 종료
            if (distance < END_THRESHOLD_CM)
            {
                uint64 end_us = getTimeUs();

                uint64 elapsed_us = end_us - space_measure_start_us;

                float32 elapsed_seconds = (float32) elapsed_us / 1000000.0f;

                float32 parking_width_cm = elapsed_seconds * CAR_SPEED;

                my_printf("Measurement complete! Distance = %.2fcm, Parking space width: %.2f cm\n", distance,
                        parking_width_cm);

//                // 다시 탐색 상태로 복귀
//                parking_state = PARKING_STATE_SEARCHING;

                Motor_movChA_PWM(50, 0);
                Motor_stopChB();

                delay_ms(1000);

                Motor_stopChA();

                while (1)
                    ;
            }
            else
            {
                my_printf("Still measuring... Distance = %.2f cm\n", distance);
            }
            break;
    }
}

#define SIDE_DETECT     90.0f   /* 0~100 중 “벽 발견” 임계값 */
#define ALIGN_TOLERANCE  1.0f   /* 좌·우 거리 오차 허용(cm) */
#define STOP_DISTANCE    5.0f   /* 후방 최소 안전거리(cm) */

#define BASE_PWM        30      /* 기본 후진 속도(0~100) */
#define DELTA_PWM       10      /* 방향 보정 시 속도 가감 값 */
#define KP               0.3f   /* 좌우 오차 비례계수(P 제어) */

/* 후진 + 정렬 주차 루틴 */
void go_back(void)
{
    int left_pwm  = BASE_PWM;
    int right_pwm = BASE_PWM;

    /* 처음부터 후진 시작 */
    Motor_movChA_PWM(left_pwm,  0);   /* ChA = 왼쪽 휠 */
    Motor_movChB_PWM(right_pwm, 0);   /* ChB = 오른쪽 휠 */

    while (1)
    {
        /* 1) 비상 정지 조건 */
        set_buzzer(rear_distance);
        if (rear_distance < STOP_DISTANCE)         /* 너무 가까우면 즉시 정지 */
        {
            Motor_stopChA();
            Motor_stopChB();
            break;
        }

        /* 2) 사이드 벽 진입 & 정렬 로직 */
        if (left_distance < SIDE_DETECT && right_distance >= SIDE_DETECT)
        {   /* 왼쪽만 벽 감지 → 오른쪽으로 틀기(= 왼쪽 휠 PWM ↓, 오른쪽 ↑) */
            left_pwm  = BASE_PWM - DELTA_PWM;
            right_pwm = BASE_PWM + DELTA_PWM;
        }
        else if (right_distance < SIDE_DETECT && left_distance >= SIDE_DETECT)
        {   /* 오른쪽만 벽 감지 → 왼쪽으로 틀기 */
            left_pwm  = BASE_PWM + DELTA_PWM;
            right_pwm = BASE_PWM - DELTA_PWM;
        }
        else if (left_distance < SIDE_DETECT && right_distance < SIDE_DETECT)
        {   /* 양쪽 모두 벽 감지 → 중심 맞추기 (P 제어) */
            float error = left_distance - right_distance; /* +면 오른쪽 벽이 더 가까움 */
            int delta = (int)(KP * error);                /* 비례 제어값 */
            /* 과한 보정 방지 */
            if (delta >  DELTA_PWM) delta =  DELTA_PWM;
            if (delta < -DELTA_PWM) delta = -DELTA_PWM;

            left_pwm  = BASE_PWM - delta;
            right_pwm = BASE_PWM + delta;
        }
        else
        {   /* 아직 벽이 없음 → 직진 후진 */
            left_pwm  = BASE_PWM;
            right_pwm = BASE_PWM;
        }

        /* 3) PWM 적용 (후진 방향: dir=0) */
        Motor_movChA_PWM(left_pwm,  0);
        Motor_movChB_PWM(right_pwm, 0);
    }
}


void set_buzzer(float distance)
{
    if (distance < 0)
    {
        setBeepCycle(0);
    }
    else if (distance > 30.0f)
    {
        setBeepCycle(0);  // 30cm 이상: 무음
    }
    else if (distance > 15.0f)
    {
        setBeepCycle(260);  // 15~30cm: 느린 비프 (6 토글 on/off)
    }
    else if (distance > 5.0f)
    {
        setBeepCycle(50);  // 5~15cm: 중간속도 비프
    }
    else
    {
        setBeepCycle(10);  // 5cm 이하: 빠른 비프 (최대로 빠른 깜빡임)
    }
}
