#include "ConsoleApplication.h"
#include "GateServer.h"
#include "ResourcePath.h"
#include "Config.h"
#include "application_config.h"
//#include "Statistician.h"
#include "CommandLine.h"
#include "MiniDumper.h"

#include "NetWorkParameterDefine.h"

long ConsoleApplication::m_exitFlag = 0;

ConsoleApplication* gConsoleApplication = NULL;

ConsoleApplication::ConsoleApplication(bool isdebug):IsDebug(isdebug)/* : NTService( APPLICATION_NAME, APPLICATION_NAME )*/
{
    m_hIn = 0;
    gConsoleApplication = this;
    bReloadLog4cxx = false;
}

ConsoleApplication::~ConsoleApplication()
{
    m_hIn = 0;
}

void CloseServerProcess()
{
    char szTxtBuf[128] = {0};
    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif
    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "Are you sure to close the %s:%s:%d:%s?", applicationName.c_str(), theCfg.szGameServerName, theCfg.nGateServerId, 
                                                                                      ApplicationConfig::Instance().GetFullVersion()); 
    if ( gConsoleApplication && gConsoleApplication->GetDebugMode() )
    {
        if( MessageBoxA(GetConsoleWindow(), szTxtBuf, APPLICATION_NAME, MB_YESNO|MB_ICONQUESTION|MB_TOPMOST) == IDYES)
        {
            InterlockedExchange(&ConsoleApplication::m_exitFlag, 1);
            LogMessage::LogSystemInfo("关闭Centerserver");
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
    //if ( !GetDebugMode())
    //{ ReportStatus(SERVICE_START_PENDING); }    

    // Init
    if ( !Init( argc, argv ) )
    {
        std::cout << "初始化失败" << std::endl;
        return;
    }

    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_RUNNING); }*/

    // Run
    long nResult = MainLoop();

    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_STOP_PENDING); }*/

    // UnInit
    UnInit();

    /*if ( !GetDebugMode())
    { ReportStatus(SERVICE_STOPPED); }*/
}

bool ConsoleApplication::InitLogConfigure()
{
//     try
//     {
//         LOG_CONFIGURE( theCfg.strLogConfigFilePath.c_str() );        
//     }
//     catch(ConfigureException& e)
//     {   
//         std::cout << e.what() << std::endl;
//         return false;
//     }

    return true;
}

