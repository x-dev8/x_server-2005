#include "MessageDefine.h"
#include "helper.h"
#include "DatabaseInterface.h"
#include "DatabaseClient.h"
#include "DatabaseServerApp.h"
#include "RoleDataCache.h"
#include "RunStatus.h"
//#include "NetApi.h"
#include "DetailWorkThread.h"
#include "ColorScreen.h"

static DatabaseInterface s_DBInterface;
static BOOL s_bDBWillShutDown = FALSE;

DatabaseInterface* GetDatabaseInterface()
{ return &s_DBInterface; }

void WorkThreadFun( void* lpVoid )
{
    DatabaseServerWorkThread* pThread = (DatabaseServerWorkThread*)lpVoid;
    
    pThread->Update();

    if( s_bDBWillShutDown )
        pThread->Stop();

    static const int nSleepTime = 1; //GetDatabaseServerApp()->m_bSleepTime;
    Sleep( nSleepTime );
}

DatabaseInterface::DatabaseInterface() : _pNormalWorkThread( 0 ), _pOrganizeWorkThread( 0 )
{
}

DatabaseInterface::~DatabaseInterface()
{
}

BOOL DatabaseInterface::LockQuery()
{
    m_csQuery.Lock();
    return TRUE;
}
BOOL DatabaseInterface::UnlockQuery()
{
    m_csQuery.Unlock();
    return TRUE;
}

BOOL DatabaseInterface::LockResult()
{
    m_csResult.Lock();
    return TRUE;
}

BOOL DatabaseInterface::UnlockResult()
{
    m_csResult.Unlock();
    return TRUE;
}

BOOL DatabaseInterface::PushSqlMessageQuery( BaseSqlMessage* pSqlMessage )
{
    LockQuery();
    _querys.push_back( pSqlMessage );
    UnlockQuery();
    return TRUE;
}

BOOL DatabaseInterface::PushMessage( Msg* pMsg, int32 nClientId )
{
    if ( pMsg->GetType() == MSG_PING )
    { // Ping��Ϣֱ�ӻ�
        MsgPingMsg msgPing;
        PushResult( nClientId, &msgPing );
        return TRUE;
    }

    BaseSqlMessage* pBaseSqlMessage = NULL;

    try
    {
        pBaseSqlMessage = theSqlMessageManager.GetSqlMessageByDbMsg( pMsg );
    }
    catch ( std::exception )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "�ڴ治��"); 
    	return FALSE;
    }

    if ( pBaseSqlMessage == NULL )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "�޴���ϢMessageId[%d] ��Ӧ��SqlMessage", pMsg->GetType() ); 
        return FALSE;
    }
    
    pBaseSqlMessage->nClientId = nClientId;
    pBaseSqlMessage->type      = pMsg->GetType();
    pBaseSqlMessage->time      = HQ_TimeGetTime();
    memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());
    PushSqlMessageQuery( pBaseSqlMessage );

    //////////////////////////////////////////////////////////////////////////
    //if ( pMsg->GetLength() >= DatabaseInterface::CD_BufferSizeResult )
    //{ LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "��Ϣ̫����MessageId[%d] Size[%d]", pMsg->GetType(), pMsg->GetLength()); }

    //BaseSqlMessage* pSqlMessage = DatabaseInterface::Query::CreateInstance();
    //if ( pQuery == NULL )
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "New Query ʧ��");
    //    return FALSE;
    //}

    //if ( pMsg->GetLength() > DatabaseInterface::CD_BufferSizeQuery )
    //{ 
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "��Ϣ̫���� [%d]", pMsg->GetLength() );
    //    return FALSE;
    //}
    //pQuery->nClientId = nClientId;
    //memcpy(pQuery->m_pBuffer, pMsg, pMsg->GetLength());
    //PushQuery( pQuery );
    return TRUE;
}

