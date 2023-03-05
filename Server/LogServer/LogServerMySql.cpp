#include "LogServerMySql.h"
#include "logfileobjectnameex.h"
#include "OnlineInfoWorkThread.h"
#include "ItemInfoWorkThread.h"
#include "PlayerInfoWorkThread.h"
#include "SystemInfoWorkThread.h"
#include "TestWorkThread.h"

void WorkThreadMain( void* pVoid )
{
	MySqlWorkThread* pThread = (MySqlWorkThread*)pVoid;

	pThread->Update();

	static const int nSleepTime = 1;
	Sleep( nSleepTime );
}

LogServerMySql::LogServerMySql(void)
{
}

LogServerMySql::~LogServerMySql(void)
{
}

uint32 LogServerMySql::Init(	const std::string& OnlineName, const std::string& Onlinehost, uint16 Onlineport, 
								const std::string& Onlineuser,   const std::string& Onlinepassword,
								const std::string& ItemName, const std::string& Itemhost, uint16 Itemport, 
								const std::string& Itemuser,   const std::string& Itempassword,
								const std::string& PlayerName, const std::string& Playerhost, uint16 Playerport, 
								const std::string& Playeruser,   const std::string& Playerpassword,
								const std::string& SystemName, const std::string& Systemhost, uint16 Systemport, 
								const std::string& Systemuser,   const std::string& Systempassword)
{
	// 创建两个线程 一个线程做原来所有sql
	bool bResult = MySqlWorkThread::InitMysqlLib();
	if ( !bResult  )
	{ return ER_Failed;}
	uint32 res = ER_Failed;
	//
	_pOnlineInfoWorkThread = new OnlineInfoWorkThread( this );
	if ( _pOnlineInfoWorkThread == NULL )
	{ return ER_NewNormalFail; }
	res = _pOnlineInfoWorkThread->Init( OnlineName, Onlinehost, Onlineport, Onlineuser, 
									Onlinepassword, ECD_OnlineInfoWorkThread );
	_pOnlineInfoWorkThread->CreateThread( WorkThreadMain, _pOnlineInfoWorkThread );
	//
	_pItemInfoWorkThread = new ItemInfoWorkThread( this );
	if ( _pItemInfoWorkThread == NULL )
	{ return ER_NewNormalFail; }
	res = _pItemInfoWorkThread->Init( ItemName, Itemhost, Itemport, Itemuser, 
									Itempassword, ECD_ItemInfoWorkThread );
	_pItemInfoWorkThread->CreateThread( WorkThreadMain, _pItemInfoWorkThread );
	//
	_pPlayerInfoWorkThread = new PlayerInfoWorkThread( this );
	if ( _pPlayerInfoWorkThread == NULL )
	{ return ER_NewNormalFail; }
	res = _pPlayerInfoWorkThread->Init( PlayerName, Playerhost, Playerport, Playeruser, 
									Playerpassword, ECD_PlayerInfoWorkThread );
	_pPlayerInfoWorkThread->CreateThread( WorkThreadMain, _pPlayerInfoWorkThread );
	//
	_pSystemInfoWorkThread = new /*PlayerInfoWorkThread*/SystemInfoWorkThread( this );
	if ( _pSystemInfoWorkThread == NULL )
	{ return ER_NewNormalFail; }
	res = _pSystemInfoWorkThread->Init( SystemName, Systemhost, Systemport, Systemuser, 
									Systempassword, ECD_SystemInfoWorkThread );
	_pSystemInfoWorkThread->CreateThread( WorkThreadMain, _pSystemInfoWorkThread );
	//
#ifdef _TEST
	_pTestWorkThread = new /*PlayerInfoWorkThread*/TestWorkThread( this );
	if ( _pTestWorkThread == NULL )
	{ return ER_NewNormalFail; }
	//使用各类系统相关的LOG的配置文件信息
	res = _pTestWorkThread->Init( SystemName, Systemhost, Systemport, Systemuser, 
		Systempassword, ECD_SystemInfoWorkThread );
	_pTestWorkThread->CreateThread( WorkThreadMain, _pTestWorkThread );
#endif
	return ER_Success;
}

