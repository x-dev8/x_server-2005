/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	World.cpp
* Create: 	10/06/2006
* Desc:		µØÍ¼Àà
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"

////////////////////////////////////////////////////////////////////////////////
char CWorld::m_appPath[MAX_PATH*2];
char CWorld::m_appDataCharPath[MAX_PATH*2];
wchar_t CWorld::m_appDataPath[MAX_PATH*2];
float g_fCamerFOV = D3DX_PI/180*30;
BOOL				 g_DynamicMapLoadThreadWillExit = FALSE;

FLOAT			g_LoadedProcess = 0.0f;

////////////////////////////////////////////////////////////////////////////////
CWorld::CWorld()
{
	m_isActive		= false;
	m_hasName		= false;
	m_worldBuffer	= NULL;

	m_activePos.x		= 0.0f;
	m_activePos.y		= 0.0f;
	memset( m_worldPath, 0, sizeof(m_worldPath) );
}

CWorld::~CWorld()
{
	Destroy();
}

bool CWorld::Create(CWorldBuffer* worldBuffer)
{
	Assert( NULL == m_worldBuffer );
	m_worldBuffer	= worldBuffer;
	m_worldBuffer->Create();
	m_worldBuffer->SetMaxTileCacheNum(1);
	m_hasName		= false;

	return true;
}


void CWorld::Destroy()
{
	SAFE_DELETE( m_worldBuffer );
}

void CWorld::Update( flt32 totalTime, flt32 deltaTime )
{
	m_worldBuffer->Update( totalTime, deltaTime );
}

bool CWorld::Load( const char* pathName )
{
	SetWorldPath( pathName );

	bool bLoad = m_worldBuffer->LoadWorld();

	m_isActive	= true;
	Trace( "Load world [%s] \n", pathName );

	return bLoad;
}

void CWorld::SetWorldPath( const char* pathName )
{
#if _MSC_VER >= 1400
	strcpy_s( m_worldPath, MAX_PATH*2, pathName );
#else
	strcpy( m_worldPath, pathName );
#endif
	m_hasName = true;
}

bool CWorld::IsLoading()				
{ 
	return m_worldBuffer->IsLoading(); 
}

void CWorld::Reset()
{
	m_isActive	= false;
	m_hasName	= false;
	memset( m_worldPath, 0, MAX_PATH*sizeof(char) );

	m_worldBuffer->Reset();
}

//----------------------------------------------------------------------
void CWorld::OnDeviceLost()
{
	m_worldBuffer->OnDeviceLost();
}

//--------------------------------------------------------------------
void CWorld::OnDeviceReset(bool bBeforeReset)
{
	m_worldBuffer->OnDeviceReset( bBeforeReset);
}

bool CWorld::SetActivePos( flt32 posX, flt32 posY )
{
	if( !m_isActive )
		return false;

	Vector2 oldChunk, curChunk;
	

	if( m_activePos.x == 0.f && m_activePos.y == 0.f )
	{
		curChunk.x = ChunkFromPos( posX );
		curChunk.y = ChunkFromPos( posY );
		m_worldBuffer->OnChunkChange(curChunk.x, curChunk.y);
	}
	else
	{
		oldChunk.x = ChunkFromPos( m_activePos.x );
		oldChunk.y = ChunkFromPos( m_activePos.y );
		curChunk.x = ChunkFromPos( posX );
		curChunk.y = ChunkFromPos( posY );

		if( oldChunk!=curChunk ) 
		{
			m_worldBuffer->OnChunkChange(curChunk.x, curChunk.y);
		}
	}

	m_activePos.x	= posX;
	m_activePos.y	= posY;

	return true;
}

bool CWorld::IsTileChange()
{
	return m_worldBuffer->IsTileChange();
}

void CWorld::SetTileChange( bool isChange )		
{ 
	return m_worldBuffer->SetTileChange( isChange ); 
}

void CWorld::SetLightAmbientColor( const NiColor& ambient )
{
	m_worldBuffer->SetLightAmbientColor( ambient );
}

void CWorld::SetLightDiffuseColor( const NiColor& diffuse )
{
	m_worldBuffer->SetLightDiffuseColor( diffuse );
}

void CWorld::SetLightSpecularColor( const NiColor& specular )
{
	m_worldBuffer->SetLightSpecularColor( specular );
}

void CWorld::SetSunLessColor( const NiColor& specular )
{
	m_worldBuffer->SetSunLessColor( specular );
}

void CWorld::SetLightDir( const Vector& dir )
{
	m_worldBuffer->SetLightDir( dir );
}

// void CWorld::SetFogColor( const NiColor& fogColor )
// {
// 	SwGlobal::GetRender()->SetFogColor( fogColor );
// }
// 
// void CWorld::SetFogDepth( flt32 fogNear, flt32 fogFar )
// {
// 	SwGlobal::GetRender()->SetFogDepth( fogNear, fogFar );
// }

bool CWorld::InitZone()
{
	return m_worldBuffer->InitEnv(m_worldBuffer->GetActiveTile());
}

bool CWorld::IsZoneChange()
{
	return m_worldBuffer->IsEnvChange();
}

bool CWorld::IsLightChange()
{
	return m_worldBuffer->IsLightChange();
}

bool CWorld::IsFogChange()
{
	return m_worldBuffer->IsFogChange();
}

void CWorld::SetZoneChange( bool isChange )		
{ 
	m_worldBuffer->SetEnvChange( isChange ); 
}

void CWorld::SetLightChange( bool isChange )		
{ 
	m_worldBuffer->SetLightChange( isChange ); 
}

void CWorld::SetFogChange( bool isChange )
{ 
	m_worldBuffer->SetFogChange( isChange ); 
}


CNdlEnvRes* CWorld::GetZoneRes()
{
	return m_worldBuffer->GetEnvRes();
}

CNdlLightRes* CWorld::GetLightRes()
{
	return m_worldBuffer->GetLightRes();
}

CNdlFogRes* CWorld::GetFogRes()
{
	return m_worldBuffer->GetFogRes();
}

void CWorld::GetActivePos( flt32& posX, flt32& posY )
{
	posX = m_activePos.x;
	posY = m_activePos.y;
}


