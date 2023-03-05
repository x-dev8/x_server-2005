/********************************************************************
    Filename:     MessageDefine.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/
#ifndef __MySqlTaskDefine_H__
#define __MySqlTaskDefine_H__

#pragma once
#include "MeRTLibsServer.h"
#include "Memory_Pool.h"

enum ETaskDefine
{
	eTaskBegin = 0,
	eReq_Check_Account,           //«Î«ÛºÏ≤‚’ ∫≈
	eAck_Check_Account,           //∑µªÿºÏ≤‚’ ∫≈Ω·π˚
	eTaskEnd
};

struct STaskBase
{
	unsigned short task_type;
};

struct SReqCheckAccount:public STaskBase , INHERIT_POOL(SReqCheckAccount)
{
	SReqCheckAccount()
	{
		task_type = eReq_Check_Account;
		memset(account_name,0,17);
		memset(passwords,0,14);
	}
	DECLARE_POOL_FUNC(SReqCheckAccount)
	~SReqCheckAccount(){}

	char account_name[17];
	char passwords[14];
};

enum eCheckResult
{
	eCheckResult_succ = 0,         //≥…π¶
	eCheckResult_error_account,    //Œﬁ’ ∫≈
	eCheckResult_error_pwd,        //√‹¬Î¥ÌŒÛ
	eCheckResult_fail,             //Œ¥÷™¥ÌŒÛ
};

struct SAckCheckAccount:public STaskBase , INHERIT_POOL(SAckCheckAccount)
{
	SAckCheckAccount()
	{
		task_type = eAck_Check_Account;
	}
	DECLARE_POOL_FUNC(SAckCheckAccount)
	~SAckCheckAccount(){}

	unsigned short result;
	int    account_id;
	char   account_name[17];
	unsigned short addictedstate;
};

#endif