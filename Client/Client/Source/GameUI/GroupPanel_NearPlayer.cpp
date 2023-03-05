/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel_NearPlayer.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GroupPanel_NearPlayer.h"
#include "GroupPanel.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GameMain.h"
#include "XmlStringLanguage.h"
#include "FriendDlg.h"
#include "ChatInfoBox.h"
#include "Group_Me.h"
#include "SystemConfig.h"
#include "color_config.h"
#include "Ui/InfoList.h"
#include "ui/Team.h"

CUI_ID_FRAME_GroupPanel_NearPlayer s_CUI_ID_FRAME_GroupPanel_NearPlayer;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GroupPanel_NearPlayer, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GroupPanel_NearPlayer, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_NearPlayer, ID_LIST_PlayerOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_YaoqingOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_DuizhangOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_TiChuOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_TuichuOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GroupPanel_NearPlayer, ID_LIST_TeamPlayerOnListSelectChange )
CUI_ID_FRAME_GroupPanel_NearPlayer::CUI_ID_FRAME_GroupPanel_NearPlayer()
{
	// Member
	m_pID_FRAME_GroupPanel_NearPlayer = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_LIST_PlayerTitle = NULL;
	m_pID_BUTTON_Yaoqing = NULL;
	m_pID_BUTTON_Duizhang = NULL;
	m_pID_BUTTON_TiChu = NULL;
	m_pID_BUTTON_Tuichu = NULL;
	m_pID_LIST_TeamPlayer = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_PlayerJob = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_PICTURE_Henxian = NULL;
	m_pID_PICTURE_Henxian2 = NULL;
	m_pID_TEXT_TeamMate = NULL;
	m_pID_TEXT_TeamMateLvl = NULL;
	m_pID_TEXT_TeamMateJob = NULL;

}
// Frame
bool CUI_ID_FRAME_GroupPanel_NearPlayer::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GroupPanel_NearPlayer::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_GroupPanel_NearPlayer::ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GroupPanel_NearPlayer)
		return;
	if (m_pID_LIST_Player->GetCurSelItem())
	{
		m_pID_BUTTON_Yaoqing->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Yaoqing->SetEnable(false);
		if( thePlayerRole.GetTeamMemberNum() > 0)
		{
			if (thePlayerRole.IsTeamHeader())
			{
				m_pID_BUTTON_Yaoqing->SetEnable(true);
			}
		}
	}
}
// Button
bool CUI_ID_FRAME_GroupPanel_NearPlayer::ID_BUTTON_YaoqingOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_NearPlayer)
		return false;
	if (m_pID_LIST_Player->GetCurSelItem())
	{
		if (thePlayerRole.GetTeamMemberNum() > 0 && (!thePlayerRole.IsTeamHeader()))
		{
			return false;
		}
		char szName[64] = {0};
		char szPro[64] = {0};
		int nLvl;
		sscanf(m_pID_LIST_Player->GetCurSelItem()->m_szText, "%s%s%d", &szName, &szPro, &nLvl);

		char szInfo[128] = {0};

		sprintf( szInfo, "%s ~%s_ %s", 
			theXmlString.GetString(eUI_YouTo), szName,
			theXmlString.GetString(eUI_SendTeam));
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Invite_Team, szInfo );

		//if(thePlayerRole.GetCampType() != CampDefine::NoneCamp)
		//{
		//	//不可以创建队伍
		//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_CampBattle_Team));
		//	return true;
		//}

		MsgRequestTeam msg;
		if( theHeroGame.GetPlayerMgr()->GetMe() )
			msg.header.stID = theHeroGame.GetPlayerMgr()->GetMe()->GetID();
		msg.dwNewbieID = -1;
        msg.AssignMode = thePlayerRole.GetAssignMode();
        msg.AssignItemLevel = thePlayerRole.GetItemRollLevel();
		strncpy(msg.szNewbieName, szName, sizeof(msg.szNewbieName)-1);
		GettheNetworkInput().SendMsg(&msg);
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_NearPlayer::ID_BUTTON_DuizhangOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_NearPlayer)
		return false;
	if (thePlayerRole.IsTeamHeader() && m_pID_LIST_TeamPlayer->GetCurSelItem() 
		&& !thePlayerRole.IsRole(m_pID_LIST_TeamPlayer->GetCurSelItem()->m_nID)
		)
	{
		MsgReqUpgradeTeam msg;
		msg.dwID = m_pID_LIST_TeamPlayer->GetCurSelItem()->m_nID;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_NearPlayer::ID_BUTTON_TiChuOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_NearPlayer)
		return false;
	if (thePlayerRole.IsTeamHeader() && m_pID_LIST_TeamPlayer->GetCurSelItem() &&
		!thePlayerRole.IsRole(m_pID_LIST_TeamPlayer->GetCurSelItem()->m_nID))	
	{
		MsgKickFromTeam msg;
		msg.dwWho = m_pID_LIST_TeamPlayer->GetCurSelItem()->m_nID;
		if (msg.dwWho != -1)
		{
			GettheNetworkInput().SendMsg( &msg );
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GroupPanel_NearPlayer::ID_BUTTON_TuichuOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GroupPanel_NearPlayer)
		return false;
	if (thePlayerRole.GetTeamInfo().size() > 1)
	{
		s_CUI_ID_FRAME_Team.CheckChangeFollowState();

		MsgExitTeam msg;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
// List
void CUI_ID_FRAME_GroupPanel_NearPlayer::ID_LIST_TeamPlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_GroupPanel_NearPlayer)
		return;
	m_pID_BUTTON_Duizhang->SetEnable(false);
	m_pID_BUTTON_TiChu->SetEnable(false);
	m_pID_BUTTON_Tuichu->SetEnable(false);
	if (thePlayerRole.GetTeamMemberNum() > 0)
	{
		m_pID_BUTTON_Tuichu->SetEnable(true);
		if (thePlayerRole.IsTeamHeader())
		{
			if (m_pID_LIST_TeamPlayer->GetCurSelItem())
			{
				if (!thePlayerRole.IsRole(m_pID_LIST_TeamPlayer->GetCurSelItem()->m_nID))
				{
					m_pID_BUTTON_Duizhang->SetEnable(true);
					m_pID_BUTTON_TiChu->SetEnable(true);
				}
			}
		}

	}
}

