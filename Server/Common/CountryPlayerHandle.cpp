#include "CountryMessage.h"
#include "GamePlayer.h"
#include "GameWorld.h"
#include "CountryManager.h"
#include "TimeEx.h"
#include "CountryConfig.h"
#include "ChatCheck.h"
#include "CampBattleControl.h"
#include "ShareData.h"
#include "../Common/CountryReward.h"
#include "XmlStringLanguage.h"
#include "Raise.h"
#include "ChangeCountryConfig.h"
#include "CountryQuestFlyMapConfig.h"
#include "LogEventService.h"
#include "SevenDays.h"

#ifndef	RandCountry		
#define RandCountry			11
#endif	RandCountry
bool GamePlayer::ProcessCountryMsg( Msg* pMsg )
{
    if ( m_pCountry == NULL )
    { return false; }

    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_QUERYCOUNTRYINFOREQ,        OnMsgQueryCountryInfoReq         )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYNOTICECHANGEREQ,     OnMsgCountryNoticeChangeReq      )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYQUESTSTATECHANGEREQ, OnMsgCountryQuestStatusChangeReq )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYOFFICIALAPPOINTREQ,  OnMsgCountryOfficialAppointReq   )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYOFFICIALRECALLREQ,   OnMsgCountryOfficialRecallReq    )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYREQUESTRAISEREQ,     OnMsgCountryRequestRaiseReq      )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYRAISETOPLAYERACK,    OnMsgCountryRaiseToPlayerAck     )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYFLYTOBORDERSREQ,     OnMsgCountryFlyToBordersReq      )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYOPERATETOPLAYERREQ,  OnMsgCountryOperateToPlayerReq   )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYCONVENEACK,          OnMsgCountryConveneAck           )
        GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYCHANGEREQ,           OnMsgCountryChangeReq            )
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGECOUNTRYNAMEREQ,       OnMsgChangeCountryNameReq        )
		GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYFLYMAPREQ,		   OnMsgCountryQuestFlyReq          )
        GAMESERVER_MESSAGE_HANDLE( MSG_DELCOUNTRYOFFICIALREQ,	   OnMsgDelCountryOfficialReq          )
        
		GAMESERVER_MESSAGE_HANDLE( MSG_LOADCOUNTRYINFOREQ,			OnMsgLoadCountryInfoReq          )

		GAMESERVER_MESSAGE_HANDLE( MSG_COUNTRYBUFFCHANGEACK,			OnMsgCountryBuffChangeAck          )
    GAMESERVER_MESSAGE_MAPPING_END

    return false;
}

void GamePlayer::InitPlayerCountry( GameCountry* pCountry )
{
    SetCountry( pCountry->GetID() );
    m_pCountry = pCountry; 
	SetCountryId(pCountry->GetID());
}

uint8 GamePlayer::GetCountryTitle() const
{ 
    return gCharInfoServer.baseinfo.liveinfo.nCountryTitle; 
}

uint8 GamePlayer::GetCountryTitle( uint8 uchGuardType )
{
    uint8 uchTitle = CountryDefine::Title_None;
    if ( m_pGuild == NULL )
    { return uchTitle; }

    switch ( uchGuardType )
    {
    case CountryDefine::Guard_Dragon:
        {
            if ( m_pGuild->GetID() == m_pCountry->GetDragonGuild() )
            {
                uchTitle = CountryDefine::Title_DragonGuard;
                if ( m_pGuild->IsMaster( GetDBCharacterID() ) )
                {
                    uchTitle = CountryDefine::Title_Dragon;
                }
            }
        }
        break;
    case CountryDefine::Guard_Rosefinch:
        {
            if ( m_pGuild->GetID() == m_pCountry->GetRosefinchGuild() )
            {
                uchTitle = CountryDefine::Title_RosefinchGuard;
                if ( m_pGuild->IsMaster( GetDBCharacterID() ) )
                {
                    uchTitle = CountryDefine::Title_Rosefinch;
                }
            }
        }
        break;
    default:
        break;
    }

    return uchTitle;
}

// 计算称号
void GamePlayer::InitCountryTitle( bool bSendMessage )
{
    uint8 uchCountryTitle = CountryDefine::Title_None;
    /*if ( m_pGuild == NULL )
    { return; }*/

    uint8 uchPositon = m_pCountry->GetPosition( GetDBCharacterID() );
    if ( uchPositon != CountryDefine::Position_None )
    {
        uchCountryTitle = CountryDefine::GetCountryTitleByPosition( uchPositon );
    }
    else
    {
        uchCountryTitle = CalcCountryGuardTitle();
        if ( uchCountryTitle == CountryDefine::Position_None )
        {
            switch ( GetGuildPositon() )
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
            case GuildDefine::Position_Member:
                uchCountryTitle = CountryDefine::Title_GuildMember;
            default:
                break;
            }
        }
    }

    SetCountryTitle( uchCountryTitle, bSendMessage );
}

uint8 GamePlayer::CalcCountryGuardTitle()
{
    if ( m_pGuild == NULL )
    { return CountryDefine::Title_None; }
    
    uint8 uchCountryTitle = CountryDefine::Title_None;
    if ( m_pGuild->GetID() == m_pCountry->GetKingGuild() )
    {
        uchCountryTitle = CountryDefine::Title_KingGuard;
    }
    else if ( m_pGuild->GetID() == m_pCountry->GetDragonGuild() )
    {
        uchCountryTitle = CountryDefine::Title_DragonGuard;
        if ( m_pGuild->IsMaster( GetDBCharacterID() ) )
        {
            uchCountryTitle = CountryDefine::Title_Dragon;
        }
    }
    else  if ( m_pGuild->GetID() == m_pCountry->GetRosefinchGuild() )
    {
        uchCountryTitle = CountryDefine::Title_RosefinchGuard;
        if ( m_pGuild->IsMaster( GetDBCharacterID() ) )
        {
            uchCountryTitle = CountryDefine::Title_Rosefinch;
        }
    }

    return uchCountryTitle;
}

// 设置国家称号
void GamePlayer::SetCountryTitle( unsigned short ustValue, bool bSendMessage )
{
	//判断国家称号
	if(CountryDefine::Title_Queen == ustValue)
	{
		//判断玩家性别 
		if(GetSex() == Sex_Male)
			ustValue = CountryDefine::Title_QueenMale;//亲王称号
	}

    gCharInfoServer.baseinfo.liveinfo.nCountryTitle = ustValue;

    if ( !bSendMessage )
    { return; }

    MsgTellCountryTitleInfo xInfo;
    xInfo.stPlayerID     = GetID();
    xInfo.stCountryTitle = ustValue;
    GettheServer().SendMsgToView( &xInfo, GetID(), false );

    // 更新关系属性
    m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdatePosition, ustValue );
}

void GamePlayer::TellAllCountryName()
{
    MsgTellCountryName xTell;
    for ( int i = 1; i < CountryDefine::Country_Max; ++i )
    {
        GameCountry* pCountry = theGameCountryManager.GetCountry( i );
        if ( pCountry == NULL )
        { continue; }

        HelperFunc::SafeNCpy( xTell.szName[ i ], pCountry->GetName(), sizeof( xTell.szName[ i ] ) );
    }

    SendMessageToClient( &xTell );
}

void GamePlayer::TellWeakCountry()
{
    MsgCountryTellWeak xTell;
    xTell.uchWeakCountryID = theGameCountryManager.GetWeakCountry(); 
    SendMessageToClient( &xTell );
}
void GamePlayer::TellStrongCountry()
{
    MsgCountryTellStrong xTell;
    xTell.uchStrongCountryID = theGameCountryManager.GetStrongCountry(); 
    SendMessageToClient( &xTell );
}

