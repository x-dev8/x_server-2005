#include "MySQLWorkSpace.h"
#include "PlatformConfig.h"
#include "tstring.h"
#include "WorkSpaceTaskModule.h"


CMySQLWorkSpace::CMySQLWorkSpace(void)
{
	_pMysqlConnect = NULL;
	_workState = SS_TryConnect;	
	_lastUpdateTime = HQ_TimeGetTime();
	_lastGetGMTaskTime = HQ_TimeGetTime();
	_mapGMTaskInfo.clear();
	//_mapGMTaskInfoWaiting.clear();

	_lastGetMailTaskTime = HQ_TimeGetTime();

	_mapMailTaskInfo.clear();
	_MailTaskInfoList.clear();
	_vecOtherMailTaskInfo.clear();
	_OtherMailTaskInfoList.clear();

	_WorkSpaceTaskListResult.clear();

	GMTaskPool ();
	//MailTaskPool();
}

CMySQLWorkSpace::~CMySQLWorkSpace(void)
{
	if (_pMysqlConnect)
	{
		delete _pMysqlConnect;
	}
}

void CMySQLWorkSpace::_TryConnectToSqlDb()
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
				bool ConnectOk = _pMysqlConnect->connect(thePlatFormConfig.strTaskDatabaseName.c_str(), 
					thePlatFormConfig.strTaskDatabaseIP.c_str(), 
					thePlatFormConfig.strTaskDatabaseUser.c_str(),
					thePlatFormConfig.strTaskDatabasePwd.c_str(), 
					thePlatFormConfig.TaskDatabasePort);

				if ( !ConnectOk )
				{
					printf("connect platform db error!\n");					
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

bool CMySQLWorkSpace::_CheckState()
{    
	if (!_pMysqlConnect||!_pMysqlConnect->connected())
	{
		_workState = SS_ReConnected;
		return false;
	}

	// 3分钟PING一次
	if ( _lastUpdateTime == 0)
	{ _lastUpdateTime = timeGetTime(); }

	if ( !GameTime::IsPassCurrentTime( _lastUpdateTime, ECD_PingTime ) )
	{ return true; }

	_lastUpdateTime = timeGetTime();
	if (! _pMysqlConnect->ping())
	{
		_workState = SS_ReConnected;
		return false;
	}

	return true;
}

void CMySQLWorkSpace::Run()
{
	if (!_CheckState())
	{
		if (GetWorkState() != CMySQLWorkSpace::SS_Connected)
		{
			_TryConnectToSqlDb();
			return;
		}
	}

	RunGMTask();
	RunMailTask();
	RunWorkSpaceTask();
	Sleep(1);
}

void CMySQLWorkSpace::RunGMTask()
{
	if (thePlatFormConfig.openCheckService)
	{
		return;
	}

	if (GameTime::IsPassCurrentTime( _lastGetGMTaskTime, ECD_GETGMTASKTIME )/*&&_mapGMTaskInfo.empty()*/)
	{
		GetGMTaskInfoInMYSql();
		_lastGetGMTaskTime = HQ_TimeGetTime();
	}

	ChenckTaskResult();
}

bool CMySQLWorkSpace::AddNomalGMTaskInfo(SGMTaskInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}
	CSALocker lock(&_TaskLock);

	mapGMTaskInfo::iterator itr = _mapGMTaskInfo.find(pInfo->id);
	//mapGMTaskInfo::iterator itrWaiting = _mapGMTaskInfoWaiting.begin();
	if (itr != _mapGMTaskInfo.end()/*||itr != _mapGMTaskInfoNomal.end()*/)
	{
		return false;
	}

	_mapGMTaskInfo.insert(mapGMTaskInfo::value_type(pInfo->id,pInfo));
	_GmTaskInfoList.push_back(pInfo);
	return true;
}

SGMTaskInfo* CMySQLWorkSpace::GetGMTaskInfo()
{
	CSALocker lock(&_TaskLock);
	if ( _GmTaskInfoList.empty())
	{ return NULL;}

	SGMTaskInfo* rMessage = _GmTaskInfoList.front();
	_GmTaskInfoList.pop_front();
	return rMessage;
}

bool CMySQLWorkSpace::GetGMTaskInfoInMYSql()
{
	char szSql[512] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select * from gm_task  limit 0, 50;");

	try
	{
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();

		if (res&&!res.empty())
		{
			for (int n =0;n < res.num_rows();n++)
			{
				SGMTaskInfo* pInfo = CreateGMTaskInfo();
				if (!pInfo)
				{
					printf("CreateGMTaskInfo error!\n");
					mysqlQuery.reset();
					return false;
				}
				pInfo->id = res[n]["id"];
				Common::_tstring strContent;
				strContent.fromUTF8(res[n]["content"]);
				if (!strContent.empty())
				{
					strncpy_s( pInfo->content, sizeof( pInfo->content ), strContent.c_str(), sizeof( pInfo->content ) - 1 );
				}
				pInfo->serverid = res[n]["serverid"];
				pInfo->result = eTaskResult_ResNo;

				if (!AddNomalGMTaskInfo(pInfo))
				{// 错了是否要做些什么?
				}
			}
		}
		mysqlQuery.reset();
	}
	catch (exception& er)
	{
		printf("BadQuery [%s] Error:%s\n",szSql, er.what());
	}
	

	return true;
}

