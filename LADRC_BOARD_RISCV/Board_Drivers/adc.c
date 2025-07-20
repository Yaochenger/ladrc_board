#include "adc.h"
#ifdef LDARC_DEVICE_ADC

void ADC_GPIO_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure={0};
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE ); // ʹ��GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); // ʹ��GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );// ʹ��ADC
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);// ADC ��Ƶϵ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_DeInit(ADC1);// ��λADC
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //����ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       // �ر�ɨ��
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // �ر�ѭ��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //�ر��ⲿ����
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1; // ת��1��ͨ��
    ADC_Init(ADC1, &ADC_InitStructure);// ��ʼ��ADC

    ADC_Cmd(ADC1, ENABLE);// ʹ��ADC
    ADC_BufferCmd(ADC1, DISABLE); // �ر�BUFFER
    ADC_ResetCalibration(ADC1);   // ��λ У׼
    while(ADC_GetResetCalibrationStatus(ADC1));// ��ȡ��λУ׼״̬
    ADC_StartCalibration(ADC1);// ��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1)); // ��ȡУ׼״̬
}

u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);// ���ʹ��ADCת��

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )); //�ȴ�����ת������

    val = ADC_GetConversionValue(ADC1);// ��ȡ����

    return val;
}

u16 Get_ConversionVal(s16 val)
{
    int Calibrattion_Val = Get_CalibrationValue(ADC1);
    if((val+Calibrattion_Val)<0) return 0;
    if((Calibrattion_Val+val)>4095||val==4095) return 4095;
    return (val+Calibrattion_Val); // У׼
}
#endif /* LDARC_DEVICE_ADC */
