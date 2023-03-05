/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Turbo\MEUI\3.14-3.19\功能菜单\GamMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GamMenu.h"
#include "ui/Gang.h"
#include "ui/Family.h"
#include "ui/Team.h"
#include "ui/FriendDlg.h"
#include "Gang.h"
#include "exmain.h"
#include "Select.h"
#include "Login.h"
#include "../Effect.h"
#include "exmain.h"
#include "Group_Me.h"
#include "../Cfg.h"
#include "Pack_Ex.h"
#include "..\MotionBillBoard.h"
#include "Achivement.h"
#include "shortcutkey_configure.h"
#include "FaceDlg1.h"
#include "GameSettingUI.h"
#include "GroupPanel.h"
#include "Pet.h"
#include "RightMainMenu.h"
#include "ui/ExMenu.h"
#include "MiniMapUI.h"
#include "ShopCenter.h"
#include "PickUp.h"
#include "Country.h"
#include "Gang.h"
#include "FriendDlg.h"
#include "GameDefinePlayer.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "ui/Team.h"
#include "SuAnimal.h"

#include "GuildDefine.h"
#include "Gang.h"

#include "Family.h"
#include "MainMenu.h"
#include "CountryBaseInfo.h"
#include "ui/GuildBaseInfo.h"
CUI_ID_FRAME_GamMenu s_CUI_ID_FRAME_GamMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GamMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GamMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GamMenu, ID_BUTTON_ChangeEquipOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GamMenu, ID_BUTTON_FamilyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GamMenu, ID_BUTTON_GuildOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GamMenu, ID_BUTTON_FiendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GamMenu, ID_BUTTON_ZuDuiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GamMenu, ID_BUTTON_CountryOnButtonClick)
extern void SetTipAndHotKey(ControlButton* pCtl, AN_Configure_ShortcutKey::ShortCutKey_Configure key);
CUI_ID_FRAME_GamMenu::CUI_ID_FRAME_GamMenu()
{
	// Member
	m_pID_FRAME_GamMenu = NULL;
	m_pID_BUTTON_ChangeEquip = NULL;
	m_pID_BUTTON_Family = NULL;
	m_pID_BUTTON_Guild = NULL;
	m_pID_BUTTON_Fiend = NULL;
	m_pID_BUTTON_ZuDui = NULL;
	m_pID_BUTTON_Country = NULL;
	m_pID_TEXT_Family = NULL;
	m_pID_TEXT_Guild = NULL;
	m_pID_TEXT_Fiend = NULL;
	m_pID_TEXT_ZuDui = NULL;
	m_pID_TEXT_Country = NULL;
}
// Frame
bool CUI_ID_FRAME_GamMenu::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GamMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GamMenu::ID_BUTTON_ChangeEquipOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GamMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_GamMenu::ID_BUTTON_FamilyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GamMenu )
		return false;
	s_CUI_ID_FRAME_Family.SetVisable( !s_CUI_ID_FRAME_Family.IsVisable() );
	SetFamilyHighLight();
	return true;
}

//Button
bool CUI_ID_FRAME_GamMenu::ID_BUTTON_CountryOnButtonClick(ControlObject* pSender)
{
	if (!m_pID_FRAME_GamMenu)
	{
		return false;
	}
	s_CUI_ID_FRAME_BaseInfo.SetVisable(!s_CUI_ID_FRAME_BaseInfo.IsVisable());
	//s_CUI_ID_FRAME_Country.SetVisable(!s_CUI_ID_FRAME_Country.IsVisable());
	SetCountryHighLight();
	return true;
}

