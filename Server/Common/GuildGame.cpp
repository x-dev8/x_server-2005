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
	//发送全部的玩家的客户端去 做显示
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
    if ( bSendToCenter )        // 直接发送给CenterServer
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
            { continue; }   // 不在线, 或者指定人不发

            if ( iter->second.GetLevel() < ustLevel )
            { continue; }   // 小于等级限制

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
    // 通知帮会其他成员, 某某加入帮派了
    MsgTellJoinGuildToGuild xTell;
    xTell.xMember = xMember;
    SendMessageToGuild( &xTell, xMember.GetID() );

    // 如果在本服务器
    GamePlayer* pPlayer = GetPlayer( xMember.GetID() );
    if ( pPlayer)
	{
		pPlayer->SendMessageToClient(&xTell);
		 // 处理加入帮派逻辑
		pPlayer->ProcessJoinGuild( this );
	}

	// 发送帮派信息给客户端
    SendGuildDataToClient( xMember.GetID() );
}

template<>
void GameGuild::ProcessMemberLeaveGuild( unsigned int nPlayerID )
{
    // 通知帮派其他成员, 某某离开帮派了
    MsgTellLeaveGuildToGuild xTell;
    xTell.nPlayerID = nPlayerID;
    SendMessageToGuild( &xTell );
    // 加入离开帮派记录
    theGameGuildManager.AddLeaveGuild( nPlayerID );

    // 如果在本服务器
    GamePlayer* pPlayer = GetPlayer( nPlayerID );
    if ( pPlayer  )
	{
		pPlayer->SendMessageToClient(&xTell);
		// 处理离开帮派逻辑
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

   // 如果是帮主, 判断解散时间, 如果在解散时间内通知给他
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

    // 如果是家族长, 让他变成普通成员
    switch( pMember->GetPosition() )
    {
    case GuildDefine::Position_FamilyMaster:
        pMember->SetPosition( GuildDefine::Position_Member );
        ProcessGuildPositionChange( pMember, pMember->GetPosition() );    // 处理帮派职位改变
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
			//更新帮派职位 会长 给国家所有人发送 
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
					//发送给国家的人
					GettheServer().SendMsgToCountry( &msg, m_uchCountry, false );
				}
			}
		}
		break;
    default:
        break;
    }

    // 发送给所有帮派成员
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
        return; // 不需要更新给客户端
    default:
        break;
    }

    // 发送给所有帮派成员
    MsgGuildDataUpdate xUpdate;
    xUpdate.uchUpdateType = uchType;
    xUpdate.nUpdateValue  = n64Value;
    SendMessageToGuild( &xUpdate );

	if(uchType == GuildDefine::UpdateGuildMaster)
	{
		//通知所有服务器 公会会长的名称发生变化
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

    // 通知帮派所有成员
    MsgTellGuildNotice xTell;
    HelperFunc::SafeNCpy( xTell.szNotice, szNotice, sizeof( xTell.szNotice ) );
    SendMessageToGuild( &xTell );

	// 如果在本服务器
	GamePlayer* pPlayer = GetPlayer( this->GetMasterID() );
	if ( pPlayer == NULL )
	{ return; }
	pPlayer->SendOperateAckToClient< MsgGuildNoticeAck >( MsgGuildNoticeAck::ECD_Success );
};
template<>
void GameGuild::ProcessGuildNameChange(const char * Name)
{
    SetName( Name );

    // 通知给所有服务器
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

	// 通知帮派所有成员
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

    // 通知帮派所有成员
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
    // 发消息通知客户端
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

    // 发送给帮派成员
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
    // 保存数据
    m_uchConveneLevel = uchLevel;
    m_nConveneMapID   = nMapID;
    m_fConvenePosX    = fPosX;
    m_fConvenePosY    = fPosY;
    m_fConveneDir     = fDir;

    // 发送给客户端
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
