#pragma once

#include "MySqlWorkThread.h"

class LogServerMySql
{
public:
	enum EConstDefine
	{
		ECD_OnlineInfoWorkThread         = 11, //������Ϣ
		ECD_ItemInfoWorkThread		     = 22, //��Ʒ��ص�log
		ECD_PlayerInfoWorkThread		 = 33, //��ɫ��ص�log
		ECD_SystemInfoWorkThread		 = 44, //����ϵͳ��ص�log
	};
public:
	LogServerMySql(void);
	~LogServerMySql(void);

	static LogServerMySql& Instance()
	{
		static LogServerMySql cws;
		return cws;
	}

	virtual uint32 Init(	const std::string& OnlineName, const std::string& Onlinehost, uint16 Onlineport, 
							const std::string& Onlineuser,   const std::string& Onlinepassword,
							const std::string& ItemName, const std::string& Itemhost, uint16 Itemport, 
							const std::string& Itemuser,   const std::string& Itempassword,
							const std::string& PlayerName, const std::string& Playerhost, uint16 Playerport, 
							const std::string& Playeruser,   const std::string& Playerpassword,
							const std::string& SystemName, const std::string& Systemhost, uint16 Systemport, 
							const std::string& Systemuser,   const std::string& Systempassword);

	virtual uint32 PushLogMessage( Msg* pMsg, uint32 serverid );
	virtual void   Update();
	//virtual void   ShutDown();
	//void CheckExitCondition(); // �������Ƿ�����˳�������
private:
	typedef std::vector<BaseLogMessage*> LogMesageContainer;
	typedef LogMesageContainer::iterator  ItrLogMesageContainer;

	MySqlWorkThread*  _pOnlineInfoWorkThread; // ������Ϣ     �������߳�
	MySqlWorkThread*  _pItemInfoWorkThread;	  // ��Ʒ��ص�log �������߳�
	MySqlWorkThread*  _pPlayerInfoWorkThread;   // ��ɫ��ص�log     �������߳�
	MySqlWorkThread*  _pSystemInfoWorkThread;   // ����ϵͳ��ص�log     �������߳�

	LogMesageContainer _LogMessages;      // ��Ҫ���������logMessage
	CSemiAutoIntLock   _LogMessagesLock;   // log��Ϣ��


	MySqlWorkThread*  _pTestWorkThread;   // �����߳�,���������ݿ�Ч��
};

#define theLogServerMySql LogServerMySql::Instance()