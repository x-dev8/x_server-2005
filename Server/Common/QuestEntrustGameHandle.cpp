#include "CenterServerNetEvent.h"
#include "QuestEntrust.h"
#include "QuestEntrustMessage.h"
#include "GameServer.h"
#include "ShareData.h"
#include "XmlStringLanguage.h"
#include "QuestManager.h"
#include "GamePlayer.h"
long CenterServerNetEvent::OnProcessQuestEntrustMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( CS2GS_LOADQUESTENTRUSTDATAACK, CS2GSLoadQuestEntrustDataAck, _OnCS2GSLoadQuestEntrustDataAck);
		MESSAGE_HANDLE( CS2GS_ADDQUESTENTRUSTACK, CS2GSAddQuestEntrustAck, _OnCS2GSAddQuestEntrustAck);
		MESSAGE_HANDLE( CS2GS_DELQUESTENTRUSTACK, CS2GSDelQuestEntrustAck, _OnCS2GSDelQuestEntrustAck);
		MESSAGE_HANDLE( CS2GS_UPDATEJOINQUESTENTRUSTACK, CS2GSUpdateJoinQuestEntrustAck, _OnCS2GSUpdateJoinQuestEntrustAck);
		MESSAGE_HANDLE( CS2GS_UPDATECANELQUESTENTRUSTACK, CS2GSUpdateCanelQuestEntrustAck, _OnCS2GSUpdateCanelQuestEntrustAck);	
		MESSAGE_HANDLE( CS2GS_QUESTENTRUSTSECCACK, CS2GSQuestEntrustSeccAck, _OnCS2GSQuestEntrustSeccAck);	
		MESSAGE_HANDLE( CS2GS_QUESTENTRUSTENDACK, CS2GSQuestEntrustEndAck, _OnCS2GSQuestEntrustEndAck);			
    MESSAGE_MAPPING_END
    return ER_Success;
}
void CenterServerNetEvent::_OnCS2GSLoadQuestEntrustDataAck( NetClient* pNetClient, CS2GSLoadQuestEntrustDataAck* pMessage )
{
	//��ȡȫ��������ί��
	for(int i =0;i<pMessage->Sum;++i)
	{
		theGameQuestEntrustManager.LoadQuestEntrust(pMessage->List[i]);
	}
	theGameQuestEntrustManager.SetLoadSuccess(pMessage->IsEnd);
}
void CenterServerNetEvent::_OnCS2GSAddQuestEntrustAck( NetClient* pNetClient, CS2GSAddQuestEntrustAck* pMessage )
{ 
	//���һ���µ�ί�� 
	//1.������� ���� ���͵�ȫ���Ŀͻ���ȥ
	theGameQuestEntrustManager.LoadQuestEntrust(pMessage->info);//����µ�ί��
	//2.��������ͻ���ȥ ���߿ͻ��� ���µ�ί�м��˽���
	/*MsgQuestEntrustNeedUpdate msg;
	GettheServer().SendMsgToWorld(&msg);*/
	//GettheServer().SendMsgToWorld(&msg);
	GamePlayer * pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->info.SrcPlayerID );
	MsgQuestEntrustNeedUpdate msg;
	if(pSrcPlayer)
		pSrcPlayer->SendMessageToClient(&msg);
}
void CenterServerNetEvent::_OnCS2GSDelQuestEntrustAck( NetClient* pNetClient, CS2GSDelQuestEntrustAck* pMessage )
{
	//ɾ��ָ����ί��
	unsigned int ID = pMessage->ID;
	QuestEntrustStates* pInfo = theGameQuestEntrustManager.GetQuestEntrust(ID);
	if(!pInfo)
		return;
	MsgQuestEntrustNeedUpdate msg;
	GamePlayer * pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->SrcPlayerID );
	if(pSrcPlayer)
	{
		pSrcPlayer->SetVar( pInfo->SrcQuestID,theQuestManager.SetQuestState( pSrcPlayer->GetVar( pInfo->SrcQuestID  ), QuestManager::eQuestGaining ));
		pSrcPlayer->SendMessageToClient(&msg);
	}
	GamePlayer* pDestPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->DestPlayerID );
	if(pDestPlayer)
	{
		pDestPlayer->Script_CancelQuest(pInfo->DestQuestID);
		//pDestPlayer->SetVar( pInfo->DestQuestID,theQuestManager.SetQuestState( pDestPlayer->GetVar( pInfo->DestQuestID  ), QuestManager::eQuestNotGain ));
		if(pMessage->IsTimeEnd)
		{
			long nResult = pDestPlayer->ApplyBufferStatus(theGameQuestEntrustManager.GetConfig().GetBuffID(),theGameQuestEntrustManager.GetConfig().GetBuffLevel(), pDestPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
			if ( nResult == GLR_Success  )
				pDestPlayer->OnBuffStatusChanged( true );
		}
		pDestPlayer->SendMessageToClient(&msg);

		MsgQuestEntrustShowInfo msgInfo;
		msgInfo.ID = eText_QuestEntrust_QuestDrop;
		pDestPlayer->SendMessageToClient(&msgInfo);
	}
	theGameQuestEntrustManager.EraseQuestEntrust(ID);

	/*MsgQuestEntrustNeedUpdate msg;
	GettheServer().SendMsgToWorld(&msg);*/
}
void CenterServerNetEvent::_OnCS2GSUpdateJoinQuestEntrustAck( NetClient* pNetClient, CS2GSUpdateJoinQuestEntrustAck* pMessage )
{
	//��ҳɹ���ȡ��һ��ί��
	theGameQuestEntrustManager.ChangeQuestEntrust(pMessage->info);
	GamePlayer* pDestPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->info.DestPlayerID );
	if(pDestPlayer)
	{
		//������� ���ýű�
		CScriptMgr::JoinQuestScript( pDestPlayer, pMessage->info.DestQuestID);
		//pDestPlayer->SetVar(  pMessage->info.DestQuestID,theQuestManager.SetQuestState( pDestPlayer->GetVar(  pMessage->info.DestQuestID  ), QuestManager::eQuestGaining ));
		
	}
	MsgQuestEntrustNeedUpdate msg;
	GamePlayer * pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->info.SrcPlayerID );
	if(pSrcPlayer)
		pSrcPlayer->SendMessageToClient(&msg);
	if(pDestPlayer)
		pDestPlayer->SendMessageToClient(&msg);

	//���͸ı䵽�ͻ���ȥ
	/*MsgQuestEntrustNeedUpdate msg;
	GettheServer().SendMsgToWorld(&msg);*/
}
void CenterServerNetEvent::_OnCS2GSUpdateCanelQuestEntrustAck( NetClient* pNetClient, CS2GSUpdateCanelQuestEntrustAck* pMessage )
{
	//��ҷ���һ��ί��
	QuestEntrustStates* pInfo = theGameQuestEntrustManager.GetQuestEntrust(pMessage->info.ID);
	if(!pInfo)
		return;
	GamePlayer* pDestPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->DestPlayerID );
	if(pDestPlayer)
	{
		if(pDestPlayer->IsQuestActive(pInfo->DestQuestID))
			pDestPlayer->Script_CancelQuest(pInfo->DestQuestID);
		//���һ���µ�BUFF
		long nResult = pDestPlayer->ApplyBufferStatus(theGameQuestEntrustManager.GetConfig().GetBuffID(),theGameQuestEntrustManager.GetConfig().GetBuffLevel(), pDestPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success  )
			pDestPlayer->OnBuffStatusChanged( true );
		//pDestPlayer->SetVar(  pMessage->info.DestQuestID,theQuestManager.SetQuestState( pDestPlayer->GetVar( pMessage->info.DestQuestID  ), QuestManager::eQuestNotGain ));
	}

	MsgQuestEntrustNeedUpdate msg;
	GamePlayer * pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->SrcPlayerID );
	if(pSrcPlayer)
		pSrcPlayer->SendMessageToClient(&msg);
	if(pDestPlayer)
		pDestPlayer->SendMessageToClient(&msg);

	theGameQuestEntrustManager.ChangeQuestEntrust(pMessage->info);
	//����������ͻ���ȥ
	/*MsgQuestEntrustNeedUpdate msg;
	GettheServer().SendMsgToWorld(&msg);*/
}
void CenterServerNetEvent::_OnCS2GSQuestEntrustSeccAck( NetClient* pNetClient, CS2GSQuestEntrustSeccAck* pMessage )
{
	//������һ��ί��
	QuestEntrustStates* pInfo = theGameQuestEntrustManager.GetQuestEntrust(pMessage->ID);
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID == 0)
		return;
	GamePlayer* pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->SrcPlayerID );
	GamePlayer * pDestPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->DestPlayerID );
	pInfo->IsSecc = true;
	if(pSrcPlayer)
	{
		//1.������ҵ�����״̬Ϊ���״̬
		pSrcPlayer->SetVar( pInfo->SrcQuestID,theQuestManager.SetQuestState( pSrcPlayer->GetVar( pInfo->SrcQuestID  ), QuestManager::eQuestEntrustDone ));
		//2.���������Centerȥ ��ֱ��ί�н���
		GS2CSQuestEntrustEndReq msg;
		msg.ID = pInfo->ID;
		GettheServer().SendMsgToCenterServer( &msg );
	}

	MsgQuestEntrustNeedUpdate msg;
	if(pSrcPlayer)
		pSrcPlayer->SendMessageToClient(&msg);
	if(pDestPlayer)
		pDestPlayer->SendMessageToClient(&msg);
}
void CenterServerNetEvent::_OnCS2GSQuestEntrustEndAck( NetClient* pNetClient, CS2GSQuestEntrustEndAck* pMessage )
{
	//����ָ��ί��
	QuestEntrustStates* pInfo = theGameQuestEntrustManager.GetQuestEntrust(pMessage->ID);
	if(!pInfo)
		return;
	//����������ͻ���ȥ
	MsgQuestEntrustNeedUpdate msg;
	GamePlayer * pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->SrcPlayerID );
	GamePlayer * pDestPlayer = theRunTimeData.GetGamePlayerByDBID( pInfo->DestPlayerID );
	if(pSrcPlayer)
		pSrcPlayer->SendMessageToClient(&msg);
	if(pDestPlayer)
		pDestPlayer->SendMessageToClient(&msg);
	theGameQuestEntrustManager.EraseQuestEntrust(pMessage->ID);
}	