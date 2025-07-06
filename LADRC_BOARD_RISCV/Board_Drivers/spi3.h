/*
 * spi3.h
 *
 *  Created on: 2024Äê3ÔÂ16ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_SPI3_H_
#define USER_DRIVERS_SPI3_H_
#include "ch32v30x.h"

void SPI3_GPIO_Init(void);
u8 SPI3_ReadWriteByte(u8 TxData);
void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);
#endif /* USER_DRIVERS_SPI3_H_ */
