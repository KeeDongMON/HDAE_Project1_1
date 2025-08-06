#ifndef BSW_DRIVER_ISR_PRIORITY_H_
#define BSW_DRIVER_ISR_PRIORITY_H_

/* Definition of the interrupt priorities */
/* High value - higher priority */
#define ISR_PRIORITY_ASCLIN0_RX     18
#define ISR_PRIORITY_ASCLIN0_TX     19


#define ISR_PRIORITY_CAN_TX         2       /* Define the CAN TX interrupt priority */
#define ISR_PRIORITY_CAN_RX         1       /* Define the CAN RX interrupt priority */

#define ISR_PRIORITY_CANFD_RX       3       /* Define the CAN RX interrupt priority */
#define ISR_PRIORITY_CANFD_TX       4       /* Define the CAN TX interrupt priority */

#define ISR_PRIORITY_BLE_RX         15
#define ISR_PRIORITY_BLE_TX         16

#define ISR_PRIORITY_ERU_INT0       17


#define ISR_PRIORITY_GPT1T3_TIMER   5       /* Define the GPT12 Timer interrupt priority  */
#define ISR_PRIORITY_GPT2T6_TIMER   6       /* Define the GPT12 Timer interrupt priority  */

#define ISR_PRIORITY_ATOM           20

#endif /* BSW_DRIVER_ISR_PRIORITY_H_ */
