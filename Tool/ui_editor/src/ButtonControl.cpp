#include "StdAfx.h"
#include "buttoncontrol.h"
#include "PropertyDlg.h"
#include "UIObjectDlg.h"
#include <assert.h>

CButtonControl::CButtonControl()
{
	m_nType = Type_Button;

	m_nWidth = 70;
	m_nHeight = 30;
	m_strID.Format( "ID_BUTTON_%d", rand() );

	m_ProButton[Item_Button_Comments_State].SetItem( PIT_COMMENTS, "<Button>", NULL );
	m_ProButton[Item_Button_MoveOn].SetItem( PIT_DIALOG, "MoveOn", &m_PicMoveOn );
	m_ProButton[Item_Button_Press].SetItem( PIT_DIALOG, "Press", &m_PicPress );
	m_ProButton[Item_Button_Disabled].SetItem( PIT_DIALOG, "Disabled", &m_PicDisabled );

	m_ProButton[Item_Button_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProButton[Item_Button_OnClick].SetItem( PIT_EDIT, "OnClick", &m_OnClickName );
	m_ProButton[Item_Button_MouseOn].SetItem( PIT_EDIT, "MouseOn", &m_MouseOnName );

}

CButtonControl::~CButtonControl()
{
}

void CButtonControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );
	int nX, nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcText(nX+1,nY+1,nX+m_nWidth,nY+m_nHeight);
	pDC->SetTextColor( m_stFont.m_colColor );
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText( m_strCaption, rcText, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
}

void CButtonControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_Button_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProButton[n] );
	}
}

void CButtonControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();
	theUIObjectDlg.AddPictuer( m_PicMoveOn.GetCurSelPicName() );
	theUIObjectDlg.AddPictuer( m_PicPress.GetCurSelPicName() );
	theUIObjectDlg.AddPictuer( m_PicDisabled.GetCurSelPicName() );
}

bool CButtonControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	int	nX, nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rc( nX, nY, nX+m_nWidth, nY+m_nHeight);
	if ( rc.PtInRect(point) == TRUE )
	{
		char* pPicName = m_PicMoveOn.GetCurSelPicName();
		if ( pPicName[0] != 0 )
		{
			m_strPicName = pPicName;
			m_rcDrawFrame = m_PicMoveOn.GetFrameRect();
			m_rcDrawClient = m_PicMoveOn.GetClientRect();
			return true;
		}
	}

	return CBaseControl::MouseMove( point, pFatherRc );
}

bool CButtonControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_ButtonData *pButtonControl = (S_ButtonData*)pData;

	m_PicMoveOn.SetPicStruct( &pButtonControl->m_stMoveOnPic );
	m_PicPress.SetPicStruct( &pButtonControl->m_stPressPic );
	m_PicDisabled.SetPicStruct( &pButtonControl->m_stDisabledPic );

	//if( pButtonControl->m_szOnClickName )
	//	m_OnClickName = pButtonControl->m_szOnClickName;
	//if( pButtonControl->m_szOnClickName )
	//	m_MouseOnName = pButtonControl->m_szMouseOnName;

	return CBaseControl::SetData( pData );
}

bool CButtonControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_ButtonData *pButtonControl = (S_ButtonData*)pData;

	pButtonControl->m_stMoveOnPic.SetPicStruct( m_PicMoveOn.GetCurSelPicName(),
												&m_PicMoveOn.GetFrameRect(),
												&m_PicMoveOn.GetClientRect() );
	pButtonControl->m_stPressPic.SetPicStruct( m_PicPress.GetCurSelPicName(),
												&m_PicPress.GetFrameRect(),
												&m_PicPress.GetClientRect() );
	pButtonControl->m_stDisabledPic.SetPicStruct( m_PicDisabled.GetCurSelPicName(),
													&m_PicDisabled.GetFrameRect(),
													&m_PicDisabled.GetClientRect() );

	strcpy( pButtonControl->m_szFontNormal, m_stFont.m_strName );
	pButtonControl->m_nFontSizeNormal = m_stFont.m_nSize;
	pButtonControl->m_colFontNormal = RGB(GetBValue(m_stFont.m_colColor), GetGValue(m_stFont.m_colColor), GetRValue(m_stFont.m_colColor));

	return CBaseControl::GetData( pData );
}

void CButtonControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_Button_OnClick, m_OnClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Button_MouseOn, m_MouseOnName.GetBuffer() );
}
