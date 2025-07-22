#ifndef CANFD_H_
#define CANFD_H_

#include <stdio.h>
#include <string.h>
#include "Ifx_Types.h"
#include "IfxCan_Can.h"
#include "IfxCan.h"
#include "IfxCpu_Irq.h"
#include "IfxPort.h"
#include "can.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define RX_INTERRUPT_SRC_ID         IfxMultican_SrcId_1         /* RX interrupt service request ID                   */
#define INVALID_TX_DATA_VALUE       (uint8)0x55                 /* Used to invalidate TX message data content        */
#define INVALID_RX_DATA_VALUE       (uint8)0xAA                 /* Used to invalidate RX message data content        */
#define TX_DATA_INIT_SHIFT_OFFSET   6                           /* Define the shift offset value for the TX data     */
#define NUMBER_OF_CAN_FD_CASES      4                           /* Define the number of CAN FD use cases             */
#define MAXIMUM_CAN_FD_DATA_PAYLOAD 64                          /* Define maximum CAN payload in bytes               */

/*********************************************************************************************************************/
/*--------------------------------------------------Data Structures--------------------------------------------------*/
/*********************************************************************************************************************/
typedef enum {
    HS_BD_NOUSE = 0,
    HS_BD_2M = 3,
    HS_BD_4M = 4,
} CANFD_BAUDRATES;

typedef enum {
    CANFD_NODE0 = 0, /* CAN Node 0 for lite kit */
    CANFD_NODE2 = 2  /* CAN Node 2 for mikrobus */
} CANFD_NODE;

typedef struct
{
    IfxCan_Can_Config canConfig;                        /* CAN module configuration structure                        */
    IfxCan_Can canModule;                               /* CAN module handle                                         */
    IfxCan_Can_Node canSrcNode;                         /* CAN source node handle data structure                     */
    IfxCan_Can_Node canDstNode;                         /* CAN destination node handle data structure                */
    IfxCan_Can_NodeConfig canNodeConfig;                /* CAN node configuration structure                          */
    IfxCan_Filter canFilter;                            /* CAN filter configuration structure                        */
    IfxCan_Message txMsg;                               /* Transmitted CAN message structure                         */
    IfxCan_Message rxMsg;                               /* Received CAN message structure                            */
    uint8 txData[64];          /* Transmitted CAN data array                                */
    uint8 rxData[64];          /* Received CAN data array                                   */
} mcmcanType;

typedef struct
{
    uint32 messageId : 29;                              /* Define the standard or extended message ID value          */
    IfxCan_MessageIdLength messageIdLength;             /* Define the length of the message ID                       */
    IfxCan_FrameMode frameMode : 2;                     /* Define frame mode to be used                              */
    IfxCan_DataLengthCode messageLen : 4;               /* Define length of the transmitted data (number of bytes)   */
} canFdUseCaseConfigType;

typedef enum
{
    CanCommunicationStatus_Success = 0,
    CanCommunicationStatus_Error_notExpectedMessageId,
    CanCommunicationStatus_Error_notExpectedLengthCode,
    CanCommunicationStatus_Error_notExpectedFrameMode,
    CanCommunicationStatus_Error_notExpectedData
} canCommunicationStatusType;

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IFX_EXTERN uint8 g_currentCanFdUseCase;
IFX_EXTERN canCommunicationStatusType g_status;

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void CanFd_Init(CAN_BAUDRATES ls_baudrate, CANFD_BAUDRATES hs_baudrate, CANFD_NODE CANFD_Node);

void CanFd_SendMsg(unsigned int id, const char *txData, int dlc);
int CanFd_RecvMsg(unsigned int *id, char *rxData, int *len);

#endif /* CANFD_H_ */
