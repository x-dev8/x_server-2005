/********************************************************************
	Filename: 	Main.cpp
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#include "MeRTLibsServer.h"
#include "ConsoleApplication.h"
#include "application_config.h"
#include "MiniDumper.h"
#include "ServerDefine.h"

int main( int argc, char* argv[])
{
	bool isdebug = false;
#ifdef _DEBUG
	//system("pause");
	isdebug = true;
#endif
	MiniDumper dumper( APPLICATION_NAME, ApplicationConfig::Instance().GetFullVersion(), NULL ); 

    ConsoleApplication application(isdebug); // Ӧ�ö���

    // ������׼����
   /* if (!application.Run(argc,argv))
    {}*/
	application.Run(argc,argv);

    //����ֹͣ
    return 0/*application.GetStatus().dwWin32ExitCode*/;
}
