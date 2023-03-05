#include "CenterServerNetEvent.h"
//#include "NetApi.h"
#include "GlobalDef.h"
#include "StageMonitor.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "XmlStringLanguage.h"
#include "RunStatus.h"
#include "TeamManager.h"
#include "Configure.h"
#include "RabotManager.h"
#include "DropItemManager.h"
#include "TradeCenterInfo.h"
#include "GamePlayer.h"
#include "ScriptVarMgr.h"
#include "LoginStage.h"
#include "ConfigReloader.h"
#include "application_config.h"

// disable: '<<' shift count negative or too big, undefined behavior
#pragma warning (disable : 4293)

// bool CenterServerNetEvent::OnDisconnect( TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo)
// {
//     GettheServer().SetCenterServerValidate( false );
//     LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "��CenterServer�Ͽ�����");
//     return true;
// }

long CenterServerNetEvent::OnProcessDefaultMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	//if (msgType == CS2GS_QUEUE_OP)
	//{
	//	_OnMsgQueueOp(pNetClient,(MsgCS2GSQueueOp*)pMessage);
	//	return ER_Success;
	//}
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( CS2GS_REGISTERGAMESERVERINFO_ACK,	CS2GSRegiseterGameserverInfoAck,	_OnRegiseterGameServerInfoAck );
        MESSAGE_HANDLE( UPDATEMAPINFO,						MessageUpdateMapInfo,				_OnMessageUpdateMapInfo       );
        MESSAGE_HANDLE( CS2GS_LOGININFO,					CS2GSLoginInfo,						_OnLoginInfo                  );
        MESSAGE_HANDLE( CS2GS_SWITCHSTAGEACK,				CS2GSSwitchStageAck,				_OnAckSwitchStage             );
        MESSAGE_HANDLE( S2S_SWITCHGATE,						S2SSwitchGate,						_OnS2SSwitchGate              );
        MESSAGE_HANDLE( DBMSG_KICKCHAR,						S2SMsgKickChar,						_OnS2SMsgKickChar             );
        MESSAGE_HANDLE( GS2CS_PLAYERUPDATETEAMMEMBERINFO,	GS2CSPlayerUpdateTeamMemberInfo,	_OnMsgUpdateTeamMember        );
        MESSAGE_HANDLE( CS2GS_PLAYERJOINTEAM,               CS2GSAckJoinTeam,                   _OnMsgJoinTeamAck             );
        MESSAGE_HANDLE( CS2GS_CREATETEAM,                   CS2GSCreateTeam,                    _OnMsgCreateTeam              );
        MESSAGE_HANDLE( CS2GS_TEAMOUTLINE,                  CS2GSMsgTeamOutLine,                _OnMsgTeamOutLine             );
        MESSAGE_HANDLE( GS2CS_TEAMONLINE,                   GS2CSTeamOnLine,                    _OnMsgTeamOnLine              );
        MESSAGE_HANDLE( GS2CS_PLAYERREMOVEFROMTEAMACK,		GS2CSPlayerRemoveFromTeamAck,		_OnMsgRemoveTeamMemberAck     );
		MESSAGE_HANDLE( GS2CS_DISBANDTEAMACK,				GS2CSPlayerDisbandTeamAck,			_OnMsgDisbandTeamAck		  );
        MESSAGE_HANDLE( GS2CS_PLAYERUPGRADETEAMACK,         GS2CSPlayerUpgradeTeamAck,          _OnMsgUpgradeTeamAck          );
        MESSAGE_HANDLE( CS2GS_TEAMCHANGEASSIGNMODEACK,      CS2GSTeamChangeAssignModeAck,       _OnMsgTeamChangeModeAck       );
        MESSAGE_HANDLE( CS2GS_TEAMCHANGEASSIGNITEMLEVELACK, CS2GSTeamChangeAssignItemLevelAck,  _OnMsgTeamChangeItemLevelAck  );
        MESSAGE_HANDLE( GS2CS_PLAYERCHATMESSAGE,            GS2CSPlayerChatMessage,             _OnMsgChatMessage             );
        MESSAGE_HANDLE( GS2CS_QUERYPLAYERINFOREQ,           GS2CSQueryPlayerInfoReq,            _OnMsgQueryPlayerInfoReq      );
        MESSAGE_HANDLE( GS2CS_QUERYPLAYERINFOACK,           GS2CSQueryPlayerInfoAck,            _OnMsgQueryPlayerInfoAck      );
        MESSAGE_HANDLE_NOTCHECK( GS2CS_TRANSMIT,            S2STransmit,                        _OnS2STransmit                );
        MESSAGE_HANDLE( S2S_TRANSMIT_RESULT,                S2STransmitResult,                  _OnS2STransmitResult          );

        MESSAGE_HANDLE( S2S_NOTIFYTIMEEVENT,                   S2SNotifyTimeEvent,              _OnMsgS2SNotifyTimeEvent            );
        MESSAGE_HANDLE( S2S_ANTIADDICTIONACCOUNTINFO,          S2SAntiAddictionAccountInfo,     _OnMsgS2SAntiAddictionAccountInfo   );
        MESSAGE_HANDLE( S2S_NOTIYANTIADDICTIONTIMEINFO,        S2SNotiyAntiAddictionTimeInfo,   _OnMsgS2SNotiyAntiAddictionTimeInfo );
        MESSAGE_HANDLE( GS2GS_BANSPEAK,                        GS2GSBanSpeak,                   _OnMsgGS2GSBanSpeak            );
        MESSAGE_HANDLE( GS2GS_CALLPALYER,                      GS2GSCallPlayer,                 _OnMsgGS2GSCallPlayer          );
        MESSAGE_HANDLE( CS2GS_DRAWFROMPLATFORM_ACK,            CS2GSDrawFromPlatformAck,        _OnCS2GSDrawFromPlatformAck    );
        MESSAGE_HANDLE( CS2GS_SETCHECKCHEATOPEN,               CS2GSMsgSetCheckCheatOpen,       _OnMsgCS2GSSetCheckCheatOpen   );
        MESSAGE_HANDLE( S2S_UPDATEDROPITEMCONTROL,             S2SMsgUpdateItemDropControl,     _OnMsgUpdateItemDropControl    );
        MESSAGE_HANDLE_NOTCHECK( CS2GS_ITEMDROPCONTROL,        CS2GSItemDropControl,            _OnCS2GSItemDropControl        );
        MESSAGE_HANDLE_NOTCHECK( CS2GS_SYSTEMVAR,              CS2GSSystemVar,                  _OnCS2GSSystemVar              );   // CS ����ϵͳ������ GS
        MESSAGE_HANDLE( CS2GSMSGBORNMAPOPERATE,                CS2GSMsgBornMapOperate,          _OnMsgBornMapOperate           );
        
        MESSAGE_HANDLE( CS2GS_GMBROATCAST_REQ,                 CS2GSGMBroatcastReq,             _OnCS2GSGMBroatcastReq         );
        MESSAGE_HANDLE( MSG_SERVERSTATUSREQ,                   MsgServerStatusReq,              _OnMsgServerStatusReq          );
        MESSAGE_HANDLE( MSG_SERVERVERSIONCHECKACK,             MsgServerVersionCheckAck,        _OnMsgServerVersionCheckAck    );
        MESSAGE_HANDLE_NOTCHECK( S2S_UPDATETRADESHOPCONFIG,    S2SUpdateTradeShopConfig,        _OnS2SUpdateTradeShopConfig    );
        MESSAGE_HANDLE( MSG_CHANGEMAPCALLBACK,                 MsgChangeMapCallBack,            _OnMsgChangeMapCallBack        );        
        MESSAGE_HANDLE( S2S_SHUTDOWNSERVER,                    S2SShutdownServer,               _OnS2SShutdownServer           );
        MESSAGE_HANDLE( S2S_CHANGEMAPEXPRATE,                  S2SChangeMapExpRate,             _OnS2SChangeMapExpRate         );
        MESSAGE_HANDLE_NOTCHECK( CS2GS_MAILLISTACK,            CS2GSMailListAck,                _OnCS2GSMailListAck            );
        MESSAGE_HANDLE( CS2GS_QUERYMAILCANSENDACK,             CS2GSQueryMailCanSendAck,        _OnCS2GSQueryMailCanSendAck    );
        //Center�������û���Ϣ����
        MESSAGE_HANDLE_NOTCHECK( CS2GS_OPMAILACK,              CS2GSOpMailAck,                  _OnCS2GSOpMailAck              );
        MESSAGE_HANDLE_NOTCHECK( CS2GS_SENDMAILACK,            CS2GSSendMailAck,                _OnCS2GSSendMailAck            );
        MESSAGE_HANDLE( S2S_REMOTEBANREQ,                      S2SRemoteBanReq,                 _OnS2SRemoteBanReq             );
        MESSAGE_HANDLE( MSG_PARTITIONLOGFILE,                  MsgPartitionLogFile,             _OnMsgPartitionLogFile         );
        MESSAGE_HANDLE( CS2GS_OPRECORDCHATONOFF,               CS2GSOpRecordChatOnOff,          _OnCS2GSOpRecordChatOnOff      );
        MESSAGE_HANDLE( CS2GS_REWARDOPERATE,                   CS2GSMsgRewardOperate,           _OnCS2GSMsgRewardOperate       );
        MESSAGE_HANDLE( CS2GSLOADFRESOURCESUCCESS,             CS2GSLoadResourceSuccess,        _OnCS2GSLoadResourceSuccess    );
        MESSAGE_HANDLE( CS2GS_UPDATECOUNTRYONLINECOUNT,        CS2GSUpdateCountryOnLineCount,   _OnCS2GSUpdateCountryOnLineCount );
		MESSAGE_HANDLE( CS2GS_UPDATEANTIADDICTIONINFOACK,      CS2GSUpdateAntiaddictionInfoAck, _OnGS2CSUpdateAntiaddictionInfoAck );
		MESSAGE_HANDLE( CS2GS_PING,							   CS2GSPing,						_OnMsgCenterPing );
		MESSAGE_HANDLE( CS2GS_PLATFORMSENDMAILREQ,			   MsgPFSendmailReq,				_OnMsgPFSendMail );
		MESSAGE_HANDLE( CS2GS_QUEUE_OP,						   MsgCS2GSQueueOp,				    _OnMsgQueueOp );

		MESSAGE_HANDLE( GS2CS_CREATEMULITSTAGEREQ,			   GS2CSCreateMulitStageReq,		_OnGS2CSCreateMulitStageReq );
		MESSAGE_HANDLE( GS2CS_CREATEMULITSTAGEACK,			   GS2CSCreateMulitStageAck,		_OnGS2CSCreateMulitStageAck );
		MESSAGE_HANDLE( CS2GS_TEAMSTATECHANGE,					CS2GSTeamStateChange,			_OnCS2GSTeamStateChange );
		MESSAGE_HANDLE( CS2GS_ASKBROADCAST,					   MsgCS2GSBroadCast,				_OnCS2GSBroadCast );
		MESSAGE_HANDLE( MSG_CHANNELSINFO,					   MsgChannelInfo,				    _OnCS2GSChannelInfo );			
		MESSAGE_HANDLE( CS2GS_CLEARTEAMMAPREQ,					   CS2GSClearTeamMapReq,		_OnCS2GSClearTeamMapReq );
		MESSAGE_HANDLE( CS2GS_CHARREMOVEITEMBYID,			   MsgCS2GSCharRemoveItembyId,		_OnCS2GSCharRemoveItembyId );
		MESSAGE_HANDLE( CS2GS_UPDATEARELOADCONFIG,			   MsgCS2GSUpdateReloadCfg,		    _OnCS2GSUpdateReloadCfg );
		
    MESSAGE_MAPPING_END
    return ER_Success;
}

