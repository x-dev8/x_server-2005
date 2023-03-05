#include "QuestEntrust.h"
#include "GlobalFunction.h"
#include "QuestEntrustMessage.h"
#include "..\CenterServer\Source\GameServerManager.h"
#include "..\CenterServer\Source\MySqlCommunication.h"
#include "XmlStringLanguage.h"
#include "..\CenterServer\Source\MailManagerMain.h"
template<>
void CenterQuestEntrustManager::RunUpdate( unsigned int nCurrentTime)
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

	//ÿ������12�� ��ս����ί��
	if ( RecordTime::CheckRecordTime( nRecordTime ) )
    {
        // ���ڲ�ͬ��, 
        RecordTime::SaveRecordTime( nRecordTime );
		
		//������е�ί��
		if(!QuestEntrustMap.empty())
		{
			std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
			for(;Iter != QuestEntrustMap.end();)
			{
				if(!Iter->second.IsSecc)
				{
					//������ǰί�� �����˻ؽ�Ǯ 
					CS2GSDelQuestEntrustAck msg2;
					msg2.ID = Iter->first;
					msg2.IsTimeEnd = true;
					theGameServerManager.SendMessageToGameServers( &msg2 );

					GS2CSSendMailReq xReq;
					xReq.charDbId = RelationDefine::InitID;
					xReq.mail.type  = SMail::EMT_System;
					xReq.mail.state = SMail::EMS_NotOpen;
					xReq.mail.sendTime = TimeEx::GetNowTime();        
					// ������
					xReq.mail.owners[EM_FromIndex].charDbId = 0;
					sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
					// �ռ���	
					xReq.mail.owners[EM_ToIndex].charDbId = Iter->second.SrcPlayerID;
					HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,Iter->second.ScrPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

					sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_QuestEntrust_TimeEndContent ) );
					sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_QuestEntrust_TimeEndTitile ) );
					if(Iter->second.ItemInfo.itembaseinfo.nOnlyInt == 0)
					{
						xReq.mail.accessory.type = SMail::EAT_None;
					}
					else
					{
						xReq.mail.accessory.type = SMail::EAT_Item;//2������,1����ƷEAT_None
						memcpy( &xReq.mail.accessory.content,  &Iter->second.ItemInfo, sizeof(SCharItem) ); 
					}
					xReq.mail.money = Iter->second.EntrustRewardSum;
					theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );

					//������������ݿ�ȥ �Ƴ�����
					/*CS2DBQuestEntrustDeleteReq msg;
					msg.ID = Iter->first;
					theMysqlCommunication.PushReqMessage( &msg, 0 );*/
					m_DBDel.insert(std::set<unsigned int>::value_type(Iter->first));
					if(!IsSaveTimerStart())
						StartSaveTimer(HQ_TimeGetTime());

					Iter = QuestEntrustMap.erase(Iter);
				}
				else
					++Iter;
			}
		}
    }
    // �����������
     ProcessLoadQuestEntrustData( nCurrentTime );

	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
	for(;Iter != QuestEntrustMap.end();++Iter)
	{
		//�жϵ�ǰί���Ƿ�Ӧ�û�ԭ
		time_t logtime =Iter->second.ReceiveLogTime;
		time_t nowtime;
		time(&nowtime);
		double SpanTime = difftime(nowtime,logtime);
		if(Iter->second.DestPlayerID !=0 && logtime !=0 && SpanTime >= (theCenterQuestEntrustManager.GetConfig().GetLastTime()/1000))
		{
			Iter->second.DestPlayerID = 0;
			strcpy_s(Iter->second.DestPlayerName,MaxPlayerNameLength,"");
			Iter->second.ReceiveLogTime = 0;
			//����ί�� ���ҷ��͵�GameServerȥ
			CS2GSUpdateCanelQuestEntrustAck msg2;
			msg2.info = Iter->second;
			theGameServerManager.SendMessageToGameServers( &msg2 );

			//CS2DBQuestEntrustDataSaveReq msg;
			//msg.info = Iter->second;
			//theMysqlCommunication.PushReqMessage( &msg, 0 );//�����޸�ί�е�����

			m_DBUpdate.insert(std::set<unsigned int>::value_type(Iter->first));
			if(!IsSaveTimerStart())
				StartSaveTimer(HQ_TimeGetTime());
		}
	}
	if ( m_xSaveTimer.DoneTimer() )
		SaveToDatabase();
}
template<>
void CenterQuestEntrustManager::ProcessLoadQuestEntrustData( unsigned int nCurrentTime )
{
	if(GetLoadSuccess() || m_bBeginLoad)
		return;
	//���������DB ȥ��������
	CS2DBRequestQuestEntrustDataReq msg;
	theMysqlCommunication.PushReqMessage( &msg, 0 );
	m_bBeginLoad = true;
}
template<>
void CenterQuestEntrustManager::SendQuestEntrustData( unsigned int nServerID )
{
	//��ȫ��������ί�����ݷ��͵�GameServerȥ
	if ( !GetLoadSuccess() )
    { 
		return; 
	}
	//���������ݷ���
	CS2GSLoadQuestEntrustDataAck msg;
	msg.ClearAllInfo();
	if(!QuestEntrustMap.empty())
	{
		std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
		int Index = 0;
		for(;Iter != QuestEntrustMap.end();++Iter,++Index)
		{
			if(msg.PushInfo(Iter->second,(Index == QuestEntrustMap.size()-1)))
			{
				if ( nServerID == -1)
				{
					theGameServerManager.SendMessageToGameServers( &msg );
				}
				else
				{
					GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nServerID );
					if ( pGameServer != NULL )
					{
						pGameServer->Send( &msg );
					}
				}
				msg.ClearAllInfo();
			}
		}
	}
	else
	{
		msg.Sum = 0;
		msg.IsEnd = true;
		//msg.SetLength();
		if ( nServerID == -1)
		{
			theGameServerManager.SendMessageToGameServers( &msg );
		}
		else
		{
			GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nServerID );
			if ( pGameServer != NULL )
			{
				pGameServer->Send( &msg );
			}
		}
	}
}
template<>
void CenterQuestEntrustManager::AddQuestEntrust(QuestEntrustStates& info)
{
	//���һ���µ�ί��
	unsigned int ID = GetNewQuestEntrustID();
	info.ID = ID;
	LoadQuestEntrust(info);
	//���������GameServer�������� ���µ�ί�������
	CS2GSAddQuestEntrustAck msg;
	msg.info = info;
	theGameServerManager.SendMessageToGameServers( &msg );//���͸����з�����

	/*CS2DBAddQuestEntrustDataAck msgDB;
	msgDB.info = info;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );*/

	m_DBAdd.insert(std::set<unsigned int>::value_type(info.ID));
	if(!IsSaveTimerStart())
		StartSaveTimer(HQ_TimeGetTime());
}
template<>
void CenterQuestEntrustManager::DelQuestEntrust(unsigned int ID)
{
	//�Ƴ�ָ��ID��ί��
	if(QuestEntrustMap.count(ID) == 0)
		return;
	if( QuestEntrustMap[ID].DestPlayerID == 0)
	{
		//������ҵĽ�Ǯ����Ʒ
		//����Ǯ����Ʒ �����ʼ������ ������� ί��ʱ�䵽�� ��Ʒ�˻�
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;
		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();        
		// ������
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// �ռ���	
		xReq.mail.owners[EM_ToIndex].charDbId = QuestEntrustMap[ID].SrcPlayerID;
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,QuestEntrustMap[ID].ScrPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

		sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_QuestEntrust_TimeEndContent ) );
		sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_QuestEntrust_TimeEndTitile ) );
		if(QuestEntrustMap[ID].ItemInfo.itembaseinfo.nOnlyInt == 0)
		{
			xReq.mail.accessory.type = SMail::EAT_None;
		}
		else
		{
			xReq.mail.accessory.type = SMail::EAT_Item;//2������,1����Ʒ
			memcpy( &xReq.mail.accessory.content,  &QuestEntrustMap[ID].ItemInfo, sizeof(SCharItem) ); 
		}
		xReq.mail.money = QuestEntrustMap[ID].EntrustRewardSum;
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	}
	else
	{
		unsigned int MoneySum = theCenterQuestEntrustManager.GetConfig().GetQuestMoneySum(QuestEntrustMap[ID].SrcQuestID);
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;
		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();        
		// ������
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// �ռ���	
		xReq.mail.owners[EM_ToIndex].charDbId = QuestEntrustMap[ID].DestPlayerID;
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,QuestEntrustMap[ID].ScrPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

		sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_QuestEntrust_DelContent ) );
		sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_QuestEntrust_DelTitle ) );
		if(QuestEntrustMap[ID].ItemInfo.itembaseinfo.nOnlyInt == 0)
		{
			xReq.mail.accessory.type = SMail::EAT_None;
		}
		else
		{
			xReq.mail.accessory.type = SMail::EAT_Item;//2������,1����Ʒ
			memcpy( &xReq.mail.accessory.content,  &QuestEntrustMap[ID].ItemInfo, sizeof(SCharItem) ); 
		}
		xReq.mail.money = QuestEntrustMap[ID].EntrustRewardSum + MoneySum;
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	}
	//������ڵĻ�
	EraseQuestEntrust(ID);
	//���͵����ݿ�ȥ
	/*CS2DBQuestEntrustDeleteReq msg;
	msg.ID =ID;
	theMysqlCommunication.PushReqMessage( &msg, 0 );*/
	//���͸�����GameServerȥ
	CS2GSDelQuestEntrustAck msg2;
	msg2.IsTimeEnd = false;
	msg2.ID = ID;
	theGameServerManager.SendMessageToGameServers( &msg2 );

	m_DBDel.insert(std::set<unsigned int>::value_type(ID));
	if(!IsSaveTimerStart())
		StartSaveTimer(HQ_TimeGetTime());
}
template<>
void CenterQuestEntrustManager::JoinQuestEntrust(QuestEntrustStates& info)
{
	//��ȡί��
	if(QuestEntrustMap.count(info.ID) == 0)
		return;
	if(QuestEntrustMap[info.ID].DestPlayerID != 0)
		return;
	ChangeQuestEntrust(info);
	//�������ݿ�
	/*CS2DBQuestEntrustDataSaveReq msgDB;
	msgDB.info = info;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );*/
	//��������GameServerȥ
	CS2GSUpdateJoinQuestEntrustAck msg;
	msg.info = info;
	theGameServerManager.SendMessageToGameServers( &msg );

	m_DBUpdate.insert(std::set<unsigned int>::value_type(info.ID));
	if(!IsSaveTimerStart())
		StartSaveTimer(HQ_TimeGetTime());
}
template<>
void CenterQuestEntrustManager::CanelQuestEntrust(QuestEntrustStates& info)
{
	//����ί��
	if(QuestEntrustMap.count(info.ID) == 0)
		return;
	if(QuestEntrustMap[info.ID].DestPlayerID == 0)
		return;
	ChangeQuestEntrust(info);
	//�������ݿ�
	/*CS2DBQuestEntrustDataSaveReq msgDB;
	msgDB.info = info;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );*/
	//��������GameServerȥ
	CS2GSUpdateCanelQuestEntrustAck msg;
	msg.info = info;
	theGameServerManager.SendMessageToGameServers( &msg );

	m_DBUpdate.insert(std::set<unsigned int>::value_type(info.ID));
	if(!IsSaveTimerStart())
		StartSaveTimer(HQ_TimeGetTime());
}
template<>
void CenterQuestEntrustManager::SaveToDatabase()
{
	//����Ҫ��������ݱ��浽���ݿ�ȥ
	if(!m_DBDel.empty())
	{
		std::set<unsigned int>::iterator Iter = m_DBDel.begin();
		CS2DBQuestEntrustDeleteReq msgDel;
		msgDel.ClearAllInfo();
		int Index = 0;
		for(;Iter != m_DBDel.end(); ++Iter,++Index)
		{
			if(msgDel.PushInfo(*Iter,(Index == m_DBDel.size()-1)))
			{
				theMysqlCommunication.PushReqMessage( &msgDel, 0 );
				msgDel.ClearAllInfo();
			}
		}
		m_DBDel.clear();
	}
	if(!m_DBAdd.empty())
	{
		std::set<unsigned int>::iterator Iter = m_DBAdd.begin();
		CS2DBAddQuestEntrustDataAck msgAdd;
		msgAdd.ClearAllInfo();
		int Index = 0;
		for(;Iter != m_DBAdd.end(); ++Iter,++Index)
		{
			QuestEntrustStates* pInfo = GetQuestEntrust(*Iter);
			if(!pInfo)
				continue;
			if(msgAdd.PushInfo(*pInfo,(Index == m_DBAdd.size()-1)))
			{
				theMysqlCommunication.PushReqMessage( &msgAdd, 0 );
				msgAdd.ClearAllInfo();
			}
		}
		m_DBAdd.clear();
	}
	if(!m_DBUpdate.empty())
	{
		std::set<unsigned int>::iterator Iter = m_DBUpdate.begin();
		CS2DBQuestEntrustDataSaveReq msgUpdate;
		msgUpdate.ClearAllInfo();
		int Index = 0;
		for(;Iter != m_DBUpdate.end(); ++Iter,++Index)
		{
			QuestEntrustStates* pInfo = GetQuestEntrust(*Iter);
			if(!pInfo)
				continue;
			if(msgUpdate.PushInfo(*pInfo,(Index == m_DBUpdate.size()-1)))
			{
				theMysqlCommunication.PushReqMessage( &msgUpdate, 0 );
				msgUpdate.ClearAllInfo();
			}
		}
		m_DBUpdate.clear();
	}
}
//1.���������ļ� OK 
//2.����ȫ�����ݿ����ݲ��Ҵ洢���ڴ�ȥ OK
//3.��ʼUpdate���� OK
//4.GameServer���ӽ��� ���Ƿ���ȫ�������ݵ�GameServerȥ OK
//5.����GameServer���ί�е�����   OK
//6.����GameServerȡ��ί�е�����  OK
//7.������ҽ�ȡί�е�����  OK
//8.������ҷ���ί�е����� OK
//9.�������ί�й��ڵ���� OK 
//10.����ί�й��ڵ���� OK
//11.����������ί�е�����
//12.������ҽ���ί�е�����