#include "NetEvent.h"
//#include "NetApi.h"
#include "CenterServer.h"
//#include "WindowsUserMessage.h"
#include "CenterServer.h"
#include "GlobalDef.h"
#include "GameServerManager.h"
#include "LoginServerManager.h"
#include "ClientPeerManager.h"
//#include "SessionManager.h"
#include "TeamManager.h"
#include "RelationManager.h"
#include "GlobalFunction.h"
#include "CenterItemDropManager.h"
#include "XmlStringLanguage.h"
#include "ServerStatusManager.h"
#include "ClientPeerManager.h"
#include "GameTime.h"
#include "MailManagerMain.h"
#include "MySqlCommunication.h"
#include "BroadCastManager.h"
#include <stdio.h>

bool NetEvent::OnAccept(TcpServer* pTcpServer, NetClient* pNetClient)
{ 
    CHECK_RETURN( NULL==pNetClient, false );

    //IMeSocket* pSocket = pNetClient->GetSocket();    
    //CHECK_RETURN( NULL==pSocket, false );

    //std::string strPeerIp; 
    //strPeerIp = NetApi::GetPeerIP(pSocket);

    if ( theCenterServer.IsGameServerService(pTcpServer) )
    { }
    //else if ( theCenterServer.IsLoginServer(pTcpServer) )
    //{ }
    return true; 
}

bool NetEvent::OnDisconnect(TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo)
{ 
    if ( pNetClient == NULL )
    { return true; }

    long nServerId = pNetClient->GetExtendIntData();
	
    if ( theCenterServer.IsGameServerService(pTcpServer) )
    {
        theGameServerManager.RemoveGameServerPeer( nServerId );
        //theClientPeerManager.KickClientPeersOnGameServerException( nServerId );
		//theGameServerManager.CheckQueue(theClientPeerManager.ClientPeerSize(),true);
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,  "theGameServerManager.RemoveGameServerPeer(%d)",  nServerId/*NetApi::GetPeerIP(pNetClient->GetSocket()).c_str()*/ );
    }
    //else if ( theCenterServer.IsLoginServerService(pTcpServer) )
    //{
    //    theLoginServerManager.RemoveLoginServerPeer( nServerId );
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,  "LoginServerManager::GetInstance().RemoveLoginServerPeer(%d)", nServerId);
    //}
    return true;
}

long NetEvent::OnProcessDefaultMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "Receive Message[%d]",  msgType);
	//if (msgType == CS2GS_PING)
	//{
	//	_OnGS2CSPing(pNetClient,(CS2GSPing*)pMessage);
	//	return ER_Success;
	//}
    MESSAGE_MAPPING_BEGIN
        // Common
        MESSAGE_HANDLE( MSG_SELECTCHANNEL_SS,               MsgS2SSelectChannel,                _OnSSSelectChannel                  );

		// LoginServer
        MESSAGE_HANDLE( MSG_LOGININFO,                      MsgLoginInfo,                       _OnLoginInfo                        );
        MESSAGE_HANDLE( LS2CS_REGISTERLOGINSERVERINFO_REQ,  LS2CSRegiseterLoginServerInfoReq,   _OnRegiseterLoginServerInfo         );

        // GameServer
        MESSAGE_HANDLE( GS2CS_REGISTERGAMESERVERINFO_REQ,   GS2CSRegiseterGameServerInfoReq,    _OnRegisterGameServerInfo           );
        MESSAGE_HANDLE_NOTCHECK( UPDATEMAPINFO,             MessageUpdateMapInfo,               _OnMessageUpdateMapInfo             );
        MESSAGE_HANDLE( S2S_SWITCHGATE,                     S2SSwitchGate,                      _OnS2SSwitchGate                    );
        MESSAGE_HANDLE( MSG_GWBURTHEN,                      MsgGWBurthen,                       _OnUpdateBurthen                    );
        MESSAGE_HANDLE( GS2CS_SWITCHSTAGEREQ,               GS2CSSwitchStageReq,                _OnSwitchStageReq                   );
        MESSAGE_HANDLE( GS2CS_PLAYEREXITGAMESERVER,         GS2CSPlayerExit,                    _OnGS2CSPlayerExit                  );
        MESSAGE_HANDLE( GS2CS_PLAYERSYNINSERVERINFO,        GS2CSPlayerSynInServerInfo,         _OnGS2CSPlayerSynInServerInfo       );
        MESSAGE_HANDLE( GS2CS_PLAYERTEAMINVITEEREQ,         GS2CSPlayerTeamInviteeReq,          _OnMsgGS2CSPlayerTeamInviteeReq     );
		MESSAGE_HANDLE( GS2CS_CREATETEAM,			        GS2CSCreateTeam,					_OnMsgGS2CSCreateTeam     );
        MESSAGE_HANDLE( GS2CS_PLAYERTEAMINVITEEACK,         GS2CSPlayerTeamInviteeAck,          _OnMsgGS2CSPlayerTeamInviteeAck     );
        MESSAGE_HANDLE( GS2CS_PLAYERUPDATETEAMMEMBERINFO,   GS2CSPlayerUpdateTeamMemberInfo,    _OnMsgGS2CSPlayerUpdateTeamMember   );
        MESSAGE_HANDLE( GS2CS_PLAYERREMOVEFROMTEAMREQ,      GS2CSPlayerRemoveFromTeamReq,       _OnMsgGS2CSPlayerRemoveFromTeamReq  );
		MESSAGE_HANDLE( GS2CS_DISBANDTEAM,					GS2CSPlayerDisbandTeam,				_OnMsgGS2CSPlayerDisbandTeam		);
        MESSAGE_HANDLE( GS2CS_PLAYERUPGRADETEAMREQ,         GS2CSPlayerUpgradeTeamReq,          _OnMsgGS2CSPlayerUpgradeTeamReq     );
        MESSAGE_HANDLE( GS2CS_TEAMCHANGEASSIGNMODEREQ,      GS2CSTeamChangeAssignModeReq,       _OnMsgGS2CSTeamChangeAssignReq      );
        MESSAGE_HANDLE( GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ, GS2CSTeamChangeAssignItemLevelReq,  _OnMsgGS2CSTeamChangeItemLevelReq   );   
        MESSAGE_HANDLE( GS2CS_TEAMONLINE,                   GS2CSTeamOnLine,                    _OnMsgGS2CSTeamOnLine               );
        MESSAGE_HANDLE( GS2CS_PLAYERCHATMESSAGE,            GS2CSPlayerChatMessage,             _OnMsgGS2CSPlayerChatMessage        );
        MESSAGE_HANDLE( GS2CS_QUERYPLAYERINFOREQ,           GS2CSQueryPlayerInfoReq,            _OnMsgGS2CSQueryPlayerInfoReq       );
        MESSAGE_HANDLE( GS2CS_QUERYPLAYERINFOACK,           GS2CSQueryPlayerInfoAck,            _OnMsgGS2CSQueryPlayerInfoAck       );
        MESSAGE_HANDLE( MSG_OUT_OF_LONGIN_TIME,             MsgConnectGateOverTime,             _OnProcessOutOfLoginTimeMsg         );
        MESSAGE_HANDLE( MSG_CHANGEMAPCALLBACK,              MsgChangeMapCallBack,               _OnMsgChangeMapCallBack);

        MESSAGE_HANDLE ( GS2GS_BANSPEAK,                        GS2GSBanSpeak,                        _OnMsgGS2GSBanSpeak                        );
        MESSAGE_HANDLE ( GS2GS_CALLPALYER,                      GS2GSCallPlayer,                      _OnMsgGS2GSCallPlayer                      );
        MESSAGE_HANDLE_NOTCHECK( GS2CS_TRANSMIT,                S2STransmit,                          _OnProcessTransmitMsg                      );
        //MESSAGE_HANDLE ( DB2CS_ACCOUNTPOINTER_ACK,              DB2CSAccountPoints,                   _OnDB2CSAccountPoints                      );
        //MESSAGE_HANDLE ( GS2CS_DRAWFROMPLATFORM_QUERY,          GS2CSDrawFromPlatformQuery,           _OnMsgCS2GSGS2CSDrawFromPlatformQuery      );
        MESSAGE_HANDLE ( S2S_UPDATEDROPITEMCONTROL,             S2SMsgUpdateItemDropControl,          _OnMsgUpdateItemDropControl                );
        //MESSAGE_HANDLE( GS2CS_MONEYITEMEXCHANGE,                GS2CSMoneyItemExchange,               _OnGS2CSMoneyItemExchange                  );
        //MESSAGE_HANDLE( DBMSG_ACKCREATECHAR,                    DBMsgCreateCharAck,                   _OnDBMsgCreateCharAck                      );
        MESSAGE_HANDLE( MSG_REGISTERSERVERACK,                  MsgRegisterServerAck,                 _OnMsgRegisterServerAck                    );
        MESSAGE_HANDLE( MSG_SERVERSTATUSACK,                    MsgServerStatusAck,                   _OnMsgServerStatusAck                      );
        MESSAGE_HANDLE( DBMSG_KICKCHARACK,                      S2SMsgKickCharAck,                    _OnS2SMsgKickCharAck                       );
        MESSAGE_HANDLE( GS2CS_MAILLISTREQ,                      GS2CSMailListReq,                     _OnGS2CSMailListReq                        );
        MESSAGE_HANDLE( GS2CS_SENDMAILREQ,                      GS2CSSendMailReq,                     _OnGS2CSSendMailReq                        );        
        MESSAGE_HANDLE( GS2CS_OPMAILREQ,                        GS2CSOpMailReq,                       _OnGS2CSOpMailReq                          );
        MESSAGE_HANDLE( GS2CS_QUERYMAILCANSENDREQ,              GS2CSQueryMailCanSendReq,             _OnGS2CSQueryMailCanSendReq                );
        MESSAGE_HANDLE( S2S_REMOTEBANREQ,                       S2SRemoteBanReq,                      _OnS2SRemoteBanReq                         ); 
        MESSAGE_HANDLE_NOTCHECK( S2S_RECORDCHATCONTENT,         S2SRecordChatContent,                 _OnS2SRecordChatContent                    );
        MESSAGE_HANDLE( CS2GS_REWARDOPERATE,                    CS2GSMsgRewardOperate,                _OnCS2GSMsgRewardOperate                   );
        MESSAGE_HANDLE( GS2CS_SENDCHANGEVARREQ,                 GS2CSSendChangeVarReq,                _OnGS2CSSendChangeVarReq                   ); // ����ϵͳ�����ı�
		MESSAGE_HANDLE( GS2CS_UPDATEANTIADDICTIONINFOREQ,       GS2CSUpdateAntiaddictionInfoReq,      _OnGS2CSUpdateAntiaddictionInfoReq         );
		MESSAGE_HANDLE( CS2GS_PING,								CS2GSPing,							  _OnGS2CSPing         );
		MESSAGE_HANDLE( TO_CENTER_LOGIN_ON,						MsgCenterLoginOn,                     _OnMsgCenterLoginOn         );
		MESSAGE_HANDLE( TO_CENTER_LOGIN_KICK,					MsgCenterKick,                        _OnMsgCenterLoginKick         );
		MESSAGE_HANDLE( MSG_PINGSERVER,							MsgPingServer,                        _OnCommonPing         );
		MESSAGE_HANDLE( CS2GS_PLATFORMSENDMAILACK,				MsgPFSendmailAck,                     _OnMsggPFSendMailAck         );
		MESSAGE_HANDLE( GS2CS_ASKFORPRESENT,					MsgGS2CSAskForPresent,                _OnMsgAskForPresent         );
		MESSAGE_HANDLE( GS2CS_ASKFORPLATFORMACTIVITY,			MsgGS2CsAskForPlatformActivity,       _OnMsgAskForPlatformActivity         );

		MESSAGE_HANDLE( GS2CS_CREATEMULITSTAGEREQ,				GS2CSCreateMulitStageReq,			 _OnGS2CSCreateMulitStageReq);
		MESSAGE_HANDLE( GS2CS_CREATEMULITSTAGEACK,				GS2CSCreateMulitStageAck,			 _OnGS2CSCreateMulitStageAck);
		MESSAGE_HANDLE( GS2CS_ASKBROADCAST_ACK,					MsgGS2CSBroadCastAck,				 _OnGS2CSBroadCastAck );

		MESSAGE_HANDLE( GS2CS_CLEARTEAMMAPREQ,					GS2CSClearTeamMapReq,				 _OnGS2CSClearTeamMapReq );
		MESSAGE_HANDLE( GS2CS_CLEARTEAMMAPACK,					GS2CSClearTeamMapAck,				 _OnGS2CSClearTeamMapAck );
		MESSAGE_HANDLE( GS2CS_REQ_EPISTARPOINT,					MsgGS2CSEpistarPoint,				 _OnGS2CSEpistarPointReq );
		

		
        default:
            {
                return ER_Failed;
            }
            break;
    MESSAGE_MAPPING_END
    return ER_Success;
}

