/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	MapConfigXml.h
* Create: 	11/07/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TRANSPORT_GENERATE_H__
#define __TRANSPORT_GENERATE_H__
//#include "atlpath.h"

class CxImage;
class CToolWorld;
struct THeightResult;
#include "MapConfig.h"
////////////////////////////////////////////////////////////////////////////////
class CMapConfigXml : public Singleton<CMapConfigXml>
{
public:	
					CMapConfigXml();
	virtual				~CMapConfigXml();

	bool			LoadMapConfig();
	bool			LoadMapConfig_Old();
		
	bool			WriteMapInfo(const char *szWorldPath, const char *szMapFolder = NULL, int tile_id = -1);
	
	bool			RefreshTileMapInfo(CWorldTile* tile);
	bool			RefreshTileMapInfo(sInt32 tileId);
	bool			DeleteTileMapInfor(sInt32 tileId);

	void			AddPFWeight(CWorldTile* tile,sInt32 targetId,sInt32 transportId,sInt32 weight);
	void			InitializeMapConfig();
protected:

	MeXmlElement*	AddMapElement(CWorldTile*  tile, sInt32 mapid  );

	void			VerifyTransport(sInt32 nMapId,sInt32 targetId);

	MeXmlDocument	m_doc;


protected:
	bool			WorldTileToMapData(CWorldTile* pTitle, MapConfig::MapData* pMapData);
	bool			MapDataTpWorldTile(MapConfig::MapData* pMapData, CWorldTile* pTitle);
};








#endif //__TRANSPORT_GENERATE_H__