long CenterServerNetEvent::OnMessageIncoming( TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    switch ( pMessage->GetModuleType() )
    {
    case EMessageModule_Default:
        return OnProcessDefaultMessage( pTcpServer, pNetClient, msgType, pMessage );
        break;
    case EMessageModule_Relation: // �����ϵ��Ϣ
        return OnProcessRelationMessage( pTcpServer, pNetClient, msgType, pMessage );
        break;
    case EMessageModule_Country:  // ���������Ϣ 
        return OnProcessCountryMessage( pTcpServer, pNetClient, msgType, pMessage ); 
        break;
    case EMessageModule_Guild:    // �����ϵ��Ϣ
        return OnProcessGuildMessage( pTcpServer, pNetClient, msgType, pMessage ); 
        break;
	case EMessageModule_Family:    // ���������Ϣ
		return OnProcessFamilyMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;
	case EMessageModule_LEVELLIMIT://�ȼ���ӡ
		return OnProcessGameLevelLimitMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;
	case EMessageModule_GolbalDB:
		return OnProcessGlobalDBMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;
	//xuda 
	/*case EMessageModule_Emperor:
		return OnProcessEmperorMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;
	case EMessageModule_Wanted:
		return OnProcessWantedMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;*/
	case EMessageModule_QuestEntrust:
		return OnProcessQuestEntrustMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;
	case EMessageModule_GameBattle:
		return OnProcessGameBattleMessage( pTcpServer, pNetClient, msgType, pMessage ); 
		break;
    default:
        break;
    }

    return ER_Failed;
}

void CenterServerNetEvent::_OnRegiseterGameServerInfoAck( NetClient* pNetClient, const CS2GSRegiseterGameserverInfoAck* pMessage )
{
    if ( pMessage->nResult == ER_Success )
    {
        GettheServer().SetCenterServerValidate( true );
		theGameWorld.ProcessGameStageOp(); //��һ�ξ͹�
		// ��Center ע���Լ�
		MsgRegisterServerAck xAck;
		xAck.uchParentType = ServerDataDefine::Node_Center;
		xAck.nParentID     = 0;
		xAck.nID           = g_Cfg.dwServerID;
		xAck.ustVersion    = theApplicationConfig.GetBuildVersion();
		if ( xAck.nID == CHARACTERSERVERID )
		{
			xAck.uchType = ServerDataDefine::Node_Character;
			sprintf_s( xAck.szName, sizeof( xAck.szName ) - 1, "%s", g_Cfg.szGameServerName );
		}
		else
		{
			xAck.uchType = ServerDataDefine::Node_Game;
			sprintf_s( xAck.szName, sizeof( xAck.szName ) - 1, "GameServer-%s", g_Cfg.szGameServerName );
		}

		GettheServer().SendCenterServerMsg( &xAck );	
    }
}

void CenterServerNetEvent::_OnMessageUpdateMapInfo( NetClient* pNetClient, const MessageUpdateMapInfo* pMessage )
{
}

void CenterServerNetEvent::_OnLoginInfo( NetClient* pNetClient, const CS2GSLoginInfo* pMessage )
{//center server��ȡ����֤����,�ᷢ�ʹ�Э�鵽 character server  by vvx 2012.11.22
    SLoginInfoBase info;
    strncpy_s( info.szIP,       sizeof(info.szIP),       pMessage->szIP,        sizeof(info.szIP)-1);
    strncpy_s( info.szAccount,  sizeof(info.szAccount),  pMessage->szAccount,   sizeof(info.szAccount)-1);
    //strncpy_s( info.SessionKey, sizeof(info.SessionKey), pMessage->SessionKey,  sizeof(info.SessionKey)-1);
	info.Sessionkey = pMessage->SessionKey;
    info.nAccountID = pMessage->nAccountID;
    info.LoginTime  = HQ_TimeGetTime();
    info.isWallow   = pMessage->isWallow;

    S2SSwitchGate SwitchGateMsg;
    SwitchGateMsg.nResult                 = ER_Success;
    SwitchGateMsg.header.stID             = pMessage->header.stID;
    SwitchGateMsg.nSourcePeerInServerType = pMessage->clientPeerInServerType;
    SwitchGateMsg.nTargetServerType       = g_Cfg.dwServerID == CHARACTERSERVERID ? ST_CharacterServer : ST_GameServer;        
    SwitchGateMsg.nTargetServerId         = g_Cfg.dwServerID;
    SwitchGateMsg.nAccountId              = info.nAccountID;

    // ��ÿ��õ�GateServer��Ϣ
    int nNewGateServerIndex = 0;
    bool bResult = GettheServer().SwitchGateServer( &SwitchGateMsg, nNewGateServerIndex );
    if ( bResult )
    { // �ɹ�
        // ��¼������Ϣ
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "GettheServer().AddLoginInfo AccountId[%d] SessionKey[-]", info.nAccountID/*, info.Sessionkey */);
        GettheServer().AddLoginInfo( info );
        GettheServer().AddLoginGateCacheInfo( info.Sessionkey, SwitchGateMsg );

        MsgLoginInfo loginInfo;
        loginInfo.header.stID = pMessage->header.stID;
        loginInfo.nAccountID  = pMessage->nAccountID;

        strncpy_s( loginInfo.szIP,       pMessage->szIP,      sizeof(loginInfo.szIP)-1);
        //strncpy_s( loginInfo.SessionKey, pMessage->SessionKey,sizeof(loginInfo.SessionKey)-1);
		loginInfo.SessionKey = pMessage->SessionKey;
        //strncpy_s( loginInfo.Password,   pMessage->Password,  sizeof(loginInfo.Password)-1);
        //strncpy_s( loginInfo.Seed,       pMessage->Seed,      sizeof(loginInfo.Seed)-1);
        strncpy_s( loginInfo.szAccount,  pMessage->szAccount, sizeof(loginInfo.szAccount)-1);
        GettheServer().SendMsgToGate( &loginInfo, nNewGateServerIndex );
		//printf("4,keylogin:character send to gate login info:%d\n",HQ_TimeGetTime());
    }
    else
    {
        SwitchGateMsg.nResult = ER_NotGateServer;
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CenterServerNetEvent::_OnLoginInfo( not found the GateServer )");
        GettheServer().SendMsgToCenterServer(&SwitchGateMsg);
    }
}

void CenterServerNetEvent::_OnAckSwitchStage( NetClient* pNetClient, const CS2GSSwitchStageAck* pMessage )
{
    GamePlayer* pGamePlayer = (GamePlayer*)theRunTimeData.GetCharacterByID(pMessage->header.stID);

    if ( pGamePlayer == NULL )
        return;

    CS2GSSwitchStageAck* pTMessage = (CS2GSSwitchStageAck*)pMessage;
    pGamePlayer->OnMsgAckSwitchStage( pMessage );
}

void CenterServerNetEvent::_OnS2SSwitchGate( NetClient* pNetClient, const S2SSwitchGate* pMessage )
{
    GamePlayer* pPlayerChar2 = (GamePlayer*)theRunTimeData.GetCharacterByID(pMessage->header.stID);

    if ( !pPlayerChar2 )
        return;

    S2SSwitchGate* pTMessage = (S2SSwitchGate*)pMessage;
    pPlayerChar2->OnMsgS2SSwitchGate( pTMessage );
}

