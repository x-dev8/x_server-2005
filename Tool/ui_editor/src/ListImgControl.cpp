#include "StdAfx.h"
#include "listimgcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"

CListImgControl::CListImgControl(void)
{
	m_nType = Type_ListImg;

	m_nWidth = 140;
	m_nHeight = 160;
	m_strID.Format( "ID_LISTIMG_%d", rand() );

	m_nIconSize = 32;
	m_nOffsetWidth = 2;
	m_nOffsetHeight = 2;
	m_nMaxHeightCount = 10;
	m_bCanbePick = TRUE;
	m_bShowSelFrame = TRUE;
	m_colSelFrame = RGB(255,0,0);
	m_colComments = RGB(128,0,0);

	m_ProListImg[Item_ListImg_Comments_State].SetItem( PIT_COMMENTS, "<ListImg>", NULL );
	m_ProListImg[Item_ListImg_IconSize].SetItem( PIT_NUM, "IconSize", &m_nIconSize );
	m_ProListImg[Item_ListImg_OffsetWidth].SetItem( PIT_NUM, "OffsetWidth", &m_nOffsetWidth );
	m_ProListImg[Item_ListImg_OffsetHeight].SetItem( PIT_NUM, "OffsetHeight", &m_nOffsetHeight );
	m_ProListImg[Item_ListImg_MaxHeightCount].SetItem( PIT_NUM, "MaxHeightCount", &m_nMaxHeightCount );
	m_ProListImg[Item_ListImg_CanbePick].SetItem( PIT_BOOL, "CanbePick", &m_bCanbePick );
	m_ProListImg[Item_ListImg_ShowSelFrame].SetItem( PIT_BOOL, "ShowSelFrame", &m_bShowSelFrame );
	m_ProListImg[Item_ListImg_ColSelFrame].SetItem( PIT_COLOR, "SelFrameColor", &m_colSelFrame );
	m_ProListImg[Item_ListImg_ScrollBar].SetItem( PIT_COMMENTS, "<ScrollBar>", &m_colComments );
}

CListImgControl::~CListImgControl(void)
{
}

void CListImgControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_ListImg_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProListImg[n] );
	}
	m_ScrollBar.AddToPropertyDlg();
}

void CListImgControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();
	m_ScrollBar.AddToUIObjectDlg();
}

bool CListImgControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_ListImgData *pListImgData = (S_ListImgData*)pData;

	m_nIconSize = pListImgData->m_nIconSize;
	m_nOffsetWidth = pListImgData->m_nOffsetWidth;
	m_nOffsetHeight = pListImgData->m_nOffsetHeight;
	m_nMaxHeightCount = pListImgData->m_nMaxHeightCount;
	m_bCanbePick = pListImgData->m_bCanbePick;
	m_bShowSelFrame = pListImgData->m_bShowSelFrame;
	m_colSelFrame = pListImgData->m_colSelFrame;
	m_ScrollBar.SetData( &pListImgData->m_stScrollBar );

	return CBaseControl::SetData( pData );
}

bool CListImgControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_ListImgData *pListImgData = (S_ListImgData*)pData;

	pListImgData->m_nIconSize = m_nIconSize;
	pListImgData->m_nOffsetWidth = m_nOffsetWidth;
	pListImgData->m_nOffsetHeight = m_nOffsetHeight;
	pListImgData->m_nMaxHeightCount = m_nMaxHeightCount;
	pListImgData->m_bCanbePick = m_bCanbePick==TRUE;
	pListImgData->m_bShowSelFrame = m_bShowSelFrame==TRUE;
	pListImgData->m_colSelFrame = m_colSelFrame;
	m_ScrollBar.GetData( &pListImgData->m_stScrollBar );

	return CBaseControl::GetData( pData );
}

void CListImgControl::OnSize()
{
	m_nWidth = m_nWidth/(m_nIconSize+m_nOffsetWidth)*(m_nIconSize+m_nOffsetWidth);
	m_nHeight = m_nHeight/(m_nIconSize+m_nOffsetHeight)*(m_nIconSize+m_nOffsetHeight);

	m_ScrollBar.m_nOffsetX = m_nWidth/* - m_ScrollBar.m_nWidth*/;
	m_ScrollBar.m_nHeight = m_nHeight;
	m_ScrollBar.OnSize();
}

void CListImgControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );

	CBrush	brush( RGB(128,128,128) );
	RECT rcFrame;
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	int nW = m_nWidth/(m_nIconSize+m_nOffsetWidth);
	int nH = m_nHeight/(m_nIconSize+m_nOffsetHeight);
	for( int h=0; h<nH; h++ )
	{
		for( int w=0; w<nW; w++ )
		{
			rcFrame.left = nX + m_nOffsetWidth/2 + w*(m_nIconSize+m_nOffsetWidth);
			rcFrame.top = nY + m_nOffsetHeight/2 + h*(m_nIconSize+m_nOffsetHeight);
			rcFrame.right = rcFrame.left + m_nIconSize;
			rcFrame.bottom = rcFrame.top + m_nIconSize;
			pDC->FrameRect( &rcFrame, &brush );
		}
	}
	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	m_ScrollBar.Render( pDC, rcScrollBar );
}

bool CListImgControl::MouseMove( const POINT point, const RECT* pFatherRc )
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

