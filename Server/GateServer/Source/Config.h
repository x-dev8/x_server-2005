/********************************************************************
	Filename: 	Config.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_CONFIG_H__
#define __GATESERVER_CONFIG_H__

#pragma once

#include "MeRTLibsServer.h"

class GateServerConfig
{
public:
    struct SOpenMap
    {
        SOpenMap();
        bool operator == (const int mapid )
        { return MapId == mapid; }

        uint32 MapId;
		bool   IsRun;
    };

    enum EConstDefine
    {
        EConstDefine_DefaultPlayerMaxOnlineCount = 1500,
        EConstDefine_DefaultClientMaxCountIn     = 400,
        EConstDefine_DefaultClientMaxCountOut    = 700,
        EConstDefine_DefaultClientLowLvlCast     = 400,
        EConstDefine_DefaultClientNormalLvlCast  = 300,
        EConstDefine_DefaultGameMaxCountIn       = 150000,
        EConstDefine_DefaultGameMaxCountOut      = 200000,
        EConstDefine_DefaultGameLowLvlCast       = 50000,
        EConstDefine_DefaultGameNormalLvlCast    = 100000,
    };

public:
    GateServerConfig();

    bool InitCommonData ( const char* szConfigFile );
    bool InitPrivateData( const char* szConfigFile );
    
    bool IsMapOpen( uint32 MapId );
	bool IsMapRun( uint32 MapId );

protected:
    bool InitNetSetting();

private:
    typedef std::vector<SOpenMap> OpenMaps;
    OpenMaps OpenMaps_;

public:
    char        szGameServerIP[64]   ; // 游戏世界服务器IP
    int         nGameServerPort      ; // 游戏世界服务器端口号
    int         nGateServerId        ; // GateServer的编号
    char        szGameServerName[64] ; // 游戏世界服务器名字
    DWORD       dwForClientIP        ; // GateServerIP
    char        szForClientIP[64]    ; // GateServer开放给客户端的IP
    int         nForClientGatePort   ; // GateServer监听客户端的端口
    DWORD       dwCheckClientPingMsg ; // 检查客户端的KeepAlive
    std::string strTranslateIp       ;
    std::string strLogConfigFilePath ;
    uint32      dwConnectOverTime    ;    
    uint8       gEncryptMode         ; // 加密方式

    // 由于内存池最大值占用内存的特性所以GateServer最多1500个用户 (实际Accept1200个用户 + 300缓冲释放)
    // 内存使用最大值为 主要为协议部分
    // 协议块大小[512] * ((Client In队列最大协议块[400] + Client Out队列最大协议块[700]) * 人数[1500] + (GameServer In队列协议块个数[150000] + GameServer Out队列协议块个数[200000]))
    // ~= 976.56兆内存 [峰值内存] 消息发不过来

    int    playerMaxOnlineCount; // 最大人数
    uint16 clientMaxCountIn    ; // 收取Client队列消息最大的个数
    uint16 clientMaxCountOut   ; // 发给Client队列消息最大的个数
    uint16 clientLowLvlCast    ; // Client InOut 队列中Low消息的过滤线     队列中消息(包括Low,Normal,high,tiptop)个数超过这个数就不收Low消息
    uint16 clientNormalLvlCast ; // Client InOut 队列中Normal消息的过滤线  队列中消息(包括Low,Normal,high,tiptop)个数超过这个数就不收Normal消息
    uint32 gameMaxCountIn      ; // 收取GameServer队列消息最大的个数
    uint32 gameMaxCountOut     ; // 发给GameServer队列消息最大的个数
    uint32 gameLowLvlCast      ; // GameServer InOut 队列中Low消息的过滤线 队列中消息(包括Low,Normal,high,tiptop)个数超过这个数就不收Low消息
    uint32 gameNormalLvlCast   ; // GameServer InOut 队列中Low消息的过滤线 队列中消息(包括Low,Normal,high,tiptop)个数超过这个数就不收Low消息

    uint32 netOfflineTime      ; // 断线重连时间, 单位秒
};

extern GateServerConfig theCfg;

#endif // __GATESERVER_CONFIG_H__
