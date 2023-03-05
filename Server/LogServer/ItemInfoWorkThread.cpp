#include "ItemInfoWorkThread.h"
#include "logfileobjectnameex.h"
#include "tstring.h"

ItemInfoWorkThread::ItemInfoWorkThread(LogServerMySql* pOwn) : MySqlWorkThread(pOwn)
{

}

ItemInfoWorkThread::~ItemInfoWorkThread(void)
{

}

uint32 ItemInfoWorkThread::Update()
{
	// 保存基本的 Sql连接 和 Update
	if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
	{ return ER_Success; }

	BaseLogMessage* pMessage = _LogMsgQueue.PopQuery();
	while ( pMessage != NULL)
	{
		switch( pMessage->_type )
		{
		case LOGMSG_ITEMGAIN:
			OnMsgItemGain(pMessage);
			break;
		case LOGMSG_ITEMTRADE:
			OnMsgItemTrade(pMessage);
			break;
		case LOGMSG_ITEMCONSUME:
			OnMsgItemConsume(pMessage);
			break;
		case LOGMSG_ITEMUPGRADE:
			OnMsgItemUpgrade(pMessage);
			break;
		/*case DBMSG_CREATECHAR:
			{
				OnQueryCreateChar( pSqlMessage );				
			}
			break;*/
		default:
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "ItemInfoWorkThread::Update() MessageId[%d:%d] 没有处理函数", pMessage->_type, pMessage->GetMessageSize() );
			break;
		}

		theLogMessageManager.FreeLogMessage( pMessage );
		pMessage = _LogMsgQueue.PopQuery();
	}

	_CheckState();
	return ER_Success;
}

void ItemInfoWorkThread::OnMsgItemGain(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LItemGain* pDetailMesage = (LogMessageGS2LItemGain*)pMessage;
	GS2LItemGain* pItemGain = &(pDetailMesage->msg);
	if (!pItemGain)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pItemGain->logcommon._time.wYear, pItemGain->logcommon._time.wMonth, pItemGain->logcommon._time.wDay,pItemGain->logcommon._time.wHour, pItemGain->logcommon._time.wMinute, pItemGain->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t2001_item_gain(_date,accountid,characterid,char_name,itemid,item_name,itemguid,quantity,actiontype) values(%0q,%1,%2,%3q,%4,%5q,%6,%7,%8);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pItemGain->logcommon.account_id),mysqlpp::sql_int_unsigned(pItemGain->logcommon.character_id),_tUTF8CHAR(pItemGain->logcommon.chName),
							mysqlpp::sql_smallint_unsigned(pItemGain->logitem.item_id),_tUTF8CHAR(pItemGain->logitem.ItemName),mysqlpp::sql_bigint(pItemGain->logitem.item_guid),
							mysqlpp::sql_smallint_unsigned(pItemGain->logitem.item_count),pItemGain->logtype);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测

}

void ItemInfoWorkThread::OnMsgItemTrade(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LItemTrade* pDetailMesage = (LogMessageGS2LItemTrade*)pMessage;
	GS2LItemTrade* pItemTrade = &(pDetailMesage->msg);
	if (!pItemTrade)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pItemTrade->_time.wYear, pItemTrade->_time.wMonth, pItemTrade->_time.wDay,pItemTrade->_time.wHour, pItemTrade->_time.wMinute, pItemTrade->_time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t2002_item_trade(_date,buyeraccid,buyercharid,buyer_name,itemid,item_name,itemguid,quantity,selleraccid,sellercharid,seller_name,actiontype,cost) values(%0q,%1,%2,%3q,%4,%5q,%6,%7,%8,%9,%10q,%11,%12);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pItemTrade->buyer_accid),mysqlpp::sql_int_unsigned(pItemTrade->buyer_chaid),_tUTF8CHAR(pItemTrade->buyerName),
			mysqlpp::sql_smallint_unsigned(pItemTrade->logitem.item_id),_tUTF8CHAR(pItemTrade->logitem.ItemName),mysqlpp::sql_bigint(pItemTrade->logitem.item_guid),mysqlpp::sql_smallint_unsigned(pItemTrade->logitem.item_count),
			mysqlpp::sql_int_unsigned(pItemTrade->seller_accid),mysqlpp::sql_int_unsigned(pItemTrade->seller_chaid),_tUTF8CHAR(pItemTrade->sellerName),pItemTrade->logtype,mysqlpp::sql_int_unsigned(pItemTrade->item_cost));
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void ItemInfoWorkThread::OnMsgItemConsume(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LItemConsume* pDetailMesage = (LogMessageGS2LItemConsume*)pMessage;
	GS2LItemConsume* pItemConsume = &(pDetailMesage->msg);
	if (!pItemConsume)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pItemConsume->logcommon._time.wYear, pItemConsume->logcommon._time.wMonth, pItemConsume->logcommon._time.wDay,pItemConsume->logcommon._time.wHour, pItemConsume->logcommon._time.wMinute, pItemConsume->logcommon._time.wSecond);	

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t2003_item_consume(_date,accountid,characterid,char_name,itemid,item_name,itemguid,quantity,lave_count,actiontype) values(%0q,%1,%2,%3q,%4,%5q,%6,%7,%8,%9);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pItemConsume->logcommon.account_id),mysqlpp::sql_int_unsigned(pItemConsume->logcommon.character_id),_tUTF8CHAR(pItemConsume->logcommon.chName),
			mysqlpp::sql_smallint_unsigned(pItemConsume->logitem.item_id),_tUTF8CHAR(pItemConsume->logitem.ItemName),mysqlpp::sql_bigint(pItemConsume->logitem.item_guid),
			mysqlpp::sql_smallint_unsigned(pItemConsume->logitem.item_count),mysqlpp::sql_smallint_unsigned(pItemConsume->item_LaveCount),pItemConsume->logtype);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}

