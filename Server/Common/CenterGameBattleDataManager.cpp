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
		//���д��� 
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
				//����ɾ������ ������ʾ��ҶԷ���Ҿܾ�����
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
	//������������ݿ�ȥ ����ȫ��������
	CS2DBLoadCampBattleData msg;
	theMysqlCommunication.PushReqMessage( &msg, 0 );
}
template<>
void CenterCampBattleDataManager::SendDataToServer(unsigned int nServerID )
{
	//�����ݷ��͵�GameServerȥ
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
	//���յ���ӵ�����
	/*if(!IsCanAddGuildBattleData(pData.SrcGuildID,pData.BeginTime) || !IsCanAddGuildBattleData(pData.DestGuildID,pData.BeginTime))
		return;*/
	//����������ݵ�ID
	if(IsExitesGuildCampBattleData(pData.ID))
	{
		GameBattleDefine::GuildCampBattle* pInfo = GetWriteInfoByDestID(pData.DestGuildID);
		if(pInfo)
		{
			pInfo->IsWrite = false;//�޸�Ϊ���ǵȴ���Ϣ
			pData.IsWrite = false;
			WriteTimeInfoMap.erase(pData.ID);
			CS2GSAddCampBattleData msg;
			msg.add = pData;
			theGameServerManager.SendMessageToGameServers( &msg );
			//�������ݿ�����޸�
			CS2DBAddCampBattleData msgDB;
			msgDB.IsUpadte = true;
			msgDB.add = pData;
			theMysqlCommunication.PushReqMessage( &msgDB, 0 );
		}
		else
		{
			//����ҵ�Լս���ݲ����ڵĻ� ������Ҫ���д���
			//1.�˻�˫����ȫ���Ľ�Ǯ
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
					// ������
					xReq.mail.owners[EM_FromIndex].charDbId = 0;
					sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
					// �ռ���	
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
					// ������
					xReq.mail.owners[EM_FromIndex].charDbId = 0;
					sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
					// �ռ���	
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
		//������������ݿ�ȥ
		CS2DBAddCampBattleData msgDB;
		msgDB.IsUpadte = false;
		msgDB.add = pData;
		theMysqlCommunication.PushReqMessage( &msgDB, 0 );
		//���͵����е�GameServerȥ
		CS2GSAddCampBattleData msg;
		msg.add = pData;
		theGameServerManager.SendMessageToGameServers( &msg );
		//���úü�¼ʱ��
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
	//ɾ������
	EraseGuildBattleData(ID);
	//������������ݿ�ȥ
	CS2DBDelCampBattleData msgDB;
	msgDB.ID = ID;
	theMysqlCommunication.PushReqMessage( &msgDB, 0 );
	//���͵�GameServer
	CS2GSDelCampBattleData msg;
	msg.ID = ID;
	theGameServerManager.SendMessageToGameServers( &msg );
}
template<>
bool CenterCampBattleDataManager::IsCanAddGuildBattleData(unsigned int GuildID,__int64 BeginTime,unsigned int Type)
{
	return true;
}