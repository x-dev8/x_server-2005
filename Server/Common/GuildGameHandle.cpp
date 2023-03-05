#include "CenterServerNetEvent.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "GuildConfig.h"
#include "RunStatus.h"
#include "XmlStringLanguage.h"
#include "LogEventService.h"
#include "SevenDays.h"

long CenterServerNetEvent::OnProcessGuildMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE_NOTCHECK( CS2GS_GUILDDATALIST, CS2GSGuildDataList, _OnCS2GSGuildDataList );
        MESSAGE_HANDLE( CS2GS_GUILDDATASENDSUCCESS, CS2GSGuildDataSendSuccess, _OnCS2GSGuildDataSendSuccess );
        MESSAGE_HANDLE( CS2GS_CREATEGUILDACK, CS2GSCreateGuildAck, _OnCS2GSCreateGuildAck );
        MESSAGE_HANDLE( CS2GS_LEAVEGUILDACK, CS2GSLeaveGuildAck, _OnCS2GSLeaveGuildAck );
        MESSAGE_HANDLE( CS2GS_JOINGUILDACK, CS2GSJoinGuildAck, _OnCS2GSJoinGuildAck );
        MESSAGE_HANDLE( GS2CS_DISBANDGUILDACK, CS2GSDisbandGuildAck, _OnCS2GSDisbandGuildAck );
        MESSAGE_HANDLE( CS2GS_MEMBERDATAUPDATE, CS2GSMemberDataUpdate, _OnCS2GSMemberDataUpdate );
        MESSAGE_HANDLE( CS2GS_GUILDDATAUPDATE, CS2GSGuildDataUpdate, _OnCS2GSGuildDataUpdate );
        MESSAGE_HANDLE( CS2GS_GUILDNOTICECHANGEACK, CS2GSGuildNoticeChangeAck, _OnCS2GSGuildNoticeChangeAck );
		MESSAGE_HANDLE( CS2GS_GUILDAIMCHANGEACK, CS2GSGuildAimChangeAck, _OnCS2GSGuildAimChangeAck );
        MESSAGE_HANDLE( CS2GS_GUILDFAMILYCHANGE, CS2GSGuildFamilyChange, _OnCS2GSGuildFamilyChange );
        MESSAGE_HANDLE( CS2GS_GUILDDELATEREQUESTREQ, CS2GSGuildDelateRequestReq, _OnCS2GSGuildDelateRequestReq );
        MESSAGE_HANDLE( CS2GS_GUILDDELATERESULT, CS2GSGuildDelateResult, _OnCS2GSGuildDelateResult );
        MESSAGE_HANDLE( CS2GS_GUILDDONATEREQUESTREQ, CS2GSGuildDonateRequestReq, _OnCS2GSGuildDonateRequestReq );
        MESSAGE_HANDLE( CS2GS_GUILDDONATESTOP, CS2GSGuildDonateStop, _OnCS2GSGuildDonateStop );
        MESSAGE_HANDLE( CS2GS_GUILDQUESTRELEASESTATUS, CS2GSGuildQuestReleaseStatus, _OnCS2GSGuildQuestReleaseStatus );
        MESSAGE_HANDLE( CS2GS_GUILDCLEARMEMBERACTIVITY, CS2GSGuildClearMemberActivity, _OnCS2GSGuildClearMemberActivity );
        MESSAGE_HANDLE_NOTCHECK( CS2GS_GUILDMESSAGE, CS2GSGuildMessage, _OnCS2GSGuildMessage );
        MESSAGE_HANDLE( CS2GS_GUILDCONVENEREQ, CS2GSGuildConveneReq, _OnCS2GSGuildConveneReq );
        MESSAGE_HANDLE( CS2GS_GUILDCONVENESTOP, CS2GSGuildConveneStop, _OnCS2GSGuildConveneStop );
		MESSAGE_HANDLE( CS2GS_PLAYERLVUPTOTHIRTY, GS2CSPlayerLvUpToThirtyMessage, _OnCS2GSPlayerLvUpToThirtyReq );
		MESSAGE_HANDLE( CS2GS_MISSIONNOTENOUGH, CS2GSMissionNotEnuoughMessage, _OnCS2GSMissionNotEnuoughReq );
		MESSAGE_HANDLE( CS2GS_CHANGEGUILDNAMEACK, CS2GSChangeGuildNameAck, _OnCS2GSChangeGuildNameAck );

		MESSAGE_HANDLE( CS2GS_GUILDMEMBERCHANGENAME, CS2GSGuildMemberChangeName, _OnCS2GSGuildMemberChangeName );
		MESSAGE_HANDLE( CS2GS_UPDATEGUILDMEMBERONLINETIME, CS2GSUpdateGuildMemberOnLineTime, _OnCS2GSUpdateGuildMemberOnLineTime );

		
		
    MESSAGE_MAPPING_END

    return ER_Success;
}

