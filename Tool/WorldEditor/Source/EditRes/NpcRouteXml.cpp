/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NPCRouteXml.cpp
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "RapidXml/MeRapidXml.h"
#include "MeTerrain/NPCRouteXml.h"
#include "tstring.h"

// #ifndef WORLD_EDIT
// #include "Game/map/SwMapManager.h"
// #endif
////////////////////////////////////////////////////////////////////////////////
static sInt32	nMapconfigXmlVersion = 100;
////////////////////////////////////////////////////////////////////////////////
CNPCRouteXml::CNPCRouteXml()
{
}

CNPCRouteXml::~CNPCRouteXml()
{
}




bool CNPCRouteXml::RefreshTileNPCRoute( sInt32 tileId )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName())
	{
		return false;
	}
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile )
		return false;

// 	if( !tile->IsLoad() )
// 		return false;
	std::string tileName = _strlwr(tile->GetPathName());
	
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	MeXmlElement* pRoot = m_doc.RootElement();
	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		char* pMew = (char*)pMapNode->Attribute("mew");
		if (pMew && tileName == _strlwr(pMew))
		{
			break;
		}
		pMapNode = pMapNode->NextSiblingElement("Map");
	}


	if (NULL == pMapNode)
	{
		pMapNode = AddMapElement(tile);
	}
// 	CString strMap (tile->GetTileName());	

    //std::wstring str = Common::_tstring::toWideString(tile->GetTileName());
    //pMapNode->SetAttribute("MapName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

	//pMapNode->Clear();

	pMapNode->remove_all_nodes();

	


	CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
	for (size_t i = 0; i < pResMgr->GetNPCRouteCount(); ++i)
	{
		CNPCRouteRes* flyRoute = pResMgr->NPCRoute(i);
		{
			MeXmlElement* pNPCRoute = pMapNode->InsertEndChild(("NPCRoute"))->ToElement();
			pNPCRoute->SetAttribute("NPCRouteIndex",flyRoute->GetId());
			std::wstring str = Common::_tstring::toWideString(flyRoute->GetName());
			pNPCRoute->SetAttribute("NPCRouteName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
			pNPCRoute->SetAttribute("NextMapId",flyRoute->GetNextMapID());
			pNPCRoute->SetAttribute("NextRouteId",flyRoute->GetNextRouteID());
			pNPCRoute->SetAttribute("FlyRoute",flyRoute->IsFlyRoute());

			for(size_t x = 0; x < flyRoute->GetRoutePointList().size();++x)
			{

				WriteRoutePoint(pNPCRoute, flyRoute, x);
				// 			pNPCRoute->SetDoubleAttribute("Dir",flyRoute->GetNPCRouteDir());
			}
		}
	}

	return WriteMapInfo(pWorld->GetWorldPath());
}

bool CNPCRouteXml::RefreshTileNPCRoute( CWorldTile* tile )
{
// 	CWorld* pWorld = SwGlobal::GetWorld();
// 	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	return RefreshTileNPCRoute(tile->GetMapId());
}

void CNPCRouteXml::VerifyRouteNPC( sInt32 nMapId,sInt32 targetId )
{
	std::string targetTileName;
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	if (-1 != nMapId)
	{
		std::map<sInt32,CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
		for(std::map<sInt32,CWorldTile*>::iterator iter = tileHash.begin(); iter != tileHash.end();++iter)
// 		for (sInt32 i = 0; i < tileHash.Size(); ++i)
		{
			CWorldTile* oldTile = iter->second;
			if (NULL == oldTile)
			{
				continue;
			}
			if (nMapId == oldTile->GetMapId())
			{
				targetTileName = oldTile->GetPathName();
			}
		}
	}
	if (targetTileName.length() == 0)
	{
		Trace("error tile map id %d in  NPCRoute.config !\n",nMapId);
	}
	else
	{
		bool bValid = false;
// 		CWorldTile* targetTile = pBuffer->GetTile(targetTileName);
// 		CResMgr* targetMgr = targetTile->GetCResMgr();
// 		for (size_t i = 0; i < targetMgr->GetNPCRouteCount(); ++i)
// 		{
// 			CNPCRouteResBase* res = targetMgr->NPCRoute(i);
// 			if ((!res->IsNPCRoute()) && res->GetNtargetID() == targetId)
// 			{
// 				bValid = true;
// 				break;
// 			}
// 		}
// 		if (!bValid)
// 		{
// 			Trace("error tile map flyRoute id %d of tile %s in NPCRoute.config !\n",targetId,targetTileName);
// 		}
	}

}


