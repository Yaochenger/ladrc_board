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

/**********************
 *      TYPEDEFS
 **********************/
static void load_screen0(void);
static void load_screen1(void);
static void load_screen2(void);
/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_group_t *gui_group[3];
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
        load_screen0();
    }

    if(code == LV_EVENT_PRESSED) {
        load_screen2();
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
    lv_group_focus_obj(guider_ui.screen_1_list_1_item0);
    lv_scr_load(guider_ui.screen_1);
}

static void load_screen2(void)
{
    lv_indev_set_group(indev_keypad, gui_group[2]);
    lv_group_add_obj(gui_group[2], guider_ui.screen_2_btn_1);
    lv_scr_load(guider_ui.screen_2);
}

void custom_init(lv_ui *ui)
{
    setup_scr_screen_1(ui);
    setup_scr_screen_2(ui);

    for (int var = 0; var < 3; var++) {
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
}

