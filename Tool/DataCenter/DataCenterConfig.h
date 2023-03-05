#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;


#define SERVERSTATUS_MAX 4 //服务器状态最大值4,表示维护

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
		bool   bIsNew;//新服
		bool   bIsRecommend;//是否推荐
		bool   bIsVehemence;//是否火热
		unsigned short usStatus;//服务器状态,动态生成
		
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
	sServerListConfig m_sServerListConfig;//serverlist.config的一些属性
private:

	bool Auto_LoadRank;//自动载入排行榜数据
	unsigned short Auto_Hour;  //自动载入小时
	unsigned short Auto_Min;   //自动载入分钟
	
	bool IsServerlistService; //是否开启生成serverlist.config
};

#define theConfig CDataCenterConfig::Instance()