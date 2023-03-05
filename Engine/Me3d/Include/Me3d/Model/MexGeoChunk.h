#ifndef _MEX_CHUNK_DATA_H
#define _MEX_CHUNK_DATA_H

#include "Me3d/Me3d.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderable.h"
#include "Mutex.h"
#include "Me3d/Model/MexConfig.h"
#include "Me3d/Prim.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine/MeRenderManager.h"

union Mex2Pointer;
class Mex2;
class Mex2Geometry;
class Mex2Material;
struct Mex2Face;
class Box;
enum
{
	Mex2BbrdFlag_AlwayseLookAtCamera	= 1<<0,
	Mex2BbrdFlag_AlwayseStand			= 1<<1,
	Mex2BbrdFlag_VerticalGround			= 1<<2,
	Mex2BbrdFlag_AlwayseStand_ForEffect = 1<<3,
	Mex2BbrdFlag_OriginalPointCircling	= 1<<4,
    Mex2BbrdFlag_SmoothRotating         = 1<<5,
    Mex2BbrdFlag_FrontOffset            = 1<<6
};

static const long MAX_VERTEX_PER_CHUNK = 32768;//8*1024*1024;//32768;// //32768;

struct Mex2GeoChunkProperty
{
	enum
	{
		eStatic = 0,
		eBillboard,
		eLaser,
		//eRibbonEmitter, 
		eDecal,
		eFloor,
		eSupperFloor,
		eCollision,
		eDynamic,
		eRFloor,
		eRCollision,
		eSkeleton,
		eShimmer,
		eAlphaBox,
		eNoShadow,
		eMax
	};
	int		nType;
	float	fBillboardSize;
	DWORD	dwFlag;
	Mex2GeoChunkProperty():	nType(eStatic),
		fBillboardSize(0),
		dwFlag(0){}
	BOOL	Read( Mex2Pointer inP, int nSize );
};

class CMexChunkBase;
class CMexChunkData : public MeCommonAllocObj<CMexChunkData>
{
	friend Mex2;
	friend Mex2GeoChunk;
	friend class CDecalGeoChunk;
	friend class CStaticGeoChunk;
	friend class CCollisionGeoChunk;
	friend class CHelperGeoChunk;
	friend class CNoShadowGeoChunk;
	enum
	{
		eMaxUVLayer = 4,
	};

public:
	CMexChunkData();
	~CMexChunkData();
	BOOL	Read( Mex2Pointer inP, int nSize, DWORD dwVersion );

	const char* GetName();
	int GetChunkID() const { return m_nChunkID; }
	void SetChunkID(int val) { m_nChunkID = val; }

	int		GetVertexCount(){ return m_nVertexCount; }
	void	SetVertexCount( int nVertexCount ){ m_nVertexCount = nVertexCount; }
	void	SetVertices( float* pfVertices){ m_pVertices = (Vector*)pfVertices; }
	Vector* GetVertices() { return m_pVertices; }

	int		GetFaceCount(){ return m_nFaceCount; }
	void	SetFaceCount( int nFaceCount ){ m_nFaceCount = nFaceCount; }
	Mex2Face* GetFaces() { return m_pFaces; }

	void	SetNormals( float* pfNormals ){ m_pNormals = (Vector*)pfNormals; }
	Vector* GetNormals() { return m_pNormals; }

	void	SetUVs( int nLayer, float* pfUVs );

	bool	IsExistDiffuse(){return IsDiffuseExist;}
	void	SetDiffuse( DWORD* pdwDiffuse ){ m_pColors = pdwDiffuse; }
	DWORD*  GetDiffuses() { return m_pColors; }

	void	SetIndices( WORD* pwIndices ){ m_pFaces = (Mex2Face*)pwIndices; }
	BYTE*	GetBoneGroupIndices(){ return m_pBoneGroupIndices; }
	void	SetBoneGroupIndices( BYTE* pbyBoneGroupIndices ){ m_pBoneGroupIndices = pbyBoneGroupIndices; }
	int		GetMtlId(){ return m_nMtlId; }
	//int		GetRenderTextureID();
	void	SetUVLayerCount( short nLayerCount ){ m_shUVLayerCount = nLayerCount; };
	short	GetUVLayerCount(){ return m_shUVLayerCount; }
	Vector2* GetUVs( int nLayer = 0 ) { return (nLayer < m_shUVLayerCount) ? m_pUVs[nLayer] : NULL; }

