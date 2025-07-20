#ifndef USER_DRIVERS_SPI2_H_
#define USER_DRIVERS_SPI2_H_
#include "drv_config.h"

void SPI2_GPIO_Init(void);
u8 SPI2_ReadWriteByte(u8 TxData);
#endif /* USER_DRIVERS_SPI2_H_ */
