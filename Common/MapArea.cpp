#include "MapArea.h"
#include "NewWithDebug.h"

CMapAreaManager::CMapAreaManager()
{
	m_pStageDataLoader = NULL;
}

CMapAreaManager::~CMapAreaManager()
{
	Clear();
	if( m_pStageDataLoader )
	{
        CNewWithDebug<CStageDataLoader>::Free(m_pStageDataLoader);
		m_pStageDataLoader = NULL;
	}
}

int CMapAreaManager::GetMaxArea()
{
    CSALocker lock(_lock);
    return (int)m_vectorAreaStore.size();
}

int CMapAreaManager::AddArea( const char *szName, LPRECT rect )
{
    SArea sa;
    sa.m_strName = szName;
    RECT& r = sa.m_rcArea;
    r.left = rect->left;
    r.top = rect->top;
    r.right = rect->right;
    sa.m_rcArea.bottom = rect->bottom;
	sa.m_istep = 0;
    
    int id = (int)m_vectorAreaStore.size();

    m_vectorAreaStore.push_back( sa );
    
    m_mapAreaStore.insert( std::pair< std::string, int >( sa.m_strName, id ) );
    
    return id;
}

int CMapAreaManager::AddArea( const char *szName, LPRECT rect, int istep )
{
	SArea sa;
	sa.m_strName = szName;
	RECT& r = sa.m_rcArea;
	r.left = rect->left;
	r.top = rect->top;
	r.right = rect->right;
	sa.m_rcArea.bottom = rect->bottom;
	sa.m_istep = istep;

	int id = (int)m_vectorAreaStore.size();

	m_vectorAreaStore.push_back( sa );

	m_mapAreaStore.insert( std::pair< std::string, int >( sa.m_strName, id ) );

	return id;
}

int CMapAreaManager::AddArea( SArea sa )
{
	int id = (int)m_vectorAreaStore.size();

	m_vectorAreaStore.push_back( sa );

	m_mapAreaStore.insert( std::pair< std::string, int >( sa.m_strName, id ) );

	return id;
}

SArea* CMapAreaManager::GetAreaByID( int id )
{
    CSALocker lock(_lock);
    if( id<0 || id >= (int)m_vectorAreaStore.size() )
        return NULL;

    return &m_vectorAreaStore[id];
}

SArea* CMapAreaManager::GetAreaByName( const char *szName )
{
    CSALocker lock(_lock);
    std::string strName = szName;
    std::map< std::string, int >::iterator it = m_mapAreaStore.find( strName );
    if( it == m_mapAreaStore.end() )
        return NULL;

    return GetAreaByID( it->second );
}

void CMapAreaManager::Clear()
{
    CSALocker lock(_lock);
    m_vectorAreaStore.clear();
    m_mapAreaStore.clear();
}

void CMapAreaManager::loadXML( CStageDataLoader* pStageDataLoader, XMLElement* element, int nZoneNumber )
{
	SArea sa_Area;
	//char Buffer[10];
	//ltoa( nZoneNumber, Buffer, 10 );

	pStageDataLoader->GetValue( sa_Area.m_strName, element->getChildByName( "Name" ) );
	pStageDataLoader->GetValue( sa_Area.m_rcArea.left, element->getChildByName( "Left" ) );
	pStageDataLoader->GetValue( sa_Area.m_rcArea.top, element->getChildByName( "Top" ) );
	pStageDataLoader->GetValue( sa_Area.m_rcArea.right, element->getChildByName( "Right" ) );
	pStageDataLoader->GetValue( sa_Area.m_rcArea.bottom, element->getChildByName( "Bottom" ) );
	pStageDataLoader->GetValue( sa_Area.m_istep, element->getChildByName( "AIStep" ) );
	pStageDataLoader->GetValue( sa_Area.m_nPKMode, element->getChildByName( "CanPK" ) );
	sa_Area.m_bCanDuel = true;
	if(element->getChildByName( "CanDuel" ))
	{
		int duelValue = 0;
		pStageDataLoader->GetValue(  duelValue, element->getChildByName( "CanDuel" ) );
		sa_Area.m_bCanDuel = duelValue > 0 ;
	}
	
	//pStageDataLoader->GetValue( sa_Area.m_bMapGuildPK, element->getChildByName( "MapGuildCanPK" ) );//zj

    pStageDataLoader->GetValue( sa_Area.m_bPrivateShop, element->getChildByName( "CanPrivateShop" ) );
	pStageDataLoader->GetValue( sa_Area.m_strEnterScript, element->getChildByName( "EnterScript" ) );
	pStageDataLoader->GetValue( sa_Area.m_strLeaveScript, element->getChildByName( "LeaveScript" ) );

#ifdef _CLIENT_
	LoadMonserAction(element,sa_Area);
#endif

	AddArea( sa_Area );
}

