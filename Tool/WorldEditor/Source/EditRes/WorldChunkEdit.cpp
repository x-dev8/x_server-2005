/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldChunkEdit.cpp
* Create: 	10/06/2006
* Desc:		本文件是从worldchunk抽出来的，实现了只有编辑器需要的接口
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "RapidXml/MeRapidXml.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/SwRender.h"

#include "Me3d/Model/Mex2.h"
#include "MeTerrain/NdlResMgr.h"
#include "MapConfig.h"
#include "tstring.h"
#include "application_config.h"
#include "MeTerrain/MapConfigXml.h"

void CWorldChunk::CloneFrom( CWorldChunk* pSrcChunk )
{
	m_height[0] = pSrcChunk->GetHeight()[0];
	m_height[1] = pSrcChunk->GetHeight()[1];


	CWorldTile* pSrcTile = pSrcChunk->m_parentTile;
	CResEditMgr* pSrcMgr = (CResEditMgr*)pSrcTile->GetCResMgr();

	CResEditMgr* pThisMgr = (CResEditMgr*)m_parentTile->GetCResMgr();

	//texture begin
	m_layerCount = 0;
	for( int l = 0; l < RES_LAYER_NUM; ++l ) 
	{
		if (pSrcChunk->m_texture[l] != RES_INVALID_ID)
		{
			CNdlTextureRes* pTexture = pSrcMgr->GetTexture(pSrcChunk->m_texture[l]);
			pThisMgr->ReplaceChunkTextrueId(this,l,pThisMgr->PushTexture(pTexture->GetName()));
			m_texInfo[l] = pSrcChunk->m_texInfo[l];
		}
		if( RES_INVALID_ID != m_texture[l] ) 
		{
			m_layerCount++;
		}
		if( l < (RES_LAYER_NUM-1) )	
		{
			if (pSrcChunk->m_alpha[l] != RES_INVALID_ID)
			{
				CNdlAlphaRes* pkNdlAlphaRes = pSrcMgr->GetAlpha(pSrcChunk->m_alpha[l]);
				if (pkNdlAlphaRes)
				{
					// 				uInt8 tmp[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
					uAlphaBit* alpha = pkNdlAlphaRes->GetMaskData();
					// 				for (int z = 0; z < WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM;++z)
					// 				{
					// 					tmp[z] = UINT32HIGHTOUINT8(alpha[z]);
					// 				}
					m_alpha[l]	= pThisMgr->PushAlpha(alpha);
				}
			}
		}
	}
	//texture end

	//m_shape clone
	for( sInt32 x = 0; x < (WORLD_TILE_CHUNK_UNIT_NUM + 1); ++x ) 
	{
		for( sInt32 y = 0; y < (WORLD_TILE_CHUNK_UNIT_NUM + 1); ++y ) 
		{

			sInt32 vId = y * (WORLD_TILE_CHUNK_UNIT_NUM+1) + x;
			m_vertexOut[vId].height		= pSrcChunk->m_vertexOut[vId].height;
			m_vertexOut[vId].niColor	= pSrcChunk->m_vertexOut[vId].niColor;
			m_vertexOut[vId].normal[0]	= pSrcChunk->m_vertexOut[vId].normal[0];	
			m_vertexOut[vId].normal[1]	= pSrcChunk->m_vertexOut[vId].normal[1];	
			m_vertexOut[vId].normal[2]	= pSrcChunk->m_vertexOut[vId].normal[2];	
			if( x < WORLD_TILE_CHUNK_UNIT_NUM && y < WORLD_TILE_CHUNK_UNIT_NUM ) 
			{

				vId = y * WORLD_TILE_CHUNK_UNIT_NUM + x;
				m_vertexIn[vId].height		= pSrcChunk->m_vertexIn[vId].height;
				m_vertexIn[vId].niColor		= pSrcChunk->m_vertexIn[vId].niColor;	
				m_vertexIn[vId].normal[0]	= pSrcChunk->m_vertexIn[vId].normal[0];
				m_vertexIn[vId].normal[1]	= pSrcChunk->m_vertexIn[vId].normal[1];
				m_vertexIn[vId].normal[2]	= pSrcChunk->m_vertexIn[vId].normal[2];
			}

		}
	}
	pThisMgr->PushChunkShape( this );
	//m_shape end


	//shadow begin
	if (pSrcChunk->m_shadow != RES_INVALID_ID)
	{
		CNdlAlphaRes*	pkShadow = pSrcMgr->GetShadow(pSrcChunk->m_shadow);
// 		uInt8 tmp[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
		uAlphaBit* alpha = pkShadow->GetMaskData();
// 		for (int z = 0; z < WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM;++z)
// 		{
// 			tmp[z] = UINT32HIGHTOUINT8(alpha[z]);
// 		}
		m_shadow = pThisMgr->PushShadow(alpha);
	}
	//shadow end

	//road begin
	if (pSrcChunk->m_road != RES_INVALID_ID)
	{
		CNdlAlphaRes*	pkRoad = pSrcMgr->GetRoad(pSrcChunk->m_road);
// 		uInt8 tmp[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
		uAlphaBit* alpha = pkRoad->GetMaskData();
// 		for (int z = 0; z < WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM;++z)
// 		{
// 			tmp[z] = UINT32HIGHTOUINT8(alpha[z]);
// 		}
		m_road = pThisMgr->PushRoad(alpha);
	}
	//road end


	SetCulled(pSrcChunk->IsCulled());
	//env begin
	m_envId = RES_INVALID_ID;
	if (pSrcChunk->m_envId != RES_INVALID_ID)
	{
		CNdlEnvRes* pEnv = pSrcMgr->GetEnvRes(pSrcChunk->m_envId);
		if (pEnv)
		{
			CStringA envNameA = pEnv->GetName();

			for (size_t i = 0; i < pThisMgr->GetEnvResList().size();++i)
			{
				CWorldRes* pEnv1 = pThisMgr->GetEnvResList()[i];
				if (envNameA == pEnv1->GetName())
				{
					m_envId = i;
					break;
				}
			}
			if (RES_INVALID_ID ==  m_envId)
			{
				sInt32 lightId = RES_INVALID_ID;
				if (pEnv->GetLightId() != RES_INVALID_ID)
				{
					CNdlLightRes* pLight = pSrcMgr->GetLightRes(pEnv->GetLightId());
					CStringA lightNameA = pLight->GetName();

					for (size_t i = 0; i < pThisMgr->GetLightList().size();++i)
					{
						CWorldRes* pLight = pThisMgr->GetLightList()[i];
						if (lightNameA == pLight->GetName())
						{
							lightId = i;
							break;
						}
					}
					if (RES_INVALID_ID ==  lightId)
					{
						lightId = pThisMgr->GetLightList().size();
						CNdlLightRes* lightRes		= MeNew CNdlLightRes;
						lightRes->SetName( pLight->GetName());
						lightRes->SetLightAmbient(pLight->GetLightAmbient());		
						lightRes->SetLightDiffuse(pLight->GetLightDiffuse());		
						lightRes->SetLightSpecular(pLight->GetLightSpecular());
						lightRes->SetLightDir(pLight->GetLightDir());
						lightRes->SetId(lightId);
						pThisMgr->GetLightList().push_back(lightRes);
					}
				}

				sInt32 fogId = RES_INVALID_ID;
				if (pEnv->GetFogId() != RES_INVALID_ID)
				{
					CNdlFogRes* pFog = pSrcMgr->GetFogRes(pEnv->GetFogId());
					CStringA fogNameA = pFog->GetName();

					for (size_t i = 0; i < pThisMgr->GetFogList().size();++i)
					{
						CWorldRes* pFog = pThisMgr->GetFogList()[i];
						if (fogNameA == pFog->GetName())
						{
							fogId = i;
							break;
						}
					}
					if (RES_INVALID_ID ==  fogId)
					{
						fogId = pThisMgr->GetFogList().size();
						CNdlFogRes* fogRes		= MeNew CNdlFogRes;
						fogRes->SetName( pFog->GetName());
						fogRes->SetLightColor(pFog->GetLightColor());
						fogRes->SetLightNear(pFog->GetLightNear());
						fogRes->SetLightFar(pFog->GetLightFar());
						fogRes->SetId(fogId);
						pThisMgr->GetFogList().push_back(fogRes);
					}
				}
				m_envId = pThisMgr->CreateEnv(pEnv->GetName(),lightId,fogId);
			}
		}		
	}
	//env end
	m_zoneId = RES_INVALID_ID;
	if (pSrcChunk->m_zoneId != RES_INVALID_ID)
	{
		CNdlZoneRes* pZone = pSrcMgr->GetZoneRes(pSrcChunk->m_zoneId);
		CStringA zoneNameA = pZone->GetName();

		for (size_t i = 0; i < pThisMgr->GetZoneResList().size();++i)
		{
			CWorldRes* pZone = pThisMgr->GetZoneResList()[i];
			if (zoneNameA == pZone->GetName())
			{
				m_zoneId = i;
				break;
			}
		}
		if (m_zoneId == RES_INVALID_ID)
		{
			m_zoneId = pThisMgr->CreateZone(pZone->GetName(),pZone->GetMuiscPath(), pZone->GetFontRect());
		}
	}
	if (pSrcChunk->m_liquidId != RES_INVALID_ID)
	{
		m_liquidId = pSrcChunk->m_liquidId;
		m_liquidColor = pSrcChunk->m_liquidColor;
		m_liquidHeight = pSrcChunk->m_liquidHeight;
		m_liquidAlphaCoaf = pSrcChunk->m_liquidAlphaCoaf;
		pThisMgr->PushChunkLiquid(this,m_shape,m_liquidId,m_liquidHeight,m_liquidColor,m_liquidAlphaCoaf);
	}


	//doodad begin
	{
		for (size_t i = 0; i < pSrcChunk->m_doodadList.size(); ++i)
		{
			TDoodadLevelInfo* pInfo = pSrcChunk->m_doodadList[i];
			CWorldRes* pRes = pSrcMgr->GetDoodad(pInfo->mdoodadId);
			sInt32 refId = pThisMgr->PushDoodad(pRes->GetName());

			sInt32 newid = AddDoodadLevel(pInfo->mulevelUnit,true);
			TDoodadLevelInfo* pNewDoodad = GetDoodadLevel(newid);
			pNewDoodad->mdoodadId = refId;
// 			pThisMgr->IncDoodadRef(refId);
			memcpy(pNewDoodad->GetDoodadMap(),pInfo->GetDoodadMap(),sizeof(TDoodadInfoForEdit)*pNewDoodad->mulevelUnit*pNewDoodad->mulevelUnit);
// 			pNewDoodad->RefreshDoodad(pThisMgr,this,m_parentTile);
		}

	}
	//doodad end
	m_isLoad = true;
}

