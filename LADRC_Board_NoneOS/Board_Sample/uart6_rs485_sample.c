/*
 * uart_rs485_sample.c
 *
 *  Created on: 2024Äê6ÔÂ18ÈÕ
 *      Author: MCU
 */

#include "shell.h"
#include "uart6.h"

int uart6_rs485_func(int para) {

    uint16_t data = 0, cnt = 0;
    UART6_GPIO_Init();

    while (1)
    {
        while(USART_GetFlagStatus(UART6, USART_FLAG_RXNE) == 1)
        {
            cnt++;
            data = USART_ReceiveData(UART6);
            USART_SendData(UART6,data);
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
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), uart6_rs485_func, uart6_rs485_func, test uart6 and rs485);

