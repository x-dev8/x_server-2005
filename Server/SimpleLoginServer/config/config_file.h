#ifndef __SLS_CONFIG_FILE_H__
#define __SLS_CONFIG_FILE_H__
#pragma once

#include <string>

using namespace std;

class CConfig
{
public:
	CConfig();
	~CConfig();

	static CConfig& Instance()
	{
		static CConfig cc;
		return cc;
	}

	bool InitConfig();

	const char* GetAccountDBIP(){return _AccountDBIP.c_str();}
	const char* GetAccountDBID(){return _AccountDBID.c_str();}
	const char* GetAccountDBPWD(){return _AccountDBPWD.c_str();}
	const char* GetAccountDBNAME(){return _AccountDBNAME.c_str();}
	unsigned short GetAccountDBPORT(){return _AccountDBPORT;}

	unsigned short GetClientPort(){return _ListenClent_Port;}
	unsigned short GetServerPort(){return _ListenServer_Port;}
protected:
private:
	unsigned short _ListenClent_Port;//监听客户端的端口

	unsigned short _ListenServer_Port;//监听其他服务器连接的端口

	string _AccountDBIP;//帐号数据库IP
	string _AccountDBID;//帐号数据库的用户名
	string _AccountDBPWD;//帐号数据库的密码
	string _AccountDBNAME;//帐号数据库的库名
	unsigned short _AccountDBPORT;//帐号数据库的端口
};

#endif