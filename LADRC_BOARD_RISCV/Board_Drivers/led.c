
#include "led.h"
#ifdef LDARC_DEVICE_LED

void GPIO_LED_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void LED_GPIO_Sample(void)
{
    Delay_Ms(500);
    GPIO_SetBits(GPIOD, GPIO_Pin_8);
    GPIO_SetBits(GPIOD, GPIO_Pin_10);
    Delay_Ms(500);
    GPIO_ResetBits(GPIOD, GPIO_Pin_8);
    GPIO_ResetBits(GPIOD, GPIO_Pin_10);
}

#endif // LDARC_DEVICE_LED
