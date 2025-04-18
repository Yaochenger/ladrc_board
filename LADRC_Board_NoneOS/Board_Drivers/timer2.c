/*
 * timer2.c
 *
 *  Created on: 2024年9月11日
 *      Author: MCU
 */
#include "timer2.h"
#include "board_config.h"

void TIMER2_GPIO_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);        //使能TIM3时钟

    TIM_TimeBaseStructure.TIM_Period = arr;                     //指定下次更新事件时要加载到活动自动重新加载寄存器中的周期值。
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //指定用于划分TIM时钟的预分频器值。
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频因子
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM计数模式，向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //根据指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                  //使能TIM6中断，允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //设置抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //设置响应优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能通道1中断
    NVIC_Init(&NVIC_InitStructure);                             //初始化NVIC

    TIM_Cmd(TIM2, ENABLE);                                      //TIM2使能
}

void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIMER3_MOTOR.dir = TIMER3_ENCODER_COUNTING_DIR();
        TIMER3_MOTOR.current_cnt = (int16_t) TIM_GetCounter(TIM3);
        TIM_SetCounter(TIM3, 0);

        TIMER4_MOTOR.dir = TIMER4_ENCODER_COUNTING_DIR();
        TIMER4_MOTOR.current_cnt = (int16_t) TIM_GetCounter(TIM4);
        TIM_SetCounter(TIM4, 0);

        TIMER5_MOTOR.dir = TIMER5_ENCODER_COUNTING_DIR();
        TIMER5_MOTOR.current_cnt = (int16_t) TIM_GetCounter(TIM5);
        TIM_SetCounter(TIM5, 0);

        TIMER8_MOTOR.dir = TIMER8_ENCODER_COUNTING_DIR();
        TIMER8_MOTOR.current_cnt = (int16_t) TIM_GetCounter(TIM8);
        TIM_SetCounter(TIM8, 0);
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
