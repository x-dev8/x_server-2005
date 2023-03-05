#pragma once
#include "PlatformMessageDefine.h"

class CCommonModule
{
public:
	CCommonModule(void);
	~CCommonModule(void);
	static CCommonModule& Instance()
	{
		static CCommonModule cc;
		return cc;
	}

	bool ParseCommand		(SGMTaskInfo* pInfo);
	bool ProcessFlyToMap	(const char* szContent,int server_id );
	bool ProcessBroadcast	(const char* szContent,int server_id );
	bool ProcessOpChat		(const char* szContent,int server_id );
	bool ProcessShutDown	(const char* szContent,int server_id );
	bool ProcessBanAccount	(const char* szContent,int server_id );
	bool ProcessBanMacAddr  (const char* szContent,int server_id );
private:
};

#define theCommandModule CCommonModule::Instance()