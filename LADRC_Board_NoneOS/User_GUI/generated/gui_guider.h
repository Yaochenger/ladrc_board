/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_cont_1;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_btn_1;
	lv_obj_t *screen_btn_1_label;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_cont_1;
	lv_obj_t *screen_1_list_1;
	lv_obj_t *screen_1_list_1_item0;
	lv_obj_t *screen_1_list_1_item1;
	lv_obj_t *screen_1_list_1_item2;
	lv_obj_t *screen_1_list_1_item3;
	lv_obj_t *screen_1_list_1_item4;
	lv_obj_t *screen_1_list_1_item5;
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_cont_1;
	lv_obj_t *screen_2_btn_1;
	lv_obj_t *screen_2_btn_1_label;
	lv_obj_t *screen_2_led_1;
	lv_obj_t *screen_3;
	bool screen_3_del;
	lv_obj_t *screen_3_cont_1;
	lv_obj_t *screen_3_ta_1;
	lv_obj_t *screen_3_label_1;
	lv_obj_t *screen_4;
	bool screen_4_del;
	lv_obj_t *screen_4_cont_1;
	lv_obj_t *screen_4_label_2;
	lv_obj_t *screen_4_label_3;
	lv_obj_t *screen_4_label_4;
	lv_obj_t *screen_4_label_8;
	lv_obj_t *screen_4_label_9;
	lv_obj_t *screen_4_label_10;
	lv_obj_t *screen_4_label_11;
	lv_obj_t *screen_5;
	bool screen_5_del;
	lv_obj_t *screen_5_cont_1;
	lv_obj_t *screen_5_bar_1;
	lv_obj_t *screen_5_bar_2;
	lv_obj_t *screen_5_bar_3;
	lv_obj_t *screen_5_bar_4;
	lv_obj_t *screen_5_bar_5;
	lv_obj_t *screen_5_bar_6;
	lv_obj_t *screen_5_label_1;
	lv_obj_t *screen_5_label_6;
	lv_obj_t *screen_5_label_7;
	lv_obj_t *screen_5_label_8;
	lv_obj_t *screen_5_label_9;
	lv_obj_t *screen_5_label_10;
	lv_obj_t *screen_5_label_11;
	lv_obj_t *screen_6;
	bool screen_6_del;
	lv_obj_t *screen_6_cont_1;
	lv_obj_t *screen_6_arc_1;
	lv_obj_t *screen_6_arc_2;
	lv_obj_t *screen_6_arc_3;
	lv_obj_t *screen_6_arc_4;
	lv_obj_t *screen_6_btn_1;
	lv_obj_t *screen_6_btn_1_label;
	lv_obj_t *screen_6_btn_2;
	lv_obj_t *screen_6_btn_2_label;
	lv_obj_t *screen_6_btn_3;
	lv_obj_t *screen_6_btn_3_label;
	lv_obj_t *screen_6_btn_4;
	lv_obj_t *screen_6_btn_4_label;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
void setup_scr_screen_3(lv_ui *ui);
void setup_scr_screen_4(lv_ui *ui);
void setup_scr_screen_5(lv_ui *ui);
void setup_scr_screen_6(lv_ui *ui);

LV_FONT_DECLARE(lv_font_Abel_regular_25)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Abel_regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_Abel_regular_10)


#ifdef __cplusplus
}
#endif
#endif
