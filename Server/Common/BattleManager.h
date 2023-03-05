#ifndef __BATTLEMANAGER_H__
#define __BATTLEMANAGER_H__

/************************************************************************
                战场管理逻辑
                Filename:     BattleManager.h 
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "Memory_pool.h"
#include <map>
#include <vector>
#include "GameTimer.h"
#include "Singleton.h"

namespace BattleDefine
{
    enum BattleFieldDefine
    {
        Status_Init       = 0,
        Status_SignUp     = 1,  // 报名阶段
        Status_StartEnter = 2,  // 报名结束, 进入战斗场景阶段
        Status_EndEnter   = 3,  // 进入战场结束
        Status_Fight      = 4,  // 战斗阶段
        Status_EndFight   = 5,  // 战斗结束
        Status_Close      = 6,  // 关闭阶段

        MaxPlayerSignUpCount = 3,   // 个人战场每天只能参加3次擂台
        MaxUnitCount  = 30, // 1v1战场每次只允许30人进入
        SignUpTime    = 300000, // 1v1报名持续时间

        UpdateSpaceTime = 2000, // Update 间隔时间

        NoneUnitID   = 0,
        NoneMapID    = 0xFFFF, // 错误的mapID

        Success        = 0,      // 报名成功
        ErrorTime      = 1,      // 无效的ID
        AlreadySignUp  = 2,      // 已经报名了
        SignUpFull     = 3,      // 报名已经满了
        BattleClosed   = 4,      // 战场已经关闭了
        SignUpLimit    = 5,      // 参加次数限制       

        ErrorUnitID  = 0,      // 无效的ID

        BattleRun      = 0,      // 战场运行中
        BattleRelease  = 1,      // 释放战场

        PlayerType     = 1,       // 个人战场
        TeamType       = 2,       // 队伍战场  
        GuildType      = 3        // 工会战场
    };

    class BattleRecord
    {
    public:
        BattleRecord() : nIntegral( 0 ), nKillCount( 0 ), nDeathCount( 0 ) {}

        void SetTeamID( unsigned int dwValue ) { dwTeamID = dwValue; }
        void SetIntegral( int nValue ) { nIntegral = nValue; }
        void SetDeathCount( int nValue ) { nDeathCount = nValue; }
        void SetKillCount( int nValue ) { nKillCount = nValue; }
        void SetReliveIndex( int nValue ) { nReliveIndex = nValue; }

        void AddIntegral( int nValue ) { nIntegral += nValue; }
        void AddKillCount( int nValue ) { nKillCount += nValue; }
        void AddDeathCount( int nValue ) { nDeathCount += nValue; }

        unsigned int GetTeamID() const { return dwTeamID; }
        int GetIntegral() const { return nIntegral; }
        int GetKillCount() const { return nKillCount; }
        int GetDeathCount() const { return nDeathCount; }
        int GetReliveIndex() const { return nReliveIndex; }

        bool operator > ( BattleRecord& xRecord ) const
        {
            if ( nIntegral > xRecord.GetIntegral() )
            { return true; }

            if ( nIntegral < xRecord.GetIntegral() )
            { return false; }

            // 相等判断死亡次数
            return nDeathCount < xRecord.GetDeathCount();
        }

        friend bool operator > ( BattleRecord& xLeft, BattleRecord& xRight )
        {
            return xLeft.operator > ( xRight );
        }

    private:
        unsigned int dwTeamID; // 队伍ID
        int nIntegral;      // 记录积分
        int nKillCount;     // 杀人个数
        int nDeathCount;    // 记录死亡次数
        int nReliveIndex;   // 记录重生点
    };

    class KillInfo
    {
    public:
        KillInfo() : ustIntegral( 0 ), ustKillCount( 0 ), ustBeKillCount( 0 ), ustKeepKill( 0 ) { }

        void SetIntegral( unsigned short ustValue ) { ustIntegral = ustValue; }
        void SetKillCount( unsigned short ustValue ) { ustKillCount = ustValue; }
        void SetBeKillCount( unsigned short ustValue ) { ustBeKillCount = ustValue; }
        void SetKeepKill( unsigned short ustValue ) { ustKeepKill = ustValue; }

        unsigned short GetIntegral() const { return ustIntegral; }
        unsigned short GetKillCount() const { return ustKillCount; }
        unsigned short GetBeKillCount() const { return ustBeKillCount; }
        unsigned short GetKeepKill() const { return ustKeepKill; }

    private:
        unsigned short ustIntegral;     // 获得积分
        unsigned short ustKillCount;    // 杀人总数
        unsigned short ustBeKillCount;  // 被杀总数
        unsigned short ustKeepKill;     // 当前连杀数
    };
}

struct MsgTellBattleSignUpInfo;
class GamePlayer;
template< class T, class U = GamePlayer >
class BattleData : INHERIT_POOL_PARAM( BattleData< T >, 50 )
{
public:

    static BattleData* CreateBattleData(){ return CNewWithDebug< BattleData< T > >::Alloc( 1, "BattleData::CreateBattleData中创建CreateBattleData实例" ); }
    virtual void Release() { CNewWithDebug< BattleData< T > >::Free( this ); }

    BattleData();
    bool IsBattleDataError() { return ustMapLevel == 0 || ustWaitMapID == BattleDefine::NoneMapID || ustFightMapID == BattleDefine::NoneMapID; }

    void SetMapLevel( unsigned short ustValue ) { ustMapLevel = ustValue; }
    void SetWaitMapID( unsigned short ustValue ) { ustWaitMapID = ustValue; }
    void SetFightMapID( unsigned short ustValue ) { ustFightMapID = ustValue; }
    void SetSignUpTime( unsigned int nValue ) { nSignUpTime = nValue; }
    void SetStartSignUpTime( unsigned int nValue ) { nStartSignUpTime = nValue; }
    void SetStatus( unsigned char uchValue ) { uchStatus = uchValue; }
    void SetMaxUnitCount( unsigned short ustValue ) { ustMaxUnitCount = ustValue; }
    void SetRepeatTurns( unsigned char uchValue ) { uchRepeatTurns = uchValue; }
    void SetFightTime( unsigned int dwTime ) { nFightTime = dwTime; }
    void SetStartFightTime( unsigned int dwTime ) { nStartFightTime = dwTime; }

    unsigned short GetMapLevel() const { return ustMapLevel; }
    unsigned short GetWaitMapID() const { return ustWaitMapID; }
    unsigned short GetFightMapID() const { return ustFightMapID; }
    unsigned int GetSignUpTime() const { return nSignUpTime; }
    unsigned int GetStartSignUpTime() const { return nStartSignUpTime; }
    unsigned char GetStatus() const { return uchStatus; }
    unsigned short GetMaxUnitCount() const { return ustMaxUnitCount; }
    unsigned char GetRepeatTurns() const { return uchRepeatTurns; }
    unsigned int GetFightTime() const { return nFightTime; }
    unsigned int GetStartFightTime() const { return nStartFightTime; }

    unsigned short GetUnitCount() const { return static_cast< unsigned short >( setUnit.size() ); }
    unsigned short AddUnit( unsigned int nID );
    unsigned short RemoveUnit( unsigned int nID );
    unsigned short GetUnitLevel( unsigned int nID );
    T* GetUnit( unsigned int nID );
    bool IsAlreadySignUp( unsigned int nID );   // 是否已经报名过了

    void AddBattleRecord( unsigned int dwMapID, unsigned int nID, BattleDefine::BattleRecord& xRecord );
    BattleDefine::BattleRecord* GetBattleRecord( unsigned int nID, unsigned int dwMapID );
    BattleDefine::BattleRecord* GetBattleRecord( unsigned int nID );
    void UpdateBattleRecord( unsigned int dwMapID, unsigned int nID, unsigned int nPlayerID, int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage = true );
    void SendBattleRecordToClient( unsigned int dwMapID, unsigned char uchStatus, U* pPlayer = NULL );
    unsigned int UpdateKillRecord( U* pKiller, U* pBeKill );            // 返回额外的奖励积分
    BattleDefine::KillInfo* GetBattleKillInfo( unsigned int nPlayerID );

    bool IsInBattleData( unsigned int nID, unsigned int dwMapID );    // 是否在战场中

    bool CheckCanSignUp( unsigned int nID );    // 检查能否报名
    void CloseBattle();                         // 关闭战场

    void EnterWaitMap( unsigned int nID );      // 进入等待地图

    unsigned short RunUpdate( unsigned int nCurrentTime );  // Update

    void GetUnitName( MsgTellBattleSignUpInfo* pSignUpInfo );
protected:
    typedef std::set< unsigned int > UnitSet;     // 报名的单位ID 角色是dbid  队伍是队伍ID
    typedef typename UnitSet::iterator UnitSetIter;

    typedef std::map< unsigned int, BattleDefine::BattleRecord > TeamRecord;    // 战场积分
    typedef TeamRecord::iterator TeamRecordIter;

    typedef std::map< unsigned int, TeamRecord > MapBattleRecord;
    typedef MapBattleRecord::iterator MapBattleRecordIter;

    typedef std::map< unsigned int, BattleDefine::KillInfo > MapKillInfo;
    typedef MapKillInfo::iterator MapKillInfoIter;

    void StartSignUp( unsigned int nCurrentTime );                  // 开始报名
    void StartEnterFightMap( unsigned int nCurrentTime );           // 进入战斗地图
    void EndEnterFightMap( unsigned int nCurrentTime );             // 所有玩家都进入战斗地图
    void SetSignUpInfo( unsigned int nCurrentTime );                // 设置报名信息

    void FightInFightMap( unsigned int nCurrentTime );
    void EndFight( unsigned int nCurrentTime );

    void CloseWaitMap();            // 关闭等待地图
    void CloseFightMap();           // 离开战斗地图

    void CheckSignUpValid();        // 检查报名的有效性
    void SendUnitCountMessage();    // 发送报名信息
    void SendWaitNextBattleMessage();

    void SaveSignUpInfo( T* pUint );    // 保存角色报名的一些信息

private:
    unsigned short ustMapLevel;         // 场景地图等级
    unsigned short ustWaitMapID;        // 等待场景地图ID
    unsigned short ustFightMapID;       // 战斗场景地图ID

    unsigned int nSignUpTime;           // 报名持续时间( 单位 : ms )
    unsigned int nStartSignUpTime;      // 报名开始时间
    unsigned int nStartFightTime;       // 开始战斗时间
    unsigned int nFightTime;            // 战斗持续时间
    unsigned char uchRepeatTurns;       // 战场循环几轮
    unsigned char uchStatus;            // 战场当前的状态
    unsigned short ustMaxUnitCount;     // 允许报名的最大数量 
    UnitSet setUnit;                    // 报名的单位

    MapBattleRecord mapBattleRecord;    // 战场积分
    MapKillInfo mapKillInfo;            // 记录每个人的杀人情况
};

template< class T, class U >
BattleData< T, U >::BattleData() : ustMapLevel( 0 ), ustWaitMapID( BattleDefine::NoneMapID ), ustFightMapID( BattleDefine::NoneMapID ), 
                                    nSignUpTime( 0 ), uchStatus( BattleDefine::Status_Init ), ustMaxUnitCount( 0 ), nFightTime( 0 ), nStartFightTime( 0 )
{
    setUnit.clear();
}

template< class T, class U >
unsigned short BattleData< T, U >::AddUnit( unsigned int nID )
{
    if ( nID == BattleDefine::NoneUnitID )
    { return BattleDefine::ErrorUnitID; }

    UnitSetIter iter = setUnit.find( nID );
    if ( iter != setUnit.end() )
    { return BattleDefine::AlreadySignUp; }

    if ( GetUnitCount() >= GetMaxUnitCount() )
    { return BattleDefine::SignUpFull; }

    setUnit.insert( nID );

    SendUnitCountMessage();

    return BattleDefine::Success;
}

template< class T, class U >
unsigned short BattleData< T, U >::RemoveUnit( unsigned int nID )
{
    if ( nID == BattleDefine::NoneUnitID )
    { return BattleDefine::ErrorUnitID; }

    setUnit.erase( nID );

    SendUnitCountMessage();

    return BattleDefine::Success;
}

template< class T, class U >
bool BattleData< T, U >::IsAlreadySignUp( unsigned int nID )
{
    if ( nID == BattleDefine::NoneUnitID )
    { return false; }

    UnitSetIter iter = setUnit.find( nID );
    return ( iter != setUnit.end() );
}

template< class T, class U >
void BattleData< T, U >::AddBattleRecord( unsigned int dwMapID, unsigned int nID, BattleDefine::BattleRecord& xRecord )
{
    MapBattleRecordIter iter = mapBattleRecord.find( dwMapID );
    if ( iter == mapBattleRecord.end() )
    {
        TeamRecord mapTeamRecord;
        mapTeamRecord.insert( std::make_pair( nID, xRecord ) );

        mapBattleRecord.insert( std::make_pair( dwMapID, mapTeamRecord ) );
    }
    else
    {
        iter->second.insert( std::make_pair( nID, xRecord ) );
    }
}

template< class T, class U >
BattleDefine::BattleRecord* BattleData< T, U >::GetBattleRecord( unsigned int nID, unsigned int dwMapID )
{
    MapBattleRecordIter iter = mapBattleRecord.find( dwMapID );
    if ( iter == mapBattleRecord.end() )
    { return NULL; }

    TeamRecordIter riter = iter->second.find( nID );
    if ( riter == iter->second.end() )
    { return NULL; }

    return &( riter->second );
}

template< class T, class U >
BattleDefine::BattleRecord* BattleData< T, U >::GetBattleRecord( unsigned int nID )
{
    for ( MapBattleRecordIter iter = mapBattleRecord.begin(); iter != mapBattleRecord.end(); ++iter )
    {
        TeamRecordIter riter = iter->second.find( nID );
        if ( riter != iter->second.end() )
        { return &( riter->second ); }
    }

    return NULL;
}

template< class T, class U >
BattleDefine::KillInfo* BattleData< T, U >::GetBattleKillInfo( unsigned int nPlayerID )
{
    MapKillInfoIter iter = mapKillInfo.find( nPlayerID );
    if ( iter == mapKillInfo.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T, class U >
bool BattleData< T, U >::IsInBattleData( unsigned int nID, unsigned int dwMapID )
{
    return GetBattleRecord( nID, dwMapID ) != NULL;
}

template< class T, class U >
void BattleData< T, U >::CloseBattle()
{
    // 所有玩家离开场景
    CloseWaitMap();
    CloseFightMap();

    Release();  // 释放内存
}

template< class T, class U >
void BattleData< T, U >::CloseWaitMap()
{
    // 让副本自己销毁
}

template< class T, class U >
void BattleData< T, U >::CloseFightMap()
{
    // 让副本自己销毁
}

template< class T, class U >
void BattleData< T, U >::StartSignUp( unsigned int nCurrentTime )
{
    CheckSignUpValid();     // 检查报名的有效性

    if ( GameTime::IsPassCurrentTime( nCurrentTime, GetStartSignUpTime(), GetSignUpTime() ) )
    {
        SetStatus( BattleDefine::Status_StartEnter );    // 报名结束
    }
}

template< class T, class U >
void BattleData< T, U >::SetSignUpInfo( unsigned int nCurrentTime )
{
    SetStartSignUpTime( nCurrentTime );
    SetRepeatTurns( GetRepeatTurns() - 1 );
    SetStatus( BattleDefine::Status_SignUp );
}

template< class T, class U >
void BattleData< T, U >::EndEnterFightMap( unsigned int nCurrentTime )
{
    SetStartFightTime( nCurrentTime );
    SetStatus( BattleDefine::Status_Fight );
}

template< class T, class U >
void BattleData< T, U >::FightInFightMap( unsigned int nCurrentTime )
{
    if ( !GameTime::IsPassCurrentTime( nCurrentTime, GetStartFightTime(), GetFightTime() ) )
    { return; }

    SetStartFightTime( 0 );
    SetStatus( BattleDefine::Status_EndFight );
}

template< class T, class U >
unsigned short BattleData< T, U >::RunUpdate( unsigned int nCurrentTime )
{
    switch ( GetStatus() )  // 得到状态
    {
    case BattleDefine::Status_Init:         // 初始状态
        {
            SetSignUpInfo( nCurrentTime );
        }
        break;
    case BattleDefine::Status_SignUp:       // 报名阶段
        {
            StartSignUp( nCurrentTime );
        }
        break;
    case BattleDefine::Status_StartEnter:    // 进入战场
        {
            StartEnterFightMap( nCurrentTime );
        }
        break;
    case BattleDefine::Status_EndEnter:    // 进入战场结束
        {
            EndEnterFightMap( nCurrentTime );
        }
        break;
    case BattleDefine::Status_Fight:       // 开始战斗
        {
            FightInFightMap( nCurrentTime );
        }
        break;
    case BattleDefine::Status_EndFight:
        {
            EndFight( nCurrentTime );
        }
        break;
    case BattleDefine::Status_Close:        // 关闭战场
        {
            CloseBattle();
            return BattleDefine::BattleRelease;
        }
        break;
    }

    return BattleDefine::BattleRun;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
class BattleManager : public ISingletion< BattleManager< T > >
{
public:
    BattleManager();
    ~BattleManager();

    unsigned short GetBattleDataCount() const { return static_cast< unsigned short >( m_mapBattle.size() ); }

    bool AddBattleData( T* pBattleData );
    T* GetBattleDateByMapID( unsigned short ustMapID );
    T* GetBattleDateByIndex( unsigned char uchIndex );
    bool RemoveBattleDataByMapID( unsigned short ustMapID );
    bool IsAlreadySignUp( unsigned int nID );
    bool IsInBattleData( unsigned int nID, unsigned int dwMapID );

    void RunUpdate( unsigned int nCurrenTime );

protected:
    typedef std::map< unsigned short, T* > BattleMap;
    typedef typename BattleMap::iterator BattleMapIter;

private:
    BattleMap m_mapBattle;           // 战场容器
    GameTimerEx m_xUpdateTimer;
};

template< class T >
BattleManager< T >::BattleManager()
{
    m_mapBattle.clear();
    m_xUpdateTimer.StartTimer( 1, BattleDefine::UpdateSpaceTime );
}

template< class T >
BattleManager< T >::~BattleManager()
{
    for ( BattleMapIter iter = m_mapBattle.begin(); iter != m_mapBattle.end(); ++iter )
    {
        T* pBattleData = iter->second;
        if ( pBattleData == NULL )
        { continue; }

        pBattleData->CloseBattle();
    }

    m_mapBattle.clear();
}

template< class T >
bool BattleManager< T >::AddBattleData( T* pBattleData )
{
    if ( pBattleData == NULL || pBattleData->IsBattleDataError() )
    { return false; }

    BattleMapIter iter = m_mapBattle.find( pBattleData->GetWaitMapID() );
    if ( iter != m_mapBattle.end() )
    {
        if ( iter->second != NULL )
        {
            iter->second->CloseBattle();
        }

        iter->second = pBattleData;
        return true;
    }

    return m_mapBattle.insert( std::make_pair( pBattleData->GetWaitMapID(), pBattleData ) ).second;
}

template< class T >
bool BattleManager< T >::RemoveBattleDataByMapID( unsigned short ustMapID )
{
    BattleMapIter iter = m_mapBattle.find( ustMapID );
    if ( iter == m_mapBattle.end() )
    { return false; }

    if ( iter->second != NULL )
    {
        iter->second->CloseBattle();
    }

    m_mapBattle.erase( iter );
    return true;
}

template< class T >
T* BattleManager< T >::GetBattleDateByMapID( unsigned short ustMapID )
{
    BattleMapIter iter = m_mapBattle.find( ustMapID );
    if ( iter == m_mapBattle.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
T* BattleManager< T >::GetBattleDateByIndex( unsigned char uchIndex )
{
    if ( uchIndex >= GetBattleDataCount() )
    { return NULL; }

    BattleMapIter iter = m_mapBattle.begin();
    advance( iter, uchIndex );

    return iter->second;
}

template< class T >
bool BattleManager< T >::IsAlreadySignUp( unsigned int nID )
{
    for ( BattleMapIter iter = m_mapBattle.begin(); iter != m_mapBattle.end(); ++iter )
    {
        T* pBattleData = iter->second;
        if ( pBattleData == NULL )
        { continue; }

        if ( pBattleData->IsAlreadySignUp( nID ) )
        { return true; }
    }

    return false;
}

template< class T >
bool BattleManager< T >::IsInBattleData( unsigned int nID, unsigned int dwMapID )
{
    T* pBattleData = m_mapBattle.find( EctypeId2MapId( dwMapID ) );
    if ( pBattleData == NULL )
    { return false; }

    return pBattleData->IsInBattleData( nID, dwMapID );
}

template< class T >
void BattleManager< T >::RunUpdate( unsigned int nCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    for ( BattleMapIter iter = m_mapBattle.begin(); iter != m_mapBattle.end(); )
    {
        T* pBattleData = iter->second;
        if ( pBattleData == NULL )
        { 
            iter = m_mapBattle.erase( iter );
            continue;
        }

        if ( pBattleData->RunUpdate( nCurrentTime ) == BattleDefine::BattleRelease )
        {
            iter = m_mapBattle.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// 玩家
class GamePlayer;  
typedef BattleData < GamePlayer, GamePlayer > PlayerBattleData;
typedef BattleManager< PlayerBattleData > PlayerBattleManager;
#define thePlayerBattleManager PlayerBattleManager::Instance()           // 玩家1v1 战场

// 队伍
class GameTeamMember;
template< class T, class U > class Team;      
typedef BattleData < Team< GameTeamMember, GamePlayer >, GamePlayer > TeamBattleData;
typedef BattleManager< TeamBattleData > TeamBattleManager;
#define theTeamBattleManager TeamBattleManager::Instance()           // 队伍 战场

#endif