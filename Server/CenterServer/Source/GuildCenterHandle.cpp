#include "NetEvent.h"
#include "GameServerManager.h"
#include "GuildManager.h"
#include "MySqlCommunication.h"
#include "TimeEx.h"
#include "GuildConfig.h"
#include "XmlStringLanguage.h"
#include "MailManagerMain.h"
#include "GuildMissionConfig.h"
#include "RelationManager.h"
#include "LogEventService.h"
long NetEvent::OnProcessGuildMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( GS2CS_CREATEGUILDREQ, GS2CSCreateGuildReq, _OnGS2CSCreateGuildReq );
        MESSAGE_HANDLE( GS2CS_LEAVEGUILDREQ, GS2CSLeaveGuildReq, _OnGS2CSLeaveGuildReq );
        MESSAGE_HANDLE( GS2CS_KICKGUILDREQ, GS2CSKickGuildReq, _OnGS2CSKickGuildReq );
        MESSAGE_HANDLE( GS2CS_INVITEGUILDREQ, GS2CSInviteGuildReq, _OnGS2CSInviteGuildReq );
        MESSAGE_HANDLE( GS2CS_INVITEJOINGUILDACK, GS2CSInviteJoinGuildAck, _OnGS2CSInviteJoinGuildAck );
        MESSAGE_HANDLE( GS2CS_JOINGUILDREQ, GS2CSJoinGuildReq, _OnGS2CSJoinGuildReq );
        MESSAGE_HANDLE( GS2CS_REQUESTJOINGUILDACK, GS2CSRequestJoinGuildAck, _OnGS2CSRequestJoinGuildAck );
        MESSAGE_HANDLE( GS2CS_GUILDNOTICECHANGEREQ, GS2CSGuildNoticeChangeReq, _OnGS2CSGuildNoticeChangeReq );
		MESSAGE_HANDLE( GS2CS_GUILDAIMCHANGE, GS2CSGuildAimChangeReq, _OnGS2CSGuildAimChangeReq );
        MESSAGE_HANDLE( GS2CS_GUILDRESIGNPOSITIONREQ, GS2CSGuildResignPositionReq, _OnGS2CSGuildResignPositionReq );
        MESSAGE_HANDLE( GS2CS_GUILDTRANSFERPOSITIONREQ, GS2CSGuildTransferPositionReq, _OnGS2CSGuildTransferPositionReq );
        MESSAGE_HANDLE( GS2CS_GUILDCREATEFAMILYREQ, GS2CSGuildCreateFamilyReq, _OnGS2CSGuildCreateFamilyReq );
        MESSAGE_HANDLE( GS2CS_GUILDFAMILYCHANGEREQ, GS2CSGuildFamilyChangeReq, _OnGS2CSGuildFamilyChangeReq );
        MESSAGE_HANDLE( GS2CS_GUILDMEMBERFAMILYCHANGEREQ, GS2CSGuildMemberFamilyChangeReq, _OnGS2CSGuildMemberFamilyChangeReq );
        MESSAGE_HANDLE( GS2CS_GUILDASSIGNPOSTIONREQ, GS2CSGuildAssignPositionReq, _OnGS2CSGuildAssignPositionReq );
        MESSAGE_HANDLE( GS2CS_GUILDDATACHANGEREQ, GS2CSGuildDataChangeReq, _OnGS2CSGuildDataChangeReq );
        MESSAGE_HANDLE( GS2CS_MEMBERDATACHANGEREQ, GS2CSMemberDataChangeReq, _OnGS2CSMemberDataChangeReq );
        MESSAGE_HANDLE( GS2CS_GUILDLEVELUPREQ, GS2CSGuildLevelUpReq, _OnGS2CSGuildLevelUpReq );
        MESSAGE_HANDLE( GS2CS_GUILDOFFEGUILDRREQ, GS2CSGuildOfferBuildReq, _OnGS2CSGuildOfferBuildReq );
        MESSAGE_HANDLE( GS2CS_GUILDCOLLECTREQ, GS2CSGuildCollectReq, _OnGS2CSGuildCollectReq );
        MESSAGE_HANDLE( GS2CS_GUILDDELATEREQUESTREQ, GS2CSGuildDelateRequestReq, _OnGS2CSGuildDelateRequestReq );
        MESSAGE_HANDLE( GS2CS_GUILDDELATEAGREEACK, GS2CSGuildDelateAgreeAck, _OnGS2CSGuildDelateAgreeAck );
        MESSAGE_HANDLE( GS2CS_GUILDDONATEREQUESTREQ, GS2CSGuildDonateRequestReq, _OnGS2CSGuildDonateRequestReq );
        MESSAGE_HANDLE( GS2CS_GUILDDONATEACK, GS2CSGuildDonateAck, _OnGS2CSGuildDonateAck );
        MESSAGE_HANDLE( GS2CS_GUILDQUESTRELEASEREQ, GS2CSGuildQuestReleaseReq, _OnGS2CSGuildQuestReleaseReq );
        MESSAGE_HANDLE_NOTCHECK( GS2CS_GUILDMESSAGE, GS2CSGuildMessage, _OnGS2CSGuildMessage );
        MESSAGE_HANDLE( GS2CS_GUILDCONVENEREQ, GS2CSGuildConveneReq, _OnGS2CSGuildConveneReq );
		MESSAGE_HANDLE( GS2CS_PLAYERLVUPTOTHIRTY, GS2CSPlayerLvUpToThirtyMessage, _OnGS2CSPlayerLvUpToThirtyReq );
		MESSAGE_HANDLE( GS2CS_GUILDSQREQ, GS2CSGuildSQReq, _OnGS2CSGuildSQReq );
		MESSAGE_HANDLE( GS2CS_RAISEGUILDPLAYERITEM, GS2CSRaiseGuildPlayerItem, _OnGS2CSRaiseGuildPlayerItem );
		MESSAGE_HANDLE( CS2GS_GUILDBATTLESUM, CS2GSGuildBattleSum, _OnCS2GSGuildBattleSum );
		MESSAGE_HANDLE( GS2CS_SETGUILDCAMPBATTLEVALUE, GS2CSSetGuildCampBattleValue, _OnGS2CSSetGuildCampBattleValue );
		MESSAGE_HANDLE( GS2CS_CHANGEGUILDNAMEREQ, GS2CSChangeGuildNameReq, _OnGS2CSChangeGuildNameReq );
		MESSAGE_HANDLE( GS2CS_GUILDMEMBERCHANGENAME,GS2CSGuildMemberChangeName, _OnGS2CSGuildMemberChangeName );

		MESSAGE_HANDLE( GS2CS_UPDATEGUILDCAMPBATTLEPOINT,GS2CSUpdateGuildCampBattlePoint, _OnGS2CSUpdateGuildCampBattlePoint);

		MESSAGE_HANDLE( GS2CS_UPDATEGUILDMEMBERONLINETIME,GS2CSUpdateGuildMemberOnLineTime, _OnGS2CSUpdateGuildMemberOnLineTime);

    MESSAGE_MAPPING_END

    return ER_Success;
}


