#include "NetEvent.h"
#include "GameServerManager.h"
#include "FamilyManager.h"
#include "MySqlCommunication.h"
#include "TimeEx.h"
#include "FamilyConfig.h"
#include "CenterFamily.h"


long NetEvent::OnProcessFamilyMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE( GS2CS_CREATEFAMILYREQ, GS2CSCreateFamilyReq, _OnGS2CSCreateFamilyReq );
		MESSAGE_HANDLE( GS2CS_INVITEFAMILYREQ, GS2CSInviteFamilyReq, _OnGS2CSInviteFamilyReq );
		MESSAGE_HANDLE( GS2CS_INVITEJOINFAMILYACK, GS2CSInviteJoinFamilyAck, _OnGS2CSInviteJoinFamilyAck );
		MESSAGE_HANDLE( GS2CS_JOINFAMILYREQ, GS2CSJoinFamilyReq, _OnGS2CSJoinFamilyReq );
		MESSAGE_HANDLE( GS2CS_REQUESTJOINFAMILYACK, GS2CSRequestJoinFamilyAck, _OnGS2CSRequestJoinFamilyAck );
		MESSAGE_HANDLE( GS2CS_QUITFAMILYREQ, GS2CSQuitFamilyReq, _OnGS2CSQuitFamilyReq );
		MESSAGE_HANDLE( GS2CS_KICKOUTFAMILYREQ, GS2CSKickOutFamilyReq, _OnGS2CS_KickOutFamilyReq );
		MESSAGE_HANDLE( GS2CS_FAMILYNOTICEREQ, GS2CSFamilyNoticeReq, _OnGS2CS_FamilyNoticeReq );
		MESSAGE_HANDLE( GS2CS_FAMILYTRANSFERREQ, GS2CSFamilyTransferReq, _OnGS2CSFamilyTransferReq );
		MESSAGE_HANDLE( GS2CS_FAMILYDONATEREQ, GS2CSFamilyDonateReq, _OnGS2CSFamilyDonateReq );
		MESSAGE_HANDLE( GS2CS_FAMILYUPGRADEREQ, GS2CSFamilyUpgradeReq, _OnGS2CSFamilyUpgradeReq );
		MESSAGE_HANDLE( GS2CS_TELLMEMBEROFFLINE, GS2CSTellMemberOffline, _OnGS2CSTellMemberOffline );
		MESSAGE_HANDLE( GS2CS_FAMILYPLAYERLVTOTEN, GS2CSFamilyPlayerLvUpToTenMessage, _OnGS2CSFamilyPlayerLvToTen );
		MESSAGE_HANDLE( GS2CS_FAMILYMEMBERDATACHANGEREQ, GS2CSFamilyMemberDataChangeReq, _OnGS2CSFamilyMemberDataChangeReq );
		MESSAGE_HANDLE_NOTCHECK( GS2CS_FAMILYMESSAGE, GS2CSFamilyMessage, _OnGS2CSFamilyMessage );
		MESSAGE_HANDLE( GS2CS_FAMILYPROSPERITYUPDATE, GS2CSFamilyProsperityUpdate, _OnGS2CSFamilyProsperityUpdate );
		MESSAGE_HANDLE( GS2CS_FAMILYAIMREQ, GS2CSFamilyAimReq, _OnGS2CS_FamilyAimReq );


	MESSAGE_MAPPING_END

	return ER_Success;
}

