/*
 * timer4.c
 *
 *  Created on: 2024年3月23日
 *      Author: MCU
 */

#include "timer4.h"

void TIMER4_ENCODER_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1;              //计数器自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频器值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数器值
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //初始化TIM2结构体

    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
                                     TIM_ICPolarity_Rising,
                                     TIM_ICPolarity_Rising);              //使用编码器模式3

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;      //输入捕获极性设置，可用于配置编码器正反相
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;            //输入捕获预分频器设置
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //输入捕获通道选择，编码器模式需选用此配置
    TIM_ICInitStructure.TIM_ICFilter = 10;                           //输入捕获滤波器设置
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, ENABLE);
}
