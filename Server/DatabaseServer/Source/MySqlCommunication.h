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

    virtual uint32 PushReqMessage( Msg* pMsg, uint32 nClientId ); // ѹ��������Ϣ
    virtual uint32 PushAckMessage( Msg* pMsg, uint32 nClientId ); // ѹ�������Ϣ

    void CheckExitCondition(); // �������Ƿ�����˳�������

	//tool
	bool  GetWorkThreadWorkState(EConstDefine type);

protected:
	void   UpdateForRequest();				// ������������
	void   UpdateForAcknowledge();			// ����Ӧ������

public:
    bool bMemoryInfo;

private:
    typedef std::vector<BaseSqlMessage*> DbMesageContainer;
    typedef DbMesageContainer::iterator  ItrDbMesageContainer;

    MySqlWorkThread*  _pBillingWorkThread; // ��ֵ����     �������߳�
    MySqlWorkThread*  _pNormalLogicThread; // ��ͨ��Ϸ�߼� �������߳�
    MySqlWorkThread*  _pSocietyLogicThread;// ����ϵ     �������߳�
                      
    DbMesageContainer _dbReqMessages;      // ��Ҫ���������DbMessage
    CSemiAutoIntLock  _dbAckMessageLock;   // dbAck��Ϣ��
                      
    DbMesageContainer _dbAckMessages;      // ��������DbMessage���
    CSemiAutoIntLock  _dbReqMessageLock;   // dbReq��Ϣ��
};

MySqlCommunication& GetMySqlCommunication();

#endif // __MYSQLCOMMUNICATION_H__
