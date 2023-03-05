/********************************************************************
Filename: 	Auction.h
MaintenanceMan Mail: lufeipeng@163.com
Brief: 系统寄售，暂时实现寄售金锭
*********************************************************************/
#ifndef _AUCTION_H_
#define _AUCTION_H_

#include "MeRTLibsServer.h"
#include "Memory_Pool.h"
#include "Singleton.h"
#include "CenterGameMessage.h"
#include "aTime.h"

class ClientPeer;
struct MsgHandleSystemAuctionAccountMoney;
struct CSLoadMysqlDataMsg;
struct MsgExcuteSystemAuction;
struct MsgQuerySystemAuctionItemList;


//寄售系统管理
class AuctionManager: public ISingletion<AuctionManager>
{
public:
		enum
		{
			enumMinAuctionNum = 15,
			enumSendToClientAuction_Num = 10,	
		};
		//初始化系统寄售系统
		bool init();
		//是否完成系统寄售账号的加载
		bool isFinishLoadAccount()
		{
			return is_finishloadcount;
		}
		//完成用户账号数据加载
		void setFinishLoadAccount()
		{
			is_finishloadcount = true;
		}
		//是否完成系统寄售账号的加载
		bool isFinishLoadAuctionList()
		{
			return is_finishload_auctionlist;
		}
		//完成用户账号数据加载
		void setFinishLoadAuctionList()
		{
			is_finishload_auctionlist = true;
		}
		//是否完成金银交易数据加载
		bool isFinishMoneyAuctionLoad()
		{
			return (is_finishloadcount && is_finishload_auctionlist);
		}
		//交易历史记录加载
		void setFinishLoadAuctionHistroy()
		{
			 isfinish_loadhistroy = true;
		}
		bool isFinishLoadAuctionHistroy()
		{
			return isfinish_loadhistroy;
		}
		//重新加载用户寄售账号数据
		void tryReloadData(DWORD currentTime);
		//加载用户账号数据
		void loadUserAccount(CSLoadMysqlDataMsg *pLoadMsg, bool notifyclient = false);
		//加载一条金锭寄售单子
		void AddOneAuctionItem(MoneyExChangeData *data);
		//加载金锭寄售单子
		void loadGoldAuctionItem(CSLoadMysqlDataMsg *pLoadMsg);

		//发送寄售账号资金给用户
		void sendAuctionAccountMoneyToUser(ClientPeer *client);
		//发送寄售记录给客户端
		void sendAuctionHistroyToUser(ClientPeer *client);
		//操作账号资金
		void OnHandleAuctionMoney(MsgHandleSystemAuctionAccountMoney *pMsg, ClientPeer *client);
		//更新账号资金到DB
		void UpdateAuctionMoneyToDB(ClientPeer *client,DWORD gamemoney, DWORD rmbmoney,uint8 type);
		//通知GameServer对包裹金钱进行操作
		bool AuctionManager::notifyGameServerMoney(CSLoadMysqlDataMsg *pLoadMsg);
		//操作账号的钱
		void AuctionManager::AddAccountGameMoney(DWORD owner, DWORD money);
		void AuctionManager::AddAccountRmbMoney(DWORD owner, DWORD money);
		void AuctionManager::SubAccountRmbMoney(DWORD owner, DWORD money);
		void AuctionManager::SubAccountGameMoney(DWORD owner, DWORD money);
		//处理操作
		void OnExcuteAuction(MsgExcuteSystemAuction *pMsg, ClientPeer *client);
		void OnSellRmbAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnBuyRmbAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnSellGameMoneyAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnBuyGameMoneyAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnTerminateAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnAuctionTimeOut(MoneyExChangeData *data);
		//处理DB返回
		void OnDBReturnExcuteResult(CSExcuteAuctionListMsg *pSave);
		void OnAckSellRmbAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckBuyRmbAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckSellGameMoneyAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckBuyGameMoneyAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckTerminateAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckAuctionTimeOut(CSExcuteAuctionListMsg *pSave);
		//删除记录
		void removeAuctionItem(DWORD auctionid);
		//检索寄售列表
		void findQueryItem(DWORD num, DWORD userid, DWORD userid2 = (DWORD)-1);
		void queryAuctionListByType(ClientPeer *client,  BYTE type, DWORD num = 0);
		void queryAuctionList(ClientPeer *client, MsgQuerySystemAuctionItemList *pQuery);
		void sendAuctionItemToUserByType(ClientPeer *client, BYTE selltype);
		void TellWorldMoneyAuction(BYTE sellType, DWORD num, DWORD price);
		//加载寄售记录
		void loadAuctionHistroy(CSLoadMysqlDataMsg *pLoadMsg);
		//执行操作后处理历史记录
		void UpdateAuctionHistroy(CSExcuteAuctionListMsg *pSave);
		void AddOneHistroy(DWORD charactrid, MoneyAuctionHistroy data);
		//循环
		void Loop();
		//是否已经在操作中
		bool CheckHaveAuction(DWORD characterID);
		//开始操作
		void StartAuction(DWORD characterID);
		//结束操作
		void FinishAuction(DWORD characterID);
private:
		//定义下管理用户账号的容器
		typedef std::map<DWORD, AuctionAccount> Account_Map;
		typedef std::map<DWORD, AuctionAccount>::iterator Account_Map_Iter;
		Account_Map account_map;
		bool is_finishloadcount;		//是否完成用户账号的加载

		//定一下寄售金锭单子容器
		typedef std::map<DWORD, MoneyExChangeData*> Auction_List;
		typedef std::map<DWORD, MoneyExChangeData*>::iterator Auction_List_Iter;
		Auction_List auction_list;
		bool is_finishload_auctionlist;	//是否完成寄售金锭单子加载

		//定义下临时排序的容器
		typedef std::vector<MoneyExChangeData*> Auction_SortList;
		typedef std::vector<MoneyExChangeData*>::iterator Auction_SortList_Iter;
		//两个临时容器共检索用
		Auction_SortList sellrmb_temp;
		Auction_SortList sellmoney_temp;
		
		//历史记录
		typedef std::map<DWORD, MoneyAuctionHistroy> UserMoneyAuctionList;
		typedef std::map<DWORD, MoneyAuctionHistroy>::iterator UserMoneyAuctionList_Iter;
		typedef std::map<DWORD, UserMoneyAuctionList> MoneyAuctionHistroy_List;
		typedef std::map<DWORD, UserMoneyAuctionList>::iterator MoneyAuctionHistroy_List_Iter;
		MoneyAuctionHistroy_List moneyauction_histroylist;
		bool isfinish_loadhistroy;		//是否完成交易历史记录加载

		//用户操作列表
		typedef std::map<DWORD, DWORD> UserHandleMap;
		typedef std::map<DWORD, DWORD>::iterator UserHandleMap_Iter;
		UserHandleMap userHandleMap;

		//循环定时器，删除操作的操作
		HRTimer *tenSec;
};

#endif