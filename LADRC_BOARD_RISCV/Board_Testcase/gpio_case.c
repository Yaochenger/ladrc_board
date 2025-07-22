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
    GPIO_LED_INIT();

    for (int i = 0; i < cnt; i++)
    {
        LED_GPIO_Sample();
    }

    return 0;

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), gpio_func, gpio_func, test board gpio);
