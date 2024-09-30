/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

#include "debug.h"
#include "board_config.h"
#include "user_peripheral_driver.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
uint16_t cnt= 0, dir =0;

static void event_handler(lv_event_t * e) {
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, NULL); // ��ȡ��ǩ����

    if (e->code == LV_EVENT_PRESSED) {
        lv_label_set_text(label, "1");  // ����ʱ�����ַ�Ϊ 1
    } else if (e->code == LV_EVENT_RELEASED) {
        lv_label_set_text(label, "0");  // �ͷ�ʱ�����ַ�Ϊ 0
    }
}

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    EXTI0_GPIO_Init();
    userShellInit(); //letter Shell
    Lcd_Init();
    Lcd_Clear(WHITE);//clear LCD
    TIMER7_GPIO_Init(10 - 1, 9600 - 1);
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    TIMER2_GPIO_Init(10000 - 1,96 - 1);
    TIMER8_ENCODER_GPIO_Init();
    TIMER3_ENCODER_GPIO_Init();
    TIMER4_ENCODER_GPIO_Init();
    TIMER5_ENCODER_GPIO_Init();
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 100, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    // ����һ����ǩ��ʾ�ַ�
    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "0");  // ��ʼ�ַ�Ϊ 0
    lv_obj_center(label);

    while(1)
    {
#if 0
        cnt = TIM_GetCounter(TIM3);
        dir = TIMER3_ENCODER_COUNTING_DIR();
        printf("cnt=%d dir=%d\r\n",cnt, dir);
        Delay_Ms(1000);
#endif
        Delay_Ms(5);
        lv_timer_handler();
    }
}


