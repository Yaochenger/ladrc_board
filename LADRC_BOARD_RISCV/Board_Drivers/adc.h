#ifndef USER_DRIVERS_ADC_H_
#define USER_DRIVERS_ADC_H_
#include "drv_config.h"

void ADC_GPIO_Init(void);
u16 Get_ADC_Val(u8 ch);
u16 Get_ConversionVal(s16 val);
#endif /* USER_DRIVERS_ADC_H_ */
