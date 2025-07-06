/*
 * uart2.c
 *
 *  Created on: 2024年3月15日
 *      Author: MCU
 */

#include "uart2.h"

chry_ringbuffer_t chry_rbuffer_tid;
static uint8_t rbuffer_pool[1024];
static uint8_t g_recvFinshFlag = 0;

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void UART2_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    if (0 == chry_ringbuffer_init(&chry_rbuffer_tid, rbuffer_pool, 1024))
        printf("\rsuccess\r\n");
    else
        printf("error\r\n");

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = 9600; // 板载蓝牙使用SPP透传模式 这里波特率建议《=9600
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    USART_Cmd(USART2, ENABLE);
    USART_SetAddress(USART2, 0x1);
}

uint8_t *IsUsart1RecvFinsh(void)
{
    return &g_recvFinshFlag;
}

void USART2_IRQHandler(void)
{
    uint16_t Clear = Clear;
    uint8_t res;

    if(USART_GetITStatus(USART2,USART_IT_RXNE)!= RESET)
    {
        res = USART_ReceiveData(USART2);
        chry_ringbuffer_write_byte(&chry_rbuffer_tid, res);
    }

    else if(USART_GetITStatus(USART2, USART_IT_IDLE)!= RESET)
    {
        Clear = USART2->STATR;
        Clear = USART2->DATAR;
        g_recvFinshFlag = 1;
    }
}
