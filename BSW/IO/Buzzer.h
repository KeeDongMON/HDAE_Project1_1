#ifndef BUZZER_H_
#define BUZZER_H_

#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 783
#define NOTE_A5 880
#define NOTE_B5 987
#define NOTE_C6 1046

void Buzzer_Init(void);
void Buzzer_Buzz(unsigned int Hz);
void Buzzer_Beep(unsigned int Hz, int duration_ms);

void Buzzer_Up(void);
void Buzzer_Down(void);

#endif /* BUZZER_H_ */
