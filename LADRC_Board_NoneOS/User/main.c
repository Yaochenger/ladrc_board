/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

/*
 *@Note
 串口打印调试例程：
 USART1_Tx(PA9)。
 本例程演示使用 USART1(PA9) 作打印调试口输出。

*/

#include "debug.h"
#include "iic.h"
#include "user_peripheral_driver.h"
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
typedef struct attitude
{
    float roll;
    float pitch;
    float yaw;
} mpu6050_attitude;

mpu6050_attitude mpu6050 = {0};
//extern short aacx,aacy,aacz;       //加速度传感器原始数据
//extern short gyrox,gyroy,gyroz;    //陀螺仪原始数据

int main(void)
{
    short aacx,aacy,aacz;       //加速度传感器原始数据
    short gyrox,gyroy,gyroz;    //陀螺仪原始数据
    short temp;                 //温度
    float anglex = 0;
    float angley = 0;
    float anglez = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    MPU_Init();                //初始化MPU6050

    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("MPU6050 TEST\r\n");
    MPU6050_Filter_Init(50);
    while(1)
    {
        temp=MPU_Get_Temperature(); //得到温度值
        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //得到加速度传感器数据
        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //得到陀螺仪数据
        printf("Temperature:%d\r\n",temp);

        printf("%f, " , First_Order_Filter_Calc(aacy, aacz, gyrox, &anglex));
        printf("%f, " , First_Order_Filter_Calc(aacx, aacz, gyroy, &angley));
        printf("%f\r\n",First_Order_Filter_Calc(aacx, aacy, gyroz, &anglez));
        Delay_Ms(50);
    }
}


