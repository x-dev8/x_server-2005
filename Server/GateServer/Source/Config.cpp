#include "Config.h"
#include "GlobalDef.h"
#include "ResourcePath.h"
//#include "MeNetwork.h"
//#include "NetApi.h"
#include "Tinyxml/tinyxml.h"
#include "tstring.h"

#define SAME_STRING 0

GateServerConfig theCfg;

GateServerConfig::SOpenMap::SOpenMap()
{
    MapId  = 0;
}

GateServerConfig::GateServerConfig()
{
    gEncryptMode         = msgflag_des8;
    playerMaxOnlineCount = EConstDefine_DefaultPlayerMaxOnlineCount;
    clientMaxCountIn     = EConstDefine_DefaultClientMaxCountIn    ; 
    clientMaxCountOut    = EConstDefine_DefaultClientMaxCountOut   ;
    clientLowLvlCast     = EConstDefine_DefaultClientLowLvlCast    ;
    clientNormalLvlCast  = EConstDefine_DefaultClientNormalLvlCast ;
    gameMaxCountIn       = EConstDefine_DefaultGameMaxCountIn      ;
    gameMaxCountOut      = EConstDefine_DefaultGameMaxCountOut     ;
    gameLowLvlCast       = EConstDefine_DefaultGameLowLvlCast      ;
    gameNormalLvlCast    = EConstDefine_DefaultGameNormalLvlCast   ;
    netOfflineTime       = 2 * OneMinuteMicroSecond;
}

bool GateServerConfig::InitCommonData( const char* szConfigFile )
{
    if ( !szConfigFile )
    { return false; }

    TiXmlDocument doc;
    if (!doc.LoadFile( szConfigFile ))
    { return false; }

    int    nValue      = 0;
    double dValue      = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( !pProject)
    { return false; }

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( !pSetting)
    { return false; }
    
    TiXmlElement* pLogic = pSetting->FirstChildElement("Logic");
    if ( pLogic )
    {
        if ( pLogic->Attribute( "MaxPlayerOnline", &nValue ) )
        { playerMaxOnlineCount = nValue; }

        if ( pLogic->Attribute( "ClientPingSpaceTime", &nValue ) )
        { dwCheckClientPingMsg = nValue * 1000; }

        if (pLogic->Attribute( "ConnectOverTime", &nValue )!=NULL)
        { dwConnectOverTime = nValue * 1000; }
        else
        { dwConnectOverTime = 1000; }

        if (pLogic->Attribute( "EncryptMode", &nValue )!=NULL)
        { 
            switch ( nValue )
            {
            case 0: // 不加密明文
                { gEncryptMode = msgflag_normal; }
                break;
            case 1: // exclusive or 加密
                { gEncryptMode = msgflag_xor; }
                break;
            case 2: // DES8 加密
                { gEncryptMode = msgflag_des8; }
                break;
            case 3: // exclusive or 加密
                { gEncryptMode = msgflag_blowfish; }
                break;
            }
        }
        else
        { gEncryptMode = msgflag_xor; }

        if ( pLogic->Attribute("NetOfflineTime", &nValue ) != NULL )
        { netOfflineTime = nValue; }
    }

    TiXmlElement* pMsgQueue = pSetting->FirstChildElement("MsgQueue");
    if ( pMsgQueue )
    {
        TiXmlElement* pClient = pMsgQueue->FirstChildElement("Client");
        if ( pClient )
        {
            pClient->Attribute("MaxCountIn", &nValue );
            clientMaxCountIn = nValue;
            
            pClient->Attribute("MaxCountOut", &nValue );
            clientMaxCountOut = nValue;

            pClient->Attribute("LowLvlCast", &nValue );
            clientLowLvlCast = nValue;

            pClient->Attribute("NormalLvlCast", &nValue );
            clientNormalLvlCast = nValue;
        }

        TiXmlElement* pGamServer = pMsgQueue->FirstChildElement("GamServer");
        if ( pGamServer )
        {
            pGamServer->Attribute("MaxCountIn", &nValue );
            gameMaxCountIn = nValue;

            pGamServer->Attribute("MaxCountOut", &nValue );
            gameMaxCountIn = nValue;

            pGamServer->Attribute("LowLvlCast", &nValue );
            gameMaxCountIn = nValue;

            pGamServer->Attribute("NormalLvlCast", &nValue );
            gameMaxCountIn = nValue;
        }
    }

    return true;
}

