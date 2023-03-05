/********************************************************************
    Filename:    MySqlWorkThread.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MYSQLWORKTHREAD_H__
#define __MYSQLWORKTHREAD_H__

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

	bool _CheckState();        // ���SqlService�������
protected:
    void _TryConnectToSqlDb(); // ��������sql

    
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

    MysqlConnectionPoolEx* _mysqlConnectionPool;
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
#endif // __MYSQLWORKTHREAD_H__
