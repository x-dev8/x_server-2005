#include "Guild.h"
#include "GameServerManager.h"
#include "RelationManager.h"
#include "MySqlCommunication.h"
#include "CountryManager.h"
#include "VarClearConfig.h"
#include "GuildMissionConfig.h"
#include "LogEventService.h"
#include "XmlStringLanguage.h"
#include "..\CenterServer\Source\MailManagerMain.h"
#define MISSIONCOUNT_ZERO 0
#define MISSION_ZERO 0
template<>
void CenterGuild::SaveGuildDataToDatabase()
{
	//ÿ�α�������ݵ�ʱ��ʵʱ��һ�¹����ʵ��
	SetStrength(GetGuildStrength());

    CS2DBGuildDataUpdateReq xReq;
    xReq.xData = *this;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>
void CenterGuild::SaveMemberDataToDatabase()
{
    if ( m_setSave.empty() )
    { return; }

    CS2DBGuildMemberUpdateReq xReq;
    for ( SaveSetIter iter = m_setSave.begin(); iter != m_setSave.end(); ++iter )
    {
        GuildMember* pMember = GetMember( *iter );
        if ( pMember == NULL )
        { continue; }

        xReq.AddGuildMember( *pMember );
    }
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    m_setSave.clear();
}

template<>
void CenterGuild::ProcessMemberJoinGuild( const GuildMember& xMember )
{
    // �������ݿ�
    AddNeedSaveMember( xMember.GetID() );

    // �����ɢ����
    //ProcessDisbandTime();

    // ֪ͨGameServer
    CS2GSJoinGuildAck xAck;
    xAck.xMember = xMember;
    theGameServerManager.SendMessageToGameServers( &xAck );

    // ���¹�ϵ����
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( xMember.GetID() );
    if ( pRelation == NULL )
    { return; }     
    pRelation->UpdateRelationAttribute( RelationDefine::UpdateGuild, GetID() );
}
template<>
void CenterGuild::UpdateGuildMemberOnLineTime(unsigned int PlayerID,__int64 Time)
{
	GuildMember* pMember = GetMember(PlayerID);
	if(!pMember)
		return;
	pMember->SetOnLineTime(Time);
	AddNeedSaveMember( PlayerID );
	//����ȫ����GameServerȥ
	CS2GSUpdateGuildMemberOnLineTime msg;
	msg.PlayerID = PlayerID;
	msg.GuildID = GetID();
	msg.OnLineTime = Time;
	theGameServerManager.SendMessageToGameServers( &msg);
}
template<>
void CenterGuild::ProcessMemberLeaveGuild( unsigned int nPlayerID )
{
    // �����ɢ����
    //ProcessDisbandTime();

    // ����ǹ��ҹ�Ա, ��ȥ������ְλ �����뿪���ŵ�һ�����ǹ��� �ǹ����Ĺ�ְ�뿪���᲻����
    /*CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
    if ( pCountry != NULL )
    {
        unsigned char uchPosition = pCountry->GetPosition( nPlayerID );
        if ( uchPosition != CountryDefine::Position_None && uchPosition != CountryDefine::Position_Queen )
        {
            pCountry->ProcessCountryOfficialChange( uchPosition, CountryDefine::NoneID, "", 0,0,0,0);
        }
    }*/

    // ͬ��������Game������
    CS2GSLeaveGuildAck xAck;
    xAck.nPlayerID = nPlayerID;
    xAck.nGuildID  = GetID();
    theGameServerManager.SendMessageToGameServers( &xAck );

    // �������ݿ�
    CS2DBGuildMemberLeaveReq xReq;
    xReq.nPlayerID = nPlayerID;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    // ���¹�ϵ����
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL )
    { return; }     

    pRelation->UpdateRelationAttribute( RelationDefine::UpdateGuild, GuildDefine::InitID );
    pRelation->UpdateRelationAttribute( RelationDefine::UpdatePosition, GuildDefine::InitID );
}

