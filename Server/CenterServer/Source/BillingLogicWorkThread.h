///********************************************************************
//    Filename:    BillingLogicWorkThread.h
//    MaintenanceMan Mail: debugcommand@hotmail.com
//*********************************************************************/
//
//#ifndef __CENTER_BILLINGLOGICWORKTHREAD_H__
//#define __CENTER_BILLINGLOGICWORKTHREAD_H__
//
//#pragma once
//
//#include "MySqlWorkThread.h"
//#include "SqlMessages.h"
//
//// 正常逻辑的Sql存储线程
//class BillingLogicWorkThread : public MySqlWorkThread
//{
//public:
//    BillingLogicWorkThread( MySqlCommunication* pOwn );
//    virtual ~BillingLogicWorkThread(){}
//
//    virtual bool IsHaveTask()
//    { return _dbMsgQueue.GetQueueSize() > 0; }
//
//    virtual uint32 Update();
//
//public:
//    virtual void OnCS2PAddPayAck( BaseSqlMessage* pSqlMessage ); // 请求充值
//
//protected:
//    // 尝试拿充值纪录
//    void _TryGetPayRecord();
//
//protected:
//    GameTimerEx _timerGetPay; // 获取充值纪录的定时器 
//}; 
//
//#endif // __CENTER_BILLINGLOGICWORKTHREAD_H__