void GamePlayer::TellCountryQuestStatus()
{
    MsgTellCountryQuestStatus xTell;

    for ( int i = CountryDefine::QuestType_None; i < CountryDefine::QuestType_Max; ++i )
    {
        OperateTime* pOperateTime = m_pCountry->GetQuestOperate( i );
        if ( pOperateTime == NULL || pOperateTime->GetStartTime() == 0 )
        { continue; }

        MsgTellCountryQuestStatus::QuestStatus xStatus;
        xStatus.uchType      = i;
        xStatus.n64StartTime = pOperateTime->GetStartTime();
        xStatus.bNeedNotice  = false;
        xTell.AddQuestStatus( xStatus );
    }

    if ( xTell.nCount > 0 )
    {
        SendMessageToClient( &xTell );
    }
}

uint8 GamePlayer::GetCountryOfficial()
{
    return m_pCountry->GetPosition( GetDBCharacterID() );
}

bool GamePlayer::IsHaveCountryMaster( uint8 uchType, uint8 uchCountry )
{
    if ( uchCountry == CountryDefine::Country_Init )
    { uchCountry = GetCountry(); }

    switch ( uchType )
    {
    case CountryDefine::Battle_King:
        return m_pCountry->IsHaveKing();
        break;
    case CountryDefine::Battle_Dragon:
        return m_pCountry->IsHaveDragon();
        break;
    case CountryDefine::Battle_Rosefinch:
        return m_pCountry->IsHaveRosefinch();
        break;
    default:
        break;
    }

    return false;
}

bool GamePlayer::IsCountryMaster( uint8 uchType )
{
    if ( !IsCountryGuild( uchType ) )
    { return false; }

    return m_pGuild->IsMaster( GetDBCharacterID() );
}

bool GamePlayer::IsCountryGuild( uint8 uchType )
{
    if ( m_pGuild == NULL )
    { return false; }

    uint32 dwGuildID = CountryDefine::NoneID;
    switch ( uchType )
    {
    case CountryDefine::Battle_King:
        dwGuildID = m_pCountry->GetKingGuild();
        break;
    case CountryDefine::Battle_Dragon:
        dwGuildID = m_pCountry->GetDragonGuild();
        break;
    case CountryDefine::Battle_Rosefinch:
        dwGuildID = m_pCountry->GetRosefinchGuild();
        break;
    default:
        return false;
    }

    return m_pGuild->GetID() == dwGuildID;
}

bool GamePlayer::IsCountryMount( SMountItem* pMount )
{
    if ( pMount == NULL )
    { return true; }

    for ( int i = 0; i < theCountryConfig.GetMountSettingCount(); ++i )
    {
        const CountryConfig::MountSetting* pSetting = theCountryConfig.GetMountSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }

        if ( pMount->GetMountID() == pSetting->GetKingID()  || pMount->GetMountID() == pSetting->GetQueenID() ||
            pMount->GetMountID() == pSetting->GetDragonID() || pMount->GetMountID() == pSetting->GetRostfinchID() )
        {
            return true;
        }
    }

    return false;
}

// 获得国家坐骑
SMountItem* GamePlayer::GetCountryMount()
{
    if ( m_nCountryMountGUID == InvalidLogicNumber )
    { return NULL; }

    SMountItem* pMount = _mountManager.GetMountByGuid( m_nCountryMountGUID );
    if ( pMount == NULL )
    {
        m_nCountryMountGUID = InvalidLogicNumber;
        return NULL;
    }

    return pMount;
}

SMountItem* GamePlayer::FindCountryMount()
{
    for ( int j = 0; j < _mountManager.GetMountCount(); ++j )
    {
        SMountItem* pMount = _mountManager.GetMountByIndex( j );
        if ( pMount == NULL )
        { continue; }

        for ( int i = 0; i < theCountryConfig.GetMountSettingCount(); ++i )
        {
            const CountryConfig::MountSetting* pSetting = theCountryConfig.GetMountSettingByIndex( i );
            if ( pSetting == NULL )
            { continue; }

            if ( pMount->GetMountID() == pSetting->GetKingID() || pMount->GetMountID() == pSetting->GetQueenID() ||
                pMount->GetMountID() == pSetting->GetDragonID() || pMount->GetMountID() == pSetting->GetRostfinchID() )
            {
                return pMount;
            }
        }
    }

    return NULL;
}

bool GamePlayer::ReceiveCountryMount( uint8 uchType )
{
    __int64 n64MountGuid = InvalidLogicNumber;

    switch ( uchType )
    {
    case CountryDefine::MountType_King:
        {
            unsigned char uchPositon = m_pCountry->GetPosition( GetDBCharacterID() );
            if ( uchPositon != CountryDefine::Position_King && uchPositon != CountryDefine::Position_Queen )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_NotRight );
                return false;
            }

            // 判断是否已经有了国王坐骑
            if ( GetCountryMount() != NULL )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_Alreadly );
                return false;
            }

            // 判断等级, 领取坐骑( 玩家等级取整 减去10级 )
            unsigned int nMountLevel = ( GetLevel() / 10 ) * 10 - 10;
            const CountryConfig::MountSetting* pSetting = theCountryConfig.GetMountSettingByLevel( nMountLevel );
            if ( nMountLevel == NULL )
            { 
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_NotHaveMount );
                return false;
            }

            unsigned short ustMountID = 0;
            switch ( uchPositon )
            {
            case CountryDefine::Position_King:
                ustMountID = pSetting->GetKingID();
                break;
            case CountryDefine::Position_Queen:
                ustMountID = pSetting->GetQueenID();
                break;
            default:
                return false;
            }

            n64MountGuid = AddMount( ustMountID );
            if ( n64MountGuid == InvalidLogicNumber )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_MaxCount );
                return false;
            }
        }
        break;
    case CountryDefine::MountType_Guard:
        {
            if ( m_pGuild == NULL )
            { 
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_NotRight );
                return false;
            }

            if ( m_pGuild->GetID() != m_pCountry->GetDragonGuild() && m_pGuild->GetID() != m_pCountry->GetRosefinchGuild() )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_NotRight );
                return false;
            }

            if ( !m_pGuild->IsMaster( GetDBCharacterID() ) )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_NotRight );
                return false;
            }

            if ( GetCountryMount() != NULL )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_Alreadly );
                return false;
            }

            // 判断等级, 领取坐骑( 玩家等级取整 减去10级 )
            unsigned int nMountLevel = ( GetLevel() / 10 ) * 10 - 10;
            const CountryConfig::MountSetting* pSetting = theCountryConfig.GetMountSettingByLevel( nMountLevel );
            if ( nMountLevel == NULL )
            { 
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_NotHaveMount );
                return false;
            }

            unsigned short ustMountID = 0;
            if ( m_pGuild->GetID() == m_pCountry->GetDragonGuild() )
            {
                ustMountID = pSetting->GetDragonID();
            }
            else
            {
                ustMountID = pSetting->GetRostfinchID();
            }

            n64MountGuid = AddMount( ustMountID );
            if ( n64MountGuid == InvalidLogicNumber )
            {
                SendOperateAckToClient< MsgCountryReceiveMountAck >( MsgCountryReceiveMountAck::ECD_MaxCount );
                return false;
            }
        }
        break;
    default:
        return false;
    }


    // 领取成功, 设置国家坐骑GUID
    m_nCountryMountGUID = n64MountGuid;
    SMountItem* pMount = _mountManager.GetMountByGuid( n64MountGuid );
    if ( pMount != NULL )   // 国家坐骑不能交易, 所以锁定之
    { pMount->SetLock( true ); }

    return true;
}

