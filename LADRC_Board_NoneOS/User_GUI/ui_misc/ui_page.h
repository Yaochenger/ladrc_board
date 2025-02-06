#ifndef UI_PAGE_H
#define UI_PAGE_H

#define usr_group_num 9

typedef enum {
    SCR_LED_ID = 1,
    SCR_MOTOR_ID = 2,
    SCR_MPU6050_ID = 3,
    SCR_BLE_ID = 4,
    SCR_ADC_ID = 5,
} third_screen_id_t;

typedef enum {
    SCR_MOTOR_ALL_ID = 1,
    SCR_MOTOR_ONE_ID = 2,
    SCR_PROTOCOL_ID = 3,
} fourth_screen_id_t;

void load_screen_main(void);
void load_screen_second(void);
void load_screen_third(third_screen_id_t id);
void load_screen_fourth(fourth_screen_id_t id);

#endif // UI_PAGE_H