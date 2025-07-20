#include "adc.h"
#ifdef LDARC_DEVICE_ADC

void ADC_GPIO_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure={0};
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE ); // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );// 使能ADC
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);// ADC 分频系数

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_DeInit(ADC1);// 复位ADC
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       // 关闭扫描
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 关闭循环模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //关闭外部触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1; // 转化1个通道
    ADC_Init(ADC1, &ADC_InitStructure);// 初始化ADC

    ADC_Cmd(ADC1, ENABLE);// 使能ADC
    ADC_BufferCmd(ADC1, DISABLE); // 关闭BUFFER
    ADC_ResetCalibration(ADC1);   // 复位 校准
    while(ADC_GetResetCalibrationStatus(ADC1));// 获取复位校准状态
    ADC_StartCalibration(ADC1);// 开始校准
    while(ADC_GetCalibrationStatus(ADC1)); // 获取校准状态
}

u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);// 软件使能ADC转化

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )); //等待规则转换结束

    val = ADC_GetConversionValue(ADC1);// 获取数据

    return val;
}

u16 Get_ConversionVal(s16 val)
{
    int Calibrattion_Val = Get_CalibrationValue(ADC1);
    if((val+Calibrattion_Val)<0) return 0;
    if((Calibrattion_Val+val)>4095||val==4095) return 4095;
    return (val+Calibrattion_Val); // 校准
}
#endif /* LDARC_DEVICE_ADC */