long NetEvent::OnMessageIncoming(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    uint32 result = ER_Success;
    switch ( pMessage->GetModuleType() )
    {
    case EMessageModule_Default:
        result = OnProcessDefaultMessage( pTcpServer, pNetClient, msgType, pMessage );
        break;
    case EMessageModule_Relation: // �����ϵ��Ϣ
        result = OnProcessRelationMessage( pTcpServer, pNetClient, msgType, pMessage );
        break;
    case EMessageModule_Country:  // ���������Ϣ 
        result = OnProcessCountryMessage( pTcpServer, pNetClient, msgType, pMessage ); 
        break;
    case EMessageModule_Guild:    // �����ϵ��Ϣ
        result = OnProcessGuildMessage( pTcpServer, pNetClient, msgType, pMessage ); 
        break;
    case EMessageModule_Consignment:
        result = OnProcessConsignmentMessage( pTcpServer, pNetClient, msgType, pMessage );
        break;
	case EMessageModule_Family:    // ���������Ϣ
		result = OnProcessFamilyMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;
	case EMessageModule_LEVELLIMIT://�ȼ���ӡ
		result = OnProcessLevelLimitMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;
	case EMessageModule_GolbalDB:
		result = OnProcessGlobalDBMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;
	//xuda 
	/*case EMessageModule_Wanted:
		result = OnProcessWantedMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;
	case EMessageModule_Emperor:
		result = OnProcessEmperorMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;*/
	case EMessageModule_QuestEntrust:
		result = OnProcessQuestEntrustMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;
	case EMessageModule_GameBattle:
		result =OnProcessGameBattleMessage( pTcpServer, pNetClient, msgType, pMessage );
		break;
    default:
        result = ER_Failed;
        break;
    }
    
    return ER_Success;
}

void NetEvent::_OnSSSelectChannel( NetClient* pNetClient, MsgS2SSelectChannel* pMessage )
{   
    GameServerPeer* pGameServerPeer = theGameServerManager.GetGameServerPeer( pMessage->channel.nServerId );
    if ( !pGameServerPeer )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_OnSSSelectChannel GetGameServerPeer ServerId[%d] not found", pMessage->channel.nServerId);
        return;
    }
   
    ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeer( pMessage->nAccountId );
    if ( !pClientPeer )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_OnSSSelectChannel GetClientPeer AccountId[%d] not found", pMessage->nAccountId);
        return;
    }

    pClientPeer->ProcessMessage( pNetClient, pMessage );
}

void NetEvent::_OnLoginInfo( NetClient* pNetClient, MsgLoginInfo* pMessage )
{

	//printf("2,keylogin:recv login server login info:%d\n",HQ_TimeGetTime());
	long lResult = theClientPeerManager.AddLoginClientPeer( pMessage->nAccountID, pMessage->szAccount, pMessage->SessionKey, 
		/*pMessage->Password,*/ /*pMessage->Seed, */pMessage->szMac,pMessage->isWallow );

#ifdef __NEW_LOGIN__
    //������loginserver��login
    //long lResult = ClientPeerManager::GetInstance().OnClientPeerLogin( pMessage->nAccountID, pMessage->szAccount, pMessage->SessionKey
    //                                                                  ,pMessage->Password,pMessage->SessionKey);
#else	
//      lResult = ClientPeerManager::GetInstance().OnClientPeerLogin( pMessage->szIP, pMessage->nAccountID, pMessage->szAccount, 
//          pMessage->SessionKey, pNetClient->GetExtendIntData(), pMessage->header.stID ,pMessage->IsForceLogin);
#endif
	 if ( RESULT_FAILED(lResult) )
	 {
		 LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"�û������½ʧ�� [%s][%d][%s] Error[%d]", pMessage->szIP, pMessage->nAccountID,  pMessage->szAccount, lResult);
	 }
}

void NetEvent::_OnMessageUpdateMapInfo( NetClient* pNetClient, MessageUpdateMapInfo* pMessage )
{
    if ( pNetClient == NULL || pMessage == NULL )
    { return; }

    unsigned long nServerId = pNetClient->GetExtendIntData();
    GameServerPeer* pGamePeer = theGameServerManager.GetGameServerPeer( nServerId );
    if ( pGamePeer != NULL )
    {
        pGamePeer->OnMessageUpdateMapInfo( pMessage );
    }
}

