#include "Me3d/Me3d.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/MeTextureSorter.h"

//////////////////////////////////////////////////////////////////////////
void MeTextureSorter::StartSorting()
{/**/}
//////////////////////////////////////////////////////////////////////////
void MeTextureSorter::FinishSorting()
{
	Sort();
// 	MeSorter::RenderableListIter it = m_kItems.begin();
// 	for( ; it != m_kItems.end(); ++ it )
// 	{
// 		( *it )->DoRender();
// 	}
	m_kItems.clear();
}
//////////////////////////////////////////////////////////////////////////
void MeTextureSorter::Sort()
{
	/*m_kItems.sort( MeTextureSorterImpl() );*/
}
//////////////////////////////////////////////////////////////////////////
bool MeTextureSorterImpl::operator()(
									 const MeSorter::RenderableBase* pLeft, 
									 const MeSorter::RenderableBase* pRight
									) const
{		
// 	if( pLeft->GetUseTexId() < pRight->G() )
// 		return true;
	return false;
}
//////////////////////////////////////////////////////////////////////////