/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\RbtnMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "RbtnMenu.h"
#include "PetRbtnMenu.h"
#include "actionUI.h"
#include "../Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "Group.h"
#include "ChatInfoBox.h"
#include "FriendDlg.h"
#include "SeekEquip.h"
#include "Target.h"
#include "XmlStringLanguage.h"
#include "AddMember.h"
#include "baseProperty.h"
#include "ChatMessageMgr.h"
#include "SelfRbtnMenu.h"
#include "MeTerrain/stdafx.h"
#include "color_config.h"
#include "ui/PrivateShop.h"
#include "GivePresent.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "GivePresentLogic.h"
#include "Ui/InfoList.h"
#include "RelationMessage.h"
#include "ui/AddFriend.h"
#include "FamilyMessage.h"
#include "SystemFamily.h"
#include "AutoAttackSet.h"
#include "Rename.h"
extern int g_nCharacterDBID;
extern BOOL g_bAutoPlayInteractionWithTarget;
#include "MapConfig.h"

static bool RbtnMenuMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( !s_CUI_ID_FRAME_RBTNMENU.IsVisable() )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE )
			{
				s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
				return true;
			}
		}
		break;
	}

	return false;
}

CUI_ID_FRAME_RBTNMENU s_CUI_ID_FRAME_RBTNMENU;
MAP_FRAME_RUN( s_CUI_ID_FRAME_RBTNMENU, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_RBTNMENU, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_TERMOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_TERM2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_EXCHANGEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_FRDOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_KICKOUTOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_PrivateOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_SEEKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_DUELOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_UpgradeTeamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_GUILDOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_TuanOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_HeimingdanOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_FOLLOWMEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_WaiguaOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_FuzhiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_MessageChatOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_LockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_UnLockOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_AddHeiOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_FRDClassOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_RemarkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_DelFriendOnButtonClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_SQQCOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_YQQCOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_AddFamilyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RBTNMENU, ID_BUTTON_AddVendettaOnButtonClick )

CUI_ID_FRAME_RBTNMENU::CUI_ID_FRAME_RBTNMENU()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_RBTNMENU::ResetMembers()
{
	m_pID_FRAME_RBTNMENU = NULL;
	m_pID_BUTTON_TERM = NULL;
	m_pID_BUTTON_TERM2 = NULL;
	m_pID_BUTTON_EXCHANGE = NULL;
	m_pID_BUTTON_FRD = NULL;
	m_pID_BUTTON_KICKOUT = NULL;
	m_pID_BUTTON_Private = NULL;
	m_pID_BUTTON_SEEK = NULL;
	m_pID_BUTTON_DUEL = NULL;
	m_pID_BUTTON_UpgradeTeam = NULL;
	m_pID_BUTTON_GUILD = NULL;
	m_pID_BUTTON_Tuan = NULL;
	m_pID_BUTTON_FOLLOWME = NULL;
	//m_pID_BUTTON_Waigua = NULL;
	m_pID_BUTTON_Fuzhi = NULL;
 	m_pID_BUTTON_MessageChat = NULL;
	m_pID_BUTTON_Lock = NULL;
	m_pID_BUTTON_UnLock = NULL;
	m_pID_BUTTON_AddHei = NULL;
	m_pID_BUTTON_FRDClass = NULL;
	m_pID_PICTURE_1 = NULL;
	m_pID_BUTTON_Remark = NULL;

	m_pID_BUTTON_SQQC = NULL;
	m_pID_BUTTON_YQQC = NULL;
	m_pID_BUTTON_AddFamily = NULL;
	m_pID_BUTTON_AddVendetta = NULL;

}

