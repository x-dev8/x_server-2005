/********************************************************************
    Filename:    PlatformRPCLogicWorkThread.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTER_PLATFORMRPCLOGICWORKTHREAD_H__
#define __CENTER_PLATFORMRPCLOGICWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"

// �����߼���Sql�洢�߳�
class PlatformRPCLogicWorkThread : public MySqlWorkThread
{
public:
    PlatformRPCLogicWorkThread( MySqlCommunication* pOwn );
    virtual ~PlatformRPCLogicWorkThread(){}

    virtual bool IsHaveTask()
    { return _dbMsgQueue.GetQueueSize() > 0; }

    virtual uint32 Update();

public:
    //virtual void OnCS2PNewCardReq( BaseSqlMessage* pSqlMessage ); // ��ѯ��Ƭ����
	
	virtual void OnGS2CSUpdateAntiaddictionInfoReq( BaseSqlMessage* pSqlMessage ); // ��ѯ���·�������Ϣ


protected:
    // ������GMTask��¼
    void _TryGetGmTaskRecord();

protected:
    GameTimerEx _timerGetPay; // ��ȡ��ֵ��¼�Ķ�ʱ�� 
}; 

#endif // __CENTER_PLATFORMLOGICWORKTHREAD_H__