void NetEvent::_OnUpdateBurthen( NetClient* pNetClient, MsgGWBurthen* pMessage )
{
    unsigned long nServerId = pNetClient->GetExtendIntData();

    GameServerPeer* pGamePeer = theGameServerManager.GetGameServerPeer( nServerId );
    if (  pGamePeer == NULL )
    { return; }

    SBurthenBase info;
    info.nCurrentPlayerCount  = pMessage->nCurrOnline;
    info.nMaxPlayerCount      = pMessage->nMaxOnline;
    info.nGateCount           = pMessage->nGateCount;
    pGamePeer->UpdateBurthen( info );

	//#ifdef _USE_SQL
 //   if ( !CenterServer::GetInstance().GetSqlService().IsEnableService() && theGameServerManager.IsAllGameServerReady() )
 //   { // �����û����gls��ʼ����  ���з������Ѿ�Ready
 //       // ��ʼgls����
 //        CenterServer::GetInstance().GetSqlService().EnableService(); 
 //   }
	//#endif
}

void NetEvent::_OnS2SSwitchGate( NetClient* pNetClient, S2SSwitchGate* pMessage )
{
    ClientPeer* pClientPeer = NULL;
    switch ( pMessage->nSourcePeerInServerType )
    {
    case ST_LoginServer:
        { pClientPeer = theClientPeerManager.GetClientPeerFromLoginQueue( pMessage->nAccountId ); }
        break;
    default:
        { pClientPeer = theClientPeerManager.GetClientPeer( pMessage->nAccountId ); }
        break;
    }

    if ( NULL == pClientPeer)
    { return; }

    pClientPeer->ProcessMessage( pNetClient, pMessage );
}

void NetEvent::_OnSwitchStageReq( NetClient* pNetClient, GS2CSSwitchStageReq* pMessage )
{
    ClientPeer* pClientPeer = theClientPeerManager.GetClientPeer( pMessage->nAccountId );
    if ( NULL == pClientPeer)
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"_OnSwitchStageReq(%u:%u:%u) can't find", pMessage->nAccountId, pMessage->nCharacterDbId, pMessage->nMapId);
        return;
    }
    pClientPeer->ProcessMessage( pNetClient, pMessage );
}

void NetEvent::_OnGS2CSPlayerExit( NetClient* pNetClient, GS2CSPlayerExit* pMessage )
{
    theClientPeerManager.OnPlayerExit( pMessage );
}

void NetEvent::_OnGS2CSPlayerSynInServerInfo( NetClient* pNetClient, GS2CSPlayerSynInServerInfo* pMessage )
{
    long nResult = theClientPeerManager.OnPlayerSynInServerInfo( pMessage );
    if ( nResult == ER_ClientPeerNotExist )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnGS2CSPlayerSynInServerInfo not find(%ld,%ld,%s)",pMessage->nAccountId, pMessage->nCharacterDbId, pMessage->szCharacterName );
        // ToDo Kick

    }
}

void NetEvent::_OnProcessTransmitMsg( NetClient* pNetClient, S2STransmit* pMessage )
{
    unsigned long nResult = S2STransmitResult::ETR_Success;

    Msg* pMsg = (Msg*)pMessage->buffer;
    unsigned long nMsgType = pMsg->GetType();    
    switch( pMessage->ucSessionType )
    {
    case S2STransmit::SESSIONT_World:
        { 
            theGameServerManager.SendMsgToWorld( pMessage ); 
        }
        break;
    case S2STransmit::SESSTONT_Single:
        {
            // ת����Ŀ��
            long result = theGameServerManager.SendMsgToSingle( pMessage, pMessage->targetData.character.uDbId, pMessage->targetData.character.szName);
            if ( result != ER_Success)
            { // ת����Ŀ��ʧ��
                if ( pMessage->identifyId != InvalidLogicNumber)
                { // ��Ҫ����
                    S2STransmitResult msg;
                    msg.identifyId                 = pMessage->identifyId;
                    msg.nResult                    = S2STransmitResult::ETR_ClientPeerNotExist;
                    msg.ucSessionType              = pMessage->ucSessionType;
                    msg.msgType                    = nMsgType;
                    msg.targetData.character.uDbId = pMessage->targetData.character.uDbId;
                    strncpy_s( msg.targetData.character.szName, sizeof( msg.targetData.character.szName ), pMessage->targetData.character.szName, sizeof(msg.targetData.character.szName) - 1);
                    theGameServerManager.SendMsgToSingle( &msg, pMessage->identifyId );
                }
            }
        }
        break;
    case S2STransmit::SESSIONT_Team:
        {
            CenterTeam* pCenterTeam = theCenterTeamManager.GetTeam( pMessage->targetData.team.dwSessionID );
            if ( pCenterTeam != NULL )
            {
                pCenterTeam->SendMessageToTeamClient( pMessage, pNetClient->GetExtendIntData(), TeamDefine::SendToSomeGame );
            }
        }
        
        break;
    case S2STransmit::SESSIONT_Guild:
        {
            theGameServerManager.SendMessageToGameServers( pMessage, pNetClient->GetExtendIntData() );
        }
        break;
    case S2STransmit::SESSIONT_Server:
        {
            if ( pMessage->targetData.server.exceptMe == 1)
            { theGameServerManager.SendMessageToGameServers( pMessage, pNetClient->GetExtendIntData() ); }
            else
            { theGameServerManager.SendMessageToGameServers( pMessage ); }
            
        }
        break;
    case S2STransmit::SESSIONT_Country:
        {
            theGameServerManager.SendMessageToGameServers( pMessage, pNetClient->GetExtendIntData() );
        }
        break;
    default:
        theGameServerManager.SendMessageToGameServers( pMessage, pNetClient->GetExtendIntData() );
        break;
    }
    return;
}

void NetEvent::_OnMsgCenterLoginOn( NetClient* pNetClient, MsgCenterLoginOn* pMessage)
{
#ifndef _USE_SQL
	//theCenterServer.GetSqlService().PushUserLoginOn( pMessage->sql );
#endif
}

void NetEvent::_OnMsgCenterLoginKick( NetClient* pNetClient, MsgCenterKick* pMessage)
{
#ifndef _USE_SQL
	//theCenterServer.GetSqlService().PushUserKick( pMessage->sql );
#endif
}

// �������˶���
void NetEvent::_OnMsgGS2CSCreateTeam( NetClient* pNetClient, GS2CSCreateTeam* pMessage )
{
	CenterTeam* pReqTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwReqID );
	if ( pReqTeam )	// �ж�����
	{ return; }

	// ��������
	uint32 dwTeamSessionID = theCenterTeamManager.CreateTeamSessionID();
	pReqTeam = theCenterTeamManager.CreateTeam( dwTeamSessionID, pMessage->AssignMode, pMessage->AssignItemLevel );
	if ( pReqTeam == NULL )
	{ return; }

	// ��ӳ�Ա
	CenterTeamMember xReqMember;
	xReqMember.SetID( pMessage->dwReqID );
	xReqMember.SetName( pMessage->szReqName );

	TeamDefine::TeamInvite xRecord;
	xRecord.dwReqID         = pMessage->dwReqID;
	xRecord.nHp             = pMessage->nHp;
	xRecord.nHpMax          = pMessage->nHpMax;
	xRecord.nMp             = pMessage->nMp;
	xRecord.nMpMax          = pMessage->nMpMax;
	xRecord.stLevel         = pMessage->stLevel;
	xRecord.chProfession    = pMessage->chProfession;
	xRecord.chSex           = pMessage->chSex;
	xRecord.nFaceId         = pMessage->nFaceId;
	xRecord.nHairId         = pMessage->nHairId;
	xRecord.nHeadPicId      = pMessage->nHeadPicId;
	xRecord.AssignMode      = pMessage->AssignMode;
	xRecord.AssignItemLevel = pMessage->AssignItemLevel;
	strncpy_s( xRecord.szReqName, sizeof( xRecord.szReqName ), pMessage->szReqName, sizeof( xRecord.szAckName ) - 1 );

	pReqTeam->SetTeamHeaderID( pMessage->dwReqID );
	pReqTeam->AddTeamMember( xReqMember, theCenterTeamManager, &xRecord );
}

