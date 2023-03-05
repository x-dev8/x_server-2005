#include "ClientPeerManager.h"
#include "CenterLoginMessage.h"
#include "GameServerManager.h"
#include "LoginServerManager.h"
#include "DBMessageDefine.h"
//#include "LoginQueue.h"
#include "Config.h"
#include "CenterServer.h"
#include "TeamManager.h"
//#include "AntiAddictionSystem.h"
#include "RelationManager.h"
#include "GameTime.h"

ClientPeerManager& ClientPeerManager::GetInstance()
{
    static ClientPeerManager instance;
    return instance;
}

void ClientPeerManager::_Release()
{
    ItrClientPeerMapContainer it = _clientPeers.begin();
    for ( ; it!=_clientPeers.end();++it)
    {
        ClientPeer* pClientPeer = it->second;
        if ( !pClientPeer)
            continue;

        pClientPeer->Release();
    }
    _clientPeers.clear();
}

ClientPeerManager::ClientPeerManager() : _lastProcessLoginClieetPeersTime(0)
{
}

ClientPeer* ClientPeerManager::GetClientPeerFromLoginQueue( unsigned long nAccountId )
{
    ItrClientPeerMapContainer it = _loginPeers.find( nAccountId );

    if ( it != _loginPeers.end() )
        return it->second;

    return NULL;
}

bool ClientPeerManager::AddClientPeerToLoginQueue( ClientPeer* pClientPeer )
{
    if ( !pClientPeer)
        return false;

    return _loginPeers.insert( ClientPeerMapContainer::value_type( pClientPeer->GetAccountId(), pClientPeer) ).second;
}

void ClientPeerManager::RemoveClientPeerFromLoginQueue( unsigned long nAccountId, bool bRelease/* = true */)
{
    ItrClientPeerMapContainer it = _loginPeers.find( nAccountId );
    if ( it != _loginPeers.end())
    {
        ClientPeer* pClientPeer = it->second;
        
        if ( pClientPeer && bRelease)
        {
            pClientPeer->Release();
        }
        _loginPeers.erase( it );
    }
}

bool ClientPeerManager::UpdateClientPeer( ClientPeer* pClientPeer )
{
    if ( NULL == pClientPeer)
    { return false; }

    ClientPeer* pOldClientPeer = GetClientPeer( pClientPeer->GetAccountId() );
    if ( pOldClientPeer )
    {
        RemoveClientPeer( pClientPeer->GetAccountId() ); 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] UpdateClientPeer 存在 被重置", pOldClientPeer->GetAccountId(), pOldClientPeer->GetLoginInfo().szAccount/*, pOldClientPeer->GetLoginInfo().Sessionkey*/ );
    }

    /* comment out by zhangqi 2010-7-8
    if ( Config::GetInstance().isOpenAntiAddictionSystem)
    { GetAntiAddictionSystem().OnMinorAccountOnline(pClientPeer->GetAccountId());}*/

    return _clientPeers.insert( ClientPeerMapContainer::value_type( pClientPeer->GetAccountId(), pClientPeer) ).second;
}

ClientPeer* ClientPeerManager::GetClientPeer( unsigned long nAccountId )
{
    ItrClientPeerMapContainer it = _clientPeers.find( nAccountId );

    if ( it != _clientPeers.end() )
        return it->second;

    return NULL;
}

