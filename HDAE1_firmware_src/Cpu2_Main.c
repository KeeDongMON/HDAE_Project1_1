#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Emergency_stop.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;

float current_velocity =0.1;
float Braking_Distance = 0.1;
float tmp_Distance = 0.1;
void core2_main(void)
{
    //IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG2 IS DISABLED HERE!!
     * Enable the watchdog and service it periodically if it is required
     */
    //IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
//
//    /* Wait for CPU sync event */
//    IfxCpu_emitEvent(&g_cpuSyncEvent);
//    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    while(1)
    {

        current_velocity = velocity();
        Braking_Distance = Get_Braking_Distance(current_velocity);

        //my_printf("PWM:50 Deceleration_rate: 1\n");
//        my_printf("braking distance : %f\n", Braking_Distance);//v 안에 안갇혀있으니, v값이 들어왔을떄만 코드가 돌아가도록해라.
//        my_printf("current V: %fm/s\n", current_velocity);


    }
}
