// Editor.h : main header file for the Editor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEditorApp:
// See Editor.cpp for the implementation of this class
//

class CEditorApp : public CWinApp
{
public:
	CEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEditorApp theApp;