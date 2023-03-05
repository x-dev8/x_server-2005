#include "CenterServerNetEvent.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "FamilyConfig.h"
#include "RunStatus.h"
#include "GameFamily.h"
#include "XmlStringLanguage.h"

long CenterServerNetEvent::OnProcessFamilyMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
	MESSAGE_MAPPING_BEGIN
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYDETAIL, CS2GSFamilyDetail, _OnCS2GSFamilyDetail );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_ALLFAMILIESSENDEND, CS2GSAllFamiliesSendEnd, _OnCS2GSAllFamiliesSendEnd );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_CREATEFAMILYACK, CS2GSCreateFamilyAck, _OnCS2GSCreateFamilyAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_JOINFAMILYACK, CS2GSJoinFamilyAck, _OnCS2GSJoinFamilyAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_LEAVEFAMILYACK, CS2GSLeaveFamilyAck, _OnCS2GSLeaveFamilyAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYNOTICEACK, CS2GSFamilyNoticeAck, _OnCS2GSFamilyNoticeAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYTRANSFERACK, CS2GSFamilyTransferAck, _OnCS2GSFamilyTransferAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYDONATEACK, CS2GSFamilyDonateAck, _OnCS2GSFamilyDonateAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYUPGRADEACK, CS2GSFamilyUpgradeAck, _OnCS2GSFamilyUpgradeAck );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_TELLFAMILYDISBAND, CS2GSTellFamilyDisband, _OnCS2GSTellFamilyDisband );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYPLAYERLVTOTEN, GS2CSFamilyPlayerLvUpToTenMessage, _OnCS2GSFamilyPlayerLvToTen );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYMEMBERDATAUPDATE, CS2GSFamilyMemberDataUpdate, _OnCS2GSFamilyMemberDataUpdate );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYMESSAGE, CS2GSFamilyMessage, _OnCS2GSFamilyMessage );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYPROSPERITYUPDATE, CS2GSFamilyProsperityUpdate, _OnCS2GSFamilyProsperityUpdate );
		MESSAGE_HANDLE_NOTCHECK( CS2GS_FAMILYAIMACK, CS2GSFamilyAimAck, _OnCS2GSFamilyAimAck );
	MESSAGE_MAPPING_END

	return ER_Success;
}

void CenterServerNetEvent::_OnCS2GSFamilyDetail( NetClient* pNetClient, CS2GSFamilyDetail* pMessage )
{
	GameFamily* pFamily = GameFamily::CreateFamily();
	if ( NULL == pFamily )
	{ return; }

	pFamily->InitFamilyInfo( pMessage->info );
	theGameFamilyManager.AddFamily( pFamily );

	for ( int i = 0; i < pMessage->nCount; ++i )
	{
		pFamily->AddMember( pMessage->members[i] );
	}
}

void CenterServerNetEvent::_OnCS2GSAllFamiliesSendEnd( NetClient* pNetClient, CS2GSAllFamiliesSendEnd* pMessage )
{
	theGameFamilyManager.SetLoadSuccess(true);
}

void CenterServerNetEvent::_OnCS2GSCreateFamilyAck( NetClient* pNetClient, CS2GSCreateFamilyAck* pMessage )
{
	GameFamily* pFamily = GameFamily::CreateFamily();
	if ( NULL == pFamily )
	{ return; }

	pFamily->InitFamilyInfo( pMessage->familyInfo );
	theGameFamilyManager.AddFamily( pFamily );

	// 全服通告
	MsgTellCreateFamily tell;
	tell.nFamilyID = pFamily->GetFamilyID();
	tell.nFamilyLevel = pFamily->GetFamilyLevel();
	tell.nMemberCount = pFamily->GetMemberCount();
	tell.nProspeprity = pFamily->GetProsperity();
	HelperFunc::SafeNCpy( tell.szPlayer, pMessage->szPlayer, sizeof( tell.szPlayer ) );
	HelperFunc::SafeNCpy( tell.szName, pFamily->GetFamilyName(), sizeof( tell.szName ) );
	GettheServer().SendMsgToWorld( &tell, false );

	GamePlayer* pPlayer = GameFamily::GetPlayer( pFamily->GetLeaderID() );
	if ( NULL == pPlayer )
	{ return; }

	// 扣钱
	pPlayer->OperateMoney( EOT_Sub, theFamilyConfig.GetCreateSetting().GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_CreateFamily);
}

void CenterServerNetEvent::_OnCS2GSJoinFamilyAck( NetClient* pNetClient, CS2GSJoinFamilyAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->member.GetFamilyID() );
	if ( NULL == pFamily )
	{ return; }

	pFamily->AddMember( pMessage->member );
	pFamily->ProcessMemberJoinFamily( pMessage->member );
}

void CenterServerNetEvent::_OnCS2GSLeaveFamilyAck( NetClient* pNetClient, CS2GSLeaveFamilyAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->member.GetFamilyID() );
	if ( NULL == pFamily )
	{ return; }

	pFamily->RemoveMember( pMessage->member.GetID() );
	pFamily->ProcessMemberLeaveFamily( pMessage->member , pMessage->uType );
}

