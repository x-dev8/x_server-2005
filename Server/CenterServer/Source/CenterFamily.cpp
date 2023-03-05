#include "CenterFamily.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"
#include "FamilyMessage.h"
#include "FamilyConfig.h"
#include "XmlStringLanguage.h"
#include "MailManagerMain.h"
#include "RelationManager.h"


void CenterFamily::SaveFamilyDataToDatabase()
{
	CS2DBFamilyDataUpdateReq req;
	req.info = *this;
	theMysqlCommunication.PushReqMessage( &req, 0 );
}

void CenterFamily::ProcessMemberJoinFamily( const FamilyDefine::FamilyMember& member )
{
	// �������ݿ�
	AddNeedSaveMember( member.GetID() );

	// ֪ͨgameserver
	CS2GSJoinFamilyAck ack;
	ack.member = member;
	theGameServerManager.SendMessageToGameServers( &ack );

	// ���¹�ϵ����
	CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( member.GetID() );
	if ( pRelation == NULL )
	{ return; }  
	pRelation->UpdateRelationAttribute( RelationDefine::UpdateFamily, GetFamilyID() );
}

void CenterFamily::AddNeedSaveMember( unsigned int nPlayerID )
{
	_saveMembers.insert( nPlayerID );
}

void CenterFamily::ProcessMemberLeaveFamily( const FamilyDefine::FamilyMember& member, uint8 nType )
{
	// �������ݿ�
	//AddNeedSaveMember( member.GetID() );

	// ֪ͨgameserver
	CS2GSLeaveFamilyAck ack;
	ack.member = member;
	ack.uType = nType;
	theGameServerManager.SendMessageToGameServers( &ack );

	// �������ݿ�
	CS2DBFamilyMemberLeaveReq xReq;
	xReq.nPlayerID = member.GetID();
	theMysqlCommunication.PushReqMessage( &xReq, 0 );

	// ��Ҳ����ߣ������ʼ�����
	if ( !member.GetOnLine() )
	{
		SendMailToMemberNotOnLine( member, nType );
	}

	// ���¹�ϵ����
	CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( member.GetID() );
	if ( pRelation == NULL )
	{ return; }  
	pRelation->UpdateRelationAttribute( RelationDefine::UpdateFamily, FamilyDefine::InitFamilyID );
}

void CenterFamily::SendMailToAllMemberNotOnLine( uint8 nType )
{
	SaveMemberContainerItr itr = _saveMembers.begin();
	SaveMemberContainerItr endItr = _saveMembers.end();
	for ( ; itr != endItr; ++itr )
	{
		FamilyDefine::FamilyMember* pMember = GetMemberByID( *itr );
		if ( !pMember->GetOnLine())
		{
			SendMailToMemberNotOnLine( *pMember, nType );
		}
	}
 
}
void CenterFamily::SendMailToMemberNotOnLine( const FamilyDefine::FamilyMember& member, uint8 nType )
{
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;

	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        

	// ������
	xReq.mail.owners[EM_FromIndex].charDbId = FamilyDefine::InitFamilyID;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

	// �ռ���
	xReq.mail.owners[EM_ToIndex].charDbId = member.GetID();
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, member.GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

	if ( nType == FamilyDefine::Enum_Leave_Kicked )
	{
		sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_MailBeKickedFromFamily ) );
	}

	if ( nType == FamilyDefine::Enum_Family_Disbanded )
	{
		sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_MailFamilyDisbanded ) );
	}

	if ( nType == FamilyDefine::Enum_Leave_Self )
	{
		return;
	}
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_MailSystemTitle ) );
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
}

