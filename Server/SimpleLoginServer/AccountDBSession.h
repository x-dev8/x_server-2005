//与帐号数据库的操作类 by vvx 2012.4.9
#pragma once
//#include "MeRTLibsServer.h"
#include "mysql++.h"
#include "GameTimer.h"

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

	//验证帐号，最简单的验证,返回帐号ID
	unsigned long CheckAccount(const char* AccountName,const char* AccountPWD);
private:
	mysqlpp::Connection* _pMysqlConnect;  // 和mysql 的连接
	uint8 _workState;      // 连接的状态
	GameTimerEx          _connectTime;    // 连接时间间隔控制
	uint32               _lastUpdateTime; // 最新的更新时间
};