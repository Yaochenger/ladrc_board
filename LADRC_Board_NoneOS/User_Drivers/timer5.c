/*
 * timer5.c
 *
 *  Created on: 2024年3月23日
 *      Author: MCU
 */

#include "timer5.h"
#include "drv_def.h"

void TIM5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

LDRC_Encoder_Handler TIMER5_MOTOR;

void TIMER5_ENCODER_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 10 - 1;                  //计数器自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频器值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数器值
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             //初始化TIM5结构体

    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,
                                     TIM_ICPolarity_Rising,
                                     TIM_ICPolarity_Rising);    //使用编码器模式3

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;      //输入捕获极性设置，可用于配置编码器正反相
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;            //输入捕获预分频器设置
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //输入捕获通道选择，编码器模式需选用此配置
    TIM_ICInitStructure.TIM_ICFilter = 10;                           //输入捕获滤波器设置
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearFlag(TIM5, TIM_FLAG_Update);
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM5, 0);
    TIM_Cmd(TIM5, ENABLE);

    Encoder_TCB_Init(&TIMER5_MOTOR);
}

void TIM5_IRQHandler(void)
{
    TIMER5_MOTOR.overflow_cnt ++;
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)    //是否产生更新（溢出）中断
    {
        printf("TIM5_IRQHandler \r\n");
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清空TIM5中断标志位
    }
}

