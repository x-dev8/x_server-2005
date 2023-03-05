/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\SettingGame.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SettingGame.h"
#include "GameSettingUI.h"
#include "UIBase.h"
#include "UserData.h"
#include "GameMain.h"
#include "wsCamera.h"
#include "Common.h"
#include "GameSetting.h"
#include "PopIntro.h"
#include "SettingEffect.h"
#include "GameSettingBgFrame.h"

CUI_ID_FRAME_GameSetup s_CUI_ID_FRAME_GameSetup;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSetup, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSetup, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_BUTTON_DefaultOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_SelfHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_PlayerNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_PlayerGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_OthersHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_MonsterNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_MonsterHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseFriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseTradeOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseBattleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseTeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_CloseGuideOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_LockShortcutOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_AutomatismOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_PlayerCHOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_PetNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_PetMasterOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_PetHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_OtherPetHPOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_CHECKBOX_HPLetterOnCheckBoxCheck )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_SCROLLBAREX_AgilityOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSetup, ID_SCROLLBAREX_SpeedOnScrollBarExUpdatePos )
CUI_ID_FRAME_GameSetup::CUI_ID_FRAME_GameSetup()
{
	// Member
	m_pID_FRAME_GameSet = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_CHECKBOX_SelfHP = NULL;
	m_pID_CHECKBOX_PlayerName = NULL;
	m_pID_CHECKBOX_PlayerGuild = NULL;
	m_pID_CHECKBOX_OthersHP = NULL;
	m_pID_CHECKBOX_MonsterName = NULL;
	m_pID_CHECKBOX_MonsterHP = NULL;
	m_pID_CHECKBOX_RefuseFriend = NULL;
	m_pID_CHECKBOX_RefuseTrade = NULL;
	m_pID_CHECKBOX_RefuseBattle = NULL;
	m_pID_CHECKBOX_RefuseTeam = NULL;
	m_pID_CHECKBOX_RefuseGuild = NULL;
	m_pID_CHECKBOX_CloseGuide = NULL;
	m_pID_CHECKBOX_LockShortcut = NULL;
	m_pID_CHECKBOX_CloseChatBubble = NULL;
	m_pID_CHECKBOX_RefuseStrangerMessaage = NULL;
	m_pID_CHECKBOX_RefuseAllMessaage = NULL;
	m_pID_CHECKBOX_Automatism = NULL;
	m_pID_CHECKBOX_PlayerCH = NULL;
	m_pID_CHECKBOX_PetName = NULL;
	m_pID_CHECKBOX_PetMaster = NULL;
	m_pID_CHECKBOX_PetHP = NULL;
	m_pID_CHECKBOX_OtherPetHP = NULL;
	m_pID_CHECKBOX_HPLetter = NULL;
	m_pID_SCROLLBAREX_Agility = NULL;
	m_pID_SCROLLBAREX_Speed = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSetup::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GameSetup::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GameSetup::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GameSet )
		return false;
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MOUSESPEED,  MouseSpeed );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_CAMERAROTATESPEED,  CameraRotateSpeed);
	GameSetting::Instance()->CommitChanges();

	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->SaveSetting( szSetting );
	SetVisable( false );
	s_CUI_ID_FRAME_GameSettingBgFrame._SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GameSetup::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GameSet )
		return false;
	SetVisable( false );
	s_CUI_ID_FRAME_GameSettingBgFrame._SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GameSetup::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GameSet )
		return false;
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetAccountDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->LoadSetting( szSetting );
	GameSetting::Instance()->CommitChanges();
	RefreshUI();
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_SelfHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_PlayerNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfName, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerName, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_PlayerGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerGuild, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfGuild, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerGuild, (unsigned int)*pbChecked );
	
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_OthersHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerHp, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_MonsterNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MonsterName, (unsigned int)*pbChecked );	
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_MonsterHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MonsterHp, (unsigned int)*pbChecked );	
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	 GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddFriendInFight, (unsigned int)*pbChecked );
	 GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddFriend, (unsigned int)*pbChecked );
     GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseTradeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseBargainInFight, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseBargain, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseBattleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseDuelInFight, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseDuel, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddTeamInFight, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddTeam, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddGang, (unsigned int)*pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddGangInFight, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_CloseGuideOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_IntroductionEnable, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	s_CUI_ID_FRAME_POPINTRO.CheckBoxClose_SetCheck(!(*pbChecked));
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_LockShortcutOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eSSC_SKILLLOCK,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eSSC_SKILLLOCK2,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatOther, !(*pbChecked) );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatTeam, !(*pbChecked) );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatSelf, !(*pbChecked) );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatTeam, !(*pbChecked) );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatMonster, !(*pbChecked) );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatNpc, !(*pbChecked) );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseStrangerMsg, (*pbChecked) );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAllMsg, (*pbChecked) );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_AutomatismOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_GameSet )
		return;
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_PlayerCHOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfTitle,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerTitle,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerTitle,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_PetNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetName,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerPetName,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerPetName,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_PetMasterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetTitle,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPetTitle,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPetTitle,  *pbChecked );

	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_PetHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetHp,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_OtherPetHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerPetHp,  *pbChecked );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerPetHp,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSetup::ID_CHECKBOX_HPLetterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_FightFlyText,  *pbChecked );
	GameSetting::Instance()->CommitChanges();
	
}
// ScrollBarEx
void CUI_ID_FRAME_GameSetup::ID_SCROLLBAREX_AgilityOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	MouseSpeed = n / 10 + 4;
	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)(INT_PTR)(MouseSpeed), 0);
}
// ScrollBarEx
void CUI_ID_FRAME_GameSetup::ID_SCROLLBAREX_SpeedOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	CameraRotateSpeed = n / 8 + 20;
	getwsCamera()->SetCameraRotateZSpeed( (float)CameraRotateSpeed/180*D3DX_PI*0.001f );
}

