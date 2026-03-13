/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

#include "ch32v30x.h"
#include "sdkconfig.h"
#include "debug.h"
#include "lshell_port.h"
#include "MultiTimer.h"
#include "tft_st7735s.h"
#include "simulation.h"
#include "vofa.h"
#include "LADRC.h"
#include "chry_ringbuffer.h"
#include "auto_init.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
chry_ringbuffer_t chry_rbuffer_tid;
uint8_t g_recvFinshFlag = 0;
static uint8_t rbuffer_pool[1024];

static int board_startup_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    return 0;
}
INIT_BOARD_EXPORT(board_startup_init);

static int shell_service_init(void)
{
    Shell_INIT();
    return 0;
}
INIT_DEVICE_EXPORT(shell_service_init);

static int ringbuffer_service_init(void)
{
    if (0 == chry_ringbuffer_init(&chry_rbuffer_tid, rbuffer_pool, sizeof(rbuffer_pool))) {
        printf("success\r\n");
        return 0;
    }

    printf("error\r\n");
    return -1;
}
INIT_COMPONENT_EXPORT(ringbuffer_service_init);

#ifdef LDARC_COMPONENT_MULTITIMER
static int multitimer_service_init(void)
{
    multiTimerInstall(getPlatformTicks);
    return 0;
}
INIT_COMPONENT_EXPORT(multitimer_service_init);
#endif /* LDARC_COMPONENT_MULTITIMER */

#ifdef LDARC_COMPONENT_TFT
static int tft_service_init(void)
{
    LCD_INIT();
    return 0;
}
INIT_COMPONENT_EXPORT(tft_service_init);
#endif /* LDARC_COMPONENT_TFT */

#ifdef LDARC_COMPONENT_TFT_OFF
static int tft_off_service_init(void)
{
    LCD_OFF();
    return 0;
}
INIT_APP_EXPORT(tft_off_service_init);
#endif /* LDARC_COMPONENT_TFT_OFF */

#if defined(SDK_USING_TIM2) || defined(SDK_USING_TIM6) || defined(SDK_USING_TIM7)
static int timer_gpio_init(void)
{
    TIM_GPIO_Init();
    return 0;
}
INIT_DEVICE_EXPORT(timer_gpio_init);
#endif /* SDK_USING_TIM2 || SDK_USING_TIM6 || SDK_USING_TIM7 */

#ifdef LDARC_COMPONENT_SIMULATION
static int simulation_service_init(void)
{
    SIMULATION_INIT();
    SIMULATION_DINIT();
    return 0;
}
INIT_APP_EXPORT(simulation_service_init);
#endif /* LDARC_COMPONENT_SIMULATION */

uint8_t *IsUsart1RecvFinsh(void)
{
    return &g_recvFinshFlag;
}

int main(void)
{
    auto_init_run();

    while(1)
    {
#ifdef LDARC_COMPONENT_SIMULATION
        Simulation_parse_command();
#endif /* LDARC_COMPONENT_SIMULATION */

#ifdef LDARC_COMPONENT_MULTITIMER
        multiTimerYield();
#endif /* LDARC_COMPONENT_MULTITIMER */

#if defined(LDARC_COMPONENT_LVGL) && defined(LDARC_COMPONENT_LVGL)
        lv_timer_handler();
#endif /* LDARC_COMPONENT_LVGL */
    }
}

