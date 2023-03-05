#pragma once

#include "WorkThread.h"

class CLogicWork
{
public:
	CLogicWork(void);
	~CLogicWork(void);
public:
	static CLogicWork& Instance()
	{
		static CLogicWork clw;
		return clw;
	}

	static void Main( void* pParam );

	bool Init();
	
private:
	static CWorkThread g_MainLogicThread;
};

#define theLogicWork CLogicWork::Instance()