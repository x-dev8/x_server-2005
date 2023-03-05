#ifndef __LogEventService_H__
#define __LogEventService_H__

#pragma once

#include "network.h"
#include "LogServerMessageDefine.h"

using namespace network;
class LogEventService
{
public:
	enum
	{
		eState_TryConnect = 0,
		eState_Connected,
		eState_ReConnect
	};
public:
	LogEventService(void);
	~LogEventService(void);

	static LogEventService& Instance()
	{
		static LogEventService les;
		return les;
	}
	bool Init(char* ipAddr,unsigned short port,short serverid,bool bService = true);
	bool TryConnect();

	void CloseLogServer();
	bool SendMsgToLogServer(Msg* pMsg);
	void RunOneStep();
	void CheckSend();
	void CheckRec();
	void ProcessLogServer();

	//////////////////////////////////////////////////
	//在线信息 //VVV
	bool LogOnlineInfo(unsigned short login,unsigned short normalquit,unsigned short kickquit,unsigned short total,const char* frondose);
	//角色上下线信息 //VVV
	bool LogPlayerInOut(unsigned long accid,unsigned long chid,unsigned short lv,unsigned short country,unsigned long onlinetime,const char* ipaddr,const char* macAddr,char logtype,const char* chName);
	//获得物品  //VVV
	bool LogItemGain(unsigned long accid,unsigned long chid,unsigned short item_id,unsigned short count,__int64 item_guid,char logtype,const char* chName,const char* ItemName);
	//交易物品 //VVV
	bool LogItemTrade(unsigned long buyer_accid,unsigned long buyer_chid,unsigned long seller_accid,unsigned long seller_chid,unsigned short item_id,unsigned short item_count,
						__int64 item_guid,unsigned long item_cost,char logtype,const char* buyerName ,const char* SellerName ,const char* ItemName);
	//摧毁物品 //VVV
	bool LogItemConsume(unsigned long accid,unsigned long chid,unsigned short item_id,unsigned long item_count,__int64 item_guid,unsigned short LaveCount,char logtype,const char* CharName, const char* ItemName);
	//升级物品 //VVV
	bool LogItemUpgrade(unsigned long accid,unsigned long chid,unsigned short item_id,unsigned long item_count,__int64 item_guid,char logtype,char _result,
						unsigned short previous[],unsigned short current[],const char* CharName , const char* ItemName);
	//任务日志 //VVV 只在任务完成时 添加
	bool LogQuest(unsigned long accid,unsigned long chid,unsigned short questid,const char* CharName);
	//货币流通日志 //VVV
	bool LogCurrency(unsigned long accid,unsigned long chid,int count,char money_type,char logtype,const char* CharName ,int16 sourcetype = ePlayerMoneySourceType_Unkown);
	//经验日志 //VVV
	bool LogExp(unsigned long accid,unsigned long chid,int _exp,int monsterid,char logtype,const char* CharName);
	//等级日志 //VVV
	bool LogLevelChange(unsigned long accid,unsigned long chid,unsigned short previouslv,unsigned short newlv,const char* CharName);
	//邮件日志 //VVV
	bool LogMail(unsigned long sender_accid,unsigned long sender_chid,unsigned long recv_chid,char* _title,char* _detail,
		            unsigned short item_id,unsigned short item_count,uint32 _money,__int64 ItemGUID,const char* SenderName, const char* RevcName, const char* ItemName);
	//工会日志 //VVV
	bool LogGuild(unsigned long accid,unsigned long chid,unsigned long guildid,char logtype,const char* CharName);
	//工会具体属性日志
	bool LogGuildDetail(unsigned long accid,unsigned long chid,unsigned long guildid,int moneychange,int expchange,int missionchange,const char* CharName);
	//gm命令日志
	bool LogGMCommand(unsigned long accid,unsigned long chid,const char* chname,const char* content,const char* ipaddr,const char* CharName);
	//聊天信息
	bool LogChatInfo(unsigned long accid,unsigned long chid,unsigned long targetid,const char* content,short chattype,const char* CharName, const char* TargetName);
	//////////////////////////////////////////////////
	void TestLog(int num = 1);
private:
	Socketer*		m_LogServerSocket;
	bool			_OpenService;
	char			_chState;
	std::string		strIpAddr;
	unsigned short	usPort;
	short			server_id;
};

#define theLogEventService LogEventService::Instance()

#endif