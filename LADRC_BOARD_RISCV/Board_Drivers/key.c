#include "key.h"
#ifdef LDARC_DEVICE_KEY

void EXTI0_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD,ENABLE); //使能复用功能时钟和GPIOA时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;                  //配置GPIO引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;              //配置GPIO上拉输入模式
  GPIO_Init(GPIOD, &GPIO_InitStructure);                     //初始化GPIOA
}
#endif /* LDARC_DEVICE_KEY */
