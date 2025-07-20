#ifndef USER_DRIVERS_TIMER5_H_
#define USER_DRIVERS_TIMER5_H_
#include "drv_config.h"

#define TIMER5_ENCODER_COUNTING_DIR()    (((TIM5->CTLR1)&TIM_DIR) == (TIM_DIR))
void TIMER5_ENCODER_GPIO_Init(void);
#endif /* USER_DRIVERS_TIMER5_H_ */
