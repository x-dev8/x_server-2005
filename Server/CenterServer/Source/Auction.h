/********************************************************************
Filename: 	Auction.h
MaintenanceMan Mail: lufeipeng@163.com
Brief: ϵͳ���ۣ���ʱʵ�ּ��۽�
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


//����ϵͳ����
class AuctionManager: public ISingletion<AuctionManager>
{
public:
		enum
		{
			enumMinAuctionNum = 15,
			enumSendToClientAuction_Num = 10,	
		};
		//��ʼ��ϵͳ����ϵͳ
		bool init();
		//�Ƿ����ϵͳ�����˺ŵļ���
		bool isFinishLoadAccount()
		{
			return is_finishloadcount;
		}
		//����û��˺����ݼ���
		void setFinishLoadAccount()
		{
			is_finishloadcount = true;
		}
		//�Ƿ����ϵͳ�����˺ŵļ���
		bool isFinishLoadAuctionList()
		{
			return is_finishload_auctionlist;
		}
		//����û��˺����ݼ���
		void setFinishLoadAuctionList()
		{
			is_finishload_auctionlist = true;
		}
		//�Ƿ���ɽ����������ݼ���
		bool isFinishMoneyAuctionLoad()
		{
			return (is_finishloadcount && is_finishload_auctionlist);
		}
		//������ʷ��¼����
		void setFinishLoadAuctionHistroy()
		{
			 isfinish_loadhistroy = true;
		}
		bool isFinishLoadAuctionHistroy()
		{
			return isfinish_loadhistroy;
		}
		//���¼����û������˺�����
		void tryReloadData(DWORD currentTime);
		//�����û��˺�����
		void loadUserAccount(CSLoadMysqlDataMsg *pLoadMsg, bool notifyclient = false);
		//����һ���𶧼��۵���
		void AddOneAuctionItem(MoneyExChangeData *data);
		//���ؽ𶧼��۵���
		void loadGoldAuctionItem(CSLoadMysqlDataMsg *pLoadMsg);

		//���ͼ����˺��ʽ���û�
		void sendAuctionAccountMoneyToUser(ClientPeer *client);
		//���ͼ��ۼ�¼���ͻ���
		void sendAuctionHistroyToUser(ClientPeer *client);
		//�����˺��ʽ�
		void OnHandleAuctionMoney(MsgHandleSystemAuctionAccountMoney *pMsg, ClientPeer *client);
		//�����˺��ʽ�DB
		void UpdateAuctionMoneyToDB(ClientPeer *client,DWORD gamemoney, DWORD rmbmoney,uint8 type);
		//֪ͨGameServer�԰�����Ǯ���в���
		bool AuctionManager::notifyGameServerMoney(CSLoadMysqlDataMsg *pLoadMsg);
		//�����˺ŵ�Ǯ
		void AuctionManager::AddAccountGameMoney(DWORD owner, DWORD money);
		void AuctionManager::AddAccountRmbMoney(DWORD owner, DWORD money);
		void AuctionManager::SubAccountRmbMoney(DWORD owner, DWORD money);
		void AuctionManager::SubAccountGameMoney(DWORD owner, DWORD money);
		//�������
		void OnExcuteAuction(MsgExcuteSystemAuction *pMsg, ClientPeer *client);
		void OnSellRmbAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnBuyRmbAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnSellGameMoneyAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnBuyGameMoneyAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnTerminateAuction(ClientPeer *client, MsgExcuteSystemAuction *pSave, AuctionAccount &account);
		void OnAuctionTimeOut(MoneyExChangeData *data);
		//����DB����
		void OnDBReturnExcuteResult(CSExcuteAuctionListMsg *pSave);
		void OnAckSellRmbAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckBuyRmbAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckSellGameMoneyAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckBuyGameMoneyAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckTerminateAuction(CSExcuteAuctionListMsg *pSave);
		void OnAckAuctionTimeOut(CSExcuteAuctionListMsg *pSave);
		//ɾ����¼
		void removeAuctionItem(DWORD auctionid);
		//���������б�
		void findQueryItem(DWORD num, DWORD userid, DWORD userid2 = (DWORD)-1);
		void queryAuctionListByType(ClientPeer *client,  BYTE type, DWORD num = 0);
		void queryAuctionList(ClientPeer *client, MsgQuerySystemAuctionItemList *pQuery);
		void sendAuctionItemToUserByType(ClientPeer *client, BYTE selltype);
		void TellWorldMoneyAuction(BYTE sellType, DWORD num, DWORD price);
		//���ؼ��ۼ�¼
		void loadAuctionHistroy(CSLoadMysqlDataMsg *pLoadMsg);
		//ִ�в���������ʷ��¼
		void UpdateAuctionHistroy(CSExcuteAuctionListMsg *pSave);
		void AddOneHistroy(DWORD charactrid, MoneyAuctionHistroy data);
		//ѭ��
		void Loop();
		//�Ƿ��Ѿ��ڲ�����
		bool CheckHaveAuction(DWORD characterID);
		//��ʼ����
		void StartAuction(DWORD characterID);
		//��������
		void FinishAuction(DWORD characterID);
private:
		//�����¹����û��˺ŵ�����
		typedef std::map<DWORD, AuctionAccount> Account_Map;
		typedef std::map<DWORD, AuctionAccount>::iterator Account_Map_Iter;
		Account_Map account_map;
		bool is_finishloadcount;		//�Ƿ�����û��˺ŵļ���

		//��һ�¼��۽𶧵�������
		typedef std::map<DWORD, MoneyExChangeData*> Auction_List;
		typedef std::map<DWORD, MoneyExChangeData*>::iterator Auction_List_Iter;
		Auction_List auction_list;
		bool is_finishload_auctionlist;	//�Ƿ���ɼ��۽𶧵��Ӽ���

		//��������ʱ���������
		typedef std::vector<MoneyExChangeData*> Auction_SortList;
		typedef std::vector<MoneyExChangeData*>::iterator Auction_SortList_Iter;
		//������ʱ������������
		Auction_SortList sellrmb_temp;
		Auction_SortList sellmoney_temp;
		
		//��ʷ��¼
		typedef std::map<DWORD, MoneyAuctionHistroy> UserMoneyAuctionList;
		typedef std::map<DWORD, MoneyAuctionHistroy>::iterator UserMoneyAuctionList_Iter;
		typedef std::map<DWORD, UserMoneyAuctionList> MoneyAuctionHistroy_List;
		typedef std::map<DWORD, UserMoneyAuctionList>::iterator MoneyAuctionHistroy_List_Iter;
		MoneyAuctionHistroy_List moneyauction_histroylist;
		bool isfinish_loadhistroy;		//�Ƿ���ɽ�����ʷ��¼����

		//�û������б�
		typedef std::map<DWORD, DWORD> UserHandleMap;
		typedef std::map<DWORD, DWORD>::iterator UserHandleMap_Iter;
		UserHandleMap userHandleMap;

		//ѭ����ʱ����ɾ�������Ĳ���
		HRTimer *tenSec;
};

#endif