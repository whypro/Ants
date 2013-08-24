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
        int stickPixel;                 // 杆子像素
        int stickLength;                // 杆子长度
        int antsNumber;                 // 蚂蚁数量

public:
        CPoint stickPosition;           // 杆子位置
        CAAnt* ants;
        int victor;                     // 胜利者
        int timeCounter;                // 计时器

public:
	void RandStep();
	CAntsCore();                    
	virtual ~CAntsCore();

	void InitAnts();                // 初始化函数

  	int GetAntsNumber();            // 获取蚂蚁数量
        int GetStickPixel(void);        // 获取杆子像素
        int GetStickLength(void);       // 获取杆子长度

	void RandTime();                // 随机设置蚂蚁方向
	void CaculMinTime();            // 计算最短时间情况下蚂蚁的方向
	void CaculMaxTime();            // 计算最长时间情况下蚂蚁的方向

        void antsMove();                // 移动蚂蚁
};

#endif // !defined(AFX_ANTSCORE_H__C09D9885_04BB_4E9B_8012_D6B488281989__INCLUDED_)
