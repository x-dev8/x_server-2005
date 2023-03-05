#include "ConsoleApplication.h"
#include "ResourcePath.h"
#include "application_config.h"
#include "DatabaseInterface.h"
#include "CommandLine.h"
#include "DBMessageDefine.h"
#include "FileDatabase.h"
#include "RunStatus.h"
#include "DatabaseServerApp.h"
#include "MiniDumper.h"
#include "ColorScreen.h"

long ConsoleApplication::m_exitFlag = 0;

ConsoleApplication* gConsoleApplication = NULL;
ConsoleApplication* ConsoleApplication::gGlobalConsole = NULL;

ConsoleApplication::ConsoleApplication(bool isdebug):m_bDebug(isdebug)/* : NTService( APPLICATION_NAME, APPLICATION_NAME )*/
{
    m_hIn = 0;
    gConsoleApplication = this;
}

ConsoleApplication::~ConsoleApplication()
{

}

void ConsoleApplication::CrashCall()
{
    std::cout << "CrashCall" << std::endl;
    //GetFileDatabase().SaveUnsaveDatasToFiles(); 
}

void CloseServerProcess()
{
    if ( DbRunStatus::RunStatus_PrepareStop == theDbRunStatus.GetStatus() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"已经处于准备退出阶段");
        return;
    }

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
            GetRunStatus().SetStatus( DbRunStatus::RunStatus_PrepareStop );
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"开始准备关闭DatabaseServer");
        }
    }
    else
    {
        theDbRunStatus.SetStatus( DbRunStatus::RunStatus_PrepareStop );
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
   /* if ( !GetDebugMode())
    { ReportStatus(SERVICE_START_PENDING); }    */

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

bool ConsoleApplication::Init( int argc, char* argv[] )
{
    CoInitialize(NULL);
	SetupConsole();

    theMysqlCommunication;

    // 初始化SqlMessageManager
    theSqlMessageManager;
   

   // MiniDumper::m_bDebugMode = GetDebugMode();
    CommandLine command;
    char szIniFileName[MAX_PATH] = {0};
    if ( !command.ParseEx( argc, argv, szIniFileName ))
    {
        char szContent[256] = {0};
        sprintf_s( szContent, "ParseEx failed [%s]",szIniFileName);
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false; 
    }

    srand( HQ_TimeGetTime() );

    //GetFileDatabase().SetRootPath(FILEDATABASE_DIRECTORY);

    gTrueTime.SetFile( DATABASE_PERFORMANCELOG_FILEPATH );

    //SetNetworkApp( GetDatabaseServerApp() );
    //uint32 nResult = GetNetworkApp()->Init( szIniFileName );
	uint32 nResult = GetDatabaseServerApp()->Init(szIniFileName);
    if( nResult != ER_Success )
    {
        char szContent[256] = {0};
        sprintf_s( szContent, "Init failed [%d][%s]",nResult,szIniFileName);
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }
    
    char szTxtBuf[128] = {0};
    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif
    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s PID[%u] Port[%d] Version[%s]", applicationName.c_str(), ::GetCurrentProcessId(), GetDatabaseServerApp()->GetListenPort(), ApplicationConfig::Instance().GetFullVersion());
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s 程序启动.",szTxtBuf );
    SetConsoleTitleA(szTxtBuf);

    HANDLE hThread = GetCurrentThread();
    SetThreadPriority( hThread,THREAD_PRIORITY_BELOW_NORMAL );

	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "\n////////////////////\n"
												"Server Success Start\n"
												"F1 = Show Runing Information\n"
												"F5 = Enter /Commond Mode\n"
												"ESC= Quit the application\n"
												"////////////////////\n");

    _dwStartTime = HQ_TimeGetTime();
    
    GetRunStatus().SetStatus( DbRunStatus::RunStatus_Running );

    COLOR_MESSAGE( COLOR_GREEN, "[DatabaseServer OK] \n" );
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
				"F6:Try Show DBTask Queue Size Info\n"
				"F7:Try Show DBTask updata or save data Once Time Info\n"
				"ESC:Quit the application\n"
				"============================",
				DayNum,HourNum,MinNum,RunTime);
        }
        break;
    case VK_F2:
        {
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"SqlType:[%s] IsAccountBilling:[%d]\n"
				"IsOpenBillingService[%d] IsOpenBillingScoreService[%d] IsUseCancelDel[%d]\n"
				"BillingWorkThreadState[%d]\n"
				"NormalLogicWorkThreadState[%d]\n"
				"SocietyRelationWorkThreadState[%d]\n"
				"UnSavePlayerNum[%d] MaxPlayerInFileMapping[%d]\n"
				"============================",
				theDatabaseServerApp->useSqlType == DatabaseServerApp::ST_MySql ? "ST_MySql":"ST_MSSql",theDatabaseServerApp->m_bAccountBilling,
				theDatabaseServerApp->bOpenBillingService,theDatabaseServerApp->bOpenBillingScoreService,theDatabaseServerApp->m_bUseCancelDel,
				theMysqlCommunication.GetWorkThreadWorkState(MySqlCommunication::ECD_BillingWorkThread),
				theMysqlCommunication.GetWorkThreadWorkState(MySqlCommunication::ECD_NormalLogicWorkThread),
				theMysqlCommunication.GetWorkThreadWorkState(MySqlCommunication::ECD_SocietyRelationWorkThread),
				theFileMappingCharSaveManager.GetPlayerNumInFileMapping(),FileMappingCharSaveManager::CD_CHARSAVE_MAXSIZE);
				
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
			//G_PrinfInfo = PRINTFSAVEROLETIME;
        }
        break;
    case VK_F4:
        {
			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "\n============================");
			{
				CSALocker locker(GetAutoIntLock());
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
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"============================");
           /* gTrueTime.Output( true );
            G_PrinfInfo = PRINTFQUEUESIZE;*/
        }
        break;
    case VK_F5:
        {
            std::cout << "===============================\n"
                         "进入命令模式 \n"
						 "\t crash 让server挂掉\n"
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

                if(strCommand == "restart")
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
			G_PrinfInfo = PRINTFQUEUESIZE;
            //theMysqlCommunication.bMemoryInfo = true;

            //DBMsgSaveCharacter testmsg;
            //testmsg.dwCharacterID = 1000;

            //std::cout << "Begin..." << std::endl;
            //BEGINFUNCPERLOG("SaveFileDatabase");
            //for ( int i=1; i<2; ++i )
            //{                
            //    testmsg.dwCharacterID = i;
            //    GetFileDatabase().UpdateSaveData( testmsg, true );
            //}
            //ENDFUNCPERLOG("SaveFileDatabase");
            //std::cout << "..End" << std::endl;
        }
        break;
	case VK_F7:
		{
			G_PrinfInfo = PRINTFSAVEROLETIME;
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
   // GetNetworkApp()->Update();
	GetDatabaseServerApp()->Update();
    static const int nSleeptime = 1;//GetDatabaseServerApp()->m_bSleepTime;         // sleep 时间
    Sleep( nSleeptime );
}

long ConsoleApplication::MainLoop()
{
    // 初始化逻辑线程
    _mainLogicThread.CreateThread( MainLogicThreadFunc ) ;//,THREAD_PRIORITY_ABOVE_NORMAL ) )

    _hMainInputThread = GetCurrentThread();

    for(;;)
    {
        //if( GetRunStatus().GetStatus() == DbRunStatus::RunStatus_Stopped )
        //{ break; }

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
    _mainLogicThread.StopThreadAndWaitDead();

   // GetNetworkApp()->ShutDown();
	GetDatabaseServerApp()->ShutDown();

    // 施法theFileMappingCharSaveManager
    theFileMappingCharSaveManager.UnInit();

    FreeConsole();

    CoUninitialize();
}

void ConsoleApplication::Reset()
{   
}

void ConsoleApplication::SetupConsole()
{
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

    m_hIn = GetStdHandle(STD_INPUT_HANDLE);
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

    // 注册处理控制台消息回调函数
    if(SetConsoleCtrlHandler( (PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
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
