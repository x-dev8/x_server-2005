#include "ThreeDayConfig.h"
#include "RapidXml/MeRapidXml.h"
#ifdef GAME_CLIENT
	#include "GameMain.h"
#endif 
ThreeDayConfig::ThreeDayConfig()
{
	m_ThreeOnceVec.clear();
	m_Vision = 0;
	m_WriteTime = 0;
}
ThreeDayConfig::~ThreeDayConfig()
{
	std::vector<ThreeDayOnce*>::const_iterator Iter = m_ThreeOnceVec.begin();
	for(;Iter != m_ThreeOnceVec.end();++Iter)
	{
		delete *Iter;
	}
	m_ThreeOnceVec.clear();
}
bool ThreeDayConfig::LoadThreeDayConfig(const char* FilePath)
{
	//读取配置文件
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    { return false; }

    MeXmlElement* pThreeDay = xMeXml.FirstChildElement( "ThreeDays" );
    if ( pThreeDay == NULL )
    { return false; }

	if ( pThreeDay->Attribute( "WriteTime", &m_WriteTime ) == NULL )
    { return false; }

	if ( pThreeDay->Attribute( "Vision", &m_Vision ) == NULL )
    { return false; }

	MeXmlElement* pOnce = pThreeDay->FirstChildElement( "Once" );
    while ( pOnce != NULL )
    {
		int nYear = 0;
		if ( pOnce->Attribute( "Year", &nYear ) == NULL )
			return false;
		int nMonth=0;
		if ( pOnce->Attribute( "Month", &nMonth) == NULL )
			return false;
		int nDay=0;
		if ( pOnce->Attribute( "Day", &nDay) == NULL )
			return false;
		int nItemID = 0;
		if ( pOnce->Attribute( "Item", &nItemID ) == NULL )
			return false;
		int nItemSum = 0;
		if ( pOnce->Attribute( "ItemSum", &nItemSum) == NULL )
			return false;
		int nValue = 0;
		if ( pOnce->Attribute( "Value", &nValue) == NULL )
			return false;
		ThreeDayOnce* st = new ThreeDayOnce();
		st->nYear = nYear;
		st->nMonth = nMonth;
		st->nDay = nDay;
		st->nItemID = nItemID;
		st->nItemSum = nItemSum;
		st->nValue = nValue;
		m_ThreeOnceVec.push_back(st);
		pOnce = pOnce->NextSiblingElement();
	}
	return true;
}
const ThreeDayOnce* ThreeDayConfig::GetNowDayThreeDayOnceInfo()
{
	if(m_ThreeOnceVec.empty())
		return NULL;
	else
	{
		time_t now;		
		time(&now);	
		//如果是客户端我们需要处理 客户端时间转换为服务器时间
#ifdef GAME_CLIENT
		now +=theHeroGame.GetServerAndLocalOffsetTime();
#endif 
		struct tm *fmt;	
		fmt = localtime(&now);
		std::vector<ThreeDayOnce*>::const_iterator Iter = m_ThreeOnceVec.begin();
		for(;Iter != m_ThreeOnceVec.end();++Iter)
		{
			if((*Iter)->IsOnceDay(fmt))
			{
				const ThreeDayOnce* pInfo = *Iter;
				return pInfo;
			}
		}
	}
	return NULL;
}