template<>
void CenterGuild::ProcessDisbandTime()
{
    // ����ԱС��10��, 10����Զ���ɢ
    unsigned short nDisbandMemberCount = theGuildConfig.GetDisbandSetting().GetMinCount();

    if ( GetDisbandTime() == 0 )    // û���Զ���ɢ
    {
        if ( MemberCount() < nDisbandMemberCount )
        {
            ProcessGuildDataUpdate( GuildDefine::UpdateGuildDisbandTime, TimeEx::GetNowTime() );
        }
    }
    else
    {
        if ( MemberCount() >= nDisbandMemberCount )
        {
            ProcessGuildDataUpdate( GuildDefine::UpdateGuildDisbandTime, 0 );
        }
    }
}

template<>
void CenterGuild::ProcessDisbandGuild()
{
    CS2DBGuildDisbandReq xReqDB;
    xReqDB.nGuildID = GetID();
    theMysqlCommunication.PushReqMessage( &xReqDB, 0 );

    //����ǹ�������
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
    if ( pCountry != NULL )
    { 
        pCountry->ProcessCountryGuildCancel( GetID() );
    }
    
    // ֪ͨ��GameServer
    CS2GSDisbandGuildAck xAck;
    xAck.nGuildID = GetID();
    theGameServerManager.SendMessageToGameServers( &xAck );

	//���᳤ ���᳤ �����ʼ�
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// ������
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// �ռ���	
	xReq.mail.owners[EM_ToIndex].charDbId = GetMasterID();
	if(GetMember(GetMasterID()))
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetMember(GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	
	HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_Guild_Del_Title ) ,  sizeof( xReq.mail.title )* sizeof(int8));
	HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_Guild_Del_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
	xReq.mail.accessory.type = SMail::EAT_None;
	xReq.mail.money = 0;
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	if(GetViceMaster())//������᳤Ҳ���ڵĻ� �������᳤
	{
		xReq.mail.owners[EM_ToIndex].charDbId = GetViceMaster()->GetID();
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetViceMaster()->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );	
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	}
    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO ,"����[%s][%u]��ɢ", GetName(), GetID() );
}

template<>
unsigned short CenterGuild::RunUpdate( unsigned int nCurrentTime )
{
    // ���ж��Զ���ɢ
    if ( GetDisbandTime() != 0 )
    {
        unsigned int nKeepTime = theGuildConfig.GetDisbandSetting().GetKeepTime() * OneHourSecond;
        if ( TimeEx::IsPassCurrentTime( GetDisbandTime(), nKeepTime ) )
        {
            ProcessDisbandGuild();

			//LYH��־��� ��ϵͳ�Զ���ɢ����
			theLogEventService.LogGuild(0,0,GetID(),eSystemLogInfo_guild_disband,"NULL");
            return GuildDefine::UpdateDiaband;
        }
    }
	//else
	//{
	//	ProcessDisbandTime();
	//}

    // �������ݱ���
    if ( m_xDataSaveTimer.DoneTimer() )
    { SaveGuildDataToDatabase(); }

    // ��Ա���ݱ���
    if ( m_xMemberSaveTimer.DoneTimer( nCurrentTime ) )
    { SaveMemberDataToDatabase(); }

    // ���� �� �����¼ˢ��
    UpdateInivte( nCurrentTime );
    UpdateRequest( nCurrentTime );

    // ���������
    ProcessGuildDelateResult();

    // ������׳�ʱ
    ProcessGuildDonate(); 

    // ���񷢲���ʱ��
    if ( m_xReleaseTimer.DoneTimer() )
    { ProcessQuestRelease( 0, GetReleaseTime() ); }

    // �����ټ�
    ProcessGuildConveneTimeOut();

    // ÿ��1 0:00 ������а��ɳ�Ա�Ļ�Ծ��, ��հ��ɽ���
    static SYSTEMTIME xTime;
    ::GetLocalTime( &xTime );
	if ( xTime.wHour == 0 && xTime.wMinute == 0 && xTime.wDayOfWeek == 1 )
	{ 
        // 1���Ӻ�ִ��
        m_xUpdateSalaryTimer.StartTimer( HQ_TimeGetTime(), 65000 );
        m_xUpdateActivityTimer.StartTimer( HQ_TimeGetTime(), 70000 ); 
    }

    if ( m_xUpdateSalaryTimer.DoneTimer() )
    { ProcessClearGuildSalary(); }

    if ( m_xUpdateActivityTimer.DoneTimer() )
    { ProcessClearMemberActivity(); }

    // ÿ�³� �� ÿ���� ����һ��ʹ����
    //const GuildConfig::MissionSetting& xSetting = theGuildConfig.GetMissionSetting();
    //if ( xSetting.CheckDateSetting( xTime.wDay, xTime.wHour, xTime.wMinute ) )
    //{ m_xUpdateMissionTimer.StartTimer( HQ_TimeGetTime(), 70000 ); }    // 1���Ӻ�ִ��
    //if ( m_xUpdateMissionTimer.DoneTimer() )
    //{ ProcessGuildMissionSettle(); }

    return ProcessGuildVarClear();
}

