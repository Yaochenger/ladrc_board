/*
 * spi2.h
 *
 *  Created on: 2024Äê3ÔÂ21ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_SPI2_H_
#define USER_DRIVERS_SPI2_H_

#include "ch32v30x.h"

void SPI2_GPIO_Init(void);
u8 SPI2_ReadWriteByte(u8 TxData);
#endif /* USER_DRIVERS_SPI2_H_ */
