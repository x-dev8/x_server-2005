#include "BattleManager.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "MapConfig.h"
#include "MessageDefine.h"
#include "GameWorld.h"
#include "GlobalFunction.h"
#include "ScriptMgr.h"
#include "TeamManager.h"

template<>
GamePlayer* PlayerBattleData::GetUnit( unsigned int nID )
{
    return theRunTimeData.GetGamePlayerByDBID( nID );
}

template<>
void PlayerBattleData::CheckSignUpValid()
{
    bool bSendCountToClient = false;
    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); )
    {
        GamePlayer* pPlayer = GetUnit( *iter );
        if ( pPlayer == NULL || GetWaitMapID() != EctypeId2MapId( pPlayer->GetMapID() )  )
        {
            iter = setUnit.erase( iter );
            bSendCountToClient = true;
        }
        else
        {
            ++iter;
        }
    }

    if ( bSendCountToClient )
    {
        SendUnitCountMessage();
    }
}

template<>
unsigned short PlayerBattleData::GetUnitLevel( unsigned int nID )
{
    if ( nID == BattleDefine::NoneUnitID )
    { return 0; }

    UnitSetIter iter = setUnit.find( nID );
    if ( iter == setUnit.end() )
    { return 0; }

    GamePlayer* pPlayer = GetUnit( nID );
    if ( pPlayer == NULL )
    { return 0; }

    return pPlayer->GetLevel();
}

template<>
void PlayerBattleData::StartEnterFightMap( unsigned int nCurrentTime )
{
    SetStatus( BattleDefine::Status_EndEnter );

    MapConfig::MapData* pFightMapData = theMapConfig.GetMapDataById( GetFightMapID() );
    if ( pFightMapData == NULL )
    { return; }
 
    MapConfig::TransportDestination* pFirstTransport  = pFightMapData->GetTransportDestinationByIndex( 0 );
    MapConfig::TransportDestination* pSecondTransport = pFightMapData->GetTransportDestinationByIndex( 1 );
    if ( pFirstTransport == NULL || pSecondTransport == NULL )
    { return; }

    // 1v1战场, 随即匹配两个进入战场PK
    while( true )
    {
        if ( setUnit.empty() )
        { break; }

        UnitSetIter iter = setUnit.begin();
        GamePlayer* pFirstPlayer = GetUnit( *iter );
        if ( pFirstPlayer == NULL )      // 第一个玩家
        {
            setUnit.erase( iter );
            continue;
        }

        int nSize = GetUnitCount();
        if ( nSize == 1 )
        { break; }  // 最后只剩他一个人

        // 还有其他人
        setUnit.erase( iter );      // 删掉它
        GamePlayer* pSecondPlayer = NULL;
        while ( true )
        {
            nSize = GetUnitCount();
            if ( nSize == 0 )
            { break; }  // 已经没有匹配的玩家了

            int nIndex = rand() % nSize;
            iter = setUnit.begin();
            advance( iter, nIndex );

            pSecondPlayer = GetUnit( *iter );
            setUnit.erase( iter ); 

            if ( pSecondPlayer != NULL )
            { break; }  // 找到匹配的玩家
        }

        if ( pSecondPlayer == NULL )
        {
            // 没有匹配的玩家
            setUnit.insert( pFirstPlayer->GetDBCharacterID() );
            break;
        }

        // 找到以后, 创建场景, 准备飞入地图
        unsigned long dwMapID = theGameWorld.GetEctypeMapID( GetFightMapID(), true );
        theGameWorld.MultiCreateStage( GetFightMapID(), dwMapID );
        
        // 第1个玩家
        pFirstPlayer->SetWaitChangeStage( GamePlayer::EnterStage, dwMapID, pFirstTransport->PositionX, pFirstTransport->PositionY, pFirstTransport->Direction, 60, false );

        // 记录进入次数
        SaveSignUpInfo( pFirstPlayer );

        // 第2个玩家
        pSecondPlayer->SetWaitChangeStage( GamePlayer::EnterStage, dwMapID, pSecondTransport->PositionX, pSecondTransport->PositionY, pSecondTransport->Direction, 60, false );

        // 记录进入次数
        SaveSignUpInfo( pSecondPlayer );
    }

    SendUnitCountMessage();
}