void CWorldChunk::CalculateChunkTotalHeightForEditor( CResMgr *resMgr, flt32* fHeight )
{
	// 地表高度
	fHeight[0] = m_height[0];
	fHeight[1] = m_height[1];

	// 水面高度
	fHeight[0] = min(fHeight[0], m_liquidHeight);
	fHeight[1] = max(fHeight[1], m_liquidHeight);

	// 所有模型高度取最大最小
	for( size_t i=0; i<m_staticModelList.size(); i++ )
	{
		sInt32 id		= m_staticModelList[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			TObjectInfo* p	= resMgr->GetStaticModelList()[id];
			if(!p->model || p->model->HasEmitter())
				continue;
			Box* pWBox = p->model->GetWorldBBox();
			for(int b=0; b<8; b++)
			{
				float fDeltaHeight = pWBox->v[b].z - m_height[1];
				if( fDeltaHeight >= 90.f)
					continue;
				fHeight[0] = min(fHeight[0], pWBox->v[b].z);
				fHeight[1] = max(fHeight[1], pWBox->v[b].z);
			}
		}
	}
	m_fTotalHeight[0] = fHeight[0];
	m_fTotalHeight[1] = fHeight[1];
}


//以下内容是contrib 里面WorldTile.cpp里面挪出来的，实现了只有编辑器需要的函数

