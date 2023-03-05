// BugReporter-New.h : main header file for the BugReporter-New application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "../Resource/resource.h"       // main symbols


// CBugReporterNewApp:
// See BugReporter-New.cpp for the implementation of this class
//

class CBugReporterNewApp : public CWinApp
{
public:
	CBugReporterNewApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBugReporterNewApp theApp;