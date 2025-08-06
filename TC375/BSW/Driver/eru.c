#include "isr_priority.h"
#include <Ifx_reg.h>
#include <Ifx_Types.h>
#include <IfxScuWdt.h>
#include "my_stdio.h"
#include "Emergency_stop.h"
void scueru_Init()
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


extern volatile uint32_t count_enc;

IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_ERU_INT0);
void SCUERU_Int0_Handler (void)
{
    count_enc++;
}
