#ifndef MODULES_EMERGENCY_STOP_H_
#define MODULES_EMERGENCY_STOP_H_
#include "main.h"
#include "isr_priority.h"
#include "GPIO.h"
#include "can.h"
#include "motor.h"
#include "stm.h"
#include "eru.h"
#include "sys_Init.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort.h"
#include "IfxStm.h"
#include <stdint.h>
#include <stdbool.h>
#include "my_stdio.h"
#include "Motor.h"
#include "can.h"
#include "ToF.h"
#include "auto_parking.h"

//unsigned int Tof_getValue(void);
extern float current_velocity;
extern float Braking_Distance;
extern unsigned int ToftofValue;
extern float tmp_Distance;
float velocity(void);
float Get_Braking_Distance(float v);
float Deceleration_rate(void);

//void TofIsrHandler(void);//
static inline void Enable_Enc_Interrupt (void);
static inline void Disable_Enc_Interrupt (void);

#define Deceleration_rate   0.5

void Emergency_stop(void);


#endif /* MODULES_EMERGENCY_STOP_H_ */