void GamePlayer::CheckCountryMount()
{
    m_nCountryMountGUID = InvalidLogicNumber;

    SMountItem* pMount = FindCountryMount();
    if ( pMount == NULL )
    { return; }

    pMount->SetLock( true );    // 每次检查都锁定
    if ( m_pGuild == NULL )
    {
        RemoveMountByGuid( pMount->GetMountGuid() );
        return;
    }

    // 不判断对应坐骑的具体ID和职位的关系
    uint8 uchPosition = m_pCountry->GetPosition( GetDBCharacterID() );

    m_nCountryMountGUID = pMount->GetMountGuid();

    // 如果是国王 或者是王后
    if ( uchPosition == CountryDefine::Position_King || uchPosition == CountryDefine::Position_Queen )
    { return; }

    // 如果是青龙帮主
    if ( m_pGuild->GetID() == m_pCountry->GetDragonGuild() && m_pGuild->IsMaster( GetDBCharacterID() ) )
    { return; }

    // 如果是朱雀帮主 
    if ( m_pGuild->GetID() == m_pCountry->GetRosefinchGuild() && m_pGuild->IsMaster( GetDBCharacterID() ) )
    { return; }
    
    // 都不是, 把马删掉
    m_nCountryMountGUID = InvalidLogicNumber;
    RemoveMountByGuid( pMount->GetMountGuid() );
}

// 国家召集
bool GamePlayer::CountryConenve()
{
    if ( !m_pCountry->IsHaveRight( CountryDefine::Right_Convene, GetDBCharacterID() ) )
    {
        SendOperateAckToClient< MsgCountryConveneResult >( MsgCountryConveneResult::ECD_NotRight );
        return false;
    }

    if ( m_pCountry->GetConveneCount() >= theCountryConfig.GetConveneCount() )
    {
        SendOperateAckToClient< MsgCountryConveneResult >( MsgCountryConveneResult::ECD_TimeLimit );
        return false;
    }

    if ( m_pCountry->GetMoney() < theCountryConfig.GetConveneCost() )
    {
        SendOperateAckToClient< MsgCountryConveneResult >( MsgCountryConveneResult::ECD_NotEnoughMoney );
        return false;
    }

    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL || pMapData->IsEctypeMap() )
    { 
        SendOperateAckToClient< MsgCountryConveneResult >( MsgCountryConveneResult::ECD_EctypeMap );
        return false;
    }

    // 同步CenterServer
    GS2CSCountryConveneReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.nOfficialID  = GetDBCharacterID();
    xReq.ustLevel     = max( theCountryConfig.GetMinConveneLevel(), pMapData->MinPlayerLevel );
    xReq.nMapID       = GetMapID();
    xReq.fX           = GetFloatX();
    xReq.fY           = GetFloatY();
    GettheServer().SendMsgToCenterServer( &xReq );

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////

