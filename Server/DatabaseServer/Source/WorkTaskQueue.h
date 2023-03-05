/********************************************************************
    Filename:     WorkTaskQueue.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASESERVER_WORKTASKQUEUE_H__
#define __DATABASESERVER_WORKTASKQUEUE_H__

#include "MeRTLibsServer.h"
#include "Mutex.h"
#include "SqlMessages.h"

class WorkTaskQueue : public CSemiAutoIntLock
{
public:
    WorkTaskQueue();
    virtual ~WorkTaskQueue();

    bool            PushQuery( BaseSqlMessage* pSqlMessage);
    BaseSqlMessage* PopQuery();    
    BaseSqlMessage* GetSaveQueryByCharDbId( uint32 charDbid );

    uint32 GetCharacterLoadQuery() { return (uint32)m_CharacterLoadQuery.size();}
    uint32 GetEnterWorldQueueSize(){ return (uint32)m_nEnterWorldQueueSize;     }
    uint32 GetOtherQueueSize()     { return (uint32)_querys.size();             }
    uint32 GetSaveQueueSize()      { return (uint32)m_CharacterSaves.size();    }
    uint32 GetSaveQueryTotalNum()  { return m_nSaveQueryTotalNum;               }
    uint32 GetSaveQueryMaxNum()    { return m_nSaveQueryMaxNum;                 }

protected:
    void InsertSaveQueryToSaveList( BaseSqlMessage* pSqlMessage ); // 插人物存储SqlMessage到队列中，如果队列中就替换
    void CheckEnterWorld();
    void CheckStopEnterWorldWhenDBBusy();

protected:
    typedef std::map<uint32, BaseSqlMessage*> CharSaveInfoContainer;
    typedef CharSaveInfoContainer::iterator   ItrCharSaveInfoContainer;

    typedef std::list<BaseSqlMessage*> QueryContainer;
    typedef QueryContainer::iterator   ItrQueryContainer;

    QueryContainer        m_CharacterLoadQuery;  // 优先级第一(任何时候都会优先执行读取)
    QueryContainer        m_CharacterEnterWorld; // 优先级第二
    QueryContainer        _querys;          // 优先级第三(因为这部分操作不太耗时)
    CharSaveInfoContainer m_CharacterSaves;      // 优先级第四(保存玩家数据虽然很重要，但因为太耗时，为尽量少影响到其他队列执行 优先级最低)

    uint32 m_nSaveQueryTotalNum;   // 执行过的Save消息总数量
    uint32 m_nSaveQueryMaxNum;     // SaveQuery列表曾经达到的最大数量
    uint32 m_nEnterWorldQueueSize; // 进入游戏的队列查询个数
};

#endif // __DATABASESERVER_WORKTASKQUEUE_H__
