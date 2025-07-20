/*
 * timer4.h
 *
 *  Created on: 2024��3��23��
 *      Author: MCU
 */

#ifndef USER_DRIVERS_TIMER4_H_
#define USER_DRIVERS_TIMER4_H_
#include "drv_config.h"

#define TIMER4_ENCODER_COUNTING_DIR()    (((TIM4->CTLR1)&TIM_DIR) == (TIM_DIR))
void TIMER4_ENCODER_GPIO_Init(void);
#endif /* USER_DRIVERS_TIMER4_H_ */
