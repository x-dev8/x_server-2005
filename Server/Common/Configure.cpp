#include "Configure.h"
#include "ResourcePath.h"
//#include "NetApi.h"
#include "Tinyxml/tinyxml.h"
#include "tstring.h"

Configure g_Cfg;

Configure::Configure()
{
    memset( this, 0, sizeof( Configure ) );

    m_bSleepTime   = false;
    bIsOpenCommand = false;

    m_fMinModelPercent = 0.9f;
    m_fMaxModelPercent = 1.1f;

    memset( m_iBornOpen, 0, sizeof( m_iBornOpen ) );
    m_iBornOpen[0] = 1;

    bHaveGetAntiAddictionInfoConfig = false;
    bIsOpenAntiAddiction = false;
    memset( &xAntiAddictionInfo, 0, sizeof(xAntiAddictionInfo) );
    isSendChatToCenter = false;
    nAntiAddictionSaveTime = 10;
    
    isSendChatToCenter = false;
    //memset( szAccountServerIP, 0, sizeof(szAccountServerIP));
    //wAccountServerPort = 0;

    memset( szLogServerIp, 0, sizeof(szLogServerIp));
    iLogServerPort = 0;
	bOpenLogService = false;

    ustPrivateChatLevel = 15;
    minuteOfflineHookMoney = 0;
    bOpenAchievement    = false;
    bOpenOnlineReward   = false;

    itemDropDelaySecond = 0;
    petBreedIntervalTime= 0;
    petBreedFailedTime  = 0;

    iAllAIOpen      = false; 
//    bMTRefMonster   = false;
    bAIFindParth    = false;

	nDropExp = 0.0f;
	nDropHonour = 0;

}

void Configure::ReLoadSome()
{
}

