#ifndef BSW_IO_ULTRASONIC_H_
#define BSW_IO_ULTRASONIC_H_

void Ultrasonics_Init(void);
float Ultrasonic_ReadRightSensor_noFilt(void);
float Ultrasonic_ReadRightSensor_Filt(void);
float Ultrasonic_ReadLeftSensor_noFilt(void);
float Ultrasonic_ReadLeftSensor_Filt(void);
float Ultrasonic_ReadSensor_noFilt(void);
float Ultrasonic_ReadSensor_Filt (void);

#endif /* BSW_IO_ULTRASONIC_H_ */
