// PlatformCenter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PlatformConfig.h"
#include "ColorScreen.h"
#include "network.h"
#include "NetWorkParameterDefine.h"
#include "PlatformWorkSpace.h"
#include "application_config.h"
#include "MiniDumper.h"
#include "license.h"

#define APPLICATION_NAME "PlatformCenter"

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	system("pause");
#endif

	MiniDumper dumper( APPLICATION_NAME, ApplicationConfig::Instance().GetFullVersion(), NULL );

#ifndef _DEBUG
	LicenseChecker::Instance();
#endif
	

	if (!thePlatFormConfig.LoadConfig())
	{
		ColoredPrintf( COLOR_RED, "init  PlatformConfig.config error!\n" );
		system("pause");
		return 0;
	}

	if (!network::net_init(eN_PlatFormCenter_BigBufferSize,
		eN_PlatFormCenter_BigBufferNum,
		eN_PlatFormCenter_SmallBufferSize,
		eN_PlatFormCenter_SmallBufferNum,
		eN_PlatFormCenter_ListenNum,
		eN_PlatFormCenter_SocketNum,
		eN_PlatFormCenter_ThreadNum))
	{
		ColoredPrintf( COLOR_RED, "init  network error!\n" );
		system("pause");
		return 0;
	}

	if (thePlatFormWorkSpace.Init() != ER_Success)
	{
		ColoredPrintf( COLOR_RED, "init platform init error!\n" );
		system("pause");
		return 0;
	}
	ColoredPrintf( COLOR_GREEN, "[PlatformCenter OK] \n" );

	char szTxtBuf[128] = {0};
	std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
	applicationName += "-Debug";
#endif
	sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s PID[%u] Version[%s]", applicationName.c_str(),::GetCurrentProcessId(), ApplicationConfig::Instance().GetFullVersion());
	SetConsoleTitleA(szTxtBuf);	

	while (true)
	{
		Sleep(100);
	}
	return 0;
}