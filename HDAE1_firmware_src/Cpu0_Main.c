#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;
float32 distance;

volatile float right_distance __attribute__((section(".lmu_data"))) = 0.0f;
volatile float left_distance  __attribute__((section(".lmu_data"))) = 0.0f;
volatile float rear_distance  __attribute__((section(".lmu_data"))) = 0.0f;
volatile IfxCpu_mutexLock distLock __attribute__((section(".lmu_data"))) = 0;

unsigned int ToftofValue = 0;

void core0_main(void)
{
    SYSTEM_Init();
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
//
//    /* Wait for CPU sync event */
//    IfxCpu_emitEvent(&g_cpuSyncEvent);
    
    while(1)
    {
//        Motor_movChB_PWM(75,1);
//        Motor_movChA_PWM(75,1);
//        delay_ms(100);
//        Motor_movChB_PWM(75,0);
//        Motor_movChA_PWM(75,0);
//        delay_ms(100);



        Asclin1_PollCMD();
        HBA_ON();
//        my_printf("en : %d\n",count_enc);
        //Emergency_stop();
//        //UltraBuzzer();
//        setLedCycle(400);
//        setLightButton(1);
//        setLightButton(2);
//        setLightButton(3);
//        delay_ms(100);
//        //my_printf("ditance : %f cm\n", distance);

        //emergency_LED();

    }
}



IFX_INTERRUPT(CanRxHandler, 0, ISR_PRIORITY_CAN_RX);
void CanRxHandler (void)
{
    unsigned int rxID;
    unsigned char rxData[8] = {0, };
    int rxLen;
    Can_RecvMsg(&rxID, rxData, &rxLen);

    if (rxID == 0x12)
    {
        //TODO : Vision CAN Frame 구성 및 logic 처리 논의
        my_printf("%s\n", rxData);
    }
    else
    {
        ToftofValue = rxData[2] << 16 | rxData[1] << 8 | rxData[0];
        unsigned char dis_status = rxData[3];
        unsigned short signal_strength = rxData[5] << 8 | rxData[4];
        if ((ToftofValue < 100 + Braking_Distance) && Car_dir == 1) //가깝고 앞으로 가는중
            {

            if (!AEB_flag)
            {
                Motor_All_Stop();

                my_printf("tof distance: %d\n", ToftofValue);
                my_printf("Goal dist : %f\n", (100.0 + Braking_Distance));

    //            Motor_movChA_PWM(75, 0);
    //            Motor_movChB_PWM(75, 0);
    //            delay_ms(500);
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
        }


//        if (signal_strength != 0)
//        {
//            if (tofValue <= 100)
//            {
//                Motor_stopChA();
//                Motor_stopChB();
//
//                //긴급 제동 Debugging용
//                //TODO : 상세 로직
//
//            }
//        }
    }

}

