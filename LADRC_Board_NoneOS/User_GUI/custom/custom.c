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

/*********************
 *      DEFINES
 *********************/
#define usr_group_num 4
#define usr_timer_num 1
#define usr_serie_num 1
/**********************
 *      TYPEDEFS
 **********************/
static void load_screen0(void);
static void load_screen1(void);
static void load_screen2(void);
static void load_screen2_1(void);

static void usr_timer_0(lv_timer_t* timer);
/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_group_t *gui_group[usr_group_num];
static lv_timer_t *gui_timer[usr_timer_num];
static lv_chart_series_t * gui_ser[usr_serie_num];

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
            load_screen0();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item2)
        {
            load_screen0();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item3)
        {
            load_screen0();
        }
        else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item4) // ADC
        {
            load_screen2_1();
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
    if(code == LV_EVENT_PRESSED) {
        led ++;
        if (led % 2 == 0)
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_8);
            lv_led_on(guider_ui.screen_2_led_1);
        }
        else
        {
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

    if (key == LV_KEY_ESC) {
        load_screen1();
    }

}

static void load_screen0(void)
{
    lv_indev_set_group(indev_keypad, gui_group[0]);
    lv_group_add_obj(gui_group[0], guider_ui.screen_btn_1);
    lv_group_focus_obj(guider_ui.screen_btn_1);
    lv_scr_load(guider_ui.screen);
}

static void load_screen1(void)
{
    lv_indev_set_group(indev_keypad, gui_group[1]);
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
    lv_group_add_obj(gui_group[2], guider_ui.screen_2_btn_1);
    lv_scr_load(guider_ui.screen_2);
}

static void load_screen2_1(void)
{
    lv_indev_set_group(indev_keypad, gui_group[3]);
    gui_ser[0] = lv_chart_add_series(guider_ui.screen_3_chart_1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y); // 添加红色数据系列
    gui_timer[0] = lv_timer_create(usr_timer_0, 50, (void *)guider_ui.screen_3_chart_1);
    lv_group_add_obj(gui_group[3], guider_ui.screen_3_chart_1);
    lv_scr_load(guider_ui.screen_3);
}

static void usr_timer_0(lv_timer_t* timer)
{
    lv_obj_t * chart = timer->user_data;  // 获取图表对象
    static int value = 0;

    value = (value + 1) % 4;

    lv_chart_set_next_value(chart, gui_ser[0], value);
    lv_chart_refresh(chart);

}

void custom_init(lv_ui *ui)
{
    setup_scr_screen_1(ui);
    setup_scr_screen_2(ui);
    setup_scr_screen_3(ui);

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
    lv_obj_add_event_cb(ui->screen_2_btn_1, screen2_page_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_3_chart_1, screen2_1_page_cb, LV_EVENT_ALL, NULL);
}