bool CNPCRouteXml::LoadNPCRoute()
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName())
	{
		return false;
	}
	std::string ConfigName = pWorld->GetWorldPath();
	ConfigName += '\\';
	ConfigName += "NPCRoute.config";
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(ConfigName.c_str(),&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		if (!m_doc.LoadFile(ConfigName.c_str()))
		{
			Trace("error NPCRoute.config in world %s!\n",ConfigName.c_str());
			return false;
		}
	}
	else
	{
		InitializeNPCRoute();
	}
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	MeXmlElement* pRoot = m_doc.FirstChildElement("NPCRoute")->ToElement();

	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		sInt32 mapId = 0;
		pMapNode->QueryIntAttribute("id",&mapId);
		CWorldTile* tile = pBuffer->GetTile(mapId);
		if (NULL == tile)
		{
			const char* tileName = pMapNode->Attribute("mew");
			Trace("error tile name %s in  NPCRoute.config !\n",tileName);
			pMapNode = pMapNode->NextSiblingElement("Map");
			continue;
		}


		CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
		pResMgr->CleanNPCRoute();
		MeXmlElement* pNPCRoute = pMapNode->FirstChildElement( "NPCRoute");
		while (pNPCRoute)
		{
			int routeIndex;
			pNPCRoute->QueryIntAttribute("NPCRouteIndex",&routeIndex);
			std::wstring str = Common::_tstring::UTF8towcs(pNPCRoute->Attribute("NPCRouteName"));
			CNPCRouteRes* pRes = (CNPCRouteRes*)pResMgr->PushNPCRoute(Common::_tstring::toNarrowString(str.c_str()).c_str());
			Assert(routeIndex == pRes->GetId());
			int bFlyRoute = 0;
			pNPCRoute->QueryIntAttribute("FlyRoute",&bFlyRoute);
			pRes->SetFlyRoute(bFlyRoute);
			int nextMapId = 0;
			int nextRouteId = 0;
			pNPCRoute->QueryIntAttribute("NextMapId",&nextMapId);
			pNPCRoute->QueryIntAttribute("NextRouteId",&nextRouteId);
			pRes->SetNextMapID(nextMapId);
			pRes->SetNextRouteID(nextRouteId);
			int x = 0;
			while(1) 
			{
				char strRoutePoint[256];
				sprintf_s(strRoutePoint,256,"RoutePoint%d",x);
				MeXmlElement* pRoutePoint = pNPCRoute->FirstChildElement( strRoutePoint);
				
				if (pRoutePoint)
				{
					float posX;float posY;float posZ;float WalkLength;float WalkSpeed;int nStayTime;int nStayAction = -1;int nSceneID = 0;
					pRoutePoint->QueryFloatAttribute("PosX",&posX);
					pRoutePoint->QueryFloatAttribute("PosY",&posY);
					pRoutePoint->QueryFloatAttribute("PosZ",&posZ);
					pRoutePoint->QueryFloatAttribute("WalkSpeed",&WalkSpeed);
					pRoutePoint->QueryFloatAttribute("WalkLength",&WalkLength);
					pRoutePoint->QueryIntAttribute("StayTime",&nStayTime);
					pRoutePoint->QueryIntAttribute("Action",&nStayAction);
					pRoutePoint->QueryIntAttribute("SceneID", &nSceneID);
					
					pRes->AddRoutePoint(posX,posY,posZ,false);
					pRes->SetWalkSpeed(x,WalkSpeed);
					pRes->SetWalkLength(x,WalkLength);
					pRes->SetStayTime(x,nStayTime);
					pRes->SetStayAction(x,nStayAction);
					pRes->SetSceneID( x, nSceneID );
				}
				else
				{
					break;
				}
				++x;
			} 
			pNPCRoute = pNPCRoute->NextSiblingElement( "NPCRoute");
		}


		pMapNode = pMapNode->NextSiblingElement("Map");
	}
	return true;
}

