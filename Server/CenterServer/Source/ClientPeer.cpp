#include "ClientPeer.h"
#include "DBMessageDefine.h"
#include "GameServerManager.h"
#include "LoginServerManager.h"
#include "ClientPeerManager.h"
//#include "LoginQueue.h"
//#include "SessionManager.h"
#include "CenterServer.h"
#include "Config.h"
#include "TeamManager.h"
#include "RelationManager.h"
#include "CountryConfig.h"
#include "GuildManager.h"
#include "CountryManager.h"
#include "FamilyManager.h"
#include "CenterFamily.h"

#define Channel_StatusMax 3 //线状态,只有3个,越小越好
#define COUNT_PER 500 //人数的状态单位,每500人一个级别

ClientPeer::ClientPeer()
{   
    ResetAccountInfo();
    ResetCharInfo();
}

long ClientPeer::ProcessMessage( NetClient* pNetClient, Msg* pMessage )
{
    unsigned long msgType = pMessage->GetType();

    // LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "ClientPeerProcessMessage[%d] State[%d]", msgType, GetState());

    switch ( GetState() )
    {
    case CST_InLoginQueueWaitGateInfo:
    case CST_InCharacterServerWaitTargetGameServerGateInfo:
    case CST_InGameServerWaitTargetGameServerGateInfo:
    case CST_InGameServerWaitTargetCharacterServerGateInfo:
        {
            MESSAGE_MAPPING_BEGIN
                MESSAGE_HANDLE_1( S2S_SWITCHGATE, S2SSwitchGate, _OnS2SSwitchGate)
            MESSAGE_MAPPING_END
        }
        break;
    case CST_InCharacterServer:
    case CST_InGameServer:
    case CST_InGameServerPlaying:
        {
            MESSAGE_MAPPING_BEGIN
                MESSAGE_HANDLE_1( MSG_SELECTCHANNEL_SS, MsgS2SSelectChannel, _OnMsgS2SSelectChannel)
                MESSAGE_HANDLE_1( GS2CS_SWITCHSTAGEREQ, GS2CSSwitchStageReq, _OnGS2CSSwitchStageReq)
            MESSAGE_MAPPING_END
        }
        break;
    default:
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "account[%u] 在 State[%d] 收到不应该的消息Message[%d]", GetAccountId(), /*GetLoginInfo().Sessionkey, */GetState(), msgType);
        }
        break;
    }
    return ER_Success;
}

void ClientPeer::_OnS2SSwitchGate( S2SSwitchGate* pMessage )
{
    unsigned long nServerId = _serverInfo.nServerId;

    switch ( _serverInfo.nServerType )
    { 
    case ST_LoginServer:
        {
            SqlMessage sqlMessage;
            if ( RESULT_SUCCESS( pMessage->nResult ) )
            {   
                sqlMessage.nMessageId = SqlMessage::ESM_CanLogin;
                sqlMessage.Guid       = _loginInfo.nAccountID;

                sprintf_s( sqlMessage.IpPort, sizeof(sqlMessage.IpPort)-1,"%s,%d" ,pMessage->szGateIP,pMessage->uGatePort);
                //theCenterServer.GetSqlService().PushResult( sqlMessage );

                SetLoginState( CST_NoState );
                SetState( CST_WaitLoginServer2CharacterServer );

                theClientPeerManager.UpdateClientPeer( this );
                theClientPeerManager.RemoveClientPeerFromLoginQueue( _loginInfo.nAccountID, false );

				CenterServer::GetInstance().SendMessageToLogin(pMessage);

				theGameServerManager.CheckQueue(theClientPeerManager.ClientPeerSize(),false);

				//printf("7,keylogin:send to login switch gate:%d\n",HQ_TimeGetTime());
            }
            else
            {// ER_NotGateServer
                sqlMessage.nMessageId = SqlMessage::ESM_NotGameServerService;
                sqlMessage.Guid       = _loginInfo.nAccountID;
                //theCenterServer.GetSqlService().PushResult( sqlMessage );

                theClientPeerManager.RemoveClientPeerFromLoginQueue( _loginInfo.nAccountID, true );
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] 得到GateServerIp Port 失败[%d]", _loginInfo.nAccountID, _loginInfo.szAccount, pMessage->nResult);
            }
        }
        break;
    case ST_CharacterServer:
        {
            GameServerPeer* pLocusGameServerPeer = theGameServerManager.GetGameServerPeer( nServerId );
            if ( !pLocusGameServerPeer )
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_OnSwitchGate not find CharacterServerPeer[%d]\n", nServerId );
                return;
            }
            switch ( GetState() )
            {
            case CST_InCharacterServerWaitTargetGameServerGateInfo:
                if ( RESULT_SUCCESS( pMessage->nResult ))
                {
                    SetState( CST_WaitCharacterServer2GameServer );
                }
                else
                {
                    SetState( CST_InCharacterServer );
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "_OnS2SSwitchGate To MapGameserver Result[%d]", pMessage->nResult );
                }
                break;
            default:
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "_OnS2SSwitchGate ST_CharacterServer State[%d] Result[%d]",  GetState(), pMessage->nResult );
                break;
            }

            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "第一次 S2SSwitchGate State[%d] Result[%d]",  GetState(), pMessage->nResult );
            S2SSwitchGate s2sSwitchGateMsg;
            s2sSwitchGateMsg.header.stID = GetCharDynamicId();
            s2sSwitchGateMsg.nResult     = pMessage->nResult;
            s2sSwitchGateMsg.uGatePort   = pMessage->uGatePort;
            strncpy_s( s2sSwitchGateMsg.szGateIP, sizeof( s2sSwitchGateMsg.szGateIP ), pMessage->szGateIP, sizeof(s2sSwitchGateMsg.szGateIP) - 1 );
            strncpy_s( s2sSwitchGateMsg.szChannelName, sizeof( s2sSwitchGateMsg.szChannelName ), pMessage->szChannelName, sizeof(s2sSwitchGateMsg.szChannelName) - 1 );
            s2sSwitchGateMsg.nTargetServerType = pMessage->nTargetServerType;
            s2sSwitchGateMsg.nTargetServerId   = pMessage->nTargetServerId;
            s2sSwitchGateMsg.dwMapID           = _stageReqInfo.nMapId;
            s2sSwitchGateMsg.fX                = _stageReqInfo.fX;
            s2sSwitchGateMsg.fY                = _stageReqInfo.fY;
            s2sSwitchGateMsg.fDir              = _stageReqInfo.fDir;
            pLocusGameServerPeer->Send( &s2sSwitchGateMsg );
        }
        break;
    case ST_GameServer:
        {
            GameServerPeer* pLocusGameServerPeer = theGameServerManager.GetGameServerPeer( nServerId );
            if ( !pLocusGameServerPeer )
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_OnSwitchGate not find GameServerPeer[%d]\n", nServerId );
                return;
            }

            S2SSwitchGate s2sSwitchGateMsg;
            s2sSwitchGateMsg.header.stID = GetCharDynamicId();
            s2sSwitchGateMsg.nResult     = pMessage->nResult;
            s2sSwitchGateMsg.uGatePort   = pMessage->uGatePort;
            strncpy_s( s2sSwitchGateMsg.szGateIP, sizeof( s2sSwitchGateMsg.szGateIP ), pMessage->szGateIP, sizeof(s2sSwitchGateMsg.szGateIP) - 1);
            strncpy_s( s2sSwitchGateMsg.szChannelName, sizeof( s2sSwitchGateMsg.szChannelName ), pMessage->szChannelName, sizeof(s2sSwitchGateMsg.szChannelName) - 1);
            s2sSwitchGateMsg.nTargetServerType = pMessage->nTargetServerType;;
            s2sSwitchGateMsg.nTargetServerId   = pMessage->nTargetServerId;

            // 防止角色重登陆由于数据库地图不同,而无法顶掉帐号 添加新地图ID入库
            s2sSwitchGateMsg.dwMapID = _stageReqInfo.nMapId;
            s2sSwitchGateMsg.fX      = _stageReqInfo.fX;
            s2sSwitchGateMsg.fY      = _stageReqInfo.fY;
            s2sSwitchGateMsg.fDir    = _stageReqInfo.fDir;

            switch ( GetState() )
            {
            case CST_InGameServerWaitTargetGameServerGateInfo:
                if ( RESULT_SUCCESS( pMessage->nResult ))
                {
                    SetState( CST_WaitGameServer2GameServer );
                }
                else
                {   
                    SetState( CST_InGameServer );
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_OnS2SSwitchGate To MapGameserver Result[%d]", pMessage->nResult );
                }
                break;
            case CST_InGameServerWaitTargetCharacterServerGateInfo:                
                if ( RESULT_SUCCESS( pMessage->nResult ))
                {
                    SetState( CST_WaitGameServer2CharacterServer );
                    s2sSwitchGateMsg.nTargetServerType = ST_CharacterServer;
                }
                else
                {
                    SetState( CST_InGameServer );
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "_OnS2SSwitchGate To LoginGameserver Result[%d]", pMessage->nResult );
                }
                break;
            default:
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "_OnS2SSwitchGate ST_GameServer State[%d] Result[%d]",  GetState(), pMessage->nResult );
                return;
                break;
            }

            pLocusGameServerPeer->Send( &s2sSwitchGateMsg );
        }
        break;
    }
}

