#include "GLSService.h"
#include "MeRTLibs.h"
#include "ColorScreen.h"
#include "tstring.h"
#include "Timestamp/Timestamp.h"
#include "GameTimer.h"
#include "Config.h"

GLSService::GLSService(void)
{
	_pMysqlConnect = NULL;
	_workState = SS_TryConnect;	
	_lastUpdateTime = HQ_TimeGetTime();
	_loadblockinfo = false;

	m_mapOverdueBlockInfo.clear();
	m_mapBlockInfo.clear();
	m_BlockInfoList.clear();
}

GLSService::~GLSService(void)
{
	if (_pMysqlConnect)
	{
		delete _pMysqlConnect;
	}

	_mapBlockInfo::iterator itr = m_mapBlockInfo.begin();
	while(itr != m_mapBlockInfo.end())
	{
		if (itr->second)
		{
			delete itr->second;
		}
		itr++;
	}
	m_mapBlockInfo.clear();

	_mapBlockInfo::iterator itrOverdue = m_mapOverdueBlockInfo.begin();
	while(itrOverdue != m_mapOverdueBlockInfo.end())
	{
		if (itrOverdue->second)
		{
			delete itrOverdue->second;
		}
		itrOverdue++;
	}
	m_mapOverdueBlockInfo.clear();

	SBlockInfo* pInfo = NULL;
	while(!m_BlockInfoList.empty())
	{
		pInfo = m_BlockInfoList.front();
		m_BlockInfoList.pop_front();
		if (pInfo)
		{
			delete pInfo;
		}
	}
	// for ip
	_mapBlockInfoMac::iterator itrIP = m_mapBlockInfoMac.begin();
	while(itrIP != m_mapBlockInfoMac.end())
	{
		if (itrIP->second)
		{
			delete itrIP->second;
		}
		itrIP++;
	}
	m_mapBlockInfoMac.clear();

	_mapBlockInfoMac::iterator itrIPOverdue = m_mapOverdueBlockInfoMac.begin();
	while(itrIPOverdue != m_mapOverdueBlockInfoMac.end())
	{
		if (itrIPOverdue->second)
		{
			delete itrIPOverdue->second;
		}
		itrIPOverdue++;
	}
	m_mapOverdueBlockInfoMac.clear();

	SBlockInfoMac* pIPInfo = NULL;
	while(!m_BlockInfoListMac.empty())
	{
		pIPInfo = m_BlockInfoListMac.front();
		m_BlockInfoListMac.pop_front();
		if (pIPInfo)
		{
			delete pIPInfo;
		}
	}
}

void GLSService::_TryConnectToSqlDb()
{
	if ( _pMysqlConnect == NULL )
	{
		_pMysqlConnect = new mysqlpp::Connection();
		if ( _pMysqlConnect == NULL )
		{
			return;
		}
	}
	switch ( _workState )
	{
	case SS_TryConnect:
	case SS_ReConnected:
		{
			try
			{
				if ( _workState == SS_ReConnected)
				{ 
					_pMysqlConnect->disconnect();
				}
				_pMysqlConnect->set_option(new mysqlpp::MultiStatementsOption(true));
				_pMysqlConnect->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
				bool ConnectOk = _pMysqlConnect->connect(theConfig.BlockDateBaseName, 
														theConfig.BlockDateBaseIp, 
														theConfig.BlockDateBaseUser,
														theConfig.BlockDateBasePassword, 
														theConfig.BlockDateBasePort);

				if ( !ConnectOk )
				{
					COLOR_MESSAGE( COLOR_RED, "[GLsDB Fail] \n" );
					return;
				}
				// 设置mysql超时为24小时
				mysqlpp::Query query =_pMysqlConnect->query("set interactive_timeout = 24*3600");
				query.execute();

				_workState = SS_Connected; 

			}
			catch (exception& er)
			{				
			}
		}
		break;
	}
}

bool GLSService::_CheckState()
{    
	if (!_pMysqlConnect||!_pMysqlConnect->connected())
	{
		_workState = SS_ReConnected;
		return false;
	}

	// 3分钟PING一次
	if ( _lastUpdateTime == 0)
	{ _lastUpdateTime = timeGetTime(); }

	if ( !GameTime::IsPassCurrentTime( _lastUpdateTime,180000) )
	{ return true; }

	_lastUpdateTime = timeGetTime();
	if (! _pMysqlConnect->ping())
	{
		_workState = SS_ReConnected;
		return false;
	}

	return true;
}

