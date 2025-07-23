#ifndef _LADRC_H
#define _LADRC_H

/**
  * @brief LADRCϵͳ����
  */
typedef struct LADRC
{
    double v1, v2;         // �������ֵ
    double r;              // �ٶ�����
    double h;              // ���ֲ���
    double z1, z2, z3;     // �۲������
    double w0, wc, b0, u;  // �۲������� ���������� ϵͳ���� ���������
} LADRC_TypeDef;

/**
  * @brief ����Ϊ��Ҫ�����Ĳ���
  */
extern LADRC_TypeDef Yaw_Sysparam;
extern LADRC_TypeDef Depth_Sysparam;
extern LADRC_TypeDef Pitch_Sysparam;

#define RealTimeOut_Threshold 2000

/**
  * @brief ����ΪLADRC��غ���
  */
void LADRC_INIT(LADRC_TypeDef *LADRC_TYPE1);
void LADRC_REST(LADRC_TypeDef *LADRC_TYPE1);
void LADRC_TD(LADRC_TypeDef *LADRC_TYPE1, double Expect);
void LADRC_ESO(LADRC_TypeDef *LADRC_TYPE1, double FeedBack);
void LADRC_LF(LADRC_TypeDef *LADRC_TYPE1);
void LADRC_Loop(LADRC_TypeDef *LADRC_TYPE1, double* Expect, double* RealTimeOut);

#endif
