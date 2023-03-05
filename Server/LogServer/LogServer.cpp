// LogServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ColorScreen.h"
#include "network.h"
#include "NetWorkParameterDefine.h"
#include "application_config.h"
#include "MiniDumper.h"
#include "license.h"
#include "LogServerConfig.h"
#include "LogServerMySql.h"
#include "LogServerLogic.h"

#define APPLICATION_NAME "LogServer"

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	system("pause");
#endif

	MiniDumper dumper( APPLICATION_NAME, ApplicationConfig::Instance().GetFullVersion(), NULL );

#ifndef _DEBUG
	LicenseChecker::Instance();
#endif

	if (!theLogServerConfig.LoadConfig())
	{
		ColoredPrintf( COLOR_RED, "init  LogServer.config error!\n" );
		system("pause");
		return 0;
	}
	if (!network::net_init(eN_LogServer_BigBufferSize,
		eN_LogServer_BigBufferNum,
		eN_LogServer_SmallBufferSize,
		eN_LogServer_SmallBufferNum,
		eN_LogServer_ListenNum,
		eN_LogServer_SocketNum,
		eN_LogServer_ThreadNum))
	{
		ColoredPrintf( COLOR_RED, "init  network error!\n" );
		system("pause");
		return 0;
	}
	if ( ER_Success != theLogServerMySql.Init(theLogServerConfig.strOnlineInfoName,theLogServerConfig.strOnlineInfoIP,theLogServerConfig.OnlineInfoPort,theLogServerConfig.strOnlineInfoUser,theLogServerConfig.strOnlineInfoPwd, 
											  theLogServerConfig.strItemInfoName,theLogServerConfig.strItemInfoIP,theLogServerConfig.ItemInfoPort,theLogServerConfig.strItemInfoUser,theLogServerConfig.strItemInfoPwd, 
											  theLogServerConfig.strPlayerInfoName,theLogServerConfig.strPlayerInfoIP,theLogServerConfig.PlayerInfoPort,theLogServerConfig.strPlayerInfoUser,theLogServerConfig.strPlayerInfoPwd, 
											  theLogServerConfig.strSystemInfoName,theLogServerConfig.strSystemInfoIP,theLogServerConfig.SystemInfoPort,theLogServerConfig.strSystemInfoUser,theLogServerConfig.strSystemInfoPwd) )
	{ 
		ColoredPrintf( COLOR_RED, "init  LogServerMySql error!\n" );
		system("pause");
		return 0;
	}

	if (!theLogServerLogic.Init())
	{
		ColoredPrintf( COLOR_RED, "init  LogServerLogic error!\n" );
		system("pause");
		return 0;
	}

	char szTxtBuf[128] = {0};
	std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
	applicationName += "-Debug";
#endif
	sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s PID[%u] Version[%s]", applicationName.c_str(),::GetCurrentProcessId(), ApplicationConfig::Instance().GetFullVersion());
	SetConsoleTitleA(szTxtBuf);	
	ColoredPrintf( COLOR_GREEN, "LogServer OK!\n" );
	while (true)
	{
		Sleep(100);
	}

	return 0;
}