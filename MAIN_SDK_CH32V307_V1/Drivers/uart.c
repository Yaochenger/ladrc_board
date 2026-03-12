#include "uart.h"
#include "gpio_pin.h"

static void UART_Init_Config(USART_TypeDef *uart_device,
                              uint32_t uart_clk,
                              const char *tx_pin,
                              const char *rx_pin,
                              uint32_t baudrate,
                              uint32_t remap_cfg)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB1PeriphClockCmd(uart_clk, ENABLE);
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(tx_pin) | SDK_GetGPIORCC(rx_pin), ENABLE);

    if (remap_cfg != 0) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(remap_cfg, ENABLE);
    }

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(tx_pin);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SDK_GetPort(tx_pin), &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(rx_pin);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SDK_GetPort(rx_pin), &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(uart_device, &USART_InitStructure);
    USART_Cmd(uart_device, ENABLE);
}

#ifdef SDK_USING_USART2
static void USART_EnableRxIrq(void)
{
#if (SDK_USING_USART2_ISR)
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    USART_ITConfig(SDK_USING_USART2_DEVICE, USART_IT_RXNE, ENABLE);
    USART_ITConfig(SDK_USING_USART2_DEVICE, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}
#endif

void UART_GPIO_Init(void)
{
#ifdef SDK_USING_USART2
    UART_Init_Config(SDK_USING_USART2_DEVICE,
                      RCC_APB1Periph_USART2,
                      SDK_USING_USART2_TX,
                      SDK_USING_USART2_RX,
                      SDK_USING_USART2_BAUDRATE,
                      GPIO_Remap_USART2);
    USART_EnableRxIrq();
    USART_SetAddress(SDK_USING_USART2_DEVICE, 0x1);
#endif

#ifdef SDK_USING_UART4
    UART_Init_Config(SDK_USING_UART4_DEVICE,
                      RCC_APB1Periph_UART4,
                      SDK_USING_UART4_TX,
                      SDK_USING_UART4_RX,
                      SDK_USING_UART4_BAUDRATE,
                      GPIO_PartialRemap_USART4);
#endif

#ifdef SDK_USING_UART6
    UART_Init_Config(SDK_USING_UART6_DEVICE,
                      RCC_APB1Periph_UART6,
                      SDK_USING_UART6_TX,
                      SDK_USING_UART6_RX,
                      SDK_USING_UART6_BAUDRATE,
                      0);
#endif

#ifdef SDK_USING_UART7
    UART_Init_Config(SDK_USING_UART7_DEVICE,
                      RCC_APB1Periph_UART7,
                      SDK_USING_UART7_TX,
                      SDK_USING_UART7_RX,
                      SDK_USING_UART7_BAUDRATE,
                      GPIO_FullRemap_USART7);
#endif

#ifdef SDK_USING_UART8
    UART_Init_Config(SDK_USING_UART8_DEVICE,
                      RCC_APB1Periph_UART8,
                      SDK_USING_UART8_TX,
                      SDK_USING_UART8_RX,
                      SDK_USING_UART8_BAUDRATE,
                      GPIO_FullRemap_USART8);
#endif
}

