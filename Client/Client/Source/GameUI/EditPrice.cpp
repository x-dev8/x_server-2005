/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\新建文件夹 (2)\EditPrice.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "EditPrice.h"
#include "..\shortcutkey_configure.h"
#include "MeUi/ExpressionManager.h"
#include "PlayerRole.h"
#include "Common.h"

CUI_ID_FRAME_EditPrice s_CUI_ID_FRAME_EditPrice;
MAP_FRAME_RUN( s_CUI_ID_FRAME_EditPrice, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_EditPrice, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EditPrice, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EditPrice, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_EditPrice, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_EditPrice, ID_EDIT_YinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_EditPrice, ID_EDIT_TongOnEditEnter )


CUI_ID_FRAME_EditPrice::CUI_ID_FRAME_EditPrice()
{
	// Member
	m_pID_FRAME_EditPrice = NULL;
	m_pID_TEXT_13141 = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Price = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_TEXT_TotalPriceZ = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	m_pfCallBackFun = 0;
	m_pData = 0;

}

// Frame
bool CUI_ID_FRAME_EditPrice::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_EditPrice::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_EditPrice::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_EditPrice)
	{
		assert(false&&"ui error");
		return false;
	}

	if( !m_pfCallBackFun )
	{
		SetVisable( false );
		return false;
	}

	m_pfCallBackFun( GetPrice(), m_pData );
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_EditPrice::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	SetVisable( false );
	return true;
}
// Edit
void CUI_ID_FRAME_EditPrice::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_EditPrice::ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_EditPrice::ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData )
{
}

// 装载UI
bool CUI_ID_FRAME_EditPrice::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\EditPrice.MEUI", true,UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\EditPrice.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_EditPrice::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_EditPrice, s_CUI_ID_FRAME_EditPriceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_EditPrice, s_CUI_ID_FRAME_EditPriceOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_EditPrice, ID_BUTTON_OK, s_CUI_ID_FRAME_EditPriceID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_EditPrice, ID_BUTTON_Cancle, s_CUI_ID_FRAME_EditPriceID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_EditPrice, ID_EDIT_Jin, s_CUI_ID_FRAME_EditPriceID_EDIT_JinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_EditPrice, ID_EDIT_Yin, s_CUI_ID_FRAME_EditPriceID_EDIT_YinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_EditPrice, ID_EDIT_Tong, s_CUI_ID_FRAME_EditPriceID_EDIT_TongOnEditEnter );

	m_pID_FRAME_EditPrice = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_EditPrice );
	m_pID_TEXT_13141 = (ControlText*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_TEXT_13141 );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_TEXT_Msg );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_BUTTON_Cancle );
	m_pID_TEXT_Price = (ControlText*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_TEXT_Price );
	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_PICTURE_Jin );
	m_pID_PICTURE_Ying = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_PICTURE_Ying );
	m_pID_PICTURE_Tong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_PICTURE_Tong );
	m_pID_TEXT_TotalPriceZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_TEXT_TotalPriceZ );
	m_pID_TEXT_TotalPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_TEXT_TotalPrice );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_EditPrice, ID_EDIT_Tong );
	assert( m_pID_FRAME_EditPrice );
	assert( m_pID_TEXT_13141 );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_Price );
	assert( m_pID_PICTURE_Jin );
	assert( m_pID_PICTURE_Ying );
	assert( m_pID_PICTURE_Tong );
	assert( m_pID_TEXT_TotalPriceZ );
	assert( m_pID_TEXT_TotalPrice );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );
	SetVisable( false );
	m_pID_EDIT_Jin->SetIsNumber( true );
	m_pID_EDIT_Jin->SetTextChangedFun( EditDataChange );
	m_pID_EDIT_Jin->SetMaxLength( 4 );
	m_pID_EDIT_Yin->SetIsNumber( true );
	m_pID_EDIT_Yin->SetTextChangedFun( EditDataChange );
	m_pID_EDIT_Yin->SetMaxLength( 2 );
	m_pID_EDIT_Tong->SetIsNumber( true );
	m_pID_EDIT_Tong->SetTextChangedFun( EditDataChange );
	m_pID_EDIT_Tong->SetMaxLength( 2 );
	m_pID_FRAME_EditPrice->SetMsgProcFun( InputBox_MsgProc );


	m_pID_EDIT_Jin->SetTextChangedFun( EditDataChangeEx );
	m_pID_EDIT_Yin->SetTextChangedFun( EditDataChangeEx );
	m_pID_EDIT_Tong->SetTextChangedFun( EditDataChangeEx );




	return true;
}
// 卸载UI
bool CUI_ID_FRAME_EditPrice::_UnLoadUI()
{
	m_pID_FRAME_EditPrice = NULL;
	m_pID_TEXT_13141 = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Price = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_TEXT_TotalPriceZ = NULL;
	m_pID_TEXT_TotalPrice = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\EditPrice.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_EditPrice::_IsVisable()
{
	if(!m_pID_FRAME_EditPrice)
		return false;

	return m_pID_FRAME_EditPrice->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_EditPrice::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_EditPrice)
		return ;

	if( !m_pID_FRAME_EditPrice->IsVisable() && bVisable )
	{
		SetPrice( 0 );
		m_pID_EDIT_Jin->SetText( 0 );
		m_pID_EDIT_Yin->SetText( 0 );
		m_pID_EDIT_Tong->SetText( 0 );
	}
	m_pID_FRAME_EditPrice->SetVisable( bVisable );
	theUiManager.SetFocus( m_pID_EDIT_Jin );
	theUiManager.ToTop(m_pID_FRAME_EditPrice);
}

