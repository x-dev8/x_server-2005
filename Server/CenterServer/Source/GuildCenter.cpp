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
	//每次保存的数据的时候实时算一下工会的实力
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
    // 保存数据库
    AddNeedSaveMember( xMember.GetID() );

    // 计算解散日期
    //ProcessDisbandTime();

    // 通知GameServer
    CS2GSJoinGuildAck xAck;
    xAck.xMember = xMember;
    theGameServerManager.SendMessageToGameServers( &xAck );

    // 更新关系属性
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
	//发送全部的GameServer去
	CS2GSUpdateGuildMemberOnLineTime msg;
	msg.PlayerID = PlayerID;
	msg.GuildID = GetID();
	msg.OnLineTime = Time;
	theGameServerManager.SendMessageToGameServers( &msg);
}
template<>
void CenterGuild::ProcessMemberLeaveGuild( unsigned int nPlayerID )
{
    // 计算解散日期
    //ProcessDisbandTime();

    // 如果是国家官员, 先去除国家职位 可以离开军团的一定不是国王 非国王的官职离开公会不处理
    /*CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
    if ( pCountry != NULL )
    {
        unsigned char uchPosition = pCountry->GetPosition( nPlayerID );
        if ( uchPosition != CountryDefine::Position_None && uchPosition != CountryDefine::Position_Queen )
        {
            pCountry->ProcessCountryOfficialChange( uchPosition, CountryDefine::NoneID, "", 0,0,0,0);
        }
    }*/

    // 同步给所有Game服务器
    CS2GSLeaveGuildAck xAck;
    xAck.nPlayerID = nPlayerID;
    xAck.nGuildID  = GetID();
    theGameServerManager.SendMessageToGameServers( &xAck );

    // 更新数据库
    CS2DBGuildMemberLeaveReq xReq;
    xReq.nPlayerID = nPlayerID;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    // 更新关系属性
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL )
    { return; }     

    pRelation->UpdateRelationAttribute( RelationDefine::UpdateGuild, GuildDefine::InitID );
    pRelation->UpdateRelationAttribute( RelationDefine::UpdatePosition, GuildDefine::InitID );
}

template<>
void CenterGuild::ProcessDisbandTime()
{
    // 帮会成员小于10个, 10天后自动解散
    unsigned short nDisbandMemberCount = theGuildConfig.GetDisbandSetting().GetMinCount();

    if ( GetDisbandTime() == 0 )    // 没有自动解散
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

    //如果是国王帮派
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
    if ( pCountry != NULL )
    { 
        pCountry->ProcessCountryGuildCancel( GetID() );
    }
    
    // 通知给GameServer
    CS2GSDisbandGuildAck xAck;
    xAck.nGuildID = GetID();
    theGameServerManager.SendMessageToGameServers( &xAck );

	//给会长 副会长 发送邮件
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// 发信人
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// 收件人	
	xReq.mail.owners[EM_ToIndex].charDbId = GetMasterID();
	if(GetMember(GetMasterID()))
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetMember(GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	
	HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_Guild_Del_Title ) ,  sizeof( xReq.mail.title )* sizeof(int8));
	HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_Guild_Del_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
	xReq.mail.accessory.type = SMail::EAT_None;
	xReq.mail.money = 0;
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	if(GetViceMaster())//如果副会长也存在的话 发给副会长
	{
		xReq.mail.owners[EM_ToIndex].charDbId = GetViceMaster()->GetID();
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetViceMaster()->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );	
		theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
	}
    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO ,"帮派[%s][%u]解散", GetName(), GetID() );
}

