#include "NormalLogicWorkThread.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "zlib/zlib.h"


void NormalLogicWorkThread::OnFamilyDataLoadReq( BaseSqlMessage* pSqlMessage )
{
	LoadFamilyData( pSqlMessage );
	LoadFamilyMember( pSqlMessage );
}

void NormalLogicWorkThread::LoadFamilyData( BaseSqlMessage* pSqlMessage )
{
	char szSql[ 512 ] = { 0 };
	memset( szSql, 0,sizeof( szSql ) );
	uint32 result = ER_Success;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select * from family;" );

	DB2CSFamilyDataList xList;  

	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if ( res && !res.empty() )
	{
		FamilyDefine::ServerFamilyInfo xData;

		for (int i = 0; i < res.num_rows(); ++i )
		{
			xData.SetFamilyID( res[i]["id"] );

			Common::_tstring strName;
			strName.fromUTF8( res[i]["name"] );
			xData.SetFamilyName( strName.c_str() );

			Common::_tstring strNotice;
			strNotice.fromUTF8( res[i]["notice"] );
			xData.SetFamilyAim( strNotice.c_str() );

			Common::_tstring strAim;
			strAim.fromUTF8( res[i]["aim"] );
			xData.SetFamilyAim( strAim.c_str() );

			xData.SetFamilyLevel( res[i]["level"] );
			xData.SetFamilyTotem( res[i]["totem"] );
			xData.SetLeaderID( res[i]["leader"] );
			xData.SetMoney( res[i]["money"] );
			xData.SetProsperity( res[i]["prosperity"] );
			xData.SetDisbandTime( res[i]["disbandtime"] );
			xData.SetLastChangeAimTime( res[i]["changeaimtime"] );

			if ( xList.AddFamilyInfo( xData ) == false )
			{
				theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId );
				xList.Reset();
				xList.AddFamilyInfo( xData );
			}
		}
	}
	TRYEND

		CHECK_SQL_RESULT( result ) // 执行检测
		theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::LoadFamilyMember( BaseSqlMessage* pSqlMessage )
{
	char szSql[ 512 ] = { 0 };
	memset( szSql, 0,sizeof( szSql ) );
	uint32 result = ER_Success;
	sprintf_s( szSql, sizeof( szSql ) - 1, "select * from familymember;" );

	DB2CSFamilyMemberList xList;  

	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if ( res && !res.empty() )
	{
		FamilyDefine::FamilyMember xMember;

		for (int i = 0; i < res.num_rows(); ++i )
		{
			xMember.SetID( res[i]["id"] );

			Common::_tstring strName;
			strName.fromUTF8( res[i]["name"] );
			xMember.SetName( strName.c_str() );

			xMember.SetLevel( res[i]["level"] );
			xMember.SetProfession( res[i]["profession"] );
			xMember.SetPosition( res[i]["position"] );
			xMember.SetFamilyID( res[i]["familyid"] );
			xMember.SetDonateMoney( res[i]["donatemoney"] );

			if ( xList.AddMember( xMember ) == false )
			{
				xList.bTheLastPack = false;
				theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId );
				xList.Reset();
				xList.AddMember( xMember );
			}
		}
	}
	TRYEND

		CHECK_SQL_RESULT( result ) // 执行检测
		theMysqlCommunication.PushAckMessage( &xList, pSqlMessage->nClientId ); 
}

void NormalLogicWorkThread::OnFamilyDataUpdateReq( BaseSqlMessage* pSqlMessage )
{
	CS2DBFamilyDataUpdateReq *pReq = static_cast< CS2DBFamilyDataUpdateReq* >( pSqlMessage->GetMessageAddress() );

	char szSql[ 512 ] = { 0 };
	sprintf_s( szSql, sizeof( szSql ) - 1, "select id from family where id=%ld;", pReq->info.GetFamilyID() );

	uint32 result = ER_Success;
	bool bIsExist = false;

	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if ( res && !res.empty() )
	{ bIsExist = true; }
	mysqlQuery.reset();
	TRYEND

		if ( !bIsExist )        // 存在
		{
			memset( szSql, 0, sizeof( szSql ) );
			strncpy_s( szSql, sizeof( szSql ), "insert into family(id,name,level,leader,money,prosperity,totem,aim,notice,disbandtime,changeaimtime) values(%0,%1q,%2,%3,%4,%5,%6,%7q,%8q,%9,%10);", sizeof( szSql ) - 1 );

			TRYBEGIN
				mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery << szSql;
			mysqlQuery.parse();
			mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->info.GetFamilyID() ), _tUTF8CHAR( pReq->info.GetFamilyName() ), pReq->info.GetFamilyLevel(),
				mysqlpp::sql_int_unsigned( pReq->info.GetLeaderID() ), mysqlpp::sql_int_unsigned( pReq->info.GetMoney() ),mysqlpp::sql_int_unsigned( pReq->info.GetProsperity() ),
				mysqlpp::sql_int_unsigned( pReq->info.GetFamilyTotem() ),_tUTF8CHAR( pReq->info.GetFamilyAim() ),_tUTF8CHAR( pReq->info.GetFamilyNotice() ),
				pReq->info.GetDisbandTime() ,pReq->info.GetLastChangeAimTime() );
			mysqlQuery.reset();
			TRYEND
		}
		else        // 已经存在就更新
		{
			memset( szSql, 0, sizeof( szSql ) );
			strncpy_s( szSql, sizeof( szSql ), "update family set name=%1q,level=%2,leader=%3,money=%4,prosperity=%5,totem=%6,aim=%7q,notice=%8q,disbandtime=%9,changeaimtime=%10 where id=%0;", sizeof( szSql ) - 1 );

			TRYBEGIN
				mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery << szSql;
			mysqlQuery.parse();
			mysqlQuery.execute( mysqlpp::sql_int_unsigned( pReq->info.GetFamilyID() ), _tUTF8CHAR( pReq->info.GetFamilyName() ), pReq->info.GetFamilyLevel(),
				mysqlpp::sql_int_unsigned( pReq->info.GetLeaderID() ), mysqlpp::sql_int_unsigned( pReq->info.GetMoney() ),mysqlpp::sql_int_unsigned( pReq->info.GetProsperity() ),
				mysqlpp::sql_int_unsigned( pReq->info.GetFamilyTotem() ),_tUTF8CHAR( pReq->info.GetFamilyAim() ),_tUTF8CHAR( pReq->info.GetFamilyNotice() ),
				pReq->info.GetDisbandTime(),pReq->info.GetLastChangeAimTime() );
			mysqlQuery.reset();
			TRYEND
		}
}

