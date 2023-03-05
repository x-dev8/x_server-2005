/********************************************************************
Filename: 	Auction.cpp
MaintenanceMan Mail: lufeipeng@163.com
Brief: 系统寄售，暂时实现寄售金锭
*********************************************************************/
#include "Auction.h"
#include "MySqlCommunication.h"
#include "CenterGameMessage.h"
#include "GameServerManager.h"
#include "XmlStringLanguage.h"

bool AuctionManager::init()
{
	is_finishload_auctionlist = false;
	is_finishloadcount = false;
	isfinish_loadhistroy = false;
	account_map.clear();
	auction_list.clear();
	moneyauction_histroylist.clear();
	sellrmb_temp.clear();
	sellmoney_temp.clear();
	userHandleMap.clear();
	tenSec = new HRTimer(10 * 1000L);
	return true;
}
void AuctionManager::tryReloadData(DWORD currentTime)
{
	static DWORD last_checktime = 0;
	if(currentTime < last_checktime + 60 * 1000)
	{
		return;
	}
	last_checktime = currentTime;
	if(!this->isFinishLoadAccount())
	{
		CSRequestLoadMysqlDataMsg cmd;
		cmd.type = enumHandleCenterDB_LoadAuctionAccount;
		theMysqlCommunication.PushReqMessage(&cmd, 0);
	}
	if(!this->isFinishLoadAuctionList())
	{
		CSRequestLoadMysqlDataMsg cmd;
		cmd.type = enumHandleCenterDB_LoadAuctionList;
		theMysqlCommunication.PushReqMessage(&cmd, 0);
	}
	if(!this->isFinishLoadAuctionHistroy())
	{
		CSRequestLoadMysqlDataMsg cmd;
		cmd.type = enumHandleCenterDB_LoadMoneyAuctionHistroy;
		theMysqlCommunication.PushReqMessage(&cmd, 0);
	}
}
bool AuctionManager::notifyGameServerMoney(CSLoadMysqlDataMsg *pLoadMsg)
{	
	if(!pLoadMsg)
	{
		return false;
	}
	CSNotifyGameServerMoneyMsg msg;
	AuctionAccount *data = (AuctionAccount*)pLoadMsg->buffer;
	this->FinishAuction(data->charid);
	Account_Map_Iter iter = account_map.find(data->charid);
	if(iter != account_map.end())
	{
		if( (iter->second.game_money < data->game_money && iter->second.rmb_money > data->rmb_money)
			|| (iter->second.game_money > data->game_money && iter->second.rmb_money < data->rmb_money))
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "数据库返回--通知GameServer扣钱数据有问题:%u, %u, %u, %u",msg.rmb_money, msg.game_money, iter->second.rmb_money, iter->second.game_money);
			return false;
		}
		else if(iter->second.game_money > data->game_money || iter->second.rmb_money > data->rmb_money)
		{
			msg.type = CSNotifyGameServerMoneyMsg::enumNotifyGameServer_AddMoney;
			msg.rmb_money = iter->second.rmb_money - data->rmb_money;
			msg.game_money = iter->second.game_money - data->game_money;
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "数据库返回--通知GameServer加钱:%u的寄售账号资金:%u,%u",data->charid, msg.rmb_money, msg.game_money);
		}
		else if(iter->second.game_money < data->game_money || iter->second.rmb_money < data->rmb_money )
		{
			msg.type = CSNotifyGameServerMoneyMsg::enumNotifyGameServer_SubMoney;
			msg.rmb_money = data->rmb_money - iter->second.rmb_money;
			msg.game_money = data->game_money - iter->second.game_money;
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "数据库返回--通知GameServer扣钱:%u的寄售账号资金:%u,%u",data->charid, msg.rmb_money, msg.game_money);
		}
	}
	else
	{
		//初次操作账号加钱，扣钱
		msg.type = CSNotifyGameServerMoneyMsg::enumNotifyGameServer_SubMoney;
		msg.rmb_money = data->rmb_money;
		msg.game_money = data->game_money;
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "数据库返回--初始化账号通知GameServer扣钱:%u的寄售账号资金:%u,%u",data->charid, msg.rmb_money, msg.game_money);
	}
	ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(data->charid);
	if(!client)
	{
		//EConstDefine_BaseRandMaxCount保护机制
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "数据库返回--通知GameServer扣钱:%u失败:%u,%u",data->charid, msg.rmb_money, msg.game_money);
		return false;
	}
	theGameServerManager.SendMsgToGameServerUser(client, &msg);
	return true;
}