void NetEvent::_OnGS2CSCreateGuildReq( NetClient* pNetClient, GS2CSCreateGuildReq* pMessage )
{
    // 创建公会
    CenterGuild* pGuild = CenterGuild::CreateGuild();
    if ( pGuild == NULL )
    { return; }

	if( pMessage->uchCountry  == CountryDefine::Country_Init) //无国籍无法创建工会
		return;

    // 计算出帮派ID
    pGuild->SetID( theCenterGuildManager.MakeGuildID() );
    pGuild->SetName( pMessage->szName );
	pGuild->SetAim( pMessage->szAim );
    pGuild->SetCountry( pMessage->uchCountry );
    pGuild->SetMasterID( pMessage->xMember.GetID() );
    pGuild->SetLevel( 1 );      // 默认帮派为1级
    pGuild->SetCreateTime( TimeEx::GetNowTime() );
	pGuild->SetMission(theGuildMissionConfig.GetInitMissionValue());//在创建出个帮派的时候 获取初始的使命点

    theCenterGuildManager.AddGuild( pGuild );

    // 设置帮会成员的ID
    pMessage->xMember.SetGuildID( pGuild->GetID() );

    // 同步给所有Game服务器
    CS2GSCreateGuildAck xAck;
    xAck.xGuild = *pGuild;
    HelperFunc::SafeNCpy( xAck.szPlayer, pMessage->xMember.GetName(), sizeof( xAck.szPlayer ) );
    theGameServerManager.SendMessageToGameServers( &xAck );
    
    pGuild->AddMember( pMessage->xMember );
    pGuild->ProcessMemberJoinGuild( pMessage->xMember );

    // 保存入数据库
    pGuild->SaveGuildDataToDatabase();	
}

void NetEvent::_OnGS2CSLeaveGuildReq( NetClient* pNetClient, GS2CSLeaveGuildReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Leave ) )
    { return; }

    pGuild->RemoveMember( pMessage->nPlayerID );
    pGuild->ProcessMemberLeaveGuild( pMessage->nPlayerID );
}

void NetEvent::_OnGS2CSKickGuildReq( NetClient* pNetClient, GS2CSKickGuildReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Kick ) )
    { return; }

    if ( !pGuild->CheckPosition( pMessage->nPlayerID, pMessage->nTargetID ) )
    { return; }

    pGuild->RemoveMember( pMessage->nTargetID );
    pGuild->ProcessMemberLeaveGuild( pMessage->nTargetID );
}

void NetEvent::_OnGS2CSInviteGuildReq( NetClient* pNetClient, GS2CSInviteGuildReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Invite ) )
    { return; }

    GuildMember* pMember = pGuild->GetMember( pMessage->nPlayerID );
    if ( pMember == NULL )
    { return; }

    // 判断帮派人数
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( pGuild->GetLevel() );
    if ( pSetting == NULL || pGuild->MemberCount() >= pSetting->GetMaxCount() )
    { return; }

    // 直接转发给客户端
    MsgInviteJoinGuildReq xReq;
    xReq.nGuildID = pMessage->nGuildID;
    HelperFunc::SafeNCpy( xReq.szInviterName, pMember->GetName(), sizeof( xReq.szInviterName ) );
    theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xReq, pMessage->nTargetID );

    // 添加一个邀请记录
    pGuild->AddInvite( pMessage->nPlayerID, pMessage->nTargetID, HQ_TimeGetTime() );
}

