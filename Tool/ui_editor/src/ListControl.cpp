#include "StdAfx.h"
#include "listcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"

CListControl::CListControl(void)
{
	m_nType = Type_List;

	m_nWidth = 140;
	m_nHeight = 160;
	m_strID.Format( "ID_LIST_%d", rand() );

	m_colComments = RGB(128,0,0);
	m_colSelBar = RGB(0,255,0);
	m_nItemHeight = 14;

	m_ProList[Item_List_Comments_State].SetItem( PIT_COMMENTS, "<List>", NULL );
	m_ProList[Item_List_ItemHeight].SetItem( PIT_NUM, "ItemHeight", &m_nItemHeight );
	m_ProList[Item_List_SelBarColor].SetItem( PIT_COLOR, "SelBarColor", &m_colSelBar );
	m_ProList[Item_List_ScrollBar].SetItem( PIT_COMMENTS, "<ScrollBar>", &m_colComments );

	m_ProList[Item_List_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProList[Item_List_SelectChange].SetItem( PIT_EDIT, "SelectChange", &m_SelectChangeName );
	m_ProList[Item_List_LDBClick].SetItem( PIT_EDIT, "LDBClick", &m_LDBClickName );
	m_ProList[Item_List_LRBClick].SetItem( PIT_EDIT, "RBClick", &m_LRBClickName );
	m_ProList[Item_List_ShiftRBClick].SetItem( PIT_EDIT, "ShiftRBClick", &m_ShiftRBClickName );
	m_ProList[Item_List_ShiftLBClick].SetItem( PIT_EDIT, "ShiftLBClick", &m_ShiftLBClickName );
	m_ProList[Item_List_HyberClick].SetItem( PIT_EDIT, "HyberClick", &m_HyberClickName );
	m_ProList[Item_List_HyberRBClick].SetItem( PIT_EDIT, "HyberRBClick", &m_HyberRBClickName );
	m_ProList[Item_List_HyberItemClick].SetItem( PIT_EDIT, "HyberItemClick", &m_HyberItemClickName );
}

CListControl::~CListControl(void)
{
}

void CListControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_List_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProList[n] );
	}
	m_ScrollBar.AddToPropertyDlg();
}

void CListControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();
	m_ScrollBar.AddToUIObjectDlg();
}

bool CListControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_ListData *pListData = (S_ListData*)pData;

	m_ScrollBar.SetData( &pListData->m_stScrollBar );
	m_nItemHeight = pListData->m_nItemHeight;
	m_colSelBar = pListData->m_colSelBar;

	return CBaseControl::SetData( pData );
}

bool CListControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_ListData *pListData = (S_ListData*)pData;

	m_ScrollBar.GetData( &pListData->m_stScrollBar );
	pListData->m_nItemHeight = m_nItemHeight;
	pListData->m_colSelBar = m_colSelBar;

	return CBaseControl::GetData( pData );
}

void CListControl::OnSize()
{
	m_nHeight = m_nHeight/m_nItemHeight*m_nItemHeight;

	m_ScrollBar.m_nOffsetX = m_nWidth/* - m_ScrollBar.m_nWidth*/;
	m_ScrollBar.m_nHeight = m_nHeight;
	m_ScrollBar.OnSize();
}

void CListControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );

	CBrush	brush( RGB(128,128,128) );
	RECT rcFrame;
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	int nH = m_nHeight/m_nItemHeight;
	for( int h=0; h<nH; h++ )
	{
		rcFrame.left = nX;
		rcFrame.top = nY + h*m_nItemHeight;
		rcFrame.right = rcFrame.left + m_nWidth/* - m_ScrollBar.m_nWidth*/;
		rcFrame.bottom = rcFrame.top + m_nItemHeight;
		pDC->FrameRect( &rcFrame, &brush );
	}

	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	m_ScrollBar.Render( pDC, rcScrollBar );
}

bool CListControl::MouseMove( const POINT point, const RECT* pFatherRc )
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
void CListControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_List_SelectChange, m_SelectChangeName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_LDBClick, m_LDBClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_LRBClick, m_LRBClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_ShiftRBClick, m_ShiftRBClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_ShiftLBClick, m_ShiftLBClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_HyberClick, m_HyberClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_HyberRBClick, m_HyberRBClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_List_HyberItemClick, m_HyberItemClickName.GetBuffer() );
}