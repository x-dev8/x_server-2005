#ifndef __TestWorkThread_H__
#define __TestWorkThread_H__

#pragma once

#include "MySqlWorkThread.h"

class TestWorkThread:public MySqlWorkThread
{
public:
	TestWorkThread(LogServerMySql* pOwn);
	~TestWorkThread(void);

	virtual bool IsHaveTask()
	{ return _LogMsgQueue.GetQueueSize() > 0; }

	virtual uint32 Update();

	void OnTestMsg(BaseLogMessage* pMessage);
};

#endif