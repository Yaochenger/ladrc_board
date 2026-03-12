


#include "spi3.h"
#include "sdk_pin_parser.h"

#ifdef SDK_USING_SPI3

u8 Usr_TxData[1] = {0};

static void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);
void SPI3_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI3_CS), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI3_SCK), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI3_MISO), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_SPI3_MOSI), ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    // CS引脚配置 - 推挽输出
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI3_CS);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI3_CS), &GPIO_InitStructure);
    GPIO_SetBits(SDK_GetPort(SDK_USING_SPI3_CS), SDK_GetPin(SDK_USING_SPI3_CS));

    // SCK引脚配置 - 复用推挽
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI3_SCK);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI3_SCK), &GPIO_InitStructure);

    // MISO引脚配置 - 浮空输入
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI3_MISO);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI3_MISO), &GPIO_InitStructure);

    // MOSI引脚配置 - 复用推挽
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_SPI3_MOSI);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_SPI3_MOSI), &GPIO_InitStructure);

    // SPI配置
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SDK_USING_SPI3_DEVICE, &SPI_InitStructure);
    SPI_Cmd(SDK_USING_SPI3_DEVICE, ENABLE);

    SPI_I2S_DMACmd(SDK_USING_SPI3_DEVICE, SPI_I2S_DMAReq_Tx, ENABLE);
    DMA_Tx_Init(DMA2_Channel2, (u32)&SPI3->DATAR, (u32)(Usr_TxData), 1);
}

static void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
    DMA_DeInit(DMA_CHx);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_ClearFlag(DMA2_FLAG_TC2);
}

u8 SPI3_ReadWriteByte(u8 TxData)
{
    Usr_TxData[0] = TxData;
    DMA2_Channel2->CNTR = 1;
    DMA_Cmd(DMA2_Channel2, ENABLE);
    while (DMA_GetFlagStatus(DMA2_FLAG_TC2) == RESET);
    DMA_Cmd(DMA2_Channel2, DISABLE);
    DMA_ClearFlag(DMA2_FLAG_TC2);
    return 0;
}

#endif // SDK_USING_SPI3
