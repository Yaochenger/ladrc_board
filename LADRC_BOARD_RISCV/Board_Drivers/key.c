#include "key.h"
#ifdef LDARC_DEVICE_KEY

void EXTI0_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD,ENABLE); //ʹ�ܸ��ù���ʱ�Ӻ�GPIOAʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;                  //����GPIO����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;              //����GPIO��������ģʽ
  GPIO_Init(GPIOD, &GPIO_InitStructure);                     //��ʼ��GPIOA
}
#endif /* LDARC_DEVICE_KEY */
