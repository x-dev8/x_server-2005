/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldChunk.h
* Create: 	10/06/2006
* Desc:		地图数据Chunk
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _WORLD_CHUNK_H__
#define _WORLD_CHUNK_H__
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <list>
// #include "Scene/terrainBlend.h"
#include "Me3d/Bsp.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "MeTerrain/SwDebug.h"

////////////////////////////////////////////////////////////////////////////////
enum ChunckTextureLayer
{
	TextureLayer0	= 0,
	TextureLayer1,
	TextureLayer2,
	TextureLayer3,
	TextureLayerFlight
};	

struct TChunkVertex : public MeCommonAllocObj<TChunkVertex>
{
	flt32	height;
	sInt8	normal[3];
	COLORREF niColor;
	TChunkVertex()
		:niColor(0xFFFFFFFF)
	{
		normal[0] = 0;
		normal[1] = 0;
		normal[2] = 127;
	}
};

struct FTerrainVertexSpecial
{
	enum
	{
		eFVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX5
	};
	struct VertexUV 
	{
		float		u, v;
	};
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	DWORD		color;
	VertexUV	uv[4];
	VertexUV	uvShadow;
};

struct TChunkLOD2Vertex {
	D3DXVECTOR3 p;
};

class CWorldChunk;
class MexAnimCtrl;
struct ChunkIntersection{
	float t;
	float u;   
	float v;
	D3DXVECTOR3 p;
	D3DXVECTOR3 normal;
	CWorldChunk* pChunk;

};

// struct TDoodadInfo {
// //	sInt32	transType;	// -1, 0, 1
// 	flt32	pos[3];	
// 	flt32	scale;
// //	flt32	rotAroundZ;	// rad.
// };

struct TDoodadInfo : public MeCommonAllocObj<TDoodadInfo>
{
	uInt8							m_nScale;
	//0就是该点没有，1-255除以100就是scale
};

struct TDoodadInfoForEdit : public TDoodadInfo
{
	uInt8							m_nDensity;
	//此点出现的几率0-100有效
};
class CResMgr;
class CEditRender;
class CWorldTile;
class CWorldBuffer;
class CNdlEditWorldPicker;
class CNdlWorldEditor;
class CWorldReadStream;
class CWorldWriteStream;
class CToolLiquidDlg;
class CWorldChunk;
struct TDoodadLevelInfo : public MeCommonAllocObj<TDoodadLevelInfo>
{
	sInt32							mdoodadId;
	void					Render(){ GetInstanceMan()->Render();}
	bool					BeginRender(int nIndex,DWORD dwFlag){ return GetInstanceMan()->BeginMyRender(nIndex,dwFlag);}
	void					DoRender(int nIndex){ GetInstanceMan()->DoMyRender(nIndex);}
	void					RefreshDoodadInstance( CResMgr*  presMgr, CWorldChunk* worldChunk,CWorldTile* tile = NULL );

	void					ReleaseDoodadInstance();
// 	MexAnimCtrl*			m_pMesh;
	MexInstanceMan*			GetInstanceMan(){return &m_InstanceMan;}
	MexInstanceMan			m_InstanceMan;
	uInt32					mulevelUnit;
	TDoodadInfo*			GetDoodadMap()  {return m_pDoodadMap;}
	TDoodadInfo&			GetDoodad(int index);
	bool					m_bEdit;
	TDoodadLevelInfo(uInt32 ulevelUnit,bool isEdit = false);
	~TDoodadLevelInfo();
protected:
	TDoodadLevelInfo();
	TDoodadInfo*			m_pDoodadMap;
		
};

struct TTextureInfo {
	enum {
		SCALECOAF = 10,
		MAXOFFSET = 180,
		LeftAlign,
		DownAlign
	};
	uInt8							m_nX;
	//0-180除以MAXOFFSET就是x方向偏差
	uInt8							m_nY;
	//0-180除以MAXOFFSET就是y方向偏差
	uInt8							m_ScaleX;
	//0-255除以10就是x方向放大的倍数
	uInt8							m_ScaleY;
	//0-255除以10就是y方向放大的倍数
	flt32							m_angle;
	bool							IsAlign()
	{
		return m_nX > MAXOFFSET;
	}
	bool							IsLeftAlign()
	{
		return m_nX == LeftAlign;
	}
	bool							IsDownAlign()
	{
		return m_nX == DownAlign;
	}
	void							Reset()
	{
		m_nX = (0),m_nY = (0),m_ScaleX = (SCALECOAF),m_ScaleY = (SCALECOAF),m_angle = (0.f);
	}
	TTextureInfo()
		