GLSService::SBlockInfo* GLSService::GetBlockInfoByName(const char* name)
{
	if (!name)
	{
		return NULL;
	}
	_mapBlockInfo::iterator itr = m_mapBlockInfo.find(name);
	if (itr != m_mapBlockInfo.end())
	{
		return itr->second;
	}
	return NULL;
}

GLSService::SBlockInfoMac* GLSService::GetBlockInfoByMac(const char* cMac)
{
	if (!cMac)	return NULL;

	_mapBlockInfoMac::iterator itr = m_mapBlockInfoMac.find(string(cMac));
	if (itr != m_mapBlockInfoMac.end())
	{
		return itr->second;
	}
	return NULL;
}
void GLSService::DelBlockInfo(SBlockInfo* pInfo)
{
	if (!pInfo)
	{
		return;
	}
	CSALocker lock(&_Lock);
	_mapBlockInfo::iterator itr = m_mapBlockInfo.find(pInfo->name);
	if (itr != m_mapBlockInfo.end())
		m_mapBlockInfo.erase(itr);
	return;
}
void GLSService::DelBlockInfoMac(SBlockInfoMac* pInfo)
{
	if (!pInfo)		return;

	CSALocker lock(&_LockMac);
	_mapBlockInfoMac::iterator itr = m_mapBlockInfoMac.find(pInfo->cMac);
	if (itr != m_mapBlockInfoMac.end())
		m_mapBlockInfoMac.erase(itr);
	return;
}
bool GLSService::AddBlockInfo(SBlockInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}
	CSALocker lock(&_Lock);
	_mapBlockInfo::iterator itr = m_mapBlockInfo.find(pInfo->name);
	if (itr == m_mapBlockInfo.end())
	{
		m_mapBlockInfo.insert(_mapBlockInfo::value_type(pInfo->name,pInfo));		
	}
	return true;
}

bool GLSService::AddBlockInfoMac(SBlockInfoMac* pInfo)
{
	if (!pInfo)		return false;

	CSALocker lock(&_LockMac);
	_mapBlockInfoMac::iterator itr = m_mapBlockInfoMac.find(pInfo->cMac);
	if (itr == m_mapBlockInfoMac.end())
	{
		m_mapBlockInfoMac.insert(_mapBlockInfoMac::value_type(pInfo->cMac,pInfo));		
	}
	return true;
}


void GLSService::LoadBlockInfo()
{
	if (_loadblockinfo)
	{
		return;
	}
	char szSql[512] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select guid,name,blocktime,begintime from block;");

	mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if (res&&!res.empty())
	{
		for (int n =0;n < res.num_rows();n++)
		{
			Common::_tstring strName;
			strName.fromUTF8(res[n]["name"]);
			if (strName.empty())
			{
				continue;
			}
			int tempBlockTime = res[n]["blocktime"];
			if (tempBlockTime <= 0)
			{
				continue;
			}
			SBlockInfo* pBlock = GetBlockInfoByName(strName.c_str());
			if (!pBlock)
			{
				pBlock = new SBlockInfo;
				if (!pBlock)
				{
					break;
				}
			}
			strncpy_s( pBlock->name, sizeof( pBlock->name ), strName.c_str(), sizeof( pBlock->name ) - 1 );
			pBlock->blocktime = tempBlockTime;
			pBlock->guid = res[n]["guid"];
			pBlock->begintime = res[n]["begintime"];
			AddBlockInfo(pBlock);//加载时候添加
		}
	}
	mysqlQuery.reset();

	// for IP
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select mac,blocktime,begintime from blockMac;");

	mysqlpp::Query mysqlQuery1 = _pMysqlConnect->query(szSql);
	mysqlpp::StoreQueryResult res1 = mysqlQuery1.store();

	if (res1&&!res1.empty())
	{
		for (int n =0;n < res1.num_rows();n++)
		{
			Common::_tstring strMac;
			strMac.fromUTF8(res1[n]["mac"]);
			if (strMac.empty())
			{
				continue;
			}
			int tempBlockTime = res1[n]["blocktime"];
			if (tempBlockTime <= 0)
			{
				continue;
			}
			SBlockInfoMac* pBlock = GetBlockInfoByMac(strMac.c_str());
			if (!pBlock)
			{
				pBlock = new SBlockInfoMac;
				if (!pBlock)
				{
					break;
				}
			}
			strncpy_s( pBlock->cMac, sizeof( pBlock->cMac ), strMac.c_str(), sizeof( pBlock->cMac ) - 1 );
			pBlock->blocktime = tempBlockTime;
			pBlock->begintime = res1[n]["begintime"];
			AddBlockInfoMac(pBlock);
		}
	}
	mysqlQuery1.reset();

	_loadblockinfo = true;
	_lastRunBlocktime = HQ_TimeGetTime();
	
}

