// Editor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EventEditor.h"
#include "MainFrm.h"

#include "EventEditorDoc.h"
#include "EventEditorView.h"

#include "EventTimeTable.h"
#include "NpcInfo.h"
#include "MapConfig.h"
#include "ItemDetail.h"
#include <time.h>
#include "LogFileObjectName.h"

#include "MiniDumper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorApp

BEGIN_MESSAGE_MAP(CEditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CEditorApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CEditorApp construction

CEditorApp::CEditorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
#ifndef _DEBUG
    //MiniDumper dumper("EventEdit");
#else 
#endif
}


// The one and only CEditorApp object

CEditorApp theApp;


// CEditorApp initialization

BOOL CEditorApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
#ifdef _DEBUG
	MessageBox(NULL,"debug","debug",MB_OK);
#endif
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);    

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views

    //try
    //{
    //    LOG_CONFIGURE( "..\\log4cpp-Event.config" ); 
    //}
    //catch(ConfigureException &)
    //{
    //    MessageBox(NULL,"Load ..\\Log4cpp-Event.config Error!","Error",MB_ICONERROR|MB_OK);
    //    return false;
    //}

    if (FALSE == GettheItemDetail().LoadBinFile("..\\Data\\Config\\Data.config"))
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load ..\\Data\\Config\\Data.config Error!");
        return false;
    }

    if (theNpcInfo.LoadConfig("..\\Data\\Config\\Npc.config") != File_Success)
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load ..\\Data\\Config\\Npc.config Error!");
        return false;
    }

    if (!theMapConfig.LoadMapConfig("..\\Data\\Config\\Map.config"))
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load ..\\Data\\Config\\Npc.config Error!");
        return false;
    }

    tm *CurTime;
    time_t _Time;
    ::time(&_Time);
    CurTime = localtime(&_Time);
    if ( !theEventManager.Load("..\\Data\\Config\\Event.config",*CurTime) )
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load ..\\Data\\Config\\Event.config Error!");
        MessageBox(NULL,"Load Event.config Have Error!Please Check Event.config File","Warning",MB_ICONERROR|MB_OK);
    }

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
    CString strVersion;
    strVersion.Format("Event编辑器 %s", ApplicationConfig::Instance().GetFullVersion());
    m_pMainWnd->SetWindowText(strVersion);
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
    



	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}
BOOL CAboutDlg::OnInitDialog()
{
    CWnd* pWindow = GetDlgItem(IDC_STATIC_SHUOMING);
    if (NULL != pWindow)
    {
        pWindow->SetWindowText("使用说明:\r\nALT+S\t保存修改\r\nALT+A\t确认修改Even,修改到内存但是没有保存需要使用ALT+S保存\r\nALT+D\t删除当前所选\r\n增加只需要双击对应的窗口\r\n");
        pWindow->UpdateData(FALSE);
    }
    return CDialog::OnInitDialog();
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CEditorApp message handlers

