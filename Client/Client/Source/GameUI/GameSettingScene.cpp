/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\gamesetting\GameSettingScene.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSetting.h"
#include "GameSettingScene.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingScene s_CUI_ID_FRAME_GameSettingScene;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingScene, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingScene, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcHpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcTitleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterHpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_TeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_OtherPlayerChatOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_FriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_SelfChatOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_TeamChatOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_ItemNameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_EnemyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_OtherOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterChatOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_NPCChatOnCheckBoxCheck )

// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcInfoControlOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterInfoControlOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_MapInfoControlOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingScene, ID_CHECKBOX_ChatInfoControlOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingScene::CUI_ID_FRAME_GameSettingScene()
{
	// Member
	m_pID_FRAME_GameSettingScene = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_PICTURE_Wall4 = NULL;
	m_pID_TEXT_NpcInfo = NULL;
	m_pID_TEXT_NpcName = NULL;
	m_pID_TEXT_NpcHp = NULL;
	m_pID_TEXT_NpcTitle = NULL;
	m_pID_TEXT_MonsterInfo = NULL;
	m_pID_TEXT_MonsterName = NULL;
	m_pID_TEXT_MonsterHp = NULL;
	m_pID_TEXT_MapInfo = NULL;
	m_pID_TEXT_Team = NULL;
	m_pID_TEXT_Npc = NULL;
	m_pID_TEXT_Monster = NULL;
	m_pID_TEXT_OtherPlayerChat = NULL;
	m_pID_TEXT_Friend = NULL;
	m_pID_TEXT_ChatInfo = NULL;
	m_pID_TEXT_SelfChat = NULL;
	m_pID_TEXT_TeamChat = NULL;
	m_pID_CHECKBOX_NpcName = NULL;
	m_pID_CHECKBOX_NpcHp = NULL;
	m_pID_CHECKBOX_NpcTitle = NULL;
	m_pID_CHECKBOX_MonsterName = NULL;
	m_pID_CHECKBOX_MonsterHp = NULL;
	m_pID_CHECKBOX_Team = NULL;
	m_pID_CHECKBOX_Npc = NULL;
	m_pID_CHECKBOX_Monster = NULL;
	m_pID_CHECKBOX_OtherPlayerChat = NULL;
	m_pID_CHECKBOX_Friend = NULL;
	m_pID_CHECKBOX_SelfChat = NULL;
	m_pID_CHECKBOX_TeamChat = NULL;
	m_pID_TEXT_DropItem = NULL;
	m_pID_PICTURE_Wall5 = NULL;
	m_pID_TEXT_ItemName = NULL;
	m_pID_CHECKBOX_ItemName = NULL;
	m_pID_CHECKBOX_Enemy = NULL;
	m_pID_CHECKBOX_Guild = NULL;

	m_pID_CHECKBOX_Other = NULL;
	m_pID_CHECKBOX_NPCChat = NULL;
	m_pID_CHECKBOX_MonsterChat = NULL;
// 	m_pID_CHECKBOX_NpcInfoControl = NULL;
// 	m_pID_CHECKBOX_MonsterInfoControl = NULL;
// 	m_pID_CHECKBOX_MapInfoControl = NULL;
// 	m_pID_CHECKBOX_ChatInfoControl = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingScene::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingScene::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_NpcNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_NpcName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckNpcInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_NpcHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_NpcHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_NpcTitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_NpcTitle, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckNpcInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_MonsterNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MonsterName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMonsterInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_MonsterHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MonsterHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMonsterInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapTeam, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMapInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_NpcOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapNpc, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMapInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_MonsterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapMonster, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_OtherPlayerChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatOther, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckChatInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapFriend, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMapInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_SelfChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatSelf, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckChatInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_TeamChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatTeam, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckChatInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_ItemNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ItemName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
}

