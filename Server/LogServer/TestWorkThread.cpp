#include "TestWorkThread.h"
#include "logfileobjectnameex.h"
#include "tstring.h"


TestWorkThread::TestWorkThread(LogServerMySql* pOwn) : MySqlWorkThread(pOwn)
{
}

TestWorkThread::~TestWorkThread(void)
{
}

uint32 TestWorkThread::Update()
{
	// 保存基本的 Sql连接 和 Update
	if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
	{ return ER_Success; }

	unsigned long begintime = HQ_TimeGetTime();
	unsigned long count = 0;
	BaseLogMessage* pMessage = _LogMsgQueue.PopQuery();
	while ( pMessage != NULL)
	{
		switch( pMessage->_type )
		{
		case LOGMSG_BEGIN_TEST:
			{
				OnTestMsg(pMessage);
				count++;
			}
			break;
		default:
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "TestWorkThread::Update() MessageId[%d:%d] 没有处理函数", pMessage->_type, pMessage->GetMessageSize() );
			break;
		}
		theLogMessageManager.FreeLogMessage( pMessage );
		pMessage = _LogMsgQueue.PopQuery();
	}

	_CheckState();
	if (count > 0)
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Frame Info:time[%d]count[%d]!",HQ_TimeGetTime() - begintime,count);
	}
	return ER_Success;
}

void TestWorkThread::OnTestMsg(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageTestLogMessage* pDetailMesage = (LogMessageTestLogMessage*)pMessage;
	TestLogMessage* pTLM = &(pDetailMesage->msg);
	if (!pTLM)
	{
		return;
	}

	unsigned long begintime = HQ_TimeGetTime();

	static char szSql[ 1024 ] = {0};
	static char szEscape[128] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pTLM->_time.wYear, pTLM->_time.wMonth, 
			pTLM->_time.wDay,pTLM->_time.wHour, pTLM->_time.wMinute, pTLM->_time.wSecond);

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		//mysqlQuery.escape_string(szEscape,_tUTF8CHAR(pTLM->frondose),128); //聊天内容有特殊的字符,需要处理下
		strncpy_s( szSql, sizeof( szSql ), "insert into test (_date, accountid, characterid, frondose) values(%0q,%1,%2,%3q);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pTLM->account_id),mysqlpp::sql_int_unsigned(pTLM->character_id),_tUTF8CHAR(pTLM->frondose));
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测

	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Insert TestLogMessge CostTime:%d!",HQ_TimeGetTime() - begintime);
}