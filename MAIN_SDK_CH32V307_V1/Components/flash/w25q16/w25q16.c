/**
 * @file w25q16.c
 * @brief W25Q16/W25Qxx SPI flash driver implementation.
 */

/*
 *@Note
 SPI interface operation flash peripheral routine:
 Master:SPI1_SCK(PA5)��SPI1_MISO(PA6)��SPI1_MOSI(PA7).
 This example demonstrates SPI operation Winbond W25Qxx SPIFLASH.
 pins:
    CS  -- PA2
    DO  -- PA6(SPI1_MISO)
    WP   -- 3.3V
    DI   -- PA7(SPI1_MOSI)
    CLK  -- PA5(SPI1_SCK)
    HOLD -- 3.3V

*/
#include "w25q16.h"

/* Global define */
u8       SPI_FLASH_BUF[4096];

/*********************************************************************
 * @fn      SPI_Flash_ReadSR
 *
 * @brief   Read W25Qxx status register.
 *          BIT7  6   5   4   3   2   1   0
 *          SPR   RV  TB  BP2 BP1 BP0 WEL BUSY
 *
 * @return  byte - status register value.
 */
void SPI_Flash_Init(void)
{
    SPI_GPIO_Init(SDK_USING_SPI2_DEVICE);
}

u8 SPI_Flash_ReadSR(void) // cleaned legacy comment
{
    u8 byte = 0;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ReadStatusReg);
    byte = SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0Xff);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

    return byte;
}

/*********************************************************************
 * @fn      SPI_FLASH_Write_SR
 *
 * @brief   Write W25Qxx status register.
 *
 * @param   sr - status register value.
 *
 * @return  none
 */
void SPI_FLASH_Write_SR(u8 sr)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_WriteStatusReg);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, sr);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/*********************************************************************
 * @fn      SPI_Flash_Wait_Busy
 *
 * @brief   Wait flash free.
 *
 * @return  none
 */
void SPI_Flash_Wait_Busy(void) // cleaned legacy comment
{
    while((SPI_Flash_ReadSR() & 0x01) == 0x01)
        ;
}

/*********************************************************************
 * @fn      SPI_FLASH_Write_Enable
 *
 * @brief   Enable flash write.
 *
 * @return  none
 */
void SPI_FLASH_Write_Enable(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_WriteEnable);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/*********************************************************************
 * @fn      SPI_FLASH_Write_Disable
 *
 * @brief   Disable flash write.
 *
 * @return  none
 */
void SPI_FLASH_Write_Disable(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_WriteDisable);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/*********************************************************************
 * @fn      SPI_Flash_ReadID
 *
 * @brief   Read flash ID.
 *
 * @return  Temp - FLASH ID.
 */
u16 SPI_Flash_ReadID(void)
{
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

/*********************************************************************
 * @fn      SPI_Flash_Read_JEDEC_ID
 *
 * @brief   Read flash JEDEC ID.
 *
 * @return  Temp - FLASH JEDEC ID.
 */
u32 SPI_Flash_Read_JEDEC_ID(void)
{
    u32 Temp = 0;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_JedecDeviceID);
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF) << 16;
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF) << 8;
    Temp |= SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0xFF);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

    return Temp;
}

/*********************************************************************
 * @fn      SPI_Flash_Erase_Sector
 *
 * @brief   Erase one sector(4Kbyte).
 *
 * @param   Dst_Addr - 0 ���� 2047
 *
 * @return  none
 */
