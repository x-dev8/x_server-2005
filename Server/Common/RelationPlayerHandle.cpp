#include "GamePlayer.h"
#include "TeamManager.h"
#include "GameWorld.h"
#include "TitleConfig.h"
#include "ShareData.h"
#include "ServerVarInterface.h"
#include "ChatCheck.h"

extern IScriptInterface* GetScriptInterface();

bool GamePlayer::ProcessRelationMsg( Msg* pMsg )
{
    if ( m_pRelation == NULL )
    { return false; }

    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_ADDRELATIONREQ, OnMsgAddRelationReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_UPDATERELATIONREQ, OnMsgUpdateRelationReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_INVITERELATIONACK, OnMsgInviterRelationAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_DELETERELATIONREQ, OnMsgDeleteRelationReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_DELETERELATIONCHECKACK, OnDeleteRelationCheckAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_RELATIONLOCKREQ, OnMsgRelationLockReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_RELATIONUNLOCKREQ, OnMsgRelationUnLockReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYATTRIBUTEREQ, OnMsgQueryAttributeReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_REGISTERRELATIONREQ, OnMsgRegisterRelationReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_SETRECEIVESTRANGERREQ, OnMsgSetReceiveStrangerReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGESIGNATUREREQ, OnMsgChangeSignatureReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_RELATIONGROUPADDREQ, OnMsgRelationGroupAddReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_RELATIONGROUPCHANGENAMEREQ, OnMsgRelationGroupChangeNameReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_RELATIONGROUPCHANGEREQ, OnMsgRelationGroupChangeReq );  
        GAMESERVER_MESSAGE_HANDLE( MSG_RELATIONREMARTCHANGEREQ, OnMsgRelationRemarkChangeReq );  
		GAMESERVER_MESSAGE_HANDLE( MSG_CHANGEPERSONALINFO, OnMsgChangePersonalInfo );
		GAMESERVER_MESSAGE_HANDLE( MSG_FINDBYCONDITION,OnMsgFindPlayerByCondition );
        
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}

// 设置关系属性
void GamePlayer::InitRelationAttribute( RelationAttribute& xAttribute )
{
    xAttribute.SetID( GetDBCharacterID() );
    xAttribute.SetName( GetCharName() );
    xAttribute.SetHeadPic( GetHeadPic() );
    xAttribute.SetCountry( GetCountry() );
    xAttribute.SetProfession( GetProfession() );
    xAttribute.SetSex( GetSex() );
    xAttribute.SetLevel( GetLevel() );
    xAttribute.SetGuildID( GetGuildID() );
    xAttribute.SetMasterLevel( GetMasterLevel() );
    xAttribute.SetTitleID( GetCurrentTitle() );
    xAttribute.SetOnLine( true );
    xAttribute.SetPosition( GetCountryTitle() );

    xAttribute.SetIp( GetIp() );
    xAttribute.SetMapID( GetMapID() );
	xAttribute.SetFamilyID( GetFamilyID() );

    int nMonth, nDay;
    GetBirthday( NULL, &nMonth, &nDay );
    
    xAttribute.GetPersonalInfo().SetPersonalMonth( nMonth );
    xAttribute.GetPersonalInfo().SetPersonalDay( nMonth );
}

void GamePlayer::InitPlayerRelation( GameRelation* pRelation )
{
    m_pRelation = pRelation;

    // 如果职位不相同了
    if ( m_pRelation->GetPosition() != GetCountryTitle() )
    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdatePosition, GetCountryTitle() ); }

    // 如果帮派不同了
    if ( m_pRelation->GetGuildID() != GetGuildID() )
    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateGuild, GetGuildID() ); }

	// 如果家族不同了
	if ( m_pRelation->GetGuildID() != GetGuildID() )
	{ m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateFamily, GetFamilyID() ); }

    // 如果称号不同了
    if ( m_pRelation->GetTitleID() != GetCurrentTitle() )
    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateTitle, GetCurrentTitle() ); }

    if( m_pRelation->GetMapID() != GetMapID() )
    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateMapID, GetMapID() ); }

    if ( strcmp(m_pRelation->GetIp(), GetIp() ) != 0 )
    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateIp, GetIp() ); }
}

int GamePlayer::GetMasterLevel() const
{ 
    return gCharInfoServer.baseinfo.liveinfo.xMasterData.GetMasterLevel(); 
}

uint32 GamePlayer::GetMasterValue() const
{ 
    return gCharInfoServer.baseinfo.liveinfo.xMasterData.GetMasterValue(); 
}

void GamePlayer::OperateMasterValue( uint8 uchOperateType, uint32 nValue )
{
    if ( nValue == 0 )
    { return; }

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( gCharInfoServer.baseinfo.liveinfo.xMasterData.GetMasterLevel() );
            if ( pInfo == NULL )
            { return; }

            int nCanAddValue = pInfo->GetMaxMasterValue() - GetMasterValue();
            if ( nCanAddValue <= 0 )
            { return; }

            if ( nCanAddValue < nValue )
            { nValue = nCanAddValue; }

            gCharInfoServer.baseinfo.liveinfo.xMasterData.SetMasterValue( GetMasterValue() + nValue );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetMasterValue() )
            { nValue = GetMasterValue(); }

            gCharInfoServer.baseinfo.liveinfo.xMasterData.SetMasterValue( GetMasterValue() - nValue );
        }
        break;
    case EOT_Set:
        gCharInfoServer.baseinfo.liveinfo.xMasterData.SetMasterValue( nValue );
        break;
    default:
        return;
        break;
    }

    _achieveManager.UpdateTriggerByValueType( EAT_Prestige, GetMasterValue() );

    MsgCharAttrChanged xChange;
    xChange.header.stID = GetID();

    xChange.AddAttrDWORDChange( CharAttr_MasterValue, GetMasterValue() );
    xChange.CaluLength();
    SendMessageToClient( &xChange );
}

bool GamePlayer::CheckBlackListPlayer( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    RelationDataToServer* pData = m_pRelation->GetRelationData( pPlayer->GetDBCharacterID() );
    if ( pData == NULL )
    { return false; }

    return pData->HaveRelation( RelationDefine::BlackList );
}