// Frame
bool CUI_ID_FRAME_RBTNMENU::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_RBTNMENU::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_TERMOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	InviteTeam(m_szName);
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_TERM2OnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RBTNMENU )
		return false;
	InviteTeam(m_szName);
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_EXCHANGEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
    if( !CWealthProtect::Instance().IsInProtectTime() && !CPreventWallow::Instance().IsFCMNotHealthy() )
    {	
		if ( theHeroGame.GetPlayerMgr()->GetMe()->IsDueling() )
		{
			// 决斗时不能交易
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_FailedReason, theXmlString.GetString(eText_ExchangeFailed_InDueling) );
		}
		else if ( s_CUI_ID_FRAME_PrivateShop.IsVisable() || s_CUI_ID_FRAME_PrivateShop.IsOpening() )
		{
			// 摆摊中无法交易
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_FailedReason, theXmlString.GetString(eText_BargainFailed_InPrivateShop) );
		}
		else if ( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting) )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Trade_FailedReason, theXmlString.GetString(eText_BargainFailed_InFightState) );
		}
		else
		{
			s_CUI_ID_FRAME_ActionUI.SetCurFunction( CUI_ID_FRAME_BaseProperty::TYPE_BARGAINING );
			s_CUI_ID_FRAME_ActionUI.Process();
		}
    }
	//--
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_FRDOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	SetVisable( FALSE );

	s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_AddFriendFromRMenu );
	s_CUI_ID_FRAME_AddFriend.SetPrivateName(m_szName.c_str());
	s_CUI_ID_FRAME_AddFriend.SetVisable(true);

    return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_KICKOUTOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	MsgKickFromTeam msg;
	msg.dwWho = thePlayerRole.GetTeamMemberId(GetPrivateName());
	if (msg.dwWho != -1)
	{
		GettheNetworkInput().SendMsg( &msg );
	}

	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_PrivateOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	if( m_szName.length() > 0 )
	{
		s_CUI_ChatInfoBox.Begin2Secret( m_szName.c_str() );
		s_CUI_ChatInfoBox.SetChatTypeChannel(CUI_ChatInfoBox::CHAT_PRIVATE);
	}	
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_SEEKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	GameObjectId TargetPlayID = s_CUI_ID_FRAME_Target.GetPlayerID();
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( TargetPlayID );
	if( pPlayer )
	{
		if( pPlayer->GetMonsterType() == eMT_IllusionMonster )
		{
			GameObjectId MasterPlayID = pPlayer->GetMasterID();
			CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID( MasterPlayID );

			if( pMasterPlayer )
				TargetPlayID = MasterPlayID;
			else
				return false;
		}

		MsgWantPeek msg;
		msg.type = MsgWantPeek::EPT_Char;
		msg.stTargetID = TargetPlayID;
		GettheNetworkInput().SendMsg( &msg );
	}
	SetVisable( FALSE ); 
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_DUELOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	s_CUI_ID_FRAME_ActionUI.SetCurFunction( CUI_ID_FRAME_BaseProperty::TYPE_REQ_DUEL );
	s_CUI_ID_FRAME_ActionUI.Process();
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_UpgradeTeamOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	MsgReqUpgradeTeam msg;
	msg.dwID = m_dwDBID;
	GettheNetworkInput().SendMsg( &msg );
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_GUILDOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_TuanOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	SetVisable( FALSE ); 
	return true;
}

bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_FOLLOWMEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	CPlayer* pPlayer =  theHeroGame.GetPlayerMgr()->FindByName( m_szName.c_str());
	if( pPlayer && pPlayer->GetDistanceToRole() < PLAYER_RENDER_DIST_MAX )
	{
		s_CUI_ID_FRAME_Target.SetFollowPlayerId(pPlayer->GetID());
		s_CUI_ID_FRAME_AutoAttackSet.EndAutoAttack(); //选择跟随目标则 打断自动挂机
		SetVisable( FALSE ); 
	}
	return true;
}

//bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_WaiguaOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_RBTNMENU )
//		return false;
//	SetVisable( FALSE ); 
//	return true;
//}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_FuzhiOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	SetVisable( FALSE ); 

	const char* szText = GetPrivateName();
	if( !szText || strlen(szText) == 0 )
		return true;

	if( !OpenClipboard(0) )
		return true;
	EmptyClipboard();
	HGLOBAL clipbuffer;
	clipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(szText)+1);
	char* buffer = (char*)GlobalLock(clipbuffer);
	strcpy_s(buffer, strlen(szText)+1, szText );
	GlobalUnlock(clipbuffer);
	SetClipboardData(CF_TEXT, clipbuffer);
	CloseClipboard();
	return true;
}
// Button
 bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_MessageChatOnButtonClick( ControlObject* pSender )
 {
 	if( !m_pID_FRAME_RBTNMENU )
 		return false;
 	SetVisable( FALSE ); 
 
 	chatMessageManage.ShowChatMessageFrame(m_szName.c_str());
 	return true;
 }

bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_AddHeiOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_RBTNMENU)
	{
		return false;
	}
	MsgAddRelationReq msg;
	MeSprintf_s(msg.szName, sizeof(msg.szName)/sizeof(char) - 1, "%s", m_szName.c_str());
	msg.stRelation = RelationDefine::BlackList;
	GettheNetworkInput().SendMsg(&msg);
	SetVisable( FALSE ); 
	return true;
}

// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_AddVendettaOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_RBTNMENU)
	{
		return false;
	}
	MsgAddRelationReq msg;
	MeSprintf_s(msg.szName, sizeof(msg.szName)/sizeof(char) - 1, "%s", m_szName.c_str());
	msg.stRelation = RelationDefine::Vendetta;
	GettheNetworkInput().SendMsg(&msg);
	SetVisable( FALSE ); 
	return true;
}


 bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_LockOnButtonClick( ControlObject* pSender )
 {
	 if( !m_pID_FRAME_RBTNMENU )
		 return false;
	 SetVisable( FALSE ); 

	 MsgRelationLockReq msg;
	 msg.nPlayerID = thePlayerRole.GetdbID(GetPrivateName());
	 if (msg.nPlayerID != -1 && thePlayerRole.isChouRen(GetPrivateName()))
	 {
		 GettheNetworkInput().SendMsg(&msg);
		 return true;
	 }
	 return false;
 }

 bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_UnLockOnButtonClick( ControlObject* pSender )
 {
	 if( !m_pID_FRAME_RBTNMENU )
		 return false;
	 SetVisable( FALSE ); 

	 MsgRelationUnLockReq msg;
	 msg.nPlayerID = thePlayerRole.GetdbID(GetPrivateName());
	 if (msg.nPlayerID != -1 && thePlayerRole.isFrdInBlackList(GetPrivateName()))
	 {
		 GettheNetworkInput().SendMsg(&msg);
		 return true;
	 }
	 return false;
 }

 // Button
 bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_AddFamilyOnButtonClick( ControlObject* pSender )
 {
	 if ( !m_pID_FRAME_RBTNMENU )
		 return false;

	 MsgInviteFamilyReq msg;
	 MeSprintf_s(msg.szPlayerName, sizeof(msg.szPlayerName)/sizeof(char) - 1, "%s", m_szName.c_str());
	 GettheNetworkInput().SendMsg(&msg);
	 this->SetVisable(false);
	 return true;
 }

bool CUI_ID_FRAME_RBTNMENU::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\RbtnMenu.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\RbtnMenu.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_FRDClassOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RBTNMENU )
		return false;
	s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_ChangeFriendToGroup );
	s_CUI_ID_FRAME_AddFriend.SetPrivateName(m_szName.c_str());
	s_CUI_ID_FRAME_AddFriend.SetVisable(true);
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_RemarkOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RBTNMENU )
		return false;
	s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangeFriendTag);
	s_CUI_ID_FRAME_Rename.SetVisable(true);
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_DelFriendOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RBTNMENU )
		return false;
	CUI_ID_FRAME_Friend::ID_BUTTON_RemoveOnButtonClick(NULL);
	SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_SQQCOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RBTNMENU )
		return false;

	theHeroGame.GetPlayerMgr()->RequestGetOnOtherPet( theHeroGame.GetPlayerMgr()->FindByName(m_szName.c_str()) );
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_RBTNMENU::ID_BUTTON_YQQCOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RBTNMENU )
		return false;

	theHeroGame.GetPlayerMgr()->RequestGetOnOtherPet( theHeroGame.GetPlayerMgr()->FindByName(m_szName.c_str()) );
	SetVisable(false);
	return true;
}

// 关连控件
bool CUI_ID_FRAME_RBTNMENU::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_RBTNMENU, s_CUI_ID_FRAME_RBTNMENUOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_RBTNMENU, s_CUI_ID_FRAME_RBTNMENUOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_TERM, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_TERMOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_EXCHANGE, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_EXCHANGEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_FRD, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_FRDOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_KICKOUT, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_KICKOUTOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Private, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_PrivateOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_SEEK, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_SEEKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_DUEL, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_DUELOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_UpgradeTeam, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_UpgradeTeamOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_GUILD, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_GUILDOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Tuan, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_TuanOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Heimingdan, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_HeimingdanOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_FOLLOWME, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_FOLLOWMEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Waigua, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_WaiguaOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Fuzhi, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_FuzhiOnButtonClick );
 	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_MessageChat, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_MessageChatOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Lock, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_LockOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_UnLock, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_UnLockOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_AddHei, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_AddHeiOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_FRDClass, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_FRDClassOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_Remark, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_RemarkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_DelFriend, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_DelFriendOnButtonClick );

	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_SQQC, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_SQQCOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_YQQC, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_YQQCOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_AddFamily, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_AddFamilyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_TERM2, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_TERM2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RBTNMENU, ID_BUTTON_AddVendetta, s_CUI_ID_FRAME_RBTNMENUID_BUTTON_AddVendettaOnButtonClick );

	m_pID_FRAME_RBTNMENU = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_RBTNMENU );
	m_pID_BUTTON_TERM = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_TERM );
	m_pID_BUTTON_EXCHANGE = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_EXCHANGE );
	m_pID_BUTTON_FRD = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_FRD );
	m_pID_BUTTON_KICKOUT = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_KICKOUT );
	m_pID_BUTTON_Private = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Private );
	m_pID_BUTTON_SEEK = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_SEEK );
	m_pID_BUTTON_DUEL = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_DUEL );
	m_pID_BUTTON_UpgradeTeam = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_UpgradeTeam );
	/*m_pID_BUTTON_GUILD = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_GUILD );*/
