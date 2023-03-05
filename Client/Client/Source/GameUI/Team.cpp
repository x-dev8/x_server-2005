/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (7)\Team.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MeTerrain/stdafx.h"
#include "PlayerMgr.h"
#include "wsCamera.h"
#include "wsRender.h"
#include "GameMain.h"
#include "SystemConfig.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDx.h"
#include "XmlStringLanguage.h"

#include "RbtnMenu.h"
#include "AboutPeople.h"
#include "Target.h"
#include "MessageBox.h"
#include "AddFriend.h"
#include "SelfRbtnMenu.h"
#include "InfoTips.h"
#include "ScreenInfoManager.h"

#include "TeamFlag.h"
#include "CrowdCarryMainMore.h"
#include "AutoAttackSet.h"
#include "Team.h"
#include "MapConfig.h"
#include "AboutPeople.h"


extern GAME_STATE	g_GameState;

DWORD	ToneColors[] = { 0xFF00FF00, 0xFF0000FF, 0xFF6F427D };

CUI_ID_FRAME_Team s_CUI_ID_FRAME_Team;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Team, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Team, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_AcceptApplyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_TeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_TeamApplyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_TeamNearOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_Player1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_Player2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_Player3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_Player4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_Player5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_Player6OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_AcceptInviteOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_LeaveTeamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_AddFriendOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_DisBandOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_KickOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_PromoteOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_OkOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Team, ID_COMBOBOX_TeamNameOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Team, ID_COMBOBOX_ExpModeOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Team, ID_COMBOBOX_PickModeOnComboBoxChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_ApplyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_AverageOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_JoinOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_CreateTeamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_FollowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_RefuseOnButtonClick )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Team, ID_COMBOBOX_DistributeOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Team, ID_COMBOBOX_ToneOnComboBoxChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Team, ID_LIST_DistributeAccessoriesOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_FollowBreakOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_TeamInformationOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_QKLBOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_TeamInformationOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Team, ID_CHECKBOX_ApplyOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_DuorentongqiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Team, ID_BUTTON_NearOnButtonClick )
CUI_ID_FRAME_Team::CUI_ID_FRAME_Team()
{
	// Member
	m_pID_FRAME_Team = NULL;
	m_pID_CHECKBOX_AcceptApply = NULL;
	m_pID_PICTURE_BG = NULL;
	m_pID_CHECKBOX_Team = NULL;
	m_pID_CHECKBOX_TeamApply = NULL;
	m_pID_CHECKBOX_TeamNear = NULL;
	m_pID_PICTURE_Player1 = NULL;
	m_pID_PICTURE_Player2 = NULL;
	m_pID_PICTURE_Player3 = NULL;
	m_pID_PICTURE_Player4 = NULL;
	m_pID_PICTURE_Player5 = NULL;
	m_pID_PICTURE_Player6 = NULL;
	m_pID_TEXT_PlayerName2 = NULL;
	m_pID_TEXT_PlayerName3 = NULL;
	m_pID_TEXT_PlayerName4 = NULL;
	m_pID_TEXT_PlayerName5 = NULL;
	m_pID_TEXT_PlayerName6 = NULL;
	m_pID_TEXT_PlayerName1 = NULL;
	m_pID_TEXT_PlayerLevel1 = NULL;
	m_pID_TEXT_PlayerLevel2 = NULL;
	m_pID_TEXT_PlayerLevel3 = NULL;
	m_pID_TEXT_PlayerLevel4 = NULL;
	m_pID_TEXT_PlayerLevel5 = NULL;
	m_pID_TEXT_PlayerLevel6 = NULL;
	m_pID_TEXT_PlayerJob1 = NULL;
	m_pID_TEXT_PlayerJob2 = NULL;
	m_pID_TEXT_PlayerJob3 = NULL;
	m_pID_TEXT_PlayerJob4 = NULL;
	m_pID_TEXT_PlayerJob5 = NULL;
	m_pID_TEXT_PlayerJob6 = NULL;
	m_pID_TEXT_PlayerScene1 = NULL;
	m_pID_TEXT_PlayerScene2 = NULL;
	m_pID_TEXT_PlayerScene3 = NULL;
	m_pID_TEXT_PlayerScene4 = NULL;
	m_pID_TEXT_PlayerScene5 = NULL;
	m_pID_TEXT_PlayerScene6 = NULL;
	m_pID_TEXT_Near = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_FriendAttribute = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_Player1 = NULL;
	m_pID_CHECKBOX_Player2 = NULL;
	m_pID_CHECKBOX_Player3 = NULL;
	m_pID_CHECKBOX_Player4 = NULL;
	m_pID_CHECKBOX_Player5 = NULL;
	m_pID_CHECKBOX_Player6 = NULL;
	m_pID_TEXT_AcceptApplyText = NULL;
	m_pID_PICTURE_AcceptInviteText = NULL;
	m_pID_CHECKBOX_AcceptInvite = NULL;
	m_pID_TEXT_Captain = NULL;
	m_pID_BUTTON_LeaveTeam = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	m_pID_BUTTON_DisBand = NULL;
	m_pID_BUTTON_Kick = NULL;
	m_pID_BUTTON_Promote = NULL;
	m_pID_PICTURE_TeamNameText = NULL;
	m_pID_PICTURE_ExpModeText = NULL;
	m_pID_PICTURE_PickModeText = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_PICTURE_NotTeam = NULL;
	m_pID_COMBOBOX_TeamName = NULL;
	m_pID_COMBOBOX_ExpMode = NULL;
	m_pID_COMBOBOX_PickMode = NULL;
	m_pID_PICTURE_TitleSetUp = NULL;
	m_pID_BUTTON_Apply = NULL;
	m_pID_BUTTON_Average = NULL;
	m_pID_BUTTON_Join = NULL;
	m_pID_BUTTON_CreateTeam = NULL;
	m_pID_BUTTON_Follow = NULL;
	m_pID_BUTTON_Refuse = NULL;
	m_pID_PICTURE_TitleNow = NULL;
	m_pID_PICTURE_TitleTeamApplication = NULL;
	m_pID_COMBOBOX_Distribute = NULL;
	m_pID_COMBOBOX_Tone = NULL;
	//m_pID_LIST_DistributeAccessories = NULL;
	m_pID_BUTTON_FollowBreak = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_QKLB = NULL;
	m_pID_CHECKBOX_TeamInformation = NULL;
	m_pID_CHECKBOX_Apply = NULL;
	//m_pID_BUTTON_Duorentongqi = NULL;
	m_pID_BUTTON_Near = NULL;


	m_PlayerAnim = NULL;
	m_pPlayer = NULL;

	for ( int i = 0; i < MAX_TEAMSIZE; i ++ )
	{
		m_pPlayers[i] = NULL;
		m_PlayerAnims[i] = NULL;
	}
	

	m_bIsTeamLead = false;
	m_bInRequestState = false;

	m_nCurTeamCount = 0;
	m_nSelectedIdx = -1;
	m_nTeamFollowID = -1;

	m_nRequestStartIdx = 0;
	m_nRequestPageIdx = 0;
	m_nTeamFollowCount = 0;

	Clear_Time = 0;
}

CUI_ID_FRAME_Team::~CUI_ID_FRAME_Team()
{
	//DestroyAnimCtrl();
}
// Frame
bool CUI_ID_FRAME_Team::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_Team::OnFrameRender()
{
	for ( int i = 0; i < m_nCurTeamCount; i ++ )
	{
		GetEngine()->GetRenderer()->EndScene();
		if ( i == 0 )
		{
			RenderPlayers( m_pID_PICTURE_Player1, i );
		}
		else if ( i == 1 )
		{
			RenderPlayers( m_pID_PICTURE_Player2, i );
		}
		else if ( i == 2 )
		{
			RenderPlayers( m_pID_PICTURE_Player3, i );
		}
		else if ( i == 3 )
		{
			RenderPlayers( m_pID_PICTURE_Player4, i );
		}
		else if ( i == 4 )
		{
			RenderPlayers( m_pID_PICTURE_Player5, i );
		}
		else if ( i == 5 )
		{
			RenderPlayers( m_pID_PICTURE_Player6, i );
		}
		
		GetEngine()->GetRenderer()->BeginScene();
	}

	

	return true;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_NearOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_AboutPeople.SetVisable( true );
	return true;
}

// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_AcceptApplyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_TeamApplyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_TeamNearOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_Player1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{

	if ( !m_pID_FRAME_Team )
		return;

	//没有数据的位置不能选
	if ( m_nCurTeamCount < 1 )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();
	
	std::string playerName(m_pID_TEXT_PlayerName1->GetText());
	m_CurSelectedName = playerName;
	m_nSelectedIdx = 0;
	if ( !playerName.empty() && thePlayerRole.CanAddFriend(playerName.c_str()) && player && playerName.compare(player->GetName()) != 0 )
	{
		m_pID_BUTTON_AddFriend->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFriend->SetEnable(false);
	}
	
	//能看到这个按钮的只有队长,第一按钮位置默认的队长显示位置
	m_pID_BUTTON_Kick->SetEnable(false);
	m_pID_BUTTON_Promote->SetEnable(false);

	
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_Player2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;

	//没有数据的位置不能选
	if ( m_nCurTeamCount < 2 )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();

	std::string playerName(m_pID_TEXT_PlayerName2->GetText());
	m_CurSelectedName = playerName;
	m_nSelectedIdx = 1;
	if ( !playerName.empty() && thePlayerRole.CanAddFriend(playerName.c_str()) && player && playerName.compare(player->GetName()) != 0 )
	{
		m_pID_BUTTON_AddFriend->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFriend->SetEnable(false);
	}

	//当选中队友，只有自己是队长的时候才显示为可用
	if ( thePlayerRole.IsTeamHeader() )
	{
		m_pID_BUTTON_Kick->SetEnable(true);
		m_pID_BUTTON_Promote->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Kick->SetEnable(false);
		m_pID_BUTTON_Promote->SetEnable(false);
	}

}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_Player3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;

	//没有数据的位置不能选
	if ( m_nCurTeamCount < 3 )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();

	std::string playerName(m_pID_TEXT_PlayerName3->GetText());
	m_CurSelectedName = playerName;
	m_nSelectedIdx = 2;
	if ( !playerName.empty() && thePlayerRole.CanAddFriend(playerName.c_str()) && player && playerName.compare(player->GetName()) != 0 )
	{
		m_pID_BUTTON_AddFriend->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFriend->SetEnable(false);
	}

	//当选中队友，只有自己是队长的时候才显示为可用
	if ( thePlayerRole.IsTeamHeader() )
	{
		m_pID_BUTTON_Kick->SetEnable(true);
		m_pID_BUTTON_Promote->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Kick->SetEnable(false);
		m_pID_BUTTON_Promote->SetEnable(false);
	}

}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_Player4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;

	//没有数据的位置不能选
	if ( m_nCurTeamCount < 4 )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();

	std::string playerName(m_pID_TEXT_PlayerName4->GetText());
	m_CurSelectedName = playerName;
	m_nSelectedIdx = 3;
	if ( !playerName.empty() && thePlayerRole.CanAddFriend(playerName.c_str()) && player && playerName.compare(player->GetName()) != 0 )
	{
		m_pID_BUTTON_AddFriend->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFriend->SetEnable(false);
	}

	//当选中队友，只有自己是队长的时候才显示为可用
	if ( thePlayerRole.IsTeamHeader() )
	{
		m_pID_BUTTON_Kick->SetEnable(true);
		m_pID_BUTTON_Promote->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Kick->SetEnable(false);
		m_pID_BUTTON_Promote->SetEnable(false);
	}

}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_Player5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;

	//没有数据的位置不能选
	if ( m_nCurTeamCount < 5 )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}

	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();

	std::string playerName(m_pID_TEXT_PlayerName5->GetText());
	m_CurSelectedName = playerName;
	m_nSelectedIdx = 4;
	if ( !playerName.empty() && thePlayerRole.CanAddFriend(playerName.c_str()) && player && playerName.compare(player->GetName()) != 0 )
	{
		m_pID_BUTTON_AddFriend->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFriend->SetEnable(false);
	}

	//当选中队友，只有自己是队长的时候才显示为可用
	if ( thePlayerRole.IsTeamHeader() )
	{
		m_pID_BUTTON_Kick->SetEnable(true);
		m_pID_BUTTON_Promote->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Kick->SetEnable(false);
		m_pID_BUTTON_Promote->SetEnable(false);
	}

}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_Player6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;

	//没有数据的位置不能选
	if ( m_nCurTeamCount < 6 )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}


	UncheckedAll();
	((ControlCheckBox*)pSender)->SetCheck(true);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();

	std::string playerName(m_pID_TEXT_PlayerName6->GetText());
	m_CurSelectedName = playerName;
	m_nSelectedIdx = 5;
	if ( !playerName.empty() && thePlayerRole.CanAddFriend(playerName.c_str()) && player && playerName.compare(player->GetName()) != 0 )
	{
		m_pID_BUTTON_AddFriend->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFriend->SetEnable(false);
	}

	//当选中队友，只有自己是队长的时候才显示为可用
	if ( thePlayerRole.IsTeamHeader() )
	{
		m_pID_BUTTON_Kick->SetEnable(true);
		m_pID_BUTTON_Promote->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_Kick->SetEnable(false);
		m_pID_BUTTON_Promote->SetEnable(false);
	}
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_AcceptInviteOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;
}