// 查询国家信息
void GamePlayer::OnMsgQueryCountryInfoReq( Msg* pMsg )
{
    MsgQueryCountryInfoReq* pReq = static_cast< MsgQueryCountryInfoReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    MsgQueryCountryInfoAck xAck;

    HelperFunc::SafeNCpy( xAck.szName, m_pCountry->GetName(), sizeof( xAck.szName ) ); 
    HelperFunc::SafeNCpy( xAck.szNotice, m_pCountry->GetNotice(), sizeof( xAck.szNotice ) );
    for ( int i = 0; i < CountryDefine::Position_Max; ++i )
    {
        HelperFunc::SafeNCpy( xAck.szOfficial[i], m_pCountry->GetOfficial( i )->GetName(), sizeof( xAck.szOfficial[i] ) );
		xAck.szsexID[i] = m_pCountry->GetOfficial( i )->GetSexID();
		xAck.szfaceID[i] = m_pCountry->GetOfficial( i )->GetFaceID();
		xAck.szheaderID[i] = m_pCountry->GetOfficial( i )->GetHeaderID();
		xAck.szprofession[i] =  m_pCountry->GetOfficial( i )->GetProfessionID();
    }

    xAck.nMoney        = m_pCountry->GetMoney();
    xAck.nCountryRight = m_pCountry->GetRight( GetDBCharacterID() );
	xAck.nStrongth		= m_pCountry->GetNowStrength();
	xAck.nTribute		= m_pCountry->GetTribute();
    for( int i = CountryDefine::QuestType_None; i < CountryDefine::QuestType_Max; ++i )
    {
        OperateTime* pOperateTime = m_pCountry->GetQuestOperate( i );
        if ( pOperateTime == NULL )
        { continue; }

        const CountryConfig::QuestSetting* pSetting = theCountryConfig.GetQuestSetting( i );
        if ( pSetting == NULL )
        { continue; }

        xAck.xQuestStatus[ i ].uchCount = pOperateTime->GetCount();
        if ( pOperateTime->GetStartTime() != 0 )
        {
            TimeEx xStartTime( pOperateTime->GetStartTime() );
            TimeSpan xSpan = TimeEx::GetCurrentTime() - xStartTime;
            if ( xSpan.GetTotalSeconds() < pSetting->GetKeepTime() )
            {
                xAck.xQuestStatus[ i ].nLeftTime = pSetting->GetKeepTime() - xSpan.GetTotalSeconds();
            }
        }
    }
    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgCountryNoticeChangeReq( Msg* pMsg )
{
    MsgCountryNoticeChangeReq* pReq = static_cast< MsgCountryNoticeChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( !m_pCountry->IsHaveRight( CountryDefine::Right_Placard, GetDBCharacterID() ) )
    {
        return SendOperateAckToClient< MsgCountryNoticeChangeAck >( MsgCountryNoticeChangeAck::ECD_NotRight );
    }

    if ( m_pCountry->GetPlacardCount() >= theCountryConfig.GetPlacardCount() )
    {
        return SendOperateAckToClient< MsgCountryNoticeChangeAck >( MsgCountryNoticeChangeAck::ECD_TimeLimit );
    }

    if ( m_pCountry->GetMoney() < theCountryConfig.GetPlacardCost() )
    {
        return SendOperateAckToClient< MsgCountryNoticeChangeAck >( MsgCountryNoticeChangeAck::ECD_NotEnoughMoney );
    }

    HelperFunc::CheckStringValid( pReq->szNotice, sizeof( pReq->szNotice ) );

    // 请求通知CenterCountry
    GS2CSCountryNoticeChangeReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.nPlayerID    = GetDBCharacterID();
    HelperFunc::SafeNCpy( xReq.szNotice, pReq->szNotice, sizeof( xReq.szNotice ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::SendCountryQuestStatusChangeAckMessage( uint8 nQuestType, uint8 nResult )
{
    MsgCountryQuestStatusChangeAck xAck;    
    xAck.uchQuestType = nQuestType;
    xAck.uchResult    = nResult;
    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgCountryQuestStatusChangeReq( Msg* pMsg )
{
    MsgCountryQuestStatusChangeReq* pReq = static_cast< MsgCountryQuestStatusChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    unsigned int nRight = CountryDefine::GetQuestRightByType( pReq->uchQuestType );
    if ( nRight == CountryDefine::Right_None )
    { return; }

    if ( !m_pCountry->IsHaveRight( nRight, GetDBCharacterID() ) )
    {
        return SendCountryQuestStatusChangeAckMessage( pReq->uchQuestType, MsgCountryQuestStatusChangeAck::ECD_NotRight );
    }

    OperateTime* pOperateTime = m_pCountry->GetQuestOperate( pReq->uchQuestType );
    if ( pOperateTime == NULL )
    { return; }

    const CountryConfig::QuestSetting* pSetting = theCountryConfig.GetQuestSetting( pReq->uchQuestType );
    if ( pSetting == NULL )
    { return; }

    if ( pOperateTime->GetCount() >= pSetting->GetCount() )
    {
        return SendCountryQuestStatusChangeAckMessage( pReq->uchQuestType, MsgCountryQuestStatusChangeAck::ECD_Already );
    }

    if ( m_pCountry->GetMoney() < pSetting->GetCostMoney() )
    {
        return SendCountryQuestStatusChangeAckMessage( pReq->uchQuestType, MsgCountryQuestStatusChangeAck::ECD_NotEnoughMoney );
    }

    // 通知CenterServer
    GS2CSCountryQuestStatusChangeReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.uchQuestType = pReq->uchQuestType;
    xReq.nPlayerID    = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
	
	//发布特殊任务 我们设置国家的值
	m_pCountry->SetAddQuestCount(pReq->uchQuestType);

//lyh++  国家公告 只给自己的国家法（国家任务相关）
	MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	Msg.header.stID = GetID();
	Msg.SetString( theCountryConfig.GetQuestSetting(pReq->uchQuestType)->GetBoardcast() );
	GettheServer().SendMsgToCountry( &Msg , GetCountry(), true );  
}

void GamePlayer::SendCountryOfficialAppointAckMessage( uint8 nPosition, uint32 nPlayerID, uint8 nResult )
{
    MsgCountryOfficialAppointAck xAck;
    xAck.uchPosition = nPosition;
    xAck.nPlayerID   = nPlayerID;
    xAck.uchResult   = nResult;
    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgCountryOfficialAppointReq( Msg* pMsg )
{
    MsgCountryOfficialAppointReq* pReq = static_cast< MsgCountryOfficialAppointReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    unsigned int nRight = CountryDefine::GetAppointRightByPosition( pReq->uchPosition );
    if ( nRight == CountryDefine::Right_None )
    { return; }

	GameRelation* pTargetRelation = theGameRelationManager.GetPlayerRelation( pReq->szName );
	if ( pTargetRelation == NULL )
	{
		return SendErrorToClient( ER_NameNotExist );
	}
	if ( !pTargetRelation->GetOnLine() )
	{
		return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_NotOnline ); 
	}

    if ( !m_pCountry->IsHaveRight( nRight, GetDBCharacterID() ) )
    {
        return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_NotRight ); 
    }

    uint8 uchPositon = m_pCountry->GetPosition( pTargetRelation->GetID() );
    if ( uchPositon != CountryDefine::Position_None )
    { 
        return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_Already ); 
    }

	// 不是本国人
    if ( m_pCountry->GetID() != pTargetRelation->GetCountry() )
    {
		return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_NotCountryMember );
    }

    if ( pTargetRelation->GetLevel() < theCountryConfig.GetAppointMinLevel() )
    {
        return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_LevelLess ); 
    }

    // 判断是否同一个人
    OfficialInfo* pOfficial = m_pCountry->GetOfficial( pReq->uchPosition );
    if ( pOfficial == NULL )
    { return; }

    if ( pOfficial->GetID() == pTargetRelation->GetID() )
    {
        return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_Already ); 
    }

	/*if (pTargetRelation->GetGuildID() == 0)
	{
		return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_NOGuild ); 
	}*/

    /*SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_Success ); */

	//RemoveItem
	//zhuxincong 这是是消耗物品ID为100的item
	/*int nItem = 100;
	bool bItem = RemoveItem(nItem,1);
	if (!bItem)
	{
		return SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_NoItem ); 
	}*/

	// 通知CenterServer
    GS2CSCountryOfficialAppointReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.nOfficialID  = GetDBCharacterID();
    xReq.uchPosition  = pReq->uchPosition;
    xReq.nPlayerID    = pTargetRelation->GetID();
	GamePlayer * pTarget = theRunTimeData.GetGamePlayerByDBID(xReq.nPlayerID);
	if(pTarget)
	{
		xReq.sexID		  = pTarget->GetCharInfo().baseinfo.aptotic.ucSex;
		xReq.faceID		 = pTarget->GetCharInfo().visual.faceId;
		xReq.headerID	= pTarget->GetCharInfo().visual.hairId;
		xReq.professionID = pTarget->GetCharInfo().baseinfo.aptotic.usProfession;
	}
	else
	{
		xReq.sexID		  = -1;
		xReq.faceID		 =  -1;
		xReq.headerID	=  -1;
		xReq.professionID =  -1;
	}
    GettheServer().SendMsgToCenterServer( &xReq );
	//根据职位id 拷贝字符串
	char szPosition[32]={0};
	switch( pReq->uchPosition)
	{
	case CountryDefine::Position_General:
		strcpy(szPosition,theXmlString.GetString( eText_Country_Operate_Define2 )); //大都督
		break;
	case CountryDefine::Position_CouncilorLeft:
		strcpy(szPosition,theXmlString.GetString( eText_Country_Operate_Define1 )); //太师
		break;
	case CountryDefine::Position_CouncilorRight:
		strcpy(szPosition,theXmlString.GetString( eText_Country_Operate_Define3 )); //太尉
		break;;
	case CountryDefine::Position_CaptorLeft:
		strcpy(szPosition,theXmlString.GetString( eText_Country_Operate_Define4 )); //中郎将
		break;
	case CountryDefine::Position_CaptorRight:
		strcpy(szPosition,theXmlString.GetString( eText_Country_Operate_Define4 )); //中郎将
		break;
	}

	//lyh++ 国王任命官员的时候 添加系统提示。
	MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	Msg.header.stID = GetID();
	//××玩家功勋卓著，特被任命为××职位，希望再接再厉，壮大我国！
	char szChat[CHAT_STRINGMAX+1] = { 0 };
	sprintf(szChat,theXmlString.GetString( eText_Country_Operate_Appoint ),pReq->szName,szPosition);
	Msg.SetString( szChat );
	GettheServer().SendMsgToCountry( &Msg , GetCountry(), true );  

	//SendCountryOfficialAppointAckMessage( pReq->uchPosition, pTargetRelation->GetID(), MsgCountryOfficialAppointAck::ECD_Success ); 

	//zhuxincong 任命玩家为官员后给的奖励
	int nItemID = theCountryReward.GetItemID(pTargetRelation->GetLevel(),pReq->uchPosition);
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(nItemID);
	if (pItemCommon == NULL)
	{
		return;
	}

	//zhuxincong 这里是根据物品ID 创造物品
	SCharItem item;
	if( !theRunTimeData.CreateItem( NULL, nItemID, 1, HelperFunc::CreateID(), item ) )
	{
		return;
	}

	GS2CSCountryBattleReward xResult;
	memcpy(&xResult.CItem,&item,sizeof(SCharItem));
	xResult.nLevel = pTargetRelation->GetLevel();
	xResult.nPlayerID = pTargetRelation->GetID();
	xResult.nGuidID = pTargetRelation->GetGuildID();
	xResult.oldID = xResult.newID;
	xResult.newID = pTargetRelation->GetID();
	xResult.nPosition = pReq->uchPosition;
	HelperFunc::SafeNCpy(xResult.szName,GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( xResult.szName) );
	GettheServer().SendMsgToCenterServer( &xResult );
}

void GamePlayer::OnMsgCountryOfficialRecallReq( Msg* pMsg )
{
    MsgCountryOfficialRecallReq* pReq = static_cast< MsgCountryOfficialRecallReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    unsigned int nRight = CountryDefine::GetAppointRightByPosition( pReq->uchPosition );
    if ( nRight == CountryDefine::Right_None )
    { return; }

    MsgCountryOfficialRecallAck xAck;
    xAck.uchPosition = pReq->uchPosition;

    if ( !m_pCountry->IsHaveRight( nRight, GetDBCharacterID() ) )
    {
        xAck.uchResult = MsgCountryOfficialRecallAck::ECD_NotRight;
        SendMessageToClient( &xAck );
        return;
    }

	//获取这个官职以前的官员ID
	GameCountry * pCountry = theGameCountryManager.GetCountry(GetCountryId());
	if(!pCountry)
		return;
	OfficialInfo* pOff = pCountry->GetOfficial(pReq->uchPosition);
	if(!pOff || pOff->GetID() == 0) return;
	uint32 PlayerID = pOff->GetID();
    //SendMessageToClient( &xAck );

    // 通知CenterServer
	//zhuxincong 删除官员的物品
    //theCountryReward.BSubItemAndMount(pReq->uchPosition,GetDBCharacterID());
	theCountryReward.BSubItemAndMount(pReq->uchPosition,PlayerID);
	
    GS2CSCountryOfficialRecallReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.uchPosition  = pReq->uchPosition;
    xReq.nOfficialID  = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );



	OfficialInfo* pOfficial = m_pCountry->GetOfficial( pReq->uchPosition );
	if ( pOfficial == NULL || pOfficial->GetID() == 0)
	{ return; }

	//发送国家公告 免职
	MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	Msg.header.stID = GetID();
	////%s官员身体不适，辞去官职，告老还乡
	char szChat[CHAT_STRINGMAX+1] = { 0 };
	sprintf(szChat,theXmlString.GetString( eText_Country_Operate_Dismiss ),pOfficial->GetName());
	Msg.SetString( szChat );
	GettheServer().SendMsgToCountry( &Msg , GetCountry(), true );  

}

