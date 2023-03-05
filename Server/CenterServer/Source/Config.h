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
    
	char		   szServerName[64];			// ����������
    char           szDatabaseServerIP[IP_LENGTH+1];
    unsigned short usDatabaseServerPort;
    unsigned short CenterServerId;          // ��ID��ע�ᵽdbserver,��gameserverһ�������뱣֤��gameserverid���ظ�

    std::string    strGameName;
    std::string    strLogConfigFilePath;

	uint16		   nFullLoadMaxNum;			//��������������
	uint16		   nMaxNumOneMac;			//��Mac��½����

    unsigned long  unSwornSaveTime;

    uint16         listentPortForPlatform;
    bool           m_bSleepTime;
    
    char           platformIp[ IP_LENGTH + 1 ]; // ƽ̨SocketIP
    uint16         platformPort;                // ƽ̨SocketPort
	bool           platform_need;               // �Ƿ����ӵ�����ƽ̨,��Ҫ������ƽ̨���ݵĽ���
	int32          server_id;				   //��ʱ���platformʹ��

    std::string    roleDbName; // ��ɫ���ݿ������
    uint16         roleDbPort; // ��ɫ���ݿ�Ķ˿�
    std::string    roleHost  ; // ���ݿ��������host
    std::string    roleUID   ; // ���ݿ���������ʺ�
    std::string    rolePwd   ; // ���ݿ������������

    //std::string    billingDbName; // ��ֵ���ݿ������
    //uint16         billingDbPort; // ��ֵ���ݿ�Ķ˿�
    //std::string    billingHost  ; // ��ֵ���������host
    //std::string    billingUID   ; // ��ֵ����������ʺ�
    //std::string    billingPwd   ; // ��ֵ�������������

    std::string    platformDbName; // ƽ̨���ݿ������
    uint16         platformDbPort; // ƽ̨���ݿ�Ķ˿�
    std::string    platformHost  ; // ƽ̨���ݿ��������host
    std::string    platformUID   ; // ƽ̨���ݿ���������ʺ�
    std::string    platformPwd   ; // ƽ̨���ݿ������������

    //uint16         nPlatformRPCPort    ; // ƽ̨���ݿ�Ķ˿�(RPC)
    //std::string    strPlatformRPCHost  ; // ƽ̨���ݿ��host(RPC)
    //std::string    strPlatformRPCDbName; // ƽ̨���ݿ������(RPC)
    //std::string    strPlatformRPCUser  ; // ƽ̨���ݿ��ʺ�(RPC)
    //std::string    strPlatformRPCPwd   ; // ƽ̨���ݿ�����(RPC)

	bool              bOpenAntiAddiction    ; // �Ƿ�򿪷�����ϵͳ
	AntiAddictionTime antiAddiction         ; // ������ϵͳʱ������
	uint32            nAntiAddictionSaveTime; // ����ʱ��
	uint32			nOpenNum;			//��ʼ�Ŷӵ���������
	bool            bOpenService;		//�Ƿ����Ŷӷ���

	uint16			LogServerPort;		//��־�������Ķ˿�
	char			LogServerHost[IP_LENGTH+1];//��־��������IP
	bool			LogServerService;	//�Ƿ�������־������
protected:
    Config();
    Config( const Config& ){}
    Config& operator=( const Config& ){}
};

#endif // __CENTERSERVER_CONFIG_H__
