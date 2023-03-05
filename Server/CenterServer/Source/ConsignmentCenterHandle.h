#ifndef __CENTERCONSIGNMENTHANDLE_H__
#define __CENTERCONSIGNMENTHANDLE_H__

long OnProcessConsignmentMessage( TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSOpenConsignmentMoneyWindow( NetClient* pNetClient, GS2CSOpenConsignmentMoneyWindow* pMessage );
virtual void _OnGS2CSQueryConsignmentList( NetClient* pNetClinet, GS2CSQueryConsignmentList* pMessage );
virtual void _OnGS2CSOperateMoneyReq( NetClient* pNetClient, GS2CSOperateMoneyReq* pMessage );
virtual void _OnGS2CSConsignmentMoneyReq( NetClient* pNetClient, GS2CSConsignmentMoneyReq* pMessage );
virtual void _OnGS2CSConsignmentMoneyHistroyReq( NetClient* pNetClient, GS2CSConsignmentMoneyHistroyReq* pMessage );
virtual void _OnGS2CSConsignmentOperateReq( NetClient* pNetClient, GS2CSConsignmentOperateReq* pMessage );

virtual	void _OnGS2CSConsignmentItemReq( NetClient* pNetClient, GS2CSConsignmentItemReq* pMessage  );

#endif