void AuctionManager::loadUserAccount(CSLoadMysqlDataMsg *pLoadMsg, bool notifyclient)
{
	if(!pLoadMsg)
	{
		return;
	}
	for(DWORD i = 0; i < pLoadMsg->datanum; ++i)
	{
		AuctionAccount *data = (AuctionAccount*)&pLoadMsg->buffer[i * sizeof(AuctionAccount)];
		Account_Map_Iter iter = account_map.find(data->charid);
		if(iter != account_map.end())
		{
			iter->second = *data;
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "数据库返回--刷新用户:%u的寄售账号资金:%u,%u",data->charid, data->rmb_money, data->game_money);
		}
		else
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "数据库返回--新建用户:%u的寄售账号资金:%u,%u",data->charid, data->rmb_money, data->game_money);
			account_map[data->charid] = *data;
		}
		if(notifyclient)
		{
			ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(data->charid);
			this->sendAuctionAccountMoneyToUser(client);
		}
	}
}
void AuctionManager::AddOneAuctionItem(MoneyExChangeData *data)
{
	if(!data)
	{
		return;
	}
	MoneyExChangeData *item = new MoneyExChangeData();
	if(!item)
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "数据库返回--刷新寄售单分配内存失败");
		return;
	}
	item->auctionid = data->auctionid;
	item->seller = data->seller;
	item->buyer = data->buyer;
	item->gametime = data->gametime;
	item->num = data->num;
	item->price = data->price;
	item->selltype = data->selltype;
	auction_list[data->auctionid] = item;
	LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "数据库返回--增加寄售单:%u,%u:%u,%u,%u,%u", data->auctionid, data->seller, data->buyer, data->selltype,
		data->num, data->price);
}
void AuctionManager::loadGoldAuctionItem(CSLoadMysqlDataMsg *pLoadMsg)
{
	if(!pLoadMsg)
	{
		return;
	}
	for(DWORD i = 0; i < pLoadMsg->datanum; ++i)
	{
		MoneyExChangeData *data = (MoneyExChangeData*)&pLoadMsg->buffer[i * sizeof(MoneyExChangeData)];
		Auction_List_Iter iter = auction_list.find(data->auctionid);
		if(iter != auction_list.end())
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "数据库返回--重复刷新寄售单:%u:%u,%u,%u,%u", data->seller, data->buyer, data->selltype,
				data->num, data->price);
		}
		else
		{
			this->AddOneAuctionItem(data);
		}
	}
}

void AuctionManager::loadAuctionHistroy(CSLoadMysqlDataMsg *pLoadMsg)
{
	for(DWORD i = 0; i < pLoadMsg->datanum; ++i)
	{
		MoneyAuctionHistroy *data = (MoneyAuctionHistroy*)&pLoadMsg->buffer[i * sizeof(MoneyAuctionHistroy)];
		MoneyAuctionHistroy_List_Iter iter = moneyauction_histroylist.find(data->characterid);
		if(iter != moneyauction_histroylist.end())
		{
			(iter->second)[data->auctionid] = *data;
		}
		else
		{
			UserMoneyAuctionList histroy;
			histroy[data->auctionid] = *data;
			moneyauction_histroylist[data->characterid] = histroy;
		}
	}
}
void AuctionManager::UpdateAuctionMoneyToDB(ClientPeer *client,DWORD gamemoney, DWORD rmbmoney,uint8 type)
{
	if(!client)
	{	
		return;
	}
	CSSaveAuctionAccountDataMsg cmd;
	cmd.account.charid = client->GetCharDbId();
	cmd.account.game_money = gamemoney;
	cmd.account.rmb_money = rmbmoney;
	cmd.type = type;
	theMysqlCommunication.PushReqMessage(&cmd, 0);
	this->StartAuction(client->GetCharDbId());
	LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "向数据库保存:%u的寄售账号资金:[%u,%u],[%u,%u]",
		type, cmd.account.charid, cmd.account.game_money, cmd.account.rmb_money);
}
void AuctionManager::OnHandleAuctionMoney(MsgHandleSystemAuctionAccountMoney *pMsg, ClientPeer *client)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;		
	if(!this->isFinishMoneyAuctionLoad())
	{
		ack.result = enumSystemAuctionError_SystemBusy;
		goto FAIL;
	}
	if(this->CheckHaveAuction(client->GetCharDbId()))
	{
		ack.result = enumSystemAuctionError_SystemBusy;
		goto FAIL;
	}
	switch(pMsg->handletype)
	{
	case MsgHandleSystemAuctionAccountMoney::enum_AddSystemAuctionAccountMoney:
		{	
			if(pMsg->rmbmoney > enumAuctionMoney_AccountMaxRmb || pMsg->gamemoney > enumAuctionMoney_AccountMaxGameMoney)
			{
				ack.result = enumSystemAuctionError_TooMoney;
				goto FAIL;
			}
			Account_Map_Iter iter = account_map.find(client->GetCharDbId());
			if(iter != account_map.end())
			{
				if( iter->second.game_money + pMsg->gamemoney > enumAuctionMoney_AccountMaxGameMoney
					|| iter->second.rmb_money + pMsg->rmbmoney > enumAuctionMoney_AccountMaxRmb)
				{
					ack.result = enumSystemAuctionError_TooMoney;
					goto FAIL;
				}
				this->UpdateAuctionMoneyToDB(client, pMsg->gamemoney + iter->second.game_money, pMsg->rmbmoney + iter->second.rmb_money, enumHandleCenterDB_SaveAuctionAccountNotify);
			}
			else
			{
				this->UpdateAuctionMoneyToDB(client, pMsg->gamemoney, pMsg->rmbmoney, enumHandleCenterDB_SaveAuctionAccountNotify);
			}
		}
		break;
	case MsgHandleSystemAuctionAccountMoney::enum_RemoveSystemAuctionAccountMoney:
		{
			Account_Map_Iter iter = account_map.find(client->GetCharDbId());
			if(iter != account_map.end())
			{
				if(pMsg->rmbmoney > iter->second.rmb_money
					|| pMsg->gamemoney > iter->second.game_money
					|| pMsg->gamemoney > enumAuctionMoney_AccountMaxGameMoney 
					|| pMsg->rmbmoney > enumAuctionMoney_AccountMaxRmb)
				{
					ack.result = enumSystemAuctionError_NoMoney;
					goto FAIL;
				}
				this->UpdateAuctionMoneyToDB(client, iter->second.game_money - pMsg->gamemoney, iter->second.rmb_money - pMsg->rmbmoney, enumHandleCenterDB_SaveAuctionAccountNotify);
			}
			else
			{
				ack.result = enumSystemAuctionError_NoAccount;
				goto FAIL;
			}
		}
		break;
	default:
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "操作账户金钱类型出错:%u, %u", pMsg->handletype, client->GetCharDbId());
		}
		break;
	}
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::sendAuctionAccountMoneyToUser(ClientPeer *client)
{
	if(!client)
	{
		return;
	}
	MsgAckHandleSystemAuctionAccountMoney ack;
	Account_Map_Iter iter = account_map.find(client->GetCharDbId());
	if(iter != account_map.end())
	{
		ack.gamemoney = iter->second.game_money;
		ack.rmbmoney = iter->second.rmb_money;
	}
	theGameServerManager.SendMsgToGameServerUser(client,&ack);
}

