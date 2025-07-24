
#include "Ifx_reg.h"
#include "IfxEvadc_reg.h"
#include "IfxEvadc_Adc.h"

#define GROUPID_3     IfxEvadc_GroupId_3


#define AN24_CHID      1
#define AN25_CHID      0

IfxEvadc_Adc         g_evadc_EasyModule;
IfxEvadc_Adc_Group   g_adcGroup_EasyModule;
IfxEvadc_Adc_Channel g_adcChannel_VR; /* Easy Module Shield Variable Resistor */
IfxEvadc_Adc_Channel g_adcChannel_PR; /* Easy Module Shield Photo resistor */

Ifx_EVADC_G_RES g_result;                                       /* Variable to store the result of the measurement  */


void Evadc_Init(void)
{
    /* Create configuration */
    IfxEvadc_Adc_Config adcConfig;
    IfxEvadc_Adc_initModuleConfig(&adcConfig, &MODULE_EVADC);

    /* Initialize module */
    IfxEvadc_Adc_initModule(&g_evadc_EasyModule, &adcConfig);
    /* Function to initialize the EVADC group with default parameters */
    /* Create and initialize group configuration with default values */
    IfxEvadc_Adc_GroupConfig adcGroupConfig;
    IfxEvadc_Adc_initGroupConfig(&adcGroupConfig, &g_evadc_EasyModule);
    /* Setting user configuration using group 3 */
    adcGroupConfig.groupId = GROUPID_3;
    adcGroupConfig.master = GROUPID_3;
    /* Enable queued source */
    adcGroupConfig.arbiter.requestSlotQueue0Enabled = TRUE;
    /* Enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.queueRequest[0].triggerConfig.gatingMode = IfxEvadc_GatingMode_always;
    /* Initialize the group */
    IfxEvadc_Adc_initGroup(&g_adcGroup_EasyModule, &adcGroupConfig);

    /* Function to initialize the EVADC channel */
    /* Create channel configuration */
    IfxEvadc_Adc_ChannelConfig adcChannelConfig[2];

    // Init Variable Register Channel
    /* Initialize the configuration with default values */
    IfxEvadc_Adc_initChannelConfig(&adcChannelConfig[0], &g_adcGroup_EasyModule);
    /* Select the channel ID and the respective result register */
    adcChannelConfig[0].channelId = (IfxEvadc_ChannelId)(AN25_CHID);
    adcChannelConfig[0].resultRegister = (IfxEvadc_ChannelResult)(AN25_CHID);
    /* Initialize the channel */
    IfxEvadc_Adc_initChannel(&g_adcChannel_VR, &adcChannelConfig[0]);

    // Init Photo Register channel
    /* Initialize the configuration with default values */
    IfxEvadc_Adc_initChannelConfig(&adcChannelConfig[1], &g_adcGroup_EasyModule);
    /* Select the channel ID and the respective result register */
    adcChannelConfig[1].channelId = (IfxEvadc_ChannelId)(AN24_CHID);
    adcChannelConfig[1].resultRegister = (IfxEvadc_ChannelResult)(AN24_CHID);
    /* Initialize the channel */
    IfxEvadc_Adc_initChannel(&g_adcChannel_PR, &adcChannelConfig[1]);

    /* Function to add the channel to a queue */
    /* Add channel to queue with refill option enabled */
    IfxEvadc_Adc_addToQueue(&g_adcChannel_VR, IfxEvadc_RequestSource_queue0, IFXEVADC_QUEUE_REFILL);
    IfxEvadc_Adc_addToQueue(&g_adcChannel_PR, IfxEvadc_RequestSource_queue0, IFXEVADC_QUEUE_REFILL);
    /* Start the queue */
    IfxEvadc_Adc_startQueue(&g_adcGroup_EasyModule, IfxEvadc_RequestSource_queue0);

}

unsigned int Evadc_readVR(void)
{
    Ifx_EVADC_G_RES conversionResult;

    /* Wait for valid result */
    do
    {
        conversionResult = IfxEvadc_Adc_getResult(&g_adcChannel_VR); /* Read the result of the channel */
    } while(!conversionResult.B.VF);

    return conversionResult.B.RESULT;
}

unsigned int Evadc_readPR(void)
{
    Ifx_EVADC_G_RES conversionResult;

    /* Wait for valid result */
    do
    {
        conversionResult = IfxEvadc_Adc_getResult(&g_adcChannel_PR); /* Read the result of the channel */
    } while(!conversionResult.B.VF);

    return conversionResult.B.RESULT;
}


#if 0
#include "evadc.h"
#include "Ifx_reg.h"
#include "IfxEvadc_reg.h"
#include "IfxEvadc_Adc.h"


static void Evadc_startConversion(void);

void Evadc_Init(void)
{
    /* Initialize module */
    IfxScuWdt_clearCpuEndinit(IfxScuWdt_getCpuWatchdogPassword());
    MODULE_EVADC.CLC.U = 0;
    IfxScuWdt_setCpuEndinit(IfxScuWdt_getCpuWatchdogPassword());

    MODULE_P40.IOCR0.B.PC1 = 0x00;

    /* EVADC Group Configuration */
    MODULE_EVADC.G[3].ARBPR.B.PRIO0 = 0x3;   // Highest Priority for Request Source 0
    MODULE_EVADC.G[3].ARBPR.B.CSM0 = 0x0;    // Conversion Start Mode : Wait-for-start mode
    MODULE_EVADC.G[3].ARBPR.B.ASEN0 = 0x1;   // Arbitration Source Input 0 Enable
    MODULE_EVADC.G[3].Q[0].QMR.B.ENGT = 1;  /* Enable Conversion Requests for Queue0 */
    MODULE_EVADC.G[3].Q[0].QMR.B.FLUSH = 1; /* Clear all Entries for Queue0 */
    MODULE_EVADC.G[3].ARBCFG.B.ANONC = 0x3;  // Analog Converter : Normal Operation
    MODULE_EVADC.G[3].ICLASS[0].B.CMS = 0x0; // Group-specific Class 0
                                            // Conversion Mode : Standard Conversion (12-bit)
    /* EVADC Group 3 Channel 1 Setting */
    MODULE_EVADC.G[3].CHCTR[1].B.RESPOS = 1; // Read Results Right-aligned
    MODULE_EVADC.G[3].CHCTR[1].B.RESREG = 0; // Store Result in Group Result Register 0
    MODULE_EVADC.G[3].CHCTR[1].B.ICLSEL = 0; // Use Group-specific Class 0

    Evadc_startConversion();
}

static void Evadc_startConversion(void)
{
    /* No fill and Start Queue */
    MODULE_EVADC.G[3].Q[0].QINR.B.REQCHNR = 1;               // Request Channel Number : 0
    MODULE_EVADC.G[3].Q[0].QINR.B.RF = 1;                    // No fill : it is converted once
    MODULE_EVADC.G[3].Q[0].QMR.B.TREV = 1;                   // Generate a Trigger Event
}

unsigned int Evadc_readVR(void)
{
    unsigned int result;

    while(MODULE_EVADC.G[3].RES[0].B.VF == 0);               // Valid Flag, Wait until New Result Available

    result = (MODULE_EVADC.G[3].RES[0].B.RESULT);        // Read Result

    return result;
}
#endif
