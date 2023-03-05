#include "PlatformWorkSpace.h"
#include "PlatFormConfig.h"
#include "errorcode.h"
#include "NetWorkParameterDefine.h"
#include "ColorScreen.h"
#include "MySQLWorkSpace.h"
#include "CommonModule.h"
#include "MailModule.h"

#define WAITCLOSE_ALLOW_RATE 0.3f

CWorkThread CPlatformWorkSpace::g_SqlServiceThread;
CWorkThread CPlatformWorkSpace::g_MainLogicThread;

void CPlatformWorkSpace::SqlMain( void* pParam)
{
	theMYSQLWorkSpace.Run();
	Sleep(1);
}

void CPlatformWorkSpace::Main( void* pParam)
{
	thePlatFormWorkSpace.RunOneStep();
	Sleep(1);
}


CPlatformWorkSpace::CPlatformWorkSpace(void)
{
	m_psockClientListen         =  NULL;
	m_pListenServer             =  NULL;
	m_pNormalServers            =  NULL;
	m_pServerWaitClose          =  NULL;

	WorkSpaceTaskPool ();
}

CPlatformWorkSpace::~CPlatformWorkSpace(void)
{
	if( m_psockClientListen )
	{
		m_psockClientListen->Close();
		Listener_release(m_psockClientListen);
		m_psockClientListen = NULL;
	}

	if (m_pListenServer)
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

bool CPlatformWorkSpace::Init()
{
	//创建客户端监听(如果开启client登录)
	if (thePlatFormConfig.openCheckService)
	{
		m_psockClientListen = Listener_create();
		if ( !m_psockClientListen  )
		{ return ER_Failed; }

		if(!m_psockClientListen->Listen( thePlatFormConfig.ListenClientPort,eN_PlatFormCenter_ListenNum) )
		{ return ER_Failed; }
	}
	//创建服务器监听
	m_pListenServer = Listener_create();
	if ( !m_pListenServer  )
	{ return ER_Failed; }

	if(!m_pListenServer->Listen( thePlatFormConfig.ListenPort,eN_PlatFormCenter_ListenNum) )
	{ return ER_Failed; }

	m_pNormalServers   = new CStaticArray<CServerSession*>( 20  );
	m_pServerWaitClose = new CStaticArray<CServerSession*>( 20  );


	// 启动主逻辑线程
	bool bResult = CPlatformWorkSpace::g_MainLogicThread.CreateThread( CPlatformWorkSpace::Main );
	CHECK_RETURN( !bResult, ER_CreateWorkThreadFail);

	bResult = CPlatformWorkSpace::g_SqlServiceThread.CreateThread( CPlatformWorkSpace::SqlMain );
	CHECK_RETURN( !bResult, ER_SqlServiceFail );

	return ER_Success;
}

void CPlatformWorkSpace::RunOneStep()
{
	network::net_run();

	ProcessGMTask();
	ProcessMailTask();
	ProcessError();
	RunServer();
}

CServerSession* CPlatformWorkSpace::GetServerSessionById(int serverid)
{
	mapServer::iterator itr = _mapServer.find(serverid);
	if (itr == _mapServer.end())
	{
		return NULL;
	}
	return itr->second;
}

//void CPlatformWorkSpace::RelatingServerAndServerId(CServerSession* pServer,int serverid)
//{
//	if (!pServer)
//	{
//		return;
//	}
//
//	MsgP2CRegeResult msg;
//	mapServer::iterator itr = _mapServer.find(serverid);
//	if (itr != _mapServer.end())
//	{
//		msg._result = eRegeResult_Refrain;
//	}
//	else
//	{
//		if (pServer->GetServerId() != -1)
//		{
//			msg._result = eRegeResult_fail;
//		}
//		else
//		{
//			msg._result = eRegeResult_succ;
//
//			pServer->SetServerId(serverid);
//			_mapServer.insert(mapServer::value_type(serverid,pServer));
//		}		
//	}
//	pServer->SendMsg(&msg);
//}

bool CPlatformWorkSpace::AcceptNewServer()
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
			pSocket->Close();
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
			pSocket->Close();
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

void CPlatformWorkSpace::ProcessAllServerMsg()
{
#define EVERY_ONE_FRAME_PROCESS_MSG_NUM 50

	short i;
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
		Msg *pMsg;
		i = 0;
		while( pMsg = pConnector->GetMsg())
		{
			switch(pMsg->GetType())
			{
			case PFMSG_C2PTELLSERVERID:
				{
					OnMsgGetServerIdMsg(pMsg,pServer);
					/*MsgC2PTellServerid* pID = (MsgC2PTellServerid*)pMsg;
					RelatingServerAndServerId(pServer,pID->server_id);*/
				}
				break;
			case PFMSG_ASKFORPRESENT:
				OnMsgAskForPresent(pMsg,pServer);
				break;
			case PFMSG_ASKFORACTIVITY:
				OnMsgAskForActivity(pMsg,pServer);
				break;
			case PFMSG_REQ_EPISTARPOINT://晶元操作 by cloud
				OnMsgPFEpistarPoint(pMsg,pServer);
				break;
			default:
				break;
			}
			++i;
			if (EVERY_ONE_FRAME_PROCESS_MSG_NUM <= i)
				break;
		}
	}
}

