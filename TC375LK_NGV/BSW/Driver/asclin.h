#include "IfxAsclin_Asc.h"
#ifndef ASCLIN_H_
#define ASCLIN_H_

/* ASCLIN0 for micro 5-pin serial communication */
void Asclin0_InitUart(void);
void Asclin0_OutUart(const unsigned char chr);
unsigned char Asclin0_InUart(void);
char Asclin0_InUartNonBlock(void);
int Asclin0_PollUart(unsigned char *chr);

/* ASCLIN1 for Bluetooth */
void Asclin1_InitUart(void);
void Asclin1_OutUart(const unsigned char chr);
unsigned char Asclin1_InUart(void);
int Asclin1_PollUart(unsigned char *chr);

/* ASCLIN2 for S2GO1 */
void Asclin2_InitUart(void);
void Asclin2_OutUart(const unsigned char chr);
unsigned char Asclin2_InUart(void);
int Asclin2_PollUart(unsigned char *chr);

#endif /* ASCLIN_H_ */
