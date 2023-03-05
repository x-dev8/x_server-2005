/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldBuffer.cpp
* Create: 	10/06/2006
* Desc:		地图数据缓冲
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/SwRender.h"
#include <deque>
#include "Me3d/engine/RendererDx.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "logmgr.h"
#include "MeTerrain/Lighting/LightMapTexture.h"
#define INFO_LOG		"Info.log"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// 地形数据读取/卸载线程
// namespace wrt				// WorldReadThread
// {
// 	deque<CWorldTile *>	m_dequeMessageLoad;
// 	deque<CWorldTile *>	m_dequeMessageUnLoad;
// 
// 	CRITICAL_SECTION		m_hWorldReadThreadRunning;
// 	CRITICAL_SECTION		m_hCacheTileReading;
// 	CRITICAL_SECTION		m_hMessageDequeReading;
// 	bool					m_bRunWorldReadThread;
// 	DWORD					m_dwWorldReadThreadId;
// 
// 	DWORD WINAPI WorldReadThreadFunc( LPVOID lpParam ) 
// 	{
// 		// 退出临界区，意味着此线程已经结束了.
// 		EnterCriticalSection( &m_hWorldReadThreadRunning );
// 
// 		CWorldTile * tile	= NULL;  // 加载或删除的tile指针.
// 		bool isLoad			= true;
// 
// 		// 判断是否要结束此线程.
// 		while( m_bRunWorldReadThread )
// 		{
// 			if( m_dequeMessageUnLoad.size() || m_dequeMessageLoad.size() )
// 			{
// 				// 获取消息.
// 				EnterCriticalSection( &m_hMessageDequeReading );
// 				if( m_dequeMessageUnLoad.size() )
// 				{
// 					tile = m_dequeMessageUnLoad.front();
// 					isLoad = false;
// 				}	
// 				else if( m_dequeMessageLoad.size() )
// 				{
// 					tile = m_dequeMessageLoad.front();
// 					isLoad = true;
// 				}	
// 				LeaveCriticalSection( &m_hMessageDequeReading );
// 
// 				// 读取或卸载地形数据.
// 				ASSERT_NOTNULL( tile );
// 
// 				if ( isLoad )
// 				{
// 					if ( !tile->IsLoad() )
// 					{
// 						CWorldReadStream*	readStream = (CWorldReadStream*)lpParam;
// 
// 						if ( readStream	&& readStream->LoadTile( tile ) )
// 						{
// 							tile->SetLoad(true);
// 						}
// 					}
// 					m_dequeMessageLoad.pop_front();
// 				}
// 				else
// 				{
// 					if ( tile->IsLoad() )
// 					{
// 						tile->Reset();
// 					}
// 					m_dequeMessageUnLoad.pop_front();
// 				}
// 			}
// 			else
// 			{
//  				// 没有工作,就睡一下.
// 				LeaveCriticalSection(&m_hWorldReadThreadRunning);
// 				Sleep(1);
// 				if( !m_bRunWorldReadThread ) return 0;
// 				EnterCriticalSection(&m_hWorldReadThreadRunning);
// 			}
// 		}
// 
// 		LeaveCriticalSection(&m_hWorldReadThreadRunning);
// 		return 0;
// 	}
// }
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace {
	const char l_shaderName[SHADER_NUM][32]	= { "GameTerrainRender1"
		, "GameTerrainRender2"
		, "GameTerrainRender3"
		, "GameTerrainRender4" 
		, "LOD1_Terrain"
		, "LOD2_Terrain"
		, "GameTerrainSpecialRender1"
		, "GameTerrainSpecialRender2"
		, "GameTerrainSpecialRender3"
		, "GameTerrainSpecialRender4" 
		, "LOD1_Terrain_Special"
	};
};

////////////////////////////////////////////////////////////////////////////////
CWorldBuffer::CWorldBuffer( CWorld* world )
:m_MaxTileCacheNum(1)
{
	m_curChunk.x		= -1;
	m_curChunk.y		= -1;
	

// 	m_activePos.x		= FLT_MAX;
// 	m_activePos.y		= FLT_MAX;

	m_isTileChange		= false;
	m_world				= world;
	
	m_readStream		= NULL;
	m_globalResMgr		= NULL;


	m_isZoneChange		= false;
	m_isLightChange		= false;
	m_isFogChange		= false;

	m_envRes			= NULL;
	m_lightRes			= NULL;
	m_fogRes			= NULL;
	m_activeTile		= NULL;

// 	m_bMultiThread = true;
    m_farChunkBackup    = 0;

	m_tilePRI.clear();
}

