/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SoundPointXml.cpp
* Create: 	10/29/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "MeTerrain/stdafx.h"
// #include "resource.h"
#include "MeTerrain/SoundPointXml.h"
#include "tstring.h"

////////////////////////////////////////////////////////////////////////////////
static sInt32	nMapconfigXmlVersion = 100;
////////////////////////////////////////////////////////////////////////////////
CSoundPointXml::CSoundPointXml()
{
}

CSoundPointXml::~CSoundPointXml()
{
}




// bool CSoundPointXml::RefreshTileSoundPoint( sInt32 tileId )
// {
// 	CWorld* pWorld = SwGlobal::GetWorld();
// 	if (!pWorld->HasName())
// 	{
// 		return false;
// 	}
// 	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
// 	if( NULL == tile )
// 		return false;
// 
// 	std::string tileName = _strlwr(tile->GetPathName());
// 	MeXmlElement* pRoot = m_doc.RootElement();
// 	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
// 	while (pMapNode)
// 	{
// 		if (tileName == _strlwr((char*)pMapNode->Attribute("mew")))
// 		{
// 			break;
// 		}
// 		pMapNode = pMapNode->NextSiblingElement("Map");
// 	}
// 
// 
// 	if (NULL == pMapNode)
// 	{
// 		pMapNode = AddMapElement(tile);
// 	}
// 
//     std::wstring str = Common::_tstring::toWideString(tile->GetTileName());
//     pMapNode->SetAttribute("MapName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
// 
// 	pMapNode->Clear();
// 	CResMgr* pResMgr = tile->GetCResMgr();
// 	for (size_t i = 0; i < pResMgr->GetSoundPointCount(); ++i)
// 	{
// 		CSoundPointRes* soundPoint = pResMgr->SoundPoint(i);
// 		{
// 			MeXmlElement* pSoundPoint = pMapNode->InsertEndChild(MeXmlElement("SoundPoint"))->ToElement();
// 			std::wstring str = Common::_tstring::toWideString(soundPoint->GetName());
// 			pSoundPoint->SetAttribute("SoundPointName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
// 			str = Common::_tstring::toWideString(soundPoint->GetMuiscPath());
// 			pSoundPoint->SetAttribute("MusicPath", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
// 			pSoundPoint->SetDoubleAttribute("PosX",soundPoint->GetPosX());
// 			pSoundPoint->SetDoubleAttribute("PosY",soundPoint->GetPosY());
// 			pSoundPoint->SetDoubleAttribute("PosZ",soundPoint->GetPosZ());
// 			pSoundPoint->SetDoubleAttribute("MinDistance",soundPoint->GetMinDistance());
// 			pSoundPoint->SetDoubleAttribute("MaxDistance",soundPoint->GetMaxDistance());
// 		}
// 	}
// 
// 	return WriteMapInfo(pWorld->GetWorldPath());
// }