void ClientPeerManager::RemoveClientPeer( unsigned long nAccountId )
{
    ItrClientPeerMapContainer it = _clientPeers.find( nAccountId );
    if ( it != _clientPeers.end())
    {
        ClientPeer* pClientPeer = it->second;
        
        if ( pClientPeer != NULL )
        {
            //SServerInfo& rServerInfo       = pClientPeer->GetServerInfo();
            //SLoginInfoBase& rLoginInfoBase = pClientPeer->GetLoginInfo();
            //switch ( rServerInfo.nServerType )
            //{
            //case ST_LoginServer:
            //    {
            //        LoginServerPeer* pLoginServer = LoginServerManager::GetInstance().GetLoginServerPeer( rServerInfo.nServerId );
            //        if ( pLoginServer )
            //        {
            //            pLoginServer->RemoveAccountId( rLoginInfoBase.nAccountID );
            //        }
            //    }
            //    break;
            //case ST_GameServer:
            //    {   
            //        GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( rServerInfo.nServerId );
            //        if ( pGameServer )
            //        {
            //            pGameServer->RemoveAccountId( rLoginInfoBase.nAccountID);
            //        }
            //    }
            //    break;
            //}
        
            // 如果开启防沉迷
            /*if ( Config::GetInstance().isOpenAntiAddictionSystem)
            { GetAntiAddictionSystem().OnMinorAccountOffline(pClientPeer->GetAccountId());}    */

            theCenterTeamManager.TeamMemberOutLine( pClientPeer->GetCharDbId() );      // 设置不在线队伍保存超时时间

			RemoveClientPeerByDBId(pClientPeer->GetCharDbId());
            RemoveClientPeerByName(pClientPeer->GetCharacterName());
			RemoveClientPeerByMac (pClientPeer);

            pClientPeer->ProcessExitWorld();
            pClientPeer->Release();
        }
        _clientPeers.erase( it );
    }
}

bool ClientPeerManager::UpdateClientPeerByDBId(ClientPeer *pClientPeer)
{
	if (pClientPeer == NULL)
        return false;

	ItrClientPeerMapContainer it = _dbClientPeers.find(pClientPeer->GetCharDbId());
	if (it != _dbClientPeers.end()) 
    {
        _dbClientPeers.erase( it );
    }
    return _dbClientPeers.insert( ClientPeerMapContainer::value_type(pClientPeer->GetCharDbId(), pClientPeer)).second;
}

void ClientPeerManager::RemoveClientPeerByDBId(unsigned long dwDataBaseId)
{
	ItrClientPeerMapContainer iter = _dbClientPeers.find(dwDataBaseId);
	if (iter != _dbClientPeers.end())
	{
		_dbClientPeers.erase(iter);
	}
}

ClientPeer* ClientPeerManager::GetClientPeerByDBId(unsigned long dwDataBaseId)
{
	ItrClientPeerMapContainer iter = _dbClientPeers.find(dwDataBaseId);
	if (iter != _dbClientPeers.end())
	{
		return iter->second;
	}

	return NULL;
}

ClientPeer* ClientPeerManager::GetClientPeerByName( const std::string& strName )
{
    ItrClientPeerMapContainerByString it = _nameClientPeers.find( strName );
    if ( it != _nameClientPeers.end() )
        return it->second;
	return NULL;
}

bool ClientPeerManager::UpdateClientPeerByName( ClientPeer* pClientPeer )
{
	if ( pClientPeer == NULL )
        return false;

    ItrClientPeerMapContainerByString it = _nameClientPeers.find( pClientPeer->GetCharacterName() );
    if ( it != _nameClientPeers.end() )
    {
        _nameClientPeers.erase( it );
    }

	return _nameClientPeers.insert( ClientPeerMapContainerByString::value_type( pClientPeer->GetCharacterName(),  pClientPeer)).second;
}

void ClientPeerManager::RemoveClientPeerByName( const std::string& strName )
{   
	ItrClientPeerMapContainerByString iter = _nameClientPeers.find(strName);
	if (iter != _nameClientPeers.end())
		_nameClientPeers.erase(iter);
}
std::vector<ClientPeer*>* ClientPeerManager::GetClientPeerByMac( const std::string& strMac )
{
	ItrClientPeerMapContainerByMac it = _macClientPeers.find( strMac );
	if ( it != _macClientPeers.end() )
		return &it->second;
	return NULL;
}
bool ClientPeerManager::UpdateClientPeerByMac( ClientPeer* pClientPeer )
{
	if ( pClientPeer == NULL )
		return false;

	std::vector<ClientPeer*> tempPeers;
	ItrClientPeerMapContainerByMac it = _macClientPeers.find( pClientPeer->GetMacAdress() );
	if ( it != _macClientPeers.end() )
	{
		//查找是否重复了
		std::vector<ClientPeer*>::iterator itr = find(it->second.begin(), it->second.end(), pClientPeer);
		if (itr == it->second.end())
		{
			it->second.push_back(pClientPeer);
		}
		return true;
	}
	tempPeers.push_back(pClientPeer);
	return _macClientPeers.insert( ClientPeerMapContainerByMac::value_type( pClientPeer->GetMacAdress(),  tempPeers)).second;
}