void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapGuild, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMapInfoControl();
}
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_EnemyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapEnemy, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMapInfoControl();
}
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_OtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MiniMapOther, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckMapInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_MonsterChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatMonster, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckChatInfoControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_NPCChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatNpc, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckChatInfoControl();
}
// CheckBox
//void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_NpcInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//    ID_CHECKBOX_NpcNameOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_NpcTitleOnCheckBoxCheck(NULL, pbChecked);
//    m_pID_CHECKBOX_NpcName->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_NpcTitle->SetCheck(*pbChecked);
//}
//// CheckBox
//void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_MonsterInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//    ID_CHECKBOX_MonsterNameOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_MonsterHpOnCheckBoxCheck(NULL, pbChecked);
//    m_pID_CHECKBOX_MonsterName->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_MonsterHp->SetCheck(*pbChecked);
//}
//// CheckBox
//void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_MapInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//    ID_CHECKBOX_TeamOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_NpcOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_FriendOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_GuildOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_EnemyOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_OtherOnCheckBoxCheck(NULL, pbChecked);
//    m_pID_CHECKBOX_Team->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_Npc->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_Friend->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_Guild->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_Enemy->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_Other->SetCheck(*pbChecked);
//}
//// CheckBox
//void CUI_ID_FRAME_GameSettingScene::ID_CHECKBOX_ChatInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//    ID_CHECKBOX_SelfChatOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_TeamChatOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_OtherPlayerChatOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_NPCChatOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_MonsterChatOnCheckBoxCheck(NULL, pbChecked);
//    m_pID_CHECKBOX_SelfChat->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_TeamChat->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_OtherPlayerChat->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_NPCChat->SetCheck(*pbChecked);
//    m_pID_CHECKBOX_MonsterChat->SetCheck(*pbChecked);
//}
// 装载UI
bool CUI_ID_FRAME_GameSettingScene::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingScene.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingScene.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingScene::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingScene, s_CUI_ID_FRAME_GameSettingSceneOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingScene, s_CUI_ID_FRAME_GameSettingSceneOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcName, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_NpcNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcHp, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_NpcHpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcTitle, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_NpcTitleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterName, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_MonsterNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterHp, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_MonsterHpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Team, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_TeamOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Npc, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_NpcOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Monster, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_MonsterOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_OtherPlayerChat, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_OtherPlayerChatOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Friend, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_FriendOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_SelfChat, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_SelfChatOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_TeamChat, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_TeamChatOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_ItemName, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_ItemNameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_GuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Enemy, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_EnemyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_Other, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_OtherOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterChat, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_MonsterChatOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_NPCChat, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_NPCChatOnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcInfoControl, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_NpcInfoControlOnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterInfoControl, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_MonsterInfoControlOnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_MapInfoControl, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_MapInfoControlOnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingScene, ID_CHECKBOX_ChatInfoControl, s_CUI_ID_FRAME_GameSettingSceneID_CHECKBOX_ChatInfoControlOnCheckBoxCheck );

	m_pID_FRAME_GameSettingScene = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingScene );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_PICTURE_Wall1 );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_PICTURE_Wall3 );
	m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_PICTURE_Wall2 );
	m_pID_PICTURE_Wall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_PICTURE_Wall4 );
	m_pID_TEXT_NpcInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_NpcInfo );
	m_pID_TEXT_NpcName = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_NpcName );
	m_pID_TEXT_NpcHp = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_NpcHp );
	m_pID_TEXT_NpcTitle = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_NpcTitle );
	m_pID_TEXT_MonsterInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_MonsterInfo );
	m_pID_TEXT_MonsterName = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_MonsterName );
	m_pID_TEXT_MonsterHp = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_MonsterHp );
	m_pID_TEXT_MapInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_MapInfo );
	m_pID_TEXT_Team = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_Team );
	m_pID_TEXT_Npc = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_Npc );
	m_pID_TEXT_Monster = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_Monster );
	m_pID_TEXT_OtherPlayerChat = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_OtherPlayerChat );
	m_pID_TEXT_Friend = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_Friend );
	m_pID_TEXT_ChatInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_ChatInfo );
	m_pID_TEXT_SelfChat = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_SelfChat );
	m_pID_TEXT_TeamChat = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_TeamChat );
	m_pID_CHECKBOX_NpcName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcName );
	m_pID_CHECKBOX_NpcHp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcHp );
	m_pID_CHECKBOX_NpcTitle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcTitle );
	m_pID_CHECKBOX_MonsterName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterName );
	m_pID_CHECKBOX_MonsterHp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterHp );
	m_pID_CHECKBOX_Team = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Team );
	m_pID_CHECKBOX_Npc = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Npc );
	m_pID_CHECKBOX_Monster = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Monster );
	m_pID_CHECKBOX_OtherPlayerChat = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_OtherPlayerChat );
	m_pID_CHECKBOX_Friend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Friend );
	m_pID_CHECKBOX_SelfChat = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_SelfChat );
	m_pID_CHECKBOX_TeamChat = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_TeamChat );
	m_pID_TEXT_DropItem = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_DropItem );
	m_pID_PICTURE_Wall5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_PICTURE_Wall5 );
	m_pID_TEXT_ItemName = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_TEXT_ItemName );
	m_pID_CHECKBOX_ItemName = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_ItemName );
	m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Guild );
	m_pID_CHECKBOX_Enemy = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Enemy );
	m_pID_CHECKBOX_Other = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_Other );
    m_pID_CHECKBOX_MonsterChat = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterChat );
	m_pID_CHECKBOX_NPCChat = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_NPCChat );
