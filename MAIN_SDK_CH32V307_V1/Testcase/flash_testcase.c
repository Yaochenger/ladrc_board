/**
 * @file flash_testcase.c
 * @brief W25Qxx flash test case.
 */

#include "ch32v30x.h"
#include "sdkconfig.h"
#include "debug.h"
#include "w25q16.h"
#include "shell.h"

#define FLASH_TEST_SIZE (sizeof(TEXT_Buf))

static const u8 TEXT_Buf[] = {"LADRC BOARD SPI FLASH W25Qxx"};

/**
 * @brief Erase, write and read W25Qxx flash.
 *
 * @param cnt Unused.
 */
void flash_func(int cnt)
{
    u8 datap[FLASH_TEST_SIZE];
    u16 flash_model;

    (void)cnt;

    SPI_Flash_Init();
    flash_model = SPI_Flash_ReadID();

    switch (flash_model) {
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
    SPI_Flash_Read(datap, 0x0, FLASH_TEST_SIZE);
    printf("%s\r\n", datap);

    Delay_Ms(500);
    printf("Start Write W25Qxx....\r\n");
    SPI_Flash_Write((u8 *)TEXT_Buf, 0, FLASH_TEST_SIZE);
    printf("W25Qxx Write Finished!\r\n");

    Delay_Ms(500);
    printf("Start Read W25Qxx....\r\n");
    SPI_Flash_Read(datap, 0x0, FLASH_TEST_SIZE);
    printf("%s\r\n\r\n", datap);
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 flash_func,
                 flash_func,
                 test board flash);
