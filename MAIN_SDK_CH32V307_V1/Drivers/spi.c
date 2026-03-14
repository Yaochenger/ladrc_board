#include "spi.h"
#include "gpio_pin.h"

static u8 SPI2_Inited = 0;
static u8 SPI3_Inited = 0;

#ifdef SDK_USING_SPI3
static u8 SPI3_TxData[1] = {0};

static void SPI3_DMA_Tx_Init(DMA_Channel_TypeDef *dma_chx,
                             u32 peripheral_addr,
                             u32 memory_addr,
                             u16 buffer_size)
{
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
    DMA_DeInit(dma_chx);

    DMA_InitStructure.DMA_PeripheralBaseAddr = peripheral_addr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memory_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = buffer_size;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(dma_chx, &DMA_InitStructure);

    DMA_ClearFlag(DMA2_FLAG_TC2);
}
#endif

static void SPI_Init_Config(SPI_TypeDef *spi_device,
                            uint32_t spi_clk,
                            const char *cs_pin,
                            const char *sck_pin,
                            const char *miso_pin,
                            const char *mosi_pin,
                            uint16_t cpol,
                            uint16_t cpha,
                            uint16_t prescaler,
                            uint16_t crc_polynomial)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    RCC_APB1PeriphClockCmd(spi_clk, ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(cs_pin) |
                           SDK_GetGPIORCC(sck_pin) |
                           SDK_GetGPIORCC(miso_pin) |
                           SDK_GetGPIORCC(mosi_pin),
                           ENABLE);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(cs_pin);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(cs_pin), &GPIO_InitStructure);
    GPIO_SetBits(SDK_GetPort(cs_pin), SDK_GetPin(cs_pin));

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(sck_pin);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SDK_GetPort(sck_pin), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(miso_pin);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SDK_GetPort(miso_pin), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(mosi_pin);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SDK_GetPort(mosi_pin), &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = cpol;
    SPI_InitStructure.SPI_CPHA = cpha;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = crc_polynomial;

    SPI_Init(spi_device, &SPI_InitStructure);
    SPI_Cmd(spi_device, ENABLE);
}

void SPI_GPIO_Init(SPI_TypeDef *spi_device)
{
#ifdef SDK_USING_SPI2
    if (spi_device == SDK_USING_SPI2_DEVICE) {
        if (SPI2_Inited) {
            return;
        }

        SPI_Init_Config(SDK_USING_SPI2_DEVICE,
                        RCC_APB1Periph_SPI2,
                        SDK_USING_SPI2_CS,
                        SDK_USING_SPI2_SCK,
                        SDK_USING_SPI2_MISO,
                        SDK_USING_SPI2_MOSI,
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
        if (SPI3_Inited) {
            return;
        }

        SPI_Init_Config(SDK_USING_SPI3_DEVICE,
                        RCC_APB1Periph_SPI3,
                        SDK_USING_SPI3_CS,
                        SDK_USING_SPI3_SCK,
                        SDK_USING_SPI3_MISO,
                        SDK_USING_SPI3_MOSI,
                        SPI_CPOL_Low,
                        SPI_CPHA_1Edge,
                        SPI_BaudRatePrescaler_2,
                        7);
        SPI_I2S_DMACmd(SDK_USING_SPI3_DEVICE, SPI_I2S_DMAReq_Tx, ENABLE);
        SPI3_DMA_Tx_Init(DMA2_Channel2,
                         (u32)&SPI3->DATAR,
                         (u32)SPI3_TxData,
                         1);
        SPI3_Inited = 1;
    }
#endif
}

u8 SPI_ReadWriteByte(SPI_TypeDef *spi_device, u8 TxData)
{
    u8 timeout = 0;

    SPI_GPIO_Init(spi_device);

#ifdef SDK_USING_SPI2
    if (spi_device == SDK_USING_SPI2_DEVICE) {
        while (SPI_I2S_GetFlagStatus(SDK_USING_SPI2_DEVICE, SPI_I2S_FLAG_TXE) == RESET) {
            timeout++;
            if (timeout > 200) {
                return 0;
            }
        }

        SPI_I2S_SendData(SDK_USING_SPI2_DEVICE, TxData);
        timeout = 0;

        while (SPI_I2S_GetFlagStatus(SDK_USING_SPI2_DEVICE, SPI_I2S_FLAG_RXNE) == RESET) {
            timeout++;
            if (timeout > 200) {
                return 0;
            }
        }

        return SPI_I2S_ReceiveData(SDK_USING_SPI2_DEVICE);
    }
#endif

#ifdef SDK_USING_SPI3
    if (spi_device == SDK_USING_SPI3_DEVICE) {
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