void ClientPeerManager::RemoveClientPeerByMac( ClientPeer* pClientPeer /*const std::string& strMac*/ )
{
	ItrClientPeerMapContainerByMac iter = _macClientPeers.find(pClientPeer->GetMacAdress());
	if (iter != _macClientPeers.end())
	{
		std::vector<ClientPeer*>::iterator it = find(iter->second.begin(), iter->second.end(), pClientPeer);

		if (it != iter->second.end())
		{
			iter->second.erase(it);
		}

		if (iter->second.size() == 0)
		{
			_macClientPeers.erase(iter);
		}
	}
}

long ClientPeerManager::AddLoginClientPeer( int nAccountId, const std::string& strAccount,__int64 sessionkey,const char* strMac, /*char* szSessionKey ,char* szPassword, *//*char* Seed,*/ int8 isWallow )
{
	//无论在那个状态,重复帐号登录都直接KICK掉
	ClientPeer* pClientPeer = NULL;
	ClientPeer* pLClientPeer = GetClientPeerFromLoginQueue( nAccountId );
	if ( pLClientPeer != NULL )
	{//帐号登录状态,release掉就可以了
		RemoveClientPeerFromLoginQueue( nAccountId ); 
	}
	else
	{
		//表示在游戏中,要提出游戏
		pClientPeer = GetClientPeer(nAccountId);
		if (pClientPeer != NULL)
		{//不知道在那个服务器,群发给所有的服务器
			//pClientPeer->AddBeKickTimes();
			S2SMsgKickChar msg;
			msg.time        = 0;
			msg.dwAccountID = nAccountId;
			msg.usReason    = S2SMsgKickChar::KR_AccountRepeat;
			msg.SessionKey = pClientPeer->GetLoginInfo().Sessionkey;
			//msg.uchFailAck = S2SMsgKickChar::ECD_AckCount; //这个值表示不用给回应了，错误，踢号肯定要从0开始踢
			theGameServerManager.SendMessageToGameServers( &msg );
			theGameServerManager.SendMessageToCharacterServer( &msg );

			MsgLoginError le;
			le.chErrorType = eLE_AccountInGame;
			le.uAccountId = nAccountId;			
			theCenterServer.SendMessageToLogin(&le);

			//暂时解决卡号的问题 begin
// 			if (pClientPeer->GetBeKickTimes()>3)
// 			{
// 				GS2CSPlayerExit forceMsg;
// 				forceMsg.nAccountId = nAccountId;
// 				forceMsg.dwDBID     = pClientPeer->GetCharDbId();
// 				forceMsg.cExitType  = ET_BeKick;
// 				forceMsg.blockTime  = 0;
// 				forceMsg.SessionKey = pClientPeer->GetLoginInfo().Sessionkey;
// 				OnPlayerExit( &forceMsg );
// 			}
			
			//end
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "LoginError and KickChar:Account[%u],state[%d]",nAccountId,pClientPeer->GetState());

			return ER_AddLoginClientPeerFail;
		}
	}
	//检测是否爆棚 by cloud
	if( theConfig.nFullLoadMaxNum > 0 && ClientPeerSize() >= theConfig.nFullLoadMaxNum )
	{
		MsgLoginError ler;
		ler.chErrorType = eLE_AccountServerFullLoad;
		ler.uAccountId = nAccountId;
		theCenterServer.SendMessageToLogin(&ler);
		return ER_AddLoginClientPeerFail;
	}

	//检测是否超过单mac登陆值
	std::vector<ClientPeer*>* pResult = GetClientPeerByMac(strMac);
	if( theConfig.nMaxNumOneMac > 0 && pResult && pResult->size() >= theConfig.nMaxNumOneMac )
	{
		MsgLoginError ler;
		ler.chErrorType = eLE_AccountOverOneMac;
		ler.uAccountId = nAccountId;
		theCenterServer.SendMessageToLogin(&ler);
		return ER_AddLoginClientPeerFail;
	}
	
    pClientPeer = ClientPeer::CreateInstance();
    if ( pClientPeer == NULL )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "OnClientPeerLogin ClientPeer::CreateInstance Fail");
        return ER_ClientPeerNewFail;
    }

    // 记录登陆信息
    SLoginInfoBase loginInfo;
    memset( loginInfo.szIP, 0, sizeof(loginInfo.szIP) );
    strncpy_s( loginInfo.szAccount,  sizeof(loginInfo.szAccount),  strAccount.c_str(),  sizeof(loginInfo.szAccount)-1);
	strncpy_s( loginInfo.szMac,  sizeof(loginInfo.szMac),  strMac,  sizeof(loginInfo.szMac)-1);
	loginInfo.Sessionkey = sessionkey;
    //strncpy_s( loginInfo.SessionKey, sizeof(loginInfo.SessionKey), szSessionKey,        sizeof(loginInfo.SessionKey)-1);
   // strncpy_s( loginInfo.Password,   sizeof(loginInfo.Password),   szPassword,          sizeof(loginInfo.Password)-1);
    //strncpy_s( loginInfo.Seed,       sizeof(loginInfo.Seed),       Seed,                sizeof(loginInfo.Seed)-1);
    loginInfo.nAccountID  = nAccountId;
    loginInfo.LoginTime   = HQ_TimeGetTime();
    loginInfo.isWallow    = isWallow;

    pClientPeer->SetLoginInfo( loginInfo );
    pClientPeer->SetCharDynamicId( -1 ); // 设置ClientPeer角色动态Id,先给-1,等正式CLIENT连接进入再请求分配

    SServerInfo si;                     // 设置ClientPeer ServerInfo信息
    si.nServerType = ST_LoginServer;
    si.nServerId   = 0;
    pClientPeer->ChangeServerInfo( si );

    // 加入新的ClientPeer
    AddClientPeerToLoginQueue( pClientPeer );

    pClientPeer->SetState( CST_InLoginQueueNotSendLoginInfo ); // 设置ClientPeer状态

    //pClientPeer->ProcessLogin();

    return ER_Success;
}

