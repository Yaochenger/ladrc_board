/*
 * usr_printf.c
 *
 *  Created on: 2025Äê4ÔÂ9ÈÕ
 *      Author: MCU
 */

#include "usr_printf.h"
#include "string.h"
#include "stdarg.h"

static void USART_SendChar(USART_TypeDef* USARTx, uint8_t ch)
{
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USART_SendData(USARTx, ch);
}

void ladrc_printf(USART_TypeDef* USARTx, const char *format, ...)
{
    va_list args;
    char buffer[256];

    va_start(args, format);
    int length = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (length <= 0)
        return;

    if (length >= sizeof(buffer))
    {
        length = sizeof(buffer) - 1;
    }

    for (int i = 0; i < length; i++)
    {
        USART_SendChar(USARTx, buffer[i]);
    }
}