	void	SetLightmapLayer( short layer ) { m_shLightmapLayer = layer; }
	short	GetLightmapLayer() { return m_shLightmapLayer; }
	static CMexChunkBase*				CreateMexChunk(CMexChunkData* pChunkData);
protected:
	char*	m_pszName;

	int		m_nChunkID;
	int		m_nVertexCount;
	int		m_nFaceCount;
	int		m_nMtlId;
	Vector* m_pVertices;
	Vector* m_pNormals;
	Vector2*	m_pUVs[eMaxUVLayer];
	BYTE*	m_pBoneGroupIndices;
	Mex2Face* m_pFaces;
	Mex2GeoChunkProperty m_property;
	short	m_shUVLayerCount;
	short	m_shLightmapLayer;	// 光照图所在UV层

	DWORD*	m_pColors;
	bool	m_bTreeLeaf;
	bool	IsDiffuseExist;
	bool	m_bLighting;
	bool	m_bHaveShadow;//是否可产生阴影

public:
	BOOL	IsEffect() const { return m_property.nType == (Mex2GeoChunkProperty::eBillboard) 
									|| m_property.nType == (Mex2GeoChunkProperty::eDecal) ; }
	bool	IsDynamicUSAGE() const { return m_property.nType == (Mex2GeoChunkProperty::eDynamic) 
									|| IsEffect() ; }
	bool	IsLighting() const { return m_bLighting; }
	bool	IsTreeLeaf() const { return m_bTreeLeaf; }
	bool	HaveShadow() const { return m_bHaveShadow; }
	Mex2GeoChunkProperty& GetProperty() { return m_property; }
	const Mex2GeoChunkProperty* GetPropertyP() const { return &m_property; }


	Vector*	GetWorldVertices(){ return vertices; }
	Vector* GetWorldNormals() const { return normals; }
	DWORD* GetWorldDiffuses() const { return diffuses; }
	Vector2* GetWorldUvs() const { return uvs; }
protected:
// 	Vector*			vertices;
// 	Vector*			normals;
// 	DWORD*			diffuses;
// 	Vector2*		uvs;
	static Vector	vertices[MAX_VERTEX_PER_CHUNK];
	static Vector	normals[MAX_VERTEX_PER_CHUNK];
	static DWORD	diffuses[MAX_VERTEX_PER_CHUNK];
	static Vector2	uvs[MAX_VERTEX_PER_CHUNK];
};

class CMexChunkBase:public IRenderable, public MeCommonAllocObj<CMexChunkBase>, public SortRenderable
{
	friend Mex2;
public:
	CMexChunkBase(CMexChunkData* pChunkData);
	virtual ~CMexChunkBase();

	virtual const char* GetName(){ return m_ChunkData->GetName(); }
	bool IsType(DWORD nType)const {return m_ChunkData->GetPropertyP()->nType == nType;}
	int GetChunkID() const { return m_ChunkData->GetChunkID(); }

	int		GetVertexCount(){ return m_ChunkData->GetVertexCount(); }
	void	SetVertexCount( int nVertexCount ){ m_ChunkData->SetVertexCount(nVertexCount); }
	void	SetVertices( float* pfVertices){ m_ChunkData->SetVertices(pfVertices); }
	Vector* GetVertices() { return m_ChunkData->GetVertices(); }

	int		GetFaceCount(){ return m_ChunkData->GetFaceCount(); }
	void	SetFaceCount( int nFaceCount ){ m_ChunkData->SetFaceCount(nFaceCount); }
	Mex2Face* GetFaces() { return m_ChunkData->GetFaces(); }

	void	SetNormals( float* pfNormals ){ m_ChunkData->SetNormals(pfNormals); }
	Vector* GetNormals() { return m_ChunkData->GetNormals(); }
	virtual bool IsNeedNormalPoints()					{return true;}

