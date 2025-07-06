/*
 * adc.h
 *
 *  Created on: 2024��6��18��
 *      Author: MCU
 */

#ifndef USER_DRIVERS_ADC_H_
#define USER_DRIVERS_ADC_H_
#include "ch32v30x.h"

void ADC_GPIO_Init(void);
u16 Get_ADC_Val(u8 ch);
u16 Get_ConversionVal(s16 val);
#endif /* USER_DRIVERS_ADC_H_ */