void CNPCRouteXml::InitializeNPCRoute()
{
	m_doc.Clear();
	m_doc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
// 	m_doc.InsertEndChild(m_doc.RetriveCommentElement("Notice: This xml is generated automatically. So don't modify the xml format or change any key or any string value."));
// 	m_doc.InsertEndChild(m_doc.RetriveCommentElement("It is recommend always to generate the file by world editor. However, you can modify some integer or float values for convenience."));
	MeXmlElement* pRoot = m_doc.InsertEndChild(("NPCRoute"))->ToElement();
	pRoot->SetAttribute("ConfigVersion",nMapconfigXmlVersion);
	CWorld* pWorld = SwGlobal::GetWorld();
	std::map<sInt32,CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
	for(std::map<sInt32,CWorldTile*>::iterator iter = tileHash.begin(); iter != tileHash.end();++iter)
// 	PtHashString<CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
// 	sInt32 mapId = 0;
// 	for (sInt32 i = 0; i < tileHash.Size(); ++i)
	{
		CWorldTile* tile = iter->second;
		if (tile == NULL)
		{
			continue;
		}
		AddMapElement(tile);
// 		++mapId;
	}
	WriteMapInfo(pWorld->GetWorldPath());

}

MeXmlElement* CNPCRouteXml::AddMapElement( CWorldTile* tile)
{
	MeXmlElement* pRoot = m_doc.FirstChildElement("NPCRoute")->ToElement();
	MeXmlElement* pMapNode = pRoot->InsertEndChild(("Map"))->ToElement();
	pMapNode->SetAttribute("id",tile->GetMapId());
	pMapNode->SetAttribute("mew",tile->GetPathName());


	std::wstring str = Common::_tstring::toWideString(tile->GetTileName());
	pMapNode->SetAttribute("MapName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

	return pMapNode;
}

bool CNPCRouteXml::WriteMapInfo(const char* worldPath)
{
	std::string lpszPathName = worldPath;
	lpszPathName += '\\';
	lpszPathName += "NPCRoute.config";
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(lpszPathName.c_str(),&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		DWORD dwAttrs = GetFileAttributes( lpszPathName.c_str() );
		if ( dwAttrs!=INVALID_FILE_ATTRIBUTES )
		{
			if ( dwAttrs & FILE_ATTRIBUTE_READONLY ) 
			{ 
				char prompt[2*MAX_PATH];
				sprintf_s(prompt,"文件%s只读，是否覆盖？",lpszPathName.c_str());
				int ret = MessageBox(GetActiveWindow( ),prompt,"提醒" , MB_OKCANCEL );
				if (ret == IDOK)
				{
					dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
					SetFileAttributes(lpszPathName.c_str(), dwAttrs ); 
				}
				else
					return FALSE;
			} 
		} 
	}
	return m_doc.SaveFile(lpszPathName.c_str());
}

bool CNPCRouteXml::DeleteTileNPCRoute( sInt32 tileId )
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName())
	{
		return false;
	}
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile )
		return false;

// 	if( !tile->IsLoad() )
// 		return false;
	std::string tileName = _strlwr(tile->GetPathName());

	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	MeXmlElement* pRoot = m_doc.RootElement();
	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		char* pMew = (char*)pMapNode->Attribute("mew");
		if (pMew && tileName == _strlwr(pMew))
		{
			break;
		}
		pMapNode = pMapNode->NextSiblingElement("Map");
	}
	if (NULL != pMapNode)
	{
		pRoot->remove_node(pMapNode);
		return WriteMapInfo(pWorld->GetWorldPath());
	}
	return false;
}


void CNPCRouteXml::WriteRoutePoint( MeXmlElement* pNPCRoute, CNPCRouteRes* flyRoute, size_t x )
{
	char strRoutePoint[256];
	sprintf_s(strRoutePoint,256,"RoutePoint%d",x);
	MeXmlElement* pRoutePoint = pNPCRoute->InsertEndChild((strRoutePoint))->ToElement();

	pRoutePoint->SetDoubleAttribute("PosX",flyRoute->GetPosX(x));
	pRoutePoint->SetDoubleAttribute("PosY",flyRoute->GetPosY(x));
	pRoutePoint->SetDoubleAttribute("PosZ",flyRoute->GetPosZ(x));
	pRoutePoint->SetDoubleAttribute("WalkSpeed",flyRoute->GetWalkSpeed(x));
	pRoutePoint->SetDoubleAttribute("WalkLength",flyRoute->GetWalkLength(x));
	pRoutePoint->SetAttribute("StayTime",flyRoute->GetStayTime(x));
	pRoutePoint->SetAttribute("Action",flyRoute->GetStayAction(x));
	pRoutePoint->SetAttribute("SceneID", flyRoute->GetSceneID(x));

}