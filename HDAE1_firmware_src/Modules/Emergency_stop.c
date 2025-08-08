#include "Emergency_stop.h"

//unsigned int G_TofValue = 0;
uint64 t1, t2, present;
static inline void Enable_Enc_Interrupt (void)
{
    MODULE_SRC.SCU.SCUERU[0].B.SRE = 1; // Service Request Enable
}

static inline void Disable_Enc_Interrupt (void)
{
    MODULE_SRC.SCU.SCUERU[0].B.SRE = 0; // Service Request Disable
}

float velocity (void)
{
    if (VEL_flag)
    {
        count_enc = 0;
        Enable_Enc_Interrupt();
        //    delay_ms(1000);

        t1 = getTimeUs(); // 지금 조금 도는데도 인터럽트가 20번 이상 일어나는 에러가 발생함.
        while (count_enc != 80); // 한바퀴 구멍 20개. 구멍 나갈 때 들어올 때, 2번, rising /falling 2번 총 4번의 신호가 한번의 구멍 지날 때 발생함.
        t2 = getTimeUs(); //
        Disable_Enc_Interrupt();
        return ((WHEEL_CIRCUM * 10000) / (t2 - t1)); // m/s  즉 21* 10^-2 / 10^-6 = 21 * 10^4
    }

    return 0;
}
float Get_Braking_Distance (float v)
{
    float dis = 1.0 * (v * v) / (3 * Deceleration_rate);
    float Brake_Dis = 1000*dis;
    if (Brake_Dis > 2000) return 100;
    return Brake_Dis; // m단위이니 tof 단위로 하려면 곱하기 1000을 함.//
}

/*
void Emergency_stop (void)
{
    if ((ToftofValue < 100 + Braking_Distance) && Car_dir == 1) //
    {

        if (!AEB_flag)
        {
            my_printf("tof distance: %d\n", ToftofValue);
            my_printf("Goal dist : %f\n", (100.0 + Braking_Distance));
//            Motor_movChA_PWM(75, 0);
//            Motor_movChB_PWM(75, 0);
//            delay_ms(500);

            Motor_All_Stop();
            MODULE_P10.OUT.B.P4 = 1;
            my_printf("stop\n");
        }
        //my_printf("stopping\n");
        AEB_flag = 1;
        //긴급 제동 Debugging용
        //TODO : 상세 로직 역회전하기.

    }
    else
    {
        AEB_flag = 0;
        MODULE_P10.OUT.B.P4 = 0;    // LED OFF
    }
//    else{
//        Motor_movChA_PWM(50, 1);
//        Motor_movChB_PWM(50, 1);
//    }

}
*/
