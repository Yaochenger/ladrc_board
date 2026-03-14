/**
 * @file i2c2_mpu6050_testcase.c
 * @brief MPU6050 DMP test case on I2C2.
 */

#include "ch32v30x.h"
#include "sdkconfig.h"
#include "debug.h"
#include "mpu6050_dmp.h"
#include "shell.h"

/**
 * @brief Run MPU6050 test loop.
 *
 * When `DMP` is enabled, this function reads and prints yaw/pitch/roll.
 * Otherwise, it prints temperature only.
 *
 * @param cnt Number of samples.
 * @return 0 on completion.
 */
int i2c_mpu6050_dmp_func(int cnt)
{
    if (MPU6050_Init() != 0) {
        printf("MPU6050 init failed.\r\n");
        return -1;
    }

    for (int i = 0; i < cnt; i++) {
#ifdef DMP
        (void)MPU6050_MPU_DMP_GetData();
        printf("Yaw:%.1f, Pitch:%.1f, Roll:%.1f\r\n",
               MPU6050_para.yaw,
               MPU6050_para.pitch,
               MPU6050_para.roll);
#else
        printf("Temperature:%.2f\r\n", MPU6050_Get_Temp());
#endif
        Delay_Ms(50);
    }

    return 0;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),
                 i2c_mpu6050_dmp_func,
                 i2c_mpu6050_dmp_func,
                 test i2c2 and board mpu6050 by dmp);
