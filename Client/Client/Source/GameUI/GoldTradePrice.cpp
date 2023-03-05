/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradePrice.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GoldTradePrice.h"
#include "GoldTrade.h"
#include "PlayerRole.h"

CUI_ID_FRAME_GoldTradePrice s_CUI_ID_FRAME_GoldTradePrice;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GoldTradePrice, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GoldTradePrice, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradePrice, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradePrice, ID_BUTTON_CancleOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradePrice, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradePrice, ID_EDIT_YinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradePrice, ID_EDIT_TongOnEditEnter )
CUI_ID_FRAME_GoldTradePrice::CUI_ID_FRAME_GoldTradePrice()
{
	// Member
	m_pID_FRAME_GoldTradePrice = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Price = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
}
// Frame
bool CUI_ID_FRAME_GoldTradePrice::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GoldTradePrice::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradePrice::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradePrice)
		return false;
	int gold = atoi(m_pID_EDIT_Jin->GetText());
	int silver = atoi(m_pID_EDIT_Yin->GetText());
	int copper = atoi(m_pID_EDIT_Tong->GetText());

	int unitprice = thePlayerRole.GetMoneyFromGSC(gold, silver, copper);
	s_CUI_ID_FRAME_GoldTrade.SetUnitPrice(unitprice);

	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradePrice::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradePrice)
		return false;
	SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_GoldTradePrice::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradePrice)
		return;
}
// Edit
void CUI_ID_FRAME_GoldTradePrice::ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradePrice)
		return;
}
// Edit
void CUI_ID_FRAME_GoldTradePrice::ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradePrice)
		return;
}

// 装载UI
bool CUI_ID_FRAME_GoldTradePrice::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GoldTradePrice.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GoldTradePrice.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GoldTradePrice::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GoldTradePrice, s_CUI_ID_FRAME_GoldTradePriceOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GoldTradePrice, s_CUI_ID_FRAME_GoldTradePriceOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradePrice, ID_BUTTON_OK, s_CUI_ID_FRAME_GoldTradePriceID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradePrice, ID_BUTTON_Cancle, s_CUI_ID_FRAME_GoldTradePriceID_BUTTON_CancleOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradePrice, ID_EDIT_Jin, s_CUI_ID_FRAME_GoldTradePriceID_EDIT_JinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradePrice, ID_EDIT_Yin, s_CUI_ID_FRAME_GoldTradePriceID_EDIT_YinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradePrice, ID_EDIT_Tong, s_CUI_ID_FRAME_GoldTradePriceID_EDIT_TongOnEditEnter );

	m_pID_FRAME_GoldTradePrice = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GoldTradePrice );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_TEXT_Msg );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_BUTTON_Cancle );
	m_pID_TEXT_Price = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_TEXT_Price );
	m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_PICTURE_Jin );
	m_pID_PICTURE_Ying = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_PICTURE_Ying );
	m_pID_PICTURE_Tong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_PICTURE_Tong );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_EDIT_Yin );
	m_pID_EDIT_Tong = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradePrice, ID_EDIT_Tong );
	assert( m_pID_FRAME_GoldTradePrice );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );
	assert( m_pID_TEXT_Price );
	assert( m_pID_PICTURE_Jin );
	assert( m_pID_PICTURE_Ying );
	assert( m_pID_PICTURE_Tong );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Tong );

	SetVisable(false);

	m_pID_EDIT_Jin->SetMaxLength(5);
	m_pID_EDIT_Yin->SetMaxLength(2);
	m_pID_EDIT_Tong->SetMaxLength(2);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GoldTradePrice::_UnLoadUI()
{
	m_pID_FRAME_GoldTradePrice = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	m_pID_TEXT_Price = NULL;
	m_pID_PICTURE_Jin = NULL;
	m_pID_PICTURE_Ying = NULL;
	m_pID_PICTURE_Tong = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Tong = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GoldTradePrice.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GoldTradePrice::_IsVisable()
{
	if(m_pID_FRAME_GoldTradePrice)
		return m_pID_FRAME_GoldTradePrice->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_GoldTradePrice::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GoldTradePrice)
		return;
	m_pID_FRAME_GoldTradePrice->SetVisable( bVisable );
}
