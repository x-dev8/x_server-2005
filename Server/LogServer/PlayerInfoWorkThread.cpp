#include "PlayerInfoWorkThread.h"
#include "logfileobjectnameex.h"
#include "tstring.h"

PlayerInfoWorkThread::PlayerInfoWorkThread(LogServerMySql* pOwn) : MySqlWorkThread(pOwn)
{

}

PlayerInfoWorkThread::~PlayerInfoWorkThread(void)
{

}

uint32 PlayerInfoWorkThread::Update()
{
	// 保存基本的 Sql连接 和 Update
	if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
	{ return ER_Success; }

	BaseLogMessage* pMessage = _LogMsgQueue.PopQuery();
	while ( pMessage != NULL)
	{
		switch( pMessage->_type )
		{
		case LOGMSG_INOUNTINFO:
			OnMsgPlayerInOut(pMessage);
			break;
		case LOGMSG_QUESTLOG:
			OnMsgPlayerQuest(pMessage);
			break;
		case LOGMSG_CURRENCY:
			OnMsgPlayerCurrency(pMessage);
			break;
		case LOGMSG_EXPLOG:
			OnMsgPlayerExp(pMessage);
			break;
		case LOGMSG_LEVCHANGE:
			OnMsgPlayerLevel(pMessage);
			break;
		case LOGMSG_MAILLOG:
			OnMsgPlayerMail(pMessage);
			break;
		default:
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PlayerInfoWorkThread::Update() MessageId[%d:%d] 没有处理函数", pMessage->_type, pMessage->GetMessageSize() );
			break;
		}

		theLogMessageManager.FreeLogMessage( pMessage );
		pMessage = _LogMsgQueue.PopQuery();
	}

	_CheckState();
	return ER_Success;
}

void PlayerInfoWorkThread::OnMsgPlayerInOut(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LPlayerInOutLog* pDetailMesage = (LogMessageGS2LPlayerInOutLog*)pMessage;
	GS2LPlayerInOutLog* pPlayerInfo = &(pDetailMesage->msg);
	if (!pPlayerInfo)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pPlayerInfo->logcommon._time.wYear, pPlayerInfo->logcommon._time.wMonth, pPlayerInfo->logcommon._time.wDay,pPlayerInfo->logcommon._time.wHour, pPlayerInfo->logcommon._time.wMinute, pPlayerInfo->logcommon._time.wSecond);	

#ifdef _TEST 
	LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO,"%s account[%u] character[%u] actiontype[%d]",szDateTime,pPlayerInfo->logcommon.account_id,pPlayerInfo->logcommon.character_id,pPlayerInfo->Logtype);
