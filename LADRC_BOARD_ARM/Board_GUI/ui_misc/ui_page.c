#include "ui_page.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

// 全局标志，指示UI是否处于编辑模式
volatile bool g_is_editing = 0;

// 指针，用于保存不同屏幕的聚焦对象
lv_obj_t *screen1_saved_focus_obj;
lv_obj_t *screen2_saved_focus_obj;
lv_obj_t *screen3_saved_focus_obj;

// 数组，用于存储不同用户界面元素的�?
lv_group_t *gui_group[usr_group_num];

// 外部引用的UI元素和输入设�?
extern lv_ui guider_ui;
extern lv_indev_t *indev_keypad;

void load_screen_main(void)
{
    lv_indev_set_group(indev_keypad, gui_group[0]);
    lv_group_set_default(gui_group[0]);
    lv_group_add_obj(gui_group[0], guider_ui.screen_btn_1);
    lv_group_focus_obj(guider_ui.screen_btn_1);
    lv_scr_load(guider_ui.screen);
}

void load_screen_second(void)
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

void load_screen_third(third_screen_id_t id)
{
    third_screen_id_t temp_id = id;
    lv_indev_set_group(indev_keypad, gui_group[temp_id + 1]);
    lv_group_set_default(gui_group[temp_id + 1]);
    switch (id) {
        case SCR_LED_ID:
            {
                lv_group_add_obj(gui_group[2], guider_ui.screen_2_btn_1);
                lv_group_focus_obj(guider_ui.screen_2_btn_1);
                lv_scr_load(guider_ui.screen_2);
            }
            break;
        case SCR_MOTOR_ID:
            {
                lv_group_add_obj(gui_group[3], guider_ui.screen_7_list_1_item0);
                lv_group_add_obj(gui_group[3], guider_ui.screen_7_list_1_item1);
                lv_group_add_obj(gui_group[3], guider_ui.screen_7_list_1_item2);
                lv_group_add_obj(gui_group[3], guider_ui.screen_7_list_1_item3);

                if (screen2_saved_focus_obj != NULL) {
                    lv_group_focus_obj(screen2_saved_focus_obj);
                    screen2_saved_focus_obj = NULL;
                }
                lv_scr_load(guider_ui.screen_7);
            }
            break;
        case SCR_MPU6050_ID:
            {
                lv_group_add_obj(gui_group[4], guider_ui.screen_4_label_8);
                lv_group_focus_obj(guider_ui.screen_4_label_8);
                lv_scr_load(guider_ui.screen_4);
            }
            break;
        case SCR_BLE_ID:
            {
                lv_group_add_obj(gui_group[5], guider_ui.screen_3_ta_1);
                lv_group_focus_obj(guider_ui.screen_3_ta_1);
                lv_textarea_set_text(guider_ui.screen_3_ta_1, "Hello World\rSerial baud 9600");
                lv_scr_load(guider_ui.screen_3);
            }
            break;
        case SCR_ADC_ID:
            {
                lv_group_add_obj(gui_group[6], guider_ui.screen_5_cont_1);
                lv_group_focus_obj(guider_ui.screen_5_cont_1);
                lv_scr_load(guider_ui.screen_5);
            }
            break;
        default:
            break;
    }
}

void load_screen_fourth(fourth_screen_id_t id)
{
    lv_indev_set_group(indev_keypad, gui_group[id + 6]);
    lv_group_set_default(gui_group[id + 6]);
    switch (id) {
        case SCR_MOTOR_ALL_ID:
            {
                lv_group_add_obj(gui_group[7], guider_ui.screen_6_cont_1);
                lv_group_add_obj(gui_group[7], guider_ui.screen_6_btn_1);
                lv_group_add_obj(gui_group[7], guider_ui.screen_6_btn_2);
                lv_group_add_obj(gui_group[7], guider_ui.screen_6_btn_3);
                lv_group_add_obj(gui_group[7], guider_ui.screen_6_btn_4);
                lv_group_focus_obj(guider_ui.screen_6_cont_1);
                lv_scr_load(guider_ui.screen_6);
            }
            break;
        case SCR_MOTOR_ONE_ID:
            {
                lv_group_add_obj(gui_group[8], guider_ui.screen_8_btn_1);
                lv_group_add_obj(gui_group[8], guider_ui.screen_8_btn_2);
                lv_group_add_obj(gui_group[8], guider_ui.screen_8_btn_3);
                lv_group_add_obj(gui_group[8], guider_ui.screen_8_btn_4);

                if (screen3_saved_focus_obj != NULL) {
                    lv_group_focus_obj(screen3_saved_focus_obj);
                    screen3_saved_focus_obj = NULL;
                }

                lv_scr_load(guider_ui.screen_8);
            }
            break;
        case SCR_PROTOCOL_ID:
            {

            }
            break;
        default:
            break;
    }
}