bool CallBack_AskLeaveTeam( char bIsTell, void *pData )
{
	if ( bIsTell != 0 )
	{
		s_CUI_ID_FRAME_Team.CheckChangeFollowState();
		MsgExitTeam msg;
		GettheNetworkInput().SendMsg( &msg );
		s_CUI_ID_FRAME_Team.SetVisable(false);
	}
	
	return true;
}

// Button 离队
bool CUI_ID_FRAME_Team::ID_BUTTON_LeaveTeamOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	s_CUI_ID_FRAME_MessageBox.Show(
		theXmlString.GetString(eText_Team_LeaveTeamYESNO),				
		"",
		CUI_ID_FRAME_MessageBox::eTypeYesNo,
		true,
		CallBack_AskLeaveTeam );

	return true;
}
// Button   加为好友
bool CUI_ID_FRAME_Team::ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriendFromRMenu );
	s_CUI_ID_FRAME_AddFriend.SetPrivateName(m_CurSelectedName.c_str());
	s_CUI_ID_FRAME_AddFriend.SetVisable(true);

	return true;
}

bool CallBack_AskDisBandTeam( char bIsTell, void *pData )
{
	if ( bIsTell != 0 )
	{
		//服务器要求，队长解散队伍要提前发送一条取消跟随的消息
		CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();
		if ( player && s_CUI_ID_FRAME_Team.IsTeamLeader( player->GetName() ) )
		{
			MsgHeaderCancelTeamFollow msg;
			GettheNetworkInput().SendMsg(&msg);
		}

		MsgDisbandTeam msg;
		GettheNetworkInput().SendMsg( &msg );
		s_CUI_ID_FRAME_Team.SetVisable(false);
	}
	return true;
}

// Button 解散
bool CUI_ID_FRAME_Team::ID_BUTTON_DisBandOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	s_CUI_ID_FRAME_MessageBox.Show(
		theXmlString.GetString(eText_Team_DisbandTeamYESNO),				
		"",
		CUI_ID_FRAME_MessageBox::eTypeYesNo,
		true,
		CallBack_AskDisBandTeam );

	return true;
}

bool CallBack_AskKickMemberOut( char bIsTell, void *pData )
{
	if ( bIsTell != 0 )
	{
		MsgKickFromTeam msg;
		msg.dwWho = *(DWORD*)pData;
		GettheNetworkInput().SendMsg( &msg );
	}
	
	return true;
}

// Button 踢出队伍
bool CUI_ID_FRAME_Team::ID_BUTTON_KickOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	int idx = GetTeamIdx( m_CurSelectedName.c_str() );
	if (idx != -1)
	{
		char tmpStr[256] = {0};
		MeSprintf( tmpStr, sizeof(tmpStr) - 1, theXmlString.GetString(eText_Team_KickSomeoneOffYESNO), m_CurSelectedName.c_str() );

		s_CUI_ID_FRAME_MessageBox.Show(
			tmpStr,
			"",
			CUI_ID_FRAME_MessageBox::eTypeYesNo,
			true,
			CallBack_AskKickMemberOut, &idx, sizeof(idx) );
	}

	return true;
}

bool CallBack_AskPromote( char bIsTell, void *pData )
{
	if ( bIsTell != 0 && pData != NULL )
	{
		MsgReqUpgradeTeam msg;
		msg.dwID = *(DWORD*)pData;
		GettheNetworkInput().SendMsg( &msg );
	}

	return true;
}

// Button 提升队长
bool CUI_ID_FRAME_Team::ID_BUTTON_PromoteOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	if ( m_nSelectedIdx == 0 )
	{
		//队长不能提升自己
		return true;
	}

	int idx = GetTeamIdx( m_CurSelectedName.c_str() );
	if ( idx == -1 )
	{
		return true;
	}
	
	
	char tmpStr[256] = {0};
	MeSprintf( tmpStr, sizeof(tmpStr), theXmlString.GetString(eText_Team_PromotLeaderYESNO), m_CurSelectedName.c_str() );  
	s_CUI_ID_FRAME_MessageBox.Show(
		tmpStr,	
		"",
		CUI_ID_FRAME_MessageBox::eTypeYesNo,
		true,
		CallBack_AskPromote, &idx, sizeof(idx) );

	return true;
}
// Button 确定（接收）
bool CUI_ID_FRAME_Team::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	int idx = m_nSelectedIdx + m_nRequestStartIdx;
	if ( idx < 0 || idx >= m_vecRequesterSet.size() )
	{
		return false;
	}
	
	MsgAckInquireInvitee msg;

	msg.bAgree = 1;
	msg.dwReqID = m_vecRequesterSet[idx].dwReqID;
	msg.AssignMode = m_vecRequesterSet[idx].AssignMode;
	msg.AssignItemLevel = m_vecRequesterSet[idx].AssignItemLevel;
	GettheNetworkInput().SendMsg(&msg);

	m_vecRequesterSet.erase(m_vecRequesterSet.begin() + idx);
	RefreshView();

	return true;
}
// ComboBox
void CUI_ID_FRAME_Team::ID_COMBOBOX_TeamNameOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// ComboBox
void CUI_ID_FRAME_Team::ID_COMBOBOX_ExpModeOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// ComboBox
void CUI_ID_FRAME_Team::ID_COMBOBOX_PickModeOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// Button 切换到队伍申请界面
bool CUI_ID_FRAME_Team::ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	//尝试获取组队请求信息
	s_CUI_ID_FRAME_InfoTips.ID_BUTTON_Tips1OnButtonClick(NULL);
	SetRequestView();
	RefreshPageInfo();

	return true;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_AverageOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_JoinOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	
	theHeroGame.SetStateCursor(MouseManager::Type_Group);//暂时用这个光标代替表示请求或则邀请组队
	SetInRequestState(true);

	this->SetVisable( false );
	return true;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_CreateTeamOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	//战场中不可以创建队伍
	//if(thePlayerRole.GetCampType() != CampDefine::NoneCamp)
	//{
	//	//不可以创建队伍
	//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_CampBattle_Team));
	//	return true;
	//}

	MsgCreateTeam msg;
	sprintf( msg.szTeamName, "%s", "testTeam" );
	msg.AssignMode = thePlayerRole.GetAssignMode();
	msg.AssignItemLevel = thePlayerRole.GetItemRollLevel();
	GettheNetworkInput().SendMsg(&msg);

	SetCurrentView();

	return true;
}
// Button 组队跟随
bool CUI_ID_FRAME_Team::ID_BUTTON_FollowOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	
	MsgReqTeamFollow msg;
	GettheNetworkInput().SendMsg(&msg);

	
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_Team_InviteFollowInfoSend) );
	
	return true;
}
// Button 拒绝
bool CUI_ID_FRAME_Team::ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	int idx = m_nSelectedIdx + m_nRequestStartIdx;
	if ( idx < 0 || idx >= m_vecRequesterSet.size() )
	{
		return false;
	}

	MsgAckInquireInvitee msg;

	msg.bAgree = 0;
	msg.dwReqID = m_vecRequesterSet[idx].dwReqID;
	msg.AssignMode = m_vecRequesterSet[idx].AssignMode;
	msg.AssignItemLevel = m_vecRequesterSet[idx].AssignItemLevel;
	GettheNetworkInput().SendMsg(&msg);

	m_vecRequesterSet.erase(m_vecRequesterSet.begin() + idx);
	RefreshView();

	return true;
}
// ComboBox  分配模式改变
void CUI_ID_FRAME_Team::ID_COMBOBOX_DistributeOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Team )
		return;
	//if ( m_pID_COMBOBOX_Distribute->GetListBox().GetCurSelIndex() == 0 )
	//{
	//	m_pID_COMBOBOX_Tone->SetEnable(false);
	//	m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(-1);
	//	m_pID_COMBOBOX_Tone->GetEditInput().SetText("");

	//	bool bMeIsHeader = thePlayerRole.IsTeamHeader();
	//	if( bMeIsHeader )
	//	{
	//		//s_CUI_ID_FRAME_RBTNMENU.CheckSetAssignMode();
	//		//if( thePlayerRole.GetItemRollLevel() != eIL_Choiceness )
	//		//{
	//		//	s_CUI_ID_FRAME_RBTNMENU.SetQuality(eIL_Choiceness);
	//		//}
	//		if( thePlayerRole.GetAssignMode() != AssignMode_FreeMode )  //这里防止控件事件在相同模式下也会发送消息
	//		{
	//			s_CUI_ID_FRAME_SelfRBMenu.SetAssignMode(AssignMode_FreeMode);
	//		}
	//		m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(-1);
	//		m_pID_COMBOBOX_Tone->GetEditInput().SetText("");
	//	}
	//}
	//else if ( m_pID_COMBOBOX_Distribute->GetListBox().GetCurSelIndex() == 1 )	
	//{
	//	m_pID_COMBOBOX_Tone->SetEnable(true);

	//	bool bMeIsHeader = thePlayerRole.IsTeamHeader();
	//	if( bMeIsHeader )
	//	{
	//		if( thePlayerRole.GetAssignMode() != AssignMode_Team )
	//		{
	//			s_CUI_ID_FRAME_SelfRBMenu.SetAssignMode(AssignMode_Team);
	//		}
	//	}

	//	m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(0);
	//	m_pID_COMBOBOX_Tone->GetEditInput().SetText(m_pID_COMBOBOX_Tone->GetListBox().GetCurSelItem()->m_szText) ;
	//	m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor( ToneColors[0] );
	//}
	//else if ( m_pID_COMBOBOX_Distribute->GetListBox().GetCurSelIndex() == 2 )
	//{
	//	m_pID_COMBOBOX_Tone->SetEnable(true);

	//	bool bMeIsHeader = thePlayerRole.IsTeamHeader();
	//	if( bMeIsHeader )
	//	{
	//		if( thePlayerRole.GetAssignMode() != AssignMode_Assign )
	//		{
	//			s_CUI_ID_FRAME_SelfRBMenu.SetAssignMode(AssignMode_Assign);
	//		}
	//	}

	//	m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(0);
	//	m_pID_COMBOBOX_Tone->GetEditInput().SetText(m_pID_COMBOBOX_Tone->GetListBox().GetCurSelItem()->m_szText) ;
	//	m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor( ToneColors[0] );
	//}
	
	

}
// ComboBox
void CUI_ID_FRAME_Team::ID_COMBOBOX_ToneOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_Team )
		return;

	if( m_pID_COMBOBOX_Tone->GetListBox().GetCurSelIndex() == 0 )
	{
		m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor(ToneColors[0]);
		bool bMeIsHeader = thePlayerRole.IsTeamHeader();
		if( bMeIsHeader )
		{
			if( thePlayerRole.GetItemRollLevel() != eIL_Choiceness )
			{
				s_CUI_ID_FRAME_SelfRBMenu.SetQuality(eIL_Choiceness);
			}
		}
	}
	else if ( m_pID_COMBOBOX_Tone->GetListBox().GetCurSelIndex() == 1 )
	{
		m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor(ToneColors[1]);
		bool bMeIsHeader = thePlayerRole.IsTeamHeader();
		if( bMeIsHeader )
		{
			if( thePlayerRole.GetItemRollLevel() != eIL_Polish )
			{
				s_CUI_ID_FRAME_SelfRBMenu.SetQuality(eIL_Polish);
			}
		}
	}
	else if ( m_pID_COMBOBOX_Tone->GetListBox().GetCurSelIndex() == 2 )
	{
		m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor(ToneColors[2]);
		bool bMeIsHeader = thePlayerRole.IsTeamHeader();
		if( bMeIsHeader )
		{
			if( thePlayerRole.GetItemRollLevel() != eIL_Nonsuch )
			{
				s_CUI_ID_FRAME_SelfRBMenu.SetQuality(eIL_Nonsuch);
			}
		}
	}


}
// List
void CUI_ID_FRAME_Team::ID_LIST_DistributeAccessoriesOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_Team )
		return;
}
// Button  取消跟随
bool CUI_ID_FRAME_Team::ID_BUTTON_FollowBreakOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	if ( GetTeamFollowID() >= 0 )
	{
		//这个只有队友才会处理
		SetTeamFollowID( -1 );
		m_pID_BUTTON_FollowBreak->SetVisable(false);
	}

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();
	if ( player && IsTeamLeader( player->GetName() ) )
	{
		MsgHeaderCancelTeamFollow msg;
		GettheNetworkInput().SendMsg(&msg);
	}
	else
	{
		MsgCancelTeamFollow msg;
		GettheNetworkInput().SendMsg(&msg);
	}
	

	

	return true;
}
// 切换到当前视图界面
bool CUI_ID_FRAME_Team::ID_BUTTON_TeamInformationOnButtonClick( ControlObject* pSender )
{
	SetCurrentView();
	
	return true;
}

// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	m_nRequestPageIdx --;
	RefreshPageInfo();
	return true;
}
// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;
	m_nRequestPageIdx ++;
	RefreshPageInfo();
	return true;
}

bool CallBack_AskClearList( char bIsTell, void *pData )
{
	if ( bIsTell != 0 )
	{
		std::vector<TeamRequestInfo>& vecRequesterSet = s_CUI_ID_FRAME_Team.GetRequestList();
		int count = (int)vecRequesterSet.size();
		for ( int idx = 0; idx < count; idx ++ )
		{
			MsgAckInquireInvitee msg;

			msg.bAgree = 0;
			msg.dwReqID = vecRequesterSet[idx].dwReqID;
			msg.AssignMode = vecRequesterSet[idx].AssignMode;
			msg.AssignItemLevel = vecRequesterSet[idx].AssignItemLevel;
			GettheNetworkInput().SendMsg(&msg);

			//m_vecRequesterSet.erase(m_vecRequesterSet.begin() + idx);
		}
		vecRequesterSet.clear();

		s_CUI_ID_FRAME_Team.RefreshView();
	}
	return true;
}