//	m_pID_BUTTON_Gang = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Gang );
	/*m_pID_BUTTON_Tuan = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Tuan );*/
//	m_pID_BUTTON_Heimingdan = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Heimingdan );
	m_pID_BUTTON_FOLLOWME = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_FOLLOWME );
	//m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_CLOSE );
	//m_pID_BUTTON_Waigua = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Waigua );
	m_pID_BUTTON_Fuzhi = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Fuzhi );
	m_pID_BUTTON_MessageChat = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_MessageChat);
	m_pID_BUTTON_Lock = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Lock);
	m_pID_BUTTON_UnLock = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_UnLock);
	m_pID_BUTTON_AddHei = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_AddHei);
	m_pID_BUTTON_FRDClass = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_FRDClass );
	m_pID_PICTURE_1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_PICTURE_1 );
	m_pID_BUTTON_Remark = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_Remark );
	m_pID_BUTTON_DelFriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_DelFriend );

	m_pID_BUTTON_SQQC = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_SQQC );
	m_pID_BUTTON_YQQC = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_YQQC );
	m_pID_BUTTON_AddFamily = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_AddFamily );
	m_pID_BUTTON_TERM2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_TERM2 );
	m_pID_BUTTON_AddVendetta = (ControlButton*)theUiManager.FindControl( ID_FRAME_RBTNMENU, ID_BUTTON_AddVendetta );

	assert( m_pID_FRAME_RBTNMENU );
	assert( m_pID_BUTTON_TERM );
	assert( m_pID_BUTTON_EXCHANGE );
	assert( m_pID_BUTTON_FRD );
	assert( m_pID_BUTTON_KICKOUT );
	assert( m_pID_BUTTON_Private );
	assert( m_pID_BUTTON_SEEK );
	assert( m_pID_BUTTON_DUEL );
	assert( m_pID_BUTTON_UpgradeTeam );
	/*assert( m_pID_BUTTON_GUILD );
	assert( m_pID_BUTTON_Tuan );*/
	assert( m_pID_BUTTON_FOLLOWME );
	//assert( m_pID_BUTTON_Waigua );
	assert( m_pID_BUTTON_Fuzhi );
	assert( m_pID_BUTTON_FRDClass );
	assert( m_pID_PICTURE_1 );
	assert( m_pID_BUTTON_Remark );
	assert( m_pID_BUTTON_DelFriend );

	assert( m_pID_BUTTON_SQQC );
	assert( m_pID_BUTTON_YQQC );
	assert( m_pID_BUTTON_AddFamily );
	assert( m_pID_BUTTON_TERM2 );
	assert( m_pID_BUTTON_AddVendetta );

	m_pID_BUTTON_FRDClass->SetVisable(false);
	m_pID_PICTURE_1->SetVisable(false);
	m_pID_BUTTON_Remark->SetVisable(false);
	m_pID_BUTTON_DelFriend->SetVisable(false);

	m_pID_FRAME_RBTNMENU->SetVisable( false );
	m_pID_FRAME_RBTNMENU->SetMsgProcFun( RbtnMenuMsgProc );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_RBTNMENU::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\RbtnMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_RBTNMENU::_IsVisable()
{
	if( !m_pID_FRAME_RBTNMENU )
		return false;
	return m_pID_FRAME_RBTNMENU->IsVisable();
}

void CUI_ID_FRAME_RBTNMENU::SetLockAndUnLockState()
{
	if (thePlayerRole.IsFriend(m_szName.c_str()) || thePlayerRole.IsTempFriend(m_szName.c_str()))
	{
		m_pID_BUTTON_Lock->SetVisable(false);
		m_pID_BUTTON_UnLock->SetVisable(false);
		m_pID_BUTTON_AddHei->SetVisable(true);
		m_pID_BUTTON_AddVendetta->SetVisable(true);
// 		m_pID_BUTTON_UpgradeTeam->SetVisable(false);
		return;
	}
	if (thePlayerRole.isFrdInBlackList(m_szName.c_str()))
	{
		m_pID_BUTTON_AddHei->SetVisable(false);
	}
	if (thePlayerRole.isChouRen(m_szName.c_str()))
	{
		m_pID_BUTTON_AddVendetta->SetEnable(false);
		m_pID_BUTTON_AddHei->SetVisable(false);
	}

	if (thePlayerRole.IsPlayerLock(m_szName.c_str()) )
	{
		m_pID_BUTTON_Lock->SetVisable(false);
		m_pID_BUTTON_UnLock->SetVisable(true);
	}
	else
	{
		m_pID_BUTTON_Lock->SetVisable(true);
		m_pID_BUTTON_UnLock->SetVisable(false);
	}
}

