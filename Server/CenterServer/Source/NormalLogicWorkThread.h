/********************************************************************
    Filename:    NormalLogicWorkThread.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __DATABASE_NORMALLOGICWORKTHREAD_H__
#define __DATABASE_NORMALLOGICWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"
#include "SqlMessages.h"

// �����߼���Sql�洢�߳�
class NormalLogicWorkThread : public MySqlWorkThread
{
public:
    NormalLogicWorkThread( MySqlCommunication* pOwn );
    virtual ~NormalLogicWorkThread(){}

    virtual uint32 Update();

    virtual bool   IsHaveTask() { return _dbMsgQueue.GetQueueSize() > 0; }

    virtual void   OnQuerySaveItemDropControl( BaseSqlMessage* pSqlMessage );
    virtual void   OnQueryItemDropControlReq ( BaseSqlMessage* pSqlMessage );                 
    virtual void   OnMsgPFAddItemReq         ( BaseSqlMessage* pSqlMessage ); // �����͵���
    virtual void   OnGS2CSMailListReq        ( BaseSqlMessage* pSqlMessage ); // �ʼ��б�
    virtual void   OnGS2CSQueryMailCanSendReq( BaseSqlMessage* pSqlMessage ); // ���ʼ���ѯ
    virtual void   OnGS2CSSendMailReq        ( BaseSqlMessage* pSqlMessage ); // �����ʼ�
    virtual void   OnGS2CSOpMailReq          ( BaseSqlMessage* pSqlMessage ); // �ʼ�����

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
