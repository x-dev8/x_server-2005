#include "LogEventService.h"
#include "GameTimer.h"
#include "GlobalDef.h"

LogEventService::LogEventService(void)
{
	strIpAddr.clear();
	m_LogServerSocket = NULL;
	_chState = eState_TryConnect;
	server_id = -1;
}

LogEventService::~LogEventService(void)
{
	if (m_LogServerSocket)
	{
		network::Socketer_release(m_LogServerSocket);
		m_LogServerSocket = NULL;
	}
}

void LogEventService::TestLog(int num)
{
// 	for (int n =0; n < num;n++)
// 	{
// 		unsigned long accid =	10000+n;
// 		unsigned long chid	=	20000+n;
// 
// 		LogPlayerInOut(accid,chid,n+1,n+2,n+3,"192.168.1.1",(n+1)%2);
// 		LogItemGain(accid,chid,n+1,n+2,n+3,(n+1)%6);
// 		LogItemTrade(accid,chid,accid+1,chid+1,n+2,n+3,n+4,n+5,(n+1)%2);
// 		LogItemConsume(accid,chid,n+1,n+2,n+3,(n+1)%8);
// 		unsigned short p[7];
// 		unsigned short c[7];
// 		for (int m = 7;m < 7;m++)
// 		{
// 			p[m] = m+n;
// 			c[m] = m+n;
// 		}
// 		LogItemUpgrade(accid,chid,n+1,n+2,n+3,(n+1)%7,(n+1)%2,p,c);
// 		LogQuest(accid,chid,n+1);
// 		LogCurrency(accid,chid,n+1,(n+1)%4,(n+1)%2);
// 		LogExp(accid,chid,n+1,n+2,(n+1)%3);
// 		LogLevelChange(accid,chid,n+1,n+2);
// 		LogMail(accid,chid,n+1,"123","1234",n+2,n+3,n+4,0);
// 		LogGuild(accid,chid,n+1,(n+2)%5);
// 		LogGuildDetail(accid,chid,n+1,n+2,n+3,n+4);
// 	}
}

bool LogEventService::Init(char* ipAddr,unsigned short port,short serverid,bool bService)
{
	_OpenService = bService;
	if (!bService)
	{
		return true;
	}

	if (!ipAddr)
	{
		return false;
	}
	
	strIpAddr = ipAddr;
	usPort	  = port;
	_chState = eState_TryConnect;
	server_id = serverid;
	return true;
}

bool LogEventService::TryConnect()
{
	if (_chState == eState_Connected)
	{
		return true;
	}
	if (!m_LogServerSocket)
	{
		m_LogServerSocket = network::Socketer_create();
		return false;
	}
	if (m_LogServerSocket->Connect(strIpAddr.c_str(),usPort))
	{
		_chState = eState_Connected;
		S2LSynServerid msg;
		msg.serverid = server_id;
		SendMsgToLogServer(&msg);
	}
	return true;
}

void LogEventService::CloseLogServer()
{
	if (m_LogServerSocket)
	{
		network::Socketer_release(m_LogServerSocket);
		m_LogServerSocket = NULL;
	}
	_chState = eState_TryConnect;
}

bool LogEventService::SendMsgToLogServer(Msg* pMsg)
{
	if (!pMsg)
	{
		return false;
	}
	if (!m_LogServerSocket||m_LogServerSocket->IsClose())
	{
		CloseLogServer();
		return false;
	}
	return m_LogServerSocket->SendMsg(pMsg);
}

void LogEventService::CheckSend()
{
	if (!m_LogServerSocket||m_LogServerSocket->IsClose())
	{
		CloseLogServer();
		return;
	}
	m_LogServerSocket->CheckSend();
}

void LogEventService::CheckRec()
{
	if (!m_LogServerSocket||m_LogServerSocket->IsClose())
	{
		CloseLogServer();
		return;
	}
	m_LogServerSocket->CheckRecv();
}

