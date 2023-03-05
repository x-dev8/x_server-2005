/********************************************************************
    Filename:     DatabaseConnector.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

//#include "MeConnector.h"
//#include "MeNetwork.h"
#include "network.h"
#include "Mutex.h"
#include "GameTimer.h"

using namespace network;

class  BaseCharacter;
struct DBMsg;

//安全性：
//1。与CharDB得连接中断如何处理
//与CharDB断开连接后,某些请求可以直接返回失败，如：
//CreateChar
//DeleteChar                
//保存角色请求必须予以暂存（文件CSaveCharBackFile），等待重连成功后，重新请求
//2。如何保证SaveChar消息被已经被CharDB处理
//(CMsgBackupList)
//某些需要确保执行得消息，如：SaveChar数据库执行完成后必须返回消息，确认成功后，才能去掉
//按照当前处理流程:SaveChar消息的处理应该是FIFO,假设出现返回确认的消息不是等待得消息，断开数据库重连
//将备份消息导入到文件中(CSaveCharBackFile)

//3。安全退出机制
//退出前，数据库连接确保保存角色的消息都被处理
//连接断开的话，备份到文件

//class IMeConnector;
class DataBaseConnectors : public CSemiAutoIntLock
{
public:
    /*IMeConnector*//*Socketer* _AccountServerConnector;*/  // AccountServer连接    
    /*IMeConnector*/Socketer* _DatabaseServerConnector; // DatabaseServer连接
    /*IMeConnector*//*Socketer* _LogServerConnector; */     // LogServer连接

    /*char m_szAccountServerIP[64];
    int  _iAccountServerPort;*/

    //char m_szLogIP[64];
    //int  _iLogServerPort;

    char m_szCharDBIP[64];
    int  _iDatabaserServerPort;

    enum enumConStatus
    {    
        CS_TryConnect, // 尝试连接
        CS_ReConnect,  // 重新连接
        CS_Connectted, // 连接成功
    };

    enum EConstDefine
    {   
        ECD_iPingDatabaseServerTime = 20000, // ping DatabaseServer的时间 m
        ECD_ConnectIntervalTime     = 1000,     // 1 秒
    };

    //int _iAccountServerConnectorState;
    int _iDatabaseServerConnectorState;
    //int _iLogServerConnectorState;

    //unsigned int m_nLastPingAccount;
    unsigned int m_nLastPingChar;
    //unsigned int m_nLastPingLog;
    //unsigned int _nAccountServerPing;
    unsigned int _nDatabaseServerPing;
    //unsigned int m_nLogPing;
    bool         m_bCharIsOK;
    GameTimerEx  _connectTime;    // 连接时间间隔控制

public:    
    DataBaseConnectors();
    ~DataBaseConnectors();

    bool CreateDatabaseServerConnectorSocket();
    void TryConnectToDatabaseServer();

    //void TryConnectToAccountServer();
    //void TryConnectToLogServer();

    //void SendMsgToAccountServer( Msg *pMsg );
    void SendMsgToDatabaseServer( Msg *pMsg );
    //void SendMsgToLogServer( Msg *pMsg );

    void DispatchToPlayer( Msg *pMsg );

    //备份 存盘信息到文件
    //void BackupSaveCharToFile( void );

    bool Init( /*char* szAccountServerIP, int iAccountServerPort, */char *szCharDBIP, int iCharDBPortchar/*, char *szLogIP, int iLogPort */);
    void Shutdown();
    //发送消息
    void SendMsg( Msg *pMsg,unsigned short ustLifeCode );
    //将收到得消息转发给角色
    void DispatchMsgToPlayers( void );

    void OnDBMsgHandlerMiss( DBMsg *pDBMsg );
    void RunOneStep();
    //是否数据库连接完好
    bool IsDBConnectted();
    bool IsCharDBOK() { return m_bCharIsOK; }

    bool IsAllMsgSendOver();
};

extern DataBaseConnectors& GettheDBCon();