void ItemInfoWorkThread::OnMsgItemUpgrade(BaseLogMessage* pMessage)
{
	if (!pMessage)
	{
		return;
	}
	LogMessageGS2LItemUpgrade* pDetailMesage = (LogMessageGS2LItemUpgrade*)pMessage;
	GS2LItemUpgrade* pItemUpgrade = &(pDetailMesage->msg);
	if (!pItemUpgrade)
	{
		return;
	}

	static char szSql[ 1024 ] = {0};
	memset( szSql, 0, sizeof(szSql) );
	uint32 result = ER_Success;

	char szDateTime[256] = {0};
	_snprintf(szDateTime, sizeof(szDateTime)-1, "%04d-%02d-%02d %02d:%02d:%02d",pItemUpgrade->logcommon._time.wYear, pItemUpgrade->logcommon._time.wMonth, pItemUpgrade->logcommon._time.wDay,pItemUpgrade->logcommon._time.wHour, pItemUpgrade->logcommon._time.wMinute, pItemUpgrade->logcommon._time.wSecond);	
	
	char szPrevious[256] = {0};
	char szCurrent[256] = {0};
	_snprintf(szPrevious, sizeof(szPrevious)-1, "%d-%d-%d-%d-%d-%d-%d",pItemUpgrade->previous[0],pItemUpgrade->previous[1],pItemUpgrade->previous[2],pItemUpgrade->previous[3],pItemUpgrade->previous[4],pItemUpgrade->previous[5],pItemUpgrade->previous[6]);
	_snprintf(szCurrent, sizeof(szCurrent)-1, "%d-%d-%d-%d-%d-%d-%d",pItemUpgrade->current[0],pItemUpgrade->current[1],pItemUpgrade->current[2],pItemUpgrade->current[3],pItemUpgrade->current[4],pItemUpgrade->current[5],pItemUpgrade->current[6]);

	TRYBEGIN
	{
		mysqlpp::Transaction trans(*_pMysqlConnect); // 开始事务处理
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();		
		strncpy_s( szSql, sizeof( szSql ), "insert into t2005_item_upgrade (_date,accountid,characterid,char_name,itemid,item_name,itemguid,quantity,result,previous,current,actiontype) values(%0q,%1,%2,%3q,%4,%5q,%6,%7q,%8,%9q,%10q,%11);", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(szDateTime,mysqlpp::sql_int_unsigned(pItemUpgrade->logcommon.account_id),mysqlpp::sql_int_unsigned(pItemUpgrade->logcommon.character_id),_tUTF8CHAR(pItemUpgrade->logcommon.chName),
			mysqlpp::sql_smallint_unsigned(pItemUpgrade->logitem.item_id),_tUTF8CHAR(pItemUpgrade->logitem.ItemName),mysqlpp::sql_bigint(pItemUpgrade->logitem.item_guid),mysqlpp::sql_smallint_unsigned(pItemUpgrade->logitem.item_count),
			pItemUpgrade->result,szPrevious,szCurrent,pItemUpgrade->logtype);
		mysqlQuery.reset();
		trans.commit();
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // 执行检测
}