#include "Bluetooth.h"

#include <stdio.h>
#include <string.h>
#include "Bluetooth.h"
#include "asclin.h"
#include "my_stdio.h"
//#include "etc.h"
#include "IfxAsclin_Asc.h"
#include "isr_priority.h"


void Bluetooth_Init(void)
{
    Asclin1_InitUart();
    delay_ms(1000);
}

void Bluetooth_SetName(char *name)
{
    char buf[30];
    int i = 0;
    sprintf(buf, "AT+NAME%s", name);

    while(buf[i] != 0) {
        Asclin1_OutUart(buf[i]);
        i++;
    }
    delay_ms(3000);
}

void Bluetooth_SetPwd(char *pwd)
{
    char buf[30];
    int i = 0;
    sprintf(buf, "AT+PIN%s", pwd);

    while(buf[i] != 0) {
        Asclin1_OutUart(buf[i]);
        i++;
    }
    delay_ms(3000);
}

char Bluetooth_RecvByteBlocked()
{
    return Asclin1_InUart();
}

char Bluetooth_RecvByteNonBlocked()
{
    unsigned char ch;
    int res;
    res = Asclin1_PollUart(&ch);
    if(res == 1)
        return ch;
    else
        return -1;
}

void Bluetooth_SendByteBlocked(unsigned char ch)
{
    Asclin1_OutUart(ch);
}

void Bluetooth_printf(const char *fmt, ...)
{
   char buffer[128];
   char buffer2[128]; // add \r before \n
   char *ptr;
   va_list ap;
   va_start(ap, fmt);
   vsprintf(buffer, fmt, ap);
   va_end(ap);
   int j = 0;
   for (int i = 0; buffer[i]; i++) {
      if (buffer[i] == '\n') {
         buffer2[j++] = '\r';
         buffer2[j++] = buffer[i];
      }
      else {
         buffer2[j++] = buffer[i];
      }
   }

   buffer2[j] = '\0';


   for (ptr = buffer2; *ptr; ++ptr)
      Bluetooth_SendByteBlocked((const unsigned char) *ptr);
}

/*
void Bluetooth_SetBaud(int baudrate)
{
    char buf[30];
    int i = 0;
    switch (baudrate) {
        case 9600:
            sprintf(buf, "AT+BAUD4");
            break;
        case 115200:
            sprintf(buf, "AT+BAUD8");
    }
}
*/