template<>
void CenterGuild::UpdateInivte( unsigned int nCurrentTime )
{
    if ( m_mapInvite.empty() )
    { return; }

    for ( InviteMapIter iter = m_mapInvite.begin(); iter != m_mapInvite.end(); )
    {
        if ( GameTime::IsPassCurrentTime( nCurrentTime, iter->second.GetInviteTime(), GuildDefine::InviteKeepTime ) )
        {
            iter = m_mapInvite.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

template<>
void CenterGuild::UpdateRequest( unsigned int nCurrentTime )
{
    if ( m_mapRequest.empty() )
    { return; }

    for ( RequestMapIter iter = m_mapRequest.begin(); iter != m_mapRequest.end(); )
    {
        if ( GameTime::IsPassCurrentTime( nCurrentTime, iter->second.GetRequestTime(), GuildDefine::InviteKeepTime ) )
        {
			MsgGuildDelSQReq msg;
			msg.ID = iter->second.GetMember().GetID();
			GuildMember* pMastrtMember = GetMember( GetMasterID() );
			if ( pMastrtMember && pMastrtMember->GetOnLine() )
			{
				theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pMastrtMember->GetID() );
			}
			GuildMember* pViceMember = GetViceMaster();
			if ( pViceMember && pViceMember->GetOnLine() )
			{
				theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg, pViceMember->GetID() );
			}
			//���������ߵĻ� ����������ͻ��� ������������Ѿ����� ���Զ�ɾ��
			MsgJoinGuildAck xAck;
			xAck.uchResult = MsgJoinGuildAck::ECD_NotAgree;
			theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &xAck,iter->second.GetMember().GetID());

            iter = m_mapRequest.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

template<>
void CenterGuild::ProcessGuildDelateResult()
{
    if ( !m_xGuildDelate.DoneTimer() )
    { return; }

    const GuildConfig::DelateSetting& xSetting = theGuildConfig.GetDelateSetting();

    if ( m_xGuildDelate.GetID() == GuildDefine::InitID || m_xGuildDelate.GetTotalCount() == 0 )
    { return; }

    CS2GSGuildDelateResult xResult;
    xResult.nGuildID  = GetID();
    xResult.nPlayerID = m_xGuildDelate.GetID();

    // ���жϵ�����ҵ���Ч��
    GuildMember* pMember = GetMember( m_xGuildDelate.GetID() );
    if ( pMember == NULL )
    { 
        theGameServerManager.SendMessageToGameServers( &xResult );
        m_xGuildDelate.Reset();
        return;
    }

    // ͬ��ĸ���
    unsigned int nAgreeCount = m_xGuildDelate.GetAgreeCount();
    unsigned int nPercent = nAgreeCount * 100 / m_xGuildDelate.GetTotalCount();
    m_xGuildDelate.Reset();

    if ( nPercent < xSetting.GetRatio() )
    {     
        theGameServerManager.SendMessageToGameServers( &xResult );
        return;
    }

    // �ȷ�����Ϣ
    xResult.bDelateSuccess = true;
    theGameServerManager.SendMessageToGameServers( &xResult );

    // ������
    ProcessMemberDataUpdate( GetMasterID(), GuildDefine::UpdateMemberPosition, GuildDefine::Position_Member );
    ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberPosition, GuildDefine::Position_Master );
}

template<>  // ÿ��0����ɼ���������0
unsigned short CenterGuild::ProcessGuildVarClear()
{
    if ( !RecordTime::CheckRecordTime( m_nVarClearTime ) )
	{ return GuildDefine::UpdateNormal; }
    RecordTime::SaveRecordTime( m_nVarClearTime );

	unsigned short States = GuildDefine::UpdateNormal;
	//ÿ��۳�ָ��ֵ��ʹ����
	int Value = GetMission() - theGuildMissionConfig.GetMissionValue(GetLevel());
	if(Value <0)
		Value = 0;
	ProcessGuildDataUpdate(GuildDefine::UpdateGuildMission,Value);
	//�жϵ�ʹ����Ϊ0��ʱ�� ��ʾ����
	if(Value == 0)
	{
		States = ProcessGuildMissionSettle();
	}
	else
	{
		//ʹ�����ж���Ļ�
		//������᳤�����ʼ� ���߻᳤ ����ʹ���㲻��
		if(GetMissionCount() != MISSIONCOUNT_ZERO)
		{
			GS2CSSendMailReq xReq;
			xReq.charDbId = RelationDefine::InitID;
			xReq.mail.type  = SMail::EMT_System;
			xReq.mail.state = SMail::EMS_NotOpen;
			xReq.mail.sendTime = TimeEx::GetNowTime();        
			// ������
			xReq.mail.owners[EM_FromIndex].charDbId = 0;
			sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
			// �ռ���	
			xReq.mail.owners[EM_ToIndex].charDbId = GetMasterID();
			if(GetMember(GetMasterID()))
				HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetMember(GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
			HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_GuildMission_Non_Title ) ,  sizeof( xReq.mail.title )* sizeof(int8));
			HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_GuildMission_Non_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
			xReq.mail.accessory.type = SMail::EAT_None;
			xReq.mail.money = 0;
			theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
			if(GetViceMaster())//������᳤Ҳ���ڵĻ� �������᳤
			{
				xReq.mail.owners[EM_ToIndex].charDbId = GetViceMaster()->GetID();
				HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetViceMaster()->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );	
				theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
			}
		}
		ProcessGuildDataUpdate( GuildDefine::UpdateGuildMissionCount, MISSIONCOUNT_ZERO );
	}

    const VarClearConfig::VarMap& mapVar = theVarClearConfig.GetGuildVar();
    for ( VarClearConfig::VarMapConstIter iter = mapVar.begin(); iter != mapVar.end(); ++iter )
    {
        unsigned short nRecordTime = GetGuildVar( iter->first );
        if ( !RecordVarTime::CheckPassOneDay( nRecordTime ) )
        { continue; }

        unsigned short nNowTime = RecordVarTime::FormatTimeVar();
        OperateGuildVar( GuildDefine::OperateSet, iter->first, nNowTime );
        for ( VarClearConfig::VarVectorIter viter = iter->second.begin(); viter != iter->second.end(); ++viter )
        {
            OperateGuildVar( GuildDefine::OperateSet, *viter, 0 );
        }
    }
	return States;
}

