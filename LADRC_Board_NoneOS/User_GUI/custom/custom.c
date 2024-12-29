/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "ch32v30x.h"
#include "mpu6050_soft.h"
#include "uart2.h"
#include "adc.h"

/*********************
 *      DEFINES
 *********************/
#define usr_group_num 8
#define usr_timer_num 3
#define usr_serie_num 1

static uint16_t adc_value[6];
/**********************
 *      TYPEDEFS
 **********************/
static void load_screen0(void);
static void load_screen1(void);
static void load_screen2(void);
static void load_screen2_1(void);
static void load_screen2_2(void);
static void load_screen2_3(void);
static void load_screen2_4(void);

static void usr_timer_1(lv_timer_t* timer);
static void usr_timer_bluetooth(lv_timer_t* timer);
static void usr_timer_adc(lv_timer_t* timer);
/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_group_t *gui_group[usr_group_num];
static lv_timer_t *gui_timer[usr_timer_num];
//static lv_chart_series_t * gui_ser[usr_serie_num];

static lv_obj_t *screen1_saved_focus_obj;
/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
extern lv_ui guider_ui;
extern lv_indev_t * indev_keypad;
static void screen_page_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_PRESSED)
    {
        load_screen1();
    }
}

static void screen1_page_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    uint32_t key = lv_event_get_key(e);

    if (key == LV_KEY_ESC) {
        screen1_saved_focus_obj = lv_group_get_focused(gui_group[1]);
        load_screen0();
    }

    if(code == LV_EVENT_PRESSED) {
        screen1_saved_focus_obj = lv_group_get_focused(gui_group[1]);

        if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item0)
        {
            load_screen2();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item1)
        {
            load_screen2_4();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item2)
        {
            gui_timer[0] = lv_timer_create(usr_timer_1, 5, (void *)guider_ui.screen_4_label_8);// mpu6050
            MPU_Init();
            MPU6050_Filter_Init(50);
            load_screen2_2();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item3) // Bluetoolh
        {
            gui_timer[1] = lv_timer_create(usr_timer_bluetooth, 1, NULL);
            UART2_GPIO_Init();
            load_screen2_1();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item4) // ADC
        {
            gui_timer[2] = lv_timer_create(usr_timer_adc, 50, NULL);
            ADC_GPIO_Init();
            load_screen2_3();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item5)
        {
            load_screen0();
        }
    }
}

static void screen2_page_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    uint32_t key = lv_event_get_key(e);
    static int led = 0;
    if (code == LV_EVENT_PRESSED)
    {
        led++;
        if (led % 2 == 0)
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_8);
            lv_led_on(guider_ui.screen_2_led_1);
        } else {
            GPIO_ResetBits(GPIOD, GPIO_Pin_8);
            lv_led_off(guider_ui.screen_2_led_1);
        }
    }

    if (key == LV_KEY_ESC) {
        load_screen1();
    }
}

static void screen2_1_page_cb(lv_event_t * e)
{
    uint32_t key = lv_event_get_key(e);
    lv_group_t *group_temp  = lv_group_get_default();
    if (key == LV_KEY_ESC) {
        if (group_temp == gui_group[5])
        {
            lv_timer_del(gui_timer[2]);
        }
        else if (group_temp == gui_group[4])
        {
            lv_timer_del(gui_timer[0]);
        }
        else if (group_temp == gui_group[3])
        {
            lv_timer_del(gui_timer[1]);
        }
        load_screen1();
    }
}