template<>
unsigned short CenterGuild::RunUpdate( unsigned int nCurrentTime )
{
    // 先判断自动解散
    if ( GetDisbandTime() != 0 )
    {
        unsigned int nKeepTime = theGuildConfig.GetDisbandSetting().GetKeepTime() * OneHourSecond;
        if ( TimeEx::IsPassCurrentTime( GetDisbandTime(), nKeepTime ) )
        {
            ProcessDisbandGuild();

			//LYH日志添加 ，系统自动解散工会
			theLogEventService.LogGuild(0,0,GetID(),eSystemLogInfo_guild_disband,"NULL");
            return GuildDefine::UpdateDiaband;
        }
    }
	//else
	//{
	//	ProcessDisbandTime();
	//}

    // 帮派数据保存
    if ( m_xDataSaveTimer.DoneTimer() )
    { SaveGuildDataToDatabase(); }

    // 成员数据保存
    if ( m_xMemberSaveTimer.DoneTimer( nCurrentTime ) )
    { SaveMemberDataToDatabase(); }

    // 邀请 和 申请记录刷新
    UpdateInivte( nCurrentTime );
    UpdateRequest( nCurrentTime );

    // 处理弹劾结果
    ProcessGuildDelateResult();

    // 处理捐献超时
    ProcessGuildDonate(); 

    // 任务发布定时器
    if ( m_xReleaseTimer.DoneTimer() )
    { ProcessQuestRelease( 0, GetReleaseTime() ); }

    // 帮派召集
    ProcessGuildConveneTimeOut();

    // 每周1 0:00 清除所有帮派成员的活跃度, 清空帮派津贴
    static SYSTEMTIME xTime;
    ::GetLocalTime( &xTime );
	if ( xTime.wHour == 0 && xTime.wMinute == 0 && xTime.wDayOfWeek == 1 )
	{ 
        // 1分钟后执行
        m_xUpdateSalaryTimer.StartTimer( HQ_TimeGetTime(), 65000 );
        m_xUpdateActivityTimer.StartTimer( HQ_TimeGetTime(), 70000 ); 
    }

    if ( m_xUpdateSalaryTimer.DoneTimer() )
    { ProcessClearGuildSalary(); }

    if ( m_xUpdateActivityTimer.DoneTimer() )
    { ProcessClearMemberActivity(); }

    // 每月初 和 每月中 结算一次使命点
    //const GuildConfig::MissionSetting& xSetting = theGuildConfig.GetMissionSetting();
    //if ( xSetting.CheckDateSetting( xTime.wDay, xTime.wHour, xTime.wMinute ) )
    //{ m_xUpdateMissionTimer.StartTimer( HQ_TimeGetTime(), 70000 ); }    // 1分钟后执行
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
			//如果玩家在线的话 发送命令道客户端 告诉玩家申请已经到期 被自动删除
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

    // 先判断弹劾玩家的有效性
    GuildMember* pMember = GetMember( m_xGuildDelate.GetID() );
    if ( pMember == NULL )
    { 
        theGameServerManager.SendMessageToGameServers( &xResult );
        m_xGuildDelate.Reset();
        return;
    }

    // 同意的个数
    unsigned int nAgreeCount = m_xGuildDelate.GetAgreeCount();
    unsigned int nPercent = nAgreeCount * 100 / m_xGuildDelate.GetTotalCount();
    m_xGuildDelate.Reset();

    if ( nPercent < xSetting.GetRatio() )
    {     
        theGameServerManager.SendMessageToGameServers( &xResult );
        return;
    }

    // 先发送消息
    xResult.bDelateSuccess = true;
    theGameServerManager.SendMessageToGameServers( &xResult );

    // 换帮主
    ProcessMemberDataUpdate( GetMasterID(), GuildDefine::UpdateMemberPosition, GuildDefine::Position_Member );
    ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberPosition, GuildDefine::Position_Master );
}

