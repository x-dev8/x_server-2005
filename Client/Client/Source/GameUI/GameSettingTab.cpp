/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GameSettingTab.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingTab.h"
#include "GameSetting.h"
#include "GameMain.h"
#include "PlayerMgr.h"

CUI_ID_FRAME_GameSettingTab s_CUI_ID_FRAME_GameSettingTab;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingTab, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingTab, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_EnemyGuildBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_EnemyGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_RedNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_FriendGuildBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_RedNameBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_FriendGuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_PKOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_PKBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfInfoControlOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamInfoControlOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_OtherPlayerInfoControlOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_OtherInfoControlOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_NormalOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_NormalBBOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingTab, ID_CHECKBOX_MonsterOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingTab::CUI_ID_FRAME_GameSettingTab()
{
	// Member
	m_pID_FRAME_GameSettingTab = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PICTURE_Wall4 = NULL;
	m_pID_TEXT_SelfInfo = NULL;
	m_pID_TEXT_Self = NULL;
	m_pID_TEXT_SelfBB = NULL;
	m_pID_TEXT_TeamInfo = NULL;
	m_pID_TEXT_Team = NULL;
	m_pID_TEXT_TeamBB = NULL;
	m_pID_TEXT_OtherPlayer = NULL;
	m_pID_TEXT_FriendGuildBB = NULL;
	m_pID_TEXT_FriendGuild = NULL;
	m_pID_TEXT_RedName = NULL;
	m_pID_TEXT_EnemyGuildBB = NULL;
	m_pID_TEXT_OtherInfo = NULL;
	m_pID_TEXT_RedNameBB = NULL;
	m_pID_CHECKBOX_Self = NULL;
	m_pID_CHECKBOX_SelfBB = NULL;
	m_pID_CHECKBOX_Team = NULL;
	m_pID_CHECKBOX_TeamBB = NULL;
	m_pID_CHECKBOX_EnemyGuildBB = NULL;
	m_pID_CHECKBOX_EnemyGuild = NULL;
	m_pID_CHECKBOX_RedName = NULL;
	m_pID_CHECKBOX_FriendGuildBB = NULL;
	m_pID_CHECKBOX_RedNameBB = NULL;
	m_pID_TEXT_EnemyGuild = NULL;
	m_pID_CHECKBOX_FriendGuild = NULL;
	m_pID_TEXT_PK = NULL;
	m_pID_CHECKBOX_PK = NULL;
	m_pID_TEXT_PKBB = NULL;
	m_pID_CHECKBOX_PKBB = NULL;
	m_pID_CHECKBOX_SelfInfoControl = NULL;
	m_pID_CHECKBOX_TeamInfoControl = NULL;
	m_pID_CHECKBOX_OtherPlayerInfoControl = NULL;
	m_pID_CHECKBOX_OtherInfoControl = NULL;
	m_pID_TEXT_Normal = NULL;
	m_pID_CHECKBOX_Normal = NULL;
	m_pID_TEXT_NormalBB = NULL;
	m_pID_CHECKBOX_NormalBB = NULL;
	m_pID_TEXT_Monster = NULL;
	m_pID_CHECKBOX_Monster = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingTab::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingTab::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_SelfOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabMe, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_SelfBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabMyPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabTeamPlayer, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_TeamBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabTeamPlayerPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_EnemyGuildBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabEnemyGuildPlayerPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_EnemyGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabEnemyGuildPlayer, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_RedNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabRedNamePlayer, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_FriendGuildBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabLeaguePlayerPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_RedNameBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabRedNamePlayerPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_FriendGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabLeaguePlayer, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_PKOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabPKPlayer, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_PKBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabPKPlayerPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_SelfInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	bool check = *pbChecked;
	SetCheckValue( GameSetting::eGSC_TabMe, check );
	SetCheckValue( GameSetting::eGSC_TabMyPet, check );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_TeamInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	bool check = *pbChecked;
	SetCheckValue( GameSetting::eGSC_TabTeamPlayer, check );
	SetCheckValue( GameSetting::eGSC_TabTeamPlayerPet, check );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_OtherPlayerInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	bool check = *pbChecked;
	SetCheckValue( GameSetting::eGSC_TabEnemyGuildPlayer, check );
	SetCheckValue( GameSetting::eGSC_TabEnemyGuildPlayerPet, check );
	SetCheckValue( GameSetting::eGSC_TabLeaguePlayer, check );
	SetCheckValue( GameSetting::eGSC_TabLeaguePlayerPet, check );
	SetCheckValue( GameSetting::eGSC_TabRedNamePlayer, check );
	SetCheckValue( GameSetting::eGSC_TabRedNamePlayerPet, check );
	SetCheckValue( GameSetting::eGSC_TabPKPlayer, check );
	SetCheckValue( GameSetting::eGSC_TabPKPlayerPet, check );
	SetCheckValue( GameSetting::eGSC_TabNormalPlayer, check );
	SetCheckValue( GameSetting::eGSC_TabNormalPlayerPet, check );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_OtherInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	bool check = *pbChecked;
	SetCheckValue( GameSetting::eGSC_TabMonster, check );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_NormalOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabNormalPlayer, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_NormalBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabNormalPlayerPet, *pbChecked );
}
// CheckBox
void CUI_ID_FRAME_GameSettingTab::ID_CHECKBOX_MonsterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	SetCheckValue( GameSetting::eGSC_TabMonster, *pbChecked );
}

