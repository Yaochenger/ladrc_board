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
#include "user_peripheral_driver.h"
#include "vofa.h"
#include "LADRC.h"
#include "chry_ringbuffer.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
chry_ringbuffer_t chry_rbuffer_tid;
uint8_t g_recvFinshFlag = 0;
static uint8_t rbuffer_pool[1024];

uint8_t *IsUsart1RecvFinsh(void)
{
    return &g_recvFinshFlag;
}

int main(void)
{
    if (0 == chry_ringbuffer_init(&chry_rbuffer_tid, rbuffer_pool, 1024)) {
        printf("success\r\n");
    } else {
        printf("error\r\n");
    }

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
//    GPIO_KEY_INIT();
//    GPIO_LED_INIT();
    Shell_INIT();

#ifdef LDARC_COMPONENT_MULTITIMER
    multiTimerInstall(getPlatformTicks);
#endif /* LDARC_COMPONENT_MULTITIMER */

#ifdef LDARC_COMPONENT_TFT
    LCD_INIT();
#endif /* LDARC_COMPONENT_TFT */

#ifdef LDARC_COMPONENT_TFT_OFF
    LCD_OFF();
#endif /* LDARC_COMPONENT_TFT */

#ifdef LDARC_DEVICE_TIM6
    TIM6_INIT(10 - 1, 9600 - 1);
#endif /* LDARC_DEVICE_TIM6 */

#ifdef LDARC_DEVICE_TIM7
    TIM7_INIT(10 - 1, 9600 - 1);
#endif /* LDARC_DEVICE_TIM7 */

#ifdef LDARC_COMPONENT_SIMULATION
    SIMULATION_INIT();
    SIMULATION_DINIT();
#endif /* LDARC_COMPONENT_SIMULATION */

#if defined(LDARC_COMPONENT_LVGL) && defined(LDARC_COMPONENT_LVGL)
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    extern void custom_init(lv_ui *ui);
    custom_init(&guider_ui);
#endif /* LDARC_COMPONENT_LVGL */
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