void CenterServerNetEvent::_OnCS2GSGuildDataList( NetClient* pNetClient, CS2GSGuildDataList* pMessage )
{
    GameGuild* pGuild = GameGuild::CreateGuild();
    if ( pGuild == NULL )
    { return; }

    pGuild->SetGuildDataToServer( pMessage->xData );
    for ( int i = 0 ; i < pMessage->ustCount; ++i )
    {
        pGuild->AddMember( pMessage->xMemberList[i] );
    }

    theGameGuildManager.AddGuild( pGuild );
}

void CenterServerNetEvent::_OnCS2GSGuildDataSendSuccess( NetClient* pNetClient, CS2GSGuildDataSendSuccess* pMessage )
{
	theGameGuildManager.SetLoadSuccess(true);
}

void CenterServerNetEvent::_OnCS2GSCreateGuildAck( NetClient* pNetClient, CS2GSCreateGuildAck* pMessage )
{
    GameGuild* pGuild = GameGuild::CreateGuild();
    if ( pGuild == NULL )
    { return; }

    // 设置帮派属性
    pGuild->SetGuildDataToServer( pMessage->xGuild );
    theGameGuildManager.AddGuild( pGuild );

    // 把新创建的帮派发送给所有人
    MsgTellCreateGuild xTell;
    xTell.uchCountry = pGuild->GetCountry();
    xTell.nGuildID   = pGuild->GetID();
    HelperFunc::SafeNCpy( xTell.szPlayer, pMessage->szPlayer, sizeof( xTell.szPlayer ) );
    HelperFunc::SafeNCpy( xTell.szName, pGuild->GetName(), sizeof( xTell.szName ) );
    GettheServer().SendMsgToWorld( &xTell, false );

    GamePlayer* pPlayer = GameGuild::GetPlayer( pGuild->GetMasterID() );
    if ( pPlayer == NULL )
    { return; }

    const GuildConfig::CreateSetting& xSetting = theGuildConfig.GetCreateSetting();

    // 扣除金钱
    pPlayer->OperateJiaoZi( EOT_Sub, xSetting.GetCostMoney(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_CreateGuild);

    pPlayer->_achieveManager.UpdateTriggerByValueType( EAT_CreateGuild );

	//触发7天乐
	//pPlayer->_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_FirstDay );

	//LYH 日志添加 （创建工会）
	theLogEventService.LogGuild(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),pGuild->GetID(),eSystemLogInfo_guild_create,pPlayer->GetCharName());
}

void CenterServerNetEvent::_OnCS2GSLeaveGuildAck( NetClient* pNetClient, CS2GSLeaveGuildAck* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->RemoveMember( pMessage->nPlayerID );
    pGuild->ProcessMemberLeaveGuild( pMessage->nPlayerID );
}

void CenterServerNetEvent::_OnCS2GSJoinGuildAck( NetClient* pNetClient, CS2GSJoinGuildAck* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->xMember.GetGuildID() );
    if ( pGuild == NULL )
    { return; }

    pGuild->AddMember( pMessage->xMember );
    pGuild->ProcessMemberJoinGuild( pMessage->xMember );

	//触发7天乐
	/*GamePlayer* pPlayer = GameGuild::GetPlayer( pMessage->xMember.GetID() );
	if ( pPlayer == NULL )
	{ return; }
	pPlayer->_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_FirstDay );*/
}

