#pragma once

#include "DataCenterConfig.h"
#include "mysql++.h"
#include "GameTimer.h"

enum EMySqlStatus
{
	MS_TryConnect,
	MS_Connected,
	MS_ReConnected,

	MS_PingTime					= 3 * 1000 * 60, // 3 ����
};

class CServerStatus
{
public:
	CServerStatus(void);
	~CServerStatus(void);
	
	void _TryConnectToSqlDb();
	bool _CheckState();        // ���SqlService�������
	void SetServerConfig(CDataCenterConfig::sServerConfig* pSC);
	CDataCenterConfig::sServerConfig* GetServerConfig(){return m_pServerConfig;}
	int GetServerStatus(int count,const char* datetime);//��������������ʱ������״̬

	void Run();
	bool ProcessStatus();
private:
	bool  bInit;  //�Ƿ��ʼ��
	mysqlpp::Connection* _mySqlConnection;// ��mysql ������
	unsigned char _workState;
	//GameTimerEx          _connectTime;    // ����ʱ��������
	unsigned long        _lastUpdateTime; // ���µĸ���ʱ��
	unsigned long		 _lastSaveTime;   // ��������ʱ��

	CDataCenterConfig::sServerConfig* m_pServerConfig;//����������	
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