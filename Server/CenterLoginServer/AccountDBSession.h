//���ʺ����ݿ�Ĳ����� by vvx 2012.4.9
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
		ECD_PingTime            = 3 * 1000, // 3 ����
		ECD_ConnectIntervalTime = 1000,     // 1 ��
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
	bool _CheckState();        // ���SqlService�������

	void TestSQLDb();//�������ݿ�
	uint8 GetWorkState(){return _workState;}
	void SetService(bool b){_service = b;}
	bool GetService(){return _service ;}
	bool GetConnectState(){return _workState == SS_Connected;}

	void Run();

	//��֤�ʺţ���򵥵���֤,�����ʺ�ID
	//unsigned long CheckAccount(const char* AccountName,const char* AccountPWD);

	bool PushTask(/*const */SReqCheckAccount* pTask);
	SReqCheckAccount* GetTaskQueryMessage( /*SReqCheckAccount& rMessage*/ );	
	void ReleaseAckCheckAccountPool(SAckCheckAccount* pTask);
	void ProcessTask();

	void OnTaskCheckAccount(SReqCheckAccount* pTask);
private:
	mysqlpp::Connection* _pMysqlConnect;  // ��mysql ������
	uint8				 _workState;      // ���ӵ�״̬
	GameTimerEx          _connectTime;    // ����ʱ��������
	uint32               _lastUpdateTime; // ���µĸ���ʱ��

	SqlMessageContainerCheckAccount  _TaskQuerys;     //�������
	CSemiAutoIntLock     _TaskQuerysLock;

	bool                 _service;          //�������Ƿ���
};
#define theAccountDBSession CAccountDBSession::Instance()