//void GLSService::ReLoadBlockInfo()
//{
//	CSALocker lock(&_Lock);
//	_mapBlockInfo::iterator itr = m_mapBlockInfo.begin();
//	while(itr != m_mapBlockInfo.end())
//	{
//		if (itr->second)
//		{
//			delete itr->second;
//		}
//		itr++;
//	}
//	m_mapBlockInfo.clear();
//	
//	// for Ip
//	_mapBlockInfoMac::iterator itr1 = m_mapBlockInfoMac.begin();
//	while(itr1 != m_mapBlockInfoMac.end())
//	{
//		if (itr1->second)
//		{
//			delete itr1->second;
//		}
//		itr1++;
//	}
//	m_mapBlockInfoMac.clear();
//	_loadblockinfo = false;
//}

void GLSService::RunBlockInfo()
{
	// 1分钟检测一次
	if (!GameTime::IsPassCurrentTime( _lastRunBlocktime, GLS_CheckBlockTime ))
	{
		return;
	}
	CSALocker lock(&_Lock);
	unsigned long currtime = theTimestamp.GetTimestamp();
	SBlockInfo* pBlockInfo = NULL;
	_mapBlockInfo::iterator itr = m_mapBlockInfo.begin();
	while(itr != m_mapBlockInfo.end())
	{
		pBlockInfo = itr->second;
		if (!pBlockInfo)
		{
			itr = m_mapBlockInfo.erase(itr);
			continue;
		}
		else
		{
			if (pBlockInfo->begintime + pBlockInfo->blocktime <= currtime)
			{
				m_mapOverdueBlockInfo.insert(_mapBlockInfo::value_type(pBlockInfo->name,pBlockInfo));
				itr = m_mapBlockInfo.erase(itr);
				continue;
			}
		}
		itr++;
	}
	// for Mac
	SBlockInfoMac* pBlockInfoMac= NULL;
	_mapBlockInfoMac::iterator itr1 = m_mapBlockInfoMac.begin();
	while(itr1 != m_mapBlockInfoMac.end())
	{
		pBlockInfoMac = itr1->second;
		if (!pBlockInfoMac)
		{
			itr1 = m_mapBlockInfoMac.erase(itr1);
			continue;
		}
		else
		{
			if (pBlockInfoMac->begintime + pBlockInfoMac->blocktime <= currtime)
			{
				m_mapOverdueBlockInfoMac.insert(_mapBlockInfoMac::value_type(string(pBlockInfoMac->cMac),pBlockInfoMac));
				itr1 = m_mapBlockInfoMac.erase(itr1);
				continue;
			}
		}
		itr1++;
	}

	_lastRunBlocktime = HQ_TimeGetTime();
}

