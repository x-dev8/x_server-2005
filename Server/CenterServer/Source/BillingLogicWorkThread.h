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
//// �����߼���Sql�洢�߳�
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
//    virtual void OnCS2PAddPayAck( BaseSqlMessage* pSqlMessage ); // �����ֵ
//
//protected:
//    // �����ó�ֵ��¼
//    void _TryGetPayRecord();
//
//protected:
//    GameTimerEx _timerGetPay; // ��ȡ��ֵ��¼�Ķ�ʱ�� 
//}; 
//
//#endif // __CENTER_BILLINGLOGICWORKTHREAD_H__
