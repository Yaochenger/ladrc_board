/*
 * usr_printf.c
 *
 *  Created on: 2025年4月9日
 *      Author: MCU
 */

#include "usr_printf.h"
#include "string.h"
#include "stdarg.h"

void USART_SendChar(USART_TypeDef* USARTx, char ch)
{
    if (USARTx == NULL) return;
    USART_SendData(USARTx, (uint8_t)ch);
    uint32_t timeout = 100000;
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET && timeout > 0) {
        timeout--;
    }
}


void USART_SendString(USART_TypeDef* USARTx, const char* str)
{
    if (USARTx == NULL || str == NULL) return;
    while (*str) {
        USART_SendChar(USARTx, *str++);
    }
}

void ladrc_printf(USART_TypeDef* USARTx, const char* format, ...)
{
    if (USARTx == NULL || format == NULL) return;
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    int num = va_arg(args, int);
                    char buffer[12];
                    int i = 0;
                    int is_negative = 0;

                    if (num < 0) {
                        is_negative = 1;
                        num = -num;
                    }

                    if (num == 0) {
                        USART_SendChar(USARTx, '0');
                    } else {
                        while (num > 0) {
                            buffer[i++] = num % 10 + '0';
                            num /= 10;
                        }

                        if (is_negative) {
                            USART_SendChar(USARTx, '-');
                        }

                        for (int j = i - 1; j >= 0; j--) {
                            USART_SendChar(USARTx, buffer[j]);
                        }
                    }
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    USART_SendString(USARTx, str);
                    break;
                }
                case 'f': {
                    double num = va_arg(args, double);
                    int integer_part = (int)num;
                    double decimal_part = num - integer_part;
                    if (num < 0) {
                        USART_SendChar(USARTx, '-');
                        integer_part = -integer_part;
                        decimal_part = -decimal_part;
                    }

                    // 处理整数部分
                    char buffer[12];
                    int i = 0;
                    if (integer_part == 0) {
                        USART_SendChar(USARTx, '0');
                    } else {
                        while (integer_part > 0) {
                            buffer[i++] = integer_part % 10 + '0';
                            integer_part /= 10;
                        }
                        for (int j = i - 1; j >= 0; j--) {
                            USART_SendChar(USARTx, buffer[j]);
                        }
                    }

                    // 处理小数点
                    USART_SendChar(USARTx, '.');

                    // 处理小数部分，这里取4位小数
                    int precision = 4;
                    for (int k = 0; k < precision; k++) {
                        decimal_part *= 10;
                        int digit = (int)decimal_part;
                        USART_SendChar(USARTx, digit + '0');
                        decimal_part -= digit;
                    }
                    break;
                }
                default:
                    USART_SendChar(USARTx, *format);
                    break;
            }
        } else {
            USART_SendChar(USARTx, *format);
        }
        format++;
    }

    va_end(args);
}
