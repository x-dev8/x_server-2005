#include "ServerStatus.h"
#include "tinyxml.h"
#include "MeRapidXml.h"
#include "tstring.h"

CServerStatus::CServerStatus(void)
{
	bInit = false;  //是否初始化
	_mySqlConnection = NULL;// 和mysql 的连接
	_workState = MS_TryConnect;
	_lastUpdateTime = HQ_TimeGetTime(); // 最新的更新时间
	_lastSaveTime = 0;   // 最后的生成时间
	m_pServerConfig = NULL;//服务器属性	
}

CServerStatus::~CServerStatus(void)
{
	if (_mySqlConnection)
	{
		delete _mySqlConnection;
	}
}

void CServerStatus::_TryConnectToSqlDb()
{
	if ( _mySqlConnection == NULL )
	{
		_mySqlConnection = new mysqlpp::Connection();
		if ( _mySqlConnection == NULL )
		{
			return;
		}
	}
	switch ( _workState )
	{
	case MS_TryConnect:
	case MS_ReConnected:
		{			
			if (!m_pServerConfig)
			{
				printf("Error:No Server config info!\n");
				return;
			}

			try
			{
				if ( _workState == MS_ReConnected)
				{ 
					_mySqlConnection->disconnect();
				}
				_mySqlConnection->set_option(new mysqlpp::MultiStatementsOption(true));
				_mySqlConnection->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
				bool ConnectOk = _mySqlConnection->connect(m_pServerConfig->strDatabaseName.c_str(), 
					m_pServerConfig->strDatabaseIP.c_str(), 
					m_pServerConfig->strDatabaseUser.c_str(),
					m_pServerConfig->strDatabasePwd.c_str(), 
					m_pServerConfig->DatabasePort);

				if ( !ConnectOk )
				{
					printf("connect mysql error!server name:%s\n",m_pServerConfig->strServerName);
					return;
				}

				// 设置mysql超时为24小时
				mysqlpp::Query query =_mySqlConnection->query("set interactive_timeout = 24*3600");
				query.execute();

				_workState = MS_Connected; 

			}
			catch (exception& er)
			{				
			}
		}
		break;
	}
}

bool CServerStatus::_CheckState()
{    
	if (!_mySqlConnection||!_mySqlConnection->connected())
	{
		_workState = MS_ReConnected;
		return false;
	}

	// 3分钟PING一次
	if ( _lastUpdateTime == 0)
	{ _lastUpdateTime = timeGetTime(); }

	if ( !GameTime::IsPassCurrentTime( _lastUpdateTime, MS_PingTime ) )
	{ return true; }

	_lastUpdateTime = timeGetTime();
	if (! _mySqlConnection->ping())
	{
		_workState = MS_ReConnected;
		return false;
	}

	return true;
}

void CServerStatus::SetServerConfig(CDataCenterConfig::sServerConfig* pSC)
{
	if (pSC)
	{
		m_pServerConfig = pSC;
		bInit = false;//配置指针被重新设置了,表示需要新的信息生成
	}
}

#define COUNT_PER 1000 //人数的状态单位,每1000人一个级别
#define DELAYTIME 180   //最多不能超过180秒,超过则表示维护
int CServerStatus::GetServerStatus(int count,const char* datetime)
{
	if (!datetime)
	{
		return SERVERSTATUS_MAX;
	}
	//char timetemp[128]={0};
	int wYear = 0;
	int wMonth = 0;
	int wDay = 0;
	int wHour = 0;
	int wMinute = 0;
	int wSecond = 0;
	//strncpy(timetemp,datetime,sizeof(timetemp)-1);
	if( 6 != sscanf( datetime, "%d-%d-%d %d:%d:%d", &wYear,&wMonth,&wDay,&wHour,&wMinute,&wSecond))
		return SERVERSTATUS_MAX;

	SYSTEMTIME systime;
	GetLocalTime( &systime );
	if (systime.wDay != wDay||systime.wYear != wYear||systime.wMonth != wMonth)
	{
		return SERVERSTATUS_MAX;
	}

	if (systime.wHour > wHour)
	{
		int temphour = systime.wHour - wHour;
		if (temphour > 1)
		{
			return SERVERSTATUS_MAX;
		}

		int tempmin = systime.wMinute + 60 - wMinute;
		if (tempmin*60 > DELAYTIME)
		{
			return SERVERSTATUS_MAX;
		}
	}
	else if(systime.wHour == wHour)
	{
		int tempmin = systime.wMinute - wMinute;
		if (tempmin < 0)
		{
			return SERVERSTATUS_MAX;
		}
		if (tempmin * 60 > DELAYTIME)
		{
			return SERVERSTATUS_MAX;
		}
	}
	else
		return SERVERSTATUS_MAX;

	int temp = count/COUNT_PER;
	if (temp > SERVERSTATUS_MAX)
	{
		temp = SERVERSTATUS_MAX;
	}
	return temp;
}

bool CServerStatus::ProcessStatus()
{
	char szSql[512] = {0};
	int total = 0;
	string datetime;
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select total,date from onlineinfo order by date desc limit 1;");
	try
	{
		mysqlpp::Query mysqlQuery = _mySqlConnection->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		if (res&&!res.empty())
		{
			total = res[0]["total"];
			datetime = res[0]["date"];
		}
		mysqlQuery.reset();
	}
	catch(exception &er)
	{
		printf("error!%s\n",er.what());
	}
	m_pServerConfig->usStatus = GetServerStatus(total,datetime.c_str());
	_lastSaveTime = HQ_TimeGetTime();
	return true;
}

