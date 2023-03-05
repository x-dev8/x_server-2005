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
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] UpdateClientPeer ���� ������", pOldClientPeer->GetAccountId(), pOldClientPeer->GetLoginInfo().szAccount/*, pOldClientPeer->GetLoginInfo().Sessionkey*/ );
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
        
            // �������������
            /*if ( Config::GetInstance().isOpenAntiAddictionSystem)
            { GetAntiAddictionSystem().OnMinorAccountOffline(pClientPeer->GetAccountId());}    */

            theCenterTeamManager.TeamMemberOutLine( pClientPeer->GetCharDbId() );      // ���ò����߶��鱣�泬ʱʱ��

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
		//�����Ƿ��ظ���
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
	//�������Ǹ�״̬,�ظ��ʺŵ�¼��ֱ��KICK��
	ClientPeer* pClientPeer = NULL;
	ClientPeer* pLClientPeer = GetClientPeerFromLoginQueue( nAccountId );
	if ( pLClientPeer != NULL )
	{//�ʺŵ�¼״̬,release���Ϳ�����
		RemoveClientPeerFromLoginQueue( nAccountId ); 
	}
	else
	{
		//��ʾ����Ϸ��,Ҫ�����Ϸ
		pClientPeer = GetClientPeer(nAccountId);
		if (pClientPeer != NULL)
		{//��֪�����Ǹ�������,Ⱥ�������еķ�����
			//pClientPeer->AddBeKickTimes();
			S2SMsgKickChar msg;
			msg.time        = 0;
			msg.dwAccountID = nAccountId;
			msg.usReason    = S2SMsgKickChar::KR_AccountRepeat;
			msg.SessionKey = pClientPeer->GetLoginInfo().Sessionkey;
			//msg.uchFailAck = S2SMsgKickChar::ECD_AckCount; //���ֵ��ʾ���ø���Ӧ�ˣ������ߺſ϶�Ҫ��0��ʼ��
			theGameServerManager.SendMessageToGameServers( &msg );
			theGameServerManager.SendMessageToCharacterServer( &msg );

			MsgLoginError le;
			le.chErrorType = eLE_AccountInGame;
			le.uAccountId = nAccountId;			
			theCenterServer.SendMessageToLogin(&le);

			//��ʱ������ŵ����� begin
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
	//����Ƿ��� by cloud
	if( theConfig.nFullLoadMaxNum > 0 && ClientPeerSize() >= theConfig.nFullLoadMaxNum )
	{
		MsgLoginError ler;
		ler.chErrorType = eLE_AccountServerFullLoad;
		ler.uAccountId = nAccountId;
		theCenterServer.SendMessageToLogin(&ler);
		return ER_AddLoginClientPeerFail;
	}

	//����Ƿ񳬹���mac��½ֵ
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

    // ��¼��½��Ϣ
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
    pClientPeer->SetCharDynamicId( -1 ); // ����ClientPeer��ɫ��̬Id,�ȸ�-1,����ʽCLIENT���ӽ������������

    SServerInfo si;                     // ����ClientPeer ServerInfo��Ϣ
    si.nServerType = ST_LoginServer;
    si.nServerId   = 0;
    pClientPeer->ChangeServerInfo( si );

    // �����µ�ClientPeer
    AddClientPeerToLoginQueue( pClientPeer );

    pClientPeer->SetState( CST_InLoginQueueNotSendLoginInfo ); // ����ClientPeer״̬

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
        { // ���Ѵ���ʱ��̫���ˣ�ʧ�ܸ������ݿ�
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

    // �����¼��Ϣ���������˲�����ȥȡmysql��
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
            {// ����������GameServer������;�У� ֪ͨĿ���������Ҫ���ܴ��û��������� �㲥Ŀ�������ɾ�����ʺŵ�¼���key
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
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ���� S2SMsgKickChar ��Ϣ", rLoginInfoBase.nAccountID );
                    }
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ����״̬[%d] [%d]", rLoginInfoBase.nAccountID, rServerInfo.nServerType, pClientPeer->GetState() );
                break;
            }
        }
        break;
    case ST_GameServer:
    case ST_CharacterServer:
        {   
            switch( pClientPeer->GetState() )
            {// ����������GameServer������;�У� ֪ͨĿ���������Ҫ���ܴ��û��������� �㲥Ŀ�������ɾ�����ʺŵ�¼���key
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
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ���� S2SMsgKickChar ��Ϣ", rLoginInfoBase.nAccountID );                    
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
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ���� S2SMsgKickChar ��Ϣ", rLoginInfoBase.nAccountID );
                    }
                }
                break;
            default: // ��������GameServer�������� ��ɾ������ҵ��˳���Ϣ����֤������ȷ���
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
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ���� S2SMsgKickChar ��Ϣ", rLoginInfoBase.nAccountID );
                    }

                }
                break;
            }
        }
        break;
    default:
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ����״̬[%d] [%d]", rLoginInfoBase.nAccountID, rServerInfo.nServerType, pClientPeer->GetState() );
        break;
    }

    // ������״̬��û�з�����Ϣ, ����Ⱥ�������з�����
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
//             theCenterTeamManager.TeamMemberOutLine( pClientPeer->GetCharDbId() );      // ���ò����߶��鱣�泬ʱʱ��
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
        theCenterTeamManager.TeamMemberOutLine( pMessage->dwDBID );   // �������߶��鱣����ʱʱ��
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ClientPeerManager::OnPlayerExit can't find AccountId[%u] [%u]", pMessage->nAccountId, pMessage->cExitType );
        return ER_Failed;
    }
    
    switch ( pMessage->cExitType )
    {
    case ET_ExitGame:
        { // �˺��˳���Ϸ GameServer ����� ���������˳�(����block 0), ����Ϸ����֤���߳�(��blockʱ��)
	        pClientPeer->OnExitServer( pMessage->cExitType );           
            
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-:-] ET_ExitGame ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey, pMessage->SessionKey */);

            if (pMessage->SessionKey == 0
				||pClientPeer->GetLoginInfo().Sessionkey == pMessage->SessionKey
				/* 0 == strlen(pMessage->szSessionKey) || 0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey)*/ )
            { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] Session �쳣��һ�� ȫ������", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey, pMessage->SessionKey*/ ); }

            theCenterServer.NotifyGLSPlayerExit( pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount, pMessage->blockTime );

            RemoveClientPeer( pMessage->nAccountId );
			theGameServerManager.CheckQueue(ClientPeerSize(),true);

            // �����˳�
            theCenterServer.gGameWorldStatistics.activeExitClientPeer += 1;
        }
        break;
    case ET_BeKick:
	case ET_SystemBeKick:
        { // ��ɫ�˺ű���  CenterServer ����� ����ֻ���ʺ��ص�ʱ���߳�
            // ���szSessionKey��Ϊ�� ���� �ڴ��е�ClientPeer���쳣�˳�����ͬһ�� ��ֹ���첽����������Ϣ�����û��ߵ�
            //if ( 0 == strlen(pMessage->szSessionKey) || 0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey) )
            //{ return ER_Success; }

            pClientPeer->OnExitServer( pMessage->cExitType ); 

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] BeKick ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey */);            
            theCenterServer.NotifyGLSAccountSafeOffLine( pClientPeer->GetLoginInfo().nAccountID, pClientPeer->GetLoginInfo().szAccount );
            RemoveClientPeer( pMessage->nAccountId );
			theGameServerManager.CheckQueue(ClientPeerSize(),true);

            theCenterServer.NotifyGLSPlayerExit( pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount, pMessage->blockTime );

            // �����˳���
            theCenterServer.gGameWorldStatistics.kicklExitClientPeer += 1;
        }
        break;
    case ET_SwitchGameServer:
        { // ��ɫ����Ϸ������
            pClientPeer->OnExitServer( pMessage->cExitType ); 

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] ET_SwitchGameServer ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey*/ );
        }
        break;
    case ET_ReturnCharacterServer:
        { // ��ɫ�˳� �ص�ѡ�˽���
            pClientPeer->OnExitServer( pMessage->cExitType ); 
            
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-] ET_ReturnCharacterServer ", pMessage->nAccountId, pClientPeer->GetLoginInfo().szAccount/*, pClientPeer->GetLoginInfo().Sessionkey*/ );
        }
        break;
    case ET_ExceptionKick:
        {
            // ���szSessionKey��Ϊ�� ���� �ڴ��е�ClientPeer���쳣�˳�����ͬһ��
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

            // �����˳���
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
    {// 1.�����ǰ�ڵ�ͼ��������
        pClientPeer->SetCountry( pSynInfo->uchCountry );    // �����ù���
        // ���״̬
        switch ( pSynInfo->ucStatus )
        {
        case GS2CSPlayerSynInServerInfo::ES_FirstInMapStagePlaying: // ��һ�ν�����Ϸ
            {
                // �����������, ֪ͨ��������, �����Ա����
                pClientPeer->ProcessEnterWorld();
            }
            // �벻Ҫ��break, ����ҲҪִ��
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
	{// 2.���Ŀǰ�ڽ�ɫ��������
		// ֻ����һ��mac��Ϣ�ͺ��� �����Ĳ���
		UpdateClientPeerByMac ( pClientPeer );
	}


    return ER_Success;
}

void ClientPeerManager::Update()
{
    return;
}