#include "Ifx_Types.h"

#ifndef BSW_DRIVER_GTM_ATOM_PWM_H_
#define BSW_DRIVER_GTM_ATOM_PWM_H_

void GtmAtomPwm_Init(void);
void GtmAtomPwm_SetDutyCycle(uint32 dutyCycle);

void GtmAtomPwmA_SetDutyCycle(uint32 dutyCycle);
void GtmAtomPwmB_SetDutyCycle(uint32 dutyCycle);

#endif /* BSW_DRIVER_GTM_ATOM_PWM_H_ */
