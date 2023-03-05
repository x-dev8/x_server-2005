/********************************************************************
    Filename:     DatabaseServerApp.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASESERVER_DATABASESERVER_H__
#define __DATABASESERVER_DATABASESERVER_H__

#pragma once

//#include "MeNetwork.h"
//#include "MeConnector.h"
//#include "MapContainer.h"
#include "MapStrToID.h"
//#include "NetworkApp.h"
#include "DatabaseInterface.h"
#include "MySqlCommunication.h"
#include "network.h"
#include "StaticArray.h"

using namespace network;
class DatabaseClient;

#define APPLICATION_NAME "DatabaseServer"

#define theDatabaseServerApp GetDatabaseServerApp()

class DatabaseServerApp/* : public INetworkApp*/
{
public:
    enum ESqlType
    {
        ST_MSSql,
        ST_MySql,
    };
    DatabaseServerApp();
    ~DatabaseServerApp();

    uint32 Init( const char* szConfigFilePath );
    void   ShutDown();
    void   Update();

    WORD   GetListenPort() { return m_wListenPort;      }
    //size_t GetNodeSize()   { return m_NodeMgr.GetSize();}
    void   CheckForServerExit();
    bool   InitDBServerLog();   // ��ʼ��DB��Log4cxx
	void RunOneStep();
	bool AcceptNewClient();
	void RecvAllClientMsg();
	void ProcessClientMsg();
	void SendAllClientMsg();

	void SendMsgToAllClient(Msg* pMsg);
protected:
    bool LoadConfig( const char* szConfigFilePath, int& nResultError );
    bool InitNetSetting();

public:
    std::string m_strDatabaseName;
    
    bool m_bUseCancelDel;			 // �Ƿ��ȡ����ɾ��״̬�Ľ�ɫ
    
    std::string m_strRoleDBName;     // Ҫ��½�����ݿ������
    std::string m_strRoleDBSrvIp;    // ���ݿ��������ip
    std::string m_strRoleDBSrvUID;   // ���ݿ���������ʺ�    
    std::string m_strRoleDBSrvPWD;   // ���ݿ������������    
    std::string m_strRoleDBGateName; // DBGate�Լ�������

    std::string roleDbName; // ��ɫ���ݿ������
    uint16      roleDbPort; // ��ɫ���ݿ�Ķ˿�
    std::string roleHost;   // ���ݿ��������host
    std::string roleUID;    // ���ݿ���������ʺ�
    std::string rolePwd;    // ���ݿ������������

    std::string billingDbName; // billing���ݿ������
    uint16      billingDbPort; // billing���ݿ�Ķ˿�
    std::string billingHost;   // billing���ݿ��������host
    std::string billingUID;    // billing���ݿ���������ʺ�
    std::string billingPwd;    // billing���ݿ������������

    WORD m_wListenPort; // �����˿�

    DWORD m_dwEnterWorldConfine;
    DWORD m_RoleSaveMax;
    DWORD m_OtherSaveMax;

    std::string strLogConfigFilePath;

    bool m_bSleepTime; // ֻ���� 0 �� 1

    uint8  useSqlType;
    uint32 revShutdownCommandTime;  // �յ���ʱ��
    uint32 revShutdownDelayTime;    // �յ��ӳ�ʱ����

	Listener* m_ClientListen;
	CStaticArray<DatabaseClient*> _DatabaseClient;

	bool m_bAccountBilling; //�Ƿ�������ʺ�Ϊ��λ�ļƷ�,0/1

	std::string   strBillingServerIp;          //�Ʒѷ�����IP
	uint16        ustBillingServerPort;        //�Ʒѷ������˿�
	int           nBindBillingServerPort;      //��ͨ��ָ���˿�����,-1��ʾ������,����ʹ��
	std::string   strKey;                      //��Ʒ�ֱ�ӽ�����key
	bool          bOpenBillingService;          //�Ƿ�����billing server�ķ���

	//����
	std::string   strBillingScoreServerIp;          //�Ʒѷ�����IP
	uint16        ustBillingScoreServerPort;        //�Ʒѷ������˿�
	int           nBindBillingScoreServerPort;      //��ͨ��ָ���˿�����,-1��ʾ������,����ʹ��
	std::string   strKeyScore;                      //��Ʒ�ֱ�ӽ�����key
	bool          bOpenBillingScoreService;          //�Ƿ�����billing server�ķ���
};

DatabaseServerApp* GetDatabaseServerApp();

#endif // __DATABASESERVER_DATABASESERVER_H__
