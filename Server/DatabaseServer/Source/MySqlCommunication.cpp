#include "MySqlCommunication.h"
//#include "NetApi.h"
#include "DatabaseClient.h"
#include "DatabaseServerApp.h"
#include "AccountBillingWorkThread.h"
#include "NormalLogicWorkThread.h"
#include "SocietyRelationWorkThread.h"
#include "RunStatus.h"
#include "GameTime.h"
#include "ConsoleApplication.h"
#include "FileDatabase.h"
#include "BillingManager.h"
#include "ColorScreen.h"

static bool bDbShutDown = false;

void WorkThreadMain( void* pVoid )
{
	MySqlWorkThread* pThread = (MySqlWorkThread*)pVoid;

	pThread->Update();

	//if( bDbShutDown )
	//{ pThread->Stop(); }

	static const int nSleepTime = 1;
	Sleep( nSleepTime );
}

MySqlCommunication& GetMySqlCommunication()
{
	static MySqlCommunication instance;
	return instance;
}

MySqlCommunication::MySqlCommunication()
{
	_pNormalLogicThread  = NULL;
	_pBillingWorkThread  = NULL;
	_pSocietyLogicThread = NULL;
	bMemoryInfo = false;
}

MySqlCommunication::~MySqlCommunication()
{
	if ( _pNormalLogicThread )
	{ delete _pNormalLogicThread; }

	if ( _pBillingWorkThread )
	{ delete _pBillingWorkThread; }

	if ( _pSocietyLogicThread )
	{ delete _pSocietyLogicThread; }
}

uint32 MySqlCommunication::Init( const std::string& dbName, const std::string& host, uint16 port, 
								const std::string& user,   const std::string& password,
								const std::string& dbNameBilling, const std::string& hostBilling, uint16 portBilling, 
								const std::string& userBilling,   const std::string& passwordBilling)
{
	// 创建两个线程 一个线程做原来所有sql
	bool bResult = MySqlWorkThread::InitMysqlLib();
	if ( !bResult  )
	{ return ER_Failed;}

	_pBillingWorkThread = new AccountBillingWorkThread( this );
	if ( _pBillingWorkThread == NULL )
	{ return ER_NewNormalFail; }

	if ( GetDatabaseServerApp()->useSqlType != DatabaseServerApp::ST_MSSql )
	{
		_pNormalLogicThread = new NormalLogicWorkThread( this );
		if ( _pNormalLogicThread == NULL )
		{ return ER_NewNormalFail; }

		_pSocietyLogicThread = new SocietyRelationWorkThread( this );
		if ( _pSocietyLogicThread == NULL )
		{ return ER_NewNormalFail; }
	}

	uint32 res = _pBillingWorkThread->Init( dbNameBilling, hostBilling, portBilling, userBilling, passwordBilling, ECD_BillingWorkThread );
	_pBillingWorkThread->CreateThread( WorkThreadMain, _pBillingWorkThread );

	if ( GetDatabaseServerApp()->useSqlType != DatabaseServerApp::ST_MSSql )
	{
		_pNormalLogicThread->Init( dbName, host, port, user, password, ECD_NormalLogicWorkThread );
		_pNormalLogicThread->CreateThread( WorkThreadMain, _pNormalLogicThread );

		_pSocietyLogicThread->Init( dbName, host, port, user, password, ECD_SocietyRelationWorkThread );
		_pSocietyLogicThread->CreateThread( WorkThreadMain, _pSocietyLogicThread );
	}

	return ER_Success;
}

void MySqlCommunication::Update()
{

	UpdateForRequest();

	UpdateForAcknowledge();

	CheckExitCondition();

	static uint32 lastPrintMemoryTime = HQ_TimeGetTime();
	if ( bMemoryInfo || GameTime::IsPassCurrentTime( lastPrintMemoryTime, ONE_MIN * 10 ) )
	{
		CSALocker locker(GetAutoIntLock());
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "[堆分配内存占用输出起始]");
		uint32 nAllMemory = 0;
		for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); ++itr)
		{
			nAllMemory += itr->second.nAllUseMemory;
			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "%-60s 占用内存 [%-15d] 字节, 目前未释放共分配 [%-10d] 次, 历史申请[%-10d]次", itr->first!=NULL?itr->first:"未定义用途", itr->second.nAllUseMemory, itr->second.nExistCount, itr->second.nAllocCount );
		}
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "全部分配内存[%d]Byte [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "[堆分配内存占用输出终止]\n" );
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"网络库内容开始:");
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"%s",network::net_memory_info());
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"网络库内容结束!");
		bMemoryInfo = false;
		lastPrintMemoryTime = HQ_TimeGetTime();
	}
}