void ClientPeerManager::ProcessLoginClieetPeers()
{
    if ( !GameTime::IsPassCurrentTime( _lastProcessLoginClieetPeersTime, 1000 ) )
    { return;}

    ItrClientPeerMapContainer it    = _loginPeers.begin();
    ItrClientPeerMapContainer itEnd = _loginPeers.end();
    for ( ; it != itEnd; )
    {
        ClientPeer* pClientPeer = it->second;
        if ( pClientPeer == NULL )
        {
            it = _loginPeers.erase( it );
            continue;
        }
        
        if ( pClientPeer->GetState() == CST_InLoginQueueNotSendLoginInfo  )
        {
            pClientPeer->ProcessLogin();
        }

        if ( GameTime::IsPassCurrentTime( pClientPeer->GetLoginInfo().LoginTime, 60 * 1000 ) )
        { // 消费处理时间太久了，失败告诉数据库
            /*SqlMessage sqlMessage;
            sqlMessage.nMessageId = SqlMessage::ESM_ProcessLoginAllowTimeOver;
            sqlMessage.Guid       = pClientPeer->GetLoginInfo().nAccountID;*/
            //CenterServer::GetInstance().GetSqlService().PushResult( sqlMessage );

			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Release ClientPeer By Login Time:Account[%u:%s]",pClientPeer->GetLoginInfo().nAccountID,pClientPeer->GetLoginInfo().szAccount);

            pClientPeer->Release();
            it = _loginPeers.erase( it );
            continue;
        }
        ++it;
    }

    // 如果登录信息都消费完了才重新去取mysql表
    /*if ( _loginPeers.empty() )
    {
		#ifdef _USE_SQL
        CenterServer::GetInstance().GetSqlService().EnableOnlineQueryFlag();
		#endif
    }*/

    _lastProcessLoginClieetPeersTime = HQ_TimeGetTime();
}