void CenterServerNetEvent::_OnS2SMsgKickChar( NetClient* pNetClient, S2SMsgKickChar* pMessage )
{
    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] ���յ� S2SMsgKickChar ��Ϣ", pMessage->dwAccountID );

    switch ( pMessage->usReason )
    {
    case S2SMsgKickChar::KR_AccountRepeat:
        {
            GamePlayer* pGamePlayer = theRunTimeData.GetCharacterByAccountID( pMessage->dwAccountID );
            if ( NULL == pGamePlayer )
            {
                // Ҳ�����������������, ���ظ�CenterServer, ����T����
                if ( pMessage->uchFailAck == 0 )
                {   // û���ҵ��� һ��Ҫ����gate�������ĵ�½��Ϣ��������������ܵ�½�ˡ�
					GetTheLoginStage().KickCharByAccount( pMessage->dwAccountID );
					// ɾ���ɽ�ɫ�ĵ�¼���
					GettheServer().RemoveLoginInfo( pMessage->SessionKey );
					MsgDelLoginInfo msg;
					msg.accountId = pMessage->dwAccountID;
					// strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), pMessage->szSessionKey, sizeof(msg.szSessionKey) - 1 );
					msg.SessionKey = pMessage->SessionKey;
					GettheServer().SendMsgToGates( &msg );
					LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "_OnS2SMsgKickChar ����ʺ�[%u:%u]�Ѿ����ڷ���������",pMessage->dwAccountID, pMessage->usReason ); 
				}

                if ( pMessage->uchFailAck <= S2SMsgKickChar::ECD_AckCount )
                {
                    S2SMsgKickCharAck xAck;
                    xAck.dwAccountID = pMessage->dwAccountID;
                    xAck.usReason    = pMessage->usReason;
                    xAck.time        = pMessage->time;
                    xAck.uchFailAck  = pMessage->uchFailAck;
                    GettheServer().SendMsgToCenterServer( &xAck );
                }
				
				
                return;
            }

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-:-] S2SMsgKickChar KR_AccountRepeat", pMessage->dwAccountID, pGamePlayer->GetCharName()/*, pGamePlayer->GetSessionKey(), pMessage->SessionKey*/);

			//pGamePlayer->SetOffline();
            //if ( 0 != stricmp( pGamePlayer->GetSessionKey(), pMessage->szSessionKey)/* || pGamePlayer->GetOfflineTime() != 0*/ )
            //{ return; }
			if (pGamePlayer->GetSessionKey() != pMessage->SessionKey
				/*||pGamePlayer->GetOfflineTime() != 0*/)
			{
				return;
			}

            MsgNotifyBeKick msg;
            msg.kickType = MsgNotifyBeKick::EKT_AccountKick;
            GettheServer().SendMsgToSingle( &msg, pGamePlayer );

            pGamePlayer->Log( "Kick By S2SMsgKickChar" );
            pGamePlayer->OnExit( NULL, ET_BeKick );
        }
        break;
    case S2SMsgKickChar::KR_Ban:
        {
            GamePlayer* pGamePlayer = theRunTimeData.GetCharacterByAccountID( pMessage->dwAccountID );
            if ( NULL == pGamePlayer )
            {
                // Ҳ�����������������, ���ظ�CenterServer, ����T����
                if ( pMessage->uchFailAck == 0 )
                { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "_OnS2SMsgKickChar ����ʺ�[%u:%u]�Ѿ����ڷ���������", pMessage->dwAccountID, pMessage->usReason ); }

                if ( pMessage->uchFailAck <= S2SMsgKickChar::ECD_AckCount )
                {
                    S2SMsgKickCharAck xAck;
                    xAck.dwAccountID = pMessage->dwAccountID;
                    xAck.usReason    = pMessage->usReason;
                    xAck.time        = pMessage->time;
                    xAck.uchFailAck  = pMessage->uchFailAck;
                    GettheServer().SendMsgToCenterServer( &xAck );
                }
                return;
            }

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s:-:-] S2SMsgKickChar KR_Ban", pMessage->dwAccountID, pGamePlayer->GetCharName()/*, pGamePlayer->GetSessionKey(), pMessage->SessionKey*/);

            //if ( 0 != stricmp( pGamePlayer->GetSessionKey(), pMessage->szSessionKey) || pGamePlayer->GetOfflineTime() != 0 )
            //{ return; }
			//�������ü��session by vvx 2013.8.8
			//if (pGamePlayer->GetSessionKey() != pMessage->SessionKey
			//	/*||pGamePlayer->GetOfflineTime() != 0*/)
			//{
			//	return;
			//}
			
            pGamePlayer->ProcessBeBlock( MsgNotifyBeKick::EKT_Ban, pMessage->time * 1000 );
        }
        break;
    case S2SMsgKickChar::KR_KickToConnect:
        {
            GamePlayer* pGamePlayer = theRunTimeData.GetCharacterByAccountID( pMessage->dwAccountID );
            if ( pGamePlayer != NULL )
            { // ��������
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "_OnS2SMsgKickChar ����ʺ�[%u:%u] ������һ���з����̱���", pMessage->dwAccountID, pMessage->usReason  );                 
                pGamePlayer->OnExit( NULL, ET_ExceptionKick );
            }

            // ɾ���ɽ�ɫ�ĵ�¼���
            GettheServer().RemoveLoginInfo( pMessage->SessionKey );

            MsgDelLoginInfo msg;
            msg.accountId = pMessage->dwAccountID;
           // strncpy_s( msg.szSessionKey, sizeof(msg.szSessionKey), pMessage->szSessionKey, sizeof(msg.szSessionKey) - 1 );
			msg.SessionKey = pMessage->SessionKey;
            GettheServer().SendMsgToGates( &msg );

            S2SMsgKickCharAck xAck;
            xAck.dwAccountID = pMessage->dwAccountID;
            xAck.usReason    = pMessage->usReason;
            xAck.time        = pMessage->time;
            xAck.uchFailAck  = pMessage->uchFailAck;
            //strncpy_s( xAck.szSessionKey, sizeof(xAck.szSessionKey), pMessage->szSessionKey, sizeof(xAck.szSessionKey) - 1 );
			xAck.SessionKey = pMessage->SessionKey;
            GettheServer().SendMsgToCenterServer( &xAck );

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:-] S2SMsgKickChar KR_KickToConnect", pMessage->dwAccountID/*, pMessage->SessionKey*/);
        }
        break;
    default:
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:-] S2SMsgKickChar δ�������������[%d]", pMessage->dwAccountID, /*pMessage->SessionKey, */pMessage->usReason );
        break;
    }     
}

void CenterServerNetEvent::_OnMsgCreateTeam( NetClient* pNetClient, CS2GSCreateTeam* pMessage )
{
    if ( pMessage->dwTeamSessionID == 0 )
    { return; }

    theGameTeamManager.CreateTeam( pMessage->dwTeamSessionID, pMessage->AssignMode, pMessage->AssignItemLevel );
}

// centerserver ���͹����ļ������ɹ�����Ϣ
void CenterServerNetEvent::_OnMsgJoinTeamAck(NetClient* pNetClient, CS2GSAckJoinTeam* pMessage)
{
    GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwTeamSessionID );
    if ( pTeam == NULL )          
    {
        pTeam = theGameTeamManager.CreateTeam( pMessage->dwTeamSessionID, pMessage->chAssignModeType, pMessage->chAssignItemLevel );      
        if ( pTeam == NULL )
        { return; }
    }

    if ( pMessage->bIsTeamHeader )  // ����Ƕӳ�, �����öӳ�
    {
        pTeam->SetTeamHeaderID( pMessage->dwDataBaseID );
    }

    GameTeamMember xMember;
    xMember.SetID( pMessage->dwDataBaseID );
    xMember.SetName( pMessage->szName );
    xMember.SetTimeOut( 0 );
    xMember.SetManipleID( pMessage->stManipleID );
    xMember.SetManipleHeader( pMessage->bIsManipleHeader );
    xMember.SetFaceID( pMessage->nFaceId );
    xMember.SetHairID( pMessage->nHairId );
    xMember.SetHeadPicID( pMessage->nHeadPicId );
    xMember.SetProfession( pMessage->chProfession );
    xMember.SetSex( pMessage->chSex );
    xMember.SetLevel( pMessage->stLevel );
    xMember.SetHP( pMessage->nHp );
    xMember.SetMP( pMessage->nMp );
    xMember.SetHPMax( pMessage->nHpMax );
    xMember.SetMPMax( pMessage->nMpMax );
    
    // �����Ա
    if ( pTeam->AddTeamMember( xMember, theGameTeamManager, NULL ) == TeamDefine::JoinSuccess )
    {
        GamePlayer* pMemberPlayer = pTeam->GetMemberPlayer( pMessage->dwDataBaseID );
        if ( pMemberPlayer != NULL )
        {
            // ���ö�Ա����ID
            pMemberPlayer->SetTeamID( pTeam->GetID() );             

            // ֪ͨ�ͻ��˵�ǰ����ķ���ģʽ
            MsgTellTeamAssignInfo xAssignInfo;
            xAssignInfo.chAssignMode      = pTeam->GetTeamAssignModeType();
            xAssignInfo.chAssignItemLevel = pTeam->GetTeamAssignItemLevel();
            GettheServer().SendMsgToSingle( &xAssignInfo, pMemberPlayer );

            // ֪ͨ������Ϣ�Ѹı�
            char chPosition = ( pMessage->bIsTeamHeader ? ETP_Leader : ETP_Member );
            pMemberPlayer->TellTeamInfoChange( chPosition );

            // ������������
            pMemberPlayer->ProcessGuideQuest( GuideQuest::Guide_Team ); 
        }
    }
}

void CenterServerNetEvent::_OnMsgTeamOutLine( NetClient* pNetClient, CS2GSMsgTeamOutLine* pMessage )
{
    theGameTeamManager.TeamMemberOutLine( pMessage->dwID );
}

void CenterServerNetEvent::_OnMsgTeamOnLine( NetClient* pNetClient, GS2CSTeamOnLine* pMessage )
{
    theGameTeamManager.TeamMemberOnLine( pMessage->dwID );
}

