/**
 * @file ui_misc.c
 * @brief Miscellaneous UI functions for LADRC Board NoneOS User GUI.
 *
 * @date Created on: 2023-10-05
 * @author Your Name
 */

#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

void ui_misc_update_label (lv_obj_t *label, float value) {
    char new_text[20];
    snprintf (new_text, sizeof (new_text), "%.1f", value);
    lv_label_set_text (label, new_text);
}

int8_t ui_misc_cnt_update (int8_t *cnt, bool increment) {
    if (increment) {
        if (((*cnt)++) > 99)
            *cnt = 100;
    } else {
        if (((*cnt)--) < 1)
            *cnt = 0;
    }
    return *cnt;
}

void ui_misc_txt_set (lv_obj_t *obj, const char *format , char *buffer, uint32_t size, uint32_t cnt) {
    snprintf (buffer, size, format, cnt);
    lv_label_set_text (obj, buffer);
}

void ui_misc_arc_val (lv_obj_t *obj, uint32_t *key, int8_t *cnt) {
    if (*key == LV_KEY_RIGHT) {
        lv_arc_set_value (obj, ui_misc_cnt_update (cnt, 1));
    }
    if (*key == LV_KEY_LEFT) {
        lv_arc_set_value (obj, ui_misc_cnt_update (cnt, -1));
    }
}

char usr_buffer[7];

void ui_misc_motor_txt_val (lv_obj_t *obj, uint32_t *key, const char *format,uint32_t min, uint32_t max, uint32_t step, uint32_t* i)
{
    if (*key == LV_KEY_RIGHT) {
        *i = (*i < max) ? (*i + step) : min;
    } else if (*key == LV_KEY_LEFT) {
        *i = (*i > min) ? (*i - step) : max;
    }
    ui_misc_txt_set (obj, format, usr_buffer, sizeof(usr_buffer), *i);
}

void ui_misc_set_txt (void) {
    lv_label_set_text (guider_ui.screen_6_btn_1_label, "M1");
    lv_label_set_text (guider_ui.screen_6_btn_2_label, "M2");
    lv_label_set_text (guider_ui.screen_6_btn_3_label, "M3");
    lv_label_set_text (guider_ui.screen_6_btn_4_label, "M4");
}