void NetEvent::_OnGS2CSInviteJoinGuildAck( NetClient* pNetClient, GS2CSInviteJoinGuildAck* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->xMember.GetGuildID() );
    if ( pGuild == NULL )
    { return; }

    GuildInvite* pInvite = pGuild->GetInvite( pMessage->xMember.GetID() );
    if ( pInvite == NULL )
    { return; }

    unsigned int nInviterPlayerID = pInvite->GetPlayerID();
    pGuild->RemoveInvite( pMessage->xMember.GetID() );

    // 判断对方是否有帮会了
    if ( theCenterGuildManager.GetGuildByPlayerID( pMessage->xMember.GetID() ) != NULL )
    { return; }

    // 判断帮派人数
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( pGuild->GetLevel() );
    if ( pSetting == NULL || pGuild->MemberCount() >= pSetting->GetMaxCount() )
    { return; }

	// 如果不同意, 直接发回给邀请者
	if ( !pMessage->bAgreeJoin )
	{
        MsgInviteGuildAck xAck;
        xAck.uchResult = MsgInviteGuildAck::ECD_NotAgree;
        theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck, nInviterPlayerID );
        return;
    }

    pGuild->AddMember( pMessage->xMember );
    pGuild->ProcessMemberJoinGuild( pMessage->xMember );

    MsgInviteGuildAck xAck;
    xAck.uchResult = MsgInviteGuildAck::ECD_Agree;
    theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck, nInviterPlayerID );
}

void NetEvent::_OnGS2CSJoinGuildReq( NetClient* pNetClient, GS2CSJoinGuildReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->xMember.GetGuildID() );
    if ( pGuild == NULL )
    { return; }

	
    // 先找帮主
    //GuildMember* pMember = pGuild->GetMember( pGuild->GetMasterID() );
    //if ( pMember == NULL || !pMember->GetOnLine() )
    //{
    //    pMember = pGuild->GetViceMaster();  // 再找副帮主
    //    if ( pMember == NULL || !pMember->GetOnLine() )
    //    {
    //        MsgJoinGuildAck xAck;
    //        xAck.uchResult = MsgJoinGuildAck::ECD_NotOnLine;
    //        theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck, pMessage->xMember.GetID() );
    //        return;
    //    }
    //}
	
	// 添加一个申请记录
	GuildRequest * pR = pGuild->GetRequest(pMessage->xMember.GetID());
	if(pR)
	{
		MsgJoinGuildAck xAck;
        xAck.uchResult = MsgJoinGuildAck::ECD_IsCreSQ;
        theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck, pMessage->xMember.GetID() );
		return;
	}

    // 发送消息
    /*MsgRequestJoinGuildReq xReq;
    xReq.nPlayerID = pMessage->xMember.GetID();
    HelperFunc::SafeNCpy( xReq.szName, pMessage->xMember.GetName(), sizeof( xReq.szName ) );
    theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xReq, pMember->GetID() );*/

    
    pGuild->AddRequest( pMessage->xMember, HQ_TimeGetTime() );

	//发生一个消息给帮主或者副帮主
	MsgGuildAddSQReq msg;
	msg.ID = pMessage->xMember.GetID();
	msg.Level = pMessage->xMember.GetLevel();
	msg.Profession = pMessage->xMember.GetProfession();
	HelperFunc::SafeNCpy( msg.szName, pMessage->xMember.GetName(), sizeof(  msg.szName ) );
	GuildMember* pMastrtMember = pGuild->GetMember( pGuild->GetMasterID() );
    if ( pMastrtMember && pMastrtMember->GetOnLine() )
    {
		theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pMastrtMember->GetID() );
	}
	GuildMember* pViceMember = pGuild->GetViceMaster();
    if ( pViceMember && pViceMember->GetOnLine() )
    {
		theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pViceMember->GetID() );
	}
}

