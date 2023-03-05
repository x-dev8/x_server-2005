#ifndef __SYSTEMINFOWORKTHREAD_H__
#define __SYSTEMINFOWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"

class SystemInfoWorkThread:public MySqlWorkThread
{
public:
	SystemInfoWorkThread(LogServerMySql* pOwn);
	~SystemInfoWorkThread(void);

	virtual bool IsHaveTask()
	{ return _LogMsgQueue.GetQueueSize() > 0; }

	virtual uint32 Update();

	void OnMsgGuild(BaseLogMessage* pMessage);
	void OnMsgGuildDetail(BaseLogMessage* pMessage);
	void OnMsgChatInfo(BaseLogMessage* pMessage);
};
#endif