template<>  // 每天0点帮派记数变量清0
unsigned short CenterGuild::ProcessGuildVarClear()
{
    if ( !RecordTime::CheckRecordTime( m_nVarClearTime ) )
	{ return GuildDefine::UpdateNormal; }
    RecordTime::SaveRecordTime( m_nVarClearTime );

	unsigned short States = GuildDefine::UpdateNormal;
	//每天扣除指定值的使命点
	int Value = GetMission() - theGuildMissionConfig.GetMissionValue(GetLevel());
	if(Value <0)
		Value = 0;
	ProcessGuildDataUpdate(GuildDefine::UpdateGuildMission,Value);
	//判断当使命点为0的时候 提示帮派
	if(Value == 0)
	{
		States = ProcessGuildMissionSettle();
	}
	else
	{
		//使命点有多余的话
		//给公会会长发送邮件 告诉会长 公会使命点不足
		if(GetMissionCount() != MISSIONCOUNT_ZERO)
		{
			GS2CSSendMailReq xReq;
			xReq.charDbId = RelationDefine::InitID;
			xReq.mail.type  = SMail::EMT_System;
			xReq.mail.state = SMail::EMS_NotOpen;
			xReq.mail.sendTime = TimeEx::GetNowTime();        
			// 发信人
			xReq.mail.owners[EM_FromIndex].charDbId = 0;
			sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
			// 收件人	
			xReq.mail.owners[EM_ToIndex].charDbId = GetMasterID();
			if(GetMember(GetMasterID()))
				HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetMember(GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
			HelperFunc::SafeNCpy( xReq.mail.title,theXmlString.GetString( eText_GuildMission_Non_Title ) ,  sizeof( xReq.mail.title )* sizeof(int8));
			HelperFunc::SafeNCpy( xReq.mail.content,theXmlString.GetString( eText_GuildMission_Non_Context ) ,  sizeof( xReq.mail.content )* sizeof(int8));
			xReq.mail.accessory.type = SMail::EAT_None;
			xReq.mail.money = 0;
			theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
			if(GetViceMaster())//如果副会长也存在的话 发给副会长
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
    // 清空帮派津贴
    ProcessGuildDataUpdate( GuildDefine::UpdateGuildSalary, 0 );
}

template<>
void CenterGuild::ProcessGuildDonate()
{
    if ( !m_xDonateTimer.DoneTimer() )
    { return; }

    SetDonateMoney( 0 );

    // 通知GameServer停止
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

            // 如果是国王帮, 要换国王, 
            CenterCountry* pCountry = theCenterCountryManager.GetCountry( GetCountry() );
            if ( pCountry != NULL && pCountry->GetKingGuild() == GetID() )
            {
                pCountry->ProcessCountryOfficialChange( CountryDefine::Position_King, pMember->GetID(), pMember->GetName(),-1,-1,-1,-1);
				//发生命令
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

    // 如果是家族长, 让他变成普通成员
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
    case GuildDefine::UpdateMemberOnLine:   // 在线情况不用更新数据库
        if ( nValue == 1 )
        { AddOnLineCount(); }
        else
        { SubOnLineCount(); }
        break;
    case GuildDefine::UpdateMemberExp:      // 玩家经验在GameServer处理逻辑, 这里不需要入库
        break;
    default:
        AddNeedSaveMember( nPlayerID );    // 添加进更新列表
        break;
    }

    // 通知给所有服务器
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

    // 通知给所有服务器
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

    // 通知给所有服务器
	CS2GSChangeGuildNameAck msg;
	msg.GuildID = GetID();
	strcpy_s(msg.Name,GuildDefine::MaxNameLength-1,Name);
    theGameServerManager.SendMessageToGameServers( &msg );
};
template<>
void CenterGuild::ProcessGuildAimChange( const char* szAim, __int64 nTime )
{
	SetAim( szAim );
	SetChangeAimCD( TimeEx::GetNowTime() ); // 此处究竟是现实时间还是游戏时间
	StartSaveTimer();

	// 通知给所有服务器
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
        if ( iter->second.GetPosition() == GuildDefine::Position_FamilyMaster )     // 如果是家族长
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

    if ( szName[0] == 0 )   // 删除一个家族时, 需要把所有该家族的成员信息改变
    {
        ProcessRemoveFamily( uchFamilyID );
    }

    // 同步给所有服务器
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

    // 开启
    m_xReleaseTimer.StartTimer( HQ_TimeGetTime(), GuildDefine::ReleaseKeepTime );

    // 发消息通知客户端
    CS2GSGuildQuestReleaseStatus xStatus;
    xStatus.nGuildID       = GetID();
    xStatus.nQuestID       = GetReleaseQuest();
    xStatus.n64RelasetTime = GetReleaseTime();
    theGameServerManager.SendMessageToGameServers( &xStatus );
}

template<>
void CenterGuild::SendClearMemberActivityMessage()
{
    // 添加保存
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    { AddNeedSaveMember( iter->first ); }

    // 通知所有服务器
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

		//发送提示信息给帮派帮主
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

		//给公会会长发送邮件 告诉会长 公会使命点不足
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;
		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();        
		// 发信人
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// 收件人	
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
		if(GetViceMaster())//如果副会长也存在的话 发给副会长
		{
			xReq.mail.owners[EM_ToIndex].charDbId = GetViceMaster()->GetID();
			HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,GetViceMaster()->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );	
			theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
		}

		// 连续三次未达到指定使命点，处理解散帮派的逻辑
		if ( nMissionCount >= GuildDefine::MissionThird )
		{
			//LYH日志添加 （工会解散）
			//theLogEventService.LogGuild(0,0,GetID(),eSystemLogInfo_guild_disband);
			ProcessDisbandGuild();
			return GuildDefine::UpdateDiaband;
		}
	
	}
	else
	{
		// 使命点清空，使命点计数清空
		SetMission( MISSION_ZERO );
		SetMissionCount( MISSIONCOUNT_ZERO );
		ProcessGuildDataUpdate( GuildDefine::UpdateGuildMission, MISSION_ZERO );
		ProcessGuildDataUpdate( GuildDefine::UpdateGuildMissionCount, MISSIONCOUNT_ZERO );

	}
	//注释不用luo.qin 4.21 begin
    //if ( GetMission() <= pSetting->GetMaxMission() )
    //{ return; } // 没有达到最大值不结算

    //// 多余的全部兑换成帮派经验
    //unsigned int nMission = GetMission() - pSetting->GetMaxMission();

    //// 先更新使命点
    //ProcessGuildDataUpdate( GuildDefine::UpdateGuildMission, pSetting->GetMaxMission() );

    //// 多余的使命点兑换成帮派经验
    //const GuildConfig::MissionSetting& xSetting = theGuildConfig.GetMissionSetting();
    //OperateGuildExp( GuildDefine::OperateAdd, nMission * xSetting.GetGuildExp() );
	//注释不用luo.qin 4.21 end
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

    // 通知给所有服务器
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
    // 启动定时器
    m_xConveneTimer.StartTimer( HQ_TimeGetTime(), GuildDefine::ConveneKeepTime );

    // 发送给GameServer
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

    // 发送消息给GameServer
    CS2GSGuildConveneStop xStop;
    xStop.nGuildID = GetID();
    theGameServerManager.SendMessageToGameServers( &xStop );
}
template<>
void CenterGuild::SendAllRequest(uint32 PlayerID)
{
	//将所有请求发送到客户端
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