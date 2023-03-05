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

Config::Config()/*: DateBasePort(0)*//*, QueryTime(0), BlockAccountTime(0)*/
{
     memset( DateBaseName,     0, sizeof(DateBaseName)    );
     memset( DateBaseUser,     0, sizeof(DateBaseUser)    );
     memset( DateBasePassword, 0, sizeof(DateBasePassword));
     memset( DateBaseIp,       0, sizeof(DateBaseIp)      );
	 
	 DateBasePort = 0;
	 UsingDB = true;
	 strServiceIp.clear();
	 ustForClientPort = 0;
	 strAccountServerIp.clear();
	 ustAccountServerPort = 0;
	 nBindAccountPort = 0;
	 strKey.clear();
	 ustListenCenterPort = 0;

	 memset( BlockDateBaseName,     0, sizeof(BlockDateBaseName)    );
	 memset( BlockDateBaseUser,     0, sizeof(BlockDateBaseUser)    );
	 memset( BlockDateBasePassword, 0, sizeof(BlockDateBasePassword));
	 memset( BlockDateBaseIp,       0, sizeof(BlockDateBaseIp)      );
	 BlockDateBasePort = 0;
}

bool Config::Init( const char* szConfigFile )
{
    bool bResult = InitNetSetting();
    if ( !bResult )
    { return false; }

	bResult = InitLoginCoinfg(szConfigFile);
	if ( !bResult )
	{ return false; }
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

    TiXmlElement* pCenter = pSetting->FirstChildElement("CenterLogin");
    if ( !pCenter )
    { return false; }

	std::string strHost;
    TiXmlElement* pAccountDB = pCenter->FirstChildElement("AccountDB");
    if (!pAccountDB)
    { return false; }

    strValue = pAccountDB->Attribute("Host");
    if (!strValue.empty())
    { strncpy_s(DateBaseIp, sizeof( DateBaseIp ), strValue.c_str(),sizeof(DateBaseIp) - 1 ); }

    pAccountDB->Attribute("Port",&nValue);
    DateBasePort = nValue;

    strValue = pAccountDB->Attribute("User");
    if (!strValue.empty())
    { strncpy_s(DateBaseUser, sizeof( DateBaseUser), strValue.c_str(),sizeof(DateBaseUser) - 1 ); }

    strValue = pAccountDB->Attribute("Password");
    if (!strValue.empty())
    { strncpy_s(DateBasePassword, sizeof( DateBasePassword ), strValue.c_str(),sizeof(DateBasePassword) - 1 ); }

    strValue = pAccountDB->Attribute("Name");
    if (!strValue.empty())
    { strncpy_s(DateBaseName, sizeof( DateBaseName ), strValue.c_str(),sizeof(DateBaseName) - 1 ); }

    pAccountDB->Attribute("UsingDB",&nValue);
    UsingDB = nValue;

	//Service
	TiXmlElement* pService = pCenter->FirstChildElement("Service");
	if ( !pService )
	{ return false; }

	szTemp = pService->Attribute("Host");
	if ( !szTemp )
	{ return false; }

	strHost = (szTemp);
	if ( strHost.empty())
	{ return false; }
	strServiceIp = strHost;

	pService->Attribute("Port", &nValue);
	ustForClientPort = nValue;

	//AccountServer
	TiXmlElement* pAccountServer = pCenter->FirstChildElement("AccountServer");
	if ( !pAccountServer )
	{ return false; }

	szTemp = pAccountServer->Attribute("Host");
	if ( !szTemp )
	{ return false; }

	strHost = (szTemp);
	if ( strHost.empty())
	{ return false; }
	strAccountServerIp = strHost;

	pAccountServer->Attribute("Port", &nValue);
	ustAccountServerPort = nValue;

	pAccountServer->Attribute("BindPort", &nValue);
	nBindAccountPort = nValue;
	if (nBindAccountPort < 0)
	{
		nBindAccountPort = 0;
	}

	szTemp = pAccountServer->Attribute("Key");
	if ( !szTemp )
	{ return false; }
	strKey = szTemp;

	//ListenCenterPort
	TiXmlElement* pListenCenterPort = pCenter->FirstChildElement("ListenCenterPort");
	if ( !pListenCenterPort )
	{ return false; }
	pListenCenterPort->Attribute("Port", &nValue);
	ustListenCenterPort = nValue;

	//glsdb
	TiXmlElement* pGlsDB = pCenter->FirstChildElement("GlsDB");
	if (!pGlsDB)
	{ return false; }

	strValue = pGlsDB->Attribute("Host");
	if (!strValue.empty())
	{ strncpy_s(BlockDateBaseIp, sizeof( BlockDateBaseIp ), strValue.c_str(),sizeof(BlockDateBaseIp) - 1 ); }

	pGlsDB->Attribute("Port",&nValue);
	BlockDateBasePort = nValue;

	strValue = pGlsDB->Attribute("User");
	if (!strValue.empty())
	{ strncpy_s(BlockDateBaseUser, sizeof( BlockDateBaseUser), strValue.c_str(),sizeof(BlockDateBaseUser) - 1 ); }

	strValue = pGlsDB->Attribute("Password");
	if (!strValue.empty())
	{ strncpy_s(BlockDateBasePassword, sizeof( BlockDateBasePassword ), strValue.c_str(),sizeof(BlockDateBasePassword) - 1 ); }

	strValue = pGlsDB->Attribute("Name");
	if (!strValue.empty())
	{ strncpy_s(BlockDateBaseName, sizeof( BlockDateBaseName ), strValue.c_str(),sizeof(BlockDateBaseName) - 1 ); }

    return true;
}

bool Config::InitLoginCoinfg(const char* szConfigFile)
{
	if (!szConfigFile)
	{
		return false;
	}

	TiXmlDocument doc;
	if ( !doc.LoadFile( szConfigFile ) )
	{ return false; }

	int    nValue      = 0;
	double dValue      = 0.0f;
	const char* szTemp = NULL;
	std::string        strValue;

	TiXmlElement* pProject = doc.FirstChildElement("Project");
	if ( NULL == pProject)
	{ return false; }

	TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
	if ( NULL == pSetting)
	{ return false; }
	//todo:需要什么特殊设置的配置在这里添加
	return true;
}