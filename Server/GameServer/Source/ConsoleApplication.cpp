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
#include "RecipeConfig.h"
#include "StarLevelUpConfig.h"
//#include "TradeCenterConfig.h"
#include "TradeCenterInfo.h"
#include "LuckRewardConfig.h"
#include "SplitItemConfig.h"
#include "TreasureBoxConfig.h"
#include "GameStageConfig.h"
#include "ArmourElementsConfig.h"
#include "EquipUpgradeConfig.h"
#include "SuitOperateConfig.h"
#include "MiniDumper.h"
#include "OnLineRewardConfig.h"
#include "KillMonsterCountConfig.h"
#include "RelationConfig.h"
#include "ItemComposeConfig.h"
#include "CountryConfig.h"
#include "CharacterAttributeConfig.h"
#include "LoginStage.h"
#include "VarClearConfig.h"
#include "CampBattleControl.h"
#include "ServerDefine.h"
#include "XinFaConfig.h"
#include "DaoxingConfig.h"
#include "EquipEvolveConfig.h"
#include "PetSettingConfig.h"
#include "StallConfig.h"
#include "ConfigReloader.h"
#include "MonsterStatusConfig.h"
#include "TalismanConfig.h"
#include "FamilyConfig.h"
#include "PhyleConfig.h"
#include "MonsterGroupManager.h"
#include "ExpActionConfig.h"
#include "ItemHero.h"
#include "TPHJManger.h"
#include "NetWorkParameterDefine.h"
#include "PocketShop.h"
#include "SpecialTask.h"
#include "CountryReward.h"
#include "MountStrengthenConfig.h"
#include "Raise.h"
#include "ChangeCountryConfig.h"
#include "CountryQuestFlyMapConfig.h"
#include "GlobalDBManager.h"
#include "PKConfig.h"
#include "GameTimeHandleManager.h"
#include "WorldBattleManager.h"
#include "EquipScoreRatioConfig.h"
#include "PetDefineConfig.h"
#include "CardIconConfig.h"
#include "CardAchieveConfig.h"
#include "SevenDays.h"
#include "SuitConfig.h"
#include "EffectCharConfig.h"
#include "RankTitleConfig.h"
#include "CreateMonsterConfig.h"
#include "QuestEntrust.h"
#include "HuntingQuestConfig.h"
#include "SoulConfig.h"
#include "ThreeDayConfig.h"
#include "YuanBaoTotleConfig.h"
#include "MountMoveStarConfig.h"
#ifdef NPGUARD
#include "CSAuth.h"
#endif
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
            theRunStatus.SetStatus( RunStatusDefine::RunStatus_PrepareStop );
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"服务器开始停止行为");
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
        std::cout << "初始化失败" << std::endl;
        return;
    }

 /*   if ( !GetDebugMode())
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
#ifdef _DEBUG
	//system( "pause" );
#endif

   // MiniDumper::m_bDebugMode = GetDebugMode();
    CommandLine command;
    char szIniFileName[MAX_PATH] = {0};
    if ( !command.ParseEx( argc, argv, szIniFileName ))
    { 
        char szContent[256] = {0};
        sprintf_s( szContent, "ParseEx failed [%s]",szIniFileName);
        //AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        return false; 
    }
    
  /*  if( !GetMeNetwork().SocketStartUp() )
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
    // 初始化配置文件
    if ( !g_Cfg.InitCommonData( strInitConfigPath.c_str() ) )
    {
        sprintf_s( szContent, "LoadGameSetting failed [%s]",szIniFileName);
       // AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        printf( "InitCommonData %s [Error]", szIniFileName);
        system( "pause" );
        return false;
    }

    if ( !g_Cfg.InitPrivateData( szIniFileName ))
    {
        sprintf_s( szContent, "LoadPrivateGameSetting failed [%s]",szIniFileName);
        //AddToMessageLog( szContent, EVENTLOG_INFORMATION_TYPE );
        printf( "LoadPrivateGameSetting %s [Error]", szIniFileName);
        system( "pause" );
        return false;
    }

    sprintf_s( szContent, sizeof(szContent)-1, GAMESERVER_PERFORMANCELOG_FILEPATH, g_Cfg.szGameServerName);
    gTrueTime.SetFile( szContent );
    //HelperFunc::CreateOutputFolder( OUTPUT_DIRECTORY );

    HelperFunc::CreateOutputFolder( SYSTEM_DIRECTORY );
    sprintf_s( szContent, sizeof ( szContent ) - 1, "%s%s", SYSTEM_DIRECTORY, DATACHUNK_FILEPATH );
    HelperFunc::CreateOutputFolder( szContent );

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

    sprintf_s(szTxtBuf, sizeof(szTxtBuf)-1, "%s [%s:%d] PID[%u] Version[%s]", applicationName.c_str(), g_Cfg.szGameServerName, g_Cfg.dwServerID, 
                                                                              ::GetCurrentProcessId(), ApplicationConfig::Instance().GetFullVersion());
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s 程序启动.",szTxtBuf );
    SetConsoleTitleA(szTxtBuf);

#ifdef USE_APPLICATIONMANAGER
    ApplicationManagerChecker::Instance().IsApplicationManagerOn( "application_manager", GHackWnd );
#endif

#ifdef USE_STRINGLANGUAGE
    long result = StringLanguageTranslator::Instance().LoadStringLanguageInfo( STRING_LANGUAGE_FILENAME );
#endif

    theRunTimeData.serverStartTime = HQ_TimeGetTime();
    
    srand( HQ_TimeGetTime() );
    //MoreAction::Initialize();
    //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init ActionSystem [OK]" );

//     bool bResult = GetGraphicCodeMaker().GenerateImages( GraphicCodeMaker::ECD_GlyphCount );
//     if( !bResult )
//     {
//         LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"GenerateImages %d [Error]", GraphicCodeMaker::ECD_GlyphCount);
//         return false;
//     }
//     else
//     {
//         LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "GenerateImages %d [OK]" ,GraphicCodeMaker::ECD_GlyphCount );
//     }

    //   if (!g_dbchunk.ConnectDB())
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Connect MS Database [Error]");
    //       return false;
    //}
    //else
    //   {
    //       LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Connect MS Database [OK] " );
    //   }

    //   if (!g_dbchunk.LoadChunkMgrDataFromDB())
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Load MS Database ChunkData [Error]");
    //    return false;
    //}
    //else
    //   {
    //       LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load MS Database ChunkData [OK]" );
    //   }

    if( !theExpStage.LoadFromConfig( EXPSTAGE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",EXPSTAGE_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,EXPSTAGE_FILEPATH);
    }

    //if( !GettheItemDetail().LoadBinFile( BINDATA_FILEPATH ) )
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",BINDATA_FILEPATH);
    //    return false;
    //}
    //else
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",BINDATA_FILEPATH );
    //}

    if ( !theRecipeConfig.LoadData( RECIPE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",RECIPE_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",RECIPE_FILEPATH );
    }

    if( !theMapConfig.LoadMapConfig( WORLDMAPCONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"%s [Error]", WORLDMAPCONFIG_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]", WORLDMAPCONFIG_FILEPATH );
    }

    // 人物一级属性升级数值

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
    
    //读取道具相关配置信息
    if (!theItemDetailConfig.InitItemDetail())
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",ITEMDETAILDIRECTORY );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",ITEMDETAILDIRECTORY );
    }

    // 读取心法配置
    if ( !theXinFaConfig.LoadXinFaConfig( XINFACONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Fail]", XINFACONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]", XINFACONFIG_FILEPATH );
    }

    //加载怪物数据
    if (!theItemDetailConfig.LoadXmlMonster(MONSTERCONFIG_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",MONSTERCONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",MONSTERCONFIG_FILEPATH );
    }

    //加载宠物数据
    if (!theItemDetailConfig.LoadXmlPetMonster(PETCONFIG_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",PETCONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",PETCONFIG_FILEPATH );
    }

    //加载坐骑属性
    if (!theItemDetailConfig.LoadXmlMount(MOUNTCONFIG_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",MOUNTCONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",MOUNTCONFIG_FILEPATH );
    }

    //加载装备随机属性
    if (!theItemDetailConfig.LoadXmlRand(EQUIPMENTRANDOM_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",EQUIPMENTRANDOM_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",EQUIPMENTRANDOM_FILEPATH );
    }

	//加载装备强度系数
	if (!theItemDetailConfig.LoadXmlEquipQualityIntensity(EQUIPQUALITYINTENSITY_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",EQUIPQUALITYINTENSITY_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",EQUIPMENTRANDOM_FILEPATH );
	}
    
	
	if ( !theGameTimeHandleManager.LoadFileConfig( TIMEHANDEL_CONFIG ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",TIMEHANDEL_CONFIG);
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", TIMEHANDEL_CONFIG );
    }

    //加载交通的相关信息
    if (!theItemDetailConfig.LoadSlkTraffic(TRAFFIC_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",TRAFFIC_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",TRAFFIC_FILEPATH );
    }

    //加载成就信息
    if (!theAchieveConfig.LoadAchieveConfig(ACHIEVECONFIG_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",ACHIEVECONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",ACHIEVECONFIG_FILEPATH );
    }

    //读取任务信息 
    if(!QuestInfo::Instance().LoadQuest())
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",QUESTS_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",QUESTS_FILEPATH );
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

    if ( !GetRouteManager().LoadRouteInfo( NPCROUTE_FILEPATH ))
    { // 交通路线
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "LoadRouteInfo %s [Error]", NPCROUTE_FILEPATH);
        return false;
    }
    else
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "LoadRouteInfo %s [OK]", NPCROUTE_FILEPATH);
    }
        
    if ( !GetRouteManager().LoadTrafficRoute())
    { // 交通路线
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "LoadTrafficRoute [Error]"); 
        return false;
    }
    else
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "LoadTrafficRoute [OK]"); 
    }
    
    if ( !theTitleConfig.LoadTitleConfig( TITLE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,TITLE_FILEPATH); 
        return false;
    }
    else
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,TITLE_FILEPATH); 
    }

    if ( !thePetSettingConfig.LoadPetSettingConfig( PETSETINGCONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,PETSETINGCONFIG_FILEPATH); 
        return false;
    }
    else
    {   
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]"  ,PETSETINGCONFIG_FILEPATH); 
    }

    //if ( !GettheItemDetail().LoadReputeList( REPUTLIST_FILEPATH ) )
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,REPUTLIST_FILEPATH); 
    //    return false;
    //}
    //else
    //{   
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,REPUTLIST_FILEPATH); 
    //}
    if ( !theStarLevelUpConfig.LoadResourceConfig( STARLEVELUP_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,STARLEVELUP_FILEPATH); 
        return false;
    }
    else
    {
		theStarLevelUpConfig.OnReloadFinished();
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,STARLEVELUP_FILEPATH); 
    } 

	if ( !theMountStrengthenConfig.LoadResourceConfig(MOUNTSTRENGTHEN_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,MOUNTSTRENGTHEN_FILEPATH); 
		return false;
	} 
	else
	{
		theMountStrengthenConfig.OnReloadFinished();
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,MOUNTSTRENGTHEN_FILEPATH); 
	}

	if ( !theEquipScoreRatioConfig.LoadEquipScoreRatioConfig(EQUIPSCORERATIO_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,EQUIPSCORERATIO_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,EQUIPSCORERATIO_FILEPATH); 
	}

	if ( !theCardIconConfig.LoadCardIconConfig(CARDICONDONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,CARDICONDONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,CARDICONDONFIG_FILEPATH); 
	}

	if ( !theCardAchieveConfig.LoadCardAchieveConfig(CARDACHIEVECONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,CARDACHIEVECONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,CARDACHIEVECONFIG_FILEPATH); 
	}

	if ( !theSevenDaysConfig.LoadSevenDaysConfig(SEVENDAYSCONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,SEVENDAYSCONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,SEVENDAYSCONFIG_FILEPATH); 
	}

	if ( !theRankTitleConfig.LoadRankTitleConfig(RANKTITLECONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,RANKTITLECONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,RANKTITLECONFIG_FILEPATH); 
	}

	if ( !theSoulConfig.LoadSoulConfig(SOULCONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,SOULCONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,SOULCONFIG_FILEPATH); 
	}

	if ( !theCreateMonsterConfig.LoadCreateMonsterConfig(CREATEMONSTERCONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,CREATEMONSTERCONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,CREATEMONSTERCONFIG_FILEPATH); 
	}

	if ( !theHuntingQuestConfig.LoadHuntingQuestConfig(HUNTINGQUESTCONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,HUNTINGQUESTCONFIG_FILEPATH); 
		return false;
	} 
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,HUNTINGQUESTCONFIG_FILEPATH); 
	}

    if ( !theLuckRewardConfig.LoadLuckRewardConfig( LUCKREWARD_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,LUCKREWARD_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,LUCKREWARD_FILEPATH); 
    }

    if ( !theTreasureBoxConfig.LoadConfig( TREASUREBOX_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,TREASUREBOX_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,TREASUREBOX_FILEPATH); 
    }

    if ( !theGameStageConfig.LoadGameStageConfig( GAMESTAGE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,GAMESTAGE_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,GAMESTAGE_FILEPATH); 
    }

    //if ( !theArmourElementsConfig.LoadArmourElementsConfig( ARMOURELEMENTS_FILEPATH ) )
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,ARMOURELEMENTS_FILEPATH); 
    //    return false;
    //}
    //else
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,ARMOURELEMENTS_FILEPATH); 
    //}

    if ( !theEquipUpgradeConfig.LoadEquipUpgradeConfig( EQUIPUPGRADE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,EQUIPUPGRADE_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,EQUIPUPGRADE_FILEPATH); 
    }

    if ( !theSuitOperateConfig.LoadSuitLevelUpConfig( SUITOPERATE_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,SUITOPERATE_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,SUITOPERATE_FILEPATH); 
    }

    if ( !theOnLineRewardConfig.LoadOnLineRewardConfig( ONLINEREWARD_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" , ONLINEREWARD_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,ONLINEREWARD_FILEPATH ); 
    }

    if ( ER_Success != theItemSplitConfig.Load( SPLITITEM_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,SPLITITEM_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,SPLITITEM_FILEPATH); 
    }

    if ( !theKillMonsterCountConfig.LoadKillMonsterCountConfig( KILLMONSTERCOUNT_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,KILLMONSTERCOUNT_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,KILLMONSTERCOUNT_FILEPATH); 
    }

    if ( !theRelationConfig.LoadRelationConfig( RELATIONCONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,RELATIONCONFIG_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,RELATIONCONFIG_FILEPATH); 
    }

    if ( !theItemComposeConfig.LoadItemComposeConfig( ITEMCOMPOSECONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,ITEMCOMPOSECONFIG_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,ITEMCOMPOSECONFIG_FILEPATH); 
    }

    if ( !theItemComposeConfig.LoadItemComposeConfig2( ITEMCOMPOSECONFIG_FILEPATH2 ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,ITEMCOMPOSECONFIG_FILEPATH2); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,ITEMCOMPOSECONFIG_FILEPATH2); 
    }

    if ( !theCountryConfig.LoadCountryConfig( COUNTRY_CONFIG ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,COUNTRY_CONFIG); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,COUNTRY_CONFIG); 
    }

	if ( !theChangeCountryConfig.LoadConfigFile() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,COUNTRY_CONFIG); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,COUNTRY_CONFIG); 
    }

	

	if (!theCountryReward.LoadCountryConfig(COUNTRY_REWARD))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,COUNTRY_REWARD); 
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,COUNTRY_REWARD); 
	}

	if (!theRaiseConfig.LoadConfigFile(RAISECONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,RAISECONFIG_FILEPATH); 
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,RAISECONFIG_FILEPATH); 
	}


	if (!theCountryQuestFlyMapConfig.LoadConfigFile(COUNTRYQUESTFLYMAP))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,COUNTRYQUESTFLYMAP); 
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,COUNTRYQUESTFLYMAP); 
	}

	if (!thePKConfig.LoadConfigFile(PKDEFINECONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,PKDEFINECONFIG_FILEPATH); 
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,PKDEFINECONFIG_FILEPATH); 
	}

	if (!theSuitConfig.LoadFilePath(SUITDEFINECONFIG_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,SUITDEFINECONFIG_FILEPATH); 
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,SUITDEFINECONFIG_FILEPATH); 
	}


    if ( !theExpActionConfig.LoadExpActionConfig( EXPACTION_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,EXPACTION_FILEPATH); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,EXPACTION_FILEPATH); 
    }

    // 帮派定义
    if ( !theGuildConfig.LoadConfig( GUILDSETTING_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",GUILDSETTING_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", GUILDSETTING_FILEPATH );
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

	// 种族克制设定
	if ( !thePhyleChastenConfig.LoadConfig( PHYLECHASTEN_FILEPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",PHYLECHASTEN_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", PHYLECHASTEN_FILEPATH );
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

    if ( !theMonsterStatusConfig.LoadConfig( MONSTERSTATUS_FILEPATH ) )
    {
        LogMessage::LogSystemInfo( "Read %s [Error] ", MONSTERSTATUS_FILEPATH );
        return false;
    }
    else
    {
        LogMessage::LogSystemInfo( "Read %s [OK] ", MONSTERSTATUS_FILEPATH );
    }

	//Stiletto Config
	if ( !theEquipEvolveConfig.LoadStilettoConfig( EQUIPSTILETTO_FILEPATH ))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",EQUIPSTILETTO_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", EQUIPSTILETTO_FILEPATH );
	}

	//UnknowIdentify Config
	if ( !theEquipEvolveConfig.LoadUnknowIdentifyConfig( EQUIPUNKNOWIDENTIFY_FILEPATH ))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",EQUIPUNKNOWIDENTIFY_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", EQUIPUNKNOWIDENTIFY_FILEPATH );
	}

	if ( !theEffectCharConfig.LoadEffectCharConfig( EFFECTCHAR_FILEPATH ))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",EFFECTCHAR_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", EFFECTCHAR_FILEPATH );
	}


	//stall Config
	if ( !GetStallConfig().LoadStallConfig( STALLCONFIG_FILEPARTH ))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",STALLCONFIG_FILEPARTH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", STALLCONFIG_FILEPARTH );
	}

    if ( !theTalismanConfig.LoadTalismanConfig( TALISMANCONFIG_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",TALISMANCONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", TALISMANCONFIG_FILEPATH );
    }

	if ( !theMonsterGroupManager.LoadConfig( MONSTERGROUPCONFIG_FILEPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",MONSTERGROUPCONFIG_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", MONSTERGROUPCONFIG_FILEPATH );
	}

	if (!thePetDefineConfig.LoadFileConfigPath(PETDEFINECONFIG_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",PETDEFINECONFIG_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",PETDEFINECONFIG_FILEPATH );
    }
	
	if ( !theGameQuestEntrustManager.GetConfig().LoadQuestEntrustConfig( QUESTENTRUSTCONFIG_FILEPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",QUESTENTRUSTCONFIG_FILEPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", QUESTENTRUSTCONFIG_FILEPATH );
	}

	if ( !ThreeDayConfig::Instance().LoadThreeDayConfig( THREEDAYCONFIGPATH ) )
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",THREEDAYCONFIGPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", THREEDAYCONFIGPATH );
	}

	if(!YuanBaoTotleConfig::Instance().LoadYuanBaoTotleConfig(YUANBAOCONFIGPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,"Read %s [Error]",YUANBAOCONFIGPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ", YUANBAOCONFIGPATH );
	}
   
    //if ( !theGuideQuestConfig.LoadGuideQuestConfig( GUIDEQUEST_FILEPATH ) )
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error]" ,GUIDEQUEST_FILEPATH); 
    //    return false;
    //}
    //else
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK]" ,GUIDEQUEST_FILEPATH); 
    //}

    // GmToolIp列表
    //cGMToolPassIpList::Instance().LoadGmToolIpList( GMTOOLIP_FILEPATH );

    //ShareData::isprocessid = CChangeItemID::Instance().LoadIDChangeList();
    
    DWORD dwError = GettheServer().Init( this );
    if( dwError != ERROR_OK )
    {    
        MessageBox(NULL,"Init GameServer MeNetwork ... ", "Error", MB_OK);
        return false;
    }
    else 
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init GameServer MeNetwork [OK] " );
    }
    
    dwError = GettheServer().Startup();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Begin GameServer MeNetwork [OK] " );    
    if( dwError != ERROR_OK )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, GettheServer().GetFormatErrorString( dwError ) );
        return false;
    }

    if ( !GetDropItemManager().Init() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init DropItemManager [Error]" ); 
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init DropItemManager [OK]"); 
    }
    
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init DropItems [OK] " );

    GetScriptVarMgr();  // 初始化系统变量

    // 初始化所有角本    
    if ( !GetScriptMgr()->InitScripts() )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init Scripts [Error]" ); 
        // return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init Scripts [OK]" ); 
    }
	
	//反外挂
	#ifdef NPGUARD
	if(g_Cfg.IsOpenCSAuth  && CHARACTERSERVERID != g_Cfg.dwServerID)
	{
		if(!CSAuthManager::InitAllCSAuthManager())
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init CSAuth [Error]" ); 
		}
		else
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init CSAuth [OK]" ); 
		}
	}
	#endif
    // 初始化游戏世界时间
    GetGameWorldTimer()->Init(    g_Cfg.m_nYear,
        g_Cfg.m_nMonth,
        g_Cfg.m_nDay,
        g_Cfg.m_nHour,
        g_Cfg.m_nMinute,
        g_Cfg.m_nGameWorldTimerRate,
        g_Cfg.m_szYearName,
        g_Cfg.m_nGameYear );


    // 初始化Avatar配置
    GetAvatarSystemSetting();

    // 初始化邀请代理 邀请的动作后面记在人物身上
    //InviteProxy::Instance();

    // 初始化Npc列表
    if ( theNpcInfo.LoadConfig(NPC_FILEPATH) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init Game World Npc [Error]" );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init Game World Npc [OK]" );
    }

    // 初始化游戏世界
    theGameWorld;
    if ( !theCampBattleControl.InitCampBattleManager() )
    { return false; }
    
    //system( "pause");
    if ( !theGameWorld.InitStages() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init Game World [Fail] " );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init Game World [OK] " );
    }
    
    CChatCheck::getInstance()->LoadUndueString(UNDUEWORD_FILEPATH);
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read UndueWord.slk [OK] " );
    
    //GettheFileDB().SetPath(::g_Cfg.szFileDBPath);
    //if (!GettheFileDB().LoadNoSavedCharList())
    //{
    //    MessageBox( NULL, "Load unsaved character data list failed.", "Game Server", MB_OK | MB_ICONERROR );
    //    return false;
    //}
    //else
    //{
    //    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Init FileDb [OK]" );
    //}
	
	if (!theWorldBattleManager.LoadFilePath(CAMPWORLDBATTLE_FILEPATH))
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load [%s] [Fail]", CAMPWORLDBATTLE_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load [%s] [OK]", CAMPWORLDBATTLE_FILEPATH );
    }

    if ( DataCenter::GetInstance().LoadItemSymbol( ITEM_SYMBOL_FILEPATH ) != ER_Success )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load [%s] [Fail]", ITEM_SYMBOL_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load [%s] [OK]", ITEM_SYMBOL_FILEPATH );
    }

    if ( !theDaoxingConfig.LoadDaoxingConfig( DAOXING_FILEPATH ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load [%s] [Fail]", DAOXING_FILEPATH );
        return false;
    }
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Load [%s] [OK]", DAOXING_FILEPATH );
    }
    
	//加载武将数据
	if (!theItemHero.LoadHeroConfig(ITEMHERO_FILEPATH,ITEMHERO_STRINGPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",ITEMHERO_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",ITEMHERO_FILEPATH );
	}

	//加载太平幻境数据
	if (!theTPHJManager.LoadConifg(TPHJ_FILEPATH,true))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",TPHJ_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",TPHJ_FILEPATH );
	}
	//加载随身商店数据
	if (!thePocketShopManager.LoadConifg(POCKETSHOP_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",POCKETSHOP_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",POCKETSHOP_FILEPATH );
	}

	//特殊任务数据
	if (!TheSpecialTaskMgr.LoadConfig(SPECIALTASK_FILEPATH))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",SPECIALTASK_FILEPATH );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",SPECIALTASK_FILEPATH );
	}


	if (!MountMoveStarConfig::Instance().LoadMountMoveStarConfig(MOUNTMOVESTAR_FILEPATH_CONFIG))
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [Error] ",MOUNTMOVESTAR_FILEPATH_CONFIG );
		return false;
	}
	else
	{
		LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Read %s [OK] ",MOUNTMOVESTAR_FILEPATH_CONFIG );
	}

    theRunTimeData;

	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "\n////////////////////\n"
												"Server Success Start\n"
												"F1 = Show Runing Information\n"
												"F5 = Enter /Commond Mode\n"
												"ESC= Quit the application\n"
												"////////////////////");

	theGameGlobalDBManager.InitGlobalDB();

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
				"IsKickPlayerByCredit:[%s] GameStageNum:[%d] \n"
				"AllTypeCharacter:[%d]\n"
				"OnlinePlayer:[%d] InPlayGamePlayer[%d] MaximalPlayer:[%d]\n"
				"TotalMonstercount:[%d] TotalNPCcount:[%d] TotalItemcharcount:[%d]\n"
				"ConnectDatabaseServer:[%d] ConnectCenterServer:[%d] HaveGateServer:[%d]\n"
				"============================",
				GettheServer().GetServerElapseTime(),GettheServer().GetServerAvgElapseTime(),
				(g_Cfg.iAllAIOpen==0)?"No":"Yes",(g_Cfg.bPKOpen==0)?"No":"Yes",
				(!g_Cfg.bOnlySaveToDBOnExit)?"No":"Yes",g_Cfg.bIsOpenCommand?"Yes":"No",
				(!g_Cfg.bMTStageProcess)?"No":"Yes",
				(!g_Cfg.bKickPlayerByCredit)?"No":"Yes",theGameWorld.GetStageCount(),
				theRunTimeData.GetCharacterCount(),theRunTimeData.GetOnlinePlayer(),
				theRunTimeData.GetEnterWorldOnlinePlayer(),theRunTimeData.GetMaximalOnlinePlayer(),
				theRunTimeData.GetTotalMonster(),theRunTimeData.GetTotalNPC(),theRunTimeData.GetTotalItemchar(),
				g_bDBConnectted, GettheServer().IsCenterServerValidate(), g_GateServerNum);
           /* GameWorld::bShowRunProcessInfo = true;
            gTrueTime.Output();*/
        }
        break;
    case VK_F3:
        {
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO,
				"\n============================\n"
				"%s"
				"\n============================",
				network::net_memory_info());
            /*GameWorld::bShowMemoryInfo = true;*/
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
						 "\t ShowCharMemInfo 查看角色数据结构大小 \n"
						 "\t QuestMemInfo    查看任务数据结构大小 \n"
						 "\t UpdateBodyStatus查看MsgBuffsUpdate数据结构大小 \n"
						 "\t Crash		     尝试挂掉 \n"
						 "\t reloadscript	 重新加载脚本 \n"
						 "\t checkrolemem	 角色分配内存情况 \n"
						 "\t reloaditem 	 重新加载特定类型物品 \n"
						 "\t OpenGMCommand   打开GM命令 \n"
						 "\t CloseGMCommand  关闭GM命令 \n"
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

                if( _stricmp( strCommand.c_str(), "ShowCharMemInfo") == 0 )
                {
                    std::cout << "sizeof(SCharBaseInfo)="    << sizeof(SCharBaseInfo)    / 1024.0 <<  "KB\n"
                              << "sizeof(SCharVisual)="      << sizeof(SCharVisual)      / 1024.0 <<  "KB\n"
                              << "sizeof(SCharOtherData)="   << sizeof(SCharOtherData)   / 1024.0 <<  "KB\n"
                              << "sizeof(SCharItemBagData)=" << sizeof(SCharItemBagData) / 1024.0 <<  "KB\n"
                              << "sizeof(SExtendData)="      << sizeof(SExtendData)      / 1024.0 <<  "KB\n"
                              << "sizeof(SAchieveData)="     << sizeof(SAchieveData)     / 1024.0 <<  "KB\n"
                              << "sizeof(SIdentifyData)="    << sizeof(SIdentifyData)    / 1024.0 <<  "KB\n"
                              << "sizeof(SCharDBInfo)="      << sizeof(SCharDBInfo)      / 1024.0 <<  "KB\n"

                              << "sizeof(SBaseProperty)="    << sizeof(SBaseProperty)             <<  "Byte\n"
                              << "sizeof(SMountItem)="       << sizeof(SMountItem)                <<  "Byte\n"
                              << "sizeof(SPetItem)="         << sizeof(SPetItem)                  <<  "Byte\n"
                              << "sizeof(SCharItem)="        << sizeof(SCharItem)                 <<  "Byte\n"
                              
                              << "sizeof(MsgPlayerEnterMySight)="<< sizeof(MsgPlayerEnterMySight)        <<  "Byte\n"
                              << "sizeof(MsgAckEnterWorld)="     << sizeof(MsgAckEnterWorld)/ 1024.0     <<  "KB\n" 
                              << "sizeof(DBMsgSaveCharacter)="   << sizeof(DBMsgSaveCharacter)/ 1024.0   <<  "KB\n";  

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
                else if ( _stricmp( strCommand.c_str(),"Crash") == 0 )
                {
                    char *pCrash = NULL;
                    *pCrash = 1;
                }
                else if(strCommand == "opengpchk")
                {   
                    //GettheLoginServer().EnableGpCodeCheck(true);
                }
                else if(strCommand == "closegpchk")
                {
                    //std::cout << ">关闭验证码检测" << std::endl;
                    //GettheLoginServer().EnableGpCodeCheck(false);
                }
                else if(strCommand == "openlog")
                {
                    //GettheLoginServer().EnableOut(true);    
                }
                else if(strCommand == "closelog")
                {
                    //GettheLoginServer().EnableOut(false);    
                }
                else if(strCommand == "rs" || strCommand == "reloadscript")
                {
                    GetScriptMgr()->gbNeedReloadScript = true;
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
                    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "角色分配内存情况%s",memortempstring.c_str());
                }
                else if ( _stricmp( strCommand.c_str(),"reloaditem") == 0 )
                {
                    int nSwitch = 0;
                    std::cout << " \n"
                        "0. Restore.config    恢复药品               \n"
                        "1. Equipment.config  装备                   \n"
                        "2. Equipment.config  装备                   \n"
                        "3. Skill.config      技能                   \n"
                        "4. Status.config     状态                   \n"
                        "5. GameAction.config 基本动作               \n"
                        "6. Material.config   原料                   \n"
                        "7. Gem.config        宝石                   \n"
                        "8.                   合成配方               \n"
                        "9. Task.config       任务                   \n"
                        "10.Other.config      其他                   \n"
                        "12.Reel.config       卷轴                   \n"
                        "13.CheckUp.config    鉴定类道具             \n"
                        "14.                  无                     \n"
                        "15.GuildBox.config   鉴定物品表             \n"
                        "16.Special.config    特殊物品               \n"
                        " \n";
                    
                    std::cout << "请选择>>";
                    std::cin >> nSwitch;
                    
                    if (nSwitch >= 0 && nSwitch < ItemDefine::ITEMTYPE_MAX)
                    {
                        theItemDetailConfig.nReloadSignal = CItemDetailConfig::ConfigLoadMode_Reload;
                        theItemDetailConfig.nSwitch = nSwitch;
                    }                    

                }
				else if (_stricmp( strCommand.c_str(),"OpenGMCommand") == 0)
				{
					g_Cfg.bIsOpenCommand = true;
				}
				else if (_stricmp( strCommand.c_str(),"CloseGMCommand") == 0)
				{
					g_Cfg.bIsOpenCommand = false;
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

		case VK_F7:
			GameWorld::bShowRunProcessInfo = true;
			gTrueTime.Output( true );
			break;
			/* case VK_F6:
        {
			GameWorld::bCloseGate = true;
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
    static const int nSleepTime = 1; //g_Cfg.m_bSleepTime;
    Sleep( nSleepTime );
}

long ConsoleApplication::MainLoop()
{
    // 初始化逻辑线程
    _mainLogicThread.CreateThread( MainLogicThreadFunc ) ;//,THREAD_PRIORITY_ABOVE_NORMAL ) )

    _hMainInputThread = GetCurrentThread();

    for(;;)
    {
        //if( theRunStatus.GetStatus() == RunStatusDefine::RunStatus_DBThreadStopped  )
        //    break;

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
    sprintf_s( szFilePath, "%s%s%s.dat", SYSTEM_DIRECTORY, DATACHUNK_FILEPATH, g_Cfg.szGameServerName );
    GetDataChunkMgr()->SaveToFile( szFilePath );
    // Save timer
    g_Cfg.m_nYear = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eYear );
    g_Cfg.m_nMonth = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eMonth );
    g_Cfg.m_nDay = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eDay );
    g_Cfg.m_nHour = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eHour );
    g_Cfg.m_nMinute = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eMinute );
    HelperFunc::SafeNCpy( g_Cfg.m_szYearName,GetGameWorldTimer()->GetYearName(), sizeof( g_Cfg.m_szYearName ) );
    g_Cfg.m_nGameYear = GetGameWorldTimer()->GetCurGameYear();

	#ifdef NPGUARD
	if(g_Cfg.IsOpenCSAuth  && CHARACTERSERVERID != g_Cfg.dwServerID)
		CSAuthManager::CloseAllCSAuthManager();
	#endif

    GettheServer().ShutDown();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "关闭服务器网络服务" ); 

    theLoginStage.UnInit();
    theRunTimeData.ReleaseAllObject();
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "释放所有的对象" ); 
    
    //g_Cfg.Save();
    //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "关闭数据记录" );

    gTrueTime.Output();

    FreeConsole();

    //CoUninitialize();
}

void ConsoleApplication::SetupConsole()
{
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

    m_hIn              = GetStdHandle( STD_INPUT_HANDLE  );

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
