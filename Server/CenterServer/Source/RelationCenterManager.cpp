#include "RelationManager.h"
#include "GameServerManager.h"
#include "XmlStringLanguage.h"
#include "RelationMessage.h"
#include "MySqlCommunication.h"

template<>  // 发送所有关系属性, 关系信息到服务器
void RelationManager< CenterRelation >::SendRelationList2Client( unsigned int nAppointID )
{
    if ( !GetLoadSuccess() )
    { return; }

    for ( RelationMapIter iter = m_mapRelations.begin(); iter != m_mapRelations.end(); ++iter )
    {
		// 如果 GS宕了 重新注册的时候把 应该发送的发送过去
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

    // 处理加载数据
    ProcessLoadRelationData( dwCurrentTime );

    // 更新邀请记录
    UpdateRelationInvite( dwCurrentTime );
}

template<>
void RelationManager< CenterRelation >::ProcessLoadRelationData( unsigned int nCurrentTime )
{
    StartLoadTimer();   // 请求加载定时器
    if ( !m_xLoadTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // 发送请求所有关系信息
    CS2DBRelationListReq xRelationReq;
    theMysqlCommunication.PushReqMessage( &xRelationReq, 0 );
}