void CPlatformWorkSpace::SendAllServerMsg()
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

void CPlatformWorkSpace::RecvAllServerMsg()
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

void CPlatformWorkSpace::CloseAllServer()
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

void CPlatformWorkSpace::AddToServerWaitClose( CServerSession* pServer, char* szFun, int nLine )
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
		mapServer::iterator itr = _mapServer.find(pServer->GetServerId());
		if (itr != _mapServer.end())
		{
			_mapServer.erase(itr);
		}
	}
	return;
}

void CPlatformWorkSpace::CheckServerWaitClose( bool bWait )
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

void CPlatformWorkSpace::SendMsgToAllServer(Msg* pMsg)
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

bool CPlatformWorkSpace::SendMsgToSingleServer(Msg* pMsg,int serverid)
{
	if (!pMsg)
	{
		return false;
	}
	mapServer::iterator itr = _mapServer.find(serverid);
	if (itr == _mapServer.end())
	{
		return false;
	}
	CServerSession* pServer = itr->second;
	if (!pServer)
	{
		return false;
	}
	return pServer->SendMsg(pMsg);
}

void CPlatformWorkSpace::RunServer()
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
}

#define MAX_GMTASK_COUNT 50
void CPlatformWorkSpace::ProcessGMTask()
{
	int n = 0;
	SGMTaskInfo* pInfo = NULL;
	while(pInfo = theMYSQLWorkSpace.GetGMTaskInfo())
	{
		if (pInfo&&pInfo->result == eTaskResult_ResNo)
		{
			bool result = theCommandModule.ParseCommand(pInfo);

			if (result)
			{
				pInfo->result = eTaskResult_ResSucc;
			}
			else
				pInfo->result = eTaskResult_ResFail;

			n++;
			if (n >= MAX_GMTASK_COUNT)
			{
				break;
			}
		}
	}
}

bool CPlatformWorkSpace::AddWorkSpaceTask(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return false;
	}
	CSALocker lock(&_TaskLock);
	_WorkSpaceTaskList.push_back(pTask);
	return true;
}

SWorkSpaceTask* CPlatformWorkSpace::GetWorkSpaceTask()
{
	CSALocker lock(&_TaskLock);
	if ( _WorkSpaceTaskList.empty())
	{ return NULL;}

	SWorkSpaceTask* rMessage = _WorkSpaceTaskList.front();
	_WorkSpaceTaskList.pop_front();
	return rMessage;
}

void CPlatformWorkSpace::ReleaseWorkSpaceTask(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}
	CSALocker lock(&_TaskLock);
	ReleaseWorkSpaceTaskInfo(pTask);
}

