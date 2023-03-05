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
	unsigned short _ListenClent_Port;//�����ͻ��˵Ķ˿�

	unsigned short _ListenServer_Port;//�����������������ӵĶ˿�

	string _AccountDBIP;//�ʺ����ݿ�IP
	string _AccountDBID;//�ʺ����ݿ���û���
	string _AccountDBPWD;//�ʺ����ݿ������
	string _AccountDBNAME;//�ʺ����ݿ�Ŀ���
	unsigned short _AccountDBPORT;//�ʺ����ݿ�Ķ˿�
};

#endif