void CenterServerNetEvent::_OnCS2GSDisbandGuildAck( NetClient* pNetClient, CS2GSDisbandGuildAck* pMessage )
{
    // 通知在线所有人, 某个帮派解散了
    MsgTellDisbandGuild xTell;
    xTell.nGuildID = pMessage->nGuildID;
    GettheServer().SendMsgToWorld( &xTell, false );

    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    // 处理帮派解散
    pGuild->ProcessDisbandGuild();

	//LYH日志添加
	theLogEventService.LogGuild(0,0,pGuild->GetID(),eSystemLogInfo_guild_disband,"NULL");

    // 删除一个帮派
    theGameGuildManager.RemoveGuild( pMessage->nGuildID );


}

void CenterServerNetEvent::_OnCS2GSMemberDataUpdate( NetClient* pNetClient, CS2GSMemberDataUpdate* pMessage )
{
	GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
	if ( pGuild == NULL )
	{ return; }

	pGuild->ProcessMemberDataUpdate( pMessage->nPlayerID, pMessage->uchUpdateType, pMessage->nUpdateValue );
}

void CenterServerNetEvent::_OnCS2GSGuildDataUpdate( NetClient* pNetClient, CS2GSGuildDataUpdate* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessGuildDataUpdate( pMessage->uchUpdateType, pMessage->n64UpdateValue );
}

void CenterServerNetEvent::_OnCS2GSGuildNoticeChangeAck( NetClient* pNetClient, CS2GSGuildNoticeChangeAck* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessGuildNoticeChange( pMessage->szNotice );
}

void CenterServerNetEvent::_OnCS2GSGuildAimChangeAck( NetClient* pNetClient, CS2GSGuildAimChangeAck* pMessage )
{
	GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
	if ( pGuild == NULL )
	{ return; }

	pGuild->ProcessGuildAimChange( pMessage->szAim, pMessage->nChangeAimTime );
}

void CenterServerNetEvent::_OnCS2GSGuildFamilyChange( NetClient* pNetClient, CS2GSGuildFamilyChange* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessFamilyChange( pMessage->nRequesterID, pMessage->uchFamilyID, pMessage->szName );
}

void CenterServerNetEvent::_OnCS2GSGuildDelateRequestReq( NetClient* pNetClient, CS2GSGuildDelateRequestReq* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessGuildDelateRequest( pMessage->nPlayerID );
}

void CenterServerNetEvent::_OnCS2GSGuildDelateResult( NetClient* pNetClient, CS2GSGuildDelateResult* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    // 通知结果
    MsgGuildDelateResult xResult;
    xResult.nPlayerID      = pMessage->nPlayerID;
    xResult.bDelateSuccess = pMessage->bDelateSuccess;
    pGuild->SendMessageToGuild( &xResult, pGuild->GetMasterID() );

    pGuild->GetDelateInfo().Reset();
}

void CenterServerNetEvent::_OnCS2GSGuildDonateRequestReq( NetClient* pNetClient, CS2GSGuildDonateRequestReq* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->StartDonateTimer();
    pGuild->SetDonateMoney( 0 );

    // 发送募捐请求
    MsgGuildDonateReq xReq;
    pGuild->SendMessageToGuild( &xReq );
}

void CenterServerNetEvent::_OnCS2GSGuildDonateStop( NetClient* pNetClient, CS2GSGuildDonateStop* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->StopDonateTimer();
    pGuild->SetDonateMoney( 0 );
}

void CenterServerNetEvent::_OnCS2GSGuildQuestReleaseStatus( NetClient* pNetClient, CS2GSGuildQuestReleaseStatus* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessQuestRelease( pMessage->nQuestID, pMessage->n64RelasetTime );
}

void CenterServerNetEvent::_OnCS2GSGuildClearMemberActivity( NetClient* pNetClient, CS2GSGuildClearMemberActivity* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessClearMemberActivity();
}


void CenterServerNetEvent::_OnCS2GSGuildMessage( NetClient* pNetClient, CS2GSGuildMessage* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->SendMessageToGuild( reinterpret_cast< Msg* >( pMessage->szMessage ), pMessage->nExceptID, pMessage->ustLevel, false );
}

