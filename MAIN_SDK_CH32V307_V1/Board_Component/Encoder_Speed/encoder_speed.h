/*
 * encoder_speed.h
 *
 *  Created on: 2024Äê3ÔÂ25ÈÕ
 *      Author: MCU
 */

#ifndef USER_PERIPHERAL_DRIVER_ENCODER_SPEED_ENCODER_SPEED_H_
#define USER_PERIPHERAL_DRIVER_ENCODER_SPEED_ENCODER_SPEED_H_
#include "timer_encoder.h"
#include "timer.h"

typedef struct EncoderType
{
  uint8_t Dir;
  uint16_t Cnt;
} EncoderTypeDef;

void TIM3_EnCoder_CNT(void);
void TIM4_EnCoder_CNT(void);
void TIM5_EnCoder_CNT(void);
void TIM8_EnCoder_CNT(void);


#endif /* USER_PERIPHERAL_DRIVER_ENCODER_SPEED_ENCODER_SPEED_H_ */


