#include "timer_encoder.h"
#include "gpio_pin.h"

static void TIMER_EncoderInitByConfig(TIM_TypeDef *tim_device,
                                      const char *pin_a,
                                      const char *pin_b,
                                      uint32_t tim_rcc,
                                      uint8_t tim_on_apb2)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
    TIM_ICInitTypeDef TIM_ICInitStructure = {0};

    if (tim_on_apb2) {
        RCC_APB2PeriphClockCmd(tim_rcc, ENABLE);
    } else {
        RCC_APB1PeriphClockCmd(tim_rcc, ENABLE);
    }

    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(pin_a) | SDK_GetGPIORCC(pin_b), ENABLE);

    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(pin_a) | SDK_GetPin(pin_b);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(SDK_GetPort(pin_a), &GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(tim_device, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(tim_device, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising,
                               TIM_ICPolarity_Rising);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICFilter = 10;

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(tim_device, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(tim_device, &TIM_ICInitStructure);

    TIM_SetCounter(tim_device, 0);
    TIM_Cmd(tim_device, ENABLE);
}

void TIMER_ENCODER_GPIO_Init(void)
{
#ifdef SDK_USING_TIM3
    TIMER_EncoderInitByConfig(SDK_USING_TIM3_DEVICE,
                              SDK_USING_TIM3_PIN_A,
                              SDK_USING_TIM3_PIN_B,
                              RCC_APB1Periph_TIM3,
                              0);
#endif

#ifdef SDK_USING_TIM4
    TIMER_EncoderInitByConfig(SDK_USING_TIM4_DEVICE,
                              SDK_USING_TIM4_PIN_A,
                              SDK_USING_TIM4_PIN_B,
                              RCC_APB1Periph_TIM4,
                              0);
#endif

#ifdef SDK_USING_TIM5
    TIMER_EncoderInitByConfig(SDK_USING_TIM5_DEVICE,
                              SDK_USING_TIM5_PIN_A,
                              SDK_USING_TIM5_PIN_B,
                              RCC_APB1Periph_TIM5,
                              0);
#endif

#ifdef SDK_USING_TIM8
    TIMER_EncoderInitByConfig(SDK_USING_TIM8_DEVICE,
                              SDK_USING_TIM8_PIN_A,
                              SDK_USING_TIM8_PIN_B,
                              RCC_APB2Periph_TIM8,
                              1);
#endif
}

