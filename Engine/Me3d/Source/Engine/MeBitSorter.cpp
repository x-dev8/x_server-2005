#include "Me3d/Me3d.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/MeBitSorter.h"
#include "Me3d/Engine/MeCombinedRenderManager.h"

//////////////////////////////////////////////////////////////////////////
void MeBitSorter::StartSorting()
{/**/}
//////////////////////////////////////////////////////////////////////////
void MeBitSorter::FinishSorting()
{
	Sort();
	MeSorter::RenderableListIter it = m_kItems.begin();
	for( ; it != m_kItems.end(); ++ it )
	{
		MeSorter::RenderableBasePtr pRenderable = ( *it ).m_pRenderable; 
		pRenderable->GetRenderObject()->SetAdded( false );
		if(MeCombinedRenderManager::Instance()->TryCombinedRender(pRenderable,false))//判断是否是效果，如果是效果将会单独在做渲染。
		{
			continue;
		}
		else
		{
			MeCombinedRenderManager::Instance()->DoCombinedRender();
			pRenderable->DoRender(false);
		}
	}
	MeCombinedRenderManager::Instance()->DoCombinedRender();
// 	for( ; it != m_kItems.end(); ++ it )
// 	{
// 		( *it ).second->DoRender();
// 		( *it ).second->GetRenderObject()->SetAdded( false );
// 	}
	m_kItems.clear();
}
//////////////////////////////////////////////////////////////////////////
// bool tempsort( const MeSorter::RenderableBase* pLeft, 
// 			  const MeSorter::RenderableBase* pRight
// 			  ) 
// {		
// 	return ( pLeft->GetSortKey() < pRight->GetSortKey() );		
// }
//////////////////////////////////////////////////////////////////////////
void MeBitSorter::Sort()
{
	//m_kItems.sort( MeBitSorterImpl() );
	std::sort( m_kItems.begin(), m_kItems.end(), MeBitSorterImpl() );
}
//////////////////////////////////////////////////////////////////////////
 /*bool MeBitSorterImpl::operator()(
 									 const MeSorter::RenderableList* pLeft, 
 									 const MeSorter::RenderableList* pRight
 									 ) const
 {		
 	if( pLeft->GetSortKey() < pRight->GetSortKey() )
 		return true;
 	return false;
 }*/
//////////////////////////////////////////////////////////////////////////