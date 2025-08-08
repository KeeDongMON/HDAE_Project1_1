#ifndef BSW_DRIVER_HEADLIGHT_H_
#define BSW_DRIVER_HEADLIGHT_H_

#include "GPIO.h"
#include "Evadc.h"
#include "gtm_atom_pwm.h"
#include "my_stdio.h"
#include "main.h"

void HBA_ON(void);
void HBA_OFF(void);
void HBA_Init(void);

#endif /* BSW_DRIVER_HEADLIGHT_H_ */