template<>
void CenterGuild::ProcessClearGuildSalary()
{
    // ��հ��ɽ���
    ProcessGuildDataUpdate( GuildDefine::UpdateGuildSalary, 0 );
}

template<>
void CenterGuild::ProcessGuildDonate()
{
    if ( !m_xDonateTimer.DoneTimer() )
    { return; }

    SetDonateMoney( 0 );

    // ֪ͨGameServerֹͣ
    CS2GSGuildDonateStop xStop;
    xStop.nGuildID = GetID();
    theGameServerManager.SendMessageToGameServers( &xStop );
}

template<>
void CenterGuild::SaveGuildAndMemberData()
{
    if ( m_xDataSaveTimer.IsStart() )
    { SaveGuildDataToDatabase(); }
    
    SaveMemberDataToDatabase();
}

template<>
void CenterGuild::ProcessGuildPositionChange( GuildMember* pMember, unsigned char uchPosition )
{
    switch( uchPosition )
    {
    case GuildDefine::Position_Master:
        {
            SetMasterID( pMember->GetID() );

            // ����ǹ�����, Ҫ������, 
            CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
            if ( pCountry != NULL && pCountry->GetKingGuild() == GetID() )
            {
                pCountry->ProcessCountryOfficialChange( CountryDefine::Position_King, pMember->GetID(), pMember->GetName(),-1,-1,-1,-1);
				//��������
				/*CS2GSAddCountryOfficial msg;
				msg.uchCountryID = GetCountry();
				msg.uchPosition  = CountryDefine::Position_King;
				msg.nPlayerID    = pMember->GetID();
				theGameServerManager.SendMessageToGameServers( &msg );*/
            }
        }
        break;
    default:
        break;
    }
}   

