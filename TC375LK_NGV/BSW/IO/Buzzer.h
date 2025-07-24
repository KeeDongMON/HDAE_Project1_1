#ifndef BSW_IO_BUZZER_H_
#define BSW_IO_BUZZER_H_

/* Hertz of 5 Octave(C5 to B5) */
#define NOTE_C5 523  // 5옥타브 도
#define NOTE_D5 587  // 5옥타브 레
#define NOTE_E5 659  // 5옥타브 미
#define NOTE_F5 698  // 5옥타브 파
#define NOTE_G5 783  // 5옥타브 솔
#define NOTE_A5 880  // 5옥타브 라
#define NOTE_B5 987  // 5옥타브 시
#define NOTE_C6 1046 // 6옥타브 도

void setBeepCycle(int cycle);
void Buzzer_Init(void);
void Buzzer_Buzz(unsigned int Hz);
void Buzzer_Beep(unsigned int Hz, int duration_ms);

#endif /* BSW_IO_BUZZER_H_ */
