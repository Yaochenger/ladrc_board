/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

#include "debug.h"
#include "board_config.h"
#include "user_peripheral_driver.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
uint16_t cnt= 0, dir =0;
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    EXTI0_GPIO_Init();
    userShellInit(); //letter Shell
    Lcd_Init();
    Lcd_Clear(WHITE);//clear LCD
    TIMER2_GPIO_Init(10000 - 1,96 - 1);
    TIMER8_ENCODER_GPIO_Init();
    TIMER3_ENCODER_GPIO_Init();
    TIMER4_ENCODER_GPIO_Init();
    TIMER5_ENCODER_GPIO_Init();
    while(1)
    {
        cnt = TIM_GetCounter(TIM3);
        dir = TIMER3_ENCODER_COUNTING_DIR();
        printf("cnt=%d dir=%d\r\n",cnt, dir);
        Delay_Ms(1000);
    }
}


