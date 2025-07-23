/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_reg.h"
#include "GPIO.h"

void GPIO_Init(void)
{
    /* Set P10.1 (LED2) & P10.2(LED1) as a general output pin */
    MODULE_P10.IOCR0.B.PC1 = 0x10;
    MODULE_P10.IOCR0.B.PC2 = 0x10;

    /* Turn off led */
    GPIO_SetLed(1, 0);
    GPIO_SetLed(2, 0);

    /* Set P2.0(SW1) * P2.1(SW2) as input pull-up */
    MODULE_P02.IOCR0.B.PC0 = 0x02;
//    MODULE_P02.IOCR0.B.PC1 = 0x02;

    /* Set P00.7 (TC375 LED1) as a input pull-up */
    MODULE_P00.IOCR4.B.PC7 = 0x02;
}

void GPIO_SetLed(unsigned char num_LED, unsigned char onOff)
{
    switch (num_LED)
    {
        case 1 :
            MODULE_P10.OUT.B.P2 = onOff;
            break;
        case 2 :
            MODULE_P10.OUT.B.P1 = onOff;
            break;
    }
}

void GPIO_ToggleLed(unsigned char num_LED)
{
    switch (num_LED)
    {
        case 1:
            MODULE_P10.OUT.B.P2 ^= 1;
            break;
        case 2:
            MODULE_P10.OUT.B.P1 ^= 1;
            break;
    }
}

int GPIO_getSW1(void)
{
    return MODULE_P02.IN.B.P0 ^ 1;
}

int GPIO_getSW2(void)
{
    return MODULE_P02.IN.B.P1 ^ 1;
}

int GPIO_getSW3(void)
{
    return MODULE_P00.IN.B.P7 ^ 1;
}

int GPIO_getSWxDebounce(int sw_num)
{
    volatile int sw_state, i = 0, cnt = 0;
    volatile char buf[10] = {0, };

    while (cnt < 10000) {
        for (i = 0; i < 10; i++) {
            switch (sw_num) {
                case 1:
                    buf[i] = (char)GPIO_getSW1();
                    break;
                case 2:
                    buf[i] = (char)GPIO_getSW2();
                    break;
                case 3:
                    buf[i] = (char)GPIO_getSW3();
                    break;
            }
        }
        for (i = 0; i < 10; i++) {
            if (buf[0] != buf[i]) { cnt = 0; }
        }
        cnt += 1;
    }
    sw_state = buf[0];

    return sw_state;
}
