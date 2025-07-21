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
#include "ui_misc.h"
#include "ui_page.h"
#include "ui_timer.h"

/*********************
 *      UI ELEMENTS
 *  main screen -> second screen -> third screen (id) -> fourth screen (id)
 *
 *********************/

/*********************
 *      UI Group
 *  group[0] SCR_LED_ID
 *  group[1] SCR_LED_ID
 *  group[2] SCR_LED_ID
 *  group[3] SCR_MOTOR_ID
 *  group[4] SCR_MPU6050_ID
 *  group[5] SCR_BLE_ID
 *  group[6] SCR_ADC_ID
 *  group[7] SCR_MOTOR_ALL_ID
 *  group[8] SCR_MOTOR_ONE_ID
 *********************/

/*********************
 *  global variable
 *********************/
static uint32_t motor_val[4];

/*********************
 *      EXTERN
 *********************/

extern lv_group_t *gui_group[usr_group_num];
extern lv_timer_t *gui_timer[usr_timer_num];

extern lv_obj_t *screen1_saved_focus_obj;
extern lv_obj_t *screen2_saved_focus_obj;
extern lv_obj_t *screen3_saved_focus_obj;

extern volatile bool g_is_editing;
extern lv_indev_t *indev_keypad;

lv_ui guider_ui;

/**********************
 *  STATIC UI CallBack
 **********************/

/**
 * @brief [第<1>页面/主页面响应事件回调函数]]
 * @param  button
 * @brief [切换至第<1>级页面]
 */
static void main_scr_callback (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code (e);

    if (code == LV_EVENT_PRESSED) {
        load_screen_second();
    }
}

/**
 * @brief [第<2>页面/菜单页面响应事件回调函数]
 * @param  screen_1_list_1_item0
 * @param  screen_1_list_1_item1
 * @param  screen_1_list_1_item2
 * @param  screen_1_list_1_item3
 * @param  screen_1_list_1_item4
 * @param  screen_1_list_1_item5
 * @brief [第<2>页面 to 第<3.x>级页面]
 */
static void second_scr_callback (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code (e);
    uint32_t key = lv_event_get_key (e);

    if (key == LV_KEY_ESC) {
        screen1_saved_focus_obj = lv_group_get_focused (gui_group[1]);
        load_screen_main();
    }

    if (code == LV_EVENT_PRESSED) {
        screen1_saved_focus_obj = lv_group_get_focused (gui_group[1]);

        if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item0) {
            load_screen_third (SCR_LED_ID);
        } else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item1) {
            load_screen_third (SCR_MOTOR_ID);
        } else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item2) {
            gui_timer[0] = lv_timer_create (usr_timer_mpu6050, 50, (void *)guider_ui.screen_4_label_8);  // mpu6050
            MPU_Init();
            MPU6050_Filter_Init (50);
            load_screen_third (SCR_MPU6050_ID);
        } else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item3)  // Bluetoolh
        {
            gui_timer[1] = lv_timer_create (usr_timer_bluetooth, 50, NULL);
            UART2_GPIO_Init();
            load_screen_third (SCR_BLE_ID);
        } else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item4)  // ADC
        {
            gui_timer[2] = lv_timer_create (usr_timer_adc, 50, NULL);
            ADC_GPIO_Init();
            load_screen_third (SCR_ADC_ID);
        } else if (screen1_saved_focus_obj == guider_ui.screen_1_list_1_item5) {
            load_screen_main();
        }
    }
}

/**
 * @brief [第<3>页面/LED控制页面响应事件回调函数]
 * @param  button
 * @brief [控制LED的亮灭]
 */
static void third_led_scr_callback (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code (e);
    uint32_t key = lv_event_get_key (e);
    static int led = 0;
    if (code == LV_EVENT_PRESSED) {
        led++;
        if (led % 2 == 0) {
            GPIO_SetBits (GPIOD, GPIO_Pin_8);
            lv_led_on (guider_ui.screen_2_led_1);
        } else {
            GPIO_ResetBits (GPIOD, GPIO_Pin_8);
            lv_led_off (guider_ui.screen_2_led_1);
        }
    }

    if (key == LV_KEY_ESC) {
        load_screen_second();
    }
}

/**
 * @brief [第<3>页面/电机控制菜单响应事件回调函数]
 * @param  screen_7_list_1_item0
 * @param  screen_7_list_1_item1
 * @param  screen_7_list_1_item2
 * @param  screen_7_list_1_item3
 * @brief [切换电机控制页面]
 */