// 装载UI
bool CUI_ID_FRAME_GameSettingTab::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingTab.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingTab.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingTab::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingTab, s_CUI_ID_FRAME_GameSettingTabOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingTab, s_CUI_ID_FRAME_GameSettingTabOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_Self, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_SelfOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_SelfBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_Team, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_TeamOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_TeamBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_EnemyGuildBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_EnemyGuildBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_EnemyGuild, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_EnemyGuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_RedName, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_RedNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_FriendGuildBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_FriendGuildBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_RedNameBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_RedNameBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_FriendGuild, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_FriendGuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_PK, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_PKOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_PKBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_PKBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfInfoControl, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_SelfInfoControlOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamInfoControl, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_TeamInfoControlOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_OtherPlayerInfoControl, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_OtherPlayerInfoControlOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_OtherInfoControl, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_OtherInfoControlOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_Normal, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_NormalOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_NormalBB, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_NormalBBOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingTab, ID_CHECKBOX_Monster, s_CUI_ID_FRAME_GameSettingTabID_CHECKBOX_MonsterOnCheckBoxCheck );

	m_pID_FRAME_GameSettingTab = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingTab );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_PICTURE_Wall1 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_PICTURE_Wall3 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_PICTURE_Wall2 );
	m_pID_PICTURE_Wall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_PICTURE_Wall4 );
	m_pID_TEXT_SelfInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_SelfInfo );
	m_pID_TEXT_Self = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_Self );
	m_pID_TEXT_SelfBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_SelfBB );
	m_pID_TEXT_TeamInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_TeamInfo );
	m_pID_TEXT_Team = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_Team );
	m_pID_TEXT_TeamBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_TeamBB );
	m_pID_TEXT_OtherPlayer = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_OtherPlayer );
	m_pID_TEXT_FriendGuildBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_FriendGuildBB );
	m_pID_TEXT_FriendGuild = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_FriendGuild );
	m_pID_TEXT_RedName = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_RedName );
	m_pID_TEXT_EnemyGuildBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_EnemyGuildBB );
	m_pID_TEXT_OtherInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_OtherInfo );
	m_pID_TEXT_RedNameBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_RedNameBB );
	m_pID_CHECKBOX_Self = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_Self );
	m_pID_CHECKBOX_SelfBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfBB );
	m_pID_CHECKBOX_Team = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_Team );
	m_pID_CHECKBOX_TeamBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamBB );
	m_pID_CHECKBOX_EnemyGuildBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_EnemyGuildBB );
	m_pID_CHECKBOX_EnemyGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_EnemyGuild );
	m_pID_CHECKBOX_RedName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_RedName );
	m_pID_CHECKBOX_FriendGuildBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_FriendGuildBB );
	m_pID_CHECKBOX_RedNameBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_RedNameBB );
	m_pID_TEXT_EnemyGuild = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_EnemyGuild );
	m_pID_CHECKBOX_FriendGuild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_FriendGuild );
	m_pID_TEXT_PK = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_PK );
	m_pID_CHECKBOX_PK = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_PK );
	m_pID_TEXT_PKBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_PKBB );
	m_pID_CHECKBOX_PKBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_PKBB );
	m_pID_CHECKBOX_SelfInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_SelfInfoControl );
	m_pID_CHECKBOX_TeamInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_TeamInfoControl );
	m_pID_CHECKBOX_OtherPlayerInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_OtherPlayerInfoControl );
	m_pID_CHECKBOX_OtherInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_OtherInfoControl );
	m_pID_TEXT_Normal = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_Normal );
	m_pID_CHECKBOX_Normal = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_Normal );
	m_pID_TEXT_NormalBB = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_NormalBB );
	m_pID_CHECKBOX_NormalBB = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_NormalBB );
	m_pID_TEXT_Monster = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_TEXT_Monster );
	m_pID_CHECKBOX_Monster = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingTab, ID_CHECKBOX_Monster );
	assert( m_pID_FRAME_GameSettingTab );
	assert( m_pID_PICTURE_Wall1 );
	assert( m_pID_PICTURE_Wall3 );
	assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_PICTURE_Wall4 );
	assert( m_pID_TEXT_SelfInfo );
	assert( m_pID_TEXT_Self );
	assert( m_pID_TEXT_SelfBB );
	assert( m_pID_TEXT_TeamInfo );
	assert( m_pID_TEXT_Team );
	assert( m_pID_TEXT_TeamBB );
	assert( m_pID_TEXT_OtherPlayer );
	assert( m_pID_TEXT_FriendGuildBB );
	assert( m_pID_TEXT_FriendGuild );
	assert( m_pID_TEXT_RedName );
	assert( m_pID_TEXT_EnemyGuildBB );
	assert( m_pID_TEXT_OtherInfo );
	assert( m_pID_TEXT_RedNameBB );
	assert( m_pID_CHECKBOX_Self );
	assert( m_pID_CHECKBOX_SelfBB );
	assert( m_pID_CHECKBOX_Team );
	assert( m_pID_CHECKBOX_TeamBB );
	assert( m_pID_CHECKBOX_EnemyGuildBB );
	assert( m_pID_CHECKBOX_EnemyGuild );
	assert( m_pID_CHECKBOX_RedName );
	assert( m_pID_CHECKBOX_FriendGuildBB );
	assert( m_pID_CHECKBOX_RedNameBB );
	assert( m_pID_TEXT_EnemyGuild );
	assert( m_pID_CHECKBOX_FriendGuild );
	assert( m_pID_TEXT_PK );
	assert( m_pID_CHECKBOX_PK );
	assert( m_pID_TEXT_PKBB );
	assert( m_pID_CHECKBOX_PKBB );
	assert( m_pID_CHECKBOX_SelfInfoControl );
	assert( m_pID_CHECKBOX_TeamInfoControl );
	assert( m_pID_CHECKBOX_OtherPlayerInfoControl );
	assert( m_pID_CHECKBOX_OtherInfoControl );
	assert( m_pID_TEXT_Normal );
	assert( m_pID_CHECKBOX_Normal );
	assert( m_pID_TEXT_NormalBB );
	assert( m_pID_CHECKBOX_NormalBB );
	assert( m_pID_TEXT_Monster );
	assert( m_pID_CHECKBOX_Monster );

	m_pID_FRAME_GameSettingTab->SetMsgHoldup(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingTab::_UnLoadUI()
{
	m_pID_FRAME_GameSettingTab = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingTab.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingTab::_IsVisable()
{
	return m_pID_FRAME_GameSettingTab->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingTab::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_GameSettingTab->SetVisable( bVisable );
}

void CUI_ID_FRAME_GameSettingTab::RefreshUI()
{
	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		int nValue = (int)GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{	
		case GameSetting::eGSC_TabMe:
			m_pID_CHECKBOX_Self->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabMyPet:
			m_pID_CHECKBOX_SelfBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabTeamPlayer:
			m_pID_CHECKBOX_Team->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabTeamPlayerPet:
			m_pID_CHECKBOX_TeamBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabEnemyGuildPlayer:
			m_pID_CHECKBOX_EnemyGuild->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabEnemyGuildPlayerPet:
			m_pID_CHECKBOX_EnemyGuildBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabLeaguePlayer:
			m_pID_CHECKBOX_FriendGuild->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabLeaguePlayerPet:
			m_pID_CHECKBOX_FriendGuildBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabRedNamePlayer:
			m_pID_CHECKBOX_RedName->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabRedNamePlayerPet:
			m_pID_CHECKBOX_RedNameBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabPKPlayer:
			m_pID_CHECKBOX_PK->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabPKPlayerPet:
			m_pID_CHECKBOX_PKBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabNormalPlayer:
			m_pID_CHECKBOX_Normal->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabNormalPlayerPet:
			m_pID_CHECKBOX_NormalBB->SetCheck( nValue );
			break;
		case GameSetting::eGSC_TabMonster:
			m_pID_CHECKBOX_Monster->SetCheck( nValue );
			break;
		default:
			break;
		}
	}

	RefreshSelectAllState();
}

void CUI_ID_FRAME_GameSettingTab::RefreshSelectAllState()
{
	bool check = m_pID_CHECKBOX_Self->IsChecked() && m_pID_CHECKBOX_SelfBB->IsChecked();
	m_pID_CHECKBOX_SelfInfoControl->SetCheck(check);

	check = m_pID_CHECKBOX_Team->IsChecked() && m_pID_CHECKBOX_TeamBB->IsChecked();
	m_pID_CHECKBOX_TeamInfoControl->SetCheck(check);

	check = m_pID_CHECKBOX_EnemyGuild->IsChecked() && m_pID_CHECKBOX_EnemyGuildBB->IsChecked() &&
		m_pID_CHECKBOX_FriendGuild->IsChecked() && m_pID_CHECKBOX_FriendGuildBB->IsChecked() &&
		m_pID_CHECKBOX_RedName->IsChecked() && m_pID_CHECKBOX_RedNameBB->IsChecked() &&
		m_pID_CHECKBOX_PK->IsChecked() && m_pID_CHECKBOX_PKBB->IsChecked() &&
		m_pID_CHECKBOX_Normal->IsChecked() && m_pID_CHECKBOX_NormalBB->IsChecked();
	m_pID_CHECKBOX_OtherPlayerInfoControl->SetCheck(check);

	check = m_pID_CHECKBOX_Monster->IsChecked();
	m_pID_CHECKBOX_OtherInfoControl->SetCheck(check);
}

void CUI_ID_FRAME_GameSettingTab::SetCheckValue(int id, bool value)
{
	GameSetting::Instance()->SetLevel( (GameSetting::eGameSettingCategory)id, (unsigned int)value );
	GameSetting::Instance()->CommitChanges();

	RefreshUI();
}

#define GameSettingTab_SetTabType(type, name)	\
	if (GameSetting::Instance()->GetLevel(GameSetting::eGSC_Tab##name) == 1)	\
		dwTabType |= CPlayer::PT_##name;

DWORD CUI_ID_FRAME_GameSettingTab::GetTabPlayerType()
{
	DWORD dwTabType = 0;
	GameSettingTab_SetTabType(dwTabType, Me						);
	GameSettingTab_SetTabType(dwTabType, MyPet					);
	GameSettingTab_SetTabType(dwTabType, TeamPlayer				);
	GameSettingTab_SetTabType(dwTabType, TeamPlayerPet			);
	GameSettingTab_SetTabType(dwTabType, EnemyGuildPlayer		);
	GameSettingTab_SetTabType(dwTabType, EnemyGuildPlayerPet	);
	GameSettingTab_SetTabType(dwTabType, LeaguePlayer			);
	GameSettingTab_SetTabType(dwTabType, LeaguePlayerPet		);
	GameSettingTab_SetTabType(dwTabType, MyGuildPlayer			);
	GameSettingTab_SetTabType(dwTabType, MyGuildPlayerPet		);
	GameSettingTab_SetTabType(dwTabType, NormalPlayer			);
	GameSettingTab_SetTabType(dwTabType, NormalPlayerPet		);
	GameSettingTab_SetTabType(dwTabType, RedNamePlayer			);
	GameSettingTab_SetTabType(dwTabType, RedNamePlayerPet		);
	GameSettingTab_SetTabType(dwTabType, PKPlayer				);
	GameSettingTab_SetTabType(dwTabType, PKPlayerPet			);
	GameSettingTab_SetTabType(dwTabType, Monster				);
	GameSettingTab_SetTabType(dwTabType, Other					);
	return dwTabType;
}
