#include <RapidXml/MeRapidXml.h>
#include "WeatherEventConfig.h"
//////////////////////////////////////////////////////////////////////////
bool WeatherEventConfig::LoadWeatherEventConfig( const std::string& strFilename )
{
	MeXmlDocument kDocument;
	if( !kDocument.LoadFile( strFilename.c_str() ) )
	{
		assert( "天气系统配置文件读取错误。" );
		return false;
	}

	MeXmlElement* pRoot = kDocument.FirstChildElement( "Project" );
	if( !pRoot )
	{
		assert( "Weather ERROR: XML Read, Project.");
		return false;
	}

	pRoot = pRoot->FirstChildElement( "WeatherTimelines" );
	if( !pRoot )
	{
		assert( "Weather ERROR: XML Read, WeatherTimeline.");
		return false;
	}

	// 遍历WeatherTimeline
	MeXmlElement* pTimelineNode = pRoot->FirstChildElement( "WeatherTimeline" );
	while( pTimelineNode )
	{
		int nMapId = 0;
		if( MEXML_SUCCESS != pTimelineNode->QueryIntAttribute( "MapId", &nMapId ) )
		{
			assert( "Weather ERROR: XML Read, MapId." );
			return false;
		}
		float fTimeRatio = 0.f;
		if( MEXML_SUCCESS != pTimelineNode->QueryFloatAttribute( "TimeRatio", &fTimeRatio ) )
		{
			assert( "Weather ERROR: XML Read, TimeRatio." );
			return false;
		}

		WeatherTimelineData kTimelineData;
		kTimelineData.m_nMapId = nMapId;
		kTimelineData.m_fTimeRatio = fTimeRatio;

		// 遍历Event。
		MeXmlElement* pEventNode = pTimelineNode->FirstChildElement( "Event" );
		while( pEventNode )
		{
			int nType = 0;
			if( MEXML_SUCCESS != pEventNode->QueryIntAttribute( "Type", &nType ) )
			{
				assert( "Weather ERROR: XML Read, Type." );
				return false;
			}
			
			WeatherEventData kEvent;

			// 设置类型。
			kEvent.m_nType = nType;

			// 根据类型创建对象。
			switch( nType )
			{
			case EWET_CloudySky:
				{
					if( !LoadCloudySkyConfig( pEventNode, &kEvent ) )
					{ return false; }
				}
				break;
			case EWET_Rainy:
				{
					if( !LoadRainyConfig( pEventNode, &kEvent ) )
					{ return false; }
				}
				break;
			case EWET_Sound:
				{
					if( !LoadSoundConfig( pEventNode, &kEvent ) )
					{ return false; }
				}
				break;
			case EWET_Snowy:
				{
					if (!LoadSnowyConfig(pEventNode, &kEvent))
					{ return false; }
				}
				break;
			default:
				break;
			}

			// 添加到时间轴数据。
			kTimelineData.m_WeatherEvents.push_back( kEvent );

			pEventNode = pEventNode->NextSiblingElement( "Event" );
		}

		// 添加该时间轴。				
		if( m_Events.find( nMapId ) == m_Events.end() )
		{
			m_Events.insert( std::make_pair( nMapId, kTimelineData ) );
		}

		pTimelineNode = pTimelineNode->NextSiblingElement( "WeatherTimeline" );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool WeatherEventConfig::LoadShadeEventConfig( MeXmlElement* pElement, WeatherEventData* pEvent )
{
	if( !pElement || !pEvent )
	{ return false; }

	// 获得开始时间。
	const char* pcTime = pElement->Attribute( "StartTime" );
	if( !pcTime )
	{
		assert( "Weather ERROR: XML Read, StartTime." );
		return false;
	}

	__int64 n64Time = _atoi64( pcTime );
	if( n64Time == -1 )
	{
		assert( "Weather ERROR: XML Read, StartTimeValue." );
		return false;
	}
	pEvent->m_uiStartTime = ( unsigned int )n64Time;


	// 获得结束时间。
	pcTime = pElement->Attribute( "EndTime" );
	if( !pcTime )
	{
		assert( "Weather ERROR: XML Read, EndTime." );
		return false;
	}

	n64Time = _atoi64( pcTime );
	if( n64Time == -1 )
	{
		assert( "Weather ERROR: XML Read, EndTimeValue." );
		return false;
	}
	pEvent->m_uiEndTime = ( unsigned int )n64Time;


	// 获得从无到有的时间。
	pcTime = pElement->Attribute( "ToFull" );
	if( !pcTime )
	{
		assert( "Weather ERROR: XML Read, ToFull." );
		return false;
	}

	n64Time = _atoi64( pcTime );
	if( n64Time == -1 )
	{
		assert( "Weather ERROR: XML Read, ToFullValue." );
		return false;
	}
	pEvent->m_uiToFull =  ( unsigned int )n64Time;

	// 获得结束时间。
	pcTime = pElement->Attribute( "ToEnd" );
	if( !pcTime )
	{
		assert( "Weather ERROR: XML Read, ToEnd." );
		return false;
	}

	n64Time = _atoi64( pcTime );
	if( n64Time == -1 )
	{
		assert( "Weather ERROR: XML Read, ToEndValue." );
		return false;
	}
	pEvent->m_uiToEnd = ( unsigned int )n64Time;

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool WeatherEventConfig::LoadCloudySkyConfig( MeXmlElement* pElement, WeatherEventData* pEvent )
{
	if( !LoadShadeEventConfig( pElement, pEvent ) )
	{ return false; }

	// 获得目标环境光
	const char* pcColor = pElement->Attribute( "DestAmbient" );
	if( !pcColor )
	{
		assert( "Weather ERROR: XML Read, DestAmbient." );
		return false;
	}				
	int a = 0, r = 0, g = 0, b = 0;
	sscanf( pcColor, "%d,%d,%d,%d", &a, &r, &g, &b );
	unsigned int dwColor = ( (( a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
	pEvent->m_kCloudyData.m_uiDestAmbient = dwColor;								

	// 获得目标漫射光
	pcColor = pElement->Attribute( "DestDiffuse" );
	if( !pcColor )
	{
		assert( "Weather ERROR: XML Read, DestDiffuse." );
		return false;
	}				
	sscanf( pcColor, "%d,%d,%d,%d", &a, &r, &g, &b );
	dwColor = ( (( a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff) );
	pEvent->m_kCloudyData.m_uiDestDiffuse = dwColor;

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool WeatherEventConfig::LoadRainyConfig( MeXmlElement* pElement, WeatherEventData* pEvent )
{
	if( !LoadShadeEventConfig( pElement, pEvent ) )
	{ return false; }

	// 获得路径。
	const char* pcValue = pElement->Attribute( "Filename" );
	if( pcValue )
	{
		strcpy_s( pEvent->m_kRainyData.m_acFilename, WeatherData::MAXPATH - 1, pcValue );
	}

	// 获得速度。
	pcValue = pElement->Attribute( "RainSpeed" );
	if( !pcValue )
	{
		assert( "Weather ERROR: XML Read, RainSpeed." );
		return false;		
	}
	float fSpeed = ( float )atof( pcValue );
	pEvent->m_kRainyData.m_fRainSpeed = fSpeed;

	// 获得范围。
	pcValue = pElement->Attribute( "RainyRange" );
	if( !pcValue )
	{
		assert( "Weather ERROR: XML Read, RainyRange." );
		return false;		
	}
	int nRange = atoi( pcValue );
	pEvent->m_kRainyData.m_nRainyRange = nRange;

	// 获得雨点的长度。
	pcValue = pElement->Attribute( "RaindropHeight" );
	if( !pcValue )
	{
		assert( "Weather ERROR: XML Read, RaindropHeight." );
		return false;
	}
	float fHeight = ( float )atof( pcValue );
	pEvent->m_kRainyData.m_fRaindropHeight = fHeight;

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool WeatherEventConfig::LoadSoundConfig( MeXmlElement* pElement, WeatherEventData* pEvent )
{
	if( !LoadShadeEventConfig( pElement, pEvent ) )
	{ return false; }

	// Filename.
	const char* pcValue = pElement->Attribute( "Filename" );
	if( !pcValue )
	{
		assert( "Weather ERROR: XML Read, SoundFilename." );
		return false; 
	}

	strcpy_s( pEvent->m_kSoundData.m_acFilename, WeatherData::MAXPATH - 1, pcValue );

	// Loop。可不填，默认不循环。
	pcValue = pElement->Attribute( "Loop" );
	pEvent->m_kSoundData.m_bLoop = false;
	if( pcValue )
	{
		int nLoop = atoi( pcValue );
		pEvent->m_kSoundData.m_bLoop = ( nLoop == 1 );
	}

	return true;
}

bool WeatherEventConfig::LoadSnowyConfig( MeXmlElement* pElement, WeatherEventData* pEvent )
{
	if (!LoadShadeEventConfig(pElement, pEvent))
	{ return false; }

	// 雪花大小
	const char *pcValue = pElement->Attribute( "SnowSize" );
	if ( !pcValue )
	{
		assert( "Weather ERROR: XML Read, SnowSize." );
		return false;		
	}
	pEvent->m_kSnowyData.m_fSnowFlakeSize = (float) atof(pcValue);

	// 速度
	pcValue = pElement->Attribute( "SnowSpeed" );
	if ( !pcValue )
	{
		assert( "Weather ERROR: XML Read, SnowSpeed." );
		return false;
	}
	pEvent->m_kSnowyData.m_fSnowSpeed = (float) atof(pcValue);

	// 数量
	pcValue = pElement->Attribute( "SnowCount" );
	if ( !pcValue )
	{
		assert( "Weather ERROR: XML Read, SnowCount." );
		return false;
	}
	pEvent->m_kSnowyData.m_nSnowCount = atoi(pcValue);

	return true;
}