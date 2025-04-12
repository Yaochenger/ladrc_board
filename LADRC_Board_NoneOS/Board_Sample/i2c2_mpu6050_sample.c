/*
 * i2c2_mpu6050_sample.c
 *
 *  Created on: 2024年6月19日
 *      Author: MCU
 */

#include "shell.h"
#include "mpu6050_soft.h"
#include "mpu6050_dmp.h"
#include "usr_printf.h"

float MPU6050_Temp;
IMU_data USER_IMU_data;
int i2c_mpu6050_soft_func(int cnt)
{
    MPU_Init();
    MPU6050_Filter_Init(50);
    while (1)
    {
        for (int i=0; i<cnt; i++)
        {
            MPU6050_Temp = MPU_Get_Temperature(); //得到温度值

            USER_GET_MPU6050_DATA(&USER_IMU_data);
#if 0
            printf("Pitch %.1f, " , USER_IMU_data.Pitch);
            printf("Roll  %.1f, " , USER_IMU_data.Roll);
            printf("Yaw   %.1f, " , USER_IMU_data.Yaw);
            printf("Temperature:%.1f \r\n",MPU6050_Temp);
#endif
            ladrc_printf(USART2, "%d,%d,%d\r\n",(int)USER_IMU_data.Pitch, (int)USER_IMU_data.Roll, (int)USER_IMU_data.Yaw);
            Delay_Ms(200);
        }
        return 0;
    }
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), i2c_mpu6050_soft_func, i2c_mpu6050_soft_func, test i2c2 and board mpu6050 by soft);


int i2c_mpu6050_dmp_func(int cnt) {
    short aacx, aacy, aacz;       //加速度传感器原始数据
    short gyrox, gyroy, gyroz;    //陀螺仪原始数据
    short temp;                   //温度
    float anglex = 0;
    float angley = 0;
    float anglez = 0;

    MPU6050_Init();
    MPU6050_Filter_Init(50);
    while (1)
    {
        for (int i=0; i<cnt; i++)
        {
            temp=MPU_Get_Temperature();//得到温度值
            MPU_Get_Accelerometer(&aacx,&aacy,&aacz);//得到加速度传感器数据
            MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);//得到陀螺仪数据
            printf("Temperature:%d\r\n",temp);

            printf("%f, " , First_Order_Filter_Calc(aacy, aacz, gyrox, &anglex));
            printf("%f, " , First_Order_Filter_Calc(aacx, aacz, gyroy, &angley));
            printf("%f\r\n",First_Order_Filter_Calc(aacx, aacy, gyroz, &anglez));
            Delay_Ms(50);
        }
        return 0;
    }
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), i2c_mpu6050_dmp_func, i2c_mpu6050_dmp_func, test i2c2 and board mpu6050 by dmp);
