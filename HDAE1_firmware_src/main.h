#ifndef MAIN_H_
#define MAIN_H_

/* Includes BSW */
#include "Sys_Init.h"
#include "asclin.h"
#include "can.h"
#include "canfd.h"
#include "GPIO.h"
#include "etc.h"
#include "Sys_Init.h"
#include "my_stdio.h"
#include "stm.h"
#include "Ifx_Types.h"
#include <Ifx_reg.h>
#include <IfxScuWdt.h>
#include "Buzzer.h"
#include "gpt12.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "evadc.h"
#include "isr_priority.h"
#include "Ultrasonic.h"
#include "eru.h"
#include "ToF.h"
#include "geth_lwip.h"
#include "my_stdio.h"
#include "Headlight.h"
#include "UltraBuzzer.h"
#include "LightButton.h"
#include "Drive.h"
#include "auto_parking.h"
#include "Emergency_stop.h"

/* Includes ETH, TCP/IP examples */
#include "IfxGeth_Eth.h"
#include "Ifx_Lwip.h"
#include "Configuration.h"
#include "ConfigurationIsr.h"
#include "examples/can-ethernet.h"
#include "examples/DoIP.h"
#include "examples/someip.h"
#include "examples/tcp_echo.h"
#include "examples/udp_echo.h"
#include "syscfg.h"

extern volatile IfxCpu_mutexLock distLock;
#define CACHE_LINE(addr)   ((unsigned char *)((uint32)(addr) & ~0x1FU))
#define FLUSH_LINE(p)      __cacheawi(CACHE_LINE(p))   /* WB+INV 1라인 */
#define INV_LINE(p)        __cacheai (CACHE_LINE(p))   /* INV   1라인  */


#endif /* MAIN_H_ */