// Button  清空  申请列表
bool CUI_ID_FRAME_Team::ID_BUTTON_QKLBOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	if ( m_vecRequesterSet.size() == 0 )
	{
		return false;
	}

	s_CUI_ID_FRAME_MessageBox.Show(
		theXmlString.GetString(eText_Team_ClearListYESNO),				
		"",
		CUI_ID_FRAME_MessageBox::eTypeYesNo,
		true,
		CallBack_AskClearList );
	

	return true;
}

// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_TeamInformationOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;
	m_pID_CHECKBOX_Apply->SetCheck(false);
	SetCurrentView();
}
// CheckBox
void CUI_ID_FRAME_Team::ID_CHECKBOX_ApplyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_Team )
		return;

	if ( IsTeamLeader( thePlayerRole.GetName() ) == false )
	{
		((ControlCheckBox*)pSender)->SetCheck(false);
		return;
	}

	m_pID_CHECKBOX_TeamInformation->SetCheck(false);

	//尝试获取组队请求信息
	s_CUI_ID_FRAME_InfoTips.ID_BUTTON_Tips1OnButtonClick(NULL);
	SetRequestView();
	RefreshPageInfo();
}

// Button
bool CUI_ID_FRAME_Team::ID_BUTTON_DuorentongqiOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_Team )
		return false;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( pMe )
	{
		if ( pMe->IsMultiMounting() )
		{
			std::vector<TeamInfo> infos = thePlayerRole.GetTeamInfo();
			int count = (int)infos.size();
			for ( int i = 0; i < count; i ++ )
			{
				CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName( infos[i].szName.c_str() );
				if ( pPlayer && pMe->GetID() != pPlayer->GetID() && s_CUI_ID_FRAME_CrowdCarryMainMore.IsOnYourBoard( pPlayer->GetID() ) == false )
				{
					MsgReqGotOnDrome reqMsg;
					reqMsg.type = MsgReqGotOnDrome::EOperateType_Invite;
					reqMsg.driverId = pMe->GetID();
					reqMsg.riderId = pPlayer->GetID();
					GettheNetworkInput().SendMsg( &reqMsg );
				}
			}
			
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_NoMultiMount) );
		}
		
	}


	return true;
}

// 装载UI
bool CUI_ID_FRAME_Team::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Team.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Team.MEUI]失败")
		return false;
	}
	s_CUI_ID_FRAME_TeamFlag._LoadUI();
	return DoControlConnect();
}

bool UITeam_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if ( bMsgUsed == true || g_GameState != G_MAIN  )
		return false;

	switch( msg ) 
	{
	case WM_KEYDOWN:
		{
			if( theUiManager.GetFocus() )
			{//输入框获得焦点的话。
				if(theUiManager.GetFocus()->GetControlType() == Type_Edit)
				{
					break;
				}
			}
			if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_TeamRequest) )
			{
				s_CUI_ID_FRAME_Team.ID_BUTTON_JoinOnButtonClick( s_CUI_ID_FRAME_Team.m_pID_BUTTON_Join );
			}
			
		}
	}
	return false;
}


// 关连控件
bool CUI_ID_FRAME_Team::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Team, s_CUI_ID_FRAME_TeamOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Team, s_CUI_ID_FRAME_TeamOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_AcceptApply, s_CUI_ID_FRAME_TeamID_CHECKBOX_AcceptApplyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Team, s_CUI_ID_FRAME_TeamID_CHECKBOX_TeamOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_TeamApply, s_CUI_ID_FRAME_TeamID_CHECKBOX_TeamApplyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_TeamNear, s_CUI_ID_FRAME_TeamID_CHECKBOX_TeamNearOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_HELP, s_CUI_ID_FRAME_TeamID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_TeamID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Player1, s_CUI_ID_FRAME_TeamID_CHECKBOX_Player1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Player2, s_CUI_ID_FRAME_TeamID_CHECKBOX_Player2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Player3, s_CUI_ID_FRAME_TeamID_CHECKBOX_Player3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Player4, s_CUI_ID_FRAME_TeamID_CHECKBOX_Player4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Player5, s_CUI_ID_FRAME_TeamID_CHECKBOX_Player5OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Player6, s_CUI_ID_FRAME_TeamID_CHECKBOX_Player6OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_AcceptInvite, s_CUI_ID_FRAME_TeamID_CHECKBOX_AcceptInviteOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_LeaveTeam, s_CUI_ID_FRAME_TeamID_BUTTON_LeaveTeamOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_AddFriend, s_CUI_ID_FRAME_TeamID_BUTTON_AddFriendOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_DisBand, s_CUI_ID_FRAME_TeamID_BUTTON_DisBandOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Kick, s_CUI_ID_FRAME_TeamID_BUTTON_KickOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Promote, s_CUI_ID_FRAME_TeamID_BUTTON_PromoteOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Ok, s_CUI_ID_FRAME_TeamID_BUTTON_OkOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_Team, ID_COMBOBOX_TeamName, s_CUI_ID_FRAME_TeamID_COMBOBOX_TeamNameOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Team, ID_COMBOBOX_ExpMode, s_CUI_ID_FRAME_TeamID_COMBOBOX_ExpModeOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Team, ID_COMBOBOX_PickMode, s_CUI_ID_FRAME_TeamID_COMBOBOX_PickModeOnComboBoxChange );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Apply, s_CUI_ID_FRAME_TeamID_BUTTON_ApplyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Average, s_CUI_ID_FRAME_TeamID_BUTTON_AverageOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Join, s_CUI_ID_FRAME_TeamID_BUTTON_JoinOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_CreateTeam, s_CUI_ID_FRAME_TeamID_BUTTON_CreateTeamOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Follow, s_CUI_ID_FRAME_TeamID_BUTTON_FollowOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Refuse, s_CUI_ID_FRAME_TeamID_BUTTON_RefuseOnButtonClick );
	theUiManager.OnComboBoxChange( ID_FRAME_Team, ID_COMBOBOX_Distribute, s_CUI_ID_FRAME_TeamID_COMBOBOX_DistributeOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Team, ID_COMBOBOX_Tone, s_CUI_ID_FRAME_TeamID_COMBOBOX_ToneOnComboBoxChange );
	theUiManager.OnListSelectChange( ID_FRAME_Team, ID_LIST_DistributeAccessories, s_CUI_ID_FRAME_TeamID_LIST_DistributeAccessoriesOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_FollowBreak, s_CUI_ID_FRAME_TeamID_BUTTON_FollowBreakOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_TeamInformation, s_CUI_ID_FRAME_TeamID_BUTTON_TeamInformationOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_PageUp, s_CUI_ID_FRAME_TeamID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_PageDown, s_CUI_ID_FRAME_TeamID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_QKLB, s_CUI_ID_FRAME_TeamID_BUTTON_QKLBOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_TeamInformation, s_CUI_ID_FRAME_TeamID_CHECKBOX_TeamInformationOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Team, ID_CHECKBOX_Apply, s_CUI_ID_FRAME_TeamID_CHECKBOX_ApplyOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Duorentongqi, s_CUI_ID_FRAME_TeamID_BUTTON_DuorentongqiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Team, ID_BUTTON_Near, s_CUI_ID_FRAME_TeamID_BUTTON_NearOnButtonClick );

	m_pID_FRAME_Team = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Team );
	m_pID_CHECKBOX_AcceptApply = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_AcceptApply );
	m_pID_PICTURE_BG = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_BG );
	m_pID_CHECKBOX_Team = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Team );
	m_pID_CHECKBOX_TeamApply = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_TeamApply );
	m_pID_CHECKBOX_TeamNear = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_TeamNear );
	m_pID_PICTURE_Player1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_Player1 );
	m_pID_PICTURE_Player2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_Player2 );
	m_pID_PICTURE_Player3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_Player3 );
	m_pID_PICTURE_Player4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_Player4 );
	m_pID_PICTURE_Player5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_Player5 );
	m_pID_PICTURE_Player6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_Player6 );
	m_pID_TEXT_PlayerName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerName2 );
	m_pID_TEXT_PlayerName3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerName3 );
	m_pID_TEXT_PlayerName4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerName4 );
	m_pID_TEXT_PlayerName5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerName5 );
	m_pID_TEXT_PlayerName6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerName6 );
	m_pID_TEXT_PlayerName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerName1 );
	m_pID_TEXT_PlayerLevel1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerLevel1 );
	m_pID_TEXT_PlayerLevel2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerLevel2 );
	m_pID_TEXT_PlayerLevel3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerLevel3 );
	m_pID_TEXT_PlayerLevel4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerLevel4 );
	m_pID_TEXT_PlayerLevel5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerLevel5 );
	m_pID_TEXT_PlayerLevel6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerLevel6 );
	m_pID_TEXT_PlayerJob1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerJob1 );
	m_pID_TEXT_PlayerJob2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerJob2 );
	m_pID_TEXT_PlayerJob3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerJob3 );
	m_pID_TEXT_PlayerJob4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerJob4 );
	m_pID_TEXT_PlayerJob5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerJob5 );
	m_pID_TEXT_PlayerJob6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerJob6 );
	m_pID_TEXT_PlayerScene1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerScene1 );
	m_pID_TEXT_PlayerScene2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerScene2 );
	m_pID_TEXT_PlayerScene3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerScene3 );
	m_pID_TEXT_PlayerScene4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerScene4 );
	m_pID_TEXT_PlayerScene5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerScene5 );
	m_pID_TEXT_PlayerScene6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_PlayerScene6 );
	m_pID_TEXT_Near = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_Near );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_Exp );
	m_pID_TEXT_FriendAttribute = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_FriendAttribute );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_HELP );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_CLOSE );
	m_pID_CHECKBOX_Player1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Player1 );
	m_pID_CHECKBOX_Player2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Player2 );
	m_pID_CHECKBOX_Player3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Player3 );
	m_pID_CHECKBOX_Player4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Player4 );
	m_pID_CHECKBOX_Player5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Player5 );
	m_pID_CHECKBOX_Player6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Player6 );
	m_pID_TEXT_AcceptApplyText = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_AcceptApplyText );
	m_pID_PICTURE_AcceptInviteText = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_AcceptInviteText );
	m_pID_CHECKBOX_AcceptInvite = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_AcceptInvite );
	m_pID_TEXT_Captain = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_Captain );
	m_pID_BUTTON_LeaveTeam = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_LeaveTeam );
	m_pID_BUTTON_AddFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_AddFriend );
	m_pID_BUTTON_DisBand = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_DisBand );
	m_pID_BUTTON_Kick = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Kick );
	m_pID_BUTTON_Promote = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Promote );
	m_pID_PICTURE_TeamNameText = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_TeamNameText );
	m_pID_PICTURE_ExpModeText = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_ExpModeText );
	m_pID_PICTURE_PickModeText = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_PickModeText );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Ok );
	m_pID_PICTURE_NotTeam = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_NotTeam );
	m_pID_COMBOBOX_TeamName = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Team, ID_COMBOBOX_TeamName );
	m_pID_COMBOBOX_ExpMode = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Team, ID_COMBOBOX_ExpMode );
	m_pID_COMBOBOX_PickMode = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Team, ID_COMBOBOX_PickMode );
	m_pID_PICTURE_TitleSetUp = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_TitleSetUp );
	m_pID_BUTTON_Apply = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Apply );
	m_pID_BUTTON_Average = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Average );
	m_pID_BUTTON_Join = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Join );
	m_pID_BUTTON_CreateTeam = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_CreateTeam );
	m_pID_BUTTON_Follow = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Follow );
	m_pID_BUTTON_Refuse = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Refuse );
	m_pID_PICTURE_TitleNow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_TitleNow );
	m_pID_PICTURE_TitleTeamApplication = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Team, ID_PICTURE_TitleTeamApplication );
	m_pID_COMBOBOX_Distribute = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Team, ID_COMBOBOX_Distribute );
	m_pID_COMBOBOX_Tone = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Team, ID_COMBOBOX_Tone );
	m_pID_TEXT_String0 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_String0 );
	m_pID_TEXT_String1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_String1 );
	//m_pID_LIST_DistributeAccessories = (ControlList*)theUiManager.FindControl( ID_FRAME_Team, ID_LIST_DistributeAccessories );
	m_pID_BUTTON_FollowBreak = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_FollowBreak );
	m_pID_BUTTON_TeamInformation = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_TeamInformation );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_PageUp );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_PageDown );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_Team, ID_TEXT_Page );
	m_pID_BUTTON_QKLB = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_QKLB );
	m_pID_CHECKBOX_TeamInformation = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_TeamInformation );
	m_pID_CHECKBOX_Apply = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Team, ID_CHECKBOX_Apply );
	//m_pID_BUTTON_Duorentongqi = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Duorentongqi );
	m_pID_BUTTON_Near = (ControlButton*)theUiManager.FindControl( ID_FRAME_Team, ID_BUTTON_Near );

	assert( m_pID_FRAME_Team );
	assert( m_pID_CHECKBOX_AcceptApply );
	assert( m_pID_PICTURE_BG );
	assert( m_pID_CHECKBOX_Team );
	assert( m_pID_CHECKBOX_TeamApply );
	assert( m_pID_CHECKBOX_TeamNear );
	assert( m_pID_PICTURE_Player1 );
	assert( m_pID_PICTURE_Player2 );
	assert( m_pID_PICTURE_Player3 );
	assert( m_pID_PICTURE_Player4 );
	assert( m_pID_PICTURE_Player5 );
	assert( m_pID_PICTURE_Player6 );
	assert( m_pID_TEXT_PlayerName2 );
	assert( m_pID_TEXT_PlayerName3 );
	assert( m_pID_TEXT_PlayerName4 );
	assert( m_pID_TEXT_PlayerName5 );
	assert( m_pID_TEXT_PlayerName6 );
	assert( m_pID_TEXT_PlayerName1 );
	assert( m_pID_TEXT_PlayerLevel1 );
	assert( m_pID_TEXT_PlayerLevel2 );
	assert( m_pID_TEXT_PlayerLevel3 );
	assert( m_pID_TEXT_PlayerLevel4 );
	assert( m_pID_TEXT_PlayerLevel5 );
	assert( m_pID_TEXT_PlayerLevel6 );
	assert( m_pID_TEXT_PlayerJob1 );
	assert( m_pID_TEXT_PlayerJob2 );
	assert( m_pID_TEXT_PlayerJob3 );
	assert( m_pID_TEXT_PlayerJob4 );
	assert( m_pID_TEXT_PlayerJob5 );
	assert( m_pID_TEXT_PlayerJob6 );
	assert( m_pID_TEXT_PlayerScene1 );
	assert( m_pID_TEXT_PlayerScene2 );
	assert( m_pID_TEXT_PlayerScene3 );
	assert( m_pID_TEXT_PlayerScene4 );
	assert( m_pID_TEXT_PlayerScene5 );
	assert( m_pID_TEXT_PlayerScene6 );
	assert( m_pID_TEXT_Near );
	assert( m_pID_TEXT_Exp );
	assert( m_pID_TEXT_FriendAttribute );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_CHECKBOX_Player1 );
	assert( m_pID_CHECKBOX_Player2 );
	assert( m_pID_CHECKBOX_Player3 );
	assert( m_pID_CHECKBOX_Player4 );
	assert( m_pID_CHECKBOX_Player5 );
	assert( m_pID_CHECKBOX_Player6 );
	assert( m_pID_TEXT_AcceptApplyText );
	assert( m_pID_PICTURE_AcceptInviteText );
	assert( m_pID_CHECKBOX_AcceptInvite );
	assert( m_pID_TEXT_Captain );
	assert( m_pID_BUTTON_LeaveTeam );
	assert( m_pID_BUTTON_AddFriend );
	assert( m_pID_BUTTON_DisBand );
	assert( m_pID_BUTTON_Kick );
	assert( m_pID_BUTTON_Promote );
	assert( m_pID_PICTURE_TeamNameText );
	assert( m_pID_PICTURE_ExpModeText );
	assert( m_pID_PICTURE_PickModeText );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_PICTURE_NotTeam );
	assert( m_pID_COMBOBOX_TeamName );
	assert( m_pID_COMBOBOX_ExpMode );
	assert( m_pID_COMBOBOX_PickMode );
	assert( m_pID_PICTURE_TitleSetUp );
	assert( m_pID_BUTTON_Apply );
	assert( m_pID_BUTTON_Average );
	assert( m_pID_BUTTON_Join );
	assert( m_pID_BUTTON_CreateTeam );
	assert( m_pID_BUTTON_Follow );
	assert( m_pID_BUTTON_Refuse );
	assert( m_pID_PICTURE_TitleNow );
	assert( m_pID_PICTURE_TitleTeamApplication );
	assert( m_pID_COMBOBOX_Distribute );
	assert( m_pID_COMBOBOX_Tone );
	//assert( m_pID_LIST_DistributeAccessories );
	assert( m_pID_BUTTON_FollowBreak );
	assert( m_pID_BUTTON_TeamInformation );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_TEXT_Page );
	assert( m_pID_BUTTON_QKLB );
	assert( m_pID_CHECKBOX_TeamInformation );
	assert( m_pID_CHECKBOX_Apply );
	assert( m_pID_BUTTON_Near );
