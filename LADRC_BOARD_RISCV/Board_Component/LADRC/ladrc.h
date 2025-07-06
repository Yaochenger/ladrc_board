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
} LADRC_NUM;

/**
  * @brief �Զ���������
  */
typedef struct Auto_Tuning
{
    double Pu; // �̵�ʵ���������
    double a;  // �̵�ʵ�������ֵ
    double h;  // ָ�������ֵ
    double Wu; // ϵͳ�ٽ�Ƶ��
    double Kp; // ϵͳ�ٽ��ֵ
} AuTu;

/**
  * @brief ����Ϊ��Ҫ�����Ĳ���
  */
extern LADRC_NUM Yaw_Sysparam;
extern LADRC_NUM Depth_Sysparam;
extern LADRC_NUM Pitch_Sysparam;

#define RealTimeOut_Threshold 2000

/**
  * @brief ����ΪLADRC��غ���
  */
void LADRC_Init(LADRC_NUM *LADRC_TYPE1);
void LADRC_REST(LADRC_NUM *LADRC_TYPE1);
void LADRC_TD(LADRC_NUM *LADRC_TYPE1, double Expect);
void LADRC_ESO(LADRC_NUM *LADRC_TYPE1, double FeedBack);
void LADRC_LF(LADRC_NUM *LADRC_TYPE1);
void LADRC_Loop(LADRC_NUM *LADRC_TYPE1, double* Expect, double* RealTimeOut);

#endif
