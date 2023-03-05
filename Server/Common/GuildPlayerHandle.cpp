#include "GamePlayer.h"
#include "chatcheck.h"
#include "TimeEx.h"
#include "GuildConfig.h"
#include "GuildMessage.h"
#include "GameServer.h"
#include "GlobalFunction.h"
#include "XmlStringLanguage.h"
#include "Raise.h"
#include "ShareData.h"
#include "LogEventService.h"
#include "GameBattleDataManager.h"
bool GamePlayer::ProcessGuildMsg( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_CREATEGUILDREQ, OnMsgCreateGuildReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_LEAVEGUILDREQ, OnMsgLeaveGuildReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_KICKGUILDREQ, OnMsgKickGuildReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_INVITEUILDREQ, OnMsgInviteGuildReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_INVITEJOINGUILDACK, OnMsgInviteJoinGuildAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_REQUESTJOINGUILDACK, OnMsgRequestJoinGuildAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYGUILDATAREQ, OnMsgQueryGuildDataReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDNOTICECHANGEREQ, OnMsgGuildNoticeChangeReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEGUILDAIM, OnMsgChangeGuildAimReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDRESIGNPOSITIONREQ, OnMsgGuildResignPositionReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDTRANSFERPOSITIONREQ, OnMsgGuildTransferPositionReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDCREATEFAMILYREQ, OnMsgGuildCreateFamilyReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDFAMILYCHANGEREQ, OnMsgGuildFamilyChangeReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDMEMBERFAMILYCHANGEREQ, OnMsgGuildMemberFamilyChangeReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDASSIGNPOSITIONREQ, OnMsgGuildAssignPositionReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDDELATEAGREEACK, OnMsgGuildDelateAgreeAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDDONATEACK, OnMsgGuildDonateAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDBUYITEMREQ, OnMsgGuildBuyItemReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDSHOPLEVELUPREQ, OnMsgGuildShopLevelUpReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_JOINGUILDREQ, OnMsgJoinGuildReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_GUILDCONVENTACK, OnMsgGuildConveneAck );
		GAMESERVER_MESSAGE_HANDLE( MSG_SETGUILDCAMPBATTLEVALUE, OnMsgSetGuildCampBattleValue );
		GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEGUILDNAMEREQ, OnMsgChangeGuldNameReq );
    GAMESERVER_MESSAGE_MAPPING_END

    return false;
}


void GamePlayer::OnMsgCreateGuildReq( Msg* pMsg )
{
    MsgCreateGuildReq* pReq = static_cast< MsgCreateGuildReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );

    // �ж��Ƿ��Ѿ��й���
    if ( HaveGuild() )
    {
        return SendOperateAckToClient< MsgCreateGuildAck >( MsgCreateGuildAck::ECD_HaveGuild );
    }

    // �жϵȼ�
    const GuildConfig::CreateSetting& xSetting = theGuildConfig.GetCreateSetting();
    if ( GetLevel() < xSetting.GetLevel() )
    {
        return SendOperateAckToClient< MsgCreateGuildAck >( MsgCreateGuildAck::ECD_LevelLess );
    }
    
    // �ж�����
    if ( /*GetMoney()*/GetJiaoZiMoney() < xSetting.GetCostMoney() )
    {
        return SendOperateAckToClient< MsgCreateGuildAck >( MsgCreateGuildAck::ECD_NotEnoughMoney );
    }

    // ���жϹ����ִ�
    if ( !theChatCheck->CheckStringInLow( pReq->szName ) )
    {
        return SendOperateAckToClient< MsgCreateGuildAck >( MsgCreateGuildAck::ECD_ErrorName );
    }

    // �ж��Ƿ�����
    if ( theGameGuildManager.CheckGuildName( pReq->szName ) )
    {
        return SendOperateAckToClient< MsgCreateGuildAck >( MsgCreateGuildAck::ECD_SaveName );
    }

	if(GetCountry() == CountryDefine::Country_Init)
	{
		return SendOperateAckToClient< MsgCreateGuildAck >( MsgCreateGuildAck::ECD_NotCountry );
	}

    // ���͸�CenterServer
    GS2CSCreateGuildReq xReq;
    xReq.uchCountry = GetCountry();
    HelperFunc::SafeNCpy( xReq.szName, pReq->szName, sizeof( xReq.szName ) );
	HelperFunc::SafeNCpy( xReq.szAim, pReq->szAim, sizeof( xReq.szAim ) );
    xReq.xMember.SetID( GetDBCharacterID() );
    xReq.xMember.SetName( GetCharName() );
    xReq.xMember.SetLevel( GetLevel() );
    xReq.xMember.SetProfession( GetProfession() );
    xReq.xMember.SetPosition( GuildDefine::Position_Master );
    xReq.xMember.SetOnLine( true );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgLeaveGuildReq( Msg* pMsg )
{
    MsgLeaveGuildReq* pReq = static_cast< MsgLeaveGuildReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( m_pGuild == NULL )
    {
        return SendOperateAckToClient< MsgLeaveGuildAck >( MsgLeaveGuildAck::ECD_NotHaveGuild );
    }

    if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Leave ) )
    {
        return SendOperateAckToClient< MsgLeaveGuildAck >( MsgLeaveGuildAck::ECD_NotHaveRight );
    }

    // ֪ͨCenterServer����
    GS2CSLeaveGuildReq xReq;
    xReq.nPlayerID = GetDBCharacterID();
    xReq.nGuildID  = GetGuildID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgKickGuildReq( Msg* pMsg )
{
    MsgKickGuildReq* pReq = static_cast< MsgKickGuildReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( m_pGuild == NULL )
    {
        return SendOperateAckToClient< MsgKickGuildAck >( MsgKickGuildAck::ECD_NotHaveGuild );
    }

    if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Kick ) )
    {
        return SendOperateAckToClient< MsgKickGuildAck >( MsgKickGuildAck::ECD_NotHaveRight );
    }

    if ( !m_pGuild->CheckPosition( GetDBCharacterID(), pReq->nPlayerID ) )
    {
        return SendOperateAckToClient< MsgKickGuildAck >( MsgKickGuildAck::ECD_NotHaveRight );
    }

    // ֪ͨCenterServer����
    GS2CSKickGuildReq xReq;
    xReq.nPlayerID = GetDBCharacterID();
    xReq.nTargetID = pReq->nPlayerID;
    xReq.nGuildID  = GetGuildID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgInviteGuildReq( Msg* pMsg )
{
    MsgInviteGuildReq* pReq = static_cast< MsgInviteGuildReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szPlayerName, sizeof( pReq->szPlayerName ) );

    if ( m_pGuild == NULL )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_NotHaveGuild );
    }

    if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Invite ) )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_NotHaveRight );
    }

    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( pReq->szPlayerName );
    if ( pRelation == NULL || !pRelation->GetOnLine() )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_NotOnLine );
    }

    if ( pRelation->GetCountry() != GetCountry() )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_NotSaveCountry );
    }      

    if ( pRelation->GetGuildID() != GuildDefine::InitID )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_AlreadyHaveGuild );
    }

    // �ж϶Է��ȼ�
    const GuildConfig::JoinSetting& xSetting = theGuildConfig.GetJoinSetting();
    if ( pRelation->GetLevel() < xSetting.GetLevel() )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_LevelLess );
    }

    // �鿴�Ƿ���뿪���
    if ( !theGameGuildManager.CheckLeaveGuild( pRelation->GetID(), xSetting.GetTimeLimit() * OneHourSecond ) )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_LeaveTimeLimit );
    }

    // �жϰ�������
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( m_pGuild->GetLevel() );
    if ( pSetting == NULL || m_pGuild->MemberCount() >= pSetting->GetMaxCount() )
    {
        return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_MemberFull );
    }

    // ���͸�CenterServer����    
    GS2CSInviteGuildReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    xReq.nTargetID = pRelation->GetID();
    GettheServer().SendMsgToCenterServer( &xReq );
}
void GamePlayer::HandleGuildSQ()
{
	//�ж�����Ƿ�Ϊ���� ���߸�����
	if(!m_pGuild) return;
	GuildMember* pMember = m_pGuild->GetMember( m_pGuild->GetMasterID() );
	bool isNeedSend = false;
	if(pMember && pMember->GetID() == GetDBCharacterID())
		isNeedSend = true; 
	GuildMember * pViceMember = m_pGuild->GetViceMaster();  // ���Ҹ�����
	if(pViceMember && pViceMember->GetID() == GetDBCharacterID())
		isNeedSend = true;
	if(isNeedSend)
	{
		//������� ���������center ��ȡ�����������е������б� ���͵��ͻ���ȥ
		GS2CSGuildSQReq msg;
		msg.nGuildID = m_pGuild->GetID();
		msg.nPlayerID = GetDBCharacterID();
		GettheServer().SendMsgToCenterServer( &msg );
	}
}
void GamePlayer::OnMsgInviteJoinGuildAck( Msg* pMsg )
{
    MsgInviteJoinGuildAck* pAck = static_cast< MsgInviteJoinGuildAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    if ( !RecordTime::CheckRecordTime( gCharInfoServer.otherdata.dwLeaveGuildTime ) )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_TimeLimit );
    }

    // ֱ�ӷ��ظ�CenterServer
    GS2CSInviteJoinGuildAck xAck;
    xAck.bAgreeJoin = pAck->bAgreeJoin;
    xAck.xMember.SetID( GetDBCharacterID() );
    xAck.xMember.SetName( GetCharName() );
    xAck.xMember.SetLevel( GetLevel() );
    xAck.xMember.SetProfession( GetProfession() );
    xAck.xMember.SetGuildID( pAck->nGuildID );
    xAck.xMember.SetPosition( GuildDefine::Position_Member );
    xAck.xMember.SetOnLine( true );

    GettheServer().SendMsgToCenterServer( &xAck );
}

