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
	//试图添加新的公会约战
	if(theGameCampBattleDataManager.IsExitesNeedWriteData(pReq->add.DestGuildID))//对方公会有等待未处理的消息 不接受新的消息
	{
		MsgGameBattleErrorAck msg;
		msg.Info = eText_GuildGeneral_Target_WriteMsg;
		SendMessageToClient( &msg );
		return;
	}
	//1.判断约战的时间是否合适 CampBattleMaxLastTime  在持续时间内是否有新的约战
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
	//2.判断是否有足够的金钱
	if(this->GetMoney() < pReq->add.MoneySum)
		return;
	//3.是否有足够的使命点
	if(m_pGuild->GetMission() < pReq->add.GuildMissionSum * 20)
		return;
	//4.是否有足够的军团资金
	if(m_pGuild->GetMoney() < pReq->add.GuildMoneySum * 20)
		return;
	//5.判断目标公会是否存在
	GameGuild* pDestGuild = theGameGuildManager.GetGuild(pReq->add.DestGuildID);
	if(!pDestGuild)
		return;
	//6.判断公会的会长是否在线或者在其他的GameServer
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
	//7.扣除约战的全部金钱
	/*m_pGuild->OperateGuildMission(GuildDefine::OperateSub,pReq->add.GuildMissionSum);
	m_pGuild->OperateGuildMoney(GuildDefine::OperateSub,pReq->add.GuildMoneySum);
	OperateMoney(EOT_Sub,pReq->add.MoneySum, true, __FUNCTION__, __LINE__,0);*/
	//8.发送命令道世界去 告诉服务器开战
	//8.发送命令到中央服务器
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

	//	//直接计算CD
	//	time_t nowtime;
	//	time(&nowtime);
	//	nowtime +=theGameBattleControl.GetMapMaxTimeByType(GameBattleDefine::GameBattle_Type_GuildGeneral) * 60;
	//	gCharInfoServer.otherdata.nBeginGameGeneralBattleTime = nowtime;
	//	//发送命令道客户端去 
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
	//客户端申请加载全部的数据
	theGameCampBattleDataManager.SendDataToServer(GetDBCharacterID());
}
void GamePlayer::OnMsgAddCampBattleDataReq( Msg* pMsg )
{
	MsgAddCampBattleDataReq* pReq = (MsgAddCampBattleDataReq *)pMsg;
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(pReq->add.SrcGuildID);
	if(!pSrcGuild)
		return;
	//申请添加公会约战
	//1.发送给指定公会 申请公会约战 判断玩家当前时间是否已经有约战了
	if(pReq->Result)
	{
		//同意约战 我们处理下逻辑判断
		if(!theGameCampBattleDataManager.IsExitesNeedWriteData(pReq->add.DestGuildID))
		{
			MsgGameBattleErrorAck msg;
			msg.Info = eText_GuildGaneral_TimeError;//这个消息已经超时了 无效
			SendMessageToClient( &msg );
			return;
		}
		if(!theGameCampBattleDataManager.IsCanAddGuildBattleData(pReq->add.SrcGuildID,pReq->add.BeginTime,GameBattleDefine::GameBattle_Type_GuildGeneral) 
			|| !theGameCampBattleDataManager.IsCanAddGuildBattleData(pReq->add.DestGuildID,pReq->add.BeginTime,GameBattleDefine::GameBattle_Type_GuildGeneral))
			return;
		//判断数据是否正确
		GameBattleDefine::GuildCampBattle* pInfo = theGameCampBattleDataManager.GetWriteInfoByDestID(pReq->add.DestGuildID);
		if(!pInfo)
			return;
		if(pInfo->IsChange(pReq->add))
			return;
		//2.判断是否有足够的金钱
		if(this->GetMoney() < pReq->add.MoneySum)
			return;
		//3.是否有足够的使命点
		if(m_pGuild->GetMission() < pReq->add.GuildMissionSum* 20)
			return;
		//4.是否有足够的军团资金
		if(m_pGuild->GetMoney() < pReq->add.GuildMoneySum* 20)
			return;
		//5.判断目标公会是否存在
		GameGuild* pSrcGuild = theGameGuildManager.GetGuild(pReq->add.SrcGuildID);
		if(!pSrcGuild)
			return;
		//6.判断公会的会长是否在线或者在其他的GameServer
		GuildMember* pMaster =  pSrcGuild->GetMember(pSrcGuild->GetMasterID());
		if(!pMaster || !pMaster->GetOnLine())
			return;
		//7.扣除约战的全部金钱
		m_pGuild->OperateGuildMission(GuildDefine::OperateSub,pReq->add.GuildMissionSum);
		m_pGuild->OperateGuildMoney(GuildDefine::OperateSub,pReq->add.GuildMoneySum);
		OperateMoney(EOT_Sub,pReq->add.MoneySum, true, __FUNCTION__, __LINE__,0);

		GS2CSDelPlayerMoney msgCS;
		msgCS.add = pReq->add;
		GettheServer().SendMsgToCenterServer( &msgCS );
		//修改配置文件的地图ID
		pReq->add.MapID = theGameBattleControl.GetMapIDByType(GameBattleDefine::GameBattle_Type_GuildGeneral);
		////8.发送添加的函数到中央服务器区
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
		//拒绝了约战 我们需要通知玩家 告诉玩家 对方拒绝了约战
		//将约战的金钱返回给玩家  公会的 直接返回  玩家的通告邮件返回
		//pSrcGuild->OperateGuildMission(GuildDefine::OperateAdd,pReq->add.GuildMissionSum);
		//pSrcGuild->OperateGuildMoney(GuildDefine::OperateAdd,pReq->add.GuildMoneySum);
		//
		//GS2CSSendMailReq xReq;
		//xReq.charDbId = RelationDefine::InitID;
		//xReq.mail.type  = SMail::EMT_System;
		//xReq.mail.state = SMail::EMS_NotOpen;
		//xReq.mail.sendTime = TimeEx::GetNowTime();        
		//// 发信人
		//xReq.mail.owners[EM_FromIndex].charDbId = 0;
		//sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		//// 收件人	
		//xReq.mail.owners[EM_ToIndex].charDbId = pSrcGuild->GetMasterID();
		//HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pSrcGuild->GetMember(pSrcGuild->GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
		//sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_GuildGeneral_Secc_Content ) );
		//sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_GuildGeneral_Secc_Title ) );
		//xReq.mail.money = pReq->add.MoneySum;
		//GettheServer().SendMsgToCenterServer( &xReq );

		//发送世界公告
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
	//不允许放弃
	return;
	//申请删除公会约战
	MsgDelCampBattleDataReq* pReq = (MsgDelCampBattleDataReq*)pMsg;
	//1.自己主动放弃约战 等于认输 奖励全部还原
	if(!theGameCampBattleDataManager.IsExitesGuildCampBattleData(pReq->ID))
		return;
	//2.将约战的奖励给对方公会
	//3.发送删除的命令
	GS2CSDelCampBattleData msg;
	msg.ID = pReq->ID;
	GettheServer().SendMsgToCenterServer( &msg );
}
void GamePlayer::OnMsgEnterGameBattleReq( Msg* pMsg )
{
	//玩家进入战场
	MsgEnterGameBattleReq* pReq = (MsgEnterGameBattleReq*)pMsg;
	if(!pReq)
		return;
	GameGuild* pGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(!pGuild)
		return;
	//玩家公会存在的话 我们获取战场的管理器
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(pReq->uchBattleType));
	if(!pManager)
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(GetGuildID());
	if(!pBattle)
		return;
	if(!pManager->EnterGameBattle(this))
		return;
}