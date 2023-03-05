#include "WorkSpaceTaskModule.h"
#include "PlatformMessageDefine.h"
#include "tstring.h"

CWorkSpaceTaskModule::CWorkSpaceTaskModule(void)
{
}

CWorkSpaceTaskModule::~CWorkSpaceTaskModule(void)
{
}

bool CWorkSpaceTaskModule::ProcessWorkSpceTask(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return false;
	}
	switch(pTask->tasktype)
	{
	case eWorkSpaceTask_AskPresent:
		{
			OnTaskAskForPresent(pTask);
		}
		break;
	case eWorkSpaceTask_AskActivity:
		{
			OnTaskAskForActivity(pTask);
		}
		break;
	case eWorkSpaceTask_EpistarPoint:
		{
			OnTaskAskForEpistarPoint(pTask);
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}

void CWorkSpaceTaskModule::OnTaskAskForPresent(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}

	int result = OnCheckSN(pTask);
	if (result == 0)
	{
		SMailTaskInfo* pMailTaskInfo = TryProcessAskPresent(pTask);
		if (pMailTaskInfo)
		{
			if (!theMYSQLWorkSpace.AddOthermailTaskInfo(pMailTaskInfo))
			{// 错了是否要做些什么?
				printf("OnTaskAskForPresent AddNomalMailTaskInfo error sn=%s!\n",pTask->s.askpresent.sn);
				theMYSQLWorkSpace.ReleaseMailTaskInfo(pMailTaskInfo);
				return;
			}
			pTask->result = result;
			theMYSQLWorkSpace.AddWorkSpaceTaskResult(pTask);
		}
	}
	SErrorInfo* pError = thePlatFormWorkSpace.CreateErrorInfoTaskPool();
	if (!pError)
	{
		printf("OnTaskAskForPresent CreateErrorInfoTaskPool error!\n");
		return;
	}
	pError->accountid = pTask->s.askpresent.accountid;
	pError->characterid = pTask->s.askpresent.characterid;
	pError->serverid = pTask->serverid;

	switch(result)
	{
	case 0:
		pError->result = eError_PresentSucc;
		break;
	case 1:
		pError->result = eError_Unkown;
		break;
	case 2:
	case -1:
		pError->result = eError_SNError;
		break;
	case 3:
		pError->result = eError_AccountError;
		break;
	case 4:
		pError->result = eError_CharacterError;
		break;
	}
	thePlatFormWorkSpace.AddErrorTask(pError);
}

short CWorkSpaceTaskModule::OnCheckSN(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return -1;
	}

	int result = -1;
	char szSql[1024] = {0};
	try
	{
		memset( szSql, 0, sizeof(szSql));
		sprintf_s( szSql, sizeof( szSql ) - 1,"call CheckPresent( '%s', %u, %u, %u );", pTask->s.askpresent.sn,
			pTask->s.askpresent.accountid,pTask->s.askpresent.characterid,pTask->serverid);
		mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query();
		mysqlQuery.execute(szSql);
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		printf("BadQuery [%s] Error:%s\n",szSql, er.what());
	}

	try
	{
		memset( szSql, 0, sizeof(szSql));
		sprintf_s( szSql, sizeof( szSql ) - 1,"select check_result from Present where serialnumber = '%s';", 
			pTask->s.askpresent.sn);
		mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query(szSql);
		mysqlpp::StoreQueryResult res = mysqlQuery.store();
		if (res&&!res.empty())
		{
			result = res[0]["check_result"];
		}
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		printf("BadQuery [%s] Error:%s\n",szSql, er.what());
	}
	return result;
}

void CWorkSpaceTaskModule::DoneAskPresent(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}
	char szSqlout[1024] = {0};
	try
	{	
		memset( szSqlout, 0, sizeof(szSqlout));
		sprintf_s( szSqlout, sizeof( szSqlout ) - 1, "CALL DonePresent('%s',%d,%d,%d,%d);",pTask->s.askpresent.sn,
			pTask->result,pTask->s.askpresent.accountid,pTask->s.askpresent.characterid,pTask->serverid);

		mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query();
		mysqlQuery.execute(szSqlout);
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		printf("BadQuery [%s] Error:%s\n",szSqlout, er.what());
	}

	thePlatFormWorkSpace.ReleaseWorkSpaceTask(pTask);
}

