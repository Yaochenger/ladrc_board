/*
 * timer5.h
 *
 *  Created on: 2024Äê3ÔÂ23ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_TIMER5_H_
#define USER_DRIVERS_TIMER5_H_
#include "ch32f20x.h"
#include "drv_def.h"
extern LDRC_Encoder_Handler TIMER5_MOTOR;
#define TIMER5_ENCODER_COUNTING_DIR()    (((TIM5->CTLR1)&TIM_DIR) == (TIM_DIR))
void TIMER5_ENCODER_GPIO_Init(void);
#endif /* USER_DRIVERS_TIMER5_H_ */