// 设置是否可视
void CUI_ID_FRAME_RBTNMENU::_SetVisable(const bool bVisable, bool isOnline)
{
	if( !m_pID_FRAME_RBTNMENU )
		return;
	m_pID_FRAME_RBTNMENU->SetVisable( bVisable );

	if (!bVisable)
	{
		return;
	}

	
	if ( CSystemFamily::Instance()->IsMeFamilyLeader(thePlayerRole.GetDBID()) )
	{
		m_pID_BUTTON_AddFamily->SetEnable(true);
	}
	else
	{
		m_pID_BUTTON_AddFamily->SetEnable(false);
	}
	 

	s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
	s_CUI_ID_FRAME_PetRBMenu.SetVisable(false);
	BOOL bIsTeamHeader = thePlayerRole.IsTeamHeader();

	CPlayer* pTagetPlayer = theHeroGame.GetPlayerMgr()->FindByName(m_szName.c_str());
	SetLockAndUnLockState();
	bool TargetIsMyTeamMember = false;
	if (pTagetPlayer && pTagetPlayer->GetDistanceToRole() > PLAYER_RENDER_DIST_MAX )
	{	
		pTagetPlayer = NULL;
	}
	if (pTagetPlayer)
	{
		s_CUI_ID_FRAME_Target.SetPlayer(pTagetPlayer->GetID());
		theHeroGame.GetPlayerMgr()->SetLockNpc(pTagetPlayer->GetID());
		
		m_pID_BUTTON_YQQC->SetVisable(false);
		m_pID_BUTTON_SQQC->SetVisable(false);
		m_pID_BUTTON_YQQC->SetEnable(true);
		m_pID_BUTTON_SQQC->SetEnable(true);

		CPlayer* player = theHeroGame.GetPlayerMgr()->GetMe();

		if ( pTagetPlayer->MyTeamMember)
		{
			//骑乘相关
			if ( pTagetPlayer->IsMultiMounting() == true && player->IsMounting() == FALSE && player->IsOthersPet() == false )
			{
				//if ( thePlayerRole.IsTeamMember( pTagetPlayer->GetName() ) )
				//{
				//	m_pID_BUTTON_SQQC->SetEnable(true);
				//}
				//else
				//{
				//	m_pID_BUTTON_SQQC->SetEnable(false);
				//}
				//m_pID_BUTTON_YQQC->SetEnable(false);
				m_pID_BUTTON_SQQC->SetVisable(true);
				m_pID_BUTTON_YQQC->SetVisable(false);
			}
			else if ( pTagetPlayer->IsMounting() == FALSE && pTagetPlayer->IsOthersPet() == false && player->IsMultiMounting() == true )
			{
				//m_pID_BUTTON_SQQC->SetEnable(false);
				//m_pID_BUTTON_YQQC->SetEnable(true);
				m_pID_BUTTON_SQQC->SetVisable(true);
				m_pID_BUTTON_SQQC->SetEnable(false);
				m_pID_BUTTON_YQQC->SetVisable(true);
				m_pID_BUTTON_YQQC->SetEnable(true);
			}
			else
			{
				//m_pID_BUTTON_SQQC->SetEnable(false);
				//m_pID_BUTTON_YQQC->SetEnable(false);
				m_pID_BUTTON_SQQC->SetVisable(true);
				m_pID_BUTTON_SQQC->SetEnable(false);
				m_pID_BUTTON_YQQC->SetVisable(true);	//当两个都没有坐骑多人坐骑的时候，显示邀请，但是不可用状态
				m_pID_BUTTON_YQQC->SetEnable(false);
			}
		}
			
			
		

		if ( pTagetPlayer->GetTeamId() != 0 )
		{
			m_pID_BUTTON_TERM->SetVisable(true);	//显示申请
			m_pID_BUTTON_TERM2->SetVisable(false);
		}
		else
		{
			m_pID_BUTTON_TERM->SetVisable(false);
			m_pID_BUTTON_TERM2->SetVisable(true);	//显示邀请
		}
	}
	else
	{
		m_pID_BUTTON_TERM->SetVisable(false);
		m_pID_BUTTON_TERM2->SetVisable(true);	//显示邀请

		if( thePlayerRole.IsTeamMember( m_szName.c_str()) )	//队友 并且不在一张地图
		{
			m_pID_BUTTON_TERM->SetVisable(false);   //ya
			m_pID_BUTTON_TERM2->SetVisable(true);	//显示邀请
			m_pID_BUTTON_TERM2->SetEnable( false );
			TargetIsMyTeamMember = true;
			
		}
	}

	m_pID_BUTTON_KICKOUT->SetEnable( FALSE );
	m_pID_BUTTON_UpgradeTeam->SetEnable( FALSE );
	m_pID_BUTTON_FRD->SetEnable(FALSE);
	m_pID_BUTTON_AddVendetta->SetEnable( FALSE );
	bool bTargetInBlackList = thePlayerRole.isFrdInBlackList(m_szName.c_str());

	UpdateTeamButtonStatus( m_pID_BUTTON_TERM, pTagetPlayer,isOnline,bTargetInBlackList,TargetIsMyTeamMember);
	UpdateTeamButtonStatus( m_pID_BUTTON_TERM2, pTagetPlayer,isOnline,bTargetInBlackList,TargetIsMyTeamMember);

	TeamInfo* pTeamInfo = NULL;
	std::vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
	for(int n=0; n<vecPlayer.size(); n++)
	{
		if(m_szName == vecPlayer[n].szName)
		{
			pTeamInfo = &vecPlayer[n];
			break;
		}
	}

	if( bIsTeamHeader && pTeamInfo)
	{
		m_pID_BUTTON_KICKOUT->SetEnable( TRUE );
		if( !thePlayerRole.m_bCorps && pTeamInfo->bOnline)
			m_pID_BUTTON_UpgradeTeam->SetEnable( TRUE );
	}

	if( !m_szName.empty() )
	{
		if(isOnline && !thePlayerRole.isFrdInBlackList( m_szName.c_str()) )
		{
			m_pID_BUTTON_MessageChat->SetEnable(true);
		}
		else
		{
			m_pID_BUTTON_MessageChat->SetEnable(false);
		}
		if (isOnline && thePlayerRole.CanAddFriend(m_szName.c_str()))
		{
			m_pID_BUTTON_FRD->SetEnable(true);
		}
		else
		{
			m_pID_BUTTON_FRD->SetEnable(false);
		}

		if (thePlayerRole.isChouRen(m_szName.c_str()))
		{
			
			m_pID_BUTTON_AddVendetta->SetEnable(false);
			m_pID_BUTTON_Lock->SetEnable(true);
			m_pID_BUTTON_UnLock->SetEnable(true);
			SetLockAndUnLockState();
		}
		else
		{
			m_pID_BUTTON_AddVendetta->SetEnable(true);
			m_pID_BUTTON_Lock->SetEnable(false);
			m_pID_BUTTON_UnLock->SetEnable(false);
		}
	}
	m_pID_BUTTON_DUEL->SetEnable(false);
	if (pTagetPlayer &&
		( !pTagetPlayer->IsOpenPrivateShop() ) &&
		(theHeroGame.GetPlayerMgr()->GetMe() && !theHeroGame.GetPlayerMgr()->GetMe()->IsOpenPrivateShop()))
	{
		CWorldTile* pCurrTile = CURRENTTILE;
		if (pCurrTile)
		{			
			if (!bTargetInBlackList)
			{
			bool canDuel = pCurrTile->GetCanDuel();

			CMapAreaManager* pAreaManager = theHeroGame.GetPlayerMgr()->m_StageDataLoader.GetMapAreaManager();
			if(pAreaManager)
			{
				int nMaxArea = pAreaManager->GetMaxArea();
				for (int n = 0;n < nMaxArea;++n)
				{
					SArea* pArea = pAreaManager->GetAreaByID(n);
					if(!pArea)
						continue;

					//与服务器逻辑匹配起来,zone的update通过配置脚本来触发,客户端如果没有也不check zone的属性
					if((pArea->m_strEnterScript.empty()&&pArea->m_strLeaveScript.empty())
						||(strcmp(pArea->m_strEnterScript.c_str(),"NA") == 0&&strcmp(pArea->m_strLeaveScript.c_str(),"NA") == 0))
						continue;

                    //切磋对象所在区域是否可以切磋
					float fx = 0.0f,fy = 0.0f,fz = 0.0f;
					float fx1 = 0.0f,fy1 = 0.0f,fz1 = 0.0f;
					pTagetPlayer->GetPos( &fx, &fy, &fz );
					POINT pt , pt1;
					pt.x = fx;
					pt.y = fy;

					RECT rc;
					rc.left = TileToFloat(pArea->m_rcArea.left);
					rc.top  = TileToFloat(pArea->m_rcArea.top);
					rc.right = TileToFloat(pArea->m_rcArea.right);
					rc.bottom = TileToFloat(pArea->m_rcArea.bottom);

					//主角所在区域是否可以切磋
					theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&fx1, &fy1, &fz1);
					pt1.x = fx1;
					pt1.y = fy1;


                    //区域不可企切磋 只要有1个人在 就不能切磋
					if(!pArea->m_bCanDuel)
					{
				      if(PtInRect(&rc,pt) || PtInRect(&rc,pt1))
					  {
						 canDuel = false;
						 break;
					  }
					}
				
					
				}
			}
            if(canDuel)
			m_pID_BUTTON_DUEL->SetEnable(true);
			}
		}
	}

	m_pID_BUTTON_Private->SetEnable(isOnline&&(!bTargetInBlackList));
	m_pID_BUTTON_FOLLOWME->SetEnable(pTagetPlayer != NULL);
	m_pID_BUTTON_SEEK->SetEnable(pTagetPlayer != NULL);
	m_pID_BUTTON_EXCHANGE->SetEnable((pTagetPlayer != NULL)&&(!bTargetInBlackList));

	if (m_eShowType == eShow_Gang)
	{
		m_pID_BUTTON_KICKOUT->SetEnable(false);
		m_pID_BUTTON_UpgradeTeam->SetEnable(false);
		m_pID_BUTTON_Lock->SetEnable(false);
		m_pID_BUTTON_UnLock->SetEnable(false);
		m_pID_BUTTON_AddHei->SetEnable(false);
		m_pID_BUTTON_AddVendetta->SetEnable(false);
		m_pID_BUTTON_TERM->SetCaption( theXmlString.GetString(eText_InviteTeam));
	}
	m_pID_BUTTON_FRD->SetVisable(true);
	m_pID_BUTTON_FRDClass->SetVisable(false);
	m_pID_PICTURE_1->SetVisable(false);
	m_pID_BUTTON_Remark->SetVisable(false);
	m_pID_BUTTON_DelFriend->SetVisable(false);
	if (eShow_FriendFriend == m_eShowType)
	{
		m_pID_BUTTON_FRDClass->SetVisable(true);
		m_pID_BUTTON_FRD->SetVisable(false);
	}
	if (eShow_FriendFriend == m_eShowType || eShow_FriendOther == m_eShowType)
	{
		m_pID_PICTURE_1->SetVisable(true);
		m_pID_BUTTON_Remark->SetVisable(true);
		m_pID_BUTTON_DelFriend->SetVisable(true);
	}
	m_eShowType = eShow_normal;
}
extern HWND g_hWnd;
void CUI_ID_FRAME_RBTNMENU::SetPos(INT x, INT y)
{
	if( !m_pID_FRAME_RBTNMENU )
		return;
	RECT rcWindowClient;
	GetClientRect( g_hWnd, &rcWindowClient );

	RECT RbtRect;
	m_pID_FRAME_RBTNMENU->GetRealRect(&RbtRect);
	LONG lWidth = RbtRect.right - RbtRect.left;
	LONG lHeight = RbtRect.bottom - RbtRect.top;
	if (x + lWidth > rcWindowClient.right)
	{
		x = rcWindowClient.right - lWidth;
	}
	if (y + lHeight > rcWindowClient.bottom)
	{
		y = rcWindowClient.bottom - lHeight;
	}
	m_pID_FRAME_RBTNMENU->SetScreenPos(x, y);
}

