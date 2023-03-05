/********************************************************************
Filename: 	Main.cpp
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#include "MeRTLibsServer.h"
#include "ConsoleApplication.h"
#include "application_config.h"
#include "MiniDumper.h"

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
    //if (!application.RegisterService(argc,argv))
    //{}
	application.Run(argc,argv);

    //����ֹͣ
    return 0/*application.GetStatus().dwWin32ExitCode*/;
}
