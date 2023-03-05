/********************************************************************
	Filename: 	Main.cpp
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#include "MeRTLibsServer.h"
#include "ConsoleApplication.h"
#include "application_config.h"
#include "MiniDumper.h"

int main( int argc, char* argv[])
{
	bool isdebug = false;
#ifdef _DEBUG
   /*system("pause");*/
	isdebug = true;
#endif

	MiniDumper dumper( APPLICATION_NAME, ApplicationConfig::Instance().GetFullVersion(), NULL );

    ConsoleApplication application(isdebug); // 应用对象

    // 解析标准命令
 /*   if (!application.RegisterService(argc,argv))
    {}*/
	application.Run(argc,argv);

    //服务停止
    return 0;/*application.pGamePlayer().dwWin32ExitCode;*/
}