CWorldBuffer::~CWorldBuffer()
{
	Destroy();
}

bool CWorldBuffer::Create()
{
	Assert( NULL == m_readStream );
	m_readStream	= new CWorldReadStream( this );

	m_globalResMgr = new CNdlGlobalResMgr();
// 	m_globalResMgr->Create();

// 	CreateMultiThread();

	return true;
}

// bool CWorldBuffer::CreateMultiThread()
// {
// 	if(!m_bMultiThread) 
// 		return true;

	// 多线程操作CSD2DTexCache的同步锁
// 	InitializeCriticalSection(&m_hLock);

	// 初始化纹理读取线程
// 	InitializeCriticalSection(&wrt::m_hWorldReadThreadRunning);
// 	InitializeCriticalSection(&wrt::m_hMessageDequeReading);
// 	InitializeCriticalSection(&wrt::m_hCacheTileReading);
// 	wrt::m_bRunWorldReadThread = true;
// 	CreateThread(NULL,0,wrt::WorldReadThreadFunc,(DWORD *)m_readStream,0,&wrt::m_dwWorldReadThreadId);
// 
// 	return true;
// }

// void CWorldBuffer::DestroyMultiThread()
// {
// 	if(!m_bMultiThread) return;
// 	if (wrt::m_bRunWorldReadThread == false) return;
// 
// 	// 等待纹理读取线程退出
// 	wrt::m_bRunWorldReadThread = false;
// 	EnterCriticalSection(&wrt::m_hWorldReadThreadRunning);
// 	LeaveCriticalSection(&wrt::m_hWorldReadThreadRunning);
// 
// 	// 是否线程的资源
// 	wrt::m_dequeMessageUnLoad.clear();
// 	wrt::m_dequeMessageLoad.clear();
// 	DeleteCriticalSection(&wrt::m_hWorldReadThreadRunning);
// 	DeleteCriticalSection(&wrt::m_hMessageDequeReading);
// 	DeleteCriticalSection(&wrt::m_hCacheTileReading);
// 
// 	DeleteCriticalSection(&m_hLock);
// }

void CWorldBuffer::Destroy()
{
	m_world				= NULL;

	m_envRes			= NULL;
	m_lightRes			= NULL;
	m_fogRes			= NULL;

// 	DestroyMultiThread();
	for(std::map<sInt32,CWorldTile*>::iterator iter = m_tileMapHash.begin(); iter != m_tileMapHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (NULL != pWorldTile)
		{
			SAFE_DELETE(pWorldTile);
		}
	}
	m_tileMapHash.clear();
	SAFE_DELETE( m_readStream );
	NDL_SAFE_DELETE( m_globalResMgr );
	m_tilePRI.clear();
	CResMgr::DestoryStaticStream();
}

void CWorldBuffer::Update( flt32 totalTime, flt32 deltaTime )
{
	//	float fTime = ZnGlobal::s_timer.GetTimeCur();
	if (GetActiveTile())
	{
		GetActiveTile()->m_ndlResMgr->Update( totalTime, deltaTime );
	}

//	Trace("CWorldBuffer::Update[%8.5f]\n", ZnGlobal::s_timer.GetTimeCur() - fTime);
	m_globalResMgr->Update( totalTime, deltaTime );
}

bool CWorldBuffer::LoadWorld()
{
	CResMgr::CreateStaticStream();
	if( !m_readStream->LoadWorld( m_world->GetWorldPath() ) ){
		Trace( "<<<ERROR>>> Failed to load world %s! \n", m_world->GetWorldPath());
		return false;
	}	
	SortMapByLevel();
	return true;
}

CResMgr* CWorldBuffer::GetResMgr(  )
{
	CWorldTile* tile = GetActiveTile();
	if ( NULL!=tile )
	{
		return tile->m_ndlResMgr;
	}

	return NULL;
}


