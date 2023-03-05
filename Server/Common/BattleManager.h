#ifndef __BATTLEMANAGER_H__
#define __BATTLEMANAGER_H__

/************************************************************************
                ս�������߼�
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
        Status_SignUp     = 1,  // �����׶�
        Status_StartEnter = 2,  // ��������, ����ս�������׶�
        Status_EndEnter   = 3,  // ����ս������
        Status_Fight      = 4,  // ս���׶�
        Status_EndFight   = 5,  // ս������
        Status_Close      = 6,  // �رս׶�

        MaxPlayerSignUpCount = 3,   // ����ս��ÿ��ֻ�ܲμ�3����̨
        MaxUnitCount  = 30, // 1v1ս��ÿ��ֻ����30�˽���
        SignUpTime    = 300000, // 1v1��������ʱ��

        UpdateSpaceTime = 2000, // Update ���ʱ��

        NoneUnitID   = 0,
        NoneMapID    = 0xFFFF, // �����mapID

        Success        = 0,      // �����ɹ�
        ErrorTime      = 1,      // ��Ч��ID
        AlreadySignUp  = 2,      // �Ѿ�������
        SignUpFull     = 3,      // �����Ѿ�����
        BattleClosed   = 4,      // ս���Ѿ��ر���
        SignUpLimit    = 5,      // �μӴ�������       

        ErrorUnitID  = 0,      // ��Ч��ID

        BattleRun      = 0,      // ս��������
        BattleRelease  = 1,      // �ͷ�ս��

        PlayerType     = 1,       // ����ս��
        TeamType       = 2,       // ����ս��  
        GuildType      = 3        // ����ս��
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

            // ����ж���������
            return nDeathCount < xRecord.GetDeathCount();
        }

        friend bool operator > ( BattleRecord& xLeft, BattleRecord& xRight )
        {
            return xLeft.operator > ( xRight );
        }

    private:
        unsigned int dwTeamID; // ����ID
        int nIntegral;      // ��¼����
        int nKillCount;     // ɱ�˸���
        int nDeathCount;    // ��¼��������
        int nReliveIndex;   // ��¼������
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
        unsigned short ustIntegral;     // ��û���
        unsigned short ustKillCount;    // ɱ������
        unsigned short ustBeKillCount;  // ��ɱ����
        unsigned short ustKeepKill;     // ��ǰ��ɱ��
    };
}

struct MsgTellBattleSignUpInfo;
class GamePlayer;
template< class T, class U = GamePlayer >
class BattleData : INHERIT_POOL_PARAM( BattleData< T >, 50 )
{
public:

    static BattleData* CreateBattleData(){ return CNewWithDebug< BattleData< T > >::Alloc( 1, "BattleData::CreateBattleData�д���CreateBattleDataʵ��" ); }
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
    bool IsAlreadySignUp( unsigned int nID );   // �Ƿ��Ѿ���������

    void AddBattleRecord( unsigned int dwMapID, unsigned int nID, BattleDefine::BattleRecord& xRecord );
    BattleDefine::BattleRecord* GetBattleRecord( unsigned int nID, unsigned int dwMapID );
    BattleDefine::BattleRecord* GetBattleRecord( unsigned int nID );
    void UpdateBattleRecord( unsigned int dwMapID, unsigned int nID, unsigned int nPlayerID, int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage = true );
    void SendBattleRecordToClient( unsigned int dwMapID, unsigned char uchStatus, U* pPlayer = NULL );
    unsigned int UpdateKillRecord( U* pKiller, U* pBeKill );            // ���ض���Ľ�������
    BattleDefine::KillInfo* GetBattleKillInfo( unsigned int nPlayerID );

    bool IsInBattleData( unsigned int nID, unsigned int dwMapID );    // �Ƿ���ս����

    bool CheckCanSignUp( unsigned int nID );    // ����ܷ���
    void CloseBattle();                         // �ر�ս��

    void EnterWaitMap( unsigned int nID );      // ����ȴ���ͼ

    unsigned short RunUpdate( unsigned int nCurrentTime );  // Update

    void GetUnitName( MsgTellBattleSignUpInfo* pSignUpInfo );
protected:
    typedef std::set< unsigned int > UnitSet;     // �����ĵ�λID ��ɫ��dbid  �����Ƕ���ID
    typedef typename UnitSet::iterator UnitSetIter;

    typedef std::map< unsigned int, BattleDefine::BattleRecord > TeamRecord;    // ս������
    typedef TeamRecord::iterator TeamRecordIter;

    typedef std::map< unsigned int, TeamRecord > MapBattleRecord;
    typedef MapBattleRecord::iterator MapBattleRecordIter;

    typedef std::map< unsigned int, BattleDefine::KillInfo > MapKillInfo;
    typedef MapKillInfo::iterator MapKillInfoIter;

    void StartSignUp( unsigned int nCurrentTime );                  // ��ʼ����
    void StartEnterFightMap( unsigned int nCurrentTime );           // ����ս����ͼ
    void EndEnterFightMap( unsigned int nCurrentTime );             // ������Ҷ�����ս����ͼ
    void SetSignUpInfo( unsigned int nCurrentTime );                // ���ñ�����Ϣ

    void FightInFightMap( unsigned int nCurrentTime );
    void EndFight( unsigned int nCurrentTime );

    void CloseWaitMap();            // �رյȴ���ͼ
    void CloseFightMap();           // �뿪ս����ͼ

    void CheckSignUpValid();        // ��鱨������Ч��
    void SendUnitCountMessage();    // ���ͱ�����Ϣ
    void SendWaitNextBattleMessage();

    void SaveSignUpInfo( T* pUint );    // �����ɫ������һЩ��Ϣ

private:
    unsigned short ustMapLevel;         // ������ͼ�ȼ�
    unsigned short ustWaitMapID;        // �ȴ�������ͼID
    unsigned short ustFightMapID;       // ս��������ͼID

    unsigned int nSignUpTime;           // ��������ʱ��( ��λ : ms )
    unsigned int nStartSignUpTime;      // ������ʼʱ��
    unsigned int nStartFightTime;       // ��ʼս��ʱ��
    unsigned int nFightTime;            // ս������ʱ��
    unsigned char uchRepeatTurns;       // ս��ѭ������
    unsigned char uchStatus;            // ս����ǰ��״̬
    unsigned short ustMaxUnitCount;     // ��������������� 
    UnitSet setUnit;                    // �����ĵ�λ

    MapBattleRecord mapBattleRecord;    // ս������
    MapKillInfo mapKillInfo;            // ��¼ÿ���˵�ɱ�����
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
    // ��������뿪����
    CloseWaitMap();
    CloseFightMap();

    Release();  // �ͷ��ڴ�
}

template< class T, class U >
void BattleData< T, U >::CloseWaitMap()
{
    // �ø����Լ�����
}

template< class T, class U >
void BattleData< T, U >::CloseFightMap()
{
    // �ø����Լ�����
}

template< class T, class U >
void BattleData< T, U >::StartSignUp( unsigned int nCurrentTime )
{
    CheckSignUpValid();     // ��鱨������Ч��

    if ( GameTime::IsPassCurrentTime( nCurrentTime, GetStartSignUpTime(), GetSignUpTime() ) )
    {
        SetStatus( BattleDefine::Status_StartEnter );    // ��������
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
    switch ( GetStatus() )  // �õ�״̬
    {
    case BattleDefine::Status_Init:         // ��ʼ״̬
        {
            SetSignUpInfo( nCurrentTime );
        }
        break;
    case BattleDefine::Status_SignUp:       // �����׶�
        {
            StartSignUp( nCurrentTime );
        }
        break;
    case BattleDefine::Status_StartEnter:    // ����ս��
        {
            StartEnterFightMap( nCurrentTime );
        }
        break;
    case BattleDefine::Status_EndEnter:    // ����ս������
        {
            EndEnterFightMap( nCurrentTime );
        }
        break;
    case BattleDefine::Status_Fight:       // ��ʼս��
        {
            FightInFightMap( nCurrentTime );
        }
        break;
    case BattleDefine::Status_EndFight:
        {
            EndFight( nCurrentTime );
        }
        break;
    case BattleDefine::Status_Close:        // �ر�ս��
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
    BattleMap m_mapBattle;           // ս������
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
// ���
class GamePlayer;  
typedef BattleData < GamePlayer, GamePlayer > PlayerBattleData;
typedef BattleManager< PlayerBattleData > PlayerBattleManager;
#define thePlayerBattleManager PlayerBattleManager::Instance()           // ���1v1 ս��

// ����
class GameTeamMember;
template< class T, class U > class Team;      
typedef BattleData < Team< GameTeamMember, GamePlayer >, GamePlayer > TeamBattleData;
typedef BattleManager< TeamBattleData > TeamBattleManager;
#define theTeamBattleManager TeamBattleManager::Instance()           // ���� ս��

#endif