void ClientPeer::_OnGS2CSSwitchStageReq( GS2CSSwitchStageReq* pMessage )
{
    unsigned long nServerId        = pMessage->nServerId;
    unsigned long nCharDynamicDBId = pMessage->header.stID;
    unsigned long nAccountId       = pMessage->nAccountId;
    unsigned long nCharDbId        = pMessage->nCharacterDbId;
    short         stWhichSlot      = pMessage->stWhichSlot;
    unsigned long nMapId           = pMessage->nMapId;
    float         x                = pMessage->fX;
    float         y                = pMessage->fY;
    float         dir              = pMessage->fDir;
    DWORD         dwTime           = pMessage->dwTime;

    CS2GSSwitchStageAck ssamsg;
    ssamsg.header.stID = pMessage->header.stID;
    ssamsg.nResult     = ER_Success;
    ssamsg.nAccountId  = nAccountId;
    ssamsg.nCharDBId   = pMessage->nCharacterDbId;
    ssamsg.stWhichSlot = stWhichSlot;
    ssamsg.dwTime      = dwTime;
    ssamsg.nMapId      = nMapId;
    ssamsg.fX          = x;
    ssamsg.fY          = y; 
    ssamsg.fDir        = dir;
    ssamsg.dwTeamSessionId = theCenterTeamManager.GetMemberSessionID(nCharDbId);

    // 现在所在的GameServer
    GameServerPeer* pLocusGameServerPeer = theGameServerManager.GetGameServerPeer( _serverInfo.nServerId );
    if ( !pLocusGameServerPeer )
    {        
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "_HandleEnterWorld ClientPeer 所在GameServer[%d]不存在", _serverInfo.nServerId );
        return;
    }

    switch ( pMessage->nSwitchStageType )
    {
    case SSRT_EnterGameWorld:
        {
            switch ( GetState() )
            {
            case CST_InCharacterServer:
                { // 已经连到专门用于选择人物进入游戏的GameServer 此服务器一定没有玩家需要的地图（空地图服务器）
                    SetCharDbId( nCharDbId );

					ProcessPreDataLogin();

                    unsigned short nResult = _HandleEnterWorld( pLocusGameServerPeer, pMessage );
                    if ( nResult != ER_Success )
                    {
                        ssamsg.nResult = nResult;
                        pLocusGameServerPeer->Send( &ssamsg );
                    }
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "accountId[%d][%d] 客户端作弊修改了协议 1", pMessage->nAccountId,GetState() );
                // ToDo
                // 踢掉已经在GameServer上的ClientPeer
                break;
            }
        }
        break;
    case SSRT_EnterGameServerMap:
        {
            switch ( GetState() )
            {
            case CST_InGameServer:
                { // 玩家登录目标GameServer 此服务器一定拥有玩家需要的地图
                    if ( pMessage->nCharacterDbId != GetCharDbId())
                    {   
                        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "客户端作弊修改了协议 SSRT_EnterTheMapGameServer CST_InMapGameServer[%d]", pMessage->nAccountId );
                        return;
                    }

                    unsigned short nResult = _HandleEnterMapGameServer( pLocusGameServerPeer, pMessage );
                    if ( nResult != ER_Success )
                    {
                        ssamsg.nResult = nResult;
                        pLocusGameServerPeer->Send( &ssamsg );
                    }
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING,"accountId[%d][%d] 客户端作弊修改了协议 2", pMessage->nAccountId,GetState() );
                // ToDo
                // 踢掉已经在GameServer上的ClientPeer
                break;
            }
        }
        break;
    case SSRT_FlyToMap:
        {
            switch ( GetState() )
            {
            case CST_InGameServerPlaying:
                {
                    unsigned short nResult = _HandleFlyToMap( pLocusGameServerPeer, pMessage ); 
                    if ( nResult != ER_Success )
                    {
                        ssamsg.nResult = nResult;
                        pLocusGameServerPeer->Send( &ssamsg );
                    }
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "accountId[%d][%d] 客户端作弊修改了协议 3", pMessage->nAccountId,GetState() );
                // ToDo
                // 踢掉已经在GameServer上的ClientPeer
                return;
                break;
            }
        }
        break;
	case SSRT_CHANGECHANNEL:
		{
			switch ( GetState() )
			{
			case CST_InGameServerPlaying:
				{
					unsigned short nResult = _HandleChangeChannel( pLocusGameServerPeer, pMessage ); 
					if ( nResult != ER_Success )
					{
						ssamsg.nResult = nResult;
						pLocusGameServerPeer->Send( &ssamsg );
					}
				}
				break;
			default:
				LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "accountId[%d][%d] 客户端作弊修改了协议 3", pMessage->nAccountId,GetState() );
				// ToDo
				// 踢掉已经在GameServer上的ClientPeer
				return;
				break;
			}
		}
		break;
    case SSRT_EnterToCharacterLogin:
        {
            switch ( GetState() )
            {
            case CST_InGameServerPlaying:
                {
                    unsigned short nResult = _HandleEnterCharacterLogin( pLocusGameServerPeer, pMessage );    
                    if ( nResult != ER_Success )
                    {
                        ssamsg.nResult = nResult;
                        pLocusGameServerPeer->Send( &ssamsg );
                    }
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "accountId[%d][%d] 客户端作弊修改了协议 4", pMessage->nAccountId,GetState() );
                // ToDo
                // 踢掉已经在GameServer上的ClientPeer
                return;
                break;
            }
        }
        break;
    default:
        break;
    }
}
/*
 @brief:客户端切换频道,即切换服务器
*/
void ClientPeer::_OnMsgS2SSelectChannel( MsgS2SSelectChannel* pMessage )
{
    GameServerPeer* pLocusGameServerPeer = theGameServerManager.GetGameServerPeer( _serverInfo.nServerId );
    if ( !pLocusGameServerPeer )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_OnMsgS2SSelectChannel ClientPeer 所在GameServer[%d]不存在了",  GetServerInfo().nServerId );
        return;
    }   

    if ( _serverInfo.nServerId == pMessage->channel.nServerId)
    { // 就在所选的GameServer上        
        CS2GSSwitchStageAck msg;
        msg.header.stID = GetCharDynamicId(); 
        msg.nResult     = ER_Success;
        msg.nAccountId  = _loginInfo.nAccountID;
        msg.nCharDBId   = _currentCharDbId;
        msg.stWhichSlot = _stWhichSlot;
        msg.dwTime      = HQ_TimeGetTime();
        msg.fX          = _stageReqInfo.fX;
        msg.fY          = _stageReqInfo.fY;
        msg.fDir        = _stageReqInfo.fDir;
        msg.nMapId      = _stageReqInfo.nMapId;
        msg.dwTeamSessionId = theCenterTeamManager.GetMemberSessionID(_currentCharDbId);


        switch ( GetState())
        {
        case CST_InCharacterServer:
            {
                msg.ucNeedTellClientCharInfo = BV_NeedTellClientCharInfo;

                if ( _stageReqInfo.bHaveInvalidInfo )
                    msg.ucNeedUseMessageMapInfo = BV_NeedUseMessageMapInfo;
                else
                    msg.ucNeedUseMessageMapInfo = BV_NotNeedUseMessageMapInfo;

                if (!_bIsHavePlayingInGameServer)
                {
                    SetRequeryLoginTime(0);
                }
                SetState( CST_InGameServerPlaying );
                _bIsHavePlayingInGameServer = true;
            }
            break;
        case CST_InGameServerPlaying:
            {
                msg.ucIsLocalFlyMap = BV_LocalFlyMap;
            }
            break;
        }
        pLocusGameServerPeer->Send( &msg );        
    }    
    else
    { // 在其他GameServer上
		pLocusGameServerPeer = theGameServerManager.GetGameServerPeer( pMessage->channel.nServerId);
		if ( !pLocusGameServerPeer )
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "请求的GameServer[%d]不存在了",pMessage->channel.nServerId);
			return;
		}

        GetStageReqInfo().nServerId = pMessage->channel.nServerId;

        CS2GSLoginInfo msg;
        msg.header.stID = GetCharDynamicId();        
        msg.nAccountID  = _loginInfo.nAccountID;
        //strncpy_s( msg.SessionKey, sizeof( msg.SessionKey ), _loginInfo.SessionKey, sizeof(msg.SessionKey) - 1);
		msg.SessionKey = _loginInfo.Sessionkey;
        msg.clientPeerInServerType = pMessage->nServerType;
        msg.nServerId   = pMessage->nServerId;
        strncpy_s( msg.szIP, sizeof( msg.szIP ),  _loginInfo.szIP, sizeof(msg.szIP) - 1 );
        strncpy_s( msg.szAccount, sizeof( msg.szAccount ), _loginInfo.szAccount, sizeof(msg.szAccount) - 1 );
        msg.isWallow    = _loginInfo.isWallow;
        switch ( GetState())
        {
        case CST_InCharacterServer:
            SetState( CST_InCharacterServerWaitTargetGameServerGateInfo );
            break;
        case CST_InGameServer:
		case CST_InGameServerPlaying:
            SetState( CST_InGameServerWaitTargetGameServerGateInfo );
			_stageReqInfo.bHaveInvalidInfo = true;
			//在游戏服务器中,就不是第一次进入游戏了
            break;
        }
        pLocusGameServerPeer->Send( &msg );             
    }
}

