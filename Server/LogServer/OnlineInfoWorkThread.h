#ifndef __ONLINEINFOWORKTHREAD_H__
#define __ONLINEINFOWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"

class OnlineInfoWorkThread:public MySqlWorkThread
{
public:
	OnlineInfoWorkThread(LogServerMySql* pOwn);
	virtual ~OnlineInfoWorkThread(void);

	virtual bool IsHaveTask()
	{ return _LogMsgQueue.GetQueueSize() > 0; }

	virtual uint32 Update();

	void OnMsgOnlineInfo(BaseLogMessage* pMessage);
	void OnMsgGMCommand	(BaseLogMessage* pMessage);
};

#endif