void GamePlayer::OnMsgCountryRequestRaiseReq( Msg* pMsg )
{
    MsgCountryRequestRaiseReq* pReq = static_cast< MsgCountryRequestRaiseReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( !m_pCountry->IsHaveRight( CountryDefine::Right_Raise, GetDBCharacterID() ) )
    {
        return SendOperateAckToClient< MsgCountryRequestRaiseAck >( MsgCountryRequestRaiseAck::ECD_NotRight );
    }

    if ( m_pCountry->GetRaiseCount() >= theCountryConfig.GetRaiseCount() )
    {
        return SendOperateAckToClient< MsgCountryRequestRaiseAck >( MsgCountryRequestRaiseAck::ECD_TimeLimit );
    }

    //通知CenterServer
    GS2CSCountryRequestRaiseReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.nPlayerID    = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgCountryRaiseToPlayerAck( Msg* pMsg )
{
    MsgCountryRaiseToPlayerAck* pAck = static_cast< MsgCountryRaiseToPlayerAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    MsgCountryRaiseTellPlayer xTell;
    //if ( GetLevel() < theCountryConfig.GetMinRaiseLevel() )    // 小于10级的不参与募捐
    //{ 
    //    return SendOperateAckToClient< MsgCountryRaiseTellPlayer >( MsgCountryRaiseTellPlayer::ECD_LevelLess );
    //}     

    if ( !m_pCountry->CheckRaiseTime() )
    {
        return SendOperateAckToClient< MsgCountryRaiseTellPlayer >( MsgCountryRaiseTellPlayer::ECD_NotRaiseTime );
    }
	
    /*uint32 nMaxMoney = theCountryConfig.GetMaxRaiseMoney( GetLevel() );
    if ( pAck->nMoney > nMaxMoney )
    { 
        return SendOperateAckToClient< MsgCountryRaiseTellPlayer >( MsgCountryRaiseTellPlayer::ECD_ErrorRaiseMoney );
    }*/

    if ( GetMoney() < pAck->nMoney )
    { 
        return SendOperateAckToClient< MsgCountryRaiseTellPlayer >( MsgCountryRaiseTellPlayer::ECD_NotEnoughMoney );
    }

    //unsigned int nCanAddMoney = theCountryConfig.GetMaxMoney() - m_pCountry->GetMoney();
    /*if ( pAck->nMoney > nCanAddMoney )
    { pAck->nMoney = nCanAddMoney; }*/

    if ( pAck->nMoney == 0 )
    {
        return SendOperateAckToClient< MsgCountryRaiseTellPlayer >( MsgCountryRaiseTellPlayer::ECD_CountryMoneyMax );
    }

    // 扣钱
    OperateMoney( EOT_Sub, pAck->nMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_CountryRaise);

	unsigned int ItemID = 0;
	unsigned int Exp = 0;

	theRaiseConfig.GetExpAndItemByCountryMoney(pAck->nMoney,Exp,ItemID);

    // 奖励经验
    //IncreaseExp( theCountryConfig.GetRaiseRewardExp() * pAck->nMoney, 0 );
	IncreaseExp( Exp, 0 );

	//发送邮件
	if(ItemID != 0)
	{
		SCharItem item;
		if( !theRunTimeData.CreateItem( NULL, ItemID, 1, HelperFunc::CreateID(), item ) )
			return;
		//发送命令道中央服务器 准备发送邮件个玩家
		GS2CSRaiseCountryPlayerItem msg;
		msg.PlayerID = GetDBCharacterID();
		msg.ItemID = ItemID;
		memcpy(&msg.CItem,&item,sizeof(SCharItem));
		HelperFunc::SafeNCpy(msg.szName,GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( msg.szName) );
		GettheServer().SendMsgToCenterServer( &msg );

		//全服公告 X国 XX为军团捐献大量资金，获得募捐大礼包
		MsgTellCountryPlayerRaiseItem msgItem;
		HelperFunc::SafeNCpy( msgItem.szName, GetCharName(), sizeof( msgItem.szName ) );
		msgItem.CountryID = GetCountry();
		GettheServer().SendMsgToWorld(&msgItem,true);
	}	

    // 达到广播数量, 全国广播下
    /*if ( pAck->nMoney >= theCountryConfig.GetRaiseBoradMoney() )
    {
        MsgTellCountryPlayerRaise xShow;
        HelperFunc::SafeNCpy( xShow.szName, GetCharName(), sizeof( xShow.szName ) );
        xShow.nMoney = pAck->nMoney;
        GettheServer().SendMsgToCountry( &xShow, GetCountry(), true );
    }*/

    // 通知给CenterServer
    GS2CSCountryMoneyRaiseed xRaiseed;
	xRaiseed.nType = 0;
    xRaiseed.uchCountryID = GetCountry();
    xRaiseed.nMoney       = pAck->nMoney;
    GettheServer().SendMsgToCenterServer( &xRaiseed );
}

void GamePlayer::OnMsgCountryFlyToBordersReq( Msg* pMsg )
{
    MsgCountryFlyToBordersReq* pReq = static_cast< MsgCountryFlyToBordersReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( !m_pCountry->IsHaveRight( CountryDefine::Right_FlyToBorders, GetDBCharacterID() ) )
    { return; }

    if ( !m_pCountry->CheckCanFlyToBorders( pReq->ustMapID, pReq->ustPosX, pReq->ustPosY ) )
    { return; }

    FlyToMapReq( pReq->ustMapID, pReq->ustPosX, pReq->ustPosY, 0.0f, false );
}

void GamePlayer::SendCountryOperateToPlayerAckMessage( uint8 nOperate, uint8 nResult )
{
    MsgCountryOperateToPlayerAck xAck;
    xAck.uchOperate = nOperate;
    xAck.uchResult  = nResult;
    SendMessageToClient( &xAck );
}

void GamePlayer::OnMsgCountryOperateToPlayerReq( Msg* pMsg )
{
    MsgCountryOperateToPlayerReq* pReq = static_cast< MsgCountryOperateToPlayerReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );
    if ( strcmp( pReq->szName, GetCharName() ) == 0 )
    { return; } // 不能对自己

    // 国王争夺战, 朱雀争夺战, 青龙争夺战期间不能使用该功能
    bool bInCampCountryBattle = false;
    for ( int i = CampDefine::BattleTypeKing; i <= CampDefine::BattleTypeRosefinch; ++i )
    {
        CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(i,GetCountryId());
        if ( pManager == NULL )
        { continue; }

        if ( pManager->GetBattleStatus() != CampDefine::StatusInit )
        {
            bInCampCountryBattle = true;
            break;
        }
    }

    int nCostMoney = 0;
    switch( pReq->uchOperate )
    {
    case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
        {        
            if ( !m_pCountry->IsHaveRight( CountryDefine::Right_BanSpeak, GetDBCharacterID() ) )
            {
               return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_NotRight );
            }

            if ( m_pCountry->GetBanSpeakCount() >= theCountryConfig.GetBanSpeakCount() )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_TimeLimit );
            }

            if ( bInCampCountryBattle )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_CountryBattle );
            }

            nCostMoney = theCountryConfig.GetBanSpeakCost();
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Chain:
        {
            if ( !m_pCountry->IsHaveRight( CountryDefine::Right_Chain, GetDBCharacterID() ) )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_NotRight );
            }

            if ( m_pCountry->GetChainCount() >= theCountryConfig.GetChainCount() )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_TimeLimit );
            }

            if ( bInCampCountryBattle )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_CountryBattle );
            }

            nCostMoney = theCountryConfig.GetChainCost();
        }
        break;
    case  MsgCountryOperateToPlayerReq::Operate_Remit:
        {
            if ( !m_pCountry->IsHaveRight( CountryDefine::Right_Remit, GetDBCharacterID() ) )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_NotRight );
            }

            if ( m_pCountry->GetRemitCount() >= theCountryConfig.GetRemitCount() )
            {
                return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_TimeLimit );
            }
            nCostMoney = theCountryConfig.GetRemitCost();
        }
        break;
    default:
        return;
    }
    
    if ( m_pCountry->GetMoney() < nCostMoney )
    {
        return SendCountryOperateToPlayerAckMessage( pReq->uchOperate, MsgCountryOperateToPlayerAck::ECD_NotEnoughMoney );
    }

    // 发送给CenterServer
    GS2CSCountryOperateToPlayerReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.uchOperate   = pReq->uchOperate;
    xReq.nPlayerID    = GetDBCharacterID();
    HelperFunc::SafeNCpy( xReq.szName, pReq->szName, sizeof( xReq.szName ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}

void GamePlayer::OnMsgCountryConveneAck( Msg* pMsg )
{
    MsgCountryConveneAck* pAck = static_cast< MsgCountryConveneAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    if ( GetLevel() < theCountryConfig.GetMinConveneLevel() )
    { return; }

    if ( !m_pCountry->CheckConveneStartTime() )
    { return; }

    const BordersFight& xPlace = m_pCountry->GetConvenePlace();

    FlyToMapReq( xPlace.GetMapID(), xPlace.GetPosX(), xPlace.GetPosY(), 0.f );
}

void GamePlayer::OnMsgCountryChangeReq( Msg* pMsg )
{
	MsgCountryChangeReq* pReq = static_cast< MsgCountryChangeReq* >( pMsg );
    if ( pReq == NULL )
    { return; }


	bool bIsRandJoin = false;
	//随机的值
	if (pReq->uchCountryID == RandCountry)
	{//todo:做国家随机，并赋值
		bIsRandJoin = true;
		pReq->uchCountryID = theRunTimeData.CalcRandCreateCountryID();
			//( ( rand() % CountryDefine::Country_DunHuang ) + 1);
	}

    if ( HaveTeam() )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong有队伍无法选择国家%d", MsgCountryChangeAck::ECD_HaveTeam);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveTeam );
    }
	

    // 一周之内只能改变一次国籍
    if ( !TimeEx::IsPassCurrentTime( GetTimeVar( ECT_ChangeCountryTime ) , theChangeCountryConfig.GetCD()/*7 * OneDaySecond*/ ) )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong一周只能改变一次%d",  MsgCountryChangeAck::ECD_TimeLimit);
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_TimeLimit );
        //return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_TimeLimit );
    }

    if ( m_pGuild != NULL )
    {
		 LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong有帮派%d",  MsgCountryChangeAck::ECD_HaveGuild);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveGuild );
    }

    if ( IsHaveTeacher() )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong有师傅%d",  MsgCountryChangeAck::ECD_HaveTeacher);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveTeacher );
    }


    if ( IsHaveMarriage() )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong结婚了%d",  MsgCountryChangeAck::ECD_HaveMarriage);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveMarriage );
    }
	

    if ( IsHaveStudent() )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong有徒弟%d",  MsgCountryChangeAck::ECD_HaveStudent);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveStudent );
    }
	
	if(gCharInfoServer.baseinfo.liveinfo.uchPosition != CountryDefine::Position_None)
	{
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong有官职%d",  MsgCountryChangeAck::ECD_HaveOff);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveOff );
	}

    if ( GetCountry () == pReq->uchCountryID )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong国家ID相同%d",  MsgCountryChangeAck::ECD_SameCountry);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_SameCountry );
    }
	
    if ( pReq->uchCountryID == CountryDefine::Country_Init || pReq->uchCountryID >= CountryDefine::Country_Max )
    {
		LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong错误国家ID%d",  MsgCountryChangeAck::ECD_ErrorCountry);
        return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_ErrorCountry );
    }
	

	//从国籍0到其他国籍是不需要付钱的
	if (GetCountry() != CountryDefine::Country_Init)
	{
		// 判断金钱
		//if ( GetMoney() < theCountryConfig.GetCountryChangeCostMoney() )
		//{
		//	LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong钱不够ID%d",  MsgCountryChangeAck::ECD_NotEnoughMoney);
		//	return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_NotEnoughMoney );
		//}


		//// 扣钱
		//OperateMoney( EOT_Sub, theCountryConfig.GetCountryChangeCostMoney(), true, __FUNCTION__, __LINE__ );
		//叛国处理
		//1.判断配置文件是否可以叛国 可以的话 删除掉指定物品
		//判断等级
		if((theChangeCountryConfig.GetMaxLevel() != -1 && theChangeCountryConfig.GetMaxLevel()<GetLevel()))
		{
			LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong配置文件 最高等级不符合ID%d",  MsgCountryChangeAck::ECD_MaxLevel);
			return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_MaxLevel );
		}
		if(theChangeCountryConfig.GetMinLevel() != -1 && theChangeCountryConfig.GetMinLevel() > GetLevel())
		{
			LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong配置文件 最低不符合ID%d",  MsgCountryChangeAck::ECD_MinLevel);
			return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_MinLevel );
		}
		int ItemID = theChangeCountryConfig.GetItemID(GetCountry(),pReq->uchCountryID,theGameCountryManager.GetWeakCountry(),theGameCountryManager.GetStrongCountry());
		int ItemNum = theChangeCountryConfig.GetItemSum(GetCountry(),pReq->uchCountryID,theGameCountryManager.GetWeakCountry(),theGameCountryManager.GetStrongCountry());
		if(ItemID != 0 && ItemNum != 0)
		{
			if(GetItemCount(ItemID) < ItemNum)
			{
				LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong配置文件 物品不符合ID%d",  MsgCountryChangeAck::ECD_Item);
				return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_Item );
			}
		}
		if(theChangeCountryConfig.GetQuestIndex() !=-1)
		{
			if(GetVar(theChangeCountryConfig.GetQuestIndex()) != theChangeCountryConfig.GetQuestValue())
			{
				LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong配置文件 任务不符合ID%d",  MsgCountryChangeAck::ECD_QuestStates);
				return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_QuestStates );
			}
		}
		if(ItemID != 0 && ItemNum != 0)
		{
			int64 _Guid = GetItemGUIDByItemID(ItemID);
			if(!RemoveItem(ItemID,ItemNum))
			{
			//不可以切换国家
			LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong物品不足ID%d",  MsgCountryChangeAck::ECD_Item);
			return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_Item );
			}else
			{
                ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(ItemID);
				SCharItem *_item = GetBagItemByGuid(_Guid);

				 if(_pitem)
                  theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),ItemID,ItemNum,_Guid,
				  _item?_item->GetItemCount():0,eItemLogInfo_ItemConsume_ChangeCountry,GetCharName(),_pitem->GetItemName());
			}
		}
	}

 //   // 判断金钱
 //   if ( GetMoney() < theCountryConfig.GetCountryChangeCostMoney() )
 //   {
 //       return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_NotEnoughMoney );
 //   }
	//else
	//{
	//	LOG_MESSAGE("Info.log",LOG_PRIORITY_INFO,"zhuxincong钱不够ID%d",  MsgCountryChangeAck::ECD_NotEnoughMoney);
	//}

 //   // 扣钱
 //   OperateMoney( EOT_Sub, theCountryConfig.GetCountryChangeCostMoney(), true, __FUNCTION__, __LINE__ );

    // 叛国成功
	GS2CSCountryPlayerChange msg;
	msg.nPlayerID = GetDBCharacterID();
	msg.oldCountryID = GetCountry();
	msg.nowCountryID = pReq->uchCountryID;

    GameCountry* pCountry = theGameCountryManager.GetCountry( pReq->uchCountryID );
    InitPlayerCountry( pCountry );
	if (bIsRandJoin)
	{
		//随机加入给奖励
		int rewardID = theCountryConfig.GetRandJoinReward().GetRewardID();
		ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID(rewardID);
		if(pItem)
		{
			SCharItem item;
			unsigned short nCount = 1;
			theRunTimeData.CreateItem( this, pItem->ustItemID, nCount, HelperFunc::CreateID(), item );
			AddItemToBag(item,nCount);
		}
	}

    SetTimeVar( ECT_ChangeCountryTime, TimeEx::GetNowTime() );

	//触发7天乐
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_FirstDay );

    // 通知附近玩家
    MsgCountryTellCountryID xTell;
	xTell.header.stID = GetID();
    xTell.uchCountry = pReq->uchCountryID;
    GettheServer().SendMsgToView( &xTell, GetID(), false );

    // 同步给CenterServer
    GS2CSCountryChangeResult xResult;
    xResult.nPlayerID    = GetDBCharacterID();
    xResult.uchCountryID = pReq->uchCountryID;
    GettheServer().SendMsgToCenterServer( &xResult );

	GettheServer().SendMsgToCenterServer( &msg );
}