void NormalLogicWorkThread::OnFamilyMemberUpdateReq( BaseSqlMessage* pSqlMessage )
{
	CS2DBFamilyMemberUpdateReq *pReq = static_cast< CS2DBFamilyMemberUpdateReq* >( pSqlMessage->GetMessageAddress() );

	for ( int i = 0; i < pReq->nCount; ++i )
	{
		UpdateFamilyMember( pReq->memberList[i] );
	}
}

void NormalLogicWorkThread::UpdateFamilyMember( FamilyDefine::FamilyMember& xMember )
{
	char szSql[ 512 ] = { 0 };
	sprintf_s( szSql, sizeof( szSql ) - 1, "select level from familymember where id=%ld;", xMember.GetID() );

	uint32 result = ER_Success;
	bool bIsExist = false;

	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if ( res && !res.empty() )
	{ bIsExist = true; }
	mysqlQuery.reset();
	TRYEND

		if ( !bIsExist )        // 存在
		{
			memset( szSql, 0, sizeof( szSql ) );
			strncpy_s( szSql, sizeof( szSql ), "insert into familymember(id,name,level,profession,familyid,position,donatemoney) values(%0,%1q,%2,%3,%4,%5,%6);", sizeof( szSql ) - 1 );

			TRYBEGIN
				mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery << szSql;
			mysqlQuery.parse();
			mysqlQuery.execute( mysqlpp::sql_int_unsigned( xMember.GetID() ), _tUTF8CHAR( xMember.GetName() ), xMember.GetLevel(), xMember.GetProfession(),
				mysqlpp::sql_int_unsigned( xMember.GetFamilyID() ), xMember.GetPosition(), xMember.GetDonateMoney() );
			mysqlQuery.reset();
			TRYEND
		}
		else        // 已经存在就更新
		{
			memset( szSql, 0, sizeof( szSql ) );
			strncpy_s( szSql, sizeof( szSql ), "update familymember set name=%1q,level=%2,profession=%3,familyid=%4,position=%5,donatemoney=%6 where id=%0;", sizeof( szSql ) - 1 );

			TRYBEGIN
				mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			mysqlQuery << szSql;
			mysqlQuery.parse();
			mysqlQuery.execute( mysqlpp::sql_int_unsigned( xMember.GetID() ), _tUTF8CHAR( xMember.GetName() ), xMember.GetLevel(), xMember.GetProfession(),
				mysqlpp::sql_int_unsigned( xMember.GetFamilyID() ), xMember.GetPosition(), xMember.GetDonateMoney() );
			mysqlQuery.reset();
			TRYEND
		}
}

void NormalLogicWorkThread::OnFamilyMemberLeaveReq( BaseSqlMessage* pSqlMessage )
{
	CS2DBFamilyMemberLeaveReq *pReq = static_cast< CS2DBFamilyMemberLeaveReq* >( pSqlMessage->GetMessageAddress() );

	char szSql[512] = { 0 };
	uint32 result = ER_Success;    

	sprintf_s( szSql, sizeof( szSql ) - 1, "delete from familymember where id=%u;", pReq->nPlayerID );

	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
	mysqlQuery.execute( szSql );
	mysqlQuery.reset();
	TRYEND
}

void NormalLogicWorkThread::OnFamilyDisbandReq( BaseSqlMessage* pSqlMessage )
{
	CS2DBFamilyDisbandReq *pReq = static_cast< CS2DBFamilyDisbandReq* >( pSqlMessage->GetMessageAddress() );

	char szSql[512] = { 0 };
	uint32 result = ER_Success;    

	TRYBEGIN
		sprintf_s( szSql, sizeof( szSql ) - 1, "delete from family where id=%ld;", pReq->nFamilyID );
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
	mysqlQuery.execute( szSql );
	mysqlQuery.reset();

	sprintf_s( szSql, sizeof( szSql ) - 1, "delete from familymember where familyid=%u;", pReq->nFamilyID );
	mysqlQuery.execute( szSql );
	mysqlQuery.reset();
	TRYEND
}