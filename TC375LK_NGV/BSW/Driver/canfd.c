#include "canfd.h"
#include "isr_priority.h"
#include "syscfg.h"

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
mcmcanType                          g_mcmcanFD;                                   /* Structure for handling MCMCAN     */
canCommunicationStatusType          g_status = CanCommunicationStatus_Success;  /* Communication status variable     */
volatile uint8                      g_isrRxCount = 0; /* Declared as volatile in order not to be removed by compiler */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
//IFX_INTERRUPT(CanFd_TxIsrHandler, 0, ISR_PRIORITY_CANFD_TX);
//void CanFd_TxIsrHandler(void)
//{
//    IfxCan_Node_clearInterruptFlag(g_mcmcanFD.canSrcNode.node, IfxCan_Interrupt_transmissionCompleted);
//}

#ifndef CAN_PROJECT
IFX_INTERRUPT(CanFd_RxIsrHandler, 0, ISR_PRIORITY_CANFD_RX);
void CanFd_RxIsrHandler(void)
{
    unsigned int rxID = 0;
    char rxData[64] = {0,};
    int rxDLC = 0;
    CanFd_RecvMsg(&rxID, rxData, &rxDLC);
}
#endif

/* Function to initialize MCMCAN module and nodes related for this application use case */
void CanFd_Init(CAN_BAUDRATES ls_baudrate, CANFD_BAUDRATES hs_baudrate, CANFD_NODE CANFD_Node)
{
    /* wake up transceiver */
    IfxPort_setPinModeOutput(&MODULE_P20,6, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    MODULE_P20.OUT.B.P6 = 0;

    IfxCan_Can_initModuleConfig(&g_mcmcanFD.canConfig, &MODULE_CAN0);
    IfxCan_Can_initModule(&g_mcmcanFD.canModule, &g_mcmcanFD.canConfig);
    IfxCan_Can_initNodeConfig(&g_mcmcanFD.canNodeConfig, &g_mcmcanFD.canModule);

    switch (ls_baudrate)
    {
        case BD_NOUSE:
            g_mcmcanFD.canNodeConfig.busLoopbackEnabled = TRUE;
            break;
        case BD_500K:
            g_mcmcanFD.canNodeConfig.baudRate.baudrate = 500000;
//            IfxCan_Node_setBitTiming(&MODULE_CAN0.N[0], 80.0f, 500000, 8000, 3);
            break;
        case BD_1M:
            g_mcmcanFD.canNodeConfig.baudRate.baudrate = 1000000;
            break;
    }

    switch (hs_baudrate)
    {
        case HS_BD_NOUSE:
            g_mcmcanFD.canNodeConfig.busLoopbackEnabled = TRUE;
            break;
        case HS_BD_2M:
            g_mcmcanFD.canNodeConfig.fastBaudRate.baudrate = 2000000;
//            IfxCan_Node_setFastBitTiming(&MODULE_CAN0.N[2], 75.0f, 2000000, 8000, 1);
            break;
        case HS_BD_4M:
            g_mcmcanFD.canNodeConfig.fastBaudRate.baudrate = 4000000;
            break;
    }

    g_mcmcanFD.canNodeConfig.busLoopbackEnabled = FALSE;

    if (CANFD_Node == CANFD_NODE0) {
        g_mcmcanFD.canNodeConfig.nodeId = IfxCan_NodeId_0;
        const IfxCan_Can_Pins pins =
        {
                &IfxCan_TXD00_P20_8_OUT, IfxPort_OutputMode_pushPull, /* TX Pin for lite kit (canfd node 0) */
                &IfxCan_RXD00B_P20_7_IN, IfxPort_InputMode_pullUp, /* RX Pin for lite kit (canfd node 0) */
                IfxPort_PadDriver_cmosAutomotiveSpeed1
        };
        g_mcmcanFD.canNodeConfig.pins = &pins;
    } else if (CANFD_Node == CANFD_NODE2) {
        g_mcmcanFD.canNodeConfig.nodeId = IfxCan_NodeId_2;
        const IfxCan_Can_Pins pins =
        {
                &IfxCan_TXD02_P15_0_OUT, IfxPort_OutputMode_pushPull, /* TX Pin for mikrobus (canfd node 2) */
                &IfxCan_RXD02A_P15_1_IN, IfxPort_InputMode_pullUp, /* RX Pin for mikrobus (canfd node 2) */
                IfxPort_PadDriver_cmosAutomotiveSpeed1
        };
        g_mcmcanFD.canNodeConfig.pins = &pins;
    }

    g_mcmcanFD.canNodeConfig.frame.type = IfxCan_FrameType_transmitAndReceive;
    g_mcmcanFD.canNodeConfig.frame.mode = IfxCan_FrameMode_fdLongAndFast;
    g_mcmcanFD.canNodeConfig.txConfig.txMode = IfxCan_TxMode_dedicatedBuffers;
    g_mcmcanFD.canNodeConfig.txConfig.txBufferDataFieldSize = IfxCan_DataFieldSize_64;
    g_mcmcanFD.canNodeConfig.interruptConfig.transmissionCompletedEnabled = TRUE;
    g_mcmcanFD.canNodeConfig.interruptConfig.traco.priority = ISR_PRIORITY_CANFD_TX;
    g_mcmcanFD.canNodeConfig.interruptConfig.traco.interruptLine = IfxCan_InterruptLine_2;
    g_mcmcanFD.canNodeConfig.interruptConfig.traco.typeOfService = IfxSrc_Tos_cpu0;
    IfxCan_Can_initNode(&g_mcmcanFD.canSrcNode, &g_mcmcanFD.canNodeConfig);

    /* Reception handling configuration */
    g_mcmcanFD.canNodeConfig.rxConfig.rxMode = IfxCan_RxMode_fifo0;
    g_mcmcanFD.canNodeConfig.rxConfig.rxBufferDataFieldSize = IfxCan_DataFieldSize_64;
    g_mcmcanFD.canNodeConfig.rxConfig.rxFifo0DataFieldSize = IfxCan_DataFieldSize_64;
    g_mcmcanFD.canNodeConfig.rxConfig.rxFifo0Size = NUMBER_OF_CAN_FD_CASES;
    /* General filter configuration */
    g_mcmcanFD.canNodeConfig.filterConfig.messageIdLength = IfxCan_MessageIdLength_standard;
    g_mcmcanFD.canNodeConfig.filterConfig.standardListSize = 8;
    g_mcmcanFD.canNodeConfig.filterConfig.standardFilterForNonMatchingFrames = IfxCan_NonMatchingFrame_reject;
    g_mcmcanFD.canNodeConfig.filterConfig.rejectRemoteFramesWithStandardId = TRUE;
    /* Interrupt configuration */
    g_mcmcanFD.canNodeConfig.interruptConfig.rxFifo0NewMessageEnabled = TRUE;
    g_mcmcanFD.canNodeConfig.interruptConfig.rxf0n.priority = ISR_PRIORITY_CANFD_RX;
    g_mcmcanFD.canNodeConfig.interruptConfig.rxf0n.interruptLine = IfxCan_InterruptLine_3;
    g_mcmcanFD.canNodeConfig.interruptConfig.rxf0n.typeOfService = IfxSrc_Tos_cpu0;
    IfxCan_Can_initNode(&g_mcmcanFD.canDstNode, &g_mcmcanFD.canNodeConfig);

    /* Rx filter configuration (default: all messages are accepted) */
    g_mcmcanFD.canFilter.number = 1;
    g_mcmcanFD.canFilter.type = IfxCan_FilterType_range;
    g_mcmcanFD.canFilter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxFifo0;
    g_mcmcanFD.canFilter.id1 = 0x0;
    g_mcmcanFD.canFilter.id2 = 0x7ff;

    IfxCan_Can_setStandardFilter(&g_mcmcanFD.canDstNode, &g_mcmcanFD.canFilter);
}

void CanFd_SendMsg(unsigned int id, const char *txData, int len)
{
    /* Initialization of the TX message with the default configuration */
    IfxCan_Can_initMessage(&g_mcmcanFD.txMsg);

    g_mcmcanFD.txMsg.messageId = id;
    g_mcmcanFD.txMsg.messageIdLength = IfxCan_MessageIdLength_standard;
    g_mcmcanFD.txMsg.frameMode = IfxCan_FrameMode_fdLongAndFast;

    /* Initialization of the TX message data content */
    for (int i = 0; i < len; i++) {
        g_mcmcanFD.txData[i] = txData[i];
    }
    if (len > 48) {
        g_mcmcanFD.txMsg.dataLengthCode = 15;
    } else if (len > 32) {
        g_mcmcanFD.txMsg.dataLengthCode = 14;
    } else if (len > 24) {
        g_mcmcanFD.txMsg.dataLengthCode = 13;
    } else if (len > 20) {
        g_mcmcanFD.txMsg.dataLengthCode = 12;
    } else if (len > 16) {
        g_mcmcanFD.txMsg.dataLengthCode = 11;
    } else if (len > 12) {
        g_mcmcanFD.txMsg.dataLengthCode = 10;
    } else if (len > 8) {
        g_mcmcanFD.txMsg.dataLengthCode = 9;
    } else {
        g_mcmcanFD.txMsg.dataLengthCode = len;
    }

    /* Send the CAN message with the previously defined TX message configuration and content */
    while (IfxCan_Status_notSentBusy ==
           IfxCan_Can_sendMessage(&g_mcmcanFD.canSrcNode, &g_mcmcanFD.txMsg, (uint32*)&g_mcmcanFD.txData[0]));
}

int CanFd_RecvMsg(unsigned int *id, char *rxData, int *dlc)
{
    int err = 0;
    /* Clear the "RX FIFO 0 new message" interrupt flag */
    IfxCan_Node_clearInterruptFlag(g_mcmcanFD.canDstNode.node, IfxCan_Interrupt_rxFifo0NewMessage);

    /* Received message content should be updated with the data stored in the RX FIFO 0 */
    g_mcmcanFD.rxMsg.readFromRxFifo0 = TRUE;
    g_mcmcanFD.rxMsg.readFromRxFifo1 = FALSE;

    /* Read the received CAN message */
    IfxCan_Can_readMessage(&g_mcmcanFD.canDstNode,
                           &g_mcmcanFD.rxMsg,
                           (uint32*)&g_mcmcanFD.rxData);
    *id = g_mcmcanFD.rxMsg.messageId;
    for (int i = 0; i < 64; i++) {
        rxData[i] = g_mcmcanFD.rxData[i];
    }

    *dlc = g_mcmcanFD.rxMsg.dataLengthCode;
    if (*dlc == 15) *dlc = 64;
    else if (*dlc == 14) *dlc = 48;
    else if (*dlc == 13) *dlc = 32;
    else if (*dlc == 12) *dlc = 24;
    else if (*dlc == 11) *dlc = 20;
    else if (*dlc == 10) *dlc = 16;
    else if (*dlc == 9) *dlc = 12;

    return err;
}