//	assert( m_pID_BUTTON_Duorentongqi );

	ControlList::S_List item;
	//item.SetData(theXmlString.GetString(eText_TeamAssignMode_Free));
	//m_pID_COMBOBOX_Distribute->GetListBox().AddItem(&item);
	item.SetData(theXmlString.GetString(eText_TeamAssignMode_Team));
	m_pID_COMBOBOX_Distribute->GetListBox().AddItem(&item);
	//item.SetData(theXmlString.GetString(eText_TeamAssignMode_Assign));
	//m_pID_COMBOBOX_Distribute->GetListBox().AddItem(&item);

	item.SetData( theXmlString.GetString(ePreItemText_LiangPin), 0, NULL, ToneColors[0] );
	m_pID_COMBOBOX_Tone->GetListBox().AddItem(&item);
	item.SetData( theXmlString.GetString(ePreItemText_JingPin), 0, NULL, ToneColors[1] );
	m_pID_COMBOBOX_Tone->GetListBox().AddItem(&item);
	item.SetData( theXmlString.GetString(ePreItemText_JiPin), 0, NULL, ToneColors[2] );
	m_pID_COMBOBOX_Tone->GetListBox().AddItem(&item);

	m_pID_FRAME_Team->SetMsgProcFun( UITeam_MsgProc );

	SetVisable(false);

	s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetFather( m_pID_FRAME_Team );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Team::_UnLoadUI()
{
	m_pID_FRAME_Team = NULL;
	m_pID_CHECKBOX_AcceptApply = NULL;
	m_pID_PICTURE_BG = NULL;
	m_pID_CHECKBOX_Team = NULL;
	m_pID_CHECKBOX_TeamApply = NULL;
	m_pID_CHECKBOX_TeamNear = NULL;
	m_pID_PICTURE_Player1 = NULL;
	m_pID_PICTURE_Player2 = NULL;
	m_pID_PICTURE_Player3 = NULL;
	m_pID_PICTURE_Player4 = NULL;
	m_pID_PICTURE_Player5 = NULL;
	m_pID_PICTURE_Player6 = NULL;
	m_pID_TEXT_PlayerName2 = NULL;
	m_pID_TEXT_PlayerName3 = NULL;
	m_pID_TEXT_PlayerName4 = NULL;
	m_pID_TEXT_PlayerName5 = NULL;
	m_pID_TEXT_PlayerName6 = NULL;
	m_pID_TEXT_PlayerName1 = NULL;
	m_pID_TEXT_PlayerLevel1 = NULL;
	m_pID_TEXT_PlayerLevel2 = NULL;
	m_pID_TEXT_PlayerLevel3 = NULL;
	m_pID_TEXT_PlayerLevel4 = NULL;
	m_pID_TEXT_PlayerLevel5 = NULL;
	m_pID_TEXT_PlayerLevel6 = NULL;
	m_pID_TEXT_PlayerJob1 = NULL;
	m_pID_TEXT_PlayerJob2 = NULL;
	m_pID_TEXT_PlayerJob3 = NULL;
	m_pID_TEXT_PlayerJob4 = NULL;
	m_pID_TEXT_PlayerJob5 = NULL;
	m_pID_TEXT_PlayerJob6 = NULL;
	m_pID_TEXT_PlayerScene1 = NULL;
	m_pID_TEXT_PlayerScene2 = NULL;
	m_pID_TEXT_PlayerScene3 = NULL;
	m_pID_TEXT_PlayerScene4 = NULL;
	m_pID_TEXT_PlayerScene5 = NULL;
	m_pID_TEXT_PlayerScene6 = NULL;
	m_pID_TEXT_Near = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_FriendAttribute = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_CHECKBOX_Player1 = NULL;
	m_pID_CHECKBOX_Player2 = NULL;
	m_pID_CHECKBOX_Player3 = NULL;
	m_pID_CHECKBOX_Player4 = NULL;
	m_pID_CHECKBOX_Player5 = NULL;
	m_pID_CHECKBOX_Player6 = NULL;
	m_pID_TEXT_AcceptApplyText = NULL;
	m_pID_PICTURE_AcceptInviteText = NULL;
	m_pID_CHECKBOX_AcceptInvite = NULL;
	m_pID_TEXT_Captain = NULL;
	m_pID_BUTTON_LeaveTeam = NULL;
	m_pID_BUTTON_AddFriend = NULL;
	m_pID_BUTTON_DisBand = NULL;
	m_pID_BUTTON_Kick = NULL;
	m_pID_BUTTON_Promote = NULL;
	m_pID_PICTURE_TeamNameText = NULL;
	m_pID_PICTURE_ExpModeText = NULL;
	m_pID_PICTURE_PickModeText = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_PICTURE_NotTeam = NULL;
	m_pID_COMBOBOX_TeamName = NULL;
	m_pID_COMBOBOX_ExpMode = NULL;
	m_pID_COMBOBOX_PickMode = NULL;
	m_pID_PICTURE_TitleSetUp = NULL;
	m_pID_BUTTON_Apply = NULL;
	m_pID_BUTTON_Average = NULL;
	m_pID_BUTTON_Join = NULL;
	m_pID_BUTTON_CreateTeam = NULL;
	m_pID_BUTTON_Follow = NULL;
	m_pID_BUTTON_Refuse = NULL;
	m_pID_PICTURE_TitleNow = NULL;
	m_pID_PICTURE_TitleTeamApplication = NULL;
	m_pID_COMBOBOX_Distribute = NULL;
	//m_pID_LIST_DistributeAccessories = NULL;
	m_pID_BUTTON_FollowBreak = NULL;
	m_pID_BUTTON_TeamInformation = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_BUTTON_QKLB = NULL;
	m_pID_CHECKBOX_TeamInformation = NULL;
	m_pID_CHECKBOX_Apply = NULL;
//	m_pID_BUTTON_Duorentongqi = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Team.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Team::_IsVisable()
{
	if ( !m_pID_FRAME_Team )
		return false;
	return m_pID_FRAME_Team->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Team::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Team )
		return;
	m_pID_FRAME_Team->SetVisable( bVisable );

	s_CUI_ID_FRAME_TeamFlag._SetVisable(bVisable);

	if ( s_CUI_ID_FRAME_Team.IsVisable() )
	{
		CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();
		if ( player )
		{
			//uint32 teamId = player->GetTeamId();
			std::vector<TeamInfo> teamInfos = thePlayerRole.GetTeamInfo();
			if ( teamInfos.size() == 0 ) //没有队伍，显示创建队伍模式
			{
				s_CUI_ID_FRAME_Team.SetCreateView();
			}
			else //查看队伍模式
			{
				s_CUI_ID_FRAME_Team.SetCurrentView();
				if ( player->IsTeamHeader() )
				{
					s_CUI_ID_FRAME_Team.SetIsTeamLeader(true);
				}
				else
				{
					s_CUI_ID_FRAME_Team.SetIsTeamLeader(false);
				}
				
			}
		}
	}

}

void CUI_ID_FRAME_Team::CheckOnPlayerClick( CPlayer* player )
{
	if ( player != NULL && m_bInRequestState == true )
	{
		if ( player->IsPlayer() )
		{
			//统一走通用菜单流程，这样出错的提示都是统一的
			s_CUI_ID_FRAME_RBTNMENU.InviteTeam( std::string(player->GetName()) );
		}	
	}
	m_bInRequestState = false;
	theHeroGame.SetStateCursor(MouseManager::Type_Max);//恢复光标
}

void CUI_ID_FRAME_Team::AddRequest( void* pData )
{
	MsgInquireInvitee* reqData = (MsgInquireInvitee*)pData;
	if ( reqData )
	{
		int count = (int)m_vecRequesterSet.size();
		for ( int i = 0; i < count; i ++ )
		{
			if( m_vecRequesterSet[i].dwReqID == reqData->dwReqID )
			{
				m_vecRequesterSet[i].AssignItemLevel = reqData->AssignItemLevel;
				m_vecRequesterSet[i].AssignMode = reqData->AssignMode;
				m_vecRequesterSet[i].chProfession = reqData->chProfession;
				m_vecRequesterSet[i].dwReqID = reqData->dwReqID;
				m_vecRequesterSet[i].IsCorps = reqData->IsCorps;
				m_vecRequesterSet[i].stLevel = reqData->stLevel;
				m_vecRequesterSet[i].szReqName = reqData->szReqName;
				m_vecRequesterSet[i].nSex = reqData->nSex;
				RefreshPageInfo();
				return;
			}
		}
		
		//m_pRequesterSet.push_back(reqData);
		TeamRequestInfo info;
		info.AssignItemLevel = reqData->AssignItemLevel;
		info.AssignMode = reqData->AssignMode;
		info.chProfession = reqData->chProfession;
		info.dwReqID = reqData->dwReqID;
		info.IsCorps = reqData->IsCorps;
		info.stLevel = reqData->stLevel;
		info.szReqName = reqData->szReqName;
		info.nSex = reqData->nSex;
		m_vecRequesterSet.push_back(info);

		if (IsRequestView())
		{
			SetRequestView();	//主要是为了激活按钮
		}
		else
		{
			RefreshPageInfo();
		}
		
	}
	
	
}

