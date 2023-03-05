/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlWorldCreater.h
* Date: 	02/05/2007
* Desc:
*
*******************************************************************************/
#ifndef _NDL_NDLWORLDCREATER_H__
#define _NDL_NDLWORLDCREATER_H__


#include <set>

struct TVertOptInfo {
	flt32	height;
	flt32	weight;
	flt32	scale;
	bool	isDelta;
	bool	isModify;
	bool	isAve;
	bool	isInvAve;
};

////////////////////////////////////////////////////////////////////////////////
class CWorld;
class CToolWorld;
class CNdlAlphaRes;
class CNdlMaskRes;
class CNdlTextureRes;
class CResEditMgr;
class CWorldChunk;
class CWorldWriteStream;
class LightMapMeshProcessDlg;
////////////////////////////////////////////////////////////////////////////////
class CNdlWorldEditor/*	: public NiRefObject*/
{
public:
							CNdlWorldEditor();
	virtual					~CNdlWorldEditor();
	
	bool					Create( CWorld* world );

	bool					NewWorld();
	CWorldTile*				NewTile( const char*  pTileFullName, const char* baseTexture, flt32 height,uInt32 row,uInt32 column, flt32 heightMapUnit, const CImage* heightMap, CToolWorld* worlDlg );
	bool					DeleteTile(uInt32 tileId);
	
							// 改变vertex height之后,需要更新Normal 和 显示数据.
	//void					ModifyHeight( const sInt32* vertId, flt32 deltaHeight, flt32 weight, flt32 scale, bool isDelta = true, bool isModify = false, bool isAve = false, bool isInvAve = false );
	bool					UpDownVert( const flt32* origin, flt32 brushSize, flt32 deltaHeight );
	bool					SmoothVert( const flt32* origin, flt32 brushSize, flt32 deltaScale );
	bool					PlaneVert( const flt32* beginPos, const flt32* endPos, flt32 flight );
	bool					EqualVert( const flt32* origin, flt32 brushSize, flt32 height );
	bool					GetVertHeight( const sInt32* vertId, flt32& height );
	bool					GetVertHeight( sInt32 vertIdX, sInt32 vertIdY, flt32& height );
	bool					SetGlVertNormal( const sInt32* vertId, sInt32* normal );
	
	//bool					PaintLayer( flt32* pt2, uInt8* brush, znAppendMode appendMode );
	bool					PaintRoad( flt32* pt2, uInt8* brush, uInt32 brushSize, bool isAddShadow , uInt8 alpha);
	bool					PaintShadow( flt32* pt2, uInt8* brush, uInt32 brushSize, bool isAddShadow , uInt8 alpha);
	bool					PaintTexture( flt32* pt2, uInt8* brush, uInt32 brushSize, const char* textureName, uInt8 alpha, sInt32 paintMode );
	bool					PaintDoodads(const flt32* pt2, sInt32 doodadId, uInt32 brushUnit,  uInt32 brushSize, sInt32 nDensity, uInt32* scale,sInt32 paintMode);
	bool					PaintVertexColor( flt32* pt2, uInt32 brushSize,NiColor& niColor,uInt32 flow, bool isAdd , uInt8 alpha);
	bool					ClearVertexColor( flt32* pt2,  uInt32 brushSize);

	bool					SetChunkEnv( flt32* pt, sInt32 brushSize, sInt32 zoneId );
	bool					SetChunkZone( flt32* pt, sInt32 brushSize, sInt32 zoneId );
	bool					ResetTileTexture( const char* textureName, sInt32 tile );

