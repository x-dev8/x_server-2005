#include "GameServerManager.h"
#include "GlobalDef.h"
#include "ResourcePath.h"
#include "Config.h"
#include "CenterServer.h"
#include "LogEventService.h"

GameServerManager& GameServerManager::GetInstance()
{
    static GameServerManager instance;
    return instance;
}

GameServerManager::GameServerManager()
{
    m_bExtendBornMapOpen = true;
	m_QueueOpen = false;
}

void GameServerManager::_Release()
{
    ItrGameServerPeerContainer it = _GameServerPeers.begin();
    for ( ; it!=_GameServerPeers.end();++it)
    {
        GameServerPeer* pGameServer = it->second;
        if ( !pGameServer)
            continue;

        pGameServer->Release();
    }
    _GameServerPeers.clear();
}

long GameServerManager::Init()
{
    _Release();

    long nResult = ER_Success;
    return nResult;
}

void GameServerManager::UnInit()
{
    _Release();
}

bool GameServerManager::AddGameServerPeer( GameServerPeer* pPeer )
{
    CHECK_RETURN( pPeer==NULL, ER_NullPointer );
    return _GameServerPeers.insert( GameServerPeerContainer::value_type(pPeer->GetId(), pPeer) ).second;
}

GameServerPeer* GameServerManager::GetGameServerPeer( unsigned long Id )
{
    if ( InvalidLogicNumber == Id )
    { return NULL; }

    ItrGameServerPeerContainer it = _GameServerPeers.find( Id );
    if ( it != _GameServerPeers.end() )
    { return it->second; }

    return NULL;
}

void GameServerManager::RemoveGameServerPeer( unsigned long Id )
{ 
    ItrGameServerPeerContainer it = _GameServerPeers.find( Id );
    if ( it != _GameServerPeers.end())
    {
        GameServerPeer* pGameServerPeer = it->second;

        if ( pGameServerPeer )
        {
            AccountIdContainer    Clients = pGameServerPeer->GetAllClient();
            ItrAccountIdContainer it    = Clients.begin();
            ItrAccountIdContainer itEnd = Clients.end();
            for (; it!=itEnd; ++it )
            {
                ClientPeer* pClientPeer = theClientPeerManager.GetClientPeer( *it );
                if ( pClientPeer )
                { 
					theCenterServer.NotifyGLSPlayerExit( pClientPeer->GetAccountId(), pClientPeer->GetLoginInfo().szAccount ); 
				}

                theClientPeerManager.RemoveClientPeer( *it );
            }
            pGameServerPeer->Release();

			CheckQueue(theClientPeerManager.ClientPeerSize(),true);
        }

        _GameServerPeers.erase( it );
    }
}

void GameServerManager::GetGameServerNames( StringsType& strNames )
{
    ItrGameServerPeerContainer it = _GameServerPeers.begin();
    for ( ; it!=_GameServerPeers.end(); ++it)
    {
        GameServerPeer* p = it->second;
        if ( p )
            strNames.push_back( p->GetName() );
    }
}

GameServerPeer* GameServerManager::GetLowestBurthenGameServerPeer()
{
    ItrGameServerPeerContainer it = _GameServerPeers.begin();

    GameServerPeer* pFindGameServerPeer = NULL;
    
    unsigned long nLessPlayerCount = 0xffffffff;

    for ( ; it!=_GameServerPeers.end();++it)
    {
        GameServerPeer* pGameServerPeer = it->second;

        if ( !pGameServerPeer)
            continue;

        unsigned long nPlayerCount = pGameServerPeer->GetBurthen().nCurrentPlayerCount;
        if ( nPlayerCount < nLessPlayerCount)
        {
            nLessPlayerCount = nPlayerCount;
            pFindGameServerPeer = pGameServerPeer;
        }
    }

    return pFindGameServerPeer;
}

GameServerPeer* GameServerManager::GetCharacterServerPeer()
{
    ItrGameServerPeerContainer it = _GameServerPeers.find( CHARACTERSERVERID );
    if ( it != _GameServerPeers.end())
    {  return it->second;}

    return NULL;
}

