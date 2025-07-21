#include "ch32v30x_it.h"
#include "lvgl.h"

volatile uint32_t timer6_tick = 0;

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void NMI_Handler(void)
{
    while (1)
    {

    }
}

void HardFault_Handler(void)
{
    while (1)
    {

    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_SetCounter(TIM3, 0);
        TIM_SetCounter(TIM4, 0);
        TIM_SetCounter(TIM5, 0);
        TIM_SetCounter(TIM8, 0);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


void TIM6_IRQHandler(void)
{
    timer6_tick++;
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    }
}


uint64_t getPlatformTicks(void)
{
    return (uint64_t)timer6_tick;
}


void TIM7_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        lv_tick_inc(1);
    }
}


void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        uint8_t res = USART_ReceiveData(USART2);
        chry_ringbuffer_write_byte(&chry_rbuffer_tid, res);
    }
    else if (USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        volatile uint16_t temp = USART2->STATR;
        temp = USART2->DATAR;
        g_recvFinshFlag = 1;
    }
}
