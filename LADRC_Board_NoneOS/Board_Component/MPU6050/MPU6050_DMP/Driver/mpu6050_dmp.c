/*
 * mpu6050_dmp.c
 *
 *  Created on: 2024年4月18日
 *      Author: MCU
 */

#include "mpu6050_dmp.h"
#include "debug.h"
#include "inv_mpu.h"
#include "i2c2.h"

MPU6050_para_t MPU6050_para =
{
    0,//yaw
    0,//pitch
    0,//row
};


void MPU6050_I2C_Mem_Write(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf)
{
    //产生起始信号
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C2, ENABLE);
    //发送地址&写
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, DEV_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    //发送数据
    I2C_SendData(I2C2, REG_ADDR);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    while(len--)
    {
        I2C_SendData(I2C2, *buf++);
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
    I2C_GenerateSTOP(I2C2, ENABLE);
}

static void MPU6050_WriteByte(unsigned char REG_ADDR,unsigned char _data)
{
    MPU6050_I2C_Mem_Write(MPU6050_ADDR, REG_ADDR, 1, &_data);
}

static void MPU6050_SetRate(unsigned char rate)
{
    MPU6050_WriteByte(MPU6050_REG_SMPLRT_DIV, 1000/rate-1);//设置数字低通滤波器

    if(rate/2>=188)MPU6050_WriteByte(MPU6050_REG_CONFIG, 1);
    else if(rate/2>=98)MPU6050_WriteByte(MPU6050_REG_CONFIG, 2);
    else if(rate/2>=42)MPU6050_WriteByte(MPU6050_REG_CONFIG, 3);
    else if(rate/2>=20)MPU6050_WriteByte(MPU6050_REG_CONFIG, 4);
    else if(rate/2>=10)MPU6050_WriteByte(MPU6050_REG_CONFIG, 5);
    else MPU6050_WriteByte(MPU6050_REG_CONFIG, 6);
}

unsigned char MPU6050_Init()
{
//=============================【初始化】=================================
//返回值：初始化mpu_dmp_init()的错误码，0表示初始化成功
//=======================================================================
    u8 res = 0;

    I2C2_GPIO_Init(400000, 0x00);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x80);//复位
    Delay_Ms(100);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x00);//解除休眠状态
    MPU6050_SetRate(50);//设置采样率50Hz
    MPU6050_WriteByte(MPU6050_REG_ACCEL_CONFIG, 0x00 << 3);//0x00 = 2g;0x01 = 4g;0x02 = 8g;0x03 = 16g
    MPU6050_WriteByte(MPU6050_REG_GYRO_CONFIG, 0x03 << 3);//0x00 = ±250dps;0x01 = ±500dps;0x02 = ±1000dps;0x03 = ±2000dps
    MPU6050_WriteByte(MPU6050_REG_INT_EN, 0X00);    //关闭所有中断
    MPU6050_WriteByte(MPU6050_REG_USER_CTRL, 0X00); //I2C主模式关闭
    MPU6050_WriteByte(MPU6050_REG_FIFO_EN, 0X00);   //关闭FIFO
    MPU6050_WriteByte(MPU6050_REG_INTBP_CFG, 0X80); //INT引脚低电平有效
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0X01);//设置CLKSEL,PLL X轴为参考

#ifdef DMP
    res = mpu_dmp_init();
    printf("mpu_dmp_init err code:%d\r\n", res);
#endif

    return res;
}

void MPU6050_I2C_Mem_Read(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf)
{
    //产生起始信号
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C2, ENABLE);
    //发送地址&写
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, DEV_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    //发送数据
    I2C_SendData(I2C2, REG_ADDR);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    //产生起始信号
    I2C_GenerateSTART(I2C2, ENABLE);
    //发送地址&读
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, DEV_ADDR, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    while(len--)
    {
        if(len == 0)I2C_AcknowledgeConfig(I2C2, DISABLE);//NACK
        while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
        *buf = I2C_ReceiveData(I2C2);
        buf++;
    }
    I2C_GenerateSTOP(I2C2, ENABLE);
    I2C_AcknowledgeConfig(I2C2, ENABLE);//ACK
}

unsigned int MPU6050_Get_Data(unsigned char REG_ADDR)
{
//============================【读高低寄存器值】================================
//参数：
//REG_ADDR:寄存器高位地址
//返回值:获取到的16位数据
//===========================================================================
    unsigned char dataH, dataL;

    MPU6050_I2C_Mem_Read(MPU6050_ADDR, REG_ADDR, 1, &dataH);
    MPU6050_I2C_Mem_Read(MPU6050_ADDR, REG_ADDR + 1, 1, &dataL);
    return (dataH<<8|dataL);
}

float MPU6050_Get_Temp()
{
//============================【获取温度】================================
//返回值:获取到的温度
//======================================================================
    return (36.53 + (short)MPU6050_Get_Data(MPU6050_REG_TEMP_OUT_H) / 340.0);
}

#ifdef DMP
unsigned char MPU6050_MPU_DMP_GetData(void)
{
//============================【获取DMP值】================================
//返回值:mpu_dmp_get_data()的错误码，0表示获取成功
//========================================================================
    float a,b,c;
    u8 res;

    res = mpu_dmp_get_data(&a,&b,&c);
    MPU6050_para.yaw = c;
    MPU6050_para.pitch = a;
    MPU6050_para.roll = b;
    printf("yaw:%.1f\r\npitch:%.1f\r\nroll:%.1f\r\n",c,a,b);
    printf("mpu_dmp_get_data err code:%d\r\n", res);

    return res;
}
#endif

