#include "config_file.h"
#include "Tinyxml/tinyxml.h"

#define XML_SERVERINFO_LIST "login_config.xml"

CConfig::CConfig()
{
	_ListenClent_Port = 0;//监听客户端的端口

	_ListenServer_Port = 0;//监听其他服务器连接的端口

	_AccountDBIP="";//帐号数据库IP
	_AccountDBID="";//帐号数据库的用户名
	_AccountDBPWD="";//帐号数据库的密码
	_AccountDBNAME="";//帐号数据库的库名
}
CConfig::~CConfig()
{

}

bool CConfig::InitConfig()
{
	std::string filename = XML_SERVERINFO_LIST;
	TiXmlDocument doc;
	if( !doc.LoadFile( filename.c_str()) )
	{
		assert( false && "load login_config.xml error!" );
		return false;
	}
	TiXmlElement *pconfiginfo = doc.FirstChildElement("logininfo");
	if( !pconfiginfo )
		return false;
	int ListenClent_Port = 0;
	int ListenServer_Port = 0;
	pconfiginfo->QueryIntAttribute("ListenClent_Port", &ListenClent_Port );
	pconfiginfo->QueryIntAttribute("_ListenServer_Port", &ListenServer_Port );
	if (ListenServer_Port <= 0 || ListenClent_Port<= 0)
	{
		return false;
	}

	_ListenClent_Port = ListenClent_Port;
	_ListenServer_Port = ListenServer_Port;

	_AccountDBIP = pconfiginfo->Attribute("AccountDBIP");
	_AccountDBID = pconfiginfo->Attribute("AccountDBID");
	_AccountDBPWD = pconfiginfo->Attribute("AccountDBPWD");
	_AccountDBNAME = pconfiginfo->Attribute("AccountDBNAME");
	int AccountDBPORT = 0;
	pconfiginfo->QueryIntAttribute("AccountDBPORT", &AccountDBPORT );
	if (AccountDBPORT <= 0)
	{
		return false;
	}
	_AccountDBPORT = AccountDBPORT;
	return true;
}