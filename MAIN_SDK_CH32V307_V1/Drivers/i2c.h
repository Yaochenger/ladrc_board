/**
 * @file    i2c.h
 * @brief   I2C driver interface.
 * @author  LADRC Board
 * @date    2026-03-12
 */

#ifndef USER_DRIVERS_I2C_H_
#define USER_DRIVERS_I2C_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize I2C bus GPIO and peripheral.
 * @param bound I2C bus clock in Hz.
 * @param address Local own address.
 * @note  Uses SDK_USING_I2C2_DEVICE, SDK_USING_I2C2_SCL, and SDK_USING_I2C2_SDA.
 */
void I2C_GPIO_Init(u32 bound, u16 address);

#endif /* USER_DRIVERS_I2C_H_ */
