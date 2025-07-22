#include <gpt12.h>
#include <Ifx_reg.h>
#include <Ifx_Types.h>
#include <IfxGpt12.h>
#include <IfxPort.h>
#include "Ifx_Types.h"
#include "IfxGpt12.h"
#include "IfxPort.h"
#include "asclin.h"
#include "isr_priority.h"
#include "GPIO.h"
#include "Buzzer.h"

#define ISR_PROVIDER_GPT12_TIMER    0       //IfxSrc_Tos_cpu0
#define GPT1_BLOCK_PRESCALER        32      /* GPT1 block prescaler value                 */
#define TIMER_T3_INPUT_PRESCALER    32      /* Timer input prescaler value                */

//static volatile unsigned int cnt_10us = 0;
static volatile unsigned int cntDelay = 0;

static void gpt1_init(void);
static void gpt2_init(void);

IFX_INTERRUPT(IsrGpt2T6Handler, 0, ISR_PRIORITY_GPT2T6_TIMER);
void IsrGpt2T6Handler(void)
{
    cntDelay++;
}


unsigned int getcntDelay(void)
{
    return cntDelay;
}

void setcntDelay(unsigned int n)
{
    cntDelay = n;
}

void gpt12_Init(void)
{
    IfxScuWdt_clearCpuEndinit(IfxScuWdt_getGlobalEndinitPassword());
    MODULE_GPT120.CLC.U = 0;
    IfxScuWdt_setCpuEndinit(IfxScuWdt_getGlobalEndinitPassword());

    gpt1_init();
    gpt2_init();
}

void gpt1_init(void)
{
    /* Initialize the Timer T3 (PWM) */
    MODULE_GPT120.T3CON.B.BPS1 = 0x2; /* Set GPT1 block prescaler: 32 */
    MODULE_GPT120.T3CON.B.T3M = 0x0; /* Set T3 to timer mode */
    MODULE_GPT120.T3CON.B.T3UD = 0x1; /* Set T3 count direction(down) */
    MODULE_GPT120.T3CON.B.T3I = 0x5; /* Set T3 input prescaler(2^5=32) */
    /* Calculate dutyUpTime and dutyDownTime for reloading timer T3 */
    MODULE_GPT120.T3.U = 93; /* Set timer T3 value */
    /* Timer T2: reloads the value DutyDownTime in timer T3 */
    MODULE_GPT120.T2CON.B.T2M = 0x4; /* Set the timer T2 in reload mode */
    MODULE_GPT120.T2CON.B.T2I = 0x7; /* Reload Input Mode : Rising/Falling Edge T3OTL */
    MODULE_GPT120.T2.U = 93;

    /* Initialize the interrupt */
    volatile Ifx_SRC_SRCR *src;
    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.GPT12.GPT12[0].T3);
    src->B.SRPN = ISR_PRIORITY_GPT1T3_TIMER;
    src->B.TOS = 0;
    src->B.CLRR = 1; /* clear request */

    src->B.SRE = 1; /* interrupt enable */

    runGpt12_T3();
}

void gpt2_init(void)
{
    /* Initialize the Timer T6 for delay_ms */
    MODULE_GPT120.T6CON.B.BPS2 = 0x0; /* Set GPT2 block prescaler: 4 */
    MODULE_GPT120.T6CON.B.T6M = 0x0; /* Set T6 to timer mode */
    MODULE_GPT120.T6CON.B.T6UD = 0x1; /* Set T6 count direction(down) */
    MODULE_GPT120.T6CON.B.T6I = 0x0; /* Set T6 input prescaler(2^0=1) */
    MODULE_GPT120.T6CON.B.T6OE = 0x1; /* Overflow/Underflow Output Enable */
    MODULE_GPT120.T6CON.B.T6SR = 0x1; /* Reload from register CAPREL Enabled */
    MODULE_GPT120.T6.U = 250u; /* Set T6 start value (10us) */

    MODULE_GPT120.CAPREL.U = 250u; /* Set CAPREL reload value */                                          /* Set CAPREL reload value */

    /* Initialize the interrupt */
    volatile Ifx_SRC_SRCR *src;
    src = (volatile Ifx_SRC_SRCR*) (&MODULE_SRC.GPT12.GPT12[0].T6);
    src->B.SRPN = ISR_PRIORITY_GPT2T6_TIMER;
    src->B.TOS = 0;
    src->B.CLRR = 1; /* clear request */
    src->B.SRE = 1; /* interrupt enable */

    runGpt12_T6();
}

void runGpt12_T3()
{
    IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
}

void stopGpt12_T3()
{
    IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_stop);
}

void runGpt12_T6()
{
    IfxGpt12_T6_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
}

void stopGpt12_T6()
{
    IfxGpt12_T6_run(&MODULE_GPT120, IfxGpt12_TimerRun_stop);
}
