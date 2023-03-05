/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradeSelect.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GoldTradeSelect.h"
#include "GoldTrade.h"
#include "NetworkInput.h"
#include "ConsignmentDefine.h"
#include "ConsignmentMessage.h"

CUI_ID_FRAME_GoldTradeSelect s_CUI_ID_FRAME_GoldTradeSelect;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GoldTradeSelect, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GoldTradeSelect, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GoldTradeSelect, ID_EDIT_AddNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeSelect, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldTradeSelect, ID_BUTTON_CancleOnButtonClick )
CUI_ID_FRAME_GoldTradeSelect::CUI_ID_FRAME_GoldTradeSelect()
{
	// Member
	m_pID_FRAME_GoldTradeSelect = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;

}
// Frame
bool CUI_ID_FRAME_GoldTradeSelect::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GoldTradeSelect::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_GoldTradeSelect::ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GoldTradeSelect)
		return;
}
// Button
bool CUI_ID_FRAME_GoldTradeSelect::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeSelect)
		return false;
	int gold = atoi(m_pID_EDIT_AddName->GetText());

	MsgQueryConsignmentList msg;
	if (m_IsBuy)
	{
		msg.uchConsignmentType = ConsignmentDefine::Consignment_SellRMB;
		msg.uchQueryType       = ConsignmentDefine::Sort_Count;
		msg.nCount             = gold;

		s_CUI_ID_FRAME_GoldTrade.SetSellFilter( gold );
		s_CUI_ID_FRAME_GoldTrade.SetSellUnCheck();	

		GettheNetworkInput().SendMsg( &msg );
	}
	else
	{
		msg.uchConsignmentType = ConsignmentDefine::Consignment_BuyRMB;
		msg.uchQueryType       = ConsignmentDefine::Sort_Count;
		msg.nCount             = gold;

		s_CUI_ID_FRAME_GoldTrade.SetBuyFilter( gold );
		s_CUI_ID_FRAME_GoldTrade.SetBuyUnCheck();

		GettheNetworkInput().SendMsg( &msg );
	}	
	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_GoldTradeSelect::ID_BUTTON_CancleOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GoldTradeSelect)
		return false;
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GoldTradeSelect::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GoldTradeSelect.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GoldTradeSelect.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GoldTradeSelect::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GoldTradeSelect, s_CUI_ID_FRAME_GoldTradeSelectOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GoldTradeSelect, s_CUI_ID_FRAME_GoldTradeSelectOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_GoldTradeSelect, ID_EDIT_AddName, s_CUI_ID_FRAME_GoldTradeSelectID_EDIT_AddNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeSelect, ID_BUTTON_OK, s_CUI_ID_FRAME_GoldTradeSelectID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldTradeSelect, ID_BUTTON_Cancle, s_CUI_ID_FRAME_GoldTradeSelectID_BUTTON_CancleOnButtonClick );

	m_pID_FRAME_GoldTradeSelect = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GoldTradeSelect );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldTradeSelect, ID_TEXT_Msg );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldTradeSelect, ID_PICTURE_Wall );
	m_pID_EDIT_AddName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GoldTradeSelect, ID_EDIT_AddName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeSelect, ID_BUTTON_OK );
	m_pID_BUTTON_Cancle = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldTradeSelect, ID_BUTTON_Cancle );
	assert( m_pID_FRAME_GoldTradeSelect );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_EDIT_AddName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancle );

	SetVisable(false);

	m_IsBuy = false;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GoldTradeSelect::_UnLoadUI()
{
	m_pID_FRAME_GoldTradeSelect = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_EDIT_AddName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancle = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GoldTradeSelect.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GoldTradeSelect::_IsVisable()
{
	if(m_pID_FRAME_GoldTradeSelect)
		return m_pID_FRAME_GoldTradeSelect->IsVisable();

	return false;
}
// 设置是否可视
void CUI_ID_FRAME_GoldTradeSelect::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GoldTradeSelect)
		return;

	m_pID_FRAME_GoldTradeSelect->SetVisable( bVisable );

	if(!bVisable)
	{
		m_pID_EDIT_AddName->SetText("");
	}
}

void CUI_ID_FRAME_GoldTradeSelect::SetBuy()
{
	m_IsBuy = true;
}

void CUI_ID_FRAME_GoldTradeSelect::SetSell()
{
	m_IsBuy = false;
}