static void GP_OnVisibleChanged(ControlObject* pSender)
{
	if (!pSender->IsVisable() && pSender->GetFather() && pSender->GetFather()->IsVisable() && 
		s_CUI_ID_FRAME_GroupPanel.GetGroupSelect() == s_CUI_ID_FRAME_GroupPanel.GetFuJinCheckBox())
		pSender->SetVisable(true);
}

// 装载UI
bool CUI_ID_FRAME_GroupPanel_NearPlayer::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GroupPanel_NearPlayer.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GroupPanel_NearPlayer.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GroupPanel_NearPlayer::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GroupPanel_NearPlayer, s_CUI_ID_FRAME_GroupPanel_NearPlayerOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GroupPanel_NearPlayer, s_CUI_ID_FRAME_GroupPanel_NearPlayerOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_GroupPanel_NearPlayer, ID_LIST_Player, s_CUI_ID_FRAME_GroupPanel_NearPlayerID_LIST_PlayerOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_Yaoqing, s_CUI_ID_FRAME_GroupPanel_NearPlayerID_BUTTON_YaoqingOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_Duizhang, s_CUI_ID_FRAME_GroupPanel_NearPlayerID_BUTTON_DuizhangOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_TiChu, s_CUI_ID_FRAME_GroupPanel_NearPlayerID_BUTTON_TiChuOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_Tuichu, s_CUI_ID_FRAME_GroupPanel_NearPlayerID_BUTTON_TuichuOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GroupPanel_NearPlayer, ID_LIST_TeamPlayer, s_CUI_ID_FRAME_GroupPanel_NearPlayerID_LIST_TeamPlayerOnListSelectChange );

	m_pID_FRAME_GroupPanel_NearPlayer = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GroupPanel_NearPlayer );
	m_pID_LIST_Player = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_LIST_Player );
	m_pID_LIST_PlayerTitle = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_LIST_PlayerTitle );
	m_pID_LIST_TeamTitle = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_LIST_TeamTitle );
	m_pID_BUTTON_Yaoqing = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_Yaoqing );
	m_pID_BUTTON_Duizhang = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_Duizhang );
	m_pID_BUTTON_TiChu = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_TiChu );
	m_pID_BUTTON_Tuichu = (ControlButton*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_BUTTON_Tuichu );
	m_pID_LIST_TeamPlayer = (ControlList*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_LIST_TeamPlayer );
	m_pID_TEXT_PlayerName = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_TEXT_PlayerName );
	m_pID_TEXT_PlayerJob = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_TEXT_PlayerJob );
	m_pID_TEXT_PlayerLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_TEXT_PlayerLvl );
	m_pID_PICTURE_Henxian = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_PICTURE_Henxian );
	m_pID_PICTURE_Henxian2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_PICTURE_Henxian2 );
	m_pID_TEXT_TeamMate = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_TEXT_TeamMate );
	m_pID_TEXT_TeamMateLvl = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_TEXT_TeamMateLvl );
	m_pID_TEXT_TeamMateJob = (ControlText*)theUiManager.FindControl( ID_FRAME_GroupPanel_NearPlayer, ID_TEXT_TeamMateJob );
	assert( m_pID_FRAME_GroupPanel_NearPlayer );
	assert( m_pID_LIST_Player );
	assert( m_pID_BUTTON_Yaoqing );
	assert( m_pID_BUTTON_Duizhang );
	assert( m_pID_BUTTON_TiChu );
	assert( m_pID_BUTTON_Tuichu );
	assert( m_pID_LIST_TeamPlayer );
	assert( m_pID_PICTURE_Henxian );
	assert( m_pID_PICTURE_Henxian2 );

	m_pID_FRAME_GroupPanel_NearPlayer->SetMsgHoldup(false);
	m_pID_FRAME_GroupPanel_NearPlayer->enableEscKey(false);
	m_pID_FRAME_GroupPanel_NearPlayer->SetOnVisibleChangedFun(GP_OnVisibleChanged);

	//add text to title
	m_pID_LIST_PlayerTitle->HaveSelBar( false, 0 );
	m_pID_LIST_TeamTitle->HaveSelBar( false, 0 );
	m_pID_LIST_Player->SetSelBarOffset( 1 );
	m_pID_LIST_TeamPlayer->SetSelBarOffset( 1 );
	
	SetVisable(false);
	Refresh();
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GroupPanel_NearPlayer::_UnLoadUI()
{
	m_pID_FRAME_GroupPanel_NearPlayer = NULL;
	m_pID_LIST_Player = NULL;
	m_pID_LIST_PlayerTitle = NULL;
	m_pID_BUTTON_Yaoqing = NULL;
	m_pID_BUTTON_Duizhang = NULL;
	m_pID_BUTTON_TiChu = NULL;
	m_pID_BUTTON_Tuichu = NULL;
	m_pID_LIST_TeamPlayer = NULL;
	m_pID_TEXT_PlayerName = NULL;
	m_pID_TEXT_PlayerJob = NULL;
	m_pID_TEXT_PlayerLvl = NULL;
	m_pID_PICTURE_Henxian = NULL;
	m_pID_PICTURE_Henxian2 = NULL;
	m_pID_TEXT_TeamMate = NULL;
	m_pID_TEXT_TeamMateLvl = NULL;
	m_pID_TEXT_TeamMateJob = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GroupPanel_NearPlayer.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GroupPanel_NearPlayer::_IsVisable()
{
    if(!m_pID_FRAME_GroupPanel_NearPlayer)
        return false;

	return m_pID_FRAME_GroupPanel_NearPlayer->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GroupPanel_NearPlayer::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_GroupPanel_NearPlayer)
        return;

	m_pID_FRAME_GroupPanel_NearPlayer->SetVisable( bVisable );
	if (bVisable)
		Refresh();
}

