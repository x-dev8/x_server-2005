#include "Me3d/Me3d.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/MeAlphaCollector.h"
#include "Me3d/Engine/MeCombinedRenderManager.h"

//////////////////////////////////////////////////////////////////////////
bool MeAlphaCollector::IsCollectible( MeSorter::RenderableBasePtr pkObj )
{
	if( !pkObj )
		return false;

	return pkObj->GetCollectibleType() == SortRenderable::eCT_AlphaBlend;
}
//////////////////////////////////////////////////////////////////////////
void MeAlphaCollector::DoRender()
{
	MeScopeProfileAlphaCollectorFun
	if( m_kItems.empty() )
		return;

	Sort();
	for(std::vector< SortRenderable* >::iterator iter = m_NoSortAlphaItems.begin(); iter != m_NoSortAlphaItems.end(); ++iter)
	{
		SortRenderable* pRenderable = ( *iter ); 
		if(MeCombinedRenderManager::Instance()->TryCombinedRender(pRenderable,true))
		{
			continue;
		}
		else
		{
			MeCombinedRenderManager::Instance()->DoCombinedRender();
			pRenderable->DoRender(true);
		}
		pRenderable->DoRender(true);
	}
	MeCombinedRenderManager::Instance()->DoCombinedRender();
	AlphaRenderableList::reverse_iterator it = m_AlphaItems.rbegin();
	for( ; it != m_AlphaItems.rend(); ++ it )
	{
		SortRenderable* pRenderable = ( *it ).m_pObj; 
		if(MeCombinedRenderManager::Instance()->TryCombinedRender(pRenderable,true))
		{
			continue;
		}
		else
		{
			MeCombinedRenderManager::Instance()->DoCombinedRender();
			pRenderable->DoRender(true);
		}
	}
	MeCombinedRenderManager::Instance()->DoCombinedRender();
#ifdef _DEBUG
	it = m_AlphaItems.rbegin();
	for( ; it != m_AlphaItems.rend(); ++ it )
	{
		SortRenderable* pRenderable = ( *it ).m_pObj; 
		if (pRenderable->GetOtherInfos(true).size() > 0)
		{
			assert(0);
		}
	}
#endif
	m_AlphaItems.clear();
	m_NoSortAlphaItems.clear();
}

MeAlphaCollector::MeAlphaCollector() 
{
	m_NoSortAlphaItems.reserve( 1000 );
	m_AlphaItems.reserve( 1000 );
}

void MeAlphaCollector::Sort()
{
	MeScopeProfileAlphaCollectorFun
	MeSorter::RenderableListIter it = m_kItems.begin();
	for( ; it != m_kItems.end(); ++ it )
	{
		MeSorter::RenderableBasePtr pRenderable = ( *it ).m_pRenderable; 
		if( !pRenderable )
			continue;

		if (pRenderable->IsEffect())
		{
			//m_AlphaItems.insert(std::make_pair(pRenderable->GetDisToCameraEye(NULL),pRenderable));
			m_AlphaItems.push_back( AlphaRenderableStr( pRenderable->GetDisToCameraEye( NULL ), pRenderable ) );
		}
		else
		{
			for( RenderParams::OtherInfosConstIter otherit = pRenderable->GetOtherInfos( true ).begin(); 
				otherit != pRenderable->GetOtherInfos( true ).end() ; ++ otherit )
			{	
				const RenderParams* params = (*otherit );
				if (params->m_bNoSort)
				{
					m_NoSortAlphaItems.push_back(pRenderable);
					continue;
				}
				//m_AlphaItems.insert(std::make_pair(params->fDistanceToEye,pRenderable));
				m_AlphaItems.push_back( AlphaRenderableStr( params->fDistanceToEye, pRenderable ) );
			}
		}
	}
	m_kItems.clear();
}
