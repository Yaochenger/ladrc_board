/**
 * @file uart2_ble_testcase.c
 * @brief UART2 BLE loopback test case.
 */

#include "ch32v30x.h"
#include "sdkconfig.h"
#include "debug.h"
#include "shell.h"

/**
 * @brief Loopback UART2 data and mirror to USART1.
 *
 * @param para Number of bytes to process before returning.
 * @return 0 on completion.
 */
int uart2_ble_func(int para)
{
#if defined(SDK_USING_USART2) && defined(SDK_USING_USART1)
    uint16_t data = 0;
    uint16_t cnt = 0;

    while (1) {
        while (USART_GetFlagStatus(SDK_USING_USART2_DEVICE, USART_FLAG_RXNE) == SET) {
            cnt++;
            data = USART_ReceiveData(SDK_USING_USART2_DEVICE);
            USART_SendData(SDK_USING_USART2_DEVICE, data);
            USART_SendData(SDK_USING_USART1_DEVICE, data);

            if (cnt == (uint16_t)para) {
                printf("\r\r\n");
                return 0;
            }
        }
    }
#else
    (void)para;
    printf("UART2/USART1 testcase disabled by sdkconfig.\r\n");
    return -1;
#endif
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 uart2_ble_func,
                 uart2_ble_func,
                 test uart2 and ble);
