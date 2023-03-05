// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "GameBot.h"
#include "OptionDlg.h"
#include "MainFrm.h"
#include "PlatFormDialog.h"
#include "LoginInfo.h"
#include "LogFileObjectName.h"
#include "GameBotView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4201)
#pragma warning(disable:4702)
// CMainFrame
CMainFrame* theMainFrame;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_COMMAND(ID_APP_LOG, &CMainFrame::OnAppLog)
    ON_COMMAND(ID_APP_OPTION, &CMainFrame::OnAppOption)
    ON_COMMAND(ID_APP_GMOPERATION, &CMainFrame::OnAppGMOption)
	ON_COMMAND(ID_BUTTON_LOGIN, &CMainFrame::OnAppLogin)
    ON_COMMAND(ID_APP_GMOPERATION, &CMainFrame::OnPlatform)	
	ON_COMMAND(ID_BUTTON_ADDFrm, &CMainFrame::OnShowAddFrm)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
    theMainFrame = this;
	m_pLoginInfo = NULL;
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    theMainFrame->m_wndStatusBar.SetPaneText(0, _T("正在加载资源，请稍等..."));
    ShowWindow(SW_MAXIMIZE);
	return 0;
}

void CMainFrame::OnClose()
{
    theApp.gBotApplication.SetAppState( BotApplication::EAppStateType_Exist );
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序




BOOL CMainFrame::DestroyWindow()
{
    // TODO: 在此添加专用代码和/或调用基类
    theMainFrame = NULL;
    return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnAppLog()
{
    theApp.NetworkMsgLog();
    // TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnAppGMOption()
{
    PlatFormDialog Dialog;
    Dialog.DoModal();
}

void CMainFrame::OnShowAddFrm()
{
	if (GettheMainView())
	{
		GettheMainView()->m_frmAdd.ShowWindow(SW_SHOW);
	}
}

void CMainFrame::OnAppOption()
{
    COptionDlg option;
    option.DoModal();
    // TODO: 在此添加命令处理程序代码
}

void CMainFrame::OnPlatform()
{
	
}

void CMainFrame::OnAppLogin()
{
#ifdef HIDE_BOT_INFO
	//return;
#endif

	//登录游戏
	if (m_pLoginInfo == NULL)
	{
		m_pLoginInfo = new LoginInfo();
		if (m_pLoginInfo != NULL)
		{
			m_pLoginInfo->Create(IDD_DIALOG_LOGIN, this);
			m_pLoginInfo->InitInformation();
		}
	}
	
	if (m_pLoginInfo != NULL)
	{
		m_pLoginInfo->ShowWindow(SW_NORMAL);
		m_pLoginInfo->SetForegroundWindow();
	}
}