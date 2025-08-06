#include "gtm_atom_pwm.h"
#include "Ifx_Types.h"
#include "IfxGtm_Atom_Pwm.h"
#include "isr_priority.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_ATOM   20                                  /* Interrupt priority number                        */
#define LED                 IfxGtm_ATOM0_4_TOUT14_P00_5_OUT     /* LED which will be driven by the PWM              */
#define PWM_A               IfxGtm_ATOM0_1_TOUT1_P02_1_OUT
#define PWM_B               IfxGtm_ATOM1_3_TOUT105_P10_3_OUT

#define CLK_FREQ            1000000.0f                          /* CMU clock frequency, in Hertz                    */
#define PWM_PERIOD          1000                                /* PWM period for the ATOM, in ticks                */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxGtm_Atom_Pwm_Config g_atomConfig_PwmA;
IfxGtm_Atom_Pwm_Config g_atomConfig_PwmB;
IfxGtm_Atom_Pwm_Driver g_atomDriver_PwmA;
IfxGtm_Atom_Pwm_Driver g_atomDriver_PwmB;

IfxGtm_Atom_Pwm_Config g_atomConfig;                            /* Timer configuration structure                    */
IfxGtm_Atom_Pwm_Driver g_atomDriver;                            /* Timer Driver structure                           */

/*********************************************************************************************************************/
/*--------------------------------------------Function Implementations-----------------------------------------------*/
/*********************************************************************************************************************/
/* This function initializes the ATOM */
void GtmAtomPwm_Init(void)
{
    IfxGtm_enable(&MODULE_GTM);                                             /* Enable GTM                           */

    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, CLK_FREQ);    /* Set the CMU clock 0 frequency        */
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);            /* Enable the CMU clock 0               */
//    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_1, CLK_FREQ);
//    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK1);

    IfxGtm_Atom_Pwm_initConfig(&g_atomConfig_PwmA, &MODULE_GTM);
//    IfxGtm_Atom_Pwm_initConfig(&g_atomConfig, &MODULE_GTM);                 /* Initialize default parameters        */

    g_atomConfig_PwmA.atom = PWM_A.atom;
    g_atomConfig_PwmA.atomChannel = PWM_A.channel;
    g_atomConfig_PwmA.period = PWM_PERIOD;
    g_atomConfig_PwmA.pin.outputPin = &PWM_A;
    g_atomConfig_PwmA.synchronousUpdateEnabled = TRUE;

    IfxGtm_Atom_Pwm_init(&g_atomDriver_PwmA, &g_atomConfig_PwmA);
    IfxGtm_Atom_Pwm_start(&g_atomDriver_PwmA, TRUE);


    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_1, CLK_FREQ);
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK1);

    IfxGtm_Atom_Pwm_initConfig(&g_atomConfig_PwmB, &MODULE_GTM);

    g_atomConfig_PwmB.atom = PWM_B.atom;                                       /* Select the ATOM depending on the LED     */
    g_atomConfig_PwmB.atomChannel = PWM_B.channel;                             /* Select the channel depending on the LED  */
    g_atomConfig_PwmB.period = PWM_PERIOD;                                   /* Set timer period                         */
    g_atomConfig_PwmB.pin.outputPin = &PWM_B;                                  /* Set LED as output                        */
    g_atomConfig_PwmB.synchronousUpdateEnabled = TRUE;                       /* Enable synchronous update                */

    IfxGtm_Atom_Pwm_init(&g_atomDriver_PwmB, &g_atomConfig_PwmB);                 /* Initialize the PWM                       */
    IfxGtm_Atom_Pwm_start(&g_atomDriver_PwmB, TRUE);                         /* Start the PWM                            */
}

/* This function sets the duty cycle of the PWM */
void GtmAtomPwm_SetDutyCycle(uint32 dutyCycle)
{
    g_atomConfig.dutyCycle = dutyCycle;                 /* Set duty cycle                                           */
    IfxGtm_Atom_Pwm_init(&g_atomDriver, &g_atomConfig); /* Re-initialize the PWM                                    */
}

void GtmAtomPwmA_SetDutyCycle(uint32 dutyCycle)
{
    g_atomConfig_PwmA.dutyCycle = dutyCycle;                 /* Set duty cycle                                           */
    IfxGtm_Atom_Pwm_init(&g_atomDriver_PwmA, &g_atomConfig_PwmA); /* Re-initialize the PWM                                    */
}

void GtmAtomPwmB_SetDutyCycle(uint32 dutyCycle)
{
    g_atomConfig_PwmB.dutyCycle = dutyCycle;                 /* Set duty cycle                                           */
    IfxGtm_Atom_Pwm_init(&g_atomDriver_PwmB, &g_atomConfig_PwmB); /* Re-initialize the PWM                                    */
}
