#include "WorkTaskQueue.h"
#include "FuncPerformanceLog.h"
#include "logfileobjectnameex.h"

WorkTaskQueue::WorkTaskQueue()
{
}

WorkTaskQueue::~WorkTaskQueue()
{   
    while (!_querys.empty())
    {
        theLogMessageManager.FreeLogMessage( *_querys.begin() );
        _querys.erase(_querys.begin());
    }
}

bool WorkTaskQueue::PushQuery( BaseLogMessage* pSqlMessage )
{   
    if ( pSqlMessage == NULL )
    { return false; }

    CSALocker locker(this);

    _querys.push_back( pSqlMessage );

    //const uint32 limitCount = 2000;
    //if ( GetQueueSize() > limitCount || G_PrinfInfo == PRINTFQUEUESIZE )
    //{
    //    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"QueueSize:%d ", GetQueueSize());
    //    G_PrinfInfo = NOPRINT;
    //}
    return true;
}

BaseLogMessage* WorkTaskQueue::PopQuery()
{
    CSALocker locker(this);

    BaseLogMessage* pSqlMessage = NULL;
    
    if ( !_querys.empty() )
    {
        pSqlMessage = _querys.front();
        _querys.pop_front();
    }

    return pSqlMessage;
}
