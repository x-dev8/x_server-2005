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

// ToDo ������ʱ����
// ToDo 1500������ �� 1Сʱ������
// ToDo ����ʱ�����Ϣ����

typedef mysqlpp::SQLQueryParms    SqlParams;
typedef mysqlpp::SQLTypeAdapter   SqlType;
typedef mysqlpp::StoreQueryResult SqlResult;
typedef mysqlpp::Row              SqlRow;

class MySqlWorkThread : public CWorkThread
{
public:
    enum EConstDefine
    {
        ECD_PingTime            = 3 * 1000, // 3 ����
        ECD_ConnectIntervalTime = 1000,     // 1 ��
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
    virtual uint32 PushMessage( BaseSqlMessage* pMsg ); // ������Ϣ

protected:
    // ��������sql
    void _TryConnectToSqlDb();

    // ���SqlService�������
    bool _CheckState( bool bPing = true );

    // ִ����ͨ������ݼ�Sql���--1.Select
    bool DBStore( SqlResult& xOutReuslt, const char* formatSql, ... );

    // ��DBStore���� ʹ��ģ�����
    bool DBStoreT( SqlResult& xOutReuslt, const char* templateSql, SqlParams& xParams );

    // ִ����ͨSql���--1.Update 2.Delete
    bool DBExecute( const char* formatSql, ... );

    // ��DBExecute���� ʹ��ģ�����
    bool DBExecuteT( const char* templateSql, SqlParams& xParams );

    // ִ�д洢������Ҫ���õĽӿ�
    bool DBCallSp( SqlResult& xOutReuslt, const char* formatSql, ... );

    // ��DBCallSp���� ʹ��ģ�����
    bool DBCallSpT( SqlResult& xOutReuslt, const char* templateSql, SqlParams& xParams );
    
protected:
    MySqlCommunication*  _pOwn;
    mysqlpp::Connection* _pMysqlConnect;  // ��mysql ������
    uint8                _workState;      // ���ӵ�״̬
    uint32               _lastUpdateTime; // ���µĸ���ʱ��
    std::string          _dbName;         // ���ݿ���
    std::string          _host;           // ��ַ
    std::string          _user;           // �û���
    std::string          _password;       // ����
    uint16               _port;           // �˿�
    WorkTaskQueue        _dbMsgQueue;     // ��Ҫ���������DbMessage
    uint32               _threadId;       // �̱߳��
    GameTimerEx          _connectTime;    // ����ʱ��������
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