//每次循环删除30个
#define  RunOverdueBlock_MaxCount 30
void GLSService::RunOverdueBlockInfo()
{
	static char szSql[ 1024 ] = {0};
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
	int n = 0;
	_mapBlockInfo::iterator itr = m_mapOverdueBlockInfo.begin();
	while(itr != m_mapOverdueBlockInfo.end())
	{
		if (!itr->second)
		{
			itr = m_mapOverdueBlockInfo.erase(itr);
			continue;
		}

		memset( szSql, 0, sizeof(szSql) );
		strncpy_s( szSql, sizeof( szSql ), "delete from block where name = %0q;",sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(itr->second->name);
		mysqlQuery.reset();

		delete itr->second;
		itr = m_mapOverdueBlockInfo.erase(itr);

		n++;
		if (n >= RunOverdueBlock_MaxCount)
		{
			break;
		}
	}
	// for mac
	n = 0;
	mysqlQuery = _pMysqlConnect->query();
	_mapBlockInfoMac::iterator itr1 = m_mapOverdueBlockInfoMac.begin();
	while(itr1 != m_mapOverdueBlockInfoMac.end())
	{
		if (!itr1->second)
		{
			itr1 = m_mapOverdueBlockInfoMac.erase(itr1);
			continue;
		}

		memset( szSql, 0, sizeof(szSql) );
		strncpy_s( szSql, sizeof( szSql ), "delete from blockMac where mac = %0q;",sizeof( szSql ) - 1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(itr1->second->cMac);
		mysqlQuery.reset();

		delete itr1->second;
		itr1 = m_mapOverdueBlockInfoMac.erase(itr1);

		n++;
		if (n >= RunOverdueBlock_MaxCount)
		{
			break;
		}
	}
}

void GLSService::RunOnStep()
{
	if (!_CheckState())
	{
		if (_workState != SS_Connected)
		{
			_TryConnectToSqlDb();
			return;
		}
	}
	LoadBlockInfo();
	RunBlockInfo();
	RunOverdueBlockInfo();
	ProcessNewBlockInfo();
	ProcessNewBlockInfoMac();
}

int GLSService::CheckBlockAccount(char* accountname)
{
	CSALocker lock(&_Lock);
	_mapBlockInfo::iterator itr = m_mapBlockInfo.find(accountname);
	if (itr != m_mapBlockInfo.end())
	{
		if (!itr->second)
		{
			m_mapBlockInfo.erase(itr);
			return 0;
		}

		return itr->second->blocktime+itr->second->begintime - theTimestamp.GetTimestamp();
	}
	return 0;
}
int	 GLSService::CheckBlockUserMac( const char* cMac)
{
	CSALocker lock(&_LockMac);
	_mapBlockInfoMac::iterator itr = m_mapBlockInfoMac.find(string(cMac));
	if (itr != m_mapBlockInfoMac.end())
	{
		if (!itr->second)
		{
			m_mapBlockInfoMac.erase(itr);
			return 0;
		}

		return itr->second->blocktime + itr->second->begintime - theTimestamp.GetTimestamp();
	}
	return 0;
}

bool GLSService::AddNewBlockInfoPublic(SBlockInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}
	CSALocker lock(&_LockList);
	m_BlockInfoList.push_back(pInfo);
	return true;
}
bool GLSService::AddNewBlockInfoMacPublic(SBlockInfoMac* pInfo)
{
	if (!pInfo)	return false;

	CSALocker lock(&_LockListMac);
	m_BlockInfoListMac.push_back(pInfo);
	return true;
}

bool GLSService::InsertNewBlockInfo(SBlockInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}
	int num = 0;
	char szSql[1024] = {0};
	bool result = true;
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select count(*) from block where name='%s';",pInfo->name);
	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		num = res[0][0];
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND

	memset( szSql, 0, sizeof(szSql));
	if (num > 0)
	{
		if(pInfo->blocktime == 0)
		{
			//执行Del
			sprintf_s( szSql, sizeof( szSql )-1, "delete from block where name = %0q;",pInfo->name);
		}
		else
		{
			sprintf_s( szSql, sizeof( szSql ) - 1,"update block set blocktime=%u,begintime=%u,datetime=now() where name='%s';",pInfo->blocktime,pInfo->begintime,pInfo->name);
		}
		//mysqlQuery << szSql;
		//mysqlQuery.parse();
		//mysqlQuery.execute( mysqlpp::sql_int_unsigned( pInfo->blocktime ), mysqlpp::sql_int_unsigned( pInfo->begintime ),pInfo->name);
		//mysqlQuery.reset();
	}
	else
	{
		if(pInfo->blocktime != 0)	
			sprintf_s( szSql, sizeof( szSql ) - 1,"insert into block (guid,name,blocktime,begintime,datetime) values(%u,'%s',%u,%u,now());",pInfo->guid,pInfo->name,pInfo->blocktime,pInfo->begintime);
		/*mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlQuery.execute(mysqlpp::sql_int_unsigned( pInfo->guid ),pInfo->name,mysqlpp::sql_int_unsigned( pInfo->blocktime ), mysqlpp::sql_int_unsigned( pInfo->begintime ));
		mysqlQuery.reset();*/
	}

	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlQuery.execute( szSql);
	FREESTOREPROCEDURE_TRY;
	TRYEND

	if(pInfo->blocktime == 0)
	{
		SBlockInfo* pTempBlock = GetBlockInfoByName(pInfo->name);
		if (pTempBlock)
		{
			//执行删除操作
			DelBlockInfo(pTempBlock);
			delete pInfo;
		}
	}
	else
	{
		SBlockInfo* pTempBlock = GetBlockInfoByName(pInfo->name);
		if (pTempBlock)
		{
			pTempBlock->begintime = pInfo->begintime;
			pTempBlock->blocktime = pInfo->blocktime;

			delete pInfo;
		}
		else
		{
			pTempBlock = pInfo;
		}

		AddBlockInfo(pTempBlock);// 运行时添加
	}
	return true;
}

