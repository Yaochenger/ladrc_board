#ifndef __IIC_H
#define __IIC_H

#include "ch32v30x_conf.h"

#define  IIC_SDA_H  GPIO_SetBits(GPIOB,GPIO_Pin_11)    //配置SDA接口高电平
#define  IIC_SDA_L  GPIO_ResetBits(GPIOB,GPIO_Pin_11)  //配置SDA接口低电平

#define  IIC_SCL_H  GPIO_SetBits(GPIOB,GPIO_Pin_10)    //配置SCL接口高电平
#define  IIC_SCL_L  GPIO_ResetBits(GPIOB,GPIO_Pin_10)  //配置SCL接口低电平

#define  I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  //读SDA口线状态

void IIC_Init(void);         //IIC初始化函数
void IIC_Idle_State(void);   //IIC空闲状态
void IIC_Start(void);        //IIC开始信号函数
void IIC_Stop(void);         //IIC停止信号函数
void IIC_SendByte(u8 data);  //IIC发送一个字节
u8 IIC_ReadByte(unsigned char ack);          //IIC读取一个字节
u8   IIC_WaitAck(void);      //等待响应信号（ACK或者NACK）
void IIC_ACK(void);          //IIC发出ACK信号
void IIC_NACK(void);         //IIC发出NACK信号

#endif
















