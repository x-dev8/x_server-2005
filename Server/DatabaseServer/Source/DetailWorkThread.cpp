#include "DetailWorkThread.h"

void NormalWorkThread::Update()
{
    DatabaseServerWorkThread::Update();

    _TryLoadGmInfo();

    if ( _connectState != MSS_Connected )
    { return; }

    uint32 nResult = ER_Success;

    BaseSqlMessage* pSqlMessage = m_taskqueue.PopQuery();
    while ( pSqlMessage != NULL )
    {
        switch( pSqlMessage->type )
        {
        case DBMSG_LOGIN:
            OnQueryLogin( pSqlMessage );
            break;
        case DBMSG_OFFLINE:
            OnQueryLogout( pSqlMessage );
            break;
        case DBMSG_CREATECHAR:
            OnQueryCreateChar( pSqlMessage );
            break;
        case DBMSG_REQ_CREATE_CHECKNAME:
            OnQueryCreateCheckName( pSqlMessage );
            break;
        case DBMSG_QUERYACCOUNTCHAR:
            nResult = OnQueryAccountChar( pSqlMessage );
            break;
        case DBMSG_ENTERWORD:
            nResult = OnQueryCharEnterWorld( pSqlMessage );
            break;
        case DBMSG_SAVECHARACTER:
            nResult = OnQuerySaveChar( pSqlMessage );
            break;
        case DBMSG_DELETECHAR:
            OnQueryDelChar( pSqlMessage );
            break;
        case DBMSG_CANCELDELCHAR:
            OnQueryCancelDelChar( pSqlMessage );
            break;
        case DBMSG_REQ_STORAGE:
            OnQueryStorage( pSqlMessage );
            break;
        default:
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "NormalWorkThread MessageId[%u] ClientId[%d] 没有处理函数", pSqlMessage->type, pSqlMessage->nClientId );
            break;
        }
        
        pSqlMessage->Release();
        if ( nResult == ER_SQLConnectionReset)
        { break; }

        pSqlMessage = m_taskqueue.PopQuery();
    }

    _CheckConnection();
}

bool OrganizeWorkThread::IsHaveTask()
{ 
    return m_taskqueue.GetOtherQueueSize() != 0;
}

void OrganizeWorkThread::Update()
{
    DatabaseServerWorkThread::Update();

    if ( _connectState != MSS_Connected )
    { return; }

    BaseSqlMessage* pSqlMessage = m_taskqueue.PopQuery();
    while (pSqlMessage != NULL)
    {
        //switch( pSqlMessage->type )
        //{

        //default:
        //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "OrganizeWorkThread MessageId[%d] Client[%d] 没有处理函数", pSqlMessage->type, pSqlMessage->nClientId );
        //    break;
        //}

        pSqlMessage->Release();
        pSqlMessage = m_taskqueue.PopQuery();
    }

    _CheckConnection();
}
