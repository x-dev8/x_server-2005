#include "GamePlayer.h"
#include "ShareData.h"
#include "GameFamily.h"


void GameFamily::ProcessMemberJoinFamily( const FamilyDefine::FamilyMember& member )
{
	// ֪ͨ������Ա, ĳĳ���������
	MsgTellJoinFamilyToFamily tell;
	tell.member = member;
	SendMessageToFamily( &tell, member.GetID() );

	// ���ͼ�����Ϣ���ͻ���
	SendFamilyDetailToClient( member.GetID() );

	// ����ڱ�������
	GamePlayer* pPlayer = GetPlayer( member.GetID() );
	if ( pPlayer == NULL )
	{ return; }

	// �����������߼�
	pPlayer->ProcessJoinFamily( this );
}

GamePlayer* GameFamily::GetPlayer( unsigned int nPlayerID )
{
	return theRunTimeData.GetGamePlayerByDBID( nPlayerID );
}

void GameFamily::SendMessageToFamily( Msg* pMessage, unsigned int nExceptID /*= FamilyDefine::InitFamilyID*/, unsigned short nLevel /*= 0*/, bool bSendToCenter /*= false */ )
{
	if ( bSendToCenter )
	{
		GS2CSFamilyMessage msg;
		msg.nFamilyID = GetFamilyID();
		msg.nExceptID = nExceptID;
		msg.nLevel = nLevel;
		msg.AddMessage( pMessage, pMessage->GetLength() );
		GettheServer().SendMsgToCenterServer( &msg );
	}
	else
	{
		MemberContainerItr itr = _memberContainer.begin();
		MemberContainerItr endItr = _memberContainer.end();
		for ( ; itr != endItr; ++itr )
		{
			if ( ! itr->second.GetOnLine() || itr->second.GetID() == nExceptID )
			{ continue; }   // ������, ����ָ���˲���

			if ( itr->second.GetLevel() < nLevel )
			{ continue; }   // С�ڵȼ�����

			GamePlayer* pPlayer = GetPlayer( itr->second.GetID() );
			if ( pPlayer == NULL )
			{ continue; }

			pPlayer->SendMessageToClient( pMessage );
		}
	}
}

void GameFamily::SendFamilyDetailToClient( unsigned int nPlayerID )
{
	GamePlayer* pPlayer = GetPlayer( nPlayerID );
	if ( pPlayer == NULL )
	{ return; }

	MsgTellFamilyInfo tell;
	tell.info = *this ;

	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( tell.AddMember( itr->second ) == false )
		{
			tell.bEnd = false;
			pPlayer->SendMessageToClient( &tell );
			tell.ResetMembers();
			tell.AddMember( itr->second );
		}
	}

	if ( tell.nCount > 0 )
	{
		pPlayer->SendMessageToClient( &tell );
	}
}

void GameFamily::ProcessMemberLeaveFamily( const FamilyDefine::FamilyMember& member, uint8 nType)
{
	// ֪ͨ������Ա, ĳĳ���������
	MsgTellLeaveFamilyToFamily tell;
	tell.member = member;
	SendMessageToFamily( &tell, member.GetID() );

	// ����ڱ�������
	GamePlayer* pPlayer = GetPlayer( member.GetID() );
	if ( pPlayer == NULL )
	{ return; }

	// �����뿪�����߼�
	pPlayer->ProcessLeaveFamily( this, nType );

}

void GameFamily::ProcessEnterWorld( unsigned int nPlayerID )
{
	SendFamilyDetailToClient( nPlayerID );
}

void GameFamily::ProcessUpdateFamilyNotice()
{
	// ֪ͨ���幫�����
	MsgTellFamilyNoticeUpdate tell;
	HelperFunc::SafeNCpy( tell.szNotice, GetFamilyNotice(), sizeof( tell.szNotice ) );
	SendMessageToFamily( &tell );

	// ����ڱ�������
	GamePlayer* pPlayer = GetPlayer( this->GetLeaderID() );
	if ( pPlayer == NULL )
	{ return; }
	pPlayer->SendOperateAckToClient< MsgFamilyNoticeAck >( MsgFamilyNoticeAck::ECD_Success );
}

void GameFamily::ProcessUpdateFamilyAim()
{
	// ����ڱ�������
	GamePlayer* pPlayer = GetPlayer( this->GetLeaderID() );
	if ( pPlayer == NULL )
	{ return; }
	pPlayer->SendOperateAckToClient< MsgFamilyAimAck >( MsgFamilyAimAck::ECD_Success );
}

void GameFamily::ProcessTransferPosition( const FamilyDefine::FamilyMember& requester, const FamilyDefine::FamilyMember& target )
{
	if ( target.GetPosition() == FamilyDefine::Position_Leader )
	{
		SetLeaderID( target.GetID() );
	}

	// ֪ͨת��ְλ
	MsgTellFamilyTransfer tell;
	tell.nRequesterID = requester.GetID();
	tell.nTargetPlayerID = target.GetID();
	tell.nPosition = target.GetPosition();
	SendMessageToFamily( &tell );

	// ֪ͨ��Ұ�����Ŀ��ְλ�ı仯
	MsgTellViewPositionChange xTell;
	GamePlayer *pPlayer = theRunTimeData.GetGamePlayerByDBID( requester.GetID() );
	if ( pPlayer )
	{
		xTell.nPlayerID = pPlayer->GetID();
		xTell.nPosition = requester.GetPosition();
		GettheServer().SendMsgToView( &xTell, pPlayer->GetID(), false );
	}
	
	GamePlayer *pTargetPlayer = theRunTimeData.GetGamePlayerByDBID( target.GetID() );
	if ( pTargetPlayer )
	{
		xTell.nPlayerID = pTargetPlayer->GetID();
		xTell.nPosition = target.GetPosition();
		GettheServer().SendMsgToView( &xTell, pTargetPlayer->GetID(), false );
	}

}

