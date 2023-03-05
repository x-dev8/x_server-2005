#pragma once

#include "PlatformMessageDefine.h"

class CMailModule
{
public:
	CMailModule(void);
	~CMailModule(void);

	static CMailModule& Instance()
	{
		static CMailModule cmm;
		return cmm;
	}
	
	bool ProcessMailTask(SMailTaskInfo* pInfo);
};
#define theMailModule CMailModule::Instance()