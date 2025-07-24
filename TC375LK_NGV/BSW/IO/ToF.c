#include "isr_priority.h"
#include "my_stdio.h"
#include "GPIO.h"
#include "can.h"

static unsigned int g_TofValue = 0;

//IFX_INTERRUPT(TofIsrHandler, 0, ISR_PRIORITY_CAN_RX);
void TofIsrHandler(void)
{
    unsigned int rxID;
    unsigned char rxData[8] = {0,};
    int rxLen;
    Can_RecvMsg(&rxID, rxData, &rxLen);
    unsigned char dis_status = rxData[3];
    unsigned short signal_strength = rxData[5] << 8 | rxData[4];

    if (signal_strength != 0) {
        g_TofValue = rxData[2] << 16 | rxData[1] << 8 | rxData[0];
//        my_printf("TOF Distance: %d\n", g_TofValue); // for debugging
    } else {
//        my_printf("out of range!\n"); // for debugging
    }
}

unsigned int Tof_GetValue(void)
{
    return g_TofValue;
}
