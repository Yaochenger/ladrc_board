


#include "spi2.h"
#include "sdk_pin_parser.h"

#ifdef SDK_USING_SPI2
void SPI2_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI2_CS), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI2_SCK), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI2_MISO), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI2_MOSI), ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // CS引脚配置 - 推挽输出
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI2_CS);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI2_CS), &GPIO_InitStructure);
    GPIO_SetBits(SDK_GetPort(SDK_USING_SPI2_CS), SDK_GetPin(SDK_USING_SPI2_CS));

    // SCK引脚配置 - 复用推挽
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI2_SCK);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI2_SCK), &GPIO_InitStructure);

    // MISO引脚配置 - 浮空输入
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI2_MISO);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI2_MISO), &GPIO_InitStructure);

    // MOSI引脚配置 - 复用推挽
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI2_MOSI);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI2_MOSI), &GPIO_InitStructure);

    // SPI配置
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SDK_USING_SPI2_DEVICE, &SPI_InitStructure);

    SPI_Cmd(SDK_USING_SPI2_DEVICE, ENABLE);
}


u8 SPI2_ReadWriteByte(u8 TxData)
{
    u8 i = 0;

    while (SPI_I2S_GetFlagStatus(SDK_USING_SPI2_DEVICE, SPI_I2S_FLAG_TXE) == RESET)
    {
        i++;
        if (i > 200)
            return 0;
    }

    SPI_I2S_SendData(SDK_USING_SPI2_DEVICE, TxData);
    i = 0;

    while (SPI_I2S_GetFlagStatus(SDK_USING_SPI2_DEVICE, SPI_I2S_FLAG_RXNE) == RESET)
    {
        i++;
        if (i > 200)
            return 0;
    }

    return SPI_I2S_ReceiveData(SDK_USING_SPI2_DEVICE);
}

#endif // SDK_USING_SPI2