void CenterServerNetEvent::_OnMsgUpdateTeamMember(NetClient* pNetClient, GS2CSPlayerUpdateTeamMemberInfo* pMessage)
{
	GameTeam *pTeam  = theGameTeamManager.GetTeam( pMessage->dwSessionId );
	if ( pTeam == NULL ) 
	{ return; } // û���������,������

    // ���¸ö�Ա��Ϣ
    GameTeamMember* pTeamMember = pTeam->GetTeamMemberByID( pMessage->dwDataBaseId );
    if ( pTeamMember != NULL )
    {
        pTeamMember->SetTimeOut( 0 );
        pTeamMember->SetHP( pMessage->nHp );
        pTeamMember->SetHPMax( pMessage->nHpMax );
        pTeamMember->SetMP( pMessage->nMp );
        pTeamMember->SetMPMax( pMessage->nMpMax );
        pTeamMember->SetLevel( pMessage->stLevel );
    }
    else // ���ڶ�����, ��ӽ��� ( �����Ƿ�����������, ��ǰ�Ķ����Ա��û�� ) CenterServer ��֤�������Ա�ڶ�����Żᷢ�͹���
    {
        GameTeamMember xTeamMember;
        xTeamMember.SetID( pMessage->dwDataBaseId );
        xTeamMember.SetName( pMessage->szName );
        xTeamMember.SetTimeOut( 0 );
        xTeamMember.SetManipleID( pMessage->stManiple );
        xTeamMember.SetManipleHeader( pMessage->bManipleHeader );
        xTeamMember.SetHP( pMessage->nHp );
        xTeamMember.SetHPMax( pMessage->nHpMax );
        xTeamMember.SetMP( pMessage->nMp );
        xTeamMember.SetMPMax( pMessage->nMpMax );
        xTeamMember.SetLevel( pMessage->stLevel );
        xTeamMember.SetProfession( pMessage->Profession );
        xTeamMember.SetSex( pMessage->stSex );
        xTeamMember.SetHairID( pMessage->nHairID );
        xTeamMember.SetFaceID( pMessage->nFaceID );
        xTeamMember.SetHeadPicID( pMessage->nHeadPicId);
        
        pTeam->AddTeamMember( xTeamMember, theGameTeamManager, NULL );
    }

    //���¸������ͻ���
    Msg_Team_PlayerInfo xInfo;
    xInfo.dwDataBaseId	= pMessage->dwDataBaseId;
    xInfo.bHeader		= pTeam->IsTeamHeader( pMessage->dwDataBaseId );
    xInfo.nHp			= pMessage->nHp;
    xInfo.nHpMax		= pMessage->nHpMax;
    xInfo.nMp			= pMessage->nMp;
    xInfo.nMpMax		= pMessage->nMpMax;
    xInfo.Profession	= pMessage->Profession;
    xInfo.stLvl			= pMessage->stLevel;
    xInfo.dwMapID		= pMessage->dwMapID;
    xInfo.x				= pMessage->x;
    xInfo.y				= pMessage->y;
    xInfo.fx			= pMessage->fx;
    xInfo.fy			= pMessage->fy;
    xInfo.stManiple		= pMessage->stManiple;
    xInfo.bHeader2		= pMessage->bManipleHeader;
	xInfo.AssignMode	= pTeam->GetTeamAssignModeType();

    pTeam->SendMessageToTeamClient( &xInfo, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
}

void CenterServerNetEvent::_OnMsgRemoveTeamMemberAck( NetClient* pNetClient, GS2CSPlayerRemoveFromTeamAck* pMessage )
{
    // ��������һ���ж� �ж��Լ��ı��ص�Sessionid �Ƿ�ͻش���һ��
    GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->dwDataBaseId );
    if ( pTeamPlayer != NULL )
    {
        if ( pTeamPlayer->GetTeamID() != pMessage->dwSessionId )
        {
            // ���ñ���session ɾ������
            GameTeam* pTeam = theGameTeamManager.GetTeam( pTeamPlayer->GetTeamID() );
            if ( pTeam != NULL )
            {
                pTeam->RemoveTeamMemberAndReleaseTeam( pMessage->dwDataBaseId, theGameTeamManager );
            }
            else
            {
                MsgExitTeam xExit;
				xExit.header.stID = pTeamPlayer->GetID();
                GettheServer().SendMsgToSingle( &xExit, pTeamPlayer );

                pTeamPlayer->SetTeamID( TeamDefine::NoneSessionID );
                pTeamPlayer->TellTeamInfoChange( ETP_None );
            }
        }
    }

    GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwSessionId );          
    if ( pTeam == NULL )
    { 
        if ( pTeamPlayer != NULL )
        {
            MsgExitTeam xExit;
			xExit.header.stID = pTeamPlayer->GetID();
            GettheServer().SendMsgToSingle( &xExit, pTeamPlayer );

            pTeamPlayer->SetTeamID( TeamDefine::NoneSessionID );
            pTeamPlayer->TellTeamInfoChange( ETP_None );
        }
        return; 
    }

    pTeam->RemoveTeamMemberAndReleaseTeam( pMessage->dwDataBaseId, theGameTeamManager );
}

void CenterServerNetEvent::_OnMsgDisbandTeamAck( NetClient* pNetClient, GS2CSPlayerDisbandTeamAck* pMessage )
{
	/*GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->dwDataBaseID );
	if ( pTeamPlayer )
	{
		if ( pTeamPlayer->GetTeamID() == pMessage->dwTeamSessionID )
		{*/
			// ���ñ���session ɾ������
			GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwTeamSessionID );
			if ( pTeam )
			{
				for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
				{
					unsigned long nMemberID = pTeam->GetMemberIDByIndex(i);
					GamePlayer* pMemberPlayer = theRunTimeData.GetGamePlayerByDBID( nMemberID );
					if ( pMemberPlayer )
					{
						pMemberPlayer->SetTeamID(TeamDefine::NoneSessionID);//������ҵĶ���IDΪ��
						MsgExitTeam xExit;
						xExit.bIsDisband = true;
						xExit.header.stID = pMemberPlayer->GetID();
						//GettheServer().SendMsgToSingle( &xExit, pMemberPlayer );
						GettheServer().SendMsgToView(&xExit,pMemberPlayer->GetID(),false);
					}
				}

				pTeam->DisbandTeam( theGameTeamManager );
			}
		//}
	//}
}

void CenterServerNetEvent::_OnMsgUpgradeTeamAck(NetClient* pNetClient, GS2CSPlayerUpgradeTeamAck* pMessage)
{
    GamePlayer* pTeamHeader = theRunTimeData.GetGamePlayerByDBID( pMessage->dwDataBaseId );

    GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwSessionId );
    if ( pTeam == NULL || !pTeam->IsInTeam( pMessage->dwDataBaseId ) )
    { return; } 

    unsigned int dwLastHeaderID = pTeam->GetTeamHeaderID();
    if ( pTeam->UpgradeTeamHeader( pMessage->dwDataBaseId ) )
    {
        MsgAckJoinTeam msgResult;
        HelperFunc::SafeNCpy( msgResult.name, pMessage->szName, sizeof( msgResult.name ) );
        msgResult.stError = MsgAckJoinTeam::succeed_upgrade;
        pTeam->SendMessageToTeamClient( &msgResult, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );

        //֪ͨ�������,�ӳ���Ϣ�Ѿ��ı�
        GamePlayer* pLastHeader = pTeam->GetMemberPlayer( dwLastHeaderID );
        if ( pLastHeader != NULL )        
        { // �Ѿ����Ƕӳ�
			if (pTeam->IsInTeam(dwLastHeaderID))
			{
				pLastHeader->TellTeamInfoChange( ETP_Member );
			}
			else
				pLastHeader->TellTeamInfoChange( ETP_None );            
        }

        GamePlayer* pNowHeader = pTeam->GetMemberPlayer( pMessage->dwDataBaseId );
        if ( pNowHeader != NULL )
        {  //�Ѿ����Ϊ�ӳ�
            pNowHeader->TellTeamInfoChange( ETP_Leader );
        }
    }
}

void CenterServerNetEvent::_OnMsgTeamChangeModeAck( NetClient* pNetClient, CS2GSTeamChangeAssignModeAck* pMessage )
{
    GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwTeamSessionID );
    if ( pTeam == NULL )
    { return; }

    pTeam->SetTeamAssignModeType(pMessage->chAssignMode);

    //֪ͨ�ͻ���
    MsgAckChangeAssignMode xChangeAck;
    xChangeAck.AssignMode = pMessage->chAssignMode;
    pTeam->SendMessageToTeamClient( &xChangeAck, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
}

void CenterServerNetEvent::_OnMsgTeamChangeItemLevelAck( NetClient* pNetClient, CS2GSTeamChangeAssignItemLevelAck* pMessage )
{
    GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwTeamSessionID );
    if ( pTeam == NULL )
    { return; }

    pTeam->SetTeamAssignItemLevel( pMessage->chAssignItemLevel );

    //֪ͨ�ͻ���
    MsgChangeAssignItemLevelAck xChangeAck;
    xChangeAck.chAssignItemLevel = pMessage->chAssignItemLevel;
    pTeam->SendMessageToTeamClient( &xChangeAck, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
}

//������Ϣ (˽�� �� ����Ϣ)
void CenterServerNetEvent::_OnMsgChatMessage(NetClient* pNetClient, GS2CSPlayerChatMessage* pMessage)
{
    MsgChat* pChat = (MsgChat*) pMessage->szBuf;
    pChat->header.stID = -1;        //�ó�-1 ,�ÿͻ���������ȥ�ж�

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pChat->chatHeader.dwToPlayerDBID );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->SendMessageToClient( pChat );  

    // û�й�ϵ, �����ʱ����
    GameRelation* pRelation = pPlayer->GetRelation();
    if ( pRelation == NULL )
    { return; }

    RelationDataToServer* pData = pRelation->GetRelationData( pChat->chatHeader.dwSpeakPlayerDBID );
    if ( pData == NULL)
    { pPlayer->AddRelation( pChat->chatHeader.szSpeakName, RelationDefine::TempFriend ); }
}