bool GLSService::InsertNewBlockInfoMac(SBlockInfoMac* pInfo)
{
	if (!pInfo)		return false;

	int num = 0;
	char szSql[1024] = {0};
	bool result = true;
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select count(*) from blockMac where mac='%s';",pInfo->cMac);
	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql));
	if ( res && !res.empty())
	{
		num = res[0][0];
	}
	FREESTOREPROCEDURE_TRY;
	TRYEND

	memset( szSql, 0, sizeof(szSql));
	if (num > 0)
	{
		if(pInfo->blocktime == 0)
		{
			//执行Del
			sprintf_s( szSql, sizeof( szSql )-1, "delete from blockMac where mac = %0q;",pInfo->cMac);
		}
		else
		{
			sprintf_s( szSql, sizeof( szSql ) - 1,"update blockMac set blocktime=%u,begintime=%u,datetime=now() where mac='%s';",pInfo->blocktime,pInfo->begintime,pInfo->cMac);
		}
	}
	else
	{
		if(pInfo->blocktime != 0)	
			sprintf_s( szSql, sizeof( szSql ) - 1,"insert into blockMac (mac,blocktime,begintime,datetime) values('%s',%u,%u,now());",pInfo->cMac,pInfo->blocktime,pInfo->begintime);
	}

	TRYBEGIN
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
	mysqlQuery.execute( szSql);
	FREESTOREPROCEDURE_TRY;
	TRYEND

	if(pInfo->blocktime == 0)
	{
		SBlockInfoMac* pTempBlock = GetBlockInfoByMac(pInfo->cMac);
		if (pTempBlock)
		{
			//执行删除操作
			DelBlockInfoMac(pTempBlock);
			delete pInfo;
		}
	}
	else
	{
		SBlockInfoMac* pTempBlock = GetBlockInfoByMac(pInfo->cMac);
		if (pTempBlock)
		{
			pTempBlock->begintime = pInfo->begintime;
			pTempBlock->blocktime = pInfo->blocktime;

			delete pInfo;
		}
		else
		{
			pTempBlock = pInfo;
		}

		AddBlockInfoMac(pTempBlock);
	}
	return true;
}

void GLSService::ProcessNewBlockInfo()
{
	ContainerBlockInfo temBlockList;
	{
		CSALocker _lock(_LockList);
		temBlockList = m_BlockInfoList;
		m_BlockInfoList.clear();
	}

	ContainerBlockInfo::iterator it    = temBlockList.begin();
	ContainerBlockInfo::iterator itEnd = temBlockList.end();
	for( ; it!=itEnd ; ++it )
	{
		SBlockInfo* pBlockInfo = (*it);
		if (!pBlockInfo)
		{
			continue;
		}
		
		InsertNewBlockInfo(pBlockInfo);
	}
}
void GLSService::ProcessNewBlockInfoMac()
{
	ContainerBlockInfoMac temBlockList;
	{
		CSALocker _lock(_LockListMac);
		temBlockList = m_BlockInfoListMac;
		m_BlockInfoListMac.clear();
	}

	ContainerBlockInfoMac::iterator it    = temBlockList.begin();
	ContainerBlockInfoMac::iterator itEnd = temBlockList.end();
	for( ; it!=itEnd ; ++it )
	{
		SBlockInfoMac* pBlockInfo = (*it);
		if (!pBlockInfo)
		{
			continue;
		}

		InsertNewBlockInfoMac(pBlockInfo);
	}
}