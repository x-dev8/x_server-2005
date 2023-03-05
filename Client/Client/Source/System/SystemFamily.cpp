
#include "FamilyDefine.h"
#include "FamilyMessage.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "ScreenInfoManager.h"
#include "ui/Family.h"
#include "ui/FamilyMessageBox.h"
#include "Common.h"
#include "SystemFamily.h"

void CSystemFamily::OnMsgAllFamilyInfoList( Msg* pMsg )
{
	MsgAllFamilyInfoList* msgInfoList = (MsgAllFamilyInfoList*)pMsg;
	for ( int i = 0; i < msgInfoList->nFamilyCount; i ++ )
	{
		//m_mapFamilySimpleInfo.insert( std::pair<unsigned int,FamilyDefine::FamilySimpleInfo>(msgInfoList->infoList[i].GetFamilyID(), msgInfoList->infoList[i]) );
		m_mapFamilySimpleInfo[msgInfoList->infoList[i].GetFamilyID()] = msgInfoList->infoList[i];
	}
}

void CSystemFamily::OnMsgTellCreateFmily( Msg *pMsg )
{
	MsgTellCreateFamily* msgCreate = (MsgTellCreateFamily*)pMsg;
	FamilySimpleInfoSetIt_t it = m_mapFamilySimpleInfo.find( msgCreate->nFamilyID );
	if ( it != m_mapFamilySimpleInfo.end() )
	{
		//列表中已经存在
		return;
	}
	FamilyDefine::FamilySimpleInfo simpleInfo;
	simpleInfo.SetFamilyID( msgCreate->nFamilyID );
	simpleInfo.SetFamilyName( msgCreate->szName );
	simpleInfo.SetProsperity( msgCreate->nProspeprity );
	simpleInfo.SetLevel( msgCreate->nFamilyLevel );
	simpleInfo.SetMemberCount( msgCreate->nMemberCount );
	m_mapFamilySimpleInfo[simpleInfo.GetFamilyID()] = simpleInfo;
}

void CSystemFamily::OnMsgTellClientProsperity(Msg *pMsg)
{
	MsgTellClientProsperity* msgPros = (MsgTellClientProsperity*)pMsg;
	m_FamilyInfo.SetProsperity( msgPros->nProsperity );
	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}
}

void CSystemFamily::OnMsgTellFamilyInfo(Msg *pMsg)
{
	MsgTellFamilyInfo* msgInfo = (MsgTellFamilyInfo*)pMsg;

	m_FamilyInfo = msgInfo->info;
	for ( int i = 0; i < int(msgInfo->nCount); i ++ )
	{
		m_FamilyMembers[msgInfo->members[i].GetID()] = msgInfo->members[i];
	}
	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}

	//初始化家族信息的时候，把自己头顶的家族信息加上
	CPlayer* playerMe = theHeroGame.GetPlayerMgr()->GetMe();
	if ( playerMe )
	{
		playerMe->SetFamilyID(msgInfo->info.GetFamilyID());
		if( msgInfo->info.GetLeaderID() == thePlayerRole.GetDBID() )
		{
			playerMe->SetFamilyPos( FamilyDefine::Position_Leader );
		}
	}
}

void CSystemFamily::OnMsgTellJoinFamilyToFamily(Msg *pMsg)
{
	MsgTellJoinFamilyToFamily* msgJoin = (MsgTellJoinFamilyToFamily*)pMsg;
	m_FamilyMembers[msgJoin->member.GetID()] = msgJoin->member;
	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}
}

void CSystemFamily::OnMsgTellLeaveFamilyToFamily(Msg *pMsg)
{
	MsgTellLeaveFamilyToFamily* msgLeave = (MsgTellLeaveFamilyToFamily*)pMsg;

	m_FamilyMembers.erase(msgLeave->member.GetID());
	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}
}