void NetEvent::_OnGS2CSRequestJoinGuildAck( NetClient* pNetClient, GS2CSRequestJoinGuildAck* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

	CenterRelation* pTargetRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nTargetID );
	if(pTargetRelation && pTargetRelation->GetGuildID() !=0)
	{
		MsgGuildDelSQReq msg;
		msg.ID = pMessage->nTargetID;
		theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg,pMessage->nPlayerID);
		return;
	}
	

    GuildRequest* pRequest = pGuild->GetRequest( pMessage->nTargetID );
    if ( pRequest == NULL )
    { return; }

    GuildRequest xRequest = *pRequest;
    pGuild->RemoveRequest( pMessage->nTargetID );

    if ( !pMessage->bAgreeJoin )
    {
        MsgJoinGuildAck xAck;
        xAck.uchResult = MsgJoinGuildAck::ECD_NotAgree;
        theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck, pMessage->nTargetID );
		
		MsgGuildDelSQReq msg;
		msg.ID = pMessage->nTargetID;
		GuildMember* pMastrtMember = pGuild->GetMember( pGuild->GetMasterID() );
		if ( pMastrtMember && pMastrtMember->GetOnLine() )
		{
			theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pMastrtMember->GetID() );
		}
		GuildMember* pViceMember = pGuild->GetViceMaster();
		if ( pViceMember && pViceMember->GetOnLine() )
		{
			theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pViceMember->GetID() );
		}
        return;
    }

    // 判断权限
    if ( !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Invite ) )
    { return; }

    // 判断帮派人数
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( pGuild->GetLevel() );
    if ( pSetting == NULL || pGuild->MemberCount() >= pSetting->GetMaxCount() )
    { return; }

	
	if(pTargetRelation && xRequest.GetMember().GetOnLine() != pTargetRelation->GetOnLine())
	{
		GuildMember& pMember = const_cast<GuildMember&>(xRequest.GetMember());
		pMember.SetOnLine(pTargetRelation->GetOnLine());//设置公会玩家的在线状态
	}

    pGuild->AddMember( xRequest.GetMember() );
    pGuild->ProcessMemberJoinGuild( xRequest.GetMember() );

	//发生命令到帮主和副帮主 处理玩家申请
	MsgGuildDelSQReq msg;
	msg.ID = pMessage->nTargetID;
	GuildMember* pMastrtMember = pGuild->GetMember( pGuild->GetMasterID() );
    if ( pMastrtMember && pMastrtMember->GetOnLine() )
    {
		theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pMastrtMember->GetID() );
	}
	GuildMember* pViceMember = pGuild->GetViceMaster();
    if ( pViceMember && pViceMember->GetOnLine() )
    {
		theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pViceMember->GetID() );
	}
}

void NetEvent::_OnGS2CSGuildNoticeChangeReq( NetClient* pNetClient, GS2CSGuildNoticeChangeReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Notice ) )
    { return; }

    pGuild->ProcessGuildNoticeChange( pMessage->szNotice );
}

void NetEvent::_OnGS2CSGuildResignPositionReq( NetClient* pNetClient, GS2CSGuildResignPositionReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Resign ) )
    { return; }

    pGuild->ProcessMemberDataUpdate( pMessage->nPlayerID, GuildDefine::UpdateMemberPosition, GuildDefine::Position_Member );
}

void NetEvent::_OnGS2CSGuildTransferPositionReq( NetClient* pNetClient, GS2CSGuildTransferPositionReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Transfer ) )
    { return; }

    GuildMember* pMember = pGuild->GetMember( pMessage->nPlayerID );
    if ( pMember == NULL )
    { return; }

    GuildMember* pTargetMember = pGuild->GetMember( pMessage->nTargetID );
    if ( pTargetMember == NULL )
    { return; }

    // 帮主必须禅让给副帮主
    if ( pMessage->nPlayerID == pGuild->GetMasterID() )
    {
        if ( pTargetMember->GetPosition() != GuildDefine::Position_ViceMaster )
        { return; }
    }
    else
    {
        if ( pTargetMember->GetPosition() != GuildDefine::Position_Member )
        { return; }
		// 如果是转让堂主
		if ( pMember->GetPosition() == GuildDefine::Position_FamilyMaster )
		{
			if ( pMember->GetFamilyID() != pTargetMember->GetFamilyID() )
			{ return; }
		}
    }

    unsigned char uchTargetPosition = pTargetMember->GetPosition();     // 对方的职位
    pGuild->ProcessMemberDataUpdate( pTargetMember, GuildDefine::UpdateMemberPosition, pMember->GetPosition() );
    pGuild->ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberPosition, uchTargetPosition );

    MsgGuildTransferAck xAck;
    xAck.uchResult = MsgGuildTransferAck::ECD_Success;
    theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck, pMessage->nPlayerID );
}

void NetEvent::_OnGS2CSGuildCreateFamilyReq( NetClient* pNetClient, GS2CSGuildCreateFamilyReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Family ) )
    { return; }

    if ( pGuild->GetFamilyID( pMessage->szName ) != GuildDefine::InitID )
    { return; }

    unsigned char uchFamilyID = pGuild->GetEmptyFamilyID();
    if ( uchFamilyID == GuildDefine::InitID )
    { return; }

    pGuild->ProcessFamilyChange( pMessage->nPlayerID, uchFamilyID, pMessage->szName );
}

void NetEvent::_OnGS2CSGuildFamilyChangeReq( NetClient* pNetClient, GS2CSGuildFamilyChangeReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Family ) )
    { return; }

    if ( !pGuild->HaveFamily( pMessage->uchFamilyID ) )
    { return; }

    if ( pGuild->GetFamilyID( pMessage->szName ) != GuildDefine::InitID )
    { return; }

    pGuild->ProcessFamilyChange( pMessage->nPlayerID, pMessage->uchFamilyID, pMessage->szName );
}

void NetEvent::_OnGS2CSGuildMemberFamilyChangeReq( NetClient* pNetClient, GS2CSGuildMemberFamilyChangeReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
	if ( pGuild == NULL )
	{ return; }

    if ( pMessage->uchFamilyID > 0 && !pGuild->HaveFamily( pMessage->uchFamilyID ) )
    { return; }

    GuildMember* pMember = pGuild->GetMember( pMessage->nTargetID );
    if ( pMember == NULL )
    { return; }

    if ( pMember->GetFamilyID() == pMessage->uchFamilyID )
    { return; }

	if ( pMessage->uchFamilyID > 0 && ! pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_InFamily ) )
	{// 转入分堂
		return;
	}

	if ( pMessage->uchFamilyID == 0 && ! pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_OutFamily ) )
	{// 转出分堂
		return;
	}

	if ( pMessage->uchFamilyID == 0 && pMember->GetPosition() == GuildDefine::Position_FamilyMaster )
	{ return; }

    pGuild->ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberFamily, pMessage->uchFamilyID );
}

