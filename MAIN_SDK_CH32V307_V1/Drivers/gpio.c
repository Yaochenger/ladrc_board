#include "gpio.h"
#include "gpio_pin.h"

static void GPIO_ConfigInputPullUpPin(const char *pin_name)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(pin_name), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(pin_name);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(SDK_GetPort(pin_name), &GPIO_InitStructure);
}

static void GPIO_ConfigOutputPushPullPin(const char *pin_name)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(pin_name), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(pin_name);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(pin_name), &GPIO_InitStructure);
}

void KEY_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

#ifdef SDK_USING_GPIOD_KEY0
    GPIO_ConfigInputPullUpPin(SDK_USING_GPIOD_KEY0);
#endif
#ifdef SDK_USING_GPIOD_KEY1
    GPIO_ConfigInputPullUpPin(SDK_USING_GPIOD_KEY1);
#endif
#ifdef SDK_USING_GPIOD_KEY2
    GPIO_ConfigInputPullUpPin(SDK_USING_GPIOD_KEY2);
#endif
#ifdef SDK_USING_GPIOD_KEY3
    GPIO_ConfigInputPullUpPin(SDK_USING_GPIOD_KEY3);
#endif
}

void LED_GPIO_INIT(void)
{
#ifdef SDK_USING_GPIOD_LED5
    GPIO_ConfigOutputPushPullPin(SDK_USING_GPIOD_LED5);
#endif
#ifdef SDK_USING_GPIOD_LED6
    GPIO_ConfigOutputPushPullPin(SDK_USING_GPIOD_LED6);
#endif
}

