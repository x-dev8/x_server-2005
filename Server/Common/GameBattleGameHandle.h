#pragma once
long OnProcessGameBattleMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnCS2GSLoadCampBattleData( NetClient* pNetClient, CS2GSLoadCampBattleData* pMessage );
virtual void _OnCS2GSAddCampBattleData( NetClient* pNetClient, CS2GSAddCampBattleData* pMessage );
virtual void _OnCS2GSDelCampBattleData( NetClient* pNetClient, CS2GSDelCampBattleData* pMessage );
virtual void _OnCS2GSCampBattleNewDataReq( NetClient* pNetClient, CS2GSCampBattleNewDataReq* pMessage );
virtual void _OnCS2GSSDelPlayerMoney( NetClient* pNetClient, CS2GSSDelPlayerMoney* pMessage );
virtual void _OnCS2GSCampBattleAddError( NetClient* pNetClient, CS2GSCampBattleAddError* pMessage );