static void screen2_4_page_cb(lv_event_t * e)
{
    uint32_t key = lv_event_get_key(e);
    lv_obj_t *label = lv_group_get_focused(gui_group[6]);
    if(label != NULL)
    {
        lv_obj_set_style_text_color(guider_ui.screen_6_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.screen_6_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.screen_6_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.screen_6_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
        if (label == guider_ui.screen_6_label_1)
        {
            lv_obj_set_style_text_color(guider_ui.screen_6_label_1, lv_color_hex(0xFF0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        }
        else if (label == guider_ui.screen_6_label_2)
        {
            lv_obj_set_style_text_color(guider_ui.screen_6_label_2, lv_color_hex(0xFF0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        }
        else if (label == guider_ui.screen_6_label_3)
        {
            lv_obj_set_style_text_color(guider_ui.screen_6_label_3, lv_color_hex(0xFF0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        }
        else if (label == guider_ui.screen_6_label_4)
        {
            lv_obj_set_style_text_color(guider_ui.screen_6_label_4, lv_color_hex(0xFF0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        }
    }

    if (key == LV_KEY_ESC) {
        load_screen1();
    }
}

static void load_screen0(void)
{
    lv_indev_set_group(indev_keypad, gui_group[0]);
    lv_group_set_default(gui_group[0]);
    lv_group_add_obj(gui_group[0], guider_ui.screen_btn_1);
    lv_group_focus_obj(guider_ui.screen_btn_1);
    lv_scr_load(guider_ui.screen);
}

static void load_screen1(void)
{
    lv_indev_set_group(indev_keypad, gui_group[1]);
    lv_group_set_default(gui_group[1]);
    lv_group_add_obj(gui_group[1], guider_ui.screen_1_list_1_item0);
    lv_group_add_obj(gui_group[1], guider_ui.screen_1_list_1_item1);
    lv_group_add_obj(gui_group[1], guider_ui.screen_1_list_1_item2);
    lv_group_add_obj(gui_group[1], guider_ui.screen_1_list_1_item3);
    lv_group_add_obj(gui_group[1], guider_ui.screen_1_list_1_item4);
    lv_group_add_obj(gui_group[1], guider_ui.screen_1_list_1_item5);

    if (screen1_saved_focus_obj != NULL) {
        lv_group_focus_obj(screen1_saved_focus_obj);
        screen1_saved_focus_obj = NULL;
    }

    lv_scr_load(guider_ui.screen_1);
}

static void load_screen2(void)
{
    lv_indev_set_group(indev_keypad, gui_group[2]);
    lv_group_set_default(gui_group[2]);
    lv_group_add_obj(gui_group[2], guider_ui.screen_2_cont_1);
    lv_group_focus_obj(guider_ui.screen_2_cont_1);
    lv_scr_load(guider_ui.screen_2);
}

static void load_screen2_1(void)
{
    lv_indev_set_group(indev_keypad, gui_group[3]);
    lv_group_set_default(gui_group[3]);
    lv_group_add_obj(gui_group[3], guider_ui.screen_3_ta_1);
    lv_group_focus_obj(guider_ui.screen_3_ta_1);
    lv_textarea_set_text(guider_ui.screen_3_ta_1, "Hello World\rSerial baud 9600");
    lv_scr_load(guider_ui.screen_3);
}

static void load_screen2_2(void)
{
    lv_indev_set_group(indev_keypad, gui_group[4]);
    lv_group_set_default(gui_group[4]);
    lv_group_add_obj(gui_group[4], guider_ui.screen_4_label_8);
    lv_group_focus_obj(guider_ui.screen_4_label_8);
    lv_scr_load(guider_ui.screen_4);
}

static void load_screen2_3(void)
{
    lv_indev_set_group(indev_keypad, gui_group[5]);
    lv_group_set_default(gui_group[5]);
    lv_group_add_obj(gui_group[5], guider_ui.screen_5_cont_1);
    lv_group_focus_obj(guider_ui.screen_5_cont_1);
    lv_scr_load(guider_ui.screen_5);
}

static void load_screen2_4(void)
{
    lv_indev_set_group(indev_keypad, gui_group[6]);
    lv_group_set_default(gui_group[6]);
    lv_group_add_obj(gui_group[6], guider_ui.screen_6_cont_1);
    lv_group_add_obj(gui_group[6], guider_ui.screen_6_label_1);
    lv_group_add_obj(gui_group[6], guider_ui.screen_6_label_2);
    lv_group_add_obj(gui_group[6], guider_ui.screen_6_label_3);
    lv_group_add_obj(gui_group[6], guider_ui.screen_6_label_4);
    lv_group_focus_obj(guider_ui.screen_6_cont_1);
    lv_scr_load(guider_ui.screen_6);
}

static void usr_timer_1(lv_timer_t* timer)
{
    char new_text[20];
    IMU_data USER_IMU_data;

    USER_GET_MPU6050_DATA(&USER_IMU_data);
    snprintf(new_text, sizeof(new_text), "%.1f",USER_IMU_data.Pitch);
    lv_label_set_text(guider_ui.screen_4_label_2, new_text);
    snprintf(new_text, sizeof(new_text), "%.1f",USER_IMU_data.Roll);
    lv_label_set_text(guider_ui.screen_4_label_3, new_text);
    snprintf(new_text, sizeof(new_text), "%.1f",USER_IMU_data.Yaw);
    lv_label_set_text(guider_ui.screen_4_label_4, new_text);

}

extern uint8_t USART_RX_BUF[100];
extern int USART_RX_STA;
static void usr_timer_bluetooth(lv_timer_t* timer)
{
    if(USART_RX_STA == 1)
    {
        lv_textarea_set_text(guider_ui.screen_3_ta_1, USART_RX_BUF);
        memset(USART_RX_BUF, 0, sizeof (USART_RX_BUF));
        USART_RX_STA = 0;
    }
}

static void usr_timer_adc(lv_timer_t* timer)
{
    char adc_text[10];

    adc_value[0] = (Get_ConversionVal(Get_ADC_Val(ADC_Channel_4)) * 100)/ 4095;
    adc_value[1] = (Get_ConversionVal(Get_ADC_Val(ADC_Channel_5)) * 100)/ 4095;
    adc_value[2] = (Get_ConversionVal(Get_ADC_Val(ADC_Channel_12)) * 100)/ 4095;
    adc_value[3] = (Get_ConversionVal(Get_ADC_Val(ADC_Channel_13)) * 100)/ 4095;
    adc_value[4] = (Get_ConversionVal(Get_ADC_Val(ADC_Channel_14)) * 100)/ 4095;
    adc_value[5] = (Get_ConversionVal(Get_ADC_Val(ADC_Channel_15)) * 100)/ 4095;

    snprintf(adc_text, sizeof(adc_text), "%.1f", (float)(adc_value[0] / 100.0) * 3.3);
    lv_label_set_text(guider_ui.screen_5_label_8, adc_text);
    snprintf(adc_text, sizeof(adc_text), "%.1f", (float)(adc_value[1] / 100.0) * 3.3);
    lv_label_set_text(guider_ui.screen_5_label_6, adc_text);
    snprintf(adc_text, sizeof(adc_text), "%.1f", (float)(adc_value[2] / 100.0) * 3.3);
    lv_label_set_text(guider_ui.screen_5_label_7, adc_text);
    snprintf(adc_text, sizeof(adc_text), "%.1f", (float)(adc_value[3] / 100.0) * 3.3);
    lv_label_set_text(guider_ui.screen_5_label_9, adc_text);
    snprintf(adc_text, sizeof(adc_text), "%.1f", (float)(adc_value[4] / 100.0) * 3.3);
    lv_label_set_text(guider_ui.screen_5_label_10, adc_text);
    snprintf(adc_text, sizeof(adc_text), "%.1f", (float)(adc_value[5] / 100.0) * 3.3);
    lv_label_set_text(guider_ui.screen_5_label_11, adc_text);

    lv_bar_set_value(guider_ui.screen_5_bar_1, adc_value[0], LV_ANIM_OFF);
    lv_bar_set_value(guider_ui.screen_5_bar_2, adc_value[1], LV_ANIM_OFF);
    lv_bar_set_value(guider_ui.screen_5_bar_3, adc_value[2], LV_ANIM_OFF);
    lv_bar_set_value(guider_ui.screen_5_bar_4, adc_value[3], LV_ANIM_OFF);
    lv_bar_set_value(guider_ui.screen_5_bar_5, adc_value[4], LV_ANIM_OFF);
    lv_bar_set_value(guider_ui.screen_5_bar_6, adc_value[5], LV_ANIM_OFF);
}

void custom_init(lv_ui *ui)
{
    setup_scr_screen_1(ui);
    setup_scr_screen_2(ui);
    setup_scr_screen_3(ui);
    setup_scr_screen_4(ui);
    setup_scr_screen_5(ui);
    setup_scr_screen_6(ui);

    for (int var = 0; var < usr_group_num; var++) {
        gui_group[var] = lv_group_create();
    }

    lv_obj_add_event_cb(ui->screen_btn_1, screen_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_1_list_1_item0, screen1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_1_list_1_item1, screen1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_1_list_1_item2, screen1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_1_list_1_item3, screen1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_1_list_1_item4, screen1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_1_list_1_item5, screen1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_2_cont_1, screen2_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_3_ta_1, screen2_1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_4_label_8, screen2_1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_5_cont_1, screen2_1_page_cb, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui->screen_6_cont_1, screen2_1_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_6_label_1, screen2_4_page_cb, LV_EVENT_ALL, ui->screen_6_label_1);
    lv_obj_add_event_cb(ui->screen_6_label_2, screen2_4_page_cb, LV_EVENT_ALL, ui->screen_6_label_2);
    lv_obj_add_event_cb(ui->screen_6_label_3, screen2_4_page_cb, LV_EVENT_ALL, ui->screen_6_label_3);
    lv_obj_add_event_cb(ui->screen_6_label_4, screen2_4_page_cb, LV_EVENT_ALL, ui->screen_6_label_4);
}

