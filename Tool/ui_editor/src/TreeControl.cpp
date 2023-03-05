//#include "StdAfx.h"
//#include "treecontrol.h"
//#include <assert.h>
//#include "PropertyDlg.h"
//
//CTreeControl::CTreeControl(void)
//{
//	m_nType = Type_Tree;
//
//	m_nWidth = 140;
//	m_nHeight = 160;
//	m_strID.Format( "ID_TREE_%d", rand() );
//
//	m_colComments = RGB(128,0,0);
//	m_colSelBar = RGB(0,255,0);
//	m_nItemHeight = 14;
//
//	m_ProList[Item_Tree_Comments_State].SetItem( PIT_COMMENTS, "<Tree>", NULL );
//	m_ProList[Item_Tree_OpenPic].SetItem( PIT_DIALOG, "OpenPic", &m_OpenPicDlg );
//	m_ProList[Item_Tree_ClosePic].SetItem( PIT_DIALOG, "ClosePic", &m_ClosePicDlg );
//	m_ProList[Item_Tree_ItemPic].SetItem( PIT_DIALOG, "ItemPic", &m_ItemPicDlg );
//
//	m_ProList[Item_Tree_ItemHeight].SetItem( PIT_NUM, "ItemHeight", &m_nItemHeight );
//	m_ProList[Item_Tree_SelBarColor].SetItem( PIT_COLOR, "SelBarColor", &m_colSelBar );
//	m_ProList[Item_Tree_ScrollBar].SetItem( PIT_COMMENTS, "<ScrollBar>", &m_colComments );
//
//	m_ProList[Item_Tree_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
//	m_ProList[Item_Tree_SelectChange].SetItem( PIT_EDIT, "SelectChange", &m_SelectChangeName );
//	m_ProList[Item_Tree_LDBClick].SetItem( PIT_EDIT, "LDBClick", &m_LDBClickName );
//	m_ProList[Item_Tree_LRBClick].SetItem( PIT_EDIT, "RBClick", &m_LRBClickName );
//	m_ProList[Item_Tree_ShiftRBClick].SetItem( PIT_EDIT, "ShiftRBClick", &m_ShiftRBClickName );
//	m_ProList[Item_Tree_ShiftLBClick].SetItem( PIT_EDIT, "ShiftLBClick", &m_ShiftLBClickName );
//}
//
//CTreeControl::~CTreeControl(void)
//{
//}
//
//void CTreeControl::AddToPropertyDlg()
//{
//	CBaseControl::AddToPropertyDlg();
//	for( int n=0; n<Item_Tree_Max; n++ )
//	{
//		thePropertyDlg.AddItem( &m_ProList[n] );
//	}
//	m_ScrollBar.AddToPropertyDlg();
//}
//
//void CTreeControl::AddToUIObjectDlg()
//{
//	CBaseControl::AddToUIObjectDlg();
//	m_ScrollBar.AddToUIObjectDlg();
//}
//
//bool CTreeControl::SetData( const S_BaseData* /*[In]*/pData )
//{
//	assert( pData );
//	S_TreeData *pListData = (S_TreeData*)pData;
//
//	m_ScrollBar.SetData( &pListData->m_stScrollBar );
//	m_nItemHeight = pListData->m_nItemHeight;
//	m_colSelBar = pListData->m_colSelBar;
//
//	m_OpenPicDlg.SetPicStruct( &pListData->m_stOpenPic );
//	m_ClosePicDlg.SetPicStruct( &pListData->m_stClosePic );
//	m_ItemPicDlg.SetPicStruct( &pListData->m_stItemPic );
//
//	return CBaseControl::SetData( pData );
//}
//
//bool CTreeControl::GetData( S_BaseData* /*[Out]*/pData )
//{
//	assert( pData );
//	S_TreeData *pListData = (S_TreeData*)pData;
//
//	m_ScrollBar.GetData( &pListData->m_stScrollBar );
//	pListData->m_nItemHeight = m_nItemHeight;
//	pListData->m_colSelBar = m_colSelBar;
//
//	pListData->m_stOpenPic.SetPicStruct(m_OpenPicDlg.GetCurSelPicName(),
//		&m_OpenPicDlg.GetFrameRect(),
//		&m_OpenPicDlg.GetClientRect() );
//	pListData->m_stClosePic.SetPicStruct(m_ClosePicDlg.GetCurSelPicName(),
//		&m_ClosePicDlg.GetFrameRect(),
//		&m_ClosePicDlg.GetClientRect() );
//	pListData->m_stItemPic.SetPicStruct(m_ItemPicDlg.GetCurSelPicName(),
//		&m_ItemPicDlg.GetFrameRect(),
//		&m_ItemPicDlg.GetClientRect() );
//
//	return CBaseControl::GetData( pData );
//}
//
//void CTreeControl::OnSize()
//{
//	m_nHeight = m_nHeight/m_nItemHeight*m_nItemHeight;
//
//	m_ScrollBar.m_nOffsetX = m_nWidth/* - m_ScrollBar.m_nWidth*/;
//	m_ScrollBar.m_nHeight = m_nHeight;
//	m_ScrollBar.OnSize();
//}
//
//void CTreeControl::Render( CDC* pDC, const RECT* pFatherRc )
//{
//	CBaseControl::Render( pDC, pFatherRc );
//
//	CBrush	brush( RGB(128,128,128) );
//	RECT rcFrame;
//	int nX,nY;
//	GetPos( &nX, &nY, pFatherRc );
//	int nH = m_nHeight/m_nItemHeight;
//	for( int h=0; h<nH; h++ )
//	{
//		rcFrame.left = nX;
//		rcFrame.top = nY + h*m_nItemHeight;
//		rcFrame.right = rcFrame.left + m_nWidth/* - m_ScrollBar.m_nWidth*/;
//		rcFrame.bottom = rcFrame.top + m_nItemHeight;
//		pDC->FrameRect( &rcFrame, &brush );
//	}
//
//	CRect rcScrollBar;
//	rcScrollBar.left = nX;
//	rcScrollBar.top = nY;
//	rcScrollBar.right = rcScrollBar.left + m_nWidth;
//	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
//	m_ScrollBar.Render( pDC, rcScrollBar );
//}
//
//bool CTreeControl::MouseMove( const POINT point, const RECT* pFatherRc )
//{
//	int nX,nY;
//	GetPos( &nX, &nY, pFatherRc );
//
//	CRect rcScrollBar;
//	rcScrollBar.left = nX;
//	rcScrollBar.top = nY;
//	rcScrollBar.right = rcScrollBar.left + m_nWidth;
//	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
//	if( m_ScrollBar.MouseMove( point, rcScrollBar ) == true )
//		return true;
//
//	return CBaseControl::MouseMove( point, pFatherRc );
//}
//void CTreeControl::GetData_Event( int index )
//{
//	stUIData.SetEventFunName( index, EET_Tree_SelectChange, m_SelectChangeName.GetBuffer() );
//	stUIData.SetEventFunName( index, EET_Tree_LDBClick, m_LDBClickName.GetBuffer() );
//	stUIData.SetEventFunName( index, EET_Tree_LRBClick, m_LRBClickName.GetBuffer() );
//	stUIData.SetEventFunName( index, EET_Tree_ShiftRBClick, m_ShiftRBClickName.GetBuffer() );
//	stUIData.SetEventFunName( index, EET_Tree_ShiftLBClick, m_ShiftLBClickName.GetBuffer() );
//}