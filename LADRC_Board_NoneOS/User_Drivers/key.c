/*
 * key.c
 *
 *  Created on: 2024��4��3��
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

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOD,ENABLE); //ʹ�ܸ��ù���ʱ�Ӻ�GPIOAʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;                  //����GPIO����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;              //����GPIO��������ģʽ
  GPIO_Init(GPIOD, &GPIO_InitStructure);                     //��ʼ��GPIOA

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0); //ָ���ж�/�¼��ߵ�����Դ��ʵ�������趨�ⲿ�ж����üĴ���AFIO_EXTICRx��ֵ���˴�ΪPA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line0;                   //EXTI�ж�/�¼���ѡ�񣬴˴�ѡ��EXTI_Line0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        //EXTIģʽѡ�񣬴˴�ѡ��Ϊ�����ж�ģʽ
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //EXTI���ش����¼����˴�ѡ��Ϊ�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                  //ʹ��EXTI��
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1); //ָ���ж�/�¼��ߵ�����Դ��ʵ�������趨�ⲿ�ж����üĴ���AFIO_EXTICRx��ֵ���˴�ΪPA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line1;                   //EXTI�ж�/�¼���ѡ�񣬴˴�ѡ��EXTI_Line0
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3); //ָ���ж�/�¼��ߵ�����Դ��ʵ�������趨�ⲿ�ж����üĴ���AFIO_EXTICRx��ֵ���˴�ΪPA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line3;                   //EXTI�ж�/�¼���ѡ�񣬴˴�ѡ��EXTI_Line0
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4); //ָ���ж�/�¼��ߵ�����Դ��ʵ�������趨�ⲿ�ж����üĴ���AFIO_EXTICRx��ֵ���˴�ΪPA0
  EXTI_InitStructure.EXTI_Line=EXTI_Line4;                   //EXTI�ж�/�¼���ѡ�񣬴˴�ѡ��EXTI_Line0
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn ;           //ʹ��EXTI0�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //������ռ���ȼ�Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //���������ȼ�Ϊ2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                            //�ж����ȼ������ʼ��

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn ;           //ʹ��EXTI0�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                            //�ж����ȼ������ʼ��

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn ;           //ʹ��EXTI0�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                            //�ж����ȼ������ʼ��

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn ;           //ʹ��EXTI0�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                            //�ж����ȼ������ʼ��
}

void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0)==SET)  //EXTI_GetITStatus������ȡ�жϱ�־λ״̬�����EXTI�߲����ж��򷵻�SET�����򷵻�RESET
   {
    Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
    {
        nButtonClick(ID_BUTTON_0);
        printf("Run at EXTI_0\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line0);  //����жϱ�־λ
   }
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1)==SET)  //EXTI_GetITStatus������ȡ�жϱ�־λ״̬�����EXTI�߲����ж��򷵻�SET�����򷵻�RESET
   {
      Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1))
    {
      nButtonClick(ID_BUTTON_0);
      printf("Run at EXTI_1\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line1);  //����жϱ�־λ
   }
}

void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3)==SET)  //EXTI_GetITStatus������ȡ�жϱ�־λ״̬�����EXTI�߲����ж��򷵻�SET�����򷵻�RESET
   {
    Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3))
    {
        nButtonClick(ID_BUTTON_0);
        printf("Run at EXTI_3\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line3);  //����жϱ�־λ
   }
}

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4)==SET)  //EXTI_GetITStatus������ȡ�жϱ�־λ״̬�����EXTI�߲����ж��򷵻�SET�����򷵻�RESET
   {
    Delay_Ms(40);
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4))
    {
        nButtonClick(ID_BUTTON_0);
        printf("Run at EXTI_4\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line4);  //����жϱ�־λ
   }
}

