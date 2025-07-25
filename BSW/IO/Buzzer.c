//#include "Buzzer.h"
//#include "sys_init.h"
//
//void Buzzer_Init(void) {
//    MODULE_P02.IOCR0.B.PC3 = 0x10;
//}
//
//void Buzzer_Buzz(unsigned int Hz) {
//    volatile int loop = 1000000000 / Hz / 2 / 5 / 2;
//    MODULE_P02.OUT.B.P3 = 1;
//    for(int i = 0; i < loop; i++);
//    MODULE_P02.OUT.B.P3 = 0;
//    for(int i = 0; i < loop; i++);
//}
//
//void Buzzer_Beep(unsigned int Hz, int duration_ms) {
//    volatile unsigned int j = 0;
//    while(j++ < duration_ms) {
//        Buzzer_Buzz(Hz);
//    }
//}
//
//void Buzzer_Up(void) {
//    Buzzer_Beep(NOTE_C5, 30);
//    Buzzer_Beep(NOTE_D5, 30);
//    Buzzer_Beep(NOTE_E5, 30);
//    Buzzer_Beep(NOTE_F5, 30);
//    Buzzer_Beep(NOTE_G5, 30);
//    Buzzer_Beep(NOTE_A5, 30);
//    Buzzer_Beep(NOTE_B5, 30);
//    Buzzer_Beep(NOTE_C6, 30);
//}
//
//void Buzzer_Down(void) {
//    Buzzer_Beep(NOTE_C6, 30);
//    Buzzer_Beep(NOTE_B5, 30);
//    Buzzer_Beep(NOTE_A5, 30);
//    Buzzer_Beep(NOTE_G5, 30);
//    Buzzer_Beep(NOTE_F5, 30);
//    Buzzer_Beep(NOTE_E5, 30);
//    Buzzer_Beep(NOTE_D5, 30);
//    Buzzer_Beep(NOTE_C5, 30);
//}
//
////IFX_INTERRUPT(IsrGpt1T3Handler_Beep, 0, ISR_PRIORITY_GPT1T3_TIMER);
////void IsrGpt1T3Handler_Beep(void)
////{
////    MODULE_P02.OUT.B.P3 ^= 1;
////}