uint32 ClientPeerManager::KickClientPeer( ClientPeer* pClientPeer, uint8 kickType, uint32 time/* = 0 */ )
{
    if ( NULL == pClientPeer)
    { return ER_Failed; }

    const SServerInfo&    rServerInfo    = pClientPeer->GetServerInfo();
    const SLoginInfoBase& rLoginInfoBase = pClientPeer->GetLoginInfo();
    const SStageReqInfo&  rReqServerInfo = pClientPeer->GetReqServerInfo();

    bool bSendKickMessage = false;
    switch ( rServerInfo.nServerType )
    {
    case ST_LoginServer:
        {
            switch( pClientPeer->GetState() )
            {// 如果玩家在切GameServer服务器途中， 通知目标服务器不要接受此用户的连接了 广播目标服务器删除此帐号登录许可key
            case CST_WaitLoginServer2CharacterServer: 
                {
                    GameServerPeer* pTargetGameServerPeer = theGameServerManager.GetCharacterServerPeer();
                    if ( NULL != pTargetGameServerPeer )
                    { 
                        S2SMsgKickChar msg;
                        msg.time        = time;
                        msg.dwAccountID = rLoginInfoBase.nAccountID;
                        msg.usReason    = S2SMsgKickChar::KR_KickToConnect;
                        //strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), rLoginInfoBase.SessionKey, sizeof(msg.szSessionKey)-1);
						msg.SessionKey = rLoginInfoBase.Sessionkey;
                        pTargetGameServerPeer->Send( &msg );

                        bSendKickMessage = true;
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 发送 S2SMsgKickChar 消息", rLoginInfoBase.nAccountID );
                    }
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 游离状态[%d] [%d]", rLoginInfoBase.nAccountID, rServerInfo.nServerType, pClientPeer->GetState() );
                break;
            }
        }
        break;
    case ST_GameServer:
    case ST_CharacterServer:
        {   
            switch( pClientPeer->GetState() )
            {// 如果玩家在切GameServer服务器途中， 通知目标服务器不要接受此用户的连接了 广播目标服务器删除此帐号登录许可key
            case CST_WaitGameServer2CharacterServer:
                {
                    GameServerPeer* pTargetGameServerPeer = theGameServerManager.GetCharacterServerPeer();
                    if ( NULL != pTargetGameServerPeer )
                    { 
                        S2SMsgKickChar msg;
                        msg.time        = time;
                        msg.dwAccountID = rLoginInfoBase.nAccountID;
                        msg.usReason    = S2SMsgKickChar::KR_KickToConnect;
                        //strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), rLoginInfoBase.SessionKey, sizeof(msg.szSessionKey)-1);
						msg.SessionKey = rLoginInfoBase.Sessionkey;
                        pTargetGameServerPeer->Send( &msg );

                        bSendKickMessage = true;
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 发送 S2SMsgKickChar 消息", rLoginInfoBase.nAccountID );                    
                    }
                }
                break;
            case CST_WaitCharacterServer2GameServer:
            case CST_WaitGameServer2GameServer:
                {
                    GameServerPeer* pTargetGameServerPeer = theGameServerManager.GetGameServerPeer( rReqServerInfo.nServerId );
                    if ( NULL != pTargetGameServerPeer )
                    { 
                        S2SMsgKickChar msg;
                        msg.time        = time;
                        msg.dwAccountID = rLoginInfoBase.nAccountID;
                        msg.usReason    = S2SMsgKickChar::KR_KickToConnect;
                        //strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), rLoginInfoBase.SessionKey, sizeof(msg.szSessionKey)-1);
						msg.SessionKey = rLoginInfoBase.Sessionkey;
                        pTargetGameServerPeer->Send( &msg );

                        bSendKickMessage = true;
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 发送 S2SMsgKickChar 消息", rLoginInfoBase.nAccountID );
                    }
                }
                break;
            default: // 如果玩家在GameServer服务器上 不删，等玩家的退出消息，保证数据正确入库
                {
                    GameServerPeer* pGameServerPeer = theGameServerManager.GetGameServerPeer( rServerInfo.nServerId );
                    if ( NULL != pGameServerPeer)
                    { 
                        S2SMsgKickChar msg;
                        msg.time        = time;
                        msg.dwAccountID = rLoginInfoBase.nAccountID;
                        msg.usReason    = kickType;
                        //strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), rLoginInfoBase.SessionKey, sizeof(msg.szSessionKey)-1);
						msg.SessionKey = rLoginInfoBase.Sessionkey;
                        pGameServerPeer->Send( &msg );

                        bSendKickMessage = true;
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 发送 S2SMsgKickChar 消息", rLoginInfoBase.nAccountID );
                    }

                }
                break;
            }
        }
        break;
    default:
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] 游离状态[%d] [%d]", rLoginInfoBase.nAccountID, rServerInfo.nServerType, pClientPeer->GetState() );
        break;
    }

    // 在游离状态下没有发送消息, 这里群发给所有服务器
    if ( !bSendKickMessage )
    {
        S2SMsgKickChar xKick;
        xKick.dwAccountID = rLoginInfoBase.nAccountID;
        xKick.time        = time;
        xKick.usReason    = kickType;
        xKick.uchFailAck  = S2SMsgKickChar::ECD_AckCount;
        theGameServerManager.SendMessageToGameServers( &xKick );
        theGameServerManager.SendMessageToCharacterServer( &xKick );
    }

    return ER_Success;
}

