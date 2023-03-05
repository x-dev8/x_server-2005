//���ʺ����ݿ�Ĳ����� by vvx 2012.4.9
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

	//��֤�ʺţ���򵥵���֤,�����ʺ�ID
	unsigned long CheckAccount(const char* AccountName,const char* AccountPWD);
private:
	mysqlpp::Connection* _pMysqlConnect;  // ��mysql ������
	uint8 _workState;      // ���ӵ�״̬
	GameTimerEx          _connectTime;    // ����ʱ��������
	uint32               _lastUpdateTime; // ���µĸ���ʱ��
};