#include "LogServerLogic.h"
#include "GameTimer.h"
#include "ColorScreen.h"
#include "LogServerConfig.h"
#include "NetWorkParameterDefine.h"
#include "logfileobjectnameex.h"
#include "LogServerMySql.h"
#include "Mutex.h"

#define WAITCLOSE_ALLOW_RATE 0.3f

CWorkThread LogServerLogic::g_SqlServiceThread;
CWorkThread LogServerLogic::g_MainLogicThread;

void LogServerLogic::Main( void* pParam)
{
	theLogServerLogic.Run();
	Sleep(1);
}

void LogServerLogic::MySqlMain( void* pParam)
{
	theLogServerMySql.Update();
	Sleep(1);
}


LogServerLogic::LogServerLogic(void)
{
	m_pListenServer				= NULL;
	m_pNormalServers            = NULL;
	m_pServerWaitClose          = NULL;
}

LogServerLogic::~LogServerLogic(void)
{
	if( m_pListenServer )
	{		
		Listener_release(m_pListenServer);
		m_pListenServer = NULL;
	}
	if (m_pServerWaitClose)
	{
		delete m_pServerWaitClose;
	}
	if (m_pNormalServers)
	{
		delete m_pNormalServers;
	}
}

bool LogServerLogic::Init()
{
	//创建服务器监听
	m_pListenServer = Listener_create();
	if ( !m_pListenServer  )
	{ return false; }

	if(!m_pListenServer->Listen( theLogServerConfig.ListenPort,eN_LogServer_ListenNum) )
	{ return false; }

	m_pNormalServers   = new CStaticArray<CServerSession*>( 50  );
	m_pServerWaitClose = new CStaticArray<CServerSession*>( 50  );

	// 启动主逻辑线程
	bool bResult = LogServerLogic::g_MainLogicThread.CreateThread( LogServerLogic::Main );
	CHECK_RETURN( !bResult, ER_CreateWorkThreadFail);

	bResult = LogServerLogic::g_SqlServiceThread.CreateThread( LogServerLogic::MySqlMain );
	CHECK_RETURN( !bResult, ER_SqlServiceFail );

	return true;
}

void LogServerLogic::Run()
{
	network::net_run();
	RunServer();
}

void LogServerLogic::RunServer()
{
	int acceptnum = 0;
	const int acceptmax = 5;
	while( m_pListenServer->CanAccept() && acceptnum < acceptmax )
	{
		AcceptNewServer();
		acceptnum++;
	}

	RecvAllServerMsg();
	ProcessAllServerMsg();
	CheckServerWaitClose();
	SendAllServerMsg();
#ifdef _TEST
	DoTestLogMessage();
#endif
}

bool LogServerLogic::AcceptNewServer()
{
	// 延迟销毁队列过长
	float fUsed = (float)(m_pServerWaitClose->GetUsed()) / m_pServerWaitClose->GetSize();
	if( fUsed > WAITCLOSE_ALLOW_RATE )
	{
		ColoredPrintf( COLOR_RED, "延迟销毁队列过长Rate[%f:%f]\n",fUsed, WAITCLOSE_ALLOW_RATE );
		return false;
	}

	Socketer* pSocket = NULL;

	pSocket = m_pListenServer->Accept();
	if ( !pSocket )
	{
		return false;
	}

	// 检查允许连接IP，如果不允许连接则断开
	//in_addr addr;
	std::string strIP;
	char chip[20];
	pSocket->GetIP(chip,20);
	strIP = chip;
	/////////////////////////////////////////////
	GameObjectId iID = m_pNormalServers->Malloc();
	if ( InvalidGameObjectId == iID )
	{
		if ( pSocket )
		{
			Socketer_release(pSocket);
		}
		return false;
	}
	*(*m_pNormalServers)[iID] = NULL;

	CServerSession* pServer = new CServerSession;
	if( !pServer )
	{
		if ( pSocket )
		{
			Socketer_release(pSocket);
		}

		if( InvalidGameObjectId != iID)
		{
			m_pNormalServers->Free(iID);
		}
		delete pServer;
		return false;
	}
	// 付给
	pServer->SetIConnecter(pSocket);
	pServer->SetConnect(HQ_TimeGetTime());

	*(*m_pNormalServers)[ iID ] = pServer;
	pServer->SetId(iID);
	pServer->SetInNormalList();
	return true;
}

void LogServerLogic::ProcessAllServerMsg()
{
	CServerSession** ppServer = NULL, *pServer = NULL;
	int iSize = m_pNormalServers->GetSize();
	int iUsed = m_pNormalServers->GetUsed();
	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0, iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if ( !m_pNormalServers->IsUsed(iLoopSize) )
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }	

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }

		// 是否已经断线
		if (pConnector->IsClose())
		{
			AddToServerWaitClose( pServer, __FUNCTION__, __LINE__);
			continue;
		}
		//每个GAME SERVER只处理20MS
		GameTimerEx processGameMessageTime;
		processGameMessageTime.StartTimer( HQ_TimeGetTime(), 20 );

		Msg *pMsg = NULL;
		// 时间片到了就退了
		while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
		{
			pMsg = pConnector->GetMsg();
			if ( pMsg == NULL )
			{ break;  }
			switch(pMsg->GetType())
			{
			case LOGMSG_SynServerid:
				{
					S2LSynServerid* pSyn = (S2LSynServerid*)pMsg;
					if (pSyn)
					{
						pServer->SetServerId(pSyn->serverid);
					}
				}
				break;
			default:
				if (pServer->GetServerId() == -1)
				{
					AddToServerWaitClose( pServer, __FUNCTION__, __LINE__);
					break;
				}
				theLogServerMySql.PushLogMessage(pMsg,pServer->GetServerId());
				break;
			}
		}
	}
}

