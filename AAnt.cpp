// AAnt.cpp: implementation of the CAAnt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ants.h"
#include "AAnt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAAnt::CAAnt()
{
        InitOneAnt();
}

CAAnt::~CAAnt()
{

}

void CAAnt::InitOneAnt()
{
        status = live;
        direction = right;
        position = 0;
        step = 1;
        course = 0;
}

int CAAnt::GetCourse(void) {
        return course;
}

int CAAnt::GetPosition(void) {
        return position;
}

COLORREF CAAnt::GetColor(void) {
        return color;
}

bool CAAnt::isDead(void) {
        if (status == dead) {
                return true;
        }
        else {
                return false;
        }
}

void CAAnt::SetPosition(int pos) {
        position = pos;
}

void CAAnt::SetColor(COLORREF clr) {
        color = clr;
}

void CAAnt::SetDirection(int dir)
{
        switch (dir) {
        case 0:
                direction = left;
                break;
        case 1:
                direction = right;
                break;
        default:
                break;
        }
}

void CAAnt::Kill() {
        status = dead;
}

void CAAnt::Move(int edge) {
        // 检测蚂蚁状态
        if (status == dead) {
                return;
        }

        // 检测是否走到尽头
        if (position >= edge - 1 && direction == right) {
                direction = left;
        }
        else if (position <= 0 && direction == left) {
                direction = right;
        }

        // 移动一步
        if (direction == left) {
                position -= step;
        }
        else if (direction == right) {
                position += step;
        }
        // 行走的路程增加
        course++;
}
