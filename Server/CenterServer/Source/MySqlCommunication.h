/********************************************************************
    Filename:    MySqlCommunication.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_MYSQLCOMMUNICATION_H__
#define __CENTERSERVER_MYSQLCOMMUNICATION_H__

#pragma once

#include "MeRTLibsServer.h"
#include "MsgBase.h"
#include "Mutex.h"
#include "Memory_Pool.h"
#include "MySqlWorkThread.h"

#define theMysqlCommunication GetMySqlCommunication()

class MySqlCommunication
{
public:
    enum EConstDefine
    { 
        ECD_NormalLogicWorkThread      = 22, 
        ECD_BillingLogicWorkThread     = 33,
        ECD_PlatformLogicWorkThread    = 44,
        ECD_PlatformRPCLogicWorkThread = 55,
    };

public:
    MySqlCommunication();
    ~MySqlCommunication();
	//配置文件里面的这两个都没用了<BillingDB/><PlatformRPC/>|billingDbName+strPlatformRPCDbName
    virtual uint32 Init( const std::string& roleDbName   , const std::string& host   , uint16 port   , const std::string& user   , const std::string& password  , // GameDB
                         const std::string& platformDbName , const std::string& hostPL , uint16 portPL , const std::string& userPL , const std::string& passwordPL // PlatformDB 
                         );

    virtual void   Update();
    virtual void   ShutDown();    

    virtual uint32 Push3PartyReqMessage( Msg* pMsg, uint32 nClientId ); // 压入3方请求消息
    virtual uint32 Push3PartyAckMessage( Msg* pMsg, uint32 nClientId ); // 压入3方回馈消息

	virtual uint32 PushReqMessage( Msg* pMsg, uint32 nClientId ); // 压入请求消息
	virtual uint32 PushAckMessage( Msg* pMsg, uint32 nClientId ); // 压入回馈消息

    void CheckExitCondition(); // 检查程序是否可以退出的条件
	void ParseMysqlAck( BaseSqlMessage *pAckMsg );

public:
    bool bMemoryInfo;

protected:
	void   UpdateForRequest();				// 处理请求容器
	void   UpdateForAcknowledge();			// 处理应答容器

private:
    typedef std::vector<BaseSqlMessage*> DbMesageContainer;
    typedef DbMesageContainer::iterator  ItrDbMesageContainer;

    MySqlWorkThread*  _pNormalLogicThread  ; // 普通游戏逻辑 处理工作线程
    //MySqlWorkThread*  _pBillingLogicThread ; // 充值逻辑     处理工作线程
    MySqlWorkThread*  _pPlatformLogicThread; // 平台逻辑     处理工作线程 目前只处理防沉迷了
    //MySqlWorkThread*  _pPlatformRPCLogicThread; // 平台逻辑     处理工作线程

    DbMesageContainer _dbReqMessages;      // 需要处理的请求DbMessage
    CSemiAutoIntLock  _dbAckMessageLock;   // dbAck消息锁
                      
    DbMesageContainer _dbAckMessages;      // 处理过后的DbMessage结果
    CSemiAutoIntLock  _dbReqMessageLock;   // dbReq消息锁
};

MySqlCommunication& GetMySqlCommunication();

#endif // __CENTERSERVER_MYSQLCOMMUNICATION_H__
