#include "spi.h"
#include "gpio_pin.h"

/**
 * @brief Configure CS, SCK, MISO, and MOSI pins for SPI master mode.
 */
static void SPI_ConfigPins(const char *cs, const char *sck, const char *miso, const char *mosi)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(cs), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(sck), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(miso), ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(mosi), ENABLE);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(cs);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(cs), &GPIO_InitStructure);
    GPIO_SetBits(SDK_GetPort(cs), SDK_GetPin(cs));

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(sck);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SDK_GetPort(sck), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(miso);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SDK_GetPort(miso), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(mosi);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SDK_GetPort(mosi), &GPIO_InitStructure);
}

/**
 * @brief Initialize SPI peripheral in master mode.
 */
static void SPI_InitMaster(SPI_TypeDef *spi,
                           uint16_t cpol,
                           uint16_t cpha,
                           uint16_t prescaler,
                           uint16_t crc_polynomial)
{
    SPI_InitTypeDef SPI_InitStructure = {0};

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = cpol;
    SPI_InitStructure.SPI_CPHA = cpha;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = crc_polynomial;
    SPI_Init(spi, &SPI_InitStructure);
    SPI_Cmd(spi, ENABLE);
}

/**
 * @brief Transfer one byte in polling mode.
 */
static u8 SPI_PollReadWriteByte(SPI_TypeDef *spi, u8 TxData, u8 Timeout)
{
    u8 i = 0;

    while (SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_TXE) == RESET) {
        i++;
        if (i > Timeout)
            return 0;
    }

    SPI_I2S_SendData(spi, TxData);
    i = 0;

    while (SPI_I2S_GetFlagStatus(spi, SPI_I2S_FLAG_RXNE) == RESET) {
        i++;
        if (i > Timeout)
            return 0;
    }

    return SPI_I2S_ReceiveData(spi);
}

#ifdef SDK_USING_SPI3
static u8 SPI3_TxData[1] = {0};
static u8 SPI3_Inited = 0;

/**
 * @brief Configure SPI3 TX DMA channel.
 */
static void SPI3_DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
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
#endif

#ifdef SDK_USING_SPI2
static u8 SPI2_Inited = 0;
#endif

/**
 * @brief Initialize SPI once by bus id.
 */
static void SPI_InitOnce(SPI_TypeDef *spi_device)
{
#ifdef SDK_USING_SPI2
    if (spi_device == SDK_USING_SPI2_DEVICE) {
        if (SPI2_Inited)
            return;
        SPI_ConfigPins(SDK_USING_SPI2_CS,
                       SDK_USING_SPI2_SCK,
                       SDK_USING_SPI2_MISO,
                       SDK_USING_SPI2_MOSI);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
        SPI_InitMaster(SDK_USING_SPI2_DEVICE,
                       SPI_CPOL_High,
                       SPI_CPHA_2Edge,
                       SPI_BaudRatePrescaler_4,
                       7);
        SPI2_Inited = 1;
        return;
    }
#endif

#ifdef SDK_USING_SPI3
    if (spi_device == SDK_USING_SPI3_DEVICE) {
        if (SPI3_Inited)
            return;
        SPI_ConfigPins(SDK_USING_SPI3_CS,
                       SDK_USING_SPI3_SCK,
                       SDK_USING_SPI3_MISO,
                       SDK_USING_SPI3_MOSI);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
        SPI_InitMaster(SDK_USING_SPI3_DEVICE,
                       SPI_CPOL_Low,
                       SPI_CPHA_1Edge,
                       SPI_BaudRatePrescaler_2,
                       7);
        SPI_I2S_DMACmd(SDK_USING_SPI3_DEVICE, SPI_I2S_DMAReq_Tx, ENABLE);
        SPI3_DMA_Tx_Init(DMA2_Channel2, (u32)&SPI3->DATAR, (u32)SPI3_TxData, 1);
        SPI3_Inited = 1;
        return;
    }
#endif
}

/**
 * @brief Initialize-on-demand and transfer one byte on selected SPI bus.
 */
static u8 SPI_ReadWriteByteById(SPI_TypeDef *spi_device, u8 TxData)
{
#ifdef SDK_USING_SPI2
    if (spi_device == SDK_USING_SPI2_DEVICE) {
        SPI_InitOnce(SDK_USING_SPI2_DEVICE);
        return SPI_PollReadWriteByte(SDK_USING_SPI2_DEVICE, TxData, 200);
    }
#endif

#ifdef SDK_USING_SPI3
    if (spi_device == SDK_USING_SPI3_DEVICE) {
        SPI_InitOnce(SDK_USING_SPI3_DEVICE);
        SPI3_TxData[0] = TxData;
        DMA2_Channel2->CNTR = 1;
        DMA_Cmd(DMA2_Channel2, ENABLE);
        while (DMA_GetFlagStatus(DMA2_FLAG_TC2) == RESET)
            ;
        DMA_Cmd(DMA2_Channel2, DISABLE);
        DMA_ClearFlag(DMA2_FLAG_TC2);
        return 0;
    }
#endif

    return 0;
}

/**
 * @brief Initialize-on-demand and transfer one byte on selected SPI device.
 */
u8 SPI_ReadWriteByte(SPI_TypeDef *spi_device, u8 TxData)
{
    return SPI_ReadWriteByteById(spi_device, TxData);
}

#ifdef SDK_USING_SPI2
/**
 * @brief Initialize SPI2 pins and peripheral.
 */
void SPI2_GPIO_Init(void)
{
    SPI_InitOnce(SDK_USING_SPI2_DEVICE);
}

/**
 * @brief Transfer one byte through SPI2.
 */
u8 SPI2_ReadWriteByte(u8 TxData)
{
    return SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, TxData);
}
#endif

#ifdef SDK_USING_SPI3
/**
 * @brief Initialize SPI3 pins, peripheral, and TX DMA.
 */
void SPI3_GPIO_Init(void)
{
    SPI_InitOnce(SDK_USING_SPI3_DEVICE);
}

/**
 * @brief Transfer one byte through SPI3 TX DMA.
 * @return Always 0 in TX-only DMA mode.
 */
u8 SPI3_ReadWriteByte(u8 TxData)
{
    return SPI_ReadWriteByte(SDK_USING_SPI3_DEVICE, TxData);
}
#endif

