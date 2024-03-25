/*
 * time6.c
 *
 *  Created on: 2024��3��25��
 *      Author: MCU
 */

#include "timer6.h"
void TIM6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void TIMER6_GPIO_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);        //ʹ��TIM3ʱ��

    TIM_TimeBaseStructure.TIM_Period = arr;                     //ָ���´θ����¼�ʱҪ���ص���Զ����¼��ؼĴ����е�����ֵ��
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //ָ�����ڻ���TIMʱ�ӵ�Ԥ��Ƶ��ֵ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM����ģʽ�����ϼ���ģʽ
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);             //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);                  //ʹ��TIM6�жϣ���������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;             //TIM6�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //������ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //������Ӧ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ��ͨ��1�ж�
    NVIC_Init(&NVIC_InitStructure);                             //��ʼ��NVIC

    TIM_Cmd(TIM6, ENABLE);                                      //TIM6ʹ��
}

static u16 i = 0;
void TIM6_IRQHandler(void)
{
    i++;
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        if (i==100)
        {
            i=0;
            printf("Enter TIM6 interrupt\r\n");
        }
    }
}
