#include "NetEvent.h"
#include "GameServerManager.h"
#include "GameBattleDataManager.h"
#include "GameBattleMessage.h"
#include "..\CenterServer\Source\MySqlCommunication.h"
#include "Guild.h"
#include "GuildManager.h"
long NetEvent::OnProcessGameBattleMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( GS2CS_CAMPBATTLENEWDATAREQ, GS2CSCampBattleNewDataReq, _OnGS2CSCampBattleNewDataReq );
		MESSAGE_HANDLE( GS2CS_ADDCAMPBATTLEDATA, GS2CSAddCampBattleData, _OnGS2CSAddCampBattleData );
		MESSAGE_HANDLE( GS2CS_DELCAMPBATTLEDATA, GS2CSDelCampBattleData, _OnGS2CSDelCampBattleData );
		MESSAGE_HANDLE( GS2CS_DELPLAYERMONEY, GS2CSDelPlayerMoney, _OnGS2CSDelPlayerMoney );

		MESSAGE_HANDLE( GS2CS_CAMPBATTLEADDERROR, GS2CSCampBattleAddError, _OnGS2CSCampBattleAddError );
		
    MESSAGE_MAPPING_END
    return ER_Success;
}
void NetEvent::_OnGS2CSCampBattleNewDataReq( NetClient* pNetClient, GS2CSCampBattleNewDataReq* pMessage )
{
	//�����ݽ���ת��
	/*if(!theCenterCampBattleDataManager.IsCanAddGuildBattleData(pMessage->add.SrcGuildID,pMessage->add.BeginTime) || !theCenterCampBattleDataManager.IsCanAddGuildBattleData(pMessage->add.DestGuildID,pMessage->add.BeginTime))
		return;*/
	//Ŀ��᳤�Ƿ�����
	CenterGuild* pSrcGuild = theCenterGuildManager.GetGuild(pMessage->add.SrcGuildID);
	CenterGuild* pDestGuild = theCenterGuildManager.GetGuild(pMessage->add.DestGuildID);
	if(!pSrcGuild || !pDestGuild)
		return;
	GuildMember* pSrcMaster = pSrcGuild->GetMember(pSrcGuild->GetMasterID());
	GuildMember* pDestMaster = pDestGuild->GetMember(pDestGuild->GetMasterID());
	if(!pSrcMaster || !pDestMaster)
		return;
	if(!pSrcMaster->GetOnLine() || !pDestMaster->GetOnLine())
		return;
	CS2GSCampBattleNewDataReq msg;
	msg.add = pMessage->add;
	strcpy_s(msg.info,sizeof(msg.info)-1,pMessage->info);
	theGameServerManager.SendMessageToGameServers( &msg );
}
void NetEvent::_OnGS2CSAddCampBattleData( NetClient* pNetClient, GS2CSAddCampBattleData* pMessage )
{
	//GameServer ����µĹ���Լս��Ϣ
	if(pMessage->Result)
		theCenterCampBattleDataManager.AddGuildBattleData(pMessage->add);
	else
	{
		//�Է��ܾ�����Լս
		unsigned int ID = pMessage->add.ID;
		if(pMessage->add.ID == 0 && pMessage->add.IsWrite)
		{
			GameBattleDefine::GuildCampBattle* pInfo = theCenterCampBattleDataManager.GetWriteInfoByDestID(pMessage->add.DestGuildID);
			if(!pInfo)
				return;
			ID = pInfo->ID;
		}
		theCenterCampBattleDataManager.DedGuildBattleData(ID);
		MsgAddCampBattleDataAck msg;
		msg.Result = false;
		CenterGuild* pSrcGuild = theCenterGuildManager.GetGuild(pMessage->add.SrcGuildID);
		if(!pSrcGuild)
			return;
		theGameServerManager.SendMsgToSingle(&msg,pSrcGuild->GetMasterID());
	}
}
void NetEvent::_OnGS2CSDelCampBattleData( NetClient* pNetClient, GS2CSDelCampBattleData* pMessage )
{
	theCenterCampBattleDataManager.DedGuildBattleData(pMessage->ID);
}
void NetEvent::_OnGS2CSDelPlayerMoney( NetClient* pNetClient, GS2CSDelPlayerMoney* pMessage )
{
	CS2GSSDelPlayerMoney msg;
	msg.add= pMessage->add;
	theGameServerManager.SendMessageToGameServers( &msg );
}
void NetEvent::_OnGS2CSCampBattleAddError( NetClient* pNetClient, GS2CSCampBattleAddError* pMessage )
{
	//ֱ�ӷ���������ͻ���ȥ
	CS2GSCampBattleAddError msg;
	msg.ErrorID = pMessage->ErrorID;
	msg.PlayerID = pMessage->PlayerID;
	msg.Result = pMessage->Result;
	theGameServerManager.SendMessageToGameServers( &msg );
	if(pMessage->Result)
	{
		//��ǹ���Լս�Ѿ���ʽ׼������ ����Ҳ���͵�Ŀ�����Ļ����ȥ�� ����
		GameBattleDefine::GuildCampBattle pInfo = pMessage->add;
		pInfo.IsWrite = true;
		theCenterCampBattleDataManager.AddGuildBattleData(pInfo);
	}
}
