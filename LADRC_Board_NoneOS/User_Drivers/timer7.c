/*
 * timer7.c
 *
 *  Created on: 2024年3月25日
 *      Author: MCU
 */
#include "timer7.h"

void TIMER7_GPIO_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);        //使能TIM3时钟

    TIM_TimeBaseStructure.TIM_Period = arr;                     //指定下次更新事件时要加载到活动自动重新加载寄存器中的周期值。
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //指定用于划分TIM时钟的预分频器值。
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频因子
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM计数模式，向上计数模式
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);             //根据指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);                  //使能TIM7中断，允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;             //TIM7中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //设置抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //设置响应优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能通道1中断
    NVIC_Init(&NVIC_InitStructure);                             //初始化NVIC

    TIM_Cmd(TIM7, ENABLE);                                      //TIM7使能
}