CWorldChunk* CWorldBuffer::GetChunk( sInt32 chunkX, sInt32 chunkY )
{
	CWorldTile* tile = GetActiveTile();
	if( NULL == tile )
		return NULL;
	
	return tile->GetChunk( chunkX, chunkY );
}



void CWorldBuffer::Reset()
{
// 	DestroyMultiThread();
// 	CreateMultiThread();
	for(std::map<sInt32,CWorldTile*>::iterator iter = m_tileMapHash.begin(); iter != m_tileMapHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (NULL != pWorldTile)
		{
			SAFE_DELETE(pWorldTile);
		}
	}
	m_tileMapHash.clear();
	m_activeTile		= NULL;

	m_globalResMgr->Reset();

	m_tilePRI.clear();

}

//----------------------------------------------------------------------------
void CWorldBuffer::OnDeviceLost()
{
	std::list<sInt32>::iterator ite = m_tilePRI.begin();
	while (ite != m_tilePRI.end())
	{
		CWorldTile* tile = GetTile(*ite);
		tile->OnDeviceLost();
		++ite;
	}
// 	if (GetActiveTile())
// 	GetActiveTile()->OnDeviceLost( );

	if( SwGlobal::GetRender() )
		SwGlobal::GetRender()->OnDeviceLost();
}

//----------------------------------------------------------------------------
void CWorldBuffer::OnDeviceReset(bool bBeforeReset)
{
	std::list<sInt32>::iterator ite = m_tilePRI.begin();
	while (ite != m_tilePRI.end())
	{
		CWorldTile* tile = GetTile(*ite);
		tile->OnDeviceReset(bBeforeReset);
		++ite;
	}
// 	if (GetActiveTile())
// 	GetActiveTile()->OnDeviceReset( bBeforeReset);

	if( SwGlobal::GetRender() )
		SwGlobal::GetRender()->OnDeviceReset();
}

// bool CWorldBuffer::GetVertexHeight( const sInt32* startGlUnit, const sInt32* overGlUnit, flt32* heightOut, flt32* heightIn )
// {
// 	sInt32 unitSize[2], starTile[2], startChunk[2], unit[2], subUnit[2];
// 	
// 	unitSize[0]		= overGlUnit[0] - startGlUnit[0];	
// 	unitSize[1]		= overGlUnit[1] - startGlUnit[1];	
// 	
// 	for(;;) {
// 		if( (unitSize[0]==0) && (unitSize[1]==0) )
// 			break;
// 		
// 		starTile[0]		= ( (startGlUnit[0])/(CURRENTTILE->GetRowColumn()[0]*WORLD_TILE_CHUNK_UNIT_NUM) );
// 		starTile[1]		= ( (startGlUnit[1])/(CURRENTTILE->GetRowColumn()[1]*WORLD_TILE_CHUNK_UNIT_NUM) );
// 
// 		startChunk[0]		= ( ((startGlUnit[0])%(CURRENTTILE->GetRowColumn()[0]*WORLD_TILE_CHUNK_UNIT_NUM))/WORLD_TILE_CHUNK_UNIT_NUM );
// 		startChunk[1]		= ( ((startGlUnit[1])%(CURRENTTILE->GetRowColumn()[1]*WORLD_TILE_CHUNK_UNIT_NUM))/WORLD_TILE_CHUNK_UNIT_NUM );
// 
// 		unit[0]			= UnitFromGlUnit( startGlUnit[0] );
// 		unit[1]			= UnitFromGlUnit( startGlUnit[1] );
// 
// 		subUnit[0]		= overGlUnit[0] - startGlUnit[0];
// 		subUnit[1]		= overGlUnit[1] - startGlUnit[1];
// 
// 	}
// 	
// 	return true;
// }

void CWorldBuffer::SetLightAmbientColor( const NiColor& ambient )
{
	float lightColor[4] = { ambient.r, ambient.g, ambient.b, 1.0f };
}

void CWorldBuffer::SetLightDiffuseColor( const NiColor& diffuse )
{
	float lightColor[4] = { diffuse.r, diffuse.g, diffuse.b, 1.0f };
}

void CWorldBuffer::SetLightSpecularColor( const NiColor& specular )
{
	float lightColor[4] = { specular.r, specular.g, specular.b, 1.0f };
}
void CWorldBuffer::SetSunLessColor( const NiColor& specular )
{
	float lightColor[4] = { specular.r, specular.g, specular.b, 1.0f };

}
void CWorldBuffer::SetLightDir( const Vector& dir )
{
	float lightDir[4] = { dir.x, dir.y, dir.z, 1.0f };
}