bool GamePlayer::IsFriend( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    RelationDataToServer* pData = m_pRelation->GetRelationData( pPlayer->GetDBCharacterID() );
    if ( pData == NULL )
    { return false; }

    return pData->HaveRelation( RelationDefine::Friend );
}

void GamePlayer::AddRelation( const char* szName, unsigned short stRelation )
{
    if ( szName == NULL || szName[0] == 0 )
    { return; }

    MsgAddRelationReq xAddFriend;
    xAddFriend.stRelation = stRelation;
    strncpy_s( xAddFriend.szName, sizeof( xAddFriend.szName ), szName, sizeof( xAddFriend.szName ) - 1 );
    OnMsgAddRelationReq( &xAddFriend );
}

bool GamePlayer::SendDeleteRelationCheckMessage( uint32 dwPlayerID, uint16 ustRelation )
{
    MsgDeleteRelationCheckReq xReq;
    xReq.nPlayerID   = dwPlayerID;
    xReq.ustRelation = ustRelation;
    SendMessageToClient( &xReq );

    return true;
}

bool GamePlayer::MasterLevelUp()
{
    if ( GetMasterLevel() >= theRelationConfig.GetMaxMasterLevel() )
    { 
        MsgAckResult xAck;
        xAck.result = ER_AlreadyMaxMasterLevel;
        GettheServer().SendMsgToSingle( &xAck, this );
        return false; 
    }

    // 判断威望值够不够
    const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( GetMasterLevel() + 1 );
    if ( pInfo == NULL )
    { return false; }

    if ( gCharInfoServer.baseinfo.liveinfo.xMasterData.GetMasterValue() < pInfo->GetNeedMasterValue() )
    {
        MsgAckResult xAck;
        xAck.result = ER_NotEnoughMasterValue;
        GettheServer().SendMsgToSingle( &xAck, this );
        return false; 
    }

    // 增加等级
    gCharInfoServer.baseinfo.liveinfo.xMasterData.SetMasterLevel( GetMasterLevel() + 1 );
    ChangeAttr( CharAttr_MasterLevel, static_cast< DWORD >( GetMasterLevel() ), true );

    OperateMasterValue( EOT_Sub, pInfo->GetNeedMasterValue() );       // 减少威望值

    // 添加称号
    if ( pInfo->GetMasterTitleID() != TitleConfig::Init_ID )
    {
        AddTitle( pInfo->GetMasterTitleID() );
    }

    m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateMasterLevel, GetMasterLevel() );

    return true;
}

// 更新于某玩家的好友度
void GamePlayer::UpdateFriendly( uint32 dwPlayerID, uint8 uchOperate, uint32 nFriendly )
{
    RelationDataToServer* pData = m_pRelation->GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return; }

    unsigned int nCanAdd = theRelationConfig.GetMaxFriendly() - pData->GetFriendly();
    if ( nFriendly > nCanAdd )
    { nFriendly = nCanAdd; }
    if ( nFriendly == 0 )
    { return; }

    m_pRelation->SendUpdateRelationDataReqMessage( dwPlayerID, uchOperate, nFriendly );
}