unsigned short CenterFamily::RunUpdate( unsigned int nCurrentTime )
{
	// ���ж��Զ���ɢ
	if ( GetDisbandTime() > 0 )
	{
		unsigned int nKeepTime = theFamilyConfig.GetDisbandSetting().GetFamilyKeepTime() * OneDayMicroSecond;
		if ( TimeEx::IsPassCurrentTime( GetDisbandTime(), nKeepTime ) )
		{
			ProcessDisbandFamily();
			return FamilyDefine::UpdateDiaband;
		}
	}

	static SYSTEMTIME xTime;
	::GetLocalTime( &xTime );
	if ( xTime.wHour == 0 && xTime.wMinute == 0 )
	{ 
		// ÿ��1 0:00 �۳����м���500�ķ��ٶ�
		if( xTime.wDayOfWeek == 1 )
		{ _prosperityTimer.StartTimer( HQ_TimeGetTime(), 65000 ); }

		// 1���Ӻ�ִ��
		_bFirstEnterTimer.StartTimer( HQ_TimeGetTime(), 70000 );

	}

	if ( (xTime.wHour == 0 || xTime.wHour == 12 ) && xTime.wMinute == 0)
	{
		// ÿ��0:00 ����12:00 ��ʱ���һ��������뿪�������Ϣ
		_memberLeaveTimer.StartTimer( HQ_TimeGetTime(), 71000 );
	}

	if ( _prosperityTimer.DoneTimer() )
	{ OperateProsperity( FamilyDefine::OperateSub, theFamilyConfig.GetProsperitySetting().GetProsPerWeek() ); }

	if ( _bFirstEnterTimer.DoneTimer() )
	{ SetbFirstEnterWorld( true ); }

	if ( _memberLeaveTimer.DoneTimer() )
	{ UpdateMemberLeave( theFamilyConfig.GetMemberLeaveSetting().GetLeaveSettingTime() * OneHourMicroSecond ); }

	// ��ʱ���������Ϣ
	if ( _familyInfoSaveTimer.DoneTimer( nCurrentTime ) )
	{ SaveFamilyDataToDatabase(); }

	// ��ʱ��������Ա��Ϣ
	if ( _memberSaveTimer.DoneTimer( nCurrentTime ) )
	{ SaveMemberDataToDatabase(); }

	// ���� �� �����¼ˢ��
	UpdateInivte( nCurrentTime );
	UpdateRequest( nCurrentTime );

	return FamilyDefine::UpdateNormal;
}

void CenterFamily::SendFamilyDataToGameServer( unsigned int nServerID )
{
	GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nServerID );

	CS2GSFamilyDetail detail;
	detail.info = *this;

	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( detail.AddMember( itr->second ) == false )
		{
			if ( pGameServer != NULL )
			{
				pGameServer->Send( &detail );
			}
			else
			{
				theGameServerManager.SendMessageToGameServers( &detail );
			}

			detail.ResetMembers();
			detail.AddMember( itr->second );
		}
	}

	if ( detail.nCount > 0 )
	{
		if ( pGameServer != NULL )
		{
			pGameServer->Send( &detail );
		}
		else
		{
			theGameServerManager.SendMessageToGameServers( &detail );
		}
	}
}

void CenterFamily::SaveMemberDataToDatabase()
{
	if ( _saveMembers.empty() )
	{ return; }

	CS2DBFamilyMemberUpdateReq req;
	SaveMemberContainerItr itr = _saveMembers.begin();
	SaveMemberContainerItr endItr = _saveMembers.end();
	for ( ; itr != endItr; ++itr )
	{
		FamilyDefine::FamilyMember* pMember = GetMemberByID( *itr );
		if ( pMember )
		{
			if ( req.AddMember( *pMember ) == false )
			{
				theMysqlCommunication.PushReqMessage( &req, 0 );
				req.Reset();
				req.AddMember( *pMember );
			}
		}
	}

	if ( req.nCount > 0 )
	{ theMysqlCommunication.PushReqMessage( &req, 0 ); }

	_saveMembers.clear();
}

CenterFamily::CenterFamily()
{
	_memberSaveTimer.StartTimer( 1, FamilyDefine::SaveSpaveTime );
}

void CenterFamily::ProcessUpdateFamilyNotice()
{
	StartSaveTimer();

	// ͬ��gameserver
	CS2GSFamilyNoticeAck ack;
	ack.nFamilyID = GetFamilyID();
	HelperFunc::SafeNCpy( ack.szNotice, GetFamilyNotice(), sizeof( ack.szNotice ) );
	theGameServerManager.SendMessageToGameServers( &ack );
}

void CenterFamily::ProcessUpdateFamilyAim()
{
	StartSaveTimer();

	// ͬ��gameserver
	CS2GSFamilyAimAck ack;
	ack.nFamilyID = GetFamilyID();
	ack.nChangeAimTime = GetLastChangeAimTime();
	HelperFunc::SafeNCpy( ack.szAim, GetFamilyNotice(), sizeof( ack.szAim ) );
	theGameServerManager.SendMessageToGameServers( &ack );
}


void CenterFamily::OperateProsperity( uint8 uType, int nValue )
{
	switch ( uType )
	{
		case FamilyDefine::OperateAdd:
		{
			SetProsperity( GetProsperity() + nValue );
		}
		break;
		case  FamilyDefine::OperateSub:
		{
			int nProsperity = GetProsperity() - nValue;
			if ( nProsperity <= 0 )
			{
				nProsperity = 0;
			}
			SetProsperity( nProsperity );
		}
		break;
		default:
			return;
	}
	StartSaveTimer();
	// ͬ��gameserver
	CS2GSFamilyProsperityUpdate xUpdate;
	xUpdate.nFamilyID = GetFamilyID();
	xUpdate.nProsperity = GetProsperity();
	theGameServerManager.SendMessageToGameServers( &xUpdate );

}

