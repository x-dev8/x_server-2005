#ifndef _H_USER_LOGGER_H_
#define _H_USER_LOGGER_H_

#pragma once

#include "MeRTLibsServer.h"
#include "Memory_Pool.h"


#define MAX_LOG_NUM 10000
#define LOG_MSG_LENGTH 1024

class CPlayerLogger : public CSemiAutoIntLock
{
	typedef std::vector<std::string> vecLogStr;
public:
	CPlayerLogger();
	virtual ~CPlayerLogger();

public:
	bool PushLogger(std::string& strLog);
	bool PopLoggers(vecLogStr& vecStrLog);

	static void SaveThread(void* pLogger);
	vecLogStr m_LogStr;
};

extern CPlayerLogger& GetthePlayerLogger();

#endif //_H_USER_LOGER_H_