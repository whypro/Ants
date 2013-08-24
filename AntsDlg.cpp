// AntsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ants.h"
#include "AntsDlg.h"
#include "AntsCore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SPEED 600

#include "mmsystem.h"                   //��������ͷ�ļ�
#pragma comment(lib,"winmm.lib")        //��������ͷ�ļ���

// ���������
CAntsCore theCore;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntsDlg dialog

CAntsDlg::CAntsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAntsDlg)
	m_stepA = 0.5f;
	m_stepB = 0.5f;
	m_stepC = 0.5f;
	m_stepD = 0.5f;
	m_stepE = 0.5f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntsDlg)
	DDX_Text(pDX, IDC_STEP_A, m_stepA);
	DDX_Text(pDX, IDC_STEP_B, m_stepB);
	DDX_Text(pDX, IDC_STEP_C, m_stepC);
	DDX_Text(pDX, IDC_STEP_D, m_stepD);
	DDX_Text(pDX, IDC_STEP_E, m_stepE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAntsDlg, CDialog)
	//{{AFX_MSG_MAP(CAntsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RAND, OnRand)
	ON_BN_CLICKED(IDC_MIN, OnMin)
	ON_BN_CLICKED(IDC_MAX, OnMax)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_RANDSTEP, OnRandStep)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntsDlg message handlers

BOOL CAntsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
                // ���ùرհ�ť
                pSysMenu->DeleteMenu(SC_CLOSE,MF_BYCOMMAND);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

        // �����ı�������ַ�����
        CEdit * pEdt;
        pEdt = (CEdit *) GetDlgItem(IDC_STEP_A);
        pEdt->SetLimitText(3);
        pEdt = (CEdit *) GetDlgItem(IDC_STEP_B);
        pEdt->SetLimitText(3);
        pEdt = (CEdit *) GetDlgItem(IDC_STEP_C);
        pEdt->SetLimitText(3);
        pEdt = (CEdit *) GetDlgItem(IDC_STEP_D);
        pEdt->SetLimitText(3);
        pEdt = (CEdit *) GetDlgItem(IDC_STEP_E);
        pEdt->SetLimitText(3);

        // ������ͣ��ֹͣ��ť
        GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STOP)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAntsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CAboutDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
        CWnd::MessageBox("�����������˼����ֻ�ܵ�ȷ����", "С��ʾ", MB_ICONINFORMATION | MB_OK);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAntsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
                CWnd* pWnd = GetDlgItem(IDC_STATIC_DRAW);
                CDC* pDC = pWnd->GetDC();

                pWnd->Invalidate();
                pWnd->UpdateWindow();
                

                // ������
                int x = theCore.stickPosition.x * theCore.GetStickPixel();
                int y = theCore.stickPosition.y * theCore.GetStickPixel();
                CRect stickBody(x,
                                y,
                                x + theCore.GetStickLength() * theCore.GetStickPixel(),
                                y + int (0.4 * theCore.GetStickPixel())
                               );
                CBrush* stickBrush = new CBrush;
                stickBrush->CreateSolidBrush(RGB(0x8B, 0x45, 0x13));
                pDC->FillRect(stickBody, stickBrush);
                delete stickBrush;

                // ������
                for (int i = 0; i < theCore.GetAntsNumber(); i++) {
                        if (!theCore.ants[i].isDead()) {
                                int x = int ((theCore.stickPosition.x + theCore.ants[i].GetPosition()) * theCore.GetStickPixel());
                                int y = (theCore.stickPosition.y - 1)  * theCore.GetStickPixel();
                                CRect antBody(x,
                                              y,
                                              x + theCore.GetStickPixel(),
                                              y + theCore.GetStickPixel()
                                             );
                                CBrush* antBrush = new CBrush;
                                antBrush->CreateSolidBrush(theCore.ants[i].GetColor());
                                pDC->SelectObject(antBrush);
                                pDC->Ellipse(antBody);
                                //pDC->FillRect(antBody, antBrush);
                                delete antBrush;
                        }
                }

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAntsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CAntsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
        // ���þ�̬����ı�����ɫ
        if (pWnd->GetDlgCtrlID() == IDC_STATIC_DRAW) {
                HBRUSH m_hbrush;
                COLORREF bgColor = RGB(0xFF, 0xFF, 0xFF);
                m_hbrush = CreateSolidBrush(bgColor);
                return m_hbrush;
        }
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CAntsDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

        // �˴�����˴�����˸�����⣡
        CWnd* pWnd = GetDlgItem(IDC_STATIC_DRAW);
        CRect rect;
        pWnd->GetClientRect(&rect);
        InvalidateRect(rect);
        UpdateWindow();



        // �ж��Ƿ�������ʤ��

        if (theCore.victor != -1) {
                CString text;
                KillTimer(1);

                if (theCore.victor == 0) {
                        text.Format("������%d�룬��������ͬ���ھ���", theCore.timeCounter);
                }
                else {
                        text.Format("������%d�룬%d������ʤ���ˣ�", theCore.timeCounter, theCore.victor);
                }

                // ���Ž�������
                PlaySound((LPCTSTR)IDR_WIN, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
                CWnd::MessageBox(text, "���", MB_ICONWARNING | MB_OK);
                GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
                GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
                GetDlgItem(IDC_RANDSTEP)->EnableWindow(TRUE);
                GetDlgItem(IDC_RAND)->EnableWindow(TRUE);
                GetDlgItem(IDC_MAX)->EnableWindow(TRUE);
                GetDlgItem(IDC_MIN)->EnableWindow(TRUE);
                return;
        }

        
        theCore.antsMove();
        theCore.timeCounter++;
        
	
	CDialog::OnTimer(nIDEvent);
}