	{Reset();}
};
////////////////////////////////////////////////////////////////////////////////
class CWorldChunk : public MeCommonAllocObj<CWorldChunk>
{
	friend class		CToolEnv;
	friend class		CNdlDecalRes;
	friend class		CWorldEditView;
	friend class		CTextureNavigationWnd;
	friend				CResMgr;
	friend				CEditRender;
	friend				CWorldTile;
	friend				CWorldBuffer;
	friend				CNdlWorldEditor;
	friend				CWorldReadStream;
	friend				CWorldWriteStream;
	friend				CToolLiquidDlg;
	friend	class		CResEditMgr;
	friend class		CWorldReadStreamEdit;
public:
						CWorldChunk( CWorldTile* tile );
						~CWorldChunk();
public://加载等级
	enum eChunkLoadLevel
	{
		eCreate = 0,
		eInitialize,
		eTerrainLODLoaded,
		eTerrainLoaded,
		eModelLoaded,
		eDoodadLoaded,
		eTotalChunkLoadLevel
	};
	enum eChunkDataInUsing
	{
		eModel							= 0x1,
		eTerrain						= 0x2,
		eTerrainLOD						= 0x4,
		eDoodad							= 0x8,
	};
	int GetLoadLevel() const { return m_eLoadLevel; }
	void SetLoadLevel(int val);
	bool IsDataInUsing(int val) ;
	void MarkDataUsing(int val,bool bInUsing);
	void				LockFlag(bool bLock);
	bool				IsLockFlag() ;
protected:
	void				LoadStaticModelList();
	void				UnloadStaticModelList();
	void				LoadDoodadList();
	void				UnloadDoodadList();
	void				LoadTexture();
	void				UnloadTexture();
	void				_SetLoadLevel(int val);
	volatile eChunkLoadLevel		m_eLoadLevel;
	volatile int					m_usingMark;
	CRITICAL_SECTION				m_usingMarkCS;
// 	CRITICAL_SECTION				m_DataLoadingCS[4];
public:
	void				Create( sInt32 chunkX, sInt32 chunkY );	
	void				CloneFrom(CWorldChunk* pSrcChunk);

	void				Reset(  CWorldTile* tile );
	bool				IsLoad()	{ return m_isLoad; };
	
	bool				GetMinMaxHeight( sInt32 unitX, sInt32 unitY, flt32& minHeight, flt32& maxHeight );
	bool				GetUnitVertex( sInt32 unitX, sInt32 unitY, TVertInfo* outVertInfo );
	
	void				CalcHeight();
	bool				PushModel( sInt32 modelId );

	int					AddDoodadLevel( uInt32 ulevelUnit,bool isEdit = false );
	TDoodadLevelInfo*	GetDoodadLevel(sInt32 nIndex);

	//only for worldEdit
	TDoodadLevelInfo*	GetDoodadLevel(uInt32 mdoodadId, uInt32 ulevelUnit,CResMgr*	pResMgr);
	sInt32				GetDoodadLevelCount();
	bool				DeleteDoodadLevel(sInt32 nIndex);

	flt32*				Origin()  { return m_origin; }
	TChunkVertex*		GetVertexOut() const { return (TChunkVertex*)m_vertexOut; }
	TChunkVertex*		GetVertexIn() const { return (TChunkVertex*)m_vertexIn; }
	flt32*				GetHeight() { return m_height; }

	sInt32				GetLiquidId() { return m_liquidId; }
	flt32				GetLiquidHeight() { return m_liquidHeight; }
	flt32				GetLiquidAlphaCoaf() { return m_liquidAlphaCoaf; }
	COLORREF			GetLiquidColor() { return m_liquidColor; }

	flt32*				GetTotalHeight() {return m_fTotalHeight;}
	sInt32				GetShape() {return m_shape;}
	sInt32				GetLayerCount() { return m_layerCount; }
	std::vector<sInt32>& GetStaticModelList() { return m_staticModelList; }

	CWorldTile*			GetParentTile() const { return m_parentTile; }
	std::vector<TDoodadLevelInfo*>& GetDoodadList() { return m_doodadList; }