bool CSoundPointXml::RefreshTileSoundPoint( CWorldTile* tile )
{
// 	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
// 	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile( tileId);
	if( NULL == tile )
		return false;

	std::string tileName = _strlwr(tile->GetPathName());
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

	std::wstring str = Common::_tstring::toWideString(tile->GetTileName());
	pMapNode->SetAttribute("MapName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

 	pMapNode->Clear();
	CResMgr* pResMgr = tile->GetCResMgr();
	for (size_t i = 0; i < pResMgr->GetSoundPointCount(); ++i)
	{
		CSoundPointRes* soundPoint = pResMgr->SoundPoint(i);
		{
			MeXmlElement* pSoundPoint = pMapNode->InsertEndChild(("SoundPoint"))->ToElement();
			std::wstring str = Common::_tstring::toWideString(soundPoint->GetName());
			pSoundPoint->SetAttribute("SoundPointName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
			str = Common::_tstring::toWideString(soundPoint->GetMuiscPath());
			pSoundPoint->SetAttribute("MusicPath", Common::_tstring::wcstoUTF8(str.c_str()).c_str());
			pSoundPoint->SetDoubleAttribute("PosX",soundPoint->GetPosX());
			pSoundPoint->SetDoubleAttribute("PosY",soundPoint->GetPosY());
			pSoundPoint->SetDoubleAttribute("PosZ",soundPoint->GetPosZ());
			pSoundPoint->SetDoubleAttribute("MinDistance",soundPoint->GetMinDistance());
			pSoundPoint->SetDoubleAttribute("MaxDistance",soundPoint->GetMaxDistance());
		}
	}

	return WriteMapInfo(SwGlobal::GetWorld()->GetWorldPath());
// 	return RefreshTileSoundPoint(pBuffer->GetTileHashId(tile->GetPathName()));
}

void CSoundPointXml::VerifyRouteFly( sInt32 nMapId,sInt32 targetId )
{
	std::string  targetTileName;
	CWorld* pWorld = SwGlobal::GetWorld();
// 	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	if (-1 != nMapId)
	{
		std::map<sInt32,CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
		for(std::map<sInt32,CWorldTile*>::iterator iter = tileHash.begin(); iter != tileHash.end();++iter)
		{
			CWorldTile* pWorldTile =iter->second;
			if (NULL == pWorldTile)
			{
				continue;
			}
			if (nMapId == pWorldTile->GetMapId())
			{
				targetTileName = pWorldTile->GetPathName();
			}
		}
	}
	if (targetTileName.length() == 0)
	{
		Trace("error tile map id %d in  SoundPoint.config !\n",nMapId);
	}
	else
	{
// 		bool bValid = false;
// 		CWorldTile* targetTile = pBuffer->GetTile(targetTileName);
// 		CResMgr* targetMgr = targetTile->GetCResMgr();
// 		for (size_t i = 0; i < targetMgr->GetSoundPointCount(); ++i)
// 		{
// 			CSoundPointResBase* res = targetMgr->SoundPoint(i);
// 			if ((!res->IsSoundPoint()) && res->GetNtargetID() == targetId)
// 			{
// 				bValid = true;
// 				break;
// 			}
// 		}
// 		if (!bValid)
// 		{
// 			Trace("error tile map flyRoute id %d of tile %s in SoundPoint.config !\n",targetId,targetTileName);
// 		}
	}

}


bool CSoundPointXml::LoadSoundPoint(bool bInitial)
{
	CWorld* pWorld = SwGlobal::GetWorld();
	if (!pWorld->HasName())
	{
		return false;
	}
	std::string ConfigName = pWorld->GetWorldPath();
	ConfigName += '\\';
	ConfigName += "SoundPoint.config";
// 	WIN32_FIND_DATAA data;
// 	HANDLE hFind = FindFirstFileA(ConfigName.c_str(),&data);
// 	bool bFind = (hFind != INVALID_HANDLE_VALUE);
// 	if (bFind)
	{
		if (!m_doc.LoadFile(ConfigName.c_str()))
		{
			if (bInitial)
			{
				InitializeSoundPoint();
			}
			Trace("error SoundPoint.config in world %s!\n",ConfigName);
			return false;
		}
	}
	CWorldBuffer* pBuffer = pWorld->GetWorldBuffer();
	MeXmlElement* pRoot = m_doc.FirstChildElement("SoundPoint")->ToElement();

	MeXmlElement* pMapNode = pRoot->FirstChildElement( "Map");
	while (pMapNode)
	{
		const char* tileName = pMapNode->Attribute("mew");
		sInt32 mapId = 0;
		pMapNode->QueryIntAttribute("id",&mapId);
		CWorldTile* tile = pBuffer->GetTile(mapId);
		if (NULL == tile)
		{
			Trace("error tile name %s in  SoundPoint.config !\n",tileName);
			pMapNode = pMapNode->NextSiblingElement("Map");
			continue;
		}

		CResMgr* pResMgr = tile->GetCResMgr();
		pResMgr->CleanSoundPoint();
		MeXmlElement* pSoundPoint = pMapNode->FirstChildElement( "SoundPoint");
		while (pSoundPoint)
		{
// 			int routeIndex;
// 			pSoundPoint->QueryIntAttribute("SoundPointIndex",&routeIndex);
			std::wstring str = Common::_tstring::UTF8towcs(pSoundPoint->Attribute("SoundPointName"));
			CSoundPointRes* pRes = (CSoundPointRes*)pResMgr->PushSoundPoint(Common::_tstring::toNarrowString(str.c_str()).c_str());
			str = Common::_tstring::UTF8towcs(pSoundPoint->Attribute("MusicPath"));
			pRes->SetMuiscPath(Common::_tstring::toNarrowString(str.c_str()).c_str());
// 			Assert(routeIndex == pRes->GetId());
			float posX;float posY;float posZ;
			pSoundPoint->QueryFloatAttribute("PosX",&posX);
			pSoundPoint->QueryFloatAttribute("PosY",&posY);
			pSoundPoint->QueryFloatAttribute("PosZ",&posZ);
			pRes->SetPosX(posX);
			pRes->SetPosY(posY);
			pRes->SetPosZ(posZ);
			float fminDistance;
			pSoundPoint->QueryFloatAttribute("MinDistance",&fminDistance);
			pRes->SetMinDistance(fminDistance);
			float fmaxDistance;
			pSoundPoint->QueryFloatAttribute("MaxDistance",&fmaxDistance);
			pRes->SetMaxDistance(fmaxDistance);
			pSoundPoint = pSoundPoint->NextSiblingElement( "SoundPoint");
		}


		pMapNode = pMapNode->NextSiblingElement("Map");
	}
	return true;
}

void CSoundPointXml::InitializeSoundPoint()
{
	m_doc.Clear();
	m_doc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
// 	m_doc.InsertEndChild(MeXmlComment("Notice: This xml is generated automatically. So don't modify the xml format or change any key or any string value."));
// 	m_doc.InsertEndChild(MeXmlComment("It is recommend always to generate the file by world editor. However, you can modify some integer or float values for convenience."));
	MeXmlElement* pRoot = m_doc.InsertEndChild(("SoundPoint"))->ToElement();
	pRoot->SetAttribute("ConfigVersion",nMapconfigXmlVersion);
	CWorld* pWorld = SwGlobal::GetWorld();
	std::map<sInt32,CWorldTile*>& tileHash = pWorld->GetWorldBuffer()->GetTileMapHash();
	sInt32 mapId = 0;
	for(std::map<sInt32,CWorldTile*>::iterator iter = tileHash.begin(); iter != tileHash.end();++iter)
	{
		CWorldTile* pWorldTile =iter->second;
		if (pWorldTile == NULL)
		{
			continue;
		}
		AddMapElement(pWorldTile);
		++mapId;
	}
	WriteMapInfo(pWorld->GetWorldPath());

}

MeXmlElement* CSoundPointXml::AddMapElement( CWorldTile* tile)
{
	MeXmlElement* pRoot = m_doc.FirstChildElement("SoundPoint")->ToElement();
	MeXmlElement* pMapNode = pRoot->InsertEndChild(("Map"))->ToElement();
	pMapNode->SetAttribute("id",tile->GetMapId());
	pMapNode->SetAttribute("mew",tile->GetPathName());


	std::wstring str = Common::_tstring::toWideString(tile->GetTileName());
	pMapNode->SetAttribute("MapName", Common::_tstring::wcstoUTF8(str.c_str()).c_str());

	return pMapNode;
}
bool CSoundPointXml::WriteMapInfo(const char* worldPath)
{
	std::string lpszPathName = worldPath;
	lpszPathName += '\\';
	lpszPathName += "SoundPoint.config";
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFile(lpszPathName.c_str(),&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		DWORD dwAttrs = GetFileAttributes( lpszPathName.c_str() );
		if ( dwAttrs!=INVALID_FILE_ATTRIBUTES )
		{
			if ( dwAttrs & FILE_ATTRIBUTE_READONLY ) 
			{ 
				char prompt[2*MAX_PATH];
				sprintf_s(prompt, MAX_PATH*2, "文件%s只读，是否覆盖？",lpszPathName.c_str());
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

bool CSoundPointXml::DeleteTileSoundPoint( sInt32 tileId )
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



