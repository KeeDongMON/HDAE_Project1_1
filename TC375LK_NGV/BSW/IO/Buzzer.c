#include "Ifx_reg.h"
#include "Buzzer.h"
#include "isr_priority.h"
#include "asclin.h"

int beepCnt = 0;
int beepOnOff = 0;

IFX_INTERRUPT(IsrGpt1T3Handler_Beep, 0, ISR_PRIORITY_GPT1T3_TIMER);
//void IsrGpt1T3Handler_Beep(void)
//{
//    MODULE_P02.OUT.B.P3 ^= 1;
//}

void IsrGpt1T3Handler_Beep(void)
{
    if ((beepCnt < beepOnOff) || (beepOnOff == 1)) {
        MODULE_P02.OUT.B.P3 ^= 1;
    } else if (beepCnt < beepOnOff * 2) {
        MODULE_P02.OUT.B.P3 = 0;
    } else {
        beepCnt = 0;
    }
    beepCnt++;
}

void setBeepCycle(int cycle)
{
    beepOnOff = cycle;
}

void Buzzer_Init(void)
{
    /* Set P02.3 (Buzzer) as a general output pin */
    MODULE_P02.IOCR0.B.PC3 = 0x10;
}

/* Busy wait to generate specific hertz (1 period) */
/**
 * loop: number of instruction
 * CPU frequency: 200Mhz -> 1 cycle takes 5ns
 *
 * <Calculation of loop count>
 * loop = 10^9ns(1s) / Hz / 2(half of 1 period time) / 5ns(1 cycle cpu time) / 2(each for loop takes 2 cycle time)
 */
void Buzzer_Buzz(unsigned int Hz)
{
    volatile int loop = 1000000000 / Hz / 2 / 5 / 2;
    MODULE_P02.OUT.B.P3 = 1;
    for (int i = 0; i < loop; i++);
    MODULE_P02.OUT.B.P3 = 0;
    for (int i = 0; i < loop; i++);
}

void Buzzer_Beep(unsigned int Hz, int duration_ms)
{
    float second = (float)duration_ms / 1000.0f;
    volatile unsigned int i = 0, j = Hz * second;
    while (i++ < j) {
        Buzzer_Buzz(Hz);
    }
}
