// SimpleLoginServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "network.h"

#include "config/config_file.h"
#include "AccountDBSession.h"
#include "LoginInterface.h"

#include "MiniDumper.h"

#include "NetWorkParameterDefine.h"

using namespace network;

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	system("pause");
#endif
	printf("this is simple login server,vvx's product!\n");

	//MiniDumper dumper( "login server", "alpha", NULL );

	if (!CConfig::Instance().InitConfig())
	{
		printf("Instance config file error!!\n");
		system("pause");
		return 0;
	}

	if (!network::net_init(eN_LoginServer_BigBufferSize,
						   eN_LoginServer_BigBufferNum,
						   eN_LoginServer_SmallBufferSize,
						   eN_LoginServer_SmallBufferNum,
						   eN_LoginServer_ListenNum,
						   eN_LoginServer_SocketNum,
						   eN_LoginServer_ThreadNum))
	{
		printf("net init error!!\n");
		system("pause");
		return 0;
	}

	if( !CLoginInterface::Instance().InitLogin())
	{
		printf("init login interface error!\n");
		system("pause");
		return 0;
	}

	CLoginInterface::Instance().StartThread();

	while(1)
	{
		Sleep(1);
	}
	//≤‚ ‘ ˝æ›ø‚
	//CAccountDBSession::Instance()._TryConnectToSqlDb();
	//if (CAccountDBSession::Instance().GetWorkState() == CAccountDBSession::SS_Connected)
	//{
	//	//CAccountDBSession::Instance().TestSQLDb();
	//	CAccountDBSession::Instance().CheckAccount("123","123");
	//	CAccountDBSession::Instance().CheckAccount("124","123");
	//	CAccountDBSession::Instance().CheckAccount("123","124");
	//}
	return 0;
}