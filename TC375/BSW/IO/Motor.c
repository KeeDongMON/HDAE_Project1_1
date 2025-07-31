#include <gpt12.h>
#include <Ifx_reg.h>
#include <Ifx_Types.h>
#include <IfxGpt12.h>
#include <IfxPort.h>
#include "Motor.h"
#include "Bsp.h"
#include "isr_priority.h"
#include "gtm_atom_pwm.h"
#include "my_stdio.h"

unsigned int front_duty = 30;
unsigned int back_duty =30;

void Motor_Init(void)
{
    MODULE_P02.IOCR4.B.PC7 = 0x10;  // PWM A Break
    MODULE_P02.IOCR4.B.PC6 = 0x10;  // PWM B Break

    // Init GTM for PWM generation
    GtmAtomPwm_Init();

    // Set duty 0
    GtmAtomPwmA_SetDutyCycle(0);
    GtmAtomPwmB_SetDutyCycle(0);
}

///* 1: 정방향, 2: 역방향 */
void Motor_movChA(int dir)
{
    if(dir)
    {
        MODULE_P10.OUT.B.P1 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P1 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    MODULE_P02.OUT.B.P7 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
    GtmAtomPwm_SetDutyCycle(1000); /* 100% PWM duty  */
}

void Motor_stopChA(void)
{
    MODULE_P02.OUT.B.P7 = 1;   /* 모터 Brake 신호 인가 (1: 정지, 0: PWM-A에 따라 동작) */
}


///* 1: 정방향, 0: 역방향 */
void Motor_movChA_PWM(int duty, int dir)
{
//    GtmAtomPwm_SetDutyCycle(duty);
    GtmAtomPwmA_SetDutyCycle(duty*10);
    if(dir)
    {
        MODULE_P10.OUT.B.P1 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P1 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }

    MODULE_P02.OUT.B.P7 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
}

///* 1: 정방향, 2: 역방향 */
void Motor_movChB(int dir)
{
    if(dir)
    {
        MODULE_P10.OUT.B.P2 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P2 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    MODULE_P02.OUT.B.P6 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
    GtmAtomPwm_SetDutyCycle(1000); /* 100% PWM duty  */
}

void Motor_stopChB(void)
{
    MODULE_P02.OUT.B.P6 = 1;   /* 모터 Brake 신호 인가 (1: 정지, 0: PWM-A에 따라 동작) */
}


///* 1: 정방향, 0: 역방향 */
void Motor_movChB_PWM(int duty, int dir)
{
//    GtmAtomPwm_SetDutyCycle(duty);
    GtmAtomPwmB_SetDutyCycle(duty*10);

    if(dir)
    {
        MODULE_P10.OUT.B.P2 = 1; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }
    else {
        MODULE_P10.OUT.B.P2 = 0; /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    }

    MODULE_P02.OUT.B.P6 = 0;   /* 모터 Brake 해제 (1: 정지, 0: PWM-A에 따라 동작) */
}

void Motor_Control_CMD(char x, char y, char swL, char swR, char swP){
    my_printf("Motor 진입성공\n");

    //stop
    if(x == 'x' && y == 'x'){
        Motor_stopChA();
        Motor_stopChB();
        front_duty = 30;
        back_duty = 30; // reset
    }
    //forward(직교 위치에만 반응함 지금은)
    else if(x =='w' && y=='x'){
        Motor_movChA_PWM(front_duty,1);
        Motor_movChB_PWM(front_duty,1);
        front_duty += 2; //acceleration, TODO : 정밀 제어 수정 예정
    }
    //backward
    else if(x=='s' && y=='x'){
        Motor_movChA_PWM(back_duty,0);
        Motor_movChB_PWM(back_duty,0);
        back_duty += 2; // TODO : forward와 마찬가지
    }
    //Turn Left
    else if(x =='w' && y=='a'){
        Motor_stopChA(); // 조향 안됨. 사이드 꺼서 회전하는 방식 채택함
        Motor_movChB_PWM(50,1); // 일단 fixed value로 회전
    }
    //Trun Right
    else if(x =='w' && y == 'd'){
        Motor_stopChB();
        Motor_movChA_PWM(50,1);
    }
    // 혹시 모를 Exception처리용
    else{
        Motor_stopChA();
        Motor_stopChB();
        front_duty = 30;
        back_duty = 30;
    }

    //TODO : Switch 처리 및 추가 및 응집도 결합도 Fan-IN/Fan-OUT 고려해 Module화 진행 예정
}

