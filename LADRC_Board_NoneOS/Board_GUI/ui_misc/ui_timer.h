#ifndef UI_TIMER_H
#define UI_TIMER_H
#include "lvgl.h"

#define usr_timer_num 3
void usr_timer_mpu6050(lv_timer_t* timer);
void usr_timer_bluetooth(lv_timer_t* timer);
void usr_timer_adc(lv_timer_t* timer);

#endif // UI_TIMER_H