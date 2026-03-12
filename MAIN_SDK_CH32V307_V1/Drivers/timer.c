#include "timer.h"

static void TIM_BaseInitWithIrq(TIM_TypeDef *tim,
                                uint16_t arr,
                                uint16_t psc,
                                uint32_t rcc_tim,
                                uint8_t irq_channel)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB1PeriphClockCmd(rcc_tim, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(tim, &TIM_TimeBaseStructure);

    TIM_ITConfig(tim, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = irq_channel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(tim, ENABLE);
}

void TIM_GPIO_Init(void)
{
#ifdef SDK_USING_TIM2
    TIM_BaseInitWithIrq(SDK_USING_TIM2_DEVICE,
                        SDK_USING_TIM2_ARR,
                        SDK_USING_TIM2_PSC,
                        RCC_APB1Periph_TIM2,
                        TIM2_IRQn);
#endif

#ifdef SDK_USING_TIM6
    TIM_BaseInitWithIrq(SDK_USING_TIM6_DEVICE,
                        SDK_USING_TIM6_ARR,
                        SDK_USING_TIM6_PSC,
                        RCC_APB1Periph_TIM6,
                        TIM6_IRQn);
#endif

#ifdef SDK_USING_TIM7
    TIM_BaseInitWithIrq(SDK_USING_TIM7_DEVICE,
                        SDK_USING_TIM7_ARR,
                        SDK_USING_TIM7_PSC,
                        RCC_APB1Periph_TIM7,
                        TIM7_IRQn);
#endif
}
