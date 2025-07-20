/*
 * adc_sample.c
 *
 *  Created on: 2024Äê6ÔÂ18ÈÕ
 *      Author: MCU
 */
#include "drv_config.h"
#include "user_peripheral_driver.h"

int adc_func(int cnt)
 {
    ADC_GPIO_Init();

    while (1)
    {
        u16 adc_val[6];

        adc_val[0] = Get_ADC_Val(ADC_Channel_4);
        adc_val[1] = Get_ADC_Val(ADC_Channel_5);
        adc_val[2] = Get_ADC_Val(ADC_Channel_12);
        adc_val[3] = Get_ADC_Val(ADC_Channel_13);
        adc_val[4] = Get_ADC_Val(ADC_Channel_14);
        adc_val[5] = Get_ADC_Val(ADC_Channel_15);

        Delay_Ms(100);

        printf("1:%04d 2:%04d 3:%04d 4:%04d 5:%04d 6:%04d \r\n",
                Get_ConversionVal(adc_val[0]), Get_ConversionVal(adc_val[1]),
                Get_ConversionVal(adc_val[2]), Get_ConversionVal(adc_val[3]),
                Get_ConversionVal(adc_val[4]), Get_ConversionVal(adc_val[5]));
    }
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), adc_func, adc_func, test board adc);

