#include "ui_timer.h"
#include "custom.h"
#include "mpu6050_soft.h"
#include "adc.h"
#include "ui_misc.h"

// 外部引用的UI元素和缓冲区
extern lv_ui guider_ui;
extern uint8_t USART_RX_BUF[100];
extern int USART_RX_STA;

// 用于存储ADC值的数组
uint16_t adc_value[6];

// 用于存储定时器指针的数组
lv_timer_t *gui_timer[usr_timer_num];


void usr_timer_mpu6050(lv_timer_t* timer)
{
    IMU_data USER_IMU_data;

    USER_GET_MPU6050_DATA(&USER_IMU_data);
    ui_misc_update_label(guider_ui.screen_4_label_2, USER_IMU_data.Pitch);
    ui_misc_update_label(guider_ui.screen_4_label_3, USER_IMU_data.Roll);
    ui_misc_update_label(guider_ui.screen_4_label_4, USER_IMU_data.Yaw);
}

void usr_timer_bluetooth(lv_timer_t* timer)
{
    if (USART_RX_STA == 1)
    {
        lv_textarea_set_text(guider_ui.screen_3_ta_1, (const char*)USART_RX_BUF);
        memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));
        USART_RX_STA = 0;
    }
}

void usr_timer_adc(lv_timer_t* timer)
{
    const uint8_t adc_channels[] = {ADC_Channel_4, ADC_Channel_5, ADC_Channel_12, ADC_Channel_13, ADC_Channel_14, ADC_Channel_15};
    lv_obj_t* labels[] = {guider_ui.screen_5_label_8, guider_ui.screen_5_label_6, guider_ui.screen_5_label_7, guider_ui.screen_5_label_9, guider_ui.screen_5_label_10, guider_ui.screen_5_label_11};
    lv_obj_t* bars[] = {guider_ui.screen_5_bar_1, guider_ui.screen_5_bar_2, guider_ui.screen_5_bar_3, guider_ui.screen_5_bar_4, guider_ui.screen_5_bar_5, guider_ui.screen_5_bar_6};

    for (int i = 0; i < 6; i++) {
        adc_value[i] = (Get_ConversionVal(Get_ADC_Val(adc_channels[i])) * 100) / 4095;
        ui_misc_update_label(labels[i], (float)(adc_value[i] / 100.0) * 3.3);
        lv_bar_set_value(bars[i], adc_value[i], LV_ANIM_OFF);
    }
}

