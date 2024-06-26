/*
 * gpio_sample.c
 *
 *  Created on: 2024��6��10��
 *      Author: MCU
 */

#include "shell.h"
#include "led.h"

int gpio_func(int cnt)
{
    LED_GPIO_Init();

    for (int i = 0; i < cnt; i++)
    {
        LED_GPIO_Sample();
    }

    return 0;

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), gpio_func, gpio_func, test board gpio);
