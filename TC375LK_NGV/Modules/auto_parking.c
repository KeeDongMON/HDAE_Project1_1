#include "auto_parking.h"

// 주차 공간 측정 상태

volatile ParkingState parking_state = PARKING_STATE_SEARCHING;

// 주차 공간 폭 측정 관련 변수
uint64 space_measure_start_us = 0; // 시작 시간을 us 단위로 저장

// GTM TOM 타이머 핸들
IfxGtm_Tom_Timer g_tom_timer_driver;




void calc_parking_distance(float distance)
{
    switch (parking_state)
    {
        case PARKING_STATE_SEARCHING :
            if (distance > START_THRESHOLD_CM)
            {
                parking_state = PARKING_STATE_MEASURING;

                space_measure_start_us = getTimeUs();
                my_printf("Parking space detected! Start measuring width...Distance = %.2fcm\n", distance);
            }
            else
            {
                my_printf("Searching... Distance = %.2f cm\n", distance);
            }
            break;

        case PARKING_STATE_MEASURING :
            // 현재 거리가 25cm 미만으로 들어오면 측정 종료
            if (distance < END_THRESHOLD_CM)
            {
                uint64 end_us = getTimeUs();

                uint64 elapsed_us = end_us - space_measure_start_us;

                float32 elapsed_seconds = (float32)elapsed_us / 1000000.0f;

                float32 parking_width_cm = elapsed_seconds * CAR_SPEED;

                my_printf("Measurement complete! Distance = %.2fcm, Parking space width: %.2f cm\n", distance, parking_width_cm);

//                // 다시 탐색 상태로 복귀
//                parking_state = PARKING_STATE_SEARCHING;


                Motor_movChA_PWM(50, 0);
                Motor_stopChB();

                delay_ms(1000);

                Motor_stopChA();

                while(1);
            }
            else
            {
                my_printf("Still measuring... Distance = %.2f cm\n", distance);
            }
            break;
    }
}