bool GateServerConfig::InitPrivateData( const char* szConfigFile )
{
    if ( NULL == szConfigFile )
    { return false; }

    TiXmlDocument doc;
    if (!doc.LoadFile( szConfigFile ))
    { return false; }

    int    nValue      = 0;
    double dValue      = 0.0f;
    const char* szTemp = NULL;

    TiXmlElement* pProject = doc.FirstChildElement("Project");
    if ( NULL == pProject)
    { return false; }

    TiXmlElement* pSetting = pProject->FirstChildElement("Setting");
    if ( NULL == pSetting)
    { return false; }

    TiXmlElement* pMsgQueue = pSetting->FirstChildElement("MsgQueue");
    if ( pMsgQueue )
    {
        TiXmlElement* pClient = pMsgQueue->FirstChildElement("Client");
        if ( pClient )
        {
            pClient->Attribute("MaxCountIn", &nValue );
            clientMaxCountIn = nValue;

            pClient->Attribute("MaxCountOut", &nValue );
            clientMaxCountOut = nValue;

            pClient->Attribute("LowLvlCast", &nValue );
            clientLowLvlCast = nValue;

            pClient->Attribute("NormalLvlCast", &nValue );
            clientNormalLvlCast = nValue;
        }

        TiXmlElement* pGamServer = pMsgQueue->FirstChildElement("GamServer");
        if ( pGamServer )
        {
            pGamServer->Attribute("MaxCountIn", &nValue );
            gameMaxCountIn = nValue;

            pGamServer->Attribute("MaxCountOut", &nValue );
            gameMaxCountIn = nValue;

            pGamServer->Attribute("LowLvlCast", &nValue );
            gameMaxCountIn = nValue;

            pGamServer->Attribute("NormalLvlCast", &nValue );
            gameMaxCountIn = nValue;
        }
    }

    TiXmlElement* FirstElement = pSetting->FirstChildElement();
    while (NULL != FirstElement)
    {
        if ( FirstElement->Value() == NULL )
        {
            FirstElement = FirstElement->NextSiblingElement();
            continue;
        }
        else if ( stricmp( FirstElement->Value(), "Logic" ) == SAME_STRING )
        {
            if ( FirstElement->Attribute( "NetId", &nValue ) == NULL )
            { return false; }
            nGateServerId = nValue;

            bool bResult = InitNetSetting();
            if ( !bResult)
            { return false; }

            szTemp = FirstElement->Attribute( "LogConfigFile");
            if (szTemp)
            { strLogConfigFilePath = szTemp; }

            if ( NULL != FirstElement->Attribute( "MaxPlayerOnline", &nValue ) )
            { playerMaxOnlineCount = nValue; }

            if ( NULL != FirstElement->Attribute( "ClientPingSpaceTime", &nValue ))
            { dwCheckClientPingMsg = nValue * 1000; }

            if ( NULL != FirstElement->Attribute( "ConnectOverTime", &nValue ))
            { dwConnectOverTime = nValue * 1000; }
        }
        else if ( stricmp( FirstElement->Value(), "ActiveMaps" ) == SAME_STRING )
        {
            TiXmlElement* pMap = FirstElement->FirstChildElement("Map");
            while ( pMap )
            {
                int mapid = 0;
                int isOpen = 0;
                SOpenMap sOpenMap;
                if ( NULL != pMap->Attribute("Id",&mapid) )
                {
                    if (mapid < 0 )
                    { return false; }
                    sOpenMap.MapId = mapid;
					
					if ( NULL != pMap->Attribute("IsRun",&isOpen) )
					{
						sOpenMap.IsRun = isOpen;
					}
                }

                OpenMaps::iterator itr = find(OpenMaps_.begin(),OpenMaps_.end(),sOpenMap.MapId);
                if ( itr == OpenMaps_.end())
                { OpenMaps_.push_back(sOpenMap); }

                pMap = pMap->NextSiblingElement("Map");
            }
        }

        //next
        FirstElement = FirstElement->NextSiblingElement();
    }

    return true;
}

bool GateServerConfig::InitNetSetting()
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

    TiXmlElement* pGates = pSetting->FirstChildElement("Gates");
    if ( !pGates )
    { return false; }

    TiXmlElement* pGate = pGates->FirstChildElement("Gate");
    while ( pGate )
    {
        nValue = -1;
        if ( pGate->Attribute( "Id", &nValue ) )
        {
            if ( nValue == nGateServerId )
            {
                szTemp = pGate->Attribute("Name");
                if ( NULL != szTemp)
                {
                    Common::_tstring strTemp;
                    strTemp.fromUTF8( szTemp );
                    strncpy_s( szGameServerName, strTemp.c_str(), sizeof(szGameServerName) );
                }

                TiXmlElement* pService = pGate->FirstChildElement("Service");
                if ( !pService )
                { return false; }

                szTemp = pService->Attribute("Host");
                if ( NULL != szTemp )
                { strncpy_s( szForClientIP, szTemp, sizeof(szForClientIP) ); }

                strTranslateIp = /*NetApi::GetHostByName*/( std::string(szForClientIP) );
                //if ( !strTranslateIp.empty())
                //{ dwForClientIP = inet_addr( strTranslateIp.c_str() ); }

                if ( NULL != pService->Attribute("Port", &nValue))
                { nForClientGatePort = nValue; }

                TiXmlElement* pGameServer = pGate->FirstChildElement("GameServer");
                if ( !pGameServer )
                { return false; }

                szTemp = pGameServer->Attribute("Host");
                if ( NULL != szTemp )
                { strncpy_s( szGameServerIP, szTemp, sizeof( szGameServerIP )); }

                if ( NULL != pGameServer->Attribute("Port", &nValue) )
                { nGameServerPort = nValue; }

                break;
            }
        }
        pGate = pGate->NextSiblingElement("Gate");
    }

    return true;
}

bool GateServerConfig::IsMapOpen( uint32 MapId )
{
    OpenMaps::iterator itr = find( OpenMaps_.begin(),OpenMaps_.end(), MapId);
    if (itr != OpenMaps_.end())
    { return true; }
    return false;
}

bool GateServerConfig::IsMapRun(uint32 MapId)
{
	OpenMaps::iterator itr = find(OpenMaps_.begin(),OpenMaps_.end(),MapId);
	if (itr != OpenMaps_.end())
	{
		return itr->IsRun;
	}
	return false;
}
