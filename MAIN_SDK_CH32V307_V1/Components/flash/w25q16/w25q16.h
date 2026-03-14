/**
 * @file w25q16.h
 * @brief W25Q16/W25Qxx SPI flash driver interface.
 */

#ifndef COMPONENTS_FLASH_W25Q16_W25Q16_H_
#define COMPONENTS_FLASH_W25Q16_W25Q16_H_

#include "spi.h"
#include "string.h"

/* Winbond SPI flash device IDs. */
#define W25Q80                   0XEF13
#define W25Q16                   0XEF14
#define W25Q32                   0XEF15
#define W25Q64                   0XEF16
#define W25Q128                  0XEF17

/* Winbond SPI flash command set. */
#define W25X_WriteEnable         0x06
#define W25X_WriteDisable        0x04
#define W25X_ReadStatusReg       0x05
#define W25X_WriteStatusReg      0x01
#define W25X_ReadData            0x03
#define W25X_FastReadData        0x0B
#define W25X_FastReadDual        0x3B
#define W25X_PageProgram         0x02
#define W25X_BlockErase          0xD8
#define W25X_SectorErase         0x20
#define W25X_ChipErase           0xC7
#define W25X_PowerDown           0xB9
#define W25X_ReleasePowerDown    0xAB
#define W25X_DeviceID            0xAB
#define W25X_ManufactDeviceID    0x90
#define W25X_JedecDeviceID       0x9F
/**
 * @brief Initialize the SPI flash hardware interface.
 */
void SPI_Flash_Init(void);

/**
 * @brief Read the status register.
 * @return Status register value.
 */
u8 SPI_Flash_ReadSR(void);

/**
 * @brief Write the status register.
 * @param sr Status register value.
 */
void SPI_FLASH_Write_SR(u8 sr);

/**
 * @brief Wait until the flash is no longer busy.
 */
void SPI_Flash_Wait_Busy(void);

/**
 * @brief Enable write operations.
 */
void SPI_FLASH_Write_Enable(void);

/**
 * @brief Disable write operations.
 */
void SPI_FLASH_Write_Disable(void);

/**
 * @brief Read the manufacturer/device ID.
 * @return Device ID value.
 */
u16 SPI_Flash_ReadID(void);

/**
 * @brief Read the JEDEC ID.
 * @return JEDEC ID value.
 */
u32 SPI_Flash_Read_JEDEC_ID(void);

/**
 * @brief Erase one 4 KB sector.
 * @param Dst_Addr Sector index.
 */
void SPI_Flash_Erase_Sector(u32 Dst_Addr);

/**
 * @brief Read data from flash.
 * @param pBuffer Destination buffer.
 * @param ReadAddr Start address.
 * @param size Number of bytes to read.
 */
void SPI_Flash_Read(u8 *pBuffer, u32 ReadAddr, u16 size);

/**
 * @brief Program up to one page.
 * @param pBuffer Source buffer.
 * @param WriteAddr Start address.
 * @param size Number of bytes to write.
 */
void SPI_Flash_Write_Page(u8 *pBuffer, u32 WriteAddr, u16 size);

/**
 * @brief Program data without checking whether erase is required.
 * @param pBuffer Source buffer.
 * @param WriteAddr Start address.
 * @param size Number of bytes to write.
 */
void SPI_Flash_Write_NoCheck(u8 *pBuffer, u32 WriteAddr, u16 size);

/**
 * @brief Write data with automatic sector erase handling.
 * @param pBuffer Source buffer.
 * @param WriteAddr Start address.
 * @param size Number of bytes to write.
 */
void SPI_Flash_Write(u8 *pBuffer, u32 WriteAddr, u16 size);

/**
 * @brief Erase the entire chip.
 */
void SPI_Flash_Erase_Chip(void);

/**
 * @brief Enter power-down mode.
 */
void SPI_Flash_PowerDown(void);

/**
 * @brief Wake the device from power-down mode.
 */
void SPI_Flash_WAKEUP(void);
#endif /* COMPONENTS_FLASH_W25Q16_W25Q16_H_ */


