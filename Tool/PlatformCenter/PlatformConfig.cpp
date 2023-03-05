#include "PlatformConfig.h"
#include "tinyxml.h"

CPlatFormConfig::CPlatFormConfig(void)
{
	ListenPort = 0;
	strTaskDatabaseUser.clear();
	strTaskDatabasePwd.clear();
	strTaskDatabaseName.clear();
	strTaskDatabaseIP.clear();
	TaskDatabasePort = 0;

	//strAccountDatabaseUser.clear();
	//strAccountDatabasePwd.clear();
	//strAccountDatabaseName.clear();
	openCheckService = false;

	/*strLogDatabaseUser.clear();
	strLogDatabasePwd.clear();
	strLogDatabaseName.clear();*/
}

CPlatFormConfig::~CPlatFormConfig(void)
{
}

bool CPlatFormConfig::LoadConfig()
{
	const char* filename = "PlatformConfig.config";
	TiXmlDocument doc;
	if( !doc.LoadFile( filename))
	{
		assert( false && "load PlatformConfig.config error!" );
		return false;
	}

	int nvalue = 0;
	TiXmlElement *lproot = doc.FirstChildElement("root");
	if( !lproot)
		return false;
	else
	{
		TiXmlElement *lpservice = lproot->FirstChildElement("service");
		if( !lpservice)
			return false;
		lpservice->QueryIntAttribute("listenserverPort", &nvalue);
		ListenPort = nvalue;
		lpservice->QueryIntAttribute("listenclientPort", &nvalue);
		ListenClientPort = nvalue;
		lpservice->QueryIntAttribute("checkclientservice", &nvalue);
		openCheckService = nvalue;

		TiXmlElement *lptaskdatabase = lproot->FirstChildElement("taskdatabase");
		if( !lptaskdatabase)
			return false;
		strTaskDatabaseUser = lptaskdatabase->Attribute("user");
		strTaskDatabasePwd = lptaskdatabase->Attribute("pwd");
		strTaskDatabaseName = lptaskdatabase->Attribute("name");
		strTaskDatabaseIP = lptaskdatabase->Attribute("ip");
		lptaskdatabase->QueryIntAttribute("port", &nvalue);
		TaskDatabasePort = nvalue;

		/*TiXmlElement *lpaccountdatabase = doc.FirstChildElement("accountdatabase");
		if( !lpaccountdatabase)
			return false;
		strAccountDatabaseUser = lpaccountdatabase->Attribute("user");
		strAccountDatabasePwd = lpaccountdatabase->Attribute("pwd");
		strAccountDatabaseName = lpaccountdatabase->Attribute("name");		*/

		/*TiXmlElement *lplogdatabase = doc.FirstChildElement("logdatabase");
		if( !lplogdatabase)
			return false;
		strLogDatabaseUser = lplogdatabase->Attribute("user");
		strLogDatabasePwd = lplogdatabase->Attribute("pwd");
		strLogDatabaseName = lplogdatabase->Attribute("name");*/
	}

	return true;
}