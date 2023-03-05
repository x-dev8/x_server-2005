#include "RelationManager.h"
#include "GamePlayer.h"
#include "MessageDefine.h"
#include "ShareData.h"
#include "TeamManager.h"
#include "CountryManager.h"

template<>
GamePlayer* GameRelation::GetPlayer( unsigned int dwPlayerID )
{
    return theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
}

template<>
void GameRelation::SendAddAttributeMessage()
{
    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    GS2CSAddRelationAttribute xReq;
    pPlayer->InitRelationAttribute( xReq.xAttribute );
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendUpdateAttributeReqMessage( unsigned char uchType, unsigned int nValue )
{
    GS2CSUpdateRelationAttribute xReq;
    xReq.nPlayerID           = GetID();
    xReq.uchType             = uchType;
    xReq.xAttribute.n64Value = nValue;
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendUpdateAttributeReqMessage( unsigned char uchType, const char* szValue )
{
    GS2CSUpdateRelationAttribute xReq;
    xReq.nPlayerID               = GetID();
    xReq.uchType                 = uchType;
    HelperFunc::SafeNCpy( xReq.xAttribute.szValue, szValue, sizeof( xReq.xAttribute.szValue ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendUpdatePersonalInfoReqMsg( const PersonalInfo& xValue )
{
	GS2CSUpdatePersonalInfo xReq;
	xReq.nPlayerID               = GetID();
	xReq.xPersonalInfo.SetInfo( xValue );
	GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendUpdateAttributeMessage( unsigned char uchType, __int64 n64Value )
{

}

template<>
void GameRelation::SendUpdateAttributeMessage( unsigned char uchType, const char* szValue )
{
    switch ( uchType )
    {
    case RelationDefine::UpdateName:
        theGameRelationManager.AddPlayerNameID( this );
        break;
    case RelationDefine::UpdateSignature:
        break;
    default:
        break;
    }
}

template<>
void GameRelation::SendUpdatePersonalInfo( const PersonalInfo& xValue )
{

}

template<>
void GameRelation::TellAddRelationMessage( unsigned int nPlayerID, unsigned short ustRelation )
{
    if ( ustRelation != RelationDefine::Friend )
    { return; }

    // 如果已经是好友 不用发邀请
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL || pRelation->HaveRelation( RelationDefine::Friend ) )
    { return; }
    
    GamePlayer* pPlayer = GetPlayer( nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    MsgTellAddRelation xTell;
    HelperFunc::SafeNCpy( xTell.szName, GetName(), sizeof( xTell.szName ) );
    xTell.ustRelation = ustRelation;
    pPlayer->SendMessageToClient( &xTell );
}

template<>
void GameRelation::ProcessAddRelationToMe( unsigned int nPlayerID )
{
    RelationDataToServer* pData = GetRelationData( nPlayerID );
    if ( pData == NULL )
    { return; }

    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->AddRelationToMe( GetID(), pData->GetRelation() );
}

template<>
void GameRelation::AddRelationToMe( unsigned int nPlayerID, unsigned short ustRelation )
{
    m_mapRelationToMe[ nPlayerID ] = ustRelation;
}

template<>
void GameRelation::ProcessRemoveRelationToMe( unsigned int nPlayerID, RelationDataToServer* pData )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL )
    { return; }

    if ( pData == NULL )        // 没关系了 删除之
    {
        pRelation->RemoveRelationToMe( GetID() );
    }
    else
    {
        pRelation->AddRelationToMe( GetID(), pData->GetRelation() );
    }
}

template<>
void GameRelation::RemoveRelationToMe( unsigned int nPlayerID )
{
    RelationToMeMapIter iter = m_mapRelationToMe.find( nPlayerID );
    if ( iter == m_mapRelationToMe.end() )
    { return; }

    m_mapRelationToMe.erase( iter );
}

template<>
void GameRelation::ProcessAddRelation( RelationDataToServer& xRelation, unsigned char uchOperate ,RelationDataToServer& xOldRelation)
{
    // 添加所有加了我为好友的列表
    ProcessAddRelationToMe( xRelation.GetID() );

    if ( uchOperate == RelationDefine::NotSendToClient )
    { return; } // 如果只是初始化, 直接返回

    // 处理通知对方 自己加为他好友 逻辑
    TellAddRelationMessage( xRelation.GetID(), xRelation.GetRelation() );

    // 对方的信息
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( xRelation.GetID() );
    if ( pRelation == NULL )
    { return; }

    // 判断添加高级关系后
    switch ( xOldRelation.GetHigherRelation() )
    {
    case RelationDefine::Teacher:
        theGameRelationManager.RemoveRegisterID( RelationDefine::Student, GetID() );    // 加过师傅以后, 删除徒弟注册
        break;
    case RelationDefine::Student:
        {
            const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( GetMasterLevel() );
            if ( pInfo != NULL && GetStudentCount() >= pInfo->GetRecruitCount() )   // 师傅不能收徒弟了, 删除师傅注册
            { 
                theGameRelationManager.RemoveRegisterID( RelationDefine::Teacher, GetID() );
            }
        }
        break;
    case RelationDefine::Marriage:
        {
            if ( GetSex() == Sex_Male )                    // 全世界公告一下
            {
                MsgTellWorldAddRelation xTell;
                xTell.ustRelation = RelationDefine::Marriage;
                HelperFunc::SafeNCpy( xTell.szPlayer1, GetName(), sizeof( xTell.szPlayer1 ) );
                HelperFunc::SafeNCpy( xTell.szPlayer2, pRelation->GetName(), sizeof( xTell.szPlayer2 ) );
                GettheServer().SendMsgToWorld( &xTell, false );
            }
        }
        break;
    default:
        break;
    }

    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }     // 在本服务器上才处理下面的消息

    RelationDataToServer* pData = GetRelationData( xRelation.GetID() );
    if ( pData == NULL )
    { return; }

    // 通知给客户端
    MsgAddRelationAck xAck;
    xAck.uchResult = RelationDefine::AddRelationSuccess;
    xAck.xRelationData.SetRelationAttribute( *pRelation );
    xAck.xRelationData.InitRelationData( *pData );
    pPlayer->SendMessageToClient( &xAck );

    // 处理加为关系后的逻辑
    switch ( xRelation.GetRelation() )
    {
    case RelationDefine::Friend: // 加为好友 刷新一下队伍buffer
        pPlayer->ProcessGuideQuest( GuideQuest::Guide_Friend );
        theGameTeamManager.UpdateTeamBuffer( GetID(), xRelation.GetID(), true, true );
        break;  
    default:
        break;
    }

    switch ( xOldRelation.GetHigherRelation() )
    {
    case RelationDefine::Marriage:  // 处理结婚后的事情, 由脚本执行
        GetScriptMgr()->StartupVM( ST_MARRIAGE, 0, pPlayer );   // 调用结婚脚本
        break;
    case RelationDefine::Teacher:  // 处理拜师的事情, 由脚本执行
        GetScriptMgr()->StartupVM( ST_TEACHERSTUDENT, 0, pPlayer, false, 1 );   // 调用师徒脚本
		pPlayer->_achieveManager.UpdateTriggerByValueType( EAT_FirstMaster );
		break;
    case RelationDefine::Student:  // 处理收徒的事情, 由脚本执行
        {
            if ( GetStudentCount() == 1 )
            {
                GetScriptMgr()->StartupVM( ST_TEACHERSTUDENT, 0, pPlayer, false, 2 );   // 调用师徒脚本
            }
            pPlayer->_achieveManager.UpdateTriggerByValueType( EAT_FirstStudent );
        }
        break;
    default:
        break;
    }
}

template<>
void GameRelation::ProcessRemoveRelation( unsigned int dwPlayerID, unsigned short stRelation )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    
    // 处理对方的有我的关系列表
    ProcessRemoveRelationToMe( dwPlayerID, pData );

    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    // 发送消息给客户端
    MsgDeleteRaltionAck xDelete;
    xDelete.stRelation = stRelation;
    xDelete.nPlayerID  = dwPlayerID;
    if ( pData == NULL )
    { xDelete.stFriendly = 0; }
    else
    { xDelete.stFriendly = pData->GetFriendly(); }
    pPlayer->SendMessageToClient( &xDelete );

    // 处理删除关系后逻辑
    switch ( stRelation )
    {
    case RelationDefine::Friend:    // 删除好友 刷新一下队伍buffer
        theGameTeamManager.UpdateTeamBuffer( GetID(), dwPlayerID, true, false );
        break;
    case RelationDefine::Marriage:  // 删除夫妻关系
        {
            GetScriptMgr()->StartupVM( ST_MARRIAGE, 0, pPlayer, false, 2 );       // 调用结婚脚本

            pPlayer->RemoveTypeTitle( TitleConfig::Title_Marriage );
            pPlayer->SetReqRemoveMarriage( false );
            pPlayer->SetForceRemove( false );
        }
        break;
    case RelationDefine::Teacher:
        {
            pPlayer->RemoveTypeTitle( TitleConfig::Title_Student );
        }
        break;
    case RelationDefine::Student:
        {
            if ( GetStudentCount() == 0 )
            {
                pPlayer->RemoveTypeTitle( TitleConfig::Title_Teacher );
            }
        }
        break;
    default:
        break;
    }
}

template<>  // 第一次进入游戏世界
void GameRelation::ProcessEnterWorld()
{
    SendRelationListToClient(); // 发送属性 和 关系列表

    // 检测是否已经设置了关系属性
    if ( GetLevel() == 0 )
    { SendAddAttributeMessage(); }

    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    // 不在线时 如果有徒弟贡献经验
    if ( GetRewardExp() > 0 || GetRewardPrestige() > 0 )
    {
        pPlayer->ProcessStudentLevelUp( RelationDefine::InitID, true, GetRewardExp(), GetRewardPrestige() );

        // 通知给CenterServer更新
        GS2CSResetStudentReward xReset;
        xReset.nPlayerID = GetID();
        GettheServer().SendMsgToCenterServer( &xReset );
    }

    // 如果有夫妻称号, 而没有夫妻关系了, 要删除该称号
    if ( !pPlayer->IsHaveMarriage() )
    { pPlayer->RemoveTypeTitle( TitleConfig::Title_Marriage ); }

    // 如果有徒弟称号, 而没有师傅了, 要删除称号
    if ( !pPlayer->IsHaveTeacher() )
    { pPlayer->RemoveTypeTitle( TitleConfig::Title_Student ); }

    // 如果没有徒弟, 还有师傅称号, 删除称号
    if ( !pPlayer->IsHaveStudent() )
    { pPlayer->RemoveTypeTitle( TitleConfig::Title_Teacher ); }
}

template<>  // 第一次进入游戏世界
void GameRelation::ProcessExitWorld()
{
    SendOutLineMessage();
}
template<>
void GameRelation::SendRelationMessage(Msg* pMsg)
{
	for ( RelationToMeMapIter iter = m_mapRelationToMe.begin(); iter != m_mapRelationToMe.end(); ++iter )
    {
        GamePlayer* pPlayer = GetPlayer( iter->first );
        if ( pPlayer == NULL )
        { continue; }
        pPlayer->SendMessageToClient(pMsg);
    }
}
template<>      // 通知加了A玩家好友的所有玩家, A玩家上线了
void GameRelation::SendOnLineMessage()
{
    SetOnLine( true );  // 设置在线状态

    MsgFriendOnline xOnLine;
    xOnLine.nPlayerID = GetID();

    for ( RelationToMeMapIter iter = m_mapRelationToMe.begin(); iter != m_mapRelationToMe.end(); ++iter )
    {
        // 好友 或者 仇人 都通知
        if ( RelationData::HaveRelation( iter->second, RelationDefine::Friend ) || RelationData::HaveRelation( iter->second, RelationDefine::Vendetta ) 
			 || RelationData::HaveRelation( iter->second, RelationDefine::TempFriend ) )
        {
            GamePlayer* pPlayer = GetPlayer( iter->first );
            if ( pPlayer == NULL )
            { continue; }
            
            pPlayer->SendMessageToClient( &xOnLine );
        }
    }
}

template<>  // 通知加了A玩家好友的所有玩家, A玩家下线了
void GameRelation::SendOutLineMessage()
{
    SetOnLine( false );  // 设置不在线状态

    MsgFriendOutLine xOutLine;
    xOutLine.nPlayerID = GetID();

    for ( RelationToMeMapIter iter = m_mapRelationToMe.begin(); iter != m_mapRelationToMe.end(); ++iter )
    {
        // 好友 或者 仇人 都通知
        if ( RelationData::HaveRelation( iter->second, RelationDefine::Friend ) || RelationData::HaveRelation( iter->second, RelationDefine::Vendetta )
			|| RelationData::HaveRelation( iter->second, RelationDefine::TempFriend ))
        {
            GamePlayer* pPlayer = GetPlayer( iter->first );
            if ( pPlayer == NULL )
            { continue; }

            pPlayer->SendMessageToClient( &xOutLine );
        }
    }
}

template<>  // 发送关系列表给客户端
void GameRelation::SendRelationListToClient( unsigned int nAppointID )
{
    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    // 自己个属性设置
    MsgRelationAttribute xAttribute;
    xAttribute.ustMessageRefuse = GetMessageRefuse();     // 接受聊天消息设置
    HelperFunc::SafeNCpy( xAttribute.szSignature, GetSignature(), sizeof( xAttribute.szSignature ) ); // 个性签名
    memcpy_s( xAttribute.xGroup, sizeof( xAttribute.xGroup ), xGroup, sizeof( xGroup ) );
    pPlayer->SendMessageToClient( &xAttribute );

	MsgPersonalInfo xPersonInfoMsg;
	xPersonInfoMsg.xPersonalInfo.SetInfo( xPersonalInfo );
	pPlayer->SendMessageToClient( &xPersonInfoMsg );

    MsgRelationList xList;
    for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
    {
        GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( iter->second.GetID() );
        if ( pRelation == NULL )
        { continue; }

        RelationDataToClient xData;

        xData.SetRelationAttribute( *pRelation );
        xData.InitRelationData( iter->second );

        xList.AddRelationData( xData );
        if ( xList.IsFull() )
        {
            pPlayer->SendMessageToClient( &xList );
            xList.Reset();
        }
    }
    
    // 有没有好友都要发送给客户端
    pPlayer->SendMessageToClient( &xList );
}

template<>  // 更新在线的关系信息给客户端
void GameRelation::UpdateRelationToClient( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }
    
    MsgUpdateRelationAck xUpdate;
    for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
    {
        GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( iter->second.GetID() );
        if ( pRelation == NULL || !pRelation->GetOnLine() )
        { continue; }

        xUpdate.AddAttribute( *pRelation );
    }

    pPlayer->SendMessageToClient( &xUpdate );
}


template<>
void GameRelation::ProcessStudentLevelUp( unsigned int nPlayerID, int nLevel )
{
    SendUpdateAttributeReqMessage( RelationDefine::UpdateLevel, nLevel );

    if ( !IsHaveTeacher() )
    { return; }

    // 如果有师傅, 给师父加经验
    GS2CSStudentLevelUp xLevelUp;
    xLevelUp.nPlayerID = GetID();
    xLevelUp.nLevel    = nLevel;
    GettheServer().SendMsgToCenterServer( &xLevelUp );
}

template<>  // 检查是否能收徒
unsigned short GameRelation::CheckCanAddStudent( unsigned int dwPlayerID )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( dwPlayerID );
    if ( pRelation == NULL )
    { return RelationDefine::CanNotAddRelation; }

    if ( GetCountry() != pRelation->GetCountry() )
    { return  RelationDefine::MustSameCountry; }

    const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( GetMasterLevel() );
    if ( pInfo == NULL )
    { return RelationDefine::CanNotReceivePrentice; }

    // 徒弟数量已经满了
    if ( GetStudentCount() >= pInfo->GetRecruitCount() )
    { return RelationDefine::StudentCountLimit; }

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    
    // 判断最小等级
    if ( pRelation->GetLevel() < xPrenticeLimit.GetMinStudentLevel() )
    { return RelationDefine::StudentMinLevelLimit; }

    // 最大等级
    if ( GetLevel() < xPrenticeLimit.GetMinTeacherLevel() )
    { return RelationDefine::TeacherMinLevelLimit; }

    // 师徒等级差
    if ( GetLevel() - pRelation->GetLevel() < xPrenticeLimit.GetMinLevelSpan() )
    { return RelationDefine::StudentMinLevelSpan; }

    // 判断自己的时间限制
    if ( !TimeEx::IsPassCurrentTime( GetLastAddStudentTime(), xPrenticeLimit.GetTeacherTimeSpan() * OneHourSecond ) )
    { return RelationDefine::AddStudentTimeLimit; }

    return RelationDefine::CanAddRelation;
}