void MySqlCommunication::ShutDown()
{
	if ( _pBillingWorkThread )
	{ _pBillingWorkThread->StopThreadAndWaitDead(); }

	if ( _pNormalLogicThread )
	{ _pNormalLogicThread->StopThreadAndWaitDead(); }

	if ( _pSocietyLogicThread )
	{ _pSocietyLogicThread->StopThreadAndWaitDead(); }

	Sleep( 1000 );
}

uint32 MySqlCommunication::PushReqMessage( Msg* pMsg, uint32 nClientId )
{

	BaseSqlMessage* pBaseSqlMessage = NULL;

	try
	{
		pBaseSqlMessage = theSqlMessageManager.GetSqlMessageByDbMsg( pMsg );
	}
	catch ( std::exception& e)
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage->GetSqlMessageByDbMsg Memory Not Enough(%s)", e.what());
		return FALSE;
	}

	if ( pBaseSqlMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType() ); 
		return FALSE;
	}

	pBaseSqlMessage->nClientId = nClientId;
	pBaseSqlMessage->type      = pMsg->GetType();
	pBaseSqlMessage->time      = HQ_TimeGetTime();
	memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());

	{
		CSALocker _lock(_dbReqMessageLock);
		_dbReqMessages.push_back( pBaseSqlMessage );
	}

	return ER_Success;
}

uint32 MySqlCommunication::PushAckMessage( Msg* pMsg, uint32 nClientId )
{
	BaseSqlMessage* pBaseSqlMessage = NULL;

	try
	{
		pBaseSqlMessage = theSqlMessageManager.GetSqlMessageByDbMsg( pMsg );
	}
	catch ( std::exception& e )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushReqMessage->GetSqlMessageByDbMsg Memory Not Enough(%s)", e.what());
		return FALSE;
	} 

	if ( pBaseSqlMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType() ); 
		return FALSE;
	}

	pBaseSqlMessage->nClientId = nClientId;
	pBaseSqlMessage->type      = pMsg->GetType();
	pBaseSqlMessage->time      = HQ_TimeGetTime();
	memcpy( pBaseSqlMessage->GetMessageAddress(), pMsg, pBaseSqlMessage->GetMessageSize());

	{
		CSALocker _lock(_dbAckMessageLock);
		_dbAckMessages.push_back( pBaseSqlMessage );
	}

	return ER_Success;
}

