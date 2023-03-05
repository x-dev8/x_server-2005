/********************************************************************
	Filename: 	Config.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_CONFIG_H__
#define __CENTERSERVER_CONFIG_H__

#pragma once

#include "GlobalDef.h"

#define theConfig Config::GetInstance()

class Config
{
public:
    static Config& GetInstance();

    bool Init( const char* szConfigFile );    

protected:
    bool InitNetSetting();

public:
    unsigned short usListenPortForGameServer;
    unsigned short usListentPortForLoginServer;
    unsigned short usMaxTickNum;
    unsigned long  dwOutReqLoginTime;

	char           szLoginServerIP[IP_LENGTH+1];
	unsigned short usLoginServerPort;
    
	char		   szServerName[64];			// 服务器名字
    char           szDatabaseServerIP[IP_LENGTH+1];
    unsigned short usDatabaseServerPort;
    unsigned short CenterServerId;          // 此ID会注册到dbserver,和gameserver一样所以请保证和gameserverid不重复

    std::string    strGameName;
    std::string    strLogConfigFilePath;

	uint16		   nFullLoadMaxNum;			//服务器爆棚人数
	uint16		   nMaxNumOneMac;			//单Mac登陆人数

    unsigned long  unSwornSaveTime;

    uint16         listentPortForPlatform;
    bool           m_bSleepTime;
    
    char           platformIp[ IP_LENGTH + 1 ]; // 平台SocketIP
    uint16         platformPort;                // 平台SocketPort
	bool           platform_need;               // 是否连接第三方平台,主要用作与平台数据的交互
	int32          server_id;				   //暂时针对platform使用

    std::string    roleDbName; // 角色数据库的名字
    uint16         roleDbPort; // 角色数据库的端口
    std::string    roleHost  ; // 数据库服务器的host
    std::string    roleUID   ; // 数据库服务器的帐号
    std::string    rolePwd   ; // 数据库服务器的密码

    //std::string    billingDbName; // 充值数据库的名字
    //uint16         billingDbPort; // 充值数据库的端口
    //std::string    billingHost  ; // 充值库服务器的host
    //std::string    billingUID   ; // 充值库服务器的帐号
    //std::string    billingPwd   ; // 充值库服务器的密码

    std::string    platformDbName; // 平台数据库的名字
    uint16         platformDbPort; // 平台数据库的端口
    std::string    platformHost  ; // 平台数据库服务器的host
    std::string    platformUID   ; // 平台数据库服务器的帐号
    std::string    platformPwd   ; // 平台数据库服务器的密码

    //uint16         nPlatformRPCPort    ; // 平台数据库的端口(RPC)
    //std::string    strPlatformRPCHost  ; // 平台数据库的host(RPC)
    //std::string    strPlatformRPCDbName; // 平台数据库的名字(RPC)
    //std::string    strPlatformRPCUser  ; // 平台数据库帐号(RPC)
    //std::string    strPlatformRPCPwd   ; // 平台数据库密码(RPC)

	bool              bOpenAntiAddiction    ; // 是否打开防沉迷系统
	AntiAddictionTime antiAddiction         ; // 防沉迷系统时间设置
	uint32            nAntiAddictionSaveTime; // 保存时间
	uint32			nOpenNum;			//开始排队的在线人数
	bool            bOpenService;		//是否开启排队服务

	uint16			LogServerPort;		//日志服务器的端口
	char			LogServerHost[IP_LENGTH+1];//日志服务器的IP
	bool			LogServerService;	//是否连接日志服务器
protected:
    Config();
    Config( const Config& ){}
    Config& operator=( const Config& ){}
};

#endif // __CENTERSERVER_CONFIG_H__
