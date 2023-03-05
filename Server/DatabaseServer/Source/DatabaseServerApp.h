/********************************************************************
    Filename:     DatabaseServerApp.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASESERVER_DATABASESERVER_H__
#define __DATABASESERVER_DATABASESERVER_H__

#pragma once

//#include "MeNetwork.h"
//#include "MeConnector.h"
//#include "MapContainer.h"
#include "MapStrToID.h"
//#include "NetworkApp.h"
#include "DatabaseInterface.h"
#include "MySqlCommunication.h"
#include "network.h"
#include "StaticArray.h"

using namespace network;
class DatabaseClient;

#define APPLICATION_NAME "DatabaseServer"

#define theDatabaseServerApp GetDatabaseServerApp()

class DatabaseServerApp/* : public INetworkApp*/
{
public:
    enum ESqlType
    {
        ST_MSSql,
        ST_MySql,
    };
    DatabaseServerApp();
    ~DatabaseServerApp();

    uint32 Init( const char* szConfigFilePath );
    void   ShutDown();
    void   Update();

    WORD   GetListenPort() { return m_wListenPort;      }
    //size_t GetNodeSize()   { return m_NodeMgr.GetSize();}
    void   CheckForServerExit();
    bool   InitDBServerLog();   // 初始化DB的Log4cxx
	void RunOneStep();
	bool AcceptNewClient();
	void RecvAllClientMsg();
	void ProcessClientMsg();
	void SendAllClientMsg();

	void SendMsgToAllClient(Msg* pMsg);
protected:
    bool LoadConfig( const char* szConfigFilePath, int& nResultError );
    bool InitNetSetting();

public:
    std::string m_strDatabaseName;
    
    bool m_bUseCancelDel;			 // 是否读取正在删除状态的角色
    
    std::string m_strRoleDBName;     // 要登陆的数据库的名字
    std::string m_strRoleDBSrvIp;    // 数据库服务器的ip
    std::string m_strRoleDBSrvUID;   // 数据库服务器的帐号    
    std::string m_strRoleDBSrvPWD;   // 数据库服务器的密码    
    std::string m_strRoleDBGateName; // DBGate自己的名字

    std::string roleDbName; // 角色数据库的名字
    uint16      roleDbPort; // 角色数据库的端口
    std::string roleHost;   // 数据库服务器的host
    std::string roleUID;    // 数据库服务器的帐号
    std::string rolePwd;    // 数据库服务器的密码

    std::string billingDbName; // billing数据库的名字
    uint16      billingDbPort; // billing数据库的端口
    std::string billingHost;   // billing数据库服务器的host
    std::string billingUID;    // billing数据库服务器的帐号
    std::string billingPwd;    // billing数据库服务器的密码

    WORD m_wListenPort; // 监听端口

    DWORD m_dwEnterWorldConfine;
    DWORD m_RoleSaveMax;
    DWORD m_OtherSaveMax;

    std::string strLogConfigFilePath;

    bool m_bSleepTime; // 只能是 0 和 1

    uint8  useSqlType;
    uint32 revShutdownCommandTime;  // 收到的时刻
    uint32 revShutdownDelayTime;    // 收到延迟时间秒

	Listener* m_ClientListen;
	CStaticArray<DatabaseClient*> _DatabaseClient;

	bool m_bAccountBilling; //是否采用以帐号为单位的计费,0/1

	std::string   strBillingServerIp;          //计费服务器IP
	uint16        ustBillingServerPort;        //计费服务器端口
	int           nBindBillingServerPort;      //是通过指定端口连接,-1表示不限制,否则使用
	std::string   strKey;                      //与计费直接交互的key
	bool          bOpenBillingService;          //是否开启与billing server的服务

	//积分
	std::string   strBillingScoreServerIp;          //计费服务器IP
	uint16        ustBillingScoreServerPort;        //计费服务器端口
	int           nBindBillingScoreServerPort;      //是通过指定端口连接,-1表示不限制,否则使用
	std::string   strKeyScore;                      //与计费直接交互的key
	bool          bOpenBillingScoreService;          //是否开启与billing server的服务
};

DatabaseServerApp* GetDatabaseServerApp();

#endif // __DATABASESERVER_DATABASESERVER_H__