void LogEventService::ProcessLogServer()
{
	if (!m_LogServerSocket||m_LogServerSocket->IsClose())
	{
		CloseLogServer();
		return;
	}

	GameTimerEx processGameMessageTime;
	processGameMessageTime.StartTimer( HQ_TimeGetTime(), 10 );

	Msg *pMsg = NULL;
	// Ê±¼äÆ¬µ½ÁË¾ÍÍËÁË
	while( !processGameMessageTime.DoneTimer( HQ_TimeGetTime() ) )
	{
		pMsg = m_LogServerSocket->GetMsg();
		if ( pMsg == NULL )
		{ break;  }
		switch(pMsg->GetType())
		{
		default:
			break;
		}
	}
}

void LogEventService::RunOneStep()
{
	if (!_OpenService)
	{
		return;
	}

	if (!TryConnect())
	{
		return;
	}

	CheckRec();
	ProcessLogServer();
	CheckSend();
}

bool LogEventService::LogOnlineInfo(unsigned short login,unsigned short normalquit,unsigned short kickquit,unsigned short total,const char* frondose)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	CS2LOnlineInfo onlineinfo;
	onlineinfo.login = login;
	onlineinfo.normalquit = normalquit;
	onlineinfo.kickquit = kickquit;
	onlineinfo.total = total;
	memcpy(&onlineinfo._time,&systime,sizeof(SYSTEMTIME));
	_snprintf(onlineinfo.frondose, sizeof(onlineinfo.frondose)-1, "%s",frondose);
	return SendMsgToLogServer(&onlineinfo);
}

bool LogEventService::LogPlayerInOut(unsigned long accid,unsigned long chid,unsigned short lv,unsigned short country,unsigned long onlinetime,const char* ipaddr,const char* macAddr,char logtype,const char* chName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );
	
	GS2LPlayerInOutLog inotlog;
	inotlog.country = country;
	inotlog.lv = lv;
	inotlog.logcommon.account_id = accid;
	inotlog.logcommon.character_id = chid;
	memcpy(&inotlog.logcommon._time,&systime,sizeof(SYSTEMTIME));
	_snprintf(inotlog.IpAddr, sizeof(inotlog.IpAddr)-1, "%s",ipaddr);
	memcpy(inotlog.logcommon.chName,chName ,min(strlen(chName)+1, sizeof(inotlog.logcommon.chName)));
	inotlog.onlinetime = onlinetime;
	inotlog.Logtype    = logtype;
	_snprintf(inotlog.scMac, sizeof(inotlog.scMac)-1, "%s",macAddr);
	return SendMsgToLogServer(&inotlog);
}

bool LogEventService::LogItemGain(unsigned long accid,unsigned long chid,unsigned short item_id,unsigned short count,__int64 item_guid,char logtype,const char* chName,const char* ItemName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LItemGain gain;
	gain.logcommon.account_id = accid;
	gain.logcommon.character_id = chid;
	memcpy(&gain.logcommon._time,&systime,sizeof(SYSTEMTIME));
	memcpy(gain.logcommon.chName ,chName ,min(strlen(chName)+1, sizeof(gain.logcommon.chName)));
	gain.logitem.item_id = item_id;
	memcpy(gain.logitem.ItemName, ItemName,min(strlen(ItemName)+1, sizeof(gain.logitem.ItemName)));
	gain.logitem.item_count = count;
	gain.logitem.item_guid = item_guid;
	gain.logtype = logtype;
	return SendMsgToLogServer(&gain);
}