void SPI_Flash_Erase_Sector(u32 Dst_Addr)
{
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

/*********************************************************************
 * @fn      SPI_Flash_Read
 *
 * @brief   Read data from flash.
 *
 * @param   pBuffer -
 *          ReadAddr -Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Read(u8 *pBuffer, u32 ReadAddr, u16 size)
{
    u16 i;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ReadData);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((ReadAddr) >> 16));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((ReadAddr) >> 8));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)ReadAddr);

    for(i = 0; i < size; i++)
    {
        pBuffer[i] = SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, 0XFF);
    }

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/*********************************************************************
 * @fn      SPI_Flash_Write_Page
 *
 * @brief   Write data by one page.
 *
 * @param   pBuffer -
 *          WriteAddr - Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Write_Page(u8 *pBuffer, u32 WriteAddr, u16 size)
{
    u16 i;

    SPI_FLASH_Write_Enable();
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_PageProgram);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((WriteAddr) >> 16));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)((WriteAddr) >> 8));
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, (u8)WriteAddr);

    for(i = 0; i < size; i++)
    {
        SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, pBuffer[i]);
    }

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    SPI_Flash_Wait_Busy();
}

/*********************************************************************
 * @fn      SPI_Flash_Write_NoCheck
 *
 * @brief   Write data to flash.(need Erase)
 *          All data in address rang is 0xFF.
 *
 * @param   pBuffer -
 *          WriteAddr - Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Write_NoCheck(u8 *pBuffer, u32 WriteAddr, u16 size)
{
    u16 pageremain;

    pageremain = 256 - WriteAddr % 256; // cleaned legacy comment

    if(size <= pageremain) // cleaned legacy comment
        pageremain = size; // cleaned legacy comment

    while(1)
    {
        SPI_Flash_Write_Page(pBuffer, WriteAddr, pageremain); // cleaned legacy comment

        if(size == pageremain) // cleaned legacy comment
        {
            break;
        }
        else
        {
            pBuffer += pageremain; // cleaned legacy comment
            WriteAddr += pageremain;
            size -= pageremain; // cleaned legacy comment

            if(size > 256)
                pageremain = 256;
            else
                pageremain = size;
        }
    }
}

/*********************************************************************
 * @fn      SPI_Flash_Write
 *
 * @brief   Write data to flash.(no need Erase)
 *
 * @param   pBuffer -
 *          WriteAddr - Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Write(u8 *pBuffer, u32 WriteAddr, u16 size)
{
    u32 secpos;
    u16 secoff;
    u16 secremain;
    u16 i;

    secpos = WriteAddr / 4096; // cleaned legacy comment
    secoff = WriteAddr % 4096; // cleaned legacy comment
    secremain = 4096 - secoff; // cleaned legacy comment

    if(size <= secremain) // cleaned legacy comment
        secremain = size; // cleaned legacy comment

    while(1)
    {
        SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096); // cleaned legacy comment

        for(i = 0; i < secremain; i++)
        {
            if(SPI_FLASH_BUF[secoff + i] != 0XFF) // cleaned legacy comment
                break;
        }

        if(i < secremain) // cleaned legacy comment
        {
            SPI_Flash_Erase_Sector(secpos); // cleaned legacy comment

            SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096); // cleaned legacy comment

            for(i = 0; i < 4096; i++)
            {
                printf("start \r\n ");
                printf("%d ", SPI_FLASH_BUF[i]);
                printf("end \r\n ");
            }

            for(i = 0; i < secremain; i++)
            {
                SPI_FLASH_BUF[i + secoff] = pBuffer[i]; // cleaned legacy comment
            }

            SPI_Flash_Write_NoCheck(SPI_FLASH_BUF, secpos * 4096, 4096); // cleaned legacy comment
        }
        else
        {
            SPI_Flash_Write_NoCheck(pBuffer, WriteAddr, secremain); // cleaned legacy comment
        }

        if(size == secremain) // cleaned legacy comment
        {
            break;
        }
        else
        {
            secpos++; // cleaned legacy comment
            secoff = 0;

            pBuffer += secremain; // cleaned legacy comment
            WriteAddr += secremain; // cleaned legacy comment
            size -= secremain; // cleaned legacy comment

            if(size > 4096) // cleaned legacy comment
            {
                secremain = 4096; // cleaned legacy comment
            }
            else
            {
                secremain = size; // cleaned legacy comment
            }
        }
    }
}

/*********************************************************************
 * @fn      SPI_Flash_Erase_Chip
 *
 * @brief   Erase all FLASH pages.
 *
 * @return  none
 */
void SPI_Flash_Erase_Chip(void)
{
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ChipErase);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    SPI_Flash_Wait_Busy();
}

/*********************************************************************
 * @fn      SPI_Flash_PowerDown
 *
 * @brief   Enter power down mode.
 *
 * @return  none
 */
void SPI_Flash_PowerDown(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_PowerDown);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    Delay_Us(3);
}

/*********************************************************************
 * @fn      SPI_Flash_WAKEUP
 *
 * @brief   Power down wake up.
 *
 * @return  none
 */
void SPI_Flash_WAKEUP(void)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI_ReadWriteByte(SDK_USING_SPI2_DEVICE, W25X_ReleasePowerDown);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    Delay_Us(3);
}

