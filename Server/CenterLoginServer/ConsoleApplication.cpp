#include "ConsoleApplication.h"
//#include "LoginServer.h"
#include "ResourcePath.h"
#include "Config.h"
#include "application_config.h"
#include "LoginServer.h"
//#include "GameServerManager.h"
//#include "LoginQueue.h"
#include "CommandLine.h"
#include "SqlService.h"
#include "MiniDumper.h"
#include "XmlStringLanguage.h"
#include "LogFileObjectNameEx.h"
//#include "ServerStatusManager.h"
#include "TradeCenterInfo.h"
#include "MeNetworkCode.h"
#include "CountryConfig.h"
#include "GuildConfig.h"
#include "CountryManager.h"
#include "VarClearConfig.h"
#include "FamilyConfig.h"
#include "ColorScreen.h"
#include "NetWorkParameterDefine.h"
//#include "LevelLimitConfig.h"
#include "CountryReward.h"
#include "network.h"
#include "GLSService.h"
#include "AccountServer.h"
#include "AccountDBSession.h"

long ConsoleApplication::m_exitFlag = 0;

ConsoleApplication* gConsoleApplication = NULL;

ConsoleApplication::ConsoleApplication(bool bdebug):_debugmode(bdebug)/* : NTService( APPLICATION_NAME, APPLICATION_NAME )*/
{
    m_hIn = 0;
    gConsoleApplication = this;
}

ConsoleApplication::~ConsoleApplication()
{
}

void CloseServerProcess()
{
    char szTxtBuf[128] = {0};

    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif

    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "Are you sure to close the %s:%s?", applicationName.c_str(), ApplicationConfig::Instance().GetFullVersion()); 

    if ( gConsoleApplication && gConsoleApplication->GetDebugMode() )
    {
        if( MessageBoxA(GetConsoleWindow(), szTxtBuf, APPLICATION_NAME, MB_YESNO|MB_ICONQUESTION|MB_TOPMOST) == IDYES)
        {
            InterlockedExchange(&ConsoleApplication::m_exitFlag, 1);
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"关闭Centerserver");
        }
    }
    else
    {
        InterlockedExchange(&ConsoleApplication::m_exitFlag, 1);
    }
}

BOOL WINAPI ConsoleHandler(DWORD cEvent)
{
    switch(cEvent)
    {
    case CTRL_C_EVENT:
        {
            CloseServerProcess();
        }
        break;
    case CTRL_BREAK_EVENT:
        {
            CloseServerProcess();
        }
        break;
    default:
        return true;
    }
    return true;
}

void ConsoleApplication::Run( DWORD argc, LPTSTR argv[])
{
    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_START_PENDING); }    */
	SetupConsole();
    // Init
    if ( !Init( argc, argv ) )
    {
        std::cout << "初始化失败" << std::endl;
#ifdef _DEBUG
		system("pause");
#endif
        return;
    }

    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_RUNNING); }*/

    // Run
    long nResult = MainLoop();

    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_STOP_PENDING); }*/

    // UnInit
#ifdef _DEBUG
	system("pause");
#endif

    UnInit(); 

    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_STOPPED); }*/
}