void AuctionManager::removeAuctionItem(DWORD auctionid)
{
	Auction_List_Iter iter = auction_list.find(auctionid);
	if(iter != auction_list.end())
	{
		delete iter->second;
		auction_list.erase(auctionid);
	}
	else
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "删除交易记录出错:%u!", auctionid);
	}
}
void AuctionManager::AddAccountGameMoney(DWORD owner, DWORD money)
{
	Account_Map_Iter iter = account_map.find(owner);
	if(iter != account_map.end())
	{
		iter->second.game_money += money;
	}
	else
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "增加用户游戏币出错:%u, %u!", owner, money);
	}
}
void AuctionManager::AddAccountRmbMoney(DWORD owner, DWORD money)
{
	Account_Map_Iter iter = account_map.find(owner);
	if(iter != account_map.end())
	{
		iter->second.rmb_money += money;
	}
	else
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "增加用户金锭出错:%u, %u!", owner, money);
	}
}
void AuctionManager::SubAccountRmbMoney(DWORD owner, DWORD money)
{
	Account_Map_Iter iter = account_map.find(owner);
	if(iter != account_map.end())
	{
		if(iter->second.rmb_money > money)
		{
			iter->second.rmb_money -= money;
		}
	}
	else
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "减少用户金锭出错:%u, %u!", owner, money);
	}
}
void AuctionManager::SubAccountGameMoney(DWORD owner, DWORD money)
{
	Account_Map_Iter iter = account_map.find(owner);
	if(iter != account_map.end())
	{
		if(iter->second.game_money > money)
		{
			iter->second.game_money -= money;
		}
	}
	else
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "减少用户游戏币出错:%u, %u!", owner, money);
	}
}
void AuctionManager::AddOneHistroy(DWORD charactrid, MoneyAuctionHistroy data)
{
	MoneyAuctionHistroy_List_Iter iter = moneyauction_histroylist.find(charactrid);
	if(iter != moneyauction_histroylist.end())
	{
		(iter->second)[data.auctionid] = data;
	}
	else
	{
		UserMoneyAuctionList histroy;
		histroy[data.auctionid] = data;
		moneyauction_histroylist[data.characterid] = histroy;
	}
}
void AuctionManager::UpdateAuctionHistroy(CSExcuteAuctionListMsg *pSave)
{
	MoneyAuctionHistroy histroy;
	memcpy_s(&histroy, sizeof(histroy), &pSave->data, sizeof(MoneyExChangeData) - sizeof(DWORD));
	switch(pSave->excutetype)
	{
	case enumSystemAuctionSubType_SellRmb:
	case enumSystemAuctionSubType_SellGameMoney:
		{
			histroy.state = enumAuctionItemState_Running;
			this->AddOneHistroy(pSave->excute_charid, histroy);
		}
		break;
	case enumSystemAuctionSubType_BuyRmb:
		{
			histroy.state = enumAuctionItemState_Success;
			this->AddOneHistroy(pSave->excute_charid, histroy);

			histroy.selltype = enumSystemAuctionSubType_SellRmb;
			this->AddOneHistroy(histroy.characterid, histroy);
		}
		break;
	case enumSystemAuctionSubType_BuyGameMoney:
		{
			histroy.state = enumAuctionItemState_Success;
			this->AddOneHistroy(pSave->excute_charid, histroy);

			histroy.selltype = enumSystemAuctionSubType_SellGameMoney;
			this->AddOneHistroy(histroy.characterid, histroy);		
		}
		break;
	case enumSystemAuctionSubType_TerminateAuction:
		{		
			histroy.state = enumAuctionItemState_Terminate;
			this->AddOneHistroy(pSave->excute_charid, histroy);
		}
		break;
	case enumSystemAuctionSubType_AuctionTimeOut:
		{
			histroy.state = enumAuctionItemState_TimeOut;
			this->AddOneHistroy(pSave->excute_charid, histroy);
		}
		break;
	default:
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "更新历史记录类型出错:%u, %u!", pSave->excutetype, pSave->excute_charid);
		}
		break;
	}
}