void CUI_ID_FRAME_Team::RefreshTeamInfo()
{
	ClearAllTeamInfo();
	UncheckedAll();
	//之后都要求队长放在最前面，可以在获取这个链表这后再把队长抽出来放到最前面
	std::vector<TeamInfo> vecTeamInfos = thePlayerRole.GetTeamInfo();

	int count = (int)vecTeamInfos.size();
	//将队长移动到队首
	if ( count > 1 )
	{
		for ( int i = 0; i < count; i ++ )
		{
			if ( vecTeamInfos[i].bHeader )
			{
				if ( i == 0 )
				{
					break;
				}
				TeamInfo info = vecTeamInfos[i];
				vecTeamInfos.erase( vecTeamInfos.begin() + i );
				vecTeamInfos.insert(vecTeamInfos.begin(), info);
				break;
			}
		}
		
		
	}
		
	
	m_nCurTeamCount = count;
	
	for ( int i = 0; i + m_nRequestStartIdx < count; i ++ )
	{
		if ( i == 0 )
		{
			m_pID_TEXT_PlayerName1->SetText( vecTeamInfos[i].szName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", vecTeamInfos[i].nLvl);
			m_pID_TEXT_PlayerLevel1->SetText( tmpStr );
			m_pID_TEXT_PlayerJob1->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( vecTeamInfos[i].usProfession ) );
			if( vecTeamInfos[i].bHeader )
			{
				//m_pID_TEXT_PlayerScene1->SetText( theXmlString.GetString(eTeam_TeamLeader) );
				SetTeamLeaderFlag(1);
			}
			else
			{
				m_pID_TEXT_PlayerScene1->SetText("");
			}

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( vecTeamInfos[i].szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( vecTeamInfos[i], i );
			}
			

		}
		else if ( i == 1 )
		{
			m_pID_TEXT_PlayerName2->SetText( vecTeamInfos[i].szName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", vecTeamInfos[i].nLvl);
			m_pID_TEXT_PlayerLevel2->SetText( tmpStr );
			m_pID_TEXT_PlayerJob2->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( vecTeamInfos[i].usProfession ) );
			if( vecTeamInfos[i].bHeader )
			{
				//m_pID_TEXT_PlayerScene2->SetText( theXmlString.GetString(eTeam_TeamLeader) );
				SetTeamLeaderFlag(2);
			}
			else
			{
				m_pID_TEXT_PlayerScene2->SetText("");
			}

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( vecTeamInfos[i].szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( vecTeamInfos[i], i );
			}
		}
		else if ( i == 2 )
		{
			m_pID_TEXT_PlayerName3->SetText( vecTeamInfos[i].szName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", vecTeamInfos[i].nLvl);
			m_pID_TEXT_PlayerLevel3->SetText( tmpStr );
			m_pID_TEXT_PlayerJob3->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( vecTeamInfos[i].usProfession ) );
			if( vecTeamInfos[i].bHeader )
			{
				//m_pID_TEXT_PlayerScene3->SetText( theXmlString.GetString(eTeam_TeamLeader) );
				SetTeamLeaderFlag(3);
			}
			else
			{
				m_pID_TEXT_PlayerScene3->SetText("");
			}

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( vecTeamInfos[i].szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( vecTeamInfos[i], i );
			}
		}
		else if ( i == 3 )
		{
			m_pID_TEXT_PlayerName4->SetText( vecTeamInfos[i].szName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", vecTeamInfos[i].nLvl);
			m_pID_TEXT_PlayerLevel4->SetText( tmpStr );
			m_pID_TEXT_PlayerJob4->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( vecTeamInfos[i].usProfession ) );
			if( vecTeamInfos[i].bHeader )
			{
				//m_pID_TEXT_PlayerScene4->SetText( theXmlString.GetString(eTeam_TeamLeader) );
				SetTeamLeaderFlag(4);
			}
			else
			{
				m_pID_TEXT_PlayerScene4->SetText("");
			}

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( vecTeamInfos[i].szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( vecTeamInfos[i], i );
			}
		}
		else if ( i == 4 )
		{
			m_pID_TEXT_PlayerName5->SetText( vecTeamInfos[i].szName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", vecTeamInfos[i].nLvl);
			m_pID_TEXT_PlayerLevel5->SetText( tmpStr );
			m_pID_TEXT_PlayerJob5->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( vecTeamInfos[i].usProfession ) );
			if( vecTeamInfos[i].bHeader )
			{
				//m_pID_TEXT_PlayerScene5->SetText( theXmlString.GetString(eTeam_TeamLeader) );
				SetTeamLeaderFlag(5);
			}
			else
			{
				m_pID_TEXT_PlayerScene5->SetText("");
			}

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( vecTeamInfos[i].szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( vecTeamInfos[i], i );
			}
		}
		else if ( i == 5 )
		{
			m_pID_TEXT_PlayerName6->SetText( vecTeamInfos[i].szName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", vecTeamInfos[i].nLvl);
			m_pID_TEXT_PlayerLevel6->SetText( tmpStr );
			m_pID_TEXT_PlayerJob6->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( vecTeamInfos[i].usProfession ) );
			if( vecTeamInfos[i].bHeader )
			{
				//m_pID_TEXT_PlayerScene6->SetText( theXmlString.GetString(eTeam_TeamLeader) );
				SetTeamLeaderFlag(6);
			}
			else
			{
				m_pID_TEXT_PlayerScene6->SetText("");
			}

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( vecTeamInfos[i].szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( vecTeamInfos[i], i );
			}
		}
	}
	
	if ( m_nCurTeamCount > 0 )
	{
		//m_pID_CHECKBOX_Player1->SetCheck(true);	//默认选择第一个
		bool bVal = true;
		ID_CHECKBOX_Player1OnCheckBoxCheck( m_pID_CHECKBOX_Player1, &bVal );
	}
	else	//表明没有队伍了，同时要将未处理申请信息清除
	{
		m_vecRequesterSet.clear();
	}
	
}

void CUI_ID_FRAME_Team::RefreshTeamRequestInfo( int startIdx )
{
	if ( m_vecRequesterSet.size() == 0 )
	{
		ClearAllTeamInfo();
		UncheckedAll();
		m_nCurTeamCount = 0;
	}
	
	if ( startIdx < 0 || startIdx >= m_vecRequesterSet.size() )
	{
		//错误起始页码
		return;
	}

	ClearAllTeamInfo();
	UncheckedAll();

	m_nCurTeamCount = m_vecRequesterSet.size() - startIdx;
	

	for ( int i = 0; i < MAX_TEAMSIZE && i + startIdx < m_vecRequesterSet.size(); i ++ )
	{
		if ( i == 0 )
		{
			m_pID_TEXT_PlayerName1->SetText( m_vecRequesterSet[i + startIdx].szReqName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", m_vecRequesterSet[i + startIdx].stLevel);
			m_pID_TEXT_PlayerLevel1->SetText( tmpStr );
			m_pID_TEXT_PlayerJob1->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( m_vecRequesterSet[i + startIdx].chProfession ) );

			TeamInfo info;
			info.szName = m_vecRequesterSet[i + startIdx].szReqName;
			info.usProfession = m_vecRequesterSet[i + startIdx].chProfession;
			info.nLvl = m_vecRequesterSet[i + startIdx].stLevel;
			info.ucSex = m_vecRequesterSet[i + startIdx].nSex;

			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( info.szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( info, i );
			}
			
		}
		else if ( i == 1 )
		{
			m_pID_TEXT_PlayerName2->SetText( m_vecRequesterSet[i + startIdx].szReqName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", m_vecRequesterSet[i + startIdx].stLevel);
			m_pID_TEXT_PlayerLevel2->SetText( tmpStr );
			m_pID_TEXT_PlayerJob2->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( m_vecRequesterSet[i + startIdx].chProfession ) );

			TeamInfo info;
			info.szName = m_vecRequesterSet[i + startIdx].szReqName;
			info.usProfession = m_vecRequesterSet[i + startIdx].chProfession;
			info.nLvl = m_vecRequesterSet[i + startIdx].stLevel;
			info.ucSex = m_vecRequesterSet[i + startIdx].nSex;
			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( info.szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( info, i );
			}
		}
		else if ( i == 2 )
		{
			m_pID_TEXT_PlayerName3->SetText( m_vecRequesterSet[i + startIdx].szReqName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", m_vecRequesterSet[i + startIdx].stLevel);
			m_pID_TEXT_PlayerLevel3->SetText( tmpStr );
			m_pID_TEXT_PlayerJob3->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( m_vecRequesterSet[i + startIdx].chProfession ) );

			TeamInfo info;
			info.szName = m_vecRequesterSet[i + startIdx].szReqName;
			info.usProfession = m_vecRequesterSet[i + startIdx].chProfession;
			info.nLvl = m_vecRequesterSet[i + startIdx].stLevel;
			info.ucSex = m_vecRequesterSet[i + startIdx].nSex;
			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( info.szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( info, i );
			}
		}
		else if ( i == 3 )
		{
			m_pID_TEXT_PlayerName4->SetText( m_vecRequesterSet[i + startIdx].szReqName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", m_vecRequesterSet[i + startIdx].stLevel);
			m_pID_TEXT_PlayerLevel4->SetText( tmpStr );
			m_pID_TEXT_PlayerJob4->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( m_vecRequesterSet[i + startIdx].chProfession ) );

			TeamInfo info;
			info.szName = m_vecRequesterSet[i + startIdx].szReqName;
			info.usProfession = m_vecRequesterSet[i + startIdx].chProfession;
			info.nLvl = m_vecRequesterSet[i + startIdx].stLevel;
			info.ucSex = m_vecRequesterSet[i + startIdx].nSex;
			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( info.szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( info, i );
			}
		}
		else if ( i == 4 )
		{
			m_pID_TEXT_PlayerName5->SetText( m_vecRequesterSet[i + startIdx].szReqName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", m_vecRequesterSet[i + startIdx].stLevel);
			m_pID_TEXT_PlayerLevel5->SetText( tmpStr );
			m_pID_TEXT_PlayerJob5->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( m_vecRequesterSet[i + startIdx].chProfession ) );

			TeamInfo info;
			info.szName = m_vecRequesterSet[i + startIdx].szReqName;
			info.usProfession = m_vecRequesterSet[i + startIdx].chProfession;
			info.nLvl = m_vecRequesterSet[i + startIdx].stLevel;
			info.ucSex = m_vecRequesterSet[i + startIdx].nSex;
			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( info.szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( info, i );
			}
		}
		else if ( i == 5 )
		{
			m_pID_TEXT_PlayerName6->SetText( m_vecRequesterSet[i + startIdx].szReqName );
			char tmpStr[32] = {0};
			sprintf( tmpStr, "%d", m_vecRequesterSet[i + startIdx].stLevel);
			m_pID_TEXT_PlayerLevel6->SetText( tmpStr );
			m_pID_TEXT_PlayerJob6->SetText( s_CUI_ID_FRAME_AboutPeople.GetMPTypeString( m_vecRequesterSet[i + startIdx].chProfession ) );

			TeamInfo info;
			info.szName = m_vecRequesterSet[i + startIdx].szReqName;
			info.usProfession = m_vecRequesterSet[i + startIdx].chProfession;
			info.nLvl = m_vecRequesterSet[i + startIdx].stLevel;
			info.ucSex = m_vecRequesterSet[i + startIdx].nSex;
			CPlayer* player = theHeroGame.GetPlayerMgr()->FindByName( info.szName.c_str() );
			if ( player )
			{
				UpdateAniCtrl( player, i );
			}
			else
			{
				UpdateAniCtrlEx( info, i );
			}
		}
	}

	if ( m_nCurTeamCount > 0 )
	{
		//m_pID_CHECKBOX_Player1->SetCheck(true);	//默认选择第一个
		bool bVal = true;
		ID_CHECKBOX_Player1OnCheckBoxCheck( m_pID_CHECKBOX_Player1, &bVal );
	}
}

void CUI_ID_FRAME_Team::ClearAllTeamInfo()
{
	//p1
	m_pID_TEXT_PlayerName1->SetText( "" );
	m_pID_TEXT_PlayerLevel1->SetText( "" );
	m_pID_TEXT_PlayerJob1->SetText( "" );
	m_pID_TEXT_PlayerScene1->SetText( "" );
	//p2
	m_pID_TEXT_PlayerName2->SetText( "" );
	m_pID_TEXT_PlayerLevel2->SetText( "" );
	m_pID_TEXT_PlayerJob2->SetText( "" );
	m_pID_TEXT_PlayerScene2->SetText( "" );
	//p3
	m_pID_TEXT_PlayerName3->SetText( "" );
	m_pID_TEXT_PlayerLevel3->SetText( "" );
	m_pID_TEXT_PlayerJob3->SetText( "" );
	m_pID_TEXT_PlayerScene3->SetText( "" );
	//p4
	m_pID_TEXT_PlayerName4->SetText( "" );
	m_pID_TEXT_PlayerLevel4->SetText( "" );
	m_pID_TEXT_PlayerJob4->SetText( "" );
	m_pID_TEXT_PlayerScene4->SetText( "" );
	//p5
	m_pID_TEXT_PlayerName5->SetText( "" );
	m_pID_TEXT_PlayerLevel5->SetText( "" );
	m_pID_TEXT_PlayerJob5->SetText( "" );
	m_pID_TEXT_PlayerScene5->SetText( "" );
	//p6
	m_pID_TEXT_PlayerName6->SetText( "" );
	m_pID_TEXT_PlayerLevel6->SetText( "" );
	m_pID_TEXT_PlayerJob6->SetText( "" );
	m_pID_TEXT_PlayerScene6->SetText( "" );

	s_CUI_ID_FRAME_TeamFlag._SetVisable(false);	//队长标记采用一面旗子了
}

