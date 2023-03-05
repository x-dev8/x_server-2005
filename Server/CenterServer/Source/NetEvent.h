#ifndef __CENTERSERVER_NETEVENT_H__
#define __CENTERSERVER_NETEVENT_H__

#include "NetEventInterface.h"
//#include "MessageDefine.h"
#include "CenterGameMessage.h"
#include "CenterLoginMessage.h"
#include "DBMessageDefine.h"
#include "CenterDataBaseMessage.h"
#include "CountryMessage.h"
#include "RelationMessage.h"
#include "GuildMessage.h"
#include "ConsignmentMessage.h"
#include "CenterSystemVarManager.h"
#include "FamilyMessage.h"
#include "LevelLimitMessage.h"
#include "SqlService.h"
#include "GlobalDBMessage.h"
//xuda #include "WantedMessage.h"
//xuda #include "EmperorMessage.h"
#include "QuestEntrustMessage.h"
#include "GameBattleMessage.h"
class NetEvent : public INetEvent
{
public:
    // 网络事件
    virtual bool OnAccept(TcpServer* pTcpServer, NetClient* pNetClient);
    virtual bool OnDisconnect(TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo);
    virtual bool OnOvertime(TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo){ return true; }
    virtual bool OnConnectBroken(TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo){ return true; }
    virtual long OnMessageIncoming(TcpServer* pTcpServer, NetClient* pNetClient, unsigned long msgType, Msg* pMessage );

protected:
    // Common
    virtual void _OnSSSelectChannel( NetClient* pNetClient, MsgS2SSelectChannel* pMessage );

    // LoginServer
    virtual void _OnLoginInfo( NetClient* pNetClient, MsgLoginInfo* pMessage );
    virtual void _OnRegiseterLoginServerInfo( NetClient* pNetClient, LS2CSRegiseterLoginServerInfoReq* pMessage );    

	virtual void _OnMsgCenterLoginOn( NetClient* pNetClient, MsgCenterLoginOn* pMessage);	// 废弃
	virtual void _OnMsgCenterLoginKick( NetClient* pNetClient, MsgCenterKick* pMessage);	// 废弃

    // GameServer
    virtual void _OnRegisterGameServerInfo         ( NetClient* pNetClient, GS2CSRegiseterGameServerInfoReq* pMessage );
    virtual void _OnMessageUpdateMapInfo           ( NetClient* pNetClient, MessageUpdateMapInfo*            pMessage );
    virtual void _OnUpdateBurthen                  ( NetClient* pNetClient, MsgGWBurthen*                    pMessage );
    virtual void _OnS2SSwitchGate                  ( NetClient* pNetClient, S2SSwitchGate*                   pMessage );
    virtual void _OnSwitchStageReq                 ( NetClient* pNetClient, GS2CSSwitchStageReq*             pMessage );
    virtual void _OnGS2CSPlayerExit                ( NetClient* pNetClient, GS2CSPlayerExit*                 pMessage );
    virtual void _OnGS2CSPlayerSynInServerInfo     ( NetClient* pNetClient, GS2CSPlayerSynInServerInfo*      pMessage );
    virtual void _OnProcessTransmitMsg             ( NetClient* pNetClient, S2STransmit*                     pMessage );
    virtual void _OnProcessOutOfLoginTimeMsg       ( NetClient* pNetClient, MsgConnectGateOverTime*               pMessage );

     //组队
	virtual void _OnMsgGS2CSCreateTeam			    ( NetClient* pNetClient, GS2CSCreateTeam* pMessage				  );
	virtual void _OnMsgGS2CSPlayerTeamInviteeReq    ( NetClient* pNetClient, GS2CSPlayerTeamInviteeReq* pMessage      );
	virtual void _OnMsgGS2CSPlayerTeamInviteeAck    ( NetClient* pNetClient, GS2CSPlayerTeamInviteeAck* pMessage      );
	virtual void _OnMsgGS2CSPlayerUpdateTeamMember  ( NetClient* pNetClient, GS2CSPlayerUpdateTeamMemberInfo* pMessage);
	virtual void _OnMsgGS2CSPlayerRemoveFromTeamReq ( NetClient* pNetClient, GS2CSPlayerRemoveFromTeamReq* pMessage   );
    virtual void _OnMsgGS2CSPlayerUpgradeTeamReq    ( NetClient* pNetClient, GS2CSPlayerUpgradeTeamReq* pMessage      );
    virtual void _OnMsgGS2CSTeamChangeAssignReq     ( NetClient* pNetClient, GS2CSTeamChangeAssignModeReq* pMessage   );
    virtual void _OnMsgGS2CSTeamChangeItemLevelReq  ( NetClient* pNetClient, GS2CSTeamChangeAssignItemLevelReq* pMessage);
    virtual void _OnMsgGS2CSTeamOnLine              ( NetClient* pNetClient, GS2CSTeamOnLine* pMessage				  );
	virtual void _OnMsgGS2CSPlayerDisbandTeam		( NetClient* pNetClient, GS2CSPlayerDisbandTeam* pMessage		  );

    //chat
    virtual void _OnMsgGS2CSPlayerChatMessage   ( NetClient* pNetClient, GS2CSPlayerChatMessage* pMessage         );

