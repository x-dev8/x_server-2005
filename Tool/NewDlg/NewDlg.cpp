// NewDlg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NewDlg.h"
#include "NewDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewDlgApp

BEGIN_MESSAGE_MAP(CNewDlgApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNewDlgApp construction

CNewDlgApp::CNewDlgApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// ClauncherApp initialization
string GetFileName(string strFilePath)
{
	//	strFilePath.Replace(_T("/"), _T("\\"));
	size_t nLength = strFilePath.length();
	size_t nPos = 0;
	for (size_t i = nLength; i>0; i--)
	{
		if (strFilePath[i-1] == _T('\\'))
		{
			nPos = i;
			break;
		}
	}
	string strFileName = strFilePath.substr(nPos, strFilePath.length()-nPos);
	return strFileName;
}

int ver=8;



#include "psapi.h"
DWORD FindProcess(char *strProcessName)
{
	DWORD aProcesses[1024], cbNeeded, cbMNeeded;
	HMODULE hMods[1024];
	HANDLE hProcess;
	char szProcessName[MAX_PATH];

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) ) return 0;
	for(int i=0; i< (int) (cbNeeded / sizeof(DWORD)); i++)
	{
		//_tprintf(_T("%d\t"), aProcesses[i]);
		hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
		GetModuleFileNameEx( hProcess, hMods[0], szProcessName,sizeof(szProcessName));

		if(strstr(szProcessName, strProcessName))
		{
			//_tprintf(_T("%s;"), szProcessName);
			return(aProcesses[i]);
		}
		//_tprintf(_T("\n"));
	}
	return 0;
}

void CHECK_APP_NAME()
{	
	TCHAR szCurName[1024];
	TCHAR szNewName[1024];
	GetModuleFileName( NULL,szCurName,MAX_PATH );	
	std::string name=szCurName;
	name=GetFileName(name);
	if(strcmp(name.c_str(),_T("launcher.exe"))!=0)
	{
		//重命名，删除旧版本
		while (1)
		{
			//zhao jingcheng launcher.exe
			if (FindProcess("launcher.exe")==0)
			{
				break;
			}
			Sleep(100);
		}
		//::MessageBox(NULL,"da","Aa",MB_OK);
		DeleteFile(_T("launcher.exe"));
		_tcscpy( szNewName,_T("launcher.exe") );
		MoveFile( szCurName,szNewName );

	}
}

// The one and only CNewDlgApp object

CNewDlgApp theApp;

bool bRebootApp=false;
// CNewDlgApp initialization
void RENANE_APP()
{
	TCHAR szCurName[1024];
	GetModuleFileName( NULL,szCurName,MAX_PATH );	
	MoveFile( szCurName,NEW_LAUNCHER_OLD_TEMP_NAME );

	Sleep(500);
}
BOOL CNewDlgApp::InitInstance()
{
	//MessageBox(NULL,"123","123",MB_OK);
	if (!FindInstance())
	{
		return FALSE;
	}
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	//MessageBox(NULL,"123","123",MB_OK);
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	//切换当前路径为EXE文件所在路径
	TCHAR FilePath[_MAX_PATH ] = {0};
	TCHAR Drive[_MAX_DRIVE];
	TCHAR Dir[_MAX_DIR];
	TCHAR FileTitle[_MAX_FNAME];
	TCHAR FileExt[_MAX_EXT];
	GetModuleFileName(NULL,FilePath,MAX_PATH);
	_splitpath_s(FilePath,Drive,Dir,FileTitle,FileExt);
	sprintf( FilePath, "%s%s", Drive,Dir );
	SetCurrentDirectory(FilePath);
	
	CHECK_APP_NAME();
	DeleteFile(NEW_LAUNCHER_OLD_TEMP_NAME); 
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CNewDlgDlg dlg;
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

BOOL CNewDlgApp::FindInstance()
{
	TCHAR szCurName[1024];
	GetModuleFileName( NULL,szCurName,MAX_PATH );	
	std::string name=szCurName;
	name=GetFileName(name);
	if(strcmp(name.c_str(),_T("launcher.exe"))!=0)
	{
		//如果不叫launcher可能是更新后的本身exe.所以掉过唯一性
		return TRUE;
	}

	CWnd *pWndPrev, *pWndChild;

	// Determine if another window with our class name and Window title exists...
	// The title "Instance " is set up latter, in the InitDialog function.
	if (pWndPrev = CWnd::FindWindow(NULL,"launcher"))
	{
		pWndChild = pWndPrev->GetLastActivePopup();
		// if so, does it have any popups?
		if (pWndPrev->IsIconic())
			pWndPrev->ShowWindow(SW_RESTORE);
		// If iconic, restore the main window
		pWndChild->SetForegroundWindow();
		// Bring the window to the foreground
		return FALSE;
	}
	else
		return TRUE; // First instance. Proceed as normal.
}