	int					GetLODLevel() const { return m_lodLevel; }
	void				SetLODLevel(int val);
	int					GetTextureLODLevel() const { return m_textureLOD; }
	void				SetTextureLODLevel(int val){m_textureLOD = val;}
	bool				IsCulled() const { return m_culled; }
	void				SetCulled(bool val) { m_culled = val; }
	int					IsExistSpecialLayer();
	int					IsExistSpecialTexture(sInt32 textureId);
	TTextureInfo&		GetTexInfo(int index)  { return m_texInfo[index]; }
	void				Render( int* pVertexCount=NULL, int* pFaceCount=NULL );	// 返回渲染的顶点数和三角形数
	// added, jiayi, [2009.4.21]
	void				RenderShadow( int* pVertexCount=NULL, int* pFaceCount=NULL );	// 返回渲染的顶点数和三角形数
	void				RenderLod2( int* pVertexCount=NULL, int* pFaceCount=NULL );	// 返回渲染的顶点数和三角形数
	void				RenderLiquid( int* pVertexCount=NULL, int* pFaceCount=NULL );
	void				RenderLiquid_High(int* pVertexCount = 0, int* pFaceCount = 0);

	void				RenderWireFrame(bool isLiquid  = false);
	void				CalculateChunkTotalHeight( CResMgr *resMgr, flt32* fHeight );	// 计算chunk所有物件的Z轴最大最小值
	void				CalculateChunkTotalHeightForEditor( CResMgr *resMgr, flt32* fHeight );	// 计算chunk所有物件的Z轴最大最小值
	sInt32				GetTexture(sInt32 nLevel) const {Assert(nLevel < TextureLayerFlight && nLevel >= 0); return m_texture[nLevel]; }
	void				GetCameraTerrainIntersection( D3DXVECTOR3* pvFrom, D3DXVECTOR3* pvDir, std::vector<ChunkIntersection>* pvectorIntersection);
	sInt32				GetRoad() const { return m_road; }
	bool				IsInShadow( sInt32 nX, sInt32 nY );
	BspTree::SIntersect*				GetSimpleCollision(Vector& vPos,bool bNearest = false,bool bDown = true);
	BspTree::SIntersect*				GetSimpleFloor(Vector& vPos,bool bNearest = false,bool bDown = true,bool bSupper = false,BOOL bNormal = FALSE);
	BspTree::SIntersect* GetNearestIntersectCmpZ(Vector& vPos, Vector& vDir, BOOL bNormal, float fCurrZ  );
	sInt32				GetZoneId() const { return m_zoneId; }
	void				SetZoneId(sInt32 val) { m_zoneId = val; }
	sInt32				GetMaskId() const { return m_maskId; }
	sInt32				GetEnvId() const { return m_envId; }
	sInt32				GetChunkX() const { return m_chunk[0]; }
	sInt32				GetChunkY() const { return m_chunk[1]; }
protected:
	void				SetPos( sInt32 chunkX, sInt32 chunkY );

	bool				m_isLoad;
	CWorldTile*			m_parentTile;

	sInt32				m_chunk[2];
						// 中心点在 World 中的位置
	flt32				m_origin[2];	
	flt32				m_height[2];	// m_height[0]=minHeight, m_height[1]=maxHeight
	flt32				m_fTotalHeight[2];	// chunk里地表、水面和模型的最大最小Z值；m_fChunkModelHeight[0]最小Z值，m_fChunkModelHeight[1]最大Z值

	sInt32				m_layerCount;
	sInt32				m_shape;
	sInt32				m_texture[TextureLayerFlight];
	TTextureInfo		m_texInfo[TextureLayerFlight];
	sInt32				m_alpha[TextureLayerFlight-1];	
// 	int					m_nSplattingTextureId[eMaxSplatting];
	sInt32				m_maskId;
	sInt32				m_shadow;
	sInt32				m_road;
	sInt32				m_effect;
	
	sInt32				m_zoneId;
	sInt32				m_envId;

	sInt32				m_liquidId;
	flt32				m_liquidHeight;
	flt32				m_liquidAlphaCoaf;
	COLORREF			m_liquidColor;

	int					m_lodLevel;
	int					m_textureLOD;
	TChunkVertex		m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1)];
	TChunkVertex		m_vertexIn[WORLD_TILE_CHUNK_UNIT_NUM*WORLD_TILE_CHUNK_UNIT_NUM];


	std::vector<sInt32>	m_staticModelList;
	std::vector<TDoodadLevelInfo*>	m_doodadList;
	bool			m_culled;
};
class CWorldChunkDataLock
{
public:
	CWorldChunkDataLock(CWorldChunk*pChunk,int val)
		:m_pChunk(pChunk),m_val(val)
	{
		m_pChunk->LockFlag(true);
		m_pChunk->MarkDataUsing(m_val,true);
	}
	~CWorldChunkDataLock()
	{
		m_pChunk->MarkDataUsing(m_val,false);
		m_pChunk->LockFlag(false);
	}
private:
	int m_val;
	CWorldChunk* m_pChunk;
};

#endif	// _MAP_MAPCHUNK_H__

