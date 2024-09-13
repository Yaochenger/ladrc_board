/*
 * drv_def.c
 *
 *  Created on: 2024��9��3��
 *      Author: MCU
 */

#include "drv_def.h"

void Encoder_TCB_Init(LDRC_Encoder_Handler_t encoder)
{
    encoder->current_cnt = 0;
    encoder->last_cnt = 0;
    encoder->overflow_cnt = 0;
    encoder->speed = 0;
    encoder->dir = 0;
}