void GamePlayer::OnMsgJoinGuildReq( Msg* pMsg )
{
    MsgJoinGuildReq* pReq = static_cast< MsgJoinGuildReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( m_pGuild != NULL )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_AlreadyHaveGuild );
    }

    // �жϵȼ�, ��ʱ������
    const GuildConfig::JoinSetting& xSetting = theGuildConfig.GetJoinSetting();
    if ( GetLevel() < xSetting.GetLevel() )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_LevelLess );
    }

   /* if ( !RecordTime::CheckRecordTime( gCharInfoServer.otherdata.dwLeaveGuildTime ) )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_TimeLimit );
    }*/

    GameGuild* pGuild = theGameGuildManager.GetGuild( pReq->nGuildID );
    if ( pGuild == NULL )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_GuildNotExist );
    }

    // �жϹ���
    if ( pGuild->GetCountry() != GetCountry() )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_NotSaveCountry );
    }

	// �鿴�Ƿ���뿪���
	if ( !theGameGuildManager.CheckLeaveGuild( GetDBCharacterID(), xSetting.GetTimeLimit() * OneHourSecond ) )
	{
		return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_LeaveTimeLimit );
	}

    // �жϰ�������
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( pGuild->GetLevel() );
    if ( pSetting == NULL || pGuild->MemberCount() >= pSetting->GetMaxCount() )
    {
        return SendOperateAckToClient< MsgJoinGuildAck >( MsgJoinGuildAck::ECD_MemberFull );
    }

    // ֪ͨCenterServe����
    GS2CSJoinGuildReq xReq;
    xReq.xMember.SetID( GetDBCharacterID() );
    xReq.xMember.SetName( GetCharName() );
    xReq.xMember.SetLevel( GetLevel() );
    xReq.xMember.SetProfession( GetProfession() );
    xReq.xMember.SetGuildID( pReq->nGuildID );
    xReq.xMember.SetPosition( GuildDefine::Position_Member );
    xReq.xMember.SetOnLine( true );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgRequestJoinGuildAck( Msg* pMsg )
{
    MsgRequestJoinGuildAck* pAck = static_cast< MsgRequestJoinGuildAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    if ( m_pGuild == NULL )
    { return; }

	// �ж϶Է��ȼ�
	const GuildConfig::JoinSetting& xSetting = theGuildConfig.GetJoinSetting();

	// �鿴�Ƿ���뿪���
	if ( !theGameGuildManager.CheckLeaveGuild( pAck->nPlayerID, xSetting.GetTimeLimit() * OneHourSecond ) )
	{
		return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_LeaveTimeLimit );
	}

    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( m_pGuild->GetLevel() );
    if ( pSetting == NULL || m_pGuild->MemberCount() >= pSetting->GetMaxCount() )
    { return; }

	//�ж�����Ƿ��Ѿ��а���
	GameRelation* pTargetRelation = theGameRelationManager.GetPlayerRelation( pAck->nPlayerID );
	
	if(pTargetRelation && pTargetRelation->GetGuildID() !=0)
	{
		//ɾ���ͻ��˵�����
		MsgGuildDelSQReq msg;
		msg.ID = pAck->nPlayerID;
		SendMessageToClient( &msg );
		return SendOperateAckToClient< MsgInviteGuildAck >( MsgInviteGuildAck::ECD_AlreadyHaveGuild );
	}

    // ֱ�ӷ��͸�CenterServer����
    GS2CSRequestJoinGuildAck xAck;
    xAck.nPlayerID  = GetDBCharacterID();
    xAck.nGuildID   = m_pGuild->GetID();
    xAck.nTargetID  = pAck->nPlayerID;
    xAck.bAgreeJoin = pAck->bAgreeJoin;
    GettheServer().SendMsgToCenterServer( &xAck );
}

