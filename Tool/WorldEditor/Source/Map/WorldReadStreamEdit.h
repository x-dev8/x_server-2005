/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldReadStream.h
* Create: 	10/06/2006
* Desc:		µÿÕº∂¡»°¿‡
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_WORLD_READ_STREAM_EDIT_H__
#define _MAP_WORLD_READ_STREAM_EDIT_H__
#include "MeTerrain/WorldReadStream.h"
class CWorldBuffer;
class CWorldTile;
class CResEditMgr;
////////////////////////////////////////////////////////////////////////////////
class CWorldReadStreamEdit : public CWorldReadStream
{
public:
					CWorldReadStreamEdit( CWorldBuffer* worldBuffer );
					~CWorldReadStreamEdit();
					
	virtual bool			LoadWorld( const char* worldPath );				
	virtual bool			LoadTile( CWorldTile* tile );				
	bool			LoadRoadRes( CWorldTile* tile, const char* pathName );
	bool			LoadMonsterData( CWorldTile* tile, const char* pathName );
	bool			LoadLightmapColorData( const char* pathName );
	bool			LoadStaticLights( const char* pathName );
protected:

	bool			ReadRoadTable( FILE* stream, CResEditMgr* resMgr );
    bool            LoadNpc(CWorldTile* pTile);
	
protected:
//	bool			LoadTileHash( LPCTSTR dirName );
	static 	void	LoadTileHash( LPCTSTR strPath,void* point );


	virtual void ReadInDoodadData( TDoodadLevelInfo* pLevelInfo, TWTDDoodesRef &doodes, FILE* stream, CWorldTile* tile, CWorldChunk* worldChunk );

	virtual void InitializeLoadLevel( CWorldChunk* worldChunk );
	virtual void AddDoodadLevel( CWorldChunk* worldChunk, TWTDDoodesRef &doodes );
	static  void ColorChange( COLORREF& niColor );
};

#endif	// _MAP_WORLD_READ_STREAM_EDIT_H__
