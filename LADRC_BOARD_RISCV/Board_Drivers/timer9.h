#ifndef USER_DRIVERS_TIMER9_H_
#define USER_DRIVERS_TIMER9_H_
#include "drv_config.h"

/* PWM Output Mode Definition */
#define PWM_MODE1   0
#define PWM_MODE2   1

/* PWM Output Mode Selection */
#define PWM_MODE PWM_MODE2

void TIMER9_PWM_GPIO_Init(u16 arr, u32 psc, u16 ccp);
#endif /* USER_DRIVERS_TIMER9_H_ */
