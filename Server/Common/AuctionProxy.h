/********************************************************************
Filename: 	AuctionProxy.h
MaintenanceMan Mail: lufeipeng@163.com
Brief: 系统寄售，暂时实现寄售金锭
*********************************************************************/
#ifndef _AUCTION_PROXY_
#define _AUCTION_PROXY_

#include "MeRTLibsServer.h"

class GamePlayer;
struct Msg;

//定义寄售GameServer信息处理
class AuctionProxy
{
public:
	AuctionProxy():rmb_money(0), game_money(0), owner(NULL)
	{
	}
	~AuctionProxy()
	{
		owner = NULL;
	}
	void SetOwner(GamePlayer *player)
	{
		owner = player;
	}
	//寄售系统消息处理
	void OnClientHandleAuctionMoney(Msg* pMsg);
	void OnClientExcuteAuction(Msg* pMsg);

	//CenterServer同步寄售账号金钱
	void OnServerHandleAuctionMoney(Msg *pMsg);
	//刷新寄售账号资金
	void OnAckHandleAuctionAccountMoney(Msg *pMsg);
public:
	DWORD getAuctionRmb()
	{
		return rmb_money;
	}
	DWORD getAuctionGameMoney()
	{
		return game_money;
	}
	void setAuctionRmb(DWORD money)
	{
		rmb_money = money;
	}
	void setAuctionGameMoney(DWORD money)
	{
		game_money = money;
	}
	void OpenSystemAuction();
private:
	//账号的资金只是CenterServer账号资金的缓存，实际的加减操作放CenterServer
	//寄售账号金锭数量
	DWORD	rmb_money;
	//寄售账号金子数量
	DWORD game_money;
	//当前寄售的主人
	GamePlayer *owner;
};
#endif