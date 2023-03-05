#include "GamePlayer.h"
#include "QuestEntrust.h"
#include "QuestEntrustMessage.h"
#include "QuestManager.h"
#include "RapidXml/MeRapidXml.h"
#include "XmlStringLanguage.h"
bool GamePlayer::ProcessQuestEntrustMsg( Msg* pMsg )
{
	DWORD dwType = pMsg->GetType();
    GAMESERVER_MESSAGE_MAPPING_BEGIN
		GAMESERVER_MESSAGE_HANDLE(MSG_LOADQUESTENTRUSTDATAREQ, OnMsgLoadQuestEntrustDataReq);
		GAMESERVER_MESSAGE_HANDLE(MSG_DELQUESTENTRUSTREQ, OnMsgDelQuestEntrustReq);
		GAMESERVER_MESSAGE_HANDLE(MSG_UPDATEJOINQUESTENTRUSTREQ, OnMsgUpdateJoinQuestEntrustReq);
		GAMESERVER_MESSAGE_HANDLE(MSG_UPDATECANELQUESTENTRUSTREQ, OnMsgUpdateCanelQuestEntrustReq);
		GAMESERVER_MESSAGE_HANDLE(MSG_QUESTENTRUSTSECCREQ, OnMsgQuestEntrustSeccReq);
		GAMESERVER_MESSAGE_HANDLE(MSG_ADDQUESTENTRUSTREQ, OnMsgAddQuestEntrustReq);
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}
void GamePlayer::OnMsgLoadQuestEntrustDataReq( Msg* pMsg )
{
	if(!theGameQuestEntrustManager.GetLoadSuccess())
		return;
	//指定客户端加载所有的任务委托数据 
	theGameQuestEntrustManager.SendQuestEntrustData(GetDBCharacterID());
}
void GamePlayer::OnMsgAddQuestEntrustReq( Msg* pMsg )
{
	//玩家想添加一个任务委托 我们要进行过滤
	MsgAddQuestEntrustReq * pAdd = (MsgAddQuestEntrustReq *)pMsg;
	if(!pAdd)
		return;
	if(IsInProtectLockTime())
	{
		MsgSendMailAck msgToClient;
		msgToClient.result = MsgSendMailAck::ER_InProtectLockTime;
		GettheServer().SendMsgToSingle( &msgToClient, this );
		return;
	}
	//1.判断任务是否可以委托
	if(theGameQuestEntrustManager.GetConfig().GetChangeQuestID(pAdd->info.SrcQuestID) == 0)
		return;
	//2.判断玩家身上的货币是否足够
	if(pAdd->info.EntrustRewardType == QuestEntrust_YinBi)
	{
		if(GetMoney() < pAdd->info.EntrustRewardSum)
			return;
	}
	else if(pAdd->info.EntrustRewardType == QuestEntrust_YuanBao)
	{
		if(GetJinDing() < pAdd->info.EntrustRewardSum)
			return;
	}
	//3.判断玩家是否有指定物品
	__int64 ItemID = pAdd->info.ItemInfo.GetItemGuid();
	if(ItemID !=0)
	{
		 SCharItem* pItem = GetBagItemByGuid(ItemID);
		 if(!pItem || pItem->IsBounded() || pItem->IsLock() || pItem->IsSoulStamp())
			 return;
		 //如果存在的话
		 pAdd->info.ItemInfo = *pItem;
	}
	//4.判断任务是否存在
	SQuest* pQuest = theQuestManager.GetQuest( pAdd->info.SrcQuestID );
	if(!pQuest)
		return;
	if(theQuestManager.GetQuestState( GetVar( pAdd->info.SrcQuestID  )) != QuestManager::eQuestGaining)
		return;
	//5.设置好结构的数据
	pAdd->info.DestQuestID = theGameQuestEntrustManager.GetConfig().GetChangeQuestID(pAdd->info.SrcQuestID);
	pAdd->info.SrcPlayerID = GetDBCharacterID();
	//6.冻结玩家的任务状态
	SetVar( pAdd->info.SrcQuestID,theQuestManager.SetQuestState( GetVar( pAdd->info.SrcQuestID  ), QuestManager::eQuestFrozen ));//设置任务为冻结状态 不可以放弃 不可以进行
	//7.扣除玩家的金钱
	if(pAdd->info.EntrustRewardType == QuestEntrust_YinBi)
	{
		OperateMoney(EOT_Sub,pAdd->info.EntrustRewardSum,true,__FUNCTION__, __LINE__,ePlayerMoneySourceType_QuestEntrust);
	}
	else if(pAdd->info.EntrustRewardType == QuestEntrust_YuanBao)
	{
		OperateJinDing(EOT_Sub,pAdd->info.EntrustRewardSum,__FUNCTION__, __LINE__,ePlayerMoneySourceType_QuestEntrust);
	}
	//8.删除物品
	if(pAdd->info.ItemInfo.GetItemGuid() !=0 && !RemoveBagItemByGuid(pAdd->info.ItemInfo.GetItemGuid(),pAdd->info.ItemInfo.GetItemCount()))
		return;
	//9.发送命令到CenterServer去
	theGameQuestEntrustManager.AddQuestEntrust(pAdd->info);
}
void GamePlayer::OnMsgDelQuestEntrustReq( Msg* pMsg )
{
	//移除指定的委托
	MsgDelQuestEntrustReq * pDel = (MsgDelQuestEntrustReq*)pMsg;
	if(!pDel)
		return;
	unsigned int ID = pDel->ID;
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	//1.判断指定委托是否存在
	if(!pInfo)
		return;
	//2.判断指定委托是否是自己发送的
	if(pInfo->SrcPlayerID != GetDBCharacterID())
		return;
	//3.发送命令
	theGameQuestEntrustManager.DelQuestEntrust(ID);//发送命令
}
void GamePlayer::OnMsgUpdateJoinQuestEntrustReq( Msg* pMsg )
{
	//接取委托
	MsgUpdateJoinQuestEntrustReq * pJoin = (MsgUpdateJoinQuestEntrustReq*)pMsg;
	if(!pJoin )
		return;
	unsigned int ID = pJoin->ID;
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	//1.判断指定委托是否存在
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != 0)
		return;
	//判断有无特殊BUFF
	if(GetBuffManager()->IsHaveStatus(theGameQuestEntrustManager.GetConfig().GetBuffID()))
		return;
	unsigned int MoneySum = theGameQuestEntrustManager.GetConfig().GetQuestMoneySum(pInfo->SrcQuestID);
	if(GetMoney() < MoneySum)
		return;
	//2.判断自己是否已经有接取委托了 有的话 无法重复接取委托
	if(theGameQuestEntrustManager.IsExitesJoinQuestEntrust(GetDBCharacterID()) != 0)
		return;
	//3.判断指定任务是否可以接取 满足任务的条件
	unsigned int QuestID = pInfo->DestQuestID;
	if(!IfCanJoinQuest(QuestID))//不可以接取任务
	{
		MsgQuestEntrustInfoAck msg;
		msg.ID = eText_QuestEntrust_JoinQuest;
		SendMessageToClient( &msg );
		return;
	}
	if(!CanGetNewQuest())
	{
		MsgQuestEntrustInfoAck msg;
		msg.ID = eText_QuestEntrust_JoinQuest;
		SendMessageToClient( &msg );
		return;
	}
	//5.判断玩家接取任务委托的押金问题 如果够的话 扣除玩家的押金
	OperateMoney(EOT_Sub,MoneySum,true,__FUNCTION__, __LINE__,ePlayerMoneySourceType_QuestEntrust);//扣除押金
	//4.组织结构
	QuestEntrustStates states = *pInfo;
	states.DestPlayerID = GetDBCharacterID();
	time_t nowtime;
	time(&nowtime);
	states.ReceiveLogTime = nowtime;
	strcpy_s(states.DestPlayerName,MaxPlayerNameLength,GetCharInfo().baseinfo.aptotic.szCharacterName);
	//5.发送命令
	theGameQuestEntrustManager.JoinQuestEntrust(states);
}
void GamePlayer::OnMsgUpdateCanelQuestEntrustReq( Msg* pMsg )
{
	MsgUpdateCanelQuestEntrustReq * pCanel = (MsgUpdateCanelQuestEntrustReq*)pMsg;
	if(!pCanel)
		return;
	unsigned int ID = pCanel->ID;
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	//1.判断指定委托是否存在
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != GetDBCharacterID())
		return;
	//2.发送命令
	QuestEntrustStates states = *pInfo;
	states.DestPlayerID = 0;
	states.ReceiveLogTime = 0;
	strcpy_s(states.DestPlayerName,MaxPlayerNameLength,"");
	theGameQuestEntrustManager.CanelQuestEntrust(states);
}
void GamePlayer::OnMsgQuestEntrustSeccReq( Msg* pMsg )
{
	MsgQuestEntrustSeccReq * pSec = (MsgQuestEntrustSeccReq*)pMsg;
	if(!pSec)
		return;
	//玩家提交完成了一个委托
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(pSec->ID);
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != GetDBCharacterID())
		return;
	//直接设置完成任务
	CScriptMgr::DoneQuestScript(this,pInfo->DestQuestID);
	//1.获得奖励 发送邮件
	/*GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// 发信人
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// 收件人	
	xReq.mail.owners[EM_ToIndex].charDbId = pInfo->SrcPlayerID;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pInfo->ScrPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_QuestEntrust_SeccContent ) );
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_QuestEntrust_SeccTitle ) );
	xReq.mail.accessory.type = SMail::EAT_Item;//2是坐骑,1是物品
	memcpy( &xReq.mail.accessory.content,  &pInfo->ItemInfo, sizeof(SCharItem) ); 
	//设置金钱 或者元宝
	xReq.mail.money = pInfo->EntrustRewardSum;
	GettheServer().SendMsgToCenterServer( &xReq );
	//2.完成任务
	//CScriptMgr::DoneQuestScript(this,pInfo->DestQuestID);
	//Script_CancelQuest(pInfo->DestQuestID);
	//SetVar(  pInfo->DestQuestID,theQuestManager.SetQuestState( GetVar( pInfo->DestQuestID  ), QuestManager::eQuestNotGain ));
	//3.发送命令道Center去
	GS2CSQuestEntrustSeccReq msg;
	msg.ID = pSec->ID;
	GettheServer().SendMsgToCenterServer( &msg );*/
}