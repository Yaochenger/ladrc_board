/*
 * mpu6050_dmp.h
 *
 *  Created on: 2024��4��18��
 *      Author: MCU
 */

#ifndef USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_DMP_DRIVER_MPU6050_DMP_H_
#define USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_DMP_DRIVER_MPU6050_DMP_H_

//�Ƿ�����DMP
// #define DMP

//MPU6050��ַ
#define MPU6050_ADDR  (0x68<<1)

//MPU6050�˿�
#define I2C_PORT   GPIOB
#define I2C_SCL_PIN    GPIO_Pin_10
#define I2C_SDA_PIN    GPIO_Pin_11

#define MPU6050_REG_ACCEL_OFFS      0X06    //accel_offs�Ĵ���,�ɶ�ȡ�汾��,�Ĵ����ֲ�δ�ᵽ
#define MPU6050_REG_PROD_ID         0X0C    //prod id�Ĵ���,�ڼĴ����ֲ�δ�ᵽ
#define MPU6050_REG_SELF_TESTX      0X0D    //�Լ�Ĵ���X
#define MPU6050_REG_SELF_TESTY      0X0E    //�Լ�Ĵ���Y
#define MPU6050_REG_SELF_TESTZ      0X0F    //�Լ�Ĵ���Z
#define MPU6050_REG_SELF_TESTA      0X10    //�Լ�Ĵ���A
#define MPU6050_REG_SMPLRT_DIV      0X19    //����Ƶ�ʷ�Ƶ��
#define MPU6050_REG_CONFIG          0X1A    //���üĴ���
#define MPU6050_REG_GYRO_CONFIG     0X1B    //���������üĴ���
#define MPU6050_REG_ACCEL_CONFIG    0X1C    //���ٶȼ����üĴ���
#define MPU6050_REG_MOTION_DET      0X1F    //�˶���ֵⷧ���üĴ���
#define MPU6050_REG_FIFO_EN         0X23    //FIFOʹ�ܼĴ���
#define MPU6050_REG_I2CMST_CTRL     0X24    //IIC�������ƼĴ���
#define MPU6050_REG_I2CSLV0_ADDR    0X25    //IIC�ӻ�0������ַ�Ĵ���
#define MPU6050_REG_I2CSLV0         0X26    //IIC�ӻ�0���ݵ�ַ�Ĵ���
#define MPU6050_REG_I2CSLV0_CTRL    0X27    //IIC�ӻ�0���ƼĴ���
#define MPU6050_REG_I2CSLV1_ADDR    0X28    //IIC�ӻ�1������ַ�Ĵ���
#define MPU6050_REG_I2CSLV1         0X29    //IIC�ӻ�1���ݵ�ַ�Ĵ���
#define MPU6050_REG_I2CSLV1_CTRL    0X2A    //IIC�ӻ�1���ƼĴ���
#define MPU6050_REG_I2CSLV2_ADDR    0X2B    //IIC�ӻ�2������ַ�Ĵ���
#define MPU6050_REG_I2CSLV2         0X2C    //IIC�ӻ�2���ݵ�ַ�Ĵ���
#define MPU6050_REG_I2CSLV2_CTRL    0X2D    //IIC�ӻ�2���ƼĴ���
#define MPU6050_REG_I2CSLV3_ADDR    0X2E    //IIC�ӻ�3������ַ�Ĵ���
#define MPU6050_REG_I2CSLV3         0X2F    //IIC�ӻ�3���ݵ�ַ�Ĵ���
#define MPU6050_REG_I2CSLV3_CTRL    0X30    //IIC�ӻ�3���ƼĴ���
#define MPU6050_REG_I2CSLV4_ADDR    0X31    //IIC�ӻ�4������ַ�Ĵ���
#define MPU6050_REG_I2CSLV4_        0X32    //IIC�ӻ�4���ݵ�ַ�Ĵ���
#define MPU6050_REG_I2CSLV4_DO      0X33    //IIC�ӻ�4д���ݼĴ���
#define MPU6050_REG_I2CSLV4_CTRL    0X34    //IIC�ӻ�4���ƼĴ���
#define MPU6050_REG_I2CSLV4_DI      0X35    //IIC�ӻ�4�����ݼĴ���

#define MPU6050_REG_I2CMST_STA      0X36    //IIC����״̬�Ĵ���
#define MPU6050_REG_INTBP_CFG       0X37    //�ж�/��·���üĴ���
#define MPU6050_REG_INT_EN          0X38    //�ж�ʹ�ܼĴ���
#define MPU6050_REG_INT_STA         0X3A    //�ж�״̬�Ĵ���

//���ٶȼĴ���
#define MPU6050_REG_ACCEL_XOUT_H    0x3B
#define MPU6050_REG_ACCEL_XOUT_L    0x3C
#define MPU6050_REG_ACCEL_YOUT_H    0x3D
#define MPU6050_REG_ACCEL_YOUT_L    0x3E
#define MPU6050_REG_ACCEL_ZOUT_H    0x3F
#define MPU6050_REG_ACCEL_ZOUT_L    0x40

//�¶ȼĴ���
#define MPU6050_REG_TEMP_OUT_H      0x41
#define MPU6050_REG_TEMP_OUT_L      0x42

//���ٶȼĴ���
#define MPU6050_REG_GYRO_XOUT_H     0x43
#define MPU6050_REG_GYRO_XOUT_L     0x44
#define MPU6050_REG_GYRO_YOUT_H     0x45
#define MPU6050_REG_GYRO_YOUT_L     0x46
#define MPU6050_REG_GYRO_ZOUT_H     0x47
#define MPU6050_REG_GYRO_ZOUT_L     0x48

//�����Ĵ���
#define MPU6050_REG_I2CSLV0_DO      0X63    //IIC�ӻ�0���ݼĴ���
#define MPU6050_REG_I2CSLV1_DO      0X64    //IIC�ӻ�1���ݼĴ���
#define MPU6050_REG_I2CSLV2_DO      0X65    //IIC�ӻ�2���ݼĴ���
#define MPU6050_REG_I2CSLV3_DO      0X66    //IIC�ӻ�3���ݼĴ���

#define MPU6050_REG_I2CMST_DELAY    0X67    //IIC������ʱ����Ĵ���
#define MPU6050_REG_SIGPATH_RST     0X68    //�ź�ͨ����λ�Ĵ���
#define MPU6050_REG_MDETECT_CTRL    0X69    //�˶������ƼĴ���
#define MPU6050_REG_USER_CTRL       0X6A    //�û����ƼĴ���
#define MPU6050_REG_PWR_MGMT1       0X6B    //��Դ����Ĵ���1
#define MPU6050_REG_PWR_MGMT2       0X6C    //��Դ����Ĵ���2
#define MPU6050_REG_FIFO_CNTH       0X72    //FIFO�����Ĵ����߰�λ
#define MPU6050_REG_FIFO_CNTL       0X73    //FIFO�����Ĵ����Ͱ�λ
#define MPU6050_REG_FIFO_RW         0X74    //FIFO��д�Ĵ���
#define MPU6050_REG_DEVICE_ID       0X75    //����ID�Ĵ���

unsigned char MPU6050_Init(void);
unsigned int MPU6050_Get_Data(unsigned char REG_ADDR);
float MPU6050_Get_Temp(void);

void MPU6050_I2C_Mem_Write(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf);
void MPU6050_I2C_Mem_Read(unsigned char DEV_ADDR, unsigned char REG_ADDR, unsigned char len, unsigned char *buf);
unsigned char MPU6050_MPU_DMP_GetData(void);

typedef struct
{
    float yaw;
    float pitch;
    float roll;
}MPU6050_para_t;

extern MPU6050_para_t MPU6050_para;


#endif /* USER_PERIPHERAL_DRIVER_MPU6050_MPU6050_DMP_DRIVER_MPU6050_DMP_H_ */