bool CWorldBuffer::InitEnv(CWorldTile* tile)
{
	if (NULL == tile)
	{
		return false;
	}
	sInt32 tileChunk[2];
	Vector2 activePos;
	m_world->GetActivePos(activePos.x, activePos.y);
	tileChunk[0]	= ChunkFromPos( activePos.x );
	tileChunk[1]	= ChunkFromPos( activePos.y );

	CResMgr* pResMgr = tile->GetCResMgr();
	CWorldChunk* worldChunk = tile->GetChunk(  tileChunk[0], tileChunk[1] );

	if (NULL != worldChunk )
	{
		if (RES_INVALID_ID != worldChunk->m_envId )
		{
			Assert( worldChunk->m_envId>=0 && worldChunk->m_envId < pResMgr->GetEnvResList().size() );

			CNdlEnvRes* envRes	= (CNdlEnvRes*)pResMgr->GetEnvRes(worldChunk->m_envId);
			CWorldBuffer:UpdateEnv( envRes );

			CNdlLightRes* lightRes	= (CNdlLightRes*)pResMgr->GetLightRes(envRes->GetLightId());
			CWorldBuffer::UpdateLight( lightRes );

			CNdlFogRes* fogRes		= (CNdlFogRes*)pResMgr->GetFogRes(envRes->GetFogId());
			CWorldBuffer::UpdateFog( fogRes );
		}
	}
	m_isZoneChange	= false;
	m_isLightChange	= false;
	m_isFogChange	= false;

	return true;
}

void CWorldBuffer::UpdateTileEnv(CWorldTile *tile, sInt32 envId)
{
	if (tile == NULL || envId == -1)
		return;

	CResMgr *resMgr = tile->GetCResMgr();
	Assert(envId >= 0 && envId < resMgr->GetEnvResList().size());
	
	// 把Tile的环境Id存在[0, 0]Chunk中
	CWorldChunk *chunk = tile->GetChunk(0, 0);
	if (chunk != NULL)
	{
		Assert(envId != RES_INVALID_ID);

		chunk->m_envId = envId;

		CNdlEnvRes *envRes = resMgr->GetEnvRes(envId);
		CWorldBuffer::UpdateEnv(envRes);

		CNdlLightRes *lightRes = resMgr->GetLightRes(envRes->GetLightId());
		CWorldBuffer::UpdateLight(lightRes);

		CNdlFogRes *fogRes = resMgr->GetFogRes(envRes->GetFogId());
		CWorldBuffer::UpdateFog(fogRes);

		// 设置Tile的全局光雾
		{/*
			SwGlobal::GetRender()->SetLightDir(lightRes->GetLightDir());

			NiColor color;
			ConvertRGB2NiColor(lightRes->GetLightAmbient(), color);
			SwGlobal::GetRender()->SetLightAmbientColor(color);

			ConvertRGB2NiColor(lightRes->GetLightDiffuse(), color);
			SwGlobal::GetRender()->SetLightDiffuseColor(color);

			ConvertRGB2NiColor(lightRes->GetLightSpecular(), color);
			SwGlobal::GetRender()->SetLightSpecularColor(color);*/
		}
	}
}

void CWorldBuffer::OnChunkChange(int newchunkX, int newchunkY)
{
	CWorldChunk* worldChunk = GetChunk( newchunkX, newchunkY );
	if( NULL != worldChunk ) 
	{
		if( RES_INVALID_ID != worldChunk->m_envId ) 
		{
			Assert( worldChunk->m_envId>=0 && worldChunk->m_envId < GetResMgr()->m_envResList.size() );
			CNdlEnvRes* envRes	= (CNdlEnvRes*)GetResMgr()->m_envResList[worldChunk->m_envId];
			Assert( envRes->GetLightId()>=0 && envRes->GetLightId()<GetResMgr()->m_lightList.size() );
			Assert( envRes->GetFogId()>=0 && envRes->GetFogId()<GetResMgr()->m_fogList.size() );
			UpdateEnv( envRes );
			CNdlLightRes* lightRes	= (CNdlLightRes*)GetResMgr()->m_lightList[envRes->GetLightId()];
			Assert( NULL != lightRes );
			UpdateLight( lightRes );
			CNdlFogRes* fogRes		= (CNdlFogRes*)GetResMgr()->m_fogList[envRes->GetFogId()];
			Assert( NULL != fogRes );
			UpdateFog( fogRes );
		}
	}
}

