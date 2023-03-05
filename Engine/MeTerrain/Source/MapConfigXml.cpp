/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	MapConfigXml.cpp
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "MeTerrain/stdafx.h"
// #include "resource.h"
#include "MeTerrain/MapConfigXml.h"
#include "tstring.h"


////////////////////////////////////////////////////////////////////////////////
static sInt32	nMapconfigXmlVersion = 100;
////////////////////////////////////////////////////////////////////////////////
CMapConfigXml::CMapConfigXml()
{
}

CMapConfigXml::~CMapConfigXml()
{
}


bool CMapConfigXml::WorldTileToMapData(CWorldTile* pTile, MapConfig::MapData* pMapData)
{
	if (pTile == NULL || pMapData == NULL)	{ return false;}

	pMapData->Id = pTile->GetMapId();
	pMapData->FilePath = _strlwr(pTile->GetPathName());		//保存小写

	char strTemp[MAX_PATH];
	char strValue[MAX_PATH];
	strcpy(strTemp, pTile->GetPathName());
	char *p = strrchr(strTemp, '\\');
	if( p )	{ p++; }
	else { p = strTemp; }
	strcpy(strValue, p);
	p = strrchr(strValue,'.');
	if( p ) { *p = 0; }
	char strMap[MAX_PATH];
	strcpy(strMap,pTile->GetReachablePathName());
	pMapData->ClientReachableMap = _strlwr(strMap);   //保存小写

	char strMonster[MAX_PATH];
	strcpy(strMonster,pTile->GetMonsterPath());
	pMapData->MonsterFilePath = _strlwr(strMonster);   //保存小写

	pMapData->MapName = pTile->GetTileName();

	pMapData->Row = pTile->GetRowColumn()[1];
	pMapData->Column = pTile->GetRowColumn()[0];
	pMapData->ShowFootPrint = pTile->GetShowFootPrint();
	pMapData->Type = pTile->GetMapType();
	pMapData->MinPlayerLevel = pTile->GetMinLevel();
	pMapData->Order = pTile->GetOrder();
	pMapData->CanRide = pTile->GetRide();
	pMapData->CanPk = pTile->GetCanPk();
	pMapData->Duration = pTile->GetDuration();
	pMapData->Count = pTile->GetCount();
	pMapData->UnitCount = pTile->GetUnitCount();
    pMapData->SystemCreate = pTile->GetSystemCreate();
	pMapData->m_nRegionOffsetX = pTile->GetRegionOffsetX();
	pMapData->m_nRegionOffsetY = pTile->GetRegionOffsetY();
	pMapData->m_nRegionEdge = pTile->GetRegionEdge();
	pMapData->SkyBox = pTile->GetSkyBoxPath();
	pMapData->EffectPath   = pTile->GetEffectPath();
    pMapData->MapNameColor = pTile->GetMapNameColor();
    pMapData->MapTip = pTile->GetMapTip();
	pMapData->m_bSunLightRender = pTile->IsSunLightRender();
	pMapData->m_BloomScale = pTile->GetBloomScale();
	pMapData->m_Luminance = pTile->GetLuminance();
	pMapData->CountryID = pTile->GetCountry();
	pMapData->m_fBrightnessOffset = pTile->GetBrightnessOffset();
	pMapData->m_fContrastOffsetR = pTile->GetContrastOffsetR();
	pMapData->m_fContrastOffsetG = pTile->GetContrastOffsetG();
	pMapData->m_fContrastOffsetB = pTile->GetContrastOffsetB();
	pMapData->ScriptFile = pTile->GetScriptFilePath();
	pMapData->m_bGrassDestBlendOne = pTile->IsGrassDestBlendOne();
	CResMgr* pResMgr = pTile->GetCResMgr();
	if (pResMgr == NULL) { return false; }
	int nCount = pResMgr->GetTransportCount();
	for (int i = 0; i < nCount; ++i)
	{
		CTransportResBase* pRes = pResMgr->Transport(i);
		if (pRes == NULL) { continue; }
		if (!pRes->IsTransport())
		{
			CTargetRes* pTarget = (CTargetRes*) pRes;
			if (pTarget->IsRelive()) //重生点
			{
				MapConfig::RelivePosition xRelive;
				xRelive.Id = pTarget->GetReliveId();
				xRelive.MapId = pTarget->GetReliveMapId();
				xRelive.PositionX = pTarget->GetPosX();
				xRelive.PositionY = pTarget->GetPosY();
				xRelive.Direction = pTarget->GetTargetDir();
				xRelive.Type = pTarget->GetReliveType();

				pMapData->AddRelivePosition(xRelive, true);
			}
			else			//目标点
			{
				MapConfig::TransportDestination xDestination;
				xDestination.Id = pTarget->GetNtargetID();
				xDestination.PositionX = pTarget->GetPosX();
				xDestination.PositionY = pTarget->GetPosY();
				xDestination.Direction = pTarget->GetTargetDir();
				xDestination.vecWeight = pTarget->GetPFWeightArr();

				pMapData->AddTransportDestination(xDestination, true);
			}			
		}
		else  //传送点
		{
			CTransportRes* pTransport = (CTransportRes*) pRes;

			MapConfig::TransportPosition xPosition;
			xPosition.Id = pTransport->GetEntranceId();
			xPosition.TargetMapId = pTransport->GetDesMapID();
			xPosition.TargetId = pTransport->GetNtargetID();
			xPosition.MinX = pTransport->GetLeft();
			xPosition.MaxX = pTransport->GetRight();
			xPosition.MaxY = pTransport->GetTop();
			xPosition.MinY = pTransport->GetBottom();

			pMapData->AddTransportPosition(xPosition, true);
		}
	}

	return true;
}


