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
#include "QDTFT_demo.h"
/* Global typedef */

/* Global define */

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
	TIMER6_GPIO_Init(10000, 96);
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
	printf("This is printf example\r\n");
    uint16_t data = 0;
    TIMER3_ENCODER_GPIO_Init();
    TIMER4_ENCODER_GPIO_Init();
    TIMER5_ENCODER_GPIO_Init();
    TIMER9_PWM_GPIO_Init( 100, 4800-1, 20 );

    GPIO_SetBits(GPIOE, GPIO_Pin_8);
    GPIO_SetBits(GPIOE, GPIO_Pin_9);

    GPIO_SetBits(GPIOE, GPIO_Pin_0);
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);

    GPIO_SetBits(GPIOE, GPIO_Pin_2);
    GPIO_ResetBits(GPIOE, GPIO_Pin_3);

    GPIO_SetBits(GPIOE, GPIO_Pin_4);
    GPIO_ResetBits(GPIOE, GPIO_Pin_5);

    GPIO_SetBits(GPIOE, GPIO_Pin_6);
    GPIO_ResetBits(GPIOE, GPIO_Pin_7);
    while(1)
    {
//        QDTFT_Test_Demo();
        while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == 1)
        {
            data = USART_ReceiveData(USART2);
            USART_SendData(USART2,data);
            printf("%s \r\n", &data);
        }
    }
}

