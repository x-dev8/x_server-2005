#include "OnlineInfoWorkThread.h"
#include "logfileobjectnameex.h"
#include "tstring.h"

OnlineInfoWorkThread::OnlineInfoWorkThread(LogServerMySql* pOwn) : MySqlWorkThread(pOwn)
{

}

OnlineInfoWorkThread::~OnlineInfoWorkThread(void)
{

}

uint32 OnlineInfoWorkThread::Update()
{
	// 保存基本的 Sql连接 和 Update
	if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
	{ return ER_Success; }

	BaseLogMessage* pMessage = _LogMsgQueue.PopQuery();
	while ( pMessage != NULL)
	{
		switch( pMessage->_type )
		{
		case LOGMSG_OnlineInfo:
			OnMsgOnlineInfo(pMessage);
			break;
		case LOGMSG_GMCOMMAND:
			OnMsgGMCommand(pMessage);
			break;
		/*case DBMSG_CREATECHAR:
			{				
				OnQueryCreateChar( pSqlMessage );				
			}
			break;*/
		default:
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "OnlineInfoWorkThread::Update() MessageId[%d:%d] 没有处理函数", pMessage->_type, pMessage->GetMessageSize() );
			break;
		}

		theLogMessageManager.FreeLogMessage( pMessage );
		pMessage = _LogMsgQueue.PopQuery();
	}

	_CheckState();
	return ER_Success;
}

void OnlineInfoWorkThread::OnMsgOnlineInfo(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageCS2LOnlineInfo* pDetailMesage = (LogMessageCS2LOnlineInfo*)pMessage;
	CS2LOnlineInfo* pOnlineInfo = &(pDetailMesage->msg);
	if (!pOnlineInfo)
	{
		return;
	}
	
	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pOnlineInfo->_time.wYear, pOnlineInfo->_time.wMonth, pOnlineInfo->_time.wDay,pOnlineInfo->_time.wHour, pOnlineInfo->_time.wMinute, pOnlineInfo->_time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into onlineinfo(login,normalquit,kickquit,total,frondose,date) values(%0,%1,%2,%3,%4q,%5q);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(pOnlineInfo->login,pOnlineInfo->normalquit,pOnlineInfo->kickquit,pOnlineInfo->total,_tUTF8CHAR(pOnlineInfo->frondose),szDateTime);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void OnlineInfoWorkThread::OnMsgGMCommand	(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LGMCommand* pDetailMesage = (LogMessageGS2LGMCommand*)pMessage;
	GS2LGMCommand* pGMCommand = &(pDetailMesage->msg);
	if (!pGMCommand)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pGMCommand->logcommon._time.wYear, pGMCommand->logcommon._time.wMonth, pGMCommand->logcommon._time.wDay,pGMCommand->logcommon._time.wHour, pGMCommand->logcommon._time.wMinute, pGMCommand->logcommon._time.wSecond);

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t8001_gmlog (_date,GMaccountid,GMcharid,GMname,Command,IPaddress) values(%0q,%1,%2,%3q,%4q,%5q);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pGMCommand->logcommon.account_id),mysqlpp::sql_int_unsigned(pGMCommand->logcommon.character_id),
						  _tUTF8CHAR(pGMCommand->name),_tUTF8CHAR(pGMCommand->frondose),pGMCommand->ipAddr);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}