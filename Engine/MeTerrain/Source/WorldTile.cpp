/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldTile.cpp
* Create: 	10/06/2006
* Desc:		地图Tile结构定义
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeCommon\HeightMapData.h"
#include "Me3d/Model/Mex2.h"
#include "MeTerrain/SwRender.h"
#include "MeTerrain/Lighting/LightMapTexture.h"

////////////////////////////////////////////////////////////////////////////////
CWorldTile::CWorldTile(const char* pPath)
:m_bLoadReachableMap(false)
,m_bShowFootPrint(false)
,m_bSunLightRender(true)
{
	m_isLoad		= false;
// #ifdef WORLD_EDIT
	m_isModify		= false;
// #endif	// WORLD_EDIT
	m_chunckTable	= NULL;


	m_origin[0]		= 0.0f;
	m_origin[1]		= 0.0f;

	m_nRolePosition[0] = -1;
	m_nRolePosition[1] = -1;

	m_height[0]		=  swInfinity;
	m_height[1]		= -swInfinity;
    m_TotalHeight[0]=  swInfinity;
    m_TotalHeight[1]= -swInfinity;
	m_ndlResMgr		= NULL;
	m_reachableAngle= 40.f;
    int length = min(MAX_PATH, sizeof(char)*(strlen(pPath) + 1));
	memcpy(m_pathName,pPath,length);
	memset(m_tileName,0,sizeof(char)*64);
	memset(m_reachablePathName,0,sizeof(char)*MAX_PATH);
	memset(m_MonsterPath,0,sizeof(char)*MAX_PATH);
	// add, jiayi, [2009.4.14]
	memset(m_skyboxPath, 0, sizeof(char)*MAX_PATH);
	// temp, jiayi, [2009.4.14]
	sprintf_s( m_skyboxPath, MAX_PATH, "%s", "\\data\\SceneObject\\Common\\skybox\\common.mex" );
	m_TextureForcedMaxLevel = TextureLayerFlight;
	m_ForcedMinLOD = CResMgr::LOD0;
	
	m_MapId			= -1;
	m_nMinimapId	= -1;
	m_nRegionMapId  = -1;
	m_bPointSoundPlay	= false;

	m_pHeightMapData = NULL;

	m_nType = 0;
	m_nMinLevel = 1;
	m_nOrder = 0;
	m_bRide = true;
	m_bCanPk = false;
	m_nDuration = 0;
	m_nCount = 0;
	m_nUnitCount = 0;
	m_nRegionOffsetX = 0;
	m_nRegionOffsetY = 0;
	m_strEffectPath.clear();
	m_nRegionEdge = 1024;
	m_BloomScale = 0.0f;
	m_Luminance = 0.0f;
	m_Country	= 0;

	m_fBrightnessOffset = 0.f;		// 亮度偏移
	m_fContrastOffsetR = 1.f;		// 对比度R偏移
	m_fContrastOffsetG = 1.f;		// 对比度G偏移
	m_fContrastOffsetB = 1.f;		// 对比度B偏移

	m_bGrassDestBlendOne = false;

	m_vecLightMaps.clear();
	m_bduel = 1; //默认都可以切磋
}

CWorldTile::~CWorldTile()
{
	Reset();
	NDL_SAFE_DELETE( m_ndlResMgr );
	ClearLightMaps();
}

bool CWorldTile::Create( CWorldBuffer* worldBuffer,CResMgr* pndlResMgr )
{
	m_worldBuffer = worldBuffer;


	Assert( NULL == m_ndlResMgr );
	m_ndlResMgr = pndlResMgr;
	m_ndlResMgr->Create( worldBuffer, this );

	return true;
}

void CWorldTile::Reset()
{
	if (m_chunckTable)
	{
		for( int i = 0; i < GetChunkTotal(); i++ ) 
		{
			m_chunckTable[i]->SetLoadLevel(CWorldChunk::eInitialize);
		}
	}
	m_height[0]	=  swInfinity;
	m_height[1]	= -swInfinity;
	m_nRolePosition[0] = -1;
	m_nRolePosition[1] = -1;

	FreeChunckTable();
	m_isLoad	= false;
	m_ndlResMgr->Unload();
// #ifdef WORLD_EDIT
	m_isModify	= false;
// #endif	// WORLD_EDIT
	m_reachableMap.Destroy();
	m_bLoadReachableMap = false;
	if (GetEngine())
	{
		ITextureManager* pMgr = GetEngine()->GetTextureManager();
		if( pMgr )
		{
			if (m_nMinimapId != -1 )
			{
				pMgr->UnRegisterTexture( m_nMinimapId );
				m_nMinimapId = -1;
			}
			if (m_nRegionMapId != -1 )
			{
				pMgr->UnRegisterTexture( m_nRegionMapId );
				m_nRegionMapId = -1;
			}
		}	
	}
	m_tileQuadTree.Destroy();
	m_bPointSoundPlay = false;

	if( m_pHeightMapData )
	{
		delete m_pHeightMapData;
		m_pHeightMapData = NULL;
	}	
}
//------------------------------------------------------------------------------------------
void CWorldTile::OnDeviceLost()
{
	if( m_ndlResMgr)
		m_ndlResMgr->OnDeviceLost();
}