void NetEvent::_OnGS2CSCreateFamilyReq( NetClient* pNetClient, GS2CSCreateFamilyReq* pMessage )
{

	__int64 nTime = theCenterFamilyManager.GetLeaveFamilyTime( pMessage->member.GetID() );
	if ( nTime != 0 && !TimeEx::IsPassCurrentTime( nTime , theFamilyConfig.GetMemberLeaveSetting().GetLeaveSettingTime() * OneHourMicroSecond ) )
	{//	退家族后24小时之内不得创建家族
		MsgJoinFamilyAck ack;
		ack.uchResult = MsgJoinFamilyAck::ECD_TimeLimit;
		return theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->member.GetID() );
	}

	// 创建家族
	CenterFamily* pFamily = CenterFamily::CreateFamily();
	if ( NULL == pFamily )
	{ return; }

	pFamily->SetFamilyID( theCenterFamilyManager.MakeFamilyID() );
	pFamily->SetFamilyName( pMessage->szFamilyName );
	pFamily->SetFamilyAim( pMessage->szAim );
	pFamily->SetFamilyTotem( pMessage->nTotem );
	pFamily->SetLeaderID( pMessage->member.GetID() );
	pFamily->SetFamilyLevel( 1 );
	pFamily->SetMoney( 0 );
	pFamily->SetProsperity( 0 );

	// 添加到管理器
	theCenterFamilyManager.AddFamily( pFamily );

	// 同步gameserver
	CS2GSCreateFamilyAck ack;
	ack.familyInfo = *pFamily;
	HelperFunc::SafeNCpy( ack.szPlayer, pMessage->member.GetName(), sizeof( ack.szPlayer ) );
	theGameServerManager.SendMessageToGameServers( &ack );

	// 添加成员
	pMessage->member.SetFamilyID( pFamily->GetFamilyID() );
	pFamily->AddMember( pMessage->member );
	pFamily->ProcessMemberJoinFamily( pMessage->member );

	// 如果玩家是当天第一次上线
	if ( pMessage->member.GetbFirstEnterWorld() )
	{
		pMessage->member.SetbFirstEnterWorld( false );
		pFamily->AddMember( pMessage->member );
		pFamily->OperateProsperity( FamilyDefine::OperateAdd, theFamilyConfig.GetProsperitySetting().GetProsPerDay() );
	}

	//入库
	pFamily->SaveFamilyDataToDatabase();
}

void NetEvent::_OnGS2CSInviteFamilyReq( NetClient* pNetClient, GS2CSInviteFamilyReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily || !pFamily->HaveRight( pMessage->nInviterID, FamilyDefine::Right_Invite ) )
	{ return; }

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( pMessage->nInviterID );
	if ( NULL == pMember )
	{ return; }

	const FamilyConfig::AttrSetting* pAttrSetting = theFamilyConfig.GetAttrSettingByLevel( pFamily->GetFamilyLevel() );
	if ( NULL == pAttrSetting )
	{ return; }

	if ( pFamily->GetMemberCount() >= pAttrSetting->GetMemberCountLimit() )
	{ return; }

	__int64 nTime= pFamily->GetMemberLeaveRecord( pMessage->nInviteeID );
	if ( nTime != 0 && !TimeEx::IsPassCurrentTime( nTime , theFamilyConfig.GetMemberLeaveSetting().GetLeaveSettingTime() * OneHourMicroSecond ) )
	{//	退家族后24小时之内不得再次加入
		MsgJoinFamilyAck ack;
		ack.uchResult = MsgJoinFamilyAck::ECD_TimeLimit;
		return theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->nInviterID );
	}

	// 成功发出邀请
	MsgInviteFamilyAck ack;
	ack.uchResult = MsgInviteFamilyAck::ECD_Success;
	theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->nInviterID );

	MsgInviteJoinFamilyReq req;
	req.nFamilyID = pFamily->GetFamilyID();
	HelperFunc::SafeNCpy( req.szInviterName, pMember->GetName(), sizeof(req.szInviterName) );
	theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &req, pMessage->nInviteeID );

	pFamily->AddInviteRecord( pMessage->nInviterID, pMessage->nInviteeID, HQ_TimeGetTime() );
}