//�������
void NetEvent::_OnMsgGS2CSPlayerTeamInviteeReq(NetClient* pNetClient, GS2CSPlayerTeamInviteeReq* pMessage)
{
    ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByName( pMessage->szAckName );
    if ( pClientPeer == NULL ) 
    { 
        MsgAckJoinTeam xJoinMsg;
        HelperFunc::SafeNCpy( xJoinMsg.name, pMessage->szAckName, sizeof( xJoinMsg.name ) );
        xJoinMsg.stError = MsgAckJoinTeam::error_cannotfindtarget;
        theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwReqID, pMessage->szReqName );
		/*printf("team:error_cannotfindtarget");*/
        return; 
    }

    if ( pClientPeer->GetCountry() != pMessage->uchCountry && !pMessage->countryTeam)
    {
        MsgAckJoinTeam xJoinMsg;
        HelperFunc::SafeNCpy( xJoinMsg.name, pMessage->szAckName, sizeof( xJoinMsg.name ) );
        xJoinMsg.stError = MsgAckJoinTeam::error_notsamecountry;
        theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwReqID, pMessage->szReqName );
		/*printf("team:error_notsamecountry");*/
        return;
    }
	
    TeamDefine::TeamInvite* pInvite = theCenterTeamManager.GetInviteRecord( pMessage->szAckName, pMessage->dwReqID );
    if ( pInvite != NULL )  // �Ѿ���������, �������ó�ʱʱ��, ��������Ϣ
    {
        pInvite->dwTimeOut = HQ_TimeGetTime();
		/*printf("team:already have team");*/
        return;
    }

    TeamDefine::TeamInvite xRecord;
    strncpy_s( xRecord.szAckName, sizeof( xRecord.szAckName ), pMessage->szAckName, sizeof( xRecord.szAckName ) - 1 );
    strncpy_s( xRecord.szReqName, sizeof( xRecord.szReqName ), pMessage->szReqName, sizeof( xRecord.szReqName ) - 1 );
    xRecord.dwReqID         = pMessage->dwReqID;
    xRecord.nHp             = pMessage->nHp;
    xRecord.nHpMax          = pMessage->nHpMax;
    xRecord.nMp             = pMessage->nMp;
    xRecord.nMpMax          = pMessage->nMpMax;
    xRecord.stLevel         = pMessage->stLevel;
    xRecord.chProfession    = pMessage->chProfession;
    xRecord.chSex           = pMessage->chSex;
    xRecord.nFaceId         = pMessage->nFaceId;
    xRecord.nHairId         = pMessage->nHairId;
    xRecord.nHeadPicId      = pMessage->nHeadPicId;
    xRecord.AssignMode      = pMessage->AssignMode;
    xRecord.AssignItemLevel = pMessage->AssignItemLevel;
    xRecord.dwTimeOut       = HQ_TimeGetTime();
    xRecord.chInviteType    = TeamDefine::TeamInvite::ECD_Invite;

    // �ж������ߵĶ�����Ϣ
    CenterTeam* pReqTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwReqID );
    CenterTeam* pAckTeam = theCenterTeamManager.GetTeamByMemberID( pClientPeer->GetCharDbId() );
    if ( pReqTeam != NULL )     // �������ж���
    {
        if( pAckTeam != NULL )          // ���������ж���
        { 
            MsgAckJoinTeam xJoinMsg;
            HelperFunc::SafeNCpy( xJoinMsg.name, pMessage->szAckName, sizeof( xJoinMsg.name ) );
            xJoinMsg.stError = MsgAckJoinTeam::error_targetalreadyinTeam;
            theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwReqID, pMessage->szReqName );
			/*printf("team:error_targetalreadyinTeam");*/
            return; 
        }
		//����Ӧ�ý������ߵ�ID ת��Ϊ����Ķӳ���ID
		if(pMessage->dwReqID  != pReqTeam->GetTeamHeaderID())
			pMessage->dwReqID = pReqTeam->GetTeamHeaderID();

        unsigned short stResult = pReqTeam->IsCanInviteJoinInTeam( pMessage->dwReqID, pClientPeer->GetCharDbId() );
        if ( stResult == TeamDefine::CanJoinTeam )
        {
            // ��������
            MsgInquireInvitee xInviteeMsg;
            xInviteeMsg.dwReqID         = pMessage->dwReqID;
            xInviteeMsg.chProfession    = pMessage->chProfession;
            xInviteeMsg.stLevel         = pMessage->stLevel;
            xInviteeMsg.AssignMode      = pReqTeam->GetTeamAssignModeType();
            xInviteeMsg.IsCorps         = pReqTeam->GetTeamCrops();
            xInviteeMsg.AssignItemLevel = pReqTeam->GetTeamAssignItemLevel();
			xInviteeMsg.nSex			= pMessage->chSex;
            HelperFunc::SafeNCpy( xInviteeMsg.szReqName, pMessage->szReqName, sizeof( xInviteeMsg.szReqName ) );
            theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xInviteeMsg, pClientPeer->GetCharDbId(), pMessage->szAckName, false );

            // ��Ӽ�¼
            xRecord.AssignMode      = pReqTeam->GetTeamAssignModeType();
            xRecord.AssignItemLevel = pReqTeam->GetTeamAssignItemLevel();
            theCenterTeamManager.AddInviteRecord( xRecord );
        }
        else
        {
            MsgAckJoinTeam xJoinMsg;
            xJoinMsg.stError = stResult;
            theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwReqID );
			/*printf("TeamErro:InvalidLogicNumber");*/
        }

        return;
    }

    if ( pAckTeam != NULL )         // ����������
    {
        unsigned short stResult = pAckTeam->IsCanRequestJoinInTeam( pMessage->dwReqID );
        if ( stResult == TeamDefine::CanJoinTeam )
        {
            // ��������
            MsgInquireInvitee xInviteeMsg;
            xInviteeMsg.dwReqID         = pMessage->dwReqID;
            xInviteeMsg.chProfession    = pMessage->chProfession;
            xInviteeMsg.stLevel         = pMessage->stLevel;
            xInviteeMsg.AssignMode      = pAckTeam->GetTeamAssignModeType();
            xInviteeMsg.IsCorps         = pAckTeam->GetTeamCrops();
            xInviteeMsg.AssignItemLevel = pAckTeam->GetTeamAssignItemLevel();
			xInviteeMsg.nSex			= pMessage->chSex;
            HelperFunc::SafeNCpy( xInviteeMsg.szReqName, pMessage->szReqName, sizeof( xInviteeMsg.szReqName ) );
            theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xInviteeMsg, pAckTeam->GetTeamHeaderID(), "", false );

            // ��Ӽ�¼A
            CenterTeamMember* pMember = pAckTeam->GetTeamMemberByID( pAckTeam->GetTeamHeaderID() );
            if ( pMember != NULL )
            {
                HelperFunc::SafeNCpy( xRecord.szAckName, pMember->GetName(), sizeof( xRecord.szAckName ) );
            }
            xRecord.AssignMode      = pAckTeam->GetTeamAssignModeType();
            xRecord.AssignItemLevel = pAckTeam->GetTeamAssignItemLevel();
            xRecord.chInviteType    = TeamDefine::TeamInvite::ECD_Request;
            theCenterTeamManager.AddInviteRecord( xRecord );
        }
        else
        {
            MsgAckJoinTeam xJoinMsg;
            xJoinMsg.stError = stResult;
            theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwReqID );
			/*printf("team:InvalidLogicNumber breakpoint2");*/
        }

        return;
    }

    MsgInquireInvitee xInviteeMsg;
    xInviteeMsg.dwReqID         = pMessage->dwReqID;
    xInviteeMsg.AssignMode      = pMessage->AssignMode;
    xInviteeMsg.chProfession    = pMessage->chProfession;
    xInviteeMsg.stLevel         = pMessage->stLevel;
    xInviteeMsg.IsCorps         = false;
    xInviteeMsg.AssignItemLevel = pMessage->AssignItemLevel;
	xInviteeMsg.nSex			= pMessage->chSex;
    HelperFunc::SafeNCpy( xInviteeMsg.szReqName, pMessage->szReqName, sizeof( xInviteeMsg.szReqName ) );
    theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xInviteeMsg, pClientPeer->GetCharDbId(), pMessage->szAckName, false );

    // ��������¼
    theCenterTeamManager.AddInviteRecord( xRecord );
}