bool CUI_ID_FRAME_Team::IsTeamLeader( const char* playerName )
{
	if ( playerName )
	{
		std::vector<TeamInfo> vecInfos = thePlayerRole.GetTeamInfo();
		int count = (int)vecInfos.size();
		for ( int i = 0; i < count; i ++ )
		{
			if( vecInfos[i].bHeader )
			{
				
				if ( vecInfos[i].szName.compare(playerName) == 0 )
				{
					return true;
				}
				break;
			}
		}
		
	}
	return false;
}

int	 CUI_ID_FRAME_Team::GetTeamIdx( const char* playerName )
{
	if ( playerName == NULL )
	{
		return -1;
	}
	
	std::vector<TeamInfo> teamInfos = thePlayerRole.GetTeamInfo();

	for ( int i = 0; i < teamInfos.size(); i ++ )
	{
		if( teamInfos[i].szName.compare( playerName ) == 0 )
		{
			return teamInfos[i].nID;
		}
	}
	return -1;
	
}

void CUI_ID_FRAME_Team::CheckChangeFollowState()
{
	//服务器要求，队长离开队伍要提前发送一条取消跟随的消息
	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();
	if ( player && IsTeamLeader( player->GetName() ) )
	{
		MsgHeaderCancelTeamFollow msg;
		GettheNetworkInput().SendMsg(&msg);
	}
	else if ( GetTeamFollowID() >= 0 )	//队员处于跟随状态
	{
		MsgCancelTeamFollow msg;
		GettheNetworkInput().SendMsg(&msg);
	}
	
}

void CUI_ID_FRAME_Team::InitializeAtEnterWorld()
{
	Reset();
	DestroyAnimCtrl();

	m_pPlayer = MeNew CPlayer();
	int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
	if( nIndex >= 0 )
	{
		m_pPlayer->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
	}

	for ( int i = 0; i < MAX_TEAMSIZE; i ++ )
	{
		m_pPlayers[i] = MeNew CPlayer();
		int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
		if( nIndex >= 0 )
		{
			m_pPlayers[i]->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
		}

	}	

	m_PlayerAnim = MeNew CPlayerAnim();

	m_pPlayer->SetAnim(m_PlayerAnim);
	m_PlayerAnim->SetPlayer( m_pPlayer );

	for ( int i = 0; i < MAX_TEAMSIZE; i ++ )
	{
		m_PlayerAnims[i] = MeNew CPlayerAnim();

		m_pPlayers[i]->SetAnim(m_PlayerAnims[i]);
		m_PlayerAnims[i]->SetPlayer( m_pPlayers[i] );

		theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayers[i] );
	}

	InitCamera();

	theHeroGame.GetPlayerMgr()->AddNoLogicPlayer( m_pPlayer );

	if ( !m_pID_FRAME_Team )
		return;
	this->SetVisable(false);
}

BOOL CUI_ID_FRAME_Team::InitCamera()
{
	FLOAT fAspect = ((FLOAT)200.0f) / 300.0f;
	m_Camera.SetProjParams( D3DX_PI*(30/45.0f)/4, fAspect, 1.0f, 220.0f );

	m_ViewPort.X = 0;
	m_ViewPort.Y = 0;
	m_ViewPort.Width = 800;
	m_ViewPort.Height = 600;
	m_ViewPort.MinZ = 0;
	m_ViewPort.MaxZ = 1;

	return TRUE;
}

void CUI_ID_FRAME_Team::DestroyAnimCtrl()
{
	if (m_pPlayer)
	{
		theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayer );
		m_pPlayer->Destroy();	
		delete m_pPlayer;
		m_pPlayer = 0;
		m_PlayerAnim = 0;
	}
	for ( int i = 0; i < MAX_TEAMSIZE; i ++ )
	{
		if (m_pPlayers[i])
		{
			theHeroGame.GetPlayerMgr()->ClearNoLogicPlayer( m_pPlayers[i] );
			m_pPlayers[i]->Destroy();	
			delete m_pPlayers[i];
			m_pPlayers[i] = 0;
			m_PlayerAnims[i] = 0;
		}
	}
}

void CUI_ID_FRAME_Team::Reset()
{
	m_fRotateZ = 0;
	m_bRotate = false;
	DestroyAnimCtrl();
	//m_bLvlupHasShown = false;
	//PetAIType = 0;

	m_fLightTry1 = 0.6f;
	m_fLightTry2 = 1.0f;
	m_fLightTry3 = 1.0f;
}

void CUI_ID_FRAME_Team::UpdateAniCtrl( CPlayer* pMe, const int idx )
{

	if( !pMe )
		return;

	if( pMe->GetAnim() )
	{
		uint16 stVisualItemID[EEquipPartType_MaxEquitPart];
		uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart];
		uint8 equipLevel[EEquipPartType_MaxEquitPart];
		uint8 equipElements[EEquipPartType_MaxEquitPart];
		CPlayer_SEquipment equip[eKeyAll_Max];

		memcpy(equip, pMe->GetEquip(), eKeyAll_Max * sizeof(CPlayer_SEquipment));
		for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			int nPart = CEquipPartMap::Instance()->GetLogicPart(i);
			stVisualItemID[i] = equip[nPart].item.itembaseinfo.ustItemID;
			equipIntensifyTime[i] = equip[nPart].item.equipdata.gemHoleCount;
			equipLevel[i] = equip[nPart].item.equipdata.ucLevel;
			equipElements[i] = equip[nPart].item.itembaseinfo.value1;
		}

		//bool showHelmet = pMe->IsShowHelmet() || pMe->IsShowAecpratove();
		m_PlayerAnims[idx]->ChangeSkeletonAndEquipAll(
			&equip,
			pMe->GetSex(),
			pMe->GetProfession(),
			pMe->GetHairColorIndex(),
			pMe->IsShowHelmet(), pMe->IsShowAecpratove(),0,pMe->GetHeroID(),pMe->IsSHowHero());
		m_PlayerAnims[idx]->UpdateHardItem( pMe->HasFightFlag(eFighting),
			(void*)equip );
		m_PlayerAnims[idx]->SetPosition( 0.0f, 0.0f, 0.0f );

		if( pMe->IsHaveWeapon() )
		{
			// 是否拿旗子
			BOOL bHoldFlag = FALSE;
			if( m_PlayerAnims[idx]->IsHoldingFlagOnRightHand() )
				bHoldFlag = TRUE;

			m_PlayerAnims[idx]->ChangeWeaponAnim( m_PlayerAnims[idx]->GetWeaponActionModelId( pMe->GetProfession(), pMe->GetSex(), bHoldFlag ));

			m_PlayerAnims[idx]->PlayAnim2(	MoreActionClient::single_idle,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes, 
				MexAnimCtrl::eMaxTimeout, 
				MoreActionClient::single_idle,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			m_PlayerAnims[idx]->PlayAnim2(	MoreActionClient::Idle1,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes, 
				MexAnimCtrl::eMaxTimeout, 
				MoreActionClient::Idle1,
				MexAnimCtrl::eNormalPlay );
		}

		// 五行
		m_pPlayers[idx]->EquipByItemID(stVisualItemID, equipIntensifyTime, equipLevel, equipElements);
		m_pPlayers[idx]->UpdateBones();
		m_pPlayers[idx]->SetSex(pMe->GetSex());
	}

}

void CUI_ID_FRAME_Team::UpdateAniCtrlEx(  const TeamInfo& teamInfo, const int idx  )
{

	uint16 stVisualItemID[EEquipPartType_MaxEquitPart] = {0};
	uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart] = {0};
	uint8 equipLevel[EEquipPartType_MaxEquitPart] = {0};
	uint8 equipElements[EEquipPartType_MaxEquitPart] = {0};
	m_pPlayers[idx]->EquipByItemID(stVisualItemID, equipIntensifyTime, equipLevel, equipElements);
	m_pPlayers[idx]->UpdateBones();
	m_pPlayers[idx]->SetSex(teamInfo.ucSex);

	CPlayer_SEquipment equip[eKeyAll_Max];
	equip[eKeyAll_Hair].iModelID = teamInfo.nHairId;
	equip[eKeyAll_Face].iModelID = teamInfo.nFaceId;
	m_PlayerAnims[idx]->ChangeSkeletonAndEquipAll(
		&equip,
		teamInfo.ucSex,
		teamInfo.usProfession,
		0xFFFFFFFF,
		true, false,0,m_pPlayers[idx]->GetHeroID());
	m_PlayerAnims[idx]->UpdateHardItem( false,
		(void*)equip );
	m_PlayerAnims[idx]->SetPosition( 0.0f, 0.0f, 0.0f );

	m_PlayerAnims[idx]->PlayAnim2(	MoreActionClient::Idle1,
		MexAnimCtrl::eNormalPlay, 
		0,
		MexAnimCtrl::eMaxLoopTimes, 
		MexAnimCtrl::eMaxTimeout, 
		MoreActionClient::Idle1,
		MexAnimCtrl::eNormalPlay );

}

void CUI_ID_FRAME_Team::RefreshView()
{
	//当自己已经没有队伍信息的时候，强制取消跟随，不管是踢出，主动离开，解散队伍
	if ( thePlayerRole.GetTeamInfo().size() == 0 )
	{
		if( GetTeamFollowID() >= 0 )
		{
			SetTeamFollowID( -1 );
		}
		
		m_eViewType = VT_CreateView; //视图也切换到创建模式，因为没有队伍了
	}
	else if( m_eViewType == VT_CreateView )
	{
		m_eViewType = VT_CurrentView;
	}
	
	if ( !IsVisable() )
	{
		//只有可见的时候需要刷新当前界面
		return;
	}
	
	if ( m_eViewType == VT_CreateView )
	{
		SetCreateView();
	}
	else if ( m_eViewType == VT_CurrentView )
	{
		SetCurrentView();
	}
	else
	{
		SetRequestView();
	}

	RefreshAssignMode();
	RefreshRollMode();
	
}

void CUI_ID_FRAME_Team::SetCurrentView()	//查看当前队伍界面
{
	m_eViewType = VT_CurrentView;
	m_nRequestStartIdx = 0;//保证非申请视图正常
	//ID_PICTURE_TitleNow	当前队伍
	//ID_PICTURE_TitleSetUp		创建队伍
	//ID_PICTURE_TitleTeamApplication	组队申请

	//===============标题======================
	m_pID_PICTURE_TitleNow->SetVisable(true);
	m_pID_PICTURE_TitleSetUp->SetVisable(false);
	m_pID_PICTURE_TitleTeamApplication->SetVisable(false);

	//===============按钮======================
	/*
	ID_BUTTON_CreateTeam 创建队伍
	ID_BUTTON_Apply 申请入队
	ID_BUTTON_Promote 提升队长
	ID_BUTTON_Kick 踢出队伍
	ID_BUTTON_DisBand 解散队伍
	ID_BUTTON_LeaveTeam 离开队伍
	ID_BUTTON_Join 组队
	ID_BUTTON_Ok 确定
	ID_BUTTON_Refuse 拒绝

	ID_BUTTON_Follow 跟随
	ID_BUTTON_FollowBreak 取消跟随
	ID_BUTTON_AddFriend 加为好友
	*/
	SetAllButtonsVisible(true);
	SetAllButtonsEnable(true);
	m_pID_BUTTON_Apply->SetVisable(false);
	m_pID_BUTTON_CreateTeam->SetVisable(false);
	m_pID_BUTTON_FollowBreak->SetVisable(false);
	m_pID_BUTTON_Ok->SetVisable(false);
	m_pID_BUTTON_Refuse->SetVisable(false);
	m_pID_BUTTON_QKLB->SetVisable(false);
	m_pID_BUTTON_Follow->SetVisable(false);
	m_pID_BUTTON_TeamInformation->SetVisable(false);
	m_pID_BUTTON_Apply->SetVisable(false);

	m_pID_CHECKBOX_TeamInformation->SetVisable(true);
	m_pID_CHECKBOX_Apply->SetVisable(true);
	m_pID_CHECKBOX_TeamInformation->SetCheck(true);
	m_pID_CHECKBOX_Apply->SetCheck(false);

	CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();
	if ( player && !IsTeamLeader( player->GetName() ) )
	{
		m_pID_BUTTON_Promote->SetEnable(false);
		m_pID_BUTTON_Kick->SetEnable(false); 
		m_pID_BUTTON_DisBand->SetEnable(false);
		m_pID_BUTTON_Join->SetEnable(false);
		SetDistributeModeVisible(true);	
		SetDistributeModeEnable(false);
		
	}
	else
	{
		m_pID_BUTTON_Follow->SetVisable(true); //队长这个是任何时刻都可见且有效
		m_pID_BUTTON_FollowBreak->SetVisable(true);
		m_pID_BUTTON_TeamInformation->SetVisable(false);
		m_pID_BUTTON_Apply->SetVisable(true);		//点这个切换到队伍申请界面
		SetDistributeModeVisible(true);			//这个只有当前队伍，队长是可见,且可用，不是队长仅仅可见，其他视图都是不可见
		SetDistributeModeEnable(true);
	}
	
	if ( GetTeamFollowID() >= 0 )
	{
		m_pID_BUTTON_FollowBreak->SetVisable(true);
		m_pID_BUTTON_FollowBreak->SetEnable(true);
	}
	
	//只有currentview才会刷新这些数据
	RefreshAssignMode();
	RefreshRollMode();

	if ( thePlayerRole.IsTeamHeader() )
	{
		RefreshFollowButtons();
	}
	else
	{
		m_pID_BUTTON_FollowBreak->SetEnable(true);
	}
	SetPageButtonsVisible(false);
	RefreshTeamInfo();

}

