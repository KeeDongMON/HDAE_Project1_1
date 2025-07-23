#include <stdio.h>
#include <string.h>
#include "Bluetooth.h"
#include "asclin.h"
#include "my_stdio.h"
#include "etc.h"
#include "IfxAsclin_Asc.h"

void Bluetooth_Init(void)
{
    Asclin1_InitUart();
}

void Bluetooth_SetName(char *name)
{
    char buf[30] = {'\0',};
    int i = 0;
    sprintf(buf, "AT+NAME%s", name);

    /* Send AT Command */
    while (buf[i] != 0) {
        Asclin1_OutUart(buf[i]);
        i++;
    }
    Asclin1_OutUart(buf[i]);
    delay_ms(300);
}

void Bluetooth_SetPwd(char *pwd)
{
    char buf[30] = {'\0',};
    int i =0;
    sprintf(buf, "AT+PIN%s", pwd);

    while(buf[i] != 0)
    {
        Asclin1_OutUart(buf[i]);
        i++;
    }
    Asclin1_OutUart(buf[i]);
    delay_ms(300);
}

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
            break;
    }
    while(buf[i] != 0)
    {
        Asclin1_OutUart(buf[i]);
        i++;
    }
    Asclin1_OutUart(buf[i]);
    delay_ms(300);
}

/* AT command reference: https://www.martyncurrey.com/hc-06-zg-b23090w-bluetooth-2-0-edr-modules/ */
void Bluetooth_ATCommand(char *cmd)
{
    char buf[30];
    int i = 0;
    sprintf(buf, "%s", cmd);
    while(buf[i] != 0)
    {
        Asclin1_OutUart(buf[i]);
        i++;
    }
    Asclin1_OutUart(buf[i]);
    delay_ms(300);
}

char Bluetooth_RecvByteBlocked(void)
{
    return Asclin1_InUart();
}

char Bluetooth_RecvByteNonBlocked(void)
{
    unsigned char ch = 0;
    int res;
    res = Asclin1_PollUart(&ch);

    return res == 1 ? ch : -1;
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
        } else {
            buffer2[j++] = buffer[i];
        }
    }
    buffer2[j] = '\0';

    for (ptr = buffer2; *ptr; ++ptr)
        Bluetooth_SendByteBlocked((const unsigned char) *ptr);
}