sInt32 CWorldTile::GetObjectCount()
{
	sInt32 objCount = 0;
	for( int i = 0; i < GetChunkTotal(); i++ ) {
		objCount += GetChunk(i)->m_staticModelList.size();
	}
	return objCount;
}

void CWorldTile::AttachHelperModel()
{
	for (sInt32 i = 0; i < m_ndlResMgr->GetTransportCount();++i)
	{
		CTransportResBase * pRes = (CTransportResBase *)m_ndlResMgr->Transport(i);
		pRes->AttachModel();
	}
	if (g_render->IsDisplayMonster())
	{
		((CResEditMgr*)m_ndlResMgr)->AttachAllMonsterQuad();
	}	
}

void CWorldTile::DetachHelperModel()
{
	for (sInt32 i = 0; i < m_ndlResMgr->GetTransportCount();++i)
	{
		CTransportResBase * pRes = m_ndlResMgr->Transport(i);
		((CTransportResBase*)pRes)->DetachModel();
	}
	if (g_render->IsDisplayMonster())
	{
		((CResEditMgr*)m_ndlResMgr)->DetachAllMonsterQuad();
	}	
}
bool CWorldTile::CalPFWeight()
{
	if (!m_bLoadReachableMap)
	{
		LoadReachableMap(false);
	}
	if (!m_bLoadReachableMap)
	{
		return false;
	}
	CResMgr* pResMgr = GetCResMgr();
	for (size_t i = 0; i < pResMgr->GetTransportCount(); ++i)
	{
		CTransportResBase* pRes = pResMgr->Transport(i);
		if (!pRes->IsTransport())
		{
			CTargetRes* target = (CTargetRes*)pRes;
			if (!target->IsRelive())  //只计算传送目标点
			{
				target->ClearPFWeight();
				for (size_t j = 0; j < pResMgr->GetTransportCount(); ++j)
				{
					CTransportResBase* pTranRes = pResMgr->Transport(j);
					if (pTranRes->IsTransport())
					{
						CTransportRes* transport = (CTransportRes*)pTranRes;
						target->AddPFWeight(m_reachableMap.CalPFWeight(target->GetPosX(),target->GetPosY(),transport->GetPosX(),transport->GetPosY()));
					}
				}
			}
		}
	}
	return true;
}

