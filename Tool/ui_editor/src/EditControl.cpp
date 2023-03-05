#include "StdAfx.h"
#include "editcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"

CEditControl::CEditControl(void)
{
	m_nType = Type_Edit;

	m_nWidth = 120;
	m_nHeight = 20;
	m_strID.Format( "ID_EDIT_%d", rand() );


	m_bMultiline = FALSE;
	m_bReadOnly = FALSE;
	m_bPassword  = FALSE;
	m_bIsNumber = FALSE;
	m_colComments = RGB( 128,0,0 );
	m_comboTextAlign.SetData( ALIGN_MODE_LEFT_TOP, ALIGN_MODE_TEXT_COMBO );

	m_ProEdit[Item_Edit_Comments_State].SetItem( PIT_COMMENTS, "<Edit>", NULL );
	m_ProEdit[Item_Edit_Multiline].SetItem( PIT_BOOL, "多行显示", &m_bMultiline );
	m_ProEdit[Item_Edit_ReadOnly].SetItem( PIT_BOOL, "是否只读", &m_bReadOnly );
	m_ProEdit[Item_Edit_Password].SetItem( PIT_BOOL, "Password", &m_bPassword );
	m_ProEdit[Item_Edit_Number].SetItem( PIT_BOOL, "IsNumber", &m_bIsNumber );
	m_ProEdit[Item_Edit_TextAlign].SetItem( PIT_COMBO, "文字本对齐模式", &m_comboTextAlign );
	m_ProEdit[Item_Edit_ScrollBar].SetItem( PIT_COMMENTS, "<ScrollBar>", &m_colComments );

	m_ProEdit[Item_Edit_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProEdit[Item_Edit_OnEnter].SetItem( PIT_EDIT, "OnEnter", &m_OnEnterName );
	m_ProEdit[Item_Edit_OnTab].SetItem( PIT_EDIT, "OnTab", &m_OnTabName );
	m_ProEdit[Item_Edit_OnLBtnDown].SetItem( PIT_EDIT, "OnLBtnDown", &m_OnLBtnDownName );
	m_ProEdit[Item_Edit_OnLBtnUp].SetItem( PIT_EDIT, "OnLBtnUp", &m_OnLBtnUpName );
	m_ProEdit[Item_Edit_DelByte].SetItem( PIT_EDIT, "DelByte", &m_DelByteName );
}

CEditControl::~CEditControl(void)
{
}

void CEditControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );
	int nX, nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcText(nX,nY,nX+m_nWidth,nY+m_nHeight);
	pDC->SetTextColor( m_stFont.m_colColor );
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText( m_strCaption+"|", rcText, DT_LEFT );

	if ( m_bMultiline )
	{
		CRect rcScrollBar;
		rcScrollBar.left = nX;
		rcScrollBar.top = nY;
		rcScrollBar.right = rcScrollBar.left + m_nWidth;
		rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
		m_ScrollBar.Render( pDC, rcScrollBar );
	}
}

void CEditControl::OnSize()
{
	if ( m_bMultiline )
	{
		m_nHeight = m_nHeight/(m_stFont.m_nSize)*m_stFont.m_nSize+4;

		m_ScrollBar.m_nOffsetX = m_nWidth/* - m_ScrollBar.m_nWidth*/;
		m_ScrollBar.m_nHeight = m_nHeight;
		m_ScrollBar.OnSize();
	}
	else
	{
		m_nHeight = m_stFont.m_nSize+12;
	}
}

void CEditControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_Edit_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProEdit[n] );
	}
	m_ScrollBar.AddToPropertyDlg();
}

void CEditControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();
	m_ScrollBar.AddToUIObjectDlg();
}

bool CEditControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_EditData *pEditControl = (S_EditData*)pData;

	m_bMultiline = !pEditControl->m_bSingleLine;
	m_bReadOnly = pEditControl->m_bReadOnly;
	m_bPassword = pEditControl->m_bPassword;
	m_bIsNumber = pEditControl->m_bIsNumber;
	m_comboTextAlign.m_curValue = GetAlignMode( pEditControl->m_nTextAlign );
	m_ScrollBar.SetData( &pEditControl->m_stScrollBar );

	return CBaseControl::SetData( pData );
}

bool CEditControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_EditData *pEditControl = (S_EditData*)pData;

	pEditControl->m_bSingleLine = m_bMultiline==FALSE;
	pEditControl->m_bReadOnly = m_bReadOnly==TRUE;
	pEditControl->m_bPassword = m_bPassword==TRUE;
	pEditControl->m_bIsNumber = m_bIsNumber==TRUE;
	pEditControl->m_nTextAlign = GetAlignMode( &m_comboTextAlign );
	m_ScrollBar.GetData( &pEditControl->m_stScrollBar );
	
	return CBaseControl::GetData( pData );
}

bool CEditControl::MouseMove( const POINT point, const RECT* pFatherRc )
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
void CEditControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_Edit_OnEnter, m_OnEnterName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Edit_OnTab, m_OnTabName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Edit_OnLBtnDown, m_OnLBtnDownName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Edit_OnLBtnUp, m_OnLBtnUpName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Edit_DelByte, m_DelByteName.GetBuffer() );
}

