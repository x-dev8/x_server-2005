/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel_CityPlayer.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GroupPanel_CityPlayer.h"
#include "GroupPanel.h"

CUI_ID_FRAME_GroupPanel_CityPlayer s_CUI_ID_FRAME_GroupPanel_CityPlayer;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GroupPanel_CityPlayer, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GroupPanel_CityPlayer, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_AddFriendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_MiyuOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_YaoqingOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_CityPlayer, ID_LIST_PlayerOnListSelectChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_CityPlayer, ID_COMBOBOX_ShenshiOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_CityPlayer, ID_COMBOBOX_DiquOnComboBoxChange )
CUI_ID_FRAME_GroupPanel_CityPlayer::CUI_ID_FRAME_GroupPanel_CityPlayer()
{
	// Member
	m_pID_FRAME_GroupPanel_CityPlayer = NULL;
	m_pID_PICTURE_List = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	m_pID_BUTTON_Miyu = NULL;
	m_pID_BUTTON_Yaoqing = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_PlayerJob = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_PICTURE_Henxian = NULL;
	m_pID_PICTURE_Henxian2 = NULL;
	m_pID_TEXT_Jieyi = NULL;
	m_pID_TEXT_Gonghui = NULL;
	m_pID_TEXT_Shenshi = NULL;
	m_pID_TEXT_Diqu = NULL;
	m_pID_PICTURE_Henxian3 = NULL;
	m_pID_PICTURE_Henxian4 = NULL;
	m_pID_PICTURE_Henxian5 = NULL;
	m_pID_PICTURE_Henxian6 = NULL;
	m_pID_TEXT_Shenshi1 = NULL;
	m_pID_COMBOBOX_Shenshi = NULL;
	m_pID_TEXT_Diqu2 = NULL;
	m_pID_COMBOBOX_Diqu = NULL;

}
// Frame
bool CUI_ID_FRAME_GroupPanel_CityPlayer::OnFrameRun()
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return false;
	return true;
}
bool CUI_ID_FRAME_GroupPanel_CityPlayer::OnFrameRender()
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_CityPlayer::ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_CityPlayer::ID_BUTTON_MiyuOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_CityPlayer::ID_BUTTON_YaoqingOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return false;
	return true;
}
// List
void CUI_ID_FRAME_GroupPanel_CityPlayer::ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return;
}
// ComboBox
void CUI_ID_FRAME_GroupPanel_CityPlayer::ID_COMBOBOX_ShenshiOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return;
}
// ComboBox
void CUI_ID_FRAME_GroupPanel_CityPlayer::ID_COMBOBOX_DiquOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if(!m_pID_FRAME_GroupPanel_CityPlayer)
		return;
}

static void GP_OnVisibleChanged(ControlObject* pSender)
{
	if (!pSender->IsVisable() && pSender->GetFather() && pSender->GetFather()->IsVisable() && 
		s_CUI_ID_FRAME_GroupPanel.GetGroupSelect()/*m_optionGroup.GetSelectRadio()*/ == s_CUI_ID_FRAME_GroupPanel.GetCheckBoxTongchen()/*m_pID_CHECKBOX_Tongchen*/)
		pSender->SetVisable(true);
}