	bool	IsExistDiffuse(){return m_ChunkData->IsExistDiffuse();}
	void	SetDiffuse( DWORD* pdwDiffuse ){ m_ChunkData->SetDiffuse(pdwDiffuse); }
	void	SetIndices( WORD* pwIndices ){ m_ChunkData->SetIndices(pwIndices); }
	DWORD*  GetDiffuses() { return m_ChunkData->GetDiffuses(); }

	BYTE*	GetBoneGroupIndices(){ return m_ChunkData->GetBoneGroupIndices(); }
	void	SetBoneGroupIndices( BYTE* pbyBoneGroupIndices ){ m_ChunkData->SetBoneGroupIndices(pbyBoneGroupIndices); }
	int		GetMtlId(){ return m_ChunkData->GetMtlId(); }

	void	SetUVLayerCount( short nLayerCount ){ m_ChunkData->SetUVLayerCount(nLayerCount); }
	short	GetUVLayerCount(){ return m_ChunkData->GetUVLayerCount(); }

	void	SetUVs( int nLayer, float* pfUVs ){ m_ChunkData->SetUVs(nLayer,pfUVs); }
	Vector2* GetUVs( int nLayer = 0 ) { return m_ChunkData->GetUVs(nLayer); }

	void	SetLightmapLayer( short layer ) { m_ChunkData->SetLightmapLayer(layer); }
	short	GetLightmapLayer() { return m_ChunkData->GetLightmapLayer(); }

	// Vertex Buffer And Index Buffer
	virtual Vector*	GetVerticesLocked();
	virtual Vector*	GetNormalsLocked();
	virtual DWORD*	GetDiffuseLocked();
	virtual Vector2* GetUVsLocked( int nLayer );
	virtual void	UnlockVertices();
	virtual void	UnlockNormals();
	virtual void	UnlockUVs(int nLayer);

	void	UnlockDiffuse();

	Mex2Face*	GetIndicesLocked();
	void	UnlockIndices();

	void	SetIB( LPDIRECT3DINDEXBUFFER9 pIB ){ m_pIB = pIB; }
	LPDIRECT3DINDEXBUFFER9&	 GetIB(){return m_pIB;}

	virtual void createBuffers();
	virtual void AfterCreateBuffers();
	virtual void restoreBuffers();
	virtual void invalidateBuffers();
	virtual void destroyBuffers();
	virtual void OnDeviceLost();
	virtual void RebuildBuffer();
	LPDIRECT3DVERTEXBUFFER9 GetVerticesBuffer() const { return verticesBuffer; }
	LPDIRECT3DVERTEXBUFFER9 GetNormalsBuffer() const { return normalsBuffer; }
	LPDIRECT3DVERTEXBUFFER9 GetDiffusesBuffer() const { return diffusesBuffer; }
	LPDIRECT3DVERTEXBUFFER9 GetUvsBuffer() const { return uvsBuffer; }
	LPDIRECT3DVERTEXBUFFER9 GetUvsBuffer2() const { return uvsBuffer2; }

	Vector* GetMin(){ return &m_vMin; }
	Vector* GetMax(){ return &m_vMax; }
	Vector& GetNormalPoints(int index) ;

	bool IsNoSortChunk() const { return m_bNoSortChunk; }
	void SetNoSortChunk(bool val) { m_bNoSortChunk = val; }
	bool IsSolidChunk() const { return m_bSolidChunk; }
	void SetSolidChunk(bool val) { m_bSolidChunk = val; }
	virtual void	SetAvatarComponent() { m_bIsAvatarComponent = true; }
	virtual bool	IsAvatarComponent() { return m_bIsAvatarComponent; }

public://from SortRenderable
	virtual int	GetTotalVerticesCount(bool bPost)
	{
		if (false == bPost)
		{
			return GetOtherInfos(bPost).size() * GetVertexCount();
		}
		else
		{
			return GetVertexCount();
		}
	}
	virtual int	GetTotalFacesCount(bool bPost)
	{
		if (false == bPost)
		{
			return GetOtherInfos(bPost).size() * GetFaceCount();
		}
		else
		{
			return GetFaceCount();
		}
	}

