#ifndef _LADRC_H
#define _LADRC_H

/**
  * @brief LADRC系统参数
  */
typedef struct LADRC
{
    float v1, v2;         // 最速输出值
    float r;              // 速度因子
    float h;              // 积分步长
    float z1, z2, z3;     // 观测器输出
    float w0, wc, b0, u;  // 观测器带宽 控制器带宽 系统参数 控制器输出
} LADRC_NUM;

/**
  * @brief 自动整定参数
  */
typedef struct Auto_Tuning
{
    float Pu; // 继电实验输出周期
    float a;  // 继电实验输出幅值
    float h;  // 指令输出幅值
    float Wu; // 系统临界频率
    float Kp; // 系统临界幅值
} AuTu;

/**
  * @brief 以下为需要整定的参数
  */
extern LADRC_NUM Yaw_Sysparam;
extern LADRC_NUM Depth_Sysparam;
extern LADRC_NUM Pitch_Sysparam;

#define RealTimeOut_Threshold 2000

/**
  * @brief 以下为LADRC相关函数
  */
void LADRC_Init(LADRC_NUM *LADRC_TYPE1);
void LADRC_REST(LADRC_NUM *LADRC_TYPE1);
void LADRC_TD(LADRC_NUM *LADRC_TYPE1, float Expect);
void LADRC_ESO(LADRC_NUM *LADRC_TYPE1, float FeedBack);
void LADRC_LF(LADRC_NUM *LADRC_TYPE1);
void LADRC_Loop(LADRC_NUM *LADRC_TYPE1, float* Expect, float* RealTimeOut);

#endif