template<>
void CenterGuild::ProcessMemberFamilyChange( GuildMember* pMember )
{
    if ( pMember == NULL )
    { return; }

    // ����Ǽ��峤, ���������ͨ��Ա
    if ( pMember->GetPosition() == GuildDefine::Position_FamilyMaster ) 
    { 
        pMember->SetPosition( GuildDefine::Position_Member ); 
    }
}   

template<>
void CenterGuild::SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    switch ( uchType )
    {
    case GuildDefine::UpdateMemberOnLine:   // ����������ø������ݿ�
        if ( nValue == 1 )
        { AddOnLineCount(); }
        else
        { SubOnLineCount(); }
        break;
    case GuildDefine::UpdateMemberExp:      // ��Ҿ�����GameServer�����߼�, ���ﲻ��Ҫ���
        break;
    default:
        AddNeedSaveMember( nPlayerID );    // ��ӽ������б�
        break;
    }

    // ֪ͨ�����з�����
    CS2GSMemberDataUpdate xUpdate;
    xUpdate.nGuildID      = GetID();
    xUpdate.nPlayerID     = nPlayerID;
    xUpdate.uchUpdateType = uchType;
    xUpdate.nUpdateValue  = nValue;
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterGuild::SendGuildDataUpdateMessage( unsigned char uchType, __int64 n64Value )
{
    StartSaveTimer();
    
    CS2GSGuildDataUpdate xUpdate;
    xUpdate.nGuildID       = GetID();
    xUpdate.uchUpdateType  = uchType;
    xUpdate.n64UpdateValue = n64Value;
    theGameServerManager.SendMessageToGameServers( &xUpdate );
}

template<>
void CenterGuild::ProcessEnterWorld( unsigned int nPlayerID )
{
    ProcessMemberDataUpdate( nPlayerID, GuildDefine::UpdateMemberOnLine, true );
}

template<>
void CenterGuild::ProcessExitWorld( unsigned int nPlayerID )
{
    ProcessMemberDataUpdate( nPlayerID, GuildDefine::UpdateMemberOnLine, false );
}

