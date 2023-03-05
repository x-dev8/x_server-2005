// NewDlg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNewDlgApp:
// See NewDlg.cpp for the implementation of this class
//

class CNewDlgApp : public CWinApp
{
public:
	CNewDlgApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	BOOL FindInstance();
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CNewDlgApp theApp;