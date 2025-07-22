#ifndef _SOMEIP_RAW_UDP_SOMEIP_H_
#define _SOMEIP_RAW_UDP_SOMEIP_H_

void SOMEIPSD_Init(void);
void SOMEIP_Init(void);
void SOMEIPSD_SendSubEvtGrpAck(unsigned char ip_a, unsigned char ip_b, unsigned char ip_c, unsigned char ip_d);
void SOMEIPSD_SendOfferService(unsigned char ip_a, unsigned char ip_b, unsigned char ip_c, unsigned char ip_d);

#endif /* 0_SRC_0_APPSW_TRICORE_ETHERNET_APPS_SOMEIP_RAW_UDP_SOMEIP_H_ */
