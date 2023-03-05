#include "DataCenterConfig.h"
#include "tinyxml.h"
#include "tstring.h"

CDataCenterConfig::CDataCenterConfig(void)
{
	Auto_LoadRank = false;
	Auto_Hour = 0;
	Auto_Min = 0;

	if (!_mapRankConfig.empty())
	{
		mapRankConfig::iterator itr = _mapRankConfig.begin();
		while(itr != _mapRankConfig.end())
		{
			if (itr->second)
			{
				delete itr->second;
			}
			itr = _mapRankConfig.erase(itr);
		}
	}
	m_sServerListConfig._vecServerAreaConfig.clear();
}

CDataCenterConfig::~CDataCenterConfig(void)
{
	if (!_mapRankConfig.empty())
	{
		mapRankConfig::iterator itr = _mapRankConfig.begin();
		while(itr != _mapRankConfig.end())
		{
			if (itr->second)
			{
				delete itr->second;
			}
			itr = _mapRankConfig.erase(itr);
		}
	}

	//for (int n =0;n = m_sServerListConfig._vecServerAreaConfig.size(); n++)
	//{
	//	sServerAreaConfig* pA = m_sServerListConfig._vecServerAreaConfig[n];
	//	if (pA)
	//	{
	//		for (int m =0;m < pA->_vecServerConfig.size();m++)
	//		{
	//			sServerConfig* pS = pA->_vecServerConfig[m];
	//			if (pS)
	//			{
	//				delete pS;
	//			}
	//		} 
	//		pA->_vecServerConfig.clear();

	//		delete pA;
	//	}
	//}
	m_sServerListConfig._vecServerAreaConfig.clear();
}


bool CDataCenterConfig::AddRankConfig(sRankConfig* pConfig)
{
	if (!pConfig)
	{
		return false;
	}

	if (pConfig->strDatabaseIP.empty()||
		pConfig->strDatabaseName.empty()||
		pConfig->strDatabasePwd.empty()||
		pConfig->strDatabaseUser.empty())
	{
		return false;
	}

	mapRankConfig::iterator itr = _mapRankConfig.find(pConfig->Serverid);
	if (itr != _mapRankConfig.end())
	{
		return false;
	}

	_mapRankConfig.insert(mapRankConfig::value_type(pConfig->Serverid,pConfig));
	return true;

}

