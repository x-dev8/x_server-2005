#include "StdAfx.h"
#include "tabcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"
#include "UIObjectDlg.h"

CTabControl::CTabControl(void)
{
	m_nType = Type_Tab;

	m_nWidth = 210;
	m_nHeight = 220;
	m_strID.Format( "ID_TAB_%d", rand() );

	m_colComments = RGB(0,127,0);
	m_nTabCount = 3;

	for( int n=0; n<TAB_CONTROL_MAX; n++ )
	{
		m_btnTab[n].m_nOffsetX = n*m_btnTab[0].m_nWidth;
	}

	m_ProTab[Item_Tab_Comments].SetItem( PIT_COMMENTS, "<Tab>", NULL  );
	m_ProTab[Item_Tab_FrameCount].SetItem( PIT_NUM, "FrameCount", &m_nTabCount );
	m_ProTab[Item_Tab_Comments_Button].SetItem( PIT_COMMENTS, "<Button>", &m_colComments );
	m_ProTab[Item_Tab_FrameFileName1].SetItem( PIT_EDIT, "FrameFileName1", &m_strFrameFileName[0] );
	m_ProTab[Item_Tab_FrameFileName2].SetItem( PIT_EDIT, "FrameFileName2", &m_strFrameFileName[1] );
	m_ProTab[Item_Tab_FrameFileName3].SetItem( PIT_EDIT, "FrameFileName3", &m_strFrameFileName[2] );
	m_ProTab[Item_Tab_FrameFileName4].SetItem( PIT_EDIT, "FrameFileName4", &m_strFrameFileName[3] );
	m_ProTab[Item_Tab_FrameFileName5].SetItem( PIT_EDIT, "FrameFileName5", &m_strFrameFileName[4] );
}

CTabControl::~CTabControl(void)
{
}


void CTabControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );

	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcTab;
	rcTab.left = nX;
	rcTab.top = nY;	
	rcTab.right = rcTab.left + m_nWidth;
	rcTab.bottom = rcTab.top + m_nHeight;
	for ( int n=0; n<m_nTabCount; n++ )
	{
		m_btnTab[n].Render( pDC, rcTab );
	}
	m_frame.Render( pDC, rcTab );
}

void CTabControl::OnSize()
{
	m_frame.m_nOffsetY = m_btnTab[0].m_nHeight;
	m_frame.m_nWidth = m_nWidth;
	m_frame.m_nHeight = m_nHeight - m_btnTab[0].m_nHeight;
}

bool CTabControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );

	CRect rcTab;
	rcTab.left = nX;
	rcTab.top = nY;
	rcTab.right = rcTab.left + m_nWidth;
	rcTab.bottom = rcTab.top + m_nHeight;
	for ( int n=0; n<m_nTabCount; n++ )
	{
		if ( m_btnTab[n].MouseMove( point, rcTab ) == true )
		{
			return true;
		}
	}
	m_frame.MouseMove( point, rcTab );
	return CBaseControl::MouseMove( point, pFatherRc );
}

void CTabControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();

	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_Comments] );
	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_FrameCount] );
	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_FrameFileName1] );
	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_FrameFileName2] );
	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_FrameFileName3] );
	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_FrameFileName4] );
	thePropertyDlg.AddItem( &m_ProTab[Item_Tab_FrameFileName5] );

	for ( int n=0; n<TAB_CONTROL_MAX; n++ )
	{
		thePropertyDlg.AddItem( &m_ProTab[Item_Tab_Comments_Button] );
		m_btnTab[n].AddToPropertyDlg();
	}
}

void CTabControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();

	for ( int n=0; n<TAB_CONTROL_MAX; n++ )
	{
		m_btnTab[n].AddToUIObjectDlg();
	}
}

bool CTabControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_TabData *pTab = (S_TabData*)pData;

	m_nTabCount = pTab->m_nTabCount;
	for ( int n=0; n<m_nTabCount; n++ )
	{
		m_btnTab[n].SetData( &pTab->m_btnTab[n] );
		m_strFrameFileName[n] = pTab->m_szFrameFileName[n];
	}
	m_frame.SetData( &pTab->m_frame );

	return CBaseControl::SetData( pData );
}

bool CTabControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_TabData *pTab = (S_TabData*)pData;

	pTab->m_nTabCount = m_nTabCount;
	for ( int n=0; n<m_nTabCount; n++ )
	{
		m_btnTab[n].GetData( &pTab->m_btnTab[n] );
		strcpy( pTab->m_szFrameFileName[n], m_strFrameFileName[n] );
	}
	m_frame.GetData( &pTab->m_frame );

	return CBaseControl::GetData( pData );
}






