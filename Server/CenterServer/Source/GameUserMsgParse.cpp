/********************************************************************
Filename: 	GameUserMsgParse.cpp
MaintenanceMan Mail: lufeipeng@163.com
brief:��ҵ���Ϣ������һ��
*********************************************************************/

#include "ClientPeer.h"
#include "DBMessageDefine.h"
#include "GameServerManager.h"

long ClientPeer::UserMsgParse(Msg *pMessage,unsigned long msgType)
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE_USER( MSG_HANDLESYSTEAUCTION_ACCOUNTMONEY, MsgHandleSystemAuctionAccountMoney, _OnHandleAuctionMoney);	
		MESSAGE_HANDLE_USER( MSG_EXCUTESYSTEM_AUCTION, MsgExcuteSystemAuction, _OnExcuteAuction);
		MESSAGE_HANDLE_USER( MSG_REQUESTSYSTEMAUCTION, MsgRequestSystemAuction, _OnRequestSystemAuctionList);
		MESSAGE_HANDLE_USER( MSG_QUERY_SYSTEMAUCTION_ITEMLIST, MsgQuerySystemAuctionItemList, _OnQueryAuctionList);
		default:
		{   
		}
		break;
	MESSAGE_MAPPING_END
	return ER_Success;
}
void ClientPeer::_OnHandleAuctionMoney(  MsgHandleSystemAuctionAccountMoney *pMessage)
{
	AuctionManager::Instance().OnHandleAuctionMoney(pMessage, this);
}
void ClientPeer::_OnExcuteAuction(MsgExcuteSystemAuction *pMessage)
{
	AuctionManager::Instance().OnExcuteAuction(pMessage, this);
}
void ClientPeer::_OnRequestSystemAuctionList(MsgRequestSystemAuction *pMessage)
{
	//����ļ����˺Ž�Ǯ
	AuctionManager::Instance().sendAuctionAccountMoneyToUser(this);
	//��ǰ�����б�
	AuctionManager::Instance().queryAuctionListByType(this, enumAuctionQueryType_All);
}
void ClientPeer::_OnQueryAuctionList(MsgQuerySystemAuctionItemList *pMessage)
{
	AuctionManager::Instance().queryAuctionList(this, pMessage);
}