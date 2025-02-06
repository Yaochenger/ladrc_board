/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "../../lvgl.h"
/* USER Keypad */
#include "key.h"
/*********************
 *      DEFINES
 *********************/
static bool keypad_mode = 0;
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_keypad;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Keypad (supports GUI usage only with key)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;
    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

    lv_group_t * group = lv_group_create();
    lv_group_set_default(group);
    lv_indev_set_group(indev_keypad, group);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();

    keypad_mode = lv_group_get_editing(lv_group_get_default());
    if (act_key != 0)
    {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        if (keypad_mode == 0)
        {
            switch (act_key)
            {
            case 1:
                act_key = LV_KEY_NEXT; // LV_KEY_RIGHT
                break;
            case 2:
                act_key = LV_KEY_ESC; // LV_KEY_UP
                break;
            case 3:
                act_key = LV_KEY_ENTER; // LV_KEY_DOWN
                break;
            case 4:
                act_key = LV_KEY_PREV; // LV_KEY_PREV
                break;
            }
        }
        else
        {
            switch (act_key)
            {
            case 1:
                act_key = LV_KEY_RIGHT; // LV_KEY_RIGHT
                break;
            case 2:
                act_key = LV_KEY_ESC; // LV_KEY_UP
                break;
            case 3:
                act_key = LV_KEY_ENTER; // LV_KEY_DOWN
                break;
            case 4:
                act_key = LV_KEY_LEFT; // LV_KEY_PREV
                break;
            }
        }

        last_key = act_key;
    } else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void) {
    /*Your code comes here*/
    if ((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)) == 0) {
        return 1;
    }
    if ((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)) == 0) {
        return 2;
    }
    if ((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)) == 0) {
        return 3;
    }
    if ((GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)) == 0) {
        return 4;
    }
    return 0;
}
#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