template<>
void PlayerBattleData::EndFight( unsigned int nCurrentTime )
{
    // 如果是重复报名战场, 继续下一轮
    if ( GetRepeatTurns() > 0 )
    {
        SetSignUpInfo( nCurrentTime );
    }
    else
    {
        SetStatus( BattleDefine::Status_Close );
    }
}

template<>
void PlayerBattleData::SendUnitCountMessage()
{
    MsgTellBattleSignUpCount xTell;
    
    xTell.uchType  = BattleDefine::PlayerType;
    xTell.ustMapID = GetWaitMapID();
    xTell.ustCount = GetUnitCount();
    if ( GetStatus() == BattleDefine::Status_SignUp )       // 报名阶段把剩余时间发给客户端
    {
        xTell.nStartLeftTime = GameTime::GetLeftKeepTime( HQ_TimeGetTime(), GetStartSignUpTime(), GetSignUpTime() ) / 1000;
    }

    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    {
        GamePlayer* pPlayer = GetUnit( *iter );
        if ( pPlayer == NULL )
        { continue; }

        GettheServer().SendMsgToSingle( &xTell, pPlayer );
    }
}

template<>
bool PlayerBattleData::CheckCanSignUp( unsigned int nID )
{
    GamePlayer* pPlayer = GetUnit( nID );
    if ( pPlayer == NULL )
    { return false; }

    // 其他条件

    return true;
}

template<>
void PlayerBattleData::SaveSignUpInfo( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }
    
    GetScriptMgr()->StartupVM( ST_CHALLENGE, 0, pPlayer );      // 调用脚本, 由脚本负责该做些什么
}

template<>
void PlayerBattleData::EnterWaitMap( unsigned int nID )
{
    GamePlayer* pPlayer = GetUnit( nID );
    if ( pPlayer == NULL )
    { return; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetWaitMapID() );
    if ( pMapData == NULL )
    { return; }

    // 说明一下, 因为并不知道坐标信息, 在这个地图又不会死亡, 所以让策划填第0个重生点为这个地图的传送点
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( true );
    if ( pRelive == NULL )
    { return; }

    pPlayer->FlyToMapReq( GetWaitMapID(),  pRelive->PositionX, pRelive->PositionY, pRelive->Direction );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
GameTeam* TeamBattleData::GetUnit( unsigned int nID )
{
    return theGameTeamManager.GetTeam( nID );
}

template<>
bool TeamBattleData::CheckCanSignUp( unsigned int nID )
{
    //GameTeam* pTeam = GetUnit( nID );
    //if ( pTeam == NULL )
    //{ return false; }

    // 其他条件

    return true;
}

template<>
void TeamBattleData::CheckSignUpValid()
{
    bool bSendCountToClient = false;
    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); )
    {
        GameTeam* pTeam = GetUnit( *iter );
        if ( pTeam == NULL )
        {
            iter = setUnit.erase( iter );
            bSendCountToClient = true;
        }
        else
        {
            // 判断是否都在本服务器, 都不在了, 删除报名
            bool bNeedDelete = true;
            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                if ( pMember == NULL )
                { continue; }

                GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
                if ( pPlayer == NULL )
                { continue; }       

                bNeedDelete = false;
                break;
            }

            if ( bNeedDelete )
            {
                iter = setUnit.erase( iter );
                bSendCountToClient = true;
            }
            else
            {
                ++iter;
            }
        }
    }

    if ( bSendCountToClient )
    {
        SendUnitCountMessage();
    }
}