bool ConsoleApplication::Init( int argc, char* argv[] )
{
    SetupConsole();    
    
    srand( HQ_TimeGetTime() );
        
    // 域名解析
   /* if( !GetMeNetwork().SocketStartUp() )
    { return false; }*/
	if (!network::net_init(eN_GateServer_BigBufferSize,
					       eN_GateServer_BigBufferNum,
						   eN_GateServer_SmallBufferSize,
						   eN_GateServer_SmallBufferNum,
						   eN_GateServer_ListenNum,
						   eN_GateServer_SocketNum,
						   eN_GateServer_ThreadNum))
	{
		return 0;
	}

  //  MiniDumper::m_bDebugMode = GetDebugMode();
    CommandLine command;
    char szConfigFileName[MAX_PATH] = {0};
    if ( !command.ParseEx( argc, argv, szConfigFileName ))
    { 
        char szContent[256] = {0};
        sprintf_s( szContent, "ParseEx failed [%s]",szConfigFileName);
        std::cout << szContent << std::endl;
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false; 
    }

    Common::_tstring ConfigPath = szConfigFileName;
    ConfigPath = ConfigPath.substr( 0,ConfigPath.find_last_of("\\")+1 );
    ConfigPath += GATESERVER_COMMON_CONFIGNAME;

    char szContent[256] = {0};
    if ( !theCfg.InitCommonData( ConfigPath.c_str() ) )
    {
        sprintf_s( szContent, "theCfg.Init failed [%s]",szConfigFileName);
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }

    if ( !theCfg.InitPrivateData( szConfigFileName  ) )
    {
        sprintf_s( szContent, "theCfg.InitPrivateData failed [%s]",szConfigFileName);
      //  AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }

	//HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );
    
    sprintf_s( szContent, sizeof(szContent)-1,GATESERVER_PERFORMANCELOG_FILEPATH, theCfg.nGateServerId,theCfg.szGameServerName );
    gTrueTime.SetFile( szContent );
    
    // 初始化Log4cxx
   /* if ( !InitLogConfigure() )
    { return false; }*/
    
    if( CGateServer::ret_succ != GettheGateServer().Init( this ) )
    { return false; }
    
    char szTxtBuf[256] = {0};
    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif

    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s[%s:%d] PID[%u] [ServiceIP %s:%d] Version[%s]", applicationName.c_str(), theCfg.szGameServerName, theCfg.nGateServerId, ::GetCurrentProcessId(),
                                                                                       theCfg.strTranslateIp.c_str(),theCfg.nForClientGatePort, ApplicationConfig::Instance().GetFullVersion());
    LogMessage::LogSystemInfo("%s 程序启动.",szTxtBuf );
    SetConsoleTitleA(szTxtBuf);

    LogMessage::LogSystemInfo( "\n////////////////////\n"
                                                "Server Success Start\n"
                                                "F1 = Show Runing Information\n"
                                                "F5 = Enter /Commond Mode\n"
												"ESC= Quit the application\n"
                                                "////////////////////");
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
			in_addr addrl;
			addrl.S_un.S_addr = theCfg.dwForClientIP;
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"GateServer -OpenIP[%s] -OpenPort[%d] -PingCheckTime[%d]\n"
				"ConnectingToGameServer:[%s][%s:%d] State[%d]\n"
				"MaxPlayerCfg[%d] OnlinePlayNum[%d] OnlineTotalNum[%d]\n"
				"MessageCfg In[%d:%d] Out[%d]\n"
				"ClientMsgQueueCfg MI[%d] MO[%d] ML[%d] MN[%d]\n"
				"GameServerMsgQueueCfg MI[%d] MO[%d] ML[%d] MN[%d]\n"
				"============================",
				inet_ntoa(addrl),theCfg.nForClientGatePort,theCfg.dwCheckClientPingMsg,
				theCfg.szGameServerName,theCfg.szGameServerIP,theCfg.nGameServerPort,theGateServer.GetGameServerConnectStatus(),
				theCfg.playerMaxOnlineCount,theGateServer.GetOnlinePlayGameNum(),theGateServer.GetOnlineNum(), 
				theGateServer.GetMessageInCount(true),theGateServer.GetMessageInCount(false),theGateServer.GetMessageOutCount(),
				theCfg.clientMaxCountIn,theCfg.clientMaxCountOut,theCfg.clientLowLvlCast,theCfg.clientNormalLvlCast,
				theCfg.gameMaxCountIn,theCfg.gameMaxCountOut,theCfg.gameLowLvlCast,theCfg.gameNormalLvlCast );
            /*gTrueTime.Output();*/
        }
        break;
    case VK_F3:
        {
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"%s"
				"\n============================",
				network::net_memory_info());
           /* gTrueTime.Output( true );*/
        }
        break;
    case VK_F4:
        {   
			size_t nSize = sizeof(BaseCharacter);
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"AllocClients    mem:[%d]KB     NormalClients mem:[%d]KB\n"
				"ClientWaitClose mem:[%d]KB     GateClients   mem:[%d]KB\n"
				"\n============================",
				nSize*dr_worldMaxPlayers * 4/1024,nSize*dr_worldMaxCharacters/1024,
				nSize*dr_worldMaxPlayers * 4/1024,nSize*dr_worldMaxPlayers * 4/1024);
            /*theGateServer.showFrameTime = true;*/
        }
        break;
    case VK_F5:
        {
			std::cout << "===============================\n"
				"进入命令模式 \n"
				"\t netiolog 进入网络统计模式\n"
				"\t crash 使gateserver崩溃,用于调试\n"
				"\t exit 退出命令模式 \n"
				"===============================\n";

			std::string strCommand; 
			
			while( true )
			{
				std::cout << ">>";
				std::cin >> strCommand;
				bool bInvalidCmd = false;
				if( _stricmp( strCommand.c_str(),"exit") == 0)
					break;

				if(strCommand == "restart")
				{
					//GettheLoginServer().Init(LOGINSERVER_CONFIGFILENAME);	
				}
				else if ( _stricmp( strCommand.c_str(),"crash") == 0 )
				{
					char *pCrash = NULL;
					*pCrash = 1;
				}
				else if( _stricmp( strCommand.c_str(),"netiolog") == 0 )
				{

				}
				else if (strCommand == "crash")
				{
					char *pCrash = NULL;
					*pCrash = 1;
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
    case VK_F6:
        {
            
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

void MainLogicThreadFunc( void* lpVoid )
{
    GettheGateServer().RunOneStep();
    static const int nSleepTime = 1; //theCfg.m_bSleepTime;
    Sleep( nSleepTime );
}

long ConsoleApplication::MainLoop()
{
    // 初始化逻辑线程
    _mainLogicThread.CreateThread( MainLogicThreadFunc ) ;//,THREAD_PRIORITY_ABOVE_NORMAL ) )

    _hMainInputThread = GetCurrentThread();

    for(;;)
    {
        if( m_exitFlag )
        { break; }

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

    _mainLogicThread.StopThreadAndWaitDead();

    return true;
}

void ConsoleApplication::UnInit()
{  
    GettheGateServer().Shutdown();

    //theCfg.Save();

    FreeConsole();
}

void ConsoleApplication::Reset()
{   
    _mainLogicThread.StopThreadAndWaitDead();
    GettheGateServer().Shutdown();
    GettheGateServer().Init( this );
    _mainLogicThread.CreateThread( MainLogicThreadFunc );
}

void ConsoleApplication::SetupConsole()
{
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

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
    if(SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
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