void GamePlayer::OnMsgQueryGuildDataReq( Msg* pMsg )
{
    MsgQueryGuildDataReq* pReq = static_cast< MsgQueryGuildDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    GameGuild* pGuild = theGameGuildManager.GetGuild( pReq->nGuildID );
    if ( pGuild == NULL )
    { return; }

    MsgQueryGuildDataAck xAck;
    xAck.nGuildID       = pGuild->GetID();
    xAck.uchLevel       = pGuild->GetLevel();
    xAck.ustMemberCount = pGuild->MemberCount();
    xAck.n64CreateTime  = pGuild->GetCreateTime();
    HelperFunc::SafeNCpy( xAck.szGuildName, pGuild->GetName(), sizeof( xAck.szGuildName ) );
    HelperFunc::SafeNCpy( xAck.szGuildAim, pGuild->GetAim(), sizeof( xAck.szGuildAim ) );
    GuildMember* pMember = pGuild->GetMember( pGuild->GetMasterID() );
    if ( pMember != NULL )
    {
        HelperFunc::SafeNCpy( xAck.szMasterName, pMember->GetName(), sizeof( xAck.szMasterName ) );
    }
    
    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgGuildNoticeChangeReq( Msg* pMsg )
{
    MsgGuildNoticeChangeReq* pReq = static_cast< MsgGuildNoticeChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szNotice, sizeof( pReq->szNotice ) );

    if ( m_pGuild == NULL )
    { return; }

    if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Notice ) )
    { return SendOperateAckToClient< MsgGuildNoticeAck >( MsgGuildNoticeAck::ECD_NotHaveRight ); }

    // ֪ͨCenterServer����
    GS2CSGuildNoticeChangeReq xReq;
    xReq.nPlayerID = GetDBCharacterID();
    xReq.nGuildID  = m_pGuild->GetID();
    HelperFunc::SafeNCpy( xReq.szNotice, pReq->szNotice, sizeof( xReq.szNotice ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgGuildResignPositionReq( Msg* pMsg )
{
    MsgGuildResignPositionReq* pReq = static_cast< MsgGuildResignPositionReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( m_pGuild == NULL )
    { return; }

    if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Resign ) )
    { return; }

    // ֪ͨCenterServer����
    GS2CSGuildResignPositionReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}



void GamePlayer::OnMsgGuildTransferPositionReq( Msg* pMsg )
{
    MsgGuildTransferPositionReq* pReq = static_cast< MsgGuildTransferPositionReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( m_pGuild == NULL || pReq->nPlayerID == GetDBCharacterID() )
    { return; }

    if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Transfer ) )
    { return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_NotHaveRight ); }

    GuildMember* pMember = m_pGuild->GetMember( pReq->nPlayerID );
    if ( pMember == NULL )
    { return; }

    switch ( GetCountryTitle() )
    {
    case CountryDefine::Title_King:
        return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_IsKing ); // �Լ��ǹ���, ����ת�ð���
        break;
    default:
        break;
    }

    if ( GetDBCharacterID() == m_pGuild->GetMasterID() )
    {
        // ����ֻ��ת�ø�������, ����Ҫ���ڴ������ɵȼ�
		// �������й���Լս �й���Լս������ת�ð���
		time_t EndTime = gCharInfoServer.otherdata.nBeginGameGeneralBattleTime;
		time_t nowtime;
		time(&nowtime);
		if(nowtime < EndTime)
		{
			return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_GameBattleCD );
		}
		if(theGameCampBattleDataManager.IsExitesGuildCampBattle(m_pGuild->GetID()))
		{
			return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_GameBattleExites );
		}


        if ( pMember->GetPosition() != GuildDefine::Position_ViceMaster )
        { return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_NotViceMaster ); }

        if ( pMember->GetLevel() < theGuildConfig.GetCreateSetting().GetLevel() )
        { return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_LevelLess ); }
    }
    else
    {
        if ( pMember->GetPosition() != GuildDefine::Position_Member )
        { return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_NotGuildMember ); }

		// �����ת������
		if ( GetGuildPositon() == GuildDefine::Position_FamilyMaster )
		{
			GuildMember * pSelf = m_pGuild->GetMember( GetDBCharacterID() );
			if ( pSelf == NULL )
			{ return; }
			if ( pSelf->GetFamilyID() != pMember->GetFamilyID() )
			{ return SendOperateAckToClient< MsgGuildTransferAck >( MsgGuildTransferAck::ECD_NotSameFamily ); }
		}
    }

    // ֪ͨ��CenterServer����
    GS2CSGuildTransferPositionReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    xReq.nTargetID = pReq->nPlayerID;
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgGuildCreateFamilyReq( Msg* pMsg )
{
    MsgGuildCreateFamilyReq* pReq = static_cast< MsgGuildCreateFamilyReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );
    if ( pReq->szName[0] == 0 )
    { return; }

    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Family ) )
    {
        return SendOperateAckToClient< MsgGuildCreateFamilyAck >( MsgGuildCreateFamilyAck::ECD_NotHaveRight );
    }

    if ( m_pGuild->GetFamilyID( pReq->szName ) != GuildDefine::InitID )
    {
        return SendOperateAckToClient< MsgGuildCreateFamilyAck >( MsgGuildCreateFamilyAck::ECD_SaveFamily );
    }

    if ( m_pGuild->GetEmptyFamilyID() == GuildDefine::InitID )
    {
        return SendOperateAckToClient< MsgGuildCreateFamilyAck >( MsgGuildCreateFamilyAck::ECD_FamilyFull );
    }

    SendOperateAckToClient< MsgGuildCreateFamilyAck >( MsgGuildCreateFamilyAck::ECD_Success );

    // ֪ͨ��CenterServer����
    GS2CSGuildCreateFamilyReq xReq;
    xReq.nGuildID = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    HelperFunc::SafeNCpy( xReq.szName, pReq->szName, sizeof( xReq.szName ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgGuildFamilyChangeReq( Msg* pMsg )
{
    MsgGuildFamilyChangeReq* pReq = static_cast< MsgGuildFamilyChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );

    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Family ) )
    {
        return SendOperateAckToClient< MsgGuildFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_NotHaveRight );
    }

    if ( !m_pGuild->HaveFamily( pReq->uchFamilyID ) )
    {
        return SendOperateAckToClient< MsgGuildFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_EmptyFamily );
    }

    if ( m_pGuild->GetFamilyID( pReq->szName ) != GuildDefine::InitID )
    {
        return SendOperateAckToClient< MsgGuildFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_SaveFamily );
    }

    GS2CSGuildFamilyChangeReq xReq;
    xReq.nGuildID    = m_pGuild->GetID();
    xReq.nPlayerID   = GetDBCharacterID();
    xReq.uchFamilyID = pReq->uchFamilyID;
    HelperFunc::SafeNCpy( xReq.szName, pReq->szName, sizeof( xReq.szName ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgGuildMemberFamilyChangeReq( Msg* pMsg )
{
    MsgGuildMemberFamilyChangeReq* pReq = static_cast< MsgGuildMemberFamilyChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    GuildMember* pMember = m_pGuild->GetMember( pReq->nPlayerID );
    if ( pMember == NULL )
    {
        return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_NotHaveRight );
    }

    if ( pMember->GetFamilyID() == pReq->uchFamilyID )
    {
        return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_SaveFamily );
    }

    if ( pReq->uchFamilyID > 0 && !m_pGuild->HaveFamily( pReq->uchFamilyID ) )
    {
        return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_EmptyFamily );
    }

	if ( m_pGuild == NULL )
	{
		return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_NotHaveRight );
	}
	else
	{
		if ( pReq->uchFamilyID > 0 && ! m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_InFamily ) )
		{// ת�����
			return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_NotHaveRight );
		}

		if ( pReq->uchFamilyID > 0 && pMember->GetPosition() == GuildDefine::Position_FamilyMaster )
		{// ת�����
			return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_AlreadyHaveFamily );
		}

        if ( pReq->uchFamilyID == 0 && pMember->GetPosition() == GuildDefine::Position_FamilyMaster )
        {// ת������
            return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_IsFamilyMaster );
        }

		if ( pReq->uchFamilyID == 0 )
		{// ת������
			GuildMember* pSelf = m_pGuild->GetMember( GetDBCharacterID() );
			if ( NULL == pSelf )
			{ return; }
			
			if ( pSelf->GetFamilyID() == pMember->GetFamilyID() && ! m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_OutFamily ) )
			{
				return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_NotHaveRight );
			}

			if ( pSelf->GetFamilyID() != pMember->GetFamilyID() && ! m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_OutFamilyOther ) )
			{
				return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_NotHaveRight );
			}

			if ( pSelf->GetFamilyID() != pMember->GetFamilyID() && pMember->GetPosition() == GuildDefine::Position_FamilyMaster )
			{
				return SendOperateAckToClient< MsgGuildMemberFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_AlreadyHaveFamily );
			}
		}
	}

    GS2CSGuildMemberFamilyChangeReq xReq;
    xReq.nGuildID    = m_pGuild->GetID();
    xReq.nPlayerID   = GetDBCharacterID();
    xReq.nTargetID   = pReq->nPlayerID;
    xReq.uchFamilyID = pReq->uchFamilyID;
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgGuildAssignPositionReq( Msg* pMsg )
{
    MsgGuildAssignPositionReq* pReq = static_cast< MsgGuildAssignPositionReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( GetDBCharacterID() == pReq->nPlayerID )
    { return; } // ���������Լ�

    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Assign ) )
    { 
        return SendOperateAckToClient< MsgGuildAssignPositionAck >( MsgGuildAssignPositionAck::ECD_NotHaveRight ); 
    }

    GuildMember* pMaster = m_pGuild->GetMember( GetDBCharacterID() );
    if ( pMaster == NULL || pMaster->GetPosition() <= pReq->uchPosition )
    {
        return SendOperateAckToClient< MsgGuildAssignPositionAck >( MsgGuildAssignPositionAck::ECD_NotHaveRight ); 
    }

    GuildMember* pMember = m_pGuild->GetMember( pReq->nPlayerID );
    if ( pMember == NULL || pMember->GetPosition() == pReq->uchPosition )
    {
        return SendOperateAckToClient< MsgGuildAssignPositionAck >( MsgGuildAssignPositionAck::ECD_SamePosition ); 
    }
    
    switch ( pReq->uchPosition )
    {
    case GuildDefine::Position_FamilyMaster:
        if ( pMember->GetFamilyID() == GuildDefine::InitID )
        {
            return SendOperateAckToClient< MsgGuildAssignPositionAck >( MsgGuildAssignPositionAck::ECD_NotHaveFamily ); 
        }
        break;
    default:
        break;
    }

    // ���͸�CenterServer ����
    GS2CSGuildAssignPositionReq xReq;
    xReq.nGuildID   = m_pGuild->GetID();
    xReq.nPlayerID  = GetDBCharacterID();
    xReq.nTargetID  = pReq->nPlayerID;
    xReq.uchPosition = pReq->uchPosition;
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgGuildDelateAgreeAck( Msg* pMsg )
{
    MsgGuildDelateAgreeAck* pAck = static_cast< MsgGuildDelateAgreeAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    if ( m_pGuild == NULL )
    { return; }

    if ( !pAck->bAgreeDelate )
    { return; }     // ��ͬ�ⲻִ��

    GuildDelateInfo& xInfo = m_pGuild->GetDelateInfo();
    if ( xInfo.GetID() == GuildDefine::InitID )
    { return; }

    // ֱ�ӷ��͸�
    GS2CSGuildDelateAgreeAck xAck;
    xAck.nGuildID  = m_pGuild->GetID();
    xAck.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xAck );
}

