// AAnt.h: interface for the CAAnt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AANT_H__1B5BDA66_8628_42C0_822C_5B1B92E26FDE__INCLUDED_)
#define AFX_AANT_H__1B5BDA66_8628_42C0_822C_5B1B92E26FDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAAnt  
{
private:
        enum {dead, live} status;               // ����״̬
        enum {left, right} direction;           // �ƶ�����
        float course;                           // ���߹���·��
        float position;                         // ����λ��
        float step;                             // �ƶ��������ٶȣ�
        COLORREF color;                         // ������ɫ

public:
	CAAnt();
	virtual ~CAAnt();

	void InitOneAnt();                      // ��ʼ��״̬

	void SetDirection(int dir);             // ���÷���
        void SetPosition(float pos);            // ����λ��
        void SetStep(float stp);                // ���ò������ٶȣ�
        void SetColor(COLORREF clr);            // ������ɫ
        void Kill(void);                        // ɱ������

        float GetCourse(void);                  // ��ȡ���߹���·�̳���
        float GetPosition(void);                // ��ȡλ��
        float GetStep(void);
        COLORREF GetColor(void);                // ��ȡ��ɫ
        bool isDead(void);                      // ��ȡ����״̬

        void Move(int edge);                    // �ƶ�����
};

#endif // !defined(AFX_AANT_H__1B5BDA66_8628_42C0_822C_5B1B92E26FDE__INCLUDED_)
