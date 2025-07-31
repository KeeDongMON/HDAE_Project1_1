/*
 * etc.c
 */

#include "etc.h"
#include "Bsp.h"

void delay_ms(unsigned int ms)
{
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, ms));    /* Wait 500 milliseconds            */
}
