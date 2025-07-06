/*
 * timer8.c
 *
 *  Created on: 2024��3��23��
 *      Author: MCU
 */
#include "timer8.h"

LDRC_Encoder_Handler TIMER8_MOTOR;

void TIMER8_ENCODER_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0XFFFF - 1;                  //�������Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //Ԥ��Ƶ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�ظ�������ֵ
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);             //��ʼ��TIM5�ṹ��

    TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12,
                                     TIM_ICPolarity_Rising,
                                     TIM_ICPolarity_Rising);    //ʹ�ñ�����ģʽ3

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);

    TIM_SetCounter(TIM8, 0);
    TIM_Cmd(TIM8, ENABLE);
}