void CenterServerNetEvent::_OnS2STransmit( NetClient* pNetClient, S2STransmit* pMessage )
{
    switch( pMessage->ucSessionType )
    {
    case S2STransmit::SESSIONT_World:
        {
            GettheServer().SendMsgToWorld( (Msg*)pMessage->buffer );
        }
        break;
    case S2STransmit::SESSTONT_Single:
        {
            GamePlayer* pGamePlayer = NULL;
            if ( pMessage->targetData.character.uDbId == InvalidLogicNumber )
            {
                pGamePlayer = theRunTimeData.GetGamePlayerByName( pMessage->targetData.character.szName );
            }
            else
            {
                pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->targetData.character.uDbId );
            }

            if ( pGamePlayer == NULL )
            { return; }

            Msg* pMsg = (Msg*) pMessage->buffer;
            if ( pMessage->directToClient == 0 )
            { // ��Ҫ�����߼�
                pGamePlayer->ProcessMsg( pMsg );
            }
            else
            {
                GettheServer().SendMsgToSingle( pMsg, pGamePlayer );
            }
        }
        break;
    case S2STransmit::SESSIONT_Team:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->targetData.team.dwSessionID );
            if ( pTeam != NULL )
            {
                pTeam->SendMessageToTeamClient( ( Msg* )pMessage->buffer, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
            }
        }
        break;
    case S2STransmit::SESSIONT_Guild:
        {
            GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->targetData.guild.id );
            if ( pGuild != NULL )
            {  pGuild->SendMessageToGuild( (Msg*)pMessage->buffer ); }
        }
        break;
    case S2STransmit::SESSIONT_Server:
        {
            Msg* pMessageT = (Msg*)pMessage->buffer;
            switch ( pMessageT->GetType() )
            {
            case S2S_CHANGEEXP:
                {
                    S2SChangeExp* pMsg = (S2SChangeExp*)pMessageT;
                    theRunTimeData.g_nExpPer = pMsg->expPer;
                    MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);                    
                    char bufStr[BUFSIZ + 1] = {0};
                    sprintf_s(bufStr, BUFSIZ,theXmlString.GetString(eTell_Client_ServerExpPer), theRunTimeData.g_nExpPer);
                    chat.SetString(bufStr);
                    GettheServer().SendMsgToWorld( &chat, false );
                }
                break;
            }
        }
        break;
    case S2STransmit::SESSIONT_Country:
        {
            GettheServer().SendMsgToCountry( (Msg*)pMessage->buffer, pMessage->targetData.country.countryId , false );
        }
        break;
    }

    //������һЩ���ʧ����Ϣ
}

void CenterServerNetEvent::_OnS2STransmitResult( NetClient* pNetClient, S2STransmitResult* pMessage )
{
    switch ( pMessage->ucSessionType )
    {
    case S2STransmit::SESSTONT_Single:
        {
            GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->identifyId );            
            if ( pGamePlayer == NULL )
            { return; }

            pGamePlayer->OnS2STransmitResult( pMessage );
        }
    	break;
    }
}

void CenterServerNetEvent::_OnMsgQueryPlayerInfoReq(NetClient* pNetClient, GS2CSQueryPlayerInfoReq* pMessage)
{
    GamePlayer* pGamePlayer = NULL;
    if (pMessage->dwAckID != -1)
    {
        pGamePlayer = theRunTimeData.GetGamePlayerByDBID(pMessage->dwAckID);
    }
    else if (pMessage->szAckName[0] != 0)
    {
        pGamePlayer = theRunTimeData.GetGamePlayerByName(pMessage->szAckName);
    }

    if (pGamePlayer == NULL) 
    { return; }

    MapConfig::MapData* pMapData = pGamePlayer->GetMapData();
    if ( pMapData == NULL )
    { return; }

    GS2CSQueryPlayerInfoAck xAck;
    xAck.dwReqID     = pMessage->dwReqID;
    xAck.dwAckID     = pGamePlayer->GetDBCharacterID();
    xAck.nAction     = pMessage->nAction;
    HelperFunc::SafeNCpy(xAck.szAckName, pGamePlayer->GetCharName(), sizeof(xAck.szAckName));

    if ( !pMapData->IsEctypeMap() )
    {
        xAck.nMapID  = pGamePlayer->GetMapID();
        xAck.fX      = pGamePlayer->GetFloatX();
        xAck.fY      = pGamePlayer->GetFloatY();
        xAck.fDir    = 0.0f;
    }
    else
    {
        MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
        if ( pRelive == NULL )
        { return; }

        xAck.nMapID = pRelive->MapId;
        xAck.fX     = pRelive->PositionX;
        xAck.fY     = pRelive->PositionY;
        xAck.fDir   = pRelive->Direction;
    }

    GettheServer().SendMsgToCenterServer(&xAck);
}

void CenterServerNetEvent::_OnMsgQueryPlayerInfoAck(NetClient* pNetClient, GS2CSQueryPlayerInfoAck* pMessage)
{
    GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->dwReqID );
    if (pGamePlayer == NULL) 
    { return; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pMessage->nMapID ) );
    if ( pMapData == NULL )
    {
        //����Ҫ֪ͨ�ͻ���,��������ڸ�����,���÷�
        pGamePlayer->TellClient("��������ڸ�����, ��ʱ���ܷ���!");
        return;
    }

    switch ( pMessage->nAction )
    {
    case GS2CSQueryPlayerInfoReq::Action_FlyToPlayer:
        {
            pGamePlayer->FlyToMapReq( pMessage->nMapID, pMessage->fX /*+ 1.0f*/, pMessage->fY /*+ 1.0f*/, pMessage->fDir );
        }
        break;
    case GS2CSQueryPlayerInfoReq::Action_ItemFlyToPlayer:
        {
            pGamePlayer->FlyToMapReq( pMessage->nMapID, pMessage->fX /*+ 1.0f*/, pMessage->fY /*+ 1.0f*/, pMessage->fDir, false );
        }
        break;
    }
}




void CenterServerNetEvent::_OnMsgS2SNotifyTimeEvent( NetClient* pNetClient, S2SNotifyTimeEvent* pMessage )
{
    // GetScriptMgr()->RunTimeScript( ST_REAL_TIME, pMessage->timeEventValue );
}

void CenterServerNetEvent::_OnMsgS2SAntiAddictionAccountInfo ( NetClient* pNetClient, S2SAntiAddictionAccountInfo* pMessage )
{
}

void CenterServerNetEvent::_OnMsgS2SNotiyAntiAddictionTimeInfo ( NetClient* pNetClient, S2SNotiyAntiAddictionTimeInfo* pMessage )
{
	g_Cfg.bIsOpenAntiAddiction            = pMessage->bOpenantiAddiction;
	g_Cfg.xAntiAddictionInfo              = pMessage->antiAddictionTime ;
	g_Cfg.bHaveGetAntiAddictionInfoConfig = true;
	g_Cfg.nAntiAddictionSaveTime          = pMessage->nAntiAddictionSaveTime;

	char szContent[ 512 ] = { 0 };
	sprintf_s( szContent, sizeof( szContent ),"������ϵͳ��Ϣ ״̬:%s ����ʱ��:%d %d  ƣ��ʱ��:%d %d  ����ʱ��:%d %d (��λ:����)",
		g_Cfg.bIsOpenAntiAddiction ? "����":"�ر�",
		pMessage->antiAddictionTime._normal._playTime, pMessage->antiAddictionTime._normal._notifyTime,
		pMessage->antiAddictionTime._tired._playTime, pMessage->antiAddictionTime._tired._notifyTime,
		pMessage->antiAddictionTime._rest._playTime, pMessage->antiAddictionTime._rest._notifyTime  );

	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, szContent );
	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, szContent );
}

void CenterServerNetEvent::_OnMsgGS2GSBanSpeak( NetClient* pNetClient, GS2GSBanSpeak* pMessage )
{
    GamePlayer* pPlayer = NULL;
    if ( pMessage->szName[0] != 0 )
    {
        pPlayer = theRunTimeData.GetGamePlayerByName( pMessage->szName );
    }
    else if ( pMessage->dwDBID != InvalidLogicNumber )
    {
        pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->dwDBID );
    }

    if ( pPlayer == NULL )
    { return; }

    pPlayer->SetBanSpeakTime( pMessage->dwBanTime * OneMinuteMicroSecond, true );
}

void CenterServerNetEvent::_OnMsgGS2GSCallPlayer( NetClient* pNetClient, GS2GSCallPlayer* pMessage )
{
    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByName( pMessage->szName );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->FlyToMapReq( pMessage->dwMapID, pMessage->fX, pMessage->fY, pMessage->fDir );
}


void CenterServerNetEvent::_OnCS2GSDrawFromPlatformAck( NetClient* pNetClient, CS2GSDrawFromPlatformAck* pMessage )
{
    GamePlayer* pGamePlayer = theRunTimeData.GetCharacterByAccountID( pMessage->guid );
    if ( !pGamePlayer)
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "CS2GSDrawFromPlatformAck �Ҳ����˺���[%ld] op[%d] value[%u]", pMessage->guid, pMessage->drawType, pMessage->value );
        return; 
    }

    pGamePlayer->OnDrawFromPlatformAck( pMessage );    
}

