#pragma once

#include "MySqlWorkThread.h"

class LogServerMySql
{
public:
	enum EConstDefine
	{
		ECD_OnlineInfoWorkThread         = 11, //在线信息
		ECD_ItemInfoWorkThread		     = 22, //物品相关的log
		ECD_PlayerInfoWorkThread		 = 33, //角色相关的log
		ECD_SystemInfoWorkThread		 = 44, //各类系统相关的log
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
	//void CheckExitCondition(); // 检查程序是否可以退出的条件
private:
	typedef std::vector<BaseLogMessage*> LogMesageContainer;
	typedef LogMesageContainer::iterator  ItrLogMesageContainer;

	MySqlWorkThread*  _pOnlineInfoWorkThread; // 在线信息     处理工作线程
	MySqlWorkThread*  _pItemInfoWorkThread;	  // 物品相关的log 处理工作线程
	MySqlWorkThread*  _pPlayerInfoWorkThread;   // 角色相关的log     处理工作线程
	MySqlWorkThread*  _pSystemInfoWorkThread;   // 各类系统相关的log     处理工作线程

	LogMesageContainer _LogMessages;      // 需要处理的请求logMessage
	CSemiAutoIntLock   _LogMessagesLock;   // log消息锁


	MySqlWorkThread*  _pTestWorkThread;   // 测试线程,用来拿数据库效率
};

#define theLogServerMySql LogServerMySql::Instance()