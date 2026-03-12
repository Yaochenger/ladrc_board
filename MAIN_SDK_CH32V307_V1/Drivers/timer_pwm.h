#ifndef USER_DRIVERS_TIMER_PWM_H_
#define USER_DRIVERS_TIMER_PWM_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize configured TIM9 PWM outputs.
 */
void TIMER_PWM_GPIO_Init(void);

#endif /* USER_DRIVERS_TIMER_PWM_H_ */
