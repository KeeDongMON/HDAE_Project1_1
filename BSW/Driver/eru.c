#include "eru.h"

void scueru_Init(void)
{
    uint16 password = IfxScuWdt_getSafetyWatchdogPasswordInline();
    IfxScuWdt_clearSafetyEndinitInline(password);

    MODULE_P10.IOCR4.B.PC7 = 0x02;
    /* EICR.EXIS 레지스터 설정 : ESR2, 1번 신호 */
    MODULE_SCU.EICR[0].B.EXIS0 = 2;
    /* rising, falling edge 트리거 설정 */
    MODULE_SCU.EICR[0].B.REN0 = 1;
    MODULE_SCU.EICR[0].B.FEN0 = 1;
    /* Enable Trigger Pulse */
    MODULE_SCU.EICR[0].B.EIEN0 = 1;
    /* Determination of output channel for trigger event (Register INP) */
    MODULE_SCU.EICR[0].B.INP0 = 1;
    /* Configure Output channels, outputgating unit OGU (Register IGPy) */
    MODULE_SCU.IGCR[0].B.IGP1 = 1;

    MODULE_SRC.SCU.SCUERU[1].B.SRPN = ISR_PRIORITY_ERU_INT0;
    MODULE_SRC.SCU.SCUERU[1].B.TOS = 0;
    MODULE_SRC.SCU.SCUERU[1].B.CLRR = 1;
    MODULE_SRC.SCU.SCUERU[1].B.SRE = 1;


//    volatile Ifx_SRC_SRCR *src;
//    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.SCU.SCUERU);
//    src->B.SRPN = ISR_PRIORITY_ERU_INT0;
//    src->B.TOS = 0;
//    src->B.CLRR = 1; /* clear request */
//    src->B.SRE = 1; /* interrupt enable */
    IfxScuWdt_setSafetyEndinitInline(password);
}

//void scueru_Init ()
//{
//    uint16 password = IfxScuWdt_getSafetyWatchdogPasswordInline();
//    IfxScuWdt_clearSafetyEndinitInline(password);
//
//    MODULE_P02.IOCR0.B.PC1 = 0x02;
//    /* EICR.EXIS 레지스터 설정 : ESR2, 1번 신호 */
//    MODULE_SCU.EICR[1].B.EXIS0 = 1;
//    /* rising, falling edge 트리거 설정 */
//    MODULE_SCU.EICR[1].B.REN0 = 0;
//    MODULE_SCU.EICR[1].B.FEN0 = 1;
//    /* Enable Trigger Pulse */
//    MODULE_SCU.EICR[1].B.EIEN0 = 1;
//    /* Determination of output channel for trigger event (Register INP) */
//    MODULE_SCU.EICR[1].B.INP0 = 0;
//    /* Configure Output channels, outputgating unit OGU (Register IGPy) */
//    MODULE_SCU.IGCR[0].B.IGP0 = 1;
//    volatile Ifx_SRC_SRCR *src;
//    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.SCU.SCUERU);
//    src->B.SRPN = ISR_PRIORITY_ERU_INT0;
//    src->B.TOS = 0;
//    src->B.CLRR = 1; /* clear request */
//    src->B.SRE = 1; /* interrupt enable */
//    IfxScuWdt_setSafetyEndinitInline(password);
//}

IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_ERU_INT0);
float timer_start = -1;
float timer_end = -1;
float dist = 0;

void SCUERU_Int0_Handler (void)
{
    if(MODULE_P10.IN.B.P7 == 1) {
        //rising edge
        timer_end = -1;
        //my_printf("echo start\n");
        timer_start = getTimeUs();
    }

    else if(MODULE_P10.IN.B.P7 == 0) {
        //falling edge
        //my_printf("echo end\n");
        timer_end = getTimeUs();
    }

    if(timer_start != -1 && timer_end != -1) {
        dist = (float)0.0343 * (timer_end - timer_start) / 2.0;
        my_printf("%f cm\n", dist);
        timer_start = -1;
        timer_end = -1;
    }
}
