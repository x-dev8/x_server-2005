#include "Guild.h"
#include "GamePlayer.h"
#include "ShareData.h"

template<>
GamePlayer* GameGuild::GetPlayer( unsigned int nPlayerID )
{
    return theRunTimeData.GetGamePlayerByDBID( nPlayerID );
}
template<>
void GameGuild::UpdateGuildMemberOnLineTime(unsigned int PlayerID,__int64 Time)
{
	GuildMember* pMember = GetMember(PlayerID);
	if(!pMember)
		return;
	pMember->SetOnLineTime(Time);
	//����ȫ������ҵĿͻ���ȥ ����ʾ
	MsgUpdateGuildMemberOnLineTime msg;
	msg.PlayerID = PlayerID;
	msg.GuildID = GetID();
	msg.OnLineTime = Time;
	SendMessageToGuild(&msg);
}
template<>
void GameGuild::SendGuildDataToClient( unsigned int nAppointID )
{
    GamePlayer* pPlayer = GetPlayer( nAppointID );
    if ( pPlayer == NULL )
    { return; }

    MsgTellGuildData xTell;
    xTell.xData = *this ;

    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        xTell.AddMember( iter->second );
    }

    pPlayer->SendMessageToClient( &xTell );
}

template<>
void GameGuild::SendMessageToGuild( Msg* pMessage, unsigned int nExceptID, unsigned short ustLevel, bool bSendToCenter )
{
    if ( bSendToCenter )        // ֱ�ӷ��͸�CenterServer
    {
        GS2CSGuildMessage xMessage;
        xMessage.nGuildID  = GetID();
        xMessage.nExceptID = nExceptID;
        xMessage.ustLevel  = ustLevel;
        xMessage.AddMessage( pMessage, pMessage->GetLength() );
        GettheServer().SendMsgToCenterServer( &xMessage );
    }
    else
    {
        for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
        {
            if ( !iter->second.GetOnLine() || iter->second.GetID() == nExceptID )
            { continue; }   // ������, ����ָ���˲���

            if ( iter->second.GetLevel() < ustLevel )
            { continue; }   // С�ڵȼ�����

            GamePlayer* pPlayer = GetPlayer( iter->second.GetID() );
            if ( pPlayer == NULL )
            { continue; }

            pPlayer->SendMessageToClient( pMessage );
        }
    }
}

template<>
void GameGuild::ProcessMemberJoinGuild( const GuildMember& xMember )
{
    // ֪ͨ���������Ա, ĳĳ���������
    MsgTellJoinGuildToGuild xTell;
    xTell.xMember = xMember;
    SendMessageToGuild( &xTell, xMember.GetID() );

    // ����ڱ�������
    GamePlayer* pPlayer = GetPlayer( xMember.GetID() );
    if ( pPlayer)
	{
		pPlayer->SendMessageToClient(&xTell);
		 // �����������߼�
		pPlayer->ProcessJoinGuild( this );
	}

	// ���Ͱ�����Ϣ���ͻ���
    SendGuildDataToClient( xMember.GetID() );
}

template<>
void GameGuild::ProcessMemberLeaveGuild( unsigned int nPlayerID )
{
    // ֪ͨ����������Ա, ĳĳ�뿪������
    MsgTellLeaveGuildToGuild xTell;
    xTell.nPlayerID = nPlayerID;
    SendMessageToGuild( &xTell );
    // �����뿪���ɼ�¼
    theGameGuildManager.AddLeaveGuild( nPlayerID );

    // ����ڱ�������
    GamePlayer* pPlayer = GetPlayer( nPlayerID );
    if ( pPlayer  )
	{
		pPlayer->SendMessageToClient(&xTell);
		// �����뿪�����߼�
		pPlayer->ProcessLeaveGuild( this );
	}   
}

