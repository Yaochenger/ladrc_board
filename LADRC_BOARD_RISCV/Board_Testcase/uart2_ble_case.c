/*
 * uart2_ble_sample.c
 *
 *  Created on: 2024Äê6ÔÂ16ÈÕ
 *      Author: MCU
 */

#include "drv_config.h"
#include "user_peripheral_driver.h"

int uart2_ble_func(int para) {

    uint16_t data = 0, cnt = 0;
    UART2_INIT();

    while (1)
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == 1)
        {
            cnt++;
            data = USART_ReceiveData(USART2);
            USART_SendData(USART2,data);
            USART_SendData(USART1,data);
            if (cnt == para)
            {
                printf("\r\r\n");
                return 0;
            }
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), uart2_ble_func, uart2_ble_func, test uart2 and ble);

