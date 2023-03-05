/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	TextureWindow.cpp
* Date: 	03/14/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "TextureWindow.h"

////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTextureWindow, CWnd)
	//{{AFX_MSG_MAP(CTextureWindow)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
CTextureWindow::CTextureWindow()
{
	m_totalX		= 0;
	m_totalY		= 0;
	m_displaySize	= 0;

}

CTextureWindow::~CTextureWindow()
{

}

void CTextureWindow::Create( CWnd *parentWnd, RECT& rect )
{

}

void CTextureWindow::EnableUpdate( bool bEnable )
{

}

void CTextureWindow::UpdateScrollSizes()
{

}

void CTextureWindow::HighlightCurTexture( CDC *pDC )
{

}

void CTextureWindow::SetDisplaySize( int iSize )
{

}

void CTextureWindow::SelectTexture( LPCTSTR pszTexture, BOOL bAllowRedraw )
{

}

void CTextureWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect clientrect;
	GetClientRect(clientrect);

	dc.SetWindowOrg( GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT) );
	
	
}

void CTextureWindow::OnSize(UINT nType, int cx, int cy)
{

}

void CTextureWindow::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CTextureWindow::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

}

void CTextureWindow::OnLButtonDown(UINT nFlags, CPoint point)
{

}

void CTextureWindow::OnLButtonDblClk(UINT nFlags, CPoint point)
{

}

void CTextureWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CTextureWindow::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

BOOL CTextureWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{

	return TRUE;
}



