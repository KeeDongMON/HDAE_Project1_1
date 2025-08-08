#include "UltraBuzzer.h"

void UltraBuzzer_Init(void){
    Buzzer_Init();
}

void Ultrabuzzer (float distance)
{
    if (distance < 0)
    {
        setBeepCycle(0);
    }
    else if (distance > 30.0f)
    {
        setBeepCycle(0);  // 30cm 이상: 무음
    }
    else if (distance > 25.0f)
    {
        setBeepCycle(300);  // 30cm 이상: 무음
    }
    else if (distance > 23.0f)
        {
            setBeepCycle(250);  // 30cm 이상: 무음
        }
    else if (distance > 20.0f)
        {
            setBeepCycle(200);  // 30cm 이상: 무음
        }
    else if (distance > 17.0f)
        {
            setBeepCycle(150);  // 30cm 이상: 무음
        }
    else if (distance > 15.0f)
    {
        setBeepCycle(100);  // 15~30cm: 느린 비프 (6 토글 on/off)
    }
    else if (distance > 10.0f)
        {
            setBeepCycle(80);  // 15~30cm: 느린 비프 (6 토글 on/off)
        }
    else if (distance > 7.0f)
        {
            setBeepCycle(65);  // 15~30cm: 느린 비프 (6 토글 on/off)
        }
    else if (distance > 5.0f)
    {
        setBeepCycle(50);  // 5~15cm: 중간속도 비프
    }
    else
    {
        setBeepCycle(10);  // 5cm 이하: 빠른 비프 (최대로 빠른 깜빡임)
    }

}