void NetEvent::_OnGS2CSInviteJoinFamilyAck( NetClient* pNetClient, GS2CSInviteJoinFamilyAck* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->member.GetFamilyID() );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyInvite* pInvite = pFamily->GetInviteRecord( pMessage->member.GetID() );
	if ( NULL == pInvite )
	{ return; }

	unsigned int nInviterID = pInvite->GetInviterID();
	pFamily->RemoveInviteRecord( pInvite->GetInviteeID() );

	// 申请人是否有家族
	if ( theCenterFamilyManager.GetFamilyByPlayerID( pMessage->member.GetID() ) )
	{ return; }

	if ( pMessage->bAgree == false )
	{// 不同意,通知邀请人
		MsgInviteFamilyAck ack;
		ack.uchResult = MsgInviteFamilyAck::ECD_NotAgree;
		theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, nInviterID );
		return;
	}

	// 判断被邀请人是否有家族
	if ( theCenterFamilyManager.GetFamilyByPlayerID( pMessage->member.GetID() ) )
	{ return; }

	// 判断家族人数上限
	const FamilyConfig::AttrSetting* pSetting = theFamilyConfig.GetAttrSettingByLevel( pFamily->GetFamilyLevel() );
	if ( NULL == pSetting || pFamily->GetMemberCount() >= pSetting->GetMemberCountLimit() )
	{ return; }


	pFamily->AddMember( pMessage->member );
	pFamily->ProcessMemberJoinFamily( pMessage->member );

	// 如果玩家是当天第一次上线
	if ( pMessage->member.GetbFirstEnterWorld() )
	{
		pMessage->member.SetbFirstEnterWorld( false );
		pFamily->AddMember( pMessage->member );
		pFamily->OperateProsperity( FamilyDefine::OperateAdd, theFamilyConfig.GetProsperitySetting().GetProsPerDay() );
	}

}

void NetEvent::_OnGS2CSJoinFamilyReq( NetClient* pNetClient, GS2CSJoinFamilyReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->member.GetFamilyID() );
	if ( NULL == pFamily )
	{ return; }

	if ( theCenterFamilyManager.GetFamilyByPlayerID( pMessage->member.GetID() ) )
	{ return; }

	__int64 nTime = pFamily->GetMemberLeaveRecord( pMessage->member.GetID() );
	if ( nTime != 0 && !TimeEx::IsPassCurrentTime( nTime, theFamilyConfig.GetMemberLeaveSetting().GetLeaveSettingTime() * OneHourMicroSecond ) )
	{//	退家族后24小时之内不得再次加入
		MsgJoinFamilyAck ack;
		ack.uchResult = MsgJoinFamilyAck::ECD_TimeLimit;
		return theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->member.GetID() );
	}

	// 人数上限
	const FamilyConfig::AttrSetting* pSetting = theFamilyConfig.GetAttrSettingByLevel( pFamily->GetFamilyLevel() );
	if ( NULL == pSetting || pFamily->GetMemberCount() >= pSetting->GetMemberCountLimit() )
	{ 		
		MsgJoinFamilyAck ack;
		ack.uchResult = MsgJoinFamilyAck::ECD_MemberFull;
		return theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->member.GetID() ); 
	}

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( pFamily->GetLeaderID() );
	if ( pMember == NULL )
	{
		return;
	}

	if ( pMember->GetOnLine() == false )
	{// 家族长不在线
		MsgJoinFamilyAck ack;
		ack.uchResult = MsgJoinFamilyAck::ECD_NotOnLine;
		return theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->member.GetID() );
	}

	MsgRequestJoinFamilyReq req;
	req.nRequesterID = pMessage->member.GetID();
	HelperFunc::SafeNCpy( req.szRequesterName, pMessage->member.GetName(), sizeof(req.szRequesterName) );
	HelperFunc::SafeNCpy( req.szNote, pMessage->szNote, sizeof(req.szNote) );
	theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &req, pMember->GetID() );

	pFamily->AddRequestRecord( pMessage->member, HQ_TimeGetTime() );
}

