/*
 * i2c2_mpu6050_sample.c
 *
 *  Created on: 2024年6月19日
 *      Author: MCU
 */

#include "shell.h"
#include "mpu6050_soft.h"

float MPU6050_Temp;
IMU_data USER_IMU_data;
int i2c_mpu6050_soft_func(int cnt)
{
    MPU_Init();
    MPU6050_Filter_Init(49);
    while (1)
    {
        for (int i=0; i<cnt; i++)
        {
            MPU6050_Temp = MPU_Get_Temperature(); //得到温度值

            USER_GET_MPU6050_DATA(&USER_IMU_data);
            printf("Pitch %.1f, " , USER_IMU_data.Pitch);
            printf("Roll  %.1f, " , USER_IMU_data.Roll);
            printf("Yaw   %.1f, " , USER_IMU_data.Yaw);
            printf("Temperature:%.1f \r\n",MPU6050_Temp);
            Delay_Ms(50);
        }
        return 0;
    }
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), i2c_mpu6050_soft_func, i2c_mpu6050_soft_func, test i2c2 and board mpu6050);


int i2c_mpu6050_dmp_func(int cnt)
{
        return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), i2c_mpu6050_dmp_func, i2c_mpu6050_dmp_func, test i2c2 and board mpu6050);