// Button
bool CUI_ID_FRAME_GamMenu::ID_BUTTON_GuildOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GamMenu )
		return false;
	//s_CUI_ID_FRAME_Gang.SetVisable( !s_CUI_ID_FRAME_Gang.IsVisable() );
	s_CUI_ID_FRAME_GuildBaseInfo.SetVisable( !s_CUI_ID_FRAME_GuildBaseInfo.IsVisable() );
	SetGuildHighLight();
	return true;
}
// Button
bool CUI_ID_FRAME_GamMenu::ID_BUTTON_FiendOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_GamMenu )
		return false;
	if( s_CUI_ID_FRAME_Friend.IsVisable())
		s_CUI_ID_FRAME_Friend.SetVisable( false );
	else
		s_CUI_ID_FRAME_Friend.SetVisable( true );

	SetFriendHighLight();
	//SetNeedSpark(false, ekey_friend);
	return true;
}
// Button
bool CUI_ID_FRAME_GamMenu::ID_BUTTON_ZuDuiOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GamMenu )
		return false;
	s_CUI_ID_FRAME_Team.SetVisable( !s_CUI_ID_FRAME_Team.IsVisable() );

	SetZuDuiHighLight();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GamMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GamMenu.MEUI",true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GamMenu.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GamMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GamMenu, s_CUI_ID_FRAME_GamMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GamMenu, s_CUI_ID_FRAME_GamMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GamMenu, ID_BUTTON_ChangeEquip, s_CUI_ID_FRAME_GamMenuID_BUTTON_ChangeEquipOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GamMenu, ID_BUTTON_Family, s_CUI_ID_FRAME_GamMenuID_BUTTON_FamilyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GamMenu, ID_BUTTON_Guild, s_CUI_ID_FRAME_GamMenuID_BUTTON_GuildOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GamMenu, ID_BUTTON_Fiend, s_CUI_ID_FRAME_GamMenuID_BUTTON_FiendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GamMenu, ID_BUTTON_ZuDui, s_CUI_ID_FRAME_GamMenuID_BUTTON_ZuDuiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GamMenu, ID_BUTTON_Country, s_CUI_ID_FRAME_GamMenuID_BUTTON_CountryOnButtonClick );

	m_pID_FRAME_GamMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GamMenu );
	m_pID_BUTTON_ChangeEquip = (ControlButton*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_BUTTON_ChangeEquip );
	m_pID_BUTTON_Family = (ControlButton*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_BUTTON_Family );
	m_pID_BUTTON_Country = (ControlButton*)theUiManager.FindControl(ID_FRAME_GamMenu,ID_BUTTON_Country);
	m_pID_BUTTON_Guild = (ControlButton*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_BUTTON_Guild );
	m_pID_BUTTON_Fiend = (ControlButton*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_BUTTON_Fiend );
	m_pID_BUTTON_ZuDui = (ControlButton*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_BUTTON_ZuDui );
	m_pID_TEXT_Family = (ControlText*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_TEXT_Family );
	m_pID_TEXT_Country = (ControlText*)theUiManager.FindControl(ID_FRAME_GamMenu, ID_TEXT_Country);
	m_pID_TEXT_Guild = (ControlText*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_TEXT_Guild );
	m_pID_TEXT_Fiend = (ControlText*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_TEXT_Fiend );
	m_pID_TEXT_ZuDui = (ControlText*)theUiManager.FindControl( ID_FRAME_GamMenu, ID_TEXT_ZuDui );

	assert( m_pID_FRAME_GamMenu );
	assert( m_pID_BUTTON_ChangeEquip );
	assert( m_pID_BUTTON_Family );
	assert( m_pID_BUTTON_Guild );
	assert( m_pID_BUTTON_Fiend );
	assert( m_pID_BUTTON_ZuDui );
	assert(m_pID_BUTTON_Country);
	assert(m_pID_TEXT_Country);
	assert( m_pID_TEXT_Family );
	assert( m_pID_TEXT_Guild );
	assert( m_pID_TEXT_Fiend );
	assert( m_pID_TEXT_ZuDui );

	m_pID_FRAME_GamMenu->SetFadeInorFadeOut(true);

	m_pID_TEXT_Family->SetEnable(false);
	m_pID_TEXT_Family->SetVisable(false);
	m_pID_TEXT_Guild->SetEnable(false);
	m_pID_TEXT_Guild->SetVisable(false);
	m_pID_TEXT_Fiend->SetEnable(false);
	m_pID_TEXT_Fiend->SetVisable(false);
	m_pID_TEXT_ZuDui->SetEnable(false);
	m_pID_TEXT_ZuDui->SetVisable(false);
	m_pID_TEXT_Country->SetEnable(false);
	m_pID_TEXT_Country->SetVisable(false);

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GamMenu::_UnLoadUI()
{
	m_pID_FRAME_GamMenu = NULL;
	m_pID_BUTTON_ChangeEquip = NULL;
	m_pID_BUTTON_Family = NULL;
	m_pID_BUTTON_Guild = NULL;
	m_pID_BUTTON_Fiend = NULL;
	m_pID_BUTTON_ZuDui = NULL;
	m_pID_BUTTON_Country = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GamMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GamMenu::_IsVisable()
{
	if ( !m_pID_FRAME_GamMenu )
		return false;
	return m_pID_FRAME_GamMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GamMenu::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GamMenu )
		return ;
	m_pID_FRAME_GamMenu->SetVisable( bVisable );
	if(bVisable)
		RefreshHotKey();
}