void GamePlayer::SendAddRelationAckMessage( int nRelation, int nGroupID, const char* szName, int nResult )
{
    MsgAddRelationAck xAck;
    xAck.xRelationData.SetRelation( nRelation );
    xAck.xRelationData.SetGroupID( nGroupID );
    xAck.xRelationData.SetName( szName );
    xAck.uchResult = nResult;
    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgAddRelationReq( Msg* pMsg )
{
    MsgAddRelationReq* pReq = static_cast< MsgAddRelationReq* >( pMsg );
    if ( pReq == NULL )
    { return; }
    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );

    // 获得对方的关系属性
    GameRelation* pTargetRelation = theGameRelationManager.GetPlayerRelation( pReq->szName );
    if ( pTargetRelation == NULL )
    {
        return SendAddRelationAckMessage( pReq->stRelation, pReq->uchGroupID, pReq->szName, RelationDefine::NameError );
    }

    // 不能加自己
    if ( pTargetRelation->GetID() == GetDBCharacterID() )
    {
        return SendAddRelationAckMessage( pReq->stRelation, pReq->uchGroupID, pReq->szName, RelationDefine::CanNotAddSelf );
    }

    // 不在线不能加
    if ( !pTargetRelation->GetOnLine() )
    {
        return SendAddRelationAckMessage( pReq->stRelation, pReq->uchGroupID, pReq->szName, RelationDefine::NotOnLine );
    }

    // 判断是否能加此关系
    unsigned short ustCheckResult = m_pRelation->CheckCanAddRelation( pTargetRelation->GetID(), pReq->stRelation );
    if ( ustCheckResult != RelationDefine::CanAddRelation )
    {
        return SendAddRelationAckMessage( pReq->stRelation, pReq->uchGroupID, pReq->szName, ustCheckResult );
    }

    // 2级关系, 需判断对方是否满足条件
    if ( RelationData::IsHigherRelation( pReq->stRelation ) )
    {
        unsigned short ustRelation = pReq->stRelation;
        switch( pReq->stRelation )
        {
        case RelationDefine::Student:
            ustRelation = RelationDefine::Teacher;
            break;
        case RelationDefine::Teacher:
            ustRelation = RelationDefine::Student;
            break;
        default:
            break;
        }

        ustCheckResult = pTargetRelation->CheckCanAddRelation( GetDBCharacterID(), ustRelation );
        if ( ustCheckResult != RelationDefine::CanAddRelation )
        {
            // 处理错误逻辑
            switch ( ustCheckResult )
            {
            case RelationDefine::RelationFull:
                ustCheckResult = RelationDefine::TargetRelationFull;
                break;
            case RelationDefine::AddStudentTimeLimit:
                ustCheckResult = RelationDefine::TargetAddStudentTimeLimit;
                break;
            case RelationDefine::AddTeacherTimeLimit:
                ustCheckResult = RelationDefine::TargetAddTeacherTimeLimit;
                break;
            case RelationDefine::StudentCountLimit:
                ustCheckResult = RelationDefine::TargetStudentCountLimit;
                break;
            case RelationDefine::AlreadyHaveTeacher:
                ustCheckResult = RelationDefine::TargetAlreadyHaveTeacher;
                break;
            case RelationDefine::CanNotReceivePrentice:
                ustCheckResult = RelationDefine::TargetCanNotReceivePrentice;
                break;
            }

            return SendAddRelationAckMessage( pReq->stRelation, pReq->uchGroupID, pReq->szName, ustCheckResult );
        }
    }

    // 发送消息给CenterServer
    GS2CSAddRelationReq xReq;
    xReq.nReqID     = GetDBCharacterID();
    xReq.nAckID     = pTargetRelation->GetID();
    xReq.stRelation = pReq->stRelation;
    xReq.uchGroupID = pReq->uchGroupID;
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgUpdateRelationReq( Msg* pMsg )
{
    // 只把在线的好友更新给客户端
    m_pRelation->UpdateRelationToClient( this );
}

void GamePlayer::OnMsgInviterRelationAck( Msg* pMsg )
{
    MsgInviteRelationAck* pInvite = static_cast< MsgInviteRelationAck* >( pMsg );
    if ( pInvite == NULL )
    { return; }

    // 发送给CenterServer处理
    GS2CSAddRelationAck xAck;
    xAck.bAgreeAdd   = pInvite->bAgree;
    xAck.nReqID      = pInvite->nReqID;
    xAck.nAckID      = GetDBCharacterID();
    xAck.ustRelation = pInvite->stRelation;
    GettheServer().SendMsgToCenterServer( &xAck );
}

bool GamePlayer::OnMsgDeleteRelationReq( Msg* pMsg )    //请求删除好友 
{
    MsgDeleteRelationReq *pReq = static_cast< MsgDeleteRelationReq* >( pMsg );
    if ( pReq == NULL )
    { return false; }

    MsgDeleteRaltionAck xAck;
    xAck.nPlayerID  = pReq->nPlayerID;
    xAck.stRelation = pReq->stRelation;

    // 先做一个判断吧
    RelationDataToServer* pRelation = m_pRelation->GetRelationData( pReq->nPlayerID );
    if ( pRelation == NULL || !pRelation->HaveRelation( pReq->stRelation ) )
    { 
        xAck.nResult = MsgDeleteRaltionAck::ECD_NotHaveThisRelation;
        SendMessageToClient( &xAck );
        return false;
    }

    // 存在2级关系,不只能直接删除好友关系
    if ( pRelation->HaveHigherRelation() && RelationData::HaveRelation( pReq->stRelation, RelationDefine::Friend ) )
    {   
        xAck.nResult = MsgDeleteRaltionAck::ECD_CanNotDelRelation;
        SendMessageToClient( &xAck );
        return false;      
    }

	/*GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( xAck.nPlayerID );
	if ( pPlayer == NULL )
	{ return false; }
	pPlayer->SendMessageToClient( &xAck );*/

    GS2CSRemoveRelationReq xReq;
    xReq.nReqID     = GetDBCharacterID();
    xReq.nAckID     = pReq->nPlayerID;
    xReq.stRelation = pReq->stRelation;
    GettheServer().SendMsgToCenterServer( &xReq );

    return true;
}

void GamePlayer::OnDeleteRelationCheckAck( Msg* pMsg )
{
    MsgDeleteRelationCheckAck* pAck = static_cast< MsgDeleteRelationCheckAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pAck->nFriendID );
    if ( pPlayer == NULL )
    { return; }

    if ( !pAck->bDelete )
    {
        pPlayer->SetReqRemoveMarriage( false );
        pPlayer->SetForceRemove( false );

        pAck->nFriendID = GetDBCharacterID();
        pPlayer->SendMessageToClient( pAck );
        return;
    }

	GamePlayer* pPlayer1 = theRunTimeData.GetGamePlayerByDBID( GetDBCharacterID() );
	if ( pPlayer1 == NULL )
	{ return; }

	pPlayer->SendMessageToClient( pAck );
	pPlayer1->SendMessageToClient( pAck );

    MsgDeleteRelationReq xReq;
    xReq.nPlayerID  = GetDBCharacterID();
    xReq.stRelation = pAck->stRelation;
    pPlayer->OnMsgDeleteRelationReq( &xReq );
}

void GamePlayer::OnMsgRelationLockReq( Msg* pMsg )
{
    MsgRelationLockReq* pReq = static_cast< MsgRelationLockReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    int nValue = 1;
    m_pRelation->SendUpdateRelationDataReqMessage( pReq->nPlayerID, RelationDefine::UpdateLocked, nValue );
}

void GamePlayer::OnMsgRelationUnLockReq( Msg* pMsg )
{
    MsgRelationUnLockReq* pReq = static_cast< MsgRelationUnLockReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    int nValue = 0;
    m_pRelation->SendUpdateRelationDataReqMessage( pReq->nPlayerID, RelationDefine::UpdateLocked, nValue );
}

void GamePlayer::OnMsgQueryAttributeReq( Msg* pMsg )
{
    MsgQueryAttributeReq* pReq = static_cast< MsgQueryAttributeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }
																																		
    if ( !GameTime::IsPassCurrentTime( m_nLastQueryTime, 5000 ) )
    { return; } // 10秒内只能查询一次
    m_nLastQueryTime = HQ_TimeGetTime();

    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );

    // 直接发送给Database查询
    GS2CSQueryAttributeReq xReq;
    xReq.nPlayerID  = GetDBCharacterID();
    xReq.uchCountry = GetCountry();
    HelperFunc::SafeNCpy( xReq.szName, pReq->szName, sizeof( xReq.szName ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgRegisterRelationReq( Msg* pMsg )
{
    MsgRegisterRelationReq* pReq = static_cast< MsgRegisterRelationReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    const PrenticeLimit& xLimit = theRelationConfig.GetPrenticeLimit();

    switch ( pReq->ustRelation )
    {
    case RelationDefine::Student:
        if ( GetLevel() < xLimit.GetMinStudentLevel() )
        { return; }
        break;
    case RelationDefine::Teacher:
        if ( GetLevel() <  xLimit.GetMinTeacherLevel() )
        { return; }
        break;
    default:
        break;
    }

    // 信息直接保存在GameServer, 因为只能在此NPC获得信息 并且下线后信息不保存
    theGameRelationManager.AddRegisterID( GetDBCharacterID(), pReq->ustRelation );
}

void GamePlayer::OnMsgSetReceiveStrangerReq( Msg* pMsg )
{
    MsgSetReceiveStrangerReq* pReq = static_cast< MsgSetReceiveStrangerReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateMessageRefuse, pReq->ustMessageRefuse );
}

void GamePlayer::OnMsgChangeSignatureReq( Msg* pMsg )
{
    MsgChangeSignatureReq* pReq = static_cast< MsgChangeSignatureReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szSignature, sizeof( pReq->szSignature ) );

    if ( !theChatCheck->CheckStringInLow( pReq->szSignature ) )
    { return; }

    m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateSignature, pReq->szSignature );

    if (gCharInfoServer.visual.IsShowSignature())
    {
        MsgShowSignature msgShow ;
        msgShow.header.stID   = GetID();
        msgShow.showSignature = true;
        HelperFunc::SafeNCpy( msgShow.szSignature, pReq->szSignature  , RelationDefine::MaxSignLength );

        // 发给周围的人
        GettheServer().SendMsgToView( &msgShow, GetID(), true );
    }
}

