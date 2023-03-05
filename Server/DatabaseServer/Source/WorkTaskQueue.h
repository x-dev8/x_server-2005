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
    void InsertSaveQueryToSaveList( BaseSqlMessage* pSqlMessage ); // ������洢SqlMessage�������У���������о��滻
    void CheckEnterWorld();
    void CheckStopEnterWorldWhenDBBusy();

protected:
    typedef std::map<uint32, BaseSqlMessage*> CharSaveInfoContainer;
    typedef CharSaveInfoContainer::iterator   ItrCharSaveInfoContainer;

    typedef std::list<BaseSqlMessage*> QueryContainer;
    typedef QueryContainer::iterator   ItrQueryContainer;

    QueryContainer        m_CharacterLoadQuery;  // ���ȼ���һ(�κ�ʱ�򶼻�����ִ�ж�ȡ)
    QueryContainer        m_CharacterEnterWorld; // ���ȼ��ڶ�
    QueryContainer        _querys;          // ���ȼ�����(��Ϊ�ⲿ�ֲ�����̫��ʱ)
    CharSaveInfoContainer m_CharacterSaves;      // ���ȼ�����(�������������Ȼ����Ҫ������Ϊ̫��ʱ��Ϊ������Ӱ�쵽��������ִ�� ���ȼ����)

    uint32 m_nSaveQueryTotalNum;   // ִ�й���Save��Ϣ������
    uint32 m_nSaveQueryMaxNum;     // SaveQuery�б������ﵽ���������
    uint32 m_nEnterWorldQueueSize; // ������Ϸ�Ķ��в�ѯ����
};

#endif // __DATABASESERVER_WORKTASKQUEUE_H__