#ifdef _CLIENT_
void CMapAreaManager::LoadMonserAction(XMLElement *element,SArea &area)
{   
	// NPC动作+说话
	area.vctActionData.clear();

	XMLElement* AutoTalksChild = NULL;
	for ( int idx = 0; idx < element->getChildrenCount(); ++idx )
	{
		if ( !( AutoTalksChild = element->getChild(idx) ) )
		{
			continue;
		}

		if (AutoTalksChild->getName() == "AutoTalks")
		{
			XMLElement *StageChild = NULL;
			for (int i = 0;i < AutoTalksChild->getChildrenCount();++i)
			{
				if( !(StageChild = AutoTalksChild->getChild(i)))
					continue;

				if(StageChild->getName() == "AutoTalk")
				{
					SArea::AreaActionData actionData;
					XMLElement *pElem = StageChild->getChildByName("Id");
					if(pElem)
						actionData.shId = pElem->getValuei();

					pElem = StageChild->getChildByName("Time");
					if(pElem)
						actionData.shElapseTime = pElem->getValuei();

					pElem = StageChild->getChildByName("NextTimeId");
					if(pElem)
						actionData.shNextId = pElem->getValuei();

					XMLElement *ElapseChild = NULL;
					for (int j = 0; j < StageChild->getChildrenCount();++j)
					{
						if(!(ElapseChild = StageChild->getChild(j)))
							continue;

						/*	if(ElapseChild->getName() == "Actions")
						{
						for (int z = 0; z < ElapseChild->getChildrenCount();++z)
						{
						XMLElement *pAction = NULL;
						if(!(pAction = ElapseChild->getChild(z)))
						continue;

						if(pAction->getName() == "Action")
						{
						SArea::ActionData action;
						XMLElement *pElem = pAction->getChildByName("Name");
						if(pElem)
						action.strAnimName = pElem->getValues();

						pElem = pAction->getChildByName("Probability");
						if(pElem)
						action.shProbability = pElem->getValuei();

						actionData.vctActions.push_back(action);
						}
						}
						}*/
						if(ElapseChild->getName() == "Talks")
						{
							for (int z = 0; z < ElapseChild->getChildrenCount();++z)
							{
								XMLElement *pTalk = NULL;
								if(!(pTalk = ElapseChild->getChild(z)))
									continue;

								if(pTalk->getName() == "Talk")
								{
									SArea::TalkData data;

									XMLElement *pElem = pTalk->getChildByName("StringId");
									if(pElem)
										data.shStringId = pElem->getValuei();

									pElem = pTalk->getChildByName("Probability");
									if(pElem)
										data.shProbability = pElem->getValuei();

									actionData.vctTalks.push_back(data);
								}
							}
						}
					}
					area.vctActionData.push_back(actionData);
				}
			}
		}
	}
}
#endif

void CMapAreaManager::exportXML( CStageDataLoader* pStageDataLoader, int i )
{
		SArea *pArea = GetAreaByID( i );

		//char Buffer[10];
		//ltoa( i, Buffer, 10 );

		pStageDataLoader->beginFlag( "ZoneInfo" );
		pStageDataLoader->writeString( "Name", pArea->m_strName.c_str(), pArea->m_strName.length() );
		//pStageDataLoader->writeString( "Name", Buffer, strlen(Buffer) );
		pStageDataLoader->writeInt( "Left", pArea->m_rcArea.left );
		pStageDataLoader->writeInt( "Top", pArea->m_rcArea.top );
		pStageDataLoader->writeInt( "Right", pArea->m_rcArea.right );
		pStageDataLoader->writeInt( "Bottom", pArea->m_rcArea.bottom );
		pStageDataLoader->writeInt( "AIStep", pArea->m_istep );
		pStageDataLoader->writeInt( "CanPK", pArea->m_nPKMode );
		pStageDataLoader->writeInt( "CanDuel", pArea->m_bCanDuel );
		//pStageDataLoader->writeBool( "MapGuildCanPK", pArea->m_bMapGuildPK );

	    pStageDataLoader->writeBool( "CanPrivateShop", pArea->m_bPrivateShop );
		pStageDataLoader->writeString( "EnterScript", pArea->m_strEnterScript.c_str(), pArea->m_strEnterScript.length() );
		pStageDataLoader->writeString( "LeaveScript", pArea->m_strLeaveScript.c_str(), pArea->m_strLeaveScript.length() );
		
		pStageDataLoader->EndParam();
		pStageDataLoader->endFlag( "ZoneInfo" );
		pArea = NULL;
}

bool CMapAreaManager::loadXMLSettings( const char *path )
{
	bool bLoadSuccess;

	Clear();

	if( !m_pStageDataLoader )
	{
        m_pStageDataLoader = CNewWithDebug<CStageDataLoader>::Alloc(1, "CMapAreaManager::loadXMLSettings中创建m_pStageDataLoader");
	//	delete m_pStageDataLoader;
	}
	else
	{
		m_pStageDataLoader->Clear();
	}

	m_pStageDataLoader->SetMapAreaManager( this );

	bLoadSuccess = m_pStageDataLoader->loadXMLSettings( path );

	return bLoadSuccess;
}

bool CMapAreaManager::exportXMLSettings( const char* xmlPath )
{
	bool bExportSuccess = false;

	if( !m_pStageDataLoader )
	{
        m_pStageDataLoader = CNewWithDebug<CStageDataLoader>::Alloc(1, "CMapAreaManager::exportXMLSettings中创建m_pStageDataLoader");
	}

	m_pStageDataLoader->SetMapAreaManager( this );

	bExportSuccess = m_pStageDataLoader->exportXMLSettings( xmlPath );

	return bExportSuccess;
}