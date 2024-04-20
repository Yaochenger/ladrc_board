/*
 * mpu6050_soft.h
 *
 *  Created on: 2024年4月18日
 *      Author: MCU
 */

#ifndef USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_SOFT_MPU6050_SOFT_H_
#define USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_SOFT_MPU6050_SOFT_H_

#include "i2c2.h"
#include "mpu6050_filter.h"

#define MPU_AD0_H               GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define MPU_AD0_L               GPIO_ResetBits(GPIOA,GPIO_Pin_15)

#define MPU_SELF_TESTX_REG      0X0D
#define MPU_SELF_TESTY_REG      0X0E
#define MPU_SELF_TESTZ_REG      0X0F
#define MPU_SELF_TESTA_REG      0X10
#define MPU_SAMPLE_RATE_REG     0X19    //潩潩?�?�?潩
#define MPU_CFG_REG             0X1A    //潩濣?潩�
#define MPU_GYRO_CFG_REG        0X1B    //潩潩潩潩濣?潩�
#define MPU_ACCEL_CFG_REG       0X1C    //潩�??潩潩�?潩�
#define MPU_MOTION_DET_REG      0X1F    //�?潩�??潩濣?潩�
#define MPU_FIFO_EN_REG         0X23    //FIFO?�??潩�
#define MPU_I2CMST_CTRL_REG     0X24    //IIC潩潩潩�??潩�
#define MPU_I2CSLV0_ADDR_REG    0X25    //IIC�?�0潩潩潩?�?潩�
#define MPU_I2CSLV0_REG         0X26    //IIC�?�0潩�?�?�?潩�
#define MPU_I2CSLV0_CTRL_REG    0X27    //IIC�?�0潩�??潩�
#define MPU_I2CSLV1_ADDR_REG    0X28    //IIC�?�1潩潩潩?�?潩�
#define MPU_I2CSLV1_REG         0X29    //IIC�?�1潩�?�?�?潩�
#define MPU_I2CSLV1_CTRL_REG    0X2A    //IIC�?�1潩�??潩�
#define MPU_I2CSLV2_ADDR_REG    0X2B    //IIC�?�2潩潩潩?�?潩�
#define MPU_I2CSLV2_REG         0X2C    //IIC�?�2潩�?�?�?潩�
#define MPU_I2CSLV2_CTRL_REG    0X2D    //IIC�?�2潩�??潩�
#define MPU_I2CSLV3_ADDR_REG    0X2E    //IIC�?�3潩潩潩?�?潩�
#define MPU_I2CSLV3_REG         0X2F    //IIC�?�3潩�?�?�?潩�
#define MPU_I2CSLV3_CTRL_REG    0X30    //IIC�?�3潩�??潩�
#define MPU_I2CSLV4_ADDR_REG    0X31    //IIC�?�4潩潩潩?�?潩�
#define MPU_I2CSLV4_REG         0X32    //IIC�?�4潩�?�?�?潩�
#define MPU_I2CSLV4_DO_REG      0X33    //IIC�?�4?潩�??潩�
#define MPU_I2CSLV4_CTRL_REG    0X34    //IIC�?�4潩�??潩�
#define MPU_I2CSLV4_DI_REG      0X35    //IIC�?�4潩潩�??潩�

#define MPU_I2CMST_STA_REG      0X36    //IIC潩潩??�?潩�
#define MPU_INTBP_CFG_REG       0X37    //�?�/潩窛潩�?潩�
#define MPU_INT_EN_REG          0X38    //�?�?�??潩�
#define MPU_INT_STA_REG         0X3A    //�?�??�?潩�

