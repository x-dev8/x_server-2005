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
	//����
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
	Listener*		m_psockClientListen;  //�ͻ��˼���
	Listener*		m_pListenServer;      //����������

	static CWorkThread g_SqlServiceThread;
	static CWorkThread g_MainLogicThread;

	CStaticArray<CServerSession*>* m_pNormalServers;    // �����ķ���������
	CStaticArray<CServerSession*>* m_pServerWaitClose;  // �ȴ��ӳ�ɾ������������

	typedef std::map<int,CServerSession*> mapServer;
	mapServer							  _mapServer;   //����server id��֤�ɹ������Ӽ���

	ContainerWorkSpaceTask				_WorkSpaceTaskList;		//�������,���ڶ��̲߳���

	ContainerErrorTask					_ErrorTaskList;//�����������ļ���
};

#define thePlatFormWorkSpace CPlatformWorkSpace::Instance()