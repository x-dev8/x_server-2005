#include "GamePlayer.h"
#include "MessageDefine.h"


long GamePlayer::CenterUserMsgParse(Msg *pMessage,unsigned long msgType)
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE_USER( MSG_ACKHANDLESYSTEMAUCTION_ACCOUNTMONEY, MsgAckHandleSystemAuctionAccountMoney,this->auction_proxy.OnAckHandleAuctionAccountMoney);
		MESSAGE_HANDLE_USER( CS_NOTIFY_GAMESERVER_MONEY, CSNotifyGameServerMoneyMsg, OnHandleCenterMoneyMsg);
		MESSAGE_HANDLE_UNPACK(MSG_RETURNSTSTEMAUCTION, MsgReturnSystemAuction, sendCenterMsgToClient);
		MESSAGE_HANDLE_UNPACK(MSG_ACK_EXCUTESYSTEM_AUCTION, MsgAckExcuteSystemAuction, sendCenterMsgToClient);
		MESSAGE_HANDLE_UNPACK(MSG_AUCTION_HISTROYLIST, MsgAuctionHistroyList, sendCenterMsgToClient);
		default:
			{   
			}
			break;
	MESSAGE_MAPPING_END
	return ER_Success;
}

//消息直接转发给Client
void GamePlayer::sendCenterMsgToClient(Msg *msg)
{
	GettheServer().SendMsgToSingle(msg,this);
}
void GamePlayer::OnHandleCenterMoneyMsg(CSNotifyGameServerMoneyMsg *msg)
{
	if(msg->type == CSNotifyGameServerMoneyMsg::enumNotifyGameServer_AddMoney)
	{
		if(msg->rmb_money)
		{
			this->OperateJinDing(true, msg->rmb_money);
		}
		if(msg->game_money)
		{
			this->SetMoney(this->GetMoney() + msg->game_money);
		}
	}
	else if(msg->type == CSNotifyGameServerMoneyMsg::enumNotifyGameServer_SubMoney)
	{
		if(msg->rmb_money)
		{
			this->OperateJinDing(false, msg->rmb_money);
		}
		if(msg->game_money)
		{
			if(this->GetMoney() < msg->game_money)
			{
				LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CenterServer通知GameServer出错,%u,%s", this->GetDBCharacterID(), this->GetPlayerName());
			}
			else
			{
				this->SetMoney(this->GetMoney() - msg->game_money);
			}
		}
	}
	else
	{
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CenterServer通知GameServer扣钱用户%u类型不对,%u");
	}
	MsgMoneyChange change;
	change.dwNumber = this->GetMoney();
	change.header.stID = GetID();    
	GettheServer().SendMsgToSingle( &change, this);
}