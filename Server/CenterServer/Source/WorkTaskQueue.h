/********************************************************************
    Filename:     WorkTaskQueue.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_WORKTASKQUEUE_H__
#define __CENTERSERVER_WORKTASKQUEUE_H__

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
    uint32          GetQueueSize(){ return (uint32)_querys.size(); }

protected:
    typedef std::map<uint32, BaseSqlMessage*> CharSaveInfoContainer;
    typedef CharSaveInfoContainer::iterator   ItrCharSaveInfoContainer;

    typedef std::list<BaseSqlMessage*> QueryContainer;
    typedef QueryContainer::iterator   ItrQueryContainer;

    QueryContainer _querys; // 
};

#endif // __CENTERSERVER_WORKTASKQUEUE_H__