void GamePlayer::OnMsgFindPlayerByCondition( Msg* pMsg )
{
	MsgFindByCondiotion* pReq = static_cast< MsgFindByCondiotion* >( pMsg );
	if ( NULL == pReq )
	{ return; }

	if ( !GameTime::IsPassCurrentTime( m_nLastFindPersonTime, 5000 ) )
	{ return; }
	m_nLastFindPersonTime = HQ_TimeGetTime();

	if ( ( pReq->uchUnlimit & RelationDefine::UnLimitPrv ) == RelationDefine::UNLimitInit )
	{// 限制省份
		HelperFunc::CheckStringValid( pReq->szProvince, sizeof( pReq->szProvince ) );
		if ( !theChatCheck->CheckStringInLow( pReq->szProvince ) )
		{ return; }
	}

	if ( ( pReq->uchUnlimit & RelationDefine::UnLimitCity ) == RelationDefine::UNLimitInit )
	{// 限制城市
		HelperFunc::CheckStringValid( pReq->szCity, sizeof( pReq->szCity ) );
		if ( !theChatCheck->CheckStringInLow( pReq->szCity ) )
		{ return; }
	}

	if ( pReq->uchAgeMin > pReq->uchAgeMax )
	{ return; }

	GS2CSFindPersonReq xReq;
	xReq.nPlayerID  = GetDBCharacterID();
	xReq.uchUnlimit = pReq->uchUnlimit;
	xReq.uchSex = pReq->uchSex;
	xReq.uchAgeMin = pReq->uchAgeMin;
	xReq.uchAgeMax = pReq->uchAgeMax;
	HelperFunc::SafeNCpy( xReq.szProvince, pReq->szProvince, sizeof( xReq.szProvince ) );
	HelperFunc::SafeNCpy( xReq.szCity, pReq->szCity, sizeof( xReq.szCity ) );
	GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgChangePersonalInfo( Msg* pMsg )
{
	MsgChangePersonalInfo* pReq = static_cast< MsgChangePersonalInfo* >( pMsg );
	if ( NULL == pReq )
	{ return; }
	
	HelperFunc::CheckStringValid( pReq->xPersonalInfo.szProvince, sizeof( pReq->xPersonalInfo.szProvince ) );
	if ( !theChatCheck->CheckStringInLow( pReq->xPersonalInfo.GetProvince() ) )
	{ return; }

	HelperFunc::CheckStringValid( pReq->xPersonalInfo.szCity, sizeof( pReq->xPersonalInfo.szCity ) );
	if ( !theChatCheck->CheckStringInLow( pReq->xPersonalInfo.GetCity() ) )
	{ return; }

	HelperFunc::CheckStringValid( pReq->xPersonalInfo.szProfession, sizeof( pReq->xPersonalInfo.szProfession ) );
	if ( !theChatCheck->CheckStringInLow( pReq->xPersonalInfo.GetProfession() ) )
	{ return; }

	HelperFunc::CheckStringValid( pReq->xPersonalInfo.szQQ, sizeof( pReq->xPersonalInfo.szQQ ) );
	if ( !theChatCheck->CheckStringInLow( pReq->xPersonalInfo.GetQQ() ) )
	{ return; }

	HelperFunc::CheckStringValid( pReq->xPersonalInfo.szMSN, sizeof( pReq->xPersonalInfo.szMSN ) );
	if ( !theChatCheck->CheckStringInLow( pReq->xPersonalInfo.GetMSN() ) )
	{ return; }

	HelperFunc::CheckStringValid( pReq->xPersonalInfo.szIntroduction, sizeof( pReq->xPersonalInfo.szIntroduction) );
	if ( !theChatCheck->CheckStringInLow( pReq->xPersonalInfo.GetIntroduction() ) )
	{ return; }

	m_pRelation->SendUpdatePersonalInfoReqMsg( pReq->xPersonalInfo );
}

void GamePlayer::OnMsgRelationGroupAddReq( Msg* pMsg )
{
    MsgRelationGroupAddReq* pReq = static_cast< MsgRelationGroupAddReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szGroup, sizeof ( pReq->szGroup ) );
    if ( pReq->szGroup[0] == 0 )
    { return; }

    if ( !theChatCheck->CheckStringInLow( pReq->szGroup ) )
    { return; }

    unsigned char uchGroupID = m_pRelation->CheckCanAddGroup( pReq->szGroup );
    if ( uchGroupID == 0 )
    { return; }

    m_pRelation->SendGroupNameChangeReqMessage( uchGroupID, pReq->szGroup );
}

void GamePlayer::OnMsgRelationGroupChangeNameReq( Msg* pMsg )
{
    MsgRelationGroupChangeNameReq* pReq = static_cast< MsgRelationGroupChangeNameReq* >( pMsg );
    if ( pReq == NULL || pReq->uchGroupID >= RelationDefine::GroupCount )
    { return; }

    HelperFunc::CheckStringValid( pReq->szGroup, sizeof( pReq->szGroup ) );

    // 默认组不让删除
    if ( pReq->uchGroupID == 0 && pReq->szGroup[0] == 0 )
    { return; }

    if ( !theChatCheck->CheckStringInLow( pReq->szGroup ) )
    { return; }

    m_pRelation->SendGroupNameChangeReqMessage( pReq->uchGroupID, pReq->szGroup );
}