//GameServerPeer* GameServerManager::GetCenterLoginServerPeer()
//{
//	ItrGameServerPeerContainer it = _GameServerPeers.find( CENTERLOGINSERVERID );
//	if ( it != _GameServerPeers.end())
//	{  return it->second;}
//
//	return NULL;
//}

long GameServerManager::GetGameServerPeerList( unsigned long nMap, bool bIsRun, GameServerPeers& output )
{
    output.clear();

    ItrGameServerPeerContainer it = _GameServerPeers.begin();
    for ( ; it!=_GameServerPeers.end(); ++it)
    {
        GameServerPeer* pGameServer = it->second;
        if ( !pGameServer)
        { continue; }

        if ( pGameServer->IsHaveStageInfo( nMap, bIsRun ) )
        { output.push_back( pGameServer ); }
    }
    
    return ER_Success;
}

long GameServerManager::GetAllMapInfo( MapInfoContainer& mapInfos )
{
    mapInfos.clear();
    
    ItrGameServerPeerContainer it = _GameServerPeers.begin();
    for ( ; it!=_GameServerPeers.end(); ++it)
    {
        GameServerPeer* pGameServer = it->second;
        if ( pGameServer == NULL )
        { continue; }

        MapIdContainer mapIds;
        pGameServer->GetAllStageId( mapIds );
        for ( MapIdContainer::iterator itv = mapIds.begin(); itv!=mapIds.end(); ++itv)
        {
            mapInfos.push_back( make_pair(pGameServer->GetId(),*itv));
        }
    }

    return ER_Success;
}


bool GameServerManager::IsAllGameServerReady()
{
    bool bAllReady = true;

    ItrGameServerPeerContainer it    = _GameServerPeers.begin();
    ItrGameServerPeerContainer itEnd = _GameServerPeers.end();
    for ( ; it!=itEnd; ++it )
    {
        GameServerPeer* pGamePeer = it->second;
        if ( !pGamePeer)
            continue;

        if ( !pGamePeer->GetHaveReady() )
        {
            bAllReady = false;
            break;
        }
    }
    return bAllReady;
}
long GameServerManager::SendMsgToWorldUser( Msg* pMsg)
{
	S2STransmit msg;
	msg.ucSessionType  = S2STransmit::SESSIONT_World;
	//msg.targetData.server.id = g_Cfg.dwServerID;
	bool bResult = msg.StorageMessage( pMsg );
	if ( !bResult)
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToWorldUsere[%d,%d]转发消息太长了", pMsg->GetLength(), pMsg->GetType());
		return ER_Failed;
	}
	this->SendMsgToWorld(&msg);
	return ER_Success;
}
long GameServerManager::SendMsgToWorld( Msg* pMsg  )
{
    if ( !pMsg )
        return ER_Failed;

    DWORD dwMsgType = pMsg->GetType();
    switch ( dwMsgType )
    {
    case GS2CS_TRANSMIT:
        {
            S2STransmit* pMessage = (S2STransmit*)pMsg;
            switch ( pMessage->ucSessionType )
            {
            case S2STransmit::SESSIONT_World:
                {
                    ItrGameServerPeerContainer it = _GameServerPeers.begin();
                    ItrGameServerPeerContainer itEnd = _GameServerPeers.end();
                    for ( ; it != itEnd ; ++it)
                    {
                        GameServerPeer* pGamePeer = it->second;
                        if ( !pGamePeer || pGamePeer->GetId() == pMessage->targetData.server.id )
                            continue;
                        pGamePeer->Send( pMsg );
                    }
                }
            	break;
            }
        }
        break;
    }
    return ER_Success;
}

//发送消息到gameserver
long GameServerManager::SendMsgToSingle( Msg* pMsg, uint32 charDbId, const char* szName /* = "" */)
{
    ClientPeer* pClientPeer = NULL;
    if (charDbId != InvalidLogicNumber )
    { pClientPeer = theClientPeerManager.GetClientPeerByDBId(charDbId); }
    else if (szName != NULL && szName[0] != 0)
    { pClientPeer = theClientPeerManager.GetClientPeerByName(szName); }
     
    if (pClientPeer == NULL)
    {  return ER_Failed; }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
    if ( pGameServer == NULL )
    { return ER_Failed; }

    pGameServer->Send( pMsg );

    return ER_Success;
}