void CUI_ID_FRAME_Team::SetCreateView() //创建当前队伍界面
{
	m_eViewType = VT_CreateView;
	m_nRequestStartIdx = 0;//保证非申请视图正常
	//===============标题======================
	m_pID_PICTURE_TitleNow->SetVisable(false);
	m_pID_PICTURE_TitleSetUp->SetVisable(true);
	m_pID_PICTURE_TitleTeamApplication->SetVisable(false);

	//===============按钮======================
	SetAllButtonsVisible(false);
	m_pID_BUTTON_CreateTeam->SetVisable(true);
	m_pID_BUTTON_CreateTeam->SetEnable(true);
	m_pID_BUTTON_Join->SetVisable(true);
	m_pID_BUTTON_Join->SetEnable(true);

	m_pID_CHECKBOX_TeamInformation->SetVisable(false);
	m_pID_CHECKBOX_Apply->SetVisable(false);

	SetDistributeModeVisible(false);	
	SetPageButtonsVisible(false);
	RefreshTeamInfo();

}

void CUI_ID_FRAME_Team::SetRequestView() //申请界面
{
	m_eViewType = VT_RequestView;
	//===============标题======================
	m_pID_PICTURE_TitleNow->SetVisable(false);
	m_pID_PICTURE_TitleSetUp->SetVisable(false);
	m_pID_PICTURE_TitleTeamApplication->SetVisable(true);
	//===============按钮======================
	SetAllButtonsVisible(false);
	m_pID_BUTTON_Ok->SetVisable( true );
	m_pID_BUTTON_Refuse->SetVisable( true );
	m_pID_BUTTON_QKLB->SetVisable(true);
	m_pID_BUTTON_Ok->SetEnable( false );
	m_pID_BUTTON_Refuse->SetEnable( false );
	m_pID_BUTTON_QKLB->SetEnable( false );

	m_pID_CHECKBOX_TeamInformation->SetVisable(true);
	m_pID_CHECKBOX_Apply->SetVisable(true);
	m_pID_CHECKBOX_TeamInformation->SetCheck(false);
	m_pID_CHECKBOX_Apply->SetCheck(true);

	if ( thePlayerRole.IsTeamHeader() )
	{
		m_pID_BUTTON_TeamInformation->SetVisable(true);
		m_pID_BUTTON_Apply->SetVisable(false);
	}
	SetDistributeModeVisible(false);
	SetPageButtonsVisible(true);
	RefreshPageInfo();
	RefreshTeamRequestInfo(m_nRequestStartIdx);//默认从0页开始
	//当选中有效目标的时候按钮才有效
    if (m_vecRequesterSet.size() > 0)
    {
		if (IsPlayerSelected())
		{
			m_pID_BUTTON_Ok->SetEnable( true);
			m_pID_BUTTON_Refuse->SetEnable( true );
			m_pID_BUTTON_QKLB->SetEnable(true);
		}
	}

}

bool CUI_ID_FRAME_Team::IsCurrentView()
{
	return (m_eViewType == VT_CurrentView);
}
bool CUI_ID_FRAME_Team::IsCreateView()
{
	return (m_eViewType == VT_CreateView);
}
bool CUI_ID_FRAME_Team::IsRequestView()
{
	return (m_eViewType == VT_RequestView);
}

void CUI_ID_FRAME_Team::UncheckedAll()
{
	m_pID_CHECKBOX_Player1->SetCheck(false);
	m_pID_CHECKBOX_Player2->SetCheck(false);
	m_pID_CHECKBOX_Player3->SetCheck(false);
	m_pID_CHECKBOX_Player4->SetCheck(false);
	m_pID_CHECKBOX_Player5->SetCheck(false);
	m_pID_CHECKBOX_Player6->SetCheck(false);
}

void CUI_ID_FRAME_Team::SetTeamLeaderFlag( int i )
{
	if ( i == 1 )
	{
		RECT rc;
		m_pID_PICTURE_Player1->GetRealRect(&rc);
		s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetPos( rc.left, rc.top );
		s_CUI_ID_FRAME_TeamFlag._SetVisable(true);
	}
	else if ( i == 2 )
	{
		RECT rc;
		m_pID_PICTURE_Player2->GetRealRect(&rc);
		s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetPos( rc.left, rc.top );
		s_CUI_ID_FRAME_TeamFlag._SetVisable(true);
	}
	else if ( i == 3 )
	{
		RECT rc;
		m_pID_PICTURE_Player3->GetRealRect(&rc);
		s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetPos( rc.left, rc.top );
		s_CUI_ID_FRAME_TeamFlag._SetVisable(true);
	}
	else if ( i == 4 )
	{
		RECT rc;
		m_pID_PICTURE_Player4->GetRealRect(&rc);
		s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetPos( rc.left, rc.top );
		s_CUI_ID_FRAME_TeamFlag._SetVisable(true);
	}
	else if ( i == 5 )
	{
		RECT rc;
		m_pID_PICTURE_Player5->GetRealRect(&rc);
		s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetPos( rc.left, rc.top );
		s_CUI_ID_FRAME_TeamFlag._SetVisable(true);
	}
	else if ( i == 6 )
	{
		RECT rc;
		m_pID_PICTURE_Player6->GetRealRect(&rc);
		s_CUI_ID_FRAME_TeamFlag.GetFrame()->SetPos( rc.left, rc.top );
		s_CUI_ID_FRAME_TeamFlag._SetVisable(true);
	}
	
}

void CUI_ID_FRAME_Team::SetDistributeModeVisible( bool bVal )
{
	m_pID_COMBOBOX_Distribute->SetVisable(bVal);
	m_pID_COMBOBOX_Tone->SetVisable(bVal);
	m_pID_TEXT_String0->SetVisable(bVal);
	m_pID_TEXT_String1->SetVisable(bVal);
}

void CUI_ID_FRAME_Team::SetDistributeModeEnable( bool bVal )
{
	m_pID_COMBOBOX_Distribute->SetEnable(bVal);
	m_pID_COMBOBOX_Tone->SetEnable(bVal);
	m_pID_TEXT_String0->SetEnable(bVal);
	m_pID_TEXT_String1->SetEnable(bVal);
}

void CUI_ID_FRAME_Team::SetPageButtonsVisible( bool bVal )
{
	m_pID_BUTTON_PageUp->SetVisable(bVal);
	m_pID_BUTTON_PageDown->SetVisable(bVal);
	m_pID_TEXT_Page->SetVisable(bVal);
}

void CUI_ID_FRAME_Team::RefreshAssignMode()
{
	if( thePlayerRole.GetAssignMode() == AssignMode_FreeMode )       //自由拾取
	{
		m_pID_COMBOBOX_Distribute->GetListBox().SetCurSelIndex(0);
		m_pID_COMBOBOX_Distribute->GetEditInput().SetText(m_pID_COMBOBOX_Distribute->GetListBox().GetCurSelItem()->m_szText) ;
		m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(-1);
		m_pID_COMBOBOX_Tone->GetEditInput().SetText("");
		m_pID_COMBOBOX_Tone->SetEnable(false);
	}
	else if ( thePlayerRole.GetAssignMode() == AssignMode_Team )       //队伍分配
	{
		m_pID_COMBOBOX_Distribute->GetListBox().SetCurSelIndex(1);
		m_pID_COMBOBOX_Distribute->GetEditInput().SetText(m_pID_COMBOBOX_Distribute->GetListBox().GetCurSelItem()->m_szText) ;
		if( thePlayerRole.IsTeamHeader() )
		{
			m_pID_COMBOBOX_Tone->SetEnable(true);
		}
		
	}
	else if ( thePlayerRole.GetAssignMode() == AssignMode_Assign )		//队长分配
	{
		m_pID_COMBOBOX_Distribute->GetListBox().SetCurSelIndex(2);
		m_pID_COMBOBOX_Distribute->GetEditInput().SetText(m_pID_COMBOBOX_Distribute->GetListBox().GetCurSelItem()->m_szText) ;
		if( thePlayerRole.IsTeamHeader() )
		{
			m_pID_COMBOBOX_Tone->SetEnable(true);
		}
	}
}

void CUI_ID_FRAME_Team::RefreshRollMode()
{
	if ( thePlayerRole.GetAssignMode() == AssignMode_FreeMode )
	{
		m_pID_COMBOBOX_Tone->GetEditInput().SetText("");
		m_pID_COMBOBOX_Tone->SetEnable(false);
		return;
	}
	
	if ( thePlayerRole.GetItemRollLevel() == eIL_Choiceness )
	{
		m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(0);
		m_pID_COMBOBOX_Tone->GetEditInput().SetText(m_pID_COMBOBOX_Tone->GetListBox().GetCurSelItem()->m_szText) ;
		m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor( ToneColors[0] );
	}
	else if ( thePlayerRole.GetItemRollLevel() == eIL_Polish )
	{
		m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(1);
		m_pID_COMBOBOX_Tone->GetEditInput().SetText(m_pID_COMBOBOX_Tone->GetListBox().GetCurSelItem()->m_szText) ;
		m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor( ToneColors[1] );
	}
	else if ( thePlayerRole.GetItemRollLevel()  == eIL_Nonsuch )
	{
		m_pID_COMBOBOX_Tone->GetListBox().SetCurSelIndex(2);
		m_pID_COMBOBOX_Tone->GetEditInput().SetText(m_pID_COMBOBOX_Tone->GetListBox().GetCurSelItem()->m_szText) ;
		m_pID_COMBOBOX_Tone->GetEditInput().setDefaultColor( ToneColors[2] );
	}
}

void CUI_ID_FRAME_Team::RefreshFollowButtons()
{
	if ( m_nTeamFollowCount == 0 )
	{
		m_pID_BUTTON_FollowBreak->SetEnable( false );
	}
	else if ( m_nTeamFollowCount > 0 )
	{
		m_pID_BUTTON_FollowBreak->SetEnable( true );
	}

	//当队伍里面的人全部处于跟随状态的时候，跟随按钮无效
	if ( m_nTeamFollowCount == int(thePlayerRole.GetTeamInfo().size()) - 1 )
	{
		m_pID_BUTTON_Follow->SetEnable(false);
	}
	else
	{
		m_pID_BUTTON_Follow->SetEnable(true);
	}
}

void CUI_ID_FRAME_Team::RefreshPageInfo()
{
	if ( thePlayerRole.IsTeamHeader() == FALSE )
	{
		return;
	}
	
	if ( thePlayerRole.GetTeamMemberNum() <= 0 )
	{
		m_vecRequesterSet.clear();
		m_pID_BUTTON_PageUp->SetEnable(false);
		m_pID_BUTTON_PageDown->SetEnable(false);
	}
	
	if ( m_vecRequesterSet.size() > 0 )
	{
		int total = (int)m_vecRequesterSet.size();
		int maxPageIdx = total / MAX_TEAMSIZE;
		if ( total % MAX_TEAMSIZE > 0 )
		{
			maxPageIdx ++;
		}
		if ( m_nRequestPageIdx > maxPageIdx )
		{
			m_nRequestPageIdx = maxPageIdx;
			m_pID_BUTTON_PageUp->SetEnable(false);
			m_pID_BUTTON_PageDown->SetEnable(true);
		}
		if ( m_nRequestPageIdx <= 0 )
		{
			m_nRequestPageIdx = 1;
			m_pID_BUTTON_PageUp->SetEnable(false);
			m_pID_BUTTON_PageDown->SetEnable(false);
		}

		m_nRequestStartIdx = ( m_nRequestPageIdx - 1 ) * MAX_TEAMSIZE;
		
		char tmpStr[128] = {0};
		sprintf( tmpStr, "%d/%d", m_nRequestPageIdx, maxPageIdx );
		m_pID_TEXT_Page->SetText( tmpStr );
		
	}
	else
	{
		m_nRequestPageIdx = 0;
		m_nRequestStartIdx = 0;
		m_pID_BUTTON_PageUp->SetEnable(false);
		m_pID_BUTTON_PageDown->SetEnable(false);
		m_pID_TEXT_Page->SetText(theXmlString.GetString(eText_Team_NoApplyPages));
	}
	RefreshTeamRequestInfo(m_nRequestStartIdx);
}

void CUI_ID_FRAME_Team::SetAllButtonsVisible( bool bVal )
{
	m_pID_BUTTON_CreateTeam->SetVisable( bVal );
	m_pID_BUTTON_Apply->SetVisable( bVal );
	m_pID_BUTTON_Promote->SetVisable( bVal );
	///m_pID_BUTTON_Duorentongqi->SetVisable( bVal );
	m_pID_BUTTON_Kick->SetVisable( bVal );
	m_pID_BUTTON_DisBand->SetVisable( bVal );
	m_pID_BUTTON_LeaveTeam->SetVisable( bVal );
	m_pID_BUTTON_Join->SetVisable( bVal );
	m_pID_BUTTON_Ok->SetVisable( bVal );
	m_pID_BUTTON_Refuse->SetVisable( bVal );
	m_pID_BUTTON_QKLB->SetVisable( bVal );

	m_pID_BUTTON_Follow->SetVisable( bVal );
	m_pID_BUTTON_FollowBreak->SetVisable( bVal );
	m_pID_BUTTON_AddFriend->SetVisable( bVal );
	m_pID_BUTTON_TeamInformation->SetVisable( bVal );

	//m_pID_BUTTON_Near->SetVisable( bVal );
}

