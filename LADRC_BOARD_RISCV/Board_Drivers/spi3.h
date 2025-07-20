#ifndef USER_DRIVERS_SPI3_H_
#define USER_DRIVERS_SPI3_H_
#include "drv_config.h"

void SPI3_GPIO_Init(void);
u8 SPI3_ReadWriteByte(u8 TxData);
#endif /* USER_DRIVERS_SPI3_H_ */
