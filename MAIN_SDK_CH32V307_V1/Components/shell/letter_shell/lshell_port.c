/**
 * @file lshell_port.c
 * @brief Letter shell platform port implementation.
 */

#include "lshell_port.h"
#include "sdkconfig.h"

Shell shell;
char shellBuffer[512];

Log uartLog = {
    .write = uartLogWrite,
    .active = 1,
    .level = LOG_DEBUG
};

/**
 * @brief Forward log output to the shell transport.
 * @param buffer Log buffer.
 * @param len Buffer length.
 */
void uartLogWrite(char *buffer, short len) {
    if (uartLog.shell) {
        shellWriteEndLine(uartLog.shell, buffer, len);
    }
}

/**
 * @brief Transmit shell output through the configured UART device.
 * @param data Data buffer.
 * @param len Number of bytes to send.
 * @return Number of bytes written.
 */
short userShellWrite(char *data, unsigned short len) {
    int i;

    for (i = 0; i < len; i++) {
        USART_SendData(SDK_USING_USART1_DEVICE, (uint8_t)data[i]);
        /* Wait until the current byte has been transmitted. */
        while (USART_GetFlagStatus(SDK_USING_USART1_DEVICE, USART_FLAG_TC) == RESET);
    }

    return len;
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/**
 * @brief USART1 receive interrupt handler for shell input.
 */
void USART1_IRQHandler(void) {
    uint8_t ch;

    if (USART_GetITStatus(SDK_USING_USART1_DEVICE, USART_IT_RXNE) != RESET) {
        ch = USART_ReceiveData(SDK_USING_USART1_DEVICE);
        shellHandler(&shell, ch);
    }
}

/**
 * @brief Initialize the shell instance and register the log object.
 */
void Shell_INIT(void) {
    shell.write = userShellWrite;
    shellInit(&shell, shellBuffer, 512);
    logRegister(&uartLog, &shell);
}
