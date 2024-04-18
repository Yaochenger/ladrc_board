#ifndef __IIC_H
#define __IIC_H

#include "ch32v30x_conf.h"

#define  IIC_SDA_H  GPIO_SetBits(GPIOB,GPIO_Pin_11)    //����SDA�ӿڸߵ�ƽ
#define  IIC_SDA_L  GPIO_ResetBits(GPIOB,GPIO_Pin_11)  //����SDA�ӿڵ͵�ƽ

#define  IIC_SCL_H  GPIO_SetBits(GPIOB,GPIO_Pin_10)    //����SCL�ӿڸߵ�ƽ
#define  IIC_SCL_L  GPIO_ResetBits(GPIOB,GPIO_Pin_10)  //����SCL�ӿڵ͵�ƽ

#define  I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  //��SDA����״̬

void IIC_Init(void);         //IIC��ʼ������
void IIC_Idle_State(void);   //IIC����״̬
void IIC_Start(void);        //IIC��ʼ�źź���
void IIC_Stop(void);         //IICֹͣ�źź���
void IIC_SendByte(u8 data);  //IIC����һ���ֽ�
u8 IIC_ReadByte(unsigned char ack);          //IIC��ȡһ���ֽ�
u8   IIC_WaitAck(void);      //�ȴ���Ӧ�źţ�ACK����NACK��
void IIC_ACK(void);          //IIC����ACK�ź�
void IIC_NACK(void);         //IIC����NACK�ź�

#endif
















