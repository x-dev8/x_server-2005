#include "Me3d/Me3d.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/MeCollector.h"

//////////////////////////////////////////////////////////////////////////
MeCollector::MeCollector()
{
	m_kItems.clear();
	m_kItems.reserve( 1000 );
	m_bUseCollector = true;
}
//////////////////////////////////////////////////////////////////////////
MeCollector::~MeCollector()
{
	MeSorter::RenderableListIter it = m_kItems.begin();
	for( ; it != m_kItems.end(); ++ it )
		( *it ).m_pRenderable = 0;		

	m_kItems.clear();
}
//////////////////////////////////////////////////////////////////////////
void MeCollector::SetEnable( bool bEnable )
{
	m_bUseCollector = bEnable;
}
//////////////////////////////////////////////////////////////////////////