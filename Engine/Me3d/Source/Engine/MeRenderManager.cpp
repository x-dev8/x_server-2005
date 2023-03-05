#include "Me3d/Me3d.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "Me3d/Engine/MeCombinedRenderManager.h"

//////////////////////////////////////////////////////////////////////////
// MeSorter::RenderableList MeRenderManager::ms_kItems;
//////////////////////////////////////////////////////////////////////////
void MeRenderManager::OnDeviceLost()
{
	MeCombinedRenderManager::Instance()->OnDeviceLost();
}
//////////////////////////////////////////////////////////////////////////
void MeRenderManager::SetSorter( MeSorter* pkSorter )
{
	m_spSorter = pkSorter;
}
//////////////////////////////////////////////////////////////////////////
MeSorter* MeRenderManager::GetSorter() const
{
	return ( MeSorter* )m_spSorter;
}
//////////////////////////////////////////////////////////////////////////
void MeRenderManager::AddCollector( MeCollector* pkCollector )
{
	m_aspCollectors.push_back( pkCollector );
}
//////////////////////////////////////////////////////////////////////////
// MeCollector* MeRenderManager::GetCollector() const
// {
// 	return ( MeCollector* )m_spCollector;
// }
//////////////////////////////////////////////////////////////////////////
bool MeRenderManager::IsFreshObject( MeSorter::RenderableBasePtr pkObject )
{
	MeScopeProfileRenderManagerFun
	if( !pkObject || !GetSorter() || !pkObject->GetRenderObject() )
		return false;

	if( HaveCollectors() )
	{
		MeCollectorPtrsIter it = m_aspCollectors.begin();
		for( ; it != m_aspCollectors.end(); ++it )
		{
			if( (*it)->IsCollectible( pkObject ) )
				return (*it)->IsFreshObject(pkObject);
		}
	}

	if( pkObject->GetRenderObject()->GetAdded() )
		return false;

	return true;
}
//////////////////////////////////////////////////////////////////////////
bool MeRenderManager::HaveCollectors() const
{
	return !m_aspCollectors.empty();
}
//////////////////////////////////////////////////////////////////////////
bool MeRenderManager::AddToCollector( MeSorter::RenderableBasePtr pkObject )
{
	MeScopeProfileRenderManagerFun

	MeCollectorPtrsIter it = m_aspCollectors.begin();
	for( ; it != m_aspCollectors.end(); ++it )
	{
		if( (*it)->AddObject( pkObject ) )
			return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool MeRenderManager::AddObject( MeSorter::RenderableBasePtr pkObject )
{
	MeScopeProfileRenderManagerFun
	if( !pkObject || !GetSorter() || !pkObject->GetRenderObject() )
		return false;

	if( HaveCollectors() )
		if( AddToCollector( pkObject ) )
			return true;	

	if( pkObject->GetRenderObject()->GetAdded() )
		return false;

	pkObject->GetRenderObject()->SetAdded( true );

	return GetSorter()->AddObject( pkObject );	
}
//////////////////////////////////////////////////////////////////////////
void MeRenderManager::DoRender(bool bPost)
{
	MeScopeProfileRenderManagerFun
	if( !GetSorter() )
		return;

	m_dRenderTime = HQ_TimeGetTime();
	GetSorter()->StartSorting();

	// Ìí¼Óµ½sorterÖÐ
// 	MeSorter::RenderableListIter it = ms_kItems.begin();
// 	for( ; it != ms_kItems.end(); ++ it )
// 		GetSorter()->AddObject( (*it) );

	GetSorter()->FinishSorting();
	m_dRenderTime = HQ_TimeGetTime() - m_dRenderTime;
	if (bPost)
	{
		DoRenderCollector();
		CRenderParamsMgr::Instance()->ResetRenderParamsMgr();
	}
//	ms_kItems.clear();
}
//////////////////////////////////////////////////////////////////////////
void MeRenderManager::DoRenderCollector()
{
	MeScopeProfileRenderManagerFun
	if( !HaveCollectors() )
		return;
	m_dCollectorRenderTime = HQ_TimeGetTime();
	MeCollectorPtrsIter it = m_aspCollectors.begin();
	for( ; it != m_aspCollectors.end(); ++it )
	{
		(*it)->DoRender();		
	}
	m_dCollectorRenderTime = HQ_TimeGetTime() - m_dCollectorRenderTime;
}
//////////////////////////////////////////////////////////////////////////
// MeRenderObject* MeRenderManager::CreateRenderObject( 
// 	MeRenderObject::ERenderObjectType eType )
// {
// 	switch( eType )
// 	{
// 	case MeRenderObject::EROT_MODEL:
// 		return MeNew MeModelRenderObject;
// 		break;
// 
// 	case MeRenderObject::EROT_BILLBOARD:
// 		return MeNew MeBillboardRenderObject;
// 		break;
// 
// 	case MeRenderObject::EROT_PARTICLERIBBON:
// 		return MeNew MeParticleRibbonRenderObject;
// 		break;
// 
// 	case MeRenderObject::EROT_SKELETON:
// 		return MeNew MeSkeletonRenderObject;
// 		break;
// 	}
// 	return 0;
// }
//////////////////////////////////////////////////////////////////////////
// void MeRenderManager::DeleteAllRenderObjects()
// {
// 	ms_kItems.clear();
// }
//////////////////////////////////////////////////////////////////////////
MeRenderManager::~MeRenderManager()
{
// 	DeleteAllRenderObjects();
	m_spSorter = NULL;

	MeCollectorPtrsIter it = m_aspCollectors.begin();
	for( ; it != m_aspCollectors.end(); ++it )	
		(*it) = NULL;		
	m_aspCollectors.clear();
}

void MeRenderManager::Clear()
{
	MeScopeProfileRenderManagerFun
	GetSorter()->Clear();
	MeCollectorPtrsIter it = m_aspCollectors.begin();
	for( ; it != m_aspCollectors.end(); ++it )
	{
		(*it)->Clear();		
	}
	CRenderParamsMgr::Instance()->ResetRenderParamsMgr();

}
//////////////////////////////////////////////////////////////////////////