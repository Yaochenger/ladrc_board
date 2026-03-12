/**
 * @file    adc.h
 * @brief   ADC driver interface.
 * @author  LADRC Board
 * @date    2026-03-12
 */

#ifndef USER_DRIVERS_ADC_H_
#define USER_DRIVERS_ADC_H_

#include "ch32v30x.h"
#include "sdkconfig.h"

/**
 * @brief Initialize ADC1 and related analog GPIO pins.
 * @note  Pins are conditionally configured only when corresponding
 *        SDK_USING_ADCx_INy macros are defined in sdkconfig.h.
 */
void ADC_GPIO_Init(void);

/**
 * @brief Read one ADC conversion result from a channel.
 * @param ch ADC channel index.
 * @return Raw ADC value (12-bit).
 */
u16 Get_ADC_Val(u8 ch);

/**
 * @brief Apply ADC calibration offset and clamp to valid range.
 * @param val Raw ADC value.
 * @return Calibrated value in range 0..4095.
 */
u16 Get_ConversionVal(s16 val);

#endif /* USER_DRIVERS_ADC_H_ */