	virtual float			GetDisToCameraEye(float* pMatrices);
	void TestCreateUVsBuffer( int layer, float offsetx, float offsety, float uscale, float vscale );
protected:
	LPDIRECT3DVERTEXBUFFER9 verticesBuffer;
	LPDIRECT3DVERTEXBUFFER9 normalsBuffer;
	LPDIRECT3DVERTEXBUFFER9 diffusesBuffer;
	LPDIRECT3DVERTEXBUFFER9 uvsBuffer;
	LPDIRECT3DVERTEXBUFFER9 uvsBuffer2;// for uv2

	LPDIRECT3DINDEXBUFFER9 m_pIB;

	Vector m_vMin;
	Vector m_vMax;
	Vector m_vCenter;

	void CreateIndexBuffer();
	void CreateVertexBuffers( DWORD usage, D3DPOOL pool );
	virtual DWORD GetD3DUSAGE(){return D3DUSAGE_WRITEONLY;}
	virtual D3DPOOL GetD3DPOOL(){return D3DPOOL_MANAGED;}
protected:
	CMexChunkData* m_ChunkData;
	virtual void		InitialBBox();

	Vector* m_pNormalPoints;

	bool m_bSolidChunk;//该chunk永远不会被半透处理
	bool m_bNoSortChunk;//该chunk不会参与alpha排序

	bool m_bIsAvatarComponent;	// 是装备模型
public:
	bool HaveShadow() const { return m_ChunkData->HaveShadow(); }
	bool IsDynamicUSAGE() const { return m_ChunkData->IsDynamicUSAGE(); }
	BOOL IsEffect() const { return m_ChunkData->IsEffect(); }
	bool IsLighting() const { return m_ChunkData->IsLighting(); }
	bool IsTreeLeaf() const { return m_ChunkData->IsTreeLeaf(); }
	Mex2GeoChunkProperty& GetProperty() { return m_ChunkData->GetProperty(); }

	Vector*	GetWorldVertices(){ return m_ChunkData->GetWorldVertices(); }
	Vector* GetWorldNormals() const { return m_ChunkData->GetWorldNormals(); }
	DWORD* GetWorldDiffuses() const { return m_ChunkData->GetWorldDiffuses(); }
	Vector2* GetWorldUvs() const { return m_ChunkData->GetWorldUvs(); }

	CMexChunkData* GetChunkData() { return m_ChunkData; }
};

class Mex2GeoChunk : public CMexChunkBase
{
	friend Mex2;
	friend Mex2Geometry;
public:
	Mex2GeoChunk(CMexChunkData* pChunkData);
	virtual ~Mex2GeoChunk();

// 	void	InitInstance();//for grass
 	virtual DWORD	GetType() = 0;
	//void	BlendVertex( SK_VERTEX* vertex, int nMaxVertexCount, Mex2* pMex, MeMatrix* pMatrices );
	//   added 2004.08.03
	virtual void DoRender( bool bPost = false );
	void	BlendBoneGroup( MeMatrix* pMatrices, MeMatrix* pBoneGroupMatrices );
	int		CalcUseBoneGroup();
	//   added 2004.07.16
	BOOL	CheckIsSingleBoneInfl();

	//   added 2004.07.07
	Mex2Material* GetMtl();

	// change [5/29/2008 whu]
	virtual bool	Render( RenderParams* params, DWORD dwFlagEx = 0, IReplaceableTextureProj* pLuminanceTextureProj = NULL, int* pVertexCount=NULL,
		int* pFaceCount=NULL);
// 	virtual void	FastRender( IMex* pMex, float* pMatrices, IRenderer* pRenderer, IReplaceableTextureProj* pReplaceableTextureProj, float fAlpha, bool bMustUseAlphaBlend,int nFrameId, DWORD dwFlagEx = 0 );
	virtual void	RenderShadow( IMex* pMex, float* pMatrices, IRenderer* pRenderer, IReplaceableTextureProj* pReplaceableTextureProj, float fAlpha, bool bMustUseAlphaBlend,int nFrameId, DWORD dwFlagEx = 0 );

