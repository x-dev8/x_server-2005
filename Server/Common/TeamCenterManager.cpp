#include "TeamManager.h"
#include "CenterGameMessage.h"
#include "..\CenterServer\Source\GameServerManager.h"
#include "..\CenterServer\Source\ClientPeerManager.h"
#include "RelationManager.h"
#include "LogFileObjectNameEx.h"
#include "GameTime.h"

// 判断能否邀请队伍
template<>
int CenterTeam::IsCanInviteJoinInTeam( unsigned int dwHeaderID, unsigned int dwNewAddID )
{
    if ( !IsTeamHeader( dwHeaderID ) )      
    { return TeamDefine::NotTeamHeader; }       // 自己不是队长

    if ( IsTeamFull() )                         // 队伍满了
    { return TeamDefine::TeamFull; }

    if ( IsInTeam( dwNewAddID ) )
    { return TeamDefine::AlreadyInTeam; }       // 已经在队伍中

    return TeamDefine::CanJoinTeam;
}

// 判断能否申请加入队伍
template<>
int CenterTeam::IsCanRequestJoinInTeam( unsigned int dwNewAddID )
{
    if ( IsInTeam( dwNewAddID ) )
    { return TeamDefine::AlreadyInTeam; }

    if ( IsTeamFull() )
    { return TeamDefine::TeamFull; }

    return TeamDefine::CanJoinTeam;
}

template<>
void CenterTeam::ProcessManipleInfo( CenterTeamMember& xMember )
{
    for ( ManipleCountMapIter iter = m_mapManipleCount.begin(); iter != m_mapManipleCount.end(); ++iter )
    {
        if ( iter->second < TeamMaxManipleMember )
        {
            xMember.SetManipleID( iter->first );
            if ( iter->second == 0 )    // 小队的第一个
            {
                xMember.SetManipleHeader( true );
            }
            break;
        }
    }
}

template<>
void CenterTeam::SendMessageToTeamClient( Msg* pMessage, unsigned int nExceptID, unsigned char chOperate )
{
    switch ( chOperate )
    {
    case TeamDefine::SendToAllGame:     // 发送给所有服务器
        {
            theGameServerManager.SendMessageToGameServers( pMessage, nExceptID );
        }
        break;
    case TeamDefine::SendToSomeGame:        // 发送给某些指定的服务器
        {
            std::vector< long > vecHasSendGameServerPeer( 0 );
            for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
            {
                if ( iter->GetTimeOut() != 0 )
                { continue; }   // 不在线

                ClientPeer* pTeamClient = GetMemberPlayer( iter->GetID() );
                if( pTeamClient == NULL ) 
                { continue; }

                GameServerPeer* pDestGameServer = theGameServerManager.GetGameServerPeer( pTeamClient->GetServerInfo().nServerId );
                if( pDestGameServer == NULL )
                { continue; }

                if ( nExceptID == pDestGameServer->GetId() )
                { continue; }       //  指定服的不发
                
                std::vector< long >::iterator senditer = find( vecHasSendGameServerPeer.begin(), vecHasSendGameServerPeer.end(), pDestGameServer->GetId() );
                if ( senditer != vecHasSendGameServerPeer.end() ) 
                { continue; }	    // 这个服务器已经发送过了		

                vecHasSendGameServerPeer.push_back( pDestGameServer->GetId() );   //添加进列表
                pDestGameServer->Send( pMessage );
            }
        }
        break;
    default:
        break;
    }
}

template<>
void CenterTeam::ProcessAddTeamMember( CenterTeamMember& xMember, TeamDefine::TeamInvite* pRecord )
{
    if ( pRecord == NULL )
    { return; }

    // 通知每个服务器添加新成员
    CS2GSAckJoinTeam xJoinTeam;
    strncpy_s( xJoinTeam.szName, sizeof( xJoinTeam.szName ), xMember.GetName(), sizeof( xJoinTeam.szName ) - 1 );
    xJoinTeam.dwTeamSessionID   = GetID();
    xJoinTeam.dwDataBaseID      = xMember.GetID();
    xJoinTeam.nHp               = pRecord->nHp;
    xJoinTeam.nHpMax            = pRecord->nHpMax;
    xJoinTeam.nMp               = pRecord->nMp;
    xJoinTeam.nMpMax            = pRecord->nMpMax;
    xJoinTeam.stLevel           = pRecord->stLevel;
    xJoinTeam.chProfession      = pRecord->chProfession;
    xJoinTeam.chSex             = pRecord->chSex;
    xJoinTeam.nFaceId           = pRecord->nFaceId;
    xJoinTeam.nHairId           = pRecord->nHairId;
    xJoinTeam.nHeadPicId        = pRecord->nHeadPicId;
    xJoinTeam.stManipleID       = xMember.GetManipleID();
    xJoinTeam.bIsTeamHeader     = IsTeamHeader( xMember.GetID() );
    xJoinTeam.bIsManipleHeader  = xMember.GetManipleHeader();
    xJoinTeam.chAssignModeType  = GetTeamAssignModeType();
    xJoinTeam.chAssignItemLevel = GetTeamAssignItemLevel();

    SendMessageToTeamClient( &xJoinTeam, TeamDefine::ErrorID, TeamDefine::SendToAllGame );
}