void CUI_ID_FRAME_GamMenu::SetFamilyHighLight()
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	s_CUI_ID_FRAME_MainMenu.SetGamHighLight();
	m_pID_TEXT_Family->SetVisable(false);
}

void CUI_ID_FRAME_GamMenu::SetCountryHighLight()
{
	if (!m_pID_FRAME_GamMenu)
	{
		return;
	}
	s_CUI_ID_FRAME_MainMenu.SetGamHighLight();
	m_pID_TEXT_Country->SetVisable(false);
}

void CUI_ID_FRAME_GamMenu::SetGuildHighLight()
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	s_CUI_ID_FRAME_MainMenu.SetGamHighLight();
	m_pID_TEXT_Guild->SetVisable(false);
}

void CUI_ID_FRAME_GamMenu::SetFriendHighLight()
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	s_CUI_ID_FRAME_MainMenu.SetGamHighLight();
	m_pID_TEXT_Fiend->SetVisable(false);
}

void CUI_ID_FRAME_GamMenu::SetZuDuiHighLight()
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	s_CUI_ID_FRAME_MainMenu.SetGamHighLight();
	m_pID_TEXT_ZuDui->SetVisable(false);
}

void CUI_ID_FRAME_GamMenu::SetFamilyBtnState(bool bValue)
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	m_pID_BUTTON_Family->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_GamMenu::SetCountryBtnState(bool bValue)
{
	if (!m_pID_FRAME_GamMenu)
	{
		return;
	}

	m_pID_BUTTON_Country->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_GamMenu::SetGuildBtnState(bool bValue)
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	m_pID_BUTTON_Guild->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_GamMenu::SetFriendBtnState(bool bValue)
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	m_pID_BUTTON_Fiend->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_GamMenu::SetTeamBtnState(bool bValue)
{
	if ( !m_pID_FRAME_GamMenu )
		return ;

	m_pID_BUTTON_ZuDui->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_GamMenu::RefreshHotKey()
{
	if( !m_pID_FRAME_GamMenu )
		return;

	SetTipAndHotKey(m_pID_BUTTON_Family,AN_Configure_ShortcutKey::AN_SCKC_uiFamily);
	SetTipAndHotKey(m_pID_BUTTON_Country,AN_Configure_ShortcutKey::AN_SCKC_uiCountry);
	SetTipAndHotKey(m_pID_BUTTON_Guild,AN_Configure_ShortcutKey::AN_SCKC_uiGuild);
	SetTipAndHotKey(m_pID_BUTTON_Fiend,AN_Configure_ShortcutKey::AN_SCKC_uiFriend);
	SetTipAndHotKey(m_pID_BUTTON_ZuDui,AN_Configure_ShortcutKey::AN_SCKC_uiGroup);
}
