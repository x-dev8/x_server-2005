#include "AccountBillingWorkThread.h"
#include "MySqlCommunication.h"
#include "DatabaseServerApp.h"

AccountBillingWorkThread::AccountBillingWorkThread( MySqlCommunication* pOwn ) : MySqlWorkThread(pOwn)
{	
	m_bHaveInitMoneyCache = false;
}

uint32 AccountBillingWorkThread::Update()
{
	// 保存基本的 Sql连接 和 Update
	if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
	{ return ER_Success; }

	if (!m_bHaveInitMoneyCache&&GetDatabaseServerApp()->m_bAccountBilling)
	{
		if (LoadAllMoney() == ER_Success)
		{
			m_bHaveInitMoneyCache = true;
		}
	}

	BaseSqlMessage* pSqlMessage = _dbMsgQueue.PopQuery();
	while ( pSqlMessage != NULL)
	{
		switch( pSqlMessage->type )
		{
		case DBMSG_REQ_ACCOUNT_BILLING:
			{ OnReqAccountBilling( pSqlMessage );}
			break;
		case DBMSG_REQ_ACCOUNT_BILLING_OP:
			{ OnReqAccountBillingOp( pSqlMessage ); }
			break;
		case CS2DB_ACCOUNTPOINTER_REQ:
			{ OnReqAccountPoints( pSqlMessage ); }
			break;
		case DBMSG_OPERATEACCOUNTMONEY:
			{
				OnReqOperateMoney(pSqlMessage );//操作点数
			}
			break;
		case DBMSG_OPCONSUMESCORE:
			{
				OnReqOperateConsumeScore(pSqlMessage );//操作积分
			}
			break;
		case DBMSG_SHOPPING:
			{
				OnReqShopping(pSqlMessage);
			}
			break;
		default:
			//新逻辑从这里开始 by vvx
			if (GetDatabaseServerApp()->m_bAccountBilling)
			{
				switch( pSqlMessage->type )
				{
				case DB2DB_Cash:
					{
						OnReqCashMoney(pSqlMessage);
					}
					break;
				case DB2DB_ConsumeScore:
					{
						OnReqConsumeScore(pSqlMessage);
					}
					break;
				default:
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "AccountBillingWorkThread::Update() MessageId[%d] 没有处理函数 accountbilling true", pSqlMessage->type );
					break;
				}
			}
			else
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "AccountBillingWorkThread::Update() MessageId[%d] 没有处理函数:accountbilling false", pSqlMessage->type );

			break;
		}

		theSqlMessageManager.FreeSqlMessage( pSqlMessage );
		pSqlMessage = _dbMsgQueue.PopQuery();
	}

	_CheckState();
	return ER_Success;
}

uint32 AccountBillingWorkThread::OnReqAccountBilling( BaseSqlMessage* pSqlMessage )
{
	SqlMessageDBMsgReqAccountBilling* pDetailSqlMessage = (SqlMessageDBMsgReqAccountBilling*)pSqlMessage;

	DBMsgReqAccountBilling* pMessage = &pDetailSqlMessage->msg;

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s(szSql, sizeof(szSql)-1,"call get_account_billing_info(%u);", pMessage->guid );      
	uint32 point = 0;
	uint32 result = ER_Failed;

	TRYBEGIN  
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		uint32 count = res[0][0]; // num
		if ( count == 1 )
		{ 
			point = res[0][1]; 
			result = ER_Success;
		} // point
		else if ( count == 0)
		{
			point = 0;
			result = ER_Success;
		}
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND

		DBMsgAckAccountBilling ack;
	ack.op          = pMessage->op;
	ack.identifyId  = pMessage->identifyId;
	ack.identifyId2 = pMessage->identifyId2;
	ack.result      = result;
	ack.guid        = pMessage->guid;
	ack.point       = point;
	ack.value       = pMessage->value;
	_pOwn->PushAckMessage( &ack, pDetailSqlMessage->nClientId );
	return result;
}

