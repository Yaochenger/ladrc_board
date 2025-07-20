/*
 * timer8.h
 *
 *  Created on: 2024Äê3ÔÂ23ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_TIMER8_H_
#define USER_DRIVERS_TIMER8_H_
#include "drv_config.h"

#define TIMER8_ENCODER_COUNTING_DIR()    (((TIM8->CTLR1)&TIM_DIR) == (TIM_DIR))
void TIMER8_ENCODER_GPIO_Init(void);
#endif /* USER_DRIVERS_TIMER8_H_ */
