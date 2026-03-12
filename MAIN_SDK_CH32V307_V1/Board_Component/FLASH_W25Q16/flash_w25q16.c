/*
 * flash_w25q16.c
 *
 *  Created on: 2024年3月21日
 *      Author: MCU
 */


/*
 *@Note
 SPI interface operation flash peripheral routine:
 Master:SPI1_SCK(PA5)銆丼PI1_MISO(PA6)銆丼PI1_MOSI(PA7).
 This example demonstrates SPI operation Winbond W25Qxx SPIFLASH.
 pins:
    CS  -- PA2
    DO  -- PA6(SPI1_MISO)
    WP   -- 3.3V
    DI   -- PA7(SPI1_MOSI)
    CLK  -- PA5(SPI1_SCK)
    HOLD -- 3.3V

*/
#include "flash_w25q16.h"

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
    SPI2_GPIO_Init();
}

u8 SPI_Flash_ReadSR(void)// 读状态寄存器
{
    u8 byte = 0;

    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI2_ReadWriteByte(W25X_ReadStatusReg);
    byte = SPI2_ReadWriteByte(0Xff);
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
    SPI2_ReadWriteByte(W25X_WriteStatusReg);
    SPI2_ReadWriteByte(sr);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
}

/*********************************************************************
 * @fn      SPI_Flash_Wait_Busy
 *
 * @brief   Wait flash free.
 *
 * @return  none
 */
void SPI_Flash_Wait_Busy(void)// 判断Flash是否在忙
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
    SPI2_ReadWriteByte(W25X_WriteEnable);
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
    SPI2_ReadWriteByte(W25X_WriteDisable);
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
    SPI2_ReadWriteByte(W25X_ManufactDeviceID);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    SPI2_ReadWriteByte(0x00);
    Temp |= SPI2_ReadWriteByte(0xFF) << 8;
    Temp |= SPI2_ReadWriteByte(0xFF);
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
    SPI2_ReadWriteByte(W25X_JedecDeviceID);
    Temp |= SPI2_ReadWriteByte(0xFF) << 16;
    Temp |= SPI2_ReadWriteByte(0xFF) << 8;
    Temp |= SPI2_ReadWriteByte(0xFF);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);

    return Temp;
}

/*********************************************************************
 * @fn      SPI_Flash_Erase_Sector
 *
 * @brief   Erase one sector(4Kbyte).
 *
 * @param   Dst_Addr - 0 锛侊紒 2047
 *
 * @return  none
 */
void SPI_Flash_Erase_Sector(u32 Dst_Addr)
{
    Dst_Addr *= 4096;
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 0);
    SPI2_ReadWriteByte(W25X_SectorErase);
    SPI2_ReadWriteByte((u8)((Dst_Addr) >> 16));
    SPI2_ReadWriteByte((u8)((Dst_Addr) >> 8));
    SPI2_ReadWriteByte((u8)Dst_Addr);
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
    SPI2_ReadWriteByte(W25X_ReadData);
    SPI2_ReadWriteByte((u8)((ReadAddr) >> 16));
    SPI2_ReadWriteByte((u8)((ReadAddr) >> 8));
    SPI2_ReadWriteByte((u8)ReadAddr);

    for(i = 0; i < size; i++)
    {
        pBuffer[i] = SPI2_ReadWriteByte(0XFF);
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
    SPI2_ReadWriteByte(W25X_PageProgram);
    SPI2_ReadWriteByte((u8)((WriteAddr) >> 16));
    SPI2_ReadWriteByte((u8)((WriteAddr) >> 8));
    SPI2_ReadWriteByte((u8)WriteAddr);

    for(i = 0; i < size; i++)
    {
        SPI2_ReadWriteByte(pBuffer[i]);
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

    pageremain = 256 - WriteAddr % 256; // 计算当前页剩余的字节数

    if(size <= pageremain) // 如果剩余字节数小于或等于要写入的数据大小
        pageremain = size; // 将剩余字节数赋值给size，因为剩余的字节数已经满足写入要求

    while(1)
    {
        SPI_Flash_Write_Page(pBuffer, WriteAddr, pageremain);// 将数据写入当前页

        if(size == pageremain)// 判断数据是否已经写入完毕
        {
            break;
        }
        else
        {
            pBuffer += pageremain;// 移动pBuffer指针向后移动pageremain个字节
            WriteAddr += pageremain;
            size -= pageremain; // 更新size

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

    secpos = WriteAddr / 4096; // 扇区号 1 2 3 ...
    secoff = WriteAddr % 4096; // 在当前扇区的偏移
    secremain = 4096 - secoff; // 当前扇区剩余可以写的空间 （不一定能写 写之前读一下检查 ）

    if(size <= secremain) // 需要写的数据 少于 当前扇区可以写的空间
        secremain = size; // 直接将剩余空间写为当前需要写的数据的数量

    while(1)
    {
        SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096);// 从当前扇区读取整个扇区的数据

        for(i = 0; i < secremain; i++)
        {
            if(SPI_FLASH_BUF[secoff + i] != 0XFF)// 判断当前扇区需要写数据的地方是否 已经擦除 Flash 只能置0  不能写1
                break;
        }

        if(i < secremain)// 当前扇区存在数据 不能直接写
        {
            SPI_Flash_Erase_Sector(secpos);// 擦除当前扇区的数据

            SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096);// 从当前扇区读取整个扇区的数据

            for(i = 0; i < 4096; i++)
            {
                printf("start \r\n ");
                printf("%d ", SPI_FLASH_BUF[i]);
                printf("end \r\n ");
            }

            for(i = 0; i < secremain; i++)
            {
                SPI_FLASH_BUF[i + secoff] = pBuffer[i];// 将需要写的数据直接拷贝到 SPI_FLASH_BUF 缓存区的对应位置
            }

            SPI_Flash_Write_NoCheck(SPI_FLASH_BUF, secpos * 4096, 4096);// 从头开始写
        }
        else
        {
            SPI_Flash_Write_NoCheck(pBuffer, WriteAddr, secremain);// 将要写数据的地方没有数据 直接写
        }

        if(size == secremain)// 剩余数据 与 需要写的数据数量一致
        {
            break;
        }
        else
        {
            secpos++; // 扇区号偏移
            secoff = 0;

            pBuffer += secremain; // 移动写buff指针 移动刚才写过的
            WriteAddr += secremain;// 写地址也同步移动
            size -= secremain; // 减去已经写的数据的个数

            if(size > 4096) // 剩余数据的数量 大于 一个扇区的数量
            {
                secremain = 4096; // 接下来写一个扇区
            }
            else
            {
                secremain = size; // 不足一个扇区  有多少写多少
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
    SPI2_ReadWriteByte(W25X_ChipErase);
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
    SPI2_ReadWriteByte(W25X_PowerDown);
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
    SPI2_ReadWriteByte(W25X_ReleasePowerDown);
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, 1);
    Delay_Us(3);
}