#include "PlatformDefine.h"

uint32 AccountBillingWorkThread::OnReqAccountBillingOp( BaseSqlMessage* pSqlMessage )
{
	SqlMessageDBMsgReqAccountBillingOp* pDetailSqlMessage = (SqlMessageDBMsgReqAccountBillingOp*)pSqlMessage;

	DBMsgReqAccountBillingOp* pMessage = &pDetailSqlMessage->msg;

	uint32 result = ER_Success;

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"call account_point_op( %u, %d, %d );", pMessage->guid, pMessage->point, EAPOT_Sub );
	uint32 point = 0;

	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();        
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql) );
	FREESTOREPROCEDURE_TRY;
	TRYEND

		LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "Result[%u] 请求扣点数操作( %u, %d )", pMessage->guid, pMessage->point );

	return result;
}

uint32 AccountBillingWorkThread::OnReqAccountPoints( BaseSqlMessage* pSqlMessage )
{
	SqlMessageCS2DBAccountPoints* pDetailSqlMessage = (SqlMessageCS2DBAccountPoints*)pSqlMessage;
	CS2DBAccountPoints* pMessage = &pDetailSqlMessage->msg;

	uint32 result = ER_Success;

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"call account_point_op( %u, %d, %d );", pMessage->info.guid, pMessage->info.points, EAPOT_Add );        

	uint32 point = 0;
	TRYBEGIN
		mysqlpp::Query mysqlQuery     = _pMysqlConnect->query();        
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql) );

	FREESTOREPROCEDURE_TRY;
	TRYEND

		LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "Result[%u] 处冲值请求(%u:%u:%u:%s:%u:%u:%u:%u:%s:%s:%s:%s:%u:%u)",
		result,
		pMessage->info.guid,
		pMessage->info.gssid,
		pMessage->info.typeId,
		pMessage->info.typesn,
		pMessage->info.points,
		pMessage->info.discount,
		pMessage->info.addamount,
		pMessage->info.netincome,
		pMessage->info.signstr,
		pMessage->info.remark,
		pMessage->info.userip,
		pMessage->info.gateway,
		pMessage->info.channel,
		pMessage->info.paytime);

	DB2CSAccountPoints msg;
	msg.identifyId  = pMessage->identifyId;
	msg.identifyId2 = pMessage->identifyId2;
	msg.result      = result;
	msg.guid        = pMessage->info.guid;
	msg.points      = pMessage->info.points;
	memcpy( &msg.typesn, &pMessage->info.typesn, sizeof(msg.typesn) );
	_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );

	return result;
}

//


uint32 AccountBillingWorkThread::LoadAllMoney()
{
	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s(szSql, sizeof(szSql)-1,"select * from account_billing;");      
	uint32 point = 0;
	uint32 account_id = 0;
	uint32 result = ER_Failed;

	TRYBEGIN  
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		for (int i = 0; i < res.num_rows();++i )
		{
			account_id = res[i]["guid"];
			point = res[i]["point"];

			if(theAccountMoneyCache.OperateMoney(account_id,point,eMoneyOperate_set) != ER_Success)
			{
				result = ER_Failed;
				LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"LoadAllMoney error!accountid:[%d],point:[%d]",account_id, point);
			}
			else
				result = ER_Success;

		}
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND


		//============================================
	{

		//下面是处理 商城积分的
		sprintf_s(szSql, sizeof(szSql)-1,"select * from ConsumeScore;");      
		uint32 point = 0;
		uint32 account_id = 0;
		uint32 result = ER_Failed;

		TRYBEGIN  
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		if ( res && !res.empty())
		{
			for (int i = 0; i < res.num_rows();++i )
			{
				account_id = res[i]["guid"];
				point = res[i]["point"];

				if(theAccountMoneyCache.OperateConsumeScore(account_id,point,eMoneyOperate_set) != ER_Success)
				{
					result = ER_Failed;
					LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"LoadAllMoney ConsumeScore error!accountid:[%d],point:[%d]",account_id, point);
				}
				else
					result = ER_Success;

			}
		}
		FREESTOREPROCEDURE_TRY;
		TRYEND

	}
	return result;
}