unsigned short ClientPeer::_HandleEnterWorld( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMsg, bool bCorrect /*= false*/ )
{   
    if ( pLocusGameServerPeer == NULL )
    { return ER_LocusGameServerNotExit;}

    unsigned long nServerId        = pMsg->nServerId;
    unsigned long nCharDynamicDBId = pMsg->header.stID;
    unsigned long nAccountId       = pMsg->nAccountId;
    unsigned long nCharDbId        = pMsg->nCharacterDbId;
    short         stWhichSlot      = pMsg->stWhichSlot;
    //unsigned long nMapId           = pMsg->nMapId;
    float         x                = pMsg->fX;
    float         y                = pMsg->fY;
    float         dir              = pMsg->fDir;
    DWORD         dwTime           = pMsg->dwTime;

    /*CS2GSSwitchStageAck ssamsg;
    ssamsg.header.stID = pMsg->header.stID;
    ssamsg.nResult     = ER_Success;
    ssamsg.nAccountId  = nAccountId;
    ssamsg.nCharDBId   = pMsg->nCharacterDbId;
    ssamsg.stWhichSlot = stWhichSlot;
    ssamsg.dwTime      = dwTime;
    ssamsg.nMapId      = nMapId;
    ssamsg.fX          = x;
    ssamsg.fY          = y; 
    ssamsg.fDir        = dir;
    ssamsg.dwTeamSessionId = theCenterTeamManager.GetMemberSessionID( nCharDbId );*/

    GameServerPeers gameServerPeers;
    theGameServerManager.GetGameServerPeerList( (ushort)EctypeId2MapId(pMsg->nMapId), true, gameServerPeers );    
    if ( gameServerPeers.empty() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "_HandleEnterWorld GetGameServerPeerList MapId[0x%x] 不存在 开始纠正 在GameServer[%d]上, GameServerCount(%d)", 
            pMsg->nMapId, _serverInfo.nServerId, theGameServerManager.GetGameServerSize());
        // 没有此GameStage,传送到重生点
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById((ushort)EctypeId2MapId(pMsg->nMapId));
        if ( pMapData != NULL && pMapData->IsEctypeMap() )  
        {
            // 如果是副本, 找到复活点
            //MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( true/*false*/ );
            //if ( pRelive != NULL )
            //{
            //    pMsg->nMapId = pRelive->MapId;
            //    pMsg->fX     = pRelive->PositionX;
            //    pMsg->fY     = pRelive->PositionY;				

            //    theGameServerManager.GetGameServerPeerList( pMsg->nMapId, true, gameServerPeers ); 
            //}

			const MapConfig::SpecRelivePosition* pSpecRelive = pMapData->GetSpecRelivePositionByCountry( pMsg->ustCountryID );
			if (pSpecRelive != NULL)
			{
				pMsg->nMapId = pSpecRelive->MapId;
				pMsg->fX     = pSpecRelive->PositionX;
				pMsg->fY     = pSpecRelive->PositionY;

				theGameServerManager.GetGameServerPeerList( pMsg->nMapId, true, gameServerPeers ); 
			}


        }

        // 为版本的更新错误做纠正
        if ( gameServerPeers.empty() )
        {
            const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( pMsg->ustCountryID );
            if ( pSetting != NULL )
            {
                pMsg->nMapId = pSetting->GetMapID();
                pMsg->fX     = pSetting->GetPosX();
                pMsg->fY     = pSetting->GetPosY();

                theGameServerManager.GetGameServerPeerList( pMsg->nMapId, true, gameServerPeers ); 
            }
        }

        if ( gameServerPeers.empty() )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_HandleEnterWorld GetGameServerPeerList MapId[0x%x] 不存在 在GameServer[%d]上", pMsg->nMapId, _serverInfo.nServerId );
            return ER_GameServerNotExist;
        }
    }

    if ( gameServerPeers.size() == 1 )
    {  // 只有一个服务器有这个地图
        GameServerPeer* pTargetGameServerPeer = gameServerPeers.front();        
        if ( !pTargetGameServerPeer )
            return ER_SystemException;

        if ( _serverInfo.nServerId == pTargetGameServerPeer->GetId())
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "角色服务器 不能作为地图游戏服务器");
            return ER_CharacterServerCantBeGameServer;
        }

        // 目标GameServer和所在GameServer不一样
        if ( !pTargetGameServerPeer->IsCanLogin() )
            return ER_MapGameServerPlayerIsFull;

        _stageReqInfo.nServerId         = pTargetGameServerPeer->GetId();
        _stageReqInfo.nMapId            = pMsg->nMapId;
        _stageReqInfo.fX                = pMsg->fX;
        _stageReqInfo.fY                = pMsg->fY;            
        _stageReqInfo.fDir              = pMsg->fDir;
        _stageReqInfo.bHaveInvalidInfo  = bCorrect;

        // 给目标MapGameServer发信息
        CS2GSLoginInfo limsg;
        limsg.header.stID = GetCharDynamicId();
        limsg.nAccountID  = _loginInfo.nAccountID;
        //strncpy_s( limsg.SessionKey, sizeof( limsg.SessionKey ),  _loginInfo.SessionKey, sizeof(limsg.SessionKey) - 1 );
		limsg.SessionKey = _loginInfo.Sessionkey;		
        limsg.clientPeerInServerType = ST_CharacterServer;
        limsg.nServerId   = _serverInfo.nServerId;
        strncpy_s( limsg.szIP,     sizeof( limsg.szIP ), _loginInfo.szIP,      sizeof(limsg.szIP) - 1    );
        strncpy_s( limsg.szAccount, sizeof( limsg.szAccount ), _loginInfo.szAccount, sizeof(limsg.szAccount) - 1);

        //strncpy_s( limsg.Password,  sizeof(limsg.Password),  _loginInfo.Password,  sizeof(limsg.Password) - 1 );
        /*strncpy_s( limsg.Seed,      sizeof(limsg.Seed),      _loginInfo.Seed,      sizeof(limsg.Seed) - 1     );*/
        limsg.isWallow    = _loginInfo.isWallow;

        pTargetGameServerPeer->Send( &limsg );
        SetState( CST_InCharacterServerWaitTargetGameServerGateInfo );
    }
    else
    { // 很多

		//只有副本允许很多
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById((ushort)EctypeId2MapId(pMsg->nMapId));
		if ( pMapData != NULL && pMapData->IsEctypeMap() )  
		{
			// 如果是副本, 找到复活点
			const MapConfig::SpecRelivePosition* pSpecRelive = pMapData->GetSpecRelivePositionByCountry( pMsg->ustCountryID );
			if (pSpecRelive != NULL)
			{
				pMsg->nMapId = pSpecRelive->MapId;
				pMsg->fX     = pSpecRelive->PositionX;
				pMsg->fY     = pSpecRelive->PositionY;

				theGameServerManager.GetGameServerPeerList( pMsg->nMapId, true, gameServerPeers ); 
			}
			else
			{
				MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( true/*false*/ );
				if ( pRelive != NULL )
				{
					pMsg->nMapId = pRelive->MapId;
					pMsg->fX     = pRelive->PositionX;
					pMsg->fY     = pRelive->PositionY;

					theGameServerManager.GetGameServerPeerList( pMsg->nMapId, true, gameServerPeers ); 
				}
			}
			// 为版本的更新错误做纠正
			if ( gameServerPeers.empty() )
			{
				const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( pMsg->ustCountryID );
				if ( pSetting != NULL )
				{
					pMsg->nMapId = pSetting->GetMapID();
					pMsg->fX     = pSetting->GetPosX();
					pMsg->fY     = pSetting->GetPosY();

					theGameServerManager.GetGameServerPeerList( pMsg->nMapId, true, gameServerPeers ); 
				}
			}

			if ( gameServerPeers.empty() )
			{
				LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_HandleEnterWorld GetGameServerPeerList MapId[0x%x] 不存在 在GameServer[%d]上", pMsg->nMapId, _serverInfo.nServerId );
				return ER_GameServerNotExist;
			}

			if (gameServerPeers.size() == 1)
			{
				GameServerPeer* pTargetGameServerPeer = gameServerPeers.front();        
				if ( !pTargetGameServerPeer )
					return ER_SystemException;

				if ( _serverInfo.nServerId == pTargetGameServerPeer->GetId())
				{
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "角色服务器 不能作为地图游戏服务器");
					return ER_CharacterServerCantBeGameServer;
				}

				// 目标GameServer和所在GameServer不一样
				if ( !pTargetGameServerPeer->IsCanLogin() )
					return ER_MapGameServerPlayerIsFull;

				_stageReqInfo.nServerId         = pTargetGameServerPeer->GetId();
				_stageReqInfo.nMapId            = pMsg->nMapId;
				_stageReqInfo.fX                = pMsg->fX;
				_stageReqInfo.fY                = pMsg->fY;            
				_stageReqInfo.fDir              = pMsg->fDir;
				_stageReqInfo.bHaveInvalidInfo  = bCorrect;

				// 给目标MapGameServer发信息
				CS2GSLoginInfo limsg;
				limsg.header.stID = GetCharDynamicId();
				limsg.nAccountID  = _loginInfo.nAccountID;				
				limsg.SessionKey = _loginInfo.Sessionkey;		
				limsg.clientPeerInServerType = ST_CharacterServer;
				limsg.nServerId   = _serverInfo.nServerId;
				strncpy_s( limsg.szIP,     sizeof( limsg.szIP ), _loginInfo.szIP,      sizeof(limsg.szIP) - 1    );
				strncpy_s( limsg.szAccount, sizeof( limsg.szAccount ), _loginInfo.szAccount, sizeof(limsg.szAccount) - 1);
				limsg.isWallow    = _loginInfo.isWallow;

				pTargetGameServerPeer->Send( &limsg );
				SetState( CST_InCharacterServerWaitTargetGameServerGateInfo );
			}
		}
		else if(pMapData&&!pMapData->IsEctypeMap())
		{
			MsgChannelInfo cimsg;
			cimsg.header.stID = GetCharDynamicId();
			cimsg.nMapId = pMsg->nMapId;

			GameServerPeers::iterator it = gameServerPeers.begin();
			for ( ; it!=gameServerPeers.end(); ++it )
			{
				GameServerPeer* pGameServerPeer = *it;
				if ( !pGameServerPeer)
					continue;

				SChannelInfo channelInfo;
				strncpy_s( channelInfo.szChannelName, sizeof( channelInfo.szChannelName ), pGameServerPeer->GetName().c_str(), sizeof(channelInfo.szChannelName)-1 );
				channelInfo.nServerId = pGameServerPeer->GetId();
				channelInfo.chChannelStatus = GetChannelStatus(pGameServerPeer->GetClientSize());
				if ( !cimsg.AddChannelInfo( channelInfo ) )
				{
					pLocusGameServerPeer->Send( &cimsg );
					cimsg.Reset();
				}
			}

			if ( cimsg.nChannelsCount != 0)
				pLocusGameServerPeer->Send( &cimsg );

			// 可能要去的地图信息
			_stageReqInfo.nServerId = INVALID_SERVERID;
			_stageReqInfo.nMapId    = pMsg->nMapId;
			_stageReqInfo.fX        = pMsg->fX;
			_stageReqInfo.fY        = pMsg->fY;
			_stageReqInfo.fDir      = pMsg->fDir;
		}       
    }

    return ER_Success;
}

