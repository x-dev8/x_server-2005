#include "StdAfx.h"
#include "listexcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"

CListExControl::CListExControl(void)
{
	m_nType = Type_ListEx;

	m_nWidth = 132;
	m_nHeight = 160;
	m_strID.Format( "ID_LISTEX_%d", rand() );

	m_colSelBar = RGB(255,0,0);
	m_nItemHeight = 32;
	m_nItemWidth = 100;
	m_nOffsetWidth = 2;
	m_nOffsetHeight = 2;
	m_nMaxHeightCount = 10;
	m_colComments = RGB(128,0,0);
	m_bCanbePick = false;

	m_ProListEx[Item_ListEx_Comments_State].SetItem( PIT_COMMENTS, "<ListEx>", NULL );
	m_ProListEx[Item_ListEx_ItemHeight].SetItem( PIT_NUM, "ItemHeight", &m_nItemHeight );
	m_ProListEx[Item_ListEx_ItemWidth].SetItem( PIT_NUM, "ItemWidth", &m_nItemWidth );
	m_ProListEx[Item_ListEx_OffsetWidth].SetItem( PIT_NUM, "OffsetWidth", &m_nOffsetWidth );
	m_ProListEx[Item_ListEx_OffsetHeight].SetItem( PIT_NUM, "OffsetHeight", &m_nOffsetHeight );
	m_ProListEx[Item_ListEx_MaxHeightCount].SetItem( PIT_NUM, "MaxHeightCount", &m_nMaxHeightCount );
	m_ProListEx[Item_ListEx_SelBarColor].SetItem( PIT_COLOR, "SelBarColor", &m_colSelBar );
	m_ProListEx[Item_ListEx_CanbePick].SetItem( PIT_BOOL, "CanbePick", &m_bCanbePick );
	m_ProListEx[Item_ListEx_ScrollBar].SetItem( PIT_COMMENTS, "<ScrollBar>", &m_colComments );

	m_ProListEx[Item_ListEx_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProListEx[Item_ListEx_DrawInfo].SetItem( PIT_EDIT, "DrawInfo", &m_DrawInfoName );
}

CListExControl::~CListExControl(void)
{
}

void CListExControl::OnSize()
{
	if ( (m_nWidth+m_nOffsetWidth)%(m_nItemWidth+m_nOffsetWidth) != 0 )
	{
		m_nWidth = m_nWidth/(m_nItemWidth+m_nOffsetWidth)*(m_nItemWidth+m_nOffsetWidth)-m_nOffsetWidth;
	}
	if ( (m_nHeight+m_nOffsetHeight)%(m_nItemHeight+m_nOffsetHeight) != 0 )
	{
		m_nHeight = m_nHeight/(m_nItemHeight+m_nOffsetHeight)*(m_nItemHeight+m_nOffsetHeight)-m_nOffsetHeight;
	}

	m_ScrollBar.m_nOffsetX = m_nWidth;
	m_ScrollBar.m_nHeight = m_nHeight;
	m_ScrollBar.OnSize();
}

void CListExControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );

	CBrush	brush( RGB(128,128,128) );
	CBrush	brush1( RGB(128,0,0) );
	RECT rcFrame;
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	int nW = (m_nWidth+m_nOffsetWidth)/(m_nItemWidth+m_nOffsetWidth);
	int nH = (m_nHeight+m_nOffsetHeight)/(m_nItemHeight+m_nOffsetHeight);
	for( int h=0; h<nH; h++ )
	{
		for( int w=0; w<nW; w++ )
		{
			rcFrame.left = nX + w*(m_nItemWidth+m_nOffsetWidth);
			rcFrame.top = nY + h*(m_nItemHeight+m_nOffsetHeight);
			rcFrame.right = rcFrame.left + m_nItemHeight;
			rcFrame.bottom = rcFrame.top + m_nItemHeight;
			pDC->FrameRect( &rcFrame, &brush );

			rcFrame.left = nX + w*(m_nItemWidth+m_nOffsetWidth)+m_nItemHeight;
			rcFrame.top = nY + h*(m_nItemHeight+m_nOffsetHeight);
			rcFrame.right = rcFrame.left + m_nItemWidth-m_nItemHeight;
			rcFrame.bottom = rcFrame.top + m_nItemHeight;
			pDC->FrameRect( &rcFrame, &brush1 );
		}
	}

	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	m_ScrollBar.Render( pDC, rcScrollBar );
}

bool CListExControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );

	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	if( m_ScrollBar.MouseMove( point, rcScrollBar ) == true )
		return true;

	return CBaseControl::MouseMove( point, pFatherRc );
}

void CListExControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_ListEx_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProListEx[n] );
	}
	m_ScrollBar.AddToPropertyDlg();
}

void CListExControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();
	m_ScrollBar.AddToUIObjectDlg();
}

bool CListExControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_ListExData *pListExData = (S_ListExData*)pData;

	m_ScrollBar.SetData( &pListExData->m_stScrollBar );
	m_colSelBar = pListExData->m_colSelBar;
	m_nItemHeight = pListExData->m_nItemHeight;
	m_nItemWidth = pListExData->m_nItemWidth;
	m_nOffsetWidth = pListExData->m_nOffsetWidth;
	m_nOffsetHeight = pListExData->m_nOffsetHeight;
	m_nMaxHeightCount = pListExData->m_nMaxHeightCount;
	m_bCanbePick = pListExData->m_bCanbePick;

	return CBaseControl::SetData( pData );
}

bool CListExControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_ListExData *pListExData = (S_ListExData*)pData;

	m_ScrollBar.GetData( &pListExData->m_stScrollBar );
	pListExData->m_colSelBar = m_colSelBar;
	pListExData->m_nItemHeight = m_nItemHeight;
	pListExData->m_nItemWidth = m_nItemWidth;
	pListExData->m_nOffsetWidth = m_nOffsetWidth;
	pListExData->m_nOffsetHeight = m_nOffsetHeight;
	pListExData->m_nMaxHeightCount = m_nMaxHeightCount;
	pListExData->m_bCanbePick = m_bCanbePick == TRUE;

	return CBaseControl::GetData( pData );
}

void CListExControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_ListEx_DrawInfo, m_DrawInfoName.GetBuffer() );
}