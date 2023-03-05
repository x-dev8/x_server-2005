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
	bool           UsingDB;                        //是否使用数据库中的帐号认证,0:使用account server,1:使用数据库中的帐号
	//unsigned long  QueryTime;
	//int            BlockAccountTime;    
	//unsigned int   unOnceUpdateAccount; // 一次去账号个数

	std::string   strServiceIp;                //开启服务IP
	uint16        ustForClientPort;				// Login Server监听客户端的端口	

	std::string   strAccountServerIp;          //认证服务器IP
	uint16        ustAccountServerPort;        //认证服务器端口
	int           nBindAccountPort;            //是通过指定端口连接,-1表示不限制,否则使用
	std::string   strKey;                      //与认证直接交互的key

	uint16        ustListenCenterPort;         //监听Center的端口

	char           BlockDateBaseName[256];
	char           BlockDateBaseUser[256];
	char           BlockDateBasePassword[256];
	char           BlockDateBaseIp[IP_LENGTH+1];
	unsigned short BlockDateBasePort;
};

#define theConfig Config::GetInstance()

#endif // __CENTERSERVER_CONFIG_H__
