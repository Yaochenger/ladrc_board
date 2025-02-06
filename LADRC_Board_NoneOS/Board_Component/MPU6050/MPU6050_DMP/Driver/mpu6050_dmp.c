/*
 * mpu6050_dmp.c
 *
 *  Created on: 2024��4��18��
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
    //������ʼ�ź�
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C2, ENABLE);
    //���͵�ַ&д
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, DEV_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    //��������
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
    MPU6050_WriteByte(MPU6050_REG_SMPLRT_DIV, 1000/rate-1);//�������ֵ�ͨ�˲���

    if(rate/2>=188)MPU6050_WriteByte(MPU6050_REG_CONFIG, 1);
    else if(rate/2>=98)MPU6050_WriteByte(MPU6050_REG_CONFIG, 2);
    else if(rate/2>=42)MPU6050_WriteByte(MPU6050_REG_CONFIG, 3);
    else if(rate/2>=20)MPU6050_WriteByte(MPU6050_REG_CONFIG, 4);
    else if(rate/2>=10)MPU6050_WriteByte(MPU6050_REG_CONFIG, 5);
    else MPU6050_WriteByte(MPU6050_REG_CONFIG, 6);
}

unsigned char MPU6050_Init()
{
//=============================����ʼ����=================================
//����ֵ����ʼ��mpu_dmp_init()�Ĵ����룬0��ʾ��ʼ���ɹ�
//=======================================================================
    u8 res = 0;

    I2C2_GPIO_Init(400000, 0x00);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x80);//��λ
    Delay_Ms(100);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x00);//�������״̬
    MPU6050_SetRate(50);//���ò�����50Hz
    MPU6050_WriteByte(MPU6050_REG_ACCEL_CONFIG, 0x00 << 3);//0x00 = 2g;0x01 = 4g;0x02 = 8g;0x03 = 16g
    MPU6050_WriteByte(MPU6050_REG_GYRO_CONFIG, 0x03 << 3);//0x00 = ��250dps;0x01 = ��500dps;0x02 = ��1000dps;0x03 = ��2000dps
    MPU6050_WriteByte(MPU6050_REG_INT_EN, 0X00);    //�ر������ж�
    MPU6050_WriteByte(MPU6050_REG_USER_CTRL, 0X00); //I2C��ģʽ�ر�
    MPU6050_WriteByte(MPU6050_REG_FIFO_EN, 0X00);   //�ر�FIFO
    MPU6050_WriteByte(MPU6050_REG_INTBP_CFG, 0X80); //INT���ŵ͵�ƽ��Ч
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0X01);//����CLKSEL,PLL X��Ϊ�ο�

#ifdef DMP
    res = mpu_dmp_init();
    printf("mpu_dmp_init err code:%d\r\n", res);
#endif

    return res;
}

void MPU6050_I2C_Mem_Read(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf)
{
    //������ʼ�ź�
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET);
    I2C_GenerateSTART(I2C2, ENABLE);
    //���͵�ַ&д
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C2, DEV_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    //��������
    I2C_SendData(I2C2, REG_ADDR);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    //������ʼ�ź�
    I2C_GenerateSTART(I2C2, ENABLE);
    //���͵�ַ&��
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
//============================�����ߵͼĴ���ֵ��================================
//������
//REG_ADDR:�Ĵ�����λ��ַ
//����ֵ:��ȡ����16λ����
//===========================================================================
    unsigned char dataH, dataL;

    MPU6050_I2C_Mem_Read(MPU6050_ADDR, REG_ADDR, 1, &dataH);
    MPU6050_I2C_Mem_Read(MPU6050_ADDR, REG_ADDR + 1, 1, &dataL);
    return (dataH<<8|dataL);
}

float MPU6050_Get_Temp()
{
//============================����ȡ�¶ȡ�================================
//����ֵ:��ȡ�����¶�
//======================================================================
    return (36.53 + (short)MPU6050_Get_Data(MPU6050_REG_TEMP_OUT_H) / 340.0);
}

#ifdef DMP
unsigned char MPU6050_MPU_DMP_GetData(void)
{
//============================����ȡDMPֵ��================================
//����ֵ:mpu_dmp_get_data()�Ĵ����룬0��ʾ��ȡ�ɹ�
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