bool Configure::InitCommonData(const char* szGamesettingPath)
{
    if ( !szGamesettingPath)
    { return false; }

    TiXmlDocument doc;
    if (!doc.LoadFile(szGamesettingPath))
    { return false; }
    
    int    nValue = 0;
    double dValue = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( !pProject )
    { return false; }

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( !pSetting)
    { return false; }

    TiXmlElement* pSystem = pSetting->FirstChildElement("System");
    if ( !pSystem )
    { return false; }
    
    TiXmlElement* pGameTime = pSetting->FirstChildElement("GameTime");
    if ( !pGameTime)
    { return false; }

    szTemp = pGameTime->Attribute("YearName");
    if (!szTemp)
    { return false; }
    strncpy_s( m_szYearName, szTemp, sizeof(m_szYearName) );

    pGameTime->Attribute("Year", &nValue );
    m_nYear = nValue;
    
    pGameTime->Attribute("Month", &nValue );
    m_nMonth = nValue;

    pGameTime->Attribute("Day", &nValue );
    m_nDay = nValue;

    pGameTime->Attribute("Hour", &nValue );
    m_nHour = nValue;

    pGameTime->Attribute("Minute", &nValue );
    m_nMinute = nValue;

    pGameTime->Attribute("RealLifeRate", &nValue );
    m_nGameWorldTimerRate = nValue;

    pGameTime->Attribute("CurYear", &nValue );
    m_nGameYear = nValue;

    TiXmlElement* pAntiPlugin = pSetting->FirstChildElement("AntiPlugin");
    if ( !pAntiPlugin)
    { return false; }

    pAntiPlugin->Attribute("IsOpen", &nValue );
    bAntiPluginOpen = ( nValue != 0 ) ? true : false;
    
    pAntiPlugin->Attribute("CheckTimeInFight", &nValue);
    dwCheckWhenFightingTime = nValue;

    pAntiPlugin->Attribute("IsKickCheater", &nValue);
    m_bIsKickCheater = (nValue != 0) ? true : false;

    pAntiPlugin->Attribute("MaxCheckFailCount", &nValue);
    nMaxCheckFailCount = nValue;

    pAntiPlugin->Attribute("FailBlockTime", &nValue);
    graphicValidFailBlockTime = nValue;

    pAntiPlugin->Attribute("OnMapLimitTime", &nValue);
    onMapLimitTime = nValue;

    pAntiPlugin->Attribute("PlayerApplyTime", &nValue);
    dwPlayerApplyTime = nValue;
    
    TiXmlElement* pPK = pSetting->FirstChildElement("PK");
    if ( !pPK)
    { return false; }
    
    pPK->Attribute("IsOpen", &nValue );
    bPKOpen = nValue != 0 ? true : false;
    
    pPK->Attribute("FirstKillRate", &nValue );
    m_nFirstKill = nValue;

    pPK->Attribute("SecondKillRate", &nValue );
    m_nSecondKill = nValue;

    pPK->Attribute("ThirdKillRate", &nValue );
    m_nThirdKill = nValue;

    pPK->Attribute("MoreKillRate", &nValue );
    m_nMoreKill = nValue;
    
    pPK->Attribute("RefreshTimeOnKillTheSameOne", &nValue );
    m_dwRefreshKillTime = nValue;
    
    pPK->Attribute("PkValueMaxPerDay", &nValue );
    nMaxDailyPKValue = nValue;

    TiXmlElement* pDuel = pSetting->FirstChildElement("Duel");
    if ( !pDuel)
    { return false; }
    
    pDuel->Attribute("HpRestoreRate", &nValue );
    nDulEndHpper = nValue;

    //pDuel->Attribute("OutProtectTime", &nValue );
    //protecttime = nValue;

    pDuel->Attribute("ProtectStatus", &nValue);
    nProtectStatusId = nValue;

    pDuel->Attribute("ProtectStatusLevel", &nValue);
    nProtectStatusLevel = nValue;
    
	pDuel->Attribute("ChannelStatus", &nValue);
	nChannelStatusId = nValue;

	pDuel->Attribute("ChannelStatusLevel", &nValue);
	nChannelStatusLevel = nValue;

    TiXmlElement* pMonster = pSetting->FirstChildElement("Monster");
    if ( !pMonster)
    { return false; }

    pMonster->Attribute("IsAIOpen", &nValue );
    iAllAIOpen = nValue;

//     pMonster->Attribute("IsMultiThreadRefresh", &nValue );
//     bMTRefMonster = nValue != 0 ? true : false ;

    pMonster->Attribute("AIFindParth", &nValue );
    bAIFindParth = nValue;
    
    TiXmlElement* pPlayer = pSetting->FirstChildElement("Player");
    if ( !pPlayer)
    { return false; }
    
    pPlayer->Attribute("OnlineMax", &nValue );
    iOnlineMax = nValue;

    pPlayer->Attribute("LevelLimit", &nValue );
    m_nLevelLimt = nValue;

    pPlayer->Attribute("PKProtectLevel", &nValue);
    m_nPKProtectLevel = (nValue == 0 ? PKProtectLevel : nValue);
    
    pPlayer->Attribute("PrivateShopLevel", &nValue);
    m_nPrivateShopLevel = (nValue == 0 ? PKProtectLevel : nValue);

    pPlayer->Attribute("BeRelivePkValue", &nValue );
    beRelivePkValue = nValue;

    pPlayer->Attribute("SkillExpLimit", &nValue );
    m_nSkillExpLimt = nValue;

    pPlayer->Attribute("MoneyLimit", &nValue );
    m_nMoneyMax = nValue;

    pPlayer->Attribute("JiaoZiLimit", &nValue );
    m_nMaxJiaoZi = nValue;
    
    pPlayer->Attribute("SaveDelay", &nValue );
    dwAutoSaveDelay = nValue;

    pPlayer->Attribute("OnlySaveToDBOnExit", &nValue );
    bOnlySaveToDBOnExit = nValue != 0 ? true : false;
    
    pPlayer->Attribute("NormalBagInitSize", &nValue );
    m_nCreatBagSize = nValue;

    pPlayer->Attribute("MaterialBagInitSize", &nValue );
    m_nCreateMaterialSize = nValue;

    pPlayer->Attribute("StorageItemInitGrid", &nValue );
    m_nStorageItemGrid = nValue;

    pPlayer->Attribute("StorageMountInitGrid", &nValue );
    m_nStorageMountGrid = nValue;

    pPlayer->Attribute("LockItemLimt", &nValue );
    m_nLockItemLimt = nValue;

    pPlayer->Attribute("SitdownRestorePer", &nValue );
    m_SitdownRestorePer = (float)nValue/DEF_PER;;

    pPlayer->Attribute("RestoreCheckTime", &nValue );
    nCharHPRestoreCheck = nValue;

    pPlayer->Attribute("WarriorMPCheckTime", &nValue );
    nCharMPCheckTime[EArmType_Warrior] = nValue;

    pPlayer->Attribute("MageMPCheckTime", &nValue );
    nCharMPCheckTime[EArmType_Mage] = nValue;

    pPlayer->Attribute("TaoistMPCheckTime", &nValue );
    nCharMPCheckTime[EArmType_Taoist] = nValue;

    pPlayer->Attribute("AssassinMPCheckTime", &nValue );
    nCharMPCheckTime[EArmType_Assassin] = nValue;

    pPlayer->Attribute("HunterMPCheckTime", &nValue );
    nCharMPCheckTime[EArmType_Hunter] = nValue;

    pPlayer->Attribute("SniperMPCheckTime", &nValue );
    nCharMPCheckTime[EArmType_Sniper] = nValue;

    pPlayer->Attribute("IntegralMaxByItem", &nValue );
    m_nIntegralMaxByItem = nValue;

    pPlayer->Attribute("XPRestoreCheckTime", &nValue );
    nCharXPRestoreCheck = nValue;

    pPlayer->Attribute("AfkTime", &nValue );
    m_nTimeInAfk = nValue;

    pPlayer->Attribute("IsHighShoutTimeLimit", &nValue );
    bHighShoutTimeLimit = nValue;

    pPlayer->Attribute("HighShoutTimeInterval", &nValue );
    nHighShoutPerTime = nValue;

    pPlayer->Attribute("HighShoutLevelLimit", &nValue);
    nHighShoutLevelLimit = nValue;

    pPlayer->Attribute("HighShoutCostMoney", &nValue);
    nHighShoutCostMoney = nValue;

    pPlayer->Attribute("OffHookMinNeedMoney1", &nValue);
    minuteOfflineHookMoney = nValue;
    
    double fPercent;
    if ( pPlayer->Attribute( "MinModelPercent", &fPercent ) != NULL )
    { m_fMinModelPercent = fPercent; }

    if ( pPlayer->Attribute( "MaxModelPercent", &fPercent ) != NULL )
    { m_fMaxModelPercent = fPercent; }

    if ( pPlayer->Attribute( "ExchangeJindingLevelLimit", &nValue ) != NULL )
    { exchangeJindingLevelLimit = nValue; }

    isTakeMoneyCorrect = false;
    if ( pPlayer->Attribute( "IsTakeMoneyCorrect", &nValue ) != NULL )
    { isTakeMoneyCorrect = nValue==1? true : false; }

    if ( pPlayer->Attribute( "PrivateChatLevel", &nValue ) != NULL )
    { ustPrivateChatLevel = nValue; }

    TiXmlElement* pGameWorld = pSetting->FirstChildElement("GameWorld");
    if ( !pGameWorld)
    { return false; }
    
    pGameWorld->Attribute("IsMultiThreadProcess", &nValue );
    bMTStageProcess = nValue != 0 ? true : false;

    pGameWorld->Attribute("GoldCovSilver", &nValue );
    m_nGlodCovSilver = nValue;

    pGameWorld->Attribute("MonsterNumber", &nValue );
    iMonsterNumber = nValue;

    pGameWorld->Attribute("KickPlayerByCredit", &nValue );
    bKickPlayerByCredit = nValue !=0 ? true : false;

    pGameWorld->Attribute("ReliveOriginAllHpMp", &nValue );
    m_nReliveOriginAllHpMp = nValue;

    pGameWorld->Attribute("ReliveOriginNon", &nValue );
    m_nReliveOriginNon = nValue;

    pGameWorld->Attribute("RePairCost", &nValue );
    m_nReqairRmb = nValue;

    pGameWorld->Attribute("StageThreadSleep", &nValue );
	dwMapThreadSleep = nValue>1 ? nValue : 1;

    pGameWorld->Attribute("IsDisableChatofWorld", &nValue );
    bDisableChatofWorld = nValue !=0 ? true : false;

    pGameWorld->Attribute("LockIntensifyRMB", &nValue );
    m_nLockIntensifySilver = nValue;

    pGameWorld->Attribute("ShopCenterOffSet", &nValue );
    m_nOffSetInShopCenter = nValue;
    bIsChangedShopCenterOff = false;

    pGameWorld->Attribute("GlobalDropRate", &dValue );
    m_fGlobalDropRate = dValue;

    pGameWorld->Attribute("WeaponDropHp", &nValue );
    nWeaponDropHp = nValue;

    pGameWorld->Attribute("ArmourDropHp", &nValue );
    nArmourDropHp = nValue;

    pGameWorld->Attribute("DeathEquipDropHpMin", &nValue );
    nDeathEquipDropHpMin = nValue;

    pGameWorld->Attribute("DeathEquipDropHpMax", &nValue );
    nDeathEquipDropHpMax = nValue;

    pGameWorld->Attribute("EquipTopStarExp", &nValue );
    nEquipTopStarExp = nValue;

    pGameWorld->Attribute("ItemDropDelaySecond", &nValue );
    itemDropDelaySecond = nValue;

    pGameWorld->Attribute("OpenAchievement", &nValue );
    bOpenAchievement = nValue;

    pGameWorld->Attribute("OpenOnlineReward", &nValue );
    bOpenOnlineReward = nValue;

    pGameWorld->Attribute("PetBreedIntervalTime", &nValue );
    petBreedIntervalTime = nValue;

    pGameWorld->Attribute("PetBreedFailedTime", &nValue );
    petBreedFailedTime = nValue;
    
    TiXmlElement* pGM = pSetting->FirstChildElement("GM");
    if ( !pGM)
    { return false; }
    
    szTemp = pGM->Attribute("Password");
    if ( szTemp )
    { strncpy_s( szGMPassword, szTemp, sizeof(szGMPassword) ); }    

    szTemp = pGM->Attribute("IsOpen", &nValue );
    if ( NULL != szTemp)
    { bIsOpenCommand = nValue; }
    
    TiXmlElement* pRobot = pSetting->FirstChildElement("Robot");
    if ( !pRobot )
    { return false; }
    if ( pRobot->Attribute("IsOpen"), &nValue != NULL )
    { bIsOpenRobotCmd = ( nValue != 0 ? true : false ); }
    else
    { bIsOpenRobotCmd = false; }

    TiXmlElement* pQuest = pSetting->FirstChildElement("Quest");
    if ( !pQuest)
    { return false; }

    pQuest->Attribute("GoldMultiplicator", &dValue );
    fTaskGoldMultiplicator = dValue;

    pQuest->Attribute("ExperienceMultiplicator", &dValue );
    fTaskExperienceMultiplicator = dValue;

    pQuest->Attribute("MultiplicatorProbability", &dValue );
    nTaskGetMultiplicatorPercent = dValue;

    TiXmlElement* pNpc = pSetting->FirstChildElement("NPC");
    if ( !pNpc)
    { return false; }

    pNpc->Attribute("MaintainCrossLevel", &nValue );
    maintainCrossLevel = nValue;

	TiXmlElement* pBiaoChe = pSetting->FirstChildElement("OnBiaoChe");
	if (!pBiaoChe)
		return false;
	pBiaoChe->Attribute("OnBiaoCheBuffId", &nValue);
	nOnBiaoCheBuffId = nValue;
	pBiaoChe->Attribute("OnBiaoCheBuffLevel", &nValue);
	nOnBiaoCheBuffLevel = nValue;

    logintype = 0;
    strncpy_s( gamenum,"10044",sizeof(gamenum));

	TiXmlElement* pNurturePet = pSetting->FirstChildElement("NurturePet");
    if ( !pNurturePet)
    { return false; }

    pNurturePet->Attribute("IsOpenAttacter", &nValue );
	isOpenPetAttacter = (nValue == 1)?true:false;


	pNurturePet->Attribute("IsSubOpenAtter", &nValue );
	isOpenSubPetAtter = (nValue == 1)?true:false;


	TiXmlElement* pHonourDefine = pSetting->FirstChildElement("HonourDefine");
    if ( !pHonourDefine)
    { return false; }

    if (pHonourDefine->Attribute("CountryMapHonour",&CountryKillPlayerHonour) == NULL)
		return false;

	if (pHonourDefine->Attribute("LevelLimit",&LevelLimit) == NULL)
		return false;

	if (pHonourDefine->Attribute("TeamHonourDis",&TeamHonourDis) == NULL)
		return false;

	if (pHonourDefine->Attribute("KillPlayerHonour",&KillPlayerHonour) == NULL)
		return false;

	if (pHonourDefine->Attribute("MaxHonour",&MaxHonour) == NULL)
		return false;

	if (pHonourDefine->Attribute("AllMaxHonour",&AllMaxHonour) == NULL)
		return false;

	if (pHonourDefine->Attribute("OncePlayerKillSum",&OncePlayerKillSum) == NULL)
		return false;
	if (pHonourDefine->Attribute("KillPlayerMission",&KillPlayerMission) == NULL)
		return false;
	if (pHonourDefine->Attribute("MaxMissionSum",&MaxMissionSum) == NULL)
		return false;

	if (pHonourDefine->Attribute("TeamDelHonour",&TeamDelHonour) == NULL)
		return false;
	if (pHonourDefine->Attribute("TeamOtherPlayerHonour",&TeamOtherPlayerHonour) == NULL)
		return false;


	TiXmlElement* pDrop = pSetting->FirstChildElement("BeKilled");
	if (!pDrop)
		return false;
	pDrop->Attribute("DropExp", &dValue);
	nDropExp = dValue;
	pDrop->Attribute("DropHonour", &nValue);
	nDropHonour = nValue;

	TiXmlElement* pPetDuration = pSetting->FirstChildElement("PetDuration");
    if ( !pPetDuration)
    { return false; }
    if (pPetDuration->Attribute("MaxPetDuration",&MaxPetDuration) == NULL)
		return false;
	if (pPetDuration->Attribute("InitPetDuration",&InitPetDuration) == NULL)
		return false;


	TiXmlElement* pCSAuth = pSetting->FirstChildElement("CSAuth");
    if ( !pCSAuth)
		return false;
    if (pCSAuth->Attribute("IsOpenCSAuth",&nValue) == NULL)
		return false;
	IsOpenCSAuth = nValue == 1?true:false;



	
	TiXmlElement* pCountry = pSetting->FirstChildElement("CountryBuff");
	if (!pCountry)
		return false;

	pCountry->Attribute("CountryWeakBuffID", &dValue);
	CountryWeakBuffID = dValue;

	pCountry->Attribute("CountryWeakBuffLevel", &dValue);
	CountryWeakBuffLevel = dValue;

	pCountry->Attribute("CountryStrongBuffID", &dValue);
	CountryStrongBuffID = dValue;

	pCountry->Attribute("CountryStrongBuffLevel", &dValue);
	CountryStrongBuffLevel = dValue;

	pCountry->Attribute("CountryBalancedBuffID", &dValue);
	CountryBalancedBuffID = dValue;

	pCountry->Attribute("CountryBalancedBuffLevel", &dValue);
	CountryBalancedBuffLevel = dValue;


	TiXmlElement* pLeaveExp = pSetting->FirstChildElement("LeaveExp");
	if (!pLeaveExp)
		return false;
	pLeaveExp->Attribute("MaxHourSum", &dValue);
	MaxLeaveExpHour = dValue;

    return true;
}

