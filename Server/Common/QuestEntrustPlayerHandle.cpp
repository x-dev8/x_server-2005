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
	//ָ���ͻ��˼������е�����ί������ 
	theGameQuestEntrustManager.SendQuestEntrustData(GetDBCharacterID());
}
void GamePlayer::OnMsgAddQuestEntrustReq( Msg* pMsg )
{
	//��������һ������ί�� ����Ҫ���й���
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
	//1.�ж������Ƿ����ί��
	if(theGameQuestEntrustManager.GetConfig().GetChangeQuestID(pAdd->info.SrcQuestID) == 0)
		return;
	//2.�ж�������ϵĻ����Ƿ��㹻
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
	//3.�ж�����Ƿ���ָ����Ʒ
	__int64 ItemID = pAdd->info.ItemInfo.GetItemGuid();
	if(ItemID !=0)
	{
		 SCharItem* pItem = GetBagItemByGuid(ItemID);
		 if(!pItem || pItem->IsBounded() || pItem->IsLock() || pItem->IsSoulStamp())
			 return;
		 //������ڵĻ�
		 pAdd->info.ItemInfo = *pItem;
	}
	//4.�ж������Ƿ����
	SQuest* pQuest = theQuestManager.GetQuest( pAdd->info.SrcQuestID );
	if(!pQuest)
		return;
	if(theQuestManager.GetQuestState( GetVar( pAdd->info.SrcQuestID  )) != QuestManager::eQuestGaining)
		return;
	//5.���úýṹ������
	pAdd->info.DestQuestID = theGameQuestEntrustManager.GetConfig().GetChangeQuestID(pAdd->info.SrcQuestID);
	pAdd->info.SrcPlayerID = GetDBCharacterID();
	//6.������ҵ�����״̬
	SetVar( pAdd->info.SrcQuestID,theQuestManager.SetQuestState( GetVar( pAdd->info.SrcQuestID  ), QuestManager::eQuestFrozen ));//��������Ϊ����״̬ �����Է��� �����Խ���
	//7.�۳���ҵĽ�Ǯ
	if(pAdd->info.EntrustRewardType == QuestEntrust_YinBi)
	{
		OperateMoney(EOT_Sub,pAdd->info.EntrustRewardSum,true,__FUNCTION__, __LINE__,ePlayerMoneySourceType_QuestEntrust);
	}
	else if(pAdd->info.EntrustRewardType == QuestEntrust_YuanBao)
	{
		OperateJinDing(EOT_Sub,pAdd->info.EntrustRewardSum,__FUNCTION__, __LINE__,ePlayerMoneySourceType_QuestEntrust);
	}
	//8.ɾ����Ʒ
	if(pAdd->info.ItemInfo.GetItemGuid() !=0 && !RemoveBagItemByGuid(pAdd->info.ItemInfo.GetItemGuid(),pAdd->info.ItemInfo.GetItemCount()))
		return;
	//9.�������CenterServerȥ
	theGameQuestEntrustManager.AddQuestEntrust(pAdd->info);
}
void GamePlayer::OnMsgDelQuestEntrustReq( Msg* pMsg )
{
	//�Ƴ�ָ����ί��
	MsgDelQuestEntrustReq * pDel = (MsgDelQuestEntrustReq*)pMsg;
	if(!pDel)
		return;
	unsigned int ID = pDel->ID;
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	//1.�ж�ָ��ί���Ƿ����
	if(!pInfo)
		return;
	//2.�ж�ָ��ί���Ƿ����Լ����͵�
	if(pInfo->SrcPlayerID != GetDBCharacterID())
		return;
	//3.��������
	theGameQuestEntrustManager.DelQuestEntrust(ID);//��������
}
void GamePlayer::OnMsgUpdateJoinQuestEntrustReq( Msg* pMsg )
{
	//��ȡί��
	MsgUpdateJoinQuestEntrustReq * pJoin = (MsgUpdateJoinQuestEntrustReq*)pMsg;
	if(!pJoin )
		return;
	unsigned int ID = pJoin->ID;
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	//1.�ж�ָ��ί���Ƿ����
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != 0)
		return;
	//�ж���������BUFF
	if(GetBuffManager()->IsHaveStatus(theGameQuestEntrustManager.GetConfig().GetBuffID()))
		return;
	unsigned int MoneySum = theGameQuestEntrustManager.GetConfig().GetQuestMoneySum(pInfo->SrcQuestID);
	if(GetMoney() < MoneySum)
		return;
	//2.�ж��Լ��Ƿ��Ѿ��н�ȡί���� �еĻ� �޷��ظ���ȡί��
	if(theGameQuestEntrustManager.IsExitesJoinQuestEntrust(GetDBCharacterID()) != 0)
		return;
	//3.�ж�ָ�������Ƿ���Խ�ȡ �������������
	unsigned int QuestID = pInfo->DestQuestID;
	if(!IfCanJoinQuest(QuestID))//�����Խ�ȡ����
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
	//5.�ж���ҽ�ȡ����ί�е�Ѻ������ ������Ļ� �۳���ҵ�Ѻ��
	OperateMoney(EOT_Sub,MoneySum,true,__FUNCTION__, __LINE__,ePlayerMoneySourceType_QuestEntrust);//�۳�Ѻ��
	//4.��֯�ṹ
	QuestEntrustStates states = *pInfo;
	states.DestPlayerID = GetDBCharacterID();
	time_t nowtime;
	time(&nowtime);
	states.ReceiveLogTime = nowtime;
	strcpy_s(states.DestPlayerName,MaxPlayerNameLength,GetCharInfo().baseinfo.aptotic.szCharacterName);
	//5.��������
	theGameQuestEntrustManager.JoinQuestEntrust(states);
}
void GamePlayer::OnMsgUpdateCanelQuestEntrustReq( Msg* pMsg )
{
	MsgUpdateCanelQuestEntrustReq * pCanel = (MsgUpdateCanelQuestEntrustReq*)pMsg;
	if(!pCanel)
		return;
	unsigned int ID = pCanel->ID;
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	//1.�ж�ָ��ί���Ƿ����
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != GetDBCharacterID())
		return;
	//2.��������
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
	//����ύ�����һ��ί��
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(pSec->ID);
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != GetDBCharacterID())
		return;
	//ֱ�������������
	CScriptMgr::DoneQuestScript(this,pInfo->DestQuestID);
	//1.��ý��� �����ʼ�
	/*GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// ������
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// �ռ���	
	xReq.mail.owners[EM_ToIndex].charDbId = pInfo->SrcPlayerID;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pInfo->ScrPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_QuestEntrust_SeccContent ) );
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_QuestEntrust_SeccTitle ) );
	xReq.mail.accessory.type = SMail::EAT_Item;//2������,1����Ʒ
	memcpy( &xReq.mail.accessory.content,  &pInfo->ItemInfo, sizeof(SCharItem) ); 
	//���ý�Ǯ ����Ԫ��
	xReq.mail.money = pInfo->EntrustRewardSum;
	GettheServer().SendMsgToCenterServer( &xReq );
	//2.�������
	//CScriptMgr::DoneQuestScript(this,pInfo->DestQuestID);
	//Script_CancelQuest(pInfo->DestQuestID);
	//SetVar(  pInfo->DestQuestID,theQuestManager.SetQuestState( GetVar( pInfo->DestQuestID  ), QuestManager::eQuestNotGain ));
	//3.���������Centerȥ
	GS2CSQuestEntrustSeccReq msg;
	msg.ID = pSec->ID;
	GettheServer().SendMsgToCenterServer( &msg );*/
}