void CSystemFamily::OnMsgQuitFamilyAck(Msg *pMsg)
{
	MsgQuitFamilyAck* msgAck = (MsgQuitFamilyAck*)pMsg;
	//if ( msgAck->uchResult == MsgQuitFamilyAck::ECD_Success )
	{
		//提示退出家族  队长剔除和自己主动退出***
		char tmpStr[512] = {0};
		if ( msgAck->uchResult == FamilyDefine::Enum_Leave_Self )
		{
			MeSprintf( tmpStr, sizeof(tmpStr) - 1, theXmlString.GetString(eText_FamilySuccessedLeave), m_FamilyInfo.GetFamilyName() );
		}
		else
		{
			MeSprintf( tmpStr, sizeof(tmpStr) - 1, theXmlString.GetString(eText_FamilyBeKickout), this->GetLeaderName() );
		}

		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			tmpStr );
		

		//自己退出家族要把自己家族id信息清除
		CPlayer* playerMe = theHeroGame.GetPlayerMgr()->GetMe();
		if ( playerMe )
		{
			playerMe->SetFamilyID(0);
		}
		//退出成功，需要清除家族信息
		ClearFamilyInfo();
		if ( s_CUI_ID_FRAME_Family.IsVisable() )
		{
			s_CUI_ID_FRAME_Family.SetButtonsEnable(false);
			s_CUI_ID_FRAME_Family.ClearAllValues();
			s_CUI_ID_FRAME_Family.SetVisable(false);
		}
	}
}

void CSystemFamily::OnMsgFamilyTransferAck(Msg *pMsg)
{
	MsgFamilyTransferAck* msgAck = (MsgFamilyTransferAck*)pMsg;
	if ( msgAck->uchResult == MsgFamilyTransferAck::ECD_NoRight )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyTransferFailed) );
	}
	else if ( msgAck->uchResult == MsgFamilyTransferAck::ECD_Success )
	{
		char tmpStr[256] = {0};
		MeSprintf( tmpStr, sizeof(tmpStr), theXmlString.GetString(eText_FamilyYouAreLeader), this->GetFamilyInfo()->GetFamilyName() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			tmpStr ); 
	}
	else if ( msgAck->uchResult == MsgFamilyTransferAck::ECD_TargetNull )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyTransFailedNoPlayer) );
	}
}

void CSystemFamily::OnMsgTellFamilyTransfer(Msg *pMsg)
{
	MsgTellFamilyTransfer* msgTran = (MsgTellFamilyTransfer*)pMsg;
	if ( m_FamilyMembers.find(msgTran->nRequesterID) != m_FamilyMembers.end() 
		&& m_FamilyMembers.find(msgTran->nTargetPlayerID) != m_FamilyMembers.end() )
	{
		m_FamilyInfo.SetLeaderID( m_FamilyMembers[msgTran->nTargetPlayerID].GetID() );
		m_FamilyMembers[msgTran->nRequesterID].SetPosition(m_FamilyMembers[msgTran->nTargetPlayerID].GetPosition());
		m_FamilyMembers[msgTran->nTargetPlayerID].SetPosition( msgTran->nPosition );
	}
	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}
}

void CSystemFamily::OnMsgTellViewPositionChange(Msg *pMsg)
{
	MsgTellViewPositionChange* msgChange = (MsgTellViewPositionChange*)pMsg;
	CPlayer* player = theHeroGame.GetPlayerMgr()->FindByID( msgChange->nPlayerID );
	if ( player )
	{
		player->SetFamilyPos( msgChange->nPosition );
	}
}

