/********************************************************************
    Filename:    AccountBillingWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __DATABASE_ACCOUNTBILLINGWORKTHREAD_H__
#define __DATABASE_ACCOUNTBILLINGWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"
#include "AccountBillingDefine.h"

class AccountBillingWorkThread : public MySqlWorkThread
{
public:
    AccountBillingWorkThread( MySqlCommunication* pOwn );
    virtual ~AccountBillingWorkThread(){}

    virtual bool IsHaveTask()
    { return _dbMsgQueue.GetOtherQueueSize() > 0; }

    virtual uint32 Update();
    virtual uint32 OnReqAccountBilling          ( BaseSqlMessage* pSqlMessage ); // 请求帐号点数
    virtual uint32 OnReqAccountBillingOp        ( BaseSqlMessage* pSqlMessage ); // 请求帐号点数操作
    virtual uint32 OnReqAccountPoints           ( BaseSqlMessage* pSqlMessage ); // 请求帐号冲值

	//加入新的计费机制,即:点数以帐号为单位消耗,在次类中增加点数的CACHE,消费通过实时写入数据,保留原逻辑 by vvx
public:
	uint32 LoadAllMoney();
	virtual uint32 OnReqShopping                ( BaseSqlMessage* pSqlMessage );//请求消费	
	virtual uint32 OnReqOperateMoney            ( BaseSqlMessage* pSqlMessage );//操作点数
	virtual uint32 OnReqCashMoney               ( BaseSqlMessage* pSqlMessage );//冲钱,平台过来的
	virtual uint32 OnReqOperateConsumeScore     ( BaseSqlMessage* pSqlMessage );//操作积分
	virtual uint32 OnReqConsumeScore            ( BaseSqlMessage* pSqlMessage );//冲积分,平台过来的
private:	
	bool          m_bHaveInitMoneyCache;
}; 

#endif // __DATABASE_ACCOUNTBILLINGWORKTHREAD_H__
