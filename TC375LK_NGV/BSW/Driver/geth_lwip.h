#ifndef BSW_DRIVER_GETH_LWIP_H_
#define BSW_DRIVER_GETH_LWIP_H_

#include "Ifx_Lwip.h"

void initLwip(eth_addr_t mac);
void geth_sendETH(uint8 *destAddr, uint8 *payload, int payloadLength);
int geth_recvETH(uint8 *buf);

#endif /* BSW_DRIVER_GETH_LWIP_H_ */