bool CWorldBuffer::IsEnvChange()
{
	return m_isZoneChange;
}

CNdlEnvRes* CWorldBuffer::GetEnvRes()
{
	return m_envRes;
}

bool CWorldBuffer::IsLightChange()
{
	return m_isLightChange;
}

CNdlLightRes* CWorldBuffer::GetLightRes()
{
	return m_lightRes;
}

bool CWorldBuffer::IsFogChange()
{
	return m_isFogChange;
}

CNdlFogRes* CWorldBuffer::GetFogRes()
{
	return m_fogRes;
}

bool CWorldBuffer::_LoadTileRes( CWorldTile* tile )
{
	Trace( "LoadTileRes(%s) \n", tile->GetPathName());

// 	if ( m_bMultiThread )
// 	{
// 		EnterCriticalSection(&m_hLock);
// 
// 		EnterCriticalSection(&wrt::m_hMessageDequeReading);
// 
// 		wrt::m_dequeMessageLoad.push_back(tile);
// 
// 		LeaveCriticalSection(&wrt::m_hMessageDequeReading);
// 
// 		LeaveCriticalSection(&m_hLock);
// 	}
// 	else
	{
		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d      地表基本数据加载", GetCurrentThreadId() );
		if ( m_readStream->LoadTile( tile ) )
		{
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d     地表动态数据加载", GetCurrentThreadId() );
			tile->SetLoad(true);
			InitEnv(tile);
			tile->RefreshChunkLoadLevel(SwGlobal::GetRender()->GetFogProperty()->fFogFar,false);
			LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d     地表动态数据加载结束", GetCurrentThreadId() );

			return true;
		}
	}
	
	return false;
}

bool CWorldBuffer::UnloadTileRes( uInt32 tileId )
{
	CWorldTile * tile = GetTile(tileId);
	Trace( "UnloadTileRes(%s) \n", tile->GetPathName() );

	ClearTileModify(tile, tileId);

// 	if ( m_bMultiThread )
// 	{
// 		EnterCriticalSection(&m_hLock);
// 
// 		EnterCriticalSection(&wrt::m_hMessageDequeReading);
// 
// 		wrt::m_dequeMessageUnLoad.push_back(tile);
// 
// 		LeaveCriticalSection(&wrt::m_hMessageDequeReading);
// 
// 		LeaveCriticalSection(&m_hLock);
// 	}
// 	else
	{
		tile->Reset();
		FinishUnLoadingTile( tile );
	}

	return true;
}