static void third_menu_scr_callback (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code (e);
    uint32_t key = lv_event_get_key (e);

    if (key == LV_KEY_ESC) {
        screen2_saved_focus_obj = lv_group_get_focused (gui_group[3]);
        load_screen_second();
    }

    if (code == LV_EVENT_PRESSED) {
        screen2_saved_focus_obj = lv_group_get_focused (gui_group[3]);

        if (screen2_saved_focus_obj == guider_ui.screen_7_list_1_item0) {
            load_screen_fourth (SCR_MOTOR_ALL_ID);
        } else if (screen2_saved_focus_obj == guider_ui.screen_7_list_1_item1) {
            load_screen_fourth (SCR_MOTOR_ONE_ID);
        } else if (screen2_saved_focus_obj == guider_ui.screen_7_list_1_item2) {
            load_screen_second();
        } else if (screen2_saved_focus_obj == guider_ui.screen_7_list_1_item3)  // Bluetoolh
        {
            load_screen_second();
        }
    }
}

/**
 * @brief [第<4>页面/多个电机控制页面响应事件回调函数]
 * @param  screen_8_btn_1
 * @param  screen_8_btn_2
 * @param  screen_8_btn_3
 * @param  screen_8_btn_4
 * @brief [切换电机控制页面]
 */
