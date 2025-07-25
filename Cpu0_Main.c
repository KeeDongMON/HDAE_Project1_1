#include "cpu_main.h"
#include <stdint.h>

void core0_main (void)
{
    SYSTEM_INIT();

    int duty = 30;


    float distance;

    while (1)
    {
        distance = ReadRearUltrasonic_Filt();

        calc_parking_distance(distance);

        delay_ms(500);

//        Motor_movChA_PWM(duty, 1);
//        Motor_movChB_PWM(duty, 1);
//        delay_ms(50);

        if(duty > 20) {
            duty--;
            Motor_movChA_PWM(duty, 1);
            Motor_movChB_PWM(duty, 1);
        }
    }
}
