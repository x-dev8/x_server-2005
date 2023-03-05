//#include "..\controlcenter\mainfrm.h"
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "UIEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
IMPLEMENT_MENUXP(CMainFrame, CFrameWnd);

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_PROPERTY, OnViewProperty)
	ON_COMMAND(ID_VIEW_OBJECT, OnViewObject)
	ON_MENUXP_MESSAGES()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/销毁

CMainFrame::CMainFrame()
{
	// TODO：在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CMenuXP::SetXPLookNFeel (this);
	
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

//	//===SkinMagic====
////	VERIFY( 1 == SetDialogSkin( "Dialog" ) );
//	VERIFY( 1 == SetWindowSkin( m_hWnd ,  _T("MainFrame") ) );
//	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() & ~CBRS_TOOLTIPS );
//	VERIFY( 1 == SetControlTooltip( m_wndToolBar.m_hWnd , _T("ToolBar") ) );
//	//===SkinMagic====

	OnViewProperty();
	OnViewObject();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

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


void CMainFrame::OnViewProperty()
{
	// TODO: 在此添加命令处理程序代码
	m_wndPropertyBar.Show( this, &thePropertyDlg, CPropertyDlg::IDD, "Property", CBRS_RIGHT );
}

void CMainFrame::OnViewObject()
{
	// TODO: 在此添加命令处理程序代码
	m_wndObjectBar.Show( this, &theUIObjectDlg, CUIObjectDlg::IDD, "Object", CBRS_LEFT );
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
	if ( !CFrameWnd::LoadFrame (nIDResource, dwDefaultStyle, pParentWnd, pContext) )
	{
		return false;
	}
	CMenuXP::UpdateMenuBar (this);
	return true;
}

