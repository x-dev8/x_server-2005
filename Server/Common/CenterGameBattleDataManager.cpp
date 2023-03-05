#include "GameBattleDataManager.h"
#include "GameBattleMessage.h"
#include "..\CenterServer\Source\GameServerManager.h"
#include "..\CenterServer\Source\MySqlCommunication.h"
#include "Guild.h"
#include "GuildManager.h"
#include "XmlStringLanguage.h"
#include "..\CenterServer\Source\MailManagerMain.h"
template<>
void CenterCampBattleDataManager::RunUpdate( unsigned int nCurrentTime)
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }
	LoadAddDataByDataBase();
	if(!WriteTimeInfoMap.empty())
	{
		//进行处理 
		time_t nowtime;
		time(&nowtime);
		std::map<unsigned int,__int64>::iterator Iter = WriteTimeInfoMap.begin();
		for(;Iter != WriteTimeInfoMap.end();)
		{
			unsigned int ID = Iter->first;
			__int64 TimeLog = Iter->second;
			if(GuildCampBattleDataMap.count(ID) != 1)
			{
				++Iter;
				continue;
			}
			if(nowtime - TimeLog >=GameBattleDefine::WaiteAddMsgBattleTime)
			{
				//进行删除操作 并且提示玩家对方玩家拒绝操作
				MsgAddCampBattleDataAck msg;
				msg.Result = false;
				CenterGuild* pSrcGuild = theCenterGuildManager.GetGuild(GuildCampBattleDataMap[ID].SrcGuildID);
				if(!pSrcGuild)
				{
					++Iter;
					continue;
				}
				theGameServerManager.SendMsgToSingle(&msg,pSrcGuild->GetMasterID());
				DedGuildBattleData(ID);
				Iter = WriteTimeInfoMap.erase(Iter);
			}
			else
				++Iter;
		}
	}
}
template<>
void CenterCampBattleDataManager::LoadAddDataByDataBase()
{
	if(IsLoadSecc)
		return;
	//发送命令道数据库去 加载全部的数据
	CS2DBLoadCampBattleData msg;
	theMysqlCommunication.PushReqMessage( &msg, 0 );
}
template<>
void CenterCampBattleDataManager::SendDataToServer(unsigned int nServerID )
{
	//将数据发送到GameServer去
	if(!IsLoadSecc)
		return;
	CS2GSLoadCampBattleData msg;
	msg.ClearAllData();
	if(GuildCampBattleDataMap.empty())
	{
		msg.Sum = 0;
		msg.IsEnd = true;
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
	else
	{
		std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
		int Index = 0;
		for(;Iter != GuildCampBattleDataMap.end(); ++Iter,++Index)
		{
			if(msg.PushInfo(Iter->second,Index == GuildCampBattleDataMap.size()-1))
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
				msg.ClearAllData();
			}
		}
	}
}
template<>
void CenterCampBattleDataManager::AddGuildBattleData(GameBattleDefine::GuildCampBattle& pData)
{
	//接收到添加的命令
	/*if(!IsCanAddGuildBattleData(pData.SrcGuildID,pData.BeginTime) || !IsCanAddGuildBattleData(pData.DestGuildID,pData.BeginTime))
		return;*/
	//设置添加数据的ID
	if(IsExitesGuildCampBattleData(pData.ID))
	{
		GameBattleDefine::GuildCampBattle* pInfo = GetWriteInfoByDestID(pData.DestGuildID);
		if(pInfo)
		{
			pInfo->IsWrite = false;//修改为不是等待消息
			pData.IsWrite = false;
			WriteTimeInfoMap.erase(pData.ID);
			CS2GSAddCampBattleData msg;
			msg.add = pData;
			theGameServerManager.SendMessageToGameServers( &msg );
			//发送数据库进行修改
			CS2DBAddCampBattleData msgDB;
			msgDB.IsUpadte = true;
			msgDB.add = pData;
			theMysqlCommunication.PushReqMessage( &msgDB, 0 );
		}
		else
		{
			//当玩家的约战数据不存在的话 我们需要进行处理
			//1.退回双方的全部的金钱
			{
				//Dest
				CenterGuild* pDestGuild = theCenterGuildManager.GetGuild(pData.DestGuildID);
				if(pDestGuild)
				{
					pDestGuild->OperateGuildMission(GuildDefine::OperateAdd,pData.GuildMissionSum);
					pDestGuild->OperateGuildMoney(GuildDefine::OperateAdd,pData.GuildMoneySum);
					
					GS2CSSendMailReq xReq;
					xReq.charDbId = RelationDefine::InitID;
					xReq.mail.type  = SMail::EMT_System;
					xReq.mail.state = SMail::EMS_NotOpen;
					xReq.mail.sendTime = TimeEx::GetNowTime();        
					// 发信人
					xReq.mail.owners[EM_FromIndex].charDbId = 0;
					sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
					// 收件人	
					xReq.mail.owners[EM_ToIndex].charDbId = pDestGuild->GetMasterID();
					HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pDestGuild->GetMember(pDestGuild->GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
					sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_GuildGeneral_Secc_Content ) );
					sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_GuildGeneral_Secc_Title ) );
					xReq.mail.money = pData.MoneySum;
					theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
				}
			}
			{
				//Src
				CenterGuild* pSrcGuild = theCenterGuildManager.GetGuild(pData.SrcGuildID);
				if(pSrcGuild)
				{
					pSrcGuild->OperateGuildMission(GuildDefine::OperateAdd,pData.GuildMissionSum);
					pSrcGuild->OperateGuildMoney(GuildDefine::OperateAdd,pData.GuildMoneySum);
					
					GS2CSSendMailReq xReq;
					xReq.charDbId = RelationDefine::InitID;
					xReq.mail.type  = SMail::EMT_System;
					xReq.mail.state = SMail::EMS_NotOpen;
					xReq.mail.sendTime = TimeEx::GetNowTime();        
					// 发信人
					xReq.mail.owners[EM_FromIndex].charDbId = 0;
					sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
					// 收件人	
					xReq.mail.owners[EM_ToIndex].charDbId = pSrcGuild->GetMasterID();
					HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pSrcGuild->GetMember(pSrcGuild->GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
					sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_GuildGeneral_Secc_Content ) );
					sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_GuildGeneral_Secc_Title ) );
					xReq.mail.money = pData.MoneySum;
					theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
				}
			}
		}
	}
	else
	{
		pData.ID = GetNewID();
		InsertGuildBattleData(pData);
		//发送命令道数据库去
		CS2DBAddCampBattleData msgDB;
		msgDB.IsUpadte = false;
		msgDB.add = pData;
		theMysqlCommunication.PushReqMessage( &msgDB, 0 );
		//发送到所有的GameServer去
		CS2GSAddCampBattleData msg;
		msg.add = pData;
		theGameServerManager.SendMessageToGameServers( &msg );
		//设置好记录时间
		time_t nowtime;
		time(&nowtime);
		WriteTimeInfoMap.insert(std::map<unsigned int,__int64>::value_type(pData.ID,nowtime));
	}
}
template<>
void CenterCampBattleDataManager::DedGuildBattleData(unsigned int ID)
{
	if(!IsExitesGuildCampBattleData(ID))
		return;
	//删除数据
	EraseGuildBattleData(ID);
	//发送命令道数据库去
	CS2DBDelCampBattleData msgDB;
	msgDB.ID = ID;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );
	//发送到GameServer
	CS2GSDelCampBattleData msg;
	msg.ID = ID;
	theGameServerManager.SendMessageToGameServers( &msg );
}
template<>
bool CenterCampBattleDataManager::IsCanAddGuildBattleData(unsigned int GuildID,__int64 BeginTime,unsigned int Type)
{
	return true;
}