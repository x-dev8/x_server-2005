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
	//只判断金钱是否足够 其他的判断在之前已经做了
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
			//通过Center进行转发到玩家所在的GameServer去 告诉玩家添加新的约战失败
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
		//发送处理CD的命令道源玩家处
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
		//	//发送命令道客户端去 
		//	MsgUpdateAddCampBattleCD msg;
		//	msg.Time = nowtime;
		//	pSrcPlayer->SendMessageToClient( &msg );
		//}
		//else
		//{
		//	//发送到Center进行转发
		//	GS2CSCampBattleAddError msg;
		//	msg.ErrorID = 0;
		//	msg.PlayerID=pSrcGuild->GetMasterID();
		//	msg.Result = true;
		//	GettheServer().SendMsgToCenterServer( &msg );
		//}
		//发送到Center进行转发
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
	//客户端加载
	for(int i =0;i<pMessage->Sum;++i)
	{
		theGameCampBattleDataManager.InsertGuildBattleData(pMessage->info[i]);
	}
	if(pMessage->IsEnd)
		theGameCampBattleDataManager.SetLoadSecc();
	theGameBattleControl.RegisterGuildGeneralBattleManger();//创建公会约战管理器
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	//将已经加载的是不数据放入到战场集合里面去
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
	//判断玩家是否有足够的金钱和数据
	bool IsOk = true;
	if(pSrcPlayer->GetMoney() < pMessage->add.MoneySum)
		IsOk = false;
	//3.是否有足够的使命点
	if(pSrcGuild->GetMission() < pMessage->add.GuildMissionSum * 20)
		IsOk = false;
	//4.是否有足够的军团资金
	if(pSrcGuild->GetMoney() < pMessage->add.GuildMoneySum * 20)
		IsOk = false;
	if(!theGameCampBattleDataManager.IsExitesNeedWriteData(pMessage->add.DestGuildID))
		IsOk = false;//消息超时了
	GameBattleDefine::GuildCampBattle* pInfo = theGameCampBattleDataManager.GetWriteInfoByDestID(pMessage->add.DestGuildID);
	if(!pInfo || pInfo->IsChange(pMessage->add))
		IsOk = false;
	if(!IsOk)
	{
		//返还原玩家的金钱
		pDestGuild->OperateGuildMission(GuildDefine::OperateAdd,pMessage->add.GuildMissionSum);
		pDestGuild->OperateGuildMoney(GuildDefine::OperateAdd,pMessage->add.GuildMoneySum);
		
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
		xReq.mail.money = pMessage->add.MoneySum;
		GettheServer().SendMsgToCenterServer( &xReq );

		//删除数据库的约战信息
		GS2CSAddCampBattleData msg;
		msg.add= *pInfo;
		msg.Result = false;
		GettheServer().SendMsgToCenterServer( &msg );
		return;
	}
	pSrcGuild->OperateGuildMission(GuildDefine::OperateSub,pMessage->add.GuildMissionSum);
	pSrcGuild->OperateGuildMoney(GuildDefine::OperateSub,pMessage->add.GuildMoneySum);
	pSrcPlayer->OperateMoney(EOT_Sub,pMessage->add.MoneySum, true, __FUNCTION__, __LINE__,0);
	//当前成功 我们可以开启战场了
	pMessage->add.MapID = theGameBattleControl.GetMapIDByType(GameBattleDefine::GameBattle_Type_GuildGeneral);
	//8.发送添加的函数到中央服务器区
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
		//设置CD
		time_t nowtime;
		time(&nowtime);
		nowtime +=theGameBattleControl.GetMapMaxTimeByType(GameBattleDefine::GameBattle_Type_GuildGeneral) * 60;
		pPlayer->gCharInfoServer.otherdata.nBeginGameGeneralBattleTime = nowtime;
		//发送命令道客户端去 
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