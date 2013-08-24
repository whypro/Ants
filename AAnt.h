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
        int course;                             // ���߹���·��
        int position;                           // ����λ��
        int step;                               // �ƶ��������ٶȣ�
        COLORREF color;                         // ������ɫ

public:
	CAAnt();
	virtual ~CAAnt();

	void InitOneAnt();                      // ��ʼ��״̬

	void SetDirection(int dir);             // ���÷���
        void SetPosition(int pos);              // ����λ��
        void SetColor(COLORREF clr);            // ������ɫ
        void Kill(void);                        // ɱ������

        int GetCourse(void);                    // ��ȡ���߹���·�̳���
        int GetPosition(void);                  // ��ȡλ��
        COLORREF GetColor(void);                // ��ȡ��ɫ
        bool isDead(void);                      // ��ȡ����״̬

        void Move(int edge);                    // �ƶ�����
};

#endif // !defined(AFX_AANT_H__1B5BDA66_8628_42C0_822C_5B1B92E26FDE__INCLUDED_)