long GameServerManager::SendMsgToSingle( ClientPeer* pClientPeer, Msg *pMsg)
{
	if (pClientPeer == NULL)
	{  return ER_Failed; }

	GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
	if ( pGameServer == NULL )
	{ return ER_Failed; }

	pGameServer->Send( pMsg );

	return ER_Success;
}

long GameServerManager::SendMsgToSingleByAccountId( Msg* pMsg, uint32 accountId )
{
    ClientPeer* pClientPeer = theClientPeerManager.GetClientPeer( accountId );
    if (pClientPeer == NULL)
    {  return ER_Failed; }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
    if ( pGameServer == NULL )
    { return ER_Failed; }

    pGameServer->Send( pMsg );
    return ER_Success;
}

//将消息转发到客户端
void GameServerManager::SendMsgToSingleRemote( unsigned long sourceDbId, Msg* pMessage, unsigned long nDbId, const char* szCharacterName /* =  */, bool bDirect /* = true */ )
{   
    S2STransmit msg;
    msg.identifyId = sourceDbId;
    msg.ucSessionType    = S2STransmit::SESSTONT_Single;
    msg.targetData.character.uDbId = nDbId;
    msg.directToClient = bDirect;
    strncpy_s( msg.targetData.character.szName, sizeof( msg.targetData.character.szName ), szCharacterName, sizeof(msg.targetData.character.szName) - 1 );
    bool bResult = msg.StorageMessage( pMessage );
    if ( !bResult)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "SendMsgToSingleRemote SendMessage Remote[%d,%d]转发消息太长了", pMessage->GetLength(), pMessage->GetType());
        return;
    }
    SendMsgToSingle( &msg, nDbId, szCharacterName);
}

long GameServerManager::SendMessageToGameServers( Msg* pMessage, long ExceptServerId /*= -1*/)
{
    if ( pMessage == NULL) 
    { return ER_Failed; }

    ItrGameServerPeerContainer it    = _GameServerPeers.begin();
    ItrGameServerPeerContainer itEnd = _GameServerPeers.end();
    for ( ; it != itEnd ; ++it)
    {
        GameServerPeer* pGamePeer = it->second;
        if ( pGamePeer == NULL || pGamePeer->GetId() == ExceptServerId || pGamePeer->GetId() == CHARACTERSERVERID  )
        { continue; }
        pGamePeer->Send( pMessage );
    }
    return ER_Success;
}
long GameServerManager::SendMsgToSingleGameServers  ( Msg* pMessage, long GameServerId )
{
	//发送命令道指定ID的GameServer 去 或者随便一个
	if ( pMessage == NULL) 
    { return ER_Failed; }

    ItrGameServerPeerContainer it    = _GameServerPeers.begin();
    ItrGameServerPeerContainer itEnd = _GameServerPeers.end();
    for ( ; it != itEnd ; ++it)
    {
        GameServerPeer* pGamePeer = it->second;
        if ( pGamePeer == NULL || pGamePeer->GetId() == CHARACTERSERVERID  )
        { continue; }
		if(GameServerId != -1 && pGamePeer->GetId() == GameServerId)
		{
			pGamePeer->Send( pMessage );
			return ER_Success;
		}
		else if(GameServerId == -1)
		{
			pGamePeer->Send( pMessage );
			return ER_Success;
		}
    }
    return ER_Success;
}
long GameServerManager::SendMessageToCharacterServer( Msg* pMessage )
{
    if ( pMessage == NULL) 
    { return ER_Failed; }

    GameServerPeer* pGamePeer = GetCharacterServerPeer();
    if ( pGamePeer == NULL )
    { return ER_Failed; }

    pGamePeer->Send( pMessage );

    return ER_Success;
}