uint32 AccountBillingWorkThread::OnReqShopping( BaseSqlMessage* pSqlMessage )
{
	if (!GetDatabaseServerApp()->m_bAccountBilling)
	{
		return ER_Success;
	}
	SqlMessageDBMsgShopping* pDetailSqlMessage = (SqlMessageDBMsgShopping*)pSqlMessage;
	DBMsgShopping* pMessage = &pDetailSqlMessage->msg;

	uint32 result = ER_Success;
	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	if(pMessage->flag == 0)
	{
		sprintf_s( szSql, sizeof( szSql ) - 1,"call Shopping( %u, %u, %u,%u, %u, %u );",  pMessage->account_id,
			pMessage->character_id,
			pMessage->item_id,
			pMessage->item_count,
			pMessage->cost_money,
			pMessage->Unit_price);
		uint32 point = 0;

		TRYBEGIN  
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		if ( res && !res.empty())
		{
			uint32 count = res[0][0]; // num
			if ( count == 1 )
			{ 
				point = res[0][1]; 
				result = ER_Success;
			} // point
			else if ( count == 0)
			{
				point = 0;
				result = ER_Success;
			}
		}
		FREESTOREPROCEDURE_TRY;
		TRYEND

			theAccountMoneyCache.OperateMoney(pMessage->account_id,point,eMoneyOperate_set);

		DBMsgSetBillingMoney msg;
		msg.account_id = pMessage->account_id;
		msg.character_id = pMessage->character_id;
		msg.money = point;
		_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );
	}
	else
	{		
		sprintf_s( szSql, sizeof( szSql ) - 1,
			"insert into shopping_log(guid,character_id,item_id,item_count,cost_money,unit_price,old_money,new_money,date ,type) values(%u, %u, %u,%u, %u, %u , %u, %u, now() ,%u);",
			pMessage->account_id,pMessage->character_id,pMessage->item_id,pMessage->item_count,pMessage->cost_money,pMessage->Unit_price,pMessage->oldValue,pMessage->newValue,pMessage->flag);
		uint32 point = 0;

		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		FREESTOREPROCEDURE_TRY;
		TRYEND

			if(pMessage->flag == 2) //写运行时数据
			{
				DBMsgSetConsumeScore msg;
				msg.account_id = pMessage->account_id;
				msg.character_id = pMessage->character_id;
				msg.money = point;
				_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );

				theAccountMoneyCache.OperateConsumeScore(pMessage->account_id,pMessage->newValue,eMoneyOperate_set);
			}
	}	
	return result;
}
uint32 AccountBillingWorkThread::OnReqOperateConsumeScore( BaseSqlMessage* pSqlMessage )
{
	SqlMessageDBMsgOperateAccountConsumeScore * pDetailSqlMessage = (SqlMessageDBMsgOperateAccountConsumeScore*)pSqlMessage;
	DBMsgOperateAccountConsumeScore * pMessage = &pDetailSqlMessage->msg;

	uint32 point = 0;
	uint32 result = ER_Success;

	//设置ConsumeScore表中的字段 （addjinfen 过来的消息）

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"call OperateConsumeScore( %u, %u, %u);",  pMessage->account_id,
		pMessage->modify_money,	pMessage->operate_flag);

	TRYBEGIN  
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		uint32 count = res[0][0]; // num
		if ( count == 1 )
		{ 
			point = res[0][1]; 
			result = ER_Success;
		} // point
		else if ( count == 0)
		{
			point = 0;
			result = ER_Success;
		}
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND

		if (result == ER_Success)
		{
			theAccountMoneyCache.OperateConsumeScore(pMessage->account_id,point,eMoneyOperate_set);
		}


		//下发客户端 积分改变
		DBMsgSetConsumeScore msg;
		msg.header.stID = pMessage->header.stID;
		msg.account_id = pMessage->account_id;
		msg.character_id = pMessage->character_id;
		msg.money = point;
		_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );
		return result;

}

