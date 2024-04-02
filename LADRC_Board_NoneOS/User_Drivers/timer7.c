/*
 * timer7.c
 *
 *  Created on: 2024��3��25��
 *      Author: MCU
 */
#include "timer7.h"

void TIMER7_GPIO_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);        //ʹ��TIM3ʱ��

    TIM_TimeBaseStructure.TIM_Period = arr;                     //ָ���´θ����¼�ʱҪ���ص���Զ����¼��ؼĴ����е�����ֵ��
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //ָ�����ڻ���TIMʱ�ӵ�Ԥ��Ƶ��ֵ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM����ģʽ�����ϼ���ģʽ
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);             //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);                  //ʹ��TIM7�жϣ���������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;             //TIM7�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //������ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //������Ӧ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ��ͨ��1�ж�
    NVIC_Init(&NVIC_InitStructure);                             //��ʼ��NVIC

    TIM_Cmd(TIM7, ENABLE);                                      //TIM7ʹ��
}
