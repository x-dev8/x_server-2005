#pragma once

#include "PlatformWorkSpace.h"
#include "GameTimer.h"
#include "objectpool.h"
#include "PlatformDefine.h"
#include "Mutex.h"
#include "mysql++.h"

#define GM_TASK_MAX 1000

static poolmgr<SGMTaskInfo> &GMTaskPool ()
{
	static poolmgr<SGMTaskInfo> m(GM_TASK_MAX, "GM Task Pool");
	return m;
}
static SGMTaskInfo *CreateGMTaskInfo ()
{	
	SGMTaskInfo *self = GMTaskPool().GetObject();
	if (!self)
	{
		return NULL;
	}
	self->SGMTaskInfo::SGMTaskInfo();
	return self;
}
static void ReleaseGMTaskInfo (SGMTaskInfo *self)
{
	if (!self)
		return;
	self->SGMTaskInfo::~SGMTaskInfo();
	GMTaskPool().FreeObject(self);
}

typedef std::list<SGMTaskInfo*>         ContainerGMTaskInfo;
typedef ContainerGMTaskInfo::iterator   ItrContainerGMTaskInfo;

typedef std::map<int,SGMTaskInfo*> mapGMTaskInfo;

////////////////////////////////////////////////////////////////////////////
#define MAIL_TASK_MAX 5000

typedef std::list<SMailTaskInfo*>         ContainerMailTaskInfo;
typedef ContainerMailTaskInfo::iterator   ItrContainerMailTaskInfo;

typedef std::map<int,SMailTaskInfo*> mapMailTaskInfo;

typedef std::vector<SMailTaskInfo*> vecMailTaskInfo;

///////////////////////////////////////////////////////////////////

class CMySQLWorkSpace
{
public:
	static poolmgr<SMailTaskInfo> &MailTaskPool ()
	{
		static poolmgr<SMailTaskInfo> m(MAIL_TASK_MAX, "Mail Task Pool");
		return m;
	}
	static SMailTaskInfo *CreateMailTaskInfo ()
	{	
		SMailTaskInfo *self = MailTaskPool().GetObject();
		if (!self)
		{
			return NULL;
		}
		self->SMailTaskInfo::SMailTaskInfo();
		return self;
	}
	static void ReleaseMailTaskInfo (SMailTaskInfo *self)
	{
		if (!self)
			return;
		self->SMailTaskInfo::~SMailTaskInfo();
		MailTaskPool().FreeObject(self);
	}	
public:
	enum EWorkStatus
	{
		SS_TryConnect,
		SS_Connected,
		SS_ReConnected,
	};
	enum EConstDefine
	{
		ECD_PingTime            = 3 * 1000 * 60, // 3 ����
		ECD_ConnectIntervalTime = 1000,     // 1 ��
		ECD_GETGMTASKTIME         = 10*1000,  //10��һ��ɨ�������ݿ�
		ECD_GETMAILTASKTIME		= 30*1000, //30sһ��ɨ���ʼ��б����ݿ�
	};
public:
	CMySQLWorkSpace(void);
	~CMySQLWorkSpace(void);
	static CMySQLWorkSpace& Instance()
	{
		static CMySQLWorkSpace cws;
		return cws;
	}

	void _TryConnectToSqlDb();
	bool _CheckState();        // ���SqlService�������
	void Run();
	uint8 GetWorkState(){return _workState;}

	//GM����
	void RunGMTask();
	bool GetGMTaskInfoInMYSql();
	bool AddNomalGMTaskInfo(SGMTaskInfo* pInfo);
	SGMTaskInfo* GetGMTaskInfo();
	void ChenckTaskResult();

	//mail
	void RunMailTask();
	bool GetMailTaskInfoInMYSql();
	bool AddNomalMailTaskInfo(SMailTaskInfo* pInfo);
	bool AddOthermailTaskInfo(SMailTaskInfo* pInfo);
	SMailTaskInfo* GetMailTaskInfo();
	SMailTaskInfo* GetOtherMailTaskInfo();
	void ChenckMailTaskResult();

	//workspace
	void RunWorkSpaceTask();	
	void ChenckWorkSpaceTaskResult();
	void AddWorkSpaceTaskResult(SWorkSpaceTask* pTask);
	SWorkSpaceTask* GetWorkSpaceTaskResult();

	mysqlpp::Connection* GetMySqlConnect(){return _pMysqlConnect;}
private:
	CSemiAutoIntLock     _TaskLock;

	mysqlpp::Connection* _pMysqlConnect;  // ��mysql ������
	uint8				 _workState;      // ���ӵ�״̬
	GameTimerEx          _connectTime;    // ����ʱ��������
	uint32               _lastUpdateTime; // ���µĸ���ʱ��
	uint32				 _lastGetGMTaskTime;// ���»�ȡGM�����ʱ��
	mapGMTaskInfo		 _mapGMTaskInfo;  // �մ����ݿ��ȡ�������,��ҪΨһ�Լ��
	ContainerGMTaskInfo	 _GmTaskInfoList;		//�������,���ڶ��̲߳���

	uint32				 _lastGetMailTaskTime;// ���»�ȡ�ʼ������ʱ��
	mapMailTaskInfo		 _mapMailTaskInfo;  // �մ����ݿ��ȡ���ʼ������,��ҪΨһ�Լ��
	ContainerMailTaskInfo	 _MailTaskInfoList;	//�������,���ڶ��̲߳���
	vecMailTaskInfo			 _vecOtherMailTaskInfo;
	ContainerMailTaskInfo    _OtherMailTaskInfoList;//�������ܳ����ķ���maillist

	ContainerWorkSpaceTask _WorkSpaceTaskListResult;
};

#define theMYSQLWorkSpace CMySQLWorkSpace::Instance()