	bool HaveSameTextures( const IRenderable* pObject ) const { return true; }

	/*
	 * Author:	2012-7-18 wangshuai
	 * Desc: 	GeoChunk的材质是否有AlphaTest标记
	 */
	bool IsMtrlHasAlphaTest();

	virtual bool	BlendVertex(IMex* pMex, float* pMatrices);	// 模型local坐标转换为世界坐标
	virtual bool	BlendVertex( float* pBlendedVertices, float* pBlendedNormals, int nMaxVertexCount, IMex* pMex, float* pMatrices ,MeMatrix* pTmpMatrices );

	void OutputBoneGroupInfoByVertexId( int nVId );


// 	void	CombineTo( CombineModelData* pRenderParams, Vector* pDstVertices, Vector* pDstNormals, DWORD* pDstDiffuses,
// 		Vector2* pDstUVs, Mex2Face* pDstFaces, int nVertexOffset );
// 	void	CombineTo( CombineModelData* pRenderParams, MexVertex* pVBVertex, short* shIBFace, int nVertexOffset );
// 	void	RenderWithFlag( IRenderer* pRenderer, CombineModelData* pRenderParams, short stUseTexId );


// 	BOOL	Intersect( Vector* pvStart, Vector* pvDir,float* hits,  int nMax_INTERSECTION, int& nHit, DWORD dwFlag );
	bool	IntersectQuick( Vector* pvStart, Vector* pvDir, MexReplaceableTextureProj* replaceableTexture, D3DXMATRIX* pModelInverseMatrix );

	bool	IsAlphaChunk(const RenderParams* params )
	{
		return (!IsSolidChunk()) 
		&& ((params->fGlobalAlpha < 1.0f)|| (params->dwFlag & eAlphaBlend) );
		/*&& (!(params->dwFlag & eRenderTreeLeaf)) ;*/
	}

	Mex2*	GetMex() { return m_pSrcMex; }
	void	SetMex(Mex2* pMex) { if( pMex ) m_pSrcMex = pMex; }

	BOOL	IsBillboard() { return (GetType() == Mex2GeoChunkProperty::eBillboard); }
	BOOL	IsDecal() { return (GetType() == Mex2GeoChunkProperty::eDecal); }
	BOOL	IsFloor() { return (GetType() == Mex2GeoChunkProperty::eFloor) || (GetType() == Mex2GeoChunkProperty::eRFloor); }
	BOOL	IsSupperFloor() { return (GetType() == Mex2GeoChunkProperty::eSupperFloor); }
	BOOL	IsCollision() { return (GetType() == Mex2GeoChunkProperty::eCollision) || (GetType() == Mex2GeoChunkProperty::eRCollision) ; }
	BOOL	IsHelper() { return IsFloor() || IsSupperFloor() ||  IsCollision(); }

protected:
	virtual void _Render( RenderParams* params );		
	virtual void _DoRender(const RenderParams* params);

	virtual void _WriteDiffuseBuffer(DWORD dwColor, DWORD lockFlag);
	virtual void _ChangeVertexColorAlpha(BYTE alpha, DWORD lockFlag);
	virtual void _WriteUVBuffer(DWORD lockFlag);

	//   added 2004.07.16
	BOOL	m_bSingleBoneInfl;
	int		m_nSingleBoneId;
	std::vector<bool> m_vectorUseBoneGroup;

	//   added 2003.10.14
	Mex2*	m_pSrcMex;

protected:
	// 保存转换为世界坐标的数据，用于渲染
	float			m_fOldU;
	float			m_fOldV;
	DWORD			m_dwOldColor;
	BYTE			m_oldAlpha;
	int				m_nTileFrameId;
	int				m_nUTiles;
	int				m_nVTiles;
};

class CStaticGeoChunk : public Mex2GeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eStatic;}
	CStaticGeoChunk(CMexChunkData* pChunkData)
		:Mex2GeoChunk(pChunkData){ m_spRenderObject = MeNew MeModelRenderObject;}
	virtual ~CStaticGeoChunk(){}

	virtual bool IsNeedNormalPoints()					{return false;}

	virtual void AfterCreateBuffers();

