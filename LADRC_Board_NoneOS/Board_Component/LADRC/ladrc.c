#include "LADRC.h"
#include "ladrc_params.h"

/**
  * @brief ϵͳ��Ҫ�����Ĳ���
  */
LADRC_NUM M1_Sysparam;
LADRC_NUM M2_Sysparam;
LADRC_NUM M3_Sysparam;
LADRC_NUM M4_Sysparam;

/**
  * @brief LADRC��ʼ�ο�ֵ
  */
const float LADRC_Unit[5][5] =
{
    {0.005, 20, 100, 400, 0.5},
    {0.001, 20, 33, 133, 8},
    {0.005, 100, 20, 80, 0.5},
    {0.005, 100, 14, 57, 0.5},
    {0.005, 100, 50, 10, 1}
};

/**
  * @brief LADRC��ʼ��
  */
void LADRC_Init(LADRC_NUM *LADRC_TYPE1)
{
    LADRC_TYPE1->h = LADRC_Unit[1][0];  // ��ʱʱ�估ʱ�䲽��
    LADRC_TYPE1->r = LADRC_Unit[1][1];  // �����ٶȲ���
    LADRC_TYPE1->wc = LADRC_Unit[1][2]; // �۲�������
    LADRC_TYPE1->w0 = LADRC_Unit[1][3]; // ״̬�����ʴ���
    LADRC_TYPE1->b0 = LADRC_Unit[1][4]; // ϵͳ����
}

/**
  * @brief LADRCȱʡ
  */
void LADRC_REST(LADRC_NUM *LADRC_TYPE1)
{
    LADRC_TYPE1->z1 = 0; // ��ʱʱ�估ʱ�䲽��
    LADRC_TYPE1->z2 = 0; // �����ٶȲ���
    LADRC_TYPE1->z3 = 0; // �۲�������
}

/**
  * @brief LADRC����΢�ֲ���
  * @param[in] LADRC_TYPE1 ��ڲ���
  * @param[in] Expect ����ֵ
  */
void LADRC_TD(LADRC_NUM *LADRC_TYPE1, float Expect)
{
    float fh = -LADRC_TYPE1->r * LADRC_TYPE1->r * (LADRC_TYPE1->v1 - Expect) - 2 * LADRC_TYPE1->r * LADRC_TYPE1->v2;
    LADRC_TYPE1->v1 += LADRC_TYPE1->v2 * LADRC_TYPE1->h;
    LADRC_TYPE1->v2 += fh * LADRC_TYPE1->h;
}

/**
  * @brief LADRC����״̬�۲���
  * @param[in] LADRC_TYPE1 ��ڲ���
  * @param[in] FeedBack ����ֵ
  */
void LADRC_ESO(LADRC_NUM *LADRC_TYPE1, float FeedBack)
{
    float Beita_01 = 3 * LADRC_TYPE1->w0;
    float Beita_02 = 3 * LADRC_TYPE1->w0 * LADRC_TYPE1->w0;
    float Beita_03 = LADRC_TYPE1->w0 * LADRC_TYPE1->w0 * LADRC_TYPE1->w0;

    float e = LADRC_TYPE1->z1 - FeedBack;
    LADRC_TYPE1->z1 += (LADRC_TYPE1->z2 - Beita_01 * e) * LADRC_TYPE1->h;
    LADRC_TYPE1->z2 += (LADRC_TYPE1->z3 - Beita_02 * e + LADRC_TYPE1->b0 * LADRC_TYPE1->u) * LADRC_TYPE1->h;
    LADRC_TYPE1->z3 += -Beita_03 * e * LADRC_TYPE1->h;
}

/**
  * @brief LADRC���Կ�����
  */
void LADRC_LF(LADRC_NUM *LADRC_TYPE1)
{
    float Kp = LADRC_TYPE1->wc * LADRC_TYPE1->wc;
    float Kd = 2 * LADRC_TYPE1->wc;
    /**
      * @brief ���Կ�����������kd = 2wc
      * @note  Kd=3*LADRC_TYPE1->wc;
      * @note  Kd=2*LADRC_TYPE1->wc;
      * @date  2022-04-27
      */
    float e1 = LADRC_TYPE1->v1 - LADRC_TYPE1->z1;
    float e2 = LADRC_TYPE1->v2 - LADRC_TYPE1->z2;
    float u0 = Kp * e1 + Kd * e2;
    LADRC_TYPE1->u = (u0 - LADRC_TYPE1->z3) / LADRC_TYPE1->b0;
    if (LADRC_TYPE1->u > 2000)
        LADRC_TYPE1->u = 2000;
    else if (LADRC_TYPE1->u < -2000)
        LADRC_TYPE1->u = -2000;
}

/**
  * @brief LADRC���ƺ���
  * @note ������������ѭ���м���
  */
void LADRC_Loop(LADRC_NUM *LADRC_TYPE1, float* Expect, float* RealTimeOut)
{
    float Expect_Value = *Expect;
    float Measure = *RealTimeOut;
    LADRC_TD(LADRC_TYPE1, Expect_Value);
    LADRC_ESO(LADRC_TYPE1, Measure);
    LADRC_LF(LADRC_TYPE1);
}