bool Configure::InitPrivateData(const char* szGamesettingPath)
{
    if ( NULL == szGamesettingPath)
    { return false; }

    TiXmlDocument doc;
    if (!doc.LoadFile(szGamesettingPath))
    { return false; }

    int    nValue = 0;
    double dValue = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( NULL == pProject )
    { return false; }

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( NULL == pSetting)
    { return false; }

    TiXmlElement* pSystem = pSetting->FirstChildElement("System");
    if ( !pSystem )
    { return false; }

    pSystem->Attribute( "NetId", &nValue );
    dwServerID = nValue;

    szTemp = pSystem->Attribute("LogConfigFile");
    if ( !szTemp )
    { return false; }
    strLogConfigFilePath = szTemp;

    bool bResult = InitNetSetting();
    if ( !bResult )
    { return false; }

    if ( dwServerID == CHARACTERSERVERID )
    {
        TiXmlElement* pBorn = pSetting->FirstChildElement("Born");
        if ( !pBorn)
        { return false; }

        TiXmlElement* pPoint = pBorn->FirstChildElement("Point");
        int nIndex = 0;
        while ( pPoint )
        {
            if ( nIndex >=  BORN_POINT_COUNT)
                break;

            pPoint->Attribute("MapId", &nValue);
            m_iBornPointMap[nIndex] = nValue;

            pPoint->Attribute("X", &nValue);
            m_iBornPointX[nIndex] = nValue;

            pPoint->Attribute("Y", &nValue);
            m_iBornPointY[nIndex] = nValue;

            if ( pPoint->Attribute( "IsOpen", &nValue ) != NULL )
            { m_iBornOpen[nIndex] = nValue; }

            pPoint = pPoint->NextSiblingElement("Point");
            ++nIndex;
        }
    }
    else
    {
        TiXmlElement* pActiveMaps = pSetting->FirstChildElement("ActiveMaps");
        if ( !pActiveMaps )
        { return false; }

        TiXmlElement* pMap = pActiveMaps->FirstChildElement("Map");
        while ( pMap)
        {
            int mapid = 0;
            int isOpen = 0;
            int isRun  = 1;
            SOpenMap sOpenMap;
            if ( NULL != pMap->Attribute("Id",&mapid) )
            {
                if ( mapid < 0 )
                { return false; }

                sOpenMap.MapId = mapid;
            }
            if ( pMap->Attribute( "IsRun", &isRun ) != NULL )
            { sOpenMap.IsRun = isRun; }

            OpenMaps::iterator itr = find( OpenMaps_.begin(), OpenMaps_.end(), sOpenMap.MapId );
            if ( OpenMaps_.end() != itr )
            { *itr = sOpenMap; }
            else
            { OpenMaps_.push_back(sOpenMap); }

            pMap = pMap->NextSiblingElement("Map");
        }
    }
    
    return true;
}