bool ConsoleApplication::Init( int argc, char* argv[] )
{
    CoInitialize(NULL);    

    srand( HQ_TimeGetTime() );

    // 网络服务
    //bool bResult = NetApi::NetworkIntance().SocketStartUp();
    //if ( !bResult )
    //{ return false; }
	if (!network::net_init(eN_LoginServer_BigBufferSize,
						   eN_LoginServer_BigBufferNum,
						   eN_LoginServer_SmallBufferSize,
						   eN_LoginServer_SmallBufferNum,
						   eN_LoginServer_ListenNum,
						   eN_LoginServer_SocketNum,
						   eN_LoginServer_ThreadNum))
	{
		return 0;
	}

	CommandLine command;
	char szIniFileName[MAX_PATH] = {0};
	if ( !command.ParseEx( argc, argv, szIniFileName ))
	{ 
		char szContent[256] = {0};
		sprintf_s( szContent, "ParseEx failed [%s]",szIniFileName);
		std::cout << szContent << std::endl;		
		return false;
	}
    
    bool bResult = theConfig.Init( szIniFileName );
    if ( !bResult )
    {
        char szContent[256] = {0};
        sprintf_s( szContent, "Config::GetInstance().Init failed [%s]",szIniFileName);
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }
//     
    gTrueTime.SetFile( CENTERLOGIN_PERFORMANCELOG_FILEPATH );

    //HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );    

    uint32 nResult = theCenterLoginServer.Init( this );
    if ( RESULT_FAILED(nResult ))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s 初始化失败[%d]\n", APPLICATION_NAME, nResult );
        return false; 
    }

    char szTxtBuf[128] = {0};
    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif

    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s PID[%u] Version[%s]", applicationName.c_str(), ::GetCurrentProcessId(), ApplicationConfig::Instance().GetFullVersion());    
    SetConsoleTitleA(szTxtBuf);
    
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s 程序启动.",szTxtBuf );


    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "\n////////////////////\n"
                                                "Server Success Start\n"
                                                "F1 = Show Runing Information\n"
                                                "F5 = Enter /Commond Mode\n"
												"ESC= Quit the application\n"
                                                "////////////////////\n");

    COLOR_MESSAGE( COLOR_GREEN, "[LoginServer OK] \n" );
    _dwStartTime = HQ_TimeGetTime();

    return true;
}

void ConsoleApplication::ProcessKey(DWORD keycode)
{
	switch(keycode)
	{
	case VK_F1:
		{
			int RunTime = (HQ_TimeGetTime() - _dwStartTime)/1000;
			int RunMin  = 60;
			int RunHour = 60 * RunMin;
			int RunDay = 24 * RunHour;
			int DayNum = RunTime / RunDay;
			RunTime -= DayNum * RunDay;
			int HourNum = RunTime / RunHour;
			RunTime -= HourNum * RunHour;
			int MinNum = RunTime / RunMin;
			RunTime -= MinNum * RunMin;

			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"Runing Time: [%d]day:[%d]hour:[%d]minute:[%d]second\n"
				"F2:Show Runtime sys-data\n"
				"F3:Show Runtime capability-net\n"
				"F4:Show Runtime capability-app\n"
				"ESC:Quit the application\n"
				"============================",
				DayNum,HourNum,MinNum,RunTime);
		}
		break;
	case VK_F2:
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"OnLoginNum[%d] IsNeedAccountServer[%d] -ConnectAccountServer[%d]\n"
				"IsNeedDB[%d] -ConnectMySql[%d] CurBlockSize[%d]\n"
				"============================",
				theCenterLoginServer.GetOnLoginNum(),theAccountServer.IsInService(),theAccountServer.IsConnected(),
				theAccountDBSession.GetService(),theAccountDBSession.GetConnectState(),theGLSService.GetBlockInfoSize());
		}
		break;
	case VK_F3:
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"%s"
				"\n============================",
				network::net_memory_info());
		}
		break;
	case VK_F4:
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"\n============================");
			{
				CSALocker locker(GetAutoIntLock());
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "[Heap-allocated memory footprint output start:]\n");
				uint32 nAllMemory = 0;
				for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); ++itr)
				{
					nAllMemory += itr->second.nAllUseMemory;
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, 
						"%-52s\n"
						"占用内存 [%-18d] 字节"
						"目前未释放共分配 [%-6d] 次"
						"历史申请[%-6d]次", 
						itr->first!=NULL?itr->first:"未定义用途", itr->second.nAllUseMemory, 
						itr->second.nExistCount, itr->second.nAllocCount );
				}
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "全部分配内存[%d]Byte | [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );
			}
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"\n============================");
		}
		break;
	case VK_F5:
		{
			std::cout << "===============================\n"
				"进入命令模式 \n"
				"\t reloadblock: 重新加载Block账号 \n"
				"\t exit 退出命令模式 \n"
				"===============================\n";

			std::string strCommand; 
			while( true )
			{
				std::cout << ">>";
				std::cin >> strCommand;
				bool bInvalidCmd = false;
				if(strCommand.compare("exit") == 0)
					break;
				if(strCommand == "reloadblock")
				{
					theGLSService.ReLoadBlockInfo();
				}
				else
				{
					bInvalidCmd = true;
				}
				bInvalidCmd ? std::cout << "Invalid command! \n": std::cout << "command ok \n";
			}
			std::cout << "**********end**********\n";
		}
		break;
	case VK_ESCAPE:
		{
			static DWORD dwLastDownKeyTime = 0;
			if (HQ_TimeGetTime() - dwLastDownKeyTime < 150)
			{
				CloseServerProcess();
			}
			dwLastDownKeyTime = HQ_TimeGetTime();
		}
		break;
	}
}

