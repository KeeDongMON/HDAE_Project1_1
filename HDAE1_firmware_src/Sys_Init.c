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

    GPIO_Init();
    UltraBuzzer_Init();
    LightButton_Init();
    Ultrasonics_Init();
    Motor_Init();

    /* Module Init */
    Asclin0_InitUart();
    Bluetooth_Init();

    HBA_Init();
    gpt12_Init();
    Evadc_Init();
    Parking_Init();
    Can_Init(BD_500K, CAN_NODE0);
    //CanFd_Init(BD_500K, HS_BD_2M, CANFD_NODE2);
}