// 	virtual void DoRender( bool bPost = false );
protected:
// 	virtual void _Render( RenderParams* params );
	virtual void _DoRender(const RenderParams* params);
};

class CDynamicGeoChunk : public Mex2GeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eDynamic;}
	CDynamicGeoChunk(CMexChunkData* pChunkData)
		:Mex2GeoChunk(pChunkData){m_spRenderObject = MeNew MeModelRenderObject;}
	virtual ~CDynamicGeoChunk(){}
	virtual Vector*	GetVerticesLocked(){return GetVertices();}
	virtual Vector*	GetNormalsLocked(){return GetNormals();}
	virtual void	UnlockVertices(){;}
	virtual void	UnlockNormals(){;}
protected:
	virtual DWORD GetD3DUSAGE(){return D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC;}
	virtual D3DPOOL GetD3DPOOL(){return D3DPOOL_DEFAULT;}
};


class CBillboardGeoChunk : public Mex2GeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eBillboard;}
	CBillboardGeoChunk(CMexChunkData* pChunkData);
	virtual ~CBillboardGeoChunk();

	void	SetBillboardLocaled(bool bLocaled){ m_bIsBillboardLocal = bLocaled; }
	bool	IsBillboardLocaled(){ return m_bIsBillboardLocal; }

	Vector*  GetWorldBillboardVertices(){ return billboard_vertices; }

	virtual Vector*	GetVerticesLocked(){return GetVertices();}
	virtual Vector*	GetNormalsLocked(){return GetNormals();}
	virtual void	UnlockVertices(){;}
	virtual void	UnlockNormals(){;}

	virtual void createBuffers();
	virtual void _WriteDiffuseBuffer(DWORD dwColor, DWORD lockFlag);
	virtual void _WriteUVBuffer(DWORD lockFlag);

	void	UpdateBillboard(float* pMatrices);
	void	UpdateBillboard(Vector* billboard_vertices, float* pMatrices);
// 	virtual void DoRender( bool bPost = false );
	bool	CanCombinedRender();
	void		CombinedRender( bool bPost, int nBaseVertex,
		Vector*						m_VertexMem,
		Vector*						m_NormalMem,
		DWORD*						m_DiffuseMem,
		Vector2*					m_UvsMem
//		,unsigned short*				m_shIBMem
		);

protected:
// 	virtual void _Render( RenderParams* params );
	virtual void _DoRender(const RenderParams* params);
		
protected:
	bool m_bIsBillboardLocal;//用于lightmap
	Vector* billboard_vertices;

	void	UpdateBillboardBox();

	virtual DWORD GetD3DUSAGE(){return D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC;}
	virtual D3DPOOL GetD3DPOOL(){return D3DPOOL_DEFAULT;}

private:
    float m_fFrontOffset;     // 公告板增加向前偏移       added by zhuomeng.hu		[1/27/2011]
};

class CDecalGeoChunk : public Mex2GeoChunk
{
public:
	typedef float (*funcGetZByXY)( float fCurrentZ,float x, float y,DWORD dwFlag, 
		BOOL* bInFloor, DWORD* pdwRet, 
		BOOL bIsRole, D3DXVECTOR3 *pNormal );

	static void SetGetZByXYFunc( funcGetZByXY pfFun ){ ms_pfGetZByXY = pfFun; }
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eDecal;}
	CDecalGeoChunk(CMexChunkData* pChunkData);
	virtual ~CDecalGeoChunk(){}

// 	virtual void DoRender( bool bPost = false );

protected:
	void	SetWorldMatrix(const MeMatrix& kMatrix);
	bool	IsEqualToWorldMatrix(const MeMatrix& kMatrix);
	bool	IsWorldMatrixEqualToZero();
	virtual Vector*	GetVerticesLocked(){return GetVertices();}
	virtual Vector*	GetNormalsLocked(){return GetNormals();}
	virtual void	UnlockVertices(){;}
	virtual void	UnlockNormals(){;}