void CSystemFamily::OnMsgFamilyMemberDataUpdate(Msg *pMsg)
{
	MsgFamilyMemberDataUpdate* msgUpdate = (MsgFamilyMemberDataUpdate*)pMsg;
	if ( m_FamilyMembers.find( msgUpdate->nPlayerID ) != m_FamilyMembers.end() )
	{
		if( FamilyDefine::UpdateMemberOnLine == msgUpdate->uchUpdateType )     // 更新在线
		{
			m_FamilyMembers[msgUpdate->nPlayerID].SetOnline( (bool)msgUpdate->nUpdateValue );
		}
		else if( FamilyDefine::UpdateMemberLevel == msgUpdate->uchUpdateType )          // 更新等级
		{
			m_FamilyMembers[msgUpdate->nPlayerID].SetLevel( (unsigned short)msgUpdate->nUpdateValue );
		}
		else if( FamilyDefine::UpdateMemberPosition == msgUpdate->uchUpdateType )       // 更新职位
		{
			m_FamilyMembers[msgUpdate->nPlayerID].SetPosition( (unsigned char)msgUpdate->nUpdateValue );
		}
		else if( FamilyDefine::UpdateMemberProfession == msgUpdate->uchUpdateType )    // 更新职业
		{
			m_FamilyMembers[msgUpdate->nPlayerID].SetProfession( (unsigned char)msgUpdate->nUpdateValue );
		}
		else if( FamilyDefine::UpdateMemberExp == msgUpdate->uchUpdateType )           // 更新玩家经验( 客户端不用处理 )
		{
			//do nothing...
		}
		else if( FamilyDefine::UpdateMemberDonateMoney == msgUpdate->uchUpdateType )	// 更新玩家捐金
		{
			m_FamilyMembers[msgUpdate->nPlayerID].SetDonateMoney( msgUpdate->nUpdateValue );
		}
		if ( s_CUI_ID_FRAME_Family.IsVisable() )
		{
			s_CUI_ID_FRAME_Family.RefreshValues();
		}
	}
}

void CSystemFamily::OnMsgTellLeaveFamilyToView(Msg *pMsg)
{
	MsgTellLeaveFamilyToView* msgLeave = (MsgTellLeaveFamilyToView*)pMsg;
	FamilyDefine::FamilySimpleInfo* sinfo = GetFamilySimpleInfo( msgLeave->nFamilyID );
	CPlayer* player = theHeroGame.GetPlayerMgr()->FindByID( msgLeave->header.stID );
	if ( sinfo && player )
	{
		player->SetFamilyID(0);
		char tmpStr[512] = {0};
		sprintf( tmpStr, theXmlString.GetString(eText_FamilyQuitTip), player->GetName(), sinfo->GetFamilyName() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			tmpStr );
	}
}

void CSystemFamily::OnMsgTellJoinFamilyToView(Msg *pMsg)
{
	MsgTellJoinFamilyToView* msgJoin = (MsgTellJoinFamilyToView*)pMsg;
	FamilyDefine::FamilySimpleInfo* sinfo = GetFamilySimpleInfo( msgJoin->nFamilyID );
	CPlayer* player = theHeroGame.GetPlayerMgr()->FindByID( msgJoin->header.stID );
	if ( sinfo && player )
	{
		player->SetFamilyID(msgJoin->nFamilyID);
		char tmpStr[512] = {0};
		sprintf( tmpStr, theXmlString.GetString(eText_FamilyJoinTip), player->GetName(), sinfo->GetFamilyName() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			tmpStr );
	}

}

void CSystemFamily::OnMsgTellFamilyNoticeUpdate(Msg *pMsg)
{
	MsgTellFamilyNoticeUpdate* msgUpdate = (MsgTellFamilyNoticeUpdate*)pMsg;
	m_FamilyInfo.SetFamilyNotice( msgUpdate->szNotice );
	s_CUI_ID_FRAME_Family.m_pID_TEXT_Affiche->SetText( msgUpdate->szNotice );
	//s_CUI_ID_FRAME_GUILD_FamilyMessageBox.m_pID_TEXT_Message->SetText( msgUpdate->szNotice );
}

void CSystemFamily::OnMsgFamilyNoticeAck(Msg *pMsg)
{
	MsgFamilyNoticeAck* msgAck = (MsgFamilyNoticeAck*)pMsg;
	if ( msgAck->uchResult == MsgFamilyNoticeAck::ECD_Success )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyModifyNoteSuccess) );
	}
	else if ( msgAck->uchResult == MsgFamilyNoticeAck::ECD_ErrorNotice )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyModifyNoteFailed) );
	}
}

