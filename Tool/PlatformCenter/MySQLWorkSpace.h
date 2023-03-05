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
		ECD_PingTime            = 3 * 1000 * 60, // 3 分钟
		ECD_ConnectIntervalTime = 1000,     // 1 秒
		ECD_GETGMTASKTIME         = 10*1000,  //10秒一次扫任务数据库
		ECD_GETMAILTASKTIME		= 30*1000, //30s一次扫描邮件列表数据库
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
	bool _CheckState();        // 检查SqlService运行情况
	void Run();
	uint8 GetWorkState(){return _workState;}

	//GM任务
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

	mysqlpp::Connection* _pMysqlConnect;  // 和mysql 的连接
	uint8				 _workState;      // 连接的状态
	GameTimerEx          _connectTime;    // 连接时间间隔控制
	uint32               _lastUpdateTime; // 最新的更新时间
	uint32				 _lastGetGMTaskTime;// 最新获取GM任务的时间
	mapGMTaskInfo		 _mapGMTaskInfo;  // 刚从数据库读取的命令集合,主要唯一性检测
	ContainerGMTaskInfo	 _GmTaskInfoList;		//命令队列,用于多线程操作

	uint32				 _lastGetMailTaskTime;// 最新获取邮件任务的时间
	mapMailTaskInfo		 _mapMailTaskInfo;  // 刚从数据库读取的邮件命令集合,主要唯一性检测
	ContainerMailTaskInfo	 _MailTaskInfoList;	//命令队列,用于多线程操作
	vecMailTaskInfo			 _vecOtherMailTaskInfo;
	ContainerMailTaskInfo    _OtherMailTaskInfoList;//其他功能出发的发送maillist

	ContainerWorkSpaceTask _WorkSpaceTaskListResult;
};

#define theMYSQLWorkSpace CMySQLWorkSpace::Instance()