void CenterServerNetEvent::_OnMsgCS2GSSetCheckCheatOpen( NetClient* pNetClient, CS2GSMsgSetCheckCheatOpen* pMessage )
{
    theRabotManager.SetCheckOpen( pMessage->bOpen );
    if ( pMessage->bOpen )      // ����ǿ����Ļ� ������ȡ����
    {
        theRabotManager.DoneChangeConfigTimer();
    }
}

void CenterServerNetEvent::_OnMsgUpdateItemDropControl( NetClient* pNetClient, S2SMsgUpdateItemDropControl* pMessage )
{
    theDropItemManager.AddItemDropControl( pMessage->nItemID, pMessage->dwControlCount, pMessage->dwDropCount );
}

void CenterServerNetEvent::_OnCS2GSItemDropControl( NetClient* pNetClient, CS2GSItemDropControl* pMessage )
{
    for ( int i = 0; i < pMessage->nCount; ++i )
    {
        theDropItemManager.AddItemDropControl( pMessage->xDropInfo[i].nItemID, pMessage->xDropInfo[i].xControl.dwControlCount, pMessage->xDropInfo[i].xControl.dwDropCount );
    }

    if ( !pMessage->IsFull() )
    {
        theRunStatus.SetLoadSuccess( RunStatusDefine::LoadItemDropuccess );
    }
}

void CenterServerNetEvent::_OnCS2GSSystemVar( NetClient* pNetClient, CS2GSSystemVar* pMessage )
{
    //GetScriptVarMgr()->SetVar(pMessage->xSystemVar.sysVar); // ��CS����ϵͳ����������GS
    for (int i=0; i<More_iMaxSysVars; ++i)
    {
        if (pMessage->xSystemVar.sysVar[i].szName[0] != 0)
        {
            GetScriptVarMgr()->SetScriptVar(pMessage->xSystemVar.sysVar[i], i); // ��������ƣ����޸����ƶ�Ӧ�ı���
        }
    }

    theRunStatus.SetLoadSuccess( RunStatusDefine::LoadSystemVarSuccess );
}

void CenterServerNetEvent::_OnMsgBornMapOperate( NetClient* pNetClient, CS2GSMsgBornMapOperate* pMessage )
{
    theGameWorld.SetExtendrnMapOpen( pMessage->chOperate );
}

void CenterServerNetEvent::_OnCS2GSGMBroatcastReq( NetClient* pNetClient, CS2GSGMBroatcastReq* pMessage )
{
    MsgChat chat(MsgChat::CHAT_TYPE_BULL);
    chat.SetString( pMessage->content );
    GettheServer().SendMsgToWorld( &chat, false );
}

void CenterServerNetEvent::_OnMsgServerStatusReq( NetClient* pNetClient, MsgServerStatusReq* pMessage )
{
    MsgServerStatusAck xAck;
    xAck.uchParentType = ServerDataDefine::Node_Center;
    xAck.nParentID     = 0;
    xAck.nID           = g_Cfg.dwServerID;
    if ( xAck.nID == CHARACTERSERVERID )
    {
        xAck.uchType = ServerDataDefine::Node_Character;
    }
    else
    {
        xAck.uchType = ServerDataDefine::Node_Game;
    }
    GettheServer().SendMsgToCenterServer( &xAck );

    // ���͸�GateServer
    GettheServer().SendMsgToGates( pMessage );
}


void CenterServerNetEvent::_OnMsgServerVersionCheckAck( NetClient* pNetClient, MsgServerVersionCheckAck* pMessage )
{
    theRunStatus.SetLoadSuccess( RunStatusDefine::CheckVersionSuccess );      // ������֤�ɹ�
}

void CenterServerNetEvent::_OnMsgChangeMapCallBack( NetClient* pNetClient, MsgChangeMapCallBack* pMessage )
{
    if ( pMessage->dwTeamSessionID != TeamDefine::NoneSessionID )
    {
        GameTeam* pTeam = theGameTeamManager.GetTeam( pMessage->dwTeamSessionID );
        if ( pTeam != NULL )
        {
            pTeam->UpdateTeamBuffer();
        }
    }
}

void CenterServerNetEvent::_OnS2SUpdateTradeShopConfig( NetClient* pNetClient, S2SUpdateTradeShopConfig* pMessage )
{
    if ( !theTradeCenter.LoadConfigFromBuffer( pMessage->buffer, pMessage->bufferSize, pMessage->zip == 1) )
    { return; }
    
    MsgNotifyTradeShopChange msg;
    msg.timeStamp = HQ_TimeGetTime();
    GettheServer().SendMsgToWorld( &msg );
}

void CenterServerNetEvent::_OnS2SShutdownServer( NetClient* pNetClient, S2SShutdownServer* pMessage )
{
    if ( ST_CenterServer != pMessage->serverType)
    { return; }    

    uint32 curTime = HQ_TimeGetTime();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "�յ�CenterServer�ط�֪ͨ(%u:%u),��ʼ�Կͻ��˹ط��㲥...", curTime, pMessage->delayTime );

    GettheServer().SetShutdownTime( curTime, pMessage->delayTime );

    // ���߿ͻ��˹ط�����
    MsgShutdownServer msgShutdown;
    __time64_t ltime;
    _time64(&ltime);
    msgShutdown.nowTime   = ltime;
    msgShutdown.delayTime = pMessage->delayTime;
    GettheServer().SendMsgToWorld( &msgShutdown );

    // ���ط�������Ϣ������Gate
    S2SShutdownServer msg;
    msg.serverType = ST_GameServer;
    msg.delayTime  = pMessage->delayTime;
    GettheServer().SendMsgToGates( &msg );
}

void CenterServerNetEvent::_OnS2SChangeMapExpRate( NetClient* pNetClient, S2SChangeMapExpRate* pMessage )
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( pMessage->mapConfigId );
    if ( NULL == pMapData )
    { return; }
    
    pMapData->ExpRate = pMessage->fExpRate;
    GettheServer().TellClients( theXmlString.GetString(eText_ShowChangeMapExpRate), pMapData->MapName.c_str(),(int)(pMapData->ExpRate * 100));
    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "�յ�CenterServer �޸ĵ�ͼ����(%u:%f)", pMessage->mapConfigId, pMapData->ExpRate );
}

void CenterServerNetEvent::_OnCS2GSMailListAck( NetClient* pNetClient, CS2GSMailListAck* pMessage )
{
    GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->charDbId );
    if ( NULL == pGamePlayer )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnCS2GSMailListAck GetGamePlayerByDBID(%u) fail", pMessage->charDbId );
        return;
    }

    MsgMailListAck msg;
    
    if ( pMessage->count > EM_MailMaxCount )
    { pMessage->count = EM_MailMaxCount; }

    for ( int i=0; i<pMessage->count; ++i )
    {
        SMail& mail = pMessage->mails[i];
        msg.AddMail( mail );
    }

    GettheServer().SendMsgToSingle( &msg, pGamePlayer );
}

void CenterServerNetEvent::_OnCS2GSQueryMailCanSendAck( NetClient* pNetClient, CS2GSQueryMailCanSendAck* pMessage )
{
    GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->charDbId );
    if ( NULL == pGamePlayer )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnCS2GSQueryMailCanSendAck GetGamePlayerByDBID(%u) fail", pMessage->charDbId );
        return;
    }

    if ( pMessage->result == ER_Success)
    { 
        pGamePlayer->_mailManager.SendValidMailToCS();
        pGamePlayer->_mailManager.EndSendValidMail();
    }
    else
    {
        pGamePlayer->_mailManager.SendInValidMailToClient( pMessage );
        pGamePlayer->_mailManager.EndSendValidMail();
    }
}

