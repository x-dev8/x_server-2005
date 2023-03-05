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

	//每天晚上12点 清空今天的委托
	if ( RecordTime::CheckRecordTime( nRecordTime ) )
    {
        // 日期不同了, 
        RecordTime::SaveRecordTime( nRecordTime );
		
		//清空所有的委托
		if(!QuestEntrustMap.empty())
		{
			std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
			for(;Iter != QuestEntrustMap.end();)
			{
				if(!Iter->second.IsSecc)
				{
					//结束当前委托 并且退回金钱 
					CS2GSDelQuestEntrustAck msg2;
					msg2.ID = Iter->first;
					msg2.IsTimeEnd = true;
					theGameServerManager.SendMessageToGameServers( &msg2 );

					GS2CSSendMailReq xReq;
					xReq.charDbId = RelationDefine::InitID;
					xReq.mail.type  = SMail::EMT_System;
					xReq.mail.state = SMail::EMS_NotOpen;
					xReq.mail.sendTime = TimeEx::GetNowTime();        
					// 发信人
					xReq.mail.owners[EM_FromIndex].charDbId = 0;
					sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
					// 收件人	
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
						xReq.mail.accessory.type = SMail::EAT_Item;//2是坐骑,1是物品EAT_None
						memcpy( &xReq.mail.accessory.content,  &Iter->second.ItemInfo, sizeof(SCharItem) ); 
					}
					xReq.mail.money = Iter->second.EntrustRewardSum;
					theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );

					//发送命令道数据库去 移除数据
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
    // 处理加载数据
     ProcessLoadQuestEntrustData( nCurrentTime );

	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
	for(;Iter != QuestEntrustMap.end();++Iter)
	{
		//判断当前委托是否应该还原
		time_t logtime =Iter->second.ReceiveLogTime;
		time_t nowtime;
		time(&nowtime);
		double SpanTime = difftime(nowtime,logtime);
		if(Iter->second.DestPlayerID !=0 && logtime !=0 && SpanTime >= (theCenterQuestEntrustManager.GetConfig().GetLastTime()/1000))
		{
			Iter->second.DestPlayerID = 0;
			strcpy_s(Iter->second.DestPlayerName,MaxPlayerNameLength,"");
			Iter->second.ReceiveLogTime = 0;
			//重置委托 并且发送到GameServer去
			CS2GSUpdateCanelQuestEntrustAck msg2;
			msg2.info = Iter->second;
			theGameServerManager.SendMessageToGameServers( &msg2 );

			//CS2DBQuestEntrustDataSaveReq msg;
			//msg.info = Iter->second;
			//theMysqlCommunication.PushReqMessage( &msg, 0 );//发送修改委托的命令

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
	//发送命令道DB 去加载数据
	CS2DBRequestQuestEntrustDataReq msg;
	theMysqlCommunication.PushReqMessage( &msg, 0 );
	m_bBeginLoad = true;
}
template<>
void CenterQuestEntrustManager::SendQuestEntrustData( unsigned int nServerID )
{
	//将全部的任务委托数据发送到GameServer去
	if ( !GetLoadSuccess() )
    { 
		return; 
	}
	//将所有数据发送
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
	//添加一个新的委托
	unsigned int ID = GetNewQuestEntrustID();
	info.ID = ID;
	LoadQuestEntrust(info);
	//发送命令道GameServer告诉他们 有新的委托添加了
	CS2GSAddQuestEntrustAck msg;
	msg.info = info;
	theGameServerManager.SendMessageToGameServers( &msg );//发送给所有服务器

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
	//移除指定ID的委托
	if(QuestEntrustMap.count(ID) == 0)
		return;
	if( QuestEntrustMap[ID].DestPlayerID == 0)
	{
		//返还玩家的金钱和物品
		//将金钱和物品 发送邮件给玩家 告诉玩家 委托时间到期 物品退回
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;
		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();        
		// 发信人
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// 收件人	
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
			xReq.mail.accessory.type = SMail::EAT_Item;//2是坐骑,1是物品
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
		// 发信人
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// 收件人	
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
			xReq.mail.accessory.type = SMail::EAT_Item;//2是坐骑,1是物品
			memcpy( &xReq.mail.accessory.content,  &QuestEntrustMap[ID].ItemInfo, sizeof(SCharItem) ); 
		}
		xReq.mail.money = QuestEntrustMap[ID].EntrustRewardSum + MoneySum;
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	}
	//如果存在的话
	EraseQuestEntrust(ID);
	//发送到数据库去
	/*CS2DBQuestEntrustDeleteReq msg;
	msg.ID =ID;
	theMysqlCommunication.PushReqMessage( &msg, 0 );*/
	//发送给所有GameServer去
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
	//截取委托
	if(QuestEntrustMap.count(info.ID) == 0)
		return;
	if(QuestEntrustMap[info.ID].DestPlayerID != 0)
		return;
	ChangeQuestEntrust(info);
	//发送数据库
	/*CS2DBQuestEntrustDataSaveReq msgDB;
	msgDB.info = info;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );*/
	//发送所有GameServer去
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
	//放弃委托
	if(QuestEntrustMap.count(info.ID) == 0)
		return;
	if(QuestEntrustMap[info.ID].DestPlayerID == 0)
		return;
	ChangeQuestEntrust(info);
	//发送数据库
	/*CS2DBQuestEntrustDataSaveReq msgDB;
	msgDB.info = info;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );*/
	//发送所有GameServer去
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
	//将需要保存的数据保存到数据库去
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
//1.加载配置文件 OK 
//2.加载全部数据库数据并且存储到内存去 OK
//3.开始Update函数 OK
//4.GameServer连接进来 我们发送全部的数据到GameServer去 OK
//5.接收GameServer添加委托的请求   OK
//6.接收GameServer取消委托的请求  OK
//7.接收玩家接取委托的请求  OK
//8.接收玩家放弃委托的请求 OK
//9.处理玩家委托过期的情况 OK 
//10.处理委托过期的情况 OK
//11.处理玩家完成委托的请求
//12.处理玩家结束委托的请求