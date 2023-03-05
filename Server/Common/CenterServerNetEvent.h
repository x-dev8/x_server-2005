#ifndef __GAMESERVER_CENTERSERVERNETEVENT_H__
#define __GAMESERVER_CENTERSERVERNETEVENT_H__

#pragma warning( disable : 4293 )

#include "NetEventInterface.h"
#include "CenterGameMessage.h"
#include "MessageDefine.h"
#include "DBMessageDefine.h"
#include "CountryMessage.h"
#include "RelationMessage.h"
#include "GuildMessage.h"
#include "SystemVarMessage.h"
#include "FamilyMessage.h"
#include "LevelLimitMessage.h"
#include "GlobalDBMessage.h"
//xuda #include "WantedMessage.h"
//xuda #include "EmperorMessage.h"
#include "QuestEntrustMessage.h"
#include "GameBattleMessage.h"
class CenterServerNetEvent : public INetEvent
{
public:
    // 网络事件
    virtual bool OnAccept           ( TcpServer* pTcpServer, NetClient* pNetClient){ return true;}
    virtual bool OnDisconnect       ( TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo){ return true; }
    virtual bool OnOvertime         ( TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo){ return true; }
    virtual bool OnConnectBroken    ( TcpServer* pTcpServer, NetClient* pNetClient, void *pAttachInfo){ return true; }
    virtual long OnMessageIncoming  ( TcpServer* pTcpServer, NetClient* pNetClient, unsigned long msgType, Msg* pMessage );

protected:
    virtual void _OnRegiseterGameServerInfoAck ( NetClient* pNetClient, const CS2GSRegiseterGameserverInfoAck* pMessage );
    virtual void _OnMessageUpdateMapInfo       ( NetClient* pNetClient, const MessageUpdateMapInfo* pMessage            );
    virtual void _OnLoginInfo                  ( NetClient* pNetClient, const CS2GSLoginInfo* pMessage                  );
    virtual void _OnAckSwitchStage             ( NetClient* pNetClient, const CS2GSSwitchStageAck* pMessage             );
    virtual void _OnS2SSwitchGate              ( NetClient* pNetClient, const S2SSwitchGate* pMessage                   );
    virtual void _OnS2SMsgKickChar             ( NetClient* pNetClient, S2SMsgKickChar* pMessage                         );
    virtual void _OnS2STransmit                ( NetClient* pNetClient, S2STransmit* pMessage                           );
    virtual void _OnS2STransmitResult          ( NetClient* pNetClient, S2STransmitResult* pMessage                     );
    virtual void _OnMsgJoinTeamAck             ( NetClient* pNetClient, CS2GSAckJoinTeam* pMessage                      );
    virtual void _OnMsgCreateTeam              ( NetClient* pNetClient, CS2GSCreateTeam* pMessage                       );
    virtual void _OnMsgTeamOutLine             ( NetClient* pNetClient, CS2GSMsgTeamOutLine* pMessage                   );
    virtual void _OnMsgTeamOnLine                 ( NetClient* pNetClient, GS2CSTeamOnLine* pMessage                       );
	virtual void _OnMsgUpdateTeamMember        ( NetClient* pNetClient, GS2CSPlayerUpdateTeamMemberInfo* pMessage       );
	virtual void _OnMsgRemoveTeamMemberAck     ( NetClient* pNetClient, GS2CSPlayerRemoveFromTeamAck* pMessage          );
	virtual void _OnMsgDisbandTeamAck			( NetClient* pNetClient, GS2CSPlayerDisbandTeamAck* pMessage          );
    virtual void _OnMsgUpgradeTeamAck          ( NetClient* pNetClient, GS2CSPlayerUpgradeTeamAck* pMessage             );
    virtual void _OnMsgChatMessage             ( NetClient* pNetClient, GS2CSPlayerChatMessage* pMessage                );
    virtual void _OnMsgQueryPlayerInfoReq      ( NetClient* pNetClient, GS2CSQueryPlayerInfoReq* pMessage               );
    virtual void _OnMsgQueryPlayerInfoAck      ( NetClient* pNetClient, GS2CSQueryPlayerInfoAck* pMessage               );
    virtual void _OnMsgTeamChangeModeAck       ( NetClient* pNetClient, CS2GSTeamChangeAssignModeAck* pMessage          );
    virtual void _OnMsgTeamChangeItemLevelAck  ( NetClient* pNetClient, CS2GSTeamChangeAssignItemLevelAck* pMessage     );
    
    virtual void _OnMsgS2SNotifyTimeEvent           ( NetClient* pNetClient, S2SNotifyTimeEvent* pMessage            );
    virtual void _OnMsgS2SAntiAddictionAccountInfo  ( NetClient* pNetClient, S2SAntiAddictionAccountInfo* pMessage   );
    virtual void _OnMsgS2SNotiyAntiAddictionTimeInfo( NetClient* pNetClient, S2SNotiyAntiAddictionTimeInfo* pMessage );
    virtual void _OnMsgGS2GSBanSpeak                ( NetClient* pNetClient, GS2GSBanSpeak* pMessage                 ); // 禁言
    virtual void _OnMsgGS2GSCallPlayer              ( NetClient* pNetClient, GS2GSCallPlayer* pMessage               ); // 拉人

    virtual void _OnCS2GSDrawFromPlatformAck       ( NetClient* pNetClient, CS2GSDrawFromPlatformAck* pMessage     );