template<>  // 判断是否能拜师
unsigned short GameRelation::CheckCanAddTeacher( unsigned int dwPlayerID )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( dwPlayerID );
    if ( pRelation == NULL )
    { return RelationDefine::CanNotAddRelation; }

    if ( GetCountry() != pRelation->GetCountry() )
    { return  RelationDefine::MustSameCountry; }

    // 自己已经有师傅了
    if ( IsHaveTeacher() )
    { return RelationDefine::AlreadyHaveTeacher; }

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    // 自己拜师限制
    if ( !TimeEx::IsPassCurrentTime( GetLastAddTeacherTime(), xPrenticeLimit.GetStudentTimeSpan() * OneHourSecond ) )
    { return RelationDefine::AddTeacherTimeLimit; }

    // 徒弟最小等级
    if ( GetLevel() < xPrenticeLimit.GetMinStudentLevel() )
    { return RelationDefine::StudentMinLevelLimit; }

    // 师傅最小等级
    if ( pRelation->GetLevel() < xPrenticeLimit.GetMinTeacherLevel() )
    { return RelationDefine::TeacherMinLevelLimit; }

    // 师徒等级差
    if ( pRelation->GetLevel() - GetLevel() < xPrenticeLimit.GetMinLevelSpan() )
    { return RelationDefine::StudentMinLevelSpan; }

    return RelationDefine::CanAddRelation;
}