//������ӻظ�
void NetEvent::_OnMsgGS2CSPlayerTeamInviteeAck( NetClient* pNetClient, GS2CSPlayerTeamInviteeAck* pMessage )
{
	TeamDefine::TeamInvite* pRecord = theCenterTeamManager.GetInviteRecord( pMessage->szAckName, pMessage->dwReqID );
	/*
	 * Author:	2012-8-25 wangshuai
	 * Desc: 	�ж���ָ��
	 */
	if (pRecord == NULL)
		return;

	// ����Է���ͬ�⣬��ɾ�������¼
	if ( pMessage->bAgree == MsgAckInquireInvitee::result_nonAgree )
	{
		
		if ( pRecord != NULL )			// ������������¼����ɾ��
		{		
			TeamDefine::TeamInvite xRecord = *pRecord;
			theCenterTeamManager.RemoveInviteRecord( pMessage->szAckName, pMessage->dwReqID );
			return;
		}
	}
	else
	{
		// ������ͬ�⣬�ж������Ƿ�ʱ

		if ( pRecord == NULL )			// ��ʱ��
		{ return; }

	}

	TeamDefine::TeamInvite xRecord = *pRecord;
	theCenterTeamManager.RemoveInviteRecord( pMessage->szAckName, pMessage->dwReqID );

    CenterTeamMember xAckMember;
    xAckMember.SetID( pMessage->dwAckID );
    xAckMember.SetName( pMessage->szAckName );

    CenterTeam* pAckTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwAckID );       // �����߶���
    CenterTeam* pReqTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwReqID );       // �����߶���

    if ( xRecord.chInviteType == TeamDefine::TeamInvite::ECD_Invite )
    {
        if( pAckTeam != NULL )          // ���������Ѿ��ж�����
        { return; }

        if ( pReqTeam == NULL )         // ��û�ж���,�ȴ���һ������
        {
            uint32 dwTeamSessionID = theCenterTeamManager.CreateTeamSessionID();
            pReqTeam = theCenterTeamManager.CreateTeam( dwTeamSessionID, xRecord.AssignMode, xRecord.AssignItemLevel );
            if ( pReqTeam == NULL )
            { return; }

            // ����������
            CenterTeamMember xReqMember;
            xReqMember.SetID( xRecord.dwReqID );
            xReqMember.SetName( xRecord.szReqName );
 
            pReqTeam->SetTeamHeaderID( xRecord.dwReqID );
            pReqTeam->AddTeamMember( xReqMember, theCenterTeamManager, &xRecord );
        }

		MsgAckJoinTeam xJoinMsg;
		HelperFunc::SafeNCpy( xJoinMsg.name, xRecord.szReqName, sizeof( xJoinMsg.name ) );
		xJoinMsg.stError = MsgAckJoinTeam::success_addTeam;
		if ( pReqTeam->IsTeamFull() )
			xJoinMsg.stError = MsgAckJoinTeam::error_Teamisfull;
		theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwAckID, xRecord.szReqName );

        // ���뱻������
        xRecord.nHp          = pMessage->nHp;
        xRecord.nMp          = pMessage->nMp;
        xRecord.nHpMax       = pMessage->nHpMax;
        xRecord.nMpMax       = pMessage->nMpMax;
        xRecord.stLevel      = pMessage->stLevel;
        xRecord.chProfession = pMessage->chProfession;
        xRecord.chSex        = pMessage->chSex;
        xRecord.nFaceId      = pMessage->nFaceId;
        xRecord.nHairId      = pMessage->nHairId;
        xRecord.nHeadPicId   = pMessage->nHeadPicId;
        pReqTeam->AddTeamMember( xAckMember, theCenterTeamManager, &xRecord );
    }
    else
    {
        if ( pReqTeam != NULL )         // �������Ѿ��ж�����
        { return; }

        // �ӳ��Ѿ�û�ж��� �����Ѿ����Ƕӳ���
        if( pAckTeam == NULL || !pAckTeam->IsTeamHeader( pMessage->dwAckID ) )          
        { return; }

		MsgAckJoinTeam xJoinMsg;
		HelperFunc::SafeNCpy( xJoinMsg.name, pMessage->szAckName, sizeof( xJoinMsg.name ) );
		xJoinMsg.stError = MsgAckJoinTeam::success_addTeam;
		if ( pAckTeam->IsTeamFull() )
			xJoinMsg.stError = MsgAckJoinTeam::error_Teamisfull;
		theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xJoinMsg, pMessage->dwReqID, pMessage->szAckName );

        CenterTeamMember xReqMember;
        xReqMember.SetID( xRecord.dwReqID );
        xReqMember.SetName( xRecord.szReqName );

        pAckTeam->AddTeamMember( xReqMember, theCenterTeamManager, &xRecord );

// 		if ( NULL == pAckTeam )
// 		{// ����������û����,����һ������
// 			uint32 dwTeamSessionID = theCenterTeamManager.CreateTeamSessionID();
// 			pAckTeam = theCenterTeamManager.CreateTeam( dwTeamSessionID, xRecord.AssignMode, xRecord.AssignItemLevel );
// 			if ( pAckTeam == NULL )
// 			{ return; }
// 
// 			pAckTeam->AddTeamMember( xAckMember, theCenterTeamManager, &xRecord );
// 			pAckTeam->SetTeamHeaderID( pMessage->dwAckID );
// 		}
// 
// 		// ����������
// 		xRecord.nHp          = pMessage->nHp;
// 		xRecord.nMp          = pMessage->nMp;
// 		xRecord.nHpMax       = pMessage->nHpMax;
// 		xRecord.nMpMax       = pMessage->nMpMax;
// 		xRecord.stLevel      = pMessage->stLevel;
// 		xRecord.chProfession = pMessage->chProfession;
// 		xRecord.chSex        = pMessage->chSex;
// 		xRecord.nFaceId      = pMessage->nFaceId;
// 		xRecord.nHairId      = pMessage->nHairId;
// 		xRecord.nHeadPicId   = pMessage->nHeadPicId;
// 
// 		CenterTeamMember xReqMember;
// 		xReqMember.SetID( xRecord.dwReqID );
// 		xReqMember.SetName( xRecord.szReqName );
// 		pAckTeam->AddTeamMember( xReqMember, theCenterTeamManager, &xRecord );
    }
}

//���¶����Ա��Ϣ
void NetEvent::_OnMsgGS2CSPlayerUpdateTeamMember(NetClient* pNetClient, GS2CSPlayerUpdateTeamMemberInfo* pMessage)
{
    if ( pNetClient == NULL || pMessage == NULL )
    { return; }

    //���ҳ����������ڵķ�����
    CenterTeam* pTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwDataBaseId );
    if( pTeam != NULL )
    {
        pTeam->SendMessageToTeamClient( pMessage, pNetClient->GetExtendIntData(), TeamDefine::SendToSomeGame );
    }
}

//�������Ϊ�л�����������T�Ķ���,��Ҫɾ���Ự����
void NetEvent::_OnMsgGS2CSPlayerRemoveFromTeamReq( NetClient* pNetClient, GS2CSPlayerRemoveFromTeamReq *pMessage )
{
    CenterTeam* pTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwDataBaseId );
    if ( pTeam == NULL )
    {
        pTeam = theCenterTeamManager.GetTeam( pMessage->dwSessionId );
        if ( pTeam == NULL )
        {   // GameServer ������ɾ��,��Ȼû�ж���,�ͻط���Ϣ,��gameserverɾ��

            //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_OnMsgGS2CSPlayerRemoveFromTeamReq �Ҳ���������Ϣ, ����Ϣɾ����Ա[%u]", pMessage->dwDataBaseId );

            GS2CSPlayerRemoveFromTeamAck xMsg;
            xMsg.dwDataBaseId = pMessage->dwDataBaseId;
            xMsg.dwSessionId  = pMessage->dwSessionId;
            theGameServerManager.SendMessageToGameServers( &xMsg );
            return;
        }
    }

    if ( pTeam->GetID() != pMessage->dwSessionId )
    {
        CenterTeam* pCenterTeam = theCenterTeamManager.GetTeam( pMessage->dwSessionId );
        if ( pCenterTeam != NULL )
        {
            //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"_OnMsgGS2CSPlayerRemoveFromTeamReq  ����SessionID �� ��Ϣ��SessionID ��һ��, ɾ����Ա[%u]", pMessage->dwDataBaseId);
            pCenterTeam->RemoveTeamMemberAndReleaseTeam( pMessage->dwDataBaseId, theCenterTeamManager );
        }
    }

    pTeam->RemoveTeamMemberAndReleaseTeam( pMessage->dwDataBaseId, theCenterTeamManager );
}

void NetEvent::_OnMsgGS2CSPlayerUpgradeTeamReq(NetClient* pNetClient, GS2CSPlayerUpgradeTeamReq* pMessage)
{
   ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId( pMessage->dwDataBaseId );
   if ( pClientPeer == NULL )
   { return; }      // ���ܲ�����, ���������ӳ�

    CenterTeam* pTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwDataBaseId );
    if ( pTeam == NULL )
    { return; }

    pTeam->UpgradeTeamHeader( pMessage->dwDataBaseId );
}

