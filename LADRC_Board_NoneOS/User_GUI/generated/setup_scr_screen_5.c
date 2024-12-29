/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen_5(lv_ui *ui)
{
	//Write codes screen_5
	ui->screen_5 = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_5, 128, 128);

	//Write style for screen_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_cont_1
	ui->screen_5_cont_1 = lv_obj_create(ui->screen_5);
	lv_obj_set_pos(ui->screen_5_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_5_cont_1, 128, 128);
	lv_obj_set_scrollbar_mode(ui->screen_5_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_5_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_5_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_5_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_5_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_cont_1, 243, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_cont_1, lv_color_hex(0x2F35DA), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_bar_1
	ui->screen_5_bar_1 = lv_bar_create(ui->screen_5_cont_1);
	lv_obj_set_style_anim_time(ui->screen_5_bar_1, 1000, 0);
	lv_bar_set_mode(ui->screen_5_bar_1, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_5_bar_1, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_5_bar_1, 3, 15);
	lv_obj_set_size(ui->screen_5_bar_1, 12, 93);

	//Write style for screen_5_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_5_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_1, lv_color_hex(0x00ff7e), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_1, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_5_bar_2
	ui->screen_5_bar_2 = lv_bar_create(ui->screen_5_cont_1);
	lv_obj_set_style_anim_time(ui->screen_5_bar_2, 1000, 0);
	lv_bar_set_mode(ui->screen_5_bar_2, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_5_bar_2, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_5_bar_2, 24, 15);
	lv_obj_set_size(ui->screen_5_bar_2, 12, 93);

	//Write style for screen_5_bar_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_bar_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_5_bar_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_2, lv_color_hex(0x00ff7e), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_2, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_5_bar_3
	ui->screen_5_bar_3 = lv_bar_create(ui->screen_5_cont_1);
	lv_obj_set_style_anim_time(ui->screen_5_bar_3, 1000, 0);
	lv_bar_set_mode(ui->screen_5_bar_3, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_5_bar_3, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_5_bar_3, 45, 15);
	lv_obj_set_size(ui->screen_5_bar_3, 12, 93);

	//Write style for screen_5_bar_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_bar_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_5_bar_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_3, lv_color_hex(0x00ff7e), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_3, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_5_bar_4
	ui->screen_5_bar_4 = lv_bar_create(ui->screen_5_cont_1);
	lv_obj_set_style_anim_time(ui->screen_5_bar_4, 1000, 0);
	lv_bar_set_mode(ui->screen_5_bar_4, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_5_bar_4, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_5_bar_4, 66, 15);
	lv_obj_set_size(ui->screen_5_bar_4, 12, 93);

	//Write style for screen_5_bar_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_bar_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_5_bar_4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_4, lv_color_hex(0x00ff7e), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_4, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_5_bar_5
	ui->screen_5_bar_5 = lv_bar_create(ui->screen_5_cont_1);
	lv_obj_set_style_anim_time(ui->screen_5_bar_5, 1000, 0);
	lv_bar_set_mode(ui->screen_5_bar_5, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_5_bar_5, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_5_bar_5, 87, 15);
	lv_obj_set_size(ui->screen_5_bar_5, 12, 93);

	//Write style for screen_5_bar_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_5, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_bar_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_5_bar_5, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_5, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_5, lv_color_hex(0x00ff7e), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_5, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_5_bar_6
	ui->screen_5_bar_6 = lv_bar_create(ui->screen_5_cont_1);
	lv_obj_set_style_anim_time(ui->screen_5_bar_6, 1000, 0);
	lv_bar_set_mode(ui->screen_5_bar_6, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_5_bar_6, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->screen_5_bar_6, 108, 15);
	lv_obj_set_size(ui->screen_5_bar_6, 12, 93);

	//Write style for screen_5_bar_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_6, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_bar_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_5_bar_6, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_5_bar_6, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_5_bar_6, lv_color_hex(0x00ff7e), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_bar_6, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_5_label_1
	ui->screen_5_label_1 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_1, "C1   C2   C3   C4   C5   C6");
	lv_label_set_long_mode(ui->screen_5_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_1, 2, 110);
	lv_obj_set_size(ui->screen_5_label_1, 120, 16);

	//Write style for screen_5_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_1, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_1, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_label_6
	ui->screen_5_label_6 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_6, "0.0");
	lv_label_set_long_mode(ui->screen_5_label_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_6, 19, 4);
	lv_obj_set_size(ui->screen_5_label_6, 26, 10);

	//Write style for screen_5_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_6, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_6, &lv_font_Abel_regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_label_7
	ui->screen_5_label_7 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_7, "0.0");
	lv_label_set_long_mode(ui->screen_5_label_7, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_7, 39, 4);
	lv_obj_set_size(ui->screen_5_label_7, 26, 10);

	//Write style for screen_5_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_7, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_7, &lv_font_Abel_regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_label_8
	ui->screen_5_label_8 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_8, "0.0");
	lv_label_set_long_mode(ui->screen_5_label_8, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_8, -1, 4);
	lv_obj_set_size(ui->screen_5_label_8, 26, 10);

	//Write style for screen_5_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_8, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_8, &lv_font_Abel_regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_label_9
	ui->screen_5_label_9 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_9, "0.0");
	lv_label_set_long_mode(ui->screen_5_label_9, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_9, 59, 4);
	lv_obj_set_size(ui->screen_5_label_9, 26, 10);

	//Write style for screen_5_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_9, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_9, &lv_font_Abel_regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_label_10
	ui->screen_5_label_10 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_10, "0.0");
	lv_label_set_long_mode(ui->screen_5_label_10, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_10, 79, 4);
	lv_obj_set_size(ui->screen_5_label_10, 26, 10);

	//Write style for screen_5_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_10, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_10, &lv_font_Abel_regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_5_label_11
	ui->screen_5_label_11 = lv_label_create(ui->screen_5_cont_1);
	lv_label_set_text(ui->screen_5_label_11, "0.0");
	lv_label_set_long_mode(ui->screen_5_label_11, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_5_label_11, 99, 4);
	lv_obj_set_size(ui->screen_5_label_11, 26, 10);

	//Write style for screen_5_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_5_label_11, lv_color_hex(0xe5ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_5_label_11, &lv_font_Abel_regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_5_label_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_5_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_5_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_5);

	
}