template<>
bool GameRelation::CheckBrotherCount()
{
    return true;
}

template<>
bool GameRelation::HaveAddFriendlyTime( unsigned int dwPlayerID, bool& bClear )
{
    bClear = false;
    if ( RecordTime::CheckRecordTime( m_dwAddFriendlyTime ) )
    {
        RecordTime::SaveRecordTime( m_dwAddFriendlyTime );
        m_setAddFriendly.clear();
        bClear = true;
        return false;
    }

    return m_setAddFriendly.find( dwPlayerID ) != m_setAddFriendly.end();
}

template<>
void GameRelation::SendAddFriendlyTimeMessage( unsigned int dwPlayerID, bool bClear )
{
    GS2CSUpdateAddFriendlyTime xUpdate;
    xUpdate.dwSelfID = GetID();
    xUpdate.dwPlayerID = dwPlayerID;
    xUpdate.bClear = bClear;

    GettheServer().SendMsgToCenterServer( &xUpdate );
}

template<>
bool GameRelation::HaveReceiveQuestTime( unsigned int dwPlayerID, bool& bClear )
{
    bClear = false;
    if ( RecordTime::CheckRecordTime( m_dwReceiveQuestTime ) )
    {
        RecordTime::SaveRecordTime( m_dwReceiveQuestTime );
        m_setReceiveQuest.clear();
        bClear = true;
        return false;
    }

    return m_setReceiveQuest.find( dwPlayerID ) != m_setReceiveQuest.end();
}