// uint32 ClientPeerManager::KickClientPeersOnGameServerException( unsigned long serverId )
// {
//     ItrClientPeerMapContainer it    = _clientPeers.begin();
//     ItrClientPeerMapContainer itEnd = _clientPeers.end();
// 
//     for ( ; it!= itEnd; )
//     {
//         ClientPeer* pClientPeer = it->second;
//         if ( pClientPeer == NULL )
//         { continue; }
//         
//         if ( pClientPeer->GetReqServerInfo().nServerId == serverId || pClientPeer->GetServerInfo().nServerId == serverId)
//         {
//             theCenterServer.NotifyGLSPlayerExit( pClientPeer->GetAccountId(), pClientPeer->GetLoginInfo().szAccount ); 
// 
//             theCenterTeamManager.TeamMemberOutLine( pClientPeer->GetCharDbId() );      // 设置不在线队伍保存超时时间
// 
//             RemoveClientPeerByDBId(pClientPeer->GetCharDbId());
//             RemoveClientPeerByName(pClientPeer->GetCharacterName());
// 
//             pClientPeer->ProcessExitWorld(); 
//             pClientPeer->Release();
// 
//             it = _clientPeers.erase( it );
//             continue;
//         }
//         
//         ++it;
//     }
//     return ER_Success;
// }

void ClientPeerManager::SendLoginHintInfoToLoginServer( unsigned long nLoginServerId, short nClientIdInServer, long nResult )
{
    LoginServerPeer* pLoginServer = LoginServerManager::GetInstance().GetLoginServerPeer( nLoginServerId );
    if ( !pLoginServer)
        return;
    MsgSwitchGate msg;
    msg.header.stID = nClientIdInServer;
    msg.nResult     = nResult;
    msg.uGatePort   = 0;
    msg.nServerType = ST_LoginServer;
    memset( msg.szGateIP, 0, sizeof(msg.szGateIP));
    memset( msg.szChannelName, 0, sizeof(msg.szChannelName));
    pLoginServer->Send( &msg );
}