#endif

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t1001_client_connection(_date,accountid,characterid,char_name,ip,mac,actiontype,onlinetime,lev,country) values(%0q,%1,%2,%3q,%4q,%5q,%6,%7,%8,%9);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pPlayerInfo->logcommon.account_id),mysqlpp::sql_int_unsigned(pPlayerInfo->logcommon.character_id),
			              _tUTF8CHAR(pPlayerInfo->logcommon.chName) ,pPlayerInfo->IpAddr,pPlayerInfo->scMac,pPlayerInfo->Logtype,mysqlpp::sql_int_unsigned(pPlayerInfo->onlinetime),
			               mysqlpp::sql_smallint_unsigned(pPlayerInfo->lv),mysqlpp::sql_smallint_unsigned(pPlayerInfo->country));
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void PlayerInfoWorkThread::OnMsgPlayerQuest(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LQuestLog* pDetailMesage = (LogMessageGS2LQuestLog*)pMessage;
	GS2LQuestLog* pQuestlog = &(pDetailMesage->msg);
	if (!pQuestlog)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pQuestlog->logcommon._time.wYear, pQuestlog->logcommon._time.wMonth, pQuestlog->logcommon._time.wDay,pQuestlog->logcommon._time.wHour, pQuestlog->logcommon._time.wMinute, pQuestlog->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t3001_questlog(_date,accountid,characterid,char_name,questid) values(%0q,%1,%2,%3q,%4);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pQuestlog->logcommon.account_id),mysqlpp::sql_int_unsigned(pQuestlog->logcommon.character_id),_tUTF8CHAR(pQuestlog->logcommon.chName),mysqlpp::sql_int_unsigned(pQuestlog->questid));
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void PlayerInfoWorkThread::OnMsgPlayerCurrency(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LCurrencyLog* pDetailMesage = (LogMessageGS2LCurrencyLog*)pMessage;
	GS2LCurrencyLog* pCurrencyLog = &(pDetailMesage->msg);
	if (!pCurrencyLog)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pCurrencyLog->logcommon._time.wYear, pCurrencyLog->logcommon._time.wMonth, pCurrencyLog->logcommon._time.wDay,pCurrencyLog->logcommon._time.wHour, pCurrencyLog->logcommon._time.wMinute, pCurrencyLog->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t4001_currencylog (_date,accountid,characterid,char_name,currencytype,quantity,actiontype,sourcetype) values(%0q,%1,%2,%3q,%4,%5,%6,%7);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pCurrencyLog->logcommon.account_id),mysqlpp::sql_int_unsigned(pCurrencyLog->logcommon.character_id),_tUTF8CHAR(pCurrencyLog->logcommon.chName),pCurrencyLog->money_type,mysqlpp::sql_int(pCurrencyLog->count),pCurrencyLog->logtype,pCurrencyLog->sourcetype);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void PlayerInfoWorkThread::OnMsgPlayerExp(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LExpLog* pDetailMesage = (LogMessageGS2LExpLog*)pMessage;
	GS2LExpLog* pExpLog = &(pDetailMesage->msg);
	if (!pExpLog)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pExpLog->logcommon._time.wYear, pExpLog->logcommon._time.wMonth, pExpLog->logcommon._time.wDay,pExpLog->logcommon._time.wHour, pExpLog->logcommon._time.wMinute, pExpLog->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t5001_explog(_date,accountid,characterid,char_name,exp,actiontype,monsterid) values(%0q,%1,%2,%3q,%4,%5,%6);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pExpLog->logcommon.account_id),mysqlpp::sql_int_unsigned(pExpLog->logcommon.character_id),_tUTF8CHAR(pExpLog->logcommon.chName),mysqlpp::sql_int(pExpLog->_exp),
							pExpLog->logtype,mysqlpp::sql_int(pExpLog->monsterid));
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void PlayerInfoWorkThread::OnMsgPlayerLevel(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LLevelChange* pDetailMesage = (LogMessageGS2LLevelChange*)pMessage;
	GS2LLevelChange* pLv = &(pDetailMesage->msg);
	if (!pLv)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pLv->logcommon._time.wYear, pLv->logcommon._time.wMonth, pLv->logcommon._time.wDay,pLv->logcommon._time.wHour, pLv->logcommon._time.wMinute, pLv->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t5002_levchange(_date,accountid,characterid,char_name,previouslev,newlev) values(%0q,%1,%2,%3q,%4,%5);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pLv->logcommon.account_id),mysqlpp::sql_int_unsigned(pLv->logcommon.character_id),_tUTF8CHAR(pLv->logcommon.chName),pLv->previouslev,pLv->newlev);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void PlayerInfoWorkThread::OnMsgPlayerMail(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageS2LMailLog* pDetailMesage = (LogMessageS2LMailLog*)pMessage;
	S2LMailLog* pMail = &(pDetailMesage->msg);
	if (!pMail)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pMail->_time.wYear, pMail->_time.wMonth, pMail->_time.wDay,pMail->_time.wHour, pMail->_time.wMinute, pMail->_time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t6001_mail (_date,accountid,characterid,sender_name,recievercharid,recivever_name,mailtitle,content,itemid,item_name,quantity,money,itemguid) values(%0q,%1,%2,%3q,%4,%5q,%6q,%7q,%8,%9q,%10,%11,%12);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pMail->send_accid),mysqlpp::sql_int_unsigned(pMail->send_chid),_tUTF8CHAR(pMail->send_CharName),mysqlpp::sql_int_unsigned(pMail->recv_chid),_tUTF8CHAR(pMail->recv_CharName),
						   _tUTF8CHAR(pMail->mail_title),_tUTF8CHAR(pMail->mail_detail),mysqlpp::sql_smallint_unsigned(pMail->item_id),_tUTF8CHAR(pMail->ItemName),mysqlpp::sql_smallint_unsigned(pMail->item_count),
						   mysqlpp::sql_int_unsigned(pMail->money),mysqlpp::sql_bigint(pMail->item_Guid));
						   
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}