void GamePlayer::OnMsgRelationGroupChangeReq( Msg* pMsg )
{
    MsgRelationGroupChangeReq* pReq = static_cast< MsgRelationGroupChangeReq* >( pMsg );
    if ( pReq == NULL || pReq->uchGroupID >= RelationDefine::GroupCount )
    { return; }

    if ( m_pRelation->IsEmptyGroup( pReq->uchGroupID ) )
    { return; }

    m_pRelation->SendUpdateRelationDataReqMessage( pReq->nPlayerID, RelationDefine::UpdateGroupID, pReq->uchGroupID );
}

void GamePlayer::OnMsgRelationRemarkChangeReq( Msg* pMsg )
{
    MsgRelationRemarkChangeReq* pReq = static_cast< MsgRelationRemarkChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szRemark, sizeof( pReq->szRemark ) );
    
    if ( !theChatCheck->CheckStringInLow( pReq->szRemark ) )
    { return; }

    m_pRelation->SendUpdateRelationDataReqMessage( pReq->nPlayerID, RelationDefine::UpdateRemark, pReq->szRemark );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// 如果可以结婚返回对方的指针
GamePlayer* GamePlayer::Script_CheckCanMarriage( int nOp )
{
    // 判断等级
    switch ( nOp )
    {
    case EMO_GainQuest:
    case EMO_Marriage:
        {
            if ( GetLevel() < theRelationConfig.GetMarriageMaleLevel() || GetSex() != Sex_Male )  // 男方等级需要达到35级
            { 
                MsgAckResult xResult;
                switch( nOp )
                {
                case EMO_GainQuest: // 领取结婚任务
                    { xResult.result = ER_MaleLevelLimit; }
                    break;
                case EMO_Marriage: // 结婚
                    { xResult.result = ER_MaleLevelLimit1; }
                    break;
                }

                xResult.value  = theRelationConfig.GetMarriageMaleLevel();
                SendMessageToClient( &xResult );
                return NULL; 
            }        
        } 
        break;
    case EMO_OpenLoveIsLand:
        {
        }
        break;
    }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { 
        MsgAckResult xResult;
        xResult.result = ER_MustHaveTeam;
        GettheServer().SendMsgToSingle( &xResult, this );
        return NULL; 
    }

    if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )   // 男方不是队长
    { 
        MsgAckResult xResult;
        xResult.result = ER_MustBeTeamHeader;
        GettheServer().SendMsgToSingle( &xResult, this );
        return NULL; 
    }   

    if ( pTeam->TeamMemberCount() > 2 ) // 只能2个人的队伍
    { 
        MsgAckResult xResult;
        xResult.result = ER_OnlyTwoTeamMember;
        GettheServer().SendMsgToSingle( &xResult, this );
        return NULL; 
    }     

    DWORD dwMarriageID = InvalidLogicNumber;       // 得到女方ID
    for ( int i = 0; i < 2; ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == pTeam->GetTeamHeaderID() )
        { continue; }

        // 判断女方
        dwMarriageID = pMember->GetID();
        break;
    }

    // 判断是否可以结婚
    if ( !CheckCanMarriage( dwMarriageID, nOp ) )
    { return NULL; }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwMarriageID );
	if (pPlayer == NULL||!pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 20.f ))
	{
		//如果本服务器没找到,则有可能不是同个服务器,判定为距离过远
		//需要在附近才可以
		MsgAckResult xResult;
		xResult.result = ER_MustInArea;
		GettheServer().SendMsgToSingle( &xResult, this );
		return NULL; 
	}

    if (pPlayer->GetLevel() < theRelationConfig.GetMarriageFemaleLevel() || pPlayer->GetSex() != Sex_Female )   // 对方等级和性别都不满足
    {
        MsgAckResult xResult;
        xResult.result = ER_FemaleLevelLimit;
        xResult.value  = theRelationConfig.GetMarriageFemaleLevel();
        GettheServer().SendMsgToSingle( &xResult, this );
        return NULL; 
    }

    if ( pPlayer->GetCountry() != GetCountry() )
    { return NULL; }

    //if ( !pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 20.f ) )      // 需要在附近才可以
    //{ 
    //    MsgAckResult xResult;
    //    xResult.result = ER_MustInArea;
    //    GettheServer().SendMsgToSingle( &xResult, this );
    //    return NULL; 
    //}       

    if ( !pPlayer->CheckCanMarriage( GetDBCharacterID(), nOp ) )
    { return NULL; }

    return pPlayer;
}

bool GamePlayer::CheckCanMarriage( unsigned int dwMarriageID, int nOp )
{
    switch ( nOp )
    {
    case EMO_GainQuest: // 领取结婚任务
    case EMO_Marriage:  // 结婚
        {
            if ( m_pRelation->IsHaveMarriage() ) // 已经有夫妻关系了
            { 
                SendErrorToClient( ER_SelfAlreadyHaveMarriage );
                return false;
            }

            // 没有好友关系, 或者已经有2级关系了不能结婚
            RelationDataToServer* pData = m_pRelation->GetRelationData( dwMarriageID );
            if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) || pData->HaveHigherRelation() )    
            { 
                SendErrorToClient( ER_OnlyFriend );
                return false;
            }

            // 好友度不够1000
            if ( pData->GetFriendly() < theRelationConfig.GetMarriageFriendly() )   
            { 
                SendErrorToClient( ER_FriendlyLimit,theRelationConfig.GetMarriageFriendly() );
                return false;
            }
        }
        break;
    case EMO_OpenLoveIsLand:    // 开启爱心岛
        {
            if ( !m_pRelation->IsHaveMarriage() ) // 还没有夫妻关系
            { 
                SendErrorToClient( ER_CreateMustBeMarriage );
                return false;
            }

            RelationDataToServer* pData = m_pRelation->GetRelationData( dwMarriageID );
            if ( pData == NULL || !pData->HaveRelation( RelationDefine::Marriage ) ) 
            { 
                SendErrorToClient( ER_CreateMustBeMarriage );
                return false;
            }
        }
        break;
    default:
        return false;
    }

    return true;
}

// 判断时候满足结婚条件
bool GamePlayer::Script_AddMarriage()
{
    GamePlayer* pPlayer = Script_CheckCanMarriage( EMO_Marriage );
    if ( pPlayer == NULL )
    { return false; }

    // 发送添加夫妻请求
    AddRelation( pPlayer->GetCharName(), RelationDefine::Marriage );         
    return true;
}