void GamePlayer::OnMsgGuildDonateAck( Msg* pMsg )
{
    MsgGuildDonateAck* pAck = static_cast< MsgGuildDonateAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    if ( m_pGuild == NULL || !m_pGuild->CheckDonateTimer() )
    { return; }

    if ( GetMoney() < pAck->nMoney )
    { return; }

    /*const GuildConfig::DonateSetting& xSetting = theGuildConfig.GetDonateSetting();
    if ( m_pGuild->GetDonateMoney() >= xSetting.GetMaxMoney() )
    { return; }*/

    // ��Ǯ
    OperateMoney( EOT_Sub, pAck->nMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_GuildDelate );

	unsigned int ItemID = 0;
	unsigned int Exp = 0;
	theRaiseConfig.GetExpAndItemByGuildMoney(pAck->nMoney,Exp,ItemID);

    // ��������
	IncreaseExp( Exp, 0 );

	//�����ʼ�
	if(ItemID != 0)
	{
		SCharItem item;
		if( !theRunTimeData.CreateItem( NULL, ItemID, 1, HelperFunc::CreateID(), item ) )
			return;
		//������������������ ׼�������ʼ������
		GS2CSRaiseGuildPlayerItem msg;
		msg.PlayerID = GetDBCharacterID();
		msg.ItemID = ItemID;
		memcpy(&msg.CItem,&item,sizeof(SCharItem));
		HelperFunc::SafeNCpy(msg.szName,GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( msg.szName) );
		GettheServer().SendMsgToCenterServer( &msg );

		//ȫ��ͨ�� �����Ʒ
		MsgTellGuildPlayerRaiseItem msgItem;
		HelperFunc::SafeNCpy( msgItem.szName, GetCharName(), sizeof( msgItem.szName ) );
		msgItem.CountryID = GetCountry();
		GettheServer().SendMsgToWorld(&msgItem,true);
	}

    // ֪ͨCenterServer
    GS2CSGuildDonateAck xAck;
    xAck.nGuildID  =  m_pGuild->GetID();
    xAck.nPlayerID = GetDBCharacterID();
    xAck.nMoney    = pAck->nMoney;
    GettheServer().SendMsgToCenterServer( &xAck );

	//LYH��־��� �������Ǯ������Ҿ��ף�
	theLogEventService.LogGuildDetail(GetAccountID(),GetDBCharacterID(),m_pGuild->GetID(),pAck->nMoney,0,0,GetCharName());
}

