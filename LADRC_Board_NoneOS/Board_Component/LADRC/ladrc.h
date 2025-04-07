#ifndef _LADRC_H
#define _LADRC_H

/**
  * @brief LADRCϵͳ����
  */
typedef struct LADRC
{
    float v1, v2;         // �������ֵ
    float r;              // �ٶ�����
    float h;              // ���ֲ���
    float z1, z2, z3;     // �۲������
    float w0, wc, b0, u;  // �۲������� ���������� ϵͳ���� ���������
} LADRC_NUM;

/**
  * @brief �Զ���������
  */
typedef struct Auto_Tuning
{
    float Pu; // �̵�ʵ���������
    float a;  // �̵�ʵ�������ֵ
    float h;  // ָ�������ֵ
    float Wu; // ϵͳ�ٽ�Ƶ��
    float Kp; // ϵͳ�ٽ��ֵ
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
void LADRC_TD(LADRC_NUM *LADRC_TYPE1, float Expect);
void LADRC_ESO(LADRC_NUM *LADRC_TYPE1, float FeedBack);
void LADRC_LF(LADRC_NUM *LADRC_TYPE1);
void LADRC_Loop(LADRC_NUM *LADRC_TYPE1, float* Expect, float* RealTimeOut);

#endif