void NetEvent::_OnMsgGS2CSTeamChangeAssignReq( NetClient* pNetClient, GS2CSTeamChangeAssignModeReq* pMessage )
{
    CenterTeam* pCenterTeam = theCenterTeamManager.GetTeam( pMessage->dwTeamSessionID );
    if ( pCenterTeam == NULL )
    { return; }

    if ( !pCenterTeam->IsTeamHeader( pMessage->dwTeamHeaderID ) )     //���Ƕӳ�
    { return; }

    if ( pCenterTeam->GetTeamAssignModeType() == pMessage->chAssignMode )       //�Ѿ���Ҫ�ı��ģʽ
    { return; }

    pCenterTeam->SetTeamAssignModeType( pMessage->chAssignMode );

    //��Ϣ�·�
    CS2GSTeamChangeAssignModeAck xAck;
    xAck.dwTeamSessionID = pMessage->dwTeamSessionID;
    xAck.chAssignMode    = pMessage->chAssignMode;
    pCenterTeam->SendMessageToTeamClient( &xAck, TeamDefine::ErrorID, TeamDefine::SendToAllGame );
}

void NetEvent::_OnMsgGS2CSTeamChangeItemLevelReq( NetClient* pNetClient, GS2CSTeamChangeAssignItemLevelReq* pMessage )
{
    CenterTeam* pCenterTeam = theCenterTeamManager.GetTeam( pMessage->dwTeamSessionID );
    if (pCenterTeam == NULL)
    { return; }

    if ( !pCenterTeam->IsTeamHeader( pMessage->dwTeamHeaderID ) )     //���Ƕӳ�
    { return; }

    if ( pCenterTeam->GetTeamAssignItemLevel() == pMessage->chAssignItemLevlel )       //�Ѿ���Ҫ�ı��ģʽ
    { return; }

    pCenterTeam->SetTeamAssignItemLevel( pMessage->chAssignItemLevlel );

    //��Ϣ�·�
    CS2GSTeamChangeAssignItemLevelAck xAck;
    xAck.dwTeamSessionID   = pMessage->dwTeamSessionID;
    xAck.chAssignItemLevel = pMessage->chAssignItemLevlel;
    pCenterTeam->SendMessageToTeamClient( &xAck, TeamDefine::ErrorID, TeamDefine::SendToAllGame );
}

void NetEvent::_OnMsgGS2CSTeamOnLine( NetClient* pNetClient, GS2CSTeamOnLine* pMessage )
{
    theCenterTeamManager.TeamMemberOnLine( pMessage->dwID );
}