void CUI_ID_FRAME_GroupPanel_NearPlayer::Refresh()
{
    if(!m_pID_FRAME_GroupPanel_NearPlayer)
        return;

	m_pID_LIST_Player->Clear();
	m_pID_LIST_TeamPlayer->Clear();
	m_pID_LIST_PlayerTitle->Clear();
	m_pID_LIST_TeamTitle->Clear();

	int n1 = 20 ;
	int n2 = 12.5 ;
	int n3 = 12.5 ;
	int n4 = 16 ;
	
	ControlList::S_String_List stTitleItem;
	stTitleItem.Begin();
	stTitleItem.AddString( n1, theXmlString.GetString(eText_StringPlayerName)/*"玩家姓名"*/ );
	stTitleItem.AddString( n2, theXmlString.GetString(eText_StringPlayerLevel)/*"玩家等级"*/ );
	stTitleItem.AddString( n3, theXmlString.GetString(eText_StringPalyerProfession)/*"玩家职业"*/ );
	stTitleItem.End();
	m_pID_LIST_PlayerTitle->AddItem( &stTitleItem );
	
	std::map< GameObjectId, CPlayer* >& playArr = theHeroGame.GetPlayerMgr()->m_mapPlayers;
	std::map<GameObjectId, CPlayer*>::iterator it, end = playArr.end();
	for( it = playArr.begin(); it != end; ++it )
	{
		if (it->second && it->second != theHeroGame.GetPlayerMgr()->GetMe() &&
			it->second->IsPlayer() && it->second->GetName() 
			&& !thePlayerRole.IsTeamMember(it->second->GetName()))
		{
			CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( it->second->GetProfession() );

			ControlList::S_String_List	stItem;
			stItem.Begin();
			stItem.AddString( n1, it->second->GetName() );
			stItem.AddString( n2, it->second->GetLevel() );
            if (pProInfo)
            {
                stItem.AddString( n3, pProInfo->m_strProShow );
            }
			stItem.End();
			
			m_pID_LIST_Player->AddItem(&stItem);
		}
	}

	n1 = 20;
 	n2 = 12.5;
 	n3 = 12.5;
	stTitleItem.clear();
	stTitleItem.Begin();
	stTitleItem.AddString( n1, "队友姓名" );
	stTitleItem.AddString( n2, "队友等级" );
	stTitleItem.AddString( n3, "队友职业" );
	stTitleItem.End();
	m_pID_LIST_TeamTitle->AddItem( &stTitleItem );

	std::vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
	if (vecPlayer.size() > 1)
	{
		for (size_t i = 0; i < vecPlayer.size(); ++i)
		{
			ControlList::S_String_List	stItem;

			CProfessionInfo *pProInfo = GetSystemConfig()->GetProessionInfoFromID( vecPlayer[i].usProfession );
	
			stItem.Begin();
			stItem.AddString( n1, vecPlayer[i].szName );
			stItem.AddString( n2, vecPlayer[i].nLvl );
            if (pProInfo)
            {
                stItem.AddString( n3, pProInfo->m_strProShow );
            }
			stItem.End();
			stItem.m_nID = vecPlayer[i].nID;
			m_pID_LIST_TeamPlayer->AddItem(&stItem);
		}
	}
	ID_LIST_PlayerOnListSelectChange(NULL,NULL);
	ID_LIST_TeamPlayerOnListSelectChange(NULL,NULL);
}