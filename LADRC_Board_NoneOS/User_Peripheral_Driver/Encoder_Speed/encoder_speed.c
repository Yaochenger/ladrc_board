/*
 * encoder_speed.c
 *
 *  Created on: 2024年3月25日
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

//static u16 i = 0;
//void TIM6_IRQHandler(void)
//{
//    i++;
//    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
//    {
//        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
//        if (i==100)
//        {
//            i=0;
//            TIM3_EnCoder_CNT();
//            TIM4_EnCoder_CNT();
//            TIM5_EnCoder_CNT();
//        }
//    }
//}

#include <mpu6050_soft.h>

short aacx,aacy,aacz;       //加速度传感器原始数据
short gyrox,gyroy,gyroz;    //陀螺仪原始数据
void TIM6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM6_IRQHandler(void) {
    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //得到加速度传感器数据
    MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //得到陀螺仪数据
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
//        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //得到加速度传感器数据
//        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //得到陀螺仪数据
    }
}

