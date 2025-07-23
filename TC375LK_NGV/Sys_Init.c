#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "main.h"

static void module_Init(void);

void SYSTEM_Init(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    module_Init();
}

void module_Init(void)
{
    /* IO Init */
    GPIO_Init();
    Buzzer_Init();
//    Bluetooth_Init();
    Ultrasonics_Init();
    Motor_Init();

    /* Module Init */
    Asclin0_InitUart();
    gpt12_Init();
    Evadc_Init();
    Can_Init(BD_500K, CAN_NODE0);
    CanFd_Init(BD_500K, HS_BD_2M, CANFD_NODE2);
}