void NetEvent::_OnGS2CSRequestJoinFamilyAck( NetClient* pNetClient, GS2CSRequestJoinFamilyAck* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyRequest* pRequest = pFamily->GetRequestRecord( pMessage->nRequesterID );
	if ( NULL == pRequest )
	{ return; }

	FamilyDefine::FamilyRequest request = *pRequest;
	pFamily->RemoveRequestRecord( pMessage->nRequesterID );

	if ( pFamily->HaveRight( pMessage->nRequesteeID, FamilyDefine::Right_Accept ) == false )
	{ return; }

	// 人数上限
	const FamilyConfig::AttrSetting* pSetting = theFamilyConfig.GetAttrSettingByLevel( pFamily->GetFamilyLevel() );
	if ( NULL == pSetting || pFamily->GetMemberCount() >= pSetting->GetMemberCountLimit() )
	{ return; }

	if ( !pMessage->bAgreeJoin )
	{// 不同意
		MsgJoinFamilyAck ack;
		ack.uchResult = MsgJoinFamilyAck::ECD_NotAgree;
		theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &ack, pMessage->nRequesterID );
        return;
	}

	pFamily->AddMember( request.GetMember() );
	pFamily->ProcessMemberJoinFamily( request.GetMember() );

	// 如果玩家是当天第一次上线
	FamilyDefine::FamilyMember fMember = request.GetMember();
	if ( fMember.GetbFirstEnterWorld() )
	{
		fMember.SetbFirstEnterWorld( false );
		pFamily->AddMember( fMember );
		pFamily->OperateProsperity( FamilyDefine::OperateAdd, theFamilyConfig.GetProsperitySetting().GetProsPerDay() );
	}


}

void NetEvent::_OnGS2CSQuitFamilyReq( NetClient* pNetClient, GS2CSQuitFamilyReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	if ( pFamily->HaveRight( pMessage->nRequesterID, FamilyDefine::Right_Leave ) == false )
	{ return; }

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( pMessage->nRequesterID );
	if ( NULL == pMember )
	{ return; }

	// 保存到记录中
	pFamily->AddMemberLeaveRecord( pMessage->nRequesterID, TimeEx::GetNowTime() );

	FamilyDefine::FamilyMember member = *pMember;
	pFamily->RemoveMember( pMessage->nRequesterID );
	pFamily->ProcessMemberLeaveFamily( member , FamilyDefine::Enum_Leave_Self );
}

void NetEvent::_OnGS2CS_KickOutFamilyReq( NetClient* pNetClient, GS2CSKickOutFamilyReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( pMessage->nTargetPlayerID );
	if ( NULL == pMember )
	{ return; }

	if ( pFamily->HaveRight( pMessage->nRequesterID, FamilyDefine::Right_Kick ) == false )
	{ return; }

	// 保存到记录中
	pFamily->AddMemberLeaveRecord( pMessage->nTargetPlayerID, TimeEx::GetNowTime() );

	FamilyDefine::FamilyMember member = *pMember;
	pFamily->RemoveMember( member.GetID() );
	pFamily->ProcessMemberLeaveFamily( member, FamilyDefine::Enum_Leave_Kicked );
}

void NetEvent::_OnGS2CS_FamilyNoticeReq( NetClient* pNetClient, GS2CSFamilyNoticeReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	if ( pFamily->HaveRight( pMessage->nRequesterID, FamilyDefine::Right_LeaveMsg ) == false )
	{ return; }

	pFamily->SetFamilyNotice( pMessage->szNotice );
	pFamily->ProcessUpdateFamilyNotice();
}

void NetEvent::_OnGS2CS_FamilyAimReq( NetClient* pNetClient, GS2CSFamilyAimReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	if ( pFamily->HaveRight( pMessage->nRequesterID, FamilyDefine::Right_LeaveMsg ) == false )
	{ return; }

	int64 nTime = pFamily->GetLastChangeAimTime();
	if ( !TimeEx::IsPassCurrentTime( nTime, theFamilyConfig.GetChangeAimSetting().GetChangeAimCD() ) )
	{
		return;
	}

	pFamily->SetLastChangeAimTime( TimeEx::GetNowTime() );
	pFamily->SetFamilyAim( pMessage->szAim );
	pFamily->ProcessUpdateFamilyAim();
}


