/*
 * key.c
 *
 *  Created on: 2024年4月3日
 *      Author: MCU
 */

#include "key.h"

void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void EXTI0_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD,ENABLE); //使能复用功能时钟和GPIOA时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;                  //配置GPIO引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;              //配置GPIO上拉输入模式
  GPIO_Init(GPIOD, &GPIO_InitStructure);                     //初始化GPIOA

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0); //指定中断/事件线的输入源，实际上是设定外部中断配置寄存器AFIO_EXTICRx的值，此处为PA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line0;                   //EXTI中断/事件线选择，此处选择EXTI_Line0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        //EXTI模式选择，此处选择为产生中断模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //EXTI边沿触发事件，此处选择为下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                  //使能EXTI线
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1); //指定中断/事件线的输入源，实际上是设定外部中断配置寄存器AFIO_EXTICRx的值，此处为PA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line1;                   //EXTI中断/事件线选择，此处选择EXTI_Line0
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3); //指定中断/事件线的输入源，实际上是设定外部中断配置寄存器AFIO_EXTICRx的值，此处为PA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line3;                   //EXTI中断/事件线选择，此处选择EXTI_Line0
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4); //指定中断/事件线的输入源，实际上是设定外部中断配置寄存器AFIO_EXTICRx的值，此处为PA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line4;                   //EXTI中断/事件线选择，此处选择EXTI_Line0
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn ;           //使能EXTI0中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //设置抢占优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //设置子优先级为2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);                            //中断优先级分组初始化

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn ;           //使能EXTI0中断通道
  NVIC_Init(&NVIC_InitStructure);                            //中断优先级分组初始化

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn ;           //使能EXTI0中断通道
  NVIC_Init(&NVIC_InitStructure);                            //中断优先级分组初始化

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn ;           //使能EXTI0中断通道
  NVIC_Init(&NVIC_InitStructure);                            //中断优先级分组初始化
}

void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0)==SET)  //EXTI_GetITStatus用来获取中断标志位状态，如果EXTI线产生中断则返回SET，否则返回RESET
   {
    Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
    {
        nButtonClick(ID_BUTTON_0);
        printf("Run at EXTI_0\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line0);  //清除中断标志位
   }
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1)==SET)  //EXTI_GetITStatus用来获取中断标志位状态，如果EXTI线产生中断则返回SET，否则返回RESET
   {
      Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1))
    {
      nButtonClick(ID_BUTTON_0);
      printf("Run at EXTI_1\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line1);  //清除中断标志位
   }
}

void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3)==SET)  //EXTI_GetITStatus用来获取中断标志位状态，如果EXTI线产生中断则返回SET，否则返回RESET
   {
    Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3))
    {
        nButtonClick(ID_BUTTON_0);
        printf("Run at EXTI_3\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line3);  //清除中断标志位
   }
}

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4)==SET)  //EXTI_GetITStatus用来获取中断标志位状态，如果EXTI线产生中断则返回SET，否则返回RESET
   {
    Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4))
    {
        nButtonClick(ID_BUTTON_0);
        printf("Run at EXTI_4\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line4);  //清除中断标志位
   }
}

