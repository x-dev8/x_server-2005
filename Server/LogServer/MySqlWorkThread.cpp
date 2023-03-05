#include "MySqlWorkThread.h"
#include "ErrorCode.h"
#include "logfileobjectnameex.h"


static void __cdecl ThreadFuncMysql( void *lpVoid )
{
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
	_endthread();
}

MySqlWorkThread::MySqlWorkThread( LogServerMySql* pOwn ) : _workState( SS_TryConnect ), _lastUpdateTime( 0 ), _pOwn( pOwn ), _pMysqlConnect( NULL )
{
}

MySqlWorkThread::~MySqlWorkThread(void)
{
	if ( _pMysqlConnect )
	{ delete _pMysqlConnect;}
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

uint32 MySqlWorkThread::PushMessage( BaseLogMessage* pMsg )
{
	return _LogMsgQueue.PushQuery( pMsg );
}

void MySqlWorkThread::_TryConnectToSqlDb()
{
	if ( _pMysqlConnect == NULL )
	{
		_pMysqlConnect = new mysqlpp::Connection();
		if ( _pMysqlConnect == NULL )
		{ return;}
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
				{ _pMysqlConnect->disconnect();}
				_pMysqlConnect->set_option(new mysqlpp::MultiStatementsOption(true));
				_pMysqlConnect->set_option(new mysqlpp::SetCharsetNameOption("utf8"));

				bool ConnectOk = false;
				if ( _dbName.empty() )
				{ ConnectOk = _pMysqlConnect->connect( 0, _host.c_str(), _user.c_str(), _password.c_str(), _port ); }
				else
				{ ConnectOk = _pMysqlConnect->connect( _dbName.c_str(), _host.c_str(), _user.c_str(), _password.c_str(), _port ); }

				if ( !ConnectOk )
				{ 
					LOG_MESSAGE( SYSTEMOBJECT,LOG_PRIORITY_ERROR,"workstate[%d] Connect MySql [Error]", _workState);
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
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"WorkThread[%d] workstate[%d] Connect MySql Error:%s !", _threadId, _workState, er.what());
			}
		}
		break;
	}
}

bool MySqlWorkThread::_CheckState( bool bPing /*= true */)
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
	if ( bPing )
	{
		if ( !_pMysqlConnect->ping())
		{
			_workState = SS_ReConnected;
			return false;
		}
	}

	return true;
}

bool MySqlWorkThread::DBStore( SqlResult& xOutReuslt, const char* formatSql, ... )
{
	char szBuffer[ 1024 ] = { 0 };
	memset( szBuffer, 0, sizeof(szBuffer) );

	va_list args;
	va_start( args, formatSql );
	_vstprintf_s( szBuffer,sizeof(szBuffer), formatSql, args );
	va_end( args );

	uint32 result = ER_Success;
Repeat:
	try 
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();        
		xOutReuslt = mysqlQuery.store( szBuffer, strlen( szBuffer) );
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",szBuffer, errCode, er.what());
		result = ER_Failed;
		if (errCode == 2013 || errCode == 2006)
		{ result = ER_SystemException; }
	}
	catch (const mysqlpp::BadConversion& er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",szBuffer,er.what(), er.retrieved, er.actual_size);
		result = ER_Failed;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",szBuffer, er.what());
		result = ER_Failed;
	}
	catch(exception &er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",szBuffer, er.what());
		result = ER_Failed;
	}

	// 执行失败
	if ( RESULT_FAILED( result ) )
	{
		if ( result == ER_SystemException )
		{ // 如果是连接异常断开，需要恢复执行
			_workState = SS_ReConnected;
			while( _workState == SS_ReConnected )
			{
				_TryConnectToSqlDb();
				Sleep(1);
			}
			result = ER_Success;
			goto Repeat;
		}
		return false;
	}

	return true;
}

bool MySqlWorkThread::DBStoreT( SqlResult& xOutReuslt, const char* templateSql, SqlParams& xParams )
{
	uint32 result = ER_Success;
Repeat:
	try 
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		mysqlQuery << templateSql;
		mysqlQuery.parse();
		xOutReuslt = mysqlQuery.store( xParams );
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",templateSql, errCode, er.what());
		result = ER_Failed;
		if (errCode == 2013 || errCode == 2006)
		{ result = ER_SystemException; }
	}
	catch (const mysqlpp::BadConversion& er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",templateSql,er.what(), er.retrieved, er.actual_size);
		result = ER_Failed;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",templateSql, er.what());
		result = ER_Failed;
	}
	catch( std::exception &er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",templateSql, er.what());
		result = ER_Failed;
	}

	// 执行失败
	if ( RESULT_FAILED( result ) )
	{
		if ( result == ER_SystemException )
		{ // 如果是连接异常断开，需要恢复执行
			_workState = SS_ReConnected;
			while( _workState == SS_ReConnected )
			{
				_TryConnectToSqlDb();
				Sleep(1);
			}
			result = ER_Success;
			goto Repeat;
		}
		return false;
	}
	return true;
}

