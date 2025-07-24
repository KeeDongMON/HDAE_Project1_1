#include "main.h"
#include <stdio.h>
#include <string.h>

int front_duty=30;
int back_duty=30;


int main (void)
{
    SYSTEM_Init();
    Motor_Init();
    char ch;
    while (1)
    {
        ch = Bluetooth_RecvByteBlocked();

        if (ch != (char) -1)
        {
            switch (ch)
            {
                case 'w' :
                case 'W' :
                    back_duty = 30;
                    Motor_movChA_PWM(front_duty, 1);
                    Motor_movChB_PWM(front_duty, 1);
                    front_duty+=2;
                    break;
                case 'a' :
                case 'A' :
                    Motor_stopChA();
                    front_duty=30;
                    back_duty=30;
                    Motor_movChB_PWM(50, 1);
                    break;
                case 's' :
                case 'S' :
                    front_duty=30;
                    Motor_stopChA();
                    Motor_stopChB();
                    Motor_movChA_PWM(back_duty, 0);
                    Motor_movChB_PWM(back_duty, 0);
                    back_duty += 2;
                    break;
                case 'd' :
                case 'D' :
                    Motor_stopChB();
                    front_duty=30;
                    back_duty=30;
                    Motor_movChA_PWM(50, 1);
                    break;
                default :
                    Motor_stopChA();
                    Motor_stopChB();
                    front_duty=30;
                    back_duty=30;
            }
        }
    }
    return 0;
}

IFX_INTERRUPT(CanRxHandler, 0, ISR_PRIORITY_CAN_RX);
void CanRxHandler(void){
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
              front_duty=30;
              back_duty=30;
          }
       } else {
   //        my_printf("out of range!\n"); // for debugging
       }
}
