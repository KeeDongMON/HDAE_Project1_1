
#ifndef BSW_DRIVER_GPT12_H_
#define BSW_DRIVER_GPT12_H_

#include "sys_init.h"
#include "IfxGpt12_reg.h"
#include "Ifx_Types.h"
#include "IfxGpt12.h"
#include "IfxPort.h"
#include "isr_priority.h"

void gpt1_init (void);
void gpt2_init(void);
void setBeepCycle(int cycle);

#endif /* BSW_DRIVER_GPT12_H_ */
