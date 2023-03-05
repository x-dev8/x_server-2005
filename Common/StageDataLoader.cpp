#include "StageDataLoader.h"
#include "MapArea.h"
#include "MonsterConfig.h"

CStageDataLoader::CStageDataLoader( void ):
	IOXMLObjectInstance( "Stage" )
{
	m_pMapAreaManager = NULL;
	m_pMonsterConfig = NULL;
	m_bMapAreaManagerNew = false;
	m_bMonsterConfigNew =false;
}

CStageDataLoader::~CStageDataLoader()
{
	if( m_pMapAreaManager && m_bMapAreaManagerNew ) 
	{
		delete m_pMapAreaManager;
		m_pMapAreaManager = NULL;
	}
	if( m_pMonsterConfig && m_bMonsterConfigNew ) 
	{
		delete m_pMonsterConfig;
		m_pMonsterConfig = NULL;
	}

}

bool CStageDataLoader::loadXMLSettings( const char *path )
{
	return IOXMLObject::loadXMLSettings( path );
}

void CStageDataLoader::GetValue( std::string &strValue, XMLElement* element )
{
	if( element )
	{
		strValue = element->getValuec();
	}
}

void CStageDataLoader::GetValue( long &lValue, XMLElement* element )
{
	if( element )
	{
		lValue = element->getValuei();
	}
}

void CStageDataLoader::GetValue( int &nValue, XMLElement* element )
{
	if( element )
	{
		nValue = element->getValuei();
	}
}

void CStageDataLoader::GetValue( char* cValue, XMLElement* element, int nLength )
{
	if( element )
	{
		int nlen = sizeof(cValue);
		memcpy( cValue, element->getValues().c_str(), element->getValues().length() );
		//cValue = element->getValuec();
	}
}

void CStageDataLoader::GetValue( float &fValue, XMLElement* element )
{
	if( element )
	{
		fValue = element->getValuef();
	}
}

void CStageDataLoader::GetValue( bool &bValue, XMLElement* element )
{
	if( element )
	{
		bValue = element->getValueb();
	}
}

void CStageDataLoader::GetValue( BYTE &byValue, XMLElement* element )
{
	if( element )
	{
		byValue = element->getValuei();
	}
}

void CStageDataLoader::GetValue( const char* cValue, XMLElement* element )
{
	if( element )
	{
		cValue = element->getValuec();
	}
}

void CStageDataLoader::GetValue( short &stValue, XMLElement* element )
{
	if( element )
	{
		stValue = element->getValuei();
	}
}

bool CStageDataLoader::loadXMLSettings( XMLElement *element )
{
	if(!isSuitable(element))
		return false;

	XMLElement  *StageChild				= NULL;
	XMLElement  *ZoneChild				= NULL;

	for( int i = 0; i < element->getChildrenCount(); i++)
	{
		if( !( StageChild = element->getChild(i) )  )
			continue;

		if( StageChild->getName() == "Zone" )
		{
			if ( !m_pMapAreaManager )
			{
				m_pMapAreaManager = new CMapAreaManager;
				m_bMapAreaManagerNew = true;
			}

			for( int j = 0; j < StageChild->getChildrenCount(); j++ )
			{
				if( !( ZoneChild = StageChild->getChild(j) ) )
					continue;

				if ( ZoneChild->getName() == "ZoneInfo" )
				{
					m_pMapAreaManager->loadXML( this, ZoneChild, j );
				}
			}
		}

		if( StageChild->getName() == "Monster" )
		{
			if( !m_pMonsterConfig )
			{
				m_pMonsterConfig = new CMonsterConfig;
				m_bMonsterConfigNew = true;
			}

			for( int j = 0; j < StageChild->getChildrenCount(); j++ )
			{
				if( !( ZoneChild = StageChild->getChild(j) ) )
					continue;

				if ( ZoneChild->getName() == "MonsterGroup" )
				{
					m_pMonsterConfig->loadXML( this, ZoneChild, i );
				}
			}
		}
	}
	StageChild				= NULL;
	ZoneChild				= NULL;
	return true;
}

bool CStageDataLoader::exportXMLSettings( const char* xmlPath )
{
	bool bRet = true;
	//closeFile();
	m_xmlFile.open(xmlPath);
	bRet = exportXMLSettings( m_xmlFile );
	//m_xmlFile.close();
	closeFile();
	return bRet;
}

bool CStageDataLoader::exportXMLSettings( std::ofstream &xmlFile )
{
	if( !xmlFile.is_open() )
	{
		return false;
	}

	if( !m_pMapAreaManager )
	{
		m_pMapAreaManager = new CMapAreaManager;
		m_bMonsterConfigNew = true;
	}

	int nAreaNumber = m_pMapAreaManager->GetMaxArea();

	this->beginFlagNoParam( "Stage" );

	this->beginFlagNoParam( "Zone" );
	for( int i = 0; i < nAreaNumber; i++ )
	{
		m_pMapAreaManager->exportXML( this, i );
	}
	this->endFlag( "Zone" );

	if ( !m_pMonsterConfig )
	{
		m_pMonsterConfig = new CMonsterConfig;
		m_bMonsterConfigNew = true;
	}

	int nMonsterGroupNumber = m_pMonsterConfig->m_vecMonster.size();

	this->beginFlagNoParam( "Monster" );
	for( int j = 0; j < nMonsterGroupNumber; j++ )
	{
		this->beginFlagNoParam( "MonsterGroup" );
		m_pMonsterConfig->exportXML( this, j );
		this->endFlag( "MonsterGroup" );
	}
	this->endFlag( "Monster" );

	this->endFlag( "Stage" );

	return true;
}

void CStageDataLoader::SetMapAreaManager( CMapAreaManager* pMapAreaManager )
{
	m_pMapAreaManager = pMapAreaManager;
}

void CStageDataLoader::SetMonsterConfig( CMonsterConfig* pMonsterConfig )
{
	m_pMonsterConfig = pMonsterConfig;
}

CMapAreaManager* CStageDataLoader::GetMapAreaManager()
{
	return m_pMapAreaManager;
}

CMonsterConfig* CStageDataLoader::GetMonsterConfig()
{
	return m_pMonsterConfig;
}

void CStageDataLoader::Clear()
{
	if( m_pMapAreaManager )
	{
		m_pMapAreaManager->Clear();
	}

	if( m_pMonsterConfig )
	{
		m_pMonsterConfig->Clear();
	}
}

void CStageDataLoader::NewMapAreaManager()
{
	if ( !m_pMapAreaManager )
	{
		m_pMapAreaManager = new CMapAreaManager;
		m_bMonsterConfigNew = true;
	}
}

void CStageDataLoader::NewMonsterConfig()
{
	if ( !m_pMonsterConfig )
	{
		m_pMonsterConfig = new CMonsterConfig;
		m_bMonsterConfigNew = true;
	}
}