template<>
void GameRelation::SendReceiveQuestTimeMessage( unsigned int dwPlayerID, bool bClear )
{
    GS2CSUpdateReceiveQuestTime xUpdate;
    xUpdate.dwSelfID = GetID();
    xUpdate.dwPlayerID = dwPlayerID;
    xUpdate.bClear = bClear;

    GettheServer().SendMsgToCenterServer( &xUpdate );
}

template<>
void GameRelation::ClearAddFriendlyTime()
{
    m_setAddFriendly.clear(); 
    RecordTime::SaveRecordTime( m_dwAddFriendlyTime );
}

template<>
void GameRelation::ClearReceiveQuestTime()
{
    m_setReceiveQuest.clear(); 
    RecordTime::SaveRecordTime( m_dwReceiveQuestTime );
}

template<>
void GameRelation::SendGroupNameChangeReqMessage( unsigned char uchGroupID, const char* szValue )
{
    // 发送给CenterServer
    GS2CSRelationGroupNameChangeReq xReq;
    xReq.nPlayerID  = GetID();
    xReq.uchGroupID = uchGroupID;
    HelperFunc::SafeNCpy( xReq.szName, szValue, sizeof( xReq.szName ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendRelationGroupNameChangeMessage( unsigned char uchGroupID, const char* szValue )
{
    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    MsgTellRelationGroup xTell;
    xTell.uchGroupID = uchGroupID;
    HelperFunc::SafeNCpy( xTell.szGroup, szValue, sizeof( xTell.szGroup ) );
    pPlayer->SendMessageToClient( &xTell );
}

template<>
void GameRelation::SendUpdateRelationDataReqMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    GS2CSRelationDataChangeReq xReq;
    xReq.nPlayerID    = GetID();
    xReq.nTargetID    = nPlayerID;
    xReq.uchType      = uchType;
    xReq.xData.nValue = nValue; 
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendUpdateRelationDataReqMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue )
{
    GS2CSRelationDataChangeReq xReq;
    xReq.nPlayerID    = GetID();
    xReq.nTargetID    = nPlayerID;
    xReq.uchType      = uchType;
    HelperFunc::SafeNCpy( xReq.xData.szValue, szValue, sizeof( xReq.xData.szValue ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

template<>
void GameRelation::SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    switch ( uchType )
    {
    case RelationDefine::UpdateLocked:
        {
            MsgRelationLockStatus xStatus;
            xStatus.nPlayerID = nPlayerID;
            xStatus.bLocked   = ( nValue == 1 ? true : false );
            pPlayer->SendMessageToClient( &xStatus );
        }
        break;
    case RelationDefine::UpdateGroupID:
        {
            MsgRelationGroupChangeAck xGroup;
            xGroup.uchGroupID = nValue;
            xGroup.nPlayerID  = nPlayerID;
            pPlayer->SendMessageToClient( &xGroup );
        }
        break;
    case RelationDefine::UpdateSetFriendly:
        {
            MsgUpdateFriendly xFriendly;
            xFriendly.nPlayerID = nPlayerID;
            xFriendly.nFriendly = nValue;
            pPlayer->SendMessageToClient( &xFriendly );
        }
        break;
    default:
        break;
    }
}

template<>
void GameRelation::SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue )
{
}
