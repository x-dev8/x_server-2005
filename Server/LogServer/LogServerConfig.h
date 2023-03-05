#pragma once
#include <string>

using namespace std;
class LogServerConfig
{
public:
	LogServerConfig(void);
	~LogServerConfig(void);

	static LogServerConfig& Instance()
	{
		static LogServerConfig clsc;
		return clsc;
	}

	bool LoadConfig();
public:
	unsigned short ListenPort;

	string		   strOnlineInfoUser;
	string		   strOnlineInfoPwd;
	string		   strOnlineInfoName;
	string		   strOnlineInfoIP;
	unsigned short OnlineInfoPort;

	string		   strItemInfoUser;
	string		   strItemInfoPwd;
	string		   strItemInfoName;
	string		   strItemInfoIP;
	unsigned short ItemInfoPort;

	string		   strPlayerInfoUser;
	string		   strPlayerInfoPwd;
	string		   strPlayerInfoName;
	string		   strPlayerInfoIP;
	unsigned short PlayerInfoPort;

	string		   strSystemInfoUser;
	string		   strSystemInfoPwd;
	string		   strSystemInfoName;
	string		   strSystemInfoIP;
	unsigned short SystemInfoPort;
};

#define theLogServerConfig LogServerConfig::Instance()