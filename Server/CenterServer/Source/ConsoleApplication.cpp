#include "ConsoleApplication.h"
#include "CenterServer.h"
#include "ResourcePath.h"
#include "Config.h"
#include "application_config.h"
#include "CenterServer.h"
#include "GameServerManager.h"
//#include "LoginQueue.h"
#include "CommandLine.h"
#include "SqlService.h"
#include "MiniDumper.h"
#include "XmlStringLanguage.h"
#include "ServerStatusManager.h"
#include "TradeCenterInfo.h"
#include "MeNetworkCode.h"
#include "CountryConfig.h"
#include "GuildConfig.h"
#include "CountryManager.h"
#include "VarClearConfig.h"
#include "FamilyConfig.h"
#include "ColorScreen.h"
#include "NetWorkParameterDefine.h"
#include "LevelLimitConfig.h"
#include "CountryReward.h"
#include "GuildMissionConfig.h"
#include "GlobalDBManager.h"
#include "CenterTimeHandleManager.h"
#include "BroadCastConfig.h"
#include "QuestEntrust.h"
#include "ResourcePath.h"
#include "ConfigReloader.h"

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
	SetupConsole();

   // MiniDumper::m_bDebugMode = GetDebugMode();

    CommandLine command;
    char szIniFileName[MAX_PATH] = {0};
    if ( !command.ParseEx( argc, argv, szIniFileName ))
    { return false; }

    srand( HQ_TimeGetTime() );

    // 网络服务
    //bool bResult = NetApi::NetworkIntance().SocketStartUp();
    //if ( !bResult )
    //{ return false; }
	if (!network::net_init(eN_CenterServer_BigBufferSize,
						   eN_CenterServer_BigBufferNum,
						   eN_CenterServer_SmallBufferSize,
						   eN_CenterServer_SmallBufferNum,
						   eN_CenterServer_ListenNum,
						   eN_CenterServer_SocketNum,
						   eN_CenterServer_ThreadNum))
	{
		return 0;
	}

    //CHECK_RETURN( !bResult, ERNC_SocketStartupError );

    bool bResult = theConfig.Init( szIniFileName );
    if ( !bResult )
    {
        char szContent[256] = {0};
        sprintf_s( szContent, "Config::GetInstance().Init failed [%s]",szIniFileName);
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }

    //try
    //{
    //    LOG_CONFIGURE( theConfig.strLogConfigFilePath.c_str() ); 
    //}
    //catch( ConfigureException& )
    //{   
    //    return false;
    //}

    if( !theXmlString.LoadStringFile( STRINGSLK_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",STRINGSLK_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,STRINGSLK_FILEPATH );
    }

    if ( !theCountryConfig.LoadCountryConfig( COUNTRY_CONFIG ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",COUNTRY_CONFIG);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", COUNTRY_CONFIG );
    }

	//zhuxincong 加载国战胜利奖励
	if (!theCountryReward.LoadCountryConfig(COUNTRY_REWARD))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",COUNTRY_REWARD);
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", COUNTRY_REWARD );
	}


    if ( !theGuildConfig.LoadConfig( GUILDSETTING_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",GUILDSETTING_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", GUILDSETTING_FILEPATH );
    }

	if ( !theGuildMissionConfig.LoadConfigFile( GUILDMISSION_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",GUILDSETTING_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", GUILDSETTING_FILEPATH );
    }

	if ( !theLevelLimitConfig.LoadLevelLimitConfig())
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",CENTERSERVER_LEVELLIMIT_CONFIG );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", CENTERSERVER_LEVELLIMIT_CONFIG );
	}

	// 家族设定
	if ( !theFamilyConfig.LoadConfig( FAMILYSETTING_FILEPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",FAMILYSETTING_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", FAMILYSETTING_FILEPATH );
	}

    if ( !theVarClearConfig.LoadConfig( VARCLEARCONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",VARCLEARCONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", VARCLEARCONFIG_FILEPATH );
    }	

	if ( !theCenterTimeHandleManager.LoadFileConfig( TIMEHANDEL_CONFIG ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",TIMEHANDEL_CONFIG);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", TIMEHANDEL_CONFIG );
    }

	if ( !theBroadCastConfig.LoadBroadCastConfig( BROADCASTCONFIG_FILEPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",BROADCASTCONFIG_FILEPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", BROADCASTCONFIG_FILEPATH );
	}

	if ( !theCenterQuestEntrustManager.GetConfig().LoadQuestEntrustConfig( QUESTENTRUSTCONFIG_FILEPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",QUESTENTRUSTCONFIG_FILEPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", QUESTENTRUSTCONFIG_FILEPATH );
	}

    
    gTrueTime.SetFile( CENTERSERVER_PERFORMANCELOG_FILEPATH );

    //HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );    

    uint32 nResult = theCenterServer.Init( this );
    if ( RESULT_FAILED(nResult ))
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s 初始化失败[%d]", APPLICATION_NAME, nResult );
        return false; 
    }

    theCenterCountryManager.InitCountryName( CountryDefine::Country_LouLan, theXmlString.GetString( eText_Country_LouLan ) );
    theCenterCountryManager.InitCountryName( CountryDefine::Country_KunLun, theXmlString.GetString( eText_Country_KunLun ) );
    theCenterCountryManager.InitCountryName( CountryDefine::Country_DunHuang, theXmlString.GetString( eText_Country_DunHuang ) );

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
                                                "////////////////////");

    //COLOR_MESSAGE( COLOR_GREEN, "[CenterServer OK] \n" );
    _dwStartTime = HQ_TimeGetTime();

    return true;
}

