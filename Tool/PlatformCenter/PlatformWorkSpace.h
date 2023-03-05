#pragma once
#include "network.h"
#include "WorkThread.h"
#include "MessageDefine.h"
#include "StaticArray.h"
#include "ServerSession.h"
#include "Mutex.h"
#include "PlatformDefine.h"
#include "objectpool.h"

using namespace network;

#define Error_Task_Max 5000
#define WORKSPACETASK_MAX 1000

static poolmgr<SWorkSpaceTask> &WorkSpaceTaskPool ()
{
	static poolmgr<SWorkSpaceTask> m(WORKSPACETASK_MAX, "work space Task Pool");
	return m;
}
static SWorkSpaceTask *CreateWorkSpaceTaskInfo ()
{	
	SWorkSpaceTask *self = WorkSpaceTaskPool().GetObject();
	if (!self)
	{
		return NULL;
	}
	self->SWorkSpaceTask::SWorkSpaceTask();
	return self;
}
static void ReleaseWorkSpaceTaskInfo (SWorkSpaceTask *self)
{
	if (!self)
		return;
	self->SWorkSpaceTask::~SWorkSpaceTask();
	WorkSpaceTaskPool().FreeObject(self);
}


typedef std::list<SWorkSpaceTask*>         ContainerWorkSpaceTask;
typedef ContainerWorkSpaceTask::iterator   ItrContainerWorkSpaceTask;

typedef std::list<SErrorInfo*>          ContainerErrorTask;
typedef ContainerErrorTask::iterator	ItrContainerErrorTask;

class CPlatformWorkSpace
{
public:
	//错误
	static poolmgr<SErrorInfo> &ErrorInfoTaskPool ()
	{
		static poolmgr<SErrorInfo> m(Error_Task_Max, "error Task Pool");
		return m;
	}
	static SErrorInfo *CreateErrorInfoTaskPool ()
	{	
		SErrorInfo *self = ErrorInfoTaskPool().GetObject();
		if (!self)
		{
			return NULL;
		}
		self->SErrorInfo::SErrorInfo();
		return self;
	}
	static void ReleaseErrorInfoTaskPool (SErrorInfo *self)
	{
		if (!self)
			return;
		self->SErrorInfo::~SErrorInfo();
		ErrorInfoTaskPool().FreeObject(self);
	}
public:
	CPlatformWorkSpace(void);
	~CPlatformWorkSpace(void);

	static CPlatformWorkSpace& Instance()
	{
		static CPlatformWorkSpace spws;
		return spws;
	}

	static void SqlMain( void* pParam); 
	static void Main( void* pParam );

	bool		   Init();
	void		   RunOneStep();

	//logic
	void           ProcessGMTask();
	void           ProcessMailTask();
	void           ProcessError();

	bool           AddWorkSpaceTask(SWorkSpaceTask* pTask);
	SWorkSpaceTask* GetWorkSpaceTask();	
	void           ReleaseWorkSpaceTask(SWorkSpaceTask* pTask);

	bool           AddErrorTask(SErrorInfo* pError);
	SErrorInfo*    GetErrorTask();
	void		   ReleaseErrorTask(SErrorInfo* pError);
	//server
	void		   RunServer();
	bool           AcceptNewServer();
	void           ProcessAllServerMsg();
	void           SendAllServerMsg();
	void           RecvAllServerMsg();
	void           CloseAllServer();
	void           SendMsgToAllServer(Msg* pMsg);
	void           AddToServerWaitClose( CServerSession* pServer, char* szFun, int nLine );//
	void           CheckServerWaitClose( bool bWait = true );
	bool		   SendMsgToSingleServer(Msg* pMsg,int serverid);
	CServerSession* GetServerSessionById(int serverid);
	//void		   RelatingServerAndServerId(CServerSession* pServer,int serverid);

	void           OnMsgGetServerIdMsg(Msg* pMsg,CServerSession* pServer);
	void		   OnMsgAskForPresent (Msg* pMsg,CServerSession* pServer);
	void		   OnMsgAskForActivity(Msg* pMsg,CServerSession* pServer);
	void		   OnMsgPFEpistarPoint(Msg* pMsg,CServerSession* pServer);
	

	//client

private:
	CSemiAutoIntLock     _TaskLock;
	Listener*		m_psockClientListen;  //客户端监听
	Listener*		m_pListenServer;      //服务器监听

	static CWorkThread g_SqlServiceThread;
	static CWorkThread g_MainLogicThread;

	CStaticArray<CServerSession*>* m_pNormalServers;    // 正常的服务器连接
	CStaticArray<CServerSession*>* m_pServerWaitClose;  // 等待延迟删除服务器连接

	typedef std::map<int,CServerSession*> mapServer;
	mapServer							  _mapServer;   //所有server id认证成功的连接集合

	ContainerWorkSpaceTask				_WorkSpaceTaskList;		//命令队列,用于多线程操作

	ContainerErrorTask					_ErrorTaskList;//操作错误结果的集合
};

#define thePlatFormWorkSpace CPlatformWorkSpace::Instance()