// 装载UI
bool CUI_ID_FRAME_GroupPanel_CityPlayer::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GroupPanel_CityPlayer.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GroupPanel_CityPlayer.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GroupPanel_CityPlayer::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GroupPanel_CityPlayer, s_CUI_ID_FRAME_GroupPanel_CityPlayerOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GroupPanel_CityPlayer, s_CUI_ID_FRAME_GroupPanel_CityPlayerOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_AddFriend, s_CUI_ID_FRAME_GroupPanel_CityPlayerID_BUTTON_AddFriendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_Miyu, s_CUI_ID_FRAME_GroupPanel_CityPlayerID_BUTTON_MiyuOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_Yaoqing, s_CUI_ID_FRAME_GroupPanel_CityPlayerID_BUTTON_YaoqingOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GroupPanel_CityPlayer, ID_LIST_Player, s_CUI_ID_FRAME_GroupPanel_CityPlayerID_LIST_PlayerOnListSelectChange );
	theUiManager.OnComboBoxChange( ID_FRAME_GroupPanel_CityPlayer, ID_COMBOBOX_Shenshi, s_CUI_ID_FRAME_GroupPanel_CityPlayerID_COMBOBOX_ShenshiOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_GroupPanel_CityPlayer, ID_COMBOBOX_Diqu, s_CUI_ID_FRAME_GroupPanel_CityPlayerID_COMBOBOX_DiquOnComboBoxChange );

	m_pID_FRAME_GroupPanel_CityPlayer = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GroupPanel_CityPlayer );
	m_pID_PICTURE_List = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_List );
	m_pID_BUTTON_AddFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_AddFriend );
	m_pID_BUTTON_Miyu = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_Miyu );
	m_pID_BUTTON_Yaoqing = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_BUTTON_Yaoqing );
	m_pID_LIST_Player = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_LIST_Player );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_PlayerName );
	m_pID_TEXT_PlayerJob = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_PlayerJob );
	m_pID_TEXT_PlayerLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_PlayerLvl );
	m_pID_PICTURE_Henxian = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_Henxian );
	m_pID_PICTURE_Henxian2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_Henxian2 );
	m_pID_TEXT_Jieyi = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_Jieyi );
	m_pID_TEXT_Gonghui = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_Gonghui );
	m_pID_TEXT_Shenshi = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_Shenshi );
	m_pID_TEXT_Diqu = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_Diqu );
	m_pID_PICTURE_Henxian3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_Henxian3 );
	m_pID_PICTURE_Henxian4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_Henxian4 );
	m_pID_PICTURE_Henxian5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_Henxian5 );
	m_pID_PICTURE_Henxian6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_PICTURE_Henxian6 );
	m_pID_TEXT_Shenshi1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_Shenshi1 );
	m_pID_COMBOBOX_Shenshi = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_COMBOBOX_Shenshi );
	m_pID_TEXT_Diqu2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_TEXT_Diqu2 );
	m_pID_COMBOBOX_Diqu = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GroupPanel_CityPlayer, ID_COMBOBOX_Diqu );
	assert( m_pID_FRAME_GroupPanel_CityPlayer );
	assert( m_pID_PICTURE_List );
	assert( m_pID_BUTTON_AddFriend );
	assert( m_pID_BUTTON_Miyu );
	assert( m_pID_BUTTON_Yaoqing );
	assert( m_pID_LIST_Player );
	assert( m_pID_TEXT_PlayerName );
	assert( m_pID_TEXT_PlayerJob );
	assert( m_pID_TEXT_PlayerLvl );
	assert( m_pID_PICTURE_Henxian );
	assert( m_pID_PICTURE_Henxian2 );
	assert( m_pID_TEXT_Jieyi );
	assert( m_pID_TEXT_Gonghui );
	assert( m_pID_TEXT_Shenshi );
	assert( m_pID_TEXT_Diqu );
	assert( m_pID_PICTURE_Henxian3 );
	assert( m_pID_PICTURE_Henxian4 );
	assert( m_pID_PICTURE_Henxian5 );
	assert( m_pID_PICTURE_Henxian6 );
	assert( m_pID_TEXT_Shenshi1 );
	assert( m_pID_COMBOBOX_Shenshi );
	assert( m_pID_TEXT_Diqu2 );
	assert( m_pID_COMBOBOX_Diqu );

	m_pID_FRAME_GroupPanel_CityPlayer->SetMsgHoldup(false);
	m_pID_FRAME_GroupPanel_CityPlayer->enableEscKey(false);
	m_pID_FRAME_GroupPanel_CityPlayer->SetOnVisibleChangedFun(GP_OnVisibleChanged);
	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GroupPanel_CityPlayer::_UnLoadUI()
{
	m_pID_FRAME_GroupPanel_CityPlayer = NULL;
	m_pID_PICTURE_List = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	m_pID_BUTTON_Miyu = NULL;
	m_pID_BUTTON_Yaoqing = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_PlayerJob = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_PICTURE_Henxian = NULL;
	m_pID_PICTURE_Henxian2 = NULL;
	m_pID_TEXT_Jieyi = NULL;
	m_pID_TEXT_Gonghui = NULL;
	m_pID_TEXT_Shenshi = NULL;
	m_pID_TEXT_Diqu = NULL;
	m_pID_PICTURE_Henxian3 = NULL;
	m_pID_PICTURE_Henxian4 = NULL;
	m_pID_PICTURE_Henxian5 = NULL;
	m_pID_PICTURE_Henxian6 = NULL;
	m_pID_TEXT_Shenshi1 = NULL;
	m_pID_COMBOBOX_Shenshi = NULL;
	m_pID_TEXT_Diqu2 = NULL;
	m_pID_COMBOBOX_Diqu = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GroupPanel_CityPlayer.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GroupPanel_CityPlayer::_IsVisable()
{
    if(!m_pID_FRAME_GroupPanel_CityPlayer)
        return false;

	return m_pID_FRAME_GroupPanel_CityPlayer->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GroupPanel_CityPlayer::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_GroupPanel_CityPlayer)
        return;

	m_pID_FRAME_GroupPanel_CityPlayer->SetVisable( bVisable );
}
