/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

/*
 *@Note
 ���ڴ�ӡ�������̣�
 USART1_Tx(PA9)��
 ��������ʾʹ�� USART1(PA9) ����ӡ���Կ������

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
//extern short aacx,aacy,aacz;       //���ٶȴ�����ԭʼ����
//extern short gyrox,gyroy,gyroz;    //������ԭʼ����

int main(void)
{
    short aacx,aacy,aacz;       //���ٶȴ�����ԭʼ����
    short gyrox,gyroy,gyroz;    //������ԭʼ����
    short temp;                 //�¶�
    float anglex = 0;
    float angley = 0;
    float anglez = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    MPU_Init();                //��ʼ��MPU6050

    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("MPU6050 TEST\r\n");
    MPU6050_Filter_Init(50);
    while(1)
    {
        temp=MPU_Get_Temperature(); //�õ��¶�ֵ
        MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //�õ����ٶȴ���������
        MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //�õ�����������
        printf("Temperature:%d\r\n",temp);

        printf("%f, " , First_Order_Filter_Calc(aacy, aacz, gyrox, &anglex));
        printf("%f, " , First_Order_Filter_Calc(aacx, aacz, gyroy, &angley));
        printf("%f\r\n",First_Order_Filter_Calc(aacx, aacy, gyroz, &anglez));
        Delay_Ms(50);
    }
}