bool CMapConfigXml::MapDataTpWorldTile(MapConfig::MapData* pMapData, CWorldTile* pTile)
{
	if (pMapData == NULL || pTile == NULL) { return false; }

	pTile->SetMapId(pMapData->Id);
	pTile->SetRowColumn(pMapData->Row, pMapData->Column);
	pTile->SetTileName(pMapData->MapName.c_str());
	pTile->SetReachablePath(pMapData->ClientReachableMap.c_str());
	pTile->SetMonsterPath(pMapData->MonsterFilePath.c_str());
	pTile->SetShowFootPrint(pMapData->ShowFootPrint);
	pTile->SetMapType(pMapData->Type);
	pTile->SetMinLevel(pMapData->MinPlayerLevel);
	pTile->SetOrder(pMapData->Order);
	pTile->SetRide(pMapData->CanRide);
	pTile->SetCanPk(pMapData->CanPk);
	pTile->SetCanDuel(pMapData->CanDuel);//lyhqiecuo
	pTile->SetDuration(pMapData->Duration);
	pTile->SetCount(pMapData->Count);
	pTile->SetUnitCount(pMapData->UnitCount);
 	pTile->SetSkyBoxPath(pMapData->SkyBox.c_str());
	pTile->SetEffectPath(pMapData->EffectPath);
    pTile->SetMapNameColor(pMapData->MapNameColor);
    pTile->SetMapTip(pMapData->MapTip);
    pTile->SetSystemCreate(pMapData->SystemCreate);
	pTile->SetRegionOffsetX(pMapData->m_nRegionOffsetX);
	pTile->SetRegionOffsetY(pMapData->m_nRegionOffsetY);
	pTile->SetRegionEdge(pMapData->m_nRegionEdge);
	pTile->SetSunLightRender(pMapData->m_bSunLightRender);	
	pTile->SetBloomScale(pMapData->m_BloomScale);
	pTile->SetLuminance(pMapData->m_Luminance);	
	pTile->SetCountry(pMapData->CountryID);
	pTile->SetBrightnessOffset( pMapData->m_fBrightnessOffset );
	pTile->SetContrastOffset( pMapData->m_fContrastOffsetR, pMapData->m_fContrastOffsetG, pMapData->m_fContrastOffsetB );
	pTile->SetScripFilePath(pMapData->ScriptFile);
	pTile->SetGrassDestBlendOne(pMapData->m_bGrassDestBlendOne);
	CResMgr* pResMgr = pTile->GetCResMgr();
	if (pResMgr == NULL) { return false; }
	pResMgr->CleanTransport();

	MapConfig::tdmapiter tditer = pMapData->mapTransportDestinations.begin();
	MapConfig::tdmapiter tdend = pMapData->mapTransportDestinations.end();
	for ( ; tditer != tdend; ++tditer)
	{
		CTargetRes* pRes = (CTargetRes*)pResMgr->PushTarget(tditer->second.PositionX, tditer->second.PositionY, tditer->second.Direction, false);
		if (pRes == NULL) { continue; }
		pRes->SetNtargetID(tditer->second.Id);

		std::vector<int>::iterator viter = tditer->second.vecWeight.begin();
		std::vector<int>::iterator vend = tditer->second.vecWeight.end();
		for ( ; viter != vend; ++viter)
		{
			pRes->AddPFWeight(*viter);
		}
	}

	MapConfig::tpmapiter tpiter = pMapData->mapTransportPositions.begin();
	MapConfig::tpmapiter tpend = pMapData->mapTransportPositions.end();
	for ( ; tpiter != tpend; ++tpiter)
	{
		CTransportRes* pRes = (CTransportRes*)pResMgr->PushTransport(tpiter->second.MaxY, tpiter->second.MinX, 
			tpiter->second.MaxX, tpiter->second.MinY, tpiter->second.TargetId);
		if (pRes == NULL) { continue; }

		pRes->SetEntranceId(tpiter->second.Id);
		pRes->SetDesMapID(tpiter->second.TargetMapId);
	}
	
	MapConfig::rpmapiter rpiter = pMapData->mapRelivePositions.begin();
	MapConfig::rpmapiter rpend = pMapData->mapRelivePositions.end();
	for ( ; rpiter != rpend; ++rpiter)
	{
		CTargetRes* pRes = (CTargetRes*)pResMgr->PushTarget(rpiter->second.PositionX, rpiter->second.PositionY, rpiter->second.Direction, true);
		if (pRes == NULL) { continue; }
		pRes->SetReliveMapId(rpiter->second.MapId);
		pRes->SetReliveId(rpiter->second.Id);
		pRes->SetReliveType(rpiter->second.Type);
	}

	return true;
}


