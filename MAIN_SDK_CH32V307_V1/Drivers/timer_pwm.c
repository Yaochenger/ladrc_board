#include "timer_pwm.h"
#include "gpio_pin.h"

#ifndef SDK_USING_TIM9_ARR
#define SDK_USING_TIM9_ARR 99
#endif

#ifndef SDK_USING_TIM9_PSC
#define SDK_USING_TIM9_PSC 719
#endif

#ifndef SDK_USING_TIM9_PULSE
#define SDK_USING_TIM9_PULSE 0
#endif

#ifndef SDK_USING_TIM9_PWM_MODE
#define SDK_USING_TIM9_PWM_MODE TIM_OCMode_PWM2
#endif

static void TIMER_PWM_OutputPinInit(const char *pin_name)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(pin_name), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(pin_name);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(pin_name), &GPIO_InitStructure);
}

void TIMER_PWM_GPIO_Init(void)
{
#ifdef SDK_USING_M1_PIN1
    TIMER_PWM_OutputPinInit(SDK_USING_M1_PIN1);
#endif
#ifdef SDK_USING_M1_PIN2
    TIMER_PWM_OutputPinInit(SDK_USING_M1_PIN2);
#endif
#ifdef SDK_USING_M2_PIN1
    TIMER_PWM_OutputPinInit(SDK_USING_M2_PIN1);
#endif
#ifdef SDK_USING_M2_PIN2
    TIMER_PWM_OutputPinInit(SDK_USING_M2_PIN2);
#endif
#ifdef SDK_USING_M3_PIN1
    TIMER_PWM_OutputPinInit(SDK_USING_M3_PIN1);
#endif
#ifdef SDK_USING_M3_PIN2
    TIMER_PWM_OutputPinInit(SDK_USING_M3_PIN2);
#endif
#ifdef SDK_USING_M4_PIN1
    TIMER_PWM_OutputPinInit(SDK_USING_M4_PIN1);
#endif
#ifdef SDK_USING_M4_PIN2
    TIMER_PWM_OutputPinInit(SDK_USING_M4_PIN2);
#endif

#ifdef SDK_USING_TIM9
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_TIM9_PWM1) |
                           SDK_GetGPIORCC(SDK_USING_TIM9_PWM2) |
                           SDK_GetGPIORCC(SDK_USING_TIM9_PWM3) |
                           SDK_GetGPIORCC(SDK_USING_TIM9_PWM4), ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9 | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, ENABLE);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_TIM9_PWM1) |
                                  SDK_GetPin(SDK_USING_TIM9_PWM2) |
                                  SDK_GetPin(SDK_USING_TIM9_PWM3) |
                                  SDK_GetPin(SDK_USING_TIM9_PWM4);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDK_GetPort(SDK_USING_TIM9_PWM1), &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = SDK_USING_TIM9_ARR;
    TIM_TimeBaseInitStructure.TIM_Prescaler = SDK_USING_TIM9_PSC;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(SDK_USING_TIM9_DEVICE, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = SDK_USING_TIM9_PWM_MODE;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = SDK_USING_TIM9_PULSE;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(SDK_USING_TIM9_DEVICE, &TIM_OCInitStructure);
    TIM_OC2Init(SDK_USING_TIM9_DEVICE, &TIM_OCInitStructure);
    TIM_OC3Init(SDK_USING_TIM9_DEVICE, &TIM_OCInitStructure);
    TIM_OC4Init(SDK_USING_TIM9_DEVICE, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(SDK_USING_TIM9_DEVICE, ENABLE);
    TIM_OC1PreloadConfig(SDK_USING_TIM9_DEVICE, TIM_OCPreload_Disable);
    TIM_OC2PreloadConfig(SDK_USING_TIM9_DEVICE, TIM_OCPreload_Disable);
    TIM_OC3PreloadConfig(SDK_USING_TIM9_DEVICE, TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(SDK_USING_TIM9_DEVICE, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(SDK_USING_TIM9_DEVICE, ENABLE);
    TIM_Cmd(SDK_USING_TIM9_DEVICE, ENABLE);
#endif
}

