#pragma once
long OnProcessQuestEntrustMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnCS2GSLoadQuestEntrustDataAck		( NetClient* pNetClient, CS2GSLoadQuestEntrustDataAck* pMessage );
virtual void _OnCS2GSAddQuestEntrustAck		( NetClient* pNetClient, CS2GSAddQuestEntrustAck* pMessage );
virtual void _OnCS2GSDelQuestEntrustAck		( NetClient* pNetClient, CS2GSDelQuestEntrustAck* pMessage );
virtual void _OnCS2GSUpdateJoinQuestEntrustAck( NetClient* pNetClient, CS2GSUpdateJoinQuestEntrustAck* pMessage );
virtual void _OnCS2GSUpdateCanelQuestEntrustAck( NetClient* pNetClient, CS2GSUpdateCanelQuestEntrustAck* pMessage );
virtual void _OnCS2GSQuestEntrustSeccAck( NetClient* pNetClient, CS2GSQuestEntrustSeccAck* pMessage );
virtual void _OnCS2GSQuestEntrustEndAck( NetClient* pNetClient, CS2GSQuestEntrustEndAck* pMessage );