void CMapConfigXml::VerifyTransport( sInt32 nMapId,sInt32 targetId )
{
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(nMapId);
	if (pMapData == NULL)
	{
		Trace("error tile map id %d in  Map.Config !\n", nMapId);
		return;
	}

	MapConfig::TransportDestination* pDestination = pMapData->GetTransportDestinationById(targetId);
	if (pDestination == NULL)
	{
		Trace("error tile map target id %d of tile %s in Map.Config !\n",targetId, pMapData->FilePath.c_str());
	}
}



bool CMapConfigXml::LoadMapConfig()
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName())	{ return false; }

	char ConfigName[MAX_PATH];
	sprintf(ConfigName, "%s\\Map.Config", pWorld->GetWorldPath());

	if (!theMapConfig.LoadMapConfig(ConfigName))
	{			
		Trace("error Map.Config in world %s!\n", ConfigName);
		return false; //客户端直接返回
	}

	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	if (pBuffer == NULL) { return false; }

	int nCount = theMapConfig.MapDataCount();
	for (int i = 0; i < nCount; ++i)
	{
		MapConfig::MapData *pMapData = theMapConfig.GetMapDataByIndex(i);
		if (pMapData == NULL) { continue; }
		CWorldTile* pTitle = pBuffer->PushTileRes(pMapData->Id,pMapData->FilePath.c_str());

		if (pTitle == NULL) 
		{ 
			Trace("error tile name %s in  Map.Config !\n", pMapData->FilePath.c_str()); 
			continue; 
		}
		MapDataTpWorldTile(pMapData, pTitle);
	}	
	return true;
}

void CMapConfigXml::InitializeMapConfig()
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (pWorld == NULL) { return; }

	std::map<sInt32,CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
	sInt32 mapId = 0;
	for(std::map<sInt32,CWorldTile*>::iterator iter = tileHash.begin(); iter != tileHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (pWorldTile == NULL) {	continue; }

		pWorldTile->SetMapId(mapId);		
		MapConfig::MapData xMapData;
		WorldTileToMapData(pWorldTile, &xMapData);
		theMapConfig.AddMapData(xMapData, true);

		++mapId;
	}

}


//怎么以前不用id索引
bool CMapConfigXml::DeleteTileMapInfor( sInt32 tileId )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName()){ return false; }
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile ) { return false; }

	std::string strDir = _strlwr(tile->GetPathName());

	MapConfig::MapData* pMapData = theMapConfig.GetMapDataByDir(strDir.c_str(), true);
	if (pMapData != NULL)
	{
		return theMapConfig.RemoveMapData(pMapData->Id);
	}

	return false;
}

void CMapConfigXml::AddPFWeight( CWorldTile* tile,sInt32 targetId,sInt32 transportId,sInt32 weight )
{

}



