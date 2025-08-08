#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "main.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;




void core1_main(void)
{
    //SYSTEM_Init();
    //IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG1 IS DISABLED HERE!!
     * Enable the watchdog and service it periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
//
//    /* Wait for CPU sync event */
//    IfxCpu_emitEvent(&g_cpuSyncEvent);
//    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
//
    while(1)
    {

        float l = Ultrasonic_ReadLeftSensor_Filt();
        float r = Ultrasonic_ReadRightSensor_Filt();
        float b = Ultrasonic_ReadSensor_Filt();

        while (!IfxCpu_acquireMutex(&distLock));   // 락 획득
        left_distance = l;
        right_distance = r;
        rear_distance = b;
        //l,r,b값 테스트
//        my_printf("l : %f\n",l);
//        my_printf("r : %f\n",r);
//        my_printf("b : %f\n",b);
//
//        delay_ms(100);
        //my_printf("En : %d\n",count_enc);

        FLUSH_LINE(&left_distance);
        FLUSH_LINE(&right_distance);   /* <- 세 줄만! */
        FLUSH_LINE(&rear_distance);
        __isync();                 // 명령 파이프 동기화(보너스)
        IfxCpu_releaseMutex(&distLock);
    }
}