bool Configure::InitNetSetting()
{
    TiXmlDocument doc;
    if (!doc.LoadFile( NETSETTING_FILEPATH ))
    { return false; }

    int    nValue      = 0;
    double dValue      = 0.0f;
    const char* szTemp = NULL;
    std::string        strValue;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( !pProject )
    { return false; }

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( !pSetting )
    { return false; }

    TiXmlElement* pGames = pSetting->FirstChildElement("Games");
    if ( !pGames )
    { return false; }

    TiXmlElement* pCommon = pGames->FirstChildElement("Common");
    if ( !pCommon )
    { return false; }

    // DatabaseServer
    TiXmlElement* pDatabaseServer = pCommon->FirstChildElement("DatabaseServer");
    if ( !pDatabaseServer)
    { return false; }

    szTemp = pDatabaseServer->Attribute("Host");
    if ( !szTemp )
    { return false; }
    strncpy_s( szDBServerIP, szTemp, sizeof(szDBServerIP) );

    pDatabaseServer->Attribute("Port", &nValue );
    iDBServerPort = nValue;
    //log server
	TiXmlElement* pLogServer = pCommon->FirstChildElement("LogServer");
	if ( !pLogServer)
	{ return false; }

	szTemp = pLogServer->Attribute("Host");
	if ( !szTemp )
	{ return false; }
	strncpy_s( szLogServerIp, szTemp, sizeof(szLogServerIp) );

	pLogServer->Attribute("Port", &nValue );
	iLogServerPort = nValue;
	pLogServer->Attribute("OpenService", &nValue );
	bOpenLogService = nValue;
    // CenterServer
    TiXmlElement* pCenterServer = pCommon->FirstChildElement("CenterServer");
    if ( !pCenterServer)
    { return false; }

    szTemp = pCenterServer->Attribute("Host");
    if ( !szTemp )
    { return false; }
    strncpy_s( szCenterServerIP, szTemp, sizeof(szCenterServerIP) );

    pCenterServer->Attribute("Port", &nValue );
    sCenterServerPort = nValue;
    
    // ListenPort
    TiXmlElement* pGame = pGames->FirstChildElement("Game");
    bool bOk = false;
    while ( pGame )
    {      
        pGame->Attribute("Id", &nValue );
        if ( nValue == dwServerID )
        {
            szTemp = pGame->Attribute("Name");
            if ( NULL != szTemp)
            {
                Common::_tstring strTemp;
                strTemp.fromUTF8( szTemp );
                strncpy_s( szGameServerName, strTemp.c_str(), sizeof(szGameServerName) );
            }

            pGame->Attribute("ListenGatePort", &nValue );
            wListenGateServerPort = nValue;
            bOk = true;
            break;
        }

        pGame = pGame->NextSiblingElement("Game");
    }
    
    if ( !bOk )
    { return false; }

    return true;
}

