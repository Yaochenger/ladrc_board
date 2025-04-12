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
#include "vofa.h"
#include "LADRC.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
void MulTimer_Simulation_Callback(MultiTimer* timer, void* userData);

extern Command extended_commands[];
extern void parse_command(Command* commands, int cmd_count);
lv_ui guider_ui;
static Mode_Para USR_Sim_Mode;
static LADRC_NUM USR_Ladrc_Mode;
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    EXTI0_GPIO_Init();
    LED_GPIO_Init();
    UART2_GPIO_Init();
    userShellInit(); //letter Shell
    Lcd_Init();
    Lcd_Clear(WHITE);//clear LCD

    TIMER6_GPIO_Init(10 - 1, 9600 - 1);
    TIMER7_GPIO_Init(10 - 1, 9600 - 1);

    multiTimerInstall(getPlatformTicks);
    MultiTimer timer1;

    multiTimerStart(&timer1, 50, MulTimer_Simulation_Callback, NULL); // 50ms repeating

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    extern void custom_init(lv_ui *ui);
    custom_init(&guider_ui);

    LADRC_Init(&USR_Ladrc_Mode);
    USR_Sim_Mode.init_val = 0;
    USR_Sim_Mode.real_val = 0;
    USR_Sim_Mode.expect_val = 200;

    while(1)
    {
        parse_command(extended_commands, vofa_cmd_cnt);
        multiTimerYield();
        lv_timer_handler();
    }
}

void MulTimer_Simulation_Callback(MultiTimer* timer, void* userData)
{
    LADRC_Loop(&USR_Ladrc_Mode, &USR_Sim_Mode.expect_val, &USR_Sim_Mode.real_val);
    USR_Sim_Mode.real_val = USR_Sim_Mode.init_val + USR_Ladrc_Mode.u *0.2;
    ladrc_printf(USART2, "%f,%f,%f,%f,%f,%f\r\n",USR_Ladrc_Mode.v1, USR_Ladrc_Mode.v2,USR_Ladrc_Mode.z1, USR_Ladrc_Mode.z2, USR_Ladrc_Mode.z3,USR_Ladrc_Mode.u);
    multiTimerStart(timer, 50, MulTimer_Simulation_Callback, NULL);
}