void DatabaseInterface::PushResult( int nClientId, Msg* pMsg )
{
    DatabaseInterface::Result* pResult = new DatabaseInterface::Result;
    if ( !pResult)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "DatabaseInterface::PushResult new Fail");
        return;
    }
    pResult->nClientId = nClientId;
    memcpy(pResult->byBuffer, pMsg, min(pMsg->GetLength(), (uint32)sizeof(pResult->byBuffer)));
    PushResult( pResult );
}

void DatabaseInterface::PushResult( Result* pResult )
{
    LockResult();
    m_vectorResult.push_back( pResult );
    UnlockResult();
}
void DatabaseInterface::Update()
{
    LockQuery();
    QueryContainer vectorQuery = _querys;
    _querys.clear();
    UnlockQuery();
    
    for( int i=0; i<vectorQuery.size(); ++i )
    {
        BaseSqlMessage* pMessage = vectorQuery[i];
        
        // theRand.rand32()%_workThread.size()
        //switch ( pMessage->type )
        //{
        //default:
            _pNormalWorkThread->PushQuery( pMessage );
        //    break;
        //}
    }
    
    LockResult();
    ResultContainer vectorResult = m_vectorResult;
    m_vectorResult.clear();
    UnlockResult();

    for( int i = 0; i<vectorResult.size(); ++i)
    {
        Result* pResult = vectorResult[i];
        if ( pResult == NULL )
        { continue; }

        DatabaseClient* pClient = *(GetDatabaseServerApp()->_DatabaseClient[pResult->nClientId]);/*(DatabaseClient*)GetDatabaseServerApp()->GetNodeMgr()->Find( pResult->nClientId )*/;
        if( pClient == NULL )
        {   
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "��ѯ������� DatabaseClient[%d] �Ѿ������� MessageType[%d]"
                , pResult->nClientId,  ((Msg*)pResult->byBuffer)->GetType());
            if ( pResult != NULL )
            { delete pResult;}
            continue;
        }

        // �ѽ������Դ���ͣ���������
        if ( pClient->GetConnector() ) 
        {
            Msg* pMessage = (Msg*)pResult->byBuffer;
            int nResult = pClient->GetConnector()->SendMsg( (Msg*)pResult->byBuffer );
            if ( nResult == -1 )
            {}
        }

        if ( pResult != NULL )
        { delete pResult; }
    }

    CheckExitCondition();
}

BOOL DatabaseInterface::Init()
{  
    // ���������߳� һ���߳���ԭ������sql
    _pNormalWorkThread = new NormalWorkThread;
    _pNormalWorkThread->SetThreadId( ECD_NormalWorkThread );
    _pNormalWorkThread->CreateThread( WorkThreadFun, _pNormalWorkThread );

    // һ���߳���������֯���sql
    _pOrganizeWorkThread = new OrganizeWorkThread;
    _pOrganizeWorkThread->SetThreadId( ECD_OrganizeWorkThread );
    _pOrganizeWorkThread->CreateThread( WorkThreadFun, _pOrganizeWorkThread );

    // ��ʼ������ṹ
    GetRoleDataCacheManager();
    return TRUE;
}

void DatabaseInterface::ShutDown()
{
	//���ر�Ӧ�ó��� vvx 2013.6.6
    //s_bDBWillShutDown = TRUE;
    
    if ( _pNormalWorkThread )
    {
        _pNormalWorkThread->StopThreadAndWaitDead();
        delete _pNormalWorkThread;
    }
    
    if ( _pOrganizeWorkThread )
    {
        _pOrganizeWorkThread->StopThreadAndWaitDead();
        delete _pOrganizeWorkThread;
    }
}

void DatabaseInterface::CheckExitCondition()
{
    if ( GetRunStatus().GetStatus() == DbRunStatus::RunStatus_PrepareStop)
    {
        if ( !_pNormalWorkThread->IsHaveTask() && !_pOrganizeWorkThread->IsHaveTask() )
        { 
            GetRunStatus().SetStatus( DbRunStatus::RunStatus_Stopped ); 
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "���������԰�ȫ�˳�" );
        }
    }
}