SMailTaskInfo* CWorkSpaceTaskModule::TryProcessAskPresent(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return NULL;
	}

	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select * from Present where serialnumber='%s';", pTask->s.askpresent.sn);
	mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query(szSql);  
	mysqlpp::StoreQueryResult res = mysqlQuery.store(/*szSql, sizeof(szSql)*/);
	if (res&&!res.empty())
	{
		int server_id = res[0]["serverid"];
		if (server_id != eTaskResult_AllServer&&server_id != pTask->serverid)
		{
			printf("serverid error!task=%d,sql=%d,sn=%s\n",pTask->serverid,server_id,pTask->s.askpresent.sn);
			mysqlQuery.reset();
			return NULL;
		}

		SMailTaskInfo* pInfo = theMYSQLWorkSpace.CreateMailTaskInfo();
		if (!pInfo)
		{
			printf("OnTaskAskForPresent CreateMailTaskInfo error!\n");
			mysqlQuery.reset();
			return NULL;
		}
		pInfo->id				= 0;
		pInfo->characterid		= pTask->s.askpresent.characterid;			
		strncpy_s( pInfo->charactername, sizeof( pInfo->charactername ),pTask->s.askpresent.charactername, sizeof( pInfo->charactername ) - 1 );
		Common::_tstring strTitle;
		strTitle.fromUTF8(res[0]["mail_title"]);
		if (!strTitle.empty())
		{
			strncpy_s( pInfo->title, sizeof( pInfo->title ),strTitle.c_str() , sizeof( pInfo->title ) - 1 );
		}
		Common::_tstring strContent;
		strContent.fromUTF8(res[0]["mail_content"]);
		if (!strContent.empty())
		{
			strncpy_s( pInfo->content, sizeof( pInfo->content ),strContent.c_str(), sizeof( pInfo->content ) - 1 );
		}
		pInfo->money			= res[0]["money"];
		pInfo->itemid			= res[0]["itemid"];
		pInfo->itemcount		= res[0]["itemcount"];
		pInfo->serverid			= pTask->serverid;
		pInfo->result			= eTaskResult_ResNo;
		pInfo->_type			= eMailType_Present;

		mysqlQuery.reset();
		return pInfo;
	}
}

