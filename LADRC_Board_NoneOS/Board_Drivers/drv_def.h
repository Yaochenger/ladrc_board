/*
 * drv_def.h
 *
 *  Created on: 2024Äê9ÔÂ3ÈÕ
 *      Author: MCU
 */

#ifndef USER_DRIVERS_DRV_DEF_H_
#define USER_DRIVERS_DRV_DEF_H_

#include <stdint.h>
// USR DEF
#define ENC_INIT_NUM 0x7FFF

// USR STRUCT
typedef struct LDRC_Encoder
{
    int32_t current_cnt;
    float speed;
    uint8_t dir;

} LDRC_Encoder_Handler, *LDRC_Encoder_Handler_t;

// USR FUNC
void Encoder_TCB_Init(LDRC_Encoder_Handler_t encoder);
#endif /* USER_DRIVERS_DRV_DEF_H_ */