void AuctionManager::OnExcuteAuction(MsgExcuteSystemAuction *pMsg, ClientPeer *client)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	Account_Map_Iter iter;
	if(!this->isFinishMoneyAuctionLoad())
	{
		ack.result = enumSystemAuctionError_SystemBusy;
		goto FAIL;
	}
	if(this->CheckHaveAuction(client->GetCharDbId()))
	{
		ack.result = enumSystemAuctionError_SystemBusy;
		goto FAIL;
	}
	iter = account_map.find(client->GetCharDbId());
	if(iter == account_map.end())
	{
		ack.result = enumSystemAuctionError_NoAccount;
		goto FAIL;
	}
	switch(pMsg->type)
	{
	case enumSystemAuctionSubType_SellRmb:
		{
			this->OnSellRmbAuction(client, pMsg, iter->second);
		}
		break;
	case enumSystemAuctionSubType_BuyRmb:
		{
			this->OnBuyRmbAuction(client, pMsg,  iter->second);
		}
		break;
	case enumSystemAuctionSubType_SellGameMoney:
		{
			this->OnSellGameMoneyAuction(client, pMsg, iter->second);
		}
		break;
	case enumSystemAuctionSubType_BuyGameMoney:
		{
			this->OnBuyGameMoneyAuction(client, pMsg,  iter->second);
		}
		break;
	case enumSystemAuctionSubType_QueryExchangeMoneyRecord:
		{
			this->sendAuctionHistroyToUser(client);
		}
		break;
	case enumSystemAuctionSubType_TerminateAuction:
		{
			this->OnTerminateAuction(client, pMsg,  iter->second);
		}
		break;

	default:
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "更新历史记录类型出错:%u, %u!", pMsg->type, client->GetCharDbId());
		}
		break;
	}
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::OnDBReturnExcuteResult(CSExcuteAuctionListMsg *pSave)
{
	switch(pSave->excutetype)
	{
	case enumSystemAuctionSubType_SellRmb:
		{
			this->OnAckSellRmbAuction(pSave);
		}
		break;
	case enumSystemAuctionSubType_BuyRmb:
		{
			this->OnAckBuyRmbAuction(pSave);
		}
		break;
	case enumSystemAuctionSubType_SellGameMoney:
		{
			this->OnAckSellGameMoneyAuction(pSave);
		}
		break;
	case enumSystemAuctionSubType_BuyGameMoney:
		{
			this->OnAckBuyGameMoneyAuction(pSave);
		}
		break;
	case enumSystemAuctionSubType_TerminateAuction:
		{
			this->OnAckTerminateAuction(pSave);
		}
		break;
	case enumSystemAuctionSubType_AuctionTimeOut:
		{
			this->OnAckAuctionTimeOut(pSave);
		}
		break;
	default:
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "金锭交易操作返回出错:%u!", pSave->excutetype);
		}
		break;
	}
	//结束操作
	this->FinishAuction(pSave->excute_charid);
}
/////////////////////////////出售金锭操作//////////////////
void AuctionManager::OnSellRmbAuction(ClientPeer *client, MsgExcuteSystemAuction *pMsg, AuctionAccount &account)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	CSExcuteAuctionListMsg query_msg;
	query_msg.excutetype = pMsg->type;

	if(pMsg->num < enumMinAuctionNum)
	{
		ack.result = enumSystemAuctionError_InsertItemFail;
		goto FAIL;
	}
	DWORD needRmb = (DWORD)(pMsg->num * ( 1 + systemAuctionRate) + 0.5);
	if(pMsg->num < 25)
	{
		//手续费至少1
		needRmb += 1;
	}
	if(account.rmb_money < needRmb)
	{
		ack.result = enumSystemAuctionError_NoMoney;
		goto FAIL;
	}
	if(account.game_money + pMsg->num * pMsg->money > enumAuctionMoney_AccountMaxGameMoney)
	{
		ack.result = enumSystemAuctionError_TooMoney;
		goto FAIL;
	}
	query_msg.data.fillData(0,enumSystemAuctionSubType_SellRmb, client->GetCharDbId(), pMsg->money, pMsg->num, TimeEx::GetCurrentTime().GetTime(), 0);
	if(strlen(pMsg->buyername) <= dr_MaxUserName)
	{
		strncpy_s(query_msg.buyername, dr_MaxUserName, pMsg->buyername, strlen(pMsg->buyername));
	}
	query_msg.excute_charid = client->GetCharDbId();
	theMysqlCommunication.PushReqMessage(&query_msg, 0);
	this->StartAuction(client->GetCharDbId());
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}

void AuctionManager::OnAckSellRmbAuction(CSExcuteAuctionListMsg *pSave)
{
	if(!pSave)
	{
		return;
	}
	ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(pSave->excute_charid);
	if(!client)
	{
		return;
	}
	
	MsgAckExcuteSystemAuction ack;
	if(pSave->result != enumSystemAuction_Success)
	{
		ack.result = ack.result;
		theGameServerManager.SendMsgToGameServerUser(client, &ack);
		return;
	}
	//执行成功,EConstDefine_BaseRandMaxCount 执行成功
	this->AddOneAuctionItem(&pSave->data);
	//扣金币
	DWORD needRmb = (DWORD)(pSave->data.num * ( 1 + systemAuctionRate) + 0.5);
	if(pSave->data.num < 25)
	{
		needRmb += 1;
	}
	this->SubAccountRmbMoney(pSave->excute_charid, needRmb );
	//处理历史记录
	this->UpdateAuctionHistroy(pSave);
	this->sendAuctionAccountMoneyToUser(client);
	this->queryAuctionListByType(client, enumAuctionQueryType_BuyRmbShowAll);
	this->TellWorldMoneyAuction(enumSystemAuctionSubType_SellRmb, pSave->data.num, pSave->data.price);
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}