bool LogEventService::LogItemTrade(unsigned long buyer_accid,unsigned long buyer_chid,unsigned long seller_accid,unsigned long seller_chid,
								   unsigned short item_id,unsigned short item_count,__int64 item_guid,unsigned long item_cost,char logtype,
								   const char* buyerName ,const char* SellerName ,const char* ItemName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LItemTrade trade;
	memcpy(&trade._time,&systime,sizeof(SYSTEMTIME));
	trade.buyer_accid = buyer_accid;
	trade.buyer_chaid = buyer_chid;
	memcpy(trade.buyerName,buyerName,min(strlen(buyerName)+1, sizeof(trade.buyerName)));
	trade.seller_accid = seller_accid;
	trade.seller_chaid = seller_chid;
	memcpy(trade.sellerName,SellerName,min(strlen(SellerName)+1, sizeof(trade.sellerName)));
	trade.logitem.item_count = item_count;
	trade.logitem.item_id = item_id;
	trade.logitem.item_guid = item_guid;
	memcpy(trade.logitem.ItemName,ItemName,min(strlen(ItemName)+1, sizeof(trade.logitem.ItemName)));
	trade.logtype = logtype;
	trade.item_cost = item_cost;
	return SendMsgToLogServer(&trade);
}

bool LogEventService::LogItemConsume(unsigned long accid,unsigned long chid,unsigned short item_id,unsigned long item_count,__int64 item_guid,
									 unsigned short LaveCount,char logtype,const char* CharName, const char* ItemName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LItemConsume consume;
	memcpy(&consume.logcommon._time,&systime,sizeof(SYSTEMTIME));
	consume.logcommon.account_id = accid;
	consume.logcommon.character_id = chid;
	memcpy(consume.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(consume.logcommon.chName)));
	consume.logitem.item_id = item_id;
	consume.logitem.item_count = item_count;
	consume.logitem.item_guid = item_guid;
	consume.item_LaveCount = LaveCount;
	memcpy(consume.logitem.ItemName,ItemName,min(strlen(ItemName)+1, sizeof(consume.logitem.ItemName)));
	consume.logtype = logtype;
	return SendMsgToLogServer(&consume);
}

bool LogEventService::LogItemUpgrade(unsigned long accid,unsigned long chid,unsigned short item_id,unsigned long item_count,__int64 item_guid,char logtype,char _result,
					unsigned short previous[],unsigned short current[],const char* CharName , const char* ItemName)
{
	if (!_OpenService)
	{
		return false;
	}
//memcpy( szString, pszChatString, min(strlen(pszChatString)+1, sizeof(szString)) );
	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LItemUpgrade upgrade;
	upgrade.logcommon.account_id = accid;
	upgrade.logcommon.character_id = chid;
	memcpy(upgrade.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(upgrade.logcommon.chName)));
	memcpy(&upgrade.logcommon._time,&systime,sizeof(SYSTEMTIME));
	upgrade.logitem.item_count = item_count;
	upgrade.logitem.item_id = item_id;
	upgrade.logitem.item_guid = item_guid;
	memcpy(upgrade.logitem.ItemName,ItemName,min(strlen(ItemName)+1, sizeof(upgrade.logitem.ItemName)));
	upgrade.result = _result;
	upgrade.logtype = logtype;
	switch(logtype)
	{
	case eItemLogInfo_ItemUpgrade_Intensify://ÉýÐÇ
	case eItemLogInfo_ItemUpgrade_MountIntensify://×øÆïÉýÐÇ
	case eItemLogInfo_ItemUpgrade_TradeStar://×ªÐÇ
	case eItemLogInfo_ItemUpgrade_SoulStamp:
		upgrade.previous[0] = previous[0];
		upgrade.current[0] = current[0];
		break;
	case eItemLogInfo_ItemUpgrade_Hole://´ò¿×
	case eItemLogInfo_ItemUpgrade_InsertHole://ÏâÇ¶
	case eItemLogInfo_ItemUpgrade_OutGem://°Î±¦Ê¯
		for (int n =0; n < SCharItem::EConstDefine_GemHoleMaxCount;n++)
		{
			upgrade.previous[n] = previous[n];
			upgrade.current[n] = current[n];
		}
		break;
	case eItemLogInfo_ItemUpgrade_Random://Ï´Ëæ»ú
		for (int n =0; n < SCharItem::EConstDefine_BaseRandMaxCount;n++)
		{
			upgrade.previous[n] = previous[n];
			upgrade.current[n] = current[n];
		}
		break;
	case eItemLogInfo_ItemUpgrade_OpenLight:
		for (int n =0; n < SCharItem::EConstDefine_PurpleRandMaxCount;n++)
		{
			upgrade.previous[n] = previous[n];
			upgrade.current[n] = current[n];
		}
		break;
	case eItemLogInfo_ItemUpgrade_ReOpenLight:
		for (int n =0; n < SCharItem::EConstDefine_PurpleRandMaxCount;n++)
		{
			upgrade.previous[n] = previous[n];
			upgrade.current[n] = current[n];
		}
		break;
	default:
		return false;
	}
	return SendMsgToLogServer(&upgrade);
}