void GamePlayer::OnMsgGuildBuyItemReq( Msg* pMsg )
{
    MsgGuildBuyItemReq* pReq = static_cast< MsgGuildBuyItemReq* >( pMsg );
    if ( pReq == NULL || pReq->nCount == 0 )
    { return; }

    if ( m_pGuild == NULL )
    { 
        return SendOperateAckToClient< MsgGuildBuyItemAck >( MsgGuildBuyItemAck::ECD_NotHaveRight );
    }

    if ( !m_pGuild->CheckShopActive( pReq->uchLevel ) )
    { 
        return SendOperateAckToClient< MsgGuildBuyItemAck >( MsgGuildBuyItemAck::ECD_LevelNotActive );
    }

    const GuildConfig::ShopSetting* pSetting = theGuildConfig.GetShopSetting( pReq->uchLevel );
    if ( pSetting == NULL )
    {
        return SendOperateAckToClient< MsgGuildBuyItemAck >( MsgGuildBuyItemAck::ECD_ErrorLevel );
    }

    unsigned int nPrice = pSetting->GetItemCost( pReq->nItemID );
    if ( nPrice == 0 )
    { 
        return SendOperateAckToClient< MsgGuildBuyItemAck >( MsgGuildBuyItemAck::ECD_ErrorItem );
    }

    unsigned int nCostOffer = nPrice * pReq->nCount;
    if ( GetGuildOffer() < nCostOffer )
    { 
        return SendOperateAckToClient< MsgGuildBuyItemAck >( MsgGuildBuyItemAck::ECD_NotEnoughOffer ); 
    }

    if ( AddItem( pReq->nItemID, pReq->nCount, EIGS_NpcShop ) != ierr_Success )
    { 
        return SendOperateAckToClient< MsgGuildBuyItemAck >( MsgGuildBuyItemAck::ECD_PackFull ); 
    }

    // ���ٰﹱ
    OperateGuildOffer( GuildDefine::OperateSub, nCostOffer );
}

void GamePlayer::OnMsgGuildShopLevelUpReq( Msg* pMsg )
{
    MsgGuildShopLevelUpReq* pReq = static_cast< MsgGuildShopLevelUpReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    GuildShopLevelUp( pReq->uchLevel );
}

void GamePlayer::OnMsgGuildConveneAck( Msg* pMsg )
{
    MsgGuildConveneAck* pAck = static_cast< MsgGuildConveneAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    if ( m_pGuild == NULL )
    { return; }

    m_pGuild->ProcessGuildConveneAck( this );
}

void GamePlayer::OnMsgChangeGuildAimReq( Msg* pMsg )
{
	MsgChangeGuildAimReq* pReq = static_cast< MsgChangeGuildAimReq* >( pMsg );
	if ( pReq == NULL )
	{ return; }

	HelperFunc::CheckStringValid( pReq->szAim, sizeof( pReq->szAim ) );

	if ( m_pGuild == NULL )
	{ return; }

	if ( !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Aim ) )
	{ return; }

	if ( m_pGuild->CanChangeAim() == false )
	{
		return SendOperateAckToClient< MsgChangeGuildAimAck >( MsgChangeGuildAimAck::ECD_InCD ); 
	}

	unsigned int nCost = theGuildConfig.GetChangeAimSetting().GetChangeAimCost();
	if ( nCost > 0 && GetMoney() < nCost )
	{ return; }

	OperateMoney( EOT_Sub, nCost, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ChangeGuildAim);

	// ֪ͨCenterServer����
	GS2CSGuildAimChangeReq xReq;
	xReq.nPlayerID = GetDBCharacterID();
	xReq.nGuildID  = m_pGuild->GetID();
	HelperFunc::SafeNCpy( xReq.szAim, pReq->szAim, sizeof( xReq.szAim ) );
	GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::InitPlayerGuild()
{
    GameGuild* pGuild = theGameGuildManager.GetGuild( GetGuildID() );
    if ( pGuild == NULL )
    { 
        // �������а���
        pGuild = theGameGuildManager.GetGuildByPlayerID( GetDBCharacterID() );
        if ( pGuild == NULL )
        {
            SetGuild( NULL );   
            SetGuildID( GuildDefine::InitID );
            return;
        }
        
        SetGuildID( pGuild->GetID() );
    }

    GuildMember* pMember = pGuild->GetMember( GetDBCharacterID() );
    if ( pMember == NULL )
    {
        SetGuild( NULL );   
        SetGuildID( GuildDefine::InitID );
        return;
    }

    SetGuild( pGuild );
}

uint32 GamePlayer::GetGuildID() const
{
    return gCharInfoServer.otherdata.nGuildID;
}

void GamePlayer::SetGuildID( uint32 nGuildID )
{
    gCharInfoServer.otherdata.nGuildID = nGuildID;
}

// ����Ӱ���߼�
void GamePlayer::ProcessJoinGuild( GameGuild* pGuild )
{
    if ( pGuild == NULL )
    { return; }

    SetGuild( pGuild );
    SetGuildID( pGuild->GetID() );

    // ��������ҹ㲥
    MsgTellJoinGuildToView xTell;
    xTell.header.stID     = GetID();
    xTell.nGuildID        = pGuild->GetID();

	if ( m_pGuild )
	{
		GuildMember* pMember = m_pGuild->GetMember( GetDBCharacterID() );
		if ( pMember )
			xTell.nGuildPosition = pMember->GetPosition();
	}
	 
    GettheServer().SendMsgToView( &xTell, GetID(), true );

    // ���͸��ͻ��˼�����ɳɹ�
    SendOperateAckToClient< MsgJoinGuildAck >( pGuild->IsMaster( GetDBCharacterID() ) ? MsgJoinGuildAck::ECD_CreateSuccess : MsgJoinGuildAck::ECD_Success  );

    // ����ƺ�
    InitCountryTitle( true );     

    // ������������
    ProcessGuideQuest( GuideQuest::Guide_Guild );
}

// �����뿪�����߼�
void GamePlayer::ProcessLeaveGuild( GameGuild* pGuild )
{
    // GetScriptMgr()->StartupVM( ST_LEAVEGUILD, 0, this );

    SetGuild( NULL);
    SetGuildID( GuildDefine::InitID );

    if ( pGuild == NULL )
    { return;}  // ���治ִ��

    // ���¼�����ҳƺ�
    InitCountryTitle( true );

    // ��������ҹ㲥
    MsgTellLeaveGuildToView xTell;
    xTell.header.stID     = GetID();
    GettheServer().SendMsgToView( &xTell, GetID(), true );

    // ֪ͨ�ͻ����뿪����
    SendOperateAckToClient< MsgLeaveGuildAck >( MsgLeaveGuildAck::ECD_Success );

    // ��¼�뿪�����ʱ��
    RecordTime::SaveRecordTime( gCharInfoServer.otherdata.dwLeaveGuildTime );
}

void GamePlayer::ProcessGuildPositionChange()
{
    InitCountryTitle( true );

    // �����������, ɾ�����Ĺ�������
    if ( GetCountryTitle() != CountryDefine::Title_Queen )
    {
        SMountItem* pMount = GetCountryMount();
        if ( pMount != NULL )
        {
            RemoveMountByGuid( pMount->GetMountGuid() );
        }
    }
}