#define MAX_ERROR_COUNT 50
void CPlatformWorkSpace::ProcessError()
{
	int n = 0;
	SErrorInfo* pError = NULL;
	while(pError = GetErrorTask())
	{
		if (pError)
		{
			if (pError->characterid > 0 && pError->accountid > 0 && pError->serverid >= 0)
			{
				CServerSession* pServerSession = GetServerSessionById(pError->serverid);
				if (pServerSession)
				{
					MsgPFModifyError msg;
					msg.characterid = pError->characterid;
					msg.accountid = pError->accountid;
					msg.result = pError->result;
					pServerSession->SendMsg(&msg);
				}
			}
			n++;
			if (n >= MAX_ERROR_COUNT)
			{
				break;
			}

			ReleaseErrorTask(pError);
		}
	}
}

bool CPlatformWorkSpace::AddErrorTask(SErrorInfo* pError)
{
	if (!pError)
	{
		return false;
	}
	CSALocker lock(&_TaskLock);
	_ErrorTaskList.push_back(pError);
	return true;
}

SErrorInfo* CPlatformWorkSpace::GetErrorTask()
{
	CSALocker lock(&_TaskLock);
	if ( _ErrorTaskList.empty())
	{ return NULL;}

	SErrorInfo* rMessage = _ErrorTaskList.front();
	_ErrorTaskList.pop_front();
	return rMessage;
}

void CPlatformWorkSpace::ReleaseErrorTask(SErrorInfo* pError)
{
	if (!pError)
	{
		return;
	}
	CSALocker lock(&_TaskLock);
	ReleaseErrorInfoTaskPool(pError);
}

#define MAX_NormalMAILTASK_COUNT 30
#define MAX_OtherMAILTASK_COUNT 30
void CPlatformWorkSpace::ProcessMailTask()
{
	int n =0;
	SMailTaskInfo* pInfo = NULL;
	while(pInfo = theMYSQLWorkSpace.GetMailTaskInfo())
	{
		if (pInfo&&pInfo->result == eTaskResult_ResNo)
		{
			bool result = theMailModule.ProcessMailTask(pInfo);

			if (result)
			{
				pInfo->result = eTaskResult_ResSucc;
			}
			else
				pInfo->result = eTaskResult_ResFail;

			n++;
			if (n >= MAX_NormalMAILTASK_COUNT)
			{
				break;
			}
		}
	}

	n =0;
	pInfo = NULL;
	while(pInfo = theMYSQLWorkSpace.GetOtherMailTaskInfo())
	{
		if (pInfo&&pInfo->result == eTaskResult_ResNo)
		{
			bool result = theMailModule.ProcessMailTask(pInfo);

			if (result)
			{
				pInfo->result = eTaskResult_ResSucc;
			}
			else
				pInfo->result = eTaskResult_ResFail;

			n++;
			if (n >= MAX_OtherMAILTASK_COUNT)
			{
				break;
			}
		}
	}
}

void CPlatformWorkSpace::OnMsgGetServerIdMsg(Msg* pMsg,CServerSession* pServer)
{
	if (!pMsg||!pServer)
	{
		return;
	}
	MsgC2PTellServerid* pId = (MsgC2PTellServerid*)pMsg;
	if (!pId)
	{
		return;
	}
	CServerSession* pServerSession = GetServerSessionById(pId->server_id);
	if (!pServerSession)
	{
		pServer->SetServerId(pId->server_id);
		_mapServer.insert(mapServer::value_type(pServer->GetServerId(),pServer));

		MsgP2CRegeResult msg;
		msg._result = eRegeResult_succ;
		pServer->SendMsg(&msg);
	}
	else
	{
		if (pServer == pServerSession)
		{
			MsgP2CRegeResult msg;
			msg._result = eRegeResult_Refrain;
			pServer->SendMsg(&msg);
		}
		else
		{
			MsgP2CRegeResult msg;
			msg._result = eRegeResult_fail;
			pServer->SendMsg(&msg);

			AddToServerWaitClose(pServer,__FUNCTION__, __LINE__);
		}
	}
}