//////////////////////购买金锭/////////////////////////////////
void AuctionManager::OnBuyRmbAuction(ClientPeer *client, MsgExcuteSystemAuction *pMsg, AuctionAccount &account)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	CSExcuteAuctionListMsg query_msg;
	query_msg.excute_charid = client->GetCharDbId();
	query_msg.excutetype = pMsg->type;
	query_msg.queryid = pMsg->queryid;
	query_msg.querynum = pMsg->querynum;

	Auction_List_Iter iter = auction_list.find(pMsg->auctionid);
	if(iter == auction_list.end())
	{
		ack.result = enumSystemAuctionError_NoItem;
		goto FAIL;
	}
	if(account.game_money < iter->second->num * iter->second->price)
	{
		ack.result = enumSystemAuctionError_NoMoney;
		goto FAIL;
	}
	if(account.rmb_money + iter->second->num  > enumAuctionMoney_AccountMaxRmb)
	{
		ack.result = enumSystemAuctionError_TooMoney;
		goto FAIL;
	}
	if(iter->second->seller == client->GetCharDbId())
	{
		ack.result = enumSystemAuctionError_CannotBuySelfItem;
		goto FAIL;
	}
	if(iter->second->buyer && iter->second->buyer != client->GetCharDbId())
	{
		ack.result = enumSystemAuctionError_NotDefineBuyer;
		goto FAIL;
	}
	query_msg.data.fillData(pMsg->auctionid, enumSystemAuctionSubType_BuyRmb, iter->second->seller, iter->second->price, iter->second->num, TimeEx::GetCurrentTime().GetTime(), 0);
	theMysqlCommunication.PushReqMessage(&query_msg, 0);
	this->StartAuction(client->GetCharDbId());
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::OnAckBuyRmbAuction(CSExcuteAuctionListMsg *pSave)
{
	if(!pSave)
	{
		return;
	}
	ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(pSave->excute_charid);
	if(!client)
	{
		return;
	}
	
	MsgAckExcuteSystemAuction ack;
	if(pSave->result != enumSystemAuction_Success)
	{
		ack.result = pSave->result;
		theGameServerManager.SendMsgToGameServerUser(client, &ack);
		return;
	}
	//删除记录
	this->removeAuctionItem(pSave->data.auctionid);
	//买房加金锭
	this->AddAccountRmbMoney(pSave->excute_charid, pSave->data.num);
	this->SubAccountGameMoney(pSave->excute_charid, pSave->data.price * pSave->data.num);
	//卖方加游戏币
	this->AddAccountGameMoney(pSave->data.seller, pSave->data.price * pSave->data.num);
	//加记录
	this->UpdateAuctionHistroy(pSave);
	this->sendAuctionAccountMoneyToUser(client);
	//返回列表
	if(pSave->queryid)
	{
		this->queryAuctionListByType(client, enumAuctionQueryType_BuyRmbDefineMe);
	}
	else if(pSave->querynum)
	{
		this->queryAuctionListByType(client, enumAuctionQueryType_BuyRmbNum, pSave->querynum);
	}
	else
	{
		this->queryAuctionListByType(client, enumAuctionQueryType_BuyRmbShowAll);
	}
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
///////////////////////////卖游戏币//////////////////////////////
void AuctionManager::OnSellGameMoneyAuction(ClientPeer *client, MsgExcuteSystemAuction *pMsg, AuctionAccount &account)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	CSExcuteAuctionListMsg query_msg;
	query_msg.excutetype = pMsg->type;
	query_msg.excute_charid = client->GetCharDbId();

	if(pMsg->num < enumMinAuctionNum)
	{
		ack.result = enumSystemAuctionError_InsertItemFail;
		goto FAIL;
	}
	if(account.game_money < (DWORD)(pMsg->num * pMsg->money * (1.0 + systemAuctionRate)+ 0.5))
	{
		ack.result = enumSystemAuctionError_NoMoney;
		goto FAIL;
	}
	if(account.rmb_money + pMsg->num > enumAuctionMoney_AccountMaxRmb)
	{
		ack.result = enumSystemAuctionError_TooMoney;
		goto FAIL;
	}
	query_msg.data.fillData(0,enumSystemAuctionSubType_SellGameMoney, client->GetCharDbId(), pMsg->money, pMsg->num, TimeEx::GetCurrentTime().GetTime(), 0);
	if(strlen(pMsg->buyername) <= dr_MaxUserName)
	{
		strncpy_s(query_msg.buyername, dr_MaxUserName - 1 , pMsg->buyername, strlen(pMsg->buyername));
	}
	theMysqlCommunication.PushReqMessage(&query_msg, 0);
	this->StartAuction(client->GetCharDbId());
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::OnAckSellGameMoneyAuction(CSExcuteAuctionListMsg *pSave)
{
	if(!pSave)
	{
		return;
	}
	ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(pSave->excute_charid);
	if(!client)
	{
		return;
	}

	MsgAckExcuteSystemAuction ack;
	if(pSave->result != enumSystemAuction_Success)
	{
		ack.result = pSave->result;
		theGameServerManager.SendMsgToGameServerUser(client, &ack);
		return;
	}
	//执行成功,
	this->AddOneAuctionItem(&pSave->data);
	//扣游戏币
	this->SubAccountGameMoney(pSave->excute_charid, (DWORD)(pSave->data.num * pSave->data.price * (1.0 + systemAuctionRate) + 0.5));
	//加记录
	this->UpdateAuctionHistroy(pSave);
	this->sendAuctionAccountMoneyToUser(client);
	this->queryAuctionListByType(client, enumAuctionQueryType_BuyGameMoneyShowAll);
	//this->TellWorldMoneyAuction(enumSystemAuctionSubType_SellGameMoney, pSave->data.num, pSave->data.price * pSave->data.num);
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
/////////////////////////////买游戏币操作//////////////////////////
void AuctionManager::OnBuyGameMoneyAuction(ClientPeer *client, MsgExcuteSystemAuction *pMsg, AuctionAccount &account)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	CSExcuteAuctionListMsg query_msg;
	query_msg.excute_charid = client->GetCharDbId();
	query_msg.excutetype = pMsg->type;
	query_msg.queryid = pMsg->queryid;
	query_msg.querynum = pMsg->querynum;

	Auction_List_Iter iter = auction_list.find(pMsg->auctionid);
	if(iter == auction_list.end())
	{
		ack.result = enumSystemAuctionError_NoItem;
		goto FAIL;
	}
	if(account.game_money < iter->second->num * iter->second->price)
	{
		ack.result = enumSystemAuctionError_NoMoney;
		goto FAIL;
	}
	if(account.rmb_money + iter->second->num  > enumAuctionMoney_AccountMaxGameMoney)
	{
		ack.result = enumSystemAuctionError_TooMoney;
		goto FAIL;
	}
	if(iter->second->seller == client->GetCharDbId())
	{
		ack.result = enumSystemAuctionError_CannotBuySelfItem;
		goto FAIL;
	}
	query_msg.data.fillData(pMsg->auctionid, enumSystemAuctionSubType_BuyGameMoney, iter->second->seller, iter->second->price, iter->second->num, TimeEx::GetCurrentTime().GetTime(), 0);
	theMysqlCommunication.PushReqMessage(&query_msg, 0);
	this->StartAuction(client->GetCharDbId());
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::OnAckBuyGameMoneyAuction(CSExcuteAuctionListMsg *pSave)
{
	if(!pSave)
	{
		return;
	}
	ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(pSave->excute_charid);
	if(!client)
	{
		return;
	}

	MsgAckExcuteSystemAuction ack;
	if(pSave->result != enumSystemAuction_Success)
	{
		ack.result = pSave->result;
		theGameServerManager.SendMsgToGameServerUser(client, &ack);
		return;
	}
	//删除记录
	this->removeAuctionItem(pSave->data.auctionid);
	//卖方加金锭
	this->AddAccountRmbMoney(pSave->data.seller, pSave->data.num);
	//买房加游戏币
	this->AddAccountGameMoney(pSave->excute_charid, pSave->data.num * pSave->data.price);
	this->SubAccountRmbMoney(pSave->excute_charid, pSave->data.num);
	//加记录
	this->UpdateAuctionHistroy(pSave);
	this->sendAuctionAccountMoneyToUser(client);
	//返回列表
	if(pSave->queryid)
	{
		this->queryAuctionListByType(client, enumAuctionQueryType_BuyGameMoneyDefineMe);
	}
	else if(pSave->querynum)
	{
		this->queryAuctionListByType(client, enumAuctionQueryType_BuyGameMoneyNum, pSave->querynum);
	}
	else
	{
		this->queryAuctionListByType(client, enumAuctionQueryType_BuyGameMoneyShowAll);
	}
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}

////////////////////////取消委托///////////////////////////////////
void AuctionManager::OnTerminateAuction(ClientPeer *client, MsgExcuteSystemAuction *pMsg, AuctionAccount &account)
{
	if(!pMsg || !client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	CSExcuteAuctionListMsg query_msg;
	query_msg.excute_charid = client->GetCharDbId();
	query_msg.excutetype = pMsg->type;

	Auction_List_Iter iter = auction_list.find(pMsg->auctionid);
	if(iter == auction_list.end())
	{
		ack.result = enumSystemAuctionError_CannotCancel;
		goto FAIL;
	}	
	if(iter->second->seller != client->GetCharDbId())
	{
		ack.result = enumSystemAuctionError_NotSelfItem;
	}
	query_msg.data.auctionid = iter->second->auctionid;
	query_msg.data.fillData(pMsg->auctionid, iter->second->selltype, iter->second->seller, iter->second->price, iter->second->num, TimeEx::GetCurrentTime().GetTime(), 0);
	theMysqlCommunication.PushReqMessage(&query_msg, 0);
	this->StartAuction(client->GetCharDbId());
	return;
FAIL:
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::OnAckTerminateAuction(CSExcuteAuctionListMsg *pSave)
{
	if(!pSave)
	{
		return;
	}
	ClientPeer *client = theClientPeerManager.GetClientPeerByDBId(pSave->excute_charid);
	if(!client)
	{
		return;
	}
	MsgAckExcuteSystemAuction ack;
	if(pSave->result != enumSystemAuction_Success)
	{
		ack.result = pSave->result;
		theGameServerManager.SendMsgToGameServerUser(client, &ack);
		return;
	}
	//删除记录
	this->removeAuctionItem(pSave->data.auctionid);
	//卖房加游戏币
	if(pSave->data.selltype == enumSystemAuctionSubType_SellRmb)
	{
		this->AddAccountRmbMoney(pSave->excute_charid, pSave->data.num);
	}
	else if(pSave->data.selltype == enumSystemAuctionSubType_SellGameMoney )
	{
		this->AddAccountGameMoney(pSave->excute_charid, pSave->data.price * pSave->data.num);
	}	
	//加记录
	this->UpdateAuctionHistroy(pSave);
	this->sendAuctionAccountMoneyToUser(client);
	this->queryAuctionListByType(client, enumAuctionQueryType_All);
	this->sendAuctionHistroyToUser(client);
	theGameServerManager.SendMsgToGameServerUser(client, &ack);
}
void AuctionManager::OnAuctionTimeOut(MoneyExChangeData *data)
{
	if(!data)
	{
		return;
	}
	CSExcuteAuctionListMsg query_msg;
	query_msg.excute_charid = data->seller;
	query_msg.excutetype = enumSystemAuctionSubType_AuctionTimeOut;
	query_msg.data.auctionid = data->auctionid;
	query_msg.data.fillData(data->auctionid, data->selltype, data->seller, data->price, data->num, TimeEx::GetCurrentTime().GetTime(), 0);
	theMysqlCommunication.PushReqMessage(&query_msg, 0);
	this->StartAuction(data->seller);
}
void AuctionManager::OnAckAuctionTimeOut(CSExcuteAuctionListMsg *pSave)
{
	if(!pSave)
	{
		return;
	}
	if(pSave->result != enumSystemAuction_Success)
	{
		return;
	}
	//删除记录
	this->removeAuctionItem(pSave->data.auctionid);
	//卖房加游戏币
	if(pSave->data.selltype == enumSystemAuctionSubType_SellRmb)
	{
		this->AddAccountRmbMoney(pSave->excute_charid, pSave->data.num);
	}
	else if(pSave->data.selltype == enumSystemAuctionSubType_SellGameMoney )
	{
		this->AddAccountGameMoney(pSave->excute_charid, pSave->data.price * pSave->data.num);
	}	
	//加记录
	this->UpdateAuctionHistroy(pSave);
}
bool Sort_FunctionAesc(MoneyExChangeData *before, MoneyExChangeData *after)
{
	return before->price < after->price;
}
bool Sort_FunctionDesc(MoneyExChangeData *before, MoneyExChangeData *after)
{
	return before->price > after->price;
}

void AuctionManager::findQueryItem(DWORD num, DWORD userid, DWORD userid2)
{
	sellrmb_temp.reserve(auction_list.size());
	sellmoney_temp.reserve(auction_list.size());

	MsgReturnSystemAuction ack;
	ack.type = enumAuctionExchangeGameMoneyAndRMB;
	Auction_List_Iter iter = auction_list.begin();
	for(; iter != auction_list.end(); ++iter)
	{
		if(iter->second->selltype == enumSystemAuctionSubType_SellRmb && 
			(!num || num == iter->second->num) &&
			(userid == iter->second->buyer || userid2 == iter->second->buyer))
		{
			sellrmb_temp.push_back(iter->second);
		}
		else if(iter->second->selltype == enumSystemAuctionSubType_SellGameMoney &&
			(!num || num == iter->second->num) &&
			(iter->second->buyer == userid || userid2 == iter->second->buyer))
		{
			sellmoney_temp.push_back(iter->second);
		}
	}
	//寄售金锭
	std::sort(sellrmb_temp.begin(), sellrmb_temp.end(),Sort_FunctionAesc);
	//收购金锭
	std::sort(sellmoney_temp.begin(), sellmoney_temp.end(), Sort_FunctionDesc);
}
void AuctionManager::sendAuctionItemToUserByType(ClientPeer *client, BYTE selltype)
{
	if(!client)
	{
		return;
	}
	MsgReturnSystemAuction ack;
	ack.subtype = selltype;
	if(selltype == enumSystemAuctionSubType_SellRmb)
	{
		int num = sellrmb_temp.size();
		for(int i = 0; i < enumSendToClientAuction_Num && i < num; ++i)
		{
			MoneyExChangeData *data = sellrmb_temp[i];
			ReturnExchangeMoney *buffer = (ReturnExchangeMoney *)&ack.buffer[ack.buffersize];
			buffer->auctionid = data->auctionid;
			buffer->allmoney = data->num * data->price;
			buffer->num = data->num;
			buffer->type = data->selltype;
			ack.buffersize += sizeof(ReturnExchangeMoney);
			ack.header.stLength += sizeof(ReturnExchangeMoney);
		}
	
	}
	else if(selltype == enumSystemAuctionSubType_SellGameMoney)
	{
		int num = sellmoney_temp.size();
		for(int i = 0; i < enumSendToClientAuction_Num && i < num; ++i)
		{
			MoneyExChangeData *data = sellmoney_temp[i];
			ReturnExchangeMoney *buffer = (ReturnExchangeMoney *)&ack.buffer[ack.buffersize];
			buffer->auctionid = data->auctionid;
			buffer->allmoney = data->num * data->price;
			buffer->num = data->num;
			buffer->type = data->selltype;
			ack.buffersize += sizeof(ReturnExchangeMoney);
			ack.header.stLength += sizeof(ReturnExchangeMoney);
		}
	}
	else
	{
		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "错误的发送金锭交易类型");
		return;
	}
	theGameServerManager.SendMsgToGameServerUser(client,&ack);
}
void AuctionManager::queryAuctionListByType(ClientPeer *client, BYTE type, DWORD num)
{
	MsgQuerySystemAuctionItemList query;
	query.querytype = type;	
	query.num = num;
	this->queryAuctionList(client, &query);
}
void AuctionManager::queryAuctionList(ClientPeer *client, MsgQuerySystemAuctionItemList *pQuery)
{
	if(!client)
	{
		return;
	}
	sellrmb_temp.clear();
	sellmoney_temp.clear();
	switch(pQuery->querytype)
	{
	case enumAuctionQueryType_BuyRmbShowAll:
		{
			this->findQueryItem(0, 0);
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellRmb);
		}
		break;
	case enumAuctionQueryType_BuyGameMoneyShowAll:
		{
			this->findQueryItem(0, 0);
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellGameMoney);
		}
		break;
	case enumAuctionQueryType_BuyRmbDefineMe:
		{
			this->findQueryItem(0, client->GetCharDbId());
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellRmb);
		}
		break;
	case enumAuctionQueryType_BuyGameMoneyDefineMe:
		{
			this->findQueryItem(0, client->GetCharDbId());
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellGameMoney);
		}
		break;
	case enumAuctionQueryType_BuyRmbNum:
		{
			this->findQueryItem(pQuery->num, 0, client->GetCharDbId());
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellRmb);
		}
		break;
	case enumAuctionQueryType_BuyGameMoneyNum:
		{
			this->findQueryItem(pQuery->num, 0, client->GetCharDbId());
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellGameMoney);
		}
		break;
	case enumAuctionQueryType_All:
		{
			this->findQueryItem(0, 0);
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellRmb);
			this->sendAuctionItemToUserByType(client, enumSystemAuctionSubType_SellGameMoney);
		}
		break;
	default:
		{
			LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "检索金锭交易类型出错");
			return;
		}
		break;
	}
	sellmoney_temp.clear();
	sellrmb_temp.clear();
}
void AuctionManager::sendAuctionHistroyToUser(ClientPeer *client)
{
	if(!client)
	{
		return;
	}
	MoneyAuctionHistroy_List_Iter iter = moneyauction_histroylist.find(client->GetCharDbId());
	if(iter != moneyauction_histroylist.end())
	{
		MsgAuctionHistroyList ack;
		UserMoneyAuctionList_Iter his_iter = iter->second.begin();
		for(; his_iter != iter->second.end(); ++his_iter)
		{
			if(ack.num > MsgAuctionHistroyList::enumHistroyNum - 1)
			{
				theGameServerManager.SendMsgToGameServerUser(client,&ack);
				ack.reset();
			}
			ack.data[ack.num ++] = his_iter->second;
			ack.header.stLength += sizeof(MoneyAuctionHistroy);
		}
		theGameServerManager.SendMsgToGameServerUser(client,&ack);
	}
}

