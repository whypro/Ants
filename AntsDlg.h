// AntsDlg.h : header file
//

#if !defined(AFX_ANTSDLG_H__761B6F5F_F447_4149_A0F2_161EBEAC99F3__INCLUDED_)
#define AFX_ANTSDLG_H__761B6F5F_F447_4149_A0F2_161EBEAC99F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAntsDlg dialog

class CAntsDlg : public CDialog
{
// Construction
public:
	CAntsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAntsDlg)
	enum { IDD = IDD_ANTS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAntsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRand();
	afx_msg void OnMin();
	afx_msg void OnMax();
	afx_msg void OnAbout();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTSDLG_H__761B6F5F_F447_4149_A0F2_161EBEAC99F3__INCLUDED_)