void CAntsDlg::OnRand() 
{
	// TODO: Add your control notification handler code here
        UpdateData();
        //if (!(m_stepA && m_stepB && m_stepC && m_stepD && m_stepE)) {
        if (m_stepA <= 0 || m_stepA > 1 ||
            m_stepB <= 0 || m_stepB > 1 ||
            m_stepC <= 0 || m_stepC > 1 ||
            m_stepD <= 0 || m_stepD > 1 ||
            m_stepE <= 0 || m_stepE > 1) {
                CWnd::MessageBox("��������鲽�����á�", "С����", MB_ICONERROR | MB_OK);
                return;
        }

        OnStop();
        UpdateStep();
        theCore.RandTime();
        SetTimer(1, SPEED, NULL);
        GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
        GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
        GetDlgItem(IDC_RANDSTEP)->EnableWindow(FALSE);
        GetDlgItem(IDC_RAND)->EnableWindow(FALSE);
        GetDlgItem(IDC_MAX)->EnableWindow(FALSE);
        GetDlgItem(IDC_MIN)->EnableWindow(FALSE);
}

void CAntsDlg::OnMin() 
{
	// TODO: Add your control notification handler code here
        UpdateData();
        //if (!(m_stepA && m_stepB && m_stepC && m_stepD && m_stepE)) {
        if (m_stepA <= 0 || m_stepA > 1 ||
            m_stepB <= 0 || m_stepB > 1 ||
            m_stepC <= 0 || m_stepC > 1 ||
            m_stepD <= 0 || m_stepD > 1 ||
            m_stepE <= 0 || m_stepE > 1) {
                CWnd::MessageBox("��������鲽�����á�", "С����", MB_ICONERROR | MB_OK);
                return;
        }

        OnStop();
        UpdateStep();
        theCore.CaculMinTime();
        SetTimer(1, SPEED, NULL);
        GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
        GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
        GetDlgItem(IDC_RANDSTEP)->EnableWindow(FALSE);
        GetDlgItem(IDC_RAND)->EnableWindow(FALSE);
        GetDlgItem(IDC_MAX)->EnableWindow(FALSE);
        GetDlgItem(IDC_MIN)->EnableWindow(FALSE);
}

void CAntsDlg::OnMax() 
{
	// TODO: Add your control notification handler code here
        UpdateData();
        //if (!(m_stepA && m_stepB && m_stepC && m_stepD && m_stepE)) {
        if (m_stepA <= 0 || m_stepA > 1 ||
            m_stepB <= 0 || m_stepB > 1 ||
            m_stepC <= 0 || m_stepC > 1 ||
            m_stepD <= 0 || m_stepD > 1 ||
            m_stepE <= 0 || m_stepE > 1) {
                CWnd::MessageBox("��������鲽�����á�", "С����", MB_ICONERROR | MB_OK);
                return;
        }

        OnStop();
        UpdateStep();
        theCore.CaculMaxTime();
        SetTimer(1, SPEED, NULL);
        GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
        GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
        GetDlgItem(IDC_RANDSTEP)->EnableWindow(FALSE);
        GetDlgItem(IDC_RAND)->EnableWindow(FALSE);
        GetDlgItem(IDC_MAX)->EnableWindow(FALSE);
        GetDlgItem(IDC_MIN)->EnableWindow(FALSE);
}

void CAntsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CAntsDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
        CAboutDlg dlg;
        dlg.DoModal();
}

void CAntsDlg::OnRandStep() 
{
	// TODO: Add your control notification handler code here

        theCore.RandStep();
        UpdateStep(false);
        UpdateData(FALSE);
}

void CAntsDlg::UpdateStep(bool needSet)
{
        if (needSet) {
                theCore.ants[0].SetStep(m_stepA);
                theCore.ants[1].SetStep(m_stepB);
                theCore.ants[2].SetStep(m_stepC);
                theCore.ants[3].SetStep(m_stepD);
                theCore.ants[4].SetStep(m_stepE);
        }
        else {
                m_stepA = theCore.ants[0].GetStep();
                m_stepB = theCore.ants[1].GetStep();
                m_stepC = theCore.ants[2].GetStep();
                m_stepD = theCore.ants[3].GetStep();
                m_stepE = theCore.ants[4].GetStep();
        }
}


void CAntsDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
        KillTimer(1);
        theCore.InitAnts();
        GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
        GetDlgItem(IDC_RANDSTEP)->EnableWindow(TRUE);
        GetDlgItem(IDC_RAND)->EnableWindow(TRUE);
        GetDlgItem(IDC_MAX)->EnableWindow(TRUE);
        GetDlgItem(IDC_MIN)->EnableWindow(TRUE);
	Invalidate();
}


void CAntsDlg::OnPause() 
{
	// TODO: Add your control notification handler code here
        CString text;
        GetDlgItem(IDC_PAUSE)->GetWindowText(text);
        if  (text == "��ͣ��ʾ") {
                KillTimer(1);
                GetDlgItem(IDC_PAUSE)->SetWindowText("������ʾ");
        }
        else if (text == "������ʾ") {
                SetTimer(1, SPEED, NULL);
                GetDlgItem(IDC_PAUSE)->SetWindowText("��ͣ��ʾ");
        }                
}