bool GameServerManager::LogOnlineInfo(int _logic,int _normal,int _kick,int _total)
{
	ItrGameServerPeerContainer it    = _GameServerPeers.begin();
	ItrGameServerPeerContainer itEnd = _GameServerPeers.end();

	char szServerInfos[1024] = {0};
	char szServerInfo[512] = {0};

	sprintf_s( szServerInfos, "ServerInfos:");
	for ( ; it!=itEnd; ++it )
	{
		GameServerPeer* pGameServerPeer = it->second;
		if ( pGameServerPeer == NULL )
		{ continue; }

		if ( pGameServerPeer->GetId() == CHARACTERSERVERID)
		{ continue; }

		memset( szServerInfo,  0, sizeof(szServerInfo) );
		sprintf_s( szServerInfo, "GameServer[%d:%d]\t", pGameServerPeer->GetId(), pGameServerPeer->GetClientSize());
		HelperFunc::AddNCpy( szServerInfos, szServerInfo, sizeof(szServerInfo) );
	}
	return	theLogEventService.LogOnlineInfo(_logic,_normal,_kick,_total,szServerInfos);
}

int	GameServerManager::GetNormalClientNum()
{
	ItrGameServerPeerContainer it    = _GameServerPeers.begin();
	ItrGameServerPeerContainer itEnd = _GameServerPeers.end();
	int nTotal = 0;
	for ( ; it!=itEnd; ++it )
	{
		GameServerPeer* pGameServerPeer = it->second;
		if ( pGameServerPeer == NULL )
		{ continue; }

		if ( pGameServerPeer->GetId() == CHARACTERSERVERID)
		{ continue; }

		nTotal += pGameServerPeer->GetClientSize();
	}
	return nTotal;
}
void GameServerManager::Statistics(char* szStr )
{
    ItrGameServerPeerContainer it    = _GameServerPeers.begin();
    ItrGameServerPeerContainer itEnd = _GameServerPeers.end();

    char szServerInfos[1024] = {0};
    char szServerInfo[512] = {0};

    sprintf_s( szServerInfos, "ServerInfos:");
    for ( ; it!=itEnd; ++it )
    {
        GameServerPeer* pGameServerPeer = it->second;
        if ( pGameServerPeer == NULL )
        { continue; }

        if ( pGameServerPeer->GetId() == CHARACTERSERVERID)
        { continue; }

        memset( szServerInfo,  0, sizeof(szServerInfo) );
        sprintf_s( szServerInfo, "GameServer[%d:%d]\t", pGameServerPeer->GetId(), pGameServerPeer->GetClientSize());
        HelperFunc::AddNCpy( szServerInfos, szServerInfo, sizeof(szServerInfo) );
    }

	if (!szStr)
	{
		LOG_MESSAGE( STATISTICSOBJECT, LOG_PRIORITY_INFO, szServerInfos );
	}
	else
	{
		HelperFunc::AddNCpy( szStr, szServerInfos, strlen(szServerInfos) );
	}
    
}

bool GameServerManager::GetExtendBornMapOpen()
{
    return m_bExtendBornMapOpen;
}

void GameServerManager::SetExtendBornMapOpen( bool bValue )
{
    m_bExtendBornMapOpen = bValue;

    // 通知角色服务器
    CS2GSMsgBornMapOperate xMsg;
    xMsg.chOperate = bValue;
    SendMessageToCharacterServer( &xMsg );
}

void GameServerManager::SendLoadResourceSuccessMessage( uint8 uchLoadType )
{
    CS2GSLoadResourceSuccess xLoad;
    xLoad.uchLoadType = uchLoadType;
    SendMessageToGameServers( &xLoad );
}

void GameServerManager::CheckQueue(int nNum,bool sub)
{
	if (nNum <= 0||!theConfig.bOpenService)
	{
		return;
	}

	if (sub)
	{//减少,只检测是否可以关闭
		if (m_QueueOpen)
		{//如果开启,检测是否关闭排队,已经在排的不用管
			if (nNum < theConfig.nOpenNum)
			{		
				GameServerPeer* pCharacterServer = GetCharacterServerPeer();
				if (pCharacterServer)
				{
					MsgCS2GSQueueOp op;
					op._open = false;
					pCharacterServer->Send(&op);
				}
				m_QueueOpen = false;
			}
		}
	}
	else
	{//增加,只检测是否需要开启
		if (!m_QueueOpen)
		{//如果没开启,检测是否开启排队
			if (nNum >= theConfig.nOpenNum)
			{
				GameServerPeer* pCharacterServer = GetCharacterServerPeer();
				if (pCharacterServer)
				{
					MsgCS2GSQueueOp op;
					op._open = true;
					pCharacterServer->Send(&op);
				}
				m_QueueOpen = true;
			}
		}		
	}
}