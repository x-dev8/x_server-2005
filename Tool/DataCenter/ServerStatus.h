#pragma once

#include "DataCenterConfig.h"
#include "mysql++.h"
#include "GameTimer.h"

enum EMySqlStatus
{
	MS_TryConnect,
	MS_Connected,
	MS_ReConnected,

	MS_PingTime					= 3 * 1000 * 60, // 3 分钟
};

class CServerStatus
{
public:
	CServerStatus(void);
	~CServerStatus(void);
	
	void _TryConnectToSqlDb();
	bool _CheckState();        // 检查SqlService运行情况
	void SetServerConfig(CDataCenterConfig::sServerConfig* pSC);
	CDataCenterConfig::sServerConfig* GetServerConfig(){return m_pServerConfig;}
	int GetServerStatus(int count,const char* datetime);//根据在线人数和时间设置状态

	void Run();
	bool ProcessStatus();
private:
	bool  bInit;  //是否初始化
	mysqlpp::Connection* _mySqlConnection;// 和mysql 的连接
	unsigned char _workState;
	//GameTimerEx          _connectTime;    // 连接时间间隔控制
	unsigned long        _lastUpdateTime; // 最新的更新时间
	unsigned long		 _lastSaveTime;   // 最后的生成时间

	CDataCenterConfig::sServerConfig* m_pServerConfig;//服务器属性	
};


class CServerStatusManager
{
public:
	CServerStatusManager(void);
	~CServerStatusManager(void);

	static CServerStatusManager& Instance()
	{
		static CServerStatusManager cssm;
		return cssm;
	}

	void Run();
	void SaveServerListConfig();
	bool Init();
private:
	typedef vector<CServerStatus*> vecServerStatus;
	vecServerStatus				   _vecServerStatus;
	unsigned long                  _lastsavetime;
	bool bIsInit;
};
#define theServerStatusManager CServerStatusManager::Instance()