void NetEvent::_OnGS2CSGuildAssignPositionReq( NetClient* pNetClient, GS2CSGuildAssignPositionReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Assign ) )
    { return; }

    GuildMember* pMaster = pGuild->GetMember( pMessage->nPlayerID );
    if ( pMaster == NULL || pMaster->GetPosition() <= pMessage->uchPosition )
    { return; }

    GuildMember* pTargetMember = pGuild->GetMember( pMessage->nTargetID );
    if ( pTargetMember == NULL || pTargetMember->GetPosition() == pMessage->uchPosition )
    { return; }

    GuildMember* pRecallMember = NULL;
    switch ( pMessage->uchPosition )
    {
    case GuildDefine::Position_FamilyMaster:    // 家族长
        if ( pTargetMember->GetFamilyID() == GuildDefine::InitID )
        { return; }

        pRecallMember = pGuild->GetFamilyMaster( pTargetMember->GetFamilyID() );
        break;
    case GuildDefine::Position_ViceMaster:      // 副帮主
        pRecallMember = pGuild->GetViceMaster();
        break;
    default:
        break;
    }

    // 除去以前成员的职位
    pGuild->ProcessMemberDataUpdate( pRecallMember, GuildDefine::UpdateMemberPosition, GuildDefine::Position_Member );
    
    // 设置新成员新职位
    pGuild->ProcessMemberDataUpdate( pTargetMember, GuildDefine::UpdateMemberPosition, pMessage->uchPosition );
}

void NetEvent::_OnGS2CSGuildDataChangeReq( NetClient* pNetClient, GS2CSGuildDataChangeReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    switch( pMessage->uchChangeType )
    {
    case GuildDefine::UpdateGuildMoney:
        pGuild->OperateGuildMoney( pMessage->uchOperateType, pMessage->nValue );
        break;
    case GuildDefine::UpdateGuildExp:
        pGuild->OperateGuildExp( pMessage->uchOperateType, pMessage->nValue );
        break;
    case GuildDefine::UpdateGuildMission:
        pGuild->OperateGuildMission( pMessage->uchOperateType, pMessage->nValue );
        break;
    case GuildDefine::UpdateGuildVar:
        {
            unsigned short nIndex = 0;
            short nVarValue = 0;
            CenterGuild::GetFormatGuildVar( pMessage->nValue, nIndex, nVarValue );
            pGuild->OperateGuildVar( pMessage->uchOperateType, nIndex, nVarValue );
        }
        break;
    case GuildDefine::UpdateGuildLevel:
        pGuild->ProcessGuildDataUpdate( pMessage->uchChangeType, pMessage->nValue );
        break;
    case GuildDefine::UpdateGuildShopLevel:
        pGuild->OperateGuildShopLevel( pMessage->uchOperateType, pMessage->nValue );
        break;
    case GuildDefine::UpdateGuildSalary:
        pGuild->OperateGuildSalary( pMessage->uchOperateType, pMessage->nValue );
        break;
    default:
        return;
    }
}

void NetEvent::_OnGS2CSMemberDataChangeReq( NetClient* pNetClient, GS2CSMemberDataChangeReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    switch ( pMessage->uchChangeType )
    {
    case GuildDefine::UpdateMemberLevel:
        pGuild->ProcessMemberDataUpdate( pMessage->nPlayerID, GuildDefine::UpdateMemberLevel, pMessage->nValue );
        break;
    case GuildDefine::UpdateMemberOffer:
        pGuild->OperateMemberOffer( pMessage->nPlayerID, pMessage->uchOperateType, pMessage->nValue );
        break;
    case GuildDefine::UpdateMemberActivity:
        pGuild->OperateMemberActivity( pMessage->nPlayerID, pMessage->uchOperateType, pMessage->nValue );
        break;
	case GuildDefine::UpdateMemberCampBattleValue:
		pGuild->ProcessMemberDataUpdate( pMessage->nPlayerID, GuildDefine::UpdateMemberCampBattleValue, pMessage->nValue );
		break;
    default:
        return;
    }
}

void NetEvent::_OnGS2CSGuildLevelUpReq( NetClient* pNetClient, GS2CSGuildLevelUpReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_LevelUp ) )
    { return; }

    int nNewLevel = pGuild->GetLevel() + 1;
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( nNewLevel );
    if ( pSetting == NULL )
    { return; }

    if ( pGuild->GetMoney() < pSetting->GetNeedMoney() )
    { return; }

    if ( pGuild->GetExp() < pSetting->GetNeedExp() )
    { return; }

	if(pGuild->GetMission() < pSetting->GetNeedMission())
	{ return ;}

	pGuild->OperateGuildMission(GuildDefine::OperateSub,pSetting->GetNeedMission());
    pGuild->OperateGuildMoney( GuildDefine::OperateSub, pSetting->GetNeedMoney() ); // 扣钱
    pGuild->OperateGuildExp( GuildDefine::OperateSub, pSetting->GetNeedExp() );     // 扣经验
    pGuild->ProcessGuildDataUpdate( GuildDefine::UpdateGuildLevel, nNewLevel );     // 升级

}