// 	m_pID_CHECKBOX_NpcInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_NpcInfoControl );
// 	m_pID_CHECKBOX_MonsterInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_MonsterInfoControl );
// 	m_pID_CHECKBOX_MapInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_MapInfoControl );
// 	m_pID_CHECKBOX_ChatInfoControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingScene, ID_CHECKBOX_ChatInfoControl );

    assert( m_pID_FRAME_GameSettingScene );
	assert( m_pID_PICTURE_Wall1 );
	assert( m_pID_PICTURE_Wall3 );
	assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_PICTURE_Wall4 );
	assert( m_pID_TEXT_NpcInfo );
	assert( m_pID_TEXT_NpcName );
	assert( m_pID_TEXT_NpcHp );
	assert( m_pID_TEXT_NpcTitle );
	assert( m_pID_TEXT_MonsterInfo );
	assert( m_pID_TEXT_MonsterName );
	assert( m_pID_TEXT_MonsterHp );
	assert( m_pID_TEXT_MapInfo );
	assert( m_pID_TEXT_Team );
	assert( m_pID_TEXT_Npc );
	assert( m_pID_TEXT_Monster );
	assert( m_pID_TEXT_OtherPlayerChat );
	assert( m_pID_TEXT_Friend );
	assert( m_pID_TEXT_ChatInfo );
	assert( m_pID_TEXT_SelfChat );
	assert( m_pID_TEXT_TeamChat );
	assert( m_pID_CHECKBOX_NpcName );
	assert( m_pID_CHECKBOX_NpcHp );
	assert( m_pID_CHECKBOX_NpcTitle );
	assert( m_pID_CHECKBOX_MonsterName );
	assert( m_pID_CHECKBOX_MonsterHp );
	assert( m_pID_CHECKBOX_Team );
	assert( m_pID_CHECKBOX_Npc );
	assert( m_pID_CHECKBOX_Monster );
	assert( m_pID_CHECKBOX_OtherPlayerChat );
	assert( m_pID_CHECKBOX_Friend );
	assert( m_pID_CHECKBOX_SelfChat );
	assert( m_pID_CHECKBOX_TeamChat );
	assert( m_pID_TEXT_DropItem );
	assert( m_pID_PICTURE_Wall5 );
	assert( m_pID_TEXT_ItemName );
	assert( m_pID_CHECKBOX_ItemName );
    assert( m_pID_CHECKBOX_MonsterChat );
    assert( m_pID_CHECKBOX_NPCChat );
//     assert( m_pID_CHECKBOX_NpcInfoControl );
//     assert( m_pID_CHECKBOX_MonsterInfoControl );
//     assert( m_pID_CHECKBOX_MapInfoControl );
//     assert( m_pID_CHECKBOX_ChatInfoControl );
	m_pID_FRAME_GameSettingScene->SetMsgHoldup(false);
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingScene::_UnLoadUI()
{
	m_pID_FRAME_GameSettingScene = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingScene.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingScene::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingScene )
		return false;
	return m_pID_FRAME_GameSettingScene->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingScene::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingScene )
		return;
	m_pID_FRAME_GameSettingScene->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}
