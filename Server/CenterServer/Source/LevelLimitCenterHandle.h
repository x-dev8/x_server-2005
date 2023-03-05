#ifndef __CENTERLEVELLIMITHANDLE_H__
#define __CENTERLEVELLIMITHANDLE_H__

long OnProcessLevelLimitMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSActiveLimit( NetClient* pNetClient, MsgActiveLimit* pMessage );
virtual void _OnGS2CSAddPlayerCount(NetClient* pNetClient, MsgAddPlayerCountLimit* pMessage );
virtual void _OnGS2CSReqLimitInfo(NetClient* pNetClient, MsgGS2CSReqLimitInfo* pMessage );
#endif
