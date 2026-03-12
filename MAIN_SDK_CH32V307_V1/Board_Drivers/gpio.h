#ifndef USER_DRIVERS_GPIO_H_
#define USER_DRIVERS_GPIO_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize configured key pins as pull-up inputs.
 */
void KEY_GPIO_Init(void);

/**
 * @brief Initialize configured LED pins as push-pull outputs.
 */
void LED_GPIO_INIT(void);
#endif /* USER_DRIVERS_GPIO_H_ */