template<>
void TeamBattleData::SendWaitNextBattleMessage()
{
    if ( setUnit.empty() )
    { return; }

    MsgAckResult xAck;
    xAck.result = ER_WaitNextTeamBattle;
    xAck.value  = 3;

    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    {
        GameTeam* pTeam = GetUnit( *iter );
        if ( pTeam == NULL )
        { continue; }

        pTeam->SendMessageToTeamClient( &xAck, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
    }
}

template<>
void TeamBattleData::SendUnitCountMessage()
{
    //MsgTellBattleSignUpCount xTell;

    //xTell.uchType  = BattleDefine::TeamType;
    //xTell.ustMapID = GetFightMapID();
    //xTell.ustCount = GetUnitCount();
    //if ( GetStatus() == BattleDefine::Status_SignUp )       // 报名阶段把剩余时间发给客户端
    //{
    //    xTell.nStartLeftTime = ( GetStartSignUpTime() + GetSignUpTime() - HQ_TimeGetTime() ) / 1000;
    //}

    //for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    //{
    //    GameTeam* pTeam = GetUnit( *iter );
    //    if ( pTeam == NULL )
    //    { continue; }

    //    pTeam->SendMessageToTeamClient( &xTell, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
    //}
}

template<>
void TeamBattleData::StartEnterFightMap( unsigned int nCurrentTime )
{
    SetStatus( BattleDefine::Status_EndEnter );

    // 清空战斗记录
    mapBattleRecord.clear();
    mapKillInfo.clear();

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetFightMapID() );
    if ( pMapData == NULL )
    { return; }

    while ( true )      // 处理进入战场逻辑
    {
        if ( GetUnitCount() < 3 )
        { break; }

        unsigned long dwMapID = theGameWorld.GetEctypeMapID( GetFightMapID(), true );
        GameStage* pStage = theGameWorld.SingleCreateStage( GetFightMapID(), dwMapID );
        if ( pStage == NULL )
        { continue; }

        for ( int i = 0; i < 6; ++i )           // 每个地图副本最多允许6个队伍
        {
            int nSize = GetUnitCount();
            if ( nSize == 0 )
            { break; }  // 已经没有匹配的玩家了

            int nIndex = rand() % nSize;
            UnitSetIter iter = setUnit.begin();
            advance( iter, nIndex );

            GameTeam* pTeam = GetUnit( *iter );
            if ( pTeam != NULL )
            {
                MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByIndex( i + 2 );
                if ( pRelive == NULL )
                { return; }

                BattleDefine::BattleRecord xRecord;
                xRecord.SetTeamID( *iter );
                xRecord.SetReliveIndex( i + 2 );
                AddBattleRecord( dwMapID, *iter, xRecord );

                for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
                {
                    GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                    if ( pMember == NULL )
                    { continue; }

                    GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
                    if ( pPlayer == NULL )      // 小于50 不让进
                    { continue; }

                    if ( pPlayer->GetLevel() < 50 )
                    {
                        MsgAckResult xAck;
                        xAck.result = ER_LevelErrorEnterTeamBattle;
                        xAck.value  = 50;
                        pPlayer->SendMessageToClient( &xAck );
                        continue;
                    }

                    // 设置间隔时间0, 等客户端回馈消息
                    pPlayer->SetWaitChangeStage( GamePlayer::EnterStage, dwMapID, pRelive->PositionX, pRelive->PositionY, pRelive->Direction, 0, false );

                    MsgEnterTeamBattleReq xReq;
                    xReq.dwMapID = dwMapID;
                    pPlayer->SendMessageToClient( &xReq );
                }
            }

            setUnit.erase( iter );
        }
    }

    SendWaitNextBattleMessage();    // 通知客户端没进入的等待下一场
    SendUnitCountMessage();
}

struct GreaterBattleRecord : public std::unary_function< BattleDefine::BattleRecord*, bool >
{
    bool operator()( BattleDefine::BattleRecord* pLeft, BattleDefine::BattleRecord* pRight )
    {
        return ( *pLeft > *pRight );
    }
};

