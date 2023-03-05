#include "ConsoleApplication.h"
#include "Configure.h"
#include "ShareData.h"
#include "GameServer.h"
#include "ItemDetailConfig.h"
#include "GameWorldTimer.h"
#include "DBChunk.h"
#include "ShopMgr.h"
#include "XmlStringLanguage.h"
#include "DataChunkMgr.h"
#include "ChatCheck.h"
#include "FileDB.h"
#include "RouteManager.h"
#include "ShopCenterSlk.h"
#include "applicationmanager_checker.h"
#include "ResourcePath.h"
#include "TimeClock.h"
#include "DropItemManager.h"
#include "GameWorld.h"
#include "NpcBaseEx.h"
#include "AvatarSystemSetting.h"
#include "ExpStage.h"
#include "ScriptvarMgr.h"
#include "application_config.h"
#include "DataCenter.h"
#include "StageMonitor.h"
#include "QuestData.h"
#include "MapConfig.h"
#include "CommandLine.h"
#include "RunStatus.h"
#include "MiniDumper.h"
#include "CountryConfig.h"
#include "CharacterAttributeConfig.h"
#include "RewardProfessionItemConfig.h"
#include "GuildConfig.h"
#include "LoginStage.h"
#include "ServerDefine.h"
#include "PhyleConfig.h"
#include "ColorScreen.h"
#include "NetWorkParameterDefine.h"
#include "CountryReward.h"

ConsoleApplication* gConsoleApplication = NULL;

ConsoleApplication::ConsoleApplication(bool isdebug):_debugmode(isdebug)/* : NTService( APPLICATION_NAME, APPLICATION_NAME )*/
{
    m_hIn = 0;
    gConsoleApplication = this;
}

ConsoleApplication::~ConsoleApplication()
{

}

