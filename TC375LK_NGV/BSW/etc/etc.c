/*
 * etc.c
 *
 *  Created on: 2024. 8. 15.
 *      Author: kimye
 */

#include "etc.h"
#include "Bsp.h"

void delay_ms(unsigned int ms)
{
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, ms));    /* Wait 500 milliseconds            */
}