bool CMapConfigXml::RefreshTileMapInfo( CWorldTile* tile )
{
// 	CWorld* pWorld = SwGlobal::GetWorld();
// 	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	return RefreshTileMapInfo(tile->GetMapId());
}

bool CMapConfigXml::RefreshTileMapInfo( sInt32 tileId )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (pWorld == NULL || !pWorld->HasName())	{ return false;	}

	CWorldTile* pTile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == pTile || !pTile->IsLoad()) { return false; }

	std::string strDir = _strlwr(pTile->GetPathName());

	MapConfig::MapData xMapData;
	WorldTileToMapData(pTile, &xMapData);
	MapConfig::MapData* pOldMapData = theMapConfig.GetMapDataById(pTile->GetMapId());
	if( pOldMapData )
	{
		// 保存status属性
		if( pOldMapData->GetStatusSize() )
		{
			for( int i=0; i<pOldMapData->GetStatusSize(); ++i )
			{
				MapConfig::Status* pStatus = pOldMapData->GetStatusByIndex(i);
				if( pStatus )
					xMapData.AddStatus(*pStatus);	
			}
		}
	}
	theMapConfig.AddMapData(xMapData, true);

	int pos = strDir.rfind('\\');
	std::string strMapFolderName;
	if (pos != std::string::npos)
		strMapFolderName = strDir.substr(0, pos);

	return WriteMapInfo(pWorld->GetWorldPath(), strMapFolderName.c_str(), tileId);
}

bool CMapConfigXml::WriteMapInfo(const char* szWorldPath, const char *szMapFolder, int tile_id)
{
	char lpszPathName[MAX_PATH];
	sprintf(lpszPathName, "%s\\Map.Config", szWorldPath);
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(lpszPathName,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		DWORD dwAttrs = GetFileAttributes( lpszPathName );
		if ( dwAttrs!=INVALID_FILE_ATTRIBUTES )
		{
			if ( dwAttrs & FILE_ATTRIBUTE_READONLY ) 
			{ 
				char prompt[2*MAX_PATH];
				sprintf_s(prompt,2*MAX_PATH,"文件%s只读，是否覆盖？",lpszPathName);
				int ret = MessageBox( NULL, prompt, "提醒", MB_OKCANCEL );
				//int ret = ::AfxMessageBox(prompt,  MB_OKCANCEL );
				if (ret == IDOK)
				{
					dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
					SetFileAttributes(lpszPathName, dwAttrs ); 
				}
				else
					return FALSE;
			} 
		} 
	}

	return theMapConfig.SaveMapConfig(szWorldPath, szMapFolder, tile_id);
}