void CloseServerProcess()
{   
    if ( RunStatusDefine::RunStatus_PrepareStop == theRunStatus.GetStatus() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"�Ѿ�����׼���˳��׶�");
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
            theRunStatus.SetStatus( RunStatusDefine::RunStatus_PrepareStop );
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"��������ʼֹͣ��Ϊ");
        }
    }
    else
    {
        theRunStatus.SetStatus( RunStatusDefine::RunStatus_PrepareStop );
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
        std::cout << "��ʼ��ʧ��" << std::endl;
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
    SetupConsole();
    CommandLine command;

  //  MiniDumper::m_bDebugMode = GetDebugMode();
    char szIniFileName[MAX_PATH] = {0};
    if ( !command.ParseEx( argc, argv, szIniFileName ))
    { 
        char szContent[256] = {0};
        sprintf_s( szContent, "ParseEx failed [%s]",szIniFileName);
        //AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false; 
    }

    /*if( !GetMeNetwork().SocketStartUp() )
    { return false; }*/
	if (!network::net_init(eN_GameServer_BigBufferSize,
						   eN_GameServer_BigBufferNum,
						   eN_GameServer_SmallBufferSize,
						   eN_GameServer_SmallBufferNum,
						   eN_GameServer_ListenNum,
						   eN_GameServer_SocketNum,
						   eN_GameServer_ThreadNum))
	{
		return 0;
	}

    char szContent[256] = {0};
    Common::_tstring strInitConfigPath = szIniFileName;
    strInitConfigPath = strInitConfigPath.substr(0,strInitConfigPath.find_last_of("\\")+1);
    strInitConfigPath += GAMESERVER_COMMON_CONFIGNAME;
    // ��ʼ�������ļ�
    if ( !g_Cfg.InitCommonData( strInitConfigPath.c_str() ) )
    {
        sprintf_s( szContent, "LoadGameSetting failed [%s]",szIniFileName);
      //  AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }

    if ( !g_Cfg.InitPrivateData( szIniFileName ))
    {
        sprintf_s( szContent, "LoadPrivateGameSetting failed [%s]",szIniFileName);
        //AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false;
    }

    g_Cfg.dwServerID = CHARACTERSERVERID;

    sprintf_s( szContent, sizeof(szContent)-1, LOGINGAMESERVER_PERFORMANCELOG_FILEPATH );
    gTrueTime.SetFile( szContent );
    //HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );

    //try
    //{
    //    LOG_CONFIGURE(g_Cfg.strLogConfigFilePath.c_str() );        
    //}
    //catch(ConfigureException &e)
    //{   
    //    return false;
    //}

    char szTxtBuf[128] = {0};
    std::string applicationName = APPLICATION_NAME;
#ifdef _DEBUG
    applicationName += "-Debug";
#endif
    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s ServerId[%d] PID[%u] Version[%s]", applicationName.c_str(), g_Cfg.dwServerID,::GetCurrentProcessId(), ApplicationConfig::Instance().GetFullVersion());
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s ��������.",szTxtBuf );
    SetConsoleTitleA(szTxtBuf);

#ifdef USE_APPLICATIONMANAGER
    //ApplicationManagerChecker::Instance().IsApplicationManagerOn( "application_manager", GHackWnd );
#endif

#ifdef USE_STRINGLANGUAGE
    //long result = StringLanguageTranslator::Instance().LoadStringLanguageInfo( STRING_LANGUAGE_FILENAME );
#endif

    theRunTimeData.serverStartTime = HQ_TimeGetTime();
    
    srand( HQ_TimeGetTime() );
//     bool bResult = GetGraphicCodeMaker().GenerateNumImages( GraphicCodeMaker::ECD_GlyphCount );
//     if( !bResult )
// 	{
// 		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"GenerateImages %d [Error]", GraphicCodeMaker::ECD_GlyphCount);
// 		return false;
// 	}
// 	else
//     {
//         LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "GenerateImages %d [OK]" ,GraphicCodeMaker::ECD_GlyphCount );
//     }

     // ����һ������������ֵ
    uint32 nResult = theCharacterAttributeConfig.LoadLevelBaseSecondAttribute(CHARACTERBASESECONDATTRIBUTE_FILEPATH);
    if ( RESULT_FAILED(nResult) )
    {
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",CHARACTERBASESECONDATTRIBUTE_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [OK]",CHARACTERBASESECONDATTRIBUTE_FILEPATH);
    }

    nResult = theDataCenter.LoadArmsParamModulus(PARAMMODULUS_FILEPATH);
    if ( RESULT_FAILED(nResult) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",PARAMMODULUS_FILEPATH);
		return false;
	}
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]",PARAMMODULUS_FILEPATH);
    }

    //��ȡ�������������Ϣ
    if (!theItemDetailConfig.InitItemDetail())
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",ITEMDETAILDIRECTORY );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",ITEMDETAILDIRECTORY );
    }

    if( !theXmlString.LoadStringFile( STRINGSLK_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",STRINGSLK_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,STRINGSLK_FILEPATH );
    }
    
    if ( !CChatCheck::getInstance()->LoadUndueString(UNDUEWORD_FILEPATH) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",UNDUEWORD_FILEPATH);
        return false;
        
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", UNDUEWORD_FILEPATH );
    }

    if( !theExpStage.LoadFromConfig( EXPSTAGE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",EXPSTAGE_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,EXPSTAGE_FILEPATH);
    }

    if ( !CChatCheck::getInstance()->LoadSpecialCharFilterString(SPECIALCHARFILTER_FILEPATH) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",SPECIALCHARFILTER_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", SPECIALCHARFILTER_FILEPATH );
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

	if (!theCountryReward.LoadCountryConfig(COUNTRY_REWARD))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",COUNTRY_REWARD);
		return false;
	}
	else
	{
		 LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", COUNTRY_REWARD );
	}

    //���͵���
    if ( !theRewardProfessionItemConfig.LoadRewardProfessionItemConfig( REWARDPROFESSIONITEM_CONFIG ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",REWARDPROFESSIONITEM_CONFIG );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", REWARDPROFESSIONITEM_CONFIG );
    }
    
    DWORD dwError = GettheServer().Init( this );
    if( dwError != ERROR_OK )
    {	
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Init %s MeNetwork ... ", APPLICATION_NAME);
        return false;
    }
    else 
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init %s MeNetwork [OK] ", APPLICATION_NAME );
    }
    
    dwError = GettheServer().Startup();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Begin %s MeNetwork [OK] ", APPLICATION_NAME );
    if( dwError != ERROR_OK )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, GettheServer().GetFormatErrorString( dwError ) );
        return false;
    }

    // ��ʼ����Ϸ����ʱ��
    GetGameWorldTimer()->Init(	g_Cfg.m_nYear, g_Cfg.m_nMonth, g_Cfg.m_nDay,
        g_Cfg.m_nHour, g_Cfg.m_nMinute, g_Cfg.m_nGameWorldTimerRate, g_Cfg.m_szYearName, g_Cfg.m_nGameYear );
    
    // ��ʼ��Avatar����
    GetAvatarSystemSetting();

    theRunTimeData;

    // ��ɫ�����������Ϳ�ʼ�����������޷ֲ�ʽ��ǰ������
    theRunStatus.SetStatus( RunStatusDefine::RunStatus_Running );  

	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "\n////////////////////\n"
												"Server Success Start\n"
												"F1 = Show Runing Information\n"
												"F5 = Enter /Commond Mode\n"
												"ESC= Quit the application\n"
												"////////////////////");
    
    COLOR_MESSAGE( COLOR_GREEN, "[CharacterServer OK] \n" );
    return true;
}