template<>
void GameGuild::ProcessDisbandGuild()
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        GamePlayer* pPlayer = GetPlayer( iter->second.GetID() );
        if ( pPlayer == NULL )
        { continue; }

        pPlayer->ProcessLeaveGuild( this );
    }

    m_mapMember.clear();
}

template<>
void GameGuild::ProcessEnterWorld( unsigned int nPlayerID )
{
   SendGuildDataToClient( nPlayerID );

   // ����ǰ���, �жϽ�ɢʱ��, ����ڽ�ɢʱ����֪ͨ����
    if ( GetDisbandTime() != 0 && GetMasterID() == nPlayerID )
    {
        GamePlayer* pPlayer = GetPlayer( nPlayerID );
        if ( pPlayer != NULL )
        {
            TimeEx xDisbandTime( GetDisbandTime() );

            unsigned long nKeepTime = theGuildConfig.GetDisbandSetting().GetKeepTime() * OneHourSecond;
            TimeSpan xSpan( nKeepTime );
            xDisbandTime += xSpan;

            MsgTellGuildDisbanTime xTell;
            xTell.n64DisbandTime = xDisbandTime.GetTime();
            pPlayer->SendMessageToClient( &xTell );
        }
    }
}

template<>
void GameGuild::ProcessGuildPositionChange( GuildMember* pMember, unsigned char uchPosition )
{
    switch ( uchPosition )
    {
    case GuildDefine::Position_Master:
        ProcessGuildDataUpdate( GuildDefine::UpdateGuildMaster, pMember->GetID() );
        break;
    default:
        break;
    }

    GamePlayer* pPlayer = GetPlayer( pMember->GetID() );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->ProcessGuildPositionChange();
}   

template<>
void GameGuild::ProcessMemberFamilyChange( GuildMember* pMember )
{
    if ( pMember == NULL )
    { return; }

    // ����Ǽ��峤, ���������ͨ��Ա
    switch( pMember->GetPosition() )
    {
    case GuildDefine::Position_FamilyMaster:
        pMember->SetPosition( GuildDefine::Position_Member );
        ProcessGuildPositionChange( pMember, pMember->GetPosition() );    // �������ְλ�ı�
        break;
    default:
        break;
    }
}   

template<>
void GameGuild::SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    switch ( uchType )
    {
    case GuildDefine::UpdateMemberExp:
        return ProcessUpdateMemberExp( nPlayerID, nValue );
        break;
	case GuildDefine::UpdateMemberPosition:
		{
			//���°���ְλ �᳤ �����������˷��� 
			if(GuildDefine::Position_Master == nValue)
			{
				MsgGuildClientUpdate msg;
				msg.ClientInfo.SetID(m_nID);
				msg.ClientInfo.SetMemberNum(m_mapMember.size());
				msg.ClientInfo.SetCountry(m_uchCountry);
				msg.ClientInfo.SetLevel(m_uchLevel);
				msg.ClientInfo.SetName(m_szName);
				if(m_mapMember.count(m_nMasterID) == 1)
				{
					msg.ClientInfo.SetMasterName(m_mapMember[m_nMasterID].GetName());
					//���͸����ҵ���
					GettheServer().SendMsgToCountry( &msg, m_uchCountry, false );
				}
			}
		}
		break;
    default:
        break;
    }

    // ���͸����а��ɳ�Ա
    MsgMemberDataUpdate xUpdate;
    xUpdate.nPlayerID     = nPlayerID;
    xUpdate.uchUpdateType = uchType;
    xUpdate.nUpdateValue  = nValue;
    SendMessageToGuild( &xUpdate );
}

