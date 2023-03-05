/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\新建文件夹 (2)\ShopRegiste.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShopRegiste.h"
#include "CommonChatFrame.h"
#include "ChatInfoBox.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "PlayerRole.h"

CUI_ID_FRAME_ShopRegiste s_CUI_ID_FRAME_ShopRegiste;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ShopRegiste, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShopRegiste, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopRegiste, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopRegiste, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopRegiste, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopRegiste, ID_BUTTON_ClearOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ShopRegiste, ID_LIST_RegisteOnListSelectChange )
CUI_ID_FRAME_ShopRegiste::CUI_ID_FRAME_ShopRegiste()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_ShopRegiste::ResetMembers()
{
	m_pID_FRAME_ShopRegiste = NULL;
// 	m_pID_PICTURE_Di = NULL;
// 	m_pID_PICTURE_Di1 = NULL;
	m_pID_BUTTON_CLOSE = NULL;
//	m_pID_BUTTON_help = NULL;
	m_pID_BUTTON_Cancel = NULL;
// 	m_pID_TEXT_Title = NULL;
	m_pID_BUTTON_Clear = NULL;
	m_pID_LIST_Registe = NULL;

}
// Frame
bool CUI_ID_FRAME_ShopRegiste::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ShopRegiste::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ShopRegiste::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopRegiste )
		return false;
	SetVisable( false );
	return true;
}
// Button
//bool CUI_ID_FRAME_ShopRegiste::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_ShopRegiste )
//		return false;
//	return true;
//}
// Button
bool CUI_ID_FRAME_ShopRegiste::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopRegiste )
		return false;
	SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_ShopRegiste::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopRegiste )
		return false;
	ClearTradeInfo();
	return true;
}
// List
void CUI_ID_FRAME_ShopRegiste::ID_LIST_RegisteOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_ShopRegiste )
		return;
}

// 装载UI
bool CUI_ID_FRAME_ShopRegiste::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShopRegiste.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShopRegiste.MEUI]失败")
		return false;
	}
	m_Records.clear();
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShopRegiste::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShopRegiste, s_CUI_ID_FRAME_ShopRegisteOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShopRegiste, s_CUI_ID_FRAME_ShopRegisteOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ShopRegiste, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ShopRegisteID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_ShopRegiste, ID_BUTTON_help, s_CUI_ID_FRAME_ShopRegisteID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopRegiste, ID_BUTTON_Cancel, s_CUI_ID_FRAME_ShopRegisteID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopRegiste, ID_BUTTON_Clear, s_CUI_ID_FRAME_ShopRegisteID_BUTTON_ClearOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ShopRegiste, ID_LIST_Registe, s_CUI_ID_FRAME_ShopRegisteID_LIST_RegisteOnListSelectChange );

	m_pID_FRAME_ShopRegiste = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShopRegiste );
//	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_PICTURE_Di );
	//m_pID_PICTURE_Di1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_PICTURE_Di1 );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_BUTTON_CLOSE );
	//m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_BUTTON_help );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_BUTTON_Cancel );
// 	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_TEXT_Title );
	m_pID_BUTTON_Clear = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_BUTTON_Clear );
	m_pID_LIST_Registe = (ControlList*)theUiManager.FindControl( ID_FRAME_ShopRegiste, ID_LIST_Registe );
	assert( m_pID_FRAME_ShopRegiste );
	//assert( m_pID_PICTURE_Di );
	//assert( m_pID_PICTURE_Di1 );
	assert( m_pID_BUTTON_CLOSE );
//	assert( m_pID_BUTTON_help );
	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_Title );
	assert( m_pID_BUTTON_Clear );
	assert( m_pID_LIST_Registe );
	SetVisable( false );
	m_pID_LIST_Registe->HaveSelBar( false, 0 );
	m_pID_LIST_Registe->SetHyberRBtnDown( CommonChatFrame::HyberRBtnDown );
// 	m_pID_LIST_Registe->SetHyberClickFun( CUI_ChatInfoBox::HyberClickPrivateChat );
//     m_pID_LIST_Registe->SetHyberItemClick(CommonChatFrame::HyberItemClick);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShopRegiste::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\ShopRegiste.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ShopRegiste::_IsVisable()
{
	if( !m_pID_FRAME_ShopRegiste )
		return false;
	return m_pID_FRAME_ShopRegiste->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShopRegiste::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_ShopRegiste )
		return;
	m_pID_FRAME_ShopRegiste->SetVisable( bVisable );
}

void CUI_ID_FRAME_ShopRegiste::ClearTradeInfo()
{
	if( !m_pID_FRAME_ShopRegiste )
		return;
	m_pID_LIST_Registe->Clear();
}

void CUI_ID_FRAME_ShopRegiste::AddTradeInfo( const char* pszTradeInfo, DWORD dwMoney,char* itemData /*= NULL*/ )
{
	if( !m_pID_FRAME_ShopRegiste )
		return;
	ControlList::S_List	stItem;		
	stItem.SetData( pszTradeInfo, 0, NULL, 0xFFFFFFFF,NULL,itemData,1,sizeof(SCharItem));
	m_pID_LIST_Registe->AddItem(&stItem,NULL, false);

	// add money
	DWORD dwTotalPrice = dwMoney;
	int gold = 0,silver = 0,copper = 0;
    thePlayerRole.GetGSCFromMoney(dwTotalPrice,gold,silver,copper);

	std::stringstream str;
	str << theXmlString.GetString(eText_YouGet);
	if( gold > 0 )
		str << gold << theXmlString.GetString( eText_Money_Gold );
	if( silver > 0 )
		str << silver << theXmlString.GetString( eText_Money_Silver );
	if( copper > 0 )
		str << copper << theXmlString.GetString( eText_Money_Copper );

	if( str.str().size() == 0 )
		str << 0 << theXmlString.GetString( eText_Money_Copper );

	std::string text = str.str();
	stItem.clear();
	stItem.SetData( text.c_str(), 0, NULL, Color_Config.getColor(CC_PRIVATE_SHOP_MONEY) );
	m_pID_LIST_Registe->AddItem( &stItem,NULL, false);
}