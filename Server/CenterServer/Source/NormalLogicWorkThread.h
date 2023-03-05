/********************************************************************
    Filename:    NormalLogicWorkThread.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __DATABASE_NORMALLOGICWORKTHREAD_H__
#define __DATABASE_NORMALLOGICWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"

// 正常逻辑的Sql存储线程
class NormalLogicWorkThread : public MySqlWorkThread
{
public:
    NormalLogicWorkThread( MySqlCommunication* pOwn );
    virtual ~NormalLogicWorkThread(){}

    virtual uint32 Update();

    virtual bool   IsHaveTask() { return _dbMsgQueue.GetQueueSize() > 0; }

    virtual void   OnQuerySaveItemDropControl( BaseSqlMessage* pSqlMessage );
    virtual void   OnQueryItemDropControlReq ( BaseSqlMessage* pSqlMessage );                 
    virtual void   OnMsgPFAddItemReq         ( BaseSqlMessage* pSqlMessage ); // 积分送道具
    virtual void   OnGS2CSMailListReq        ( BaseSqlMessage* pSqlMessage ); // 邮件列表
    virtual void   OnGS2CSQueryMailCanSendReq( BaseSqlMessage* pSqlMessage ); // 发邮件查询
    virtual void   OnGS2CSSendMailReq        ( BaseSqlMessage* pSqlMessage ); // 发新邮件
    virtual void   OnGS2CSOpMailReq          ( BaseSqlMessage* pSqlMessage ); // 邮件操作

#include "CountryDatabaseHandle.h"
#include "RelationDatabaseHandle.h"
#include "GuildDatabaseHandle.h"
#include "ConsignmentDatabaseHandle.h"
#include "SystemVarDatabaseHandle.h"
#include "NormalLogicWorkThreadBillingModule.h"
#include "FamilyDatabaseHandle.h"
#include "LevelLimitDBHandle.h"
#include "GlobalDBDataBaseHandle.h"
//xuda #include "EmperorDatabaseHandle.h"
//xuda #include "WantedDatabaseHandle.h"
#include "QuestEntrustDataBaseHandle.h"
#include "GameBattleDataBaseHandle.h"
public:
    bool WriteItemData ( SCharItem* pItem,   uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WriteMountData( SMountItem* pMount, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WritePetData  ( SPetItem* pMount  , uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
}; 

#endif // __DATABASE_NORMALLOGICWORKTHREAD_H__