unsigned short ClientPeer::_HandleEnterMapGameServer( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage )
{
    if ( pLocusGameServerPeer == NULL )
    {        
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_HandleEnterWorld ClientPeer 所在GameServer[%d]不存在", _serverInfo.nServerId );
        return ER_LocusGameServerNotExit;
    }

    unsigned long nServerId        = pMessage->nServerId;
    unsigned long nCharDynamicDBId = pMessage->header.stID;
    unsigned long nAccountId       = pMessage->nAccountId;
    unsigned long nCharDbId        = pMessage->nCharacterDbId;
    short         stWhichSlot      = pMessage->stWhichSlot;
    unsigned long nMapId           = pMessage->nMapId;
    float         x                = pMessage->fX;
    float         y                = pMessage->fY;
    float         dir              = pMessage->fDir;
    DWORD         dwTime           = pMessage->dwTime;

    CS2GSSwitchStageAck ssamsg;
    ssamsg.header.stID = pMessage->header.stID;
    ssamsg.nResult     = ER_Success;
    ssamsg.nAccountId  = nAccountId;
    ssamsg.nCharDBId   = pMessage->nCharacterDbId;
    ssamsg.stWhichSlot = stWhichSlot;
    ssamsg.dwTime      = dwTime;
    ssamsg.nMapId      = nMapId;
    ssamsg.fX          = x;
    ssamsg.fY          = y; 
    ssamsg.fDir        = dir;
    ssamsg.dwTeamSessionId = theCenterTeamManager.GetMemberSessionID( nCharDbId );


    if ( _stageReqInfo.nServerId != pMessage->nServerId )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "玩家登录的GameServer和他所要切的目标GamServer不一样 [%d]:[%d]\n", _stageReqInfo.nServerId,  nServerId );
        return ER_ErrorTargetMapGameServerId;
    }

    ssamsg.nResult = ER_Success;
    if ( _stageReqInfo.bHaveInvalidInfo )
    {
        ssamsg.nMapId                  = _stageReqInfo.nMapId;
        ssamsg.fX                      = _stageReqInfo.fX;
        ssamsg.fY                      = _stageReqInfo.fY;
        ssamsg.fDir                    = _stageReqInfo.fDir;
        ssamsg.ucNeedUseMessageMapInfo = BV_NeedUseMessageMapInfo;
    }   
    else
    {
        ssamsg.ucNeedUseMessageMapInfo = BV_NotNeedUseMessageMapInfo;
    }

    if ( _bIsHavePlayingInGameServer )
        ssamsg.ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
    else
        ssamsg.ucNeedTellClientCharInfo = BV_NeedTellClientCharInfo;

    pLocusGameServerPeer->Send( &ssamsg );

    if (!_bIsHavePlayingInGameServer)
    {
        SetRequeryLoginTime(0);
    }
    SetState( CST_InGameServerPlaying );
    _bIsHavePlayingInGameServer = true;
    ResetStageReqInfo();

    // 如果刚上线,还保留了队伍,这里同步给客户端
    //theCenterTeamManager.ClearTeamOntLineTime( nCharDbId );

    return ER_Success;
}

