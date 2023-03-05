/********************************************************************
Filename: 	AuctionProxy.h
MaintenanceMan Mail: lufeipeng@163.com
Brief: ϵͳ���ۣ���ʱʵ�ּ��۽�
*********************************************************************/
#ifndef _AUCTION_PROXY_
#define _AUCTION_PROXY_

#include "MeRTLibsServer.h"

class GamePlayer;
struct Msg;

//�������GameServer��Ϣ����
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
	//����ϵͳ��Ϣ����
	void OnClientHandleAuctionMoney(Msg* pMsg);
	void OnClientExcuteAuction(Msg* pMsg);

	//CenterServerͬ�������˺Ž�Ǯ
	void OnServerHandleAuctionMoney(Msg *pMsg);
	//ˢ�¼����˺��ʽ�
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
	//�˺ŵ��ʽ�ֻ��CenterServer�˺��ʽ�Ļ��棬ʵ�ʵļӼ�������CenterServer
	//�����˺Ž�����
	DWORD	rmb_money;
	//�����˺Ž�������
	DWORD game_money;
	//��ǰ���۵�����
	GamePlayer *owner;
};
#endif