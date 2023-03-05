
#include "tip_configure.h"
#include "FuncPerformanceLog.h"
#include "RapidXml/MeRapidXml.h"

CTip_Configure Tip_Configure;

#define	TIP_CONFIGURE_PATH	"CONFIG\\TipConfigure.xml"

CTip_Configure::CTip_Configure()
{
	guardfunc;
	mapOccuption_TipInfo.clear();
	unguard;
}
CTip_Configure::~CTip_Configure()
{
	guardfunc;
	unguard;
}
const char*	CTip_Configure::getTip(int occuption, TipConfigure type)
{
	guardfunc;

	if( type < 0 || type >= Tip_Configure_Max)
		return 0;

	if( occuption < 0 || occuption > 4 )
		return 0;

	std::map<int, Occuption_Tip_Info>::iterator iter;
	iter = mapOccuption_TipInfo.find( occuption );
	if( iter != mapOccuption_TipInfo.end() )
	{
		return iter->second.tip_configure[type].c_str(); 
	}

	return NULL;
	unguard;
}
void CTip_Configure::load()
{
	guardfunc;
	MeXmlDocument	m_MeXmlDoc;
	if( !m_MeXmlDoc.LoadFile(TIP_CONFIGURE_PATH) )
	{
		OutputDebugString("tip_configure.cpp::load 读取文件出错\n");
		return;
	}

	const char* szValue = NULL;
	int mapIndex_of_occuptionTipInfo = 0;
	
	MeXmlElement* pClient = m_MeXmlDoc.FirstChildElement("client");
	if( pClient )
	{
		MeXmlElement* rolrProperty = pClient->FirstChildElement("roleProperty");
		if( rolrProperty )
		{
			MeXmlElement* occuption = rolrProperty->FirstChildElement("occupation");
			while( occuption )
			{
				occuption->Attribute( "id", &mapIndex_of_occuptionTipInfo);
				Occuption_Tip_Info tip_TextInfo;
				int tipInfo_id;

				MeXmlElement* tipInfo = occuption->FirstChildElement("tipinfo");
				while( tipInfo )
				{
					tipInfo->Attribute( "id", &tipInfo_id );
					szValue = tipInfo->Attribute( "tip" );
					if( szValue )
					{
						tip_TextInfo.tip_configure[tipInfo_id] = szValue;
					}

					tipInfo = tipInfo->NextSiblingElement();
				}

				mapOccuption_TipInfo[mapIndex_of_occuptionTipInfo] = tip_TextInfo;

				occuption = occuption->NextSiblingElement();
			}
		}
	}
	unguard;
}