unsigned short ClientPeer::_HandleEnterCharacterLogin( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage )
{
    if ( pLocusGameServerPeer == NULL )
    { return ER_LocusGameServerNotExit; }

    GameServerPeer* pGameServerPeer = theGameServerManager.GetCharacterServerPeer();
    if ( NULL == pGameServerPeer )
    { return ER_CharacterServerNotExit;}

    if ( !pGameServerPeer->IsCanLogin())
    {  return ER_CharacterServerPlayerIsFull; }
    
    CS2GSLoginInfo msg;
    msg.header.stID = GetCharDynamicId();
    msg.nAccountID  = _loginInfo.nAccountID;
    msg.clientPeerInServerType = _serverInfo.nServerType;
    msg.nServerId   = _serverInfo.nServerId;
    strncpy_s( msg.szIP, sizeof( msg.szIP ), _loginInfo.szIP, sizeof(msg.szIP)-1);

#ifdef __NEW_LOGIN__
    //strncpy_s( msg.SessionKey, sizeof(msg.SessionKey), _loginInfo.SessionKey,  sizeof(msg.SessionKey )-1 );

    //strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  _loginInfo.szAccount,   sizeof(msg.szAccount)-1   );
    //strncpy_s( msg.Password,   sizeof(msg.Password),   _loginInfo.Password,    sizeof(msg.Password)-1    );
    //strncpy_s( msg.Seed ,      sizeof(msg.Seed),       _loginInfo.Seed ,       sizeof(msg.Seed)-1        );
#endif
	strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  _loginInfo.szAccount,   sizeof(msg.szAccount)-1   );
	msg.SessionKey = _loginInfo.Sessionkey;
    msg.isWallow    = _loginInfo.isWallow;

    pGameServerPeer->Send( &msg );
    
    SetState( CST_InGameServerWaitTargetCharacterServerGateInfo ); // 设置ClientPeer状态
    return ER_Success;
}