template<>
void TeamBattleData::EndFight( unsigned int nCurrentTime )
{
    // 如果是重复报名战场, 继续下一轮
    if ( GetRepeatTurns() > 0 )
    {
        SetSignUpInfo( nCurrentTime );
    }
    else
    {
        SetStatus( BattleDefine::Status_Close );
    }

    for ( MapBattleRecordIter iter = mapBattleRecord.begin(); iter != mapBattleRecord.end(); ++iter )
    {
        SendBattleRecordToClient( iter->first, MsgTellBattleRecord::Status_FightEnd );      // 发送结果给客户端

        // 计算积分, 处理结果
        std::vector< BattleDefine::BattleRecord* > vecRecord( 0 );
        for ( TeamRecordIter riter = iter->second.begin(); riter != iter->second.end(); ++riter )
        {
            vecRecord.push_back( &riter->second );
        }

        std::sort( vecRecord.begin(), vecRecord.end(), GreaterBattleRecord() );       // 排序
        int nIndex = 1;
        for ( std::vector< BattleDefine::BattleRecord* >::iterator viter = vecRecord.begin(); viter != vecRecord.end(); ++viter )
        {
            GameTeam* pTeam = GetUnit( ( *viter )->GetTeamID() );
            if ( pTeam == NULL )
            { continue; }

            // 处理奖励
            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                if ( pMember == NULL )
                { continue; }

                GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
                if ( pPlayer == NULL || pPlayer->GetMapID() != iter->first )
                { continue; }       // 不在本地图的不给奖励 

                // 调用脚本, 由脚本负责该做些什么
                GetScriptMgr()->StartupVM( ST_TEAMBATTLER, 0, pPlayer, false, nIndex );      
            }

            ++nIndex;
        }
    }
}

template<>
void TeamBattleData::UpdateBattleRecord( unsigned dwMapID, unsigned int nID, unsigned int nPlayeriD, int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage /* = true */ )
{
    BattleDefine::BattleRecord* pRecord = GetBattleRecord( nID, dwMapID );
    if ( pRecord == NULL )
    { return; }

    pRecord->AddIntegral( nIntegral );
    pRecord->AddKillCount( nKillCount );
    pRecord->AddDeathCount( nDeathCount );

    // 更新个人积分
    if ( nIntegral > 0 )
    {
        MapKillInfoIter kiter = mapKillInfo.find( nPlayeriD );
        if ( kiter == mapKillInfo.end() )
        {
            kiter = mapKillInfo.insert( std::make_pair( nPlayeriD, BattleDefine::KillInfo() ) ).first;
        }
        if ( kiter != mapKillInfo.end() )
        {
            kiter->second.SetIntegral( kiter->second.GetIntegral() + nIntegral );
        }
    }

    // 通知客户端
    if ( !bSendMessage )
    { return; }

    SendBattleRecordToClient( dwMapID, MsgTellBattleRecord::Status_Fighting );
}

template<>
void TeamBattleData::SendBattleRecordToClient( unsigned int dwMapID, unsigned char uchStatus, GamePlayer* pPlayer /* = NULL*/ )
{
    MapBattleRecordIter iter = mapBattleRecord.find( dwMapID );
    if ( iter == mapBattleRecord.end() )
    { return; }

    MsgTellBattleRecord xTell;
    xTell.uchType   = BattleDefine::TeamType;
    xTell.uchStatus = uchStatus;
    xTell.dwMapID   = dwMapID;

    int nCount = 0;
    for ( TeamRecordIter riter = iter->second.begin(); riter != iter->second.end(); ++riter )
    {
        GameTeam* pTeam = GetUnit( riter->first );
        if ( pTeam == NULL )
        { continue; }

        GameTeamMember* pMember = pTeam->GetTeamMemberByID( pTeam->GetTeamHeaderID() );
        if ( pMember == NULL )
        { continue; }

        xTell.xRecord[nCount].dwID = pTeam->GetID();
        strncpy_s( xTell.xRecord[nCount].szName, sizeof( xTell.xRecord[nCount].szName ), pMember->GetName(), sizeof( xTell.xRecord[nCount].szName ) - 1 );

        xTell.xRecord[nCount].nIntegral   = riter->second.GetIntegral();
        xTell.xRecord[nCount].nKillCount  = riter->second.GetKillCount();
        xTell.xRecord[nCount].nDeathCount = riter->second.GetDeathCount();
        ++nCount;
    }

    if ( pPlayer != NULL )
    {
        pPlayer->SendMessageToClient( &xTell );
    }
    else
    {
        GettheServer().SendMsgToStage( &xTell, dwMapID );
    }
}

