/********************************************************************
    Filename:    MySqlCommunication.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MYSQLCOMMUNICATION_H__
#define __MYSQLCOMMUNICATION_H__

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
        ECD_BillingWorkThread         = 11,
        ECD_NormalLogicWorkThread     = 22,
        ECD_SocietyRelationWorkThread = 33,
    };

public:
    MySqlCommunication();
    ~MySqlCommunication();

    virtual uint32 Init( const std::string& dbName, const std::string& host, uint16 port, 
        const std::string& user,   const std::string& password,
        const std::string& dbNameBilling, const std::string& hostBilling, uint16 portBilling, 
        const std::string& userBilling,   const std::string& passwordBilling);

    virtual void   Update();
    virtual void   ShutDown();    

    virtual uint32 PushReqMessage( Msg* pMsg, uint32 nClientId ); // 压入请求消息
    virtual uint32 PushAckMessage( Msg* pMsg, uint32 nClientId ); // 压入回馈消息

    void CheckExitCondition(); // 检查程序是否可以退出的条件

	//tool
	bool  GetWorkThreadWorkState(EConstDefine type);

protected:
	void   UpdateForRequest();				// 处理请求容器
	void   UpdateForAcknowledge();			// 处理应答容器

public:
    bool bMemoryInfo;

private:
    typedef std::vector<BaseSqlMessage*> DbMesageContainer;
    typedef DbMesageContainer::iterator  ItrDbMesageContainer;

    MySqlWorkThread*  _pBillingWorkThread; // 冲值数据     处理工作线程
    MySqlWorkThread*  _pNormalLogicThread; // 普通游戏逻辑 处理工作线程
    MySqlWorkThread*  _pSocietyLogicThread;// 社会关系     处理工作线程
                      
    DbMesageContainer _dbReqMessages;      // 需要处理的请求DbMessage
    CSemiAutoIntLock  _dbAckMessageLock;   // dbAck消息锁
                      
    DbMesageContainer _dbAckMessages;      // 处理过后的DbMessage结果
    CSemiAutoIntLock  _dbReqMessageLock;   // dbReq消息锁
};

MySqlCommunication& GetMySqlCommunication();

#endif // __MYSQLCOMMUNICATION_H__