void CSystemFamily::OnMsgFamilyDonateAck(Msg *pMsg)
{
	MsgFamilyDonateAck* msgAck = (MsgFamilyDonateAck*)pMsg;
	if( msgAck->uchResult == MsgFamilyDonateAck::ECD_Success )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyContributeSuccess) );
	}
	else if( msgAck->uchResult == MsgFamilyDonateAck::ECD_MaxFamilyMoney )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyContributeFailed) );
	}
}

void CSystemFamily::OnMsgTellFamilyDonate(Msg *pMsg)
{
	MsgTellFamilyDonate* msgDonate = (MsgTellFamilyDonate*)pMsg;
	const FamilyDefine::FamilyMember* member = GetMember( msgDonate->nMemberID );
	if ( member )
	{
		GetFamilyInfo()->SetMoney( GetFamilyInfo()->GetMoney() + msgDonate->nMoney );
		char tmpStr[256] = {0};
		int gold = 0;
		int silver = 0;
		int copper = 0;
		thePlayerRole.GetGSCFromMoney( msgDonate->nMoney, gold, silver, copper );
		sprintf_s( tmpStr, 255, theXmlString.GetString(eText_FamilyContributeTip), member->GetName(), gold, silver, copper );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			tmpStr );
	}

	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}
}

void CSystemFamily::OnMsgFamilyUpgradeAck(Msg *pMsg)
{
	MsgFamilyUpgradeAck* msgAck = (MsgFamilyUpgradeAck*)pMsg;
	if( msgAck->uchResult == MsgFamilyUpgradeAck::ECD_Success )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyUpgradeAckSuccess) );
	}
	else if ( msgAck->uchResult == MsgFamilyUpgradeAck::ECD_UpgradeError )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyUpgradeAckFailed) );
	}
}

void CSystemFamily::OnMsgTellFamilyUpgrade(Msg *pMsg)
{
	MsgTellFamilyUpgrade* msgUp = (MsgTellFamilyUpgrade*)pMsg;
	m_FamilyInfo.SetMoney( msgUp->nNewFamilyMoney );
	m_FamilyInfo.SetFamilyLevel( msgUp->nNewFamilyLevel );
	m_FamilyInfo.SetProsperity( msgUp->nNewFamilyProsperity );
	if ( s_CUI_ID_FRAME_Family.IsVisable() )
	{
		s_CUI_ID_FRAME_Family.RefreshValues();
	}

	char tmpStr[256] = {0};
	MeSprintf( tmpStr, sizeof(tmpStr) - 1, theXmlString.GetString(eText_FamilyLevelReachTo), msgUp->nNewFamilyLevel );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
		tmpStr ); 
}

void CSystemFamily::OnMsgTellFamilyDisband(Msg *pMsg)
{
	MsgTellFamilyDisband* msgDisband = (MsgTellFamilyDisband*)pMsg;
	m_mapFamilySimpleInfo.erase( msgDisband->nFamilyID );
}

void CSystemFamily::OnMsgJoinFamilyAck(Msg *pMsg)
{
	MsgJoinFamilyAck* msgAck = (MsgJoinFamilyAck*)pMsg;
	if( msgAck->uchResult == MsgJoinFamilyAck::ECD_JoinSuccess )
	{
		char tmpStr[512] = {0};
		MeSprintf( tmpStr, sizeof(tmpStr) - 1, theXmlString.GetString(eText_FamilyRequestSuccess), m_FamilyInfo.GetFamilyName() );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			tmpStr );
	}
	else if ( msgAck->uchResult == MsgJoinFamilyAck::ECD_LevelLess )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyLevelNotEnough) );
	}
	else if ( msgAck->uchResult == MsgJoinFamilyAck::ECD_TimeLimit )
	{
		if ( IsMeFamilyLeader( thePlayerRole.GetDBID() ) )
		{
			//如果是族长接到这个消息，说明是邀请刚推出家族的玩家失败
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyRefuseInviteIn24) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
				theXmlString.GetString(eText_FamilyRefuseJionIn24) );
		}
		
	}
	else if ( msgAck->uchResult == MsgJoinFamilyAck::ECD_GuildNotExist )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyNoSuchFamily) );
	}
	else if ( msgAck->uchResult == MsgJoinFamilyAck::ECD_MemberFull )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyFull) );
	}
	else if ( msgAck->uchResult == MsgJoinFamilyAck::ECD_NotAgree )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyRefuseJion) );
	}
	else if ( msgAck->uchResult == MsgJoinFamilyAck::ECD_NotOnLine )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyManagerOffline) );
	}

}