#define Check_GMTASK_COUNT 50
void CMySQLWorkSpace::ChenckTaskResult()
{
	CSALocker lock(&_TaskLock);
	int n =0;
	char szSql[512] = {0};
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();

	SGMTaskInfo* pInfo = NULL;
	mapGMTaskInfo::iterator itr = _mapGMTaskInfo.begin();
	while(itr != _mapGMTaskInfo.end())
	{
		pInfo = itr->second;
		if (!pInfo)
		{
			itr = _mapGMTaskInfo.erase(itr);
			continue;
		}

		if (pInfo->result != eTaskResult_ResNo)
		{
			memset( szSql, 0, sizeof(szSql));
			sprintf_s( szSql, sizeof( szSql ) - 1, "CALL DoneGmTask(%d,%d);",pInfo->id,pInfo->result);			
			mysqlQuery.execute(szSql);
			mysqlQuery.reset();

			ReleaseGMTaskInfo(pInfo);

			itr = _mapGMTaskInfo.erase(itr);
			continue;
		}
		itr++;
		n++;
		if (n >= Check_GMTASK_COUNT)
		{
			break;
		}
	}
}

void CMySQLWorkSpace::RunMailTask()
{
	if (GameTime::IsPassCurrentTime( _lastGetMailTaskTime, ECD_GETMAILTASKTIME ))
	{
		GetMailTaskInfoInMYSql();
		_lastGetMailTaskTime = HQ_TimeGetTime();
	}

	ChenckMailTaskResult();
}

bool CMySQLWorkSpace::GetMailTaskInfoInMYSql()
{
	char szSql[512] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select * from maillist limit 0, 50;");

	mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);
	mysqlpp::StoreQueryResult res = mysqlQuery.store();

	if (res&&!res.empty())
	{
		for (int n =0;n < res.num_rows();n++)
		{
			SMailTaskInfo* pInfo = CreateMailTaskInfo();
			if (!pInfo)
			{
				printf("CreateMailTaskInfo error!\n");
				mysqlQuery.reset();
				return false;
			}
			pInfo->id				= res[n]["id"];
			pInfo->characterid		= res[n]["characterid"];
			Common::_tstring strName;
			strName.fromUTF8(res[n]["charactername"]);
			if (!strName.empty())
			{
				strncpy_s( pInfo->charactername, sizeof( pInfo->charactername ),strName.c_str() , sizeof( pInfo->charactername ) - 1 );
			}
			Common::_tstring strTitle;
			strTitle.fromUTF8(res[n]["title"]);
			if (!strTitle.empty())
			{
				strncpy_s( pInfo->title, sizeof( pInfo->title ),strTitle.c_str() , sizeof( pInfo->title ) - 1 );
			}
			Common::_tstring strContent;
			strContent.fromUTF8(res[n]["contents"]);
			if (!strContent.empty())
			{
				strncpy_s( pInfo->content, sizeof( pInfo->content ),strContent.c_str(), sizeof( pInfo->content ) - 1 );
			}
			pInfo->money			= res[n]["money"];
			pInfo->itemid			= res[n]["itemid"];
			pInfo->itemcount		= res[n]["itemcount"];
			pInfo->serverid			= res[n]["serverid"];
			pInfo->result			= eTaskResult_ResNo;
			pInfo->_type			= eMailType_maillist;

			if (!AddNomalMailTaskInfo(pInfo))
			{// 错了是否要做些什么?
			}			
		}
	}
	mysqlQuery.reset();

	return true;
}

bool CMySQLWorkSpace::AddNomalMailTaskInfo(SMailTaskInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}
	CSALocker lock(&_TaskLock);

	mapMailTaskInfo::iterator itr = _mapMailTaskInfo.find(pInfo->id);
	if (itr != _mapMailTaskInfo.end())
	{
		return false;
	}

	_mapMailTaskInfo.insert(mapMailTaskInfo::value_type(pInfo->id,pInfo));
	_MailTaskInfoList.push_back(pInfo);
	return true;
}

bool CMySQLWorkSpace::AddOthermailTaskInfo(SMailTaskInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}
	CSALocker lock(&_TaskLock);
	_vecOtherMailTaskInfo.push_back(pInfo);
	_OtherMailTaskInfoList.push_back(pInfo);
	return true;
}