void ConsoleApplication::ProcessKey(DWORD keycode)
{
    switch(keycode)
    {
    case VK_F1:
        {
			int RunTime = (HQ_TimeGetTime() - GettheServer().GetStartTime())/1000;
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
				"Disposal time:[%d]  Average time:[%d]\n"
				"IsOpenMonsterAI:[%s]  IsOpenPK:[%s]  \n"
				"IsOnlySaveToDBOnExit:[%s]  IsOpenGMCommand:[%s]  \n"
				"MultiThreadRefreshStages:[%s]\n"
				"IsKickPlayerByCredit:[%s] \n"
				"AllTypeCharacter:[%d]\n"
				"OnlinePlayer:[%d] InPlayGamePlayer[%d] MaximalPlayer:[%d]\n"
				"ConnectDatabaseServer:[%d] ConnectCenterServer:[%d] HaveGateServer:[%d]\n"
				"============================",
				GettheServer().GetServerElapseTime(),GettheServer().GetServerAvgElapseTime(),
				(g_Cfg.iAllAIOpen==0)?"No":"Yes",(g_Cfg.bPKOpen==0)?"No":"Yes",
				(!g_Cfg.bOnlySaveToDBOnExit)?"No":"Yes",g_Cfg.bIsOpenCommand?"Yes":"No",
				(!g_Cfg.bMTStageProcess)?"No":"Yes",
				(!g_Cfg.bKickPlayerByCredit)?"No":"Yes",
				theRunTimeData.GetCharacterCount(),theRunTimeData.GetOnlinePlayer(),
				theRunTimeData.GetEnterWorldOnlinePlayer(),theRunTimeData.GetMaximalOnlinePlayer(),
				g_bDBConnectted, GettheServer().IsCenterServerValidate(), g_GateServerNum);

            //GameWorld::bShowRunProcessInfo = true;
        }
        break;
    case VK_F3:
        {
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"%s"
				"\n============================",
				network::net_memory_info());
            //GameWorld::bShowMemoryInfo = true;
        }
        break;
    case VK_F4:
        {
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"\n============================");
			{
				CSALocker locker(GetAutoIntLock());
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "[Heap-allocated memory footprint output start:]");
				uint32 nAllMemory = 0;
				for (map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().begin(); itr != GetAllocInfo().end(); ++itr)
				{
					nAllMemory += itr->second.nAllUseMemory;
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, 
						"%-52s\n"
						"ռ���ڴ� [%-18d] �ֽ�"
						"Ŀǰδ�ͷŹ����� [%-6d] ��"
						"��ʷ����[%-6d]��", 
						itr->first!=NULL?itr->first:"δ������;", itr->second.nAllUseMemory, 
						itr->second.nExistCount, itr->second.nAllocCount );
				}
				LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ȫ�������ڴ�[%d]Byte | [%d]MByte", nAllMemory, nAllMemory/(1024*1024) );
			}
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"\n============================");
        }
        break;
    case VK_F5:
        {
            std::cout << "===============================\n"
                         "��������ģʽ \n"
						 "\t ShowCharMemInfo �鿴��ɫ���ݽṹ��С \n"
						 "\t QuestMemInfo    �鿴�������ݽṹ��С \n"
						 "\t UpdateBodyStatus�鿴MsgBuffsUpdate���ݽṹ��С \n"
						 "\t EnterTheWorld   �鿴SCharInfoClient-SCharItemBagData���ݽṹ��С \n"
						 "\t Crash		     ���Թҵ� \n"
						 "\t reloadscript	 ���¼��ؽű� \n"
						 "\t checkrolemem	 ��ɫ�����ڴ���� \n"
						 "\t reloaditem 	 ���¼����ض�������Ʒ \n"
                         "\t exit �˳�����ģʽ \n"
                         "===============================\n";

            std::string strCommand; 
	        while( true )
	        {
		        std::cout << ">>";
		        std::cin >> strCommand;
				bool bInvalidCmd = false;
		        if(strCommand.compare("exit") == 0)
					break;

		        if( _stricmp( strCommand.c_str(), "ShowCharMemInfo") == 0 )
		        {
                    std::cout << "sizeof(SCharBaseInfo)="    << sizeof(SCharBaseInfo)    / 1024.0 <<  "k\n"
                              << "sizeof(SCharVisual)="      << sizeof(SCharVisual)      / 1024.0 <<  "k\n"
                              << "sizeof(SCharOtherData)="   << sizeof(SCharOtherData)   / 1024.0 <<  "k\n"
                              << "sizeof(SCharItemBagData)=" << sizeof(SCharItemBagData) / 1024.0 <<  "k\n"
                              << "sizeof(SCharDBInfo)="      << sizeof(SCharDBInfo)      / 1024.0 <<  "k\n";
		        }
                else if ( _stricmp( strCommand.c_str(), "QuestMemInfo") == 0 )
                {
                    std::cout << "sizeof(SQuest)=" << sizeof(SQuest) / 1024.0 << "\n"
                              << std::endl;
                }
                else if ( _stricmp( strCommand.c_str(), "UpdateBodyStatus") == 0 )
                {
                    std::cout << "sizeof(MsgBuffsUpdate)=" << sizeof(MsgBuffsUpdate) / 1024.0 << "\n"
                              << std::endl;
                    
                }
                else if ( _stricmp( strCommand.c_str(), "EnterTheWorld") == 0 )
                {
                    std::cout << "sizeof(SCharInfoClient)=" << sizeof(SCharInfoClient) / 1024.0 << "\n"
                              << std::endl;

                    
                    std::cout << "sizeof(SCharItemBagData)=" << sizeof(SCharItemBagData) / 1024.0 << "\n"
                              << std::endl;
                    
                }
				else if ( _stricmp( strCommand.c_str(),"Crash") == 0 )
				{
					char *pCrash = NULL;
					*pCrash = 1;
				}
				else if (strCommand == "checkrolemem")
				{
					std::string memortempstring( "" );
					const char* debugMem = theRunTimeData.theCharacters.GetUseStateMemory();
					for (int k = 0;k<=theRunTimeData.theCharacters.GetSize();k++)
					{
						if (debugMem[k] == 0)
						{
							memortempstring+='0';
						}
						else
						{
							memortempstring+='1';
						}
					}
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "��ɫ�����ڴ����%s",memortempstring.c_str());
				}
                else if ( _stricmp( strCommand.c_str(),"ReloadItem") == 0 )
                {
                    int nSwitch = 0;
                    std::cout << " \n"
                        "0. Restore.config    �ָ�ҩƷ               \n"
                        "1. Equipment.config  װ��                   \n"
                        "2. Equipment.config  װ��                   \n"
                        "3. Skill.config      ����                   \n"
                        "4. Status.config     ״̬                   \n"
                        "5. GameAction.config ��������               \n"
                        "6. Material.config   ԭ��                   \n"
                        "7. Gem.config        ��ʯ                   \n"
                        "8.                   �ϳ��䷽               \n"
                        "9. Task.config       ����                   \n"
                        "10.Other.config      ����                   \n"
                        "12.Reel.config       ����                   \n"
                        "13.CheckUp.config    ���������             \n"
                        "14.                  ��                     \n"
                        "15.GuildBox.config   ������Ʒ��             \n"
                        "16.Special.config    ������Ʒ               \n"
                        " \n";

                    std::cout << "��ѡ��>>";
                    std::cin >> nSwitch;

                    if (nSwitch >= 0 && nSwitch < ItemDefine::ITEMTYPE_MAX)
                    {
                        theItemDetailConfig.nReloadSignal = CItemDetailConfig::ConfigLoadMode_Reload;
                        theItemDetailConfig.nSwitch = nSwitch;
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
    /*case VK_F6:
        {
            if ( g_Cfg.bIsOpenRobotCmd )
                std::cout << "Open Robot Command !" << std::endl;
            else
                std::cout << "Close Robot Command !"<< std::endl;
        }
        break;*/
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
    GettheServer().RunOneStep();
    static const int nSleepTime = 1;//g_Cfg.m_bSleepTime;
    Sleep( nSleepTime );
}

long ConsoleApplication::MainLoop()
{
    // ��ʼ���߼��߳�
    _mainLogicThread.CreateThread( MainLogicThreadFunc ) ;//,THREAD_PRIORITY_ABOVE_NORMAL ) )

    _hMainInputThread = GetCurrentThread();

    for(;;)
    {
        //if( theRunStatus.GetStatus() == RunStatusDefine::RunStatus_DBThreadStopped  )
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
    GetScriptVarMgr()->SaveVar();
    GetShopMgr()->SaveData();
    // g_dbchunk.SaveChunkMgrDataToDB();
    char szFilePath[512] = {0};
    sprintf_s( szFilePath, sizeof( szFilePath ) - 1, "%s%s%s.dat", SYSTEM_DIRECTORY, DATACHUNK_FILEPATH, g_Cfg.szGameServerName );
    GetDataChunkMgr()->SaveToFile( szFilePath );
    // Save timer
    g_Cfg.m_nYear = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eYear );
    g_Cfg.m_nMonth = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eMonth );
    g_Cfg.m_nDay = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eDay );
    g_Cfg.m_nHour = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eHour );
    g_Cfg.m_nMinute = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eMinute );
    HelperFunc::SafeNCpy( g_Cfg.m_szYearName,GetGameWorldTimer()->GetYearName(), 32 );
    g_Cfg.m_nGameYear = GetGameWorldTimer()->GetCurGameYear();
       
    GettheServer().ShutDown();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "�رշ������������" ); 

    theLoginStage.UnInit();

    theRunTimeData.ReleaseAllObject();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "�ͷ����еĶ���" ); 
    
    //g_Cfg.Save();
    //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "�ر����ݼ�¼" );

    gTrueTime.Output();

    FreeConsole();

    //CoUninitialize();
}

void ConsoleApplication::SetupConsole()
{
    ShowWindow( GetConsoleWindow(), SW_SHOWMAXIMIZED );

    m_hIn = GetStdHandle ( STD_INPUT_HANDLE  );

    // prevent mouse input( it may cause some error )
    {
        DWORD dwMode = 0;
        GetConsoleMode( m_hIn, &dwMode);
        dwMode &= ~ENABLE_MOUSE_INPUT;
        SetConsoleMode( m_hIn, dwMode);
    }

    // �رա���ť ��ֹ����
    HWND hWnd = GetConsoleWindow();  
    if(hWnd)  
    {  
        HMENU hMenu = GetSystemMenu(hWnd, FALSE);  
        EnableMenuItem(hMenu, SC_CLOSE, MF_DISABLED | MF_BYCOMMAND);  
    }

    //
    // ע�ᴦ�����̨��Ϣ�ص�����
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