    virtual void _OnMsgCS2GSSetCheckCheatOpen       ( NetClient* pNetClient, CS2GSMsgSetCheckCheatOpen* pMessage        );
    virtual void _OnMsgUpdateItemDropControl        ( NetClient* pNetClient, S2SMsgUpdateItemDropControl* pMessage      );
    virtual void _OnCS2GSItemDropControl            ( NetClient* pNetClient, CS2GSItemDropControl* pMessage            );
    virtual void _OnMsgBornMapOperate               ( NetClient* pNetClient, CS2GSMsgBornMapOperate* pMessage             );
    virtual void _OnCS2GSSystemVar                  ( NetClient* pNetClient, CS2GSSystemVar* pMessage );
    
    virtual void _OnCS2GSGMBroatcastReq             ( NetClient* pNetClient, CS2GSGMBroatcastReq* pMessage              );
    virtual void _OnMsgServerStatusReq              ( NetClient* pNetClient, MsgServerStatusReq* pMessage               );    

    virtual void _OnMsgServerVersionCheckAck        ( NetClient* pNetClient, MsgServerVersionCheckAck* pMessage         );
    virtual void _OnMsgChangeMapCallBack            ( NetClient* pNetClient, MsgChangeMapCallBack* pMessage             );
    virtual void _OnS2SUpdateTradeShopConfig        ( NetClient* pNetClient, S2SUpdateTradeShopConfig* pMessage         );
    //用户Center消息解析
    virtual void _OnS2SShutdownServer               ( NetClient* pNetClient, S2SShutdownServer* pMessage                );
    virtual void _OnS2SChangeMapExpRate             ( NetClient* pNetClient, S2SChangeMapExpRate* pMessage              );
    virtual void _OnCS2GSMailListAck                ( NetClient* pNetClient, CS2GSMailListAck* pMessage                 );
    virtual void _OnCS2GSQueryMailCanSendAck        ( NetClient* pNetClient, CS2GSQueryMailCanSendAck* pMessage         );
    virtual void _OnCS2GSOpMailAck                  ( NetClient* pNetClient, CS2GSOpMailAck* pMessage                   );
    virtual void _OnCS2GSSendMailAck                ( NetClient* pNetClient, CS2GSSendMailAck* pMessage                 );
    virtual void _OnS2SRemoteBanReq                 ( NetClient* pNetClient, S2SRemoteBanReq* pMessage                  );
    //zhuxincong
	virtual void _OnS2SDleteCountryBattleReward		( NetClient* pNetClient, S2SDleteCountryBattleReward* pMessage );
    virtual void _OnMsgPartitionLogFile             ( NetClient* pNetClient, MsgPartitionLogFile* pMessage              );
    virtual void _OnCS2GSOpRecordChatOnOff          ( NetClient* pNetClient, CS2GSOpRecordChatOnOff* pMessage           );
    virtual void _OnCS2GSMsgRewardOperate           ( NetClient* pNetClient, CS2GSMsgRewardOperate* pMessage            );
    virtual void _OnCS2GSLoadResourceSuccess        ( NetClient* pNetClient, CS2GSLoadResourceSuccess* pMessage         );  

    virtual void _OnCS2GSUpdateCountryOnLineCount   ( NetClient* pNetClient, CS2GSUpdateCountryOnLineCount* pMessage    );

	virtual void _OnGS2CSUpdateAntiaddictionInfoAck ( NetClient* pNetClient, CS2GSUpdateAntiaddictionInfoAck* pMessage );
	virtual void _OnMsgCenterPing					( NetClient* pNetClient, CS2GSPing* pMessage );
	virtual void _OnMsgPFSendMail					( NetClient* pNetClient, MsgPFSendmailReq* pMessage );
	virtual void _OnMsgQueueOp						( NetClient* pNetClient, MsgCS2GSQueueOp* pMessage );

	virtual void _OnGS2CSCreateMulitStageReq		( NetClient* pNetClient, GS2CSCreateMulitStageReq* pMessage );
	virtual void _OnGS2CSCreateMulitStageAck		(  NetClient* pNetClient, GS2CSCreateMulitStageAck* pMessage );

	virtual void _OnCS2GSTeamStateChange			(  NetClient* pNetClient, CS2GSTeamStateChange* pMessage );

	virtual void _OnCS2GSBroadCast					( NetClient* pNetClient, MsgCS2GSBroadCast* pMessage );
	virtual void _OnCS2GSChannelInfo				( NetClient* pNetClient, MsgChannelInfo* pMessage );

	virtual void _OnCS2GSClearTeamMapReq			( NetClient* pNetClient, CS2GSClearTeamMapReq* pMessage );
	virtual void _OnCS2GSCharRemoveItembyId			( NetClient* pNetClient, MsgCS2GSCharRemoveItembyId* pMessage );
	virtual void _OnCS2GSUpdateReloadCfg			( NetClient* pNetClient, MsgCS2GSUpdateReloadCfg* pMessage );

    long OnProcessDefaultMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

#include "CountryGameHandle.h"
#include "RelationGameHandle.h"
#include "GuildGameHandle.h"
#include "FamilyGameHandle.h"
#include "LevelLimitGameHandle.h"
#include "GlobalDBGameHandle.h"	
//xuda #include "WantedGameHandle.h"
//xuda #include "EmperorGameHandle.h"
#include "QuestEntrustGameHandle.h"
#include "GameBattleGameHandle.h"
};

#endif // __GAMESERVER_CENTERSERVERNETEVENT_H__