void CenterFamily::ProcessTransferPosition( const FamilyDefine::FamilyMember& requester, const FamilyDefine::FamilyMember& target )
{
	AddNeedSaveMember( requester.GetID() );
	AddNeedSaveMember( target.GetID() );
	StartSaveTimer();

	if ( target.GetPosition() == FamilyDefine::Position_Leader )
	{
		SetLeaderID( target.GetID() );
	}

	// ͬ��gameserver
	CS2GSFamilyTransferAck ack;
	ack.nFamilyID = GetFamilyID();
	ack.nRequesterID = requester.GetID();
	ack.nTargetPlayerID = target.GetID();
	theGameServerManager.SendMessageToGameServers( &ack );
}

void CenterFamily::ProcessDonate( FamilyDefine::FamilyMember& member, unsigned int nMoeny )
{
	Family::ProcessDonateMoney( member, nMoeny );
	StartSaveTimer();

	// ͬ��gameserver
	CS2GSFamilyDonateAck ack;
	ack.nFamilyID = GetFamilyID();
	ack.nRequesterID = member.GetID();
	ack.nMoney = nMoeny;
	theGameServerManager.SendMessageToGameServers( &ack );
}

void CenterFamily::ProcessUpgrade(const FamilyDefine::FamilyMember& member )
{
	StartSaveTimer();

	// ͬ��gameserver
	CS2GSFamilyUpgradeAck ack;
	ack.nRequesterID = member.GetID();
	ack.nFamilyID = GetFamilyID();
	ack.nNewLevel = GetFamilyLevel();
	ack.nNewMoney = GetMoney();
	ack.nNewProsperity = GetProsperity();
	theGameServerManager.SendMessageToGameServers( &ack );
}

void CenterFamily::UpdateInivte( unsigned int nCurrentTime )
{
	if ( _inviteRecords.empty() )
	{ return; }

	InviteRecordsContainerItr itr = _inviteRecords.begin();
	InviteRecordsContainerItr endItr = _inviteRecords.end();
	for ( ; itr != endItr; )
	{
		if ( GameTime::IsPassCurrentTime( nCurrentTime, itr->second.GetInviteTime(), FamilyDefine::InviteKeepTime ) )
		{ itr = _inviteRecords.erase( itr ); }
		else
		{ ++itr; }
	}
}

void CenterFamily::UpdateRequest( unsigned int nCurrentTime )
{
	if ( _requestRecords.empty() )
	{ return; }

	RequestRecordsContainerItr itr = _requestRecords.begin();
	RequestRecordsContainerItr endItr = _requestRecords.end();
	for ( ; itr != endItr; )
	{
		if ( GameTime::IsPassCurrentTime( nCurrentTime, itr->second.GetRequestTime(), FamilyDefine::RequestKeepTime ) )
		{ itr = _requestRecords.erase( itr ); }
		else
		{ ++itr; }
	}
}

void CenterFamily::UpdateMemberLeave( unsigned int nKeepTime )
{
	if ( _leaveTimeRecords.empty() )
	{ return; }

	MemberLeaveContainerItr itr = _leaveTimeRecords.begin();
	MemberLeaveContainerItr endItr = _leaveTimeRecords.end();
	for ( ; itr != endItr; )
	{
		if ( TimeEx::IsPassCurrentTime( itr->second, nKeepTime ) )
		{ itr = _leaveTimeRecords.erase( itr ); }
		else
		{ ++itr; }
	}
}

void CenterFamily::StartSaveTimer()
{
	_familyInfoSaveTimer.StartTimer( HQ_TimeGetTime(), FamilyDefine::SaveSpaveTime );
}

void CenterFamily::ProcessDisbandFamily()
{
	// �����ʼ���Ϣ�����в����ߵļ����Ա
	SendMailToAllMemberNotOnLine( FamilyDefine::Enum_Family_Disbanded );

	CS2DBFamilyDisbandReq req;
	req.nFamilyID = GetFamilyID();
	theMysqlCommunication.PushReqMessage( &req, 0 );

	CS2GSTellFamilyDisband tell;
	tell.nFamilyID = GetFamilyID();
	theGameServerManager.SendMessageToGameServers( &tell );

}

void CenterFamily::ProcessMemberOffline( FamilyDefine::FamilyMember& member )
{
	Family::ProcessMemberOffline( member );

	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( itr->second.GetOnLine() )
		{ break; }
	}
	if ( itr == endItr )
	{
		SetDisbandTime( HQ_TimeGetTime() );
	}
}