							// 去除已经删除的模型.主要是针对旧版本Edit遗留下的问题.
	bool					CleanUnusedModel( sInt32 tile );
	bool					DeleteStaticModel(  sInt32 modelId,bool isKeyTrigger );
	bool					ModifyStaticModel(  sInt32 modelId, const flt32* offset, const flt32* rotate, const flt32* scale );
	bool					PutStaticModel( const flt32* pt2, const flt32* offset, const flt32* rotate, const flt32* scale, const char* modelName );
	//added by zilong. 2011-01-14
	bool					PutStaticModel(const flt32* pt, const flt32* offset, const flt32* rotate, const flt32* scale, TObjectInfo *pModel);
	bool					PutStaticModel(const flt32* pt, const flt32* offset, const flt32* rotate, const flt32* scale, sInt32 modelID);

	bool					UpdateShape();
	bool					UpdateTileNormal();
	
	void					Rescale( flt32 scale );
	
	bool					GetVertexList( uInt32 vertId, sInt32 halfSize, std::vector<struct TSelInfo*>* selList );	
	
	void					GetChunkIndexFromPos( sInt32* chunk, flt32* pos );
	bool					GetSelWorld( flt32* pt2, CWorldChunk** worldChunk, CResEditMgr** resMgr );
	bool					GetChunkLayerTextureInfo( CWorldChunk* worldChunk, CResEditMgr* resMgr, CNdlTextureRes** layer0, CNdlTextureRes** layer1, CNdlTextureRes** layer2, CNdlTextureRes** layer3 );
	bool					ReplaceChunkTexture( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId, const char* textureName );
	bool					ReplaceTexture( CResEditMgr* resMgr, sInt32 texId, const char* textureName );
	bool					DelChunkLayer( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId );
	bool					UpChunkLayer( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId );
	bool					DownChunkLayer( CWorldChunk* worldChunk, CResEditMgr* resMgr, sInt32 layerId );


	bool					GenerateLightMap();
	void					ChangeAllShadowColor(short sShadowColor);
	inline bool				IsPointInTriangle(D3DXVECTOR2 &va, D3DXVECTOR2 &vb, D3DXVECTOR2 &vc, D3DXVECTOR2 &vp, float& u, float& v);
	void					BlurLightMapGauss(CNdlAlphaRes* shadowRes);
	void					BlurLightMap(CNdlAlphaRes* shadowRes);
	bool					GenerateMeshLightMap();
	void					SaveLightmapTexture(CWorldTile* pWorldTile, LightMapMeshProcessDlg* dlg);

	//added by zilong. 2011-02-10. --------------------------
	void ProcessChunkBoundaryForShadow(CResEditMgr *pResMgr_, CWorldTile *pTile_, CWorldChunk *pChunk_);
	void ProcessLRNeighbourPixelForShadow(uAlphaBit *pMe_, uAlphaBit *pYou_, bool bFlag_ = true);
	void ProcessUDNeighbourPixelForShadow(uAlphaBit *pMe_, uAlphaBit *pYou_);
	//added by zilong. end. ---------------------------------

protected:
	bool					UpdateNormal( CWorldTile* worldTile );
	bool					UpdateChunkNormal( CWorldChunk* worldChunk );
	bool					GetChunkVertHeight( const sInt32 chunk[2], sInt32 vert[2], flt32& height );
	bool					SetChunkVertNormal( const sInt32 chunk[2], sInt32 vert[2], sInt32* normal );

	bool					FillChunkWithSHeightmap( CWorldChunk* chunk, flt32 height, flt32 heightMapUnit, sInt32 textureId, const CImage* heightMap, const sInt32* baseCood );
	//bool					FillChunkWithLHeightmap( CWorldChunk* chunk, flt32 height, flt32 heightMapUnit, sInt32 textureId, const CImage* heightMap );
	bool					FillChunkNoHeightmap( CWorldChunk* chunk, flt32 height, sInt32 textureId );
	bool					FillLayerData( CNdlAlphaRes* alphaRes, uInt32* originDest, uInt8* brush, uInt32* originSrc, uInt32* sizeSrc, uInt32 brushSize, sInt32 layerId, sInt32 blendMode, uInt8 alpha );
	bool					FillShadowData( CNdlAlphaRes* shadowRes, uInt32* originDest, uInt8* brush, uInt32* originSrc, uInt32* sizeSrc, uInt32 brushSize, bool isAddShadow , uInt8 alpha);
	bool					FillRoadData( CNdlAlphaRes* shadowRes, uInt32* originDest, uInt8* brush, uInt32* originSrc, uInt32* sizeSrc, uInt32 brushSize, bool isAddShadow , uInt8 alpha);
	bool					FindTextureLayer( CWorldChunk* worldChunk, sInt32 textureId, sInt32& texLayerId );
	bool					FillDoodadData( TDoodadLevelInfo* pLevelInfo,uInt32* originDest, uInt32* originSrc, uInt32* sizeSrc,sInt32 nDensity,uInt32* scale, sInt32 paintMode );

