/*
 * usr_printf.h
 *
 *  Created on: 2025Äê4ÔÂ9ÈÕ
 *      Author: MCU
 */

#ifndef BOARD_COMPONENT_USR_PRINTF_USR_PRINTF_H_
#define BOARD_COMPONENT_USR_PRINTF_USR_PRINTF_H_
#include "ch32f20x.h"

void USART_SendString(USART_TypeDef* USARTx, char *str);
void ladrc_printf(USART_TypeDef* USARTx, const char *format, ...);
#endif /* BOARD_COMPONENT_USR_PRINTF_USR_PRINTF_H_ */
