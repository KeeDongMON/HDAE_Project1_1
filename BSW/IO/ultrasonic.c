#include "ultrasonic.h"

#define FILT_SIZE 5

void Ultrasonics_Init(void)
{
    /* Init Ultrasonic Pin */
    MODULE_P13.IOCR0.B.PC2 = 0x10;  /* Set TRIG (P13.2)Pin to output */
    MODULE_P13.IOCR0.B.PC1 = 0x02;  /* Set ECHO (P13.1)Pin to input */
}

float Ultrasonic_ReadSensor_noFilt(void)
{
    volatile int j = 0;
    uint64 timer_start, timer_end, rear_duration;
    float distance;

    /* Send Trigger Pulse */
    MODULE_P13.OUT.B.P2 = 1;    // Rear TRIG_HIGH
    for(j = 0; j < 1000; j++) continue;

    MODULE_P13.OUT.B.P2 = 0;    // Rear TRIG_LOW
    //my_printf("trigger\n");

    /* Calculate Distance */
    while(MODULE_P13.IN.B.P1 == 0); // wait for Rear ECHO_HIGH
    timer_start = getTimeUs();
    while (MODULE_P13.IN.B.P1 == 1); // wait for Rear ECHO_LOW
    timer_end = getTimeUs();

    rear_duration = (timer_end - timer_start);
    distance = (float)0.0343 * rear_duration / 2.0;
    return distance;
}

float ReadRearUltrasonic_Filt(void)
{
    float distance_nofilt;
    static float avg_filt_buf[10] = {0, };
    static int old_index = 0;
    float distance_filt;
    static int sensorRxCnt = 0;
    distance_nofilt = Ultrasonic_ReadSensor_noFilt();
    ++old_index;
    old_index %= FILT_SIZE; // Buffer Size = 5
    avg_filt_buf[old_index] = distance_nofilt;
    sensorRxCnt++;
    /* Calculate Moving Average Filter */
    if (sensorRxCnt > FILT_SIZE)
    {
        float sum = 0;
        for (int i = 0; i < FILT_SIZE; i++)
        {
            sum += avg_filt_buf[i];
        }
        distance_filt = sum / FILT_SIZE;
    }
    else
        distance_filt = distance_nofilt;
    return distance_filt;
}
