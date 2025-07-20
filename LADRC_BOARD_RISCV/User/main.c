/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

#include <board_info.h>
#include "debug.h"
#include "drv_config.h"
#include "user_peripheral_driver.h"
#include "lvgl.h"
#include "events_init.h"
#include "gui_guider.h"
#include "vofa.h"
#include "LADRC.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/

extern Command extended_commands[];
extern void parse_command(Command* commands, int cmd_count);
lv_ui guider_ui;

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    EXTI0_GPIO_Init();
    LED_GPIO_Init();
    UART2_GPIO_Init();
    userShellInit();
    board_info();
    Lcd_Init();
    Lcd_Clear(WHITE);

    TIMER6_GPIO_Init(10 - 1, 9600 - 1);
    TIMER7_GPIO_Init(10 - 1, 9600 - 1);

    multiTimerInstall(getPlatformTicks);
    Simulation_Init();

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    extern void custom_init(lv_ui *ui);
    custom_init(&guider_ui);

    LADRC_Init(&USR_Ladrc_Mode);
    USR_Sim_Para_DInit(&USR_Sim_Mode);

    while(1)
    {
        parse_command(extended_commands, vofa_cmd_cnt);
        multiTimerYield();
        lv_timer_handler();
    }
}
