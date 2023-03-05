#ifndef __ITEMINFOWORKTHREAD_H__
#define __ITEMINFOWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"

class ItemInfoWorkThread:public MySqlWorkThread
{
public:
	ItemInfoWorkThread(LogServerMySql* pOwn);
	virtual ~ItemInfoWorkThread(void);

	virtual bool IsHaveTask()
	{ return _LogMsgQueue.GetQueueSize() > 0; }

	virtual uint32 Update();

	void OnMsgItemGain(BaseLogMessage* pMessage);
	void OnMsgItemTrade(BaseLogMessage* pMessage);
	void OnMsgItemConsume(BaseLogMessage* pMessage);
	void OnMsgItemUpgrade(BaseLogMessage* pMessage);
};

#endif