//------------------------------------------------------------------------------------------
void CWorldTile::OnDeviceReset(bool bBeforeReset)
{
	if( m_ndlResMgr)
		m_ndlResMgr->OnDeviceReset( bBeforeReset);
}



CWorldChunk* CWorldTile::GetChunk( sInt32 chunkX, sInt32 chunkY )
{
	if( !CheckChunk( chunkX, chunkY ) )
		return NULL;
	if (NULL == m_chunckTable)
	{
		m_chunckTable	= MeDefaultNew CWorldChunk*[GetChunkTotal()];
		for( int i = 0; i < GetChunkTotal(); i++ ) {
			m_chunckTable[i] = MeNew CWorldChunk( this );
			m_chunckTable[i]->Create( (i%m_rowColumn[0]), (i/m_rowColumn[0]) );
		}
		m_cNewChunkLoadLevel = MeDefaultNew char[GetChunkTotal()];
	}
	return m_chunckTable[chunkY*GetRowColumn()[0]+chunkX];
}

CWorldChunk* CWorldTile::GetChunk( sInt32 index )
{
	return GetChunk(index%GetRowColumn()[0],index/GetRowColumn()[0]);
}

CWorldChunk* CWorldTile::GetChunkFromPos( flt32 posX, flt32 posY )
{
	sInt32 chunk[2];
	chunk[0] = ChunkFromPos( posX );
	chunk[1] = ChunkFromPos( posY);

	return GetChunk( chunk[0], chunk[1] );
}

bool CWorldTile::CheckChunk( sInt32 chunkX, sInt32 chunkY )
{
	if( chunkX < 0 || chunkX >= GetRowColumn()[0] || chunkY < 0 || chunkY >= GetRowColumn()[1] ) {
		return false;
	}
	return true;
}

void CWorldTile::SetRowColumn( sInt32 row, sInt32 column )
{
	if (m_rowColumn[0] != column || m_rowColumn[1] != row)
	{
		FreeChunckTable();
		m_rowColumn[0]	= column;
		m_rowColumn[1]	= row;

		m_origin[0]		=  WORLD_CHUNKSIZE*m_rowColumn[0]*0.5f;
		m_origin[1]		= WORLD_CHUNKSIZE*m_rowColumn[1]*0.5f;
	}

}

void CWorldTile::CalcHeight()
{
	m_height[0] =  swInfinity;
	m_height[1] = -swInfinity;
	for( int i = 0; i < GetChunkTotal(); i++ )
	{
		m_height[0] = ZnMin<flt32>( m_height[0], GetChunk(i)->m_height[0] );
		m_height[1] = ZnMax<flt32>( m_height[1], GetChunk(i)->m_height[1] );
	}
}

void CWorldTile::UpdateHeightByChunk( CWorldChunk* pChunk )
{
	m_TotalHeight[0] = ZnMin<flt32>( m_TotalHeight[0], pChunk->m_fTotalHeight[0] );
	m_TotalHeight[1] = ZnMax<flt32>( m_TotalHeight[1], pChunk->m_fTotalHeight[1] );

}
void CWorldTile::CalcNormal()
{

}

flt32 CWorldTile::GetReachableAngle() const
{
	return m_reachableAngle;
}

void CWorldTile::SetReachableAngle( flt32 val )
{
	m_reachableAngle = val;
}

void CWorldTile::SetTileName(const char* val )
{
	memcpy(m_tileName,val,sizeof(char)*(strlen(val) + 1));
}