    //人物信息
    virtual void _OnMsgGS2CSQueryPlayerInfoReq  ( NetClient* pNetClient, GS2CSQueryPlayerInfoReq *pMessage        );
    virtual void _OnMsgGS2CSQueryPlayerInfoAck  ( NetClient* pNetClient, GS2CSQueryPlayerInfoAck *pMessage        );

    virtual void _OnMsgGS2GSBanSpeak            ( NetClient* pNetClient,   GS2GSBanSpeak* pMessage                ); // 禁言
    virtual void _OnMsgGS2GSCallPlayer          ( NetClient* pNetClient,   GS2GSCallPlayer* pMessage              ); // 拉人
    //virtual void _OnDB2CSAccountPoints          ( NetClient* pNetClient,   DB2CSAccountPoints* pMessage           ); // 冲值回馈

    //virtual void _OnMsgCS2GSGS2CSDrawFromPlatformQuery( NetClient* pNetClient, GS2CSDrawFromPlatformQuery* pMessage );

    virtual void _OnMsgUpdateItemDropControl        ( NetClient* pNetClient, S2SMsgUpdateItemDropControl* pMessage  );
    //virtual void _OnGS2CSMoneyItemExchange          ( NetClient* pNetClient, GS2CSMoneyItemExchange* pMessage       );
    //virtual void _OnDBMsgCreateCharAck              ( NetClient* pNetClient, DBMsgCreateCharAck* pMessage           );
                                                                                                                 
    virtual void _OnMsgRegisterServerAck            ( NetClient* pNetClient, MsgRegisterServerAck* pMessage         );
    virtual void _OnMsgServerStatusAck              ( NetClient* pNetClient, MsgServerStatusAck* pMessage           );
                                                                                                                 
    virtual void _OnS2SMsgKickCharAck               ( NetClient* pNetClient, S2SMsgKickCharAck* pMessage            );

    virtual void _OnMsgChangeMapCallBack            ( NetClient* pNetClient, MsgChangeMapCallBack* pMessage         ); 

    virtual void _OnGS2CSMailListReq                ( NetClient* pNetClient, GS2CSMailListReq*     pMessage         );
    virtual void _OnGS2CSSendMailReq                ( NetClient* pNetClient, GS2CSSendMailReq*     pMessage         );

    virtual void _OnGS2CSOpMailReq                  ( NetClient* pNetClient, GS2CSOpMailReq*       pMessage         );
    virtual void _OnGS2CSQueryMailCanSendReq        ( NetClient* pNetClient, GS2CSQueryMailCanSendReq* pMessage     );
    virtual void _OnS2SRemoteBanReq                 ( NetClient* pNetClient, S2SRemoteBanReq* pMessage              );

    virtual void _OnS2SRecordChatContent            ( NetClient* pNetClient, S2SRecordChatContent* pMessage         );

    virtual void _OnCS2GSMsgRewardOperate           ( NetClient* pNetClient, CS2GSMsgRewardOperate* pMessage        );
    virtual void _OnGS2CSSendChangeVarReq           ( NetClient* pNetClient, GS2CSSendChangeVarReq* pMessage        );

	virtual void _OnGS2CSUpdateAntiaddictionInfoReq ( NetClient* pNetClient, GS2CSUpdateAntiaddictionInfoReq* pMessage );

	virtual void _OnGS2CSPing						( NetClient* pNetClient, CS2GSPing* pMessage        );
	virtual void _OnCommonPing						( NetClient* pNetClient, MsgPingServer* pMessage        );
	virtual void _OnMsggPFSendMailAck				( NetClient* pNetClient, MsgPFSendmailAck* pMessage        );
	virtual void _OnMsgAskForPresent				( NetClient* pNetClient, MsgGS2CSAskForPresent* pMessage        );
	virtual void _OnMsgAskForPlatformActivity		( NetClient* pNetClient, MsgGS2CsAskForPlatformActivity* pMessage        );

	virtual void _OnGS2CSCreateMulitStageAck		(NetClient* pNetClient,  GS2CSCreateMulitStageAck* pMessage );
	virtual void _OnGS2CSCreateMulitStageReq		(NetClient* pNetClient,  GS2CSCreateMulitStageReq* pMessage );

	virtual void _OnGS2CSBroadCastAck				( NetClient* pNetClient, MsgGS2CSBroadCastAck* pMessage );
	virtual void _OnGS2CSClearTeamMapReq			( NetClient* pNetClient, GS2CSClearTeamMapReq* pMessage );
	virtual void _OnGS2CSClearTeamMapAck			( NetClient* pNetClient, GS2CSClearTeamMapAck* pMessage );

	virtual void _OnGS2CSEpistarPointReq			( NetClient* pNetClient, MsgGS2CSEpistarPoint* pMessage );

    long OnProcessDefaultMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

#include "RelationCenterHandle.h"
#include "CountryCenterHandle.h"
#include "GuildCenterHandle.h"
#include "ConsignmentCenterHandle.h"
#include "FamilyCenterHandle.h"
#include "LevelLimitCenterHandle.h"
#include "GlobalDBCenterHandle.h"
//xuda #include "WantedCenterHandle.h"
//xuda #include "EmperorCenterHandle.h"
#include "QuestEntrustCenterHandle.h"
#include "GameBattleCenterHandle.h"
};

#endif // __CENTERSERVER_NETEVENT_H__
