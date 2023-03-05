#include "MySqlWorkThread.h"
#include "GameTime.h"
#include "MySqlCommunication.h"

static void __cdecl ThreadFuncMysql( void *lpVoid )
{
    // mysqlpp::Connection::thread_start();

    CWorkThread* pThread = (CWorkThread*)lpVoid;
    if( pThread )
    {
        HANDLE hThread        = GetCurrentThread();
        pThread->SetThreadID( GetCurrentThreadId() );
        SetThreadPriority( hThread,pThread->GetThreadPriority() );
        while( true )
        {			
            // 退出线程
            if( pThread->IsStop() )
            {	
                pThread->SetDead();
                break;
            }
            pThread->RunOneStep();
        }
    }

    // mysqlpp::Connection::thread_end();

    _endthread();
}

MySqlWorkThread::MySqlWorkThread( MySqlCommunication* pOwn ) : _workState( SS_TryConnect ), _lastUpdateTime( 0 ), _pOwn( pOwn ), _pMysqlConnect( NULL )
{
}

MySqlWorkThread::~MySqlWorkThread()
{
    if ( _pMysqlConnect )
    { delete _pMysqlConnect;}

    if ( _mysqlConnectionPool )
    { delete _mysqlConnectionPool; }
}

bool MySqlWorkThread::CreateThread( t_fnThreadFuncOneStep fn,void *lpData /*= 0*/,int iPriority /*= THREAD_PRIORITY_NORMAL */)
{
    m_bStop = false;
    m_bPause = true;
    m_pThreadFunc = fn;
    uintptr_t hThread = _beginthread( ThreadFuncMysql,0,(void*)this );
    m_iPriority = iPriority;
    m_hThread = (HANDLE)hThread;
    if( -1 != hThread )
    {
        m_bStop = false;
        m_bDead = false;
        m_lpData = lpData;
        m_bPause = false;
        return true;
    }
    return false;
}

uint32 MySqlWorkThread::Init( const std::string& dbName, const std::string& host, uint16 port, 
                                 const std::string& user, const std::string& password, uint32 threadId )
{
    _dbName   = dbName;
    _host     = host;
    _port     = port;
    _user     = user;
    _password = password;
    _threadId = threadId;

    _mysqlConnectionPool = NULL;
    //_mysqlConnectionPool = new MysqlConnectionPoolEx( _dbName, _host, _port, _user, _password );
    //if ( _mysqlConnectionPool == NULL )
    //{ return  ER_NewNormalFail;}

    return ER_Success;
}

uint32 MySqlWorkThread::Update()
{
    if ( _workState != SS_Connected )
    { _TryConnectToSqlDb(); }

    if ( _workState != SS_Connected)
    { return ER_SqlNotConnected;}

    return ER_Success;
}

uint32 MySqlWorkThread::PushMessage( BaseSqlMessage* pMsg )
{
    return _dbMsgQueue.PushQuery( pMsg );
}

void MySqlWorkThread::_TryConnectToSqlDb()
{
    if ( _pMysqlConnect == NULL )
    {
        _pMysqlConnect = new mysqlpp::Connection();
        if ( _pMysqlConnect == NULL )
        { return;}

        //try 
        //{
        //    _pMysqlConnect = _mysqlConnectionPool->grab();
        //    if (!_pMysqlConnect->thread_aware()) 
        //    {
        //        std::cerr << "mysql++ wasn't built with thread awareness!  " << endl;
        //        return;
        //    }
        //    _mysqlConnectionPool->release(_pMysqlConnect);
        //    _pMysqlConnect = NULL;
        //}
        //catch (mysqlpp::Exception& e) 
        //{
        //    std::cerr << "Failed to set up initial pooled connection: " << e.what() << endl;
        //    return ;
        //}
    }

    switch ( _workState )
    {
    case SS_TryConnect:
    case SS_ReConnected:
        { // 启示没有必要这样重连, 连接池都是可用的连接
            _connectTime.StartTimer( HQ_TimeGetTime(), ECD_ConnectIntervalTime );
            if ( !_connectTime.DoneTimer( HQ_TimeGetTime() ))
            { return; }
                
            try
            {
                if ( _workState == SS_ReConnected)
                { 
					_pMysqlConnect->disconnect();
				}
                _pMysqlConnect->set_option(new mysqlpp::MultiStatementsOption(true));
                _pMysqlConnect->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
                bool ConnectOk = _pMysqlConnect->connect( _dbName.c_str(), _host.c_str(), _user.c_str(), _password.c_str(), _port );
                
                if ( !ConnectOk )
                { 
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"workstate[%d] Connect MySql [Error]", _workState);
                    return;
                }
                
                // 设置mysql超时为24小时
                mysqlpp::Query query =_pMysqlConnect->query("set interactive_timeout = 24*3600");
                query.execute();

                if ( _workState == SS_TryConnect)
                { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "WorkThread[%d] Connect MySql Success.", _threadId ); }
                else
                { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "WorkThread[%d] ReConnect MySql Success.", _threadId ); }

                _workState = SS_Connected; 
                
            }
            catch (exception& er)
            {
                 LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"WorkThread[%d] workstate[%d] Connect MySql Error:%s !", _threadId, _workState, er.what());
            }
        }
        break;
    }
}

bool MySqlWorkThread::_CheckState()
{    
    if (!_pMysqlConnect->connected())
    {
        _workState = SS_ReConnected;
        return false;
    }

    // 5分钟PING一次
    if ( _lastUpdateTime == 0)
    { _lastUpdateTime = HQ_TimeGetTime(); }

    if ( !GameTime::IsPassCurrentTime( _lastUpdateTime, ECD_PingTime ) )
    { return true; }

    _lastUpdateTime = HQ_TimeGetTime();
    if (! _pMysqlConnect->ping())
    {
        _workState = SS_ReConnected;
        return false;
    }

    return true;
}
