#include "adc.h"
#include "gpio_pin.h"
#if defined(SDK_USING_ADC1) || defined(SDK_USING_ADC2)

/**
 * @brief Configure ADC1 and analog input pins.
 */
void ADC_GPIO_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    /* Enable GPIO clocks and configure analog input pins when macros exist. */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

#ifdef SDK_USING_ADC1_IN0
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN0), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN0);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN0), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC1_IN4
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN4), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN4);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN4), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC1_IN5
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN5), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN5);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN5), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC1_IN12
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN12), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN12);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN12), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC1_IN13
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN13), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN13);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN13), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC1_IN14
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN14), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN14);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN14), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC1_IN15
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC1_IN15), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC1_IN15);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC1_IN15), &GPIO_InitStructure);
#endif

#ifdef SDK_USING_ADC2_IN0
    RCC_APB2PeriphClockCmd(SDK_GetGPIORCC(SDK_USING_ADC2_IN0), ENABLE);
    GPIO_InitStructure.GPIO_Pin = SDK_GetPin(SDK_USING_ADC2_IN0);
    GPIO_Init(SDK_GetPort(SDK_USING_ADC2_IN0), &GPIO_InitStructure);
#endif

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);
    ADC_BufferCmd(ADC1, DISABLE);
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;
}

/**
 * @brief Trigger one conversion on selected ADC channel.
 * @param ch ADC channel index.
 * @return Raw ADC conversion result.
 */
u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
        ;
    val = ADC_GetConversionValue(ADC1);
    return val;
}

/**
 * @brief Convert raw value with calibration offset and saturation.
 * @param val Raw ADC value.
 * @return Calibrated value limited to 0..4095.
 */
u16 Get_ConversionVal(s16 val)
{
    int Calibrattion_Val = Get_CalibrationValue(ADC1);
    if ((val + Calibrattion_Val) < 0)
        return 0;
    if ((Calibrattion_Val + val) > 4095 || val == 4095)
        return 4095;
    return (val + Calibrattion_Val);
}

#endif /* SDK_USING_ADC1 || SDK_USING_ADC2 */

