/**
 * @file mpu6050_dmp.h
 * @brief MPU6050 register definitions and public APIs.
 */

#ifndef USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_DMP_DRIVER_MPU6050_DMP_H_
#define USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_DMP_DRIVER_MPU6050_DMP_H_

#include "ch32v30x.h"

/* Enable DMP processing when needed. */
/* #define DMP */

/* MPU6050 7-bit I2C address shifted for CH32 HAL API. */
#define MPU6050_ADDR  (0x68 << 1)

/* Default I2C port pins used by MPU6050. */
#define I2C_PORT       GPIOB
#define I2C_SCL_PIN    GPIO_Pin_10
#define I2C_SDA_PIN    GPIO_Pin_11

/* Register map (partial). */
#define MPU6050_REG_ACCEL_OFFS      0x06
#define MPU6050_REG_PROD_ID         0x0C
#define MPU6050_REG_SELF_TESTX      0x0D
#define MPU6050_REG_SELF_TESTY      0x0E
#define MPU6050_REG_SELF_TESTZ      0x0F
#define MPU6050_REG_SELF_TESTA      0x10
#define MPU6050_REG_SMPLRT_DIV      0x19
#define MPU6050_REG_CONFIG          0x1A
#define MPU6050_REG_GYRO_CONFIG     0x1B
#define MPU6050_REG_ACCEL_CONFIG    0x1C
#define MPU6050_REG_MOTION_DET      0x1F
#define MPU6050_REG_FIFO_EN         0x23
#define MPU6050_REG_I2CMST_CTRL     0x24
#define MPU6050_REG_I2CSLV0_ADDR    0x25
#define MPU6050_REG_I2CSLV0         0x26
#define MPU6050_REG_I2CSLV0_CTRL    0x27
#define MPU6050_REG_I2CSLV1_ADDR    0x28
#define MPU6050_REG_I2CSLV1         0x29
#define MPU6050_REG_I2CSLV1_CTRL    0x2A
#define MPU6050_REG_I2CSLV2_ADDR    0x2B
#define MPU6050_REG_I2CSLV2         0x2C
#define MPU6050_REG_I2CSLV2_CTRL    0x2D
#define MPU6050_REG_I2CSLV3_ADDR    0x2E
#define MPU6050_REG_I2CSLV3         0x2F
#define MPU6050_REG_I2CSLV3_CTRL    0x30
#define MPU6050_REG_I2CSLV4_ADDR    0x31
#define MPU6050_REG_I2CSLV4_        0x32
#define MPU6050_REG_I2CSLV4_DO      0x33
#define MPU6050_REG_I2CSLV4_CTRL    0x34
#define MPU6050_REG_I2CSLV4_DI      0x35

#define MPU6050_REG_I2CMST_STA      0x36
#define MPU6050_REG_INTBP_CFG       0x37
#define MPU6050_REG_INT_EN          0x38
#define MPU6050_REG_INT_STA         0x3A

#define MPU6050_REG_ACCEL_XOUT_H    0x3B
#define MPU6050_REG_ACCEL_XOUT_L    0x3C
#define MPU6050_REG_ACCEL_YOUT_H    0x3D
#define MPU6050_REG_ACCEL_YOUT_L    0x3E
#define MPU6050_REG_ACCEL_ZOUT_H    0x3F
#define MPU6050_REG_ACCEL_ZOUT_L    0x40

#define MPU6050_REG_TEMP_OUT_H      0x41
#define MPU6050_REG_TEMP_OUT_L      0x42

#define MPU6050_REG_GYRO_XOUT_H     0x43
#define MPU6050_REG_GYRO_XOUT_L     0x44
#define MPU6050_REG_GYRO_YOUT_H     0x45
#define MPU6050_REG_GYRO_YOUT_L     0x46
#define MPU6050_REG_GYRO_ZOUT_H     0x47
#define MPU6050_REG_GYRO_ZOUT_L     0x48

#define MPU6050_REG_I2CSLV0_DO      0x63
#define MPU6050_REG_I2CSLV1_DO      0x64
#define MPU6050_REG_I2CSLV2_DO      0x65
#define MPU6050_REG_I2CSLV3_DO      0x66

#define MPU6050_REG_I2CMST_DELAY    0x67
#define MPU6050_REG_SIGPATH_RST     0x68
#define MPU6050_REG_MDETECT_CTRL    0x69
#define MPU6050_REG_USER_CTRL       0x6A
#define MPU6050_REG_PWR_MGMT1       0x6B
#define MPU6050_REG_PWR_MGMT2       0x6C
#define MPU6050_REG_FIFO_CNTH       0x72
#define MPU6050_REG_FIFO_CNTL       0x73
#define MPU6050_REG_FIFO_RW         0x74
#define MPU6050_REG_DEVICE_ID       0x75

unsigned char MPU6050_Init(void);
unsigned int MPU6050_Get_Data(unsigned char reg_addr);
float MPU6050_Get_Temp(void);

void MPU6050_I2C_Mem_Write(unsigned char dev_addr,
                           unsigned char reg_addr,
                           unsigned char len,
                           unsigned char *buf);
void MPU6050_I2C_Mem_Read(unsigned char dev_addr,
                          unsigned char reg_addr,
                          unsigned char len,
                          unsigned char *buf);
unsigned char MPU6050_MPU_DMP_GetData(void);

typedef struct {
    float yaw;
    float pitch;
    float roll;
} MPU6050_para_t;

extern MPU6050_para_t MPU6050_para;

#endif /* USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_DMP_DRIVER_MPU6050_DMP_H_ */
