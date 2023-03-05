#include "NormalLogicWorkThread.h"
#include "tstring.h"
#include "MySqlCommunication.h"


void NormalLogicWorkThread::LoadLevelLimit(BaseSqlMessage* pSqlMessage)
{
	/////////////////////////////////////////////////
	short count = 0;
	char szSql2[ 512 ] = { 0 };
	memset( szSql2, 0,sizeof( szSql2 ) );	
	sprintf_s( szSql2, sizeof( szSql2 ) - 1, "select count(*) from level_limit;" );
	mysqlpp::Query mysqlQuery2 = _pMysqlConnect->query( szSql2 );
	mysqlpp::StoreQueryResult res2 = mysqlQuery2.store();
	if (res2&&!res2.empty())
	{
		for (int i = 0; i < res2.num_rows(); ++i )
		{
			count = res2[i]["count(*)"];
		}		
	}	
	/////////////////////////////////////////////////
	short max_level = 0;
	if (count > 0)
	{
		char szSql1[ 512 ] = { 0 };
		memset( szSql1, 0,sizeof( szSql1 ) );	
		sprintf_s( szSql1, sizeof( szSql1 ) - 1, "select MAX(level) from level_limit;" );
		mysqlpp::Query mysqlQuery1 = _pMysqlConnect->query( szSql1 );
		mysqlpp::StoreQueryResult res1 = mysqlQuery1.store();
		if (res1&&!res1.empty())
		{
			for (int i = 0; i < res1.num_rows(); ++i )
			{
				max_level = res1[i]["MAX(level)"];
			}		
		}
	}	
	/////////////////////////////////////////////////
	char szSql[ 512 ] = { 0 };
	memset( szSql, 0,sizeof( szSql ) );
	uint32 result = ER_Success;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select * from level_limit;" );

	MsgAckMySQLData ackdata;
	ackdata.max_level = max_level;
	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if ( res && !res.empty() )
	{
		SLevelLimitInfo xData;

		for (int i = 0; i < res.num_rows(); ++i )
		{
			xData.level         = res[i]["level"];
			if (max_level != 0 && xData.level != max_level)
			{
				continue;
			}
			xData.active_time      = res[i]["active_time"];
			xData.done_time      = res[i]["done_time"];
			xData.player_count  = res[i]["player_count"];
			xData.next_level    = res[i]["next_level"];
			xData.state         = res[i]["state"];
			Common::_tstring strRemark;
			strRemark.fromUTF8( res[i]["active_name"] );
			strncpy_s( xData.active_name, sizeof( xData.active_name ), strRemark.c_str(), sizeof( xData.active_name ) - 1 );

			ackdata.AddData( xData );
			if ( ackdata.IsFull() )
			{
				theMysqlCommunication.PushAckMessage( &ackdata, pSqlMessage->nClientId );
				ackdata.Reset();
			}
		}
	}
	TRYEND

	CHECK_SQL_RESULT( result ) // Ö´ÐÐ¼ì²â
	theMysqlCommunication.PushAckMessage( &ackdata, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::AddLevelLimit(BaseSqlMessage* pSqlMessage)
{
	MsgAddLevelLimit *pReq = static_cast< MsgAddLevelLimit* >( pSqlMessage->GetMessageAddress() );

	uint32 result = ER_Success;
	char szSql[ 512 ] = { 0 };
	strncpy_s(szSql, sizeof( szSql ), "insert into level_limit(level,active_time,done_time,player_count,next_level,state)values(%0,%1,%2,%3,%4,%5);", sizeof( szSql ) - 1 );

	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
	mysqlQuery << szSql;
	mysqlQuery.parse();
	mysqlQuery.execute(pReq->sllinfo.level, mysqlpp::sql_int_unsigned(pReq->sllinfo.active_time),mysqlpp::sql_int_unsigned( pReq->sllinfo.done_time),
		               pReq->sllinfo.player_count,pReq->sllinfo.next_level,pReq->sllinfo.state);
	mysqlQuery.reset();
	TRYEND
}

void NormalLogicWorkThread::UpdateLevelLimit(BaseSqlMessage* pSqlMessage)
{
	MsgUpdateLevelLimit *pReq = static_cast< MsgUpdateLevelLimit* >( pSqlMessage->GetMessageAddress() );
	char szSql[ 512 ] = { 0 };
	sprintf_s( szSql, sizeof( szSql ) - 1, 
		"update level_limit set active_time = '%d',done_time = '%d',\
		 player_count ='%d',next_level = '%d',state = '%d',active_name = '%s'\
		 where level = '%d' ;",
		pReq->sllinfo.active_time,pReq->sllinfo.done_time,pReq->sllinfo.player_count,pReq->sllinfo.next_level,
		pReq->sllinfo.state,_tUTF8CHAR(pReq->sllinfo.active_name),pReq->sllinfo.level);
	uint32 result = ER_Success;
	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
	mysqlQuery.execute( szSql );
	mysqlQuery.reset();
	TRYEND
}