bool Configure::IsMapOpen(int MapId)
{
    OpenMaps::iterator itr = find(OpenMaps_.begin(),OpenMaps_.end(),MapId);
    if (itr != OpenMaps_.end())
    { return true; }

    return false;
}

bool Configure::IsMapRun(int MapId)
{
    OpenMaps::iterator itr = find(OpenMaps_.begin(),OpenMaps_.end(),MapId);
    if (itr != OpenMaps_.end())
    {
        return itr->IsRun;
    }
    return false;
}

//{
//    
//    if ( !szGamesettingPath)
//    { return false; }
//
//    TiXmlDocument doc;
//    if (!doc.LoadFile(szGamesettingPath))
//    { return false; }
//    
//    int    nValue = 0;
//    double dValue = 0.0f;
//    const char* szTemp = NULL;
//
//    TiXmlElement* pProject = doc.FirstChildElement("Project");
//    if ( !pProject )
//        return false;
//
//    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
//    if ( !pSetting)
//        return false;
//
//    TiXmlElement* pServerInformation = pSetting->FirstChildElement("ServerInformation");
//    if ( !pServerInformation )
//        return false;    
//
//    szTemp  =  pServerInformation->Attribute("Name");
//    if (!szTemp)
//        return false;
//        
//    Common::_tstring strTemp;
//    strTemp.fromUTF8( szTemp );
//    strncpy_s( szGameServerName, strTemp.c_str(), sizeof(szGameServerName) );
//    
//    pServerInformation->Attribute("AreaId", &nValue );
//    dwAreaId = nValue ;
//    
//    pServerInformation->Attribute("ServerId", &nValue );
//    dwServerID = nValue;
//
//    TiXmlElement* pSleep = pSetting->FirstChildElement("Sleep");
//    if ( pSleep != NULL )
//    {
//        pSleep->Attribute( "Time", &nValue );
//        m_bSleepTime = nValue;
//    }
//
//    TiXmlElement* pLog = pSetting->FirstChildElement("Log");
//    if ( !pLog)
//        return false;
//    szTemp = pLog->Attribute("ConfigFile");
//    if ( !szTemp )
//        return false;
//    strLogConfigFilePath = szTemp;
//

