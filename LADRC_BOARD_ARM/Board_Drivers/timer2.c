/*
 * timer2.c
 *
 *  Created on: 2024��9��11��
 *      Author: MCU
 */
#include "timer2.h"
#include "board_config.h"

void TIMER2_GPIO_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);        //ʹ��TIM3ʱ��

    TIM_TimeBaseStructure.TIM_Period = arr;                     //ָ���´θ����¼�ʱҪ���ص���Զ����¼��ؼĴ����е�����ֵ��
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //ָ�����ڻ���TIMʱ�ӵ�Ԥ��Ƶ��ֵ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM����ģʽ�����ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                  //ʹ��TIM6�жϣ���������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //������ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //������Ӧ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ��ͨ��1�ж�
    NVIC_Init(&NVIC_InitStructure);                             //��ʼ��NVIC

    TIM_Cmd(TIM2, ENABLE);                                      //TIM2ʹ��
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