uint32 LogServerMySql::PushLogMessage( Msg* pMsg, uint32 nClientId )
{
	BaseLogMessage* pBaseLogMessage = NULL;

	try
	{
		pBaseLogMessage = theLogMessageManager.GetLogMessageByLogMsg( pMsg );
	}
	catch ( std::exception& e)
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PushLogMessage->GetLogMessageByDbMsg Memory Not Enough(%s)", e.what());
		return ER_Failed;
	}

	if ( pBaseLogMessage == NULL )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "无此消息MessageId[%d] 对应的SqlMessage", pMsg->GetType() ); 
		return ER_Failed;
	}

	pBaseLogMessage->serverid = nClientId;
	pBaseLogMessage->_type      = pMsg->GetType();	
	memcpy( pBaseLogMessage->GetMessageAddress(), pMsg, pBaseLogMessage->GetMessageSize());

	CSALocker _lock(_LogMessagesLock);
	_LogMessages.push_back( pBaseLogMessage );

	return ER_Success;
}

void LogServerMySql::Update()
{
	// 处理请求
	LogMesageContainer tempDbReqMessages;
	{
		CSALocker _lock(_LogMessagesLock);
		tempDbReqMessages = _LogMessages;
		_LogMessages.clear();
	}

	// 丢给各个工作线程
	ItrLogMesageContainer it    = tempDbReqMessages.begin();
	ItrLogMesageContainer itEnd = tempDbReqMessages.end();
	for( ; it!=itEnd ; ++it )
	{
		BaseLogMessage* pDbMessage = (*it);
		switch ( pDbMessage->_type)
		{
		case LOGMSG_OnlineInfo:
		case LOGMSG_GMCOMMAND:
			_pOnlineInfoWorkThread->PushMessage( pDbMessage );
			break;
		case LOGMSG_INOUNTINFO:
		case LOGMSG_QUESTLOG:
		case LOGMSG_CURRENCY:
		case LOGMSG_EXPLOG:
		case LOGMSG_LEVCHANGE:
		case LOGMSG_MAILLOG:
			_pPlayerInfoWorkThread->PushMessage( pDbMessage );
			break;
		case LOGMSG_ITEMCONSUME:
		case LOGMSG_ITEMGAIN:
		case LOGMSG_ITEMUPGRADE:
		case LOGMSG_ITEMTRADE:
			_pItemInfoWorkThread->PushMessage( pDbMessage );
			break;
		case LOGMSG_GUILDLOG:
		case LOGMSG_GUILDDETAIL:
		case LOGMSG_CHATINFO:
			_pSystemInfoWorkThread->PushMessage( pDbMessage );
			break;
		case LOGMSG_BEGIN_TEST:
			_pTestWorkThread->PushMessage(pDbMessage);
			break;
		//case :
		//	break;
		default:
			theLogMessageManager.FreeLogMessage(pDbMessage);
			break;
			//case GS2CS_UPDATEANTIADDICTIONINFOREQ:
			//         {
			//             if ( theConfig.bOpenAntiAddiction && _pPlatformLogicThread )
			//             { _pPlatformLogicThread->PushMessage( pDbMessage ); }
			//         }
			//     	break;
			//default:
			//    {
			//        if ( _pNormalLogicThread )
			//        { _pNormalLogicThread->PushMessage( pDbMessage );}
			//    }
			//    break;
		}
	}
}

//void LogServerMySql::ShutDown()
//{
//	if ( _pBillingWorkThread )
//	{ _pBillingWorkThread->StopThreadAndWaitDead(); }
//
//	if ( _pNormalLogicThread )
//	{ _pNormalLogicThread->StopThreadAndWaitDead(); }
//
//	if ( _pSocietyLogicThread )
//	{ _pSocietyLogicThread->StopThreadAndWaitDead(); }
//
//	Sleep( 1000 );
//}

//void LogServerMySql::CheckExitCondition()
//{
//	if ( theDbRunStatus.GetStatus() != DbRunStatus::RunStatus_PrepareStop )
//	{ return; }
//
//	if ( _pBillingWorkThread && _pBillingWorkThread->IsHaveTask() )
//	{ return; }
//
//	if ( _pNormalLogicThread && _pNormalLogicThread->IsHaveTask() )
//	{ return; }
//
//	if ( _pSocietyLogicThread && _pSocietyLogicThread->IsHaveTask() )
//	{ return; }
//
//	GetRunStatus().SetStatus( DbRunStatus::RunStatus_Stopped ); 
//	ConsoleApplication::gGlobalConsole->SetExitFlag();
//	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "服务器可以安全退出" );
//	ColoredPrintf( COLOR_GREEN, "[服务器可以安全退出] \n" );
//}