void NetEvent::_OnMsgGS2CSPlayerChatMessage(NetClient* pNetClient, GS2CSPlayerChatMessage* pMessage)
{
    ClientPeer *pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId( pMessage->dwRecvID );
    if (pClientPeer == NULL)            //��Ҳ�����
    { return; }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
    if( pGameServer == NULL)
    { return; }

    pGameServer->Send(pMessage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NetEvent::_OnMsgGS2CSQueryPlayerInfoReq(NetClient* pNetClient, GS2CSQueryPlayerInfoReq *pMessage)
{
    ClientPeer *pClientPeer = NULL;
    if (pMessage->dwAckID != -1)
    {
        pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId(pMessage->dwAckID);
    }
    else if (pMessage->szAckName[0] != 0)
    {
        pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByName(pMessage->szAckName);
    }

    if (pClientPeer == NULL)            //��Ҳ�����
    {
        S2STransmitResult msg;
        msg.header.stID          = pMessage->header.stID;
        msg.msgType              = MSG_CHAT;
        msg.ucSessionType        = S2STransmit::SESSTONT_Single;
        msg.targetData.character.uDbId = pMessage->dwReqID;        
        msg.nResult              = S2STransmitResult::ETR_ClientPeerNotExist;
        HelperFunc::SafeNCpy( msg.targetData.character.szName, pMessage->szAckName, sizeof(msg.targetData.character.szName));

        pNetClient->Send( &msg );
        return; 
    }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer(pClientPeer->GetServerInfo().nServerId);
    if( pGameServer != NULL)
    {
        pGameServer->Send(pMessage);
    }
}

void NetEvent::_OnMsgGS2CSQueryPlayerInfoAck(NetClient* pNetClient, GS2CSQueryPlayerInfoAck *pMessage)
{
    ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId(pMessage->dwReqID);
    if (pClientPeer == NULL) 
    { return; }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer(pClientPeer->GetServerInfo().nServerId);
    if( pGameServer != NULL)
    {
        pGameServer->Send(pMessage);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NetEvent::_OnProcessOutOfLoginTimeMsg( NetClient* pNetClient, MsgConnectGateOverTime* pMessage )
{
    ClientPeer* pClientPeer = theClientPeerManager.GetClientPeer( pMessage->accountId );
    if ( NULL == pClientPeer)
    { return; }

    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u:%s] ��ʱ����Gate[%u:%u]", pClientPeer->GetLoginInfo().nAccountID, pClientPeer->GetLoginInfo().szAccount, 
        pClientPeer->GetLoginInfo().Sessionkey, pMessage->Sessionkey/*szSessionKey*/ );
    
    if (pMessage->Sessionkey != pClientPeer->GetLoginInfo().Sessionkey /*0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey )*/)
    { return; }

    SqlMessage sqlMessage;
    sqlMessage.nMessageId = SqlMessage::ESM_ClientConnectGateOverTime;
    sqlMessage.Guid       = pClientPeer->GetLoginInfo().nAccountID;
    strncpy_s (sqlMessage.Passport, sizeof( sqlMessage.Passport ), pClientPeer->GetLoginInfo().szAccount, sizeof(sqlMessage.Passport) - 1);
	sqlMessage.SessionKey = pClientPeer->GetLoginInfo().Sessionkey;
	sqlMessage.isWallow = pClientPeer->GetLoginInfo().isWallow;
    //theCenterServer.GetSqlService().PushResult( sqlMessage );
}

void NetEvent::_OnMsgGS2GSBanSpeak( NetClient* pNetClient, GS2GSBanSpeak* pMessage )
{
    ClientPeer* pClientPeer = NULL;
    if ( pMessage->szName[0] != NULL )
    {
        pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByName( pMessage->szName );
    }
    else if ( pMessage->dwDBID != InvalidLogicNumber )
    {
        pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId( pMessage->dwDBID );
    }
    if ( pClientPeer == NULL ) 
    { return; }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
    if( pGameServer != NULL )
    {
        pGameServer->Send( pMessage );
    }
}

void NetEvent::_OnMsgGS2GSCallPlayer( NetClient* pNetClient, GS2GSCallPlayer* pMessage )
{
    ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByName( pMessage->szName );
    if (pClientPeer == NULL) 
    { return; }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
    if( pGameServer != NULL )
    {
        pGameServer->Send( pMessage );
    }
}

//void NetEvent::_OnDB2CSAccountPoints( NetClient* pNetClient, DB2CSAccountPoints* pMessage )
//{
//    MsgPFAddPointsAck msg;
//    msg.result = pMessage->result;
//    msg.guid   = pMessage->guid;
//    msg.points = pMessage->points;
//    memcpy_s( &msg.typesn, sizeof( msg.typesn ), &pMessage->typesn, sizeof(msg.typesn) );
//    CenterServer::GetInstance().SendMessageToPlatform( pMessage->identifyId2, &msg );
//}

//void NetEvent::_OnMsgCS2GSGS2CSDrawFromPlatformQuery( NetClient* pNetClient, GS2CSDrawFromPlatformQuery* pMessage )
//{
//    MsgPFInfoQueryReq msg;
//    msg.guid       = pMessage->guid;
//    msg.queryType  = pMessage->drawType;
//    theCenterServer.SendMessageToPlatform( &msg );
//}

void NetEvent::_OnMsgUpdateItemDropControl( NetClient* pNetClient, S2SMsgUpdateItemDropControl* pMessage )
{
    if (  pNetClient == NULL || pMessage == NULL )
    { return; }

    theCenterItemDropManager.AddItemDropControl( pMessage->nItemID, pMessage->dwControlCount, pMessage->dwDropCount );

    // ͬ��������������
    ItemDropControl* pControl = theCenterItemDropManager.GetItemDropControl( pMessage->nItemID );
    if ( pControl != NULL )
    {
        pMessage->dwDropCount = pControl->dwDropCount;          // ������������������͸�����������
    }

    theGameServerManager.SendMessageToGameServers( pMessage, pNetClient->GetExtendIntData() );
}


//void NetEvent::_OnGS2CSMoneyItemExchange( NetClient* pNetClient, GS2CSMoneyItemExchange* pMessage )
//{
//    MsgPFItemExchange msg;
//    strncpy_s( msg.charName, sizeof(msg.charName), pMessage->charName, sizeof(msg.charName)-1);
//    msg.guid     = pMessage->guid;
//    msg.itemId   = pMessage->itemId;    
//    msg.itemguid = pMessage->itemguid;
//    strncpy_s( msg.itemName, sizeof(msg.itemName), pMessage->itemName, sizeof(msg.itemName)-1);
//    strncpy_s( msg.linkman, sizeof(msg.linkman), pMessage->linkman, sizeof(msg.linkman)-1);
//    strncpy_s( msg.telephone, sizeof(msg.telephone), pMessage->telephone, sizeof(msg.telephone)-1);
//    strncpy_s( msg.email, sizeof(msg.email), pMessage->email, sizeof(msg.email)-1);
//    strncpy_s( msg.identityCard, sizeof(msg.identityCard), pMessage->identityCard, sizeof(msg.identityCard)-1);
//    strncpy_s( msg.passport, sizeof(msg.passport), pMessage->passport, sizeof(msg.passport)-1);
//    
//    theCenterServer.SendMessageToPlatform( &msg );
//
//    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, theXmlString.GetString( eLog_MoneyItemChangeReq ), pMessage->itemguid, pMessage->itemName, pMessage->itemId, pMessage->linkman, pMessage->telephone, pMessage->email, pMessage->identityCard );
//}

//void NetEvent::_OnDBMsgCreateCharAck( NetClient* pNetClient, DBMsgCreateCharAck* pMessage )
//{
//    MsgPFCreateCharAck msg;
//    msg.result = pMessage->result;
//    msg.guid   = pMessage->accountId;
//    strncpy_s( msg.charName, sizeof(msg.charName), pMessage->charName, sizeof(msg.charName)-1 );
//    theCenterServer.SendMessageToPlatform( pMessage->subMarker, &msg );
//
//    LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, "account[%u] char[%s:%u] createresult[%u]", pMessage->accountId, pMessage->charName, pMessage->dwCharacterId, pMessage->result );
//}

//void NetEvent::_OnMsgBornMapOperate( NetClient* pNetClient, S2SMsgBornMapOperate* pMessage )
//{
//    if ( pMessage->chOperate == S2SMsgBornMapOperate:: )
//    {
//        theGameServerManager.SetBornMapOpen( pMessage->nMapID );
//    }
//    else if ( pMessage->chOperate == S2SMsgBornMapOperate::ECD_Add )
//    {
//        GameServerPeers gameServerPeers;
//        theGameServerManager.GetGameServerPeerList( pMessage->nMapID, gameServerPeers );
//        if ( !gameServerPeers.empty() )
//        {
//            theGameServerManager.AddBornMap( pMessage->nMapID );
//
//            // ��Ϣ���ظ���ɫ������
//            pNetClient->Send( pMessage );
//        }
//    }
//}


void NetEvent::_OnMsgRegisterServerAck( NetClient* pNetClient, MsgRegisterServerAck* pMessage )
{
    ServerData xData;
    xData.SetParentNodeType( pMessage->uchParentType );
    xData.SetParentID( pMessage->nParentID );
    xData.SetNodeType( pMessage->uchType );
    xData.SetID( pMessage->nID );
    xData.SetName( pMessage->szName );
    xData.SetVersion( pMessage->ustVersion );

    theServerStatusManager.RegisterServer( xData );

    // ����������DB�İ汾��
    theServerStatusManager.CheckVersion( xData );
}

void NetEvent::_OnMsgServerStatusAck( NetClient* pNetClient, MsgServerStatusAck* pMessage )
{
    ServerData* pServerData = theServerStatusManager.GetServerData( pMessage->uchParentType, pMessage->nParentID, pMessage->uchType, pMessage->nID );
    if ( pServerData == NULL )
    { return; }

    if ( GameTime::IsPassCurrentTime( theServerStatusManager.GetSendReqTime(), ServerDataDefine::BusyTimeOut ) )
    {
        pServerData->SetStatus( ServerDataDefine::Status_Busy );
    }
    else
    {
        pServerData->SetStatus( ServerDataDefine::Status_Fine );
    }
}

void NetEvent::_OnS2SMsgKickCharAck( NetClient* pNetClient, S2SMsgKickCharAck* pMessage )
{
    // ����GameServerû��T�������, �������ﻹ��ҪT����
    switch ( pMessage->usReason )
    {
    case S2SMsgKickChar::KR_KickToConnect:
        {
            if ( 0 == pMessage->SessionKey/*strlen(pMessage->szSessionKey)*/ )
            { return; }

            ClientPeer* pClientPeer = theClientPeerManager.GetClientPeer( pMessage->dwAccountID );
            if ( pClientPeer == NULL )
            { return; } // ��ǰ��һ���׶�ɾ����û��

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "account[%u] [-:-]_OnS2SMsgKickCharAck KR_KickToConnect", pMessage->dwAccountID/*,pClientPeer->GetLoginInfo().Sessionkey,pMessage->SessionKey*//* pMessage->szSessionKey */);

            // �ж�SessionKey�Ƿ���ͬ ��ͬ��ʾ�Ѿ����µ�ClientPeer��
            //if ( 0 != stricmp( pClientPeer->GetLoginInfo().SessionKey, pMessage->szSessionKey ) )
            //{ return; }

            pClientPeer->OnExitServer( ET_ExitGame );

            theCenterServer.NotifyGLSAccountSafeOffLine( pClientPeer->GetLoginInfo().nAccountID, pClientPeer->GetLoginInfo().szAccount );
            theClientPeerManager.RemoveClientPeer( pMessage->dwAccountID );

            // �����˳���
            theCenterServer.gGameWorldStatistics.kicklExitClientPeer += 1;
        }
    	break;
    default:
        {
// 			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "_OnS2SMsgKickCharAck �쳣��� account[%u],Reason[%d],FailAck[%d]", 
// 				pMessage->dwAccountID,pMessage->usReason,pMessage->uchFailAck );

			ClientPeer* pClientPeer = theClientPeerManager.GetClientPeer( pMessage->dwAccountID );
			if ( pClientPeer == NULL )
			{ return; } // �Ѿ��Ҳ�������˵�������˳���

            // �쳣��
            if ( pMessage->uchFailAck < S2SMsgKickChar::ECD_AckCount )
            {	// �ٴη���ָ����server��
				S2SMsgKickChar xKick;
				xKick.dwAccountID = pMessage->dwAccountID;
				xKick.time        = pMessage->time;
				xKick.usReason    = pMessage->usReason;
				xKick.uchFailAck  = pMessage->uchFailAck + 1;
				
				theGameServerManager.SendMsgToSingleGameServers(&xKick,pNetClient->GetExtendIntData());
                //theGameServerManager.SendMessageToGameServers( &xKick );
                //theGameServerManager.SendMessageToCharacterServer( &xKick );
				return;
            }
			//��S2SMsgKickChar::ECD_AckCount�κ���,û�취ǿ��ɾ��
			GS2CSPlayerExit forceMsg;
			forceMsg.nAccountId = pMessage->dwAccountID;
			forceMsg.dwDBID     = pClientPeer->GetCharDbId();
			forceMsg.cExitType  = ET_BeKick;
			forceMsg.blockTime  = 0;
			forceMsg.SessionKey = pMessage->SessionKey;
			theClientPeerManager.OnPlayerExit( &forceMsg );
            
        }
        break;
    }
}

void NetEvent::_OnMsgChangeMapCallBack( NetClient* pNetClient, MsgChangeMapCallBack* pMessage )
{
    theGameServerManager.SendMessageToGameServers( pMessage );
}


void NetEvent::_OnGS2CSMailListReq( NetClient* pNetClient, GS2CSMailListReq* pMessage )
{
    theMailSystemManager.OnGS2CSMailListReq( pMessage, pNetClient->GetExtendIntData() );
}

void NetEvent::_OnGS2CSSendMailReq( NetClient* pNetClient, GS2CSSendMailReq* pMessage )
{
    theMailSystemManager.OnGS2CSSendMailReq( pMessage, pNetClient->GetExtendIntData() );
}

void NetEvent::_OnGS2CSOpMailReq( NetClient* pNetClient, GS2CSOpMailReq* pMessage )
{
    theMailSystemManager.OnGS2CSOpMailReq( pMessage, pNetClient->GetExtendIntData() );
}

void NetEvent::_OnGS2CSQueryMailCanSendReq( NetClient* pNetClient, GS2CSQueryMailCanSendReq* pMessage )
{
    theMailSystemManager.OnGS2CSQueryMailCanSendReq( pMessage, pNetClient->GetExtendIntData() );
}

void NetEvent::_OnS2SRemoteBanReq( NetClient* pNetClient, S2SRemoteBanReq* pMessage )
{
	if (pMessage->chOrAcc == 0)
	{
		theGameServerManager.SendMsgToSingle( pMessage, InvalidLogicNumber, pMessage->_Name );
	}
	else
		theGameServerManager.SendMessageToGameServers(pMessage);
}

void NetEvent::_OnS2SRecordChatContent( NetClient* pNetClient, S2SRecordChatContent* pMessage )
{
    char strChat[S2SRecordChatContent::ECD_ContentMaxSize] = {0};
    if ( pMessage->length >= S2SRecordChatContent::ECD_ContentMaxSize )
    { pMessage->length = S2SRecordChatContent::ECD_ContentMaxSize - 1; }
    strncpy_s( strChat, sizeof(strChat), pMessage->content, pMessage->length );
    LOG_MESSAGE( CHATOBJECT, LOG_PRIORITY_INFO, strChat ); 
}

void NetEvent::_OnCS2GSMsgRewardOperate( NetClient* pNetClient, CS2GSMsgRewardOperate* pMessage )
{
    theGameServerManager.SendMessageToGameServers( pMessage );
}

void NetEvent::_OnGS2CSSendChangeVarReq( NetClient* pNetClient, GS2CSSendChangeVarReq* pMessage)
{
    theCenterSysVarManager.OnGS2CSSendChangeVarReq( pMessage, pNetClient->GetExtendIntData() );
}

void NetEvent::_OnMsgGS2CSPlayerDisbandTeam( NetClient* pNetClient, GS2CSPlayerDisbandTeam* pMessage )
{
	CenterTeam* pTeam = theCenterTeamManager.GetTeamByMemberID( pMessage->dwDataBaseID );
	if ( pTeam && pTeam->GetID() == pMessage->dwTeamSessionID && pTeam->IsTeamHeader( pMessage->dwDataBaseID ) )
	{
		GS2CSPlayerDisbandTeamAck ack;
		ack.dwDataBaseID = pMessage->dwDataBaseID;
		ack.dwTeamSessionID = pMessage->dwTeamSessionID;
		pTeam->SendMessageToTeamClient( &ack, TeamDefine::ErrorID, TeamDefine::SendToAllGame );

		pTeam->DisbandTeam( theCenterTeamManager );
	}
}

void NetEvent::_OnGS2CSUpdateAntiaddictionInfoReq ( NetClient* pNetClient, GS2CSUpdateAntiaddictionInfoReq* pMessage )
{
#if 0
	CS2GSUpdateAntiaddictionInfoAck msg;
	msg.nResult     = ER_Success;
	msg.nType       = pMessage->nType;
	msg.nAccountId  = pMessage->nAccountId;
	msg.nOnlineTime = 10;
	msg.nDuration   = pMessage->nDuration;
	pNetClient->Send( &msg );
#else
	theMysqlCommunication.PushReqMessage( pMessage, 0 );
#endif
}

void NetEvent::_OnGS2CSPing( NetClient* pNetClient, CS2GSPing* pMessage)
{
	CS2GSPing msg;
	pNetClient->Send(&msg);
}


void NetEvent::_OnCommonPing( NetClient* pNetClient, MsgPingServer* pMessage)
{
	if (CenterServer::GetInstance().IsLoginServer(pNetClient))
	{
		CenterServer::GetInstance().SetLoginServerPingTime(HQ_TimeGetTime());
		//printf("pingmsg:3,center resv login server ping:%d\n",HQ_TimeGetTime());
	}
}

void NetEvent::_OnMsggPFSendMailAck ( NetClient* pNetClient, MsgPFSendmailAck* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;

	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();
	xReq.mail.money = pMessage->money;
	// ������
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

	// �ռ���
	xReq.mail.owners[EM_ToIndex].charDbId = pMessage->characterid;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, pMessage->charactername, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

	//����
	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,pMessage->content);

	//����
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, pMessage->title);

	xReq.mail.accessory.type = SMail::EAT_Item;//2������,1����Ʒ 
	memcpy( &xReq.mail.accessory.content,  &pMessage->item, sizeof(SCharItem) );	
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
}

