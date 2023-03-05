#include "StdAfx.h"
#include "comboboxcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"
#include "UIObjectDlg.h"

CComboBoxControl::CComboBoxControl(void)
{
	m_nType = Type_ComboBox;

	m_nWidth = 120;
	m_nHeight = 20;

	m_buttonSelect.m_nOffsetX = m_nWidth-m_nHeight;
	m_buttonSelect.m_nWidth = m_nHeight;
	m_buttonSelect.m_nHeight = m_nHeight;

	m_strID.Format( "ID_COMBOBOX_%d", rand() );

	m_colComments = RGB(0,127,0);

	m_ProComboBox[Item_ComboBox_Comments_EditInput].SetItem( PIT_COMMENTS, "<Edit>", &m_colComments );
	m_ProComboBox[Item_ComboBox_Comments_ListSelect].SetItem( PIT_COMMENTS, "<List>", &m_colComments );
	m_ProComboBox[Item_ComboBox_Comments_ButtonSelect].SetItem( PIT_COMMENTS, "<Button>", &m_colComments );

	m_ProComboBox[Item_ComboBox_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProComboBox[Item_ComboBox_OnChange].SetItem( PIT_EDIT, "OnChange", &m_OnChangeName );
	m_ProComboBox[Item_ComboBox_ShowList].SetItem( PIT_EDIT, "ShowList", &m_ShowListName );
}

CComboBoxControl::~CComboBoxControl(void)
{
}

void CComboBoxControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );

	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcComboBox;
	rcComboBox.left = nX;
	rcComboBox.top = nY;
	rcComboBox.right = rcComboBox.left + m_nWidth;
	rcComboBox.bottom = rcComboBox.top + m_nHeight;
	m_editInput.Render( pDC, rcComboBox );
	m_listSelect.Render( pDC, rcComboBox );
	m_buttonSelect.Render( pDC, rcComboBox );
}

void CComboBoxControl::OnSize()
{
	m_editInput.m_nWidth = m_nWidth-m_nHeight;
	m_editInput.m_nHeight = m_nHeight;

	m_listSelect.m_nOffsetY = m_nHeight;
	m_listSelect.m_nItemHeight = m_nHeight;
	m_listSelect.m_nWidth = m_nWidth/*-m_nHeight*/ - m_listSelect.m_ScrollBar.m_nWidth;
//	m_listSelect.m_nHeight = m_nHeight*3;
	//m_listSelect.m_ScrollBar.m_nWidth = m_nHeight;

	//m_buttonSelect.m_nOffsetX = m_nWidth-m_nHeight;
	//m_buttonSelect.m_nWidth = m_nHeight;
	//m_buttonSelect.m_nHeight = m_nHeight;

//	m_editInput.OnSize();
	m_listSelect.OnSize();
	m_buttonSelect.OnSize();
}

bool CComboBoxControl::MouseMove( const POINT point, const RECT* pFatherRc )
{
	int nX,nY;
	GetPos( &nX, &nY, pFatherRc );

	CRect rcComboBox;
	rcComboBox.left = nX;
	rcComboBox.top = nY;
	rcComboBox.right = rcComboBox.left + m_nWidth;
	rcComboBox.bottom = rcComboBox.top + m_nHeight;
	if( m_editInput.MouseMove( point, rcComboBox ) == true )
		return true;
	else if( m_listSelect.MouseMove( point, rcComboBox ) == true )
		return true;
	else if ( m_buttonSelect.MouseMove( point, rcComboBox ) == true )
		return true;

	return CBaseControl::MouseMove( point, pFatherRc );
}

void CComboBoxControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();

	thePropertyDlg.AddItem( &m_ProComboBox[Item_ComboBox_Comments_EditInput] );
	m_editInput.AddToPropertyDlg();
	thePropertyDlg.AddItem( &m_ProComboBox[Item_ComboBox_Comments_ListSelect] );
	m_listSelect.AddToPropertyDlg();
	thePropertyDlg.AddItem( &m_ProComboBox[Item_ComboBox_Comments_ButtonSelect] );
	m_buttonSelect.AddToPropertyDlg();
}

void CComboBoxControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();

	m_editInput.AddToUIObjectDlg();
	m_listSelect.AddToUIObjectDlg();
	m_buttonSelect.AddToUIObjectDlg();
}

bool CComboBoxControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_ComboBoxData *pComboBox = (S_ComboBoxData*)pData;

	m_editInput.SetData( &pComboBox->m_stEdit );
	m_listSelect.SetData( &pComboBox->m_stList );
	m_buttonSelect.SetData( &pComboBox->m_stButton );

	return CBaseControl::SetData( pData );
}

bool CComboBoxControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_ComboBoxData *pComboBox = (S_ComboBoxData*)pData;

	m_editInput.GetData( &pComboBox->m_stEdit );
	m_listSelect.GetData( &pComboBox->m_stList );
	m_buttonSelect.GetData( &pComboBox->m_stButton );

	return CBaseControl::GetData( pData );
}
void CComboBoxControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_ComboBox_OnChange, m_OnChangeName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_ComboBox_ShowList, m_ShowListName.GetBuffer() );
}