void CWorldTile::RefreshChunkLoadLevel( flt32 fRadius ,bool bRefreshPart)
{
	if (m_nRolePosition[0] == -1 || m_nRolePosition[1] == -1 )
	{
		for( int i = 0; i < GetChunkTotal(); i++ ) 
		{
			m_chunckTable[i]->SetLoadLevel(CWorldChunk::eDoodadLoaded);
		}
		return;
	}
// 	int nChangeCount = 0;
	int nIndex = -1;
	for( int i = 0; i < GetChunkTotal(); i++ ) 
	{
		float deltaX = m_chunckTable[i]->Origin()[0] - m_nRolePosition[0];
		float deltaY = m_chunckTable[i]->Origin()[1] - m_nRolePosition[1];
		float distance = sqrtf(deltaX*deltaX + deltaY*deltaY );
		if (SwGlobal::s_SimpleMapLoadMode)
		{
			if (distance < SwGlobal::s_SimpleMapLoadDistance)
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eDoodadLoaded;
			}
			else
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eInitialize;
			}
		}
		else
		{
			if (distance> fRadius + 70)
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eInitialize;
			}
			else if (distance > fRadius + 20)
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eTerrainLODLoaded;
			}
			else if (distance > SwGlobal::GetRender()->GetModelCullFar() + 35)
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eTerrainLoaded;
			}
			else if (distance > SwGlobal::GetRender()->GetRealDoodadShowInstance() + 50)
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eModelLoaded;
			}
			else
			{
				m_cNewChunkLoadLevel[i] = CWorldChunk::eDoodadLoaded;
			}

		}
		if (bRefreshPart && m_cNewChunkLoadLevel[i] != m_chunckTable[i]->GetLoadLevel())
		{
			// 			++nChangeCount;
			{
				nIndex = i;
				break;
			}
		}
	}
	if (bRefreshPart )
	{
		if (nIndex != -1)
		{
			m_chunckTable[nIndex]->SetLoadLevel(m_cNewChunkLoadLevel[nIndex]);
		}
	}
	else
	{
		for(int e = CWorldChunk::eTotalChunkLoadLevel - 1; e >= CWorldChunk::eInitialize; --e)
		{
			for( int i = 0; i < GetChunkTotal(); i++ ) 
			{
				if (m_cNewChunkLoadLevel[i] == e)
				{
					m_chunckTable[i]->SetLoadLevel(e);
				}
			}
		}
	}
// 	static int nTime = 0;
// 	static int nCountCount = 0;
// 	++nTime;
// 	nCountCount += nChangeCount;
// 	if (nChangeCount != 0)
// 	{
// 		nTime = 0;
// 		char debugString[1024];
// 		sprintf_s(debugString,1024,"%d Chunk nChangeCount\n",nChangeCount);
// 		OutputDebugString(debugString);
// 		nCountCount = 0;
// 	}
}

void CWorldTile::SetMonsterPath(const char* pPath )
{
	if (NULL != pPath)
	{
		memcpy(m_MonsterPath,pPath,sizeof(char)*(strlen(pPath) + 1));
	}
}

// void CWorldTile::SetSkyBoxPath(const char* skyboxPath)
// {
// 	_tstring tstr;
// 	tstr.fromUTF8(skyboxPath);
// 	memcpy(m_skyboxPath,skyboxPath,sizeof(char)*(strlen(skyboxPath) + 1));
// }

void CWorldTile::CreateFloorAndCollision()
{
	guardfunc;
	for( int i = 0; i < m_ndlResMgr->GetStaticModelList().size(); i++ )
	{
		TObjectInfo* pObject = m_ndlResMgr->GetStaticModelList()[i];
		pObject->CreateFloorAndCollision();
	}

	unguard;
}


void CWorldTile::LoadReachableMap( bool isFreeData)
{
	if ('\0' != m_reachablePathName[0])
	{
		char path[MAX_PATH];
		if ('.' == m_reachablePathName[0] && '\\' == m_reachablePathName[1])
		{
			sprintf_s( path, MAX_PATH, "%s\\%s",SwGlobal::GetWorld()->GetWorldPath(), &m_reachablePathName[2] );
		}
		else
		{
			sprintf_s( path, MAX_PATH, "%s\\%s",SwGlobal::GetWorld()->GetWorldPath(), m_reachablePathName );
		}

		m_bLoadReachableMap = m_reachableMap.Create(path,isFreeData);
	}
}

void CWorldTile::SetReachablePath(const char* pPath )
{
	if (NULL != pPath)
	{
		memcpy(m_reachablePathName,pPath,sizeof(char)*(strlen(pPath) + 1));
	}

}

SwMap& CWorldTile::ReachableMap()
{
	if (!m_bLoadReachableMap)
	{
		LoadReachableMap( );
	}
	return m_reachableMap;
}

void CWorldTile::MarkNPCPosOnReachableMap( float x,float y )
{
	const int Scope = 3;
	float delta = -Scope*0.25;
	for (int i = 0; i < Scope;++i)
	{
		for(int j = 0; j < Scope; ++j)
		{
			ReachableMap().AddBlockPoint(x + delta + i * 0.5,y + delta + j * 0.5);
		}
	}
}