// 装载UI
bool CUI_ID_FRAME_GameSetup::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SettingGame.MEUI");
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SettingGame.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSetup::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSet, s_CUI_ID_FRAME_GameSetupOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSet, s_CUI_ID_FRAME_GameSetupOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_OK, s_CUI_ID_FRAME_GameSetupID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GameSetupID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GameSet, ID_BUTTON_Default, s_CUI_ID_FRAME_GameSetupID_BUTTON_DefaultOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_SelfHP, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_SelfHPOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PlayerName, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_PlayerNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PlayerGuild, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_PlayerGuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_OthersHP, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_OthersHPOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_MonsterName, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_MonsterNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_MonsterHP, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_MonsterHPOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseFriend, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseFriendOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTrade, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseTradeOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseBattle, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseBattleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTeam, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseTeamOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseGuild, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseGuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_CloseGuide, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_CloseGuideOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_LockShortcut, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_LockShortcutOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_CloseChatBubble, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseStrangerMessaage, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_RefuseAllMessaage, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_Automatism, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_AutomatismOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PlayerCH, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_PlayerCHOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PetName, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_PetNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PetMaster, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_PetMasterOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_PetHP, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_PetHPOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_OtherPetHP, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_OtherPetHPOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSet, ID_CHECKBOX_HPLetter, s_CUI_ID_FRAME_GameSetupID_CHECKBOX_HPLetterOnCheckBoxCheck );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSet, ID_SCROLLBAREX_Agility, s_CUI_ID_FRAME_GameSetupID_SCROLLBAREX_AgilityOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSet, ID_SCROLLBAREX_Speed, s_CUI_ID_FRAME_GameSetupID_SCROLLBAREX_SpeedOnScrollBarExUpdatePos );

	m_pID_FRAME_GameSet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSet );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_Cancel );
	m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameSet, ID_BUTTON_Default );
	m_pID_CHECKBOX_SelfHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_SelfHP );
	m_pID_CHECKBOX_PlayerName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PlayerName );
	m_pID_CHECKBOX_PlayerGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PlayerGuild );
	m_pID_CHECKBOX_OthersHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_OthersHP );
	m_pID_CHECKBOX_MonsterName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_MonsterName );
	m_pID_CHECKBOX_MonsterHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_MonsterHP );
	m_pID_CHECKBOX_RefuseFriend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseFriend );
	m_pID_CHECKBOX_RefuseTrade = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTrade );
	m_pID_CHECKBOX_RefuseBattle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseBattle );
	m_pID_CHECKBOX_RefuseTeam = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseTeam );
	m_pID_CHECKBOX_RefuseGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseGuild );
	m_pID_CHECKBOX_CloseGuide = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_CloseGuide );
	m_pID_CHECKBOX_LockShortcut = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_LockShortcut );
	m_pID_CHECKBOX_CloseChatBubble = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_CloseChatBubble );
	m_pID_CHECKBOX_RefuseStrangerMessaage = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseStrangerMessaage );
	m_pID_CHECKBOX_RefuseAllMessaage = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_RefuseAllMessaage );
	m_pID_CHECKBOX_Automatism = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_Automatism );
	m_pID_CHECKBOX_PlayerCH = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PlayerCH );
	m_pID_CHECKBOX_PetName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PetName );
	m_pID_CHECKBOX_PetMaster = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PetMaster );
	m_pID_CHECKBOX_PetHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_PetHP );
	m_pID_CHECKBOX_OtherPetHP = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_OtherPetHP );
	m_pID_CHECKBOX_HPLetter = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSet, ID_CHECKBOX_HPLetter );
	m_pID_SCROLLBAREX_Agility = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSet, ID_SCROLLBAREX_Agility );
	m_pID_SCROLLBAREX_Speed = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSet, ID_SCROLLBAREX_Speed );
	assert( m_pID_FRAME_GameSet );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Default );
	assert( m_pID_CHECKBOX_SelfHP );
	assert( m_pID_CHECKBOX_PlayerName );
	assert( m_pID_CHECKBOX_PlayerGuild );
	assert( m_pID_CHECKBOX_OthersHP );
	assert( m_pID_CHECKBOX_MonsterName );
	assert( m_pID_CHECKBOX_MonsterHP );
	assert( m_pID_CHECKBOX_RefuseFriend );
	assert( m_pID_CHECKBOX_RefuseTrade );
	assert( m_pID_CHECKBOX_RefuseBattle );
	assert( m_pID_CHECKBOX_RefuseTeam );
	assert( m_pID_CHECKBOX_RefuseGuild );
	assert( m_pID_CHECKBOX_CloseGuide );
	assert( m_pID_CHECKBOX_LockShortcut );
	assert( m_pID_CHECKBOX_CloseChatBubble );
	assert( m_pID_CHECKBOX_RefuseStrangerMessaage );
	assert( m_pID_CHECKBOX_RefuseAllMessaage );
	assert( m_pID_CHECKBOX_Automatism );
	assert( m_pID_CHECKBOX_PlayerCH );
	assert( m_pID_CHECKBOX_PetName );
	assert( m_pID_CHECKBOX_PetMaster );
	assert( m_pID_CHECKBOX_PetHP );
	assert( m_pID_CHECKBOX_OtherPetHP );
	assert( m_pID_CHECKBOX_HPLetter );
	assert( m_pID_SCROLLBAREX_Agility );
	assert( m_pID_SCROLLBAREX_Speed );
	m_pID_FRAME_GameSet->SetFather(s_CUI_ID_FRAME_GameSettingBgFrame.GetFrame());
	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSetup::_UnLoadUI()
{
	m_pID_FRAME_GameSet = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_CHECKBOX_SelfHP = NULL;
	m_pID_CHECKBOX_PlayerName = NULL;
	m_pID_CHECKBOX_PlayerGuild = NULL;
	m_pID_CHECKBOX_OthersHP = NULL;
	m_pID_CHECKBOX_MonsterName = NULL;
	m_pID_CHECKBOX_MonsterHP = NULL;
	m_pID_CHECKBOX_RefuseFriend = NULL;
	m_pID_CHECKBOX_RefuseTrade = NULL;
	m_pID_CHECKBOX_RefuseBattle = NULL;
	m_pID_CHECKBOX_RefuseTeam = NULL;
	m_pID_CHECKBOX_RefuseGuild = NULL;
	m_pID_CHECKBOX_CloseGuide = NULL;
	m_pID_CHECKBOX_LockShortcut = NULL;
	m_pID_CHECKBOX_CloseChatBubble = NULL;
	m_pID_CHECKBOX_RefuseStrangerMessaage = NULL;
	m_pID_CHECKBOX_RefuseAllMessaage = NULL;
	m_pID_CHECKBOX_Automatism = NULL;
	m_pID_CHECKBOX_PlayerCH = NULL;
	m_pID_CHECKBOX_PetName = NULL;
	m_pID_CHECKBOX_PetMaster = NULL;
	m_pID_CHECKBOX_PetHP = NULL;
	m_pID_CHECKBOX_OtherPetHP = NULL;
	m_pID_CHECKBOX_HPLetter = NULL;
	m_pID_SCROLLBAREX_Agility = NULL;
	m_pID_SCROLLBAREX_Speed = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\SettingGame.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSetup::_IsVisable()
{
	if ( !m_pID_FRAME_GameSet )
		return false;
	return m_pID_FRAME_GameSet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSetup::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GameSet )
		return ;
	m_pID_FRAME_GameSet->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
	
}
void CUI_ID_FRAME_GameSetup::InitializeAtEnterWorld()
{
	if ( !m_pID_FRAME_GameSet )
		return ;
		m_pID_FRAME_GameSet->SetVisable(false);
}
void CUI_ID_FRAME_GameSetup::RefreshUI()
{
	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		int nValue = (int)GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{	
			//
		case GameSetting::eGSC_SelfHp:		
			m_pID_CHECKBOX_SelfHP->SetCheck(nValue);
			break;
		case GameSetting::eGSC_SelfName:
		case GameSetting::eGSC_TeamPlayerName:
		case GameSetting::eGSC_OtherPlayerName:
  			m_pID_CHECKBOX_PlayerName->SetCheck(nValue);
			ShowPlayerName = ( bool )nValue;
			ShowNpcName = ( bool )nValue;
			ShowItemName = ( bool )nValue;
  			break;
		case GameSetting::eGSC_TeamPlayerGuild:
		case GameSetting::eGSC_SelfGuild:
		case GameSetting::eGSC_OtherPlayerGuild:
  			m_pID_CHECKBOX_PlayerGuild->SetCheck( nValue );
  			break;
		case GameSetting::eGSC_TeamPlayerHp:
		case GameSetting::eGSC_OtherPlayerHp:
 			m_pID_CHECKBOX_OthersHP->SetCheck( nValue );
 			break;		
		case GameSetting::eGSC_MonsterName:
 			m_pID_CHECKBOX_MonsterName->SetCheck( nValue );
 			break;
		case GameSetting::eGSC_TeamPlayerPetHp:
		case GameSetting::eGSC_OtherPlayerPetHp:
 			m_pID_CHECKBOX_OtherPetHP->SetCheck( nValue );
 			break;
  		case GameSetting::eGSC_RefuseAddFriendInFight:
		case GameSetting::eGSC_RefuseAddFriend:
  			{
  				m_pID_CHECKBOX_RefuseFriend->SetCheck( nValue );
  			}			
  			break;
		case GameSetting::eGSC_RefuseStrangerMsg:
			{
				m_pID_CHECKBOX_RefuseStrangerMessaage->SetCheck(nValue);
			}
			break;
		case GameSetting::eGSC_RefuseAllMsg:
			{
				m_pID_CHECKBOX_RefuseAllMessaage->SetCheck(nValue);
			}
			break;
  		case GameSetting::eGSC_RefuseBargainInFight:
		case GameSetting::eGSC_RefuseBargain:
  			{
  				m_pID_CHECKBOX_RefuseTrade->SetCheck( nValue );
  			}			
  			break;
 		case GameSetting::eGSC_RefuseDuelInFight:
		case GameSetting::eGSC_RefuseDuel:
 			{ 
 				m_pID_CHECKBOX_RefuseBattle->SetCheck( nValue );
 			}
 			break;
 		case GameSetting::eGSC_RefuseAddTeamInFight:
		case GameSetting::eGSC_RefuseAddTeam:
 			{
 				m_pID_CHECKBOX_RefuseTeam->SetCheck( nValue );				
 			}			
 			break;
 		case GameSetting::eGSC_RefuseAddGang:
		case GameSetting::eGSC_RefuseAddGangInFight:
 			m_pID_CHECKBOX_RefuseGuild->SetCheck( nValue );
 			break;
 		case GameSetting::eGSC_IntroductionEnable:
 			m_pID_CHECKBOX_CloseGuide->SetCheck( nValue );
 			break;
//  		case GameSetting::eGSC_MAXCAMERADISTANCE:
//  			m_pID_SCROLLBAREX_CameraMaxDistance->SetValue( nValue );
//  			break;
 		case GameSetting::eSSC_SKILLLOCK:
		case GameSetting::eSSC_SKILLLOCK2:
 			m_pID_CHECKBOX_LockShortcut->SetCheck( nValue );
 			break;			
 		case GameSetting::eGSC_ChatOther:
		case GameSetting::eGSC_ChatTeam:
		case GameSetting::eGSC_ChatSelf:
		case GameSetting::eGSC_ChatMonster:
		case GameSetting::eGSC_ChatNpc:
 			m_pID_CHECKBOX_CloseChatBubble->SetCheck( !nValue );
 			break;
 		case GameSetting::eGSC_SelfTitle:
		case GameSetting::eGSC_TeamPlayerTitle:
		case GameSetting::eGSC_OtherPlayerTitle:
 			m_pID_CHECKBOX_PlayerCH->SetCheck( nValue );
 			break;
 		case GameSetting::eGSC_SelfPetName:
		case GameSetting::eGSC_TeamPlayerPetName:
		case GameSetting::eGSC_OtherPlayerPetName:
 			{
 				m_pID_CHECKBOX_PetName->SetCheck( nValue ); 				
 			}
 			break;
		case GameSetting::eGSC_SelfPetHp:
				m_pID_CHECKBOX_PetHP->SetCheck(nValue);
			break;
		case GameSetting::eGSC_MonsterHp:
			m_pID_CHECKBOX_MonsterHP->SetCheck(nValue);
			break;
		case GameSetting::eGSC_FightFlyText:
			m_pID_CHECKBOX_HPLetter->SetCheck(nValue);
			break;
		case GameSetting::eGSC_SelfPetTitle:
		case GameSetting::eGSC_TeamPetTitle:
		case GameSetting::eGSC_OtherPetTitle:
			m_pID_CHECKBOX_PetMaster->SetCheck(nValue);
		break;
 		case GameSetting::eGSC_MOUSESPEED:
 			m_pID_SCROLLBAREX_Agility->SetMaxValue(160);
 
 			if (nValue - 4 <= 0)
 				nValue = 0;
 			else
 				nValue = (nValue - 4) * 10;
 
 			m_pID_SCROLLBAREX_Agility->SetValue( nValue );
 			break;
 		case GameSetting::eGSC_CAMERAROTATESPEED:
 			m_pID_SCROLLBAREX_Speed->SetValue( nValue );
 			break;
 		default:
 			break;
		}
	}
}

