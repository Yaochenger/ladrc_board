/*
 * timer3.h
 *
 *  Created on: 2024Äê3ÔÂ23ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_TIMER3_H_
#define USER_DRIVERS_TIMER3_H_
#include "ch32f20x.h"
#include "drv_def.h"
extern LDRC_Encoder_Handler TIMER3_MOTOR;
#define TIMER3_ENCODER_COUNTING_DIR()    (((TIM3->CTLR1)&TIM_DIR) == (TIM_DIR))
void TIMER3_ENCODER_GPIO_Init(void);
#endif /* USER_DRIVERS_TIMER3_H_ */
