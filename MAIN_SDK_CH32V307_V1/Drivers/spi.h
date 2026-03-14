#ifndef USER_DRIVERS_SPI_H_
#define USER_DRIVERS_SPI_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize selected SPI peripheral from sdkconfig.
 * @param spi_device SPI device macro from sdkconfig.
 */
void SPI_GPIO_Init(SPI_TypeDef *spi_device);

/**
 * @brief Initialize-on-demand and transfer one byte on selected SPI device.
 * @param spi_device SPI device macro from sdkconfig.
 * @param TxData Byte to transmit.
 * @return Received byte for SPI2 polling mode; 0 for SPI3 DMA TX-only mode.
 */
u8 SPI_ReadWriteByte(SPI_TypeDef *spi_device, u8 TxData);

#endif /* USER_DRIVERS_SPI_H_ */
