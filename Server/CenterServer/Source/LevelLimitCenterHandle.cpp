#include "NetEvent.h"
#include "GameServerManager.h"
#include "LevelLimitCenterManager.h"

long NetEvent::OnProcessLevelLimitMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
	{
		MESSAGE_HANDLE( MSG_ACTIVELIMIT, MsgActiveLimit, _OnGS2CSActiveLimit );
		MESSAGE_HANDLE( MSG_ADDPLAYERCOUNT_LIMIT, MsgAddPlayerCountLimit, _OnGS2CSAddPlayerCount );
		MESSAGE_HANDLE( MSG_GS2CSREQLIMITINFO, MsgGS2CSReqLimitInfo, _OnGS2CSReqLimitInfo );
	}
	MESSAGE_MAPPING_END

	return ER_Success;
}

void NetEvent::_OnGS2CSActiveLimit( NetClient* pNetClient, MsgActiveLimit* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	theLevelLimitCenterManager.ActiveLimit(pMessage->active_name);
}

void NetEvent::_OnGS2CSAddPlayerCount(NetClient* pNetClient, MsgAddPlayerCountLimit* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	theLevelLimitCenterManager.AddPlayer(pMessage->add_count);
}

void NetEvent::_OnGS2CSReqLimitInfo(NetClient* pNetClient, MsgGS2CSReqLimitInfo* pMessage )
{
	if (!pMessage)
	{
		return;
	}
	Msg2AllGameInfo msg;
	pNetClient->Send(theLevelLimitCenterManager.GetLimitInfoToGame(msg));
}