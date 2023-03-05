/********************************************************************
    Filename:    PlatformRPCLogicWorkThread.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTER_PLATFORMRPCLOGICWORKTHREAD_H__
#define __CENTER_PLATFORMRPCLOGICWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"

// 正常逻辑的Sql存储线程
class PlatformRPCLogicWorkThread : public MySqlWorkThread
{
public:
    PlatformRPCLogicWorkThread( MySqlCommunication* pOwn );
    virtual ~PlatformRPCLogicWorkThread(){}

    virtual bool IsHaveTask()
    { return _dbMsgQueue.GetQueueSize() > 0; }

    virtual uint32 Update();

public:
    //virtual void OnCS2PNewCardReq( BaseSqlMessage* pSqlMessage ); // 查询卡片请求
	
	virtual void OnGS2CSUpdateAntiaddictionInfoReq( BaseSqlMessage* pSqlMessage ); // 查询更新防沉迷信息


protected:
    // 尝试拿GMTask纪录
    void _TryGetGmTaskRecord();

protected:
    GameTimerEx _timerGetPay; // 获取充值纪录的定时器 
}; 

#endif // __CENTER_PLATFORMLOGICWORKTHREAD_H__
