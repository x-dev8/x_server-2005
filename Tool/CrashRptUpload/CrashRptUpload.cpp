// CrashRptUpload.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CrashRptUpload.h"
#include "CrashRptUploadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCrashRptUploadApp

BEGIN_MESSAGE_MAP(CCrashRptUploadApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCrashRptUploadApp construction

CCrashRptUploadApp::CCrashRptUploadApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCrashRptUploadApp object

CCrashRptUploadApp theApp;
char* UnicodeToAnsi(WCHAR* wstr)
{
	if(!wstr)
		return NULL;
	int strleng = ::WideCharToMultiByte(CP_ACP, NULL, wstr, wcslen(wstr), NULL, 0, NULL, FALSE);
	char* str = new char[strleng + 1];
	::WideCharToMultiByte(CP_ACP, NULL, wstr, wcslen(wstr), str, strleng, NULL, FALSE);
	str[strleng]= '\0';
	return str;
}

// CCrashRptUploadApp initialization
extern void set_upload_info(std::string user_,std::string pwd_,std::string ip_,std::string dump,std::string app);
BOOL CCrashRptUploadApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	int argc=0;
	LPWSTR * lpszArgv=NULL;
	LPWSTR szCmdLine=GetCommandLineW();
	lpszArgv =CommandLineToArgvW(szCmdLine,&argc);
	if(argc>=3){
		CString apppara;
		for(int i=6;i<argc;i++)
		{
			CString s1;
			if(i!=argc-1)s1.Format("%s ",UnicodeToAnsi(lpszArgv[i]));
			else s1.Format("%s",UnicodeToAnsi(lpszArgv[i]));
			apppara+=s1;
		}
		
		CString app;
		app.Format("%s %s",UnicodeToAnsi(lpszArgv[5]),apppara);
		
		CString s;
		s.Format("%s,%s,%s,%s,%s",UnicodeToAnsi(lpszArgv[1]),UnicodeToAnsi(lpszArgv[2]),UnicodeToAnsi(lpszArgv[3]),
			UnicodeToAnsi(lpszArgv[4]),app);
	//	AfxMessageBox(s);
			set_upload_info(UnicodeToAnsi(lpszArgv[1]),UnicodeToAnsi(lpszArgv[2]),UnicodeToAnsi(lpszArgv[3]),
				UnicodeToAnsi(lpszArgv[4]),(std::string)app);

	}
	else return 0;






	CCrashRptUploadDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
