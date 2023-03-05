//与帐号数据库的操作类 by vvx 2012.4.9
#pragma once
//#include "MeRTLibsServer.h"
#include "mysql++.h"
#include "GameTimer.h"
#include "MySqlTaskDefine.h"
#include "Mutex.h"
#include "objectpool.h"
//
#define ACK_CHECK_ACCOUNT_MAX 3000
//static poolmgr<SAckCheckAccount> &AckCheckAccountPool ()
//{
//	static poolmgr<SAckCheckAccount> m(ACK_CHECK_ACCOUNT_MAX, "ack check account pool");
//	return m;
//}
static SAckCheckAccount *CreateAckCheckAccount ()
{	
	SAckCheckAccount *self = SAckCheckAccount::CreateInstance();
	if (!self)
	{
		return NULL;
	}
	//self->SAckCheckAccount::SAckCheckAccount();
	return self;
}
static void ReleaseAckCheckAccount (SAckCheckAccount *self)
{
	if (!self)
		return;
	self->Release();
}


typedef std::list<SReqCheckAccount*>         SqlMessageContainerCheckAccount;
typedef SqlMessageContainerCheckAccount::iterator ItrSqlMessageContainerCheckAccount;

class CAccountDBSession
{
public:
	enum EWorkStatus
	{
		SS_TryConnect,
		SS_Connected,
		SS_ReConnected,
	};

	enum EConstDefine
	{
		ECD_PingTime            = 3 * 1000, // 3 分钟
		ECD_ConnectIntervalTime = 1000,     // 1 秒
	};

public:
	CAccountDBSession(void);
	~CAccountDBSession(void);

	static CAccountDBSession& Instance()
	{
		static CAccountDBSession cadbs;
		return cadbs;
	}

	void _TryConnectToSqlDb();
	bool _CheckState();        // 检查SqlService运行情况

	void TestSQLDb();//测试数据库
	uint8 GetWorkState(){return _workState;}
	void SetService(bool b){_service = b;}
	bool GetService(){return _service ;}
	bool GetConnectState(){return _workState == SS_Connected;}

	void Run();

	//验证帐号，最简单的验证,返回帐号ID
	//unsigned long CheckAccount(const char* AccountName,const char* AccountPWD);

	bool PushTask(/*const */SReqCheckAccount* pTask);
	SReqCheckAccount* GetTaskQueryMessage( /*SReqCheckAccount& rMessage*/ );	
	void ReleaseAckCheckAccountPool(SAckCheckAccount* pTask);
	void ProcessTask();

	void OnTaskCheckAccount(SReqCheckAccount* pTask);
private:
	mysqlpp::Connection* _pMysqlConnect;  // 和mysql 的连接
	uint8				 _workState;      // 连接的状态
	GameTimerEx          _connectTime;    // 连接时间间隔控制
	uint32               _lastUpdateTime; // 最新的更新时间

	SqlMessageContainerCheckAccount  _TaskQuerys;     //任务队列
	CSemiAutoIntLock     _TaskQuerysLock;

	bool                 _service;          //服务器是否开启
};
#define theAccountDBSession CAccountDBSession::Instance()