#define MPU_ACCEL_XOUTH_REG     0X3B    //潩�?�?,X潩�8?�?潩�
#define MPU_ACCEL_XOUTL_REG     0X3C    //潩�?�?,X潩�8?�?潩�
#define MPU_ACCEL_YOUTH_REG     0X3D    //潩�?�?,Y潩�8?�?潩�
#define MPU_ACCEL_YOUTL_REG     0X3E    //潩�?�?,Y潩�8?�?潩�
#define MPU_ACCEL_ZOUTH_REG     0X3F    //潩�?�?,Z潩�8?�?潩�
#define MPU_ACCEL_ZOUTL_REG     0X40    //潩�?�?,Z潩�8?�?潩�

#define MPU_TEMP_OUTH_REG       0X41    //澏�?�?�?�?潩�
#define MPU_TEMP_OUTL_REG       0X42    //澏�?潩8?�?潩�

#define MPU_GYRO_XOUTH_REG      0X43    //潩潩潩?,X潩�8?�?潩�
#define MPU_GYRO_XOUTL_REG      0X44    //潩潩潩?,X潩�8?�?潩�
#define MPU_GYRO_YOUTH_REG      0X45    //潩潩潩?,Y潩�8?�?潩�
#define MPU_GYRO_YOUTL_REG      0X46    //潩潩潩?,Y潩�8?�?潩�
#define MPU_GYRO_ZOUTH_REG      0X47    //潩潩潩?,Z潩�8?�?潩�
#define MPU_GYRO_ZOUTL_REG      0X48    //潩潩潩?,Z潩�8?�?潩�

#define MPU_I2CSLV0_DO_REG      0X63    //IIC�?�0潩�??潩�
#define MPU_I2CSLV1_DO_REG      0X64    //IIC�?�1潩�??潩�
#define MPU_I2CSLV2_DO_REG      0X65    //IIC�?�2潩�??潩�
#define MPU_I2CSLV3_DO_REG      0X66    //IIC�?�3潩�??潩�

#define MPU_I2CMST_DELAY_REG    0X67    //IIC潩潩潩?潩潩�?潩�
#define MPU_SIGPATH_RST_REG     0X68    //�?�?潩潩?�?潩�
#define MPU_MDETECT_CTRL_REG    0X69    //�?潩潩潩??潩�
#define MPU_USER_CTRL_REG       0X6A    //濢潩潩??潩�
#define MPU_PWR_MGMT1_REG       0X6B    //潩?潩潩�?潩�1
#define MPU_PWR_MGMT2_REG       0X6C    //潩?潩潩�?潩�2
#define MPU_FIFO_CNTH_REG       0X72    //FIFO潩潩�?潩潩?�?
#define MPU_FIFO_CNTL_REG       0X73    //FIFO潩潩�?潩潩?�?
#define MPU_FIFO_RW_REG         0X74    //FIFO潩?�?潩�
#define MPU_DEVICE_ID_REG       0X75    //潩潩ID�?潩�

#define MPU_ADDR                (0x68<<1)

typedef struct MPU6050_DATA {
    short gx;
    short gy;
    short gz;
    short ax;
    short ay;
    short az;
} mpu6050_data;

typedef struct IMU_DATA {
    float Roll;
    float Pitch;
    float Yaw;
} IMU_data;

typedef IMU_data* IMU_data_t;

typedef mpu6050_data * mpu6050_data_t;

u8 MPU_Init(void);                              //潩?潩MPU6050
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf);//IIC潩潩?
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf); //IIC潩潩潩
u8 MPU_Write_Byte(u8 reg,u8 data);              //IIC??潩�?�
u8 MPU_Read_Byte(u8 reg);                       //IIC潩?潩�?�

u8 MPU_Set_Gyro_Fsr(u8 fsr);
u8 MPU_Set_Accel_Fsr(u8 fsr);
u8 MPU_Set_LPF(u16 lpf);
u8 MPU_Set_Rate(u16 rate);
u8 MPU_Set_Fifo(u8 sens);

float MPU_Get_Temperature(void);
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

void USER_GET_MPU6050_DATA(IMU_data_t USER_IMU_data);
#endif /* USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_SOFT_MPU6050_SOFT_H_ */
