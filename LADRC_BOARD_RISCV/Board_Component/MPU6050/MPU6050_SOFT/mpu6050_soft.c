/*
 * mpu6050_soft.c
 *
 *  Created on: 2024年4月18日
 *      Author: MCU
 */


#include "mpu6050_soft.h"
#include "debug.h"
#include "MahonyAHRS.h"
#include <math.h>

/**
 * @brief  初始化MPU6050传感器
 *
 * 本函数用于初始化MPU6050传感器，包括设置I2C总线、复位和唤醒传感器、
 * 设置陀螺仪和加速度传感器的量程、采样率以及其他必要的配置。
 *
 * @return u8 返回值:
 *         - 0: 成功
 *         - 其他: 错误代码
 */
u8 MPU_Init(void)
{
    u8 res;

    I2C2_GPIO_Init(400000, 0x00);           // 初始化I2C总线，速率400kHz
    MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x80); // 复位MPU6050
    Delay_Ms(100);                           // 延时100毫秒
    MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x00); // 唤醒MPU6050
    MPU_Set_Gyro_Fsr(3);                     // 设置陀螺仪传感器量程为±2000dps
    MPU_Set_Accel_Fsr(0);                    // 设置加速度传感器量程为±2g
    MPU_Set_Rate(50);                        // 设置采样率为50Hz
    MPU_Write_Byte(MPU_INT_EN_REG, 0x00);    // 关闭所有中断
    MPU_Write_Byte(MPU_USER_CTRL_REG, 0x00); // 关闭I2C主模式
    MPU_Write_Byte(MPU_FIFO_EN_REG, 0x00);   // 关闭FIFO
    MPU_Write_Byte(MPU_INTBP_CFG_REG, 0x80); // 设置INT引脚低电平有效
    res = MPU_Read_Byte(MPU_DEVICE_ID_REG);  // 读取器件ID
    if(res == MPU_ADDR) // 检查器件ID是否正确
    {
        MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x01); // 设置时钟源为PLL X轴参考
        MPU_Write_Byte(MPU_PWR_MGMT2_REG, 0x00); // 使能加速度和陀螺仪
        MPU_Set_Rate(50);                        // 再次设置采样率为50Hz
    }
    else
    {
        return 1; // 返回错误代码1，表示器件ID不正确
    }
    return 0; // 返回0，表示初始化成功
}
//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
    return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围
}

//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
    return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围
}

//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败
u8 MPU_Set_LPF(u16 lpf)
{
    u8 data=0;
    if(lpf>=188)data=1;
    else if(lpf>=98)data=2;
    else if(lpf>=42)data=3;
    else if(lpf>=20)data=4;
    else if(lpf>=10)data=5;
    else data=6;
    return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器
}

//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败
u8 MPU_Set_Rate(u16 rate)
{
    u8 data;
    if(rate>1000)rate=1000;
    if(rate<4)rate=4;
    data=1000/rate-1;
    data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);  //设置数字低通滤波器
    return MPU_Set_LPF(rate/2); //自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
float MPU_Get_Temperature(void)
{
    u8 buf[2];
    short raw;
    float temp;
    MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf);
    raw=((u16)buf[0]<<8)|buf[1];
    temp=36.53+((double)raw)/340;
    return temp;
}

//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;
    res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
    if(res==0)
    {
        *gx=((u16)buf[0]<<8)|buf[1];
        *gy=((u16)buf[2]<<8)|buf[3];
        *gz=((u16)buf[4]<<8)|buf[5];
    }
    return res;;
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;
    res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
    if(res==0)
    {
        *ax=((u16)buf[0]<<8)|buf[1];
        *ay=((u16)buf[2]<<8)|buf[3];
        *az=((u16)buf[4]<<8)|buf[5];
    }
    return res;;
}

static void MPU_I2C_Mem_Write(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf)
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

static void MPU_I2C_Mem_Read(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf)
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

//IIC连续写
//addr:器件地址
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    MPU_I2C_Mem_Write(MPU_ADDR, reg, len, buf);
    return 0;
}

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    MPU_I2C_Mem_Read(MPU_ADDR, reg, len, buf);
    return 0;
}

//IIC写一个字节
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data)
{
    MPU_I2C_Mem_Write(MPU_ADDR, reg, 1, &data);
}

//IIC读一个字节
//reg:寄存器地址
//返回值:读到的数据
u8 MPU_Read_Byte(u8 reg)
{
    u8 res;
    MPU_I2C_Mem_Read(MPU_ADDR, reg, 1, &res);
    return res;
}

#define USER_PI 3.14159
float Yaw,Pitch,Roll;

void USER_GET_MPU6050_DATA(IMU_data_t USER_IMU_data)
{
    static float q[4];

    short ax, ay, az;
    short gx, gy, gz;

    float f_ax, f_ay, f_az;
    float f_gx, f_gy, f_gz;

    MPU_Get_Accelerometer(&ax,&ay,&az);
    MPU_Get_Gyroscope(&gx, &gy,&gz);

    f_ax = ax * 0.001064;
    f_ay = ay * 0.001064;
    f_az = az * 0.001064;

    f_gx = gx / 16384;
    f_gy = gy / 16384;
    f_gz = gz / 16384;

    MahonyAHRSupdateIMU(f_gx, f_gy, f_gz, f_ax, f_ay, f_az);

    //save Quaternion
    q[0] = q0;
    q[1] = q1;
    q[2] = q2;
    q[3] = q3;

    //四元数反解欧拉角
    USER_IMU_data->Roll = (atan2(2.0f*(q[0]*q[1] + q[2]*q[3]),1 - 2.0f*(q[1]*q[1] + q[2]*q[2])))* 180/USER_PI;
    USER_IMU_data->Pitch = -asin(2.0f*(q[0]*q[2] - q[1]*q[3]))* 180/USER_PI;
    USER_IMU_data->Yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3 * q3 + 1)* 180/USER_PI; // yaw
}
