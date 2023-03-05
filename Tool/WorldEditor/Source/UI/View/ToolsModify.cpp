/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolsModify.cpp
* Date: 	05/29/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "ToolsModify.h"

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CToolsModify, CWnd)
CToolsModify::CToolsModify()
{

}

CToolsModify::~CToolsModify()
{
}


BEGIN_MESSAGE_MAP(CToolsModify, CWnd)
	//{{AFX_MSG_MAP(CToolsModify)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CToolsModify::SetActive()
{
	
}

void CToolsModify::OnInitialUpdate()
{
	VERIFY( m_wndToolBar.CreateToolBar(WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this) );
	VERIFY( m_wndToolBar.LoadToolBar( IDR_TOOLBAR_ATOM ) );

	m_wndToolBar.SetButtonSize(CSize(23, 23));

}

/////////////////////////////////////////////////////////////////////////////
// CExplorerView message handlers
void CToolsModify::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CSize sz(0);
	if (m_wndToolBar.GetSafeHwnd())
	{
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow( 0, 0, cx, sz.cy );
		m_wndToolBar.Invalidate(FALSE);
	}
}

BOOL CToolsModify::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CToolsModify::OnSetFocus(CWnd* pOldWnd)
{

}



