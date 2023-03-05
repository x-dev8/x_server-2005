#ifndef __CENTERSERVER_APPLICATION_H__
#define __CENTERSERVER_APPLICATION_H__

#pragma once

#include "TcpServer.h"
#include "TcpClient.h"
#include "WorkThread.h"
#include "NetEvent.h"
#include "SqlService.h"
#include "EventTimeTable.h"

// 刷新时间为1分钟
#define LOGININFO_UPDATETIME_INTERVAL (1000 * 60)

// 允许连接时间为10分钟
#define ALLOW_CONNECT_GATESERVER_TIME (1000 * 60 *10)

struct SGameWorldStatistics
{ // 
    unsigned long loginClientPeer;      // 新登录的
    unsigned long activeExitClientPeer; // 主动退出
    unsigned long kicklExitClientPeer;  // 被踢退出
};

#define theCenterServer CenterServer::GetInstance()

class ConsoleApplication;
class CenterServer 
{
public:
    enum EConstDefine
    {
        ECD_StatisticsTimeInterval        = 20000, // 20 秒
        ECD_MaxPlatformCount              = 200,
        ECD_ReconnectPlatformTimeInterval = 1000, // 1 秒
    };
    
    enum EConnectPlatformStatus
    {   
        CPS_TryConnect, // 试图连接游戏世界服务器
        CPS_ReConnect,  // 重连
        CPS_Normal,     // 正常连接状态
    };

public:
    static void Main( void* pParam );    
    static void SqlMain( void* pParam);

    static CWorkThread g_MainLogicThread;    
    static CWorkThread g_SqlServiceThread;
	static CWorkThread g_configReloaderThread;// 配置热重载线程

    static CenterServer& GetInstance();
    ~CenterServer();

    // 主流程
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

	// 连接第三方 和 第三方链接我
    void   RunDatabaseServerCommunication();
    bool   IsConnectingDatabaseServer() { return _databaseServerConnector.GetConnectState() == TcpClient::CS_Connected; }

	void   RunLoginServerCommunication();
	bool   IsConnectingLoginServer() { return _loginserverConnector.GetConnectState() == TcpClient::CS_Connected;}
	void   PingLoginServer();
	
	// 连接第三方
	bool   IsConnectingPlatform() { return _connectPlatformStatus == CPS_Normal; }
	int    GetPlatformConnecterSize() { return (int)_platformConnecters.size(); }

	uint32 SendMessageToLogin( Msg* pMessage );
    uint32 SendMessageToDb( Msg* pMessage );
    uint32 SendMessageToPlatform( uint32 platformId, Msg* pMessage );

    uint32 SendMessageToPlatform( Msg* pMessage );

    void   TryToConnectPlatform(); // 连接
    uint32 CreateToConnectPlatformSocket();

    void   NotifyGLSAccountSafeOffLine( unsigned long accountId, const char* accountName );
    void   NotifyGLSValidKick         ( unsigned long accountId, const char* accountName );
    void   NotifyGLSPlayerExit        ( unsigned long accountId, const char* accountName, uint32 blockTime = 0 );//只对time>0有效

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
    SGameWorldStatistics gGameWorldStatistics; // 游戏世界统计数据
    bool                 bCommandCloseAllServer; // 是否全服务关闭

private:
    typedef std::map<__int64, SLoginInfoBase> LoginInfoContainer;
    typedef LoginInfoContainer::iterator      ItrLoginInfoContainer;

    typedef std::map<uint32, /*IMeConnector*/Socketer*>      PlatformConnecterContainer;
    typedef PlatformConnecterContainer::iterator ItrPlatformConnecterContainer;

    PlatformConnecterContainer _platformConnecters; // 第三方客户端集合 冲值 GM 

    NetEvent             _netevent;
    TcpServer            _serviceForGameServer;    // 开放给GameServer的服务
    //TcpServer            _serviceForLoginServer;   // 开放给LoginServer的服务 需要修改
    TcpClient            _databaseServerConnector; // 连接Dataserver的服务
	TcpClient            _loginserverConnector; // 连接loginserver的服务

    //SqlService           _serviceSql;
    LoginInfoContainer   _loginInfos;
    DWORD                _nLastUpdateLoginInfoTime;
    uint32               _lastRunOnceTime;         // 上次RuntimeInfoOnce时间
    uint32               _lastStatisticsTime;      // 上次统计的时间
    /*IMeSocket*/Listener*           _platformService;         // 开放给平台的服务[特殊的第三方消息]
    
    /*IMeConnector*/Socketer*        _pToPlatformConnecter;    // 连接第三方平台的连接器 [查询平台数据]
    uint32               _connectPlatformStatus;   // 连接平台的状态
    uint32               _lastReconnectTime;       // 重连时间

    uint32               _revShutdownCommandTime;
    uint32               _revShutdownDelayTime;

    unsigned int         _dwPartitionLogTile;        // 分割LOG的时间
    ConsoleApplication*  _pOwner;

	uint32 _LoginServerPingTime; //收到login server ping的时间
private:
    static CenterServer* pApplicationInstance;
};

#endif // __CENTERSERVER_APPLICATION_H__
