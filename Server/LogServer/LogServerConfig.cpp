#include "LogServerConfig.h"
#include "tinyxml.h"

LogServerConfig::LogServerConfig(void)
{
	ListenPort = 0;

	strOnlineInfoUser.clear();
	strOnlineInfoPwd.clear();
	strOnlineInfoName.clear();
	strOnlineInfoIP.clear();
	OnlineInfoPort = 0;

	strItemInfoUser.clear();
	strItemInfoPwd.clear();
	strItemInfoName.clear();
	strItemInfoIP.clear();
	ItemInfoPort = 0;

	strPlayerInfoUser.clear();
	strPlayerInfoPwd.clear();
	strPlayerInfoName.clear();
	strPlayerInfoIP.clear();
	PlayerInfoPort = 0;

	strSystemInfoUser.clear();
	strSystemInfoPwd.clear();
	strSystemInfoName.clear();
	strSystemInfoIP.clear();
	SystemInfoPort = 0;
}

LogServerConfig::~LogServerConfig(void)
{
}

bool LogServerConfig::LoadConfig()
{
	const char* filename = "LogServer.config";
	TiXmlDocument doc;
	if( !doc.LoadFile( filename))
	{
		assert( false && "load LogServer.config error!" );
		return false;
	}

	int nvalue = 0;
	TiXmlElement *lproot = doc.FirstChildElement("Project");
	if( !lproot)
		return false;
	else
	{
		TiXmlElement *lpservice = lproot->FirstChildElement("service");
		if( !lpservice)
			return false;
		lpservice->QueryIntAttribute("listenserverPort", &nvalue);
		ListenPort = nvalue;

		TiXmlElement *lponlineinfo = lproot->FirstChildElement("onlineinfo");
		if( !lponlineinfo)
			return false;
		strOnlineInfoUser = lponlineinfo->Attribute("user");
		strOnlineInfoPwd = lponlineinfo->Attribute("pwd");
		strOnlineInfoName = lponlineinfo->Attribute("name");
		strOnlineInfoIP = lponlineinfo->Attribute("ip");
		lponlineinfo->QueryIntAttribute("port", &nvalue);
		OnlineInfoPort = nvalue;

		TiXmlElement *lpiteminfo = lproot->FirstChildElement("iteminfo");
		if( !lpiteminfo)
			return false;
		strItemInfoUser = lpiteminfo->Attribute("user");
		strItemInfoPwd = lpiteminfo->Attribute("pwd");
		strItemInfoName = lpiteminfo->Attribute("name");
		strItemInfoIP = lpiteminfo->Attribute("ip");
		lpiteminfo->QueryIntAttribute("port", &nvalue);
		ItemInfoPort = nvalue;

		TiXmlElement *lpplayerinfo = lproot->FirstChildElement("playerinfo");
		if( !lpplayerinfo)
			return false;
		strPlayerInfoUser = lpplayerinfo->Attribute("user");
		strPlayerInfoPwd = lpplayerinfo->Attribute("pwd");
		strPlayerInfoName = lpplayerinfo->Attribute("name");
		strPlayerInfoIP = lpplayerinfo->Attribute("ip");
		lpplayerinfo->QueryIntAttribute("port", &nvalue);
		PlayerInfoPort = nvalue;

		TiXmlElement *lpsysteminfo = lproot->FirstChildElement("systeminfo");
		if( !lpsysteminfo)
			return false;
		strSystemInfoUser = lpsysteminfo->Attribute("user");
		strSystemInfoPwd = lpsysteminfo->Attribute("pwd");
		strSystemInfoName = lpsysteminfo->Attribute("name");
		strSystemInfoIP = lpsysteminfo->Attribute("ip");
		lpsysteminfo->QueryIntAttribute("port", &nvalue);
		SystemInfoPort = nvalue;
	}
	return true;
}