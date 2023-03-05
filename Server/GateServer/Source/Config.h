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
    char        szGameServerIP[64]   ; // ��Ϸ���������IP
    int         nGameServerPort      ; // ��Ϸ����������˿ں�
    int         nGateServerId        ; // GateServer�ı��
    char        szGameServerName[64] ; // ��Ϸ�������������
    DWORD       dwForClientIP        ; // GateServerIP
    char        szForClientIP[64]    ; // GateServer���Ÿ��ͻ��˵�IP
    int         nForClientGatePort   ; // GateServer�����ͻ��˵Ķ˿�
    DWORD       dwCheckClientPingMsg ; // ���ͻ��˵�KeepAlive
    std::string strTranslateIp       ;
    std::string strLogConfigFilePath ;
    uint32      dwConnectOverTime    ;    
    uint8       gEncryptMode         ; // ���ܷ�ʽ

    // �����ڴ�����ֵռ���ڴ����������GateServer���1500���û� (ʵ��Accept1200���û� + 300�����ͷ�)
    // �ڴ�ʹ�����ֵΪ ��ҪΪЭ�鲿��
    // Э����С[512] * ((Client In�������Э���[400] + Client Out�������Э���[700]) * ����[1500] + (GameServer In����Э������[150000] + GameServer Out����Э������[200000]))
    // ~= 976.56���ڴ� [��ֵ�ڴ�] ��Ϣ��������

    int    playerMaxOnlineCount; // �������
    uint16 clientMaxCountIn    ; // ��ȡClient������Ϣ���ĸ���
    uint16 clientMaxCountOut   ; // ����Client������Ϣ���ĸ���
    uint16 clientLowLvlCast    ; // Client InOut ������Low��Ϣ�Ĺ�����     ��������Ϣ(����Low,Normal,high,tiptop)��������������Ͳ���Low��Ϣ
    uint16 clientNormalLvlCast ; // Client InOut ������Normal��Ϣ�Ĺ�����  ��������Ϣ(����Low,Normal,high,tiptop)��������������Ͳ���Normal��Ϣ
    uint32 gameMaxCountIn      ; // ��ȡGameServer������Ϣ���ĸ���
    uint32 gameMaxCountOut     ; // ����GameServer������Ϣ���ĸ���
    uint32 gameLowLvlCast      ; // GameServer InOut ������Low��Ϣ�Ĺ����� ��������Ϣ(����Low,Normal,high,tiptop)��������������Ͳ���Low��Ϣ
    uint32 gameNormalLvlCast   ; // GameServer InOut ������Low��Ϣ�Ĺ����� ��������Ϣ(����Low,Normal,high,tiptop)��������������Ͳ���Low��Ϣ

    uint32 netOfflineTime      ; // ��������ʱ��, ��λ��
};

extern GateServerConfig theCfg;

#endif // __GATESERVER_CONFIG_H__
