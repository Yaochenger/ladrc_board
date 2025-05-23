#include "ladrc.h"
#include "ladrc_params.h"

// https://blog.csdn.net/weixin_41276397/article/details/127353049
// https://www.zhihu.com/topic/21674178/hot?utm_id=0
// https://zhuanlan.zhihu.com/p/671470218

/**
  * @brief 定义四个LADRC系统参数结构体变量
  */

LADRC_NUM M1_Sysparam;
LADRC_NUM M2_Sysparam;
LADRC_NUM M3_Sysparam;
LADRC_NUM M4_Sysparam;

/**
  * @brief LADRC参数矩阵
  */
const double LADRC_Unit[5][5] =
{
    {0.05, 20, 100, 400, 0.5},
    {0.05, 20, 33, 133, 8},
    {0.05, 100, 20, 80, 0.5},
    {0.05, 100, 14, 57, 0.5},
    {0.05, 100, 50, 10, 1}
};

/**
  * @brief 初始化LADRC参数
  */
void LADRC_Init(LADRC_NUM *LADRC_Para)
{
    LADRC_Para->h = LADRC_Unit[1][0];  // 采样时间
    LADRC_Para->r = LADRC_Unit[1][1];  // 跟踪微分器参数
    LADRC_Para->wc = LADRC_Unit[1][2]; // 扰动观测器带宽
    LADRC_Para->w0 = LADRC_Unit[1][3]; // 扰动观测器带宽
    LADRC_Para->b0 = LADRC_Unit[1][4]; // 系统增益
}

/**
  * @brief 重置LADRC参数
  */
void LADRC_REST(LADRC_NUM *LADRC_Para)
{
    LADRC_Para->r = 0;
    LADRC_Para->v1 = 0;
    LADRC_Para->v2 =0;
    LADRC_Para->w0 = 0;
    LADRC_Para->b0 = 0;
    LADRC_Para->u = 0;

    LADRC_Para->z1 = 0; // 状态变量1
    LADRC_Para->z2 = 0; // 状态变量2
    LADRC_Para->z3 = 0; // 状态变量3
}

/**
  * @brief 跟踪微分器
  * @param[in] LADRC_Para LADRC参数
  * @param[in] Expect 期望值
  */
void LADRC_TD(LADRC_NUM *LADRC_Para, double Expect)
{
    double fh = -LADRC_Para->r * LADRC_Para->r * (LADRC_Para->v1 - Expect) - 2 * LADRC_Para->r * LADRC_Para->v2;
    LADRC_Para->v1 += LADRC_Para->v2 * LADRC_Para->h;
    LADRC_Para->v2 += fh * LADRC_Para->h;
}

/**
  * @brief 扰动观测器
  * @param[in] LADRC_Para LADRC参数
  * @param[in] FeedBack 反馈值
  */
void LADRC_ESO(LADRC_NUM *LADRC_Para, double FeedBack)
{
    double Beita_01 = 3 * LADRC_Para->w0;
    double Beita_02 = 3 * LADRC_Para->w0 * LADRC_Para->w0;
    double Beita_03 = LADRC_Para->w0 * LADRC_Para->w0 * LADRC_Para->w0;

    double e = LADRC_Para->z1 - FeedBack;
    LADRC_Para->z1 += (LADRC_Para->z2 - Beita_01 * e) * LADRC_Para->h;
    LADRC_Para->z2 += (LADRC_Para->z3 - Beita_02 * e + LADRC_Para->b0 * LADRC_Para->u) * LADRC_Para->h;
    LADRC_Para->z3 += -Beita_03 * e * LADRC_Para->h;
}

/**
  * @brief 线性反馈控制律
  */
void LADRC_LF(LADRC_NUM *LADRC_Para)
{
    LADRC_Para->wc = LADRC_Para->w0 / 4;
    double Kp = LADRC_Para->wc * LADRC_Para->wc;
    double Kd = 2 * LADRC_Para->wc;
    /**
      * @brief 线性反馈控制律，比例系数Kp，微分系数Kd
      * @note  Kd=3*LADRC_Para->wc;
      * @note  Kd=2*LADRC_Para->wc;
      */
    double e1 = LADRC_Para->v1 - LADRC_Para->z1;
    double e2 = LADRC_Para->v2 - LADRC_Para->z2;
    double u0 = Kp * e1 + Kd * e2;
    LADRC_Para->u = (u0 - LADRC_Para->z3) / LADRC_Para->b0;

    if (LADRC_Para->u > RealTimeOut_Threshold)
        LADRC_Para->u = RealTimeOut_Threshold;
    else if (LADRC_Para->u < -RealTimeOut_Threshold)
        LADRC_Para->u = -RealTimeOut_Threshold;
}

/**
  * @brief LADRC控制循环
  * @note 该函数实现了LADRC控制的完整流程
  */
void LADRC_Loop(LADRC_NUM *LADRC_Para, double* Expect, double* RealTimeOut)
{
    double Expect_Value = *Expect;
    double Measure = *RealTimeOut;
    LADRC_TD(LADRC_Para, Expect_Value);
    LADRC_ESO(LADRC_Para, Measure);
    LADRC_LF(LADRC_Para);
}