void CenterServerNetEvent::_OnCS2GSFamilyNoticeAck( NetClient* pNetClient, CS2GSFamilyNoticeAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	pFamily->SetFamilyNotice( pMessage->szNotice );
	pFamily->ProcessUpdateFamilyNotice();
}

void CenterServerNetEvent::_OnCS2GSFamilyAimAck( NetClient* pNetClient, CS2GSFamilyAimAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	pFamily->SetFamilyAim( pMessage->szAim );
	pFamily->SetLastChangeAimTime( pMessage->nChangeAimTime );
	pFamily->ProcessUpdateFamilyAim();
}

void CenterServerNetEvent::_OnCS2GSFamilyTransferAck( NetClient* pNetClient, CS2GSFamilyTransferAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pRequester = pFamily->GetMemberByID( pMessage->nRequesterID );
	FamilyDefine::FamilyMember* pTarget = pFamily->GetMemberByID( pMessage->nTargetPlayerID );
	if ( NULL == pRequester || NULL == pTarget )
	{ return; }

	pTarget->SetPosition( pRequester->GetPosition() );
	pRequester->SetPosition( FamilyDefine::Position_Member );
	pFamily->ProcessTransferPosition( *pRequester, *pTarget );
}

void CenterServerNetEvent::_OnCS2GSFamilyDonateAck( NetClient* pNetClient, CS2GSFamilyDonateAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pRequester = pFamily->GetMemberByID( pMessage->nRequesterID );
	if ( NULL == pRequester )
	{ return; }

	pFamily->ProcessDonate( *pRequester, pMessage->nMoney );
}

void CenterServerNetEvent::_OnCS2GSFamilyUpgradeAck( NetClient* pNetClient, CS2GSFamilyUpgradeAck* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( NULL == pFamily )
	{ return; }

	FamilyDefine::FamilyMember* pRequester = pFamily->GetMemberByID( pMessage->nRequesterID );
	if ( NULL == pRequester )
	{ return; }

	pFamily->SetFamilyLevel( pMessage->nNewLevel );
	pFamily->SetMoney( pMessage->nNewMoney );
	pFamily->SetProsperity( pMessage->nNewProsperity );
	pFamily->ProcessUpgrade( *pRequester );
}

void CenterServerNetEvent::_OnCS2GSTellFamilyDisband( NetClient* pNetClient, CS2GSTellFamilyDisband* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( pFamily == NULL )
	{ return; }

	// 处理家族解散
	pFamily->ProcessDisbandFamily();

	// 删除一个家族
	theGameFamilyManager.RemoveFamily( pMessage->nFamilyID );

	MsgTellFamilyDisband tell;
	tell.nFamilyID = pMessage->nFamilyID;
	GettheServer().SendMsgToWorld( &tell, false );

}

void CenterServerNetEvent::_OnCS2GSFamilyPlayerLvToTen( NetClient* pNetClient, GS2CSFamilyPlayerLvUpToTenMessage* pMessage )
{

	GamePlayer* pPlayer = GameFamily::GetPlayer( pMessage->nTargetID);
	if ( pPlayer )
	{
		MsgTellClientCanInvite			msgCanInvite;
		msgCanInvite.nPlayerID = pMessage->nPlayerID;
		msgCanInvite.nPlayerLv = pMessage->nPlayerLv;
		msgCanInvite.opType	   = MsgTellClientCanInvite::Family_Invite;
		HelperFunc::SafeNCpy( msgCanInvite.szPlayerName, pMessage->szSpeakName, sizeof( msgCanInvite.szPlayerName ) );

		pPlayer->SendMessageToClient( &msgCanInvite );
	}	
}

void CenterServerNetEvent::_OnCS2GSFamilyMemberDataUpdate( NetClient* pNetClient, CS2GSFamilyMemberDataUpdate* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	if ( pFamily == NULL )
	{ return; }

	pFamily->ProcessMemberDataUpdate( pMessage->nPlayerID, pMessage->uchUpdateType, pMessage->nUpdateValue );
}

void CenterServerNetEvent::_OnCS2GSFamilyMessage( NetClient* pNetClient, CS2GSFamilyMessage* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );
	
	if ( pFamily == NULL )
	{ return; }

	pFamily->SendMessageToFamily( reinterpret_cast< Msg* >( pMessage->szMessage ), pMessage->nExceptID, pMessage->nLevel, false );
}

void CenterServerNetEvent::_OnCS2GSFamilyProsperityUpdate( NetClient* pNetClient, CS2GSFamilyProsperityUpdate* pMessage )
{
	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( pMessage->nFamilyID );

	if ( pFamily == NULL )
	{ return; }

	pFamily->SetProsperity( pMessage->nProsperity );

	MsgTellClientProsperity xTellClientProsperity;
	xTellClientProsperity.nProsperity = pMessage->nProsperity;
	pFamily->SendMessageToFamily( &xTellClientProsperity );
	
}