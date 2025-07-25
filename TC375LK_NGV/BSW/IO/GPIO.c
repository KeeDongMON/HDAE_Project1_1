#include "gpio.h"

void GPIO_Init(void) {
    LED1_setting = 0x10;
    LED2_setting = 0x10;

    SW1_setting = 0x2;
    SW2_setting = 0x2;

    MODULE_P10.OUT.B.P1 = 0;
    MODULE_P10.OUT.B.P2 = 0;
}

void GPIO_SetLED(unsigned char num_LED, unsigned char onOff) {
    if(num_LED == 1) {
        MODULE_P10.OUT.B.P1 = onOff;
    }
    else if(num_LED == 2) {
        MODULE_P10.OUT.B.P2 = onOff;
    }
}

int GPIO_getSW1(void) {
    return !(MODULE_P02.IN.B.P0);
}

int GPIO_getSW2(void) {
    return !(MODULE_P02.IN.B.P1);
}

void delay_ms(uint32 ms) {
    uint64 start_time = getTimeUs();
    uint64 target_time = start_time + (ms * 1000);

    while (getTimeUs() < target_time);
}

void GPIO_ToggledLED(unsigned char num_LED) {
    if(num_LED == 1) {
        MODULE_P10.OUT.B.P1 ^= 1;
        delay_ms(500);
    }

    else if(num_LED == 2) {
        MODULE_P10.OUT.B.P2 ^= 1;
        delay_ms(500);
    }
}
