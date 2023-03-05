#include "SystemInfoWorkThread.h"
#include "logfileobjectnameex.h"
#include "tstring.h"

SystemInfoWorkThread::SystemInfoWorkThread(LogServerMySql* pOwn) : MySqlWorkThread(pOwn)
{

}

SystemInfoWorkThread::~SystemInfoWorkThread(void)
{

}

uint32 SystemInfoWorkThread::Update()
{
	// 保存基本的 Sql连接 和 Update
	if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
	{ return ER_Success; }

	BaseLogMessage* pMessage = _LogMsgQueue.PopQuery();
	while ( pMessage != NULL)
	{
		switch( pMessage->_type )
		{
		case LOGMSG_GUILDLOG:
			OnMsgGuild(pMessage);
			break;
		case LOGMSG_GUILDDETAIL:
			OnMsgGuildDetail(pMessage);
			break;
		case LOGMSG_CHATINFO:
			OnMsgChatInfo(pMessage);
			break;
		default:
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "SystemInfoWorkThread::Update() MessageId[%d:%d] 没有处理函数", pMessage->_type, pMessage->GetMessageSize() );
			break;
		}
		theLogMessageManager.FreeLogMessage( pMessage );
		pMessage = _LogMsgQueue.PopQuery();
	}

	_CheckState();
	return ER_Success;
}

void SystemInfoWorkThread::OnMsgGuild(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageS2LGuildLog* pDetailMesage = (LogMessageS2LGuildLog*)pMessage;
	S2LGuildLog* pGuild = &(pDetailMesage->msg);
	if (!pGuild)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pGuild->logcommon._time.wYear, 
			pGuild->logcommon._time.wMonth, pGuild->logcommon._time.wDay,pGuild->logcommon._time.wHour, 
			pGuild->logcommon._time.wMinute, pGuild->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t7001_guild (_date,accountid,characterid,char_name,guildid,actiontype) values(%0q,%1,%2,%3q,%4,%5);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pGuild->logcommon.account_id),mysqlpp::sql_int_unsigned(pGuild->logcommon.character_id),
			      _tUTF8CHAR(pGuild->logcommon.chName),mysqlpp::sql_int_unsigned(pGuild->guild_id),pGuild->logtype);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void SystemInfoWorkThread::OnMsgGuildDetail(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageS2LGuildDetailLog* pDetailMesage = (LogMessageS2LGuildDetailLog*)pMessage;
	S2LGuildDetailLog* pGuildDetail = &(pDetailMesage->msg);
	if (!pGuildDetail)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pGuildDetail->logcommon._time.wYear, 
		pGuildDetail->logcommon._time.wMonth, pGuildDetail->logcommon._time.wDay,pGuildDetail->logcommon._time.wHour, 
		pGuildDetail->logcommon._time.wMinute, pGuildDetail->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t7002_guilddetail (_date,accountid,characterid,char_name,moneychange,expchange,missionchange,guildid)	values(%0q,%1,%2,%3q,%4,%5,%6,%7);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pGuildDetail->logcommon.account_id),mysqlpp::sql_int_unsigned(pGuildDetail->logcommon.character_id),_tUTF8CHAR(pGuildDetail->logcommon.chName),
			mysqlpp::sql_int_unsigned(pGuildDetail->moneychange),mysqlpp::sql_int_unsigned(pGuildDetail->expchange),mysqlpp::sql_int_unsigned(pGuildDetail->missionchange),mysqlpp::sql_int_unsigned(pGuildDetail->guild_id));
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void SystemInfoWorkThread::OnMsgChatInfo(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LChatInfo* pDetailMesage = (LogMessageGS2LChatInfo*)pMessage;
	GS2LChatInfo* pChatInfo = &(pDetailMesage->msg);
	if (!pChatInfo)
	{
		return;
	}
	
	static char szSql[ 1024 ] = {0};
	static char szEscape[500] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pChatInfo->logcommon._time.wYear, 
		pChatInfo->logcommon._time.wMonth, pChatInfo->logcommon._time.wDay,pChatInfo->logcommon._time.wHour, 
		pChatInfo->logcommon._time.wMinute, pChatInfo->logcommon._time.wSecond);

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		//mysqlQuery.escape_string(szEscape,_tUTF8CHAR(pChatInfo->content),500); //聊天内容有特殊的字符,需要处理下
		strncpy_s( szSql, sizeof( szSql ), "insert into t9001_chatlog (_date,senderid,sender_name,recieverid,reciver_name,content,type) values(%0q,%1,%2q,%3,%4q,%5q,%6);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,/*mysqlpp::sql_int_unsigned(pChatInfo->logcommon.account_id),*/mysqlpp::sql_int_unsigned(pChatInfo->logcommon.character_id),_tUTF8CHAR(pChatInfo->logcommon.chName),
							mysqlpp::sql_int_unsigned(pChatInfo->target_id),_tUTF8CHAR(pChatInfo->TargetCharName),_tUTF8CHAR(pChatInfo->content),pChatInfo->chat_type);
		mysqlQuery.reset();
		trans.commit();
		
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}