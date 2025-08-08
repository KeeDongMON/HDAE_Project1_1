#include "LightButton.h"
#include "Ifx_reg.h"
#include "isr_priority.h"
#include "asclin.h"

int ledCnt = 0;
int ledOnOff = 0;
volatile int leftTurn = 0; // 임시 수신한 좌지시등
volatile int rightTurn = 0; // 임시 수신한 우지시등
volatile int HazzardLight = 0; // 임시 수신한 비상깜빡이

// 우선순위 타이머가 buzzer와 겹치기에 버저용 GPT1T3이 아닌, 비어있는 GPT2T6을 사용함.

void LightButton_Init (void) {
    /* Set P10.1 (LED2) & P10.2(LED1) as a general output pin */
    MODULE_P02.IOCR4.B.PC5 = 0x10; //10.1핀 led1 연결 -좌 방향지시등
    MODULE_P10.IOCR4.B.PC5 = 0x10; // 10.2핀 led2 연결 - 우 방향지시등
    MODULE_P10.IOCR4.B.PC4 = 0x10; // 10.3핀 led3 연결 -  비상 깜빡이-  좌우 공용

    MODULE_P02.OUT.B.P5 = 0;
    MODULE_P10.OUT.B.P5 = 0;
    MODULE_P10.OUT.B.P4 = 0;

    setLedCycle(16000);
} //

IFX_INTERRUPT(IsrGpt2T6Handler_Led, 0, ISR_PRIORITY_GPT2T6_TIMER); // buzzer.c에서 따옴. 인터럽트 방식으로 해서 while문 안의 토글 방식과 별개로 사용.
void IsrGpt2T6Handler_Led(void)
{
    __enable();
    ledCnt++;

    if (ledCnt >= ledOnOff * 2) {
        ledCnt = 0;

        // 좌측 방향지시등 제어 (P10.1)
        if (leftTurn){
            MODULE_P02.OUT.B.P5 ^= 1;
        }
        else{
            MODULE_P02.OUT.B.P5 = 0;
        }

        // 우측 방향지시등 제어 (P10.2)
        if (rightTurn) {
            MODULE_P10.OUT.B.P5 ^= 1;
        }
        else {
            MODULE_P10.OUT.B.P5 = 0;
        }

        // 비상등 제어 (P10.3)
        if (HazzardLight) {
            MODULE_P10.OUT.B.P4 ^= 1;
        }
        else {
            MODULE_P10.OUT.B.P4 = 0;
        }
    }
}

void setLedCycle(int cycle)
{
    ledOnOff = cycle;
}

void setLightButton(int Num_Led){
    switch (Num_Led)
    {
        case 1:
            leftTurn ^= 1;
            my_printf("L!\n");
            break;
        case 2:
            rightTurn ^= 1;
            my_printf("R!\n");
            break;
        case 3:
            HazzardLight ^= 1;
            my_printf("H!\n");
            break;
    }
}



/*
void setLeftTurn(int enable) // 간편 제어용. 테스트용? 블루부스로부터 버튼 데이터값 어떻게 수신하는지 몰라서 만들어둠.
{
    leftTurn = (enable != 0) ? 1 : 0;
}

void setRightTurn(int enable)
{
    rightTurn = (enable != 0) ? 1 : 0;
}

void setHazzardLight(int enable)
{
    HazzardLight = (enable != 0) ? 1 : 0;
}*/





