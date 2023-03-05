#include "TeamManager.h"
#include "CenterGameMessage.h"
#include "..\CenterServer\Source\GameServerManager.h"
#include "..\CenterServer\Source\ClientPeerManager.h"
#include "RelationManager.h"
#include "LogFileObjectNameEx.h"
#include "GameTime.h"

// �ж��ܷ��������
template<>
int CenterTeam::IsCanInviteJoinInTeam( unsigned int dwHeaderID, unsigned int dwNewAddID )
{
    if ( !IsTeamHeader( dwHeaderID ) )      
    { return TeamDefine::NotTeamHeader; }       // �Լ����Ƕӳ�

    if ( IsTeamFull() )                         // ��������
    { return TeamDefine::TeamFull; }

    if ( IsInTeam( dwNewAddID ) )
    { return TeamDefine::AlreadyInTeam; }       // �Ѿ��ڶ�����

    return TeamDefine::CanJoinTeam;
}

// �ж��ܷ�����������
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
            if ( iter->second == 0 )    // С�ӵĵ�һ��
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
    case TeamDefine::SendToAllGame:     // ���͸����з�����
        {
            theGameServerManager.SendMessageToGameServers( pMessage, nExceptID );
        }
        break;
    case TeamDefine::SendToSomeGame:        // ���͸�ĳЩָ���ķ�����
        {
            std::vector< long > vecHasSendGameServerPeer( 0 );
            for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
            {
                if ( iter->GetTimeOut() != 0 )
                { continue; }   // ������

                ClientPeer* pTeamClient = GetMemberPlayer( iter->GetID() );
                if( pTeamClient == NULL ) 
                { continue; }

                GameServerPeer* pDestGameServer = theGameServerManager.GetGameServerPeer( pTeamClient->GetServerInfo().nServerId );
                if( pDestGameServer == NULL )
                { continue; }

                if ( nExceptID == pDestGameServer->GetId() )
                { continue; }       //  ָ�����Ĳ���
                
                std::vector< long >::iterator senditer = find( vecHasSendGameServerPeer.begin(), vecHasSendGameServerPeer.end(), pDestGameServer->GetId() );
                if ( senditer != vecHasSendGameServerPeer.end() ) 
                { continue; }	    // ����������Ѿ����͹���		

                vecHasSendGameServerPeer.push_back( pDestGameServer->GetId() );   //��ӽ��б�
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

    // ֪ͨÿ������������³�Ա
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

    //����Ϣ������GameServer,�ӳ������
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

template<>      // �����Ƿ�Ҫɾ������
int CenterTeam::RunTeamUpdate( unsigned char chOperate )
{
    if ( TeamMemberCount() < 1 )
    {  return TeamDefine::DeleteTeam; }      // ��������С��2 ɾ������

    unsigned int dwNowTime = HQ_TimeGetTime();
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetTimeOut() != 0 && GameTime::IsPassCurrentTime( iter->GetTimeOut(), TeamDefine::MaxTimeOut ) )       // �Ѿ��������鱣��ʱ��
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

    // ����Ƕӳ�����, �����µĶӳ�
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

    // ��֪ͨ��������, �ö�Ա������
    GS2CSTeamOnLine xOnLine;
    xOnLine.dwID = pTeamMember->GetID();
    SendMessageToTeamClient( &xOnLine, TeamDefine::ErrorID, TeamDefine::SendToAllGame );

    // ��������ж�Աȫ����,��ʱ���һ���˽�����Ϸ,�������ӳ�
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

    // �����з�����������Ϣ
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
	//���¶���������ҵĵĹ��� �ж��Ƿ��޸Ķ����״̬ m_MapCountry  map<unsigned int,unsigned char>
	if(IsAdd)
	{
		//������
		//��ǰ������ҵĹ�����ȫ��ͬ �ж�Ŀǰ�ӽ�������ҵĹ���
		ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId(ID);
		if(!pClientPeer) return;
		unsigned char CountryID = pClientPeer->GetCountry();//��ȡ����ID
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
				//��Ϊ��ҵļ��� ���¶�������Է����仯 ��Ҫ���͵����е�GameServerȥ֪ͨ��
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
		//������뿪
		if(m_MapCountry.count(ID) == 1)
		{
			m_MapCountry.erase(ID);
		}
		if(!m_IsTransnationalTeam)
			return;
		//��ǰ����ҵĹ���ID��ͬ ������뿪�� �����ж�Ŀǰ�Ĺ���ID�Ƿ���ͬ �Ƴ���������п��ܲ�����
		map<unsigned int,unsigned char>::iterator Iter = m_MapCountry.begin();
		unsigned char LogID = m_MapCountry.begin()->second;
		for(;Iter != m_MapCountry.end();++Iter)
		{
			//�жϵ�ǰMap�����ֵ�Ƿ�ȫ����ͬ��
			if(LogID != Iter->second)
			{
				m_IsTransnationalTeam = true;
				return;
			}
		}
		m_IsTransnationalTeam = false;
		//��Ϊ��ҵ��뿪 ���¶�������Է����仯 ��Ҫ���͵����е�GameServerȥ֪ͨ��
		CS2GSTeamStateChange msg;
		msg.TeamID = GetID();
		msg.Result = m_IsTransnationalTeam;
		theGameServerManager.SendMessageToGameServers(&msg);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////