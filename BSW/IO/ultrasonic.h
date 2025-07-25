
#ifndef BSW_IO_ULTRASONIC_H_
#define BSW_IO_ULTRASONIC_H_

#include "sys_init.h"
#include "stm.h"

void Ultrasonics_Init(void);
float Ultrasonic_ReadSensor_noFilt(void);
float ReadRearUltrasonic_Filt(void);

#endif /* BSW_IO_ULTRASONIC_H_ */
