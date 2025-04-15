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
void MulTimer_Simul_TD_Callback(MultiTimer* timer, void* userData);

extern Command extended_commands[];
extern void parse_command(Command* commands, int cmd_count);
lv_ui guider_ui;
Mode_Para USR_Sim_Mode;
LADRC_NUM USR_Ladrc_Mode;

static MultiTimer timer2;
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
    multiTimerStart(&timer2, 50, MulTimer_Simul_TD_Callback, NULL); // 50ms repeating

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    extern void custom_init(lv_ui *ui);
    custom_init(&guider_ui);

    LADRC_Init(&USR_Ladrc_Mode);
    USR_Sim_Para_DInit(&USR_Sim_Mode);
    LADRC_REST(&USR_Ladrc_Mode);

    while(1)
    {
        parse_command(extended_commands, vofa_cmd_cnt);
        multiTimerYield();
        lv_timer_handler();
    }
}

void MulTimer_Simul_TD_Callback(MultiTimer* timer, void* userData)
{
    if (USR_Sim_Mode.state)
    {
        LADRC_TD(&USR_Ladrc_Mode, 500);
        ladrc_printf(USART2, "%f,%f\r\n",USR_Ladrc_Mode.v1,
                                         USR_Ladrc_Mode.v2);
    }
    multiTimerStart(timer, 50, MulTimer_Simul_TD_Callback, NULL);
}

