// AntsCore.h: interface for the CAntsCore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANTSCORE_H__C09D9885_04BB_4E9B_8012_D6B488281989__INCLUDED_)
#define AFX_ANTSCORE_H__C09D9885_04BB_4E9B_8012_D6B488281989__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AAnt.h"
#include "Afxtempl.h"

class CAntsCore  
{
private:
        int stickPixel;                 // ��������
        int stickLength;                // ���ӳ���
        int antsNumber;                 // ��������

public:
        CPoint stickPosition;           // ����λ��
        CAAnt* ants;
        int victor;                     // ʤ����
        int timeCounter;                // ��ʱ��

public:
	void RandStep();
	CAntsCore();                    
	virtual ~CAntsCore();

	void InitAnts();                // ��ʼ������

  	int GetAntsNumber();            // ��ȡ��������
        int GetStickPixel(void);        // ��ȡ��������
        int GetStickLength(void);       // ��ȡ���ӳ���

	void RandTime();                // ����������Ϸ���
	void CaculMinTime();            // �������ʱ����������ϵķ���
	void CaculMaxTime();            // �����ʱ����������ϵķ���

        void antsMove();                // �ƶ�����
};

#endif // !defined(AFX_ANTSCORE_H__C09D9885_04BB_4E9B_8012_D6B488281989__INCLUDED_)
