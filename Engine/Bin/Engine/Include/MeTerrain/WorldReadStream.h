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
#ifndef _MAP_WORLD_STREAM_H__
#define _MAP_WORLD_STREAM_H__

class CWorldBuffer;
class CWorldTile;
class CResMgr;
struct f_Handle;
////////////////////////////////////////////////////////////////////////////////
class CWorldReadStream 
{
public:
					CWorldReadStream( CWorldBuffer* worldBuffer );
					~CWorldReadStream();
					
	virtual bool			LoadWorld( const char* worldPath );				
	virtual bool			LoadTile( CWorldTile* tile );				
	bool			LoadWtd( CWorldTile* tile, const char* pathName );
	bool			LoadDoodadRes( CWorldTile* tile, const char* pathName );
	bool			LoadZoneRes(CWorldTile* tile, const char* pathName );
	bool			LoadAlphaRes(CWorldTile* tile, const char* pathName );
	CWorldBuffer*	GetWorldBuffer() const { return m_worldBuffer; }
protected:

	bool			ReadTextureTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadAlphaTable( f_Handle* stream, CResMgr* resMgr );

	bool			ReadShadowTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadLiquidTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadModelTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadMapObjTable( f_Handle* stream, CResMgr* resMgr, flt32* origin );
	bool			ReadDoodadTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadChunkTable( f_Handle* stream, CWorldTile* tile );
	bool			ReadLightMapTable( f_Handle* stream, CWorldTile* tile );

	virtual void	AddDoodadLevel( CWorldChunk* worldChunk, TWTDDoodesRef &doodes );
	virtual void	InitializeLoadLevel( CWorldChunk* worldChunk );
	virtual void	ReadInDoodadData( TDoodadLevelInfo* pLevelInfo, TWTDDoodesRef &doodes, f_Handle* stream, CWorldTile* tile, CWorldChunk* worldChunk );
	bool			ReadZoneTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadLightTable( f_Handle* stream, CResMgr* resMgr );
	bool			ReadFogTable( f_Handle* stream, CResMgr* resMgr );
	void 			ColorChange( COLORREF& niColor );
protected:
	CWorldBuffer*	m_worldBuffer;
	// 	TWMOHead		m_wmohead;
	TWTDHead		m_wifhead;
	typedef void  (*ColorChangeFun)(COLORREF& niColor );
	ColorChangeFun	m_ColorChange;
//	bool			LoadTileHash( LPCTSTR dirName );


};

#endif	// _MAP_WORLD_STREAM_H__
