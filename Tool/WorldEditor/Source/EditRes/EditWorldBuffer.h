/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldBuffer.h
* Create: 	10/06/2006
* Desc:		µØÍ¼Êý¾Ý»º³å
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_EDITWORLDTILEBUFFER_H__
#define _MAP_EDITWORLDTILEBUFFER_H__
#include "MeTerrain/WorldBuffer.h"
#include <list>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
class CWorld;
class CWorldTile;
class CWorldChunk;
class CNdlEnvRes;
class CNdlLightRes;
class CNdlFogRes;
class CResMgr;
class CNdlGlobalResMgr;
class CWorldTile;
class CEditRender;
class CNdlEditWorldPicker;
class CNdlWorldEditor;
class CWorldReadStream;
class CWorldWriteStream;
class TObjectInfo;
////////////////////////////////////////////////////////////////////////////////
class CEditWorldBuffer : public CWorldBuffer
{
	friend class			CToolWorld;
	friend					CEditRender;
	friend class			CNdlDecalRes;
	friend class			CWorldEditDoc;
	friend class			CTextureNavigationWnd;
	friend					CNdlWorldEditor;
	friend					CWorldReadStream;
	friend					CWorldWriteStream;
	friend class			CResMgr;
	friend					CNdlGlobalResMgr;
public:
	CEditWorldBuffer( CWorld* world );
	~CEditWorldBuffer();
		
	virtual bool					Create();

	virtual CWorldTile*				PushTileRes(sInt32 nMapId,  const char* pPathName);
	virtual void ClearTileModify( CWorldTile * tile, uInt32 tileId );

protected:
	virtual void					UpdateLight( CNdlLightRes* lightRes );
	virtual void					UpdateFog( CNdlFogRes* fogRes );
	virtual void					_SetActiveTile(CWorldTile* val);

public:
	virtual bool					SetActiveTile(CWorldTile* val,int nRoleX = -1,int nRoleY = -1) ;
};

#endif	// _MAP_EDITWORLDTILEBUFFER_H__