void ConsoleApplication::ProcessKey(DWORD keycode)
{
    static bool s_bCheckCheatOpen = true;

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
				"F9:Graceful Close AllServer shutdown in 60 seconds\n"
				"ESC:Quit the application\n"
                "============================",
                DayNum,HourNum,MinNum,RunTime);
        }
        break;
    case VK_F2:
        {
			int nTotalClientNum   = theClientPeerManager.ClientPeerSize();
			int nNormalClientNum  = theGameServerManager.GetNormalClientNum();
			int nInLoginClientNum = nTotalClientNum - nNormalClientNum +theClientPeerManager.ClientLoginPeerSize();
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"LoginServer[%d] GameServer[%d] RegisedGameServers[%d]\n"
				"TotalClientNum[%d] -NormalClientNum[%d] -InLoginClientNum[%d]\n"
				"ConnectDBServer[%d] IsNeedConnectPlatform[%d]-ConnectPlatform[%d]\n"
				"ListenerPlatformPort[%d] -PlatformConnecterNum[%d]\n"
				"IsOpenQueue[%d] CurOpenNum[%d] FullLoadMaxNum[%d]\n"
				"IsOpenAntiAddiction[%d] IsLogServerService[%d]\n"
				"============================",
				theCenterServer.GetLoginServerCount(),theCenterServer.GetGameServerCount(),theGameServerManager.GetGameServerSize(),
				nTotalClientNum,nNormalClientNum,nInLoginClientNum,
				theCenterServer.IsConnectingDatabaseServer(),theConfig.platform_need,theCenterServer.IsConnectingPlatform(),
				theConfig.listentPortForPlatform,theCenterServer.GetPlatformConnecterSize(),
				theConfig.bOpenService,theConfig.nOpenNum,theConfig.nFullLoadMaxNum,
				theConfig.bOpenAntiAddiction,theConfig.LogServerService);
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
			char szCapabilityInfos[1024] = {0};
			theGameServerManager.Statistics(szCapabilityInfos);
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				" Everyserver Info:\n"
				"%s",szCapabilityInfos);
			{
				CSALocker locker(GetAutoIntLock());
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "[Heap-allocated memory footprint output start:]");
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
				"\t showGSInfo:查看每个SERVER运行的地图信息 \n"
				"\t openqueue:开启排队模式 \n"
				"\t closequeue:开启排队模式 \n"
				"\t setfullload:设置server满载人数\n"
				"\t crash:让server挂掉\n"
				"\t CalcCountryStrength:计算国家实力\n"
				"\t setLoginOneMac:设置单mac登陆数量\n"
				"\t ReloadConfig:热加载配置文件\n"
                "\t exit 退出命令模式 \n"
                "===============================\n";

            std::string strCommand; 
            while( true )
            {
				bool bInvalidCmd = false;
                std::cout << ">>";
                std::cin >> strCommand;
                if(strCommand.compare("exit") == 0)
					break;

                if(strCommand.compare("showGSInfo") == 0)
                {
                    MapInfoContainer mapInfo;
                    theGameServerManager.GetAllMapInfo( mapInfo );
                    for ( MapInfoContainer::iterator it=mapInfo.begin(); it!=mapInfo.end(); ++it)
                    {
						std::cout << "ServerId:["<<(*it).first << "]	MapId:[" 
							<< (*it).second.ulStageId <<"("<<(*it).second.bIsRun<<")]"
							<<"  Playercount:["<<(*it).second.usPlayerCount <<"]"<< std::endl;
                    }
                }
				else if (strCommand == "openqueue")
				{
					theConfig.bOpenService = true;
				}
				else if (strCommand == "closequeue")
				{
					theConfig.bOpenService = false;
					GameServerPeer* pCharacterServer = theGameServerManager.GetCharacterServerPeer();
					if (pCharacterServer)
					{
						MsgCS2GSQueueOp op;
						op._open = false;
						pCharacterServer->Send(&op);
					}
				}
				else if (strCommand == "setfullload")
				{
					std:: cout << "备注：设为0  ->不限人数 \n"
								  "备注：设为>0 ->满载人数 \n"
								  "请输入满载值:\n";
					int nValue = 0;
					std::cin >> nValue;
					std::cin.clear();
					std::cin.sync();
					if ( nValue >= 0 )
					{
						theConfig.nFullLoadMaxNum = nValue;
						std:: cout << "设置满载值成功 \n";
					}
					else
					std:: cout << "无效的满载值 \n";
				}
				else if (strCommand == "setLoginOneMac")
				{
					std:: cout << "备注：设为0  ->不限数量 \n"
								  "备注：设为>0 ->共存数量 \n"
								  "请输入单Mac登陆值:\n";
					int nValue = 0;
					std::cin >> nValue;
					std::cin.clear();
					std::cin.sync();
					if ( nValue >= 0 )
					{
						theConfig.nMaxNumOneMac = nValue;
						std:: cout << "设置单Mac登陆值成功 \n";
					}
					else
						std:: cout << "无效的单Mac登陆值 \n";
				}
                else if ( strCommand == "crash" )
                {
                    char *pCrash = NULL;
                    *pCrash = 1;
                }
				else if (strCommand == "CalcCountryStrength" )
				{
					theCenterCountryManager.CalcCountryStrengthAtOnce();
				}
				else if (strCommand == "ReloadConfig" )
				{
					std:: cout << "Supported config file types as: \n";
					int count = sizeof(g_szResourceCfgPath)/sizeof(char *);
					for (int i = 0 ; i < count ; ++i)
					{
						std:: cout << "type:"<<i<<"-"<<g_szResourceCfgPath[i]<<endl;
					}
					std:: cout << "please input Number: \n";
					int nValue = 0;
					std::cin >> nValue;
					std::cin.clear();
					std::cin.sync();
					if ( nValue >= 0 && nValue < count)
					{
						ConfigReloader::ReloadReqMsg msg;
						msg.nReloadType = nValue;
						theConfigReloader.AddConfigReloadReqMsg(msg);

						MsgCS2GSUpdateReloadCfg msgcfg;
						msgcfg.nReloadType = nValue;
						theGameServerManager.SendMessageToGameServers(&msgcfg,CHARACTERSERVERID);
					}
					else
						std:: cout << "sorry, Inputed error value! \n";
				}
                else if ( strCommand == "setbornmapopen" )
                {
                    int nValue = 0;
                    std::cin >> nValue;
                    std::cin.clear();
                    std::cin.sync();

                    if ( nValue == 0 )
                    {
                        std:: cout << "附加重生点地图 关闭 \n";
                    }
                    else
                    {
                        std:: cout << "附加重生点地图 开启 \n";
                    }

                    theGameServerManager.SetExtendBornMapOpen( nValue == 1 ? true : false );
                }
                else if ( strCommand == "getbornmapopen" )
                {

                    if ( theGameServerManager.GetExtendBornMapOpen() )
                    {
                        std:: cout << "附加重生点地图 开启 \n";
                    }
                    else
                    {
                        std:: cout << "附加重生点地图 关闭 \n";
                    }
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
            s_bCheckCheatOpen = !s_bCheckCheatOpen;

            if ( s_bCheckCheatOpen )
            {
                std::cout << "防外挂机制已开启\n" ;
            }
            else
            {
                std::cout << "防外挂机制已关闭\n" ;
            }

            CS2GSMsgSetCheckCheatOpen xOpen;
            xOpen.bOpen = s_bCheckCheatOpen;
            theGameServerManager.SendMessageToGameServers( &xOpen );
        }
        break;
    case VK_F7:
        {
            if ( s_bCheckCheatOpen )
            {
                std::cout << "防外挂机制 开启状态\n";
            }
            else
            {
                std::cout << "防外挂机制 关闭状态\n";
            }
        }
        break;
    case VK_F8:
        {
            //theServerStatusManager.SetStatus( ServerDataDefine::ReqServerStatus );
        }
        break;
	case VK_F9:
		{
			theCenterServer.bCommandCloseAllServer = true;;
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
    CenterServer::GetInstance().UnInit();

    FreeConsole();

    CoUninitialize();
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
