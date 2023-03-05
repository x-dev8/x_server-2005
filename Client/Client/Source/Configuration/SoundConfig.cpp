#include "SoundConfig.h"
#include "RapidXml/MeRapidXml.h"
#include <MeFoundation/MeFoundationPCH.h>
#include <MeFoundation/MeLog.h>
//////////////////////////////////////////////////////////////////////////
bool SoundConfig::LoadSoundConfig( const char* pcFilename )
{
	if( pcFilename == NULL || *pcFilename == 0 )
		return false;

	MeXmlDocument kConfig;
	if( !kConfig.LoadFile( pcFilename ) )
		return false;
	
	MeXmlElement* pkSound = kConfig.FirstChildElement( "Project" );
	if( !pkSound )
		return false;

	pkSound = pkSound->FirstChildElement( "Sounds" );
	if( !pkSound )
		return false;

	pkSound = pkSound->FirstChildElement( "Sound" );
	while( pkSound )
	{
		/// Sound Item.
		SoundItem kItem;

		int nType = -1;

		// Get sound item type;
		if( pkSound->QueryIntAttribute( "Type", &nType ) != MEXML_SUCCESS )
			break;

		// Assign value.
		if( nType < 0 || nType >= EST_Count )
		{
			MeLog::Instance()->Print( "没有这个配乐类型, Type = %d", nType );
			pkSound = pkSound->NextSiblingElement( "Sound" );
			continue;
		}

		// Assign value.
		kItem.m_eType = ( SoundConfig::ESoundType )nType;

		// Get path value.
		const char* pcPath = pkSound->Attribute( "File" );
		if( pcPath == NULL )
		{
			MeLog::Instance()->Print( "没有填写路径, Type = %d", nType );
			pkSound = pkSound->NextSiblingElement( "Sound" );
			continue;
		}

		// Assign value.
		kItem.m_strFile = pcPath;

		// Push.
		m_SoundItems.insert( std::make_pair( kItem.m_eType, kItem ) );

		pkSound = pkSound->NextSiblingElement( "Sound" );
	}

	kConfig.Clear();
	
	return true;
}
//////////////////////////////////////////////////////////////////////////
const std::string& SoundConfig::GetSoundFile( SoundConfig::ESoundType eType ) const
{
	static const std::string strNull = "";

	SoundItemConstIter itItem = m_SoundItems.find( eType );
	if( itItem != m_SoundItems.end() )// Found.	
		return ( *itItem ).second.m_strFile;
	
	return strNull;
}
//////////////////////////////////////////////////////////////////////////