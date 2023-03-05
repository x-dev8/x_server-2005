
#include "compoundInfo_configure.h"
#include "FuncPerformanceLog.h"
#include "RapidXml/MeRapidXml.h"
#include "Cfg.h"

#define COMPOUND_XML_ROOT "CompoundInfo"
CCompoundInfo_configure g_compoundInfo_configure;

CCompoundInfo_configure::CCompoundInfo_configure()
{
	guardfunc;
	unguard;
}

CCompoundInfo_configure::~CCompoundInfo_configure()
{
	guardfunc;
	unguard;
}

compoundInfo_item*	CCompoundInfo_configure::getCompoundInfo( int id )
{
	guardfunc;
	std::map<int, compoundInfo_item>::iterator i = map_compoundInfoConfigure.find( id );
	if( i != map_compoundInfoConfigure.end() )
	{
		return &i->second;
	}
	return NULL;
	unguard;
}

std::vector<int> CCompoundInfo_configure::getVecItemId( int type )	//通过配置的type类型得到 属于此类型的item容器
{
	guardfunc;

	std::vector<int> result;

	std::map<int, compoundInfo_item>::iterator i = map_compoundInfoConfigure.begin();
	for( ; i != map_compoundInfoConfigure.end(); ++i )
	{
		if( i->second._type == type )
		{
			result.push_back( i->second._itemid );
		}
	}

	return result;
	unguard;
}

int CCompoundInfo_configure::getCompoundId( int itemid )
{
	guardfunc;
	std::map<int, compoundInfo_item>::iterator i = map_compoundInfoConfigure.begin();
	for( ; i != map_compoundInfoConfigure.end(); ++i )
	{
		if( i->second._itemid == itemid )
		{
			return i->second._compoundid;
		}
	}
	return -1;
	unguard;
}

compoundInfo_item* CCompoundInfo_configure::getCompoundInfoByItemId( int itemid )	//通过配置的id 得到 描述的名字
{
	guardfunc;
	std::map<int, compoundInfo_item>::iterator i = map_compoundInfoConfigure.begin();
	for( ; i != map_compoundInfoConfigure.end(); ++i )
	{
		if( i->second._itemid == itemid )
		{
			return &i->second;
		}
	}
	return NULL;
	unguard;
}

void CCompoundInfo_configure::load()
{
	guardfunc;

	if( !map_compoundInfoConfigure.empty() )
		return;

	MeXmlDocument	doc;
	if( !doc.LoadFile(XML_GLOBALCONFIG_FILENAME) )
	{
		assert(false && "compoundInfo_configure.cpp::load 读取文件不错");
		return;
	}
// 	MeXmlHandle hDoc(&doc);

	int		id = 0;
	int		compoundid = 0;
	int		itemId = 0;
	int		type = 0;
	const char* descriptionName = NULL;
	const char* npcName = NULL;

	compoundInfo_item info;
	memset( &info, 0, sizeof(info) );
	MeXmlElement* pGlobalRoot = doc.FirstChildElement( XML_GLOBALCONFIG_ROOT_NAME );
	if( !pGlobalRoot )
		return;
	MeXmlElement* pRoot = pGlobalRoot->FirstChildElement( COMPOUND_XML_ROOT );
	if( !pRoot )
		return;

	MeXmlElement* pElem = pRoot->FirstChildElement( "compose");
	if( !pElem )
		return;

	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{
		pElem->QueryIntAttribute("id", &id);
		pElem->QueryIntAttribute("compoundid", &compoundid);
		pElem->QueryIntAttribute("itemid", &itemId);
		pElem->QueryIntAttribute("type", &type);
		descriptionName = pElem->Attribute("itemname");
		npcName = pElem->Attribute("npcname");

		if( descriptionName && npcName )
		{
			info._compoundid = compoundid;
			info._itemid = itemId;
			info._descriptionName = descriptionName;
			info._type = type;
			info._npcName = npcName;

			map_compoundInfoConfigure[id] = info;
		}
	}

	unguard;
}