//bool CWorldBuffer::MoveCacheMap()
//{
//	sInt32 stepX = m_curTile.x - m_cache[0];
//	sInt32 stepY = m_curTile.y - m_cache[1];
//
//	// 在缓存区内,不需要移动
//	if( ((stepX >= 1) && ( stepX <= 2)) && (( stepY >= 1 ) && ( stepY <= 2 )))
//	{
//		return false;		
//	}
//	if( stepX > 2 )
//	{
//		stepX	= (stepX-2);
//	}
//	else // stepX <1;
//	{
//		stepX	= (stepX-1);
//	}
//	if( stepY > 2 )
//	{
//		stepY	= (stepY-2);
//	}
//	else // stepY <1;
//	{
//		stepY	= (stepY-1);
//	}
//
//	sInt32 cache[2]; 
//	cache[0]	= m_cache[0] + stepX;
//	cache[1]	= m_cache[1] + stepY;
//
//	sInt32 x, y;
//	CWorldTile* swapBuffer[CACHE_NUM][CACHE_NUM];
//	// 复制已经存在的.
//	for( y = 0; y < CACHE_NUM; y++ )
//	{
//		for( x = 0; x < CACHE_NUM; x++ )
//		{
//			if( ((x+stepX) >= 0) && ((x+stepX) < CACHE_NUM) && ((y+stepY) >=0 ) && ((y+stepY)<CACHE_NUM) )
//			{
//				// 缓存存在的部分
//				swapBuffer[x][y]	= m_cachedTile[x+stepX][y+stepY];
//				
//				Assert( swapBuffer[x][y]->m_Position.x == cache[0] + x );
//				Assert( swapBuffer[x][y]->m_Position.y == cache[1] + y );
//			}
//			else
//			{
//				// 卸载旧的.
//				swapBuffer[x][y]		= m_cachedTile[(CACHE_NUM-1)-x][(CACHE_NUM-1)-y];
//				CWorldTile* tile		= swapBuffer[x][y];
//				UnloadTileRes( tile );
//
//				//Assert( !tile->m_isLoad );
//
//				tile->m_Position.x = cache[0] + x;
//				tile->m_Position.y = cache[1] + y;
//			}
//		}
//	}
//
//	EnterCriticalSection( &wrt::m_hCacheTileReading );
//	memcpy( m_cachedTile, swapBuffer, sizeof( swapBuffer ) );
//	LeaveCriticalSection( &wrt::m_hCacheTileReading );
//
//	m_cache[0]	= cache[0];
//	m_cache[1]	= cache[1];
//
//	return true;
//}
//
//void CWorldBuffer::MoveActiveMap()
//{
//	sInt32 offX, offY;
//	offX = m_curTile.x-1-m_cache[0];
//	offY = m_curTile.y-1-m_cache[1];
//	
//	Assert( (offX>=0) && (offX<=2) );
//	Assert( (offY>=0) && (offY<=2) );
//
//	Trace( "=== active(%d,%d) cache(%d,%d) ===\n", m_curTile.x, m_curTile.y, m_cache[0], m_cache[1] );
//
//	CWorldTile** tiles = NULL;
//	
//	sInt32 x, y;
//	for( y = 0; y < ACTIVE_NUM; y++ )
//	{
//		for( x = 0; x < ACTIVE_NUM; x++ )
//		{
//			CWorldTile* tile = m_cachedTile[x+offX][y+offY];
//			Assert( NULL != tile );
//			Assert( tile->m_Position.x == (m_curTile.x-1+x) );
//			Assert( tile->m_Position.y == (m_curTile.y-1+y) );
//			if( !tile->m_isLoad )
//			{
//				if( TILE_NORMAL == CheckTile( tile->m_Position.x, tile->m_Position.y ) )
//				{
//					LoadTileRes( tile );
//				}
//			}
//		}
//	}
//}

void CWorldBuffer::FinishUnLoadingTile( CWorldTile* cacheTile )
{
	
	SwGlobal::GetWorld()->GetWorldBuffer()->GetGlobalResMgr()->UnloadModelDoodad();

}

bool CWorldBuffer::IsLoading()
{
	if (GetActiveTile())
		return !GetActiveTile()->m_isLoad;
	return false;
}

bool CWorldBuffer::IsTileChange()
{
	return m_isTileChange;
}

void CWorldBuffer::UpdateEnv( CNdlEnvRes* envRes )
{
	if( envRes == m_envRes ) {
		m_isZoneChange = false;
		return;
	}
	m_isZoneChange	= true;
	m_envRes		= envRes;
}

void CWorldBuffer::UpdateLight( CNdlLightRes* lightRes )
{
	if (lightRes == NULL)
		return;

	m_isLightChange = true;
	m_lightRes		= lightRes;
	Assert( NULL != lightRes );
	SwRender* pRender = SwGlobal::GetRender();
	Vector vTempDir = lightRes->GetLightDir();
	pRender->SetLightDir( vTempDir );

	NiColor color;
	ConvertRGB2NiColor( lightRes->GetLightAmbient(), color );
	pRender->SetLightAmbientColor( color );
	ConvertRGB2NiColor( lightRes->GetLightDiffuse(), color );
	pRender->SetLightDiffuseColor( color );
	ConvertRGB2NiColor( lightRes->GetLightSpecular(), color );
	pRender->SetLightSpecularColor( color );
	// 	ConvertRGB2NiColor( lightRes->m_colorSunless, color );
	// 	pRender->SetSunLessColor( color );
}