void CWorkSpaceTaskModule::OnTaskAskForActivity(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}

	bool Succ = false;
	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select * from Activity where type=%d and accountid=%d;",pTask->s.askactivity._type,pTask->s.askactivity.accountid);
	mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query(szSql);  
	mysqlpp::StoreQueryResult res = mysqlQuery.store(/*szSql, sizeof(szSql)*/);
	if (res&&!res.empty())
	{
		for (int n =0;n < res.num_rows();n++)
		{
			if (n >= ETaskInfo_ActivityIDArray)
			{//最多处理30个
				return;
			}

			int server_id = res[n]["serverid"];
			int _id = res[n]["id"];
			int character_id = res[n]["characterid"];
			if (server_id != eTaskResult_AllServer&&server_id != pTask->serverid)
			{
				printf("serverid error!task=%d,sql=%d,id=%d\n",pTask->serverid,server_id,_id);
				mysqlQuery.reset();
				continue;
			}
			if (character_id > 0&&pTask->s.askactivity.characterid != character_id)
			{
				printf("character id check error!task=%d,sql=%d,id=%d\n",pTask->s.askactivity.characterid,character_id,_id);
				mysqlQuery.reset();
				continue;
			}

			SMailTaskInfo* pInfo = theMYSQLWorkSpace.CreateMailTaskInfo();
			if (!pInfo)
			{
				printf("OnTaskAskForPresent CreateMailTaskInfo error!\n");
				mysqlQuery.reset();
				return;
			}
			pInfo->id				= 0;
			pInfo->characterid		= pTask->s.askactivity.characterid;			
			strncpy_s( pInfo->charactername, sizeof( pInfo->charactername ),pTask->s.askactivity.charactername, sizeof( pInfo->charactername ) - 1 );
			Common::_tstring strTitle;
			strTitle.fromUTF8(res[n]["mail_title"]);
			if (!strTitle.empty())
			{
				strncpy_s( pInfo->title, sizeof( pInfo->title ),strTitle.c_str() , sizeof( pInfo->title ) - 1 );
			}
			Common::_tstring strContent;
			strContent.fromUTF8(res[n]["mail_content"]);
			if (!strContent.empty())
			{
				strncpy_s( pInfo->content, sizeof( pInfo->content ),strContent.c_str(), sizeof( pInfo->content ) - 1 );
			}
			pInfo->money			= res[n]["money"];
			pInfo->itemid			= res[n]["itemid"];
			pInfo->itemcount		= res[n]["itemcount"];
			pInfo->serverid			= pTask->serverid;
			pInfo->result			= eTaskResult_ResNo;
			pInfo->_type			= eMailType_Activity;


			if (!theMYSQLWorkSpace.AddOthermailTaskInfo(pInfo))
			{// 错了是否要做些什么?
				printf("OnTaskAskForActivity AddOthermailTaskInfo error id=%d!\n",_id);
				theMYSQLWorkSpace.ReleaseMailTaskInfo(pInfo);
				continue;
			}
			pTask->s.askactivity.idArray[n] = _id;
			Succ = true;
		}
	}	
	mysqlQuery.reset();

	SErrorInfo* pError = thePlatFormWorkSpace.CreateErrorInfoTaskPool();
	if (!pError)
	{
		printf("OnTaskAskForPresent CreateErrorInfoTaskPool error!\n");
		return;
	}
	pError->accountid = pTask->s.askactivity.accountid;
	pError->characterid = pTask->s.askactivity.characterid;
	pError->serverid = pTask->serverid;
	if (Succ)
	{
		pError->result = eError_ActivitySucc;
	}
	else
		pError->result = eError_NoActivity;

	thePlatFormWorkSpace.AddErrorTask(pError);

	pTask->result = eTaskResult_ResSucc;
	theMYSQLWorkSpace.AddWorkSpaceTaskResult(pTask);	
}

