#include "Ifx_reg.h"
#include "stm.h"
#include "my_stdio.h"
#include "Ultrasonic.h"

#define FILT_SIZE 5

void Ultrasonics_Init (void)
{
    /* Init Rear Ultrasonic Pin */
    MODULE_P13.IOCR0.B.PC2 = 0x10; /* Set TRIG (P13.2) Pin to output */
    MODULE_P13.IOCR0.B.PC1 = 0x02; /* Set ECHO (P13.1) Pin to input */

    /* Init right ultrasonic pin */
    MODULE_P15.IOCR0.B.PC3 = 0x10; /* Set TRIG (P02.4) Pin to output */
    MODULE_P15.IOCR0.B.PC2 = 0x02; /* Set ECHO (P02.6) Pin to input */

    /* Init left ultrasonic pin */
    MODULE_P10.IOCR4.B.PC7 = 0x10; /* Set TRIG (P10.7) Pin to output */
    MODULE_P02.IOCR8.B.PC8 = 0x10; /* Set ECHO (P02.8) Pin to input */
}

float Ultrasonic_ReadRightSensor_noFilt(void)
{
    uint64 timer_start, timer_end;
    uint64 right_duration;
    float distance;

    /* Send Trigger Pulse */
    MODULE_P15.OUT.B.P3 = 1; // TRIG_HIGH
    for (int i = 0; i < 2000; i++); // Trigger Pulse during 20us
    MODULE_P15.OUT.B.P3 = 0; // TRIG_LOW

    /* Calculate Distance */
    uint64 timeout = getTimeUs();
    while (MODULE_P15.IN.B.P2 == 0) { // wait for ECHO_HIGH
        if (getTimeUs() - timeout > 20000) return -1.0f; // if echo pin does not triggered until 20ms, return error value
    }
    timer_start = getTimeUs();
    while (MODULE_P15.IN.B.P2 == 1); // wait for ECHO_LOW
    timer_end = getTimeUs();

    right_duration = (timer_end - timer_start);
    if (right_duration > 5850) return 100.0f; // out of range
//    if (right_duration > 36000) return -1.0f; // out of range

    distance = (float) 0.0343 * right_duration / 2.0f; // cm/us

    return distance;
}

float Ultrasonic_ReadRightSensor_Filt(void)
{
    float distance_nofilt;
    static float right_avg_filt_buf[FILT_SIZE] = {0, };
    static int right_old_index = 0;
    float distance_filt;
    static int right_sensorRxCnt = 0;

    distance_nofilt = Ultrasonic_ReadRightSensor_noFilt();

    ++right_old_index;
    right_old_index %= FILT_SIZE;  // Buffer Size = 5
    right_avg_filt_buf[right_old_index] = distance_nofilt;
    right_sensorRxCnt++;

    /* Calculate Moving Average Filter */
    if (right_sensorRxCnt > FILT_SIZE)
    {
        float sum = 0;
        for (int i = 0; i < FILT_SIZE; i++)
        {
            sum += right_avg_filt_buf[i];
        }
        distance_filt = sum / FILT_SIZE;
    }
    else
        distance_filt = distance_nofilt;

    return distance_filt;
}

float Ultrasonic_ReadLeftSensor_noFilt(void)
{
    uint64 timer_start, timer_end;
    uint64 left_duration;
    float distance;

    /* Send Trigger Pulse */
    MODULE_P10.OUT.B.P7 = 1; // TRIG_HIGH
    for (int i = 0; i < 2000; i++); // Trigger Pulse during 20us
    MODULE_P10.OUT.B.P7 = 0; // TRIG_LOW

    /* Calculate Distance */
    uint64 timeout = getTimeUs();
    while (MODULE_P02.IN.B.P8 == 0) { // wait for ECHO_HIGH
        if (getTimeUs() - timeout > 20000) return -1.0f; // if echo pin does not triggered until 20ms, return error value
    }
    timer_start = getTimeUs();
    while (MODULE_P02.IN.B.P8 == 1); // wait for ECHO_LOW
    timer_end = getTimeUs();

    left_duration = (timer_end - timer_start);
    if (left_duration > 5850) return 100.0f; // out of range
//    if (left_duration > 36000) return -1.0f; // out of range

    distance = (float) 0.0343 * left_duration / 2.0f; // cm/us
    return distance;
}

float Ultrasonic_ReadLeftSensor_Filt(void)
{
    float distance_nofilt;
    static float left_avg_filt_buf[FILT_SIZE] = {0, };
    static int left_old_index = 0;
    float distance_filt;
    static int left_sensorRxCnt = 0;

    distance_nofilt = Ultrasonic_ReadLeftSensor_noFilt();

    ++left_old_index;
    left_old_index %= FILT_SIZE;  // Buffer Size = 5
    left_avg_filt_buf[left_old_index] = distance_nofilt;
    left_sensorRxCnt++;

    /* Calculate Moving Average Filter */
    if (left_sensorRxCnt > FILT_SIZE)
    {
        float sum = 0;
        for (int i = 0; i < FILT_SIZE; i++)
        {
            sum += left_avg_filt_buf[i];
        }
        distance_filt = sum / FILT_SIZE;
    }
    else
        distance_filt = distance_nofilt;

    return distance_filt;
}

float Ultrasonic_ReadSensor_noFilt (void)
{
    uint64 timer_start, timer_end;
    uint64 rear_duration;
    float distance;

    /* Send Trigger Pulse */
    MODULE_P13.OUT.B.P2 = 1; // TRIG_HIGH
    for (int i = 0; i < 2000; i++); // Trigger Pulse during 20us
    MODULE_P13.OUT.B.P2 = 0; // TRIG_LOW

    /* Calculate Distance */
    uint64 timeout = getTimeUs();
    while (MODULE_P13.IN.B.P1 == 0) { // wait for ECHO_HIGH
        if (getTimeUs() - timeout > 20000) return -1.0f; // if echo pin does not triggered until 20ms, return error value
    }
    timer_start = getTimeUs();
    while (MODULE_P13.IN.B.P1 == 1); // wait for ECHO_LOW
    timer_end = getTimeUs();

    rear_duration = (timer_end - timer_start);
    if (rear_duration > 5850) return 100.0f; // out of range
//    if (rear_duration > 36000) return -1.0f; // out of range

    distance = (float) 0.0343 * rear_duration / 2.0f; // cm/us
    return distance;
}

float Ultrasonic_ReadSensor_Filt (void)
{
    float distance_nofilt;
    static float avg_filt_buf[FILT_SIZE] = {0, };
    static int old_index = 0;
    float distance_filt;
    static int sensorRxCnt = 0;

    distance_nofilt = Ultrasonic_ReadSensor_noFilt();

    ++old_index;
    old_index %= FILT_SIZE;  // Buffer Size = 5
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