bool MySqlWorkThread::DBExecute ( const char* formatSql, ... )
{
	char szBuffer[ 1024 ] = { 0 };
	memset( szBuffer, 0, sizeof(szBuffer) );

	va_list args;
	va_start( args, formatSql );
	_vstprintf_s( szBuffer,sizeof(szBuffer), formatSql, args );
	va_end( args );

	uint32 result = ER_Success;
Repeat:
	try 
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();        
		mysqlQuery.execute( szBuffer, strlen( szBuffer) );
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",szBuffer, errCode, er.what());
		result = ER_Failed;
		if (errCode == 2013 || errCode == 2006)
		{ result = ER_SystemException; }
	}
	catch (const mysqlpp::BadConversion& er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",szBuffer,er.what(), er.retrieved, er.actual_size);
		result = ER_Failed;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",szBuffer, er.what());
		result = ER_Failed;
	}
	catch(exception &er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",szBuffer, er.what());
		result = ER_Failed;
	}

	// 执行失败
	if ( RESULT_FAILED( result ) )
	{
		if ( result == ER_SystemException )
		{ // 如果是连接异常断开，需要恢复执行
			_workState = SS_ReConnected;
			while( _workState == SS_ReConnected )
			{
				_TryConnectToSqlDb();
				Sleep(1);
			}
			result = ER_Success;
			goto Repeat;
		}
		return false;
	}

	return true;
}

bool MySqlWorkThread::DBExecuteT( const char* templateSql, SqlParams& xParams )
{
	uint32 result = ER_Success;
Repeat:
	try 
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		mysqlQuery << templateSql;
		mysqlQuery.parse();
		mysqlQuery.execute( xParams );
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",templateSql, errCode, er.what());
		result = ER_Failed;
		if (errCode == 2013 || errCode == 2006)
		{ result = ER_SystemException; }
	}
	catch (const mysqlpp::BadConversion& er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",templateSql,er.what(), er.retrieved, er.actual_size);
		result = ER_Failed;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",templateSql, er.what());
		result = ER_Failed;
	}
	catch( std::exception &er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",templateSql, er.what());
		result = ER_Failed;
	}

	// 执行失败
	if ( RESULT_FAILED( result ) )
	{
		if ( result == ER_SystemException )
		{ // 如果是连接异常断开，需要恢复执行
			_workState = SS_ReConnected;
			while( _workState == SS_ReConnected )
			{
				_TryConnectToSqlDb();
				Sleep(1);
			}
			result = ER_Success;
			goto Repeat;
		}
		return false;
	}
	return true;
}

bool MySqlWorkThread::DBCallSp( SqlResult& xOutReuslt, const char* formatSql, ... )
{
	char szBuffer[ 1024 ] = { 0 };
	memset( szBuffer, 0, sizeof(szBuffer) );

	va_list args;
	va_start( args, formatSql );
	_vstprintf_s( szBuffer,sizeof(szBuffer), formatSql, args );
	va_end( args );

	uint32 result = ER_Success;
Repeat:
	try 
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();        
		xOutReuslt = mysqlQuery.store( szBuffer, strlen( szBuffer) );

		while(mysqlQuery.more_results())
		{ mysqlQuery.store_next(); }

		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",szBuffer, errCode, er.what());
		result = ER_Failed;
		if (errCode == 2013 || errCode == 2006)
		{ result = ER_SystemException; }
	}
	catch (const mysqlpp::BadConversion& er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",szBuffer,er.what(), er.retrieved, er.actual_size);
		result = ER_Failed;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",szBuffer, er.what());
		result = ER_Failed;
	}
	catch(exception &er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",szBuffer, er.what());
		result = ER_Failed;
	}

	// 执行失败
	if ( RESULT_FAILED( result ) )
	{
		if ( result == ER_SystemException )
		{ // 如果是连接异常断开，需要恢复执行
			_workState = SS_ReConnected;
			while( _workState == SS_ReConnected )
			{
				_TryConnectToSqlDb();
				Sleep(1);
			}
			result = ER_Success;
			goto Repeat;
		}
		return false;
	}

	return true;
}

bool MySqlWorkThread::DBCallSpT( SqlResult& xOutReuslt, const char* templateSql, SqlParams& xParams )
{
	uint32 result = ER_Success;
Repeat:
	try 
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		mysqlQuery <<  templateSql;
		mysqlQuery.parse();
		xOutReuslt = mysqlQuery.store( xParams );

		while(mysqlQuery.more_results())
		{ mysqlQuery.store_next(); }

		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		int errCode = er.errnum();
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",templateSql, errCode, er.what());
		result = ER_Failed;
		if (errCode == 2013 || errCode == 2006)
		{ result = ER_SystemException; }
	}
	catch (const mysqlpp::BadConversion& er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",templateSql,er.what(), er.retrieved, er.actual_size);
		result = ER_Failed;
	}
	catch (const mysqlpp::Exception& er)
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",templateSql, er.what());
		result = ER_Failed;
	}
	catch(exception &er) 
	{
		LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",templateSql, er.what());
		result = ER_Failed;
	}

	// 执行失败
	if ( RESULT_FAILED( result ) )
	{
		if ( result == ER_SystemException )
		{ // 如果是连接异常断开，需要恢复执行
			_workState = SS_ReConnected;
			while( _workState == SS_ReConnected )
			{
				_TryConnectToSqlDb();
				Sleep(1);
			}
			result = ER_Success;
			goto Repeat;
		}
		return false;
	}

	return true;
}