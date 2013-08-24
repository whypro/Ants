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
        stickPosition.Offset(6, 7);
        stickPixel = 10;
        stickLength = 27;
        antsNumber = 5;
        ants = new CAAnt[antsNumber];
        InitAnts();
}

CAntsCore::~CAntsCore()
{
        delete ants;
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
        victor = 0;

        // ��ʼ��ÿֻ����״̬
        for (int i = 0; i < antsNumber; i++) {
                ants[i].InitOneAnt();
        }

        // ��ʼ��������ɫ
        ants[0].SetColor(RGB(0xFF, 0x63, 0x47));
        ants[1].SetColor(RGB(0x7F, 0xFF, 0x00));
        ants[2].SetColor(RGB(0xFF, 0x00, 0xFF));
        ants[3].SetColor(RGB(0x64, 0x95, 0xED));
        ants[4].SetColor(RGB(0xFF, 0xFF, 0x00));

        // ��ʼ������λ��
        ants[0].SetPosition(3);
        ants[1].SetPosition(7);
        ants[2].SetPosition(11);
        ants[3].SetPosition(17);
        ants[4].SetPosition(23);
}

void CAntsCore::antsMove() {
        int i, j;
        
        // �ж�ʤ����
        int alive = 0;
        for (i = 0; i < antsNumber; i++) {
                if (!ants[i].isDead()) {
                        j = i + 1;      // j ��ʱ�洢δ��������
                        alive++;
                }
        }
        // ��ֻʣ��һֻ����ʱ
        if (alive == 1) {
                victor = j;
                return;
        }

        // �ƶ�
        for (i = 0; i < antsNumber; i++) {
                if (ants[i].isDead()) {
                        continue;
                }
                else {
                        ants[i].Move(stickLength);
                }
        }

        // ����Ƿ������������� �����㷨Ч�ʺܵͣ��д��ڸĽ���
        for (i = 0; i < antsNumber; i++) {
                for (j = i + 1; j < antsNumber; j++) {
                        if (ants[i].GetPosition() == ants[j].GetPosition() ||           // ����
                            ants[i].GetPosition() + 1 == ants[j].GetPosition()          // ����
                           ) {
                                if (ants[j].GetCourse() < ants[i].GetCourse()) {
                                        ants[j].Kill();
                                }
                                else if (ants[j].GetCourse() > ants[i].GetCourse()) {
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
        // ��ʼ�����Ϸ��������
        srand((unsigned)time(NULL));
        ants[0].SetDirection(rand() % 2);
        ants[1].SetDirection(rand() % 2);
        ants[2].SetDirection(rand() % 2);
        ants[3].SetDirection(rand() % 2);
        ants[4].SetDirection(rand() % 2);
}

void CAntsCore::CaculMaxTime()
{
        // ���ϸ���Ϊ 5
        // ���������������ı�ʱ����Ҫ���Ĵ˴�����ֵ

        // �������ϵ���ʱ����
        bitset<5> tmpDir;

        // �������ϵ����ʱ�䷽��
        bitset<5> maxDir;
        int maxTime = 0;

        int i, j;

        // �������� 2^antsNumber �ַ���
        for (i = 0; i < pow(2, antsNumber); i++) {
                InitAnts();
                tmpDir = i;
                // ������ʱ����
                for (j = 0; j < antsNumber; j++) {
                        ants[j].SetDirection(tmpDir[j]);
                }
                // ����ʱ�䣨ģ�⣩
                while (!victor) {
                        antsMove();
                        timeCounter++;
                }
                // �Ƿ�Ϊ���ʱ��
                if (timeCounter > maxTime) {
                        maxTime = timeCounter;
                        maxDir = tmpDir;
                }
        }

        // �������Ϸ���Ϊ���ʱ�䷽��
        InitAnts();
        for (i = 0; i < antsNumber; i++) {
                ants[i].SetDirection(maxDir[i]);
        }                        
}

void CAntsCore::CaculMinTime()
{
        // ���ϸ���Ϊ 5
        // ���������������ı�ʱ����Ҫ���Ĵ˴�����ֵ

        // �������ϵ���ʱ����
        bitset<5> tmpDir;

        // �������ϵ���Сʱ�䷽��
        bitset<5> minDir;
        // 99 Ϊ�㹻���ʱ��
        int minTime = 99;

        int i, j;

        // �������� 2^antsNumber �ַ���
        for (i = 0; i < pow(2, antsNumber); i++) {
                InitAnts();
                tmpDir = i;
                // ������ʱ����
                for (j = 0; j < antsNumber; j++) {
                        ants[j].SetDirection(tmpDir[j]);
                }
                // ����ʱ�䣨ģ�⣩
                while (!victor) {
                        antsMove();
                        timeCounter++;
                }
                // �Ƿ�Ϊ��Сʱ��
                if (timeCounter < minTime) {
                        minTime = timeCounter;
                        minDir = tmpDir;
                }
        }

        // �������Ϸ���Ϊ��Сʱ��
        InitAnts();
        for (i = 0; i < antsNumber; i++) {
                ants[i].SetDirection(minDir[i]);
        }

}
