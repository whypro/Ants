// Ants.h : main header file for the ANTS application
//

#if !defined(AFX_ANTS_H__F150DF48_938E_4628_9EDD_E697C54D68FE__INCLUDED_)
#define AFX_ANTS_H__F150DF48_938E_4628_9EDD_E697C54D68FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAntsApp:
// See Ants.cpp for the implementation of this class
//

class CAntsApp : public CWinApp
{
public:
	CAntsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAntsApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTS_H__F150DF48_938E_4628_9EDD_E697C54D68FE__INCLUDED_)
