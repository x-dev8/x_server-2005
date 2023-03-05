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
    virtual uint32 OnReqAccountBilling          ( BaseSqlMessage* pSqlMessage ); // �����ʺŵ���
    virtual uint32 OnReqAccountBillingOp        ( BaseSqlMessage* pSqlMessage ); // �����ʺŵ�������
    virtual uint32 OnReqAccountPoints           ( BaseSqlMessage* pSqlMessage ); // �����ʺų�ֵ

	//�����µļƷѻ���,��:�������ʺ�Ϊ��λ����,�ڴ��������ӵ�����CACHE,����ͨ��ʵʱд������,����ԭ�߼� by vvx
public:
	uint32 LoadAllMoney();
	virtual uint32 OnReqShopping                ( BaseSqlMessage* pSqlMessage );//��������	
	virtual uint32 OnReqOperateMoney            ( BaseSqlMessage* pSqlMessage );//��������
	virtual uint32 OnReqCashMoney               ( BaseSqlMessage* pSqlMessage );//��Ǯ,ƽ̨������
	virtual uint32 OnReqOperateConsumeScore     ( BaseSqlMessage* pSqlMessage );//��������
	virtual uint32 OnReqConsumeScore            ( BaseSqlMessage* pSqlMessage );//�����,ƽ̨������
private:	
	bool          m_bHaveInitMoneyCache;
}; 

#endif // __DATABASE_ACCOUNTBILLINGWORKTHREAD_H__