void CUI_ID_FRAME_RBTNMENU::SetPrivateName( const char* szName )
{
	if (szName)
	{
		m_szName = szName;
	}
	else
	{
		m_szName.clear();
	}
}

void CUI_ID_FRAME_RBTNMENU::SetVisable( const bool bVisable, bool isOnline /*= true */ )
{
	CUIBase::SetVisable(bVisable);
	if (m_bUILoad)
	_SetVisable(bVisable,isOnline);
}

void CUI_ID_FRAME_RBTNMENU::UpdateTeamButtonStatus( ControlButton* pTeamButton,CPlayer* pTagetPlayer, bool isOnline,bool bTargetInBlackList ,bool bTeamMember)
{//这里的状态重新写了,有点乱 vvx 2013.6.13
	//自己有队伍:目标在线,目标没有队伍,目标不是黑名单,自己是队长,队伍人数少于5个
	//自己没队伍:目标在线,目标没有队伍,目标不是黑名单
	BOOL bIsTeamHeader = thePlayerRole.IsTeamHeader();
	BOOL bIsInOneTeam =  thePlayerRole.IsTeamMember(thePlayerRole.GetName());
	pTeamButton->SetEnable( FALSE );
	if (isOnline&&pTagetPlayer&&!bTargetInBlackList)
	{
		bool bTargetIsInTeamer = pTagetPlayer->IsInOneTeam();
		if (s_CUI_ID_FRAME_RBTNMENU.m_pID_BUTTON_TERM2 == pTeamButton&&!bTargetIsInTeamer)
		{			
			if (bIsInOneTeam&&bIsTeamHeader)
			{
				int teamnum = thePlayerRole.GetTeamMemberNum();
				if (teamnum > 0 && teamnum < TeamMaxManipleMember) 
				{
					pTeamButton->SetEnable( TRUE );
				}
			}
			else if(!bIsInOneTeam)
			{
				pTeamButton->SetEnable( TRUE );
			}
		}
		else if (s_CUI_ID_FRAME_RBTNMENU.m_pID_BUTTON_TERM == pTeamButton && bTargetIsInTeamer)
		{
			/*bool bTargetIsTeamHeader = pTagetPlayer->IsTeamHeader();
			if (bTargetIsTeamHeader)
			{*/
			pTeamButton->SetEnable( TRUE );//目标有队伍 自己无队伍
			/*}*/
		}		
		//if( thePlayerRole.GetTeamMemberNum() > 0)
		//{
		//	if (!bTargetIsInTeamer)
		//	{
		//		if( bIsTeamHeader )
		//		{
		//			if (!bTargetInBlackList)
		//			{
		//				pTeamButton->SetEnable( TRUE );
		//			}
		//		}
		//	}
		//}
		//else
		//{
		//	if (bTargetIsInTeamer)
		//	{
		//		//pTeamButton->SetCaption( theXmlString.GetString(eText_ApplyTeam));
		//	}
		//	else
		//	{
		//		//pTeamButton->SetCaption( theXmlString.GetString(eText_InviteTeam));
		//	}
		//	/*if (!bTargetInBlackList)
		//		pTeamButton->SetEnable( TRUE ); */
		//}
	}
	else if (!pTagetPlayer&&!bTargetInBlackList)
	{
		if (s_CUI_ID_FRAME_RBTNMENU.m_pID_BUTTON_TERM2 == pTeamButton)
		{
			if (bIsInOneTeam&&bIsTeamHeader)
			{
				int teamnum = thePlayerRole.GetTeamMemberNum();
				if (teamnum > 0 && teamnum < TeamMaxManipleMember && !bTeamMember)
				{
					pTeamButton->SetEnable( TRUE );
				}
			}
			else if(!bIsInOneTeam)
			{
				pTeamButton->SetEnable( TRUE );
			}
		}
	}
	if ( pTagetPlayer && pTagetPlayer->MyTeamMember ) //目标和主角在同一个队伍中，则申请组队 和邀请组队按钮全部设置为不可操作状态
	{
		pTeamButton->SetEnable(FALSE);
	}

	//if (isOnline && pTeamButton == s_CUI_ID_FRAME_RBTNMENU.m_pID_BUTTON_TERM)
	//{
	//	bool bTargetIsTeamHeader = false;
	//	if (pTagetPlayer)
	//		bTargetIsTeamHeader = pTagetPlayer->IsTeamHeader();
	//	if (!thePlayerRole.IsTeamMember(thePlayerRole.GetName()) && bTargetIsTeamHeader)
	//	{
	//		if (!bTargetInBlackList)
	//		{
	//			pTeamButton->SetEnable( TRUE );
	//		}
	//	}
	//}

	//if (isOnline/*&&pTeamButton == s_CUI_ID_FRAME_RBTNMENU.m_pID_BUTTON_TERM2*/)
	//{
	//	bool bTargetIsInTeam = false;
	//	if (pTagetPlayer)
	//		bTargetIsInTeam = pTagetPlayer->IsInOneTeam();
	//	if (!thePlayerRole.IsTeamMember(thePlayerRole.GetName()) && !bTargetIsInTeam)
	//	{
	//		if (!bTargetInBlackList)
	//		{
	//			pTeamButton->SetEnable( TRUE );
	//		}
	//	}
	//}
}

bool CUI_ID_FRAME_RBTNMENU::InviteTeam( std::string& strPlayerName )
{
	if( strPlayerName.compare(thePlayerRole.GetName()) == 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, theXmlString.GetString(eUI_SendTeam_fail) );
		return false;
	}

	char szInfo[128] = {0};

	sprintf_s( szInfo, sizeof(szInfo)-1, "%s ~%s_ %s", 
		theXmlString.GetString(eUI_YouTo), strPlayerName.c_str(),
		theXmlString.GetString(eUI_SendTeam));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Team_MakeGroup, szInfo );

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
	strncpy(msg.szNewbieName, strPlayerName.c_str(), sizeof(msg.szNewbieName)-1);
	GettheNetworkInput().SendMsg(&msg);
	return true;
}