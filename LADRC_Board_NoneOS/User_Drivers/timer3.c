/*
 * timer3.c
 *
 *  Created on: 2024��3��23��
 *      Author: MCU
 */

#include "timer3.h"
#include "drv_def.h"

void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

LDRC_Encoder_Handler TIMER3_MOTOR;

void TIMER3_ENCODER_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = ENC_INIT_NUM;            //�������Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //Ԥ��Ƶ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�ظ�������ֵ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //��ʼ��TIM2�ṹ��

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
                                     TIM_ICPolarity_Rising,
                                     TIM_ICPolarity_Rising);    //ʹ�ñ�����ģʽ3

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;     //���벶�������ã����������ñ�����������
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;           //���벶��Ԥ��Ƶ������
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //���벶��ͨ��ѡ�񣬱�����ģʽ��ѡ�ô�����
    TIM_ICInitStructure.TIM_ICFilter = 10;                          //���벶���˲�������
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);        //���TIM���±�־λ
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //ʹ�ܿ���TIM�ж�

    TIM_SetCounter(TIM3, 0x7FFF);
    TIM_Cmd(TIM3, ENABLE);

    Encoder_TCB_Init(&TIMER3_MOTOR);
}

void TIM3_IRQHandler(void)
{
    TIMER3_MOTOR.overflow_cnt ++;
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)    //�Ƿ�������£�������ж�
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //���TIM5�жϱ�־λ
    }
}
