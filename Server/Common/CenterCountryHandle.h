
/************************************************************************
            Include in NetEvent.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

#include "CountryMessage.h"

long OnProcessCountryMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage );

virtual void _OnGS2CSCountryNoticeChangeReq( NetClient* pNetClient, GS2CSCountryNoticeChangeReq* pMessage );