template<>
void TeamBattleData::GetUnitName( MsgTellBattleSignUpInfo* pSignUpInfo )
{
    if ( pSignUpInfo == NULL )
    { return; }

    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    {
        GameTeam* pTeam = GetUnit( *iter );
        if ( pTeam == NULL )
        { continue; }

        GameTeamMember* pMember = pTeam->GetTeamMemberByID( pTeam->GetTeamHeaderID() );
        if ( pMember == NULL )
        { continue; }

        pSignUpInfo->AddTeamInfo( *iter, pMember->GetName() );
    }
}

template<>      // 更新每个人的杀人情况, 返回额外的奖励积分
unsigned int TeamBattleData::UpdateKillRecord( GamePlayer* pKiller, GamePlayer* pBeKill )
{
    if ( pKiller == NULL || pBeKill == NULL )
    { return 0; }

    // 获得杀人者的杀人信息
    MapKillInfoIter kiter = mapKillInfo.find( pKiller->GetDBCharacterID() );
    if ( kiter == mapKillInfo.end() )
    {
        kiter = mapKillInfo.insert( std::make_pair( pKiller->GetDBCharacterID(), BattleDefine::KillInfo() ) ).first;
        if ( kiter == mapKillInfo.end() )
        { return 1; }
    }

    // 获得被杀者的杀人信息
    MapKillInfoIter biter = mapKillInfo.find( pBeKill->GetDBCharacterID() );
    if ( biter == mapKillInfo.end() )
    {
        biter = mapKillInfo.insert( std::make_pair( pBeKill->GetDBCharacterID(), BattleDefine::KillInfo() ) ).first;
        if ( biter == mapKillInfo.end() )
        { return 1; }
    }

    // 判断杀人者....
    kiter->second.SetKillCount( kiter->second.GetKillCount() + 1 );     // 杀人数+1
    kiter->second.SetKeepKill( kiter->second.GetKeepKill() + 1 );       // 持续杀人数+1

    // 被杀者
    int nKillCount = biter->second.GetKeepKill();
    biter->second.SetKeepKill( 0 );     // 清除持续杀人记录
    biter->second.SetBeKillCount( biter->second.GetBeKillCount() + 1 );

    // 杀人2个以上, 或者终结杀2人以上, 通知客户端
    if ( kiter->second.GetKeepKill() > 2 || nKillCount > 2 )
    {
        MsgNotifyBattleKillNum xKill;
        strncpy_s( xKill.killer, sizeof( xKill.killer ), pKiller->GetCharName(), sizeof( xKill.killer ) - 1 );
        strncpy_s( xKill.beKiller, sizeof( xKill.beKiller ), pBeKill->GetCharName(), sizeof( xKill.beKiller ) - 1 );
        xKill.killNum   = kiter->second.GetKeepKill();
        xKill.beKillNum = nKillCount;
        GettheServer().SendMsgToStage( &xKill, pKiller->GetMapID() );
    }

    unsigned int nIntegral = 1;
    if ( nKillCount > 2 )       // 终结被杀者3连杀..获得额外的积分
    {
        nIntegral = ( nKillCount - 1 ) / 2;
        if ( nIntegral > 5 )
        { nIntegral = 5; }
    }

    return nIntegral;
}