#include "main.h"

int main (void)
{
    SYSTEM_Init();

    my_printf("Hello World!\n");
    while (1);
    return 0;
}

IFX_INTERRUPT(Can_RxIsrHandler, 0, ISR_PRIORITY_CAN_RX);
void Can_RxIsrHandler (void)
{
    unsigned int rxID;
    char rxData[8] = {0, };
    int rxLen;
    Can_RecvMsg(&rxID, rxData, &rxLen);
}