// 	virtual void		InitialBBox();
// 	virtual void _Render( RenderParams* params );
	virtual void _DoRender(const RenderParams* params);
		

	MeMatrix m_decalMatrix;
	int m_decalVectorCount;
	std::vector<Vector>  m_decalVectorList;
	MeMatrix m_WorldMatrix;	// 记录上一帧世界坐标转换矩阵
	virtual DWORD GetD3DUSAGE(){return D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC;}
	virtual D3DPOOL GetD3DPOOL(){return D3DPOOL_DEFAULT;}
	// added, jiayi, [2010/7/27]
	// 从外部设置，调用地形的函数
	static funcGetZByXY ms_pfGetZByXY;
};

class CHelperGeoChunk :public Mex2GeoChunk
{
public:
	virtual bool IsNeedNormalPoints()					{return true;}
	virtual void AfterCreateBuffers();
	virtual bool Render( RenderParams* params,
		DWORD dwFlag = 0,
		IReplaceableTextureProj* pLuminanceTextureProj = NULL,
		int* pVertexCount=NULL,
		int* pFaceCount=NULL );
	virtual void DoRender( bool bPost = false );
	virtual D3DXCOLOR* GetHelperColor() {return &diffuse;}
	CHelperGeoChunk(CMexChunkData* pChunkData)
		:Mex2GeoChunk(pChunkData){ m_spRenderObject = MeNew MeModelRenderObject; }
	virtual ~CHelperGeoChunk(){}
protected:
	D3DXCOLOR diffuse;
};

class CFloorGeoChunk : public CHelperGeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eFloor;}
	CFloorGeoChunk(CMexChunkData* pChunkData)
		:CHelperGeoChunk(pChunkData)
	{
		diffuse.a = 1.f;
		diffuse.r = 0.f;
		diffuse.g = 0.f;
		diffuse.b = 0.3f;
	}
	virtual ~CFloorGeoChunk(){}
};

class CAlphaBoxGeoChunk : public CHelperGeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eAlphaBox;}
	CAlphaBoxGeoChunk(CMexChunkData* pChunkData)
		:CHelperGeoChunk(pChunkData)
	{
		diffuse.a = 1.f;
		diffuse.r = 0.5f;
		diffuse.g = 0.f;
		diffuse.b = 0.3f;
	}
	virtual ~CAlphaBoxGeoChunk(){}
};

class CSupperFloorGeoChunk : public CHelperGeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eSupperFloor;}
	CSupperFloorGeoChunk(CMexChunkData* pChunkData)
		:CHelperGeoChunk(pChunkData)
	{
		diffuse.a = 1.f;
		diffuse.r = 0.f;
		diffuse.g = 0.5f;
		diffuse.b = 0.0f;
	}

	virtual ~CSupperFloorGeoChunk(){}
};

class CRfloorGeoChunk : public CHelperGeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eRFloor;}
	CRfloorGeoChunk(CMexChunkData* pChunkData)
		:CHelperGeoChunk(pChunkData)
	{
		diffuse.a = 1.f;
		diffuse.r = 0.f;
		diffuse.g = 0.1f;
		diffuse.b = 0.3f;
	}

	virtual ~CRfloorGeoChunk(){}
};

class CCollisionGeoChunk : public CHelperGeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eCollision;}
	CCollisionGeoChunk(CMexChunkData* pChunkData)
		:CHelperGeoChunk(pChunkData)
	{
		diffuse.a = 1.f;
		diffuse.r = 0.3f;
		diffuse.g = 0.f;
		diffuse.b = 0.f;
	}
	virtual void AfterCreateBuffers();

	virtual ~CCollisionGeoChunk(){}
};

class CRCollisionGeoChunk : public CHelperGeoChunk
{
public:
	virtual bool IsNeedNormalPoints()					{return false;}
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eRCollision;}
	CRCollisionGeoChunk(CMexChunkData* pChunkData)
		:CHelperGeoChunk(pChunkData)
	{
		diffuse.a = 1.f;
		diffuse.r = 0.3f;
		diffuse.g = 0.1f;
		diffuse.b = 0.f;
	}

	virtual ~CRCollisionGeoChunk(){}
};

