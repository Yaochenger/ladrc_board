/**
 * @file sdk_pin_parser.h
 * @brief SDK引脚解析器 - 将sdkconfig.h中的字符串引脚转换为GPIO常量
 * @author LADRC Board
 * @date 2026-03-12
 * 
 * @description
 * 该文件提供内联函数，用于在编译时将sdkconfig.h中定义的字符串引脚
 * （如"PB12"）转换为GPIO端口、引脚号和时钟使能常量。
 * 
 * 用法示例：
 *   GPIO_InitTypeDef gpio = {0};
 *   gpio.GPIO_Pin = SDK_GetPin(SDK_USING_SPI2_CS);
 *   gpio.GPIO_Mode = GPIO_Mode_Out_PP;
 *   gpio.GPIO_Speed = GPIO_Speed_50MHz;
 *   GPIO_Init(SDK_GetPort(SDK_USING_SPI2_CS), &gpio);
 */

#ifndef SDK_PIN_PARSER_H_
#define SDK_PIN_PARSER_H_

#include "ch32v30x.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 从字符串提取GPIO端口号
 * @param pin_str 引脚字符串，如"PB12"
 * @return GPIO端口，如GPIOB
 */
static inline GPIO_TypeDef* SDK_GetPort(const char* pin_str) {
    if (pin_str[0] != 'P') return GPIOA;
    switch (pin_str[1]) {
        case 'A': return GPIOA;
        case 'B': return GPIOB;
        case 'C': return GPIOC;
        case 'D': return GPIOD;
        case 'E': return GPIOE;
        case 'F': return GPIOF;
        case 'G': return GPIOG;
        default: return GPIOA;
    }
}

/**
 * @brief 从字符串提取GPIO引脚号
 * @param pin_str 引脚字符串，如"PB12"
 * @return GPIO引脚，如GPIO_Pin_12 (1<<12)
 */
static inline uint16_t SDK_GetPin(const char* pin_str) {
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
 * @brief 从字符串提取GPIO引脚索引（0-15）
 * @param pin_str 引脚字符串，如"PB12"
 * @return 引脚索引，如12
 */
static inline uint8_t SDK_GetPinIndex(const char* pin_str) {
    if (pin_str[0] != 'P') return 0;
    uint8_t num = 0;
    const char* ptr = pin_str + 2;
    while (*ptr >= '0' && *ptr <= '9') {
        num = num * 10 + (*ptr - '0');
        ptr++;
    }
    return num;
}

/**
 * @brief 从字符串获取GPIO时钟使能
 * @param pin_str 引脚字符串，如"PB12"
 * @return RCC时钟使能，如RCC_APB2Periph_GPIOB
 * @note CH32V307VCT6支持GPIOA-GPIOE
 */
static inline uint32_t SDK_GetGPIORCC(const char* pin_str) {
    if (pin_str[0] != 'P') return RCC_APB2Periph_GPIOA;
    switch (pin_str[1]) {
        case 'A': return RCC_APB2Periph_GPIOA;
        case 'B': return RCC_APB2Periph_GPIOB;
        case 'C': return RCC_APB2Periph_GPIOC;
        case 'D': return RCC_APB2Periph_GPIOD;
        case 'E': return RCC_APB2Periph_GPIOE;
        default: return RCC_APB2Periph_GPIOA;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* SDK_PIN_PARSER_H_ */
