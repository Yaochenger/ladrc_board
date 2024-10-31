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


void setup_scr_screen_1(lv_ui *ui)
{
	//Write codes screen_1
	ui->screen_1 = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_1, 128, 128);

	//Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_cont_1
	ui->screen_1_cont_1 = lv_obj_create(ui->screen_1);
	lv_obj_set_pos(ui->screen_1_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_1_cont_1, 128, 128);
	lv_obj_set_scrollbar_mode(ui->screen_1_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_1_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_1_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_1_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_1_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_1_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_1_list_1
	ui->screen_1_list_1 = lv_list_create(ui->screen_1_cont_1);
	ui->screen_1_list_1_item0 = lv_list_add_btn(ui->screen_1_list_1, LV_SYMBOL_LIST, "LED");
	ui->screen_1_list_1_item1 = lv_list_add_btn(ui->screen_1_list_1, LV_SYMBOL_LIST, "MOTOR");
	ui->screen_1_list_1_item2 = lv_list_add_btn(ui->screen_1_list_1, LV_SYMBOL_LIST, "MPU6050");
	ui->screen_1_list_1_item3 = lv_list_add_btn(ui->screen_1_list_1, LV_SYMBOL_LIST, "BLE");
	ui->screen_1_list_1_item4 = lv_list_add_btn(ui->screen_1_list_1, LV_SYMBOL_LIST, "NULL");
	ui->screen_1_list_1_item5 = lv_list_add_btn(ui->screen_1_list_1, LV_SYMBOL_LIST, "NULL");
	lv_obj_set_pos(ui->screen_1_list_1, 0, 0);
	lv_obj_set_size(ui->screen_1_list_1, 124, 124);
	lv_obj_set_scrollbar_mode(ui->screen_1_list_1, LV_SCROLLBAR_MODE_ON);

	//Write style state: LV_STATE_DEFAULT for &style_screen_1_list_1_main_main_default
	static lv_style_t style_screen_1_list_1_main_main_default;
	ui_init_style(&style_screen_1_list_1_main_main_default);
	
	lv_style_set_pad_top(&style_screen_1_list_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_1_list_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_1_list_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_1_list_1_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_1_list_1_main_main_default, 255);
	lv_style_set_bg_color(&style_screen_1_list_1_main_main_default, lv_color_hex(0x282294));
	lv_style_set_bg_grad_dir(&style_screen_1_list_1_main_main_default, LV_GRAD_DIR_HOR);
	lv_style_set_bg_grad_color(&style_screen_1_list_1_main_main_default, lv_color_hex(0x64ead2));
	lv_style_set_border_width(&style_screen_1_list_1_main_main_default, 0);
	lv_style_set_radius(&style_screen_1_list_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_1_list_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_1_list_1, &style_screen_1_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_1_list_1_main_scrollbar_default
	static lv_style_t style_screen_1_list_1_main_scrollbar_default;
	ui_init_style(&style_screen_1_list_1_main_scrollbar_default);
	
	lv_style_set_radius(&style_screen_1_list_1_main_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_1_list_1_main_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_1_list_1_main_scrollbar_default, lv_color_hex(0xe8e8e8));
	lv_obj_add_style(ui->screen_1_list_1, &style_screen_1_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_1_list_1_extra_btns_main_default
	static lv_style_t style_screen_1_list_1_extra_btns_main_default;
	ui_init_style(&style_screen_1_list_1_extra_btns_main_default);
	
	lv_style_set_pad_top(&style_screen_1_list_1_extra_btns_main_default, 0);
	lv_style_set_pad_left(&style_screen_1_list_1_extra_btns_main_default, 10);
	lv_style_set_pad_right(&style_screen_1_list_1_extra_btns_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_1_list_1_extra_btns_main_default, 6);
	lv_style_set_border_width(&style_screen_1_list_1_extra_btns_main_default, 1);
	lv_style_set_border_opa(&style_screen_1_list_1_extra_btns_main_default, 198);
	lv_style_set_border_color(&style_screen_1_list_1_extra_btns_main_default, lv_color_hex(0xBEAF14));
	lv_style_set_border_side(&style_screen_1_list_1_extra_btns_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_screen_1_list_1_extra_btns_main_default, lv_color_hex(0xfef6ea));
	lv_style_set_text_font(&style_screen_1_list_1_extra_btns_main_default, &lv_font_arial_12);
	lv_style_set_radius(&style_screen_1_list_1_extra_btns_main_default, 0);
	lv_style_set_bg_opa(&style_screen_1_list_1_extra_btns_main_default, 0);
	lv_obj_add_style(ui->screen_1_list_1_item5, &style_screen_1_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_1_list_1_item4, &style_screen_1_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_1_list_1_item3, &style_screen_1_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_1_list_1_item2, &style_screen_1_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_1_list_1_item1, &style_screen_1_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_1_list_1_item0, &style_screen_1_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_1_list_1_extra_texts_main_default
	static lv_style_t style_screen_1_list_1_extra_texts_main_default;
	ui_init_style(&style_screen_1_list_1_extra_texts_main_default);
	
	lv_style_set_pad_top(&style_screen_1_list_1_extra_texts_main_default, 6);
	lv_style_set_pad_left(&style_screen_1_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_right(&style_screen_1_list_1_extra_texts_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_1_list_1_extra_texts_main_default, 0);
	lv_style_set_border_width(&style_screen_1_list_1_extra_texts_main_default, 0);
	lv_style_set_text_color(&style_screen_1_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_1_list_1_extra_texts_main_default, &lv_font_arial_12);
	lv_style_set_radius(&style_screen_1_list_1_extra_texts_main_default, 3);
	lv_style_set_bg_opa(&style_screen_1_list_1_extra_texts_main_default, 0);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_1);

	
}