void CenterServerNetEvent::_OnCS2GSGuildConveneReq( NetClient* pNetClient, CS2GSGuildConveneReq* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessGuildConveneReq( pMessage->nPlayerID, pMessage->nMapID, pMessage->fPosX, pMessage->fPosY, pMessage->fDir, pMessage->uchLevel );
}

void CenterServerNetEvent::_OnCS2GSGuildConveneStop( NetClient* pNetClient, CS2GSGuildConveneStop* pMessage )
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->ProcessGuildConveneTimeOut();
}
void CenterServerNetEvent::_OnCS2GSPlayerLvUpToThirtyReq( NetClient* pNetClient, GS2CSPlayerLvUpToThirtyMessage* pMessage )
{
	GamePlayer* pPlayer = GameGuild::GetPlayer( pMessage->nTargetID);
	if ( pPlayer )
	{
		MsgTellClientCanInvite			msgCanInvite;
		msgCanInvite.nPlayerID = pMessage->nPlayerID;
		msgCanInvite.nPlayerLv = pMessage->nPlayerLv;
		msgCanInvite.opType	   = MsgTellClientCanInvite::Guild_Invite;
		HelperFunc::SafeNCpy( msgCanInvite.szPlayerName, pMessage->szSpeakName, sizeof( msgCanInvite.szPlayerName ) );

		pPlayer->SendMessageToClient( &msgCanInvite );
	}	
}

void CenterServerNetEvent::_OnCS2GSMissionNotEnuoughReq( NetClient* pNetClient, CS2GSMissionNotEnuoughMessage* pMessage )
{
	GamePlayer* pPlayer = GameGuild::GetPlayer( pMessage->nMasterID );
	if ( pPlayer )
	{
		char bufStr1[BUFSIZ] = {0};

		switch ( pMessage->nMissionCount )
		{
		case GuildDefine::MissionFirst:
			sprintf_s( bufStr1,sizeof(bufStr1), theXmlString.GetString(eText_MissionCountFirst) );
			break;
		case GuildDefine::MissionSecond:
			sprintf_s( bufStr1,sizeof(bufStr1), theXmlString.GetString(eText_MissionCountSecond) );
			break;
		case GuildDefine::MissionThird:
			sprintf_s( bufStr1,sizeof(bufStr1), theXmlString.GetString(eText_MissionCountThird) );
			break;
		default:
			return;
		}

		pPlayer->ShowInfo( false, 97, bufStr1 );
	}

}
void CenterServerNetEvent::_OnCS2GSChangeGuildNameAck( NetClient* pNetClient, CS2GSChangeGuildNameAck* pMessage )
{
	//GameServer接收到公会修改名称的命令
	GameGuild* pGuild = theGameGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild )
		return;
	if(strcoll(pGuild->GetName(),pMessage->Name) == 0)
		return;
	pGuild->ProcessGuildNameChange(pMessage->Name);
}
void CenterServerNetEvent::_OnCS2GSGuildMemberChangeName( NetClient* pNetClient, CS2GSGuildMemberChangeName* pMessage )
{
	//接收到公会玩家修改名称的命令 我们修改公会里的数据
	GameGuild* pGuild = theGameGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild)
		return;
	GuildMember* pMember= pGuild->GetMember(pMessage->PlayerID);
	if(!pMember)
		return;
	pMember->SetName(pMessage->szName);
	//发送消息给公会所有在线的玩家 刷新客户端的公会信息
	MsgGuildChangeNameAck msg;
	msg.GuildID = pMessage->GuildID;
	msg.PlayerID = pMessage->PlayerID;
	strcpy_s(msg.szName,sizeof(msg.szName),pMessage->szName);
	if(pGuild->GetMasterID() == pMessage->PlayerID)
	{
		GettheServer().SendMsgToWorld(&msg);//会长名称变化 全部服务器都需要知道
	}
	else
	{
		pGuild->SendMessageToGuild( &msg );
	}
}
void CenterServerNetEvent::_OnCS2GSUpdateGuildMemberOnLineTime( NetClient* pNetClient, CS2GSUpdateGuildMemberOnLineTime* pMessage )
{
	GameGuild* pGuild = theGameGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild)
		return;
	pGuild->UpdateGuildMemberOnLineTime(pMessage->PlayerID,pMessage->OnLineTime);
}