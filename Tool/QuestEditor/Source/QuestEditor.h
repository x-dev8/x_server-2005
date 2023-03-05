// QuestEditor.h : main header file for the QuestEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CQuestEditorApp:
// See QuestEditor.cpp for the implementation of this class
//

class CQuestEditorApp : public CWinApp
{
public:
	CQuestEditorApp();

private:
	void ShowVersionInformation();

	// Overrides
public:
	virtual BOOL InitInstance();

	// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CQuestEditorApp theApp;