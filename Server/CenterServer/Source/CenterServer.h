#ifndef __CENTERSERVER_APPLICATION_H__
#define __CENTERSERVER_APPLICATION_H__

#pragma once

#include "TcpServer.h"
#include "TcpClient.h"
#include "WorkThread.h"
#include "NetEvent.h"
#include "SqlService.h"
#include "EventTimeTable.h"

// ˢ��ʱ��Ϊ1����
#define LOGININFO_UPDATETIME_INTERVAL (1000 * 60)

// ��������ʱ��Ϊ10����
#define ALLOW_CONNECT_GATESERVER_TIME (1000 * 60 *10)

struct SGameWorldStatistics
{ // 
    unsigned long loginClientPeer;      // �µ�¼��
    unsigned long activeExitClientPeer; // �����˳�
    unsigned long kicklExitClientPeer;  // �����˳�
};

#define theCenterServer CenterServer::GetInstance()

class ConsoleApplication;
class CenterServer 
{
public:
    enum EConstDefine
    {
        ECD_StatisticsTimeInterval        = 20000, // 20 ��
        ECD_MaxPlatformCount              = 200,
        ECD_ReconnectPlatformTimeInterval = 1000, // 1 ��
    };
    
    enum EConnectPlatformStatus
    {   
        CPS_TryConnect, // ��ͼ������Ϸ���������
        CPS_ReConnect,  // ����
        CPS_Normal,     // ��������״̬
    };

public:
    static void Main( void* pParam );    
    static void SqlMain( void* pParam);

    static CWorkThread g_MainLogicThread;    
    static CWorkThread g_SqlServiceThread;
	static CWorkThread g_configReloaderThread;// �����������߳�

    static CenterServer& GetInstance();
    ~CenterServer();

    // ������
    long   Init( ConsoleApplication* pOwner );
    long   RunOnce();
    void   UnInit();

    void   CloseConnection( EServerType st, NetClient* pNetClient );

    void   AddLoginInfo( __int64 nSessionKey, const SLoginInfoBase& lis );

    bool   IsGameServerService ( TcpServer* pService ) { return (pService == &_serviceForGameServer);  }
    //bool IsLoginServerService( TcpServer* pService ) { return (pService == &_serviceForLoginServer); }
    bool   IsDabaseConnecter   ( NetClient* pClient  ) { return (pClient == &_databaseServerConnector);}
	bool   IsLoginServer   ( NetClient* pClient  ) { return (pClient == &_loginserverConnector);}

    unsigned long GetGameServerCount() { return _serviceForGameServer.GetConnectionCount(); }
    unsigned long GetLoginServerCount() { return 1/*_serviceForLoginServer.GetConnectionCount()*/; }
   // SqlService&   GetSqlService() { return _serviceSql; }

	// ���ӵ����� �� ������������
    void   RunDatabaseServerCommunication();
    bool   IsConnectingDatabaseServer() { return _databaseServerConnector.GetConnectState() == TcpClient::CS_Connected; }

	void   RunLoginServerCommunication();
	bool   IsConnectingLoginServer() { return _loginserverConnector.GetConnectState() == TcpClient::CS_Connected;}
	void   PingLoginServer();
	
	// ���ӵ�����
	bool   IsConnectingPlatform() { return _connectPlatformStatus == CPS_Normal; }
	int    GetPlatformConnecterSize() { return (int)_platformConnecters.size(); }

	uint32 SendMessageToLogin( Msg* pMessage );
    uint32 SendMessageToDb( Msg* pMessage );
    uint32 SendMessageToPlatform( uint32 platformId, Msg* pMessage );

    uint32 SendMessageToPlatform( Msg* pMessage );

    void   TryToConnectPlatform(); // ����
    uint32 CreateToConnectPlatformSocket();

    void   NotifyGLSAccountSafeOffLine( unsigned long accountId, const char* accountName );
    void   NotifyGLSValidKick         ( unsigned long accountId, const char* accountName );
    void   NotifyGLSPlayerExit        ( unsigned long accountId, const char* accountName, uint32 blockTime = 0 );//ֻ��time>0��Ч

    uint32 GetShutdownTime() { return _revShutdownCommandTime; }
    void   CheckForServerExit();
	void   SetLoginServerPingTime(uint32 pingtime){_LoginServerPingTime = pingtime;}
protected:
    CenterServer();
    CenterServer( const CenterServer& );
    CenterServer& operator=( const CenterServer& ){}

    void   _UpdateLoginInfo();
    void   _ProcessSqlMessage();
    void   _Statistics();
         
    void   _PlatformAcceptRun();
    bool   _AcceptPlatform();
    void   _RecvPlatformMessageRun();
    void   _SendPlatformMessageRun();
    void   _ProcessPlatformMessageRun();

    void PartitionLogFile();

    uint32 _GetPlatClientID();

    // FlatformMessageHandleFunction
#include "PlatformMessageHandle.h"    

public:    
    SGameWorldStatistics gGameWorldStatistics; // ��Ϸ����ͳ������
    bool                 bCommandCloseAllServer; // �Ƿ�ȫ����ر�

private:
    typedef std::map<__int64, SLoginInfoBase> LoginInfoContainer;
    typedef LoginInfoContainer::iterator      ItrLoginInfoContainer;

    typedef std::map<uint32, /*IMeConnector*/Socketer*>      PlatformConnecterContainer;
    typedef PlatformConnecterContainer::iterator ItrPlatformConnecterContainer;

    PlatformConnecterContainer _platformConnecters; // �������ͻ��˼��� ��ֵ GM 

    NetEvent             _netevent;
    TcpServer            _serviceForGameServer;    // ���Ÿ�GameServer�ķ���
    //TcpServer            _serviceForLoginServer;   // ���Ÿ�LoginServer�ķ��� ��Ҫ�޸�
    TcpClient            _databaseServerConnector; // ����Dataserver�ķ���
	TcpClient            _loginserverConnector; // ����loginserver�ķ���

    //SqlService           _serviceSql;
    LoginInfoContainer   _loginInfos;
    DWORD                _nLastUpdateLoginInfoTime;
    uint32               _lastRunOnceTime;         // �ϴ�RuntimeInfoOnceʱ��
    uint32               _lastStatisticsTime;      // �ϴ�ͳ�Ƶ�ʱ��
    /*IMeSocket*/Listener*           _platformService;         // ���Ÿ�ƽ̨�ķ���[����ĵ�������Ϣ]
    
    /*IMeConnector*/Socketer*        _pToPlatformConnecter;    // ���ӵ�����ƽ̨�������� [��ѯƽ̨����]
    uint32               _connectPlatformStatus;   // ����ƽ̨��״̬
    uint32               _lastReconnectTime;       // ����ʱ��

    uint32               _revShutdownCommandTime;
    uint32               _revShutdownDelayTime;

    unsigned int         _dwPartitionLogTile;        // �ָ�LOG��ʱ��
    ConsoleApplication*  _pOwner;

	uint32 _LoginServerPingTime; //�յ�login server ping��ʱ��
private:
    static CenterServer* pApplicationInstance;
};

#endif // __CENTERSERVER_APPLICATION_H__