void CenterServerNetEvent::_OnCS2GSOpMailAck( NetClient* pNetClient, CS2GSOpMailAck* pMessage )
{
    GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->charDbId );
    if ( NULL == pGamePlayer )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnCS2GSOpMailAck GetGamePlayerByDBID(%u) fail", pMessage->charDbId );
        return;
    }

    MsgOpMailAck msg;
    msg.result = pMessage->result;
    msg.mailId = pMessage->mailId;
    msg.op     = pMessage->op;
    msg.money  = pMessage->money;
    memcpy_s( &msg.accessory, sizeof(msg.accessory), &pMessage->accessory, sizeof(msg.accessory));
    if ( pMessage->result != ER_Success)
    {
        GettheServer().SendMsgToSingle( &msg, pGamePlayer );
        return;
    }

    switch ( pMessage->op )
    {
    case EMO_Delete:
        { // ɾ���ʼ�
        }
        break;
    case EMO_Open:
        {
        }
        break;
    case EMO_GetMoney:
        {
            pGamePlayer->OperateMoney( EOT_Add, pMessage->money, false, __FUNCTION__, __LINE__,ePlayerMoneySourceType_MailCache);
            msg.money  = pGamePlayer->GetMoney();
			//theLogEventService.LogCurrency(pGamePlayer->GetAccountID(),pGamePlayer->GetDBCharacterID(), pMessage->money,ePlayerMoneyType_Money,ePlayerCurrency_Add,pGamePlayer->GetCharName());			
        }
        break;
    case EMO_GetAccessory:
        {
           // pGamePlayer->Log("�ʼ���ȡ");
			 pGamePlayer->Log(theXmlString.GetString(eServerLog_LingQuMail));

            switch ( pMessage->accessory.type)
            {
            case SMail::EAT_Item:
                {
                    SCharItem* pCharItem = (SCharItem*)pMessage->accessory.content;
                    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                    if ( NULL == pItemCommon)
                    { break; } // ��Ʒ�������ò�����

                    ItemBag* pItemBag = pGamePlayer->GetItemBagByItemType( pItemCommon->ucItemType );
                    int nResult = pItemBag->PushItem( *pCharItem, pCharItem->itembaseinfo.ustItemCount );
                    if ( nResult != ierr_Success)
                    { msg.result = ER_Failed; }                    
                    
                    //pGamePlayer->Log("�ʼ���ȡ[%d:%s:%d:%I64u] result[%d]", pCharItem->itembaseinfo.ustItemID, pItemCommon->GetItemName(), pCharItem->itembaseinfo.ustItemCount, pCharItem->itembaseinfo.nOnlyInt ); 
					pGamePlayer->Log(theXmlString.GetString(eServerLog_LingQuMail1), pCharItem->itembaseinfo.ustItemID, pItemCommon->GetItemName(), pCharItem->itembaseinfo.ustItemCount, pCharItem->itembaseinfo.nOnlyInt ); 
                    theLogEventService.LogItemGain(pGamePlayer->GetAccountID(),pGamePlayer->GetDBCharacterID(),pCharItem->itembaseinfo.ustItemID,pCharItem->itembaseinfo.ustItemCount,pCharItem->itembaseinfo.nOnlyInt,EIGS_Mail,pGamePlayer->GetCharName(),pItemCommon->GetItemName());
				}
            	break;
            case SMail::EAT_Mount:
                {
                    SMountItem* pMountItem = (SMountItem*)pMessage->accessory.content;
                    int nResult = pGamePlayer->_mountManager.PushMount( *pMountItem );

                    //pGamePlayer->Log("�ʼ���ȡ[%d:%s:%I64u] result[%d]", pMountItem->baseInfo.id, pMountItem->baseInfo.szName, pMountItem->baseInfo.guid, nResult ); 
					pGamePlayer->Log(theXmlString.GetString(eServerLog_LingQuMail2), pMountItem->baseInfo.id, pMountItem->baseInfo.szName, pMountItem->baseInfo.guid, nResult );
					 theLogEventService.LogItemGain(pGamePlayer->GetAccountID(),pGamePlayer->GetDBCharacterID(),pMountItem->baseInfo.id,1,pMountItem->baseInfo.guid,EIGS_Mail,pGamePlayer->GetCharName(),pMountItem->baseInfo.szName);
                }
                break;
            case SMail::EAT_Pet:
                {
                    SPetItem* pPetItem = (SPetItem*)pMessage->accessory.content;
                    int nResult = pGamePlayer->_petManager.PushPet( *pPetItem );

                    pGamePlayer->Log(theXmlString.GetString(eServerLog_LingQuMail2), pPetItem->baseInfo.petId, pPetItem->baseInfo.szName, pPetItem->baseInfo.guid, nResult ); 
					theLogEventService.LogItemGain(pGamePlayer->GetAccountID(),pGamePlayer->GetDBCharacterID(),pPetItem->baseInfo.petId,1,pPetItem->baseInfo.guid,EIGS_Mail,pGamePlayer->GetCharName(),pPetItem->baseInfo.szName);
                }
                break;
            }
        }
        break;
    default:
        return;
        break;
    }
    msg.RecalLength();
    GettheServer().SendMsgToSingle( &msg, pGamePlayer );
}

void CenterServerNetEvent::_OnCS2GSSendMailAck( NetClient* pNetClient, CS2GSSendMailAck* pMessage )
{
    GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->charDbId );
    if ( NULL == pGamePlayer )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnCS2GSSendMailAck GetGamePlayerByDBID(%u) fail", pMessage->charDbId );
        return;
    }

    if ( pMessage->result != ER_Success )
    {
        pGamePlayer->_mailManager.EndSendValidMail();
    }
}

void CenterServerNetEvent::_OnS2SDleteCountryBattleReward(NetClient* pNetClient, S2SDleteCountryBattleReward* pMessage)
{
	//zhuxincong 
	 GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
	 if (pGamePlayer == NULL)
	 {
		 return;
	 }
	 
}

void CenterServerNetEvent::_OnS2SRemoteBanReq( NetClient* pNetClient, S2SRemoteBanReq* pMessage )
{
	GamePlayer* pGamePlayer = NULL;
	if (pMessage->chOrAcc == 0)
	{
		pGamePlayer = theRunTimeData.GetGamePlayerByName( pMessage->_Name );		
	}
	else
		pGamePlayer = theRunTimeData.GetCharacterByAccountID(pMessage->accountid);

	if ( pGamePlayer == NULL )
	{ return; }    

    if ( pMessage->banTime <= 0 )
    { pMessage->banTime = 900000; }

    pGamePlayer->Log( "Exit By ProcessBan EKT_Ban Remote" );
    pGamePlayer->ProcessBeBlock( MsgNotifyBeKick::EKT_Ban, pMessage->banTime );
    //pGamePlayer->Log("��Block ԭ��Ban");
	pGamePlayer->Log(theXmlString.GetString(eServerLog_Block));
}


void CenterServerNetEvent::_OnMsgPartitionLogFile( NetClient* pNetClient, MsgPartitionLogFile* pMessage )
{
    SYSTEMTIME xSystem;
    ::GetLocalTime( &xSystem );

    //LOG_MESSAGE( SYSTEMOBJECT,      LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( PLAYERLOGIC,       LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( BILLINGOBJECT,     LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( SHOPPINGOBJECT,    LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( CHECKCHEATOBJECT,  LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( SCRIPTOBJECT,      LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( CAPABILITYOBJECT,  LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );
    //LOG_MESSAGE( SQLOBJECT,         LOG_PRIORITY_INFO, "=========================[%d-%d-%d]=========================", xSystem.wYear, xSystem.wMonth, xSystem.wDay );

    GettheServer().SendMsgToGates( pMessage );
}

void CenterServerNetEvent::_OnCS2GSOpRecordChatOnOff( NetClient* pNetClient, CS2GSOpRecordChatOnOff* pMessage )
{
    g_Cfg.isSendChatToCenter = pMessage->isOpen == 1 ? true : false;
}

void CenterServerNetEvent::_OnCS2GSMsgRewardOperate( NetClient* pNetClient, CS2GSMsgRewardOperate* pMessage )
{
    switch( pMessage->uchType )
    {
    case CS2GSMsgRewardOperate::ECD_Exp:
        {
            for (int i = 0; i < dr_worldMaxPlayers; ++i )
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( i );
                if ( pChar != NULL && pChar->IsPlayer() )
                {
                    GamePlayer* pGamePlayer = static_cast< GamePlayer*>( pChar );
                    
                    pGamePlayer->IncreaseExp( pMessage->dwValue, 0, NULL );               
                }
            }
        }
        break;
    default:
        break;
    }
}

void CenterServerNetEvent::_OnCS2GSLoadResourceSuccess( NetClient* pNetClient, CS2GSLoadResourceSuccess* pMessage )
{
    theRunStatus.SetLoadSuccess( pMessage->uchLoadType );//��ʵ���� LoadConsignmentSuccess
}

void CenterServerNetEvent::_OnCS2GSUpdateCountryOnLineCount( NetClient* pNetClinet, CS2GSUpdateCountryOnLineCount* pMessage )
{
    theRunTimeData.UpdateCountryOnLineCount( pMessage->uchCountryID, pMessage->nCount );
}

void CenterServerNetEvent::_OnGS2CSUpdateAntiaddictionInfoAck ( NetClient* pNetClient, CS2GSUpdateAntiaddictionInfoAck* pMessage )
{
	if ( pMessage->nType == GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Exit)
	{ return; }

	GamePlayer* pGamePlayer = (GamePlayer*)theRunTimeData.GetCharacterByAccountID( pMessage->nAccountId );
	if ( NULL == pGamePlayer || !pGamePlayer->IsPlayer())
	{ 
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnGS2CSUpdateAntiaddictionInfoAck GetCharacterByAccountID(%u) fail", pMessage->nAccountId );
		return;
	}

	pGamePlayer->OnGS2CSUpdateAntiaddictionInfoAck( pMessage );
}

void CenterServerNetEvent::_OnMsgCenterPing ( NetClient* pNetClient, CS2GSPing*  pMessage )
{
	int n =0;
	n++;
}

void CenterServerNetEvent::_OnMsgPFSendMail ( NetClient* pNetClient, MsgPFSendmailReq* pMessage )
{
	if (!pMessage)
	{
		return;
	}

	MsgPFSendmailAck mailack;
	if (!theRunTimeData.CreateItem(pMessage->itemid,pMessage->itemcount,HelperFunc::CreateID(),mailack.item))
	{
		return;
	}	
	mailack.characterid = pMessage->characterid;
	mailack.money = pMessage->money;
	strncpy_s(mailack.charactername,sizeof(mailack.charactername),pMessage->charactername,sizeof(mailack.charactername) -1);
	strncpy_s(mailack.content,sizeof(mailack.content),pMessage->content,sizeof(mailack.content) -1);
	strncpy_s(mailack.title,sizeof(mailack.title),pMessage->title,sizeof(mailack.title) -1);
	GettheServer().SendMsgToCenterServer( &mailack );
}

