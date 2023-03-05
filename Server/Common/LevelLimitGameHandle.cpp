#include "LevelLimitGameManager.h"
#include "CenterServerNetEvent.h"

long CenterServerNetEvent::OnProcessGameLevelLimitMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
	{
		MESSAGE_HANDLE( MSG_UPDATEPLAYERCOUNT, MsgUpdatePlayerCount, OnMsgUpdateLimitPlayerCount );
		MESSAGE_HANDLE( MSG_ACTIVELIMIT_ACK, MsgActiveLimitAck, OnMsgAckActiveLimit );
		MESSAGE_HANDLE( MSG_2ALLGAMEINFO, Msg2AllGameInfo, OnMsgHoleLimitInfo );
		MESSAGE_HANDLE( MSG_UPDATELEVELLIMITSTATE, MsgUpdateLevelLimitSate, OnMsgUpdateLimitState );
	}
	MESSAGE_MAPPING_END

	return ER_Success;
}

void CenterServerNetEvent::OnMsgUpdateLimitPlayerCount( NetClient* pNetClient, MsgUpdatePlayerCount* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	theLevelLimitGameManager.UpdatePlayerCount(pMessage->_count);
}

void CenterServerNetEvent::OnMsgAckActiveLimit( NetClient* pNetClient, MsgActiveLimitAck* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	if (pMessage->_state != eLimitState_Active)
	{
		return;
	}

	theLevelLimitGameManager.ReqActiveLimit(pMessage->active_name);
}

void CenterServerNetEvent::OnMsgHoleLimitInfo( NetClient* pNetClient, Msg2AllGameInfo* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	theLevelLimitGameManager.OnMsgLevelLimitInfo(pMessage);
}

void CenterServerNetEvent::OnMsgUpdateLimitState( NetClient* pNetClient, MsgUpdateLevelLimitSate* pMessage )
{
	if (!pMessage)
	{
		return;
	}

	theLevelLimitGameManager.UpdateLimitState(pMessage->_state);
}