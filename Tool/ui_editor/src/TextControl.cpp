#include "StdAfx.h"
#include "textcontrol.h"
#include <assert.h>
#include "PropertyDlg.h"

CTextControl::CTextControl(void)
{
	m_nType = Type_Text;

	m_nWidth = 120;
	m_nHeight = 20;
	m_strID.Format( "ID_TEXT_%d", rand() );
	m_colComments = RGB( 128,0,0 );
	m_bSingleLine = FALSE;
	m_bScrollBarLeft = TRUE;

	m_comboTextAlign.SetData( ALIGN_MODE_LEFT_TOP, ALIGN_MODE_TEXT_COMBO );
	//m_PicTextBlank = 0;
	
	m_ProText[Item_Text_Comments].SetItem( PIT_COMMENTS, "Text", NULL );
	m_ProText[Item_Text_TextAlign].SetItem( PIT_COMBO, "文字本对齐模式", &m_comboTextAlign );
	m_ProText[Item_Text_SingleLine].SetItem( PIT_BOOL, "单行显示", &m_bSingleLine );
	m_ProText[Item_ScrollBar_BLeft].SetItem( PIT_BOOL, "滚动条左边", &m_bScrollBarLeft );

	m_ProText[Item_Text_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProText[Item_HyberClick].SetItem( PIT_EDIT, "HyberClick", &m_HyberClickName );
	//m_ProText[Item_Text_Pic_Blank].SetItem( PIT_NUM,"绘制位置偏移", &m_PicTextBlank);
	m_ProText[Item_Edit_ScrollBar].SetItem( PIT_COMMENTS, "<ScrollBar>", &m_colComments );
}

CTextControl::~CTextControl(void)
{
}

void CTextControl::Render( CDC* pDC, const RECT* pFatherRc )
{
	CBaseControl::Render( pDC, pFatherRc );
	int nX, nY;
	GetPos( &nX, &nY, pFatherRc );
	CRect rcText(nX+1,nY+1,nX+m_nWidth,nY+m_nHeight);
	pDC->SetTextColor( m_stFont.m_colColor );
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText( m_strCaption, rcText, DT_LEFT );

	if ( !m_bSingleLine )
	{
		CRect rcScrollBar;

		if ( m_bScrollBarLeft )
			rcScrollBar.left = nX - m_ScrollBar.m_nWidth;
		else
			rcScrollBar.left = nX;

		rcScrollBar.top = nY;

		if ( m_bScrollBarLeft )
			rcScrollBar.right = rcScrollBar.left /*+ m_nWidth*/;
		else
			rcScrollBar.right = rcScrollBar.left + m_nWidth;

		rcScrollBar.bottom = rcScrollBar.top + m_nHeight;
		m_ScrollBar.Render( pDC, rcScrollBar );
	}
}

void CTextControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_Text_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProText[n] );
	}
	m_ScrollBar.AddToPropertyDlg();
}

void CTextControl::OnSize()
{
	//m_nHeight = m_nHeight/(m_stFont.m_nSize)*m_stFont.m_nSize+4;

	if ( m_bScrollBarLeft )
		m_ScrollBar.m_nOffsetX = - m_ScrollBar.m_nWidth;
	else
		m_ScrollBar.m_nOffsetX = m_nWidth;

	m_ScrollBar.m_nHeight = m_nHeight;
	m_ScrollBar.OnSize();
}

bool CTextControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_TextData *pTextControl = (S_TextData*)pData;

	m_bSingleLine = pTextControl->m_bSingleLine;
	m_comboTextAlign.m_curValue = GetAlignMode( pTextControl->m_nTextAlign );
	//m_PicTextBlank = pTextControl->m_nPicTextBlank;
	m_ScrollBar.SetData( &pTextControl->m_stScrollBar );

	return CBaseControl::SetData( pData );
}

bool CTextControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_TextData *pTextControl = (S_TextData*)pData;

	pTextControl->m_bSingleLine = m_bSingleLine;
	pTextControl->m_nTextAlign = GetAlignMode( &m_comboTextAlign );
	//pTextControl->m_nPicTextBlank = m_PicTextBlank;
	m_ScrollBar.GetData( &pTextControl->m_stScrollBar );
	return CBaseControl::GetData( pData );
}
void CTextControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_Text_HyberClick, m_HyberClickName.GetBuffer() );
}


