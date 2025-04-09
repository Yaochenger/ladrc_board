/*
 * usr_printf.h
 *
 *  Created on: 2025��4��9��
 *      Author: MCU
 */

#ifndef BOARD_COMPONENT_USR_PRINTF_USR_PRINTF_H_
#define BOARD_COMPONENT_USR_PRINTF_USR_PRINTF_H_
#include "ch32v30x.h"

void ladrc_printf(USART_TypeDef *USARTx, const char *format, ...);
#endif /* BOARD_COMPONENT_USR_PRINTF_USR_PRINTF_H_ */
