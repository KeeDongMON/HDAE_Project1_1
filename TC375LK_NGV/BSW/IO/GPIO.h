#ifndef GPIO_H_
#define GPIO_H_

#include "cpu_main.h"
#include "stm.h"

void delay_ms(uint32 ms);

#define LED1_setting MODULE_P10.IOCR0.B.PC2
#define LED2_setting MODULE_P10.IOCR0.B.PC1
#define LED1 MODULE_P10.OUT.B.P2
#define LED2 MODULE_P10.OUT.B.P1

#define SW1_setting MODULE_P02.IOCR0.B.PC0
#define SW2_setting MODULE_P02.IOCR0.B.PC1
#define SW1 MODULE_P02.IN.B.P0
#define SW2 MODULE_P02.IN.B.P1

void GPIO_Init(void);
void GPIO_SetLED(unsigned char num_LED, unsigned char onOff);
int GPIO_getSW1(void);
int GPIO_getSW2(void);
void GPIO_ToggledLED(unsigned char num_LED);

#endif /* GPIO_H_ */
