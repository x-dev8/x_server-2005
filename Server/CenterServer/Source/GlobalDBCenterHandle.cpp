#include "NetEvent.h"
#include "GlobalDBManager.h"
long NetEvent::OnProcessGlobalDBMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( GS2CS_UPDATEGLOBALDBREQ, GS2CSUpdateGlobalDBReq, _OnGS2CSUpdateGlobalDBReq );
    MESSAGE_MAPPING_END
    return ER_Success;
}
void NetEvent::_OnGS2CSUpdateGlobalDBReq( NetClient* pNetClient, GS2CSUpdateGlobalDBReq* pMessage )
{
	theCenterGlobalDBManager.UpdateGlobalDBData(pMessage->uchUpdateType,pMessage->Index,pMessage->n64Value);//аоИФЪ§Он
}