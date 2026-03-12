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
} LADRC_TypeDef;

/**
  * @brief 以下为需要整定的参数
  */
extern LADRC_TypeDef Yaw_Sysparam;
extern LADRC_TypeDef Depth_Sysparam;
extern LADRC_TypeDef Pitch_Sysparam;

#define RealTimeOut_Threshold 2000

/**
  * @brief 以下为LADRC相关函数
  */
void LADRC_INIT(LADRC_TypeDef *LADRC_TYPE1);
void LADRC_REST(LADRC_TypeDef *LADRC_TYPE1);
void LADRC_TD(LADRC_TypeDef *LADRC_TYPE1, double Expect);
void LADRC_ESO(LADRC_TypeDef *LADRC_TYPE1, double FeedBack);
void LADRC_LF(LADRC_TypeDef *LADRC_TYPE1);
void LADRC_Loop(LADRC_TypeDef *LADRC_TYPE1, double* Expect, double* RealTimeOut);

#endif
