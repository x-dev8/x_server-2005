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

//��ȫ�ԣ�
//1����CharDB�������ж���δ���
//��CharDB�Ͽ����Ӻ�,ĳЩ�������ֱ�ӷ���ʧ�ܣ��磺
//CreateChar
//DeleteChar                
//�����ɫ������������ݴ棨�ļ�CSaveCharBackFile�����ȴ������ɹ�����������
//2����α�֤SaveChar��Ϣ���Ѿ���CharDB����
//(CMsgBackupList)
//ĳЩ��Ҫȷ��ִ�е���Ϣ���磺SaveChar���ݿ�ִ����ɺ���뷵����Ϣ��ȷ�ϳɹ��󣬲���ȥ��
//���յ�ǰ��������:SaveChar��Ϣ�Ĵ���Ӧ����FIFO,������ַ���ȷ�ϵ���Ϣ���ǵȴ�����Ϣ���Ͽ����ݿ�����
//��������Ϣ���뵽�ļ���(CSaveCharBackFile)

//3����ȫ�˳�����
//�˳�ǰ�����ݿ�����ȷ�������ɫ����Ϣ��������
//���ӶϿ��Ļ������ݵ��ļ�

//class IMeConnector;
class DataBaseConnectors : public CSemiAutoIntLock
{
public:
    /*IMeConnector*//*Socketer* _AccountServerConnector;*/  // AccountServer����    
    /*IMeConnector*/Socketer* _DatabaseServerConnector; // DatabaseServer����
    /*IMeConnector*//*Socketer* _LogServerConnector; */     // LogServer����

    /*char m_szAccountServerIP[64];
    int  _iAccountServerPort;*/

    //char m_szLogIP[64];
    //int  _iLogServerPort;

    char m_szCharDBIP[64];
    int  _iDatabaserServerPort;

    enum enumConStatus
    {    
        CS_TryConnect, // ��������
        CS_ReConnect,  // ��������
        CS_Connectted, // ���ӳɹ�
    };

    enum EConstDefine
    {   
        ECD_iPingDatabaseServerTime = 20000, // ping DatabaseServer��ʱ�� m
        ECD_ConnectIntervalTime     = 1000,     // 1 ��
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
    GameTimerEx  _connectTime;    // ����ʱ��������

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

    //���� ������Ϣ���ļ�
    //void BackupSaveCharToFile( void );

    bool Init( /*char* szAccountServerIP, int iAccountServerPort, */char *szCharDBIP, int iCharDBPortchar/*, char *szLogIP, int iLogPort */);
    void Shutdown();
    //������Ϣ
    void SendMsg( Msg *pMsg,unsigned short ustLifeCode );
    //���յ�����Ϣת������ɫ
    void DispatchMsgToPlayers( void );

    void OnDBMsgHandlerMiss( DBMsg *pDBMsg );
    void RunOneStep();
    //�Ƿ����ݿ��������
    bool IsDBConnectted();
    bool IsCharDBOK() { return m_bCharIsOK; }

    bool IsAllMsgSendOver();
};

extern DataBaseConnectors& GettheDBCon();
