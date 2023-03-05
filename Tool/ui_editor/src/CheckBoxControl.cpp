#include "StdAfx.h"
#include "checkboxcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"
#include "UIObjectDlg.h"

CCheckBoxControl::CCheckBoxControl(void)
{
	m_nType = Type_CheckBox;

	m_nWidth = 80;
	m_nHeight = 15;
	m_strID.Format( "ID_CHECKBOX_%d", rand() );

	m_bChecked = FALSE;
	m_colChecked = RGB(128,0,0);

	m_ProCheckBox[Item_CheckBox_Comments_State].SetItem( PIT_COMMENTS, "<CheckBox>", &m_colChecked );
	m_ProCheckBox[Item_CheckBox_Checked].SetItem( PIT_BOOL, "DefineCheck", &m_bChecked );

	m_ProCheckBox[Item_CheckBox_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProCheckBox[Item_CheckBox_OnCheck].SetItem( PIT_EDIT, "OnCheck", &m_OnCheckName );

}

CCheckBoxControl::~CCheckBoxControl(void)
{
}

void CCheckBoxControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );
	
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	m_btnChecked.Render( pDC, rcScrollBar );

	CRect rcText(nX+m_nHeight+1,nY+1,nX+m_nWidth,nY+m_nHeight);
	pDC->SetTextColor( m_stFont.m_colColor );
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText( m_strCaption, rcText, DT_LEFT );
}

bool CCheckBoxControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );

	CRect rcScrollBar;
	rcScrollBar.left = nX;
	rcScrollBar.top = nY;
	rcScrollBar.right = rcScrollBar.left + m_nWidth;
	rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
	if( m_btnChecked.MouseMove( point, rcScrollBar ) == true )
		return true;

	return CBaseControl::MouseMove( point, pFatherRc );
}

void CCheckBoxControl::OnSize()
{
	/*if ( m_nWidth < m_nHeight )
	{
		m_nWidth = m_nHeight;
	}*/

//	m_btnChecked.m_nWidth = m_nHeight;
	if (m_nWidth < m_btnChecked.m_nWidth)
	{
		m_nWidth = m_btnChecked.m_nWidth;
	}
	m_btnChecked.m_nHeight = m_nHeight;
}

void CCheckBoxControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();

	for( int n=0; n<Item_CheckBox_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProCheckBox[n] );
	}
	m_btnChecked.AddToPropertyDlg();
}

void CCheckBoxControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();

	m_btnChecked.AddToUIObjectDlg();
}

bool CCheckBoxControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_CheckBoxData *pCheckBoxControl = (S_CheckBoxData*)pData;

	m_bChecked = pCheckBoxControl->m_bChecked;
	m_btnChecked.SetData( &pCheckBoxControl->m_stChecked );

	return CBaseControl::SetData( pData );
}

void CCheckBoxControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_CheckBox_OnCheck, m_OnCheckName.GetBuffer() );
}

bool CCheckBoxControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_CheckBoxData *pCheckBoxControl = (S_CheckBoxData*)pData;

	pCheckBoxControl->m_bChecked = m_bChecked==TRUE;
	m_btnChecked.GetData( &pCheckBoxControl->m_stChecked );

	return CBaseControl::GetData( pData );
}

