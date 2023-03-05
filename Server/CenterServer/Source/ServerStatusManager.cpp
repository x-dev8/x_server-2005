#include "ServerStatusManager.h"
//#include "MessageDefine.h"
#include "CenterServer.h"
#include "GameServerManager.h"
#include "PlatformMessageDefine.h"
#include "GameTime.h"
#include "LogFileObjectNameEx.h"
#include "RunStatus.h"

void ServerStatusManager::RegisterServer( const ServerData& xData )
{
    switch ( xData.GetNodeType() )
    {
    case Node_Center:
        m_xServerData.AddChildData( xData );
		// center自己版本号不需要验证
		theRunStatus.SetLoadSuccess(RunStatusDefine::CheckVersionSuccess);
        break;
    case Node_Database:
    case Node_Game:
    case Node_Character:
    case Node_Gate:
        {
            ServerData* pParentData = GetServerData( &m_xServerData, xData.GetParentNodeType(), xData.GetParentID() );
            if ( pParentData == NULL )
            { return; }

            ServerData* pData = GetServerData( pParentData, xData.GetNodeType(), xData.GetID() );
            if ( pData != NULL )
            { return; }     // 已经注册过了

            pParentData->AddChildData( xData );
        }
        break;
    }
}

ServerData* ServerStatusManager::GetServerData( ServerDataDefine::NodeType nParentType, unsigned int nParentID, ServerDataDefine::NodeType nType, unsigned int nID )
{
    ServerData* pParentData = GetServerData( &m_xServerData, nParentType, nParentID );
    if ( pParentData == NULL )
    { return NULL; }
    
    return GetServerData( pParentData, nType, nID );
}

ServerData* ServerStatusManager::GetServerData( ServerData* pParentData, NodeType nType, unsigned int nID )
{
    int nIndex = 0;
    ServerData* pServerData = NULL ;
    while( ( pServerData = pParentData->GetChildData( nIndex++ ) ) != NULL )
    {
        if ( pServerData->GetNodeType() == nType && pServerData->GetID() == nID )
        { return pServerData; }

        ServerData* pChildData = GetServerData( pServerData, nType, nID );
        if ( pChildData != NULL )
        { return pChildData; }
    }

    return NULL;
}

void ServerStatusManager::RunUpdate( unsigned int nCurrentTime )
{
    switch ( GetStatus() )
    {
    case ServerDataDefine::DoNothing:           // 什么也不干
        break;
    case ServerDataDefine::ReqServerStatus:       // 发送请求给服务器,请求状态
        {
            SendMessageToServers( nCurrentTime );
        }
        break;
    case ServerDataDefine::WaitForAck:          // 等待服务器回应
        {
            WaitForServerAck( nCurrentTime );
        }
        break;
    case ServerDataDefine::SendToPlat:          // 回复平台各服务器状态
        {
            SendMessageToPlat();
        }
        break;
    default:
        break;
    }
}

void ServerStatusManager::SendMessageToServers( unsigned int nCurrentTime )
{
    MsgServerStatusReq xReq;

    theCenterServer.SendMessageToDb( &xReq );                   // 发送给DB
    theGameServerManager.SendMessageToGameServers( &xReq );     // 发送给所有服务器
    theGameServerManager.SendMessageToCharacterServer( &xReq ); // 发送给角色服务器

    // 设置所有的服务器状态为 Status_Bad 等待回应
    SetAllServerStatus( &m_xServerData, ServerDataDefine::Status_Bad );
    
    // 设置时间和状态
    m_nSendReqTime = nCurrentTime;
    SetStatus( ServerDataDefine::WaitForAck );
}

void ServerStatusManager::WaitForServerAck( unsigned int nCurrentTime )
{
    if ( !GameTime::IsPassCurrentTime( nCurrentTime, m_nSendReqTime, ServerDataDefine::WaitTime ) )
    { return; }

    SetStatus( ServerDataDefine::SendToPlat );
}

// #include <iostream>
void ServerStatusManager::SendMessageToPlat()
{
    // 判断信息, 把有问题的服务器发送给平台
    MsgPFServerStatusAck xAck;
    GetAllServerStatus( &m_xServerData, &xAck );

    theCenterServer.SendMessageToPlatform( m_nClientID, &xAck );

    //for ( int i = 0; i < xAck.nCount; ++i )
    //{
    //    std::cout << xAck.xStatus[i].szName << " : " << static_cast< int >( xAck.xStatus[i].uchStatus ) << "\n";
    //}
    //std::cout << std::endl;

    SetStatus( ServerDataDefine::DoNothing );
}

void ServerStatusManager::SetAllServerStatus( ServerData* pParentData, Status nStatus )
{
    int nIndex = 0;
    ServerData* pServerData = NULL;
    while ( ( pServerData = pParentData->GetChildData( nIndex++ ) ) != NULL )
    {
        if ( pServerData->GetNodeType() != ServerDataDefine::Node_Root && pServerData->GetNodeType() != ServerDataDefine::Node_Center )
        {
            pServerData->SetStatus( nStatus );
        }

        SetAllServerStatus( pServerData, nStatus );
    }
}

void ServerStatusManager::GetAllServerStatus( ServerData* pParentData, MsgPFServerStatusAck* pMessage )
{
    int nIndex = 0;
    ServerData* pServerData = NULL;
    while ( ( pServerData = pParentData->GetChildData( nIndex++ ) ) != NULL )
    {
        if ( pServerData->GetStatus() != ServerDataDefine::Status_Fine )
        {
            pMessage->AddServerStatus( pServerData->GetName(), pServerData->GetStatus() );
        }

        GetAllServerStatus( pServerData, pMessage );
    }
}


void ServerStatusManager::CheckVersion( ServerData& xServerData )
{
    switch ( xServerData.GetNodeType() )
    {
    case Node_Game:
        {
            ServerData* pDatabase = GetServerData( Node_Center, 0, Node_Database, 0 );
            if ( pDatabase == NULL )
            { return; }

            CheckGameVersion( xServerData, pDatabase->GetVersion() );
        }
        break;
    case Node_Database:
        {
            CheckDatabaseVersion( &m_xServerData, xServerData.GetVersion() );
        }
        break;
    }
}

void ServerStatusManager::CheckGameVersion( ServerData& xServerData, unsigned short ustDatabaseVersion )
{
    if ( ustDatabaseVersion != xServerData.GetVersion() )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Database版本号:[%d]与GameServer版本号:[%d]不相同, %s 将不提供服务!", ustDatabaseVersion, xServerData.GetVersion(), xServerData.GetName() );
        return;
    }

    // 版本验证成功 发消息给GameServer
    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( xServerData.GetID() );
    if ( pGameServer != NULL )
    { 
        MsgServerVersionCheckAck xAck;
        pGameServer->Send( &xAck );
    }
}

void ServerStatusManager::CheckDatabaseVersion( ServerData* pParentData, unsigned short ustDatabaseVersion )
{
    int nIndex = 0;
    ServerData* pServerData = NULL;
    while ( ( pServerData = pParentData->GetChildData( nIndex++ ) ) != NULL )
    {
        if ( pServerData->GetNodeType() == Node_Game )
        {
            CheckGameVersion( *pServerData, ustDatabaseVersion );
        }

        CheckDatabaseVersion( pServerData, ustDatabaseVersion );
    }
}