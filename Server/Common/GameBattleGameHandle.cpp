#include "CenterServerNetEvent.h"
#include "GameBattleDataManager.h"
#include "GameBattleMessage.h"
#include "GameServer.h"
#include "ShareData.h"
#include "XmlStringLanguage.h"
#include "GamePlayer.h"
#include "GameBattleControl.h"
#include "GameGuildGeneralBattleManager.h"
long CenterServerNetEvent::OnProcessGameBattleMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( CS2GS_LOADCAMPBATTLEDATA, CS2GSLoadCampBattleData, _OnCS2GSLoadCampBattleData);
		MESSAGE_HANDLE( CS2GS_ADDCAMPBATTLEDATA, CS2GSAddCampBattleData, _OnCS2GSAddCampBattleData);
		MESSAGE_HANDLE( CS2GS_DELCAMPBATTLEDATA, CS2GSDelCampBattleData, _OnCS2GSDelCampBattleData);
		MESSAGE_HANDLE( CS2GS_CAMPBATTLENEWDATAREQ, CS2GSCampBattleNewDataReq, _OnCS2GSCampBattleNewDataReq);

		MESSAGE_HANDLE( CS2GS_DELPLAYERMONEY, CS2GSSDelPlayerMoney, _OnCS2GSSDelPlayerMoney);
		MESSAGE_HANDLE( CS2GS_CAMPBATTLEADDERROR, CS2GSCampBattleAddError, _OnCS2GSCampBattleAddError);
		
		
    MESSAGE_MAPPING_END
    return ER_Success;
}
void CenterServerNetEvent::_OnCS2GSCampBattleNewDataReq( NetClient* pNetClient, CS2GSCampBattleNewDataReq* pMessage )
{
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(pMessage->add.SrcGuildID);
	GameGuild* pGuild = theGameGuildManager.GetGuild(pMessage->add.DestGuildID);
	if(!pGuild || !pSrcGuild)
		return;
	GuildMember* pMaster =  pGuild->GetMember(pGuild->GetMasterID());
	if(!pMaster || !pMaster->GetOnLine())
		return;
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( pGuild->GetMasterID() );
	if(!pPlayer)
		return;
	//ֻ�жϽ�Ǯ�Ƿ��㹻 �������ж���֮ǰ�Ѿ�����
	if(pPlayer->GetMoney() < pMessage->add.MoneySum)
	{	
		GuildMember* pSrcMaster =  pSrcGuild->GetMember(pSrcGuild->GetMasterID());
		if(!pSrcMaster || !pSrcMaster->GetOnLine())
			return;
		GamePlayer* pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pSrcGuild->GetMasterID() );
		if(pSrcPlayer)
		{
			MsgGameBattleErrorAck msg;
			msg.Info = eText_GuildGeneral_TargetMoneyError;
			pSrcPlayer->SendMessageToClient( &msg );
			return;
		}
		else
		{
			//ͨ��Center����ת����������ڵ�GameServerȥ �����������µ�Լսʧ��
			GS2CSCampBattleAddError msg;
			msg.ErrorID = eText_GuildGeneral_TargetMoneyError;
			msg.PlayerID=pSrcGuild->GetMasterID();
			msg.Result = false;
			GettheServer().SendMsgToCenterServer( &msg );
			return;
		}
	}
	else
	{
		//���ʹ���CD�������Դ��Ҵ�
		/*GuildMember* pSrcMaster =  pSrcGuild->GetMember(pSrcGuild->GetMasterID());
		if(!pSrcMaster || !pSrcMaster->GetOnLine())
			return;*/
		//GamePlayer* pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pSrcGuild->GetMasterID() );
		//if(pSrcPlayer)
		//{
		//	time_t nowtime;
		//	time(&nowtime);
		//	nowtime +=theGameBattleControl.GetMapMaxTimeByType(GameBattleDefine::GameBattle_Type_GuildGeneral) * 60;
		//	pSrcPlayer->gCharInfoServer.otherdata.nBeginGameGeneralBattleTime = nowtime;
		//	//����������ͻ���ȥ 
		//	MsgUpdateAddCampBattleCD msg;
		//	msg.Time = nowtime;
		//	pSrcPlayer->SendMessageToClient( &msg );
		//}
		//else
		//{
		//	//���͵�Center����ת��
		//	GS2CSCampBattleAddError msg;
		//	msg.ErrorID = 0;
		//	msg.PlayerID=pSrcGuild->GetMasterID();
		//	msg.Result = true;
		//	GettheServer().SendMsgToCenterServer( &msg );
		//}
		//���͵�Center����ת��
		GS2CSCampBattleAddError msg;
		msg.ErrorID = 0;
		msg.PlayerID=pSrcGuild->GetMasterID();
		msg.add = pMessage->add;
		msg.Result = true;
		GettheServer().SendMsgToCenterServer( &msg );
	}
	


	MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
	char WorldInfo[256];
	sprintf_s(WorldInfo,255,theXmlString.GetString(eText_GuildGeneral_AddBattleWorldInfo),pSrcGuild->GetName(),pGuild->GetName());
	xChat.SetString(WorldInfo);
	GettheServer().SendMsgToWorld(&xChat,true);

	MsgCampBattleNewDataAck msg;
	msg.add = pMessage->add;
	strcpy_s(msg.info,sizeof(msg.info)-1,pMessage->info);
	strcpy_s(msg.srcGuildName,sizeof(msg.srcGuildName)-1,pSrcGuild->GetName());
	pPlayer->SendMessageToClient( &msg );
}
void  CenterServerNetEvent::_OnCS2GSLoadCampBattleData( NetClient* pNetClient, CS2GSLoadCampBattleData* pMessage )
{
	//�ͻ��˼���
	for(int i =0;i<pMessage->Sum;++i)
	{
		theGameCampBattleDataManager.InsertGuildBattleData(pMessage->info[i]);
	}
	if(pMessage->IsEnd)
		theGameCampBattleDataManager.SetLoadSecc();
	theGameBattleControl.RegisterGuildGeneralBattleManger();//��������Լս������
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	//���Ѿ����ص��ǲ����ݷ��뵽ս����������ȥ
	for(int i =0;i<pMessage->Sum;++i)
	{
		GameBattleDefine::GuildCampBattle& pData= pMessage->info[i];
		if(pData.IsWrite)
			continue;
		pManager->AddGameGuildGeneralBattleOnceInfo(pData.ID,pData.MapID,pData.SrcGuildID,pData.DestGuildID,pData.BeginTime,pData.MoneySum,pData.GuildMoneySum,pData.GuildMissionSum);
	}
}
void  CenterServerNetEvent::_OnCS2GSAddCampBattleData( NetClient* pNetClient, CS2GSAddCampBattleData* pMessage )
{
	theGameCampBattleDataManager.AddGuildBattleData(pMessage->add);
}
void  CenterServerNetEvent::_OnCS2GSDelCampBattleData( NetClient* pNetClient, CS2GSDelCampBattleData* pMessage )
{
	theGameCampBattleDataManager.DedGuildBattleData(pMessage->ID);
}
void CenterServerNetEvent::_OnCS2GSSDelPlayerMoney( NetClient* pNetClient, CS2GSSDelPlayerMoney* pMessage )
{
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(pMessage->add.SrcGuildID);
	if(!pSrcGuild)
		return;
	GamePlayer * pSrcPlayer = theRunTimeData.GetGamePlayerByDBID( pSrcGuild->GetMasterID() );
	if(!pSrcPlayer)
		return;
	GameGuild* pDestGuild = theGameGuildManager.GetGuild(pMessage->add.DestGuildID);
	if(!pDestGuild)
		return;
	//�ж�����Ƿ����㹻�Ľ�Ǯ������
	bool IsOk = true;
	if(pSrcPlayer->GetMoney() < pMessage->add.MoneySum)
		IsOk = false;
	//3.�Ƿ����㹻��ʹ����
	if(pSrcGuild->GetMission() < pMessage->add.GuildMissionSum * 20)
		IsOk = false;
	//4.�Ƿ����㹻�ľ����ʽ�
	if(pSrcGuild->GetMoney() < pMessage->add.GuildMoneySum * 20)
		IsOk = false;
	if(!theGameCampBattleDataManager.IsExitesNeedWriteData(pMessage->add.DestGuildID))
		IsOk = false;//��Ϣ��ʱ��
	GameBattleDefine::GuildCampBattle* pInfo = theGameCampBattleDataManager.GetWriteInfoByDestID(pMessage->add.DestGuildID);
	if(!pInfo || pInfo->IsChange(pMessage->add))
		IsOk = false;
	if(!IsOk)
	{
		//����ԭ��ҵĽ�Ǯ
		pDestGuild->OperateGuildMission(GuildDefine::OperateAdd,pMessage->add.GuildMissionSum);
		pDestGuild->OperateGuildMoney(GuildDefine::OperateAdd,pMessage->add.GuildMoneySum);
		
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
		xReq.mail.money = pMessage->add.MoneySum;
		GettheServer().SendMsgToCenterServer( &xReq );

		//ɾ�����ݿ��Լս��Ϣ
		GS2CSAddCampBattleData msg;
		msg.add= *pInfo;
		msg.Result = false;
		GettheServer().SendMsgToCenterServer( &msg );
		return;
	}
	pSrcGuild->OperateGuildMission(GuildDefine::OperateSub,pMessage->add.GuildMissionSum);
	pSrcGuild->OperateGuildMoney(GuildDefine::OperateSub,pMessage->add.GuildMoneySum);
	pSrcPlayer->OperateMoney(EOT_Sub,pMessage->add.MoneySum, true, __FUNCTION__, __LINE__,0);
	//��ǰ�ɹ� ���ǿ��Կ���ս����
	pMessage->add.MapID = theGameBattleControl.GetMapIDByType(GameBattleDefine::GameBattle_Type_GuildGeneral);
	//8.������ӵĺ����������������
	GS2CSAddCampBattleData msg;
	msg.add= *pInfo;
	msg.Result = true;
	GettheServer().SendMsgToCenterServer( &msg );

	time_t tt = pMessage->add.BeginTime;
	struct tm sysNowTime(*localtime(&tt));
	char TimeLog[64];
	sprintf_s(TimeLog,63,"%d-%d-%d %d:%d:%d",sysNowTime.tm_year+1900,sysNowTime.tm_mon+1,sysNowTime.tm_mday,sysNowTime.tm_hour,sysNowTime.tm_min,sysNowTime.tm_sec);
	MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
	char WorldInfo[256];
	sprintf_s(WorldInfo,255,theXmlString.GetString(eText_GuildGeneral_AddBattle),pSrcGuild->GetName(),pDestGuild->GetName(),TimeLog);
	xChat.SetString(WorldInfo);
	GettheServer().SendMsgToWorld(&xChat,true);
}
void CenterServerNetEvent::_OnCS2GSCampBattleAddError( NetClient* pNetClient, CS2GSCampBattleAddError* pMessage )
{
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->PlayerID );
	if(!pPlayer)
		return;
	if(pMessage->Result)
	{
		//����CD
		time_t nowtime;
		time(&nowtime);
		nowtime +=theGameBattleControl.GetMapMaxTimeByType(GameBattleDefine::GameBattle_Type_GuildGeneral) * 60;
		pPlayer->gCharInfoServer.otherdata.nBeginGameGeneralBattleTime = nowtime;
		//����������ͻ���ȥ 
		MsgUpdateAddCampBattleCD msg;
		msg.Time = nowtime;
		pPlayer->SendMessageToClient( &msg );
	}
	else
	{
		MsgGameBattleErrorAck msg;
		msg.Info = pMessage->ErrorID;
		pPlayer->SendMessageToClient( &msg );
	}
}