// ��������
void GamePlayer::GuildLevelUp()
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_LevelUp ) )
    {
        return SendOperateAckToClient< MsgGuildLevelUpAck >( MsgGuildLevelUpAck::ECD_NotHaveRight );
    }
  
    int nNewLevel = m_pGuild->GetLevel() + 1;
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( nNewLevel );
    if ( pSetting == NULL )
    {
        return SendOperateAckToClient< MsgGuildLevelUpAck >( MsgGuildLevelUpAck::ECD_MaxLevel );
    }

    if ( m_pGuild->GetMoney() < pSetting->GetNeedMoney() )
    {
        return SendOperateAckToClient< MsgGuildLevelUpAck >( MsgGuildLevelUpAck::ECD_NotEnoughMoney );
    }


    if ( m_pGuild->GetExp() < pSetting->GetNeedExp() )
    {
        return SendOperateAckToClient< MsgGuildLevelUpAck >( MsgGuildLevelUpAck::ECD_NotEnoughExp );
    }

	if ( m_pGuild->GetMission() < pSetting->GetNeedMission() )
    {
        return SendOperateAckToClient< MsgGuildLevelUpAck >( MsgGuildLevelUpAck::ECD_NotEnoughMisson );
    }

    // ֪ͨCenterServer����
    GS2CSGuildLevelUpReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );

	//LYH��־��� ������������
	theLogEventService.LogGuild(GetAccountID(),GetDBCharacterID(),m_pGuild->GetID(),eSystemLogInfo_guild_LevelUp,GetCharName());
}

// �ﹱ����
void GamePlayer::GuildOfferBuild()
{
    const GuildConfig::BuildSetting& xSetting = theGuildConfig.GetBuildSetting();

    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Build ) )
    { return; }

    unsigned int nGuildOffer = GetGuildOffer();
    if ( nGuildOffer == 0 || nGuildOffer < xSetting.GetOffer() )
    {
        return SendOperateAckToClient< MsgGuildOfferBuildAck > ( MsgGuildOfferBuildAck::ECD_NotEnoughOffer );
    }

    // ֪ͨCenterServer����
    GS2CSGuildOfferBuildReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

// ����ļ��
void GamePlayer::GuildCollect()
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Collect ) )
    { return; }

    // ֱ�ӷ��͸�CenterServer
    GS2CSGuildCollectReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

// ���ɵ���
void GamePlayer::GuildMasterDelate()
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Delate ) )
    { return; } // �Լ��ǰ������ܵ���

    const GuildConfig::DelateSetting& xSetting = theGuildConfig.GetDelateSetting();

    static SYSTEMTIME xTime;
    ::GetLocalTime( &xTime );

    MsgGuildDelateRequestAck xAck;

    if ( xTime.wDayOfWeek != xSetting.GetDayOfWeek() || xTime.wHour < xSetting.GetStartHour() || xTime.wHour > xSetting.GetEndHour() )
    {
        return SendOperateAckToClient< MsgGuildDelateRequestAck >( MsgGuildDelateRequestAck::ECD_ErrorTime );
    }

    GuildDelateInfo &xInfo = m_pGuild->GetDelateInfo();
    if ( xInfo.GetID() != GuildDefine::InitID )
    {
        return SendOperateAckToClient< MsgGuildDelateRequestAck >( MsgGuildDelateRequestAck::ECD_AlreadyDelate );
    }

    if ( GetLevel() < xSetting.GetLevel() )
    {
        return SendOperateAckToClient< MsgGuildDelateRequestAck >( MsgGuildDelateRequestAck::ECD_LevelLess );
    }

    if ( GetMoney() < xSetting.GetCostMoney() )
    {
        return SendOperateAckToClient< MsgGuildDelateRequestAck >( MsgGuildDelateRequestAck::ECD_NotEnoughMoney );
    }

    // �ж���������
    if ( m_pGuild->GetOnLineCount() < xSetting.GetMinCount() )
    {
        return SendOperateAckToClient< MsgGuildDelateRequestAck >( MsgGuildDelateRequestAck::ECD_OnLineLess );
    }

    // ���͸�CenterServer����
    GS2CSGuildDelateRequestReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

// ���ɾ���
void GamePlayer::GuildDonate()
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Donate ) )
    { return; }

    // ���͸�CenterServer
    GS2CSGuildDonateRequestReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

// �������񷢲�
bool GamePlayer::GuildQuestRelease( uint32 nQuestType )
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Release ) )
    { 
        SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_NotHaveRight );
        return false;
    }

    if ( m_pGuild->GetReleaseQuest() != 0 )
    {
        SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_AlreadyRelease );
        return false;
    }

    static SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );

    // �жϷ���ʱ��
    if ( m_pGuild->GetReleaseTime() != 0 )
    {
        TimeEx xReleaseTime( m_pGuild->GetReleaseTime() );
        if ( xSystemTime.wDay == xReleaseTime.GetDay() && xSystemTime.wMonth == xReleaseTime.GetMonth() )   // �ж�ͬһ��
        {
            SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_AlreadyRelease );
            return false;
        }
    }

    const GuildConfig::ReleaseSetting& xSetting = theGuildConfig.GetReleaseSetting();

    if ( m_pGuild->GetLevel() < xSetting.GetMinLevel() )
    {
        SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_GuildLevelLess );
        return false;
    }

    if ( xSystemTime.wHour >= xSetting.GetReleaseTime() )
    {
        SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_ErrorTime );
        return false;
    }

    const GuildConfig::ReleaseSetting::QuestSetting* pSetting = xSetting.GetQuestSetting( nQuestType );
    if ( pSetting == NULL )
    {
        SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_QuestError );
        return false;
    }

    if ( m_pGuild->GetMoney() < pSetting->GetCostMoney() )
    {
        SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_NotEnoughMoney );
        return false;
    }

    SendOperateAckToClient< MsgGuildReleaseAck >( MsgGuildReleaseAck::ECD_Success );

    // ֪ͨCenterServer����
    GS2CSGuildQuestReleaseReq xReq;
    xReq.nGuildID   = m_pGuild->GetID();
    xReq.nPlayerID  = GetDBCharacterID();
    xReq.nQuestType = nQuestType;
    GettheServer().SendMsgToCenterServer( &xReq );
    return true;
}

//�����İ�������
int16 GamePlayer::GetGuildReleaseQuest()
{
	if ( m_pGuild == NULL)
	{ 		
		return 0;
	}

	return m_pGuild->GetReleaseQuest();
}

bool GamePlayer::GuildShopLevelUp( uint8 uchLevel )
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Shop ) )
    {
        SendOperateAckToClient< MsgGuildShopLevelUpAck >( MsgGuildShopLevelUpAck::ECD_NotHaveRight );
        return false;
    }

    if ( m_pGuild->CheckShopActive( uchLevel ) )
    {
        SendOperateAckToClient< MsgGuildShopLevelUpAck >( MsgGuildShopLevelUpAck::ECD_AlreadActive );
        return false;
    }

    if ( uchLevel > m_pGuild->GetLevel() )
    {
        SendOperateAckToClient< MsgGuildShopLevelUpAck >( MsgGuildShopLevelUpAck::ECD_GuildLevelLess );
        return false;
    }

    const GuildConfig::ShopSetting* pSetting = theGuildConfig.GetShopSetting( uchLevel );
    if ( pSetting == NULL )
    {
        SendOperateAckToClient< MsgGuildShopLevelUpAck >( MsgGuildShopLevelUpAck::ECD_ErrorLevel );
        return false;
    }

    if ( m_pGuild->GetExp() < pSetting->GetCostExp() )
    {
        SendOperateAckToClient< MsgGuildShopLevelUpAck >( MsgGuildShopLevelUpAck::ECD_NotEnoughExp );
        return false;
    }

    SendOperateAckToClient< MsgGuildShopLevelUpAck >( MsgGuildShopLevelUpAck::ECD_Success );

    // �����Ǯ
    OperateGuildExp( GuildDefine::OperateSub, pSetting->GetCostExp() );

    // ������Ӱ����̵�ȼ�
    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildShopLevel, GuildDefine::OperateAdd, uchLevel );
    return true;
}

