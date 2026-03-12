/**
 * @file    i2c.c
 * @brief   I2C driver implementation (I2C2-based by sdkconfig).
 * @author  LADRC Board
 * @date    2026-03-12
 */

#include "i2c.h"
#include "gpio_pin.h"

#if defined(SDK_USING_I2C2)

/**
 * @brief Configure I2C pins and peripheral from sdkconfig.
 * @param bound I2C bus clock in Hz.
 * @param address Local own address.
 */
void I2C_GPIO_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2C_InitTypeDef I2C_InitTSturcture = {0};

    /* Enable clocks for selected GPIO ports and I2C peripheral. */
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_I2C2_SCL), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_I2C2_SDA), ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

    /* Configure SCL and SDA as open-drain alternate function. */
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_I2C2_SCL);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_I2C2_SCL), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_I2C2_SDA);
    GPIO_Init(SDK_GetPort(SDK_USING_I2C2_SDA), &GPIO_InitStructure);

    /* Configure I2C timing and addressing mode. */
    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(SDK_USING_I2C2_DEVICE, &I2C_InitTSturcture);

    I2C_Cmd(SDK_USING_I2C2_DEVICE, ENABLE);
    I2C_AcknowledgeConfig(SDK_USING_I2C2_DEVICE, ENABLE);

    Delay_Ms(50);
}

/**
 * @brief Backward-compatible wrapper to the generic I2C initializer.
 * @param bound I2C bus clock in Hz.
 * @param address Local own address.
 */
void I2C2_GPIO_Init(u32 bound, u16 address)
{
    I2C_GPIO_Init(bound, address);
}

#endif // SDK_USING_I2C2

