/********************************************************************
Filename: 	AuctionProxy.cpp
MaintenanceMan Mail: lufeipeng@163.com
Brief: 系统寄售GameServer管理，暂时实现寄售金锭
*********************************************************************/
#include "AuctionProxy.h"
#include "MessageDefine.h"
#include "GamePlayer.h"
#include "GameServer.h"


void AuctionProxy::OnClientHandleAuctionMoney( Msg* pMsg )
{
	if(!pMsg || !owner)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	static DWORD last_handle_time = 0;
	//防止频繁操作带来的问题
	if(last_handle_time && HQ_TimeGetTime() - last_handle_time < 3 * 1000)
	{
		ack.result = enumSystemAuctionError_SystemBusy;
		GettheServer().SendMsgToSingle(&ack,owner);
		return;
	}
	last_handle_time = HQ_TimeGetTime();

	MsgHandleSystemAuctionAccountMoney *pMoney = static_cast<MsgHandleSystemAuctionAccountMoney*>(pMsg);
	switch(pMoney->handletype)
	{
	case MsgHandleSystemAuctionAccountMoney::enum_AddSystemAuctionAccountMoney:
		{
			MsgAckExcuteSystemAuction ack;
			if(pMoney->rmbmoney > enumAuctionMoney_AccountMaxRmb || pMoney->gamemoney > enumAuctionMoney_AccountMaxGameMoney)
			{
				ack.result = enumSystemAuctionError_TooMoney;
				GettheServer().SendMsgToSingle(&ack,owner);
				break;
			}
			if(this->getAuctionGameMoney() + pMoney->gamemoney > enumAuctionMoney_AccountMaxGameMoney
				|| this->getAuctionRmb() + pMoney->rmbmoney > enumAuctionMoney_AccountMaxRmb)
			{
				ack.result = enumSystemAuctionError_TooMoney;
				GettheServer().SendMsgToSingle(&ack,owner);
				break;
			}
			if(pMoney->gamemoney > owner->GetMoney() || pMoney->rmbmoney > owner->GetJinDingNum())
			{
				ack.result = enumSystemAuctionError_NoMoney;
				GettheServer().SendMsgToSingle(&ack,owner);
				break;
			}
			GettheServer().SendUserMsgToCenterServer(owner, pMsg);
		}
		break;
	case MsgHandleSystemAuctionAccountMoney::enum_RemoveSystemAuctionAccountMoney:
		{	
			MsgAckExcuteSystemAuction ack;
			if(pMoney->rmbmoney > this->getAuctionRmb()
				|| pMoney->gamemoney > this->getAuctionGameMoney() 
				|| pMoney->gamemoney > enumAuctionMoney_AccountMaxGameMoney 
				|| pMoney->rmbmoney > enumAuctionMoney_AccountMaxRmb)
			{
				ack.result = enumSystemAuctionError_TooMoney;
				GettheServer().SendMsgToSingle(&ack,owner);
				break;
			}
			GettheServer().SendUserMsgToCenterServer(owner, pMsg);
		}
		break;
	}
}
void AuctionProxy::OnClientExcuteAuction( Msg* pMsg )
{	
	if(!pMsg || !owner )
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	static DWORD last_handle_time = 0;

	//防止频繁操作带来的问题
    if( !GameTime::IsPassCurrentTime( last_handle_time, 3 * 1000 ) )
	{
		ack.result = enumSystemAuctionError_SystemBusy;
		GettheServer().SendMsgToSingle(&ack,owner);
		return;
	}

	last_handle_time = HQ_TimeGetTime();
	GettheServer().SendUserMsgToCenterServer(owner, pMsg);
}

void AuctionProxy::OpenSystemAuction()
{
	if(!owner)
	{
		return;
	}
	MsgRequestSystemAuction msg;
	GettheServer().SendUserMsgToCenterServer(owner, &msg);
}
void AuctionProxy::OnAckHandleAuctionAccountMoney( Msg* pMsg)
{
	if(!owner)
	{
		return;
	}
	MsgAckHandleSystemAuctionAccountMoney *pMoney = (MsgAckHandleSystemAuctionAccountMoney *)pMsg;
	if(!pMoney->error)
	{
		this->setAuctionGameMoney( pMoney->gamemoney );
		this->setAuctionRmb( pMoney->rmbmoney );
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "刷新用户:%u的寄售账号资金:%u,%u",owner->GetDBCharacterID(), this->getAuctionRmb(), this->getAuctionGameMoney());
	}
	GettheServer().SendMsgToSingle(pMoney,owner);
}