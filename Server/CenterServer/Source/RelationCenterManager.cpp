#include "RelationManager.h"
#include "GameServerManager.h"
#include "XmlStringLanguage.h"
#include "RelationMessage.h"
#include "MySqlCommunication.h"

template<>  // �������й�ϵ����, ��ϵ��Ϣ��������
void RelationManager< CenterRelation >::SendRelationList2Client( unsigned int nAppointID )
{
    if ( !GetLoadSuccess() )
    { return; }

    for ( RelationMapIter iter = m_mapRelations.begin(); iter != m_mapRelations.end(); ++iter )
    {
		// ��� GS��� ����ע���ʱ��� Ӧ�÷��͵ķ��͹�ȥ
		if ( HaveSendedRelationId( iter->second->GetID() ))
		{
			iter->second->SendRelationListToClient( nAppointID );
		}
    }

    SendRelationListSuccess( nAppointID );
}

template<>
void RelationManager< CenterRelation >::SendRelationListSuccess( unsigned int nID )
{
    CS2GSRelationDataSendSuccess xSuccess;

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nID );
    if ( pGameServer != NULL )
    {
        pGameServer->Send( &xSuccess );
    }
    else
    {
        theGameServerManager.SendMessageToGameServers( &xSuccess );
    }
}

template<>
void RelationManager< CenterRelation >::RunUpdate( unsigned int dwCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( dwCurrentTime ) )
    { return; }

    // �����������
    ProcessLoadRelationData( dwCurrentTime );

    // ���������¼
    UpdateRelationInvite( dwCurrentTime );
}

template<>
void RelationManager< CenterRelation >::ProcessLoadRelationData( unsigned int nCurrentTime )
{
    StartLoadTimer();   // ������ض�ʱ��
    if ( !m_xLoadTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // �����������й�ϵ��Ϣ
    CS2DBRelationListReq xRelationReq;
    theMysqlCommunication.PushReqMessage( &xRelationReq, 0 );
}
