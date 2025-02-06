/*
 * flash.c
 *
 *  Created on: 2024Äê6ÔÂ12ÈÕ
 *      Author: MCU
 */

#include "shell.h"
#include "flash_w25q16.h"

const u8 TEXT_Buf[] = {"LADRC BOARD SPI FLASH W25Qxx"};
#define SIZE    sizeof(TEXT_Buf)

void flash_func(int cnt) {

    u8 datap[SIZE];
    u16 Flash_Model;

    SPI_Flash_Init();

    Flash_Model = SPI_Flash_ReadID();

    switch (Flash_Model) {
    case W25Q80:
        printf("W25Q80 OK!\r\n");

        break;

    case W25Q16:
        printf("W25Q16 OK!\r\n");

        break;

    case W25Q32:
        printf("W25Q32 OK!\r\n");

        break;

    case W25Q64:
        printf("W25Q64 OK!\r\n");

        break;

    case W25Q128:
        printf("W25Q128 OK!\r\n");

        break;

    default:
        printf("Fail!\r\n");

        break;
    }
    printf("Start Erase W25Qxx....\r\n");
    SPI_Flash_Erase_Sector(0);
    printf("W25Qxx Erase Finished!\r\n");

    Delay_Ms(500);
    printf("Start Read W25Qxx....\r\n");
    SPI_Flash_Read(datap, 0x0, SIZE);
    printf("%s\r\n", datap);

    Delay_Ms(500);
    printf("Start Write W25Qxx....\r\n");
    SPI_Flash_Write((u8 *) TEXT_Buf, 0, SIZE);
    printf("W25Qxx Write Finished!\r\n");

    Delay_Ms(500);
    printf("Start Read W25Qxx....\r\n");
    SPI_Flash_Read(datap, 0x0, SIZE);
    printf("%s\r\n", datap);
    printf("\r\n");

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), flash_func, flash_func, test board flash);
