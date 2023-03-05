#ifndef __SPECIALQUESTMANAGER_H__
#define __SPECIALQUESTMANAGER_H__

/************************************************************************
            特殊任务逻辑
            Filename:     SpecialQuestManager.h 
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

#include "Memory_Pool.h"
#include <list>
#include <set>
#include <map>
#include "GlobalFunction.h"

// 特别的任务
template< class T, class U >
class SpecialQuest : public Common::TObject_pool< SpecialQuest< T, U >, 50 >
{
protected:
    enum EConstDefine
    {
        ECD_Max_PubQuestCount = 5,         // 人物最大同时只能接5个酒馆任务
        ECD_Max_ConQuestCount = 3,         // 最大同时只能接3个征伐任务
    };

    typedef std::map< unsigned int, RecordTime > MapPubQuest;  // 酒馆接任务的时间信息
    typedef MapPubQuest::iterator                MapPubQuestIter;

    typedef std::set< int >      SetQuestID;
    typedef SetQuestID::iterator SetQuestIDIter;

    typedef std::map<short, short> QuestValues;
    typedef QuestValues::iterator  QuestValuesItr;

public:
    static SpecialQuest* CreateInstance() { return CNewWithDebug< SpecialQuest< T, U > >::Alloc( 1, "SpecialQuest::CreateInstance中创建SpecialQuest实例" ); }
    virtual void Release() { CNewWithDebug< SpecialQuest< T, U > >::Free( this ); }

public:
    SpecialQuest() : m_pGamePlayer( NULL )
    {
        m_mapSpecialQuest.clear();
        m_setReceiveQuestID.clear();
    }

    bool Initialize( T* pPlayer );             // 初始化
    void SaveQuest();                                   // 保存信息
    void ShowQuestList( unsigned int nNpcRunID );          // 刷新显示该NPC得任务 ( npcid 是 服务器动态ID )
   
    bool CanReceiveQuest( unsigned int nNpcConfigID, unsigned int nQuestID );        // 是否能接任务 nNpcConfigID Config中的Npc id
   
    void ReceiveQuest( unsigned int nNpcRunID, unsigned int nQuestID )
    {
        AddSpecialQuestCount( nQuestID );
    }

    void DoneQuest( unsigned int nNpcRunID, unsigned int nQuestID )
    {
        SubSpecialQuestCount( nQuestID ); // 保存的数量先减1

        SetSpecialQuestState( nQuestID, QuestManager::ESQGS_CannotGain  );
    }

    void ClearRecordTime( unsigned int nNpcRunID )             // 清除所有的记录时间
    {
        MapPubQuestIter iter = m_mapSpecialQuest.find( nNpcRunID );
        if ( iter != m_mapSpecialQuest.end() )
        {
            iter->second.SetRecordTime( 0 );
        }
    }

protected:
    void AddSpecialQuestCount( unsigned int nQuestID ) 
    { 
        m_setReceiveQuestID.insert( nQuestID );
    }

    void SubSpecialQuestCount( unsigned int nQuestID ) 
    {
        SetQuestIDIter iter = m_setReceiveQuestID.find( nQuestID );
        if ( iter != m_setReceiveQuestID.end() )
        {
            m_setReceiveQuestID.erase( nQuestID );
        }
    }

    int GetSpecialQuestCount();             // 获得当前人物接的酒馆任务的个数

    void AddSpecialQuest( unsigned int nNpcConfigID, RecordTime& xRecordTime )
    {
        if ( nNpcConfigID == 0 )
        { return; }

        m_mapSpecialQuest[nNpcConfigID] = xRecordTime;
    }

    RecordTime* GetSpecialQuestRecordTime( unsigned int nNpcConfigID )
    {
        MapPubQuestIter iter = m_mapSpecialQuest.find( nNpcConfigID );
        if ( iter == m_mapSpecialQuest.end() )
        { return NULL; }

        return &( iter->second );
    }

    void SetSpecialQuestState( unsigned int nQuestID, uint8 nState );
    void SetSpecialQuestState( unsigned int nQuestID, uint8 nState, QuestValues& mapValue );

private:
    
    SetQuestID m_setReceiveQuestID;
    T* m_pGamePlayer;
    MapPubQuest m_mapSpecialQuest;
};

template< class T, class U >
class SpecialQuestManager
{
protected:
    typedef std::map< unsigned int, T* > MapSpecialQuest;
    typedef typename MapSpecialQuest::iterator MapSpecialQuestIter;

public:
    static SpecialQuestManager< T, U >& Instance()
    {
        static SpecialQuestManager< T, U > s_xManager;
        return s_xManager;
    }

    ~SpecialQuestManager()
    {
        for ( MapSpecialQuestIter iter = m_mapSpecialQuest.begin(); iter != m_mapSpecialQuest.end(); ++iter )
        {
            if ( iter->second != NULL )
            {
                iter->second->Release();
                iter->second = NULL;
            }
        }

        m_mapSpecialQuest.clear();
    }

    bool AddSpecialQuest( unsigned int dwPlayerID, T* pQuest )
    {
        if ( pQuest == NULL )
        { return false; }

        MapSpecialQuestIter iter = m_mapSpecialQuest.find( dwPlayerID );
        if ( iter != m_mapSpecialQuest.end() )
        { 
            if ( iter->second != NULL )
            {
                iter->second->Release();
            }
            iter->second = pQuest;
            return false; 
        }
        
        return m_mapSpecialQuest.insert( make_pair( dwPlayerID, pQuest ) ).second;        
    }

    bool RemoveSpecialQuest( unsigned int dwPlayerID )
    {
        MapSpecialQuestIter iter = m_mapSpecialQuest.find( dwPlayerID );
        if ( iter == m_mapSpecialQuest.end() )
        { return false; }

        if ( iter->second != NULL )
        {
            iter->second->Release();
        }

        m_mapSpecialQuest.erase( iter );
        return true;
    }

    T* GetSpecialQuest( unsigned int dwPlayerID )
    {
        MapSpecialQuestIter iter = m_mapSpecialQuest.find( dwPlayerID );
        if ( iter == m_mapSpecialQuest.end() )
        { return NULL; }

        return iter->second;
    }

    T* GetSpecialQuest( unsigned int dwPlayerID, U* pPlayer )
    {
        if ( pPlayer == NULL )
        { return NULL; }

        T* pQuest = GetSpecialQuest( dwPlayerID );
        if ( pQuest == NULL )
        {
            pQuest = T::CreateInstance();
            if ( pQuest == NULL )
            { return NULL; }

            pQuest->Initialize( pPlayer );

            AddSpecialQuest( dwPlayerID, pQuest );
        }

        return pQuest;
    }
    
    void ShowSpecialQuestList( U* pPlayer, unsigned int dwPlayerID, unsigned int nNpcID )
    {
        T* pQuest = GetSpecialQuest( dwPlayerID, pPlayer );
        if ( pQuest == NULL )
        { return; }

        pQuest->ShowQuestList( nNpcID );
    }

    bool CanReceiveSpecialQuest( U* pPlayer, unsigned int dwPlayerID, unsigned int nNpcID, unsigned int nQuestID )
    {
        T* pQuest = GetSpecialQuest( dwPlayerID, pPlayer );
        if ( pQuest == NULL )
        { return false; }

        return pQuest->CanReceiveQuest( nNpcID, nQuestID );
    }

    void ReceiveSpecialQuest( U* pPlayer, unsigned int dwPlayerID, unsigned int nNpcID, unsigned int nQuestID )
    {
        T* pQuest = GetSpecialQuest( dwPlayerID, pPlayer );
        if ( pQuest == NULL )
        { return; }

        pQuest->ReceiveQuest( nNpcID, nQuestID );
    }

    void DoneSpecialQuest( U* pPlayer, unsigned int dwPlayerID, unsigned int nNpcID, unsigned int nQuestID )
    {
        T* pQuest = GetSpecialQuest( dwPlayerID, pPlayer );
        if ( pQuest == NULL )
        { return; }

        pQuest->DoneQuest( nNpcID, nQuestID );
    }

    void SaveSpecialQuest( unsigned int dwPlayerID )
    {
        T* pQuest = GetSpecialQuest( dwPlayerID );
        if ( pQuest == NULL )
        { return; }

        pQuest->SaveQuest();
    }

protected:
    SpecialQuestManager()
    {
        m_mapSpecialQuest.clear();
    }
private:
    SpecialQuestManager( const SpecialQuestManager< T, U >& );
    SpecialQuestManager< T, U >& operator = ( const SpecialQuestManager< T, U >& );

private:
    MapSpecialQuest m_mapSpecialQuest;        // 玩家的任务信息
};

// 定义
class PubQuestType
{
    enum EConstDefine
    {
        TypeValue = 1, // 酒馆和皇榜类型
    };
};

class ConQuestType
{
    enum EConstDefine
    {
        TypeValue = 2, // 征伐类型
    };
};

class GamePlayer;

typedef SpecialQuest< GamePlayer, PubQuestType > PubQuest;     // 酒馆和皇榜任务
typedef SpecialQuest< GamePlayer, ConQuestType > ConQuest;     // 征伐任务

#define thePubQuestManager SpecialQuestManager< PubQuest, GamePlayer >::Instance()              // 酒馆任务管理
#define theConQuestManager SpecialQuestManager< ConQuest, GamePlayer >::Instance()              // 征伐任务管理

#endif      // end if __SPECIALQUESTMANAGER_H__