// 捐献帮贡
void NetEvent::_OnGS2CSGuildOfferBuildReq( NetClient* pNetClient, GS2CSGuildOfferBuildReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Build ) )
    { return; }

    GuildMember* pMember = pGuild->GetMember( pMessage->nPlayerID );
    if ( pMember == NULL )
    { return; }

    const GuildConfig::BuildSetting& xSetting = theGuildConfig.GetBuildSetting();
    if ( pMember->GetOffer() < xSetting.GetOffer() )
    { return; }

    // 更新玩家帮贡
    pGuild->OperateMemberOffer( pMember, GuildDefine::OperateSub, xSetting.GetOffer() );
    // 更新玩家经验
    pGuild->ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberExp, xSetting.GetPlayerExp() * pMember->GetLevel() );
    // 更新帮派经验
    pGuild->OperateGuildExp( GuildDefine::OperateAdd, xSetting.GetGuildExp() );
}

// 帮会募集
void NetEvent::_OnGS2CSGuildCollectReq( NetClient* pNetClient, GS2CSGuildCollectReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Collect ) )
    { return; }

    GuildMember* pMember = pGuild->GetMember( pMessage->nPlayerID );
    if ( pMember == NULL )
    { return; }

    const GuildConfig::CollectSetting& xSetting = theGuildConfig.GetCollectSetting();

    // 如果发布的募集令, 奖励双倍

    // 奖励帮会经验
    pGuild->OperateGuildExp( GuildDefine::OperateAdd, xSetting.GetGuildExp() );
    // 奖励帮会金钱
    pGuild->OperateGuildMoney( GuildDefine::OperateAdd, xSetting.GetGuildMoney() );

    // 奖励成员帮贡
    pGuild->OperateMemberOffer( pMember, GuildDefine::OperateAdd, xSetting.GetPlayerOffer() );
    // 奖励成员经验
    pGuild->ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberExp, xSetting.GetPlayerExp() * pMember->GetLevel() );
}

// 帮派弹劾
void NetEvent::_OnGS2CSGuildDelateRequestReq( NetClient* pNetClient, GS2CSGuildDelateRequestReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Delate ) )
    { return; }

    pGuild->ProcessGuildDelateRequest( pMessage->nPlayerID );
}

void NetEvent::_OnGS2CSGuildDelateAgreeAck( NetClient* pNetClient, GS2CSGuildDelateAgreeAck* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    GuildMember* pMember = pGuild->GetMember( pMessage->nPlayerID );
    if ( pMember == NULL )
    { return; }

    GuildDelateInfo& xInfo = pGuild->GetDelateInfo();
    if ( xInfo.GetID() == GuildDefine::InitID )
    { return; }

    xInfo.AddAgreeMember( pMessage->nPlayerID );
}

void NetEvent::_OnGS2CSGuildDonateRequestReq( NetClient* pNetClient, GS2CSGuildDonateRequestReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Donate ) )
    { return; }

    // 发起捐献, 记录一个时间
    pGuild->StartDonateTimer();
    pGuild->SetDonateMoney( 0 );

    // 发送给所有服务器
    CS2GSGuildDonateRequestReq xReq;
    xReq.nGuildID = pMessage->nGuildID;
    theGameServerManager.SendMessageToGameServers( &xReq );
}

void NetEvent::_OnGS2CSGuildDonateAck( NetClient* pNetClient, GS2CSGuildDonateAck* pMessage )
{
    const GuildConfig::DonateSetting& xSetting = theGuildConfig.GetDonateSetting();
    if ( xSetting.GetMoney() == 0 )
    { return; }

    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    int nModulus = pMessage->nMoney / xSetting.GetMoney();

    // 奖励活跃度
    pGuild->OperateMemberActivity( pMessage->nPlayerID, GuildDefine::OperateAdd, nModulus * xSetting.GetActivity() );
    // 奖励帮贡
    pGuild->OperateMemberOffer( pMessage->nPlayerID, GuildDefine::OperateAdd, nModulus * xSetting.GetOffer() );

    // 添加帮会金钱
    pGuild->OperateGuildMoney( GuildDefine::OperateAdd, pMessage->nMoney );

    // 处理金钱最大数
    pGuild->ProcessGuildDataUpdate( GuildDefine::UpdateGuildDonate, pGuild->GetDonateMoney() + pMessage->nMoney );     // 升级
}

void NetEvent::_OnGS2CSGuildAimChangeReq( NetClient* pNetClient, GS2CSGuildAimChangeReq* pMessage )
{
	CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
	if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Aim ) )
	{ return; }

// 	if ( pGuild->CanChangeAim() == false )
// 	{ return; }

	pGuild->ProcessGuildAimChange( pMessage->szAim );
}