uint32 AccountBillingWorkThread::OnReqOperateMoney( BaseSqlMessage* pSqlMessage )
{
	SqlMessageDBMsgOperateAccountMoney* pDetailSqlMessage = (SqlMessageDBMsgOperateAccountMoney*)pSqlMessage;
	DBMsgOperateAccountMoney* pMessage = &pDetailSqlMessage->msg;

	uint32 point = 0;
	uint32 result = ER_Success;
	if (GetDatabaseServerApp()->m_bAccountBilling)
	{
		char szSql[1024] = {0};
		memset( szSql, 0, sizeof(szSql));
		sprintf_s( szSql, sizeof( szSql ) - 1,"call OperateMoney( %u, %u, %u);",  pMessage->account_id,
			pMessage->modify_money,	pMessage->operate_flag);

		TRYBEGIN  
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		if ( res && !res.empty())
		{
			uint32 count = res[0][0]; // num
			if ( count == 1 )
			{ 
				point = res[0][1]; 
				result = ER_Success;
			} // point
			else if ( count == 0)
			{
				point = 0;
				result = ER_Success;
			}
		}
		FREESTOREPROCEDURE_TRY;
		TRYEND

			if (result == ER_Success)
			{
				theAccountMoneyCache.OperateMoney(pMessage->account_id,point,eMoneyOperate_set);
			}
	}
	else
	{
		point = pMessage->modify_money;
	}

	DBMsgSetBillingMoney msg;
	msg.header.stID = pMessage->header.stID;
	msg.account_id = pMessage->account_id;
	msg.character_id = pMessage->character_id;
	msg.money = point;
	_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );

	return result;
}

uint32 AccountBillingWorkThread::OnReqCashMoney( BaseSqlMessage* pSqlMessage )
{
	SqlMessageDB2DBCash* pDetailSqlMessage = (SqlMessageDB2DBCash*)pSqlMessage;
	DB2DBCash* pMessage = &pDetailSqlMessage->msg;

	DB2DBCashResult msg;
	msg.account_id = pMessage->account_id;
	msg.money = pMessage->money;
	memcpy(msg.sn,pMessage->sn,17);
	msg.result = eDB2DBCashResult_max;


	uint32 point = 0;
	uint32 lognum = 0;
	uint32 result = ER_Success;

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select count(*) from account_billing_log where typesn = '%s' and result = 0;",pMessage->sn);
	TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		lognum = res[0][0];
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND

		char op = 1;
	if (pMessage->money < 0)
	{
		op = 0;
	}
	msg.account_yuanbao_states = 0;
	msg.account_yuanbao_totle = 0;
	if (lognum == 0&&result == ER_Success)
	{
		sprintf_s( szSql, sizeof( szSql ) - 1,"call AccountCash( %u, %u, %d, %s);",  
			pMessage->account_id,	pMessage->money,	op,pMessage->sn);

		TRYBEGIN  
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		if ( res && !res.empty())
		{
			uint32 count = res[0][0]; // num
			if ( count == 1 )
			{ 
				point = res[0][1]; 
				result = ER_Success;
				msg.account_yuanbao_totle = res[0][2];
				msg.account_yuanbao_states = res[0][3];//状态值
			} // point
			else if ( count == 0)
			{
				point = 0;
				result = ER_Success;
			}
		}
		FREESTOREPROCEDURE_TRY;
		TRYEND

			if (result == ER_Success)
			{
				theAccountMoneyCache.OperateMoney(pMessage->account_id,point,eMoneyOperate_set);
				msg.result = eDB2DBCashResult_succ;
			}
	}
	else
	{
		if (lognum > 0)
		{
			msg.result = eDB2DBCashResult_cashed;

			memset( szSql, 0, sizeof(szSql));
			sprintf_s( szSql, sizeof( szSql ) - 1,
				"insert into account_billing_log(guid,typesn,typeid,addamount,addtime,result) values(%u,'%s',%u,%d,now(),%u);",
				pMessage->account_id,pMessage->sn,op,pMessage->money,eDB2DBCashResult_cashed);

		}
		else
		{
			msg.result = eDB2DBCashResult_checkerror;

			memset( szSql, 0, sizeof(szSql));
			sprintf_s( szSql, sizeof( szSql ) - 1,
				"insert into account_billing_log(guid,typesn,typeid,addamount,addtime,result) values(%u,'%s',%u,%d,now(),%u);",  
				pMessage->account_id,pMessage->sn,op,pMessage->money,eDB2DBCashResult_checkerror);
		}	

		TRYBEGIN
			mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		FREESTOREPROCEDURE_TRY;
		TRYEND
	}

	msg.all_money = point;
	_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );
	return result;
}

uint32 AccountBillingWorkThread::OnReqConsumeScore( BaseSqlMessage* pSqlMessage )
{
	SqlMessageDB2DBConsumeScore* pDetailSqlMessage = (SqlMessageDB2DBConsumeScore*)pSqlMessage;
	DB2DBConsumeScore* pMessage = &pDetailSqlMessage->msg;

	DB2DBConsumeScoreResult msg;
	msg.account_id = pMessage->account_id;
	msg.money = pMessage->money;
	memcpy(msg.sn,pMessage->sn,17);
	msg.result = eDB2DBCashResult_max;

	uint32 point = 0;
	uint32 lognum = 0;
	uint32 result = ER_Success;

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select count(*) from ConsumeScore_BillingLog where typesn = '%s' and result = 0;",pMessage->sn);
	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		lognum = res[0][0];
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND

	char op = 1;
	if (pMessage->money < 0)
	{
		op = 0;
	}
	if (lognum == 0&&result == ER_Success)
	{
		sprintf_s( szSql, sizeof( szSql ) - 1,"call AccountConsumeScore( %u, %u, %d, %s);",  
			pMessage->account_id,	pMessage->money,	op,pMessage->sn);

		TRYBEGIN  
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		if ( res && !res.empty())
		{
			uint32 count = res[0][0]; // num
			if ( count == 1 )
			{
				point = res[0][1]; 
				result = ER_Success;
			} // point
			else if ( count == 0)
			{
				point = 0;
				result = ER_Success;
			}
		}
		FREESTOREPROCEDURE_TRY;
		TRYEND

			if (result == ER_Success)
			{
				theAccountMoneyCache.OperateConsumeScore(pMessage->account_id,point,eMoneyOperate_set);
				msg.result = eDB2DBCashResult_succ;
			}
	}
	else
	{
		if (lognum > 0)
		{
			msg.result = eDB2DBCashResult_cashed;

			memset( szSql, 0, sizeof(szSql));
			sprintf_s( szSql, sizeof( szSql ) - 1,
				"insert into ConsumeScore_BillingLog(guid,typesn,typeid,addamount,addtime,result) values(%u,'%s',%u,%d,now(),%u);",
				pMessage->account_id,pMessage->sn,op,pMessage->money,eDB2DBCashResult_cashed);
		}
		else
		{
			msg.result = eDB2DBCashResult_checkerror;

			memset( szSql, 0, sizeof(szSql));
			sprintf_s( szSql, sizeof( szSql ) - 1,
				"insert into ConsumeScore_BillingLog(guid,typesn,typeid,addamount,addtime,result) values(%u,'%s',%u,%d,now(),%u);",  
				pMessage->account_id,pMessage->sn,op,pMessage->money,eDB2DBCashResult_checkerror);
		}	

		TRYBEGIN
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
		FREESTOREPROCEDURE_TRY;
		TRYEND
	}

	msg.all_money = point;
	_pOwn->PushAckMessage( &msg, pDetailSqlMessage->nClientId  );
	return result;
}