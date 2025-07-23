#include "stm.h"
#include "IfxStm.h"

uint64 getTimeUs(void)
{
    uint64 result;
    float32 frequency = 100000000.0f;

    /* Read 64-bit System Timer */
    result = MODULE_STM0.TIM0.U;
    result |= ((uint64)MODULE_STM0.CAP.U) << 32;

    /* return microseconds */
    return result / (frequency / 1000000);
}

uint64 getTimeMs(void)
{
    uint64 result;
    float32 frequency = 100000000.0f;

    /* Read 64-bit System Timer */
    result = MODULE_STM0.TIM0.U;
    result |= ((uint64)MODULE_STM0.CAP.U) << 32;

    /* return milliseconds */
    return result / (frequency / 1000);
}

