 /*
 * motor_encoder_sample.c
 *
 *  Created on: 2024Äê6ÔÂ22ÈÕ
 *      Author: MCU
 */

#include "shell.h"
#include "timer3.h"
#include "timer4.h"
#include "timer5.h"
#include "timer8.h"
#include "timer9.h"
#include "encoder_speed.h"

void TIMERX_MOTOR_Dir_GPIO_Init(void);
extern EncoderTypeDef TIM3_Encoder_SPEED;
extern EncoderTypeDef TIM4_Encoder_SPEED;
extern EncoderTypeDef TIM5_Encoder_SPEED;
extern EncoderTypeDef TIM8_Encoder_SPEED;

int motor_encoder_func(int mode, int num)
{
    TIMERX_MOTOR_Dir_GPIO_Init();
    TIMER9_PWM_GPIO_Init( 100, 4800-1, 20 );

    GPIO_SetBits(GPIOE, GPIO_Pin_8);
    GPIO_SetBits(GPIOE, GPIO_Pin_9);

    int mode_handle = mode;
    int num_handle = num;
    switch (mode_handle) {
        case 1:
            {
                TIMER5_ENCODER_GPIO_Init();
                GPIO_SetBits(GPIOE, GPIO_Pin_0);
                GPIO_ResetBits(GPIOE, GPIO_Pin_1);
                for (int i = 0; i < num_handle; i++)
                {
                    TIM5_EnCoder_CNT();
                    Delay_Ms(500);
                }
                GPIO_ResetBits(GPIOE, GPIO_Pin_0);
                GPIO_ResetBits(GPIOE, GPIO_Pin_1);
                printf("\r\n\r\n");
                return 0;
            }
        case 2:
            {
                TIMER8_ENCODER_GPIO_Init();
                GPIO_ResetBits(GPIOE, GPIO_Pin_2);
                GPIO_SetBits(GPIOE, GPIO_Pin_3);
                for (int i = 0; i < num_handle; i++)
                {
                    TIM8_EnCoder_CNT();
                    Delay_Ms(500);
                }
                GPIO_ResetBits(GPIOE, GPIO_Pin_2);
                GPIO_ResetBits(GPIOE, GPIO_Pin_3);
                printf("\r\n\r\n");
                return 0;
            }
        case 3:
            {
                TIMER3_ENCODER_GPIO_Init();
                GPIO_SetBits(GPIOE, GPIO_Pin_4);
                GPIO_ResetBits(GPIOE, GPIO_Pin_5);
                for (int i = 0; i < num_handle; i++)
                {
                    TIM3_EnCoder_CNT();
                    Delay_Ms(500);
                }
                GPIO_ResetBits(GPIOE, GPIO_Pin_4);
                GPIO_ResetBits(GPIOE, GPIO_Pin_5);
                printf("\r\n\r\n");
                return 0;
            }
        case 4:
            {
                TIMER4_ENCODER_GPIO_Init();
                GPIO_ResetBits(GPIOE, GPIO_Pin_6);
                GPIO_SetBits(GPIOE, GPIO_Pin_7);
                for (int i = 0; i < num_handle; i++)
                {
                    TIM4_EnCoder_CNT();
                    Delay_Ms(500);
                }
                GPIO_ResetBits(GPIOE, GPIO_Pin_6);
                GPIO_ResetBits(GPIOE, GPIO_Pin_7);
                printf("\r\n\r\n");
                return 0;
            }
        case 5:
            {
                GPIO_ResetBits(GPIOE, GPIO_Pin_0); // M1
                GPIO_SetBits(GPIOE, GPIO_Pin_1);

                GPIO_SetBits(GPIOE, GPIO_Pin_2); // M2
                GPIO_ResetBits(GPIOE, GPIO_Pin_3);

                GPIO_ResetBits(GPIOE, GPIO_Pin_6); // M3
                GPIO_SetBits(GPIOE, GPIO_Pin_7);

                GPIO_ResetBits(GPIOE, GPIO_Pin_4);   // M4
                GPIO_SetBits(GPIOE, GPIO_Pin_5);

                TIMER3_ENCODER_GPIO_Init();
                TIMER4_ENCODER_GPIO_Init();
                TIMER5_ENCODER_GPIO_Init();
                TIMER8_ENCODER_GPIO_Init();

                for (int i = 0; i < num_handle; i++)
                {
                    TIM3_Encoder_SPEED.Cnt = (TIM_GetCounter(TIM3));
                    TIM4_Encoder_SPEED.Cnt = (TIM_GetCounter(TIM4));
                    TIM5_Encoder_SPEED.Cnt = (TIM_GetCounter(TIM5));
                    TIM8_Encoder_SPEED.Cnt = (TIM_GetCounter(TIM8));

                    TIM_SetCounter(TIM8, 0);
                    TIM_SetCounter(TIM5, 0);
                    TIM_SetCounter(TIM4, 0);
                    TIM_SetCounter(TIM3, 0);

                    TIM3_Encoder_SPEED.Dir = TIMER3_ENCODER_COUNTING_DIR();
                    TIM4_Encoder_SPEED.Dir = TIMER4_ENCODER_COUNTING_DIR();
                    TIM5_Encoder_SPEED.Dir = TIMER5_ENCODER_COUNTING_DIR();
                    TIM8_Encoder_SPEED.Dir = TIMER8_ENCODER_COUNTING_DIR();

                    printf("M1 TIM5 Enc_Dir=%d, Cnt= %d\r\n",TIM5_Encoder_SPEED.Dir, TIM5_Encoder_SPEED.Cnt);
                    printf("M2 TIM8 Enc_Dir=%d, Cnt= %d\r\n",TIM8_Encoder_SPEED.Dir, TIM8_Encoder_SPEED.Cnt);
                    printf("M3 TIM4 Enc_Dir=%d, Cnt= %d\r\n",TIM4_Encoder_SPEED.Dir, TIM4_Encoder_SPEED.Cnt);
                    printf("M4 TIM3 Enc_Dir=%d, Cnt= %d\r\n",TIM3_Encoder_SPEED.Dir, TIM3_Encoder_SPEED.Cnt);
                    Delay_Ms(50);
                }

                GPIO_ResetBits(GPIOE, GPIO_Pin_0);
                GPIO_ResetBits(GPIOE, GPIO_Pin_1);

                GPIO_ResetBits(GPIOE, GPIO_Pin_2);
                GPIO_ResetBits(GPIOE, GPIO_Pin_3);

                GPIO_ResetBits(GPIOE, GPIO_Pin_4);
                GPIO_ResetBits(GPIOE, GPIO_Pin_5);

                GPIO_ResetBits(GPIOE, GPIO_Pin_6);
                GPIO_ResetBits(GPIOE, GPIO_Pin_7);
                printf("\r\n\r\n");
                return 0;
            }
        default:
            break;
    }
    return 0;

}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), motor_encoder_func, motor_encoder_func, test board timer and motor func);

void TIMERX_MOTOR_Dir_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | \
                                  GPIO_Pin_2 | GPIO_Pin_3 | \
                                  GPIO_Pin_4 | GPIO_Pin_5 | \
                                  GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