bool CMapConfigXml::LoadMapConfig_Old()
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName())
	{
		return false;
	}

	char ConfigName[MAX_PATH];
	sprintf(ConfigName, "%s\\MapConfig.xml", pWorld->GetWorldPath());
	// 	WIN32_FIND_DATAA data;
	// 	HANDLE hFind = FindFirstFileA(ConfigName,&data);
	// 	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	// 	if (bFind)
	{
		if (!m_doc.LoadFile(ConfigName))
		{
			InitializeMapConfig();
			Trace("error MapConfig.config in world %s!\n",ConfigName);
			return false;
		}
	}
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	MeXmlElement* pRoot = m_doc.FirstChildElement("MapConfig")->ToElement();

	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		sInt32 mapId = 0;
		pMapNode->QueryIntAttribute("id",&mapId);
		CWorldTile* tile = pBuffer->GetTile(mapId);
		if (NULL == tile)
		{
			const char* tileName = pMapNode->Attribute("mew");
			Trace("error tile name %s in  MapConfig.config !\n",tileName);
			pMapNode = pMapNode->NextSiblingElement("Map");
			continue;
		}
		tile->SetMapId(mapId);
		int row,column;
		pMapNode->QueryIntAttribute("Row",&row);
		pMapNode->QueryIntAttribute("Column",&column);
		tile->SetRowColumn(row,column);
		int showFootprint = 0;
		pMapNode->QueryIntAttribute("ShowFootPrint",&showFootprint);
		tile->SetShowFootPrint(showFootprint);
		std::wstring str = Common::_tstring::UTF8towcs(pMapNode->Attribute("MapName"));
		tile->SetTileName(Common::_tstring::toNarrowString(str.c_str()).c_str());

		tile->SetReachablePath(pMapNode->Attribute("ClientReachableMap"));
		CResMgr* pResMgr = tile->GetCResMgr();
		pResMgr->CleanTransport();
		MeXmlElement* pTarget = pMapNode->FirstChildElement( "Target");
		while (pTarget)
		{
			float posX;float posY;float dir;int targetId;
			pTarget->QueryFloatAttribute("PosX",&posX);
			pTarget->QueryFloatAttribute("PosY",&posY);
			pTarget->QueryFloatAttribute("Dir",&dir);
			pTarget->QueryIntAttribute("TargetIndex",&targetId);
			CTargetRes* pRes = (CTargetRes*)pResMgr->PushTarget(posX,posY,dir, false);
			int weight = 0;
			int x = 0;
			while(1) 
			{
				char strweight[MAX_PATH];
				sprintf(strweight, "Weight%d",x);

				if (MEXML_SUCCESS == pTarget->QueryIntAttribute(strweight,&weight))
				{
					pRes->AddPFWeight(weight);
				}
				else
				{
					break;
				}
				++x;
			} 
			pRes->SetNtargetID(targetId);
			pTarget = pTarget->NextSiblingElement( "Target");
		}

		MeXmlElement* pTransport = pMapNode->FirstChildElement( "Transport");
		while (pTransport)
		{
			float top;float left;float right;float bottom;sInt32 targetId;sInt32 nMapId;sInt32 nEntranceId;
			if(MEXML_SUCCESS != pTransport->QueryFloatAttribute("Bottom",&bottom))
			{
				pTransport->QueryFloatAttribute("MinY",&bottom);
			}
			if(MEXML_SUCCESS != pTransport->QueryFloatAttribute("Top",&top))
			{
				pTransport->QueryFloatAttribute("MaxY",&top);
			}
			if(MEXML_SUCCESS != pTransport->QueryFloatAttribute("Left",&left))
			{
				pTransport->QueryFloatAttribute("MinX",&left);
			}
			if(MEXML_SUCCESS != pTransport->QueryFloatAttribute("Right",&right))
			{
				pTransport->QueryFloatAttribute("MaxX",&right);
			}
			pTransport->QueryIntAttribute("TargetId",&targetId);
			pTransport->QueryIntAttribute("TargetMapId",&nMapId);
			CTransportRes* pRes = (CTransportRes*)pResMgr->PushTransport(top,left,right,bottom,targetId);
			pRes->SetDesMapID(nMapId);
			if (MEXML_SUCCESS == pTransport->QueryIntAttribute("EntranceId",&nEntranceId))
			{
				pRes->SetEntranceId(nEntranceId);
			}
			pTransport = pTransport->NextSiblingElement( "Transport");
		}
		// add, jiayi, [2009.4.14],skybox
		// 		MeXmlElement* pSkybox = pMapNode->FirstChildElement( "Skybox" );
		// 		if(pSkybox)
		// 		{
		// 			const char* skyboxPath = pSkybox->Attribute( "SkyboxPath" );
		// 			tile->SetSkyBoxPath( skyboxPath );
		// 		}

		//转换
		MapConfig::MapData xMapData;
		WorldTileToMapData(tile, &xMapData);
		theMapConfig.AddMapData(xMapData, true);
		pMapNode = pMapNode->NextSiblingElement("Map");
	}

	theMapConfig.SaveMapConfig(pWorld->GetWorldPath());
	return true;
}


