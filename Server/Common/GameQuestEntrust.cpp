#include "QuestEntrust.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "QuestEntrustMessage.h"
template<>
void GameQuestEntrustManager::RunUpdate( unsigned int nCurrentTime )
{
	
}
template<>
void GameQuestEntrustManager::SendQuestEntrustData( unsigned int nServerID )
{
	//���Ͳ������󵽿ͻ���ȥ �������Խ�ȥ��ί�� ���Լ���ȥ��ί�� ��δ��ɵ�ί��
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID(nServerID);
	if(pPlayer)
	{
		MsgLoadQuestEntrustDataAck msg;
		msg.ClearAllInfo();
		if(!QuestEntrustMap.empty())
		{
			std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
			int Index = 0;
			for(;Iter != QuestEntrustMap.end();++Iter,++Index)
			{
				//�ж��Ƿ�Ϊһ�����ҵ� ����
				/*if(Iter->second.SrcPlayerID != pPlayer->GetDBCharacterID() && Iter->second.DestPlayerID != pPlayer->GetDBCharacterID() && !pPlayer->IfCanJoinQuest(Iter->second.DestQuestID))
					continue;	*/
				if(msg.PushInfo(Iter->second,(Index == QuestEntrustMap.size()-1)))
				{
					pPlayer->SendMessageToClient(&msg);
					msg.ClearAllInfo();
				}
			}
		}
		else
		{
			msg.Sum = 0;
			msg.IsEnd = true;
			msg.SetLength();
			pPlayer->SendMessageToClient(&msg);
		}
	}
}
template<>
void GameQuestEntrustManager::AddQuestEntrust(QuestEntrustStates& info)
{
	//�ͻ��˷�������ӵ�����
	//1.�ж�ָ�������Ƿ����ִ��ί��
	//2.���úýṹ��һЩ��������
	//3.����һЩ������� ����ҵĽ�Ǯ
	GS2CSAddQuestEntrustReq msg;
	msg.info = info;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameQuestEntrustManager::DelQuestEntrust(unsigned int ID)
{
	//1.�ж��Ƿ��Ǳ����ֱ�ӷ�����
	if(!GetQuestEntrust(ID))
		return;
	GS2CSDelQuestEntrustReq msg;
	msg.ID = ID;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameQuestEntrustManager::JoinQuestEntrust(QuestEntrustStates& info)
{
	//1.�ж��Ƿ��Ѿ���ȡ��ί��
	//2.�Ƿ���������ȡί�� ������Ľ�ȡ����
	//3.
	GS2CSUpdateJoinQuestEntrustReq msg;
	msg.info = info;
	GettheServer().SendMsgToCenterServer( &msg );
}
template<>
void GameQuestEntrustManager::CanelQuestEntrust(QuestEntrustStates& info)
{
	GS2CSUpdateCanelQuestEntrustReq msg;
	msg.info = info;
	GettheServer().SendMsgToCenterServer( &msg );
}
//1.���������ļ� OK
//2.����Center������ȫ������ OK
//3.���տͻ��˵����ί�е�����  OK 
//4.���տͻ��˵�ɾ��ί�е����� OK
//5.���տͻ��˵Ľ�ȡί�е����� OK
//6.���տͻ��˵ķ���ί�е����� OK
//Handle �ﴦ��
//7.������������������ί�е�����
//8.���������������ɾ��ί�е�����
//9.����������������޸�ί�е�����
//10.���տͻ�������ȫ��ί�е����� OK