void CenterFamily::ProcessAllMemberOffline()
{
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; )
	{
		if ( itr->second.GetOnLine() )
		{
			SetDisbandTime( FamilyDefine::InvalidFamilyDisbandTime );
			StartSaveTimer();
			return; 
		}
		else
		{ ++itr; }
	}

	SetDisbandTime( HQ_TimeGetTime() );
	StartSaveTimer();

}
void CenterFamily::SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
	switch ( uchType )
	{
	case FamilyDefine::UpdateMemberOnLine:   // ����������ø������ݿ�
		if ( nValue == 1 )
		{ AddOnLineCount(); }
		else
		{ SubOnLineCount(); }
		break;
	default:
		AddNeedSaveMember( nPlayerID );    // ��ӽ������б�
		break;
	}

	// ֪ͨ�����з�����
	CS2GSFamilyMemberDataUpdate xUpdate;
	xUpdate.nFamilyID     = GetFamilyID();
	xUpdate.nPlayerID     = nPlayerID;
	xUpdate.uchUpdateType = uchType;
	xUpdate.nUpdateValue  = nValue;
	theGameServerManager.SendMessageToGameServers( &xUpdate );
}


void CenterFamily::ProcessFamilyPositionChange( FamilyDefine::FamilyMember* pMember, unsigned char uchPosition )
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

void CenterFamily::ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
	FamilyDefine::FamilyMember* pMember = GetMemberByID( nPlayerID );
	if ( pMember == NULL )
	{ return; }

	ProcessMemberDataUpdate( pMember, uchType, nValue );
}

void CenterFamily::ProcessMemberDataUpdate( FamilyDefine::FamilyMember* pMember, unsigned char uchType, unsigned int nValue )
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

	// �������ǵ����һ������
	if ( pMember->GetbFirstEnterWorld() && ( uchType == FamilyDefine::UpdateMemberOnLine ) && ( nValue == 1 ) )
	{
		pMember->SetbFirstEnterWorld( false );
		OperateProsperity( FamilyDefine::OperateAdd, theFamilyConfig.GetProsperitySetting().GetProsPerDay() );
	}

	SendMemberDataUpdateMessage( pMember->GetID(), uchType, nValue );
}

void CenterFamily::AddOnLineCount()
{
	++m_nOnLineCount;
}

void CenterFamily::SubOnLineCount()
{
	--m_nOnLineCount;
	if ( m_nOnLineCount < 0 )
	{ m_nOnLineCount = 0; }
}


// ��Ա����
void CenterFamily::ProcessEnterWorld( unsigned int nPlayerID )
{
	ProcessMemberDataUpdate( nPlayerID, GuildDefine::UpdateMemberOnLine, true );
}

// ��Ա����
void CenterFamily::ProcessExitWorld( unsigned int nPlayerID )
{
	ProcessMemberDataUpdate( nPlayerID, FamilyDefine::UpdateMemberOnLine, false );
}

// �����ж�����Ƿ��ǵ����һ�ν�����Ϸ��boolֵ
void CenterFamily::SetbFirstEnterWorld( bool bFirstEnterWorld )
{
	MemberContainerItr itr = _memberContainer.begin();
	MemberContainerItr endItr = _memberContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		itr->second.SetbFirstEnterWorld( bFirstEnterWorld );

		// ����������0:00����������ߣ�������幱��10�㷱�ٶ�
		if ( bFirstEnterWorld && itr->second.GetOnLine() )
		{
			this->SetProsperity( GetProsperity() + theFamilyConfig.GetProsperitySetting().GetProsPerDay() );
		}
	}

	StartSaveTimer();

	// ͬ��gameserver
	CS2GSFamilyProsperityUpdate xUpdate;
	xUpdate.nFamilyID = GetFamilyID();
	xUpdate.nProsperity = GetProsperity();
	theGameServerManager.SendMessageToGameServers( &xUpdate );
}

void CenterFamily::SendMessageToFamily( Msg* pMessage, unsigned int nExceptID, unsigned short nLevel, bool bSendToCenter)
{
	CS2GSFamilyMessage xMessage;
	xMessage.nFamilyID  = GetFamilyID();
	xMessage.nExceptID = nExceptID;
	xMessage.nLevel  = nLevel;
	xMessage.AddMessage( pMessage, pMessage->GetLength() );
	theGameServerManager.SendMessageToGameServers( &xMessage );
}

void CenterFamily::SaveFamilyAndMemberData()
{
	if ( _familyInfoSaveTimer.IsStart() )
	{ SaveFamilyDataToDatabase(); }

	SaveMemberDataToDatabase();
}
