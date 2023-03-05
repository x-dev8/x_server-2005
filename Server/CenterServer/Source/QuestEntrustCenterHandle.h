#pragma once
long OnProcessQuestEntrustMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );
virtual void _OnGS2CSAddQuestEntrustReq( NetClient* pNetClient, GS2CSAddQuestEntrustReq* pMessage );
virtual void _OnGS2CSDelQuestEntrustReq( NetClient* pNetClient, GS2CSDelQuestEntrustReq* pMessage );
virtual void _OnGS2CSUpdateJoinQuestEntrustReq( NetClient* pNetClient, GS2CSUpdateJoinQuestEntrustReq* pMessage );
virtual void _OnGS2CSUpdateCanelQuestEntrustReq( NetClient* pNetClient, GS2CSUpdateCanelQuestEntrustReq* pMessage );
virtual void _OnGS2CSQuestEntrustSeccReq( NetClient* pNetClient, GS2CSQuestEntrustSeccReq* pMessage );
virtual void _OnGS2CSQuestEntrustEndReq( NetClient* pNetClient, GS2CSQuestEntrustEndReq* pMessage );