static void fourth_all_motor_scr_callback (lv_event_t *e) {
    char buffer[5];
    uint8_t i = 0;
    static int8_t cnt[4] = {0};
    uint32_t key = lv_event_get_key (e);
    lv_obj_t *label = lv_group_get_focused (gui_group[7]);
    if (label != NULL) {
        if (label == guider_ui.screen_6_btn_1) {
            ui_misc_arc_val (guider_ui.screen_6_arc_1, &key, &(cnt[0]));
            ui_misc_txt_set (guider_ui.screen_6_btn_1_label, "%d", buffer, sizeof (buffer), cnt[0]);
        } else if (label == guider_ui.screen_6_btn_2) {
            ui_misc_arc_val (guider_ui.screen_6_arc_2, &key, &(cnt[1]));
            ui_misc_txt_set (guider_ui.screen_6_btn_2_label, "%d", buffer, sizeof (buffer), cnt[1]);
        } else if (label == guider_ui.screen_6_btn_3) {
            ui_misc_arc_val (guider_ui.screen_6_arc_3, &key, &(cnt[2]));
            ui_misc_txt_set (guider_ui.screen_6_btn_3_label, "%d", buffer, sizeof (buffer), cnt[2]);
        } else if (label == guider_ui.screen_6_btn_4) {
            ui_misc_arc_val (guider_ui.screen_6_arc_4, &key, &(cnt[3]));
            ui_misc_txt_set (guider_ui.screen_6_btn_4_label, "%d", buffer, sizeof (buffer), cnt[3]);
        } else if (label == guider_ui.screen_6_cont_1) {
            for (i = 0; i < 4; i++) {
                cnt[i] = 0;
            }
            lv_arc_set_value (guider_ui.screen_6_arc_1, 0);
            lv_arc_set_value (guider_ui.screen_6_arc_2, 0);
            lv_arc_set_value (guider_ui.screen_6_arc_3, 0);
            lv_arc_set_value (guider_ui.screen_6_arc_4, 0);
            printf ("to do :motor stop\r\n");
        }
    }

    if (key == LV_KEY_ESC) {
        ui_misc_set_txt();
        load_screen_third (SCR_MOTOR_ID);
    }

    if (key == LV_KEY_ENTER) {
        g_is_editing = !g_is_editing;
        if (!g_is_editing) {
            ui_misc_set_txt();
            lv_obj_set_style_bg_color (guider_ui.screen_6_cont_1, lv_color_hex (0x2F35DA), LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            lv_obj_set_style_bg_color (guider_ui.screen_6_cont_1, lv_color_hex (0xDDFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        lv_group_set_editing (lv_group_get_default(), g_is_editing);
    }
}

/**
 * @brief [第<4>页面/单个电机控制页面响应事件回调函数]
 * @param  screen_8_btn_1
 * @param  screen_8_btn_2
 * @param  screen_8_btn_3
 * @param  screen_8_btn_4
 * @brief [切换电机控制页面]
 */
static void fourth_one_motor_scr_callback (lv_event_t *e) {
    uint32_t key = lv_event_get_key (e);
    lv_obj_t *label = lv_group_get_focused (gui_group[8]);

    if (key == LV_KEY_ESC) {
        screen3_saved_focus_obj = lv_group_get_focused (gui_group[8]);
        load_screen_third (SCR_MOTOR_ID);
    }

    if (label != NULL) {
        if (label == guider_ui.screen_8_btn_1) {
            ui_misc_motor_txt_val (guider_ui.screen_8_label_1,
                                   &key,
                                   "MOTOR%d",
                                   1, 4, 1,
                                   &motor_val[0]);
        } else if (label == guider_ui.screen_8_btn_2) {
            ui_misc_motor_txt_val (guider_ui.screen_8_label_2,
                                   &key,
                                   "%dHz",
                                   0, 10000, 100,
                                   &motor_val[1]);
        } else if (label == guider_ui.screen_8_btn_3) {
            ui_misc_motor_txt_val (guider_ui.screen_8_label_3,
                                   &key,
                                   "%d%%",
                                   0, 100, 5,
                                   &motor_val[2]);
        } else if (label == guider_ui.screen_8_btn_4) {
            if (key == LV_KEY_RIGHT) {
                lv_label_set_text (guider_ui.screen_8_label_5, "Wait");
            } else if (key == LV_KEY_LEFT) {
                lv_label_set_text (guider_ui.screen_8_label_5, "Ready");
            }
        }
    }

    if (key == LV_KEY_ENTER) {
        g_is_editing = !g_is_editing;
        lv_group_set_editing (lv_group_get_default(), g_is_editing);
    }
}

/**
 * @brief [返回第<2>页面/菜单页面响应事件回调函数]
 * @param  screen_8_btn_1
 * @param  screen_8_btn_2
 * @param  screen_8_btn_3
 * @param  screen_8_btn_4
 * @brief [从其他页面返回至第<2>页面]
 */
static void back_to_second_scr_callback (lv_event_t *e) {
    uint32_t key = lv_event_get_key (e);
    lv_group_t *group_temp = lv_group_get_default();
    if (key == LV_KEY_ESC) {
        if (group_temp == gui_group[6]) {
            lv_timer_del (gui_timer[2]);
        } else if (group_temp == gui_group[4]) {
            lv_timer_del (gui_timer[0]);
        } else if (group_temp == gui_group[5]) {
            lv_timer_del (gui_timer[1]);
        }
        load_screen_second();
    }
}

/**
 * @brief [UI初始化函数]
 */
void custom_init (lv_ui *ui) {
    setup_scr_screen_1 (ui);
    setup_scr_screen_2 (ui);
    setup_scr_screen_3 (ui);
    setup_scr_screen_4 (ui);
    setup_scr_screen_5 (ui);
    setup_scr_screen_6 (ui);
    setup_scr_screen_7 (ui);
    setup_scr_screen_8 (ui);

    for (int var = 0; var < usr_group_num; var++) {
        gui_group[var] = lv_group_create();
    }

    lv_obj_add_event_cb (ui->screen_btn_1, main_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_1_list_1_item0, second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_1_list_1_item1, second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_1_list_1_item2, second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_1_list_1_item3, second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_1_list_1_item4, second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_1_list_1_item5, second_scr_callback, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb (ui->screen_2_btn_1, third_led_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_3_ta_1, back_to_second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_4_label_8, back_to_second_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_5_cont_1, back_to_second_scr_callback, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb (ui->screen_6_cont_1, fourth_all_motor_scr_callback, LV_EVENT_PRESSED | LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb (ui->screen_6_btn_1, fourth_all_motor_scr_callback, LV_EVENT_KEY, ui->screen_6_btn_1);
    lv_obj_add_event_cb (ui->screen_6_btn_2, fourth_all_motor_scr_callback, LV_EVENT_KEY, ui->screen_6_btn_2);
    lv_obj_add_event_cb (ui->screen_6_btn_3, fourth_all_motor_scr_callback, LV_EVENT_KEY, ui->screen_6_btn_3);
    lv_obj_add_event_cb (ui->screen_6_btn_4, fourth_all_motor_scr_callback, LV_EVENT_KEY, ui->screen_6_btn_4);

    lv_obj_add_event_cb (ui->screen_7_list_1_item0, third_menu_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_7_list_1_item1, third_menu_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_7_list_1_item2, third_menu_scr_callback, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb (ui->screen_7_list_1_item3, third_menu_scr_callback, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb (ui->screen_8_btn_1, fourth_one_motor_scr_callback, LV_EVENT_KEY, ui->screen_8_btn_1);
    lv_obj_add_event_cb (ui->screen_8_btn_2, fourth_one_motor_scr_callback, LV_EVENT_KEY, ui->screen_8_btn_2);
    lv_obj_add_event_cb (ui->screen_8_btn_3, fourth_one_motor_scr_callback, LV_EVENT_KEY, ui->screen_8_btn_3);
    lv_obj_add_event_cb (ui->screen_8_btn_4, fourth_one_motor_scr_callback, LV_EVENT_KEY, ui->screen_8_btn_4);
}
