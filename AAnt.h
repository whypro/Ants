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
        enum {dead, live} status;               // 生存状态
        enum {left, right} direction;           // 移动方向
        int course;                             // 行走过的路程
        int position;                           // 所处位置
        int step;                               // 移动步长（速度）
        COLORREF color;                         // 身体颜色

public:
	CAAnt();
	virtual ~CAAnt();

	void InitOneAnt();                      // 初始化状态

	void SetDirection(int dir);             // 设置方向
        void SetPosition(int pos);              // 设置位置
        void SetColor(COLORREF clr);            // 设置颜色
        void Kill(void);                        // 杀死蚂蚁

        int GetCourse(void);                    // 获取行走过的路程长度
        int GetPosition(void);                  // 获取位置
        COLORREF GetColor(void);                // 获取颜色
        bool isDead(void);                      // 获取生存状态

        void Move(int edge);                    // 移动蚂蚁
};

#endif // !defined(AFX_AANT_H__1B5BDA66_8628_42C0_822C_5B1B92E26FDE__INCLUDED_)