void CenterServerNetEvent::_OnMsgQueueOp ( NetClient* pNetClient, MsgCS2GSQueueOp* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	GetTheLoginStage().SetService(pMessage->_open);
}
void CenterServerNetEvent::_OnGS2CSCreateMulitStageReq( NetClient* pNetClient, GS2CSCreateMulitStageReq* pMessage )
{
	//���������� ��Ҫ�������� �ж��Ƿ���Դ������� 
	//1.�ж�ָ�������Ƿ����
	GS2CSCreateMulitStageAck msg;
	msg.PlayerDBID = pMessage->PlayerDBID;
	msg.GameServerID = pMessage->GameServerID;
	msg.MapID = pMessage->MapID;
	if(msg.PlayerDBID != 0) // ������Ҫ����ҽ�����ת��ʱ�� ����ֻ���𸱱��Ĵ�������
	{
		msg.x = pMessage->x;
		msg.y = pMessage->y;
		msg.dir = pMessage->dir;
	}
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(pMessage->MapID);
	if ( pMapData == NULL ) // û�ҵ���ͼ��Ϣ
	{
		msg.Result = false;
		msg.ErrorID = 1;//��ͼ������
		if(msg.PlayerDBID != 0)
			GettheServer().SendMsgToCenterServer(&msg);
		return;
	}
	if(!pMapData->IsEctypeMap())
	{
		msg.Result = false;
		msg.ErrorID = 2;//��ͼΪ��ͨ��ͼ
		if(msg.PlayerDBID != 0)
			GettheServer().SendMsgToCenterServer(&msg);
		return;
	}
	//�жϸ����Ƿ��Ѿ�������
	GameStage* pStage = theGameWorld.GetStageById( pMessage->EctypeMapID );
	if(pStage)
	{
		//���ǲ�һ�����Խ��� ��Ҫ�����ж�
		EctypeStage* pEctypeStage = static_cast< EctypeStage* >( pStage );
		// ����Ƿ��ڵȴ�������
		if ( pEctypeStage->IsStageWaitingRelease())
		{
			if(pMapData->GetMapType() == MapConfig::MT_Period)
			{
				msg.Result = false;
				msg.ErrorID = 3;//������ȴ��
				if(msg.PlayerDBID != 0)
					GettheServer().SendMsgToCenterServer(&msg);
				return;
			}
			pEctypeStage->SetStageWaitRelease( false );
		}
		// ���һ��ԤԼ
		pEctypeStage->AddReserve(pMessage->ReserveValue);//�������ԤԼ
		msg.Result = true;
		if(msg.PlayerDBID != 0)
			GettheServer().SendMsgToCenterServer(&msg);
		return;
	}
	//2.�����ڵĻ�...�жϸ��������Ƿ�����
	if ( pMapData->IsMapCountLimitMap() && theGameWorld.GetMapCount(pMessage->MapID) >= pMapData->Count )
	{
		msg.Result = false;
		msg.ErrorID =4;//��������
		if(msg.PlayerDBID != 0)
			GettheServer().SendMsgToCenterServer(&msg);
		return;
	}
	//3.�ж��Ƿ���Դ�������
    /*pStage =  */theGameWorld.MultiCreateStage( pMessage->MapID, pMessage->EctypeMapID, pMessage->Level, pMessage->ReserveValue,&msg);
	//if(pStage)
	//{
	//	msg.Result = true;
	//	if(msg.PlayerDBID != 0)
	//		GettheServer().SendMsgToCenterServer(&msg);
	//	return;
	//}
	//else
	//{
	//	msg.Result = false;
	//	msg.ErrorID = 5;//��������ʧ��
	//	if(msg.PlayerDBID != 0)
	//		GettheServer().SendMsgToCenterServer(&msg);
	//	return;
	//}
	return;
}
void CenterServerNetEvent::_OnGS2CSCreateMulitStageAck(NetClient* pNetClient, GS2CSCreateMulitStageAck* pMessage )
{
	//���յ����������ɹ�������
	// ���ڱ���������, ����centerserver
	GamePlayer * pPlater = theRunTimeData.GetGamePlayerByDBID(pMessage->PlayerDBID);
	if(!pPlater)
	{
		return;
	}
	else if(!pMessage->Result)
	{
		switch(pMessage->ErrorID)
		{
		case 3:
			pPlater->ShowInfo( false, 251, theXmlString.GetString( eClient_AddInfo_2slk_120 ) );//������ȴ��
			break;
		case 4:
			pPlater->ShowInfo( false, 251, theXmlString.GetString( eClient_AddInfo_2slk_46 ) );
			break;
		}
	}
	else
	{
		GS2CSSwitchStageReq msg;//���������GameServer�ϵĵ�ͼ
		msg.header.stID      = pPlater->GetID();
		msg.nSwitchStageType = SSRT_FlyToMap;
		msg.nMapId           = pMessage->MapID;
		msg.fX               = pMessage->x;
		msg.fY               = pMessage->y;
		msg.fDir             = pMessage->dir;
		msg.nAccountId       = pPlater->GetAccountID();
		msg.nCharacterDbId   = pPlater->GetDBCharacterID();
		msg.dwTime           = HQ_TimeGetTime();
		msg.nServerId        = g_Cfg.dwServerID;
		msg.ustCountryID     = pPlater->GetCountry();
		GettheServer().SendMsgToCenterServer( &msg );
		pPlater->SetFloatZ( WORLD_HEIGHT );     // ��ͼ����ͬ, ����z������
	}
}
void CenterServerNetEvent::_OnCS2GSTeamStateChange(NetClient* pNetClient,CS2GSTeamStateChange* pMessage)
{
	unsigned int TeamID = pMessage->TeamID;
	bool Result = pMessage->Result;
	GameTeam * pTeam = theGameTeamManager.GetTeam(TeamID);
	if(!pTeam)
		return;
	pTeam->SetIsTransnationalTeam(Result);//���ö����״̬
}

void CenterServerNetEvent::_OnCS2GSBroadCast( NetClient* pNetClient, MsgCS2GSBroadCast* pMessage )
{
	if ( !pMessage )
		return;

	if ( pMessage->type == MsgCS2GSBroadCast::Type_Monster )
	{
		BaseCharacter* pChar = theRunTimeData.GetCharacterByMonsterID( pMessage->nMonsterID, pMessage->nMapID );
		if ( !pChar )
			return;

		if ( !pChar->IsDead() )
		{
			MsgGS2CSBroadCastAck msg;
			msg.type = MsgCS2GSBroadCast::Type_Monster;
			msg.nResult = pMessage->nMonsterID;
			GettheServer().SendMsgToCenterServer( &msg );
		}
	}
}

void CenterServerNetEvent::_OnCS2GSChannelInfo( NetClient* pNetClient, MsgChannelInfo* pMessage )
{
	if ( !pMessage )
		return;
	if (pMessage->nChannelsCount <= 0)
	{
		return;
	}
	GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID(pMessage->header.stID);
	if(!pPlayer)
	{
		return;
	}
	GettheServer().SendMsgToSingle(pMessage,pPlayer);

	pPlayer->ApplyBufferStatus  ( g_Cfg.nChannelStatusId, g_Cfg.nChannelStatusLevel, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0 );
	pPlayer->OnBuffStatusChanged( true );

}
void CenterServerNetEvent::_OnCS2GSClearTeamMapReq( NetClient* pNetClient, CS2GSClearTeamMapReq* pMessage )
{
	if(!pMessage)
		return;
	GameTeam * pTeam = theGameTeamManager.GetTeam(pMessage->TeamID);
	if(!pTeam)
		return;
	if(!pTeam->IsTeamHeader(pMessage->PlayerID))
		return;
	unsigned short Sum = pTeam->TeamMemberCount();
	for(int i=0;i<Sum;++i)
	{
		GameTeamMember * pMember = pTeam->GetTeamMemberByIndex(i);
		if(!pMember)
			continue;
		GamePlayer* pMemberPlayer =  pTeam->GetMemberPlayer( pMember->GetID() );
        if ( pMemberPlayer == NULL )
        { continue; }
		MapConfig::MapData* pMap =  theMapConfig.GetMapDataById(pMemberPlayer->GetMapID());
		if(!pMap)
			continue;
		if(pMap->GetMapType() == MapConfig::MT_SingleTeam)
		{
			GS2CSClearTeamMapAck msg;
			msg.Result = false;
			msg.PlayerID = pMessage->PlayerID;
			GettheServer().SendMsgToCenterServer( &msg );
			return;
		}
	}
	//��ո���״̬
	//ѭ��������ǰ��������е�ͼ
	bool releasestage = false;//�Ƿ������õĸ���
	unsigned short MapSum = theMapConfig.MapDataCount();
	for(int i =0;i<MapSum;++i)
	{
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataByIndex(i);
		if(!pMapData || !g_Cfg.IsMapRun( pMapData->Id ) ||  pMapData->GetMapType() != MapConfig::MT_SingleTeam )
			continue;
		uint32 dwEctypeMapID = theGameWorld.MakeEctypeStageIDByTeamID( pMapData,pMessage->TeamID);
		GameStage* pStage = theGameWorld.GetStageById( dwEctypeMapID );
		if(pStage)
		{
			//�д��ڵĵ�ͼ ���Ǵ����
			//������������ø���,���Թ���NPC�����ȫ���ͷŵ��� wqf by cloud
// 			pStage->ReleaseAllCharacter();
// 			GettheWorld().ReleaseTheStage(dwEctypeMapID);
			pStage->SetStageWaitRelease(true,true);//������ѭ�����߼�
			releasestage = true;
		}
	}
	if (releasestage)
	{
		GS2CSClearTeamMapAck msg;
		msg.Result = true;
		msg.PlayerID = pMessage->PlayerID;
		GettheServer().SendMsgToCenterServer( &msg );
	}	
}
void CenterServerNetEvent::_OnCS2GSCharRemoveItembyId( NetClient* pNetClient, MsgCS2GSCharRemoveItembyId* pMessage )
{
	//���� ��ɾ�� ��ҵ��ض���Ʒ
	if ( !pMessage )
		return;
	GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetGamePlayerByDBID(pMessage->characterid);
	if(!pPlayer)
	{
		return;
	}
	pPlayer->RemoveItem( pMessage->nItemId, 1 );
}
void CenterServerNetEvent::_OnCS2GSUpdateReloadCfg( NetClient* pNetClient, MsgCS2GSUpdateReloadCfg* pMessage )
{
	if ( !pMessage )
		return;
	ConfigReloader::ReloadReqMsg msg;
	msg.nReloadType = pMessage->nReloadType;
	theConfigReloader.AddConfigReloadReqMsg(msg);
}