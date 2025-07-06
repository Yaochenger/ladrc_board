#ifndef _LADRC_H
#define _LADRC_H

/**
  * @brief LADRC系统参数
  */
typedef struct LADRC
{
    double v1, v2;         // 最速输出值
    double r;              // 速度因子
    double h;              // 积分步长
    double z1, z2, z3;     // 观测器输出
    double w0, wc, b0, u;  // 观测器带宽 控制器带宽 系统参数 控制器输出
} LADRC_NUM;

/**
  * @brief 自动整定参数
  */
typedef struct Auto_Tuning
{
    double Pu; // 继电实验输出周期
    double a;  // 继电实验输出幅值
    double h;  // 指令输出幅值
    double Wu; // 系统临界频率
    double Kp; // 系统临界幅值
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
void LADRC_TD(LADRC_NUM *LADRC_TYPE1, double Expect);
void LADRC_ESO(LADRC_NUM *LADRC_TYPE1, double FeedBack);
void LADRC_LF(LADRC_NUM *LADRC_TYPE1);
void LADRC_Loop(LADRC_NUM *LADRC_TYPE1, double* Expect, double* RealTimeOut);

#endif
