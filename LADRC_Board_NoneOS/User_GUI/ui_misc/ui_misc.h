#ifndef UI_MISC_H
#define UI_MISC_H

void ui_misc_update_label(lv_obj_t* label, float value);
int8_t ui_misc_cnt_update(int8_t *cnt, bool increment);
void ui_misc_txt_set (lv_obj_t *obj, const char *format , char *buffer, uint32_t size, uint32_t cnt);
void ui_misc_arc_val(lv_obj_t * obj, uint32_t *key, int8_t *cnt);
void ui_misc_motor_txt_val (lv_obj_t *obj, uint32_t *key, const char *format,uint32_t min, uint32_t max, uint32_t step, uint32_t* i);
void ui_misc_set_txt(void);

#endif // UI_MISC_H