void CSystemFamily::OnMsgTellClientCanInvite(Msg *pMsg)
{
	MsgTellClientCanInvite* msgInvite = (MsgTellClientCanInvite*)pMsg;
	char szInfo[128] = {0};
	if ( msgInvite->opType == MsgTellClientCanInvite::Guild_Invite )
	{
		MeSprintf( szInfo, sizeof(szInfo)-1, theXmlString.GetString(eText_GangPlayerReach10),msgInvite->szPlayerName);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Server_Others_Success, szInfo );
		return;
	}
	else if (msgInvite->opType == MsgTellClientCanInvite::Family_Invite)
	{
		MeSprintf( szInfo, sizeof(szInfo)-1, "%s ~%s_ %s", 
			theXmlString.GetString(eText_FamilyPlayer), msgInvite->szPlayerName,
			theXmlString.GetString(eText_FamilyPlayerReach10)/*theXmlString.GetString(eUI_SendTeam)*/);
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx, szInfo );
		return ;
	}
}

FamilyDefine::FamilySimpleInfo* CSystemFamily::GetFamilySimpleInfo( unsigned int familyID )
{
	FamilySimpleInfoSetIt_t it = m_mapFamilySimpleInfo.find( familyID );
	if ( it == m_mapFamilySimpleInfo.end() )
	{
		return NULL;
	}
	else
	{
		return &(it->second);
	}
}

void CSystemFamily::GetAllInfo( std::vector<FamilyDefine::FamilySimpleInfo>& infoList )
{
	for ( FamilySimpleInfoSetIt_t it = m_mapFamilySimpleInfo.begin(); it != m_mapFamilySimpleInfo.end(); it ++ )
	{
		infoList.push_back(it->second);
	}
}

const char* CSystemFamily::GetLeaderName()
{
	FamilyMemberSetIt_t it = m_FamilyMembers.find(m_FamilyInfo.GetLeaderID());
	if ( it != m_FamilyMembers.end() )
	{
		return it->second.GetName();
	}
	return NULL;
}

void CSystemFamily::ClearFamilyInfo()
{
	m_FamilyInfo = FamilyDefine::FamilyInfo();
	m_FamilyMembers.clear();
}

bool CSystemFamily::IsMeHaveFamily()
{
	if ( m_FamilyInfo.GetFamilyID() >= FamilyDefine::FirstFamilyID )
	{
		return true;
	}
	return false;
}

bool CSystemFamily::IsMeFamilyLeader( unsigned int dbid )
{
	if ( IsMeHaveFamily() )
	{
		if ( dbid == m_FamilyInfo.GetLeaderID() )
		{
			return true;
		}
	}
	return false;
}

void CSystemFamily::GetAllMemberInfo( std::vector<FamilyDefine::FamilyMember>& members )
{
	for ( FamilyMemberSetIt_t it = m_FamilyMembers.begin(); it != m_FamilyMembers.end(); it ++ )
	{
		members.push_back(it->second);
	}
}

const FamilyDefine::FamilyMember* CSystemFamily::GetMember( unsigned int dbid )
{
	FamilyMemberSetIt_t it = m_FamilyMembers.find( dbid );
	if ( it != m_FamilyMembers.end() )
	{
		return &it->second;
	}

	return NULL;
}

unsigned int CSystemFamily::GetMemeberCount()
{
	return (unsigned int)m_FamilyMembers.size();
}