bool GamePlayer::Script_RemoveMarriage( bool bForceRemove )
{
    if ( !m_pRelation->IsHaveMarriage() )
    { return false; }

    //if ( CheckSecondPasswordOperate( MsgCheckSecondPasswordReq::OP_DelRelation ) )
    //{ return false; }       // 验证2级别密码

    bool bResult = false;
    if ( !bForceRemove )        // 非强制解除, 要判断对方是否在队伍中
    {
        GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
        if ( pTeam == NULL )
        { 
            MsgAckResult xResult;
            xResult.result = ER_MustHaveTeam;
            GettheServer().SendMsgToSingle( &xResult, this );
            return false; 
        }

        if ( pTeam->TeamMemberCount() > 2 )     // 队伍中必须有两个人
        {
            MsgAckResult xResult;
            xResult.result = ER_OnlyTwoTeamMember;
            GettheServer().SendMsgToSingle( &xResult, this );
            return false;
        }

        if ( !pTeam->IsInTeam( m_pRelation->GetMarriageID() ) )        // 对方必须在队伍中
        {
            MsgAckResult xResult;
            xResult.result = ER_TargetMustInTeam;
            GettheServer().SendMsgToSingle( &xResult, this );
            return false;
        }

        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( m_pRelation->GetMarriageID() );
        if ( pPlayer == NULL )
        { 
            MsgAckResult xResult;
            xResult.result = ER_MustInArea;
            xResult.value  = 20;
            GettheServer().SendMsgToSingle( &xResult, this );
            return false; 
        }

        bResult = pPlayer->SendDeleteRelationCheckMessage( GetDBCharacterID(), RelationDefine::Marriage );
    }
    else
    {
        MsgDeleteRelationReq xReq;
        xReq.nPlayerID  = m_pRelation->GetMarriageID();
        xReq.stRelation = RelationDefine::Marriage;

        bResult = OnMsgDeleteRelationReq( &xReq );
    }

    SetReqRemoveMarriage( true );
    SetForceRemove( bForceRemove );

    return bResult;
}

// 创建结婚场景
bool GamePlayer::Script_CreateMarriageStage( unsigned short ustMapID )
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( ustMapID );
    if ( pMapData == NULL )
    { return false; }

    if ( pMapData->GetMapType() != MapConfig::MT_MultiPlayer )
    { 
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "结婚场景地图类型设置错误！" );
        return false;
    }

    // 满足结婚条件才能开启结婚场景
    GamePlayer* pPlayer = Script_CheckCanMarriage( EMO_OpenLoveIsLand );
    if ( pPlayer == NULL )
    { return false; }

    // 判断是否已经开启过了
    std::vector< GameStage* > vecStage( 0 );
    theGameWorld.GetCurMapStage( ustMapID, vecStage );
    if ( !vecStage.empty() )
    {
        for ( std::vector< GameStage* >::iterator iter = vecStage.begin(); iter != vecStage.end(); ++iter )
        {
            if ( !( *iter )->IsEctypeStage() )
            { continue; }

            EctypeStage* pStage = static_cast< EctypeStage* >( *iter );
            if ( pStage->IsSpecialID( GetDBCharacterID() ) )     
            {
                SendErrorToClient( ER_MarriageStageAlreadyExist );
                return false;
            }
        }
    }

    // 获得当前系统中该副本的总数
    int nStageCount = theGameWorld.GetMapCount( ustMapID );
    if ( nStageCount >= pMapData->Count )
    {

        SendErrorToClient( ER_MarriageStageCountLimit, pMapData->Count );
        return false;
    }

    GetScriptInterface()->RecordIds();

    DWORD dwMapID = theGameWorld.GetEctypeMapID( ustMapID, true );
    GameStage* pStage = theGameWorld.SingleCreateStage( ustMapID , dwMapID ); // 使用单线程创建
    if ( pStage == NULL )
    {
        SendErrorToClient( ER_CreateMarriageStageFailed );
        return false;
    }
    // 单线程创建地图会占用到 GetScriptInterface 所以要保留一份
    GetScriptInterface()->ResumeIds();

    // 设置该结婚场景归属
    EctypeStage* pEctypeStage = static_cast< EctypeStage* >( pStage );
    pEctypeStage->SetSpecialID( GetDBCharacterID(), pPlayer->GetDBCharacterID() );
    return true;
}

bool GamePlayer::Script_FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir )
{
    std::vector< GameStage* > vecStage( 0 );
    theGameWorld.GetCurMapStage( ustMapID, vecStage );
    if ( vecStage.empty() )
    {
        SendErrorToClient( ER_MarriageStageNotExist );
        return false;
    }

    GameStage* pMarriageStage = NULL;
    for ( std::vector< GameStage* >::iterator iter = vecStage.begin(); iter != vecStage.end(); ++iter )
    {
        if ( !( *iter )->IsEctypeStage() )
        { continue; }

        EctypeStage* pStage = static_cast< EctypeStage* >( *iter );
        if ( pStage->IsSpecialID( GetDBCharacterID() ) )     
        {
            pMarriageStage = pStage;
            break;
        }
    }

    if ( pMarriageStage == NULL )  // 不是新人, 判断背包中是否有请帖
    {
        unsigned int dwSpecialID = 0;
        for ( int i = 0; i < _NormalItemBag.GetNowBagSize(); ++i )
        {
            SCharItem* pCharItem = _NormalItemBag.GetItemByIndex( i );
            if ( pCharItem == NULL )
            { continue; }

            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
            if ( pItemCommon == NULL || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_SPECIAL )
            { continue; }

            ItemDefine::SItemSpecial* pItemSpecial = static_cast< ItemDefine::SItemSpecial* >( pItemCommon );
            if ( pItemSpecial == NULL || pItemSpecial->uchSpecialType != ItemDefine::SItemSpecial::ECD_MarriageCard )
            { continue; }

            dwSpecialID = pCharItem->itembaseinfo.value1;       // 得到专属ID
            break;
        }

        for ( std::vector< GameStage* >::iterator iter = vecStage.begin(); iter != vecStage.end(); ++iter )
        {
            if ( !( *iter )->IsEctypeStage() )
            { continue; }

            EctypeStage* pStage = static_cast< EctypeStage* >( *iter );
            if ( pStage->IsSpecialID( dwSpecialID ) )   
            {
                pMarriageStage = pStage;
                break;
            }
        }
    }

    if ( pMarriageStage == NULL )
    {
        // 没有开启, 或者已经关闭了
        SendErrorToClient( ER_MarriageStageNotExist );
        return false;
    }

    return FlyToMapReq( pMarriageStage->GetStageID(), fX, fY, fDir );
}


