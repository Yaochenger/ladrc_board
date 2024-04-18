#ifndef MPU6050_Filter_H_
#define MPU6050_Filter_H_

typedef struct
{
    float y;
    float angle;
}Second_Order_Filter;

typedef struct
{
    float P_00, P_01, P_10, P_11;
    float Q_bias_x;
    float angle;
}MPU_Kalman_Filter;

void MPU6050_Filter_Init(float loop_ms);
float First_Order_Filter_Calc(int16_t acc1, int16_t acc3, int16_t gyro2, float * angle2);
float Second_Order_Filter_Calc(int16_t acc1, int16_t acc3, int16_t gyro2, Second_Order_Filter* filter);
float MPU_Kalman_Filter_Calc(int16_t acc1, int16_t acc3, int16_t gyro2, MPU_Kalman_Filter* filter);

#endif