void ConsoleApplication::ConsoleInputLoop()
{
    enum{CONSOLE_BUFFER_SIZE = 1/*32*/,};
    INPUT_RECORD iBuffer/*[CONSOLE_BUFFER_SIZE]*/;
    DWORD        eventCount = 0;

    {
        CSALocker lock(_hInLock);
        if(!ReadConsoleInput( m_hIn, &iBuffer, CONSOLE_BUFFER_SIZE, &eventCount ))
			return ;
    }

	if(iBuffer.EventType!=KEY_EVENT)
		return ;
	if(iBuffer.Event.KeyEvent.bKeyDown == 0)
		return ;
	m_lstKeycode.push_back(iBuffer.Event.KeyEvent.wVirtualKeyCode);

    //for(DWORD n=0; n<eventCount; ++n)
    //{
    //    // some a key was pressed
    //    if(iBuffer[n].EventType == KEY_EVENT && iBuffer[n].Event.KeyEvent.bKeyDown)
    //    {
    //        m_lstKeycode.push_back(iBuffer[n].Event.KeyEvent.wVirtualKeyCode);
    //    }
    //}

}

long ConsoleApplication::MainLoop()
{
    _hMainInputThread = GetCurrentThread();

    for(;;)
    {
        if(m_exitFlag)
            break;

        ConsoleInputLoop();

         if(!m_lstKeycode.empty())
         {
             for(KeycodeList::iterator it = m_lstKeycode.begin(); it!=m_lstKeycode.end(); ++it)
             {
                 ProcessKey(*it);
             }
             m_lstKeycode.clear();
         }
        Sleep( 20 );
    }

    return true;
}

void ConsoleApplication::UnInit()
{  
//     LoginServer::GetInstance().UnInit();
// 
//     FreeConsole();
// 
//     CoUninitialize();
}

void ConsoleApplication::SetupConsole()
{
    ShowWindow( GetConsoleWindow(), SW_SHOWMAXIMIZED );

    m_hIn  = GetStdHandle( STD_INPUT_HANDLE );

    // prevent mouse input( it may cause some error )
    {
        DWORD dwMode = 0;
        GetConsoleMode(m_hIn, &dwMode);
        dwMode &= ~ENABLE_MOUSE_INPUT;
        SetConsoleMode(m_hIn, dwMode);
    }

    // 关闭×按钮 防止误点击
    HWND hWnd = GetConsoleWindow();  
    if(hWnd)  
    {  
        HMENU hMenu = GetSystemMenu(hWnd, FALSE);  
        EnableMenuItem(hMenu, SC_CLOSE, MF_DISABLED | MF_BYCOMMAND);  
    }

    //
    // 注册处理控制台消息回调函数
    //
    if(SetConsoleCtrlHandler(
        (PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
    {
        // unable to install handler... 
        // display message to the user
        return;
    } 

    return;
}

void ConsoleApplication::Stop()
{
    CloseServerProcess();
}
