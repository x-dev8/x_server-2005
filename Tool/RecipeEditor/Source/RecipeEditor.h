// RecipeEditor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "../Resource/Resource.h"		// main symbols


// CRecipeEditorApp:
// See RecipeEditor.cpp for the implementation of this class
//

class CRecipeEditorApp : public CWinApp
{
public:
	CRecipeEditorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRecipeEditorApp theApp;