void CWorldBuffer::UpdateFog( CNdlFogRes* fogRes )
{
	if (fogRes == NULL)
		return;

	m_isFogChange	= true;
	m_fogRes		= fogRes;
	SwRender* pRender = SwGlobal::GetRender();
	NiColor color;
	ConvertRGB2NiColor( fogRes->GetLightColor(), color );
	pRender->SetFogColor( color );

                                     
	pRender->SetFogDepth( fogRes->GetLightNear(), fogRes->GetLightFar() );
}





CWorldTile* CWorldBuffer::PushTileRes(sInt32 nMapId, const char* pPathName )
{
	CWorldTile* pNewTile = NULL;
// 	if (-1 == nMapId)
// 	{
// 		for (int i = 0 ; i < 10000; ++i)
// 		{
// 			if (!GetTile(i))
// 			{
// 				nMapId = i;
// 				break;
// 			}
// 		}
// 	}
// 	else
	{
		pNewTile = GetTile(nMapId);
	}
	if (!pNewTile)
	{
		pNewTile = new CWorldTile(pPathName);
		m_tileMapHash.insert(std::map<sInt32,CWorldTile*>::value_type(nMapId,pNewTile));
		pNewTile->Create(this,new CResMgr);
	}
	return pNewTile;
}

CWorldTile* CWorldBuffer::LoadTileRes( CWorldTile* val ,int nRoleX ,int nRoleY)
{
	if (val == NULL)
		return NULL;

	CWorldTile* tile = val;
	sInt32 tileId = tile->GetMapId();
	tile->SetRolePosition(nRoleX,nRoleY);
	ClearTileModify(tile,tileId);

	if (tile->IsLoad())
	{//已经加载了，只需要改变优先级就好了
		m_tilePRI.remove(tileId);
		AddTilePRI(tileId);
	}
	else
	{
		AddTilePRI(tileId);
		_LoadTileRes(tile);
	}
	return tile;
}

// sInt32 CWorldBuffer::GetTileHashId( const char* pPathName )
// {
// 	char temp[MAX_PATH];
// 	strcpy(temp,pPathName);
// 	_strlwr(temp);
// 	return m_tileMapHash.Find(temp);
// 
// }

void CWorldBuffer::ReomveTileRes( sInt32 hashId )
{
	m_tilePRI.remove(hashId);
	CWorldTile* pRemove = GetTile(hashId);
	if (pRemove == m_activeTile)
	{
		m_activeTile = NULL;
	}
	SAFE_DELETE(pRemove);
	m_tileMapHash.erase(hashId);

}


CWorldTile* CWorldBuffer::GetTileFromPath( const char* pPathName )
{
	if (NULL == pPathName)
	{
		return NULL;
	}
	char temp[MAX_PATH];
	strcpy(temp,pPathName);
	_strlwr(temp);
	for(std::map<sInt32,CWorldTile*>::iterator iter = m_tileMapHash.begin(); iter != m_tileMapHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (pWorldTile)
		{
			if( 0 == stricmp(temp,pWorldTile->GetPathName()) )
			{
				return pWorldTile;
			}
		}
	}
	return NULL;
}


CWorldTile* CWorldBuffer::GetTile( sInt32 hashId )
{
	std::map<sInt32,CWorldTile*>::iterator iter = m_tileMapHash.find(hashId);
	if (iter != m_tileMapHash.end())
	{
		return iter->second;
	}
	return NULL;
}

bool CWorldBuffer::SetActiveTile( CWorldTile* val ,int nRoleX ,int nRoleY )
{
	if( m_farChunkBackup != 0 )
		SwGlobal::GetRender()->SetFarChunk(m_farChunkBackup);
	// 当前激活地图名相同，直接返回
	if( GetActiveTile() && (val == GetActiveTile()) )
		return TRUE;
	SwGlobal::GetRender()->UnlockModelRes();
	// 注销光照图
	if( GetActiveTile() )
	{
		CWorldTile* pOldTile = GetActiveTile();
		for( int i=0; i<pOldTile->GetLightMaps().size(); ++i )
		{
			GetEngine()->GetTextureManager()->UnRegisterTexture( pOldTile->GetLightMaps()[i]->GetTextureId() );
		}
	}

	m_activeTile = NULL;
	CWorldTile* pTile = LoadTileRes(val,nRoleX,nRoleY);
    if( pTile )
	    pTile->m_tileQuadTree.SetNeedSetFrustumEx(TRUE);
	_SetActiveTile(pTile);

	D3DXVECTOR3 vC( pTile->GetContrastOffsetR(), pTile->GetContrastOffsetG(), pTile->GetContrastOffsetB() );
	PostProcessManager::instance().SetBrightNContrast( pTile->GetBrightnessOffset(), vC );
	PostProcessManager::instance().setParameter( "BloomScale", D3DXVECTOR4( pTile->GetBloomScale(), 0, 0, 0 ) );
	PostProcessManager::instance().setParameter( "Luminance", D3DXVECTOR4( pTile->GetLuminance(), 0, 0, 0 ) );
	return pTile != NULL;
}

