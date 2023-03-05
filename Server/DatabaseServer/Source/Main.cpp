/********************************************************************
	Filename: 	Main.cpp
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#include "MeRTLibsServer.h"
#include "ConsoleApplication.h"
#include "application_config.h"
#include "MiniDumper.h"
#include "FileDatabase.h"

int main( int argc, char* argv[])
{   
	MiniDumper dumper( APPLICATION_NAME, ApplicationConfig::Instance().GetFullVersion(), NULL ); 
   // MiniDumper::pCrashFunc = ConsoleApplication::CrashCall;
	
	bool isdebug = false;
#ifdef _DEBUG
	//system("pause");
	isdebug = true;
#endif
#if 0
    FileMappingCharSaveManager::TestRead( true );
    FileMappingCharSaveManager::TestWrite();
    FileMappingCharSaveManager::TestRead( false );
    return 0;
#endif
    
    ConsoleApplication application(isdebug); // Ӧ�ö���
    //ConsoleApplication::gGlobalConsole = &application;

    // ������׼����
    //if (!application.RegisterService(argc,argv))
    //{}
	application.Run(argc,argv);

    //����ֹͣ
    return 0;/*application.GetStatus().dwWin32ExitCode;*/
}