#define RUNTIME 60000

void CServerStatus::Run()
{
	if (!_CheckState())
	{
		if (_workState != MS_Connected)
		{
			_TryConnectToSqlDb();
			return;
		}
	}

	if (HQ_TimeGetTime() - _lastSaveTime >= RUNTIME||!bInit)
	{
		bInit = ProcessStatus();
	}
}

CServerStatusManager::CServerStatusManager(void)
{
	_lastsavetime = 0;
	_vecServerStatus.clear();
}
CServerStatusManager::~CServerStatusManager(void)
{
	for (int n= 0;n < _vecServerStatus.size();n++)
	{
		CServerStatus* pss = _vecServerStatus[n];
		if (pss)
		{
			delete pss;
		}
	}
	_vecServerStatus.clear();
}

bool CServerStatusManager::Init()
{
	for (int n =0;n < theConfig.m_sServerListConfig._vecServerAreaConfig.size();n++)
	{
		CDataCenterConfig::sServerAreaConfig* pAreaConfig = theConfig.m_sServerListConfig._vecServerAreaConfig[n];
		if (pAreaConfig)
		{
			for (int m =0;m < pAreaConfig->_vecServerConfig.size();m++)
			{
				CDataCenterConfig::sServerConfig* pServerConfig = pAreaConfig->_vecServerConfig[m];
				if (pServerConfig)
				{
					CServerStatus* pServerStatus = new CServerStatus;
					pServerStatus->SetServerConfig(pServerConfig);

					_vecServerStatus.push_back(pServerStatus);
				}
			}
		}
	}

	return true;

}

void CServerStatusManager::Run()
{
	if (!bIsInit)
	{
		bIsInit = Init();
		return;
	}

	for (int n= 0;n < _vecServerStatus.size();n++)
	{
		CServerStatus* pss = _vecServerStatus[n];
		pss->Run();
	}

	if (HQ_TimeGetTime() - _lastsavetime >= RUNTIME)
	{
		SaveServerListConfig();
		_lastsavetime = HQ_TimeGetTime();
	}
}

void CServerStatusManager::SaveServerListConfig()
{
	Common::_tstring strValue = "";

	const char* filename = theConfig.m_sServerListConfig.strFileAddr.c_str();

	MeXmlDocument serverlist;
	serverlist.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));

	MeXmlElement *pProject = serverlist.InsertEndChild(("Project"))->ToElement();
	if (pProject == NULL)
	{ return; }
	strValue = theConfig.m_sServerListConfig.strProjectName;
	pProject->SetAttribute("Name", strValue.toUTF8().c_str());
	pProject->SetAttribute("Version", theConfig.m_sServerListConfig.strProjectVersion.c_str());

	MeXmlElement *pBigArea = pProject->InsertEndChild(("BigArea"))->ToElement();
	if (pBigArea == NULL)
	{ return; }
	strValue = theConfig.m_sServerListConfig.strBigAreaName;
	pBigArea->SetAttribute("Name", strValue.toUTF8().c_str());

	MeXmlElement *pAreas = pBigArea->InsertEndChild(("Areas"))->ToElement();
	if (pAreas == NULL)
	{ return; }
	for(int n =0;n < theConfig.m_sServerListConfig._vecServerAreaConfig.size();n++)
	{
		CDataCenterConfig::sServerAreaConfig* pAreaConfig = theConfig.m_sServerListConfig._vecServerAreaConfig[n];
		if(!pAreaConfig)
		{
			continue;
		}
		MeXmlElement *pArea = pAreas->InsertEndChild(("Area"))->ToElement();
		if (pArea == NULL)
		{ return; }
		strValue = pAreaConfig->strAreaName;
		pArea->SetAttribute("Name", strValue.toUTF8().c_str());

		for(int m =0;m < pAreaConfig->_vecServerConfig.size();m++)
		{
			CDataCenterConfig::sServerConfig* pServerConfig = pAreaConfig->_vecServerConfig[m];
			if(!pServerConfig)
			{
				continue;
			}
			MeXmlElement *pServer = pArea->InsertEndChild(("Server"))->ToElement();
			if (pServer == NULL)
			{ return; }
			strValue = pServerConfig->strServerName;
			pServer->SetAttribute("Name", strValue.toUTF8().c_str());
			pServer->SetAttribute("StatusStr", " ");
			pServer->SetAttribute("Comment", " ");
			pServer->SetAttribute("ColorR", 255);
			pServer->SetAttribute("ColorG", 255);
			pServer->SetAttribute("ColorB", 255);
			pServer->SetAttribute("Ip", pServerConfig->strIp.c_str());
			pServer->SetAttribute("Port", pServerConfig->usPort);
			pServer->SetAttribute("http", pServerConfig->strRankAddr.c_str());
			pServer->SetAttribute("Status", pServerConfig->usStatus);
			pServer->SetAttribute("IsNew", pServerConfig->bIsNew);
			pServer->SetAttribute("IsRecommend", pServerConfig->bIsRecommend);
			pServer->SetAttribute("IsVehemence", pServerConfig->bIsVehemence);
		}
	}
	serverlist.SaveFile(filename);
}