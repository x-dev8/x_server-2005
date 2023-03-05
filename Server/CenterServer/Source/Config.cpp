#include "Config.h"
#include "ResourcePath.h"
#include "Tinyxml/tinyxml.h"
//#include "NetApi.h"

#define SAVESWORNDEFAULTTIME 1000*60*5

Config& Config::GetInstance()
{
    static Config instance;
    return instance;
}

Config::Config() 
:usLoginServerPort(0),platformPort(0),m_bSleepTime(false),listentPortForPlatform(0)
,roleDbPort(0),platformDbPort(0),nFullLoadMaxNum(0),nMaxNumOneMac(0)
{
    memset( platformIp,       0, sizeof(platformIp)      );
	memset( LogServerHost,    0, sizeof(LogServerHost)      );
	memset(szLoginServerIP,0,sizeof(szLoginServerIP));
    
    bOpenAntiAddiction = false;

	server_id = 0;

    /*
    默认
    正常时间为3小时(180分钟)，通知间隔60分钟
    疲劳时间为5小时(300分钟)，通知间隔30分钟
    不健康时间通知间隔为15分钟
    线下时间累积5小时(300分钟)才重新计算线上时间
    */
    antiAddiction._normal._playTime   = 180;
    antiAddiction._normal._notifyTime = 60 ;

    antiAddiction._tired._playTime    = 300;
    antiAddiction._tired._notifyTime  = 30 ;

    antiAddiction._rest._playTime     = 300;
    antiAddiction._rest._notifyTime   = 15 ;
    nAntiAddictionSaveTime = 0;

	nOpenNum = 0;
	bOpenService = false;
}

bool Config::Init( const char* szConfigFile )
{
    bool bResult = InitNetSetting();
    if ( !bResult )
    { return false; }

    TiXmlDocument doc;
    if (!doc.LoadFile(szConfigFile))
    { return false; }
        
    int    nValue      = 0;
    double dValue      = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( !pProject )
    { return false; }
    
    szTemp = pProject->Attribute("Name");
    if ( !szTemp )
    { return false; }
    strGameName = szTemp;

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( !pSetting )
    { return false; }

    TiXmlElement* pLogic = pSetting->FirstChildElement("Logic");
    if ( !pLogic )
    { return false; }

    szTemp = pLogic->Attribute("LogConfigFile");
    if ( !szTemp)
    { return false; }

    strLogConfigFilePath = szTemp;

    pLogic->Attribute("MaxTickNum", &nValue );
    usMaxTickNum = nValue;

    pLogic->Attribute("OutReqLoginTime", &nValue );
    dwOutReqLoginTime = nValue;
    
    if (pLogic->Attribute("SaveSwornTime",&nValue) != NULL)
    {
        if (nValue <= 0 )
        { unSwornSaveTime = SAVESWORNDEFAULTTIME; }
        else
        { unSwornSaveTime = nValue; }
    }
    else
    { unSwornSaveTime = SAVESWORNDEFAULTTIME; }

	pLogic->Attribute("QueueNum", &nValue );
	nOpenNum = nValue;

	pLogic->Attribute("QueueService", &nValue );
	bOpenService = nValue;
 

	TiXmlElement* pAntiAddictionSystem = pSetting->FirstChildElement("AntiAddictionSystem");
	if ( NULL == pAntiAddictionSystem )
	{ return false; }

	pAntiAddictionSystem->Attribute("IsOpen", &nValue);
	bOpenAntiAddiction = nValue !=0  ? true : false;

	if ( pAntiAddictionSystem->Attribute("Time1", &nValue))
	{ antiAddiction._normal._playTime   = nValue; }

	if ( pAntiAddictionSystem->Attribute("Time1Tell", &nValue))
	{ antiAddiction._normal._notifyTime = nValue; }

	if ( pAntiAddictionSystem->Attribute("Time2", &nValue))
	{ antiAddiction._tired._playTime    = nValue; }

	if ( pAntiAddictionSystem->Attribute("Time2Tell", &nValue) )
	{ antiAddiction._tired._notifyTime  = nValue; }

	if ( pAntiAddictionSystem->Attribute("Time3", &nValue))
	{ antiAddiction._rest._playTime     = nValue; }

	if ( pAntiAddictionSystem->Attribute("Time3Tell", &nValue))
	{ antiAddiction._rest._notifyTime   = nValue; }

    if ( pAntiAddictionSystem->Attribute("SaveTime", &nValue))
    { nAntiAddictionSaveTime = nValue; }
    return true;
}

