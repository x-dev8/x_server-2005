#include "LuckRewardManager.h"
#include "TeamManager.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "XmlStringLanguage.h"

// 只有这3中情况能领取奖品
bool LuckReward::IsCanGetReward()
{
    switch( GetRewardType() )
    {
    case ECD_RandType_Init:
        {
            return !m_bIsLucking;       // 客户端不在转盘
        }
        break;
    case ECD_RandType_Double:
    case ECD_RandType_Half:
        {
            return true;
        }
        break;
    }
    return false;
}

// 判断能否到下一关
bool LuckReward::IsCanNextLuckLevel()
{
    switch( GetRewardType() )
    {
    case ECD_RandType_Front:
    case ECD_RandType_Next:
    case ECD_RandType_Jump:
        {
            return true;
        }
        break;
    }
    return false;
}

bool LuckReward::IsCanAcceptQuest( unsigned char uchLevel )
{
    if ( GetLevel() != uchLevel )
    { return false; }       // 不是本关不能刷怪

    switch ( GetRewardType() )      // 这3种情况都不可以刷出怪物
    {
    case ECD_RandType_Leave:
    case ECD_RandType_Half:
    case ECD_RandType_Double:
        {
            return false;
        }
        break;
    case ECD_RandType_Init:
        {
            return !m_bCanLuck;
        }
        break;
    default:
        break;
    }

    return true;
}

bool LuckReward::IsCanLuckReward()
{
    return ( GetRewardType() == ECD_RandType_Init );
}

void LuckReward::CopyReward( MsgTellLuckReward& xReward )
{
    for ( RewardVecIter iter = m_vecReward.begin(); iter != m_vecReward.end(); ++iter )
    {
        xReward.AddRewardIndex( *iter );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
GameTeam* TeamLuckRewardManager::GetLuckUnit( unsigned int dwID )
{
    return theGameTeamManager.GetTeam( dwID );
}

template<>
void TeamLuckRewardManager::SendRewardMessage( LuckReward* pLuckReward, Msg* pMessage )
{
    if ( pLuckReward == NULL || pMessage == NULL )
    { return; }

    GameTeam* pTeam = GetLuckUnit( pLuckReward->GetID() );
    if ( pTeam == NULL )
    { return; }

    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetMemberIDByIndex( i ) );
        if ( pPlayer == NULL )
        { continue; }
        if ( pPlayer->IsInMapArea( pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), TEAM_EXP_DIS ) )
        {
            GettheServer().SendMsgToSingle( pMessage, pPlayer );        // 有效范围内才发送
        }
    }
}

template<>       // 队伍模式
bool TeamLuckRewardManager::CheckValid( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return false; }

    GameTeam* pTeam = GetLuckUnit( pLuckReward->GetID() );
    if ( pTeam == NULL )
    { return false; }

    // 如果队员都不在这个地图了
    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetMemberIDByIndex( i ) );
        if ( pPlayer == NULL )
        { continue; }

        if ( pLuckReward->GetMapID() == InvalidLogicNumber || pPlayer->GetMapID() == pLuckReward->GetMapID() )
        { return true; }
    }
    return false;
}