bool MapConfig::SaveMapConfig(const char* szWorldPath, const char *szMapFolder, int tile_id)
{
	if (szWorldPath == NULL || *szWorldPath == 0)
		return false;

	bool isWriteSingle = (szWorldPath != NULL && strlen(szWorldPath) > 0 && tile_id != -1);

	MeXmlDocument xMeXmlDoc;

	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","UTF-8","yes"));
	//xMeXmlDoc.InsertEndChild(MeXmlComment("Notice: This xml is generated automatically. So don't modify the xml format or change any key or any string value."));
	//xMeXmlDoc.InsertEndChild(MeXmlComment("It is recommend always to generate the file by world editor. However, you can modify some integer or float values for convenience."));

	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild((Root_Key))->ToElement();
	if (pRoot == NULL) { return false; }

	Common::_tstring strName = "HeroOnline";
	pRoot->SetAttribute(Name_Key, strName.toUTF8().c_str());

	Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();		
	pRoot->SetAttribute(Version_Key, strVersion.toUTF8().c_str()); //version	

	MeXmlElement *pMaps = pRoot->InsertEndChild((Maps_Key))->ToElement();
	if (pMaps == NULL) { return false; }

	// 按Id排序
	sort(m_vecMapData.begin(), m_vecMapData.end());

	char szSavePath[MAX_PATH] = {0};

	mdveciter iter;
	mdveciter end;
	if (isWriteSingle)
	{
		sprintf_s(szSavePath, MAX_PATH - 1, "%s\\%s\\Map.Config", szWorldPath, szMapFolder);

		CWorldTile *tile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTile(tile_id);
		if (tile == NULL || !tile->IsLoad())
			return false;

		int target_idx = GetIdToIndex(tile_id);
		int idx = 0;
		for (mdveciter i = m_vecMapData.begin(); i != m_vecMapData.end(); ++i, ++idx)
		{
			if (idx == target_idx)
			{
				iter = i;
				end = ++i;
				break;
			}
		}
	}
	else
	{
		sprintf_s(szSavePath, MAX_PATH - 1, "%s\\Map.config", szWorldPath);

		iter = m_vecMapData.begin();
		end = m_vecMapData.end();
	}
	
	for ( ; iter != end; ++iter)
	{
		MeXmlElement* pMap = pMaps->InsertEndChild((Map_Key))->ToElement();
		if (pMap == NULL) { return false; }

		pMap->SetAttribute(Id_Key, iter->Id);	

		//FilePath
		Common::_tstring FilePath = iter->FilePath;		
		pMap->SetAttribute(FilePath_Key, FilePath.toUTF8().c_str());

		Common::_tstring ClientReachableMap = iter->ClientReachableMap;		
		pMap->SetAttribute(ClientReachableMap_Key, ClientReachableMap.toUTF8().c_str());

		Common::_tstring MonsterFilePath = iter->MonsterFilePath;		
		pMap->SetAttribute(MonsterFilePath_Key, MonsterFilePath.toUTF8().c_str());

		Common::_tstring MapName = iter->MapName;
		pMap->SetAttribute(MapName_Key, MapName.toUTF8().c_str());

		pMap->SetAttribute(Row_Key, iter->Row);
		pMap->SetAttribute(Column_Key, iter->Column);
		pMap->SetAttribute(ShowFootPrint_Key, iter->ShowFootPrint);
		pMap->SetAttribute(GrassDestBlendOne_Key, iter->m_bGrassDestBlendOne);
		pMap->SetAttribute(Type_Key, iter->Type);
		pMap->SetAttribute(MinPlayerLevel_Key, iter->MinPlayerLevel);
		pMap->SetAttribute(Order_Key, iter->Order);
		pMap->SetAttribute(CanPk_Key, (int) iter->CanPk);
		pMap->SetAttribute(CanRide_Key, (int) iter->CanRide);
		pMap->SetAttribute(CanPet_Key, (int) iter->CanPet);
		pMap->SetAttribute(Duration_Key, iter->Duration);
		pMap->SetAttribute(Count_Key, iter->Count);
		pMap->SetAttribute(UnitCount_Key, iter->UnitCount);
		pMap->SetAttribute( SystemCreate_Key, iter->SystemCreate );
		pMap->SetAttribute(RegionMapOffsetX_Key,iter->m_nRegionOffsetX);
		pMap->SetAttribute(RegionMapOffsetY_Key,iter->m_nRegionOffsetY);
		pMap->SetAttribute(RegionMapEdge_Key,iter->m_nRegionEdge);
		pMap->SetAttribute(SunLightRender_Key,iter->m_bSunLightRender);
		pMap->SetAttribute(ExpRate_Key,iter->ExpRate);
		Common::_tstring ScripFile = iter->ScriptFile;
		pMap->SetAttribute(ScriptFilePath_Key, ScripFile.toUTF8().c_str());

		// 天空盒
		Common::_tstring SkyBox = iter->SkyBox;
		pMap->SetAttribute(SkyBox_Key, SkyBox.toUTF8().c_str());

		Common::_tstring StrMapNameColor;
		StrMapNameColor = iter->MapNameColor;
		pMap->SetAttribute(MapNameColor_Key,StrMapNameColor.toUTF8().c_str());

		Common::_tstring StrMapTip;
		StrMapTip = iter->MapTip;
		pMap->SetAttribute(MapTip_Key,StrMapTip.toUTF8().c_str());

		Common::_tstring EffectPath = iter->EffectPath;
		pMap->SetAttribute(EffectPath_Key, EffectPath.toUTF8().c_str());


		MeXmlElement* pTransportDestinations = pMap->InsertEndChild((TransportDestinations_Key))->ToElement();
		if (pTransportDestinations == NULL) { return false; }

		tdmapiter tditer = iter->mapTransportDestinations.begin();
		tdmapiter tdend = iter->mapTransportDestinations.end();
		for ( ; tditer != tdend; ++tditer)
		{			
			MeXmlElement* pTransportDestination = pTransportDestinations->InsertEndChild((TransportDestination_Key))->ToElement();
			if (pTransportDestination == NULL) { return false; }

			pTransportDestination->SetAttribute(Id_Key, tditer->second.Id);
			pTransportDestination->SetDoubleAttribute(PositionX_Key, tditer->second.PositionX);
			pTransportDestination->SetDoubleAttribute(PositionY_Key, tditer->second.PositionY);
			pTransportDestination->SetDoubleAttribute(Direction_Key, tditer->second.Direction);

			vector<int>::iterator viter = tditer->second.vecWeight.begin();
			vector<int>::iterator vend = tditer->second.vecWeight.end();

			for (int i = 0; viter != vend; ++viter, ++i)
			{
				char szIndex[31] = "";
				sprintf_s(szIndex, sizeof(szIndex) - 1, Weight_Key, i);

				pTransportDestination->SetAttribute(szIndex, *viter);
			}
		}

		MeXmlElement* pTransportPositions = pMap->InsertEndChild((TransportPositions_Key))->ToElement();
		if (pTransportPositions == NULL) { return false; }

		tpmapiter tpiter = iter->mapTransportPositions.begin();
		tpmapiter tpend = iter->mapTransportPositions.end();
		for ( ; tpiter != tpend; ++tpiter)
		{
			MeXmlElement* pTransportPosition = pTransportPositions->InsertEndChild((TransportPosition_Key))->ToElement();
			if (pTransportPosition == NULL) { return false; }

			pTransportPosition->SetAttribute(Id_Key, tpiter->second.Id);
			pTransportPosition->SetAttribute(TargetMapId_Key, tpiter->second.TargetMapId);
			pTransportPosition->SetAttribute(TargetId_Key, tpiter->second.TargetId);
			pTransportPosition->SetDoubleAttribute(MinX_Key, tpiter->second.MinX);
			pTransportPosition->SetDoubleAttribute(MaxX_Key, tpiter->second.MaxX);
			pTransportPosition->SetDoubleAttribute(MinY_Key, tpiter->second.MinY);
			pTransportPosition->SetDoubleAttribute(MaxY_Key, tpiter->second.MaxY);
		}

		MeXmlElement* pRelivePositions = pMap->InsertEndChild((RelivePositions_Key))->ToElement();
		if (pRelivePositions == NULL) { return false; }

		rpmapiter rpiter = iter->mapRelivePositions.begin();
		rpmapiter rpend = iter->mapRelivePositions.end();
		for ( ; rpiter != rpend; ++rpiter)
		{
			MeXmlElement* pRelivePosition = pRelivePositions->InsertEndChild((RelivePosition_Key))->ToElement();
			if (pRelivePosition == NULL) { return false; }

			pRelivePosition->SetAttribute(Id_Key, rpiter->second.Id);
			pRelivePosition->SetAttribute(TargetMapId_Key, rpiter->second.MapId);
			pRelivePosition->SetDoubleAttribute(PositionX_Key, rpiter->second.PositionX);
			pRelivePosition->SetDoubleAttribute(PositionY_Key, rpiter->second.PositionY);
			pRelivePosition->SetDoubleAttribute(Direction_Key, rpiter->second.Direction);
			pRelivePosition->SetAttribute(Type_Key, rpiter->second.Type);
		}

		if (!iter->Statuss.empty())
		{
			MeXmlElement* pStatuss_Key = pMap->InsertEndChild((Statuss_Key))->ToElement();
			if (pStatuss_Key == NULL) 
			{ return false; }

			statusiter statusItr = iter->Statuss.begin();
			statusiter statusItrEnd = iter->Statuss.end();
			for (;statusItr != statusItrEnd;++statusItr)
			{
				MeXmlElement* pStatus_Key = pStatuss_Key->InsertEndChild((Status_Key))->ToElement();
				if (pStatus_Key == NULL) 
				{ return false; }

				pStatus_Key->SetAttribute(Id_Key,statusItr->Id);
				pStatus_Key->SetAttribute(StatusLevel_Key,statusItr->Level);
			}
		}        
		MeXmlElement* pBloom = pMap->InsertEndChild((Bloom_Key))->ToElement();
		if (pBloom == NULL) 
		{ return false; }

		pBloom->SetDoubleAttribute(BloomScale_Key,iter->m_BloomScale);
		pBloom->SetDoubleAttribute(BloomLuminance_Key,iter->m_Luminance);

		MeXmlElement* pBrightContrast = pMap->InsertEndChild((BrightContrast_Key))->ToElement();
		if (pBrightContrast == NULL) 
		{ return false; }

		pBrightContrast->SetDoubleAttribute(BrightnessOffset_Key,iter->m_fBrightnessOffset);
		pBrightContrast->SetDoubleAttribute(ContrastOffsetR_Key,iter->m_fContrastOffsetR);
		pBrightContrast->SetDoubleAttribute(ContrastOffsetG_Key,iter->m_fContrastOffsetG);
		pBrightContrast->SetDoubleAttribute(ContrastOffsetB_Key,iter->m_fContrastOffsetB);
	}

	return xMeXmlDoc.SaveFile(szSavePath);
}