void CWorldTile::LoadHeightMapData()
{
	if ( m_pHeightMapData )
	{ return; }

	std::string pathName = this->GetPathName();
	int start_pos = pathName.rfind('\\') + 1;
	std::string mapNameInPinYing = pathName.substr(start_pos, pathName.rfind('.') - start_pos);

	char acFilename[MAX_PATH] = {0};
	sprintf_s( acFilename, MAX_PATH, "%s/data/world/%s/%s.height", GetRootPath(), mapNameInPinYing.c_str(), mapNameInPinYing.c_str());
	_strlwr(acFilename);
	std::string strFilename( acFilename );

	m_pHeightMapData = new CHeightMapData();
	m_pHeightMapData->ReadDataFromFile( strFilename.c_str() );
}

bool CWorldTile::LoadMinimap()
{
	if (m_nMinimapId != -1)
	{
		return true;
	}
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, MAX_PATH*2, "data\\world\\%s", GetPathName() );
	_strlwr(fileName);
	char* pFind = strstr(fileName,".mew");
	strcpy(&pFind[1],"bmp");
	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	if( pMgr )
	{
		m_nMinimapId = pMgr->RegisterTexture(  fileName, FALSE,FALSE);
	}	

	if( m_nMinimapId == -1)
	{
		std::string error = "加载小地图";
		error += fileName;
		error +=  "失败！";
		OutputDebugStringA(error.c_str());
		Trace("加载小地图%s失败！",fileName);
	}

// 	std::string name = GetPathName();
// 	std::string::size_type pos = name.find('/');
// 	std::string::size_type endpos = name.find(".mew");
// 	if (pos == std::string::npos)
// 		pos = name.find('\\');
// 	if (pos != std::string::npos)
// 	{
// 		name = name.substr(pos + 1, endpos - pos);
// 		name += "bmp";
// 		std::string minimapFilename = "data\\world\\minimap\\";
// 		minimapFilename = minimapFilename + name;
// 
// 		ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 		if( pMgr )
// 		{
// 			m_nMinimapId = pMgr->RegisterTexture(  minimapFilename.c_str(), FALSE, FALSE, FALSE);
// 		}	
// 
// 		if( m_nMinimapId == -1)
// 		{
// 			std::string error = "加载小地图" + minimapFilename + "失败！";
// 			OutputDebugStringA(error.c_str());
// 			Trace("加载小地图%s失败！",minimapFilename.c_str());
// 		}
// 	}
	return m_nMinimapId != -1;

}

void CWorldTile::FreeChunckTable()
{
	if( NULL != m_chunckTable )	{
		for( int i = 0; i < GetChunkTotal(); i++ ) {
			SAFE_DELETE( m_chunckTable[i] );
		}
		delete []m_chunckTable;
		delete []m_cNewChunkLoadLevel;
		m_chunckTable = NULL;
	}
}

bool CWorldTile::LoadRegionMap()
{
	if (m_nRegionMapId != -1)
	{
		return true;
	}
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, MAX_PATH*2, "data\\world\\%s", GetPathName() );
	_strlwr(fileName);
	char* pFind = strstr(fileName,".mew");
	strcpy(&pFind[0],"_1.bmp");
	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	if( pMgr )
	{
		m_nRegionMapId = pMgr->RegisterTexture(  fileName, FALSE,FALSE);
	}	

	if( m_nRegionMapId == -1)
	{
		std::string error = "加载小地图";
		error += fileName;
		error +=  "失败！";
		OutputDebugStringA(error.c_str());
		Trace("加载小地图%s失败！",fileName);
	}
// 
// 	std::string name = GetPathName();
// 	std::string::size_type pos = name.find('/');
// 	std::string::size_type endpos = name.find(".mew");
// 	if (pos == std::string::npos)
// 		pos = name.find('\\');
// 	if (pos != std::string::npos)
// 	{
// 		name = name.substr(pos + 1, endpos - pos - 1);
// 		name += "_1.bmp";
// 		std::string minimapFilename = "data\\world\\RegionMap\\";
// 		minimapFilename = minimapFilename + name;
// 
// 		ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 		if( pMgr )
// 		{
// 			m_nRegionMapId = pMgr->RegisterTexture(  minimapFilename.c_str(), FALSE, FALSE, FALSE);
// 		}	
// 
// 		if( m_nRegionMapId == -1)
// 		{
// 			std::string error = "加载小地图" + minimapFilename + "失败！";
// 			OutputDebugStringA(error.c_str());
// 			Trace("加载小地图%s失败！",minimapFilename.c_str());
// 		}
// 	}
	return m_nRegionMapId != -1;

}

