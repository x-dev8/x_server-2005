// CToolsTabView.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// ?998-2005 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/BaseTool.h"

#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/Custom/TextureNavigationWnd.h"
#include "ui/ToolsWnd/ToolDoodadDlg.h"
#include "ui/ToolsWnd/ToolLiquidDlg.h"
#include "ui/ToolsWnd/MonsterQuadDlg.h"
#include "ui/ToolsWnd/ToolTransportDlg.h"
#include "ui/ToolsWnd/ToolFlyRouteDlg.h"
#include "ui/ToolsScene/ToolClickToAddDlg.h"
#include "ui/ToolsWnd/ToolTerrain.h"
#include "ui/ToolsWnd/ToolLayer.h"
#include "ui/ToolsWnd/ToolModel.h"
#include "ui/ToolsScene/ToolWorld.h"
#include "ui/ToolsScene/ToolEnvironment.h"
#include "ui/ToolsScene/ToolWorldLight.h"
#include "ui/ToolsScene/ToolWorldFog.h"
#include "ui/ToolsScene/ToolZoneDlg.h"

#include "ui/View/ToolsScene.h"
#include "ui/View/ToolsCreate.h"
#include "ui/View/ToolsModify.h"
#include "ToolsTabView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolsTabView
IMPLEMENT_DYNCREATE(CToolsTabView, CView)

CToolsTabView::CToolsTabView()
{
	m_curWndType = emWT_Create;
}

CToolsTabView::~CToolsTabView()
{
}


BEGIN_MESSAGE_MAP(CToolsTabView, CView)
	//{{AFX_MSG_MAP(CToolsTabView)
	ON_WM_SIZE()
	ON_COMMAND( ID_TOOLS_CREATE, OnCommandCreate )
	ON_COMMAND( ID_TOOLS_SCENE, OnCommandScene )

	ON_UPDATE_COMMAND_UI(ID_TOOLS_CREATE, OnUpdateCommandCreate)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SCENE, OnUpdateCommandScene)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CToolsTabView::SetWnd( emWndType wndType )
{
	if( m_curWndType == wndType )
		return;

	m_wndToolCreate.ShowWindow( SW_HIDE );
	m_wndToolModify.ShowWindow( SW_HIDE );
	m_wndToolScene.ShowWindow( SW_HIDE );

	m_curWndType = wndType;

	switch(	wndType )
	{
	case emWT_Create:
		m_wndToolCreate.SetActive();
		m_wndToolCreate.ShowWindow( SW_SHOW );
		break;
	case emWT_Scene:
		m_wndToolScene.SetActive();
		m_wndToolScene.ShowWindow( SW_SHOW );
		break;
	default:
		Trace( "Error wndType! \n" );
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolsTabView drawing
void CToolsTabView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CToolsTabView diagnostics
#ifdef _DEBUG
void CToolsTabView::AssertValid() const
{
	CView::AssertValid();
}

void CToolsTabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolsTabView message handlers
void CToolsTabView::OnInitialUpdate()
{
	VERIFY( m_wndToolBar.CreateToolBar(WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this) );
	VERIFY( m_wndToolBar.LoadToolBar( IDR_TOOLS_HEAD ) );

	CWorldEditDoc::GetActiveMapDoc()->SetToolView( this );

	m_wndToolBar.SetButtonSize(CSize(23, 23));
	
	if (!m_wndToolScene.Create( _T("STATIC"), NULL, WS_CHILD, CRect(0, 0, 0, 0), this, 0 ) )
	{
		TRACE0( "Unable to create tool scene.\n" );
		return;
	}
	m_wndToolScene.OnInitialUpdate();

	if (!m_wndToolCreate.Create( _T("STATIC"), NULL, WS_CHILD, CRect(0, 0, 0, 0), this, 0 ) )
	{
		TRACE0( "Unable to create tool create.\n" );
		return;
	}
	m_wndToolCreate.OnInitialUpdate();

	if (!m_wndToolModify.Create( _T("STATIC"), NULL, WS_CHILD, CRect(0, 0, 0, 0), this, 0 ) )
	{
		TRACE0( "Unable to create tool modify.\n" );
		return;
	}
	m_wndToolModify.OnInitialUpdate();


	m_wndToolCreate.ShowWindow( SW_SHOW ); 
	

	CView::OnInitialUpdate();
}

void CToolsTabView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CSize sz(0);
	if ( m_wndToolBar.GetSafeHwnd() ) {
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow( 0, 0, cx, sz.cy );
		m_wndToolBar.Invalidate(FALSE);
	}
	if ( m_wndToolCreate.GetSafeHwnd() ) {
		m_wndToolCreate.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	}
	if ( m_wndToolModify.GetSafeHwnd() ) {
		m_wndToolModify.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	}
	if ( m_wndToolScene.GetSafeHwnd() ) {
		m_wndToolScene.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	}
}

void CToolsTabView::OnCommandCreate()
{
	SetWnd( emWT_Create );
}

void CToolsTabView::OnCommandScene()
{
	SetWnd( emWT_Scene );
}

void CToolsTabView::OnUpdateCommandCreate(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_curWndType==emWT_Create)?1:0 );
}

void CToolsTabView::OnUpdateCommandScene(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_curWndType==emWT_Scene)?1:0 );
}

BOOL CToolsTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

void CToolsTabView::Reset()
{
	m_wndToolCreate.Reset();
}