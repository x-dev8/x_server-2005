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
// #include "resource.h"
#include "NPCRouteXml.h"
#include "tstring/tstring.h"

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
	TiXmlElement* pRoot = m_doc.RootElement();
	TiXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		if (tileName == _strlwr((char*)pMapNode->Attribute("mew")))
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

    std::wstring str = Common::_tstring::toWideString(tile->GetTileName());
    pMapNode->SetAttribute("MapName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

	pMapNode->Clear();
	CResMgr* pResMgr = tile->GetCResMgr();
	for (size_t i = 0; i < pResMgr->GetNPCRouteCount(); ++i)
	{
		CNPCRouteRes* flyRoute = pResMgr->NPCRoute(i);
		{
			TiXmlElement* pNPCRoute = pMapNode->InsertEndChild(TiXmlElement("NPCRoute"))->ToElement();
			pNPCRoute->SetAttribute("NPCRouteIndex",flyRoute->GetId());
			std::wstring str = Common::_tstring::toWideString(flyRoute->GetName());
			pNPCRoute->SetAttribute("NPCRouteName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

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
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	return RefreshTileNPCRoute(pBuffer->GetTileHashId(tile->GetPathName()));
}

void CNPCRouteXml::VerifyRouteNPC( sInt32 nMapId,sInt32 targetId )
{
	std::string targetTileName;
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	if (-1 != nMapId)
	{
		PtHashString<CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
		for (sInt32 i = 0; i < tileHash.Size(); ++i)
		{
			CWorldTile* oldTile = tileHash[i];
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
	TiXmlElement* pRoot = m_doc.FirstChildElement("NPCRoute")->ToElement();

	TiXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		const char* tileName = pMapNode->Attribute("mew");
		CWorldTile* tile = pBuffer->GetTile(tileName);
		if (NULL == tile)
		{
			Trace("error tile name %s in  NPCRoute.config !\n",tileName);
			pMapNode = pMapNode->NextSiblingElement("Map");
			continue;
		}
		sInt32 mapId = 0;
		pMapNode->QueryIntAttribute("id",&mapId);

		CResMgr* pResMgr = tile->GetCResMgr();
#ifdef WORLD_EDIT
		pResMgr->CleanNPCRoute();
#endif
		TiXmlElement* pNPCRoute = pMapNode->FirstChildElement( "NPCRoute");
		while (pNPCRoute)
		{
			int routeIndex;
			pNPCRoute->QueryIntAttribute("NPCRouteIndex",&routeIndex);
			std::wstring str = Common::_tstring::UTF8towcs(pNPCRoute->Attribute("NPCRouteName"));
			CNPCRouteRes* pRes = (CNPCRouteRes*)pResMgr->PushNPCRoute(Common::_tstring::toNarrowString(str.c_str()).c_str());
			Assert(routeIndex == pRes->GetId());
			int x = 0;
			while(1) 
			{
				char strRoutePoint[256];
				sprintf_s(strRoutePoint,256,"RoutePoint%d",x);
				TiXmlElement* pRoutePoint = pNPCRoute->FirstChildElement( strRoutePoint);
				
				if (pRoutePoint)
				{
					float posX;float posY;float WalkLength;float WalkSpeed;int nStayTime;int nStayAction = -1;
					pRoutePoint->QueryFloatAttribute("PosX",&posX);
					pRoutePoint->QueryFloatAttribute("PosY",&posY);
					pRoutePoint->QueryFloatAttribute("WalkSpeed",&WalkSpeed);
					pRoutePoint->QueryFloatAttribute("WalkLength",&WalkLength);
					pRoutePoint->QueryIntAttribute("StayTime",&nStayTime);
					pRoutePoint->QueryIntAttribute("Action",&nStayAction);
					pRes->AddRoutePoint(posX,posY,0,false);
					pRes->SetWalkSpeed(x,WalkSpeed);
					pRes->SetWalkLength(x,WalkLength);
					pRes->SetStayTime(x,nStayTime);
					pRes->SetStayAction(x,nStayAction);
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
	m_doc.InsertEndChild(TiXmlDeclaration("1.0","utf-8","yes"));
	m_doc.InsertEndChild(TiXmlComment("Notice: This xml is generated automatically. So don't modify the xml format or change any key or any string value."));
	m_doc.InsertEndChild(TiXmlComment("It is recommend always to generate the file by world editor. However, you can modify some integer or float values for convenience."));
	TiXmlElement* pRoot = m_doc.InsertEndChild(TiXmlElement("NPCRoute"))->ToElement();
	pRoot->SetAttribute("ConfigVersion",nMapconfigXmlVersion);
	CWorld* pWorld = SwGlobal::GetWorld();
	PtHashString<CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
	sInt32 mapId = 0;
	for (sInt32 i = 0; i < tileHash.Size(); ++i)
	{
		CWorldTile* tile = tileHash[i];
		if (tile == NULL)
		{
			continue;
		}
		AddMapElement(tile);
		++mapId;
	}
	WriteMapInfo(pWorld->GetWorldPath());

}

TiXmlElement* CNPCRouteXml::AddMapElement( CWorldTile* tile)
{
	TiXmlElement* pRoot = m_doc.FirstChildElement("NPCRoute")->ToElement();
	TiXmlElement* pMapNode = pRoot->InsertEndChild(TiXmlElement("Map"))->ToElement();
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
	TiXmlElement* pRoot = m_doc.RootElement();
	TiXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		if (tileName == _strlwr((char*)pMapNode->Attribute("mew")))
		{
			break;
		}
		pMapNode = pMapNode->NextSiblingElement("Map");
	}
	if (NULL != pMapNode)
	{
		pRoot->RemoveChild(pMapNode);
		return WriteMapInfo(pWorld->GetWorldPath());
	}
	return false;
}


void CNPCRouteXml::WriteRoutePoint( TiXmlElement* pNPCRoute, CNPCRouteRes* flyRoute, size_t x )
{
	char strRoutePoint[256];
	sprintf_s(strRoutePoint,256,"RoutePoint%d",x);
	TiXmlElement* pRoutePoint = pNPCRoute->InsertEndChild(TiXmlElement(strRoutePoint))->ToElement();

	pRoutePoint->SetDoubleAttribute("PosX",flyRoute->GetPosX(x));
	pRoutePoint->SetDoubleAttribute("PosY",flyRoute->GetPosY(x));
	pRoutePoint->SetDoubleAttribute("WalkSpeed",flyRoute->GetWalkSpeed(x));
	pRoutePoint->SetDoubleAttribute("WalkLength",flyRoute->GetWalkLength(x));
	pRoutePoint->SetAttribute("StayTime",flyRoute->GetStayTime(x));
	pRoutePoint->SetAttribute("Action",flyRoute->GetStayAction(x));

}