void CUI_ID_FRAME_Team::SetAllButtonsEnable( bool bVal )
{
	m_pID_BUTTON_CreateTeam->SetEnable( bVal );
	m_pID_BUTTON_Apply->SetEnable( bVal );
	m_pID_BUTTON_Promote->SetEnable( bVal );
	m_pID_BUTTON_Kick->SetEnable( bVal );
	m_pID_BUTTON_DisBand->SetEnable( bVal );
	m_pID_BUTTON_LeaveTeam->SetEnable( bVal );
	m_pID_BUTTON_Join->SetEnable( bVal );
	m_pID_BUTTON_Ok->SetEnable( bVal );
	m_pID_BUTTON_Refuse->SetEnable( bVal );
	m_pID_BUTTON_QKLB->SetEnable( bVal );
	m_pID_BUTTON_Follow->SetEnable( bVal );
	m_pID_BUTTON_FollowBreak->SetEnable( bVal );
	m_pID_BUTTON_AddFriend->SetEnable( bVal );
	m_pID_BUTTON_TeamInformation->SetEnable( bVal );
}

void CUI_ID_FRAME_Team::RenderPlayers( ControlPicture* checkBox, const int idx )
{
	RECT rc;
	checkBox->GetRealRect(&rc);

	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

	m_ViewPort.X = rc.left;
	m_ViewPort.Y = rc.top;
	m_ViewPort.Width = rc.right - rc.left;
	m_ViewPort.Height = rc.bottom - rc.top;
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f;

	r->SetViewport( &m_ViewPort );
	r->BeginScene();
	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	D3DLIGHT9 light = GetSystemConfig()->m_PackRoleLight;
	light.Direction.y = -1*light.Direction.y;

	RECT rcDst = 
	{
		m_ViewPort.X, m_ViewPort.Y, m_ViewPort.X+m_ViewPort.Width, m_ViewPort.Y + m_ViewPort.Height
	};

	RECT rcSrc =
	{
		0, 0, m_ViewPort.Width, m_ViewPort.Height
	};

	GetDrawer()->FillRect2D(rcDst, 0);

	FLOAT fAspect = ((FLOAT)m_ViewPort.Width) / (float)m_ViewPort.Height;
	m_Camera.SetProjParams( D3DX_PI/180*45.0f, fAspect, 1.0f, 12000.0f );

	D3DXMATRIX matView;
	D3DXMATRIX matWorld, matOldWorld;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matTransform1;

	//pd3dDevice->GetTransform( D3DTS_WORLD, &matOldWorld );

	float x = 0, y = -14, z = 0;
	CPlayerAnim* pAnim = m_PlayerAnims[idx];
	/*if(theHeroGame.GetPlayerMgr()->GetMe())
		pAnim->SetPlayer(theHeroGame.GetPlayerMgr()->GetMe());*/
	DWORD dwTime = HQ_TimeGetTime();
	if( pAnim )
	{
		pAnim->SetPosition( x, y, z );
		if ( m_pPlayers[idx]->GetSex() == Sex_Male )
			pAnim->SetScale( 0.06f/*Config::m_fMdlSpaceScale* pViewport->m_fRoleScaleMale*/ );
		else
			pAnim->SetScale( 0.06f/*0.07f*//*Config::m_fMdlSpaceScale* pViewport->m_fRoleScaleFemale*/ );

		pAnim->CalcTransformMatrix( (MeMatrix*)&matTransform1 );
		pAnim->Update( dwTime, (MeMatrix*)&matTransform1 );
		pAnim->UpdateComponents( dwTime, (MeMatrix*)&matTransform1 );
	}

	static float fDist = 22.79f;
	static float fRotate = 0.0f;
	static float fRotateX = 0.98199f;
	static D3DXVECTOR3 vEyePt( 0,-1.2f,3.3f );
	static D3DXVECTOR3 vLookatPt( 0.0f,0.0f,0.0f );

	D3DXVECTOR3 vDist = vEyePt-vLookatPt;
	D3DXVec3Normalize( &vDist, &vDist );

	D3DXVECTOR3 vXAxis( 1, 0, 0 );
	D3DXMATRIX matRotX;
	D3DXMatrixRotationAxis(
		&matRotX,
		&vXAxis,
		fRotateX );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );

	D3DXVECTOR3 vZAxis( 0, 0, -1 );
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis(
		&matRotZ,
		&vZAxis,
		fRotate );

	D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );

	D3DXVECTOR3 vPos( 0, 0, 0 );
	m_Camera.SetViewParams( vPos+vDist*fDist, vPos, D3DXVECTOR3( 0, 0, 1 ) );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&m_Camera.GetViewMatrix() );
	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_Camera.GetProjMatrix() );
	float oldLodBias = GetMe3dConfig()->GetMipLodBais();
	GetMe3dConfig()->SetMipLodBais(-1.2);

	r->SetEyePt( (float*)&vEyePt );	
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	r->SetRenderState( D3DRS_LIGHTING, TRUE );	
	r->SetRenderState( D3DRS_FOGENABLE , false );	

	bool bUseShader = graphics::ShaderManager::instance()->isUseShader();
	
	RendererDx* pRendererDx = (RendererDx*)r;
	D3DXVECTOR3 vOldLightDir = pRendererDx->GetLightDir( LIGHT_INDEX_TERRAIN );
	D3DXVECTOR3 vNewLightDir = vOldLightDir;	
	vNewLightDir = vDist;
	D3DXVec3Normalize( &vNewLightDir, &vNewLightDir );
	D3DLIGHT9 kOldLight = SwGlobal::GetRender()->GetD9Light();
	D3DLIGHT9 kLight;
	kLight.Type = D3DLIGHT_DIRECTIONAL;	
	kLight.Ambient = D3DXCOLOR( m_fLightTry1, m_fLightTry1, m_fLightTry1, 1.0f );
	kLight.Diffuse = D3DXCOLOR( m_fLightTry2, m_fLightTry2, m_fLightTry2, 1.0f );
	kLight.Specular = D3DXCOLOR( m_fLightTry3, m_fLightTry3, m_fLightTry3, 1.0f );
	kLight.Direction = vNewLightDir;	
    pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kLight );

	Config::SetCamera(&m_Camera);

	pAnim->SetRotationZ( m_fRotateZ );
	pAnim->SetUpperRot( m_fRotateZ);

	m_pPlayers[idx]->SetCurUpperDir( m_fRotateZ - D3DX_PI/2);
	m_pPlayers[idx]->SetLowerDir( m_fRotateZ - D3DX_PI/2);

	m_pPlayers[idx]->SetPos(x, y, z);

	// update effect
	m_pPlayers[idx]->UpdateEffectHelper();
	m_pPlayers[idx]->_UpdateFullStarEffect(x, y, true, pAnim->GetScale());
	m_pPlayers[idx]->_UpdateFiveElementEffect(true, pAnim->GetScale());

	pAnim->Render( 1.0f );

	GetEffectMgr()->SetTheLookerPos( m_Camera.GetEyePt() );
	GetEffectMgr()->SetTheLookerViewDistance( 50 );
	GetEffectMgr()->Update(dwTime);

	m_pPlayers[idx]->_RenderFullStarEffect();
	m_pPlayers[idx]->_RenderFiveElement();

	GetEngine()->GetRenderer()->Flush( eSortByFarZ );
	MeRenderManager::Instance()->DoRender(false);
	MeRenderManager::Instance()->DoRender(true);

	Config::SetCamera(getwsCamera()->GetMeCamera());	
	pRendererDx->SetLight( LIGHT_INDEX_TERRAIN, (void*)&kOldLight );

	r->SetTransform( D3DTS_PROJECTION, (FLOAT*)&getwsCamera()->GetMeCamera()->GetProjMatrix()  );
	r->SetTransform( D3DTS_VIEW, (FLOAT*)&getwsCamera()->GetMeCamera()->GetViewMatrix()  );
	GetMe3dConfig()->SetMipLodBais(oldLodBias);

	r->EndScene();
	RECT ViewportRect; 
	SetRect( &ViewportRect, m_ViewPort.X, m_ViewPort.Y, 
		m_ViewPort.X + m_ViewPort.Width,
		m_ViewPort.Y + m_ViewPort.Height );

	getwsCamera()->ResetViewport();
}
//=====================function===================
bool CallBack_AskTeamFollow( char bIsTell, void *pData )
{
	MsgAckTeamFollow msg;
	if ( bIsTell == 0 )
	{
		msg.blAccept = false;
	}
	else
	{
		msg.blAccept = true;
	}
	GettheNetworkInput().SendMsg( &msg );
	return true;
}

void CUI_ID_FRAME_Team::OnMsgAskTeamFollow( Msg* msg )
{
	//如果已经处于跟随状态就不做处理
	if ( GetTeamFollowID() >= 0 )
	{
		return;
	}
	
	s_CUI_ID_FRAME_MessageBox.closeAll(false);
	s_CUI_ID_FRAME_MessageBox.Show(
		theXmlString.GetString(eText_Team_HeadInviteFollow),
		theXmlString.GetString(eText_PKMode_Team),
		CUI_ID_FRAME_MessageBox::eTypeAcceptReject,
		true,
		CallBack_AskTeamFollow );
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(10);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);	
}

void CUI_ID_FRAME_Team::OnMsgTeamFollowTo( Msg* msg )
{
	MsgFollowTeamMember* pMsg = (MsgFollowTeamMember*)msg;
	//s_CUI_ID_FRAME_Target.SetFollowPlayerId(pMsg->nMemberID);
	SetTeamFollowID( pMsg->nMemberID );
	m_pID_BUTTON_FollowBreak->SetVisable(true);
	s_CUI_ID_FRAME_AutoAttackSet.EndAutoAttack();//确定组队跟随则 打断自动挂机
}

void CUI_ID_FRAME_Team::OnMsgHeaderCancelTeamFollow( Msg* msg )
{
	if ( GetTeamFollowID() >= 0 )
	{
		//SetTeamFollowID( -1 );
		m_pID_BUTTON_FollowBreak->SetVisable(false);
	}
	
}

void CUI_ID_FRAME_Team::OnMsgMemberCountInTeamFollow( Msg* msg )
{
	//这个只有队长处理
	if ( thePlayerRole.IsTeamHeader() == FALSE )
	{
		return;
	}
	
	MsgMemberCountInTeamFollow* pMsg = (MsgMemberCountInTeamFollow*)msg;
	m_nTeamFollowCount = pMsg->nMemberCountInTeamFollow;
	RefreshFollowButtons();
	
	
}

bool CUI_ID_FRAME_Team::IsPlayerSelected()
{
		if ((ControlCheckBox*)m_pID_CHECKBOX_Player1->IsChecked())  return true;
		if ((ControlCheckBox*)m_pID_CHECKBOX_Player2->IsChecked())  return true;
		if ((ControlCheckBox*)m_pID_CHECKBOX_Player3->IsChecked())  return true;
		if ((ControlCheckBox*)m_pID_CHECKBOX_Player4->IsChecked())  return true;
		if ((ControlCheckBox*)m_pID_CHECKBOX_Player5->IsChecked())  return true;
		if ((ControlCheckBox*)m_pID_CHECKBOX_Player6->IsChecked())  return true;

		return false;
}
void CUI_ID_FRAME_Team::ClearAllTeamMutiMap()
{
	//清空队伍全部的副本 
	//1.判断是否有队伍
	//2.判断是否为队长
	//3.判断是否在副本里
	//4.判断队员是否在副本里
	//5.发送命令道服务器端去

	//副本重置操作CD1分钟
	if (Clear_Time > HQ_TimeGetTime())
	{
		char cdbuff[255];
		sprintf_s(cdbuff,255,theXmlString.GetString(eClient_ClearTeam_CD),(Clear_Time - HQ_TimeGetTime())/1000 + 1);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,cdbuff);
		return;
	}

	if(thePlayerRole.GetGroupId() == -1)
	{
		//提示玩家无队伍
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_ClearTeam_NonTeam));
		return;
	}
	else if(!thePlayerRole.IsTeamHeader())
	{
		//不是队长 提示玩家无权限操作队伍的操作
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_ClearTeam_NonTeamHeader));
		return;
	}
	std::vector<TeamInfo> vecTeam = thePlayerRole.GetTeamInfo();
	std::vector<TeamInfo>::iterator Iter = vecTeam.begin();
	for(;Iter != vecTeam.end(); ++Iter)
	{
		MapConfig::MapData* pMap = theMapConfig.GetMapDataById(Iter->nMapID);
		if(!pMap)
			continue;
		if(pMap->GetMapType() == MapConfig::MT_SingleTeam)
		{
			//未副本地图 
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eClient_ClearTeam_TeamMemberError));
			return;
		}
	}
	//发送命令
	MsgClearTeamMapReq msg;
	GettheNetworkInput().SendMsg( &msg );

	Clear_Time = HQ_TimeGetTime() + 60000;
}