bool LogEventService::LogQuest(unsigned long accid,unsigned long chid,unsigned short questid ,const char* CharName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LQuestLog questlog;
	memcpy(&questlog.logcommon._time,&systime,sizeof(SYSTEMTIME));
	questlog.logcommon.account_id = accid;
	questlog.logcommon.character_id = chid;	
	memcpy(questlog.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(questlog.logcommon.chName)));
	questlog.questid = questid;
	return SendMsgToLogServer(&questlog);
}

bool LogEventService::LogCurrency(unsigned long accid,unsigned long chid,int count,char money_type,char logtype,const char* CharName,int16 sourcetype)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LCurrencyLog currency;
	memcpy(&currency.logcommon._time,&systime,sizeof(SYSTEMTIME));
	currency.logcommon.account_id = accid;
	currency.logcommon.character_id = chid;	
	memcpy(currency.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(currency.logcommon.chName)));
	currency.money_type = money_type;
	currency.logtype = logtype;
	currency.count = count;
	currency.sourcetype = sourcetype;
	return SendMsgToLogServer(&currency);
}

bool LogEventService::LogExp(unsigned long accid,unsigned long chid,int _exp,int monsterid,char logtype,const char* CharName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LExpLog explog;
	memcpy(&explog.logcommon._time,&systime,sizeof(SYSTEMTIME));
	explog.logcommon.account_id = accid;
	explog.logcommon.character_id = chid;
	memcpy(explog.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(explog.logcommon.chName)));
	explog._exp = _exp;
	explog.logtype = logtype;
	explog.monsterid = monsterid;
	return SendMsgToLogServer(&explog);
}

bool LogEventService::LogLevelChange(unsigned long accid,unsigned long chid,unsigned short previouslv,unsigned short newlv,const char* CharName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	GS2LLevelChange lvc;
	memcpy(&lvc.logcommon._time,&systime,sizeof(SYSTEMTIME));
	lvc.logcommon.account_id = accid;
	lvc.logcommon.character_id = chid;
	memcpy(lvc.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(lvc.logcommon.chName)));
	lvc.previouslev = previouslv;
	lvc.newlev = newlv;
	return SendMsgToLogServer(&lvc);
}

bool LogEventService::LogMail(unsigned long sender_accid,
							  unsigned long sender_chid,
							  unsigned long recv_chid,
							  char* _title,
							  char* _detail,
							  unsigned short item_id,
							  unsigned short item_count,
							  uint32 _money,
							  __int64 ItemGUID,
							  const char* SenderName,
							  const char* RevcName, 
							  const char* ItemName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	S2LMailLog maillog;
	memcpy(&maillog._time,&systime,sizeof(SYSTEMTIME));
	maillog.send_accid = sender_accid;
	maillog.send_chid = sender_chid;
	maillog.recv_chid = recv_chid;
	maillog.item_count = item_count;
	maillog.item_id = item_id;
	maillog.money = _money;
	maillog.item_Guid = ItemGUID;

	//===============================================================
	memcpy(maillog.send_CharName,SenderName,min(strlen(SenderName)+1, sizeof(maillog.send_CharName)));
	memcpy(maillog.recv_CharName,RevcName,min(strlen(RevcName)+1, sizeof(maillog.recv_CharName)));
	memcpy(maillog.ItemName,ItemName,min(strlen(ItemName)+1, sizeof(maillog.ItemName)));
   //===============================================================

	_snprintf(maillog.mail_title, sizeof(maillog.mail_title)-1, "%s",_title);
	_snprintf(maillog.mail_detail, sizeof(maillog.mail_detail)-1, "%s",_detail);
	return SendMsgToLogServer(&maillog);
}

