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
	//�����ļ��������������û����<BillingDB/><PlatformRPC/>|billingDbName+strPlatformRPCDbName
    virtual uint32 Init( const std::string& roleDbName   , const std::string& host   , uint16 port   , const std::string& user   , const std::string& password  , // GameDB
                         const std::string& platformDbName , const std::string& hostPL , uint16 portPL , const std::string& userPL , const std::string& passwordPL // PlatformDB 
                         );

    virtual void   Update();
    virtual void   ShutDown();    

    virtual uint32 Push3PartyReqMessage( Msg* pMsg, uint32 nClientId ); // ѹ��3��������Ϣ
    virtual uint32 Push3PartyAckMessage( Msg* pMsg, uint32 nClientId ); // ѹ��3��������Ϣ

	virtual uint32 PushReqMessage( Msg* pMsg, uint32 nClientId ); // ѹ��������Ϣ
	virtual uint32 PushAckMessage( Msg* pMsg, uint32 nClientId ); // ѹ�������Ϣ

    void CheckExitCondition(); // �������Ƿ�����˳�������
	void ParseMysqlAck( BaseSqlMessage *pAckMsg );

public:
    bool bMemoryInfo;

protected:
	void   UpdateForRequest();				// ������������
	void   UpdateForAcknowledge();			// ����Ӧ������

private:
    typedef std::vector<BaseSqlMessage*> DbMesageContainer;
    typedef DbMesageContainer::iterator  ItrDbMesageContainer;

    MySqlWorkThread*  _pNormalLogicThread  ; // ��ͨ��Ϸ�߼� �������߳�
    //MySqlWorkThread*  _pBillingLogicThread ; // ��ֵ�߼�     �������߳�
    MySqlWorkThread*  _pPlatformLogicThread; // ƽ̨�߼�     �������߳� Ŀǰֻ�����������
    //MySqlWorkThread*  _pPlatformRPCLogicThread; // ƽ̨�߼�     �������߳�

    DbMesageContainer _dbReqMessages;      // ��Ҫ���������DbMessage
    CSemiAutoIntLock  _dbAckMessageLock;   // dbAck��Ϣ��
                      
    DbMesageContainer _dbAckMessages;      // ��������DbMessage���
    CSemiAutoIntLock  _dbReqMessageLock;   // dbReq��Ϣ��
};

MySqlCommunication& GetMySqlCommunication();

#endif // __CENTERSERVER_MYSQLCOMMUNICATION_H__
