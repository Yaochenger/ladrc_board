#ifndef USER_DRIVERS_SPI_H_
#define USER_DRIVERS_SPI_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize-on-demand and transfer one byte on selected SPI device.
 * @param spi_device SPI device macro from sdkconfig (for example SDK_USING_SPI2_DEVICE).
 * @param TxData Byte to transmit.
 * @return Received byte for polling mode; 0 for SPI3 DMA TX-only mode.
 */
u8 SPI_ReadWriteByte(SPI_TypeDef *spi_device, u8 TxData);

#ifdef SDK_USING_SPI2
/**
 * @brief Initialize SPI2 pins and peripheral.
 */
void SPI2_GPIO_Init(void);

/**
 * @brief Transfer one byte on SPI2 and return received data.
 */
u8 SPI2_ReadWriteByte(u8 TxData);
#endif

#ifdef SDK_USING_SPI3
/**
 * @brief Initialize SPI3 pins, peripheral, and TX DMA.
 */
void SPI3_GPIO_Init(void);

/**
 * @brief Transfer one byte on SPI3 DMA TX path.
 */
u8 SPI3_ReadWriteByte(u8 TxData);
#endif

#endif /* USER_DRIVERS_SPI_H_ */
