#include "sys_init.h"

void SYSTEM_INIT(void) {
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    Asclin0_InitUart();
    GPIO_Init();
    //gpt2_init();
    //Buzzer_Init();
    //gpt1_init();
    Ultrasonics_Init();
    //scueru_Init();
    Evadc_Init();
    Motor_Init();
    Bluetooth_Init();
    Can_Init(BD_500K, CAN_NODE0);
}