class CSkeletonGeoChunk : public Mex2GeoChunk
{
public:
	virtual DWORD	GetType(){return Mex2GeoChunkProperty::eSkeleton;}
	CSkeletonGeoChunk(CMexChunkData* pChunkData);
	virtual ~CSkeletonGeoChunk();

	virtual Vector2* GetUVsLocked( int nLayer );
// 	virtual void DoRender( bool bPost = false );

	virtual void createBuffers();
	virtual void restoreBuffers();
	virtual void invalidateBuffers();
	virtual void destroyBuffers();
	virtual void OnDeviceLost();

	virtual void RenderShadow( IMex* pMex, float* pMatrices, IRenderer* pRenderer, IReplaceableTextureProj* pReplaceableTextureProj, float fAlpha, bool bMustUseAlphaBlend,int nFrameId, DWORD dwFlagEx = 0 );

protected:
	virtual void _Render( RenderParams* params );
	virtual void _DoRender(const RenderParams* params);

	virtual void _WriteDiffuseBuffer(DWORD dwColor, DWORD lockFlag);
	virtual void _WriteUVBuffer(DWORD lockFlag);

private:
	LPDIRECT3DVERTEXBUFFER9	boneWgtIdxBuffer;

	std::map<int, int> m_matrixIdxByBoneIdx;

	static const unsigned int BoneMatrixCount = 56;
	D3DXMATRIXA16 m_boneWorldMatrix[BoneMatrixCount];

	bool m_bChangeColor;
};

/*
 * Author:	2012-7-18 wangshuai
 * Desc: 	MAX对象(GeoChunk)以noshadow.开头的, 不参与阴影计算
 */
class CNoShadowGeoChunk : public Mex2GeoChunk
{
public:
	virtual DWORD GetType() { return Mex2GeoChunkProperty::eNoShadow; }

	CNoShadowGeoChunk(CMexChunkData *pChunkData) : Mex2GeoChunk(pChunkData)
	{
		m_spRenderObject = MeNew MeModelRenderObject;
	}

	virtual ~CNoShadowGeoChunk() {}

	virtual void AfterCreateBuffers();

	virtual bool IsNeedNormalPoints() {return false;}

protected:
	
	virtual void _DoRender(const RenderParams* params);

	virtual void RenderShadow( IMex* pMex, float* pMatrices, IRenderer* pRenderer,
		IReplaceableTextureProj* pReplaceableTextureProj, float fAlpha, bool bMustUseAlphaBlend,int nFrameId, DWORD dwFlagEx = 0 ){}
};

// class CShimmerGeoChunkStatic : public CStaticGeoChunk
// {
// public:
// 	CShimmerGeoChunkStatic( CMexChunkData* pChunkData )
// 		: CStaticGeoChunk(pChunkData){};
// 	virtual DWORD GetType() { return Mex2GeoChunkProperty::eShimmer; }
// };
// 
// class CShimmerGeoChunkDynamic : public CDynamicGeoChunk
// {
// public:
// 	CShimmerGeoChunkDynamic( CMexChunkData* pChunkData )
// 		: CDynamicGeoChunk(pChunkData){};
// 	virtual DWORD GetType() { return Mex2GeoChunkProperty::eShimmer; }
// };
// 
// class CShimmerGeoChunkBillboard : public CBillboardGeoChunk
// {
// public:
// 	CShimmerGeoChunkBillboard( CMexChunkData* pChunkData )
// 		: CBillboardGeoChunk(pChunkData){};
// 	virtual DWORD GetType() { return Mex2GeoChunkProperty::eShimmer; }
// };
// 
// class CShimmerGeoChunkSkeleton : public CSkeletonGeoChunk
// {
// public:
// 	CShimmerGeoChunkSkeleton( CMexChunkData* pChunkData )
// 		: CSkeletonGeoChunk(pChunkData){};
// 	virtual DWORD GetType() { return Mex2GeoChunkProperty::eShimmer; }
// };


#endif