bool GamePlayer::GuildConvene()
{
    if ( m_pGuild == NULL || !m_pGuild->HaveRight( GetDBCharacterID(), GuildDefine::Right_Convene ) )
    { return false; }

    // �����в����ټ�
    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL || pMapData->IsEctypeMap() )
    { return false; }

    // �жϵȼ�����
    unsigned char uchLevel = 40;
    if ( pMapData->MinPlayerLevel > 40 )
    { uchLevel = pMapData->MinPlayerLevel; }
    
    GS2CSGuildConveneReq xReq;
    xReq.nGuildID  = m_pGuild->GetID();
    xReq.nPlayerID = GetDBCharacterID();
    xReq.uchLevel  = uchLevel;
    xReq.nMapID    = GetMapID();
    xReq.fPosX     = GetFloatX();
    xReq.fPosY     = GetFloatY();
    xReq.fDir      = 0.0f;
    GettheServer().SendMsgToCenterServer( &xReq );

    return true;
}


void GamePlayer::OperateGuildOffer( unsigned char uchOperate, int nValue )
{
    if( m_pGuild == NULL )
    { return; }

    m_pGuild->SendMemberDataChangeReqMessage( GetDBCharacterID(), GuildDefine::UpdateMemberOffer, uchOperate, nValue );
}

uint32 GamePlayer::GetGuildOffer()
{
    if ( m_pGuild == NULL )
    { return 0; }

    GuildMember* pMember = m_pGuild->GetMember( GetDBCharacterID() );
    if ( pMember == NULL )
    { return 0; }

    return pMember->GetOffer();
}

void GamePlayer::OperateGuildActivity( unsigned char uchOperate, int nValue )
{
    if( m_pGuild == NULL )
    { return; }

    m_pGuild->SendMemberDataChangeReqMessage( GetDBCharacterID(), GuildDefine::UpdateMemberActivity, uchOperate, nValue );
}

uint32 GamePlayer::GetGuildActivity()
{
    if ( m_pGuild == NULL )
    { return 0; }

    GuildMember* pMember = m_pGuild->GetMember( GetDBCharacterID() );
    if ( pMember == NULL )
    { return 0; }

    return pMember->GetActivity();
}

void GamePlayer::OperateGuildMoney( unsigned char uchOperate, int nValue )
{
    if ( m_pGuild == NULL )
    { return; }

    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMoney, uchOperate, nValue );

	//LYH��־��� �������Ǯ���٣�
	theLogEventService.LogGuildDetail(GetAccountID(),GetDBCharacterID(),m_pGuild->GetID(),nValue,0,0,GetCharName());


}

uint32 GamePlayer::GetGuildMoney()
{
    if ( m_pGuild == NULL )
    { return 0; }

    return m_pGuild->GetMoney();
}

void GamePlayer::OperateGuildExp( unsigned char uchOperate, int nValue )
{
    if ( m_pGuild == NULL )
    { return; }

    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildExp, uchOperate, nValue );

	theLogEventService.LogGuildDetail(GetAccountID(),GetDBCharacterID(),m_pGuild->GetID(),0,nValue,0,GetCharName());
}

uint32 GamePlayer::GetGuildExp()
{
    if ( m_pGuild == NULL )
    { return 0; }

    return m_pGuild->GetExp();
}

void GamePlayer::OperateGuildMission( unsigned char uchOperate, int nValue )
{
    if ( m_pGuild == NULL )
    { return; }

    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMission, uchOperate, nValue );

	//LYH��־��� ��ʹ����Ĳ�����
	theLogEventService.LogGuildDetail(GetAccountID(),GetDBCharacterID(),m_pGuild->GetID(),0,0,nValue,GetCharName());
}

uint32 GamePlayer::GetGuildMission()
{
    if ( m_pGuild == NULL )
    { return 0; }

    return m_pGuild->GetMission();
}

void GamePlayer::OperateGuildSalary( unsigned char uchOperate, int nValue )
{
    if ( m_pGuild == NULL )
    { return; }

    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildSalary, uchOperate, nValue );
}

uint32 GamePlayer::GetGuildSalary()
{
    if ( m_pGuild == NULL )
    { return 0; }

    return m_pGuild->GetSalary();
}

void GamePlayer::OperateGuildVar( uint8 uchOperate, uint32 nIndex, short nValue )
{
    if ( m_pGuild == NULL )
    { return; }

    uint32 nFormatValue = GameGuild::SetFormatGuildVar( nIndex, nValue );
    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildVar, uchOperate, nFormatValue );
}

short GamePlayer::GetGuildVar( uint32 nIndex )
{
    if ( m_pGuild == NULL )
    { return 0; }

    return m_pGuild->GetGuildVar( nIndex );
}


void GamePlayer::OperateGuildLevel( uint8 uchOperate, int nValue )
{
    if ( m_pGuild == NULL )
    { return; }

    m_pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildLevel, uchOperate, nValue );
}

uint32 GamePlayer::GetGuildLevel()
{
    if ( m_pGuild == NULL )
    { return 0; }

    return m_pGuild->GetLevel();
}

uint8 GamePlayer::GetGuildPositon()
{
    if ( m_pGuild == 0 )
    { return GuildDefine::Position_None; }

    GuildMember* pMember = m_pGuild->GetMember( GetDBCharacterID() );
    if ( pMember == NULL )
    { return GuildDefine::Position_None; }

    return pMember->GetPosition();
}

void GamePlayer::TellGuildVar( int nKey, short nVar )
{
    //MsgTellCharVar msg;
    //msg.AddState( nKey + VAR_SYS_MAX, nVar, MsgTellCharVar::eStateChange );
    //GettheServer().SendMsgToSingle( &msg, this );
}

void GamePlayer::TellAllGuildVar()
{
    MsgTellCharVar msg;

    //for( int i = 0; i < More_iMaxGuildVars; ++i )
    //{
    //    if ( m_stGuildVars[i] != 0 )
    //    {
    //        msg.AddState( i + VAR_SYS_MAX, m_stGuildVars[i] );
    //    }
    //}

    //if ( msg.nStateCount > 0 )
    //{
    //    GettheServer().SendMsgToSingle( &msg, this );
    //}
}

void GamePlayer::ClearAllGuildVar()
{
    MsgTellCharVar msg;

    //for( int i = 0; i < More_iMaxGuildVars; ++i )
    //{
    //    if ( m_stGuildVars[i] != 0 )
    //    {
    //        msg.AddState( i + VAR_SYS_MAX, 0 );
    //    }
    //}

    //if ( msg.nStateCount > 0 )
    //{
    //    GettheServer().SendMsgToSingle( &msg, this );
    //}

    //memset( m_stGuildVars, 0, sizeof( m_stGuildVars ) );
}