template<>
void CenterTeam::ProcessRemoveTeamMember( unsigned int dwMemberID )
{
    GS2CSPlayerRemoveFromTeamAck xMsg;
    xMsg.dwDataBaseId = dwMemberID;
    xMsg.dwSessionId  = GetID();
    xMsg.bDisband     = ( TeamMemberCount() <= 1 );

    SendMessageToTeamClient( &xMsg, TeamDefine::ErrorID, TeamDefine::SendToAllGame );     
}

template<>
void CenterTeam::ChangeTeamHeaderToOnLineMember()
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetTimeOut() == 0 )
        {
            if ( UpgradeTeamHeader( iter->GetID() ) )
            { return; }
        }
    }
}

template<>
bool CenterTeam::ProcessUpgradeTeamHeader( CenterTeamMember* pTeamMember )
{
    if ( pTeamMember == NULL )
    { return false; }

    //发消息给所有GameServer,队长变更了
    GS2CSPlayerUpgradeTeamAck xAck;
    xAck.dwDataBaseId = pTeamMember->GetID();
    xAck.dwSessionId  = GetID();
    HelperFunc::SafeNCpy( xAck.szName, pTeamMember->GetName(), sizeof( xAck.szName ) );
    SendMessageToTeamClient( &xAck, TeamDefine::ErrorID, TeamDefine::SendToAllGame );

    return true;
}

template<>
ClientPeer* CenterTeam::GetMemberPlayer( unsigned int dwMemberID, bool bIncludeNotInStage  )
{
    return ClientPeerManager::GetInstance().GetClientPeerByDBId( dwMemberID );
}

template<>      // 返回是否要删除队伍
int CenterTeam::RunTeamUpdate( unsigned char chOperate )
{
    if ( TeamMemberCount() < 1 )
    {  return TeamDefine::DeleteTeam; }      // 队伍人数小于2 删除队伍

    unsigned int dwNowTime = HQ_TimeGetTime();
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetTimeOut() != 0 && GameTime::IsPassCurrentTime( iter->GetTimeOut(), TeamDefine::MaxTimeOut ) )       // 已经超过队伍保留时间
        {
            return RemoveTeamMember( iter->GetID(), theCenterTeamManager );     
        }
    }

    return TeamDefine::DoNothing;
}

template<>
void CenterTeam::MemberOutLine( CenterTeamMember* pTeamMember )
{
    if ( pTeamMember == NULL )
    { return; }

    pTeamMember->SetTimeOut( HQ_TimeGetTime() );

    CS2GSMsgTeamOutLine xOutLine;
    xOutLine.dwTeamSessionID = GetID();
    xOutLine.dwID            = pTeamMember->GetID();
    SendMessageToTeamClient( &xOutLine, TeamDefine::ErrorID, TeamDefine::SendToAllGame );

    // 如果是队长掉线, 设置新的队长
    if ( IsTeamHeader( pTeamMember->GetID() ) )
    {
        ChangeTeamHeaderToOnLineMember();
    }
}

template<>
void CenterTeam::MemberOnLine( CenterTeamMember* pTeamMember  )
{
    if ( pTeamMember == NULL )
    { return; }

    pTeamMember->SetTimeOut( 0 );

    // 先通知各服务器, 该队员上线了
    GS2CSTeamOnLine xOnLine;
    xOnLine.dwID = pTeamMember->GetID();
    SendMessageToTeamClient( &xOnLine, TeamDefine::ErrorID, TeamDefine::SendToAllGame );

    // 如果队伍中队员全掉了,这时候第一个人进入游戏,让他当队长
    CenterTeamMember* pTeamHeader = GetTeamMemberByID( GetTeamHeaderID() );
    if ( pTeamHeader == NULL || pTeamHeader->GetTimeOut() != 0 )
    {
        UpgradeTeamHeader( pTeamMember->GetID() );
    }
}