void GameFamily::ProcessDonate( FamilyDefine::FamilyMember& member, unsigned int nMoney )
{
	Family::ProcessDonateMoney( member, nMoney );

	// ֪ͨ���
	MsgTellFamilyDonate tell;
	tell.nMemberID = member.GetID();
	tell.nMoney = nMoney;
	SendMessageToFamily( &tell );
}

void GameFamily::ProcessUpgrade( const FamilyDefine::FamilyMember& member )
{
	// ֪ͨ����
	MsgTellFamilyUpgrade tell;
	tell.nMemberID = member.GetID();
	tell.nNewFamilyLevel = GetFamilyLevel();
	tell.nNewFamilyMoney = GetMoney();
	tell.nNewFamilyProsperity = GetProsperity();
	SendMessageToFamily( &tell );
}

void GameFamily::SendFamilyInfoToClient( unsigned int nPlayerID )
{
	GamePlayer* pPlayer = GetPlayer( nPlayerID );
	if ( pPlayer == NULL )
	{ return; }

	MsgQueryFamilyInfoAck ack;
	ack.info = *this;
	FamilyDefine::FamilyMember* pLeader = GetMemberByID( GetLeaderID() );
	if ( pLeader )
	{
		HelperFunc::SafeNCpy( ack.szLeaderName, pLeader->GetName(), sizeof( ack.szLeaderName ) );
		ack.nPosition = pLeader->GetPosition();
		ack.bLeadOnLine = pLeader->GetOnLine();
		ack.nLeaderLv = pLeader->GetLevel();
	}

	pPlayer->SendMessageToClient( &ack );
}

void GameFamily::ProcessOffline( unsigned int nPlayerID )
{
	GS2CSTellMemberOffline tell;
	tell.nFamilyID = GetFamilyID();
	tell.nPlayerID = nPlayerID;
	GettheServer().SendMsgToCenterServer( &tell );
}

void GameFamily::SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue )
{
	GS2CSFamilyMemberDataChangeReq xReq;
	xReq.nFamilyID      = GetFamilyID();
	xReq.nPlayerID      = nPlayerID;
	xReq.uchChangeType  = uchChangeType;
	xReq.uchOperateType = uchOperatetype;
	xReq.nValue         = nValue;
	GettheServer().SendMsgToCenterServer( &xReq );
}

void GameFamily::SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
	// ���͸����а��ɳ�Ա
	MsgFamilyMemberDataUpdate xUpdate;
	xUpdate.nPlayerID     = nPlayerID;
	xUpdate.uchUpdateType = uchType;
	xUpdate.nUpdateValue  = nValue;
	SendMessageToFamily( &xUpdate );
}


void GameFamily::ProcessFamilyPositionChange( FamilyDefine::FamilyMember* pMember, unsigned char uchPosition )
{
	switch( uchPosition )
	{
	case FamilyDefine::Position_Leader:
		{
			SetLeaderID( pMember->GetID() );
		}
		break;
	default:
		break;
	}
}   


void GameFamily::ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
	FamilyDefine::FamilyMember* pMember = GetMemberByID( nPlayerID );
	if ( pMember == NULL )
	{ return; }

	ProcessMemberDataUpdate( pMember, uchType, nValue );
}

void GameFamily::ProcessMemberDataUpdate( FamilyDefine::FamilyMember* pMember, unsigned char uchType, unsigned int nValue )
{
	if ( pMember == NULL )
	{ return; }

	switch ( uchType )
	{
	case FamilyDefine::UpdateMemberOnLine:					// ��������
		pMember->SetOnline( nValue == 1 ? true : false );
		break;
	case FamilyDefine::UpdateMemberLevel:					// ���µȼ�
		pMember->SetLevel( nValue );
		break;
	case FamilyDefine::UpdateMemberPosition:				// ����ְλ
		pMember->SetPosition( nValue );
		ProcessFamilyPositionChange( pMember, nValue );		// �������ְλ�ı�
		break;
	case FamilyDefine::UpdateMemberProfession:				// ����ְҵ
		pMember->SetProfession( nValue );
		break;
	case FamilyDefine::UpdateMemberExp:						// ���³�Ա����
		break;
	case FamilyDefine::UpdateMemberDonateMoney:
		pMember->SetDonateMoney( nValue );					// ���³�Ա���
		break;
	default:
		return;
	}

	SendMemberDataUpdateMessage( pMember->GetID(), uchType, nValue );
}

void GameFamily::ProcessDisbandFamily()
{
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		GamePlayer* pPlayer = GetPlayer( itr->second.GetID() );
		if ( pPlayer )
		{
			pPlayer->ProcessLeaveFamily( this, FamilyDefine::Enum_Family_Disbanded );
		}
	}
	_memberContainer.clear();
}