unsigned short ClientPeer::_HandleFlyToMap( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage )
{ 
    if ( pLocusGameServerPeer == NULL )
    {        
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_HandleFlyToMap ClientPeer 所在GameServer[%d]不存在", _serverInfo.nServerId );
        return ER_LocusGameServerNotExit;
    }

    unsigned long nServerId        = pMessage->nServerId;
    unsigned long nCharDynamicDBId = pMessage->header.stID;
    unsigned long nAccountId       = pMessage->nAccountId;
    unsigned long nCharDbId        = pMessage->nCharacterDbId;
    short         stWhichSlot      = pMessage->stWhichSlot;
    unsigned long nMapId           = pMessage->nMapId;
    float         x                = pMessage->fX;
    float         y                = pMessage->fY;
    float         dir              = pMessage->fDir;
    DWORD         dwTime           = pMessage->dwTime;

    CS2GSSwitchStageAck ssamsg;
    ssamsg.header.stID = pMessage->header.stID;
    ssamsg.nResult     = ER_Success;
    ssamsg.nAccountId  = nAccountId;
    ssamsg.nCharDBId   = pMessage->nCharacterDbId;
    ssamsg.stWhichSlot = stWhichSlot;
    ssamsg.dwTime      = dwTime;
    ssamsg.nMapId      = nMapId;
    ssamsg.fX          = x;
    ssamsg.fY          = y; 
    ssamsg.fDir        = dir;
    ssamsg.dwTeamSessionId = theCenterTeamManager.GetMemberSessionID(nCharDbId);

    GameServerPeers gameServerPeers;
    theGameServerManager.GetGameServerPeerList( pMessage->nMapId, true, gameServerPeers);    
    if ( gameServerPeers.empty() )
        return ER_ErrorTargetMapGameServerId;

    if ( gameServerPeers.size() == 1)
    {  // 只有一个服务器有这个地图
        GameServerPeer* pTargetGameServerPeer = gameServerPeers.front();        
        if ( !pTargetGameServerPeer )
            return ER_SystemException;

        if ( _serverInfo.nServerId == pTargetGameServerPeer->GetId())
        { // 目标GameServer和所在GameServer一样
            switch ( GetState() )
            {
            case CST_InGameServerPlaying:
                {
                    ssamsg.ucIsLocalFlyMap = BV_LocalFlyMap;
                    pTargetGameServerPeer->Send( &ssamsg );
                }
                break;
            default:
                {
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_HandleFlyToMap 1 Server Error State[%d]\n", GetState() );
                }
                break;
            }
        }
        else
        { // 目标GameServer和所在GameServer不一样
            if ( !pTargetGameServerPeer->IsCanLogin() )
                return ER_MapGameServerPlayerIsFull;

            _stageReqInfo.nServerId = pTargetGameServerPeer->GetId();
            _stageReqInfo.nMapId    = pMessage->nMapId;
            _stageReqInfo.fX        = pMessage->fX;
            _stageReqInfo.fY        = pMessage->fY;            
            _stageReqInfo.fDir      = pMessage->fDir;
            _stageReqInfo.bHaveInvalidInfo = true;

            // 给目标GameServer发信息
            CS2GSLoginInfo limsg;
            limsg.header.stID = GetCharDynamicId();
            limsg.nAccountID  = _loginInfo.nAccountID;

            //strncpy_s( limsg.SessionKey, sizeof( limsg.SessionKey ), _loginInfo.SessionKey, sizeof(limsg.SessionKey) - 1 );
			limsg.SessionKey = _loginInfo.Sessionkey;
            //strncpy_s( limsg.Password,  sizeof(limsg.Password),  _loginInfo.Password,  sizeof(limsg.Password) - 1 );
			//strncpy_s( limsg.Seed,      sizeof(limsg.Seed),      _loginInfo.Seed,      sizeof(limsg.Seed) - 1     );

            limsg.clientPeerInServerType = ST_GameServer;
            limsg.nServerId   = _serverInfo.nServerId;
            strncpy_s( limsg.szIP, sizeof( limsg.szIP ), _loginInfo.szIP, sizeof(limsg.szIP) - 1);
            strncpy_s( limsg.szAccount, sizeof( limsg.szAccount ), _loginInfo.szAccount, sizeof(limsg.szAccount) - 1 );
            limsg.isWallow    = _loginInfo.isWallow;

            pTargetGameServerPeer->Send( &limsg );

            switch( GetState() )
            {
            case CST_InGameServerPlaying:
                {   
                    SetState( CST_InGameServerWaitTargetGameServerGateInfo );
                }
                break;
            default:
                {
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_HandleFlyToMap 2 Error State[%d]\n", GetState() );
                }
                break;
            }
        }
    }
    else
    { // 很多
        MsgChannelInfo cimsg;
        cimsg.header.stID = GetCharDynamicId();
        cimsg.nMapId = pMessage->nMapId;

        GameServerPeers::iterator it = gameServerPeers.begin();
        for ( ; it!=gameServerPeers.end(); ++it )
        {
            GameServerPeer* pGameServerPeer = *it;
            if ( !pGameServerPeer)
                continue;

            SChannelInfo channelInfo;
            strncpy_s( channelInfo.szChannelName, sizeof( channelInfo.szChannelName ), pGameServerPeer->GetName().c_str(), sizeof(channelInfo.szChannelName)-1 );
            channelInfo.nServerId = pGameServerPeer->GetId();
			channelInfo.chChannelStatus = GetChannelStatus(pGameServerPeer->GetClientSize());
            if ( !cimsg.AddChannelInfo( channelInfo ) )
            {
                pLocusGameServerPeer->Send( &cimsg );
                cimsg.Reset();
            }
        }

        if ( cimsg.nChannelsCount != 0)
            pLocusGameServerPeer->Send( &cimsg );

        // 可能要去的地图信息
        _stageReqInfo.nServerId = INVALID_SERVERID;
        _stageReqInfo.nMapId = pMessage->nMapId;
        _stageReqInfo.fX     = pMessage->fX;
        _stageReqInfo.fY     = pMessage->fY;
        _stageReqInfo.fDir   = pMessage->fDir;
    }
    return ER_Success;
}

unsigned short ClientPeer::_HandleChangeChannel( GameServerPeer* pLocusGameServerPeer, GS2CSSwitchStageReq* pMessage )
{
	if ( pLocusGameServerPeer == NULL )
	{        
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "_HandleChangeChannel ClientPeer 所在GameServer[%d]不存在", _serverInfo.nServerId );
		return ER_LocusGameServerNotExit;
	}

	unsigned long nServerId        = pMessage->nServerId;
	unsigned long nCharDynamicDBId = pMessage->header.stID;
	unsigned long nAccountId       = pMessage->nAccountId;
	unsigned long nCharDbId        = pMessage->nCharacterDbId;
	short         stWhichSlot      = pMessage->stWhichSlot;
	unsigned long nMapId           = pMessage->nMapId;
	float         x                = pMessage->fX;
	float         y                = pMessage->fY;
	float         dir              = pMessage->fDir;
	DWORD         dwTime           = pMessage->dwTime;

	CS2GSSwitchStageAck ssamsg;
	ssamsg.header.stID = pMessage->header.stID;
	ssamsg.nResult     = ER_Success;
	ssamsg.nAccountId  = nAccountId;
	ssamsg.nCharDBId   = pMessage->nCharacterDbId;
	ssamsg.stWhichSlot = stWhichSlot;
	ssamsg.dwTime      = dwTime;
	ssamsg.nMapId      = nMapId;
	ssamsg.fX          = x;
	ssamsg.fY          = y; 
	ssamsg.fDir        = dir;
	ssamsg.dwTeamSessionId = theCenterTeamManager.GetMemberSessionID(nCharDbId);

	GameServerPeers gameServerPeers;
	theGameServerManager.GetGameServerPeerList( pMessage->nMapId, true, gameServerPeers);    
	if ( gameServerPeers.empty() )
		return ER_ErrorTargetMapGameServerId;

	if ( gameServerPeers.size() == 1)
	{  // 只有一个服务器有这个地图
		GameServerPeer* pTargetGameServerPeer = gameServerPeers.front();        
		if ( !pTargetGameServerPeer )
			return ER_SystemException;

		if ( _serverInfo.nServerId == pTargetGameServerPeer->GetId())
		{ // 目标GameServer和所在GameServer一样
			switch ( GetState() )
			{
			case CST_InGameServerPlaying:
				{
					ssamsg.ucIsLocalFlyMap = BV_LocalFlyMap;
					pTargetGameServerPeer->Send( &ssamsg );
				}
				break;
			default:
				{
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_HandleChangeChannel 1 Server Error State[%d]\n", GetState() );
				}
				break;
			}
		}
		else
		{ // 目标GameServer和所在GameServer不一样
			if ( !pTargetGameServerPeer->IsCanLogin() )
				return ER_MapGameServerPlayerIsFull;

			_stageReqInfo.nServerId = pTargetGameServerPeer->GetId();
			_stageReqInfo.nMapId    = pMessage->nMapId;
			_stageReqInfo.fX        = pMessage->fX;
			_stageReqInfo.fY        = pMessage->fY;            
			_stageReqInfo.fDir      = pMessage->fDir;
			_stageReqInfo.bHaveInvalidInfo = true;

			// 给目标GameServer发信息
			CS2GSLoginInfo limsg;
			limsg.header.stID = GetCharDynamicId();
			limsg.nAccountID  = _loginInfo.nAccountID;
			limsg.SessionKey = _loginInfo.Sessionkey;
			limsg.clientPeerInServerType = ST_GameServer;
			limsg.nServerId   = _serverInfo.nServerId;
			strncpy_s( limsg.szIP, sizeof( limsg.szIP ), _loginInfo.szIP, sizeof(limsg.szIP) - 1);
			strncpy_s( limsg.szAccount, sizeof( limsg.szAccount ), _loginInfo.szAccount, sizeof(limsg.szAccount) - 1 );
			limsg.isWallow    = _loginInfo.isWallow;

			pTargetGameServerPeer->Send( &limsg );

			switch( GetState() )
			{
			case CST_InGameServerPlaying:
				{   
					SetState( CST_InGameServerWaitTargetGameServerGateInfo );
				}
				break;
			default:
				{
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_HandleChangeChannel 2 Error State[%d]\n", GetState() );
				}
				break;
			}
		}
	}
	else
	{ // 很多
		GameServerPeer* pGameServer = NULL;
		GameServerPeers::iterator it = gameServerPeers.begin();
		for ( ; it!=gameServerPeers.end(); ++it )
		{
			pGameServer = *it;
			if ( !pGameServer)
				continue;
			if (pGameServer->GetId() == pMessage->nTargetServerId)
			{
				break;
			}
		}

		if (!pGameServer)
			return ER_SystemException;

		if ( !pGameServer->IsCanLogin() )
			return ER_MapGameServerPlayerIsFull;

		// 可能要去的地图信息
		_stageReqInfo.nServerId = pGameServer->GetId();
		_stageReqInfo.nMapId    = pMessage->nMapId;
		_stageReqInfo.fX        = pMessage->fX;
		_stageReqInfo.fY        = pMessage->fY;            
		_stageReqInfo.fDir      = pMessage->fDir;
		_stageReqInfo.bHaveInvalidInfo = true;

		// 给目标GameServer发信息
		CS2GSLoginInfo limsg;
		limsg.header.stID = GetCharDynamicId();
		limsg.nAccountID  = _loginInfo.nAccountID;		
		limsg.SessionKey = _loginInfo.Sessionkey;
		limsg.clientPeerInServerType = ST_GameServer;
		limsg.nServerId   = _serverInfo.nServerId;
		strncpy_s( limsg.szIP, sizeof( limsg.szIP ), _loginInfo.szIP, sizeof(limsg.szIP) - 1);
		strncpy_s( limsg.szAccount, sizeof( limsg.szAccount ), _loginInfo.szAccount, sizeof(limsg.szAccount) - 1 );
		limsg.isWallow    = _loginInfo.isWallow;
		pGameServer->Send( &limsg );

		switch( GetState() )
		{
		case CST_InGameServerPlaying:
			{   
				SetState( CST_InGameServerWaitTargetGameServerGateInfo );
			}
			break;
		default:
			{
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_HandleChangeChannel 3 Error State[%d]\n", GetState() );
			}
			break;
		}
	}
	return ER_Success;
}