template<>
void CenterGuild::ProcessGuildNoticeChange( const char* szNotice )
{
    SetNotice( szNotice );
    StartSaveTimer();

    // ֪ͨ�����з�����
    CS2GSGuildNoticeChangeAck xAck;
    xAck.nGuildID = GetID();
    HelperFunc::SafeNCpy( xAck.szNotice, szNotice, sizeof( xAck.szNotice ) );
    theGameServerManager.SendMessageToGameServers( &xAck );
};
template<>
void CenterGuild::ProcessGuildNameChange(const char * Name)
{
    SetName( Name );
    StartSaveTimer();

    // ֪ͨ�����з�����
	CS2GSChangeGuildNameAck msg;
	msg.GuildID = GetID();
	strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,Name);
    theGameServerManager.SendMessageToGameServers( &msg );
};
template<>
void CenterGuild::ProcessGuildAimChange( const char* szAim, __int64 nTime )
{
	SetAim( szAim );
	SetChangeAimCD( TimeEx::GetNowTime() ); // �˴���������ʵʱ�仹����Ϸʱ��
	StartSaveTimer();

	// ֪ͨ�����з�����
	CS2GSGuildAimChangeAck xAck;
	xAck.nGuildID = GetID();
	xAck.nChangeAimTime = GetChangeAimCD();
	HelperFunc::SafeNCpy( xAck.szAim, szAim, sizeof( xAck.szAim ) );
	theGameServerManager.SendMessageToGameServers( &xAck );
};

template<>
void CenterGuild::ProcessRemoveFamily( unsigned char uchFamilyID )
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        if ( iter->second.GetFamilyID() != uchFamilyID )
        { continue; }

        ProcessMemberDataUpdate( &iter->second, GuildDefine::UpdateMemberFamily, GuildDefine::InitID );
        if ( iter->second.GetPosition() == GuildDefine::Position_FamilyMaster )     // ����Ǽ��峤
        {
            ProcessMemberDataUpdate( &iter->second, GuildDefine::UpdateMemberPosition, GuildDefine::Position_Member );
        }
    }
}

template<>
void CenterGuild::ProcessFamilyChange( unsigned int nPlayerID, unsigned char uchFamilyID, const char* szName )
{
    if ( uchFamilyID == GuildDefine::InitID || uchFamilyID > GuildDefine::MaxFamilyCount )
    { return; }

    SetFamilyName( uchFamilyID, szName );
    StartSaveTimer();

    if ( szName[0] == 0 )   // ɾ��һ������ʱ, ��Ҫ�����иü���ĳ�Ա��Ϣ�ı�
    {
        ProcessRemoveFamily( uchFamilyID );
    }

    // ͬ�������з�����
    CS2GSGuildFamilyChange xChange;
    xChange.nGuildID = GetID();
    xChange.uchFamilyID = uchFamilyID;
	xChange.nRequesterID = nPlayerID;
    HelperFunc::SafeNCpy( xChange.szName, szName, sizeof( xChange.szName ) );
    theGameServerManager.SendMessageToGameServers( &xChange );
}


template<>
void CenterGuild::SendGuildDataToClient( unsigned int nID )
{
    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nID );

    CS2GSGuildDataList xGuildData;
    xGuildData.xData = *this;

    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        xGuildData.AddGuildMember( iter->second );
    }

    if ( pGameServer != NULL )
    {
        pGameServer->Send( &xGuildData );
    }
    else
    {
        theGameServerManager.SendMessageToGameServers( &xGuildData );
    }
}

template<>
void CenterGuild::SendQuestReleaseStatusMessage()
{
    StartSaveTimer();

    // ����
    m_xReleaseTimer.StartTimer( HQ_TimeGetTime(), GuildDefine::ReleaseKeepTime );

    // ����Ϣ֪ͨ�ͻ���
    CS2GSGuildQuestReleaseStatus xStatus;
    xStatus.nGuildID       = GetID();
    xStatus.nQuestID       = GetReleaseQuest();
    xStatus.n64RelasetTime = GetReleaseTime();
    theGameServerManager.SendMessageToGameServers( &xStatus );
}