bool CDataCenterConfig::LoadConfig()
{
	const char* file_name = "DataCenter.config";

	TiXmlDocument doc;
	if( !doc.LoadFile( file_name))
	{
		assert( false && "load DataCenter.config error!" );
		return false;
	}

	int nvalue = 0;
	TiXmlElement *lpproject = doc.FirstChildElement("Project");
	if( !lpproject)
		return false;
	else
	{
		TiXmlElement *lpRanks = lpproject->FirstChildElement("Ranks");
		if( !lpRanks)
			return false;
		lpRanks->QueryIntAttribute("auto", &nvalue);
		Auto_LoadRank = nvalue;
		lpRanks->QueryIntAttribute("hour", &nvalue);
		Auto_Hour = nvalue;
		lpRanks->QueryIntAttribute("minute", &nvalue);
		Auto_Min = nvalue;

		TiXmlElement *lpRank = lpRanks->FirstChildElement("Rank");
		while(lpRank)
		{
			sRankConfig* pRankConfig = new sRankConfig;
			if (!pRankConfig)
			{
				return false;
			}

			pRankConfig->strFileAddr = lpRank->Attribute("fileaddr");
			pRankConfig->strDatabaseName = lpRank->Attribute("databasename");
			pRankConfig->strDatabaseIP = lpRank->Attribute("databaseip");
			lpRank->QueryIntAttribute("port", &nvalue);
			pRankConfig->DatabasePort = nvalue;
			pRankConfig->strDatabaseUser = lpRank->Attribute("username");
			pRankConfig->strDatabasePwd = lpRank->Attribute("pwds");
			lpRank->QueryIntAttribute("serverid", &nvalue);
			pRankConfig->Serverid = nvalue;

			if (!AddRankConfig(pRankConfig))
			{
				printf("add rank config error! server id:%d\n",pRankConfig->Serverid);
				delete pRankConfig;
			}

			lpRank = lpRank->NextSiblingElement("Rank");
		}

		Common::_tstring tstrTemp;
		string			 strTemp;
		TiXmlElement *lpServerlist = lpproject->FirstChildElement("Serverlist");
		if( !lpServerlist)
			return false;
		lpServerlist->QueryIntAttribute("service", &nvalue);
		IsServerlistService = nvalue;
		if (!IsServerlistService)
		{
			return true;
		}
		sServerListConfig* pServerlistConfig = &m_sServerListConfig;
		strTemp = lpServerlist->Attribute("project");
		tstrTemp.fromUTF8(strTemp.c_str());
		pServerlistConfig->strProjectName = tstrTemp.c_str();

		strTemp = lpServerlist->Attribute("bigarea");
		tstrTemp.fromUTF8(strTemp.c_str());
		pServerlistConfig->strBigAreaName = tstrTemp.c_str();

		strTemp = lpServerlist->Attribute("Broadcast");
		tstrTemp.fromUTF8(strTemp.c_str());
		pServerlistConfig->strBroadcast	  = tstrTemp.c_str();

		pServerlistConfig->strFileAddr	  = lpServerlist->Attribute("fileaddr");

		TiXmlElement *lpArea = lpServerlist->FirstChildElement("Area");
		while(lpArea)
		{
			sServerAreaConfig* pAreaConfig = new sServerAreaConfig;

			strTemp = lpArea->Attribute("name");
			tstrTemp.fromUTF8(strTemp.c_str());
			pAreaConfig->strAreaName = tstrTemp.c_str();

			TiXmlElement *lpServer = lpArea->FirstChildElement("Server");
			while(lpServer)
			{
				sServerConfig* pServerConfig = new sServerConfig;

				pServerConfig->usStatus = SERVERSTATUS_MAX;

				strTemp = lpServer->Attribute("name");
				tstrTemp.fromUTF8(strTemp.c_str());
				pServerConfig->strServerName = tstrTemp.c_str();

				pServerConfig->strIp = lpServer->Attribute("Ip");
				lpServer->QueryIntAttribute("loginPort", &nvalue);
				pServerConfig->usPort = nvalue;
				pServerConfig->strRankAddr = lpServer->Attribute("http");
				lpServer->QueryIntAttribute("IsNew", &nvalue);
				pServerConfig->bIsNew = nvalue;
				lpServer->QueryIntAttribute("IsRecommend", &nvalue);
				pServerConfig->bIsRecommend = nvalue;
				lpServer->QueryIntAttribute("IsVehemence", &nvalue);
				pServerConfig->bIsVehemence = nvalue;
				pServerConfig->strDatabaseUser = lpServer->Attribute("username");
				pServerConfig->strDatabasePwd = lpServer->Attribute("pwds");
				pServerConfig->strDatabaseName = lpServer->Attribute("databasename");
				pServerConfig->strDatabaseIP = lpServer->Attribute("databaseip");
				lpServer->QueryIntAttribute("port", &nvalue);
				pServerConfig->DatabasePort = nvalue;

				pAreaConfig->_vecServerConfig.push_back(pServerConfig);

				lpServer = lpServer->NextSiblingElement("Server");
			}
			
			pServerlistConfig->_vecServerAreaConfig.push_back(pAreaConfig);

			lpArea = lpArea->NextSiblingElement("Area");
		}
	}
	return true;
}

CDataCenterConfig::sRankConfig* CDataCenterConfig::GetRankConifg(unsigned short serverid)
{
	mapRankConfig::iterator itr = _mapRankConfig.find(serverid);
	if (itr == _mapRankConfig.end())
	{
		return NULL;
	}

	return itr->second;
	
}