long ClientPeerManager::OnPlayerExit( GS2CSPlayerExit* pMessage )
{
    ClientPeer* pClientPeer = GetClientPeer( pMessage->nAccountId );
    if ( pClientPeer == NULL )
    {
        theCenterTeamManager.TeamMemberOutLine( pMessage->dwDBID );   // 设置离线队伍保留超时时间
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ClientPeerManager::OnPlayerExit can't find AccountId[%u] [%u]", pMessage->nAccountId, pMessage->cExitType );
        return ER_Failed;
    }
    
    switch ( pMessage->cExitType )
    {
    case ET_ExitGame:
        { // 账号退出游戏 GameServer 发起的 包括正常退出(不带block 0), 被游戏中验证码踢除(带block时间)
	        pClientPeer->OnExitServer( pMessage->cExitType );           
            
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-:-] ET_ExitGame ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey, pMessage->SessionKey */);

            if (pMessage->SessionKey == 0
				||pClientPeer->GetLoginInfo().Sessionkey == pMessage->SessionKey
				/* 0 == strlen(pMessage->szSessionKey) || 0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey)*/ )
            { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] Session 异常不一样 全服踢人", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey, pMessage->SessionKey*/ ); }

            theCenterServer.NotifyGLSPlayerExit( pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount, pMessage->blockTime );

            RemoveClientPeer( pMessage->nAccountId );
			theGameServerManager.CheckQueue(ClientPeerSize(),true);

            // 主动退出
            theCenterServer.gGameWorldStatistics.activeExitClientPeer += 1;
        }
        break;
    case ET_BeKick:
	case ET_SystemBeKick:
        { // 角色账号被踢  CenterServer 发起的 现在只由帐号重登时候踢除
            // 如果szSessionKey不为空 或者 内存中的ClientPeer和异常退出的是同一个 防止被异步回来的踢消息把新用户踢掉
            //if ( 0 == strlen(pMessage->szSessionKey) || 0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey) )
            //{ return ER_Success; }

            pClientPeer->OnExitServer( pMessage->cExitType ); 

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] BeKick ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey */);            
            theCenterServer.NotifyGLSAccountSafeOffLine( pClientPeer->GetLoginInfo().nAccountID, pClientPeer->GetLoginInfo().szAccount );
            RemoveClientPeer( pMessage->nAccountId );
			theGameServerManager.CheckQueue(ClientPeerSize(),true);

            theCenterServer.NotifyGLSPlayerExit( pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount, pMessage->blockTime );

            // 被踢退出的
            theCenterServer.gGameWorldStatistics.kicklExitClientPeer += 1;
        }
        break;
    case ET_SwitchGameServer:
        { // 角色切游戏服务器
            pClientPeer->OnExitServer( pMessage->cExitType ); 

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] ET_SwitchGameServer ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey*/ );
        }
        break;
    case ET_ReturnCharacterServer:
        { // 角色退出 回到选人界面
            pClientPeer->OnExitServer( pMessage->cExitType ); 
            
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] ET_ReturnCharacterServer ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey*/ );
        }
        break;
    case ET_ExceptionKick:
        {
            // 如果szSessionKey不为空 或者 内存中的ClientPeer和异常退出的是同一个
            /*if ( 0 == strlen(pMessage->szSessionKey) || 0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey) )
            { return ER_Success; }*/
			if (pMessage->SessionKey == 0||
				pClientPeer->GetLoginInfo().Sessionkey != pMessage->SessionKey)
			{
				return ER_Success;
			}

            pClientPeer->OnExitServer( pMessage->cExitType ); 

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] ET_ExceptionKick ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey */);
            RemoveClientPeer( pMessage->nAccountId );
			theGameServerManager.CheckQueue(ClientPeerSize(),true);

            theCenterServer.NotifyGLSPlayerExit( pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount, pMessage->blockTime );

            // 被踢退出的
            theCenterServer.gGameWorldStatistics.kicklExitClientPeer += 1;
        }
        break;
    }

    return ER_Success;
}

long ClientPeerManager::OnPlayerSynInServerInfo( Msg* pMessage )
{
    GS2CSPlayerSynInServerInfo* pSynInfo = (GS2CSPlayerSynInServerInfo*)pMessage;    
    
    ClientPeer* pClientPeer = GetClientPeer( pSynInfo->nAccountId );
    if ( pClientPeer == NULL )
    {  return ER_ClientPeerNotExist; }

    pClientPeer->OnSynInServerInfo( pSynInfo );

	
    if ( pSynInfo->serverInfo.nServerType == ST_GameServer )
    {// 1.如果当前在地图服务器上
        pClientPeer->SetCountry( pSynInfo->uchCountry );    // 先设置国家
        // 玩家状态
        switch ( pSynInfo->ucStatus )
        {
        case GS2CSPlayerSynInServerInfo::ES_FirstInMapStagePlaying: // 第一次进入游戏
            {
                // 处理玩家上线, 通知好友上线, 公会成员上线
                pClientPeer->ProcessEnterWorld();
            }
            // 请不要加break, 下面也要执行
        case GS2CSPlayerSynInServerInfo::ES_InMapStagePlaying:
            {
                UpdateClientPeerByName( pClientPeer );
                UpdateClientPeerByDBId( pClientPeer );
				UpdateClientPeerByMac ( pClientPeer );
            }
            break;
        default:
            break;
        }
    }
	else if ( pSynInfo->serverInfo.nServerType == ST_CharacterServer)
	{// 2.如果目前在角色服务器上
		// 只处理一下mac信息就好了 其他的不变
		UpdateClientPeerByMac ( pClientPeer );
	}


    return ER_Success;
}

void ClientPeerManager::Update()
{
    return;
}