void GamePlayer::OnMsgChangeCountryNameReq( Msg* pMsg )
{
    MsgChangeCountryNameReq* pReq = static_cast< MsgChangeCountryNameReq* >( pMsg );
    if ( pReq == NULL || pReq->szName[0] == 0 )
    { return; }

    HelperFunc::CheckStringValid( pReq->szName, sizeof( pReq->szName ) );

    if ( !m_pCountry->IsHaveRight( CountryDefine::Right_ChangeName, GetDBCharacterID() ) )
    {
        return SendOperateAckToClient< MsgChangeCountryNameAck >( MsgChangeCountryNameAck::ECD_NotHaveRight );
    }

    if ( m_pCountry->GetChangeName() )
    {
        return SendOperateAckToClient< MsgChangeCountryNameAck >( MsgChangeCountryNameAck::ECD_ChangeOnce );
    }

    if ( !theChatCheck->CheckStringInLow( pReq->szName ) )
    {
        return SendOperateAckToClient< MsgChangeCountryNameAck >( MsgChangeCountryNameAck::ECD_ErrorName );
    }

    // 通知CenterServer处理
    GS2CSChangeCountryNameReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.nPlayerID    = GetDBCharacterID();
    HelperFunc::SafeNCpy( xReq.szPlayer, GetCharName(), sizeof( xReq.szPlayer ) );
    HelperFunc::SafeNCpy( xReq.szName, pReq->szName, sizeof( xReq.szName ) );
    GettheServer().SendMsgToCenterServer( &xReq );
}


