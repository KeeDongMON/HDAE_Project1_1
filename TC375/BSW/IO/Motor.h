#ifndef BSW_IO_MOTOR_H_
#define BSW_IO_MOTOR_H_

void Motor_Init(void);

void Motor_movChA(int dir);
void Motor_stopChA(void);
void Motor_movChA_PWM(int duty, int dir);

void Motor_movChB(int dir);
void Motor_stopChB(void);
void Motor_movChB_PWM(int duty, int dir);

extern void Motor_Control_CMD(char x, char y, char swL, char swR, char swP);

extern unsigned int front_duty;
extern unsigned int back_duty;

#endif /* BSW_IO_MOTOR_H_ */
