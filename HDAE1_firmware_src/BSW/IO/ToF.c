#include "ToF.h"

static unsigned int g_TofValue = 0;

//IFX_INTERRUPT(TofIsrHandler, 0, ISR_PRIORITY_CAN_RX);
void TofIsrHandler(void)
{
    unsigned int rxID;
    unsigned char rxData[8] = {0,};
    int rxLen;
    Can_RecvMsg(&rxID, rxData, &rxLen);
    unsigned int tofValue = rxData[2] << 16 | rxData[1] << 8 | rxData[0];
    unsigned char dis_status = rxData[3];
    unsigned short signal_strength = rxData[5] << 8 | rxData[4];

    if (signal_strength != 0) {
       if(tofValue <= 100){
           Motor_stopChA();
           Motor_stopChB();
       }
    } else {
//        my_printf("out of range!\n"); // for debugging
    }
}

unsigned int Tof_GetValue(void)
{
    return g_TofValue;
}