template<>
void CenterGuild::SendClearMemberActivityMessage()
{
    // ��ӱ���
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    { AddNeedSaveMember( iter->first ); }

    // ֪ͨ���з�����
    CS2GSGuildClearMemberActivity xClear;
    xClear.nGuildID = GetID();
    theGameServerManager.SendMessageToGameServers( &xClear );
}        
template<>
unsigned short CenterGuild::ProcessGuildMissionSettle()
{
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( GetLevel() );
    if ( pSetting == NULL )
    { return GuildDefine::UpdateNormal;; }

	if ( GetMission() ==0 /*<= pSetting->GetMaxMission()*/)
	{
		int nMissionCount =  GetMissionCount() + 1;
		SetMissionCount( nMissionCount );

		//������ʾ��Ϣ�����ɰ���
		CS2GSMissionNotEnuoughMessage xMessage;
		xMessage.nMissionCount = nMissionCount;
		xMessage.nMasterID = GetMasterID();

		ClientPeer* pClientPeer = theClientPeerManager.GetClientPeerByDBId( xMessage.nMasterID);
		if (pClientPeer)
		{  
			GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
			if ( pGameServer )
			{ 
				pGameServer->Send( &xMessage ); 
			}
		}

		//������᳤�����ʼ� ���߻᳤ ����ʹ���㲻��
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;
		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();        
		// ������
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// �ռ���	
		xReq.mail.owners[EM_ToIndex].charDbId = GetMasterID();
		if(GetMember(GetMasterID()))
			HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetMember(GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
		
		switch(GetMissionCount())
		{
		case GuildDefine::MissionFirst:
			HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_GuildMission_First_Title ) ,  sizeof( xReq.mail.title )* sizeof(int8));
			HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_GuildMission_First_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
			break;
		case GuildDefine::MissionSecond:
			HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_GuildMission_Two_Title ),  sizeof( xReq.mail.title )* sizeof(int8));
			HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_GuildMission_Two_Context ),  sizeof( xReq.mail.content )* sizeof(int8));
			break;
		case GuildDefine::MissionThird:
			HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_GuildMission_Three_Title ),  sizeof( xReq.mail.title )* sizeof(int8));
			HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_GuildMission_Three_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
			break;
		default:
			HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_GuildMission_Three_Title ),  sizeof( xReq.mail.title )* sizeof(int8));
			HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_GuildMission_Three_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
			break;
		}
		xReq.mail.accessory.type = SMail::EAT_None;
		xReq.mail.money = 0;
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
		if(GetViceMaster())//������᳤Ҳ���ڵĻ� �������᳤
		{
			xReq.mail.owners[EM_ToIndex].charDbId = GetViceMaster()->GetID();
			HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetViceMaster()->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );	
			theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
		}

		// ��������δ�ﵽָ��ʹ���㣬�����ɢ���ɵ��߼�
		if ( nMissionCount >= GuildDefine::MissionThird )
		{
			//LYH��־��� �������ɢ��
			//theLogEventService.LogGuild(0,0,GetID(),eSystemLogInfo_guild_disband);
			ProcessDisbandGuild();
			return GuildDefine::UpdateDiaband;
		}
	
	}
	else
	{
		// ʹ������գ�ʹ����������
		SetMission( MISSION_ZERO );
		SetMissionCount( MISSIONCOUNT_ZERO );
		ProcessGuildDataUpdate( GuildDefine::UpdateGuildMission, MISSION_ZERO );
		ProcessGuildDataUpdate( GuildDefine::UpdateGuildMissionCount, MISSIONCOUNT_ZERO );

	}
	//ע�Ͳ���luo.qin 4.21 begin
    //if ( GetMission() <= pSetting->GetMaxMission() )
    //{ return; } // û�дﵽ���ֵ������

    //// �����ȫ���һ��ɰ��ɾ���
    //unsigned int nMission = GetMission() - pSetting->GetMaxMission();

    //// �ȸ���ʹ����
    //ProcessGuildDataUpdate( GuildDefine::UpdateGuildMission, pSetting->GetMaxMission() );

    //// �����ʹ����һ��ɰ��ɾ���
    //const GuildConfig::MissionSetting& xSetting = theGuildConfig.GetMissionSetting();
    //OperateGuildExp( GuildDefine::OperateAdd, nMission * xSetting.GetGuildExp() );
	//ע�Ͳ���luo.qin 4.21 end
	return GuildDefine::UpdateNormal;
}