template<>  // 队伍模式
void TeamLuckRewardManager::ReceiveLuckReward( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return; }

    GameTeam* pTeam = GetLuckUnit( pLuckReward->GetID() );
    if ( pTeam == NULL )
    { return ; }

    // 掉落物品 队伍掉落要除以队伍数量
    DropItemVector mapDropItem;          // 平均分配奖励的物品
    DropItemVector mapRollItem;          // 需要roll的物品
    int nRewardMoney = 0;                   // 奖励的钱
    int nRewardExp   = 0;                   // 奖励的经验

    if ( pLuckReward->IsCanGetReward() )            // 只有能获得奖品
    {
        LogLuckReward( pLuckReward, pTeam );        // 记录日志

        unsigned int nTeamCount = pTeam->GetTeamMemberCountInMap( pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY() );
        LuckReward::RewardVec& vecReward = pLuckReward->GetReward();
        for ( LuckReward::RewardVecIter iter = vecReward.begin(); iter != vecReward.end(); ++iter )
        {
            const RewardData* pRewardData = theLuckRewardConfig.GetReward( pLuckReward->GetLevel(), *iter );
            if ( pRewardData == NULL )
            { continue; }

            int nValue = pRewardData->GetValue();
            if ( pLuckReward->GetRewardType() == ECD_RandType_Half )        // 奖励一半
            {
                if ( nValue > 1 )
                    nValue /= 2; 
            }
            else if ( pLuckReward->GetRewardType() == ECD_RandType_Double ) // 奖励双倍
            {
                nValue *= 2;
            }

            switch( pRewardData->GetType() )        // 目前 经验 和钱 都做成一个券 兑换
            {
            case ECD_Reward_Item:
                {
                    if ( nValue < nTeamCount )
                    {
                        DropBaseItem::AddDropItemInPackage( mapRollItem, pRewardData->GetItemID(), nValue );
                    }
                    else
                    {
                        int nCount = nValue / nTeamCount;
                        DropBaseItem::AddDropItemInPackage( mapDropItem, pRewardData->GetItemID(), nCount );
                        if ( !pRewardData->GetRealLife() && ( nCount * nTeamCount ) < nValue )     // 不是实物多出来的roll点 
                        {
                            DropBaseItem::AddDropItemInPackage( mapRollItem, pRewardData->GetItemID(), nValue - ( nCount * nTeamCount ) );
                        }
                    }
                }
                break;
            case ECD_Reward_Money:
                {
                    nRewardMoney += ( nValue * 10000 / nTeamCount );            // 配置档里填的是金 这里换算一下
                }
                break;
            case ECD_Reward_Exp:
                {
                    nRewardExp += ( nValue / nTeamCount );
                }
                break;
            default:
                break;
            }
        }

        if ( !mapRollItem.empty() )     // 如果有要roll的物品
        {
            unsigned char chAssignMode = pTeam->GetTeamAssignModeType();
            unsigned char chAssignItemLevel = pTeam->GetTeamAssignItemLevel();

            pTeam->SetTeamAssignModeType( AssignMode_Team );            // 改成队伍分配
            pTeam->SetTeamAssignItemLevel( eIL_Choiceness );       // 改成良品

            DropCharItemVector vecCharItem;          // 这个归队伍所有
            DropBaseItem::DropItemPackage( mapRollItem, vecCharItem, pTeam->GetID(), pTeam->GetTeamHeaderID(), pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), LogDefine::ECD_DropType_Luck );

            // 恢复队伍分配情况
            pTeam->SetTeamAssignModeType( chAssignMode );
            pTeam->SetTeamAssignItemLevel( chAssignItemLevel );
        }
    }

    // 设置要离开
    uint32 dwMapID = Safe_Map_Id;
    float fX       = Safe_Map_PosX;
    float fY       = Safe_Map_PosY;
    float fDir     = Safe_Map_Dir;
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pLuckReward->GetMapID() ) );
    if ( pMapData != NULL )
    { 
        MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
        if ( pRelive != NULL )
        { 
            dwMapID = pRelive->MapId;
            fX      = pRelive->PositionX;
            fY      = pRelive->PositionY;
            fDir    = pRelive->Direction;
        }
    }

    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        unsigned int dwPlayerID = pTeam->GetMemberIDByIndex( i );
        GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
        if ( pTeamPlayer == NULL )
        { continue;  }

        if ( pTeamPlayer->GetMapID() == pLuckReward->GetMapID() )           // 在地图内的都要离开本地图
        {
            pTeamPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, dwMapID, fX, fY, fDir, 180, true );
        }

        if ( !pTeamPlayer->IsInMapArea( pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), TEAM_EXP_DIS ) )
        { continue; }           // 不在范围内的不给奖励

        if ( !mapDropItem.empty() )     // 只能他所有 队伍ID传入0
        {
            DropCharItemVector vecCharItem;
            DropBaseItem::DropItemPackage( mapDropItem, vecCharItem, TeamDefine::NoneSessionID, pTeamPlayer->GetDBCharacterID(), pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), LogDefine::ECD_DropType_Luck );
        }

        if ( nRewardMoney != 0 )
        {
            pTeamPlayer->OperateMoney( EOT_Add, nRewardMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Luck );        // 奖励金钱
        }

        if ( nRewardExp != 0 )
        {
            pTeamPlayer->Script_SetExp( nRewardExp, SKW_SETADD, __FUNCTION__, __LINE__ );                   // 奖励经验
        }
    }
}