bool GamePlayer::Script_CheckCanReceiveMarriageQuest( bool bMarriage )
{
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { 
        SendErrorToClient( ER_MustHaveTeam );
        return false;
    }

    if ( pTeam->TeamMemberCount() > 2 )     // 只能2个人的队伍
    { 
        SendErrorToClient( ER_OnlyTwoTeamMember );
        return false;
    }     

    DWORD dwTargetPlayerID = InvalidLogicNumber;       // 得到对方ID
    for ( int i = 0; i < 2; ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        // 判断女方
        dwTargetPlayerID = pMember->GetID();
        break;
    }   

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwTargetPlayerID );
    if ( pPlayer == NULL || !pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 20.f ) )      // 需要在附近才可以
    { 
        SendErrorToClient( ER_MustInArea );
        return false;
    } 

    GameRelation* pAckRelation = pPlayer->GetRelation();
    if ( pAckRelation == NULL )
    { return false; }

    if ( bMarriage )        // 已经结婚了
    {
        if ( !m_pRelation->IsHaveMarriage() || dwTargetPlayerID != m_pRelation->GetMarriageID() )
        { 
            SendErrorToClient( ER_MarriageMustInTeam );
            return false;
        }  
    }
    else            // 结婚前
    {
        if ( GetSex() == Sex_Male )
        {
            if ( pPlayer->GetSex() != Sex_Female || pPlayer->GetLevel() < theRelationConfig.GetMarriageFemaleLevel() )
            {
                SendErrorToClient( ER_FemaleLevelLimit, theRelationConfig.GetMarriageFemaleLevel() );
                return false;
            }
        }
        else
        {
            if ( pPlayer->GetSex() != Sex_Male || pPlayer->GetLevel() < theRelationConfig.GetMarriageMaleLevel() )
            {
                SendErrorToClient( ER_MaleLevelLimit, theRelationConfig.GetMarriageMaleLevel() );
                return false;
            }
        }

        if ( m_pRelation->IsHaveMarriage() )
        {
            SendErrorToClient( ER_SelfAlreadyHaveMarriage );
            return false;
        }

        if ( pAckRelation->IsHaveMarriage() )
        {
            SendErrorToClient( ER_TargetAlreadyHaveMarriage );
            return false;
        }

        RelationDataToServer* pReqData = m_pRelation->GetRelationData( pPlayer->GetDBCharacterID() );
        if ( pReqData == NULL || !pReqData->HaveRelation( RelationDefine::Friend ) || pReqData->HaveHigherRelation() )
        {
            SendErrorToClient( ER_OnlyFriend );
            return false;
        }

        if ( pReqData->GetFriendly() < theRelationConfig.GetMarriageFriendly() )    // 好友度不够1000
        { 
            SendErrorToClient( ER_FriendlyLimit, theRelationConfig.GetMarriageFriendly() );
            return false;
        }     
    }   

    return true;
}

void GamePlayer::GetRelationNameByTitle( unsigned short ustTitleID, char* szName, int nSize )
{
    if ( ustTitleID == TitleConfig::Init_ID )
    { return; }

    memset( szName, 0, nSize );

    TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( ustTitleID );
    if ( pTitleConfig == NULL )   
    { return; }

    // 如果是夫妻 或者徒弟 称号
    unsigned int nRelationID = RelationDefine::InitID;
    switch ( pTitleConfig->GetType() )
    {
    case TitleConfig::Title_Marriage:
        nRelationID = GetMarriageID();
        break;
    case TitleConfig::Title_Student:
        nRelationID = GetTeacherID();
        break;
    default:
        return;
        break;
    }

    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( nRelationID );
    if ( pRelation == NULL )
    { return; }

    HelperFunc::SafeNCpy( szName, pRelation->GetName(), nSize );
}

const char* GamePlayer::GetMarriageName()
{
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( GetMarriageID() );
    if ( pRelation == NULL )
    { return ""; }

    return pRelation->GetName();
}

int GamePlayer::GetMaxFriendlyLevel()
{
    return m_pRelation->GetMaxFriendlyLevel();
}

bool GamePlayer::IsCanReceiveFriendlyQuest()
{
    // 判断队伍
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    {
        SendErrorToClient( ER_ReceiveFriendlyQuestMustHaveTeam );
        return false;
    }

    if ( pTeam->TeamMemberCount() > 2 )
    {
        SendErrorToClient( ER_ReceiveFriendlyQuestOnlyTwoMember );
        return false;
    }

    // 判断是否是好友
    unsigned int dwFriendID = TeamDefine::ErrorID;
    for ( int i = 0; i < 2; ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        dwFriendID = pMember->GetID();
    }
    if ( dwFriendID == TeamDefine::ErrorID )
    { return false; }

    if ( !m_pRelation->HaveRelation( dwFriendID, RelationDefine::Friend ) )
    { 
        SendErrorToClient( ER_ReceiveFriendlyQuestMustFriend );
        return false;
    }

    bool bClear = false;
    if ( m_pRelation->HaveReceiveQuestTime( dwFriendID, bClear ) )
    {
        SendErrorToClient( ER_ReceiveFriendlyCountLimit );
        return false;
    }

    if ( bClear )
    { m_pRelation->SendReceiveQuestTimeMessage( TeamDefine::ErrorID, bClear ); }

    return true;
}

void GamePlayer::SaveReceiveFriendlyQuest()
{
    // 判断队伍
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { return; }

    if ( pTeam->TeamMemberCount() > 2 )
    { return; }

    // 判断是否是好友
    unsigned int dwFriendID = TeamDefine::ErrorID;
    for ( int i = 0; i < 2; ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        dwFriendID = pMember->GetID();
    }
    if ( dwFriendID == TeamDefine::ErrorID )
    { return; }

    if ( !m_pRelation->HaveRelation( dwFriendID, RelationDefine::Friend ) )
    { return; }

    m_pRelation->SendReceiveQuestTimeMessage( dwFriendID, false );
}