template<>
void CenterGuild::ProcessGuildDelateRequest( unsigned int nPlayerID )
{
    GuildMember* pMember = GetMember( nPlayerID );
    if ( pMember == NULL )
    { return; }

    if ( m_xGuildDelate.GetID() != GuildDefine::InitID )
    { return; }

    const GuildConfig::DelateSetting& xSetting = theGuildConfig.GetDelateSetting();
    if ( GetOnLineCount() < xSetting.GetMinCount() )
    { return; }

    m_xGuildDelate.SetID( nPlayerID );
    m_xGuildDelate.SetTotalCount( GetOnLineCount() );
    m_xGuildDelate.ClearAgreeCount();
    m_xGuildDelate.StartTimer( HQ_TimeGetTime(), GuildDefine::DelateKeepTime );

    // ֪ͨ�����з�����
    CS2GSGuildDelateRequestReq xReq;
    xReq.nGuildID  = GetID();
    xReq.nPlayerID = nPlayerID;
    theGameServerManager.SendMessageToGameServers( &xReq );
}

template<>
void CenterGuild::SendMessageToGuild( Msg* pMessage, unsigned int nExceptID, unsigned short ustLevel, bool bSendToCenter )
{
    CS2GSGuildMessage xMessage;
    xMessage.nGuildID  = GetID();
    xMessage.nExceptID = nExceptID;
    xMessage.ustLevel  = ustLevel;
    xMessage.AddMessage( pMessage, pMessage->GetLength() );
    theGameServerManager.SendMessageToGameServers( &xMessage );
}

template<>
void CenterGuild::ProcessGuildConveneReq( unsigned int nPlayerID, unsigned int nMapID, float fPosX, float fPosY, float fDir, unsigned char uchLevel )
{
    // ������ʱ��
    m_xConveneTimer.StartTimer( HQ_TimeGetTime(), GuildDefine::ConveneKeepTime );

    // ���͸�GameServer
    CS2GSGuildConveneReq xReq;
    xReq.nGuildID  = GetID();
    xReq.nPlayerID = nPlayerID;
    xReq.nMapID    = nMapID;
    xReq.fPosX     = fPosX;
    xReq.fPosY     = fPosY;
    xReq.fDir      = fDir;
    xReq.uchLevel  = uchLevel;
    theGameServerManager.SendMessageToGameServers( &xReq );
}

template<>
void CenterGuild::ProcessGuildConveneTimeOut()
{
    if ( !m_xConveneTimer.DoneTimer() )
    { return; }

    // ������Ϣ��GameServer
    CS2GSGuildConveneStop xStop;
    xStop.nGuildID = GetID();
    theGameServerManager.SendMessageToGameServers( &xStop );
}
template<>
void CenterGuild::SendAllRequest(uint32 PlayerID)
{
	//�����������͵��ͻ���
	if(m_mapRequest.empty()) return;
	RequestMapIter Iter  = m_mapRequest.begin();
	MsgGuildSQAck msg;
	for(;Iter != m_mapRequest.end();++Iter)
	{
		GuildRequest* pGR = &Iter->second;
		msg.pushItem(pGR->GetMember().GetID(),pGR->GetMember().GetLevel(),pGR->GetMember().GetProfession(),pGR->GetMember().GetName());
	}
	msg.CaluLength();
	theGameServerManager.SendMsgToSingleRemote( GuildDefine::InitID, &msg,PlayerID );
}