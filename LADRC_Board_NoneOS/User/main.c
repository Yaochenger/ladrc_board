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
#include "lvgl.h"
#include "events_init.h"
#include "gui_guider.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
uint16_t cnt= 0, dir =0;
extern LDRC_Encoder_Handler TIMER3_MOTOR;
extern LDRC_Encoder_Handler TIMER4_MOTOR;
extern LDRC_Encoder_Handler TIMER5_MOTOR;
extern LDRC_Encoder_Handler TIMER8_MOTOR;
void MultiTimerCallback1(MultiTimer* timer, void* userData);

lv_ui guider_ui;
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    EXTI0_GPIO_Init();
    LED_GPIO_Init();
    userShellInit(); //letter Shell
    Lcd_Init();
    Lcd_Clear(WHITE);//clear LCD
    TIMER6_GPIO_Init(10 - 1, 9600 - 1);
    TIMER7_GPIO_Init(10 - 1, 9600 - 1);

    multiTimerInstall(getPlatformTicks);
    MultiTimer timer1;

    multiTimerStart(&timer1, 10, MultiTimerCallback1, NULL); // 1000 ms repeating

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    extern void custom_init(lv_ui *ui);
    custom_init(&guider_ui);

    while(1)
    {
        multiTimerYield();
        lv_timer_handler();
    }
}

void MultiTimerCallback1(MultiTimer* timer, void* userData) {
    printf("val:%d\n", (int)getPlatformTicks() );   
    multiTimerStart(timer, 500, MultiTimerCallback1, NULL);
}