template<>
void GameGuild::SendGuildDataUpdateMessage( unsigned char uchType, __int64 n64Value )
{
    switch ( uchType )
    {
    case GuildDefine::UpdateGuildVar:
    case GuildDefine::UpdateGuildDonate:
    case GuildDefine::UpdateGuildDisbandTime:
        return; // ����Ҫ���¸��ͻ���
    default:
        break;
    }

    // ���͸����а��ɳ�Ա
    MsgGuildDataUpdate xUpdate;
    xUpdate.uchUpdateType = uchType;
    xUpdate.nUpdateValue  = n64Value;
    SendMessageToGuild( &xUpdate );

	if(uchType == GuildDefine::UpdateGuildMaster)
	{
		//֪ͨ���з����� ����᳤�����Ʒ����仯
		MsgGuildChangeNameAck msg;
		msg.GuildID = GetID();
		msg.PlayerID = GetMasterID();
		GuildMember* pMaster = GetMember(GetMasterID());
		if(pMaster)
		{
			strcpy_s(msg.szName,sizeof(msg.szName),pMaster->GetName());
			GettheServer().SendMsgToWorld(&msg);
		}	
	}
}

template<>
void GameGuild::ProcessGuildNoticeChange( const char* szNotice )
{
    SetNotice( szNotice );

    // ֪ͨ�������г�Ա
    MsgTellGuildNotice xTell;
    HelperFunc::SafeNCpy( xTell.szNotice, szNotice, sizeof( xTell.szNotice ) );
    SendMessageToGuild( &xTell );

	// ����ڱ�������
	GamePlayer* pPlayer = GetPlayer( this->GetMasterID() );
	if ( pPlayer == NULL )
	{ return; }
	pPlayer->SendOperateAckToClient< MsgGuildNoticeAck >( MsgGuildNoticeAck::ECD_Success );
};
template<>
void GameGuild::ProcessGuildNameChange(const char * Name)
{
    SetName( Name );

    // ֪ͨ�����з�����
	MsgChangeGuldNameAck msg;
	msg.GuildID = GetID();
	msg.IsCanChange = true;
	strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,Name);
	GettheServer().SendMsgToWorld(&msg);
};
template<>
void GameGuild::ProcessGuildAimChange( const char* szAim, __int64 nTime )
{
	SetAim( szAim );
    SetChangeAimCD( nTime );

	// ֪ͨ�������г�Ա
	MsgTellGuildAim xTell;
	HelperFunc::SafeNCpy( xTell.szAim, szAim, sizeof( xTell.szAim ) );
	SendMessageToGuild( &xTell );
};

template<>
void GameGuild::ProcessFamilyChange( unsigned int nPlayerID, unsigned char uchFamilyID, const char* szName )
{
    if ( uchFamilyID == GuildDefine::InitID || uchFamilyID > GuildDefine::MaxFamilyCount )
    { return; }

    SetFamilyName( uchFamilyID, szName );

    // ֪ͨ�������г�Ա
    MsgTellGuildFamilyChange xChange;
    xChange.uchFamilyID = uchFamilyID;
    HelperFunc::SafeNCpy( xChange.szName, szName, sizeof( xChange.szName ) );
    SendMessageToGuild( &xChange );

	GamePlayer* pPlayer = GetPlayer( nPlayerID );
	if ( pPlayer && szName )
	{
		pPlayer->SendOperateAckToClient< MsgGuildFamilyChangeAck >( MsgGuildFamilyChangeAck::ECD_Success );
	}
}

template<>
void GameGuild::SendGuildDataChangeReqMessage( unsigned char uchChangeType, unsigned char uchOperateType, unsigned int nValue )
{
    GS2CSGuildDataChangeReq xReq;
    xReq.nGuildID       = GetID();
    xReq.uchChangeType  = uchChangeType;
    xReq.uchOperateType = uchOperateType;
    xReq.nValue         = nValue;
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameGuild::SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue )
{
    GS2CSMemberDataChangeReq xReq;
    xReq.nGuildID       = GetID();
    xReq.nPlayerID      = nPlayerID;
    xReq.uchChangeType  = uchChangeType;
    xReq.uchOperateType = uchOperatetype;
    xReq.nValue         = nValue;
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameGuild::ProcessUpdateMemberExp( unsigned int nPlayerID, unsigned int nValue )
{
    GamePlayer* pPlayer = GetPlayer( nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->IncreaseExp( nValue, 0 );
}

template<>
void GameGuild::SetCountryTitle( unsigned char uchMemberTitle, unsigned char uchMasterTitle )
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        GamePlayer* pPlayer = GetPlayer( iter->second.GetID() );
        if ( pPlayer == NULL )
        { continue; }

        switch ( iter->second.GetPosition() )
        {
        case GuildDefine::Position_Master:
            pPlayer->SetCountryTitle( uchMasterTitle, true );
            break;
        default:
            pPlayer->SetCountryTitle( uchMemberTitle, true );
            break;
        }
    }
}

