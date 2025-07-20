/*
 * timer4.c
 *
 *  Created on: 2024��3��23��
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1;              //�������Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //Ԥ��Ƶ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�ظ�������ֵ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //��ʼ��TIM2�ṹ��

    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
                                     TIM_ICPolarity_Rising,
                                     TIM_ICPolarity_Rising);              //ʹ�ñ�����ģʽ3

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;      //���벶�������ã����������ñ�����������
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;            //���벶��Ԥ��Ƶ������
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //���벶��ͨ��ѡ�񣬱�����ģʽ��ѡ�ô�����
    TIM_ICInitStructure.TIM_ICFilter = 10;                           //���벶���˲�������
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, ENABLE);
}