bool GamePlayer::RecordGuildTime( int nVarId )
{
    if ( m_pGuild == NULL )
    { return false; }

    unsigned long dwTime = GetRecordSystemTime();

    unsigned short low    = LOWORD( dwTime );
    unsigned short high   = HIWORD( dwTime );

    OperateGuildVar( GuildDefine::OperateSet, nVarId, low );
    OperateGuildVar( GuildDefine::OperateSet, nVarId + 1, high );

    return true;
}

bool GamePlayer::IsGuildExpired( int nVarId, int keyHour, int keyMinute, int minDuration )
{
    if ( m_pGuild == NULL )
    { return false; }

    unsigned short low = GetGuildVar( nVarId );
    unsigned short high = GetGuildVar( nVarId + 1 );
    unsigned long dwLastTime = MAKELONG( low, high );

    // ��һ�μ�¼ʱ��
    unsigned char Year   = (dwLastTime>>20) & 0xFFF;  // 12  1024
    unsigned char Month  = (dwLastTime>>16) & 0xF;    //  4  16
    unsigned char Day    = (dwLastTime>>11) & 0x1F;   //  5  32
    unsigned char Hour   = (dwLastTime>>6)  & 0x1F;   //  5  32
    unsigned char Minute = (dwLastTime>>0)  & 0x3F;   //  6  64

    // ��ǰʱ��
    SYSTEMTIME systime;
    GetLocalTime( &systime );
    unsigned char nCurYear   = systime.wYear - 2000;
    unsigned char nCurMonth  = systime.wMonth;
    unsigned char nCurDay    = systime.wDay;
    unsigned char nCurHour   = systime.wHour; 
    unsigned char nCurMinute = systime.wMinute;     

    long recordTimeDistance = DistanceNowTime( Year, Month, Day, Hour, Minute );    
    if ( recordTimeDistance > 0)
    { // ���ݴ����� ���� ʱ�䳬Խ ��¼ʱ���������ʱ��
        OperateGuildVar( GuildDefine::OperateSet, nVarId, 0 );
        OperateGuildVar( GuildDefine::OperateSet, nVarId + 1, 0 );
        return false;
    }

    if ( abs(recordTimeDistance)> 24 * 60 && abs(recordTimeDistance) >= minDuration )
    { // ����һ������
        //Log("����һ������ ����ͨ��ʱ��[%d][%d:%d:%d:%d:%d][%d:%d:%d]", nVarId, Year, Month, Day, Hour, Minute,keyHour, keyMinute, minDuration);
        return true;
    }

    long keyTimeDistance = DistanceNowTime( nCurYear, nCurMonth, nCurDay, keyHour, keyMinute );
    if ( keyTimeDistance < 0) 
    { // �������ʱ�����KeyTime
        if ( abs(recordTimeDistance) > abs(keyTimeDistance) && abs(recordTimeDistance) >= minDuration )
        {
            //Log("�������ʱ����� ����ͨ��ʱ��[%d][%d:%d:%d:%d:%d][%d:%d:%d]", nVarId, Year, Month, Day, Hour, Minute,keyHour, keyMinute, minDuration);
            return true;
        }
    }

    if ( Year==0 && nCurMonth==0) 
    { // û�м�¼��
        //Log("û�м�¼�� ����ͨ��ʱ��[%d][%d:%d:%d:%d:%d][%d:%d:%d]", nVarId, Year, Month, Day, Hour, Minute, keyHour, keyMinute, minDuration);
		Log(theXmlString.GetString(eServerLog_NotJiLuByTime), nVarId, Year, Month, Day, Hour, Minute, keyHour, keyMinute, minDuration);
        return true;
    }
    return false;
}

void GamePlayer::ClearGuildExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId )
{
    if ( IsGuildExpired( nVarId, keyHour, keyMinute, minDuration ) )
    {
        OperateGuildVar( GuildDefine::OperateSet, nClearVarId, 0 );
    }
}

bool GamePlayer::IsGuildMember( BaseCharacter* pChar )
{
    if ( pChar == NULL )
    { return false; }

    if ( pChar->GetID() == GetID() )
    { return true; }

    if ( !pChar->HaveGuild() )
    { return false; }

    return GetGuildID() == pChar->GetGuildID();
}
void GamePlayer::OnMsgSetGuildCampBattleValue( Msg* pMsg )
{
	MsgSetGuildCampBattleValue * pSetting = (MsgSetGuildCampBattleValue*)pMsg;
	//��GameServer�ж��Ƿ���Խ��д��� 
	//1.�ж�����Ƿ�Ϊ�᳤
	GameGuild* pGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(!pGuild || !pGuild->IsMaster(GetDBCharacterID()))
	{
		return;
	}
	//2.�ж�Ŀ���Ƿ����
	//3.�ж�Ŀ���Ƿ��Ѿ���Ȩ����
	GuildMember * pMember = pGuild->GetMember(pSetting->TargetID);
	if(!pMember)
	{
		return;
	}
	else if((pMember->GetCampBattleValue() & pSetting->CampBattleValue) == pSetting->IsAdd)
	{
		return;
	}
	//4.���͵�CenterServer���������ж�
	GS2CSSetGuildCampBattleValue msg;
	msg.PlayerID = GetDBCharacterID();
	msg.TargetID = pSetting->TargetID;
	msg.CampBattleValue = pSetting->CampBattleValue;
	msg.GuildID = pMember->GetGuildID();
	msg.IsAdd = pSetting->IsAdd;
	GettheServer().SendMsgToCenterServer(&msg);
}
void GamePlayer::OnMsgChangeGuldNameReq( Msg* pMsg )
{
	MsgChangeGuldNameReq* pName = (MsgChangeGuldNameReq*)pMsg;
	if(!pName)
		return;
	//�ж�����Ƿ��ǻ᳤
	//�ж���ҵĹ���ID�Ƿ���ȷ
	GameGuild* pGuild = theGameGuildManager.GetGuild(GetGuildID());
	if(!pGuild)
		return;
	if(!pGuild->IsMaster(GetDBCharacterID()))
		return;
	if(GetGuildID()  != pName->GuildID)
		return;
	if(!pGuild->GetIsCanChangeName())
	{
		MsgChangeGuldNameAck msg;
		msg.GuildID = pName->GuildID;
		strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,pName->Name);
		msg.IsCanChange = false;
		SendMessageToClient(&msg);
		return;
	}
	if(strcoll(pGuild->GetName(),pName->Name) == 0)
		return;
	bool bIsInLow		= CChatCheck::getInstance()->CheckStringInLow(pName->Name);
	if (!bIsInLow )//������
		return;
	else if( strlen(pName->Name) <= 0)
		return;
	else if( strlen(pName->Name) > GuildDefine::MaxNameLength  )
		return;
    else if(strchr(pName->Name, ' ') != NULL)
		return;
	// �ж��Ƿ�����
    if ( theGameGuildManager.CheckGuildName( pName->Name ) )
		return;
	//���޸Ĺ������Ƶ�����͵�centerserver
	GS2CSChangeGuildNameReq msg;
	msg.GuildID = pName->GuildID;
	msg.PlayerID = GetDBCharacterID();
	strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,pName->Name);
	GettheServer().SendMsgToCenterServer(&msg);
}