#define Check_NormalMail_Max 30
#define Check_OtherNormalMail_Max 30
void CMySQLWorkSpace::ChenckMailTaskResult()
{
	CSALocker lock(&_TaskLock);
	int n = 0;
	char szSql[512] = {0};
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();

	SMailTaskInfo* pInfo = NULL;
	mapMailTaskInfo::iterator itr = _mapMailTaskInfo.begin();
	while(itr != _mapMailTaskInfo.end())
	{
		pInfo = itr->second;
		if (!pInfo)
		{
			itr = _mapMailTaskInfo.erase(itr);
			continue;
		}

		if (pInfo->result != eTaskResult_ResNo)
		{
			if (pInfo->_type == eMailType_maillist)
			{
				memset( szSql, 0, sizeof(szSql));
				sprintf_s( szSql, sizeof( szSql ) - 1, "CALL DoneMailTask(%d,%d);",pInfo->id,pInfo->result);
				mysqlQuery.execute(szSql);
				mysqlQuery.reset();
			}

			ReleaseMailTaskInfo(pInfo);

			itr = _mapMailTaskInfo.erase(itr);
			continue;
		}
		itr++;
		n++;
		if (n >= Check_NormalMail_Max)
		{
			break;
		}
	}

	n = 0;
	pInfo = NULL;
	vecMailTaskInfo::iterator itrVec = _vecOtherMailTaskInfo.begin();
	while(itrVec != _vecOtherMailTaskInfo.end())
	{
		pInfo = *itrVec;
		if (!pInfo)
		{
			itrVec = _vecOtherMailTaskInfo.erase(itrVec);
			continue;
		}
		if (pInfo->result != eTaskResult_ResNo)
		{
			ReleaseMailTaskInfo(pInfo);

			itrVec = _vecOtherMailTaskInfo.erase(itrVec);
			continue;
		}
		itrVec++;
		n++;
		if (n >= Check_OtherNormalMail_Max)
		{
			break;
		}
	}
}

SMailTaskInfo* CMySQLWorkSpace::GetMailTaskInfo()
{
	CSALocker lock(&_TaskLock);
	if ( _MailTaskInfoList.empty())
	{ return NULL;}

	SMailTaskInfo* rMessage = _MailTaskInfoList.front();
	_MailTaskInfoList.pop_front();
	return rMessage;
}

SMailTaskInfo* CMySQLWorkSpace::GetOtherMailTaskInfo()
{
	CSALocker lock(&_TaskLock);
	if ( _OtherMailTaskInfoList.empty())
	{ return NULL;}

	SMailTaskInfo* rMessage = _OtherMailTaskInfoList.front();
	_OtherMailTaskInfoList.pop_front();
	return rMessage;
}

#define MAX_WORKSPACETASK_COUNT 50
void CMySQLWorkSpace::RunWorkSpaceTask()
{

	ChenckWorkSpaceTaskResult();
	int n =0;
	SWorkSpaceTask* pTask = NULL;
	while(pTask = thePlatFormWorkSpace.GetWorkSpaceTask())
	{
		if (pTask&&pTask->result == eTaskResult_ResNo)
		{
			theWorkSpaceTaskModule.ProcessWorkSpceTask(pTask);			

			n++;
			if (n >= MAX_WORKSPACETASK_COUNT)
			{
				break;
			}
		}
	}	
}

void CMySQLWorkSpace::ChenckWorkSpaceTaskResult()
{
	CSALocker lock(&_TaskLock);

	char szSql[512] = {0};
	mysqlpp::Query mysqlQuery = _pMysqlConnect->query();

	SWorkSpaceTask* pInfo = NULL;	
	while(pInfo = GetWorkSpaceTaskResult())
	{
		if (pInfo->result != eTaskResult_ResNo)
		{
			switch(pInfo->tasktype)
			{
			case eWorkSpaceTask_AskPresent:
				{
					theWorkSpaceTaskModule.DoneAskPresent(pInfo);
				}
				break;
			case eWorkSpaceTask_AskActivity:
				{
					theWorkSpaceTaskModule.DoneAskActivity(pInfo);
				}
				break;
			case eWorkSpaceTask_EpistarPoint://写日志
				{
					theWorkSpaceTaskModule.DoneEpistarPoint(pInfo);
				}
				break;
			default:
				break;
			}
		}
	}
}

void CMySQLWorkSpace::AddWorkSpaceTaskResult(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}
	CSALocker lock(&_TaskLock);
	_WorkSpaceTaskListResult.push_back(pTask);
}

SWorkSpaceTask* CMySQLWorkSpace::GetWorkSpaceTaskResult()
{
	if ( _WorkSpaceTaskListResult.empty())
	{ return NULL;}

	CSALocker lock(&_TaskLock);
	SWorkSpaceTask* rMessage = _WorkSpaceTaskListResult.front();
	_WorkSpaceTaskListResult.pop_front();
	return rMessage;
}