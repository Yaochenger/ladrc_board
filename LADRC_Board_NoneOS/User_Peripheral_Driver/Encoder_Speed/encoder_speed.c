/*
 * encoder_speed.c
 *
 *  Created on: 2024Äê3ÔÂ25ÈÕ
 *      Author: MCU
 */

#include "encoder_speed.h"


EncoderTypeDef TIM3_Encoder_SPEED;
EncoderTypeDef TIM4_Encoder_SPEED;
EncoderTypeDef TIM5_Encoder_SPEED;
EncoderTypeDef TIM8_Encoder_SPEED;

void TIM3_EnCoder_CNT(void)
{
    TIM3_Encoder_SPEED.Dir = TIMER3_ENCODER_COUNTING_DIR();
    TIM3_Encoder_SPEED.Cnt = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0);
    printf("TIM3 Encoder Direct=%d, Counter= %d \r\n",TIM3_Encoder_SPEED.Dir, TIM3_Encoder_SPEED.Cnt);
}

void TIM4_EnCoder_CNT(void)
{
    TIM4_Encoder_SPEED.Dir = TIMER4_ENCODER_COUNTING_DIR();
    TIM4_Encoder_SPEED.Cnt = TIM_GetCounter(TIM4);
    TIM_SetCounter(TIM4, 0);
    printf("TIM4 Encoder Direct=%d, Counter= %d \r\n",TIM4_Encoder_SPEED.Dir, TIM4_Encoder_SPEED.Cnt);
}

void TIM5_EnCoder_CNT(void)
{
    TIM5_Encoder_SPEED.Dir = TIMER5_ENCODER_COUNTING_DIR();
    TIM5_Encoder_SPEED.Cnt = TIM_GetCounter(TIM5);
    TIM_SetCounter(TIM5, 0);
    printf("TIM5 Encoder Direct=%d, Counter= %d \r\n",TIM5_Encoder_SPEED.Dir, TIM5_Encoder_SPEED.Cnt);
}

void TIM8_EnCoder_CNT(void)
{
    TIM8_Encoder_SPEED.Dir = TIMER8_ENCODER_COUNTING_DIR();
    TIM8_Encoder_SPEED.Cnt = TIM_GetCounter(TIM8);
    TIM_SetCounter(TIM8, 0);
    printf("TIM8 Encoder Direct=%d, Counter= %d \r\n",TIM8_Encoder_SPEED.Dir, TIM8_Encoder_SPEED.Cnt);
}
