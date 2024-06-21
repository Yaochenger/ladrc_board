#include <math.h>
#include <mpu6050_soft.h>
#include "mpu6050_filter.h"

#define PI 3.141592653589793

float Delta_t = 1;
float GYRO_K = 1;

#define First_Order_Filter_Tau 0.1
float First_Order_k = 1;

void MPU6050_Filter_Init(float loop_ms)
{
    Delta_t = loop_ms/1000.;
    First_Order_k = First_Order_Filter_Tau / (First_Order_Filter_Tau + Delta_t);
    switch((MPU_Read_Byte(MPU_GYRO_CFG_REG) >> 3) & 3)
    {
        case 0:
            GYRO_K = 131;
            break;
        case 1:
            GYRO_K = 65.5;
            break;
        case 2:
            GYRO_K = 32.8;
            break;
        case 3:
            GYRO_K = 16.4;
            break;
    }
}

float First_Order_Filter_Calc(int16_t acc1, int16_t acc3, int16_t gyro2, float * angle2)
{
    *angle2 = First_Order_k * (*angle2 + (-gyro2 / GYRO_K) * Delta_t) + (1 - First_Order_k) * (atan2(acc1, acc3) * 180 / PI);
    return *angle2;
}

#define Second_Order_Filter_k 5

float Second_Order_Filter_Calc(int16_t acc1, int16_t acc3, int16_t gyro2, Second_Order_Filter* filter)
{
    float angle_m = atan2(acc1, acc3) * 180 / PI;
    float gyro_m = -gyro2 / GYRO_K;
    float x1, x2;
    x1 = (angle_m - filter->angle) * Second_Order_Filter_k * Second_Order_Filter_k;
    filter->y = filter->y + x1 * Delta_t;
    x2 = filter->y + 2 * Second_Order_Filter_k * (angle_m - filter->angle) + gyro_m;
    filter->angle = filter->angle + x2 * Delta_t;
    return filter->angle;
}

#define Q_angle 0.05
#define Q_gyro  0.0003
#define R_angle 0.01

float MPU_Kalman_Filter_Calc(int16_t acc1, int16_t acc3, int16_t gyro2, MPU_Kalman_Filter* filter)
{
    float newAngle = atan2(acc1, acc3) * 180 / PI;
    float newRate = -gyro2 / GYRO_K;
    float E;
    float K_0, K_1;
    float Angle_err_x;

    filter->angle += Delta_t * (newRate - filter->Q_bias_x);
    filter->P_00 +=  - Delta_t * (filter->P_10 + filter->P_01) + Q_angle * Delta_t;
    filter->P_01 +=  - Delta_t * filter->P_11;
    filter->P_10 +=  - Delta_t * filter->P_11;
    filter->P_11 +=  + Q_gyro * Delta_t;

    Angle_err_x = newAngle - filter->angle;
    E = filter->P_00 + R_angle;
    K_0 = filter->P_00 / E;
    K_1 = filter->P_10 / E;

    filter->angle +=  K_0 * Angle_err_x;
    filter->Q_bias_x  +=  K_1 * Angle_err_x;
    filter->P_00 -= K_0 * filter->P_00;
    filter->P_01 -= K_0 * filter->P_01;
    filter->P_10 -= K_1 * filter->P_00;
    filter->P_11 -= K_1 * filter->P_01;

    return filter->angle;
}