void ClientPeer::ChangeServerInfo( const SServerInfo& si)
{ 
#ifdef _DEBUG
		printf("%s %d %d\n",__FUNCTION__,__LINE__,si.nServerId);
#endif
    if ( _serverInfo.nServerType == si.nServerType && _serverInfo.nServerId == si.nServerId  )
        return;
    
    LoginServerPeer* pOldLoginServer = NULL;
    GameServerPeer*  pOldGameServer  = NULL;

    switch( _serverInfo.nServerType)
    {
    case ST_LoginServer:
        {
            pOldLoginServer = LoginServerManager::GetInstance().GetLoginServerPeer( _serverInfo.nServerId );
        }
        break;
    case ST_GameServer:
    case ST_CharacterServer:
        {
            pOldGameServer = theGameServerManager.GetGameServerPeer( _serverInfo.nServerId );
        }
        break;
    }

    LoginServerPeer* pNewLoginServer = NULL;
    GameServerPeer*  pNewGameServer  = NULL;
    
    switch( si.nServerType)
    {
    case ST_LoginServer:
        {
            pNewLoginServer = LoginServerManager::GetInstance().GetLoginServerPeer( si.nServerId );
        }
        break;
    case ST_GameServer:
    case ST_CharacterServer:
        {
            pNewGameServer = theGameServerManager.GetGameServerPeer( si.nServerId );
        }
        break;
    }
    
    if ( pOldLoginServer)
        pOldLoginServer->RemoveAccountId( _loginInfo.nAccountID );
    if ( pOldGameServer)
        pOldGameServer->RemoveAccountId( _loginInfo.nAccountID );

    if ( pNewLoginServer )
        pNewLoginServer->AddAccountId( _loginInfo.nAccountID );
    if ( pNewGameServer )
        pNewGameServer->AddAccountId( _loginInfo.nAccountID );

    _serverInfo = si;
}

void ClientPeer::OnSynInServerInfo( GS2CSPlayerSynInServerInfo* pMessage )
{
    switch ( pMessage->ucStatus )
    {
    case GS2CSPlayerSynInServerInfo::ES_InMapStagePlaying:      // 进入游戏场景
    case GS2CSPlayerSynInServerInfo::ES_FirstInMapStagePlaying:
        {
            switch ( GetState() )
            {
            case CST_NoState:
                { // 被重置过
                    // 记录登陆信息
#ifdef _DEBUG
						printf("%s %d %d\n",__FUNCTION__,__LINE__,pMessage->serverInfo.nServerId);
#endif
                    SLoginInfoBase loginInfo = GetLoginInfo();
                    loginInfo.nAccountID  = pMessage->nAccountId;
                    loginInfo.LoginTime   = HQ_TimeGetTime();
                    SetLoginInfo( loginInfo );
                    SetCharDynamicId( pMessage->header.stID );

                    SServerInfo si;
                    si.nServerType = pMessage->serverInfo.nServerType;
                    si.nServerId   = pMessage->serverInfo.nServerId;
                    ChangeServerInfo( si );
                }
                break;
            }
            SetCharacterName( pMessage->szCharacterName );
        }
        break;
	case GS2CSPlayerSynInServerInfo::ES_OfflineStall:
		{
			SqlMessage sqlMessage;
			sqlMessage.nMessageId = SqlMessage::ESM_OfflineStall;
			sqlMessage.Guid       = _loginInfo.nAccountID;
			//CenterServer::GetInstance().GetSqlService().PushResult( sqlMessage );
		}
		break;
    default:            // 进入服务器 还没有进入游戏场景
        {
            switch ( GetState() )
            {
            case CST_NoState:
                { // 被重置过
                    // 记录登陆信息
                    SLoginInfoBase loginInfo = GetLoginInfo();
                    loginInfo.nAccountID  = pMessage->nAccountId;
                    loginInfo.LoginTime   = HQ_TimeGetTime();
                    SetLoginInfo( loginInfo );
                    SetCharDynamicId( pMessage->header.stID );
                    SetState( CST_InGameServer );
                }
                break;
            case CST_WaitLoginServer2CharacterServer:
                { 
                    // 已经连到一台GameServer上 设置所在服务器信息
                    SServerInfo si;
                    si.nServerType = ST_CharacterServer;
                    si.nServerId   = pMessage->serverInfo.nServerId;
                    ChangeServerInfo( si );
                    SetCharDynamicId( pMessage->header.stID );
                    SetState( CST_InCharacterServer );

#ifdef __NEW_LOGIN__            
                    SqlMessage sqlMessage;
                    sqlMessage.nMessageId = SqlMessage::ESM_PlayerInGame;
                    sqlMessage.Guid       = _loginInfo.nAccountID;
                   // CenterServer::GetInstance().GetSqlService().PushResult( sqlMessage );
#endif
                    CenterServer::GetInstance().gGameWorldStatistics.loginClientPeer += 1;
                }
                break;
            case CST_WaitCharacterServer2GameServer:
                {
#ifdef _DEBUG
						printf("%s %d %d\n",__FUNCTION__,__LINE__,pMessage->serverInfo.nServerId);
					#endif
                    // 设置所在GameServer信息
                    SServerInfo si;
                    si.nServerType = ST_GameServer;
                    si.nServerId   = pMessage->serverInfo.nServerId;
                    ChangeServerInfo( si );
                    SetCharDynamicId( pMessage->header.stID  );
                    SetState( CST_InGameServer );
                }
                break;
            case CST_WaitGameServer2GameServer:
                {
#ifdef _DEBUG
						printf("%s %d %d\n",__FUNCTION__,__LINE__,pMessage->serverInfo.nServerId);
					#endif
                    // 设置所在GameServer信息
                    SServerInfo si;
                    si.nServerType = ST_GameServer;
                    si.nServerId   = pMessage->serverInfo.nServerId;
                    ChangeServerInfo( si );
                    SetCharDynamicId( pMessage->header.stID );
                    SetState( CST_InGameServer );
                }        
                break;

            case CST_WaitGameServer2CharacterServer:
                {
#ifdef _DEBUG
						printf("%s %d %d\n", __FUNCTION__,__LINE__,pMessage->serverInfo.nServerId);
#endif
                    ResetCharInfo();
                    SServerInfo si;
                    si.nServerType = ST_CharacterServer;
                    si.nServerId   = pMessage->serverInfo.nServerId;
                    ChangeServerInfo( si );
                    SetCharDynamicId( pMessage->header.stID );
                    SetState( CST_InCharacterServer );
                }
                break;
            default:
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "玩家信息有错误 OnPlayerLogin accountId[%d] state[%d] serverId[%d] clientIdInServer[%d]", _loginInfo.nAccountID, 
                    GetState(), pMessage->serverInfo.nServerId, pMessage->header.stID);
                // ToDo
                // 踢掉已经在GameServer上的ClientPeer        
                break;
            }
        }
        break;
    }
}