void CUI_ID_FRAME_GameSettingScene::RefreshUI()
{
	if( !m_pID_FRAME_GameSettingScene )
		return;

	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		bool bValue = ( bool )GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{			
		case GameSetting::eGSC_MiniMapTeam:
			m_pID_CHECKBOX_Team->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MiniMapNpc:	
			m_pID_CHECKBOX_Npc->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MiniMapMonster:	
			m_pID_CHECKBOX_Monster->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MiniMapFriend:	
			m_pID_CHECKBOX_Friend->SetCheck( bValue );
			break;
		case GameSetting::eGSC_ChatSelf:
			m_pID_CHECKBOX_SelfChat->SetCheck( bValue );
			break;
		case GameSetting::eGSC_ChatTeam:		
			m_pID_CHECKBOX_TeamChat->SetCheck( bValue );
			break;
		case GameSetting::eGSC_ChatOther:
			m_pID_CHECKBOX_OtherPlayerChat->SetCheck( bValue );
			break;
		case GameSetting::eGSC_NpcName:
			m_pID_CHECKBOX_NpcName->SetCheck( bValue );
			break;
		case GameSetting::eGSC_NpcHp:				
			m_pID_CHECKBOX_NpcHp->SetCheck( bValue );
			break;
		case GameSetting::eGSC_NpcTitle:			
			m_pID_CHECKBOX_NpcTitle->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MonsterName:		
			m_pID_CHECKBOX_MonsterName->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MonsterHp:			
			m_pID_CHECKBOX_MonsterHp->SetCheck( bValue );
			break;
		case GameSetting::eGSC_ItemName:
			m_pID_CHECKBOX_ItemName->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MiniMapGuild:
			m_pID_CHECKBOX_Guild->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MiniMapEnemy:
			m_pID_CHECKBOX_Enemy->SetCheck( bValue );
			break;
		case GameSetting::eGSC_MiniMapOther:
			m_pID_CHECKBOX_Other->SetCheck( bValue );
			break;
        case GameSetting::eGSC_ChatNpc:
            m_pID_CHECKBOX_NPCChat->SetCheck( bValue );
            break;
        case GameSetting::eGSC_ChatMonster:
            m_pID_CHECKBOX_MonsterChat->SetCheck( bValue );
            break;
		default:
			break;
		}
	}
    CheckNpcInfoControl();
    CheckMonsterInfoControl();
    CheckMapInfoControl();
    CheckChatInfoControl();
}

void CUI_ID_FRAME_GameSettingScene::CheckNpcInfoControl()
{
//     if( m_pID_CHECKBOX_NpcName->IsChecked() 
//         && m_pID_CHECKBOX_NpcTitle->IsChecked() )
//         m_pID_CHECKBOX_NpcInfoControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_NpcInfoControl->SetCheck(false);
}

void CUI_ID_FRAME_GameSettingScene::CheckMonsterInfoControl()
{
//     if( m_pID_CHECKBOX_MonsterName->IsChecked()
//         && m_pID_CHECKBOX_MonsterHp->IsChecked() )
//         m_pID_CHECKBOX_MonsterInfoControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_MonsterInfoControl->SetCheck(false);
}

void CUI_ID_FRAME_GameSettingScene::CheckMapInfoControl()
{
//     if( m_pID_CHECKBOX_Team->IsChecked()
//         && m_pID_CHECKBOX_Npc->IsChecked()
//         && m_pID_CHECKBOX_Friend->IsChecked()
//         && m_pID_CHECKBOX_Guild->IsChecked()
//         && m_pID_CHECKBOX_Enemy->IsChecked()
//         && m_pID_CHECKBOX_Other->IsChecked() )
//         m_pID_CHECKBOX_MapInfoControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_MapInfoControl->SetCheck(false);
}

void CUI_ID_FRAME_GameSettingScene::CheckChatInfoControl()
{
//     if( m_pID_CHECKBOX_SelfChat->IsChecked()
//         && m_pID_CHECKBOX_TeamChat->IsChecked()
//         && m_pID_CHECKBOX_OtherPlayerChat->IsChecked()
//         && m_pID_CHECKBOX_NPCChat->IsChecked()
//         && m_pID_CHECKBOX_MonsterChat->IsChecked() )
//         m_pID_CHECKBOX_ChatInfoControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_ChatInfoControl->SetCheck(false);
}