bool GamePlayer::IsCountryQueen()
{
    OfficialInfo* pOfficial = m_pCountry->GetOfficial( CountryDefine::Position_Queen );
    if ( pOfficial == NULL )
    { return false; }

    return pOfficial->GetID() == GetDBCharacterID();
}

void GamePlayer::AddCountryResource( uint8 uchType, uint32 nValue )
{
    switch( uchType )
    {
    case CountryDefine::Resource_Money:
        {
            GS2CSCountryMoneyRaiseed xRaiseed;
			xRaiseed.nType = 0;
            xRaiseed.uchCountryID = GetCountry();
            xRaiseed.nMoney       = nValue;
            GettheServer().SendMsgToCenterServer( &xRaiseed );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::SubCountryResource( uint8 uchType, uint32 nValue )
{
    switch( uchType )
    {
    case CountryDefine::Resource_Money:
        {
            GS2CSCountryMoneyRaiseed xRaiseed;
            xRaiseed.uchCountryID = GetCountry();
            xRaiseed.nMoney       = ( 0 - nValue );     // 相当于募捐负的钱
            GettheServer().SendMsgToCenterServer( &xRaiseed );
        }
        break;
    default:
        break;
    }
}

bool GamePlayer::IsCountryQuestOpen( uint8 uchType )
{
    OperateTime* pOperateTime = m_pCountry->GetQuestOperate( uchType );
    if ( pOperateTime == NULL )
    { return false; }

    return pOperateTime->GetStartTime() != 0;
}

bool GamePlayer::CheckCanCountrySpeak()
{
    if ( m_nCountrySpeakSpaceTime > 0 )
    { return false; }

    m_nCountrySpeakSpaceTime = theCountryConfig.GetCountrySpeakSpace();

    return true;
}

void GamePlayer::ProcessCountryBeKilledByPlayer( GamePlayer* pKiller, unsigned int nMapCountry  )
{
    if ( pKiller == NULL || GetCountry() == pKiller->GetCountry() )
    { return; }  // 同一国家的不处理逻辑

    uint8 uchPositon = m_pCountry->GetPosition( GetDBCharacterID() );
    if ( uchPositon != CountryDefine::Position_None )   // 自己是国家官员, 全服广播    
    {
        MsgTellCountryKillPosition xTell;
        xTell.uchKillerCountry = pKiller->GetCountry();
        HelperFunc::SafeNCpy( xTell.szKillerName, pKiller->GetCharName(), sizeof( xTell.szKillerName ) );
        xTell.uchBeKilledCountry  = GetCountry();
        xTell.uchBeKilledPosition = uchPositon;
        HelperFunc::SafeNCpy( xTell.szBeKilledName, GetCharName(), sizeof( xTell.szBeKilledName ) );
        GettheServer().SendMsgToWorld( &xTell, true );
    }

    // 如果是在本国地图被杀,
    if ( nMapCountry == GetCountry() )
    {
        m_pCountry->SendBordersFightMessage( EctypeId2MapId( GetMapID() ), static_cast< int >( GetFloatX() ), static_cast< int >( GetFloatY() ) );
    }
    else if ( nMapCountry == pKiller->GetCountry() )
    {
        // 公告 某某某抵御了敌国入侵犯
        MsgTellCountryKillEnemy xKill;
        xKill.ustMapID = EctypeId2MapId( GetMapID() );
        HelperFunc::SafeNCpy( xKill.szPlayerName, pKiller->GetCharName(), sizeof( xKill.szPlayerName ) );
        GettheServer().SendMsgToCountry( &xKill, pKiller->GetCountry(), true );
    }

    pKiller->ProcessKillUpdateCountryScore( this );
}

void GamePlayer::ProcessKillUpdateCountryScore( GamePlayer* pBeKiller )
{
    if ( GetCountry() == pBeKiller->GetCountry() )
    { return; }

    if ( !theGameCountryManager.CheckInCountryWarFight() )
    { return; }

    // 更新国战杀人记数
    theGameCountryManager.SendWarFightKillPlayerMessage( GetCountry(), pBeKiller->GetCountry() );

    // 更新国战积分
    const CountryConfig::WarFightSetting& xSetting = theCountryConfig.GetWarFightSetting();
    if ( GetLevel() - pBeKiller->GetLevel() > xSetting.GetLevelLimit() )
    { return; }     // 杀低于自己10级以上的玩家不获得国战积分

    // 判断最大值

    // 获得国战积分
    OperateTeamCountryScore( EOT_Add, xSetting.GetCountryScore() );
}

int GamePlayer::GetWarSortIndex()
{
    return m_pCountry->GetSortIndex();
}

bool GamePlayer::SetCountryKing()
{
	GameGuild* pGuild = GetGuild();
	if (!pGuild||!m_pCountry||m_pCountry->IsHaveKing())
	{
		return false;
	}
	else
	{
		GS2CSCountryBattleResult xResult;
		xResult.uchCountryID  = GetCountry();
		xResult.uchBattleType = CountryDefine::Battle_King;
		xResult.nGuildID      = pGuild->GetID();
		xResult.uchWinType    = CountryDefine::BattleWin_FistTime;
		GettheServer().SendMsgToCenterServer( &xResult );

		//发送命令通知Center 添加新国王
		GS2CSAddCountryOfficial msg;
		msg.uchCountryID = GetCountry();
		msg.nPlayerID = pGuild->GetMasterID();
		msg.position = CountryDefine::Position_King;
		GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( msg.nPlayerID );
		if(pPlayer)
		{
			HelperFunc::SafeNCpy( msg.szName, pPlayer->GetCharName(), sizeof( msg.szName ) );
			msg.sexID = pPlayer->GetCharInfo().baseinfo.aptotic.ucSex;
			msg.faceID = pPlayer->GetCharInfo().visual.faceId;
			msg.headerID = pPlayer->GetCharInfo().visual.hairId;
			msg.professionID = pPlayer->GetCharInfo().baseinfo.aptotic.usProfession;
			GettheServer().SendMsgToCenterServer( &msg );
		}
		return true;
	}
}


bool GamePlayer::IsPlayerKing()
{
	int nPosition = m_pCountry->GetPosition( GetDBCharacterID() );
	if (nPosition != CountryDefine::Position_King)
	{
		return false;
	}
	return true;

}


//zhuxincong 9.18 设置贡品+ -
void GamePlayer::SetCountryTribute(int nValue,int countryid,int operType)
{
	if (countryid <= CountryDefine::Country_Init)
	{
		return;
	}
	GS2CSCountryMoneyRaiseed xRaiseed;
	switch(operType)
	{
		case EOT_Add:
			xRaiseed.uchCountryID = countryid;
			xRaiseed.nType		  = 1;
			xRaiseed.nMoney       = nValue ;
			break;
		case EOT_Sub:
			xRaiseed.uchCountryID = countryid;
			xRaiseed.nMoney       = (0 - nValue) ;     // 相当曾记负数的贡品
			xRaiseed.nType		  = 1;			
			break;
		case EOT_Set:
			xRaiseed.uchCountryID = countryid;
			xRaiseed.nMoney       = nValue;
			xRaiseed.nType		  = 1;
			xRaiseed.OperateType  = 3;			
			break;
	}
	GettheServer().SendMsgToCenterServer( &xRaiseed );
}

int GamePlayer::GetCountryTribute(int countryid)
{
	if (countryid <= CountryDefine::Country_Init)
	{
		return -1;
	}

	GameCountry* pCountry = theGameCountryManager.GetCountry( countryid);
	if ( pCountry == NULL )
	{
		return -1;
	}

	return pCountry->GetTribute();
}
void GamePlayer::OnMsgCountryQuestFlyReq( Msg* pMsg )
{
	MsgCountryFlyMapReq * pFly = (MsgCountryFlyMapReq *)pMsg;
	if(IsOpenStall())
	{
		return;
	}
	if ( HaveProtectChar() )
	{
		TellClient( theXmlString.GetString(eText_YaBiao_Flytomap) );
		return;
	}
	uint8 QuestType = pFly->uchType;
	unsigned int MapID = 0;
	float x=0,y=0,z=0;
	//获取任务开始时间
	GameCountry * pCountry = theGameCountryManager.GetCountry(GetCountryId());
	if(!pCountry)
		return;
	time_t nowtime;
	time(&nowtime);
	double SpanTime = difftime(nowtime,pCountry->GetQuestOperate(QuestType)->GetStartTime());
	if(SpanTime >= 120)
	{
		TellClient( theXmlString.GetString(eClient_AddInfo_EndTimeCountryTime) );
	}
	else
	{
		theCountryQuestFlyMapConfig.GetQuetMapInfo(GetCountryId(),QuestType,MapID,x,y,z);
		if(MapID == 0)
			return;
		FlyToMapReq(MapID,x,y,z);//移动到指定位置
	}
}
void GamePlayer::OnMsgDelCountryOfficialReq( Msg* pMsg )
{
	MsgDelCountryOfficialReq * pOff = static_cast<MsgDelCountryOfficialReq*>(pMsg);
	if(!pOff) return;
	//辞去自己的官职
	GameCountry* pCountry = theGameCountryManager.GetCountry(GetCountryId());
	if(!pCountry) return;//不存在国家
	//获取玩家的官职
	unsigned char uchPositon = pCountry->GetPosition(GetDBCharacterID());
	if(uchPositon == CountryDefine::Position_None || uchPositon == CountryDefine::Position_King || uchPositon == CountryDefine::Position_Queen)
		return;//无官职 国王  王后 无法辞职
	//正式辞去官员 默认为国王处理
	theCountryReward.BSubItemAndMount(uchPositon,GetDBCharacterID());//移除奖励

	//发送到中央服务器 辞职
	GS2CSDelCountryOfficialReq msg;
	msg.uchPosition = uchPositon;
	msg.uchCountryID = GetCountryId();
	GettheServer().SendMsgToCenterServer( &msg );

	OfficialInfo* pOfficial = pCountry->GetOfficial(uchPositon);
	
    /*GS2CSCountryOfficialRecallReq xReq;
    xReq.uchCountryID = GetCountry();
    xReq.uchPosition  = uchPositon;
    xReq.nOfficialID  = GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &xReq );*/

	//发送国家公告 免职
	MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	Msg.header.stID = GetID();
	////%s官员身体不适，辞去官职，告老还乡
	char szChat[CHAT_STRINGMAX+1] = { 0 };
	sprintf(szChat,theXmlString.GetString( eText_Country_Operate_Dismiss ),pOfficial->GetName());
	Msg.SetString( szChat );
	GettheServer().SendMsgToCountry( &Msg , GetCountry(), true );  
}
void GamePlayer::OnMsgLoadCountryInfoReq( Msg* pMsg )
{
	//加载国家信息
	GameCountry* pCountry = theGameCountryManager.GetCountry(GetCountryId());
	if(!pCountry) return;//不存在国家
	MsgLoadCountryInfoAck msg;
	for(int j =0;j<CountryDefine::MaxCountryInfoSum;++j)
	{
		strcpy_s(msg.Info[j%CountryDefine::MaxMsgCountryInfoSum],CountryDefine::MaxCountryInfoLength-1,pCountry->GetCountryInfo(j));
		msg.Time[j%CountryDefine::MaxMsgCountryInfoSum] = pCountry->GetCountryInfoTime(j);
		msg.values[j%CountryDefine::MaxMsgCountryInfoSum] = pCountry->GetCountryInfoValue(j);
		++msg.Sum;
		if(msg.Sum == CountryDefine::MaxMsgCountryInfoSum)
		{
			msg.IsEnd = false;
			SendMessageToClient( &msg );
			memset( msg.Info, 0, sizeof( msg.Info ) );
			memset( msg.Time, 0, sizeof( msg.Time ) );
			memset( msg.values, 0, sizeof( msg.values ) );
			msg.Sum = 0;
			msg.IsEnd = false;
		}
	}
	if(msg.Sum != 0)
	{
		msg.IsEnd = true;
		SendMessageToClient( &msg );
	}
}
void GamePlayer::OnMsgCountryBuffChangeAck( Msg* pMsg )
{
	//玩家发送国家改变的消息
	HandlePlayerCountryBuff();
}