void CWorldBuffer::_SetActiveTile( CWorldTile* val )
{
	m_activeTile = val;
}

CWorldTile* CWorldBuffer::GetTileFromMapId( int nMapId )
{
	return GetTile(nMapId);
// 	for( int i=0; i < m_tileMapHash.Size(); i++ )
// 	{
// 		if( m_tileMapHash[i] != NULL )
// 		{
// 			if( m_tileMapHash[i]->GetMapId() == nMapId )
// 			{
// 				return m_tileMapHash[i];
// 			}
// 		}
// 	}
// 	return NULL;
}


CWorldTile* CWorldBuffer::GetTileFromTileName( const char* pTileName ,short stCountry)
{
	if (pTileName == NULL)
	{
		return NULL;
	}
	for(std::map<sInt32,CWorldTile*>::iterator iter = m_tileMapHash.begin(); iter != m_tileMapHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (pWorldTile)
		{
			if( 0 == strcmp(pTileName,pWorldTile->GetTileName()) 
				&& ((stCountry == -1) ||(pWorldTile->GetCountry() == 0) ||(pWorldTile->GetCountry() == stCountry)))
			{
				return pWorldTile;
			}
		}
	}
	return NULL;
}

void CWorldBuffer::AddTilePRI( sInt32 tileId )
{
	m_tilePRI.push_back(tileId);
	Assert(m_MaxTileCacheNum > 0);
	if (m_tilePRI.size() > m_MaxTileCacheNum)
	{//如果超出cache的最大尺寸，卸载低优先级的tile
		int delta = m_tilePRI.size() - m_MaxTileCacheNum;
		for (int i = 0; i < delta; ++i)
		{
			uInt32 lastTileId = m_tilePRI.front();
			CWorldTile* pUnloadTile = GetTileFromMapId(lastTileId);
			ASSERT_NOTNULL(pUnloadTile);
			UnloadTileRes(lastTileId);
			m_tilePRI.pop_front();
		}
	}
}

void CWorldBuffer::SortMapByLevel()
{
	m_mapSortbyLevelID.clear();
	std::map<sInt32,CWorldTile*>::iterator iter = m_tileMapHash.begin(); 
	//先加入第一个
	for(; iter != m_tileMapHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (NULL != pWorldTile && pWorldTile->GetMapType() == 0 && pWorldTile->GetOrder() != 0)
		{
			m_mapSortbyLevelID.push_back(pWorldTile);
			break;
		}
	}
	if (iter != m_tileMapHash.end())
	{
		++iter;
		//排序插入其他的
		for(; iter != m_tileMapHash.end();++iter)
		{
			CWorldTile* pWorldTile =iter->second;
			if (NULL != pWorldTile && pWorldTile->GetTileName() && pWorldTile->GetTileName()[0] != '\0')
			{
				int nOrder = pWorldTile->GetOrder();
				if (pWorldTile->GetMapType() != 0 ||  nOrder == 0)
				{
					continue;
				}
				std::vector<CWorldTile*>::iterator SortIter = m_mapSortbyLevelID.begin();
				while(SortIter != m_mapSortbyLevelID.end())
				{
					if (nOrder < (*SortIter)->GetOrder())
					{
						m_mapSortbyLevelID.insert(SortIter,1,pWorldTile);
						break;
					}
					++SortIter;
					if (SortIter == m_mapSortbyLevelID.end())
					{
						m_mapSortbyLevelID.push_back(pWorldTile);
						break;
					}
				}

			}
		}
	}
}

void CWorldBuffer::ClearTileModify( CWorldTile * tile, uInt32 tileId )
{
	//do nothing
}