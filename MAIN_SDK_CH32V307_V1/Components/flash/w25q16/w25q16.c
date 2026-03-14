/**
 * @file w25q16.c
 * @brief W25Q16/W25Qxx SPI flash driver implementation.
 */

#include "w25q16.h"

/* Temporary sector buffer used by erase-before-write logic. */
u8 SPI_FLASH_BUF[4096];

/**
 * @brief Initialize the SPI flash interface.
 */
void SPI_Flash_Init(void) {
    SPI_GPIO_Init(SDK_USING_SPI2_DEVICE);
}

/**
 * @brief Read the flash status register.
 * @return Status register value.
 */
u8 SPI_Flash_ReadSR(void) {
    u8 byte = 0;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ReadStatusReg);
    byte = SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0Xff);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

    return byte;
}

/**
 * @brief Write the flash status register.
 * @param sr Status register value.
 */
void SPI_FLASH_Write_SR(u8 sr) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_WriteStatusReg);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, sr);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/**
 * @brief Wait until the flash is no longer busy.
 */
void SPI_Flash_Wait_Busy(void) {
    while ((SPI_Flash_ReadSR() & 0x01) == 0x01)
        ;
}

/**
 * @brief Enable flash write operations.
 */
void SPI_FLASH_Write_Enable(void) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_WriteEnable);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/**
 * @brief Disable flash write operations.
 */
void SPI_FLASH_Write_Disable(void) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_WriteDisable);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/**
 * @brief Read the manufacturer/device ID.
 * @return Device ID value.
 */
u16 SPI_Flash_ReadID(void) {
    u16 Temp = 0;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ManufactDeviceID);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0x00);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0x00);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0x00);
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF) << 8;
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

    return Temp;
}

/**
 * @brief Read the JEDEC ID.
 * @return JEDEC ID value.
 */
u32 SPI_Flash_Read_JEDEC_ID(void) {
    u32 Temp = 0;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_JedecDeviceID);
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF) << 16;
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF) << 8;
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

    return Temp;
}

/**
 * @brief Erase one 4 KB sector.
 * @param Dst_Addr Sector index.
 */
void SPI_Flash_Erase_Sector(u32 Dst_Addr) {
    Dst_Addr *= 4096;
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_SectorErase);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((Dst_Addr) >> 16));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((Dst_Addr) >> 8));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)Dst_Addr);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    SPI_Flash_Wait_Busy();
}

/**
 * @brief Read data from flash.
 * @param pBuffer Destination buffer.
 * @param ReadAddr Start address.
 * @param size Number of bytes to read.
 */
void SPI_Flash_Read(u8 *pBuffer, u32 ReadAddr, u16 size) {
    u16 i;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ReadData);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((ReadAddr) >> 16));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((ReadAddr) >> 8));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)ReadAddr);

    for (i = 0; i < size; i++) {
        pBuffer[i] = SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0XFF);
    }

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/**
 * @brief Program up to one page of flash.
 * @param pBuffer Source buffer.
 * @param WriteAddr Start address.
 * @param size Number of bytes to write.
 */
void SPI_Flash_Write_Page(u8 *pBuffer, u32 WriteAddr, u16 size) {
    u16 i;

    SPI_FLASH_Write_Enable();
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_PageProgram);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((WriteAddr) >> 16));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((WriteAddr) >> 8));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)WriteAddr);

    for (i = 0; i < size; i++) {
        SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, pBuffer[i]);
    }

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    SPI_Flash_Wait_Busy();
}

/**
 * @brief Write data without checking whether erase is required.
 * @param pBuffer Source buffer.
 * @param WriteAddr Start address.
 * @param size Number of bytes to write.
 * @note This function assumes the target area is already erased.
 */
void SPI_Flash_Write_NoCheck(u8 *pBuffer, u32 WriteAddr, u16 size) {
    u16 pageremain;

    pageremain = 256 - WriteAddr % 256;

    if (size <= pageremain)
        pageremain = size;

    while (1) {
        SPI_Flash_Write_Page(pBuffer, WriteAddr, pageremain);

        if (size == pageremain) {
            break;
        } else {
            pBuffer += pageremain;
            WriteAddr += pageremain;
            size -= pageremain;

            if (size > 256)
                pageremain = 256;
            else
                pageremain = size;
        }
    }
}

/**
 * @brief Write data with automatic sector erase handling.
 * @param pBuffer Source buffer.
 * @param WriteAddr Start address.
 * @param size Number of bytes to write.
 */
void SPI_Flash_Write(u8 *pBuffer, u32 WriteAddr, u16 size) {
    u32 secpos;
    u16 secoff;
    u16 secremain;
    u16 i;

    secpos = WriteAddr / 4096;
    secoff = WriteAddr % 4096;
    secremain = 4096 - secoff;

    if (size <= secremain)
        secremain = size;

    while (1) {
        SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096);

        for (i = 0; i < secremain; i++) {
            if (SPI_FLASH_BUF[secoff + i] != 0XFF)
                break;
        }

        if (i < secremain) {
            SPI_Flash_Erase_Sector(secpos);

            SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096);

            for (i = 0; i < 4096; i++) {
                printf("start \r\n ");
                printf("%d ", SPI_FLASH_BUF[i]);
                printf("end \r\n ");
            }

            for (i = 0; i < secremain; i++) {
                SPI_FLASH_BUF[i + secoff] = pBuffer[i];
            }

            SPI_Flash_Write_NoCheck(SPI_FLASH_BUF, secpos * 4096, 4096);
        } else {
            SPI_Flash_Write_NoCheck(pBuffer, WriteAddr, secremain);
        }

        if (size == secremain) {
            break;
        } else {
            secpos++;
            secoff = 0;

            pBuffer += secremain;
            WriteAddr += secremain;
            size -= secremain;

            if (size > 4096) {
                secremain = 4096;
            } else {
                secremain = size;
            }
        }
    }
}

/**
 * @brief Erase the entire flash chip.
 */
void SPI_Flash_Erase_Chip(void) {
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ChipErase);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    SPI_Flash_Wait_Busy();
}

/**
 * @brief Enter flash power-down mode.
 */
void SPI_Flash_PowerDown(void) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_PowerDown);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    Delay_Us(3);
}

/**
 * @brief Wake the flash from power-down mode.
 */
void SPI_Flash_WAKEUP(void) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ReleasePowerDown);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    Delay_Us(3);
}
