#include "stm.h"

uint64 getTimeUs(void)
{
    uint64 result;
    float frequency = 100000000.0f;

    /* read 64-bit System Timer */
    result = MODULE_STM0.TIM0.U;
    result |= ((uint64)MODULE_STM0.CAP.U) << 32;

    /* calculate Us */
    return result / (frequency / 1000000);
}
