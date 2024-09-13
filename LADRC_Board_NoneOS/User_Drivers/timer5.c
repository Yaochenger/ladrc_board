/*
 * timer5.c
 *
 *  Created on: 2024��3��23��
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
    TIM_TimeBaseStructure.TIM_Period = 10 - 1;                  //�������Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //Ԥ��Ƶ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�ظ�������ֵ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             //��ʼ��TIM5�ṹ��

    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,
                                     TIM_ICPolarity_Rising,
                                     TIM_ICPolarity_Rising);    //ʹ�ñ�����ģʽ3

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;      //���벶�������ã����������ñ�����������
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;            //���벶��Ԥ��Ƶ������
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //���벶��ͨ��ѡ�񣬱�����ģʽ��ѡ�ô�����
    TIM_ICInitStructure.TIM_ICFilter = 10;                           //���벶���˲�������
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
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)    //�Ƿ�������£�������ж�
    {
        printf("TIM5_IRQHandler \r\n");
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //���TIM5�жϱ�־λ
    }
}

