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

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
static void btn_label_time_add_cb(lv_event_t * e)
{
    static int times = 0;
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, NULL);
    lv_event_code_t code = lv_event_get_code(e);
    uint32_t key = lv_event_get_key(e);  // »ñÈ¡¼üÖµ

    if (code == LV_EVENT_KEY)
    {
        if (key == LV_KEY_UP)
        {
            times++;
            lv_label_set_text_fmt(label, "%d", times);
        }
        else if (key == LV_KEY_DOWN)
        {
            times--;
            lv_label_set_text_fmt(label, "%d", times);
        }
        else if (key == LV_KEY_RIGHT)
        {
            times = times + 10;
            lv_label_set_text_fmt(label, "%d", times);
        }
        else if (key == LV_KEY_ENTER)
        {
            times = 0;
            lv_label_set_text_fmt(label, "%d", times);
        }
        lv_label_set_text_fmt(label, "%d", times);
    }

}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    lv_obj_add_event_cb(ui->screen_btn_1, btn_label_time_add_cb, LV_EVENT_KEY, NULL);
}