template<>
void CenterTeam::UpdateTeamBuffer( unsigned int dwExceptMemberID, bool bLeaveTeam )
{

}

template<>
void CenterTeam::UpdateTeamBuffer( CenterTeamMember* pTeamMember, unsigned char uchCount, unsigned int dwExceptMemberID )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void CenterTeamManager::SendCreateTeamMessage( CenterTeam* pTeam )
{
    if ( pTeam == NULL )
    { return; }

    // 给所有服务器发送消息
    CS2GSCreateTeam xCreate;
    xCreate.dwTeamSessionID = pTeam->GetID();
    xCreate.AssignMode      = pTeam->GetTeamAssignModeType();
    xCreate.AssignItemLevel = pTeam->GetTeamAssignItemLevel();
    pTeam->SendMessageToTeamClient( &xCreate, TeamDefine::ErrorID, TeamDefine::SendToAllGame );
}

template<>
void CenterTeamManager::RunInviteRecordUpdate( unsigned int dwCurrentTime ) 
{
    for ( InviteRecordMapIter iter = m_mapInviteRecord.begin(); iter != m_mapInviteRecord.end(); )
    {
        for ( InviteInfoMapIter miter = iter->second.begin(); miter != iter->second.end(); )
        {
            if ( dwCurrentTime - miter->second.dwTimeOut > TeamDefine::TeamInvite::ECD_TimeOut )
            {
                miter = iter->second.erase( miter );
            }
            else
            {
                ++miter;
            }
        }

        if ( iter->second.empty() )
        {
            iter = m_mapInviteRecord.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

template<>
void CenterTeam::UpdateTeamTransnationalStates(bool IsAdd,unsigned int ID)
{
	//更新队伍所有玩家的的国家 判断是否修改队伍的状态 m_MapCountry  map<unsigned int,unsigned char>
	if(IsAdd)
	{
		//添加玩家
		//以前所有玩家的国家完全相同 判断目前加进来的玩家的国家
		ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId(ID);
		if(!pClientPeer) return;
		unsigned char CountryID = pClientPeer->GetCountry();//获取国家ID
		if(m_MapCountry.count(ID) == 0)
			m_MapCountry.insert(map<unsigned int,unsigned char>::value_type(ID,CountryID));
		if(m_IsTransnationalTeam)
			return;
		if(m_MapCountry.size() != m_listTeamMember.size()) 
			return;
		map<unsigned int,unsigned char>::iterator Iter = m_MapCountry.begin();
		for(;Iter != m_MapCountry.end();++Iter)
		{
			if(Iter->second != CountryID)
			{
				m_IsTransnationalTeam = true;
				//因为玩家的加入 导致队伍的属性发生变化 需要发送到所有的GameServer去通知下
				CS2GSTeamStateChange msg;
				msg.TeamID = GetID();
				msg.Result = m_IsTransnationalTeam;
				theGameServerManager.SendMessageToGameServers(&msg);
				return;
			}
		}	
		m_IsTransnationalTeam = false;
		return;
	}		
	else
	{
		//有玩家离开
		if(m_MapCountry.count(ID) == 1)
		{
			m_MapCountry.erase(ID);
		}
		if(!m_IsTransnationalTeam)
			return;
		//以前的玩家的国家ID不同 有玩家离开了 我们判断目前的国家ID是否相同 移除掉的玩家有可能不在线
		map<unsigned int,unsigned char>::iterator Iter = m_MapCountry.begin();
		unsigned char LogID = m_MapCountry.begin()->second;
		for(;Iter != m_MapCountry.end();++Iter)
		{
			//判断当前Map里面的值是否全部相同呢
			if(LogID != Iter->second)
			{
				m_IsTransnationalTeam = true;
				return;
			}
		}
		m_IsTransnationalTeam = false;
		//因为玩家的离开 导致队伍的属性发生变化 需要发送到所有的GameServer去通知下
		CS2GSTeamStateChange msg;
		msg.TeamID = GetID();
		msg.Result = m_IsTransnationalTeam;
		theGameServerManager.SendMessageToGameServers(&msg);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////