bool Config::InitNetSetting()
{
    TiXmlDocument doc;
    if ( !doc.LoadFile( NETSETTING_FILEPATH ) )
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
	//

    TiXmlElement* pCenter = pSetting->FirstChildElement("Center");
    if ( !pCenter )
    { return false; }

    TiXmlElement* pListenPort = pCenter->FirstChildElement("ListenPort");
    if ( !pListenPort )
    { return false; }

    pListenPort->Attribute("GameServer", &nValue );
    usListenPortForGameServer = nValue;

    //pListenPort->Attribute("LoginServer", &nValue );
    //usListentPortForLoginServer = nValue;

    pListenPort->Attribute("Platform", &nValue );
    listentPortForPlatform = nValue;

	//connect login server
	TiXmlElement* pLoginServer = pCenter->FirstChildElement("LoginServer");
	if ( !pLoginServer )
	{ return false; }

	szTemp = NULL;
	szTemp = pLoginServer->Attribute("Host");
	if ( !szTemp )
	{ return false; }
	strncpy_s( szLoginServerIP, sizeof(szLoginServerIP), szTemp, sizeof(szLoginServerIP)-1 );

	pLoginServer->Attribute("Port",&nValue);
	usLoginServerPort = nValue;

    //connect dbserver
    TiXmlElement* pDatabaseServer = pCenter->FirstChildElement("DatabaseServer");
    if (!pDatabaseServer)
    { return false; }

    szTemp = NULL;
    szTemp = pDatabaseServer->Attribute("Host");
    if ( !szTemp )
    { return false; }
    strncpy_s( szDatabaseServerIP, sizeof(szDatabaseServerIP), szTemp, sizeof(szDatabaseServerIP)-1 );

    pDatabaseServer->Attribute("Port",&nValue);
    usDatabaseServerPort = nValue;

    pDatabaseServer->Attribute("CenterServerId",&nValue);
    CenterServerId = nValue;

	//connect log server
	TiXmlElement* pLogServer = pCenter->FirstChildElement("LogServer");
	if ( !pLogServer )
	{ return false; }

	szTemp = NULL;
	szTemp = pLogServer->Attribute("Host");
	if ( !szTemp )
	{ return false; }
	strncpy_s( LogServerHost, sizeof(LogServerHost), szTemp, sizeof(LogServerHost)-1 );

	pLogServer->Attribute("Port",&nValue);
	LogServerPort = nValue;
	pLogServer->Attribute("OpenService",&nValue);
	LogServerService = nValue;

    //connect platformserver
    TiXmlElement* pPlatformserver= pCenter->FirstChildElement("PlatformServer");
    if (!pPlatformserver)
    { return false; }

    szTemp = NULL;
    szTemp = pPlatformserver->Attribute("Host");
    if ( !szTemp )
    { return false; }
    strncpy_s( platformIp, sizeof(platformIp), szTemp, sizeof(platformIp)-1);

    pPlatformserver->Attribute("Port",&nValue);
    platformPort = nValue;
	pPlatformserver->Attribute("UsePlatform",&nValue);
	platform_need = nValue;
	pPlatformserver->Attribute("ServerId", &nValue );
	server_id = nValue;

    // GameDB
    TiXmlElement* pGameDB = pCenter->FirstChildElement("GameDB");
    if ( !pGameDB )
    { return false; }

    szTemp = pGameDB->Attribute("Host");
    if ( !szTemp )
    { return false; }

    std::string strHost = /*NetApi::GetHostByName*/(szTemp);
    if ( strHost.empty())
    { return false; }
    roleHost = strHost;

    pGameDB->Attribute("Port", &nValue);
    roleDbPort = nValue;

    szTemp = pGameDB->Attribute("User");
    if ( !szTemp )
    { return false; }
    roleUID = szTemp;

    szTemp = pGameDB->Attribute("Password");
    if ( !szTemp )
    { return false; }
    rolePwd = szTemp;

    szTemp = pGameDB->Attribute("Name");
    if ( !szTemp )
    { return false; }
    roleDbName = szTemp;

    // PlatformDB
    //TiXmlElement* pBillingDB = pCenter->FirstChildElement("BillingDB");
    //if ( !pBillingDB )
    //{ return false; }

    //szTemp = pBillingDB->Attribute("Host");
    //if ( !szTemp )
    //{ return false; }

    //strHost.clear();
    //strHost = /*NetApi::GetHostByName*/(szTemp);
    //if ( strHost.empty())
    //{ return false; }
    //billingHost = strHost;

    //pBillingDB->Attribute("Port", &nValue);
    //billingDbPort = nValue;

    //szTemp = pBillingDB->Attribute("User");
    //if ( !szTemp )
    //{ return false; }
    //billingUID = szTemp;

    //szTemp = pBillingDB->Attribute("Password");
    //if ( !szTemp )
    //{ return false; }
    //billingPwd = szTemp;

    //szTemp = pBillingDB->Attribute("Name");
    //if ( !szTemp )
    //{ return false; }
    //billingDbName = szTemp;

    // WallowDB
    TiXmlElement* pPlatformDB = pCenter->FirstChildElement("WallowDB");
    if ( !pPlatformDB )
    { return false; }

    szTemp = pPlatformDB->Attribute("Host");
    if ( !szTemp )
    { return false; }

    strHost.clear();
    strHost = /*NetApi::GetHostByName*/(szTemp);
    if ( strHost.empty())
    { return false; }
    platformHost = strHost;

    pPlatformDB->Attribute("Port", &nValue);
    platformDbPort = nValue;

    szTemp = pPlatformDB->Attribute("User");
    if ( !szTemp )
    { return false; }
    platformUID = szTemp;

    szTemp = pPlatformDB->Attribute("Password");
    if ( !szTemp )
    { return false; }
    platformPwd = szTemp;

    szTemp = pPlatformDB->Attribute("Name");
    if ( !szTemp )
    { return false; }
    platformDbName = szTemp;

    // PlatformRPC Mysql
    //TiXmlElement* pPlatformRPC = pCenter->FirstChildElement("PlatformRPC");
    //if ( !pPlatformRPC )
    //{ return false; }

    //szTemp = pPlatformRPC->Attribute("Host");
    //if ( !szTemp )
    //{ return false; }

    //strHost = /*NetApi::GetHostByName*/(szTemp);
    //if ( strHost.empty())
    //{ return false; }
    //strPlatformRPCHost = strHost;

    //pPlatformRPC->Attribute("Port", &nValue);
    //nPlatformRPCPort = nValue;

    //szTemp = pPlatformRPC->Attribute("User");
    //if ( !szTemp )
    //{ return false; }
    //strPlatformRPCUser = szTemp;

    //szTemp = pPlatformRPC->Attribute("Password");
    //if ( !szTemp )
    //{ return false; }
    //strPlatformRPCPwd = szTemp;

    //szTemp = pPlatformRPC->Attribute("DbName");
    //if ( !szTemp )
    //{ return false; }
    //strPlatformRPCDbName = szTemp;
    return true;
}
