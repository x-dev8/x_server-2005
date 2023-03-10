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

    // ?????????????? ??????????
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

    if ( pData == NULL )        // ???????? ??????
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
    // ??????????????????????????
    ProcessAddRelationToMe( xRelation.GetID() );

    if ( uchOperate == RelationDefine::NotSendToClient )
    { return; } // ??????????????, ????????

    // ???????????? ?????????????? ????
    TellAddRelationMessage( xRelation.GetID(), xRelation.GetRelation() );

    // ??????????
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( xRelation.GetID() );
    if ( pRelation == NULL )
    { return; }

    // ??????????????????
    switch ( xOldRelation.GetHigherRelation() )
    {
    case RelationDefine::Teacher:
        theGameRelationManager.RemoveRegisterID( RelationDefine::Student, GetID() );    // ????????????, ????????????
        break;
    case RelationDefine::Student:
        {
            const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( GetMasterLevel() );
            if ( pInfo != NULL && GetStudentCount() >= pInfo->GetRecruitCount() )   // ????????????????, ????????????
            { 
                theGameRelationManager.RemoveRegisterID( RelationDefine::Teacher, GetID() );
            }
        }
        break;
    case RelationDefine::Marriage:
        {
            if ( GetSex() == Sex_Male )                    // ??????????????
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
    { return; }     // ????????????????????????????

    RelationDataToServer* pData = GetRelationData( xRelation.GetID() );
    if ( pData == NULL )
    { return; }

    // ????????????
    MsgAddRelationAck xAck;
    xAck.uchResult = RelationDefine::AddRelationSuccess;
    xAck.xRelationData.SetRelationAttribute( *pRelation );
    xAck.xRelationData.InitRelationData( *pData );
    pPlayer->SendMessageToClient( &xAck );

    // ????????????????????
    switch ( xRelation.GetRelation() )
    {
    case RelationDefine::Friend: // ???????? ????????????buffer
        pPlayer->ProcessGuideQuest( GuideQuest::Guide_Friend );
        theGameTeamManager.UpdateTeamBuffer( GetID(), xRelation.GetID(), true, true );
        break;  
    default:
        break;
    }

    switch ( xOldRelation.GetHigherRelation() )
    {
    case RelationDefine::Marriage:  // ????????????????, ??????????
        GetScriptMgr()->StartupVM( ST_MARRIAGE, 0, pPlayer );   // ????????????
        break;
    case RelationDefine::Teacher:  // ??????????????, ??????????
        GetScriptMgr()->StartupVM( ST_TEACHERSTUDENT, 0, pPlayer, false, 1 );   // ????????????
		pPlayer->_achieveManager.UpdateTriggerByValueType( EAT_FirstMaster );
		break;
    case RelationDefine::Student:  // ??????????????, ??????????
        {
            if ( GetStudentCount() == 1 )
            {
                GetScriptMgr()->StartupVM( ST_TEACHERSTUDENT, 0, pPlayer, false, 2 );   // ????????????
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
    
    // ????????????????????????
    ProcessRemoveRelationToMe( dwPlayerID, pData );

    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    // ????????????????
    MsgDeleteRaltionAck xDelete;
    xDelete.stRelation = stRelation;
    xDelete.nPlayerID  = dwPlayerID;
    if ( pData == NULL )
    { xDelete.stFriendly = 0; }
    else
    { xDelete.stFriendly = pData->GetFriendly(); }
    pPlayer->SendMessageToClient( &xDelete );

    // ??????????????????
    switch ( stRelation )
    {
    case RelationDefine::Friend:    // ???????? ????????????buffer
        theGameTeamManager.UpdateTeamBuffer( GetID(), dwPlayerID, true, false );
        break;
    case RelationDefine::Marriage:  // ????????????
        {
            GetScriptMgr()->StartupVM( ST_MARRIAGE, 0, pPlayer, false, 2 );       // ????????????

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

template<>  // ??????????????????
void GameRelation::ProcessEnterWorld()
{
    SendRelationListToClient(); // ???????? ?? ????????

    // ??????????????????????????
    if ( GetLevel() == 0 )
    { SendAddAttributeMessage(); }

    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    // ???????? ??????????????????
    if ( GetRewardExp() > 0 || GetRewardPrestige() > 0 )
    {
        pPlayer->ProcessStudentLevelUp( RelationDefine::InitID, true, GetRewardExp(), GetRewardPrestige() );

        // ??????CenterServer????
        GS2CSResetStudentReward xReset;
        xReset.nPlayerID = GetID();
        GettheServer().SendMsgToCenterServer( &xReset );
    }

    // ??????????????, ????????????????, ????????????
    if ( !pPlayer->IsHaveMarriage() )
    { pPlayer->RemoveTypeTitle( TitleConfig::Title_Marriage ); }

    // ??????????????, ????????????, ??????????
    if ( !pPlayer->IsHaveTeacher() )
    { pPlayer->RemoveTypeTitle( TitleConfig::Title_Student ); }

    // ????????????, ????????????, ????????
    if ( !pPlayer->IsHaveStudent() )
    { pPlayer->RemoveTypeTitle( TitleConfig::Title_Teacher ); }
}

template<>  // ??????????????????
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
template<>      // ????????A??????????????????, A??????????
void GameRelation::SendOnLineMessage()
{
    SetOnLine( true );  // ????????????

    MsgFriendOnline xOnLine;
    xOnLine.nPlayerID = GetID();

    for ( RelationToMeMapIter iter = m_mapRelationToMe.begin(); iter != m_mapRelationToMe.end(); ++iter )
    {
        // ???? ???? ???? ??????
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

template<>  // ????????A??????????????????, A??????????
void GameRelation::SendOutLineMessage()
{
    SetOnLine( false );  // ??????????????

    MsgFriendOutLine xOutLine;
    xOutLine.nPlayerID = GetID();

    for ( RelationToMeMapIter iter = m_mapRelationToMe.begin(); iter != m_mapRelationToMe.end(); ++iter )
    {
        // ???? ???? ???? ??????
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

template<>  // ????????????????????
void GameRelation::SendRelationListToClient( unsigned int nAppointID )
{
    GamePlayer* pPlayer = GetPlayer( GetID() );
    if ( pPlayer == NULL )
    { return; }

    // ??????????????
    MsgRelationAttribute xAttribute;
    xAttribute.ustMessageRefuse = GetMessageRefuse();     // ????????????????
    HelperFunc::SafeNCpy( xAttribute.szSignature, GetSignature(), sizeof( xAttribute.szSignature ) ); // ????????
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
    
    // ??????????????????????????
    pPlayer->SendMessageToClient( &xList );
}

template<>  // ??????????????????????????
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

    // ??????????, ????????????
    GS2CSStudentLevelUp xLevelUp;
    xLevelUp.nPlayerID = GetID();
    xLevelUp.nLevel    = nLevel;
    GettheServer().SendMsgToCenterServer( &xLevelUp );
}

template<>  // ??????????????
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

    // ????????????????
    if ( GetStudentCount() >= pInfo->GetRecruitCount() )
    { return RelationDefine::StudentCountLimit; }

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    
    // ????????????
    if ( pRelation->GetLevel() < xPrenticeLimit.GetMinStudentLevel() )
    { return RelationDefine::StudentMinLevelLimit; }

    // ????????
    if ( GetLevel() < xPrenticeLimit.GetMinTeacherLevel() )
    { return RelationDefine::TeacherMinLevelLimit; }

    // ??????????
    if ( GetLevel() - pRelation->GetLevel() < xPrenticeLimit.GetMinLevelSpan() )
    { return RelationDefine::StudentMinLevelSpan; }

    // ??????????????????
    if ( !TimeEx::IsPassCurrentTime( GetLastAddStudentTime(), xPrenticeLimit.GetTeacherTimeSpan() * OneHourSecond ) )
    { return RelationDefine::AddStudentTimeLimit; }

    return RelationDefine::CanAddRelation;
}

template<>  // ??????????????
unsigned short GameRelation::CheckCanAddTeacher( unsigned int dwPlayerID )
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( dwPlayerID );
    if ( pRelation == NULL )
    { return RelationDefine::CanNotAddRelation; }

    if ( GetCountry() != pRelation->GetCountry() )
    { return  RelationDefine::MustSameCountry; }

    // ????????????????
    if ( IsHaveTeacher() )
    { return RelationDefine::AlreadyHaveTeacher; }

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    // ????????????
    if ( !TimeEx::IsPassCurrentTime( GetLastAddTeacherTime(), xPrenticeLimit.GetStudentTimeSpan() * OneHourSecond ) )
    { return RelationDefine::AddTeacherTimeLimit; }

    // ????????????
    if ( GetLevel() < xPrenticeLimit.GetMinStudentLevel() )
    { return RelationDefine::StudentMinLevelLimit; }

    // ????????????
    if ( pRelation->GetLevel() < xPrenticeLimit.GetMinTeacherLevel() )
    { return RelationDefine::TeacherMinLevelLimit; }

    // ??????????
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
    // ??????CenterServer
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
