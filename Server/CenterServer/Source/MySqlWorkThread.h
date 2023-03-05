/********************************************************************
    Filename:    MySqlWorkThread.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __CENTERSERVER_MYSQLWORKTHREAD_H__
#define __CENTERSERVER_MYSQLWORKTHREAD_H__

#pragma once

#include "MeRTLibsServer.h"
#include "WorkThread.h"
#include "mysql++.h"
#include "MsgBase.h"
#include "WorkTaskQueue.h"
#include "MysqlConnectionPoolEx.h"
#include "GameTimer.h"

class MySqlCommunication;

// ToDo 重连的时间间隔
// ToDo 1500的重连 和 1小时的重连
// ToDo 重连时候的消息跳出

typedef mysqlpp::SQLQueryParms    SqlParams;
typedef mysqlpp::SQLTypeAdapter   SqlType;
typedef mysqlpp::StoreQueryResult SqlResult;
typedef mysqlpp::Row              SqlRow;

class MySqlWorkThread : public CWorkThread
{
public:
    enum EConstDefine
    {
        ECD_PingTime            = 3 * 1000, // 3 分钟
        ECD_ConnectIntervalTime = 1000,     // 1 秒
    };

    enum EWorkStatus
    {
        SS_TryConnect,
        SS_Connected,
        SS_ReConnected,
    };

public:
    static bool InitMysqlLib();

    MySqlWorkThread( MySqlCommunication* pOwn );
    virtual ~MySqlWorkThread();
    virtual bool CreateThread( t_fnThreadFuncOneStep fn,void *lpData = 0,int iPriority = THREAD_PRIORITY_NORMAL );

    virtual uint32 Init( const std::string& dbName, const std::string& host, uint16 port, const std::string& user, const std::string& password, uint32 threadId );    
    virtual bool   IsHaveTask(){ return false;}
    virtual uint32 Update();    
    virtual uint32 PushMessage( BaseSqlMessage* pMsg ); // 放入消息

protected:
    // 尝试连接sql
    void _TryConnectToSqlDb();

    // 检查SqlService运行情况
    bool _CheckState( bool bPing = true );

    // 执行普通获得数据集Sql语句--1.Select
    bool DBStore( SqlResult& xOutReuslt, const char* formatSql, ... );

    // 与DBStore类似 使用模板参数
    bool DBStoreT( SqlResult& xOutReuslt, const char* templateSql, SqlParams& xParams );

    // 执行普通Sql语句--1.Update 2.Delete
    bool DBExecute( const char* formatSql, ... );

    // 与DBExecute类似 使用模板参数
    bool DBExecuteT( const char* templateSql, SqlParams& xParams );

    // 执行存储过程需要调用的接口
    bool DBCallSp( SqlResult& xOutReuslt, const char* formatSql, ... );

    // 与DBCallSp类似 使用模板参数
    bool DBCallSpT( SqlResult& xOutReuslt, const char* templateSql, SqlParams& xParams );
    
protected:
    MySqlCommunication*  _pOwn;
    mysqlpp::Connection* _pMysqlConnect;  // 和mysql 的连接
    uint8                _workState;      // 连接的状态
    uint32               _lastUpdateTime; // 最新的更新时间
    std::string          _dbName;         // 数据库名
    std::string          _host;           // 地址
    std::string          _user;           // 用户名
    std::string          _password;       // 密码
    uint16               _port;           // 端口
    WorkTaskQueue        _dbMsgQueue;     // 需要处理的请求DbMessage
    uint32               _threadId;       // 线程编号
    GameTimerEx          _connectTime;    // 连接时间间隔控制
};

inline bool MySqlWorkThread::InitMysqlLib()
{
    mysqlpp::Connection* pMysqlConnect = new mysqlpp::Connection();
    if ( pMysqlConnect == NULL )
    { return false;}

    delete pMysqlConnect;
    pMysqlConnect = NULL;
    return true;
}
#endif // __CENTERSERVER_MYSQLWORKTHREAD_H__