	bool					CheckChunk( sInt32* chunk );
	bool					RescaleChunkHeight( CWorldChunk* chunk, flt32 scale );
	bool					AddVertDeltaHeight( flt32& refHeight,  const sInt32* chunk, const sInt32* vert, flt32 deltaHeight );
	bool					SetVertHeight( const sInt32* chunk, const sInt32* vert, flt32 height );

	bool					AddVertColor( NiColor& retColor,  const sInt32* chunk, const sInt32* vert,uInt32 flow, NiColor& destColor ,bool isAdd, uInt8 alpha);

	NiColor&				CalColor( bool isAdd, NiColor& myColor, float fCoaf, NiColor& destColor );
	bool					SetVertColor(  const sInt32* chunk, const sInt32* vert, NiColor& destColor , uInt8 alpha);

	bool					CheckVertex( const sInt32* vertId );
	void					SetChunkMeshDirty( CWorldChunk* worldChunk );
	
	bool					CalcOutVertNormal( sInt32* vertId );					
	bool					CalcInVertNormal( sInt32* vertId );		


	enum EChangeModelStatus
	{
		EMS_ADD		= 0,
		EMS_DELETE,
	};

	//bool					GetPosInfoByModelWorldBound( NiBound WorldBound, sInt32 tile[4][2], sInt32 chunk[4][2] );	//计算World Bound边界所在tile和chunk
	bool					GetPosInfoByModelWorldBound( Vector2 vMin, Vector2 vMax, sInt32 tile[4][2], sInt32 chunk[4][2] );	//计算World Bound边界所在tile和chunk
	void					ModifyModelRefInTile( CWorldTile* tile, const sInt32* beginChunk, const sInt32* endChunk, sInt32 modelId, int change );	//把model加入tile
	void					ModifyModelRefInOneChunk( CWorldTile* tile, const sInt32* chunk, sInt32 modelId, int change );	//把model加入chunk
	void					CalculateModelWorldBound(TObjectInfo* pObjInfo, Vector2& vMin, Vector2& vMax);
protected:
	CWorld*					m_world;
	bool					GetActiveTileAndMgr(CWorldTile*& worldTile,CResEditMgr*& resMgr);
	
	std::set<CWorldChunk*>	m_changeMeshChunkList;	// 需要更新模型的chunk
	std::set<CWorldChunk*>	m_changeMatlChunkList;	// 需要更新材质的chunk
	std::set<CWorldTile*>	m_changeTileList;
	/*
	struct for lightmap
	*/
	typedef struct _tagLightMapPixel
	{
		unsigned char ucBlurColor;
		unsigned char ucColor;
	}LightMapPixel;

	std::map<uAlphaBit*, LightMapPixel> m_mapLightMapPixel;
};
enum znLayerBlendMode {
	znLBM_Add = 0,
	znLBM_InvAdd,
	znLBM_SetUp,
	znLBM_SetDown,
// 	znLBM_InvDelta,
	znLBM_Shadow,
	znLBM_VertexCorlor,
	znLBM_InvVertexCorlor,
	znLBM_Road,

};

#include "NdlWorldEditor.inl"


#endif	// _NDL_NDLWORLDCREATER_H__