void CWorldTile::LoadLightMap( int nlightmap )
{
	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	if( !pMgr )
		return;

	if( nlightmap < 0 )
		return;

	char szLightMapFullName[MAX_PATH] = {0};
	char szTileNoExt[128] = {0};
	strncpy(szTileNoExt, GetPathName(), sizeof(szTileNoExt)-1);
	char* p = strrchr(szTileNoExt, '.');
	*p = '\0';

	char szTempFullName[MAX_PATH] = {0};
	// 从lightmap子目录下找
	// 查找'\\'
	char szFolder[128] = {0};
	strncpy(szFolder, szTileNoExt, sizeof(szFolder)-1);
	p = strrchr(szFolder, '\\');
	if( p && strlen(szFolder) > p - szFolder + 1)	// p后面还有字母
	{
		char szTileName[128] = {0};
		strncpy(szTileName, p+1, sizeof(szTileName)-1);
		*(p+1) = '\0';
		char szTemp[MAX_PATH] = {0};
		sprintf_s(szTemp, sizeof(szTemp)-1, "%slightmap\\%s", szFolder, szTileName);
		strncpy(szFolder, szTemp, sizeof(szFolder)-1);
	}
	sprintf_s( szTempFullName, sizeof(szTempFullName)-1, "%s\\%s_lm%d.dds",
		SwGlobal::GetWorld()->GetWorldPath(), szFolder, nlightmap );

	if( szTempFullName[0] == '.' && szTempFullName[1] == '.' )//../xxx
	{
		strncpy_s( szLightMapFullName, MAX_PATH, szTempFullName + 2, MAX_PATH - 2 );
	}
	else
	{
		strcpy_s( szLightMapFullName, MAX_PATH, szTempFullName );
	}

	int textureId = pMgr->RegisterTexture(szLightMapFullName, FALSE, FALSE);
	if( textureId < 0 )
	{
		// 从地图所在目录下找
		sprintf_s( szTempFullName, sizeof(szTempFullName)-1, "%s\\%s_lm%d.dds",
			SwGlobal::GetWorld()->GetWorldPath(), szTileNoExt, nlightmap );

		if( szTempFullName[0] == '.' && szTempFullName[1] == '.' )//../xxx
		{
			strncpy_s( szLightMapFullName, MAX_PATH, szTempFullName + 2, MAX_PATH - 2 );
		}
		else
		{
			strcpy_s( szLightMapFullName, MAX_PATH, szTempFullName );
		}

		textureId = pMgr->RegisterTexture(szLightMapFullName, FALSE, FALSE);
	}

	if( textureId >= 0 )
	{
		LightMapTexture* lm = new LightMapTexture(textureId, nlightmap);
		m_vecLightMaps.push_back(lm);
	}
}

void CWorldTile::ClearLightMaps()
{
	for(int i=0; i<m_vecLightMaps.size(); ++i)
	{
		if( m_vecLightMaps[i] )
		{
			delete m_vecLightMaps[i];
		}
	}
	m_vecLightMaps.clear();
}

void CWorldTile::RefreshLightmapTexId()
{
	CResMgr* resMgr = GetCResMgr();

	for( INT ChunkIndex = 0; ChunkIndex < GetChunkTotal(); ++ChunkIndex )
	{
		CWorldChunk* pWorldChunk = GetChunk(ChunkIndex);
		if( pWorldChunk->GetStaticModelList().empty() )
			continue;

		int nModelNum = pWorldChunk->GetStaticModelList().size();

		for( INT ModelIndex = 0; ModelIndex < nModelNum; ++ModelIndex )
		{
			sInt32 nModelId = pWorldChunk->GetStaticModelList()[ModelIndex];

			if( nModelId >= resMgr->GetStaticModelList().size() )
				continue;

			TObjectInfo* pObjInfo = resMgr->GetStaticModelList()[nModelId];
			if( !pObjInfo )
				continue;
			StaticMeshInstanceContainer& kCon = pObjInfo->GetStaticMeshInstanceContainer();
			for( StaticMeshInstanceContainerIter it = kCon.begin(); it != kCon.end(); ++ it )
			{
				LightMapTexture* pLMTex = GetLightMap((*it)->GetLayer()->LightMapIndex);
				if( !pLMTex )
					continue;
				(*it)->GetLayer()->nTextureID = pLMTex->GetTextureId();
			}
		}
	}
}
