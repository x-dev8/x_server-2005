/********************************************************************
    Filename:    PlatformLogicWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __CENTER_PLATFORMLOGICWORKTHREAD_H__
#define __CENTER_PLATFORMLOGICWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"

// �����߼���Sql�洢�߳�
class PlatformLogicWorkThread : public MySqlWorkThread
{
public:
    PlatformLogicWorkThread( MySqlCommunication* pOwn );
    virtual ~PlatformLogicWorkThread(){}

    virtual bool IsHaveTask()
    { return _dbMsgQueue.GetQueueSize() > 0; }

    virtual uint32 Update();

public:
    virtual void OnCS2PNewCardReq( BaseSqlMessage* pSqlMessage ); // ��ѯ��Ƭ����

protected:
    // ������GMTask��¼
    void _TryGetGmTaskRecord();

protected:
    GameTimerEx _timerGetPay; // ��ȡ��ֵ��¼�Ķ�ʱ�� 
}; 

#endif // __CENTER_PLATFORMLOGICWORKTHREAD_H__