void NetEvent::_OnGS2CSGuildQuestReleaseReq( NetClient* pNetClient, GS2CSGuildQuestReleaseReq* pMessage )
{
    const GuildConfig::ReleaseSetting& xSetting = theGuildConfig.GetReleaseSetting();
    const GuildConfig::ReleaseSetting::QuestSetting* pSetting = xSetting.GetQuestSetting( pMessage->nQuestType );
    if ( pSetting == NULL )
    { return; }

    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Release ) )
    { return; }

    if ( pGuild->GetReleaseQuest() != 0 )
    { return; }

    if ( pGuild->GetLevel() < xSetting.GetMinLevel() )
    { return; }

    static SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );

    // 判断发布时间
    if ( pGuild->GetReleaseTime() != 0 )
    {
        TimeEx xReleaseTime( pGuild->GetReleaseTime() );
        if ( xSystemTime.wDay == xReleaseTime.GetDay() && xSystemTime.wMonth == xReleaseTime.GetMonth() )   // 判断同一天
        { return; }
    }

    if ( xSystemTime.wHour >= xSetting.GetReleaseTime() )
    { return; }

    if ( pGuild->GetMoney() < pSetting->GetCostMoney() )
    { return; }

    pGuild->ProcessQuestRelease( pMessage->nQuestType, TimeEx::GetNowTime() );

    // 帮派扣钱
    pGuild->OperateGuildMoney( GuildDefine::OperateSub, pSetting->GetCostMoney() );
}

void NetEvent::_OnGS2CSGuildMessage( NetClient* pNetClient, GS2CSGuildMessage* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL )
    { return; }

    pGuild->SendMessageToGuild( reinterpret_cast< Msg* >( pMessage->szMessage ), pMessage->nExceptID, pMessage->ustLevel );
}

void NetEvent::_OnGS2CSGuildConveneReq( NetClient* pNetClient, GS2CSGuildConveneReq* pMessage )
{
    CenterGuild* pGuild = theCenterGuildManager.GetGuild( pMessage->nGuildID );
    if ( pGuild == NULL || !pGuild->HaveRight( pMessage->nPlayerID, GuildDefine::Right_Convene ) )
    { return; }

    pGuild->ProcessGuildConveneReq( pMessage->nPlayerID, pMessage->nMapID, pMessage->fPosX, pMessage->fPosY, pMessage->fDir, pMessage->uchLevel );
}

