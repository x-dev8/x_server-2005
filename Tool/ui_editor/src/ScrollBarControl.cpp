#include "StdAfx.h"
#include "scrollbarcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"
#include "UIObjectDlg.h"

CScrollBarControl::CScrollBarControl(void)
{
	m_nType = Type_ScrollBar;

	m_nWidth = 12;
	m_nHeight = 70;

	m_btnUp.m_nWidth = m_nWidth;
	m_btnUp.m_nHeight = m_nWidth;

	m_btnDown.m_nWidth = m_nWidth;
	m_btnDown.m_nHeight = m_nWidth;

	m_btnBar.m_nWidth = m_nWidth;
	m_btnBar.m_nHeight = m_nWidth;

	m_strID.Format( "ID_SCROLLBAR_%d", rand() );

	m_colComments = RGB(128,0,0);

	m_ProScrollBar[Item_ScrollBar_Comments_Up].SetItem( PIT_COMMENTS, "<ScrollBarUp>", &m_colComments );
	m_ProScrollBar[Item_ScrollBar_Comments_Down].SetItem( PIT_COMMENTS, "<ScrollBarDown>", &m_colComments );
	m_ProScrollBar[Item_ScrollBar_Comments_Bar].SetItem( PIT_COMMENTS, "<ScrollBarBar>", &m_colComments );
}

CScrollBarControl::~CScrollBarControl(void)
{
}


void CScrollBarControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );
	
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	m_btnUp.Render( pDC, rcScrollBar );
	m_btnDown.Render( pDC, rcScrollBar );
	m_btnBar.Render( pDC, rcScrollBar );
}

bool CScrollBarControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );

	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	if( m_btnUp.MouseMove( point, rcScrollBar ) == true )
		return true;
	else if( m_btnDown.MouseMove( point, rcScrollBar ) == true )
		return true;
	else if ( m_btnBar.MouseMove( point, rcScrollBar ) == true )
		return true;

	return CBaseControl::MouseMove( point, pFatherRc );
}

void CScrollBarControl::OnSize()
{
	if ( m_nHeight < 3*m_nWidth )
	{
		m_nHeight = 3*m_nWidth;
	}

	//m_btnUp.m_nWidth = m_nWidth;
	//m_btnUp.m_nHeight = m_nWidth;

	m_btnDown.m_nOffsetY = m_nHeight-m_nWidth;
	//m_btnDown.m_nWidth = m_nWidth;
	//m_btnDown.m_nHeight = m_nWidth;

	m_btnBar.m_nOffsetY = m_nHeight/2-m_nWidth/2;
	//m_btnBar.m_nWidth = m_nWidth;
	//m_btnBar.m_nHeight = m_nWidth;
}

void CScrollBarControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();

	thePropertyDlg.AddItem( &m_ProScrollBar[Item_ScrollBar_Comments_Up] );
	m_btnUp.AddToPropertyDlg();
	thePropertyDlg.AddItem( &m_ProScrollBar[Item_ScrollBar_Comments_Down] );
	m_btnDown.AddToPropertyDlg();
	thePropertyDlg.AddItem( &m_ProScrollBar[Item_ScrollBar_Comments_Bar] );
	m_btnBar.AddToPropertyDlg();
}

void CScrollBarControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();

	m_btnUp.AddToUIObjectDlg();
	m_btnDown.AddToUIObjectDlg();
	m_btnBar.AddToUIObjectDlg();
}

bool CScrollBarControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_ScrollBarData *pScrollBar = (S_ScrollBarData*)pData;

	m_btnUp.SetData( &pScrollBar->m_stUp );
	m_btnDown.SetData( &pScrollBar->m_stDown );
	m_btnBar.SetData( &pScrollBar->m_stBar );

	return CBaseControl::SetData( pData );
}

bool CScrollBarControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_ScrollBarData *pScrollBar = (S_ScrollBarData*)pData;

	m_btnUp.GetData( &pScrollBar->m_stUp );
	m_btnDown.GetData( &pScrollBar->m_stDown );
	m_btnBar.GetData( &pScrollBar->m_stBar );
	
	return CBaseControl::GetData( pData );
}

