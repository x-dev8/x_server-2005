// DataCenter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ColorScreen.h"
#include "application_config.h"
#include "MiniDumper.h"
#include "license.h"
#include "DataCenterConfig.h"
#include "LogicWork.h"
//#include "ServerStatus.h"

#define APPLICATION_NAME "DataCenter"

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	system("pause");
#endif

	MiniDumper dumper( APPLICATION_NAME, ApplicationConfig::Instance().GetFullVersion(), NULL );

#ifndef _DEBUG
	LicenseChecker::Instance();
#endif

	ColoredPrintf( COLOR_GREEN, "[DataCenter OK] \n" );

	char szTxtBuf[128] = {0};
	std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
	applicationName += "-Debug";
#endif
	if (!theConfig.LoadConfig())
	{
		ColoredPrintf( COLOR_RED, "init  DataCenter.config error!\n" );
		system("pause");
		return 0;
	}

	if (theLogicWork.Init()!= ER_Success)
	{
		ColoredPrintf( COLOR_RED, "init DataCenter init error!\n" );
		system("pause");
		return 0;
	}

	sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s PID[%u] Version[%s]", applicationName.c_str(),::GetCurrentProcessId(), ApplicationConfig::Instance().GetFullVersion());
	SetConsoleTitleA(szTxtBuf);

	while (true)
	{
		Sleep(100);
	}

	return 0;
}

