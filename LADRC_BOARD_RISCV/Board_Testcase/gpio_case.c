/*
 * gpio_sample.c
 *
 *  Created on: 2024Äê6ÔÂ10ÈÕ
 *      Author: MCU
 */

#include "drv_config.h"
#include "user_peripheral_driver.h"

int gpio_func(int cnt)
{
    SDK_GPIO_Init();

    for (int i = 0; i < cnt; i++)
    {
            Delay_Ms(500);
            GPIO_SetBits(GPIOD, GPIO_Pin_8);
            GPIO_SetBits(GPIOD, GPIO_Pin_10);
            Delay_Ms(500);
            GPIO_ResetBits(GPIOD, GPIO_Pin_8);
            GPIO_ResetBits(GPIOD, GPIO_Pin_10);
    }

    return 0;

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), gpio_func, gpio_func, test board gpio);