bool LogEventService::LogGuild(unsigned long accid,unsigned long chid,unsigned long guildid,char logtype ,const char* CharName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	S2LGuildLog guildlog;
	memcpy(&guildlog.logcommon._time,&systime,sizeof(SYSTEMTIME));
	guildlog.logcommon.account_id = accid;
	guildlog.logcommon.character_id = chid;
	memcpy(guildlog.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(guildlog.logcommon.chName)));
	guildlog.guild_id = guildid;
	guildlog.logtype = logtype;
	return SendMsgToLogServer(&guildlog);
}

bool LogEventService::LogGuildDetail(unsigned long accid,unsigned long chid,unsigned long guildid,int moneychange,int expchange,int missionchange,const char* CharName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	S2LGuildDetailLog guilddetail;
	memcpy(&guilddetail.logcommon._time,&systime,sizeof(SYSTEMTIME));
	guilddetail.logcommon.account_id = accid;
	guilddetail.logcommon.character_id = chid;
	memcpy(guilddetail.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(guilddetail.logcommon.chName)));
	guilddetail.expchange = expchange;
	guilddetail.moneychange = moneychange;
	guilddetail.missionchange = missionchange;
	return SendMsgToLogServer(&guilddetail);
}

bool LogEventService::LogGMCommand(unsigned long accid,unsigned long chid,const char* chname,const char* content,const char* ipaddr,const char* CharName)
{
	if (!_OpenService)
	{
		return false;
	}

	SYSTEMTIME systime;
	GetLocalTime( &systime );
	GS2LGMCommand gmcommand;
	memcpy(&gmcommand.logcommon._time,&systime,sizeof(SYSTEMTIME));
	gmcommand.logcommon.account_id = accid;
	gmcommand.logcommon.character_id = chid;
	memcpy(gmcommand.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(gmcommand.logcommon.chName)));
	_snprintf(gmcommand.name, sizeof(gmcommand.name)-1, "%s",chname);
	_snprintf(gmcommand.ipAddr, sizeof(gmcommand.ipAddr)-1, "%s",ipaddr);
	_snprintf(gmcommand.frondose, sizeof(gmcommand.frondose)-1, "%s",content);
	return SendMsgToLogServer(&gmcommand);
}

bool LogEventService::LogChatInfo(unsigned long accid,unsigned long chid,unsigned long targetid,const char* content,short chattype,const char* CharName, const char* TargetName)
{
	if (!_OpenService)
	{
		return false;
	}
	SYSTEMTIME systime;
	GetLocalTime( &systime );
	GS2LChatInfo chatinfo;
	memcpy(&chatinfo.logcommon._time,&systime,sizeof(SYSTEMTIME));
	memcpy(chatinfo.logcommon.chName,CharName,min(strlen(CharName)+1, sizeof(chatinfo.logcommon.chName)));
	memcpy(chatinfo.TargetCharName,TargetName,min(strlen(TargetName)+1, sizeof(chatinfo.TargetCharName)));

	chatinfo.logcommon.account_id = accid;
	chatinfo.logcommon.character_id = chid;
	chatinfo.target_id = targetid;
	chatinfo.chat_type = chattype;
	_snprintf(chatinfo.content, sizeof(chatinfo.content)-1, "%s",content);
	return SendMsgToLogServer(&chatinfo);
}