void CPlatformWorkSpace::OnMsgAskForPresent (Msg* pMsg,CServerSession* pServer)
{
	if (!pMsg||!pServer||pServer->GetServerId() == -1)
	{
		return;
	}
	MsgPFAskForPresent* pAskFor = (MsgPFAskForPresent*)pMsg;
	if (!pAskFor)
	{
		return;
	}
	SWorkSpaceTask* pTask = CreateWorkSpaceTaskInfo();
	if (!pTask)
	{
		return;
	}
	pTask->s.askpresent.accountid = pAskFor->accountid;
	pTask->s.askpresent.characterid = pAskFor->characterid;
	strncpy_s(pTask->s.askpresent.sn,sizeof(pTask->s.askpresent.sn),pAskFor->sn,sizeof(pTask->s.askpresent.sn) - 1);
	strncpy_s(pTask->s.askpresent.charactername,sizeof(pTask->s.askpresent.charactername),pAskFor->charactername,sizeof(pTask->s.askpresent.charactername) - 1);
	pTask->serverid = pServer->GetServerId();
	pTask->tasktype = eWorkSpaceTask_AskPresent;
	pTask->result = eTaskResult_ResNo;

	AddWorkSpaceTask(pTask);
}

void CPlatformWorkSpace::OnMsgAskForActivity(Msg* pMsg,CServerSession* pServer)
{
	if (!pMsg||!pServer||pServer->GetServerId() == -1)
	{
		return;
	}
	MsgPFAskForActivity* pAskFor = (MsgPFAskForActivity*)pMsg;
	if (!pAskFor)
	{
		return;
	}

	SWorkSpaceTask* pTask = CreateWorkSpaceTaskInfo();
	if (!pTask)
	{
		return;
	}
	pTask->s.askactivity.accountid = pAskFor->accountid;
	pTask->s.askactivity.characterid = pAskFor->characterid;
	pTask->s.askactivity._type = pAskFor->_type;
	strncpy_s(pTask->s.askactivity.charactername,sizeof(pTask->s.askactivity.charactername),pAskFor->charactername,sizeof(pTask->s.askactivity.charactername) - 1);
	pTask->serverid = pServer->GetServerId();
	pTask->tasktype = eWorkSpaceTask_AskActivity;
	pTask->result = eTaskResult_ResNo;

	AddWorkSpaceTask(pTask);
}
void CPlatformWorkSpace::OnMsgPFEpistarPoint(Msg* pMsg,CServerSession* pServer)
{
	if (!pMsg||!pServer||pServer->GetServerId() == -1)
	{
		return;
	}
	MsgPFEpistarPoint* pEpistarPoint = (MsgPFEpistarPoint*)pMsg;
	if (!pEpistarPoint)
	{
		return;
	}
	SWorkSpaceTask* pTask = CreateWorkSpaceTaskInfo();
	if (!pTask)
	{
		return;
	}
	pTask->s.askEpistarPoint.accountid		= pEpistarPoint->accountid;
	pTask->s.askEpistarPoint.characterid	= pEpistarPoint->characterid;
	pTask->s.askEpistarPoint._type			= pEpistarPoint->_type;
	pTask->s.askEpistarPoint.nItemId		= pEpistarPoint->nItemId;
	pTask->s.askEpistarPoint.nPoint			= pEpistarPoint->nPoint;
	strncpy_s(pTask->s.askEpistarPoint.charactername,sizeof(pTask->s.askEpistarPoint.charactername),pEpistarPoint->charactername,sizeof(pTask->s.askEpistarPoint.charactername) - 1);
	pTask->serverid = pServer->GetServerId();
	pTask->tasktype = eWorkSpaceTask_EpistarPoint;
	pTask->result = eTaskResult_ResNo;
	AddWorkSpaceTask(pTask);
}