#pragma once
long OnProcessGameBattleMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );
virtual void _OnGS2CSCampBattleNewDataReq( NetClient* pNetClient, GS2CSCampBattleNewDataReq* pMessage );
virtual void _OnGS2CSAddCampBattleData( NetClient* pNetClient, GS2CSAddCampBattleData* pMessage );
virtual void _OnGS2CSDelCampBattleData( NetClient* pNetClient, GS2CSDelCampBattleData* pMessage );
virtual void _OnGS2CSDelPlayerMoney				( NetClient* pNetClient, GS2CSDelPlayerMoney* pMessage );
virtual void _OnGS2CSCampBattleAddError( NetClient* pNetClient, GS2CSCampBattleAddError* pMessage );