void AuctionManager::TellWorldMoneyAuction(BYTE sellType, DWORD num, DWORD price)
{
	int gold = price / 10000;
	int silver = (price - gold * 10000) / 100;
	int copper = price - gold * 10000 - silver * 100;
	char str[256];
	char str2[256];
	if(gold>0)
	{
		sprintf_s(str,255,"%d金",gold);
		if(silver>0)
		{
			sprintf_s(str,255,"%s%d银",str,silver);
			if(copper>0)
			{
				sprintf_s(str,255,"%s%d铜",str,copper);
			}
		}
		else if(copper>0)
		{
			sprintf_s(str,255,"%s%d铜",str,copper);
		}
	}
	else
	{
		if(silver>0)
		{
			sprintf_s(str,255,"%d银",silver);
			if(copper>0)
			{
				sprintf_s(str,255,"%s%d铜",str,copper);
			}
		}
		else if(copper>0)
		{
			sprintf_s(str,255,"%d铜",copper);
		}
	}
	if(sellType == enumSystemAuctionSubType_SellRmb)
	{
		sprintf_s(str2, 255, theXmlString.GetString(eText_TellWorldMoneyAuction), str, "寄售", num);
	}
	else if(sellType == enumSystemAuctionSubType_SellGameMoney)
	{
		sprintf_s(str2, 255, theXmlString.GetString(eText_TellWorldMoneyAuction), str, "收购", num);
	}
	MsgChat chat( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	chat.SetString(str2);
	theGameServerManager.SendMsgToWorldUser(&chat);
}

bool AuctionManager::CheckHaveAuction(DWORD characterID)
{
	UserHandleMap_Iter iter = userHandleMap.find(characterID);
	if(iter != userHandleMap.end())
	{
		return true;
	}
	return false;
}
void AuctionManager::StartAuction(DWORD characterID)
{
	userHandleMap[characterID] = HQ_TimeGetTime();
}
void AuctionManager::FinishAuction(DWORD characterID)
{
	userHandleMap.erase(characterID);
}
void AuctionManager::Loop()
{
	if(tenSec && (*tenSec)( HQ_TimeGetTime() ))
	{
		UserHandleMap_Iter iter = userHandleMap.begin();
		for(; iter != userHandleMap.end();)
		{
			if( (HQ_TimeGetTime() - iter->second) > 15 * 1000L)
			{
				iter = userHandleMap.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		uint64 currentTime = TimeEx::GetCurrentTime().GetTime();
		Auction_List_Iter listIter = auction_list.begin();
		for(; listIter != auction_list.end(); ++listIter)
		{
			if( (currentTime - listIter->second->gametime) > 7 * 24 * 3600)
			{
				this->OnAuctionTimeOut(listIter->second);
			}
		}
	}
}