template<>
void TeamLuckRewardManager::LogLuckReward( LuckReward* pLuckReward, GameTeam* pTeam )
{
    if ( pLuckReward == NULL || pTeam == NULL )
    { return; }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetTeamHeaderID() );
    if ( pPlayer == NULL )  
    { return; }

    //LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, theXmlString.GetString( eLog_TeamLuckReward ), pTeamHeader->GetName(), pLuckReward->GetLevel(), FormatLogString( pLuckReward ) );
    pPlayer->Log( theXmlString.GetString( eLog_TeamLuckReward ), pPlayer->GetCharName(), pLuckReward->GetLevel(), FormatLogString( pLuckReward ) );

    if ( pLuckReward->IsCanGetReward() && pLuckReward->GetLevel() > 5 )
    {
        char szBroadcast[256] = {0};
        sprintf_s( szBroadcast, sizeof( szBroadcast ) - 1, theXmlString.GetString( eTellClient_LuckReward ), pPlayer->GetCharName(), pLuckReward->GetLevel() );
        pPlayer->ProcessSystem( szBroadcast, GamePlayer::SystemWorld );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
GamePlayer* CharLuckRewardManager::GetLuckUnit( unsigned int dwID )
{
    return theRunTimeData.GetGamePlayerByDBID( dwID );
}

template<>
void CharLuckRewardManager::SendRewardMessage( LuckReward* pLuckReward, Msg* pMessage )
{
    if ( pLuckReward == NULL || pMessage == NULL )
    { return; }

    GamePlayer* pPlayer = GetLuckUnit( pLuckReward->GetID() );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->SendMessageToClient( pMessage );
}

template<>      // 个人模式
bool CharLuckRewardManager::CheckValid( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return false; }

    GamePlayer* pPlayer = GetLuckUnit( pLuckReward->GetID() );
    if ( pPlayer == NULL )
    { return false; }

    return ( pLuckReward->GetMapID() == InvalidLogicNumber || pPlayer->GetMapID() == pLuckReward->GetMapID() );
}

template<>  // 个人模式
void CharLuckRewardManager::ReceiveLuckReward( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return; }

    GamePlayer* pPlayer = GetLuckUnit( pLuckReward->GetID() );
    if ( pPlayer == NULL )
    { return; }

    if ( pLuckReward->IsCanGetReward() )
    {
        LogLuckReward( pLuckReward, pPlayer );  // 记录日志

        // 掉落物品
        DropItemVector mapDropItem;
        LuckReward::RewardVec& vecReward = pLuckReward->GetReward();
        for ( LuckReward::RewardVecIter iter = vecReward.begin(); iter != vecReward.end(); ++iter )
        {
            const RewardData* pRewardData = theLuckRewardConfig.GetReward( pLuckReward->GetLevel(), *iter );
            if ( pRewardData == NULL )
            { continue; }

            int nValue = pRewardData->GetValue();
            if ( pLuckReward->GetRewardType() == ECD_RandType_Half )        // 奖励一半
            {
                nValue /= 2; 
            }
            else if ( pLuckReward->GetRewardType() == ECD_RandType_Double ) // 奖励双倍
            {
                nValue *= 2;
            }

            switch( pRewardData->GetType() )        // 目前 经验 和钱 都做成一个券 兑换
            {
            case ECD_Reward_Item:
                {
                    DropBaseItem::AddDropItemInPackage( mapDropItem, pRewardData->GetItemID(), nValue );
                }
                break;
            case ECD_Reward_Money:
                {
                    pPlayer->OperateMoney( EOT_Add, nValue * 10000, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Luck);      // 配置档里填的是金 这里换算一下
                }
                break;
            case ECD_Reward_Exp:
                {
                    pPlayer->Script_SetExp( nValue, SKW_SETADD, __FUNCTION__, __LINE__ );
                }
                break;
            default:
                break;
            }
        }

        if ( !mapDropItem.empty() )     // 掉落物品 只能他所有 队伍ID传入0
        {
            DropCharItemVector vecCharItem;
            DropBaseItem::DropItemPackage( mapDropItem, vecCharItem, TeamDefine::NoneSessionID, pPlayer->GetDBCharacterID(), pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), LogDefine::ECD_DropType_Luck );
        }
    }

    // 设置离开这个地图
    uint32 dwMapID = Safe_Map_Id;
    float fX       = Safe_Map_PosX;
    float fY       = Safe_Map_PosY;
    float fDir     = Safe_Map_Dir;
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pLuckReward->GetMapID() ) );
    if ( pMapData != NULL )
    { 
        MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
        if ( pRelive != NULL )
        { 
            dwMapID = pRelive->MapId;
            fX      = pRelive->PositionX;
            fY      = pRelive->PositionY;
            fDir    = pRelive->Direction;
        }
    }

    pPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, dwMapID, fX, fY, fDir, 120, true );
}

template<>
void CharLuckRewardManager::LogLuckReward( LuckReward* pLuckReward, GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }

    pPlayer->Log( theXmlString.GetString( eLog_CharLuckReward ), pPlayer->GetCharName(), pLuckReward->GetLevel(), FormatLogString( pLuckReward ) );
}