void NetEvent::_OnMsgAskForPresent ( NetClient* pNetClient, MsgGS2CSAskForPresent* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	MsgPFAskForPresent askfor;	
	askfor.accountid = pMessage->accountid;
	askfor.characterid = pMessage->characterid;
	strncpy_s(askfor.sn,sizeof(askfor.sn),pMessage->sn,sizeof(askfor.sn) - 1);
	strncpy_s(askfor.charactername,sizeof(askfor.charactername),pMessage->charactername,sizeof(askfor.charactername) - 1);
	CenterServer::GetInstance().SendMessageToPlatform(&askfor);
}

void NetEvent::_OnMsgAskForPlatformActivity( NetClient* pNetClient, MsgGS2CsAskForPlatformActivity* pMessage        )
{
	if (!pMessage)
	{
		return;
	}

	MsgPFAskForActivity ac;
	ac.accountid = pMessage->accountid;
	ac.characterid = pMessage->characterid;
	ac._type = pMessage->_type;
	strncpy_s(ac.charactername,sizeof(ac.charactername),pMessage->charactername,sizeof(ac.charactername) - 1);
	CenterServer::GetInstance().SendMessageToPlatform(&ac);
}
void NetEvent::_OnGS2CSCreateMulitStageReq(NetClient* pNetClient, GS2CSCreateMulitStageReq* pMessage )
{
	//��Ҵ���ָ���ĸ����������ͼ��GameServer���� 
	GameServerPeers gameServerPeers;
    theGameServerManager.GetGameServerPeerList( pMessage->MapID, true, gameServerPeers);   
	if(gameServerPeers.empty()) 
		return;
	//�����ͼ��GameServer����
	if(gameServerPeers.size() ==1)
	{
		//������ת����GameServerȥ
		GameServerPeer* pTargetGameServerPeer = gameServerPeers.front();
		pTargetGameServerPeer->Send(pMessage);       
	}
	else
	{
		//���ж��GameServer����һ����ͼ��ʱ�� ���û�ѡ��Ƶ��
		//��ȡ��һ��Gameserver �Ժ������Ҫ�����Ż���
		GameServerPeer* pTargetGameServerPeer = gameServerPeers.front();        
		pTargetGameServerPeer->Send(pMessage);  
	}
}
void NetEvent::_OnGS2CSCreateMulitStageAck(NetClient* pNetClient, GS2CSCreateMulitStageAck* pMessage )
{
	//��ȡָ������ҵ�GameServer
	GameServerPeer* pTargetGameServerPeer = theGameServerManager.GetGameServerPeer(pMessage->GameServerID);
	if(!pTargetGameServerPeer) 
		return;
	pTargetGameServerPeer->Send(pMessage);
}

void NetEvent::_OnGS2CSBroadCastAck( NetClient* pNetClient, MsgGS2CSBroadCastAck* pMessage )
{
	if ( !pMessage )
		return;

	theBroadCastManager.OnMsgAck( pMessage );
}
void NetEvent::_OnGS2CSClearTeamMapReq( NetClient* pNetClient, GS2CSClearTeamMapReq* pMessage )
{
	CenterTeam * pTeam = theCenterTeamManager.GetTeam(pMessage->TeamID);
	if(!pTeam)
		return;
	if(!pTeam->IsTeamHeader(pMessage->PlayerID))
		return;
	//���������GameServerȥ
	CS2GSClearTeamMapReq msg;
	msg.TeamID = pMessage->TeamID;
	msg.PlayerID = pMessage->PlayerID;
	theGameServerManager.SendMessageToGameServers( &msg );
}
void NetEvent::_OnGS2CSClearTeamMapAck( NetClient* pNetClient, GS2CSClearTeamMapAck* pMessage )
{
	if(!pMessage)
		return;
	//if(!pMessage->Result)
	{
		//��ն���ʧ�� ������Ҫ���߿ͻ���
		MsgClearTeamMapAck msg;
		msg.Result = pMessage->Result;
		//ClientPeer* pClientPeer = ClientPeerManager::GetInstance().GetClientPeerByDBId(pMessage->PlayerID);
		//if(pClientPeer)
		theGameServerManager.SendMsgToSingleRemote(InvalidLogicNumber,&msg,pMessage->PlayerID);
	}
}
void NetEvent::_OnGS2CSEpistarPointReq( NetClient* pNetClient, MsgGS2CSEpistarPoint* pMessage )
{
	if(!pMessage)
	{
		return;
	}
	MsgPFEpistarPoint msg;
	msg.accountid	= pMessage->accountid;
	msg.characterid = pMessage->characterid;
	msg._type		= pMessage->_type;			//������
	msg.nItemId		= pMessage->nItemId;
	msg.nPoint		= pMessage->nPoint;
	msg.charactername[ETaskInfo_NameMaxLength];
	strncpy_s(msg.charactername,sizeof(msg.charactername),pMessage->charactername,sizeof(msg.charactername) - 1);
	theCenterServer.SendMessageToPlatform(&msg);
}