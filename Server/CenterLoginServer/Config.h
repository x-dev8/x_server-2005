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
	Config();
	static Config& GetInstance();

	bool Init( const char* szConfigFile );

protected:
	bool InitNetSetting();
	bool InitLoginCoinfg(const char* szConfigFile);

public:
	char           DateBaseName[256];
	char           DateBaseUser[256];
	char           DateBasePassword[256];
	char           DateBaseIp[IP_LENGTH+1];
	unsigned short DateBasePort;
	bool           UsingDB;                        //�Ƿ�ʹ�����ݿ��е��ʺ���֤,0:ʹ��account server,1:ʹ�����ݿ��е��ʺ�
	//unsigned long  QueryTime;
	//int            BlockAccountTime;    
	//unsigned int   unOnceUpdateAccount; // һ��ȥ�˺Ÿ���

	std::string   strServiceIp;                //��������IP
	uint16        ustForClientPort;				// Login Server�����ͻ��˵Ķ˿�	

	std::string   strAccountServerIp;          //��֤������IP
	uint16        ustAccountServerPort;        //��֤�������˿�
	int           nBindAccountPort;            //��ͨ��ָ���˿�����,-1��ʾ������,����ʹ��
	std::string   strKey;                      //����ֱ֤�ӽ�����key

	uint16        ustListenCenterPort;         //����Center�Ķ˿�

	char           BlockDateBaseName[256];
	char           BlockDateBaseUser[256];
	char           BlockDateBasePassword[256];
	char           BlockDateBaseIp[IP_LENGTH+1];
	unsigned short BlockDateBasePort;
};

#define theConfig Config::GetInstance()

#endif // __CENTERSERVER_CONFIG_H__
