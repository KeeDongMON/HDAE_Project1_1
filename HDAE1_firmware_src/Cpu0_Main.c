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
    
//    Motor_All_Mov(80,1);
//    delay_ms(100);
    while(1)
    {
//        Motor_movChB_PWM(75,1);
//        Motor_movChA_PWM(75,1);
//        delay_ms(100);
//        Motor_movChB_PWM(75,0);
//        Motor_movChA_PWM(75,0);
//        delay_ms(100);
        //calc_parking_distance();

        Asclin1_PollCMD();
        HBA_ON();

//        my_printf("en : %d\n",count_enc);
//        //UltraBuzzer();
//        setLedCycle(400);
//        setLightButton(1);
//        setLightButton(2);
//        setLightButton(3);
//        delay_ms(100);
//        //my_printf("ditance : %f cm\n", distance);
    }
}



IFX_INTERRUPT(CanRxHandler, 0, ISR_PRIORITY_CAN_RX);
void CanRxHandler (void)
{
    unsigned int rxID;
    unsigned char rxData[8] = {0, };
    int rxLen;
    Can_RecvMsg(&rxID, rxData, &rxLen);
    //my_printf("COM\n");


    if (rxID == 0x123)
    {
        my_printf("%s\n", rxData);
        if(LKAS_flag){
            //my_printf("LKAS\n");
            //TODO : Vision CAN Frame 구성  logic 처리 논의

            //rxData[0] : 차선 벗어남 (0,1)
            //rxData[1] : 가야하는 방향 (0:정상,1:좌,2:우)
            if (rxData[1] != '0')
            {
                setBeepCycle(50);
            }
            else
            {
                setBeepCycle(0);
            }

        }

    }
    else
    {
        ToftofValue = rxData[2] << 16 | rxData[1] << 8 | rxData[0];
        unsigned char dis_status = rxData[3];
        unsigned short signal_strength = rxData[5] << 8 | rxData[4];
        //my_printf("tof distance: %d\n", ToftofValue);
        //my_printf("tof\n");
        if ((ToftofValue < 150 + Braking_Distance) && Car_dir == 1) //가깝고 앞으로 가는중
            {

            if (!AEB_flag)
            {
                Motor_All_Stop();

//                my_printf("tof distance: %d\n", ToftofValue);
//                my_printf("Goal dist : %f\n", (100.0 + Braking_Distance));

    //            Motor_movChA_PWM(75, 0);
    //            Motor_movChB_PWM(75, 0);
    //            delay_ms(500);
                my_printf("stop\n");
                HazzardLight = 1;
            }
            //my_printf("stopping\n");
            AEB_flag = 1;
            //긴급 제동 Debugging용
            //TODO : 상세 로직 역회전하기.

        }
        else
        {
            HazzardLight = 0;
            AEB_flag = 0;
        }

    }

}

