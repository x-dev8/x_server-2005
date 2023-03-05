#include "NormalLogicWorkThread.h"
#include "zlib/zlib.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "GameBattleMessage.h"
#include "GameBattleDataManager.h"
void NormalLogicWorkThread::OnLoadGameBattleDataReq ( BaseSqlMessage* pSqlMessage )
{
	//加载战场信息 从数据库
	//加载战场的全部信息
	SqlMessageCS2DBLoadCampBattleData* pMsg = (SqlMessageCS2DBLoadCampBattleData*)pSqlMessage;
	//组织命令头
	DB2CSLoadCampBattleData msgAck;
	msgAck.ClearAllData();
	//组织SQL语句
	uint32 result   = ER_Success;
	{
		char szSql[1024] = {0};
		sprintf_s( szSql, sizeof( szSql ) - 1, "select * from guildcampbattledata");
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
			mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql );
			if ( res && !res.empty())
			{
				for (int i = 0; i < res.num_rows();++i )
				{	
					//获取每一行的数据 组织好后 发送到GameServer去 注意处理时间判断
					GameBattleDefine::GuildCampBattle pData;
					pData.ID = res[i]["ID"];
					pData.MapID = res[i]["MapID"];
					pData.SrcGuildID = res[i]["SrcGuildID"];
					pData.DestGuildID = res[i]["DestGuildID"];
					pData.MoneySum = res[i]["MoneySum"];
					pData.GuildMoneySum = res[i]["GuildMoneySum"];
					pData.GuildMissionSum = res[i]["GuildMissionSum"];
					mysqlpp::DateTime xLogTime = res[i]["BeginTime"];
					time_t beginTime = xLogTime.operator time_t();
					pData.BeginTime = beginTime;
					pData.IsWrite = res[i]["IsWrite"];
					if(msgAck.PushInfo(pData,i==res.num_rows()-1))
					{
						theMysqlCommunication.PushAckMessage( &msgAck, pSqlMessage->nClientId );
						msgAck.ClearAllData();
					}
				}
			}
			else
			{
				msgAck.Sum = 0;
				msgAck.IsEnd = true;
				theMysqlCommunication.PushAckMessage( &msgAck, pSqlMessage->nClientId );
			}
		TRYEND
	}
}
void NormalLogicWorkThread::OnAddGameBattleData( BaseSqlMessage* pSqlMessage )
{
	//添加新的数据
	//添加新的公会约战
	SqlMessageCS2DBAddCampBattleData* pMsg = (SqlMessageCS2DBAddCampBattleData*)pSqlMessage;
	if(!pMsg)
		return;
	//组织SQL语句 insert
	uint32 result = ER_Success;
	char szSql[1024] = {0};
	if(pMsg->msg.IsUpadte)
	{
		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			strncpy_s( szSql, sizeof( szSql ), "update guildcampbattledata set IsWrite = 0 where ID = %0;", sizeof( szSql ) - 1 );
			mysqlQuery << szSql;
			mysqlQuery.parse();
			mysqlQuery.execute(pMsg->msg.add.ID);
			mysqlQuery.reset();
		TRYEND
		CHECK_SQL_RESULT( result ) // 执行检测
	}
	else
	{
		TRYBEGIN
			mysqlpp::DateTime xLogTime(pMsg->msg.add.BeginTime);
			string TimeStr = xLogTime.str();

			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
			strncpy_s( szSql, sizeof( szSql ), "insert into guildcampbattledata(ID,MapID,SrcGuildID,DestGuildID,MoneySum,GuildMoneySum,GuildMissionSum,BeginTime,IsWrite) values(%0,%1,%2,%3,%4,%5,%6,%7q,%8);", sizeof( szSql ) - 1 );
			mysqlQuery << szSql;
			mysqlQuery.parse();
			mysqlQuery.execute(pMsg->msg.add.ID,pMsg->msg.add.MapID,pMsg->msg.add.SrcGuildID,pMsg->msg.add.DestGuildID,pMsg->msg.add.MoneySum,pMsg->msg.add.GuildMoneySum,pMsg->msg.add.GuildMissionSum,TimeStr.c_str(),pMsg->msg.add.IsWrite);
			mysqlQuery.reset();
		TRYEND
		CHECK_SQL_RESULT( result ) // 执行检测
	}
}
void NormalLogicWorkThread::OnDelGameBattleData( BaseSqlMessage* pSqlMessage )
{
	SqlMessageCS2DBDelCampBattleData* pMsg = (SqlMessageCS2DBDelCampBattleData*)pSqlMessage;
	//组织SQL语句删除数据
	if(!pMsg)
		return;
	char szSql[1024] = {0};
	uint32 result = ER_Success;
	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
		strncpy_s( szSql, sizeof( szSql ), "delete from guildcampbattledata where ID=%0;", sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(pMsg->msg.ID);
		mysqlQuery.reset();
	TRYEND
	CHECK_SQL_RESULT( result ) // 执行检测
}