template<>
void GameGuild::ClearCountryTitle()
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        GamePlayer* pPlayer = GetPlayer( iter->second.GetID() );
        if ( pPlayer == NULL )
        { continue; }

        uint8 uchCountryTitle = CountryDefine::Title_GuildMember;
        switch ( iter->second.GetPosition() )
        {
        case GuildDefine::Position_Master:
            uchCountryTitle = CountryDefine::Title_GuildMaster;
            break;
        case GuildDefine::Position_ViceMaster:
            uchCountryTitle = CountryDefine::Title_ViceMaster;
            break;
        case GuildDefine::Position_FamilyMaster:
            uchCountryTitle = CountryDefine::Title_FamilyMaster;
            break;
        default:
            break;
        }

        pPlayer->SetCountryTitle( uchCountryTitle, true );
    }
}

template<>
void GameGuild::SendQuestReleaseStatusMessage()
{
    // ����Ϣ֪ͨ�ͻ���
    MsgGuildQuestReleaseStatus xStatus;
    xStatus.nQuestType     = GetReleaseQuest();
    xStatus.n64RelasetTime = GetReleaseTime();
    SendMessageToGuild( &xStatus );
}

template<>
void GameGuild::SendClearMemberActivityMessage()
{
    MsgGuildClearMemberActivity xClear;
    SendMessageToGuild( &xClear );
}

template<>
void GameGuild::ProcessGuildDelateRequest( unsigned int nPlayerID )
{
    m_xGuildDelate.SetID( nPlayerID );

    // ���͸����ɳ�Ա
    MsgGuildDelateAgreeReq xReq;
    xReq.nPlayerID = nPlayerID;
    SendMessageToGuild( &xReq, GetMasterID() );

    GamePlayer* pPlayer = GetPlayer( nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    const GuildConfig::DelateSetting& xSetting = theGuildConfig.GetDelateSetting();
    pPlayer->OperateMoney( EOT_Sub, xSetting.GetCostMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_GuildDelate );
}

template<>
void GameGuild::ProcessGuildConveneReq( unsigned int nPlayerID, unsigned int nMapID, float fPosX, float fPosY, float fDir, unsigned char uchLevel )
{
    // ��������
    m_uchConveneLevel = uchLevel;
    m_nConveneMapID   = nMapID;
    m_fConvenePosX    = fPosX;
    m_fConvenePosY    = fPosY;
    m_fConveneDir     = fDir;

    // ���͸��ͻ���
    MsgGuildConveneReq xReq;
    xReq.nMapID = nMapID;
    SendMessageToGuild( &xReq, nPlayerID, uchLevel, false );
}

template<>
void GameGuild::ProcessGuildConveneAck( GamePlayer* pPlayer )
{
    if ( m_nConveneMapID == 0 )
    { return; }

    if ( pPlayer->GetLevel() < m_uchConveneLevel )
    { return; }

    pPlayer->FlyToMapReq( m_nConveneMapID, m_fConvenePosX, m_fConvenePosY, m_fConveneDir );
}

template<>
void GameGuild::ProcessGuildConveneTimeOut()
{
    m_uchConveneLevel = 0;
    m_nConveneMapID   = 0;
    m_fConvenePosX    = 0.0f;
    m_fConvenePosY    = 0.0f;
    m_fConveneDir     = 0.0f;
}
