#include "GamePlayer.h"
#include "BaseGameBattle.h"
#include "GameBattleControl.h"
#include "GameBattleMessage.h"
#include "BaseGameBattleConfig.h"
#include "GameBattleDataManager.h"
#include "ShareData.h"
#include "XmlStringLanguage.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameBattleControl.h"
#include "GameGuildGeneralBattle.h"
bool GamePlayer::ProcessGameBattleMsg( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
		GAMESERVER_MESSAGE_HANDLE( MSG_CAMPBATTLENEWDATAREQ, OnMsgCampBattleNewDataReq);
		GAMESERVER_MESSAGE_HANDLE( MSG_LOADCAMPBATTLEDATAREQ, OnMsgLoadCampBattleDataReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_ADDCAMPBATTLEDATAREQ, OnMsgAddCampBattleDataReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_DELCAMPBATTLEDATAREQ, OnMsgDelCampBattleDataReq );

		GAMESERVER_MESSAGE_HANDLE( MSG_ENTERGAMEBATTLEREQ, OnMsgEnterGameBattleReq );
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}
void GamePlayer::OnMsgCampBattleNewDataReq( Msg* pMsg )
{
	MsgCampBattleNewDataReq * pReq = (MsgCampBattleNewDataReq*)pMsg;
	//��ͼ����µĹ���Լս
	if(theGameCampBattleDataManager.IsExitesNeedWriteData(pReq->add.DestGuildID))//�Է������еȴ�δ�������Ϣ �������µ���Ϣ
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_Target_WriteMsg;
		SendMessageToClient( &msg );
		return;
	}
	//1.�ж�Լս��ʱ���Ƿ���� CampBattleMaxLastTime  �ڳ���ʱ�����Ƿ����µ�Լս
	if(!theGameCampBattleDataManager.IsCanAddGuildBattleData(m_pGuild->GetID(),pReq->add.BeginTime,GameBattleDefine::GameBattle_Type_GuildGeneral) || 
		!theGameCampBattleDataManager.IsCanAddGuildBattleData(pReq->add.DestGuildID,pReq->add.BeginTime,GameBattleDefine::GameBattle_Type_GuildGeneral))
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_TimeError;
		SendMessageToClient( &msg );
		return;
	}
	time_t EndTime = gCharInfoServer.otherdata.nBeginGameGeneralBattleTime;
	time_t nowtime;
	time(&nowtime);
	if(nowtime < EndTime)
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GameGeneralBattle_AddTimeError;
		SendMessageToClient( &msg );
		return;
	}
	//2.�ж��Ƿ����㹻�Ľ�Ǯ
	if(this->GetMoney() < pReq->add.MoneySum)
		return;
	//3.�Ƿ����㹻��ʹ����
	if(m_pGuild->GetMission() < pReq->add.GuildMissionSum * 20)
		return;
	//4.�Ƿ����㹻�ľ����ʽ�
	if(m_pGuild->GetMoney() < pReq->add.GuildMoneySum * 20)
		return;
	//5.�ж�Ŀ�깫���Ƿ����
	GameGuild* pDestGuild = theGameGuildManager.GetGuild(pReq->add.DestGuildID);
	if(!pDestGuild)
		return;
	//6.�жϹ���Ļ᳤�Ƿ����߻�����������GameServer
	GuildMember* pMaster =  pDestGuild->GetMember(pDestGuild->GetMasterID());
	if(!pMaster || !pMaster->GetOnLine())
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_MasterNotOnLine;
		SendMessageToClient( &msg );
		return;
	}
	if(pReq->add.BeginTime < nowtime + theGameBattleControl.GetMapDiffTimeByType(GameBattleDefine::GameBattle_Type_GuildGeneral)*60)
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_TimeError;
		SendMessageToClient( &msg );
		return;
	}
	if(pDestGuild->GetMission() < pReq->add.GuildMissionSum* 20)
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_TargetMissionError;
		SendMessageToClient( &msg );
		return;
	}
	if(pDestGuild->GetMoney() < pReq->add.GuildMoneySum* 20)
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_TargetGuildMoneyError;
		SendMessageToClient( &msg );
		return;
	}
	//7.�۳�Լս��ȫ����Ǯ
	/*m_pGuild->OperateGuildMission(GuildDefine::OperateSub,pReq->add.GuildMissionSum);
	m_pGuild->OperateGuildMoney(GuildDefine::OperateSub,pReq->add.GuildMoneySum);
	OperateMoney(EOT_Sub,pReq->add.MoneySum, true, __FUNCTION__, __LINE__,0);*/
	//8.�������������ȥ ���߷�������ս
	//8.����������������
	//GamePlayer * pDestPlayer = theRunTimeData.GetGamePlayerByDBID( pDestGuild->GetMasterID() );
	//if(pDestPlayer)
	//{
	//	if(pDestPlayer->GetMoney() < pReq->add.MoneySum)
	//	{
	//		MsgGameBattleErrorAck msg;
	//		msg.Info = eText_GuildGeneral_TargetMoneyError;
	//		SendMessageToClient( &msg );
	//		return;
	//	}
	//	MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
	//	char WorldInfo[256];
	//	sprintf_s(WorldInfo,255,theXmlString.GetString(eText_GuildGeneral_AddBattleWorldInfo),m_pGuild->GetName(),pDestGuild->GetName());
	//	xChat.SetString(WorldInfo);
	//	GettheServer().SendMsgToWorld(&xChat,true);

	//	MsgCampBattleNewDataAck msg;
	//	msg.add = pReq->add;
	//	strcpy_s(msg.info,sizeof(msg.info)-1,pReq->info);
	//	strcpy_s(msg.srcGuildName,sizeof(msg.srcGuildName)-1,m_pGuild->GetName());
	//	pDestPlayer->SendMessageToClient( &msg );

	//	//ֱ�Ӽ���CD
	//	time_t nowtime;
	//	time(&nowtime);
	//	nowtime +=theGameBattleControl.GetMapMaxTimeByType(GameBattleDefine::GameBattle_Type_GuildGeneral) * 60;
	//	gCharInfoServer.otherdata.nBeginGameGeneralBattleTime = nowtime;
	//	//����������ͻ���ȥ 
	//	MsgUpdateAddCampBattleCD msgCD;
	//	msgCD.Time = nowtime;
	//	SendMessageToClient( &msgCD );
	//}
	/*else
	{
		
	}*/
	pReq->add.MapID = theGameBattleControl.GetMapIDByType(GameBattleDefine::GameBattle_Type_GuildGeneral);
	GS2CSCampBattleNewDataReq msg;
	msg.add = pReq->add;
	strcpy_s(msg.info,sizeof(msg.info)-1,pReq->info);
	GettheServer().SendMsgToCenterServer( &msg );
}
void GamePlayer::OnMsgLoadCampBattleDataReq( Msg* pMsg )
{
	//�ͻ����������ȫ��������
	theGameCampBattleDataManager.SendDataToServer(GetDBCharacterID());
}
void GamePlayer::OnMsgAddCampBattleDataReq( Msg* pMsg )
{
	MsgAddCampBattleDataReq* pReq = (MsgAddCampBattleDataReq *)pMsg;
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(pReq->add.SrcGuildID);
	if(!pSrcGuild)
		return;
	//������ӹ���Լս
	//1.���͸�ָ������ ���빫��Լս �ж���ҵ�ǰʱ���Ƿ��Ѿ���Լս��
	if(pReq->Result)
	{
		//ͬ��Լս ���Ǵ������߼��ж�
		if(!theGameCampBattleDataManager.IsExitesNeedWriteData(pReq->add.DestGuildID))
		{
			MsgGameBattleErrorAck msg;
			msg.Info = eText_GuildGaneral_TimeError;//�����Ϣ�Ѿ���ʱ�� ��Ч
			SendMessageToClient( &msg );
			return;
		}
		if(!theGameCampBattleDataManager.IsCanAddGuildBattleData(pReq->add.SrcGuildID,pReq->add.BeginTime,GameBattleDefine::GameBattle_Type_GuildGeneral) 
			|| !theGameCampBattleDataManager.IsCanAddGuildBattleData(pReq->add.DestGuildID,pReq->add.BeginTime,GameBattleDefine::GameBattle_Type_GuildGeneral))
			return;
		//�ж������Ƿ���ȷ
		GameBattleDefine::GuildCampBattle* pInfo = theGameCampBattleDataManager.GetWriteInfoByDestID(pReq->add.DestGuildID);
		if(!pInfo)
			return;
		if(pInfo->IsChange(pReq->add))
			return;
		//2.�ж��Ƿ����㹻�Ľ�Ǯ
		if(this->GetMoney() < pReq->add.MoneySum)
			return;
		//3.�Ƿ����㹻��ʹ����
		if(m_pGuild->GetMission() < pReq->add.GuildMissionSum* 20)
			return;
		//4.�Ƿ����㹻�ľ����ʽ�
		if(m_pGuild->GetMoney() < pReq->add.GuildMoneySum* 20)
			return;
		//5.�ж�Ŀ�깫���Ƿ����
		GameGuild* pSrcGuild = theGameGuildManager.GetGuild(pReq->add.SrcGuildID);
		if(!pSrcGuild)
			return;
		//6.�жϹ���Ļ᳤�Ƿ����߻�����������GameServer
		GuildMember* pMaster =  pSrcGuild->GetMember(pSrcGuild->GetMasterID());
		if(!pMaster || !pMaster->GetOnLine())
			return;
		//7.�۳�Լս��ȫ����Ǯ
		m_pGuild->OperateGuildMission(GuildDefine::OperateSub,pReq->add.GuildMissionSum);
		m_pGuild->OperateGuildMoney(GuildDefine::OperateSub,pReq->add.GuildMoneySum);
		OperateMoney(EOT_Sub,pReq->add.MoneySum, true, __FUNCTION__, __LINE__,0);

		GS2CSDelPlayerMoney msgCS;
		msgCS.add = pReq->add;
		GettheServer().SendMsgToCenterServer( &msgCS );
		//�޸������ļ��ĵ�ͼID
		pReq->add.MapID = theGameBattleControl.GetMapIDByType(GameBattleDefine::GameBattle_Type_GuildGeneral);
		////8.������ӵĺ����������������
		//GS2CSAddCampBattleData msg;
		//msg.add= pReq->add;
		//msg.Result = true;
		//GettheServer().SendMsgToCenterServer( &msg );

		//time_t tt = pReq->add.BeginTime;
		//struct tm sysNowTime(*localtime(&tt));
		//char TimeLog[64];
		//sprintf_s(TimeLog,63,"%d-%d-%d %d:%d:%d",sysNowTime.tm_year+1900,sysNowTime.tm_mon+1,sysNowTime.tm_mday,sysNowTime.tm_hour,sysNowTime.tm_min,sysNowTime.tm_sec);
		//MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
		//char WorldInfo[256];
		//sprintf_s(WorldInfo,255,theXmlString.GetString(eText_GuildGeneral_AddBattle),pSrcGuild->GetName(),m_pGuild->GetName(),TimeLog);
		//xChat.SetString(WorldInfo);
		//GettheServer().SendMsgToWorld(&xChat,true);
	}
	else
	{
		//�ܾ���Լս ������Ҫ֪ͨ��� ������� �Է��ܾ���Լս
		//��Լս�Ľ�Ǯ���ظ����  ����� ֱ�ӷ���  ��ҵ�ͨ���ʼ�����
		//pSrcGuild->OperateGuildMission(GuildDefine::OperateAdd,pReq->add.GuildMissionSum);
		//pSrcGuild->OperateGuildMoney(GuildDefine::OperateAdd,pReq->add.GuildMoneySum);
		//
		//GS2CSSendMailReq xReq;
		//xReq.charDbId = RelationDefine::InitID;
		//xReq.mail.type  = SMail::EMT_System;
		//xReq.mail.state = SMail::EMS_NotOpen;
		//xReq.mail.sendTime = TimeEx::GetNowTime();        
		//// ������
		//xReq.mail.owners[EM_FromIndex].charDbId = 0;
		//sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		//// �ռ���	
		//xReq.mail.owners[EM_ToIndex].charDbId = pSrcGuild->GetMasterID();
		//HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pSrcGuild->GetMember(pSrcGuild->GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
		//sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_GuildGeneral_Secc_Content ) );
		//sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_GuildGeneral_Secc_Title ) );
		//xReq.mail.money = pReq->add.MoneySum;
		//GettheServer().SendMsgToCenterServer( &xReq );

		//�������繫��
		MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
		char WorldInfo[256];
		sprintf_s(WorldInfo,255,theXmlString.GetString(eText_GuildGeneral_CanelBattle),pSrcGuild->GetName(),m_pGuild->GetName());
		xChat.SetString(WorldInfo);
		GettheServer().SendMsgToWorld(&xChat,true);

		GS2CSAddCampBattleData msg;
		msg.Result = false;
		msg.add = pReq->add;
		GettheServer().SendMsgToCenterServer( &msg );
	}
}
void GamePlayer::OnMsgDelCampBattleDataReq( Msg* pMsg )
{
	//���������
	return;
	//����ɾ������Լս
	MsgDelCampBattleDataReq* pReq = (MsgDelCampBattleDataReq*)pMsg;
	//1.�Լ���������Լս �������� ����ȫ����ԭ
	if(!theGameCampBattleDataManager.IsExitesGuildCampBattleData(pReq->ID))
		return;
	//2.��Լս�Ľ������Է�����
	//3.����ɾ��������
	GS2CSDelCampBattleData msg;
	msg.ID = pReq->ID;
	GettheServer().SendMsgToCenterServer( &msg );
}
void GamePlayer::OnMsgEnterGameBattleReq( Msg* pMsg )
{
	//��ҽ���ս��
	MsgEnterGameBattleReq* pReq = (MsgEnterGameBattleReq*)pMsg;
	if(!pReq)
		return;
	GameGuild* pGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(!pGuild)
		return;
	//��ҹ�����ڵĻ� ���ǻ�ȡս���Ĺ�����
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(pReq->uchBattleType));
	if(!pManager)
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(GetGuildID());
	if(!pBattle)
		return;
	if(!pManager->EnterGameBattle(this))
		return;
}