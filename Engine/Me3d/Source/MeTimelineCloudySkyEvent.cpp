#include <MeFoundation/MeFoundationPCH.h>
#include "Me3d/Me3d.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDX.h"
#include "Me3d/MeTimelineCloudySkyEvent.h"
//////////////////////////////////////////////////////////////////////////
void MeTimelineCloudySkyEvent::DoFirstInRunning( const MeTimeValue& kTime )
{
	if( m_pfResetEventWithDataCallback )
	{ m_pfResetEventWithDataCallback( this ); }
}
//////////////////////////////////////////////////////////////////////////
void MeTimelineCloudySkyEvent::UpdateBeginToFull( const MeTimeValue& kTime )
{
	// 计算当前光照颜色( 环境光，漫射光 ）
	if( m_kDestinationAmbient != 0 )
	{
		m_kCurrentAmbient = m_kOriginalAmbient + 
			( Get1_Divide_ToFull_Minus_Start() * ( kTime - GetStartTime() ) * ( m_kDestinationAmbient - m_kOriginalAmbient ) );
		m_kCurrentAmbient.a = 1.f;
	}
	else
	{
		m_kCurrentAmbient = m_kOriginalAmbient;
	}

	if( m_kDestinationDiffuse != 0 )
	{
		m_kCurrentDiffuse = m_kOriginalDiffuse + 
			( Get1_Divide_ToFull_Minus_Start() * ( kTime - GetStartTime() ) * ( m_kDestinationDiffuse - m_kOriginalDiffuse ) );
		m_kCurrentDiffuse.a = 1.f;
	}
	else
	{
		m_kCurrentDiffuse = m_kOriginalDiffuse;
	}

	// 赋值到引擎。
	RendererDx* pRenderer = ( RendererDx* )GetEngine()->GetRenderer();
	if( pRenderer )
	{
		D3DLIGHT9 kTerrainLight;
		pRenderer->GetLight( LIGHT_INDEX_TERRAIN, &kTerrainLight );
		kTerrainLight.Ambient.r = m_kCurrentAmbient.r;
		kTerrainLight.Ambient.g = m_kCurrentAmbient.g;
		kTerrainLight.Ambient.b = m_kCurrentAmbient.b;
		kTerrainLight.Diffuse.r = m_kCurrentDiffuse.r;
		kTerrainLight.Diffuse.g = m_kCurrentDiffuse.g;
		kTerrainLight.Diffuse.b = m_kCurrentDiffuse.b;
		pRenderer->SetLight( LIGHT_INDEX_TERRAIN, &kTerrainLight );
	}	
}
//////////////////////////////////////////////////////////////////////////
void MeTimelineCloudySkyEvent::UpdateInFull( const MeTimeValue& kTime )
{
	if( m_kDestinationAmbient != 0 )
	{
		m_kCurrentAmbient = m_kDestinationAmbient;
		m_kCurrentAmbient.a = 1.f;
	}
	else
	{
		m_kCurrentAmbient = m_kOriginalAmbient;
	}

	if( m_kDestinationDiffuse != 0 )
	{
		m_kCurrentDiffuse = m_kDestinationDiffuse;
		m_kCurrentDiffuse.a = 1.f;
	}
	else
	{
		m_kCurrentDiffuse = m_kOriginalDiffuse;
	}
	// 需要保证每帧的光照都是一致的，防止外界改变。
	RendererDx* pRenderer = ( RendererDx* )GetEngine()->GetRenderer();
	if( pRenderer )
	{
		D3DLIGHT9 kTerrainLight;
		pRenderer->GetLight( LIGHT_INDEX_TERRAIN, &kTerrainLight );
		kTerrainLight.Ambient.r = m_kCurrentAmbient.r;
		kTerrainLight.Ambient.g = m_kCurrentAmbient.g;
		kTerrainLight.Ambient.b = m_kCurrentAmbient.b;
		kTerrainLight.Diffuse.r = m_kCurrentDiffuse.r;
		kTerrainLight.Diffuse.g = m_kCurrentDiffuse.g;
		kTerrainLight.Diffuse.b = m_kCurrentDiffuse.b;
		pRenderer->SetLight( LIGHT_INDEX_TERRAIN, &kTerrainLight );
	}	
}
//////////////////////////////////////////////////////////////////////////
void MeTimelineCloudySkyEvent::UpdateFullToEnd( const MeTimeValue& kTime )
{
	// 计算当前光照颜色( 环境光，漫射光 ）
	if( m_kDestinationAmbient != 0 )
	{
		m_kCurrentAmbient = m_kDestinationAmbient + 
			( Get1_Divide_End_Minus_ToEnd() * ( kTime - GetToEnd() ) * ( m_kOriginalAmbient - m_kDestinationAmbient ) );
		m_kCurrentAmbient.a = 1.f;
	}
	else
	{
		m_kCurrentAmbient = m_kOriginalAmbient;
	}

	if( m_kDestinationDiffuse != 0 )
	{
		m_kCurrentDiffuse = m_kDestinationDiffuse + 
			( Get1_Divide_End_Minus_ToEnd() * ( kTime - GetToEnd() ) * ( m_kOriginalDiffuse - m_kDestinationDiffuse ) );

		m_kCurrentDiffuse.a = 1.f;
	}
	else
	{
		m_kCurrentDiffuse = m_kOriginalDiffuse;
	}

	// 赋值到引擎。
	RendererDx* pRenderer = ( RendererDx* )GetEngine()->GetRenderer();
	if( pRenderer )
	{
		D3DLIGHT9 kTerrainLight;
		pRenderer->GetLight( LIGHT_INDEX_TERRAIN, &kTerrainLight );
		kTerrainLight.Ambient.r = m_kCurrentAmbient.r;
		kTerrainLight.Ambient.g = m_kCurrentAmbient.g;
		kTerrainLight.Ambient.b = m_kCurrentAmbient.b;
		kTerrainLight.Diffuse.r = m_kCurrentDiffuse.r;
		kTerrainLight.Diffuse.g = m_kCurrentDiffuse.g;
		kTerrainLight.Diffuse.b = m_kCurrentDiffuse.b;
		pRenderer->SetLight( LIGHT_INDEX_TERRAIN, &kTerrainLight );
	}	
}
//////////////////////////////////////////////////////////////////////////