//    TiXmlElement* pFileDB = pSetting->FirstChildElement("FileDB");
//    if ( !pFileDB)
//        return false;
//
//    szTemp = pFileDB->Attribute("OutputPath");
//    if ( !szTemp)
//        return false;
//    strncpy_s( szFileDBPath, szTemp, sizeof(szFileDBPath));
//    
//    TiXmlElement* pBorn = pSetting->FirstChildElement("Born");
//    if ( !pBorn)
//        return false;
//
//    TiXmlElement* pPoint = pBorn->FirstChildElement("Point");
//    int nIndex = 0;
//    while ( pPoint )
//    {
//        if ( nIndex >=  BORN_POINT_COUNT)
//            break;
//        
//        pPoint->Attribute("MapId", &nValue);
//        m_iBornPointMap[nIndex] = nValue;
//        
//        pPoint->Attribute("X", &nValue);
//        m_iBornPointX[nIndex] = nValue;
//
//        pPoint->Attribute("Y", &nValue);
//        m_iBornPointY[nIndex] = nValue;
//
//        if ( pPoint->Attribute( "IsOpen", &nValue ) != NULL )
//        { m_iBornOpen[nIndex] = nValue; }
//
//        pPoint = pPoint->NextSiblingElement("Point");
//        ++nIndex;
//    }
//    
//    TiXmlElement* pGameTime = pSetting->FirstChildElement("GameTime");
//    if ( !pGameTime)
//        return false;
//
//    szTemp = pGameTime->Attribute("YearName");
//    if (!szTemp)
//        return false;
//    strncpy_s( m_szYearName, szTemp, sizeof(m_szYearName) );
//
//    pGameTime->Attribute("Year", &nValue );
//    m_nYear = nValue;
//    
//    pGameTime->Attribute("Month", &nValue );
//    m_nMonth = nValue;
//
//    pGameTime->Attribute("Day", &nValue );
//    m_nDay = nValue;
//
//    pGameTime->Attribute("Hour", &nValue );
//    m_nHour = nValue;
//
//    pGameTime->Attribute("Minute", &nValue );
//    m_nMinute = nValue;
//
//    pGameTime->Attribute("RealLifeRate", &nValue );
//    m_nGameWorldTimerRate = nValue;
//
//    pGameTime->Attribute("CurYear", &nValue );
//    m_nGameYear = nValue;
//
//    TiXmlElement* pAntiPlugin = pSetting->FirstChildElement("AntiPlugin");
//    if ( !pAntiPlugin)
//        return false;
//
//    pAntiPlugin->Attribute("IsOpen", &nValue );
//    bAntiPluginOpen = ( nValue != 0 ) ? true : false;
//     
//    szTemp = pAntiPlugin->Attribute("CreateImgExePath");
//    if ( szTemp )
//    {
//        strncpy_s( szCreateImgExePath, szTemp, sizeof(szCreateImgExePath));
//    }
//    
//    szTemp = pAntiPlugin->Attribute("ImgOutput");
//    if ( !szTemp )
//        return false;
//    strncpy_s( szTmpImageFolder, szTemp, sizeof(szTmpImageFolder));
//
//    pAntiPlugin->Attribute("CheckTimeInFight", &nValue);
//    dwCheckWhenFightingTime = nValue;
//
//    pAntiPlugin->Attribute("IsKickCheater", &nValue);
//    m_bIsKickCheater = (nValue != 0) ? true : false;
//
//    pAntiPlugin->Attribute("MaxCheckFailCount", &nValue);
//    nMaxCheckFailCount = nValue;
//
//    pAntiPlugin->Attribute("FailBlockTime", &nValue);
//    graphicValidFailBlockTime = nValue;
//
//    pAntiPlugin->Attribute("OnMapLimitTime", &nValue);
//    onMapLimitTime = nValue;
//
//    pAntiPlugin->Attribute("PlayerApplyTime", &nValue);
//    dwPlayerApplyTime = nValue;
//
//    /*
//    TiXmlElement* pAntiWallow = pSetting->FirstChildElement("AntiWallow");
//    if ( !pAntiWallow)
//    { return false; }
//
//    pAntiWallow->Attribute("IsOpen", &nValue );
//    m_bIsOpenDefWallow = nValue != 0 ? true : false;
//    
//
//    pAntiWallow->Attribute("FirstPhase", &nValue );
//    m_nFirstPhase            = nValue;
//    pAntiWallow->Attribute("FirstPhaseExpSub", &nValue );
//    m_nFirstPhaseExpSub      = nValue;
//    pAntiWallow->Attribute("FirstPhaseSkillExpSub", &nValue );
//    m_nFirstPhaseSkillExpSub = nValue;
//
//    pAntiWallow->Attribute("SecondPhase", &nValue );
//    m_nSecondPhase            = nValue;
//    pAntiWallow->Attribute("SecondPhaseExpSub", &nValue );
//    m_nSecondPhaseExpSub      = nValue;
//    pAntiWallow->Attribute("SecondPhaseSkillExpSub", &nValue );
//    m_nSecondPhaseSkillExpSub = nValue;
//    pAntiWallow->Attribute("ThirdPhase", &nValue );
//    m_nThirdPhase = nValue;
//    pAntiWallow->Attribute("ThirdPhaseExpSub", &nValue );
//    m_nThirdPhaseExpSub = nValue;
//    pAntiWallow->Attribute("ThirdPhaseSkillExpSub", &nValue );
//    m_nThirdPhaseSkillExpSub = nValue;
//
//    pAntiWallow->Attribute("Time1", &nValue );
//    antiAddictionTime[0]= nValue;
//
//    pAntiWallow->Attribute("Time2", &nValue );
//    antiAddictionTime[1]= nValue;
//    */
//    TiXmlElement* pEventTime = pSetting->FirstChildElement("EventTime");
//    if ( !pEventTime)
//        return false;
//
//    pEventTime->Attribute("RefreshTimeHour", &nValue );
//    m_nRefreshHour = nValue;
//
//    pEventTime->Attribute("RefreshTimeMinute", &nValue );
//    m_nRefreshMin = nValue;
//
//    pEventTime->Attribute("TellOnlineTimeInterval", &nValue );
//    m_TellPlayerPerTime = nValue;
//    
//    pEventTime->Attribute("IntegralTimeInterval", &nValue );
//    m_nIntegralPerTime = nValue;
//    
//    TiXmlElement* pPK = pSetting->FirstChildElement("PK");
//    if ( !pPK)
//        return false;
//    
//    pPK->Attribute("IsOpen", &nValue );
//    bPKOpen = nValue != 0 ? true : false;
//    
//    pPK->Attribute("FirstKillRate", &nValue );
//    m_nFirstKill = nValue;
//
//    pPK->Attribute("SecondKillRate", &nValue );
//    m_nSecondKill = nValue;
//
//    pPK->Attribute("ThirdKillRate", &nValue );
//    m_nThirdKill = nValue;
//
//    pPK->Attribute("MoreKillRate", &nValue );
//    m_nMoreKill = nValue;
//    
//    pPK->Attribute("RefreshTimeOnKillTheSameOne", &nValue );
//    m_dwRefreshKillTime = nValue;
//    
//    pPK->Attribute("PkValueMaxPerDay", &nValue );
//    nMaxDailyPKValue = nValue;
//
//    TiXmlElement* pDuel = pSetting->FirstChildElement("Duel");
//    if ( !pDuel)
//        return false;
//    
//    pDuel->Attribute("HpRestoreRate", &nValue );
//    nDulEndHpper = nValue;
//
//    pDuel->Attribute("OutProtectTime", &nValue );
//    protecttime = nValue;
//    
//    TiXmlElement* pMonster = pSetting->FirstChildElement("Monster");
//    if ( !pMonster)
//        return false;
//
//    pMonster->Attribute("IsAIOpen", &nValue );
//    iAllAIOpen = nValue;
//
//    pMonster->Attribute("IsMultiThreadRefresh", &nValue );
//    bMTRefMonster = nValue != 0 ? true : false ;
//    
//    TiXmlElement* pPlayer = pSetting->FirstChildElement("Player");
//    if ( !pPlayer)
//        return false;
//    
//    pPlayer->Attribute("OnlineMax", &nValue );
//    iOnlineMax = nValue;
//
//    pPlayer->Attribute("LevelLimit", &nValue );
//    m_nLevelLimt = nValue;
//
//    pPlayer->Attribute("PKProtectLevel", &nValue);
//    m_nPKProtectLevel = (nValue == 0 ? PKProtectLevel : nValue);
//    
//    pPlayer->Attribute("PrivateShopLevel", &nValue);
//    m_nPrivateShopLevel = (nValue == 0 ? PKProtectLevel : nValue);
//
//    pPlayer->Attribute("BeRelivePkValue", &nValue );
//    beRelivePkValue = nValue;
//
//    pPlayer->Attribute("SkillExpLimit", &nValue );
//    m_nSkillExpLimt = nValue;
//
//    pPlayer->Attribute("MoneyLimit", &nValue );
//    m_nMoneyMax = nValue;
//
//    pPlayer->Attribute("JiaoZiLimit", &nValue );
//    m_nMaxJiaoZi = nValue;
//    
//    pPlayer->Attribute("SaveDelay", &nValue );
//    dwAutoSaveDelay = nValue;
//
//    pPlayer->Attribute("OnlySaveToDBOnExit", &nValue );
//    bOnlySaveToDBOnExit = nValue != 0 ? true : false;
//    
//    pPlayer->Attribute("NormalBagInitSize", &nValue );
//    m_nCreatBagSize = nValue;
//
//    pPlayer->Attribute("MaterialBagInitSize", &nValue );
//    m_nCreateMaterialSize = nValue;
//
//    pPlayer->Attribute("InitMountCountMax", &nValue );
//    initMountCountMax = nValue;
//
//    pPlayer->Attribute("LockItemLimt", &nValue );
//    m_nLockItemLimt = nValue;
//
//    pPlayer->Attribute("SitdownRestorePer", &nValue );
//    m_SitdownRestorePer = (float)nValue/DEF_PER;;
//
//    pPlayer->Attribute("RestoreCheckTime", &nValue );
//    CharDataRestoreCheck = nValue;
//
//    pPlayer->Attribute("IntegralMaxByItem", &nValue );
//    m_nIntegralMaxByItem = nValue;
//
//    pPlayer->Attribute("AfkTime", &nValue );
//    m_nTimeInAfk = nValue;
//
//    pPlayer->Attribute("HighShoutCountPerDay", &nValue );
//    nHighShoutCountPerDay = nValue;
//
//    pPlayer->Attribute("IsHighShoutTimeLimit", &nValue );
//    bHighShoutTimeLimit = nValue;
//
//    pPlayer->Attribute("HighShotTimeInterval", &nValue );
//    nHighShoutPerTime = nValue;
//
//    pPlayer->Attribute("HighShoutLevelLimit", &nValue);
//    nHighShoutLevelLimit = nValue;
//
//    double fPercent;
//    if ( pPlayer->Attribute( "MinModelPercent", &fPercent ) != NULL )
//    { m_fMinModelPercent = fPercent; }
//
//    if ( pPlayer->Attribute( "MaxModelPercent", &fPercent ) != NULL )
//    { m_fMaxModelPercent = fPercent; }
//
//    if ( pPlayer->Attribute( "ExchangeJindingLevelLimit", &nValue ) != NULL )
//    { exchangeJindingLevelLimit = nValue; }
//
//    isTakeMoneyCorrect = false;
//    if ( pPlayer->Attribute( "IsTakeMoneyCorrect", &nValue ) != NULL )
//    { isTakeMoneyCorrect = nValue==1? true : false; }
//
//    TiXmlElement* pGameWorld = pSetting->FirstChildElement("GameWorld");
//    if ( !pGameWorld)
//    { return false; }
//    
//    pGameWorld->Attribute("IsMultiThreadProcess", &nValue );
//    bMTStageProc = nValue != 0 ? true : false;
//
//    pGameWorld->Attribute("GoldCovSilver", &nValue );
//    m_nGlodCovSilver = nValue;
//
//    pGameWorld->Attribute("MonsterNumber", &nValue );
//    iMonsterNumber = nValue;
//
//    pGameWorld->Attribute("KickPlayerByCredit", &nValue );
//    bKickPlayerByCredit = nValue !=0 ? true : false;
//
//    pGameWorld->Attribute("ReliveOriginAllHpMp", &nValue );
//    m_nReliveOriginAllHpMp = nValue;
//
//    pGameWorld->Attribute("ReliveOriginNon", &nValue );
//    m_nReliveOriginNon = nValue;
//
//    pGameWorld->Attribute("RePairCost", &nValue );
//    m_nReqairRmb = nValue;
//
//    pGameWorld->Attribute("StageThreadSleep", &nValue );
//    dwMapThreadSleep = nValue;
//
//    pGameWorld->Attribute("IsDisableChatofWorld", &nValue );
//    bDisableChatofWorld = nValue !=0 ? true : false;
//
//    pGameWorld->Attribute("LockIntensifyRMB", &nValue );
//    m_nLockIntensifySilver = nValue;
//
//    pGameWorld->Attribute("ShopCenterOffSet", &nValue );
//    m_nOffSetInShopCenter = nValue;
//    bIsChangedShopCenterOff = false;
//    
//    pGameWorld->Attribute("GlobalDropRate", &dValue );
//    m_fGlobalDropRate = dValue;
//    
//    TiXmlElement* pGM = pSetting->FirstChildElement("GM");
//    if ( !pGM)
//        return false;
//    
//    szTemp = pGM->Attribute("Password");
//    if ( szTemp )
//    {
//        strncpy_s( szGMPassword, szTemp, sizeof(szGMPassword) );
//    }    
//
//    szTemp = pGM->Attribute("IsOpen", &nValue );
//    if ( NULL != szTemp)
//        bIsOpenCommand = nValue;
//    
//    TiXmlElement* pQuest = pSetting->FirstChildElement("Quest");
//    if ( !pQuest)
//        return false;
//
//    pQuest->Attribute("GoldMultiplicator", &dValue );
//    fTaskGoldMultiplicator = dValue;
//
//    pQuest->Attribute("ExperienceMultiplicator", &dValue );
//    fTaskExperienceMultiplicator = dValue;
//
//    pQuest->Attribute("MultiplicatorProbability", &dValue );
//    nTaskGetMultiplicatorPercent = dValue;
//
//    TiXmlElement* pActiveMaps = pSetting->FirstChildElement("ActiveMaps");
//    if ( !pActiveMaps)
//        return false;
//    
//    TiXmlElement* pMap = pActiveMaps->FirstChildElement("Map");
//    while (pMap)
//    {
//        int mapid = 0;
//        int isOpen = 0;
//        int isRun = 0;
//        SOpenMap sOpenMap;
//        if (pMap->Attribute("Id",&mapid) != NULL)
//        {
//            if (mapid < 0 )
//            {
//                return false;
//            }
//            sOpenMap.MapId = mapid;
//        }
//
//        if (pMap->Attribute("IsOpen",&isOpen) != NULL)
//        {
//            sOpenMap.IsOpen = isOpen;
//        }
//
//        if ( pMap->Attribute( "IsRun", &isRun ) != NULL )
//        {
//            sOpenMap.IsRun = isRun;
//        }
//
//        OpenMaps_.push_back(sOpenMap);
//        pMap = pMap->NextSiblingElement("Map");
//    }
//
//    TiXmlElement* pPrisonMaps = pSetting->FirstChildElement("PrisonMaps");
//    if ( pPrisonMaps != NULL )
//    {
//        TiXmlElement* pMap = pPrisonMaps->FirstChildElement("Map");
//        while ( NULL != pMap )
//        {
//            PrisonMap xPrison;
//            int nMapID;
//            if ( NULL != pMap->Attribute( "Id", &nMapID ) )
//            xPrison.nMapID = nMapID;
//
//            double fX;
//            pMap->Attribute( "PositionX", &fX );
//            xPrison.fX = fX;
//
//            double fY;
//            pMap->Attribute( "PositionY", &fY );
//            xPrison.fY = fY;
//
//            int nDir;
//            pMap->Attribute( "Direction", &nDir );
//            xPrison.fDir = nDir * PI / 180.f;
//
//            m_vecPrisonMap.push_back( xPrison );
//
//            pMap = pMap->NextSiblingElement("Map");
//        }
//    }
//
//    logintype = 0;
//    strncpy_s( gamenum,"10044",sizeof(gamenum));
//    return true;
//}