void CWorkSpaceTaskModule::OnTaskAskForEpistarPoint(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}
	//mysql 操作
	bool Succ = false;
	char szSql[1024] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1,"select epistarpoint, addpointmax from epistar where accountid = %d and serverid = %d",
		pTask->s.askEpistarPoint.accountid,pTask->serverid);

	mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query(szSql);  
	mysqlpp::StoreQueryResult res = mysqlQuery.store(/*szSql, sizeof(szSql)*/);
	int epistarpoint = 0;
	int addpointmax  = 0;
	if (res&&!res.empty())
	{
		for (int n =0;n < res.num_rows();n++)
		{
			if (n >= ETaskInfo_ActivityIDArray)
			{//最多处理30个
				return;
			}
			epistarpoint = res[n]["epistarpoint"];
			addpointmax  = res[n]["addpointmax"];
			Succ = true;
		}
	}
	mysqlQuery.reset();
	if (Succ)
	{
		memset( szSql, 0, sizeof(szSql));
		sprintf_s( szSql, sizeof( szSql ) - 1,
			"update epistar set epistarpoint=%d, addpointmax=%d where accountid = %d and serverid = %d;",  
			epistarpoint+pTask->s.askEpistarPoint.nPoint,addpointmax+pTask->s.askEpistarPoint.nPoint,
			pTask->s.askEpistarPoint.accountid,pTask->serverid);
	}
	else
	{
		memset( szSql, 0, sizeof(szSql));
		sprintf_s( szSql, sizeof( szSql ) - 1,
			"insert into epistar(accountid,serverid,epistarpoint,addpointmax) values(%u,%u,%u,%u);",  
			pTask->s.askEpistarPoint.accountid,pTask->serverid,
			pTask->s.askEpistarPoint.nPoint,pTask->s.askEpistarPoint.nPoint);
	}
	Succ = true;
	try
	{
		mysqlpp::Query mysqlQuery2 = theMYSQLWorkSpace.GetMySqlConnect()->query(szSql); 
		mysqlpp::StoreQueryResult res2 = mysqlQuery2.store(/*szSql, sizeof(szSql)*/);
		mysqlQuery2.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		Succ = false;
		printf("BadQuery [%s] Error:%s\n",szSql, er.what());
	}

	SErrorInfo* pError = thePlatFormWorkSpace.CreateErrorInfoTaskPool();
	if (!pError)
	{
		printf("OnTaskAskForEpistarPoint CreateErrorInfoTaskPool error!\n");
		return;
	}
	pError->accountid = pTask->s.askEpistarPoint.accountid;
	pError->characterid = pTask->s.askEpistarPoint.characterid;
	pError->serverid = pTask->serverid;
	if (Succ)
	{
		pError->result = eError_EpistarPointSucc;
		MsgPFEpistarPointACK msg;
		msg.accountid   = pTask->s.askEpistarPoint.accountid;
		msg.characterid = pTask->s.askEpistarPoint.characterid;
		msg.nItemId		= pTask->s.askEpistarPoint.nItemId;
		thePlatFormWorkSpace.SendMsgToSingleServer(&msg,pTask->serverid);
	}
	else
		pError->result = eError_EpistarPointError;

	thePlatFormWorkSpace.AddErrorTask(pError);

	pTask->result = Succ ? eTaskResult_ResSucc : eTaskResult_ResFail;
	theMYSQLWorkSpace.AddWorkSpaceTaskResult(pTask);
}
void CWorkSpaceTaskModule::DoneAskActivity(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}

	char szSqlout[1024] = {0};
	for (int n = 0;n < ETaskInfo_ActivityIDArray;n++)
	{
		if (pTask->s.askactivity.idArray[n] <= 0)
		{
			continue;
		}
		try
		{	
			memset( szSqlout, 0, sizeof(szSqlout));
			sprintf_s( szSqlout, sizeof( szSqlout ) - 1, "CALL DoneActivity(%d,%d,%d,%d,%d);",pTask->result,
				pTask->s.askactivity.idArray[n],pTask->s.askactivity.accountid,pTask->s.askactivity.characterid,
				pTask->serverid);

			mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query();
			mysqlQuery.execute(szSqlout);
			mysqlQuery.reset();
		}
		catch (mysqlpp::BadQuery er)
		{
			printf("BadQuery [%s] Error:%s\n",szSqlout, er.what());
		}
	}
	thePlatFormWorkSpace.ReleaseWorkSpaceTask(pTask);
}
void CWorkSpaceTaskModule::DoneEpistarPoint(SWorkSpaceTask* pTask)
{
	if (!pTask)
	{
		return;
	}
	if (pTask->result == eTaskResult_ResFail)
	{
		return;
	}
	char szSqlLog[1024] = {0};
	try
	{	
		memset( szSqlLog, 0, sizeof(szSqlLog));
		sprintf_s( szSqlLog, sizeof( szSqlLog ) - 1, 
			"insert into epistar_log(accountid,serverid,charid,charname,changepoint,itemid,date) values(%u,%u,%u,'%s',%d,%d,now());",
			pTask->s.askEpistarPoint.accountid,pTask->serverid,pTask->s.askEpistarPoint.characterid,
			_tUTF8CHAR(pTask->s.askEpistarPoint.charactername),pTask->s.askEpistarPoint.nPoint,pTask->s.askEpistarPoint.nItemId);

		mysqlpp::Query mysqlQuery = theMYSQLWorkSpace.GetMySqlConnect()->query();
		mysqlQuery.execute(szSqlLog);
		mysqlQuery.reset();
	}
	catch (mysqlpp::BadQuery er)
	{
		printf("BadQuery [%s] Error:%s\n",szSqlLog, er.what());
	}

	thePlatFormWorkSpace.ReleaseWorkSpaceTask(pTask);
}