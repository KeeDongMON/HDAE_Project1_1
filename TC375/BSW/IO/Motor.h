#ifndef BSW_IO_MOTOR_H_
#define BSW_IO_MOTOR_H_

void Motor_Init(void);

void Motor_movChA(int dir);
void Motor_stopChA(void);
void Motor_movChA_PWM(int duty, int dir);

void Motor_movChB(int dir);
void Motor_stopChB(void);
void Motor_movChB_PWM(int duty, int dir);

extern void Motor_All_Stop(void);
extern void Motor_Control_CMD(int x, int y, int swL, int swR, int swP, int dir);
extern int AEB_flag;

extern unsigned int front_duty;
extern unsigned int back_duty;

#endif /* BSW_IO_MOTOR_H_ */