void GamePlayer::ProcessRelationKilledByPlayer( GamePlayer* pPlayer )
{
    RelationDataToServer* pData = m_pRelation->GetRelationData( pPlayer->GetDBCharacterID() );
    // 没关系, 或者临时好友, 加为仇人
    if ( pData == NULL || pData->HaveRelation( RelationDefine::TempFriend ) )
    {
        AddRelation( pPlayer->GetCharName(), RelationDefine::Vendetta );   
    }
}

void GamePlayer::ProcessRelationKillPlayer( GamePlayer* pPlayer )
{
    RelationDataToServer* pData = m_pRelation->GetRelationData( pPlayer->GetDBCharacterID() );
    if ( pData == NULL )
    { return; }

    // 杀死了自己的仇人, 报仇成功, 删除仇人列表
    if ( pData->HaveRelation( RelationDefine::Vendetta ) )
    {
        MsgDeleteRelationReq xReq;
        xReq.nPlayerID = pPlayer->GetDBCharacterID();
        xReq.stRelation = RelationDefine::Vendetta;
        OnMsgDeleteRelationReq( &xReq );
    }
    else if ( pData->HaveRelation( RelationDefine::Friend ) )   // 杀死了自己的好友, 扣好友度
    {
        UpdateFriendly( pPlayer->GetDBCharacterID(), RelationDefine::UpdateSubFriendly, theRelationConfig.GetKillSubFriendly() );
    }
}

void GamePlayer::RegisterRelation( unsigned short ustRelation )
{
    MsgRegisterRelationReq xReq;
    xReq.ustRelation = ustRelation;
    OnMsgRegisterRelationReq( &xReq );
}

void GamePlayer::QueryRegisterRelation( unsigned short ustRelation )
{
    theGameRelationManager.SendRegisterRelation( GetDBCharacterID(), ustRelation );
}

void GamePlayer::RemoveTeacher()
{
    if ( !IsHaveTeacher() )
    { return; }

    MsgDeleteRelationReq xReq;
    xReq.nPlayerID = GetTeacherID();
    xReq.stRelation = RelationDefine::Teacher;
    OnMsgDeleteRelationReq( &xReq );
}

void GamePlayer::QueryAddRelationLeftTime( unsigned short ustRelation )
{
    const PrenticeLimit& pLimit = theRelationConfig.GetPrenticeLimit();
    TimeSpan xSpanLimit;

    TimeEx xLastTime;
    switch ( ustRelation )
    {
    case RelationDefine::Teacher:
        xLastTime  = m_pRelation->GetLastAddTeacherTime();
        xSpanLimit = TimeSpan( static_cast< __int64 >( pLimit.GetStudentTimeSpan() * OneHourSecond ) ); 
    	break;
    case RelationDefine::Student:
        xLastTime = m_pRelation->GetLastAddStudentTime();
        xSpanLimit = TimeSpan( static_cast< __int64 >( pLimit.GetTeacherTimeSpan() * OneHourSecond ) ); 
        break;
    default:
        return;
    }

    MsgTellAddRelationTimeLeft xTell;
    xTell.ustRelation = ustRelation;

    TimeSpan xSpan = TimeEx::GetCurrentTime() - xLastTime;
    if ( xSpan < xSpanLimit )
    {
        xTell.nTimeLeft = xSpanLimit.GetTotalSeconds() - xSpan.GetTotalSeconds();
    }

    SendMessageToClient( &xTell );
}


void GamePlayer::ProcessStudentLevelUp( uint32 nStudentID, bool bIsStudent, uint32 nRewardExp, uint32 nRewardMasterValue )
{
    IncreaseExp( nRewardExp, 0 );
    OperateMasterValue( EOT_Add, nRewardMasterValue );

    MsgStudentLevelUp xLevelUp;
    xLevelUp.nStudentID         = nStudentID;
    xLevelUp.bIsStudent         = bIsStudent;
    xLevelUp.nRewardExp         = nRewardExp;
    xLevelUp.nRewardMasterValue = nRewardMasterValue;
    SendMessageToClient( &xLevelUp );
}

void GamePlayer::AddStudent()
{
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL || !pTeam->IsTeamHeader( GetDBCharacterID() ) )
    { return; }

    if ( pTeam->TeamMemberCount() > 2 )
    { return; }

    uint32 dwPlayerID = TeamDefine::ErrorID;       // 得到对方ID
    for ( int i = 0; i < 2; ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        // 判断女方
        dwPlayerID = pMember->GetID();
        break;
    }   

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
    if ( pPlayer == NULL )
    { return; }

    AddRelation( pPlayer->GetCharName(), RelationDefine::Student );
}

bool GamePlayer::IsCanRegisterTeacher()
{
    const MasterInfo* pInfo = theRelationConfig.GetMasterInfo( GetMasterLevel() );
    if ( pInfo == NULL )
    { return false; }

    if ( m_pRelation->GetStudentCount() >= pInfo->GetRecruitCount() )
    { return false; }

    // 判断自己的时间限制

    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    if ( !TimeEx::IsPassCurrentTime( m_pRelation->GetLastAddStudentTime(), xPrenticeLimit.GetTeacherTimeSpan() * OneHourSecond ) )
    { return false; }

    return true;
}

bool GamePlayer::IsCanRegisterStudent()
{
    if ( IsHaveTeacher() )
    { return false; }

    // 判断自己的时间限制
    const PrenticeLimit& xPrenticeLimit = theRelationConfig.GetPrenticeLimit();
    if ( !TimeEx::IsPassCurrentTime( m_pRelation->GetLastAddTeacherTime(), xPrenticeLimit.GetStudentTimeSpan() * OneHourSecond ) )
    { return false; }

    return true;
}

int GamePlayer::GetStudentCount()
{
    return m_pRelation->GetStudentCount();
}

float GamePlayer::CalcStudentExpModulus()
{
    if ( !IsHaveTeacher() )
    { return 0.f; }        // 没有师傅

    const RelationConfig::StudentExpModulus& xSetting = theRelationConfig.GetStudentExpModulus();

    // 计算排行榜等级差
    int nLevelDistance = 10;
    if ( nLevelDistance < xSetting.GetLevelDistance() )
    { return 0.f; }

    // 有师傅但不在队伍中
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL || !pTeam->IsInTeam( GetTeacherID() ) )
    { return xSetting.GetNoTeamModulus(); }

    return xSetting.GetHaveTeamModulus();
}