#include "stdafx.h"
#include "ApplicationManager.h"
#include "ApplicationManagerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CProtectorApplication, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CProtectorApplication::CProtectorApplication()
{
}

CProtectorApplication theApp;

BOOL CProtectorApplication::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("shengwang_game"));

	CApplicationManagerDialog dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	
	}
	else if (nResponse == IDCANCEL)
	{
	
	}
	return FALSE;
}
