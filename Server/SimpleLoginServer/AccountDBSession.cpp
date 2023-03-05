#include "AccountDBSession.h"
#include "config/config_file.h"
#include "GameTime.h"
#include <MMSystem.h>

#include <vector>

CAccountDBSession::CAccountDBSession(void)
{
	_pMysqlConnect = NULL;
	_workState = SS_TryConnect;
}

CAccountDBSession::~CAccountDBSession(void)
{
	if (_pMysqlConnect)
	{
		delete _pMysqlConnect;
	}
}

void CAccountDBSession::_TryConnectToSqlDb()
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
		{ // 启示没有必要这样重连, 连接池都是可用的连接
			//_connectTime.StartTimer( timeGetTime(), ECD_ConnectIntervalTime );
			//if ( !_connectTime.DoneTimer( timeGetTime() ))
			//{ return; }

			try
			{
				if ( _workState == SS_ReConnected)
				{ _pMysqlConnect->disconnect();}
				_pMysqlConnect->set_option(new mysqlpp::MultiStatementsOption(true));
				_pMysqlConnect->set_option(new mysqlpp::SetCharsetNameOption("utf8"));
				bool ConnectOk = _pMysqlConnect->connect( CConfig::Instance().GetAccountDBNAME(), CConfig::Instance().GetAccountDBIP(), 
														CConfig::Instance().GetAccountDBID(), CConfig::Instance().GetAccountDBPWD(), CConfig::Instance().GetAccountDBPORT() );

				if ( !ConnectOk )
				{
					printf("connect account db error!\n");
					//LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"workstate[%d] Connect MySql [Error]", _workState);
					return;
				}

				// 设置mysql超时为24小时
				mysqlpp::Query query =_pMysqlConnect->query("set interactive_timeout = 24*3600");
				query.execute();

				//if ( _workState == SS_TryConnect)
				//{ LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "WorkThread[%d] Connect MySql Success.", _threadId ); }
				//else
				//{ LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "WorkThread[%d] ReConnect MySql Success.", _threadId ); }

				_workState = SS_Connected; 

			}
			catch (exception& er)
			{
				//LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"WorkThread[%d] workstate[%d] Connect MySql Error:%s !", _threadId, _workState, er.what());
			}
		}
		break;
	}
}

bool CAccountDBSession::_CheckState()
{    
	if (!_pMysqlConnect||!_pMysqlConnect->connected())
	{
		_workState = SS_ReConnected;
		return false;
	}

	// 5分钟PING一次
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

struct Account
{
	int id;
	string name;
	string pwd;
	int add;
	int del;
};

void CAccountDBSession::TestSQLDb()//测试数据库
{
	char szSql[512] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select * from account_table;");

	mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);        
	mysqlpp::StoreQueryResult res = mysqlQuery.store();

	std::vector<Account*> _vecAccount;

	if (res&&!res.empty())
	{
		for (int n =0;n < res.num_rows();n++)
		{
			Account* pA = new Account;
			pA->id = res[n]["accountid"];
			pA->name = res[n]["name"];
			pA->pwd = res[n]["password"];
			pA->add = res[n]["addictedstate"];
			pA->del = res[n]["is_del"];

			_vecAccount.push_back(pA);
		}
	}
	mysqlQuery.reset();
}

#define ERORR_ACCOUNT_ID 0xffffffff
unsigned long CAccountDBSession::CheckAccount(const char* AccountName,const char* AccountPWD)
{
	if (AccountName == NULL||AccountPWD == NULL)
	{
		return ERORR_ACCOUNT_ID;
	}

	unsigned long account_id = ERORR_ACCOUNT_ID;
	char szSql[512] = {0};
	memset( szSql, 0, sizeof(szSql));
	sprintf_s( szSql, sizeof( szSql ) - 1, "select accountid from account_table where name='%s' and password='%s';",AccountName,AccountPWD);

	mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);
	mysqlpp::StoreQueryResult res = mysqlQuery.store();
	if (res&&!res.empty())
	{
		for (int n =0;n < res.num_rows();n++)
		{
			account_id = res[n]["accountid"];
		}
	}
	mysqlQuery.reset();

	return account_id;
}