void NetEvent::_OnGS2CSFamilyTransferReq( NetClient* pNetClient, GS2CSFamilyTransferReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	if ( pFamily->HaveRight( pMessage->nRequesterID, FamilyDefine::Right_LeaveMsg ) == false )
	{ return; }

	FamilyDefine::FamilyMember* pRequester = pFamily->GetMemberByID( pMessage->nRequesterID );
	if ( NULL == pRequester )
	{ return; }

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( pMessage->nTargetPlayerID );
	if ( NULL == pMember )
	{ return; }


	pMember->SetPosition( pRequester->GetPosition() );
	pRequester->SetPosition( FamilyDefine::Position_Member );
	pFamily->ProcessTransferPosition( *pRequester, *pMember );	

	// 通知转让成功
	MsgFamilyTransferAck xAck;
	xAck.uchResult = MsgFamilyTransferAck::ECD_Success;
	theGameServerManager.SendMsgToSingleRemote( FamilyDefine::InitFamilyID, &xAck, pMessage->nRequesterID );
}

void NetEvent::_OnGS2CSFamilyDonateReq( NetClient* pNetClient, GS2CSFamilyDonateReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pRequester = pFamily->GetMemberByID( pMessage->nRequesterID );
	if ( NULL == pRequester )
	{ return; }

	pFamily->ProcessDonate( *pRequester, pMessage->nMoney );
	pFamily->ProcessMemberDataUpdate( pRequester, FamilyDefine::UpdateMemberDonateMoney, pRequester->GetDonateMoney() );
}

void NetEvent::_OnGS2CSFamilyUpgradeReq( NetClient* pNetClient, GS2CSFamilyUpgradeReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pRequester = pFamily->GetMemberByID( pMessage->nRequesterID );
	if ( NULL == pRequester )
	{ return; }

	if ( pFamily->HaveRight( pMessage->nRequesterID, FamilyDefine::Right_LevelUp ) == false )
	{ return; }

	const FamilyConfig::AttrSetting* pSetting = theFamilyConfig.GetAttrSettingByLevel( pFamily->GetFamilyLevel() + 1 );
	if ( NULL == pSetting || pFamily->GetMoney() < pSetting->GetCostMoney() || pFamily->GetProsperity() < pSetting->GetProsperityNeed() )
	{ return; }

	pFamily->SetMoney( pFamily->GetMoney() - pSetting->GetCostMoney() );
	pFamily->SetProsperity( pFamily->GetProsperity() - pSetting->GetProsperityNeed() );
	pFamily->SetFamilyLevel( pFamily->GetFamilyLevel() + 1 );
	pFamily->ProcessUpgrade( *pRequester );
}

void NetEvent::_OnGS2CSTellMemberOffline( NetClient* pNetClient, GS2CSTellMemberOffline* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( pMessage->nPlayerID );
	if ( NULL == pMember || pMember->GetOnLine() == false )
	{ return; }

	pFamily->ProcessMemberOffline( *pMember );
}

void NetEvent::_OnGS2CSFamilyPlayerLvToTen( NetClient* pNetClient, GS2CSFamilyPlayerLvUpToTenMessage* pMessage )
{
	theCenterFamilyManager.SendPlayerLvUpToMaster( pMessage->nPlayerID, pMessage->nPlayerLv ,pMessage->szSpeakName );
}

void NetEvent::_OnGS2CSFamilyMemberDataChangeReq( NetClient* pNetClient, GS2CSFamilyMemberDataChangeReq* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( pFamily == NULL )
	{ return; }

	pFamily->ProcessMemberDataUpdate( pMessage->nPlayerID, pMessage->uchChangeType, pMessage->nValue );

}

void NetEvent::_OnGS2CSFamilyMessage( NetClient* pNetClient, GS2CSFamilyMessage* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( pFamily == NULL )
	{ return; }

	pFamily->SendMessageToFamily( reinterpret_cast< Msg* >( pMessage->szMessage ), pMessage->nExceptID, pMessage->nLevel, false );
}

void NetEvent::_OnGS2CSFamilyProsperityUpdate( NetClient* pNetClient, GS2CSFamilyProsperityUpdate* pMessage )
{
	CenterFamily* pFamily = theCenterFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( pFamily == NULL )
	{ return; }

	pFamily->SetProsperity( pMessage->nProsperity );

	CS2GSFamilyProsperityUpdate xUpdate;
	xUpdate.nFamilyID = pMessage->nFamilyID;
	xUpdate.nProsperity = pMessage->nProsperity;
	theGameServerManager.SendMessageToGameServers( &xUpdate );
}