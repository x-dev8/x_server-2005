/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldBuffer.h
* Create: 	10/06/2006
* Desc:		地图数据缓冲
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _MAP_WORLDTILEBUFFER_H__
#define _MAP_WORLDTILEBUFFER_H__

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
enum EShaderType {
	GameTerrainRender1 = 0
	, GameTerrainRender2
	, GameTerrainRender3
	, GameTerrainRender4 
	, LOD1_Terrain
	, LOD2_Terrain
	, GameTerrainSpecialRender1
	, GameTerrainSpecialRender2
	, GameTerrainSpecialRender3
	, GameTerrainSpecialRender4 
	, LOD1_Terrain_Special
	,SHADER_NUM
};

struct FogProperty
{
	bool		bShowFog;
	D3DXCOLOR	kFogColor;
	float		fFogNear;
	float		fFogFar;
	float		fFarPlane;	// 记录当前雾对应的相机剪裁距离
};
////////////////////////////////////////////////////////////////////////////////
class CWorldBuffer
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
							CWorldBuffer( CWorld* world );
							~CWorldBuffer();
		
	virtual bool			Create();
	void					Destroy();
	void					Reset();

	void					OnDeviceLost();
	void					OnDeviceReset( bool bBeforeReset);
	void					Update( flt32 totalTime, flt32 deltaTime );

	bool					LoadWorld();


	bool					GetVertexHeight( const sInt32* startGlUnit, const sInt32* overGlUnit, flt32* heightOut, flt32* heightIn );

	// load线程是否处于loading状态
	bool					IsLoading();

	bool					IsTileChange();
	void					SetTileChange( bool isChange )			{ m_isTileChange = isChange; };

	bool					InitEnv(CWorldTile* tile);

	bool					IsEnvChange();
	bool					IsLightChange();
	bool					IsFogChange();

	void					SetEnvChange( bool isChange )			{ m_isZoneChange = isChange; };
	void					SetLightChange( bool isChange )			{ m_isLightChange = isChange; };
	void					SetFogChange( bool isChange )			{ m_isFogChange = isChange; };

	CNdlEnvRes*				GetEnvRes();
	CNdlLightRes*			GetLightRes();
	CNdlFogRes*				GetFogRes();

	void					SetLightAmbientColor( const NiColor& ambient );
	void					SetLightDiffuseColor( const NiColor& diffuse );
	void					SetLightSpecularColor( const NiColor& specular );
	void					SetSunLessColor( const NiColor& specular );
	void					SetLightDir( const Vector& dir );
	void					UpdateTileEnv(CWorldTile *tile, sInt32 envId);


	CNdlGlobalResMgr*		GetGlobalResMgr() { return m_globalResMgr; };
	void					OnChunkChange(int newchunkX, int newchunkY);
    void                    BackupFarChunk(float farChunk) { m_farChunkBackup = farChunk; }


	static	void			FinishUnLoadingTile( CWorldTile* cacheTile );

	CResMgr*				GetResMgr(  );
	CWorld*					GetWorld() const { return m_world; }

// 	void					SetMultiThread(bool val) { m_bMultiThread = val; }


protected:
	void					UpdateEnv( CNdlEnvRes* envRes );
	bool					_LoadTileRes( CWorldTile* tile );
	bool					UnloadTileRes( uInt32 tileId );

	virtual void ClearTileModify( CWorldTile * tile, uInt32 tileId );
	//bool					MoveCacheMap();
	//void					MoveActiveMap();


	CWorldChunk*			GetChunk(  sInt32 chunkX, sInt32 chunkY );
	
	
	// 初始化多线程
	bool					CreateMultiThread();
	void					DestroyMultiThread();

protected:
	virtual void					UpdateLight( CNdlLightRes* lightRes );
	virtual void					UpdateFog( CNdlFogRes* fogRes );

protected:

	CWorld*					m_world;
	Vector2					m_curChunk;
	bool					m_isTileChange;

	//swVec2f					m_activePos;

	CWorldReadStream*		m_readStream;

	CNdlGlobalResMgr*		m_globalResMgr;

	// 多线程：
// 	bool					m_bMultiThread;
// 	CRITICAL_SECTION		m_hLock;

	bool					m_isZoneChange;
	bool					m_isLightChange;
	bool					m_isFogChange;
	CNdlEnvRes*				m_envRes;
	CNdlLightRes*			m_lightRes;
	CNdlFogRes*				m_fogRes;

	float					m_farChunkBackup;	// 渲染人物时把m_farChunk备份，然后设为默认值

public:
	virtual CWorldTile*				PushTileRes(sInt32 nMapId, const char* pPathName);

	CWorldTile*				LoadTileRes( CWorldTile* val,int nRoleX ,int nRoleY);

	void					AddTilePRI( sInt32 tileId );
// 	sInt32					GetTileHashId(const char* pPathName);
 	CWorldTile*				GetTileFromPath(const char* pPathName);
	CWorldTile*				GetTileFromTileName(const char* pTileName,short stCountry = -1);
	CWorldTile*				GetTile(sInt32 hashId);
	CWorldTile*				GetTileFromMapId(int nMapId);
	void					SetMaxTileCacheNum(size_t val) { m_MaxTileCacheNum = val; }

	void					ReomveTileRes(sInt32 hashId);
	CWorldTile*				GetActiveTile() const { return m_activeTile; }
	virtual bool					SetActiveTile(CWorldTile* val,int nRoleX = -1,int nRoleY = -1) ;
	std::list<sInt32>&		GetTilePRIList()  { return m_tilePRI; }
	std::map<sInt32,CWorldTile*>& GetTileMapHash()  { return m_tileMapHash; }
	std::vector<CWorldTile*>&		GetMapSortbyLevelArr()  { return m_mapSortbyLevelID; }
	void					SortMapByLevel();
protected:
	virtual void					_SetActiveTile(CWorldTile* val);
	std::map<sInt32,CWorldTile*> m_tileMapHash;
	std::list<sInt32>		m_tilePRI;							//这里记录hashpos
	size_t					m_MaxTileCacheNum;
	CWorldTile*				m_activeTile;
	std::vector<CWorldTile*>		m_mapSortbyLevelID;
};

#endif	// _MAP_WORLDTILEBUFFER_H__
