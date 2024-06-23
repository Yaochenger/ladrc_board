/*
 * motor_encoder_sample.c
 *
 *  Created on: 2024Äê6ÔÂ22ÈÕ
 *      Author: MCU
 */

#include "shell.h"
#include "timer3.h"
#include "timer4.h"
#include "timer5.h"
#include "timer8.h"
#include "timer9.h"
#include "encoder_speed.h"

void TIMERX_MOTOR_Dir_GPIO_Init(void);

int motor_encoder_func(int cnt)
{
    TIMER3_ENCODER_GPIO_Init();
    TIMER4_ENCODER_GPIO_Init();
    TIMER5_ENCODER_GPIO_Init();
    TIMER8_ENCODER_GPIO_Init();

    TIMERX_MOTOR_Dir_GPIO_Init();

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

    for (int i = 0; i < cnt; i++)
    {
        printf("#### Motor Encoder Start #### \r\n");
        TIM3_EnCoder_CNT();
        TIM4_EnCoder_CNT();
        TIM5_EnCoder_CNT();
        TIM8_EnCoder_CNT();
        printf("#### Motor Encoder End   #### \r\n");
        Delay_Ms(500);
    }

    return 0;

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), motor_encoder_func, motor_encoder_func, test board timer and motor func);

void TIMERX_MOTOR_Dir_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | \
                                  GPIO_Pin_2 | GPIO_Pin_3 | \
                                  GPIO_Pin_4 | GPIO_Pin_5 | \
                                  GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

