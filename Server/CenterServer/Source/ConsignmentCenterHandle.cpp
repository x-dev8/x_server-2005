#include "ConsignmentManager.h"
#include "NetEvent.h"
#include "GameServerManager.h"

long NetEvent::OnProcessConsignmentMessage( TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( GS2CS_OPERNCONSIGNMENTMONEYWINDOW, GS2CSOpenConsignmentMoneyWindow, _OnGS2CSOpenConsignmentMoneyWindow );
        MESSAGE_HANDLE( GS2CS_QUERYCONSIGNMENTLIST, GS2CSQueryConsignmentList, _OnGS2CSQueryConsignmentList );
        MESSAGE_HANDLE( GS2CS_OPERATEMONEYREQ, GS2CSOperateMoneyReq, _OnGS2CSOperateMoneyReq );
        MESSAGE_HANDLE( GS2CS_CONSIGNMENTMONEYREQ, GS2CSConsignmentMoneyReq, _OnGS2CSConsignmentMoneyReq );
        MESSAGE_HANDLE( GS2CS_CONSIGNMENTMONEYHISTROYREQ, GS2CSConsignmentMoneyHistroyReq, _OnGS2CSConsignmentMoneyHistroyReq );
        MESSAGE_HANDLE( GS2CS_CONSIGNMENTOPERATEREQ, GS2CSConsignmentOperateReq, _OnGS2CSConsignmentOperateReq );
    
		MESSAGE_HANDLE( GS2CS_CONSIGNMENTITEMREQ, GS2CSConsignmentItemReq, _OnGS2CSConsignmentItemReq );
    MESSAGE_MAPPING_END

    return ER_Success;
}

void NetEvent::_OnGS2CSOpenConsignmentMoneyWindow( NetClient* pNetClient, GS2CSOpenConsignmentMoneyWindow* pMessage )
{
    // 发送帐号消息给GameServer
    theConsignmentManager.SendAccountMessage( pMessage->nPlayerID );

	if (pMessage->bGetAll)
	{
		// 发送寄售列表
		theConsignmentManager.SendConsignmentMoneyListMessage( pMessage->nPlayerID, ConsignmentDefine::Consignment_Init, ConsignmentDefine::Sort_Normal );
	}
}

void NetEvent::_OnGS2CSQueryConsignmentList( NetClient* pNetClient, GS2CSQueryConsignmentList* pMessage )
{
    theConsignmentManager.SendConsignmentMoneyListMessage( pMessage->nPlayerID, pMessage->uchConsignmentType, pMessage->uchQueryType, pMessage->nCount );
    theConsignmentManager.SendOperateMessage( pMessage->nPlayerID, false );
}

void NetEvent::_OnGS2CSOperateMoneyReq( NetClient* pNetClient, GS2CSOperateMoneyReq* pMessage )
{
    theConsignmentManager.ProcessGameAccountOperate( pMessage->nPlayerID, pMessage->uchOperate, pMessage->nRMBMoney, pMessage->nGameMoney );
}

void NetEvent::_OnGS2CSConsignmentMoneyReq( NetClient* pNetClient, GS2CSConsignmentMoneyReq* pMessage )
{
    theConsignmentManager.ProcessGameConsignmentMoney( pMessage->nPlayerID, pMessage->xConsignment, pMessage->nCostValue );
}

void NetEvent::_OnGS2CSConsignmentMoneyHistroyReq( NetClient* pNetClient, GS2CSConsignmentMoneyHistroyReq* pMessage )
{
    theConsignmentManager.ProcessQueryMoneyHistroy( pMessage->nPlayerID );
}

void NetEvent::_OnGS2CSConsignmentOperateReq( NetClient* pNetClient, GS2CSConsignmentOperateReq* pMessage )
{
    theConsignmentManager.ProcessConsignmentOperate( pMessage->nPlayerID, pMessage->n64ConsignmentID, pMessage->uchConsignmentType, pMessage->uchOperate );
}

//寄售物品
void NetEvent::_OnGS2CSConsignmentItemReq(NetClient* pNetClient, GS2CSConsignmentItemReq* pMessage )
{
	theConsignmentManager.ProcessGameConsignmentItem( pMessage->nPlayerID, pMessage->xConsignment, pMessage->nCostValue );
}