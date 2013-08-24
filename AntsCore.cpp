// AntsCore.cpp: implementation of the CAntsCore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ants.h"
#include "AntsCore.h"

#include "stdafx.h"
#include "Ants.h"
#include "AntsDlg.h"

#include <bitset>
using std::bitset;

#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAntsCore::CAntsCore()
{
        stickPosition.Offset(4, 5);
        stickPixel = 20;
        stickLength = 27;
        antsNumber = 5;
        ants = new CAAnt[antsNumber];
        InitAnts();
}

CAntsCore::~CAntsCore()
{

}

int CAntsCore::GetStickPixel(void) {
        return stickPixel;
}

int CAntsCore::GetStickLength(void) {
        return stickLength;
}

int CAntsCore::GetAntsNumber() {
        return antsNumber;
}

void CAntsCore::InitAnts()
{
        timeCounter = 0;
        victor = -1;

        // 初始化每只蚂蚁状态
        for (int i = 0; i < antsNumber; i++) {
                ants[i].InitOneAnt();
        }

        // 初始化蚂蚁颜色
        ants[0].SetColor(RGB(0xFF, 0x63, 0x47));
        ants[1].SetColor(RGB(0x7F, 0xFF, 0x00));
        ants[2].SetColor(RGB(0xFF, 0x00, 0xFF));
        ants[3].SetColor(RGB(0x64, 0x95, 0xED));
        ants[4].SetColor(RGB(0xFF, 0xFF, 0x00));

        // 初始化蚂蚁位置
        ants[0].SetPosition(3);
        ants[1].SetPosition(7);
        ants[2].SetPosition(11);
        ants[3].SetPosition(17);
        ants[4].SetPosition(23);
}

void CAntsCore::antsMove() {
        int i, j;
        
        // 判断胜利者
        int alive = 0;
        for (i = 0; i < antsNumber; i++) {
                if (!ants[i].isDead()) {
                        j = i + 1;      // j 临时存储未死的蚂蚁
                        alive++;
                }
        }
        // 当只剩下一只蚂蚁时
        if (1 == alive) {
                victor = j;
                return;
        }
        else if (0 == alive) {
                victor = 0;
                return;
        }

        // 移动
        for (i = 0; i < antsNumber; i++) {
                if (ants[i].isDead()) {
                        continue;
                }
                else {
                        ants[i].Move(stickLength);
                }
        }

        // 检测是否有相遇的蚂蚁
        for (i = 0; i < antsNumber; i++) {
                for (j = i + 1; j < antsNumber; j++) {
                        // 两只蚂蚁的距离
                        float posDiff = abs(ants[i].GetPosition() - ants[j].GetPosition());
                        float minDiff = abs(ants[i].GetStep() - ants[j].GetStep());
                        if (posDiff <= minDiff) {
                                if (ants[j].GetCourse() - ants[i].GetCourse() < -0.1) {
                                        ants[j].Kill();
                                }
                                else if (ants[j].GetCourse() - ants[i].GetCourse() > 0.1) {
                                        ants[i].Kill();
                                }
                                else {
                                        ants[i].Kill();
                                        ants[j].Kill();
                                }
                        }
                }
        }


}


void CAntsCore::RandTime()
{
        // 初始化蚂蚁方向（随机）
        // 此处不用 rand() % 2
        srand(unsigned (time(NULL)));
        ants[0].SetDirection(rand() / (RAND_MAX / 2 + 1));
        ants[1].SetDirection(rand() / (RAND_MAX / 2 + 1));
        ants[2].SetDirection(rand() / (RAND_MAX / 2 + 1));
        ants[3].SetDirection(rand() / (RAND_MAX / 2 + 1));
        ants[4].SetDirection(rand() / (RAND_MAX / 2 + 1));
}

void CAntsCore::CaculMaxTime()
{
        // 蚂蚁个数为 5
        // 当蚂蚁数量发生改变时，需要更改此处的数值

        // 储存蚂蚁的临时方向
        bitset<5> tmpDir;

        // 储存蚂蚁的最大时间方向
        bitset<5> maxDir;
        int maxTime = 0;

        int i, j;

        // 产生所有 2^antsNumber 种方向
        for (i = 0; i < pow(2, antsNumber); i++) {
                InitAnts();
                tmpDir = i;
                // 设置临时方向
                for (j = 0; j < antsNumber; j++) {
                        ants[j].SetDirection(tmpDir[j]);
                }
                // 测试时间（模拟）
                while (victor == -1) {
                        antsMove();
                        timeCounter++;
                }
                // 是否为最大时间
                if (timeCounter > maxTime) {
                        maxTime = timeCounter;
                        maxDir = tmpDir;
                }
        }

        // 设置蚂蚁方向为最大时间方向
        InitAnts();
        for (i = 0; i < antsNumber; i++) {
                ants[i].SetDirection(maxDir[i]);
        }                        
}

void CAntsCore::CaculMinTime()
{
        // 蚂蚁个数为 5
        // 当蚂蚁数量发生改变时，需要更改此处的数值

        // 储存蚂蚁的临时方向
        bitset<5> tmpDir;

        // 储存蚂蚁的最小时间方向
        bitset<5> minDir;
        // 99 为足够大的时间
        int minTime = 99;

        int i, j;

        // 产生所有 2^antsNumber 种方向
        for (i = 0; i < pow(2, antsNumber); i++) {
                InitAnts();
                tmpDir = i;
                // 设置临时方向
                for (j = 0; j < antsNumber; j++) {
                        ants[j].SetDirection(tmpDir[j]);
                }
                // 测试时间（模拟）
                while (victor == -1) {
                        antsMove();
                        timeCounter++;
                }
                // 是否为最小时间
                if (timeCounter < minTime) {
                        minTime = timeCounter;
                        minDir = tmpDir;
                }
        }

        // 设置蚂蚁方向为最小时间
        InitAnts();
        for (i = 0; i < antsNumber; i++) {
                ants[i].SetDirection(minDir[i]);
        }

}

void CAntsCore::RandStep()
{
        // 初始化蚂蚁步长（速度）
        srand(unsigned (time(NULL)));
        ants[0].SetStep(float (rand()) / float (RAND_MAX) + 0);
        ants[1].SetStep(float (rand()) / float (RAND_MAX) + 0);
        ants[2].SetStep(float (rand()) / float (RAND_MAX) + 0);
        ants[3].SetStep(float (rand()) / float (RAND_MAX) + 0);
        ants[4].SetStep(float (rand()) / float (RAND_MAX) + 0);
}
