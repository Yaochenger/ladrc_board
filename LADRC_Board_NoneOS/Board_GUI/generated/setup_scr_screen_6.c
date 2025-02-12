/*
* Copyright 2025 NXP
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


void setup_scr_screen_6(lv_ui *ui)
{
	//Write codes screen_6
	ui->screen_6 = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_6, 128, 128);

	//Write style for screen_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_6_cont_1
	ui->screen_6_cont_1 = lv_obj_create(ui->screen_6);
	lv_obj_set_pos(ui->screen_6_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_6_cont_1, 128, 128);
	lv_obj_set_scrollbar_mode(ui->screen_6_cont_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_6_cont_1, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_6_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_6_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_6_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_6_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_6_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_6_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_cont_1, lv_color_hex(0xddff00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_6_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_6_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_6_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_6_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_6_arc_1
	ui->screen_6_arc_1 = lv_arc_create(ui->screen_6_cont_1);
	lv_arc_set_mode(ui->screen_6_arc_1, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->screen_6_arc_1, 0, 100);
	lv_arc_set_bg_angles(ui->screen_6_arc_1, 0, 360);
	lv_arc_set_angles(ui->screen_6_arc_1, 0, 0);
	lv_arc_set_rotation(ui->screen_6_arc_1, 0);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_1, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_arc_1, 11, 6);
	lv_obj_set_size(ui->screen_6_arc_1, 50, 50);

	//Write style for screen_6_arc_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_1, lv_color_hex(0xffab00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_6_arc_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_arc_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_6_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_6_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_6_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_6_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_6_arc_1, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_1, lv_color_hex(0xff00b2), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->screen_6_arc_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_6_arc_2
	ui->screen_6_arc_2 = lv_arc_create(ui->screen_6_cont_1);
	lv_arc_set_mode(ui->screen_6_arc_2, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->screen_6_arc_2, 0, 100);
	lv_arc_set_bg_angles(ui->screen_6_arc_2, 0, 360);
	lv_arc_set_angles(ui->screen_6_arc_2, 0, 0);
	lv_arc_set_rotation(ui->screen_6_arc_2, 0);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_2, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_arc_2, 65, 6);
	lv_obj_set_size(ui->screen_6_arc_2, 50, 50);

	//Write style for screen_6_arc_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_2, lv_color_hex(0xffab00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_6_arc_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_2, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_arc_2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_6_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_6_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_6_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_6_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_6_arc_2, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_2, lv_color_hex(0xff00b2), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->screen_6_arc_2, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_6_arc_3
	ui->screen_6_arc_3 = lv_arc_create(ui->screen_6_cont_1);
	lv_arc_set_mode(ui->screen_6_arc_3, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->screen_6_arc_3, 0, 100);
	lv_arc_set_bg_angles(ui->screen_6_arc_3, 0, 360);
	lv_arc_set_angles(ui->screen_6_arc_3, 0, 0);
	lv_arc_set_rotation(ui->screen_6_arc_3, 0);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_3, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_arc_3, 11, 67);
	lv_obj_set_size(ui->screen_6_arc_3, 50, 50);

	//Write style for screen_6_arc_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_3, lv_color_hex(0xffab00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_6_arc_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_3, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_arc_3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_3, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_3, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_6_arc_3, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_radius(ui->screen_6_arc_3, 6, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_top(ui->screen_6_arc_3, 20, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_bottom(ui->screen_6_arc_3, 20, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_left(ui->screen_6_arc_3, 20, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_right(ui->screen_6_arc_3, 20, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_6_arc_3, 0, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Write style for screen_6_arc_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_6_arc_3, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_3, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_3, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_3, lv_color_hex(0xff00b2), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->screen_6_arc_3, 1, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_6_arc_4
	ui->screen_6_arc_4 = lv_arc_create(ui->screen_6_cont_1);
	lv_arc_set_mode(ui->screen_6_arc_4, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->screen_6_arc_4, 0, 100);
	lv_arc_set_bg_angles(ui->screen_6_arc_4, 0, 360);
	lv_arc_set_angles(ui->screen_6_arc_4, 0, 0);
	lv_arc_set_rotation(ui->screen_6_arc_4, 0);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_4, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->screen_6_arc_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_arc_4, 65, 67);
	lv_obj_set_size(ui->screen_6_arc_4, 50, 50);

	//Write style for screen_6_arc_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_4, lv_color_hex(0xffab00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_6_arc_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_4, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_arc_4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_6_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_6_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_6_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_6_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_6_arc_4, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_6_arc_4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_6_arc_4, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_6_arc_4, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_arc_4, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_6_arc_4, lv_color_hex(0xff00b2), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->screen_6_arc_4, 1, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_6_btn_1
	ui->screen_6_btn_1 = lv_btn_create(ui->screen_6_cont_1);
	ui->screen_6_btn_1_label = lv_label_create(ui->screen_6_btn_1);
	lv_label_set_text(ui->screen_6_btn_1_label, "M1");
	lv_label_set_long_mode(ui->screen_6_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_6_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_6_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_btn_1, 30, 27);
	lv_obj_set_size(ui->screen_6_btn_1, 15, 10);

	//Write style for screen_6_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_6_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_6_btn_1, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_6_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_6_btn_2
	ui->screen_6_btn_2 = lv_btn_create(ui->screen_6_cont_1);
	ui->screen_6_btn_2_label = lv_label_create(ui->screen_6_btn_2);
	lv_label_set_text(ui->screen_6_btn_2_label, "M2");
	lv_label_set_long_mode(ui->screen_6_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_6_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_6_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_btn_2, 82, 27);
	lv_obj_set_size(ui->screen_6_btn_2, 15, 10);

	//Write style for screen_6_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_6_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_6_btn_2, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_6_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_6_btn_3
	ui->screen_6_btn_3 = lv_btn_create(ui->screen_6_cont_1);
	ui->screen_6_btn_3_label = lv_label_create(ui->screen_6_btn_3);
	lv_label_set_text(ui->screen_6_btn_3_label, "M3");
	lv_label_set_long_mode(ui->screen_6_btn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_6_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_6_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_btn_3, 30, 87);
	lv_obj_set_size(ui->screen_6_btn_3, 15, 10);

	//Write style for screen_6_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_6_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_6_btn_3, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_6_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_6_btn_4
	ui->screen_6_btn_4 = lv_btn_create(ui->screen_6_cont_1);
	ui->screen_6_btn_4_label = lv_label_create(ui->screen_6_btn_4);
	lv_label_set_text(ui->screen_6_btn_4_label, "M4");
	lv_label_set_long_mode(ui->screen_6_btn_4_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_6_btn_4_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_6_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_6_btn_4, 82, 87);
	lv_obj_set_size(ui->screen_6_btn_4, 15, 10);

	//Write style for screen_6_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_6_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_6_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_6_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_6_btn_4, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_6_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_6_label_1
	ui->screen_6_label_1 = lv_label_create(ui->screen_6_cont_1);
	lv_label_set_text(ui->screen_6_label_1, "motor control");
	lv_label_set_long_mode(ui->screen_6_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_6_label_1, 14, 55);
	lv_obj_set_size(ui->screen_6_label_1, 100, 10);

	//Write style for screen_6_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_6_label_1, lv_color_hex(0x00c4ff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_6_label_1, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_6_label_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_6_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_6_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_6);

	
}
