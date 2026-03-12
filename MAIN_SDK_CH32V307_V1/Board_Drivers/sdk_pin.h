/**
 * @file    sdk_pin.h
 * @brief   Parse pin strings (for example, "PB12") to GPIO constants.
 * @author  LADRC Board
 * @date    2026-03-12
 * @note    Invalid input falls back to GPIOA, GPIO_Pin_0, index 0, or RCC_APB2Periph_GPIOA.
 */

/**
 * @defgroup SDK_PIN SDK pin parser
 * @brief Utilities to convert pin strings into GPIO-related values.
 * @{
 */

#ifndef SDK_PIN_H_
#define SDK_PIN_H_

#include "ch32v30x.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name API Prototypes
 * @brief Centralized function declarations for quick lookup.
 * @{
 */
static inline GPIO_TypeDef* SDK_GetPort(const char* pin_str);
static inline uint16_t SDK_GetPin(const char* pin_str);
static inline uint8_t SDK_GetPinIndex(const char* pin_str);
static inline uint32_t SDK_GetGPIORCC(const char* pin_str);
/** @} */

/**
 * @defgroup SDK_PIN_PORT GPIO port parser
 * @{
 */

/**
 * @brief  Get GPIO port from pin string.
 * @param  pin_str Pin string, for example "PB12".
 * @return GPIO port pointer (GPIOA to GPIOE).
 */
static inline GPIO_TypeDef* SDK_GetPort(const char* pin_str)
{
    if (pin_str[0] != 'P') return GPIOA;

    switch (pin_str[1]) {
        case 'A': return GPIOA;
        case 'B': return GPIOB;
        case 'C': return GPIOC;
        case 'D': return GPIOD;
        case 'E': return GPIOE;
        default:  return GPIOA;
    }
}

/** @} */

/**
 * @defgroup SDK_PIN_NUM GPIO pin parser
 * @{
 */

/**
 * @brief  Get GPIO pin mask from pin string.
 * @param  pin_str Pin string, for example "PB12".
 * @return GPIO pin mask (GPIO_Pin_0 to GPIO_Pin_15).
 */
static inline uint16_t SDK_GetPin(const char* pin_str)
{
    if (pin_str[0] != 'P') return GPIO_Pin_0;

    uint8_t num = 0;
    const char* ptr = pin_str + 2;

    while (*ptr >= '0' && *ptr <= '9') {
        num = num * 10 + (*ptr - '0');
        ptr++;
    }

    return (uint16_t)(1 << num);
}

/**
 * @brief  Get GPIO pin index from pin string.
 * @param  pin_str Pin string, for example "PB12".
 * @return Pin index in range 0 to 15.
 */
static inline uint8_t SDK_GetPinIndex(const char* pin_str)
{
    if (pin_str[0] != 'P') return 0;

    uint8_t num = 0;
    const char* ptr = pin_str + 2;

    while (*ptr >= '0' && *ptr <= '9') {
        num = num * 10 + (*ptr - '0');
        ptr++;
    }

    return num;
}

/** @} */

/**
 * @defgroup SDK_PIN_RCC GPIO clock parser
 * @{
 */

/**
 * @brief  Get RCC GPIO clock bit from pin string.
 * @param  pin_str Pin string, for example "PB12".
 * @return RCC GPIO clock bit (RCC_APB2Periph_GPIOA to GPIOE).
 */
static inline uint32_t SDK_GetGPIORCC(const char* pin_str)
{
    if (pin_str[0] != 'P') return RCC_APB2Periph_GPIOA;

    switch (pin_str[1]) {
        case 'A': return RCC_APB2Periph_GPIOA;
        case 'B': return RCC_APB2Periph_GPIOB;
        case 'C': return RCC_APB2Periph_GPIOC;
        case 'D': return RCC_APB2Periph_GPIOD;
        case 'E': return RCC_APB2Periph_GPIOE;
        default:  return RCC_APB2Periph_GPIOA;
    }
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SDK_PIN_H_ */