DWORD CUI_ID_FRAME_EditPrice::GetPrice()
{
	int nGold = 0;
	if (m_pID_EDIT_Jin->GetText() != std::string(""))
		nGold = atoi( m_pID_EDIT_Jin->GetText() );
	int nSilver = 0;
	if (m_pID_EDIT_Yin->GetText() != std::string(""))
		nSilver = atoi( m_pID_EDIT_Yin->GetText() );
	int nCopper = 0;
	if (m_pID_EDIT_Tong->GetText() != std::string(""))
		nCopper = atoi( m_pID_EDIT_Tong->GetText() );
	DWORD dwPrice = thePlayerRole.GetMoneyFromGSC(nGold, nSilver, nCopper);
	return dwPrice;
}

void CUI_ID_FRAME_EditPrice::SetPrice( DWORD dwPrice )
{
	int nGold = 0, nSilver = 0, nCopper = 0;
	thePlayerRole.GetGSCFromMoney(dwPrice, nGold, nSilver, nCopper);

	char szMoney[512] = {0};
	MeSprintf_s( szMoney, sizeof(szMoney)/sizeof(char)-1, "%d", nGold );
	*m_pID_EDIT_Jin = szMoney;
	MeSprintf_s( szMoney, sizeof(szMoney)/sizeof(char)-1, "%d", nSilver );
	*m_pID_EDIT_Yin = szMoney;
	MeSprintf_s( szMoney, sizeof(szMoney)/sizeof(char)-1, "%d", nCopper );
	*m_pID_EDIT_Tong = szMoney;
}

void CUI_ID_FRAME_EditPrice::Show( funCallbackFun func, void* pData, unsigned int uiDataLength, unsigned int uiItemCount )
{
	m_pfCallBackFun = func;
	SAFE_DELETE( m_pData );
	m_pData = MeDefaultNew BYTE[ uiDataLength ];
	if( pData )
	{
		memcpy( m_pData, pData, uiDataLength );
	}
	m_uiItemCount = uiItemCount;
	SetVisable( true );
}
bool CUI_ID_FRAME_EditPrice::EditInputIsVisable()
{
	if( !m_pID_EDIT_Jin ||
		!m_pID_EDIT_Yin ||
		!m_pID_EDIT_Tong 
		)
		return false;

	return ( m_pID_EDIT_Jin == theUiManager.GetFocus() ||
		m_pID_EDIT_Yin == theUiManager.GetFocus() ||
		m_pID_EDIT_Tong == theUiManager.GetFocus() );
}

void CUI_ID_FRAME_EditPrice::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
	DWORD dwTotalPrice = s_CUI_ID_FRAME_EditPrice.GetPrice() * s_CUI_ID_FRAME_EditPrice.GetItemCount();
	std::string text = "";
	thePlayerRole.GetGSCStringFromMoney(dwTotalPrice, text);
	*s_CUI_ID_FRAME_EditPrice.m_pID_TEXT_TotalPrice = text;		
}

void CUI_ID_FRAME_EditPrice::EditDataChangeEx( OUT ControlObject* pSender, OUT const char *szData )
{
	//注意:这里检测只针对数字，就是不会出现有零出现在一个数字的前面，单独零除外
	int len = strlen( szData );
	if ( len > 1 )
	{
		int idx = 0;
		for ( ; idx < len -1; idx ++ )
		{
			if ( szData[idx] != '0' )
			{
				break;
			}
		}
		if ( idx > 0 )//表明前面有不必要的0
		{
			ControlEdit* edit = (ControlEdit*)pSender;
			edit->SetText( &szData[idx] );//下次条件就不成立，不会造成无限递归
		}
		
		
	}
}

bool CUI_ID_FRAME_EditPrice::InputBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if( !s_CUI_ID_FRAME_EditPrice.IsVisable() )
		return false;

	switch( msg ) 
	{		
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE/*g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiMessageCancel)*/ )	//cancle
			{
				s_CUI_ID_FRAME_EditPrice.ID_BUTTON_CancleOnButtonClick( NULL );
				return true;
			}
			else if( wParam == VK_RETURN/*g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiMessageOk)*/ )
			{
				s_CUI_ID_FRAME_EditPrice.ID_BUTTON_OKOnButtonClick( NULL );
				return true;
			}
		}
		break;
	}
	return false;
	unguard;
}
