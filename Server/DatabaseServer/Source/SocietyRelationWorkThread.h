/********************************************************************
    Filename:    SocietyRelationWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASE_SOCIETYRELATIONWORKTHREAD_H__
#define __DATABASE_SOCIETYRELATIONWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"

// 正常逻辑的Sql存储线程
class SocietyRelationWorkThread : public MySqlWorkThread
{
public:
    SocietyRelationWorkThread( MySqlCommunication* pOwn );
    virtual ~SocietyRelationWorkThread(){}

    virtual bool IsHaveTask()
    { return _dbMsgQueue.GetOtherQueueSize() > 0; }

    virtual uint32 Update();

    virtual void   OnQueryDBAccountWallowInfoReq   ( BaseSqlMessage* pSqlMessage );
    virtual void   OnQueryDBAccountWallowInfoSave  ( BaseSqlMessage* pSqlMessage );    
    virtual uint32 OnDBMsgJiFengShopItemsListReq   ( BaseSqlMessage* pSqlMessage );
    virtual uint32 OnDBMsgJiFengShopItemsGainReq   ( BaseSqlMessage* pSqlMessage );
}; 

#endif // __DATABASE_SOCIETYRELATIONWORKTHREAD_H__