void LogServerLogic::SendAllServerMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	CServerSession**ppServer = NULL,*pServer = NULL;

	int iSize = 0;
	int iUsed = 0;

	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalServers->IsUsed(iLoopSize))
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckSend();
	}

	iSize = m_pServerWaitClose->GetSize();
	iUsed = m_pServerWaitClose->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pServerWaitClose->IsUsed(iLoopSize))
		{ continue; }

		ppServer = (*m_pServerWaitClose)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckSend();
	}
}

void LogServerLogic::RecvAllServerMsg()
{
	int iLoopUsed=0, iLoopSize=0;

	CServerSession**ppServer = NULL,*pServer = NULL;

	int iSize = 0;
	int iUsed = 0;

	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalServers->IsUsed(iLoopSize))
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->CheckRecv();
	}
}

void LogServerLogic::CloseAllServer()
{
	int iLoopUsed,iLoopSize;
	int iUsed,iSize;

	CServerSession**ppServer = NULL,*pServer = NULL;

	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++ iLoopSize )
	{
		ppServer = (*m_pNormalServers)[ iLoopSize ];
		if( !ppServer )
			continue;
		iLoopUsed ++;

		pServer = *ppServer;
		AddToServerWaitClose( pServer, __FUNCTION__, __LINE__ );
	}
}

void LogServerLogic::AddToServerWaitClose( CServerSession* pServer, char* szFun, int nLine )
{
	if ( !pServer||!pServer->IsInNormalList())
	{ return; }

	if ( InvalidGameObjectId != pServer->GetId())
	{
		m_pNormalServers->Free(pServer->GetId());
	}

	// 加入到等待队列
	GameObjectId iID = m_pServerWaitClose->Malloc();
	if( InvalidGameObjectId == iID )
	{	
		delete pServer;
	}
	else
	{
		*(*m_pServerWaitClose)[ iID ] = pServer;
		pServer->SetCloseTime(HQ_TimeGetTime());
		pServer->SetId(iID);
		pServer->SetInWaiteList();
	}
	return;
}

void LogServerLogic::CheckServerWaitClose( bool bWait )
{
	// 检查主动关闭的socket是否关闭完成
	CServerSession** ppServer  = NULL;
	CServerSession*  pServer   = NULL;

	int iSize = m_pServerWaitClose->GetSize();
	int iUsed = m_pServerWaitClose->GetUsed();

	int iLoopUsed,iLoopSize;
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ;  ++iLoopSize )
	{
		ppServer = (*m_pServerWaitClose)[ iLoopSize ];
		if(  NULL == ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( NULL == pServer)
		{ continue; }

		Socketer* pConnector =  pServer->GetIConnecter();
		if ( NULL == pConnector )
		{ continue; }

		// 释放计数
		if( pServer->CanClose(HQ_TimeGetTime()) || !bWait )
		{
			pConnector->Close();
			// 删除
			m_pServerWaitClose->Free( iLoopSize );
			delete pServer;
		}
	}
}

void LogServerLogic::SendMsgToAllServer(Msg* pMsg)
{
	if (!pMsg)
	{
		return;
	}
	int iLoopUsed=0, iLoopSize=0;
	CServerSession**ppServer = NULL,*pServer = NULL;
	int iSize = 0;
	int iUsed = 0;
	iSize = m_pNormalServers->GetSize();
	iUsed = m_pNormalServers->GetUsed();
	for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
	{
		if (!m_pNormalServers->IsUsed(iLoopSize))
		{ continue; }

		ppServer = (*m_pNormalServers)[iLoopSize];
		if( !ppServer )
		{ continue; }

		++iLoopUsed;

		pServer = *ppServer;
		if( !pServer )
		{ continue; }

		Socketer* pConnector = pServer->GetIConnecter();
		if ( !pConnector )
		{ continue; }
		pConnector->SendMsg(pMsg);
	}
}

#define TestCount 1000 //每帧插入的数量
#define FrameCount 100   //处理多少帧,< 0 表示不限制
void LogServerLogic::DoTestLogMessage()
{
	static short fc = 0;

	if (FrameCount > 0 && fc >= FrameCount)
	{
		return;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	for (int n = 0;n < TestCount;n++)
	{
		TestLogMessage tlm;
		memcpy(&tlm._time,&systime,sizeof(SYSTEMTIME));
		tlm.account_id = 0;
		tlm.character_id = 0;
		_snprintf(tlm.frondose, sizeof(tlm.frondose)-1, "dsfgsergserglnshoeirghsuiehrgiosheriug");
		theLogServerMySql.PushLogMessage(&tlm,0);
	}
	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Insert TestLogMessge Count:%d!",TestCount);
	fc++;
}