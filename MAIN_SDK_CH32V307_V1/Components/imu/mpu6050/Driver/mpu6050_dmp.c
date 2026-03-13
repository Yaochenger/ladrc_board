/**
 * @file mpu6050_dmp.c
 * @brief MPU6050 low-level access and optional DMP data wrapper.
 */

#include "mpu6050_dmp.h"

#include "debug.h"
#include "i2c.h"
#include "inv_mpu.h"

MPU6050_para_t MPU6050_para = {
    0,
    0,
    0,
};

void MPU6050_I2C_Mem_Write(unsigned char dev_addr,
                           unsigned char reg_addr,
                           unsigned char len,
                           unsigned char *buf)
{
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET)
        ;
    I2C_GenerateSTART(I2C2, ENABLE);

    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2C2, dev_addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;

    I2C_SendData(I2C2, reg_addr);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    while (len--) {
        I2C_SendData(I2C2, *buf++);
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            ;
    }
    I2C_GenerateSTOP(I2C2, ENABLE);
}

static void MPU6050_WriteByte(unsigned char reg_addr, unsigned char data)
{
    MPU6050_I2C_Mem_Write(MPU6050_ADDR, reg_addr, 1, &data);
}

static void MPU6050_SetRate(unsigned char rate)
{
    MPU6050_WriteByte(MPU6050_REG_SMPLRT_DIV, 1000 / rate - 1);

    if (rate / 2 >= 188) {
        MPU6050_WriteByte(MPU6050_REG_CONFIG, 1);
    } else if (rate / 2 >= 98) {
        MPU6050_WriteByte(MPU6050_REG_CONFIG, 2);
    } else if (rate / 2 >= 42) {
        MPU6050_WriteByte(MPU6050_REG_CONFIG, 3);
    } else if (rate / 2 >= 20) {
        MPU6050_WriteByte(MPU6050_REG_CONFIG, 4);
    } else if (rate / 2 >= 10) {
        MPU6050_WriteByte(MPU6050_REG_CONFIG, 5);
    } else {
        MPU6050_WriteByte(MPU6050_REG_CONFIG, 6);
    }
}

unsigned char MPU6050_Init(void)
{
    u8 res = 0;

    I2C_GPIO_Init(400000, 0x00);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x80);
    Delay_Ms(100);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x00);
    MPU6050_SetRate(50);

    MPU6050_WriteByte(MPU6050_REG_ACCEL_CONFIG, 0x00 << 3);
    MPU6050_WriteByte(MPU6050_REG_GYRO_CONFIG, 0x03 << 3);

    MPU6050_WriteByte(MPU6050_REG_INT_EN, 0x00);
    MPU6050_WriteByte(MPU6050_REG_USER_CTRL, 0x00);
    MPU6050_WriteByte(MPU6050_REG_FIFO_EN, 0x00);
    MPU6050_WriteByte(MPU6050_REG_INTBP_CFG, 0x80);
    MPU6050_WriteByte(MPU6050_REG_PWR_MGMT1, 0x01);

#ifdef DMP
    res = mpu_dmp_init();
    printf("mpu_dmp_init err code:%d\r\n", res);
#endif

    return res;
}

void MPU6050_I2C_Mem_Read(unsigned char dev_addr,
                          unsigned char reg_addr,
                          unsigned char len,
                          unsigned char *buf)
{
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET)
        ;
    I2C_GenerateSTART(I2C2, ENABLE);

    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2C2, dev_addr, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;

    I2C_SendData(I2C2, reg_addr);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_GenerateSTART(I2C2, ENABLE);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2C2, dev_addr, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;

    while (len--) {
        if (len == 0) {
            I2C_AcknowledgeConfig(I2C2, DISABLE);
        }
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
            ;
        *buf++ = I2C_ReceiveData(I2C2);
    }

    I2C_GenerateSTOP(I2C2, ENABLE);
    I2C_AcknowledgeConfig(I2C2, ENABLE);
}

unsigned int MPU6050_Get_Data(unsigned char reg_addr)
{
    unsigned char data_h;
    unsigned char data_l;

    MPU6050_I2C_Mem_Read(MPU6050_ADDR, reg_addr, 1, &data_h);
    MPU6050_I2C_Mem_Read(MPU6050_ADDR, reg_addr + 1, 1, &data_l);
    return (data_h << 8 | data_l);
}

float MPU6050_Get_Temp(void)
{
    return (36.53f + (short)MPU6050_Get_Data(MPU6050_REG_TEMP_OUT_H) / 340.0f);
}

#ifdef DMP
unsigned char MPU6050_MPU_DMP_GetData(void)
{
    float pitch;
    float roll;
    float yaw;
    u8 res;

    res = mpu_dmp_get_data(&pitch, &roll, &yaw);
    MPU6050_para.yaw = yaw;
    MPU6050_para.pitch = pitch;
    MPU6050_para.roll = roll;

    printf("yaw:%.1f\r\npitch:%.1f\r\nroll:%.1f\r\n", yaw, pitch, roll);
    printf("mpu_dmp_get_data err code:%d\r\n", res);

    return res;
}
#endif
