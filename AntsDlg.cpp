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

#include "mmsystem.h"                   //导入声音头文件
#pragma comment(lib,"winmm.lib")        //导入声音头文件库

// 定义核心类
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
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
        CWnd::MessageBox("王浩宇：不好意思，你只能点确定。", "小提示", MB_ICONINFORMATION | MB_OK);
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

                // 画杆子
                int x = theCore.stickPosition.x * theCore.GetStickPixel();
                int y = theCore.stickPosition.y * theCore.GetStickPixel();
                CRect stickBody(x,
                                y,
                                x + theCore.GetStickLength() * theCore.GetStickPixel(),
                                y + int (0.5 * theCore.GetStickPixel())
                               );
                CBrush* stickBrush = new CBrush;
                stickBrush->CreateSolidBrush(RGB(0x8B, 0x45, 0x13));
                pDC->FillRect(stickBody, stickBrush);
                delete stickBrush;

                // 画蚂蚁
                for (int i = 0; i < theCore.GetAntsNumber(); i++) {
                        if (!theCore.ants[i].isDead()) {
                                int x = (theCore.stickPosition.x + theCore.ants[i].GetPosition()) * theCore.GetStickPixel();
                                int y = (theCore.stickPosition.y - 1) * theCore.GetStickPixel();
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
        // 设置静态区域的背景颜色
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
        Invalidate();
        UpdateWindow();
        
        // 判断是否有蚂蚁胜利
        if (theCore.victor) {
                KillTimer(1);
                CString text;
                text.Format("经过了%d秒，%d号蚂蚁胜利了！", theCore.timeCounter, theCore.victor);
                // 播放胜利声音
                PlaySound((LPCTSTR)IDR_WIN, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

                CWnd::MessageBox(text, "结果", MB_OK);
                return;
        }
        
        theCore.antsMove();
        theCore.timeCounter++;
        
	
	CDialog::OnTimer(nIDEvent);
}

void CAntsDlg::OnRand() 
{
	// TODO: Add your control notification handler code here
        KillTimer(1);
        theCore.InitAnts();
        theCore.RandTime();
        SetTimer(1, 600, NULL);
        
}

void CAntsDlg::OnMin() 
{
	// TODO: Add your control notification handler code here
        KillTimer(1);
        theCore.InitAnts();
        theCore.CaculMinTime();
        SetTimer(1, 600, NULL);
}

void CAntsDlg::OnMax() 
{
	// TODO: Add your control notification handler code here
        KillTimer(1);
        theCore.InitAnts();
        theCore.CaculMaxTime();
        SetTimer(1, 600, NULL);	
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
