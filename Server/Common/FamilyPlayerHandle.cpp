#include "GamePlayer.h"
#include "chatcheck.h"
#include "TimeEx.h"
#include "FamilyConfig.h"
#include "FamilyMessage.h"
#include "GameFamily.h"
#include "GameServer.h"
#include "GlobalFunction.h"


bool GamePlayer::ProcessFamilyMsg( Msg* pMsg )
{
	DWORD dwType = pMsg->GetType();

	GAMESERVER_MESSAGE_MAPPING_BEGIN
		GAMESERVER_MESSAGE_HANDLE( MSG_CREATEFAMILYREQ, OnMsgCreateFamilyReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_INVITEFAMILYREQ, OnMsgInviteFamilyReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_INVITEJOINFAMILYACK, OnMsgInviteJoinFamilyAck );
		GAMESERVER_MESSAGE_HANDLE( MSG_JOINFAMILYREQ, OnMsgJoinFamilyReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_REQUESTJOINFAMILYACK, OnMsgRequestJoinFamilyAck );
		GAMESERVER_MESSAGE_HANDLE( MSG_QUITFAMILYREQ, OnMsgQuitFamilyReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_KICKOUTFAMILYREQ, OnMsgKickOutFamilyReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_FAMILYNOTICEREQ, OnMsgFamilyNoticeReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_FAMILYTRANSFERREQ, OnMsgFamilyTransferReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_FAMILYDONATEREQ, OnMsgFamilyDonateReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_FAMILYUPGRADEREQ, OnMsgFamilyUpgradeReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_QUERYFAMILYINFOREQ, OnMsgQueryFamilyInfoReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_FAMILYAIMREQ, OnMsgFamilyAimReq );

	GAMESERVER_MESSAGE_MAPPING_END

	return false;
}

void GamePlayer::OnMsgCreateFamilyReq( Msg* pMsg )
{
	MsgCreateFamilyReq* pReq = static_cast< MsgCreateFamilyReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( HaveFamily() )
	{ return; }

	HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );
	HelperFunc::CheckStringValid( pReq->szAim, sizeof( pReq->szAim ) );

	if ( theChatCheck->CheckStringInLow( pReq->szName ) == false || theChatCheck->CheckStringInLow( pReq->szAim ) == false )
	{
		return SendOperateAckToClient< MsgCreateFamilyAck >( MsgCreateFamilyAck::ECD_ErrorName );
	}

	if ( theGameFamilyManager.CheckFamilyName( pReq->szName ) == false )
	{
		return SendOperateAckToClient< MsgCreateFamilyAck >( MsgCreateFamilyAck::ECD_SaveName );
	}

	const FamilyConfig::FamilyWordsLenLimits temFamilyWordsLenLimits = theFamilyConfig.GetFamilyWordsLenLimits();
	int len = strlen( pReq->szName );
	if ( ( len < temFamilyWordsLenLimits.GetNameLenMin() ) || ( len > temFamilyWordsLenLimits.GetNameLenMax() ) )
	{
		return;
	}

	len = strlen( pReq->szAim );
	if ( ( len < temFamilyWordsLenLimits.GetAimLenMin() ) || ( len > temFamilyWordsLenLimits.GetAimLenMax() ) )
	{
		return;
	}


	GS2CSCreateFamilyReq req;
	HelperFunc::SafeNCpy( req.szFamilyName, pReq->szName, sizeof( req.szFamilyName ) );
	HelperFunc::SafeNCpy( req.szAim, pReq->szAim, sizeof( req.szAim ) );
	req.nTotem = pReq->nTotem;
	req.member.SetID( GetDBCharacterID() );
	req.member.SetName( GetCharName() );
	req.member.SetLevel( GetLevel() );
	req.member.SetProfession( GetProfession() );
	req.member.SetPosition( FamilyDefine::Position_Leader );
	req.member.SetOnline(true);
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::ProcessJoinFamily( GameFamily* pFamily )
{
	if ( NULL == pFamily )
	{ return; }

	SetFamily( pFamily );
	SetFamilyID( pFamily->GetFamilyID() );

	// 给附近玩家广播
	MsgTellJoinFamilyToView tell;
	tell.header.stID     = GetID();
	tell.nFamilyID       = pFamily->GetFamilyID();
	GettheServer().SendMsgToView( &tell, GetID(), true );

	// 发送给客户端加入帮派成功
	SendOperateAckToClient< MsgJoinFamilyAck >( pFamily->IsFamilyLeader( GetDBCharacterID() ) ? MsgJoinFamilyAck::ECD_CreateSuccess : MsgJoinFamilyAck::ECD_JoinSuccess  );
}