long ClientPeer::OnExitServer( unsigned char ucExitType )
{
    //小退在这里删除队伍, 退出游戏在 RemoveClientPeer 函数里删除
    if ( ucExitType == ET_ReturnCharacterServer )
    {
        theCenterTeamManager.RemoveMemberByID( GetCharDbId() );

        // 通知服务器, 下线了
        ProcessExitWorld();
    }

    switch ( GetServerInfo().nServerType )
    {
    case ST_LoginServer:
        {
            LoginServerPeer* pLoginServer = LoginServerManager::GetInstance().GetLoginServerPeer( GetServerInfo().nServerId );
            if ( pLoginServer)
            { pLoginServer->RemoveAccountId( GetAccountId());}
        }
        break;
    case ST_GameServer:
    case ST_CharacterServer:
        {
            GameServerPeer* pGameServerPeer = theGameServerManager.GetGameServerPeer( GetServerInfo().nServerId );
            if ( pGameServerPeer)
            { pGameServerPeer->RemoveAccountId( GetAccountId() );}
        }
        break;
    }

#ifdef _DEBUG
	printf("%s %d %d\n",__FUNCTION__,__LINE__,ErrorUnsignedLongID);
#endif
    GetServerInfo().nServerId = ErrorUnsignedLongID;
    return ER_Success;
}
void ClientPeer::ProcessPreDataLogin()
{
	// 目前来看 只有交际数据需要登陆准备 其他的都是一波发
	CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( GetCharDbId() );
	if ( pRelation == NULL )
	{ return; }
	pRelation->ProcessPreDataLogin();
		
}
void ClientPeer::ProcessLogin()
{//告诉character server帐号认证数据 by vvx 2012.11.22
    GameServerPeer* pGameServerPeer = theGameServerManager.GetCharacterServerPeer();
    if ( NULL == pGameServerPeer )
    { return; }

    if ( !pGameServerPeer->IsCanLogin())
    { return; }
    
    CS2GSLoginInfo msg;
    msg.header.stID            = GetCharDynamicId();
    msg.nAccountID             = _loginInfo.nAccountID;
    msg.clientPeerInServerType = _serverInfo.nServerType;
    msg.nServerId              = _serverInfo.nServerId;
    strncpy_s( msg.szIP,       sizeof( msg.szIP ),     _loginInfo.szIP,        sizeof(msg.szIP)-1)       ;
    //strncpy_s( msg.SessionKey, sizeof(msg.SessionKey), _loginInfo.SessionKey,  sizeof(msg.SessionKey )-1 );
	msg.SessionKey = _loginInfo.Sessionkey;
    strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  _loginInfo.szAccount,   sizeof(msg.szAccount)-1   );
    //strncpy_s( msg.Password,   sizeof(msg.Password),   _loginInfo.Password,    sizeof(msg.Password)-1    );
    //strncpy_s( msg.Seed ,      sizeof(msg.Seed),       _loginInfo.Seed ,       sizeof(msg.Seed)-1        );
    msg.isWallow               = _loginInfo.isWallow;
    pGameServerPeer->Send( &msg );

	//printf("3,keylogin:send login info to character server:%d\n",HQ_TimeGetTime());

    SetState( CST_InLoginQueueWaitGateInfo ); // 设置ClientPeer状态
    SetRequeryLoginTime(HQ_TimeGetTime());
	

    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] 向CharacterServer投递登录", _loginInfo.nAccountID, _loginInfo.szAccount);
}

void ClientPeer::ResetAccountInfo()
{
#ifdef _DEBUG
	printf("%s %d %d\n", __FUNCTION__,__LINE__,ErrorUnsignedLongID);
#endif
    memset( &_loginInfo, 0, sizeof(SLoginInfoBase));
    _loginState             = CST_NoState;
    
    _serverInfo.nServerType = ST_None;
    _serverInfo.nServerId   = ErrorUnsignedLongID;

    _IsHaveToken            = false;
    _ReqLoginTime           = 0;
}

void ClientPeer::ResetCharInfo()
{
    memset( _szCharacterName, 0, sizeof( _szCharacterName ));
    _charDynamicId   = -1;
    _currentCharDbId = InvalidLogicNumber;
    _stWhichSlot     = -1;
    _nStageId        = ErrorUnsignedLongID;
    _playState       = CST_NoState;
    _nLastMapId      = InvalidLogicNumber;
    ResetStageReqInfo();
    _bIsHavePlayingInGameServer = false;
    _organizeId                 = 0;
}

void ClientPeer::UpdateCountryOnlineCount( int nCount )
{
    if ( theCenterCountryManager.GetWeakCountry() != CountryDefine::Country_Init )
    { return; }

    CS2GSUpdateCountryOnLineCount xUpdate;
    xUpdate.uchCountryID = GetCountry();
    xUpdate.nCount       = nCount;
    theGameServerManager.SendMessageToCharacterServer( &xUpdate );
}

void ClientPeer::ProcessEnterWorld()
{
    // 同步国家在线人数给角色服务器
    UpdateCountryOnlineCount( 1 );
    // 组队

    // 关系
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( GetCharDbId() );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessEnterWorld();

    // 帮派
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pRelation->GetGuildID() );
    if ( pGuild )
    { pGuild->ProcessEnterWorld( GetCharDbId() ); }

	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByPlayerID( GetCharDbId() );
	if ( pFamily )
	{
		pFamily->ProcessEnterWorld( GetCharDbId() );
		pFamily->ProcessAllMemberOffline();
	}	
}

void ClientPeer::ProcessExitWorld()
{
    // 同步国家在线人数给角色服务器
    UpdateCountryOnlineCount( -1 );

    // 组队

    // 关系
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( GetCharDbId() );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessExitWorld();

        // 帮派
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pRelation->GetGuildID() );
    if ( pGuild )
    { pGuild->ProcessExitWorld( GetCharDbId() ); }

	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByPlayerID( GetCharDbId() );
	if ( pFamily )
	{
		pFamily->ProcessExitWorld( GetCharDbId() );
		pFamily->ProcessAllMemberOffline();
	}	

}

uint8 ClientPeer::GetChannelStatus(uint32 client_count)
{
	int temp = client_count/COUNT_PER;
	if (temp > Channel_StatusMax)
	{
		temp = Channel_StatusMax;
	}
	return temp;
}