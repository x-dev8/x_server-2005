#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;


#define SERVERSTATUS_MAX 4 //������״̬���ֵ4,��ʾά��

class CDataCenterConfig
{
public:
	struct sRankConfig
	{
		string		   strFileAddr;
		string		   strDatabaseUser;
		string		   strDatabasePwd;
		string		   strDatabaseName;
		string		   strDatabaseIP;
		unsigned short DatabasePort;
		unsigned short Serverid;
	};

	struct sServerConfig
	{
		string strServerName;
		string strIp;
		unsigned short usPort;
		string strRankAddr;
		bool   bIsNew;//�·�
		bool   bIsRecommend;//�Ƿ��Ƽ�
		bool   bIsVehemence;//�Ƿ����
		unsigned short usStatus;//������״̬,��̬����
		
		string		   strDatabaseUser;
		string		   strDatabasePwd;
		string		   strDatabaseName;
		string		   strDatabaseIP;
		unsigned short DatabasePort;
	};
	typedef vector<sServerConfig*> vecServerConfig;

	struct sServerAreaConfig
	{
		string strAreaName;
		vecServerConfig _vecServerConfig;
	};
	typedef vector<sServerAreaConfig*> vecServerAreaConfig;

	struct sServerListConfig
	{
		string strFileAddr;
		string strProjectName;
		string strProjectVersion;
		string strBigAreaName;
		string strBroadcast;
		vecServerAreaConfig _vecServerAreaConfig;
		//
	};

	typedef map<unsigned short,sRankConfig*> mapRankConfig;
public:
	CDataCenterConfig(void);
	~CDataCenterConfig(void);

public:
	static CDataCenterConfig& Instance()
	{
		static CDataCenterConfig cdcc;
		return cdcc;
	}

	bool LoadConfig();
	bool AddRankConfig(sRankConfig* pConfig);
	bool IsAutoLoad(){return Auto_LoadRank;}
	unsigned short GetAutoHour(){return Auto_Hour;}
	unsigned short GetAutoMin(){return Auto_Min;}
	sRankConfig* GetRankConifg(unsigned short serverid);

	bool IsServerListRun(){return IsServerlistService;}

	mapRankConfig _mapRankConfig;
	sServerListConfig m_sServerListConfig;//serverlist.config��һЩ����
private:

	bool Auto_LoadRank;//�Զ��������а�����
	unsigned short Auto_Hour;  //�Զ�����Сʱ
	unsigned short Auto_Min;   //�Զ��������
	
	bool IsServerlistService; //�Ƿ�������serverlist.config
};

#define theConfig CDataCenterConfig::Instance()