void MySqlCommunication::UpdateForRequest()
{
	// 处理请求----------begin
	DbMesageContainer tempDbReqMessages;
	{
		CSALocker _lock(_dbReqMessageLock);
		tempDbReqMessages = _dbReqMessages;
		_dbReqMessages.clear();
	}

	// 丢给各个工作线程
	ItrDbMesageContainer it    = tempDbReqMessages.begin();
	ItrDbMesageContainer itEnd = tempDbReqMessages.end();
	for( ; it!=itEnd ; ++it )
	{
		BaseSqlMessage* pDbMessage = (*it);
		switch ( pDbMessage->type)
		{
		case DBMSG_REQ_ACCOUNT_BILLING   ://GS TO DB 请求 元宝
		case DBMSG_REQ_ACCOUNT_BILLING_OP://GS TO DB 操作 元宝
		case CS2DB_ACCOUNTPOINTER_REQ    ://CS TO DB 充值 元宝 感觉废弃了
		case DBMSG_OPERATEACCOUNTMONEY   ://GS TO DB 操作 元宝
		case DBMSG_SHOPPING				 ://GS TO DB 购买 商城物品
		case DB2DB_Cash					 ://BILLINGServer 操作 元宝
		case DBMSG_OPCONSUMESCORE		 ://GS TO DB 操作 积分
		case DB2DB_ConsumeScore			 ://GS TO DB 充值 积分
			{
				if ( _pBillingWorkThread )
				{ _pBillingWorkThread->PushMessage( pDbMessage ); }                
			}
			break;
		case DBMSG_ACCOUNTWALLOWINFO_REQ ://GS TO DB 防沉迷 感觉废弃了
		case DBMSG_ACCOUNTWALLOWINFO_SAVE://GS TO DB 防沉迷 感觉废弃了
		case DBMSG_JIFENGSHOPITEMSLISTREQ://GS TO DB 积分商城道具查询
		case DBMSG_JIFENGSHOPITEMSGAINREQ://GS TO DB 积分商城道具领取
			{
				if ( _pSocietyLogicThread )
				{ _pSocietyLogicThread->PushMessage( pDbMessage );}                
			}
			break;
		default:
			{
				if ( _pNormalLogicThread )
				{ _pNormalLogicThread->PushMessage( pDbMessage );}
			}
			break;
		}
	}
	// end----------
}
void MySqlCommunication::UpdateForAcknowledge()
{
	// 处理结果--------begin
	DbMesageContainer tempAckDbMessage;
	{
		CSALocker _lock( _dbAckMessageLock );
		tempAckDbMessage = _dbAckMessages;
		_dbAckMessages.clear();
	}

	ItrDbMesageContainer it    = tempAckDbMessage.begin();
	ItrDbMesageContainer itEnd = tempAckDbMessage.end();
	for( ; it!=itEnd ; ++it )
	{
		BaseSqlMessage* pDbMessage = (*it);    
		if ( pDbMessage == NULL )
		{ continue; }

		switch ( pDbMessage->type )
		{
		case DB2DB_NOTIFYFILEDBSAVECHAR:
			{
				SqlMessageDB2DBNotifyFileDBSaveChar* pDetailSqlMessage = (SqlMessageDB2DBNotifyFileDBSaveChar*)pDbMessage;
				DB2DBNotifyFileDBSaveChar* pDetailMessage = &pDetailSqlMessage->msg;
				theFileMappingCharSaveManager.RemoveDataFile( pDetailMessage->charId, pDetailMessage->lifeId );
			}
			break;
		case DB2DB_CashResult:
			{
				SqlMessageDB2DBCashResult* pDetailSqlMessage = (SqlMessageDB2DBCashResult*)pDbMessage;
				DB2DBCashResult* pDetailMessage = &pDetailSqlMessage->msg;

				theBillingManager.OnDBMsgCashResult(pDetailMessage);

				if (pDetailMessage->result == eDB2DBCashResult_succ)
				{
					GetDatabaseServerApp()->SendMsgToAllClient(pDetailMessage);
				}
			}
			break;
		case DB2DB_ConsumeScoreResult:
			{
				SqlMessageDB2DBConsumeScoreResult* pDetailSqlMessage = (SqlMessageDB2DBConsumeScoreResult*)pDbMessage;
				DB2DBConsumeScoreResult* pDetailMessage = &pDetailSqlMessage->msg;

				theBillingManager.OnDBMsgConsumeSocreResult(pDetailMessage);

				if (pDetailMessage->result == eDB2DBCashResult_succ)
				{
					GetDatabaseServerApp()->SendMsgToAllClient(pDetailMessage);
				}
			}
			break;
		default:
			{
				DatabaseClient* pClient = *(GetDatabaseServerApp()->_DatabaseClient[pDbMessage->nClientId]);/*(DatabaseClient*)GetDatabaseServerApp()->GetNodeMgr()->Find( (short)pDbMessage->nClientId );*/
				if( pClient == NULL )
				{   
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "查询结果所属 DatabaseClient[%d] 已经不存在 MessageType[%d]", pDbMessage->nClientId, pDbMessage->type );
				}
				else
				{
					/*IMeConnector*/Socketer* pConnector = pClient->GetConnector();

					if ( pConnector ) 
					{ // 把结果向来源发送 不做处理
						int nResult = pConnector->SendMsg( (Msg*)pDbMessage->GetMessageAddress() );
						if ( nResult == -1 )
						{}
					}
				}
			}
			break;
		}
		theSqlMessageManager.FreeSqlMessage( pDbMessage );
	}
	// end------------
}
void MySqlCommunication::CheckExitCondition()
{
	if ( theDbRunStatus.GetStatus() != DbRunStatus::RunStatus_PrepareStop )
	{ return; }

	if ( _pBillingWorkThread && _pBillingWorkThread->IsHaveTask() )
	{ return; }

	if ( _pNormalLogicThread && _pNormalLogicThread->IsHaveTask() )
	{ return; }

	if ( _pSocietyLogicThread && _pSocietyLogicThread->IsHaveTask() )
	{ return; }

	GetRunStatus().SetStatus( DbRunStatus::RunStatus_Stopped ); 
	ConsoleApplication::gGlobalConsole->SetExitFlag();
	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "服务器可以安全退出" );
	COLOR_MESSAGE( COLOR_GREEN, "[服务器可以安全退出] \n" );
}
bool MySqlCommunication::GetWorkThreadWorkState(EConstDefine type)
{
	switch (type)
	{
	case ECD_BillingWorkThread:
		return _pBillingWorkThread ? _pBillingWorkThread->_CheckState() : false;
	case ECD_NormalLogicWorkThread:
		return _pNormalLogicThread ? _pNormalLogicThread->_CheckState() : false;
	case ECD_SocietyRelationWorkThread:
		return _pNormalLogicThread ? _pSocietyLogicThread->_CheckState(): false;
	default:
		return false;
	}
}