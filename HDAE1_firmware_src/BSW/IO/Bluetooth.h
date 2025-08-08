#ifndef BSW_IO_BLUETOOTH_H_
#define BSW_IO_BLUETOOTH_H_

void Bluetooth_Init(void);
void Bluetooth_SetName(char *name);
void Bluetooth_SetPwd(char *pwd);
void Bluetooth_ATCommand(char *cmd);
char Bluetooth_RecvByteBlocked(void);
char Bluetooth_RecvByteNonBlocked(void);
void Bluetooth_SendByteBlocked(unsigned char ch);
void Bluetooth_printf(const char *fmt, ...);

#endif /* BSW_IO_BLUETOOTH_H_ */
