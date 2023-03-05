#ifndef __LOGSERVER_WORKTASKQUEUE_H__
#define __LOGSERVER_WORKTASKQUEUE_H__

#include "MeRTLibsServer.h"
#include "Mutex.h"
#include "LogMessager.h"

class WorkTaskQueue : public CSemiAutoIntLock
{
public:
    WorkTaskQueue();
    virtual ~WorkTaskQueue();

    bool            PushQuery( BaseLogMessage* pSqlMessage);
    BaseLogMessage* PopQuery();
    uint32          GetQueueSize(){ return (uint32)_querys.size(); }

protected:
    typedef std::map<uint32, BaseLogMessage*> CharSaveInfoContainer;
    typedef CharSaveInfoContainer::iterator   ItrCharSaveInfoContainer;

    typedef std::list<BaseLogMessage*> QueryContainer;
    typedef QueryContainer::iterator   ItrQueryContainer;

    QueryContainer _querys; // 
};

#endif // __CENTERSERVER_WORKTASKQUEUE_H__