void NetEvent::_OnGS2CSPlayerLvUpToThirtyReq( NetClient* pNetClient, GS2CSPlayerLvUpToThirtyMessage* pMessage )
{
	theCenterGuildManager.SendPlayerLvUpToMaster( pMessage->nPlayerID, pMessage->nPlayerLv ,pMessage->szSpeakName );
}
void NetEvent::_OnGS2CSGuildSQReq( NetClient* pNetClient, GS2CSGuildSQReq* pMessage )
{
	uint32 PlayerID = pMessage->nPlayerID;
	uint32 GuildID = pMessage->nGuildID;
	CenterGuild* pGuild = theCenterGuildManager.GetGuild(GuildID);
	if(!pGuild) return;
	GuildMember* pMaster = pGuild->GetMember(PlayerID);
    if (!pMaster)
		return;
    switch ( pMaster->GetPosition())
    {
    case GuildDefine::Position_Master:    // 家族长
    case GuildDefine::Position_ViceMaster:      // 副帮主
		{
			//发送命令道客户端  全部的申请数据
			pGuild->SendAllRequest(PlayerID);
		}
        break;
    default:
        break;
    }
}
void NetEvent::_OnGS2CSRaiseGuildPlayerItem( NetClient* pNetClient, GS2CSRaiseGuildPlayerItem* pMessage )
{
	//玩家接收邮件
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;

	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        

	// 发信人
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

	// 收件人	
	xReq.mail.owners[EM_ToIndex].charDbId = pMessage->PlayerID;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pMessage->szName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	
	//内容
	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( etext_GuildRaiseContext ) );

	//标题
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_GuildRaiseTitle ) );

	xReq.mail.accessory.type = 1;//2是坐骑,1是物品
	
	memcpy( &xReq.mail.accessory.content,  &pMessage->CItem, sizeof(SCharItem) ); 
	
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
}
void NetEvent::_OnCS2GSGuildBattleSum( NetClient* pNetClient, CS2GSGuildBattleSum* pMessage )
{
	//修改公会的当前的战场进度
    CenterGuild* pGuild = theCenterGuildManager.GetGuild(pMessage->nGuildID);
	if(!pGuild) return;
	//pGuild->SetBattleSum(pMessage->battleSum);
	pGuild->ProcessGuildDataUpdate( GuildDefine::UpdateGuildBattleSum,pMessage->battleSum);//更新数据并且发送命令
}
void NetEvent::_OnGS2CSSetGuildCampBattleValue( NetClient* pNetClient, GS2CSSetGuildCampBattleValue* pMessage )
{
	//给指定玩家设置指定权限 需要进行判断是否可以设置
	//1.判断指定玩家是否为公会会长
	CenterGuild* pGuild = theCenterGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild || !pGuild->IsMaster(pMessage->PlayerID))
	{
		return;
	}
	//2.目标是否为公会会员
	GuildMember * pMember = pGuild->GetMember(pMessage->TargetID);
	if(!pMember)
	{
		return;
	}
	//3.目标是否已有权限	
	if((pMember->GetCampBattleValue() & pMessage->CampBattleValue) == pMessage->IsAdd)
	{
		return;
	}
	if(!pMessage->IsAdd)
	{
		//移除权限 不需要判断太多.
		unsigned int value = pMember->GetCampBattleValue() ^ pMessage->CampBattleValue;
		pGuild->ProcessMemberDataUpdate(pMember,GuildDefine::UpdateMemberCampBattleValue,value);
		return;
	}
	//4.目标等级
	//5.目标职业
	//6.目标帮贡
	//7.权限最大数量
	GuildCampBattleSetting * pSetting = NULL;
	switch(pMessage->CampBattleValue)
	{
	case GuildDefine::CampBattleCountry:
		pSetting  = &theCenterGuildManager.GetCampBattleConfig()->m_CountrySetting;
		break;
	case GuildDefine::CampBattleGuild:
		pSetting  = &theCenterGuildManager.GetCampBattleConfig()->m_GuildSetting;
		break;
	case GuildDefine::CampBattleGuildUnion:
		pSetting  = &theCenterGuildManager.GetCampBattleConfig()->m_GuildUnionSetting;
		break;
	case GuildDefine::GameBattleGuildGeneral:
		pSetting  = &theCenterGuildManager.GetCampBattleConfig()->m_GuildGeneralSetting;
		break;
	}
	if(!pSetting)
		return;
	else if(pSetting->MinLevel > pMember->GetLevel())
	{
		return;
	}
	else if(pSetting->Profession != pMember->GetProfession() && pSetting->Profession != 0)
	{
		return;
	}
	else if(static_cast<unsigned int>(pSetting->Offer) > pMember->GetOffer())
	{
		return;
	}
	else
	{
		int Sum = theCenterGuildManager.GetSumByCampBattleValue(pMessage->GuildID,pMessage->CampBattleValue);
		if(Sum >= pSetting->MaxSum)
		{
			return;
		}
	}
	//8.设置权限 并且广播给所有GameServer 并且发送到Client
	//到处 全部判断完毕 我们需要正式修改这样服务器的数据
	unsigned int value = pMember->GetCampBattleValue() | pMessage->CampBattleValue;
	pGuild->ProcessMemberDataUpdate(pMember,GuildDefine::UpdateMemberCampBattleValue,value);
}
void NetEvent::_OnGS2CSChangeGuildNameReq( NetClient* pNetClient, GS2CSChangeGuildNameReq* pMessage )
{
	CenterGuild* pGuild = theCenterGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild || !pGuild->IsMaster(pMessage->PlayerID))
		return;
	if(strcoll(pGuild->GetName(),pMessage->Name) == 0)
		return;
	if(!pGuild->GetIsCanChangeName())
	{
		MsgChangeGuldNameAck msg;
		msg.GuildID = pMessage->GuildID;
		strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,pMessage->Name);
		msg.IsCanChange = false;
		theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg,pMessage->PlayerID);
		return;
	}
	if( strlen(pMessage->Name) <= 0)
		return;
	else if( strlen(pMessage->Name) > GuildDefine::MaxNameLength  )
		return;
	else if(strchr(pMessage->Name, ' ') != NULL)
		return;
	//发送命令道数据库去 判断当前名称是否可以使用
	if(theCenterGuildManager.CheckGuildName(pMessage->Name))
		return;
	pGuild->ProcessGuildNameChange(pMessage->Name);
	pGuild->ProcessGuildDataUpdate(GuildDefine::UpdateGuildChangeName,0);
}
void NetEvent::_OnGS2CSGuildMemberChangeName( NetClient* pNetClient, GS2CSGuildMemberChangeName* pMessage )
{
	if(!pMessage)
		return;
	//公会有成员发生改名的情况
	CenterGuild* pGuild =  theCenterGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild)
		return;
	GuildMember * pMember  = pGuild->GetMember(pMessage->PlayerID);
	if(!pMember)
		return;
	pMember->SetName(pMessage->szName);
	//改变关系Map里存储的玩家名称的信息


	//将修改后的数据发送到所有的Gamserver去
	CS2GSGuildMemberChangeName msg;
	msg.GuildID = pMessage->GuildID;
	msg.PlayerID = pMessage->PlayerID;
	strcpy_s(msg.szName,sizeof(msg.szName),pMessage->szName);
	//发送给公会的玩家
	theGameServerManager.SendMessageToGameServers( &msg );
}
void NetEvent::_OnGS2CSUpdateGuildCampBattlePoint( NetClient* pNetClient, GS2CSUpdateGuildCampBattlePoint* pMessage )
{
	if(!pMessage)
		return;
	CenterGuild* pGuild =  theCenterGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild)
		return;
	pGuild->ProcessGuildDataUpdate(GuildDefine::UpdateGuildCampBattlePoint,pMessage->Point);
}
void NetEvent::_OnGS2CSUpdateGuildMemberOnLineTime( NetClient* pNetClient, GS2CSUpdateGuildMemberOnLineTime* pMessage )
{
	if(!pMessage)
		return;
	CenterGuild* pGuild =  theCenterGuildManager.GetGuild(pMessage->GuildID);
	if(!pGuild)
		return;
	pGuild->UpdateGuildMemberOnLineTime(pMessage->PlayerID,pMessage->OnLineTime);
}