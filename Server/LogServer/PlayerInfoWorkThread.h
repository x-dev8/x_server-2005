#ifndef __PLAYERINFOWORKTHREAD_H__
#define __PLAYERINFOWORKTHREAD_H__

#pragma once

#include "MySqlWorkThread.h"

class PlayerInfoWorkThread:public MySqlWorkThread
{
public:
	PlayerInfoWorkThread(LogServerMySql* pOwn);
	~PlayerInfoWorkThread(void);

	virtual bool IsHaveTask()
	{ return _LogMsgQueue.GetQueueSize() > 0; }

	virtual uint32 Update();

	void OnMsgPlayerInOut(BaseLogMessage* pMessage);
	void OnMsgPlayerQuest(BaseLogMessage* pMessage);
	void OnMsgPlayerCurrency(BaseLogMessage* pMessage);
	void OnMsgPlayerExp(BaseLogMessage* pMessage);
	void OnMsgPlayerLevel(BaseLogMessage* pMessage);
	void OnMsgPlayerMail(BaseLogMessage* pMessage);
};
#endif