void GamePlayer::ProcessLeaveFamily( GameFamily* pFamily, uint8 nType )
{
	SetFamily( NULL );
	SetFamilyID( FamilyDefine::InitFamilyID );

	if ( NULL == pFamily )
	{ return; }

	// 给附近玩家广播
	MsgTellLeaveFamilyToView tell;
	tell.header.stID     = GetID();
	tell.nFamilyID       = pFamily->GetFamilyID();
	GettheServer().SendMsgToView( &tell, GetID(), true );

	if ( nType == FamilyDefine::Enum_Family_Disbanded )
	{
		nType = FamilyDefine::Enum_Leave_Self;
	}
	// 发送给客户端离开帮派
	SendOperateAckToClient< MsgQuitFamilyAck >( nType );
}

unsigned int GamePlayer::GetFamilyID() const
{
	return gCharInfoServer.otherdata.nFamilyID;
}

void GamePlayer::SetFamilyID( unsigned int nFamilyID )
{
	gCharInfoServer.otherdata.nFamilyID = nFamilyID;
}

void GamePlayer::InitPlayerFamily()
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( GetFamilyID() );
	if ( pFamily == NULL )
	{ 
		// 遍历所有家族
		pFamily = theGameFamilyManager.GetFamilyByPlayerID( GetDBCharacterID() );
		if ( pFamily == NULL )
		{
			SetFamily( NULL );   
			SetFamilyID( FamilyDefine::InitFamilyID );
			return;
		}

		SetFamilyID( pFamily->GetFamilyID() );
	}

	FamilyDefine::FamilyMember* pMember = pFamily->GetMemberByID( GetDBCharacterID() );
	if ( pMember == NULL )
	{
		SetFamily( NULL );   
		SetFamilyID( FamilyDefine::InitFamilyID );
		return;
	}

	SetFamily( pFamily );
}

void GamePlayer::OnMsgInviteFamilyReq( Msg* pMsg )
{
	MsgInviteFamilyReq* pReq = static_cast< MsgInviteFamilyReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	HelperFunc::CheckStringValid( pReq->szPlayerName,sizeof( pReq->szPlayerName ) );

	if ( NULL == m_pFamily )
	{
		return SendOperateAckToClient< MsgInviteFamilyAck >( MsgInviteFamilyAck::ECD_NotHaveFamily );
	}

	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_Invite ) == false )
	{
		return SendOperateAckToClient< MsgInviteFamilyAck >( MsgInviteFamilyAck::ECD_NotHaveRight );
	}

	const FamilyConfig::AttrSetting* pAttrSetting = theFamilyConfig.GetAttrSettingByLevel( m_pFamily->GetFamilyLevel() );
	if ( pAttrSetting == NULL ||  m_pFamily->GetMemberCount() >= pAttrSetting->GetMemberCountLimit() )
	{
		return SendOperateAckToClient< MsgInviteFamilyAck >( MsgInviteFamilyAck::ECD_MemberFull );
	}

	GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pReq->szPlayerName );
	if ( pRelation == NULL || !pRelation->GetOnLine() )
	{
		return SendOperateAckToClient< MsgInviteFamilyAck >( MsgInviteFamilyAck::ECD_NotOnLine );
	}

	if ( theGameFamilyManager.GetFamilyByPlayerID(  pRelation->GetID() ) )
	{
		return SendOperateAckToClient< MsgInviteFamilyAck >( MsgInviteFamilyAck::ECD_AlreadyHaveFamily );
	}

	// 判断对方等级
	if ( pRelation->GetLevel() < theFamilyConfig.GetJoinSetting().GetLevelLimit() )
	{
		return SendOperateAckToClient< MsgInviteFamilyAck >( MsgInviteFamilyAck::ECD_LevelLess );
	}

	GS2CSInviteFamilyReq req;
	req.nInviterID = GetDBCharacterID();
	req.nInviteeID = pRelation->GetID();
	req.nFamilyID = m_pFamily->GetFamilyID();
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgInviteJoinFamilyAck( Msg* pMsg )
{
	MsgInviteJoinFamilyAck* pAck = static_cast< MsgInviteJoinFamilyAck* >(pMsg);
	if ( NULL == pAck )
	{ return; }

	GS2CSInviteJoinFamilyAck ack;
	ack.bAgree = pAck->bAgreeJoin;
	ack.member.SetID( GetDBCharacterID() );
	ack.member.SetLevel( GetLevel() );
	ack.member.SetName( GetCharName() );
	ack.member.SetFamilyID( pAck->nFamilyID );
	ack.member.SetOnline(true);
	ack.member.SetProfession( GetProfession() );
	ack.member.SetPosition( FamilyDefine::Position_Member );
	GettheServer().SendMsgToCenterServer( &ack );
}

void GamePlayer::OnMsgJoinFamilyReq( Msg* pMsg )
{
	MsgJoinFamilyReq* pReq = static_cast< MsgJoinFamilyReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( m_pFamily )
	{
		return SendOperateAckToClient< MsgJoinFamilyAck >( MsgJoinFamilyAck::ECD_AlreadyHaveFamily );
	}

	// 等级限制
	if ( GetLevel() < theFamilyConfig.GetJoinSetting().GetLevelLimit() )
	{
		return SendOperateAckToClient< MsgJoinFamilyAck >( MsgJoinFamilyAck::ECD_LevelLess );
	}

	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pReq->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	GS2CSJoinFamilyReq req;
	req.member.SetID( GetDBCharacterID() );
	req.member.SetLevel( GetLevel() );
	req.member.SetName( GetCharName() );
	req.member.SetProfession( GetProfession() );
	req.member.SetFamilyID( pReq->nFamilyID );
	req.member.SetOnline(true);
	req.member.SetPosition( FamilyDefine::Position_Member );
	HelperFunc::SafeNCpy( req.szNote, pReq->szNote, sizeof( req.szNote ) );
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgRequestJoinFamilyAck( Msg* pMsg )
{
	MsgRequestJoinFamilyAck* pAck = static_cast< MsgRequestJoinFamilyAck* >(pMsg);
	if ( NULL == pAck )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	const FamilyConfig::AttrSetting* pSetting = theFamilyConfig.GetAttrSettingByLevel( m_pFamily->GetFamilyLevel() );
	if ( NULL == pSetting || m_pFamily->GetMemberCount() >= pSetting->GetMemberCountLimit() )
	{ return; }

	GS2CSRequestJoinFamilyAck ack;
	ack.nRequesterID = pAck->nPlayerID;
	ack.nRequesteeID = GetDBCharacterID();
	ack.nFamilyID = m_pFamily->GetFamilyID();
	ack.bAgreeJoin = pAck->bAgreeJoin;
	GettheServer().SendMsgToCenterServer( &ack );
}

void GamePlayer::OnMsgQuitFamilyReq( Msg* pMsg )
{
	MsgQuitFamilyReq* pReq = static_cast< MsgQuitFamilyReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_Leave ) == false )
	{ return; }

	GS2CSQuitFamilyReq req;
	req.nRequesterID = GetDBCharacterID();
	req.nFamilyID = m_pFamily->GetFamilyID();
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgKickOutFamilyReq( Msg* pMsg )
{
	MsgKickOutFamilyReq* pReq = static_cast< MsgKickOutFamilyReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_Kick ) == false )
	{ return; }

	GS2CSKickOutFamilyReq req;
	req.nRequesterID = GetDBCharacterID();
	req.nTargetPlayerID = pReq->nTargetPlayerID;
	req.nFamilyID = m_pFamily->GetFamilyID();
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgFamilyNoticeReq( Msg* pMsg )
{
	MsgFamilyNoticeReq* pReq = static_cast< MsgFamilyNoticeReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_LeaveMsg ) == false )
	{ return; }

	HelperFunc::CheckStringValid( pReq->szNotice, sizeof( pReq->szNotice ) );

	if ( theChatCheck->CheckStringInLow( pReq->szNotice ) == false)
	{
		return SendOperateAckToClient< MsgFamilyNoticeAck >( MsgFamilyNoticeAck::ECD_ErrorNotice );
	}

	GS2CSFamilyNoticeReq req;
	req.nFamilyID = m_pFamily->GetFamilyID();
	req.nRequesterID = GetDBCharacterID();
	HelperFunc::SafeNCpy( req.szNotice, pReq->szNotice, sizeof( req.szNotice ) );
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgFamilyAimReq( Msg* pMsg )
{
	MsgFamilyAimReq* pReq = static_cast< MsgFamilyAimReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_LeaveMsg ) == false )
	{ return; }

	HelperFunc::CheckStringValid( pReq->szAim, sizeof( pReq->szAim ) );

	if ( theChatCheck->CheckStringInLow( pReq->szAim ) == false)
	{
		return SendOperateAckToClient< MsgFamilyAimAck >( MsgFamilyAimAck::ECD_ErrorAim );
	}

	unsigned int nTime = m_pFamily->GetLastChangeAimTime();
	if ( !TimeEx::IsPassCurrentTime( nTime, theFamilyConfig.GetChangeAimSetting().GetChangeAimCD() ) )
	{// 一周之内只能更新一次宗旨
		return SendOperateAckToClient< MsgFamilyAimAck >( MsgFamilyAimAck::ECD_TimeLimit );
	}

	GS2CSFamilyAimReq req;
	req.nFamilyID = m_pFamily->GetFamilyID();
	req.nRequesterID = GetDBCharacterID();
	HelperFunc::SafeNCpy( req.szAim, pReq->szAim, sizeof( req.szAim ) );
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgFamilyTransferReq( Msg* pMsg )
{
	MsgFamilyTransferReq* pReq = static_cast< MsgFamilyTransferReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	// 没有转让权限
	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_Transfer ) == false )
	{ return SendOperateAckToClient< MsgFamilyTransferAck >( MsgFamilyTransferAck::ECD_NoRight); }

	// 目标不存在或者离线
	if ( m_pFamily->GetMemberByID( pReq->nTargetPlayerID ) == NULL )
	{ return SendOperateAckToClient< MsgFamilyTransferAck >( MsgFamilyTransferAck::ECD_TargetNull); }

	GS2CSFamilyTransferReq req;
	req.nFamilyID = m_pFamily->GetFamilyID();
	req.nRequesterID = GetDBCharacterID();
	req.nTargetPlayerID = pReq->nTargetPlayerID;
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgFamilyDonateReq( Msg* pMsg )
{
	MsgFamilyDonateReq* pReq = static_cast< MsgFamilyDonateReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( pReq->nMoney <= 0 )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	if ( pReq->nMoney > FamilyDefine::MaxFamilyMoney - m_pFamily->GetMoney() )
	{
		return SendOperateAckToClient< MsgFamilyDonateAck >( MsgFamilyDonateAck::ECD_MaxFamilyMoney );
	}

	if ( pReq->nMoney > GetMoney() )
	{
		return SendOperateAckToClient< MsgFamilyDonateAck >( MsgFamilyDonateAck::ECD_NoEnoughMoney );
	}

	OperateMoney( EOT_Sub, pReq->nMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_FamilyDonate);

	GS2CSFamilyDonateReq req;
	req.nFamilyID = m_pFamily->GetFamilyID();
	req.nRequesterID = GetDBCharacterID();
	req.nMoney = pReq->nMoney;
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgFamilyUpgradeReq( Msg* pMsg )
{
	MsgFamilyUpgradeReq* pReq = static_cast< MsgFamilyUpgradeReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	if ( NULL == m_pFamily )
	{ return; }

	if ( m_pFamily->HaveRight( GetDBCharacterID(), FamilyDefine::Right_LevelUp ) == false )
	{ return; }

	const FamilyConfig::AttrSetting* pSetting = theFamilyConfig.GetAttrSettingByLevel( m_pFamily->GetFamilyLevel() + 1 );
	if ( NULL == pSetting || m_pFamily->GetMoney() < pSetting->GetCostMoney() || m_pFamily->GetProsperity() < pSetting->GetProsperityNeed() )
	{
		return SendOperateAckToClient< MsgFamilyUpgradeAck >( MsgFamilyUpgradeAck::ECD_UpgradeError );
	}

	GS2CSFamilyUpgradeReq req;
	req.nFamilyID = m_pFamily->GetFamilyID();
	req.nRequesterID = GetDBCharacterID();
	GettheServer().SendMsgToCenterServer( &req );
}

void GamePlayer::OnMsgQueryFamilyInfoReq( Msg* pMsg )
{
	MsgQueryFamilyInfoReq* pReq = static_cast< MsgQueryFamilyInfoReq* >(pMsg);
	if ( NULL == pReq )
	{ return; }

	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pReq->nFamilyID );
	if (  NULL == pFamily )
	{ return; }

	pFamily->SendFamilyInfoToClient( GetDBCharacterID() );
}
