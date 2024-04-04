/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"
#include "board_config.h"
#include "user_peripheral_driver.h"
#include "lshell_port.h"
#include "shell.h"
#include <sfud.h>
/* Global typedef */

/* Global define */

#define SFUD_DEMO_TEST_BUFFER_SIZE                     1024

static void sfud_demo(uint32_t addr, size_t size, uint8_t *data);

static uint8_t sfud_demo_test_buf[SFUD_DEMO_TEST_BUFFER_SIZE];

/* Global Variable */


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	LED_GPIO_Init();
	UART2_GPIO_Init();
	USART_Printf_Init(115200);
//	TIMER6_GPIO_Init(10000, 96);

//	printf("SystemClk:%d\r\n",SystemCoreClock);
//	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
//	printf("This is printf example\r\n");

//    TIMER3_ENCODER_GPIO_Init();
//    TIMER4_ENCODER_GPIO_Init();
//    TIMER5_ENCODER_GPIO_Init();
//    TIMER9_PWM_GPIO_Init( 100, 4800-1, 20 );
//
//    GPIO_SetBits(GPIOE, GPIO_Pin_8);
//    GPIO_SetBits(GPIOE, GPIO_Pin_9);
//
//    GPIO_SetBits(GPIOE, GPIO_Pin_0);
//    GPIO_ResetBits(GPIOE, GPIO_Pin_1);
//
//    GPIO_SetBits(GPIOE, GPIO_Pin_2);
//    GPIO_ResetBits(GPIOE, GPIO_Pin_3);
//
//    GPIO_SetBits(GPIOE, GPIO_Pin_4);
//    GPIO_ResetBits(GPIOE, GPIO_Pin_5);
//
//    GPIO_SetBits(GPIOE, GPIO_Pin_6);
//    GPIO_ResetBits(GPIOE, GPIO_Pin_7);
    Lcd_Init();
    Lcd_Clear(WHITE); //«Â∆¡
    llGuiInit();
    TIMER7_GPIO_Init(10000, 96);
    userShellInit();
    EXTI0_GPIO_Init();
    int data =0;

    SPI_Flash_Init();
    u32 temp = SPI_Flash_Read_JEDEC_ID();
    printf("ID %x \r\n",temp);

    /* SFUD initialize */
    sfud_init();
    sfud_demo(0, sizeof(sfud_demo_test_buf), sfud_demo_test_buf);

    while(1)
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == 1)
        {
            data = USART_ReceiveData(USART2);
            USART_SendData(USART2,data);
            printf("%s \r\n", &data);
        }
    }
}

/**
 * SFUD demo for the first flash device test.
 *
 * @param addr flash start address
 * @param size test flash size
 * @param size test flash data buffer
 */
static void sfud_demo(uint32_t addr, size_t size, uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_flash *flash = sfud_get_device_table() + 0;
    size_t i;
    /* prepare write data */
    for (i = 0; i < size; i++) {
        data[i] = i;
    }
    /* erase test */
    result = sfud_erase(flash, addr, size);
    if (result == SFUD_SUCCESS) {
        printf("Erase the %s flash data finish. Start from 0x%08X, size is %ld.\r\n", flash->name, addr,
                size);
    } else {
        printf("Erase the %s flash data failed.\r\n", flash->name);
        return;
    }
    /* write test */
    result = sfud_write(flash, addr, size, data);
    if (result == SFUD_SUCCESS) {
        printf("Write the %s flash data finish. Start from 0x%08X, size is %ld.\r\n", flash->name, addr,
                size);
    } else {
        printf("Write the %s flash data failed.\r\n", flash->name);
        return;
    }
    /* read test */
    result = sfud_read(flash, addr, size, data);
    if (result == SFUD_SUCCESS) {
        printf("Read the %s flash data success. Start from 0x%08X, size is %ld. The data is:\r\n", flash->name, addr,
                size);
        printf("Offset (h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
        for (i = 0; i < size; i++) {
            if (i % 16 == 0) {
                printf("[%08X] ", addr + i);
            }
            printf("%02X ", data[i]);
            if (((i + 1) % 16 == 0) || i == size - 1) {
                printf("\r\n");
            }
        }
        printf("\r\n");
    } else {
        printf("Read the %s flash data failed.\r\n", flash->name);
    }
    /* data check */
    for (i = 0; i < size; i++) {
        if (data[i] != i % 256) {
            printf("Read and check write data has an error. Write the %s flash data failed.\r\n", flash->name);
            break;
        }
    }
    if (i == size) {
        printf("The %s flash test is success.\r\n", flash->name);
    }
}

