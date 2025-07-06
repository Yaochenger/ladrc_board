/*
 * uart2.h
 *
 *  Created on: 2024Äê3ÔÂ15ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_UART2_H_
#define USER_DRIVERS_UART2_H_
#include "ch32f20x.h"
#include "chry_ringbuffer.h"

extern chry_ringbuffer_t chry_rbuffer_tid;

uint8_t *IsUsart1RecvFinsh(void);
void UART2_GPIO_Init(void);
#endif /* USER_DRIVERS_UART2_H_ */
