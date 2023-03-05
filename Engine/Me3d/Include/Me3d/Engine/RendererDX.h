#pragma once
#include "Me3d/Me3d.h"
#include "MapContainer.h"
#include "Renderer.h"
#include "Mutex.h"
#include "RendererDx8.h"
#include "D3dRenderState.h"
#include "FuncPerformanceLog.h"

#define USE_MANUAL_RS_MANAGED
#define LIGHT_AMB_DIFF_SCALE 2.f

// add [6/4/2008 whu]
namespace graphics
{
    class Material;
	class ShaderVertexPixel;
}

struct HREffectVert
{
	float		x, y, z;
	DWORD		color;
	float		u, v;
};
class CHREffectBuffer
{
public:
	enum
	{
		eMaxFace = 1024,
		eMaxVert = eMaxFace*3
	};
public:
	int		m_nTextureID;
	int		m_nNumVert;
	int		m_nNumFace;
	DWORD	m_dwFlag;
	HREffectVert m_Vertices[eMaxVert];
	WORD	m_Indices[eMaxFace*3];
};


class FEngineState
{
public:
	DWORD MaxActiveLights;
	DWORD MaxPrimitiveCount;
	DWORD MaxVertexIndex;
	DWORD MaxStreams;
	DWORD MaxStreamStride;
	DWORD MaxVertexShaderConst;
	DWORD VertexProcessingCaps;
	DWORD VertexShaderVersion;
	DWORD PixelShaderVersion;

	DWORD MaxPixelShaderVersion;
	DWORD FirstColoredMip;

	DWORD MaxUserClipPlanes;

	BOOL  SupportsCubemaps;
	BOOL  UseDXT1;
	BOOL  UseDXT3;
	BOOL  UseDXT5;
	BOOL  UseTrilinear;
	BOOL  UseCubemaps;
	BOOL  UseMipmapping;
	BOOL  UseHardwareTL;
	
	BOOL  DetailTextures;

	BOOL  MaxTextureAspectRatio;	//Max aspect
	BOOL  UseMippedCubemaps;

	BOOL  SupportsLodBiasing;
	BOOL  SupportsZBiasing;
	BOOL  SupportsAddsigned2x;// D3DTOP_ADDSIGNED2X;
	BOOL  SupportsDumpEnvmap;
	BOOL  SupportsBumpenvmapLuminance; //UMPENVMAPLUMINANCE;
	BOOL  SupportsDotProduct3;

	DWORD MaxTextureWidth;
	DWORD MaxTextureHeight;
	DWORD MaxTextureBlendStages;
	DWORD MaxSimultaneousTextures;

	FEngineState();
	VOID  Init( VOID *pState );
};
// Stencil buffer operations.

enum EStencilOp
{
	SO_Keep			= 1,
	SO_Zero			= 2,
	SO_Replace		= 3,
	SO_IncrementSat	= 4,
	SO_DecrementSat	= 5,
	SO_Invert		= 6,
	SO_Increment	= 7,
	SO_Decrement	= 8
};

// Comparison functions.

enum ECompareFunction
{
	CF_Never		= 1,
	CF_Less			= 2,
	CF_Equal		= 3,
	CF_LessEqual	= 4,
	CF_Greater		= 5,
	CF_NotEqual		= 6,
	CF_GreaterEqual	= 7,
	CF_Always		= 8
};


enum GAME_LIGHT_INDEX
{
	LIGHT_INDEX_TERRAIN = 0,
	LIGHT_INDEX_PLAYER,
	LIGHT_INDEX_EQIUP,
	LIGHT_INDEX_COLLISION,
	LIGHT_INDEX_COUNT
};

class RendererDx : public IRenderer, public CSemiAutoIntLock
{

	///
	//	FD3DSavedState
	//
	class FD3DSavedState
	{
	public:

		IDirect3DSurface9*	RenderTargetSurface;
		IDirect3DSurface9*	DepthStencilSurface;

		INT					ViewportX,
			ViewportY,
			ViewportWidth,
			ViewportHeight;

		INT					ZBias;

		ECompareFunction	StencilTest;
		EStencilOp			StencilFailOp,
							StencilZFailOp,
							StencilPassOp;
		DWORD				StencilRef,
							StencilMask,
							StencilWriteMask;

		D3DXMATRIX			LocalToWorld,
							WorldToCamera,
							CameraToScreen;

		DWORD				dwFvF;
	//	FD3DVertexShader*	VertexShader;
	//	FD3DPixelShader*	PixelShader;
		class FD3DVertexStream*	Streams[16];
		INT					StreamStrides[16],
							NumStreams;

		class FD3DIndexBuffer*	IndexBuffer;
		INT					IndexBufferBase;

		D3DCULL				CullMode;

		BOOL				UseDynamicLighting;
		BOOL				UseStaticLighting;
		BOOL				LightingModulate2X;
		BOOL				LightingOnly;
	//	FD3DTexture*		Lightmap;
	//	FSphere				LitSphere;
		D3DCOLORVALUE		AmbientLightColor;
		D3DLIGHT9			Lights[8];
		BOOL				LightEnabled[8];

		BOOL				DistanceFogEnabled;
		FLOAT				DistanceFogStart,
							DistanceFogEnd;
		D3DCOLORVALUE		DistanceFogColor;

		INT					NumMaterialPasses;
		INT					CurrentMaterialPass;

		FD3DSavedState();
	};
public:
	enum
	{
		eMaxRenderBuffer = 2,
		eMaxSurface = 1024,
		eMaxTextureStage = 2,
		eMaxEffectBuffer = 128,

		//eMaxD3DRenderState = D3DRS_NORMALORDER,//D3DRS_NORMALORDER,
		//eMaxD3DTextureState = D3DTSS_RESULTARG,
	};
	enum
	{
		eNormalSurface,
		eSortSurface,
	};

public:
	RendererDx(void);
	~RendererDx(void);

	void SetDevice( void* pDevice );
	void* GetDevice();//{ return m_pDevice; }
	//void* GetRealDevice();//{ return m_pDevice; }
	void SetTexture( DWORD dwStage, void* pTexture );

	void SetTextureHardware( DWORD dwStage, void* pTexture );
	
	void SetIndices( void* IndexData, DWORD BaseVertexIndex );

#ifndef NEW_RESMGR
	void SetIndices(FIndexBuffer* IndexBuffer,INT BaseVertexIndex);
	void SetStreamSource( DWORD StreamNumber, void* StreamData, DWORD StreamStride );
#else
	void SetIndices(FIndexBuffer* IndexBuffer,INT BaseVertexIndex);
	void SetStreamSource( DWORD StreamNumber, class FVertexStream* StreamData, DWORD StreamStride );
#endif

	INT SetDynamicStream(DWORD Shader,FVertexStream* Stream);
	INT SetDynamicIndexBuffer(FIndexBuffer* IndexBuffer,INT BaseVertexIndex);

	inline void SetFVF( DWORD dwShader );
	inline void SetRenderState( DWORD dwState, DWORD dwValue );
	void SetTextureStageState( DWORD dwStage, DWORD dwType, DWORD dwValue );
	inline void SetSamplerState( DWORD dwStage, DWORD dwType, DWORD dwValue );

	inline void SetTransform( DWORD State,CONST FLOAT* pMatrix);

	inline void SetVertices( void* pVertices );
	inline void SetNormals( void* pNormals );
	inline void SetIndices( void* pIndices );
	inline void SetIB( LPDIRECT3DINDEXBUFFER9 pIB );
	inline void SetUVs( void* pUVs, int nLayer );
	inline void SetLayerCount( int nLayerCount );
	inline void SetTextureId( short shTextureId, int nLayer );
	inline void SetDiffuse( void* pDiffuse );
	inline void SetShaderId( short shShaderId );
	inline void SetSurfaceFVF( DWORD dwFVF );
	inline void SetVertexStride( int nStride );
	inline void SetMaterial( BYTE* pbyMtl );
	inline void SetDefaultMaterial( BYTE* pbyMtl );
	inline void GetDefaultMaterial( BYTE* pbyMtl );
	inline void SetMtlSpecular( float power, float a, float r, float g, float b );
	inline void EnableSpecular( BOOL bEnable );
// 	void Push( int nVertexCount, int nFaceCount, DWORD dwFlag );

// 	void PushEffectSurface( int nMainMapID,
// 						BYTE* pVertices,
// 						int nNumVert,
// 						BYTE* pIndices,
// 						int nNumTriangle,
// 						DWORD dwFlag );

// 	void PushSurface(	short nMainMapID,
// 						short nAddMapID,
// 						short nShaderID,
// 						DWORD dwFvf,
// 						UINT nStride,
// 						BYTE *pVertices,
// 						WORD nVertCount,
// 						BYTE * pIndeices,
// 						WORD nTriangleCount,
// 						DWORD dwFlag,
// 						DWORD dwPolyType = D3DPT_TRIANGLELIST );

	//void DirectPushSurface(	short nMainMapID,
	//					short nAddMapID,
	//					short nShaderID,
	//					DWORD dwFvf,
	//					UINT nStride,
	//					BYTE *pVertices,
	//					WORD nVertCount,
	//					BYTE *pIndeices,
	//					WORD nTriangleCount,
	//					DWORD dwFlag,
	//					DWORD dwPolyType = D3DPT_TRIANGLELIST,
	//					INT	  nIBOffset = 0 );

	void DirectPushSurface(	short nMainMapID,
							short nAddMapID,
							short nShaderID,
							DWORD dwFvf,
							UINT nStride,
							BYTE *pVertices,
							UINT nVertCount,
							BYTE *pIndeices,
							UINT nTriangleCount,
							DWORD dwFlag,
							DWORD dwPolyType = D3DPT_TRIANGLELIST,
							INT nIBOffset = 0,
							INT nVBOffset = 0,
                            int nType = 0,
                            short nLuminanceMapID = -1 );


	bool BeginDirectPushSurface(short nMainMapID,
		short nAddMapID,
		short nShaderID,
		DWORD dwFvf,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		LPDIRECT3DVERTEXBUFFER9 pNormals,
		LPDIRECT3DVERTEXBUFFER9 pColors,
		LPDIRECT3DVERTEXBUFFER9 pUVs,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		DWORD dwFlag,
		INT nVBOffset = 0,
		int nType = 0,
		short nLuminanceMapID = -1,
		short nLightmapTexId = -1,
		LPDIRECT3DVERTEXBUFFER9 pUVs2 = NULL,
		Vector2* pvLightmapUVScale = NULL,
		Vector2* pvLightmapUVOffset = NULL);

	graphics::ShaderVertexPixel* m_pCurrentShader;
	static bool m_BOpenKT;

	void DoDirectPushSurface(UINT nVertCount,
		UINT nTriangleCount,
		DWORD dwPolyType = D3DPT_TRIANGLELIST,
		INT nIBOffset = 0);

	void EndDirectPushSurface();

	void DirectPushSurface(	short nMainMapID,
		short nAddMapID,
		short nShaderID,
		DWORD dwFvf,
		UINT nVertCount,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		LPDIRECT3DVERTEXBUFFER9 pNormals,
		LPDIRECT3DVERTEXBUFFER9 pColors,
		LPDIRECT3DVERTEXBUFFER9 pUVs,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		UINT nTriangleCount,
		DWORD dwFlag,
		DWORD dwPolyType = D3DPT_TRIANGLELIST,
		INT nIBOffset = 0,
		INT nVBOffset = 0,
		int nType = 0,
		short nLuminanceMapID = -1 );


	bool BeginDirectPushSurfaceSkeleton(	short nMainMapID,
		short nAddMapID,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		LPDIRECT3DVERTEXBUFFER9 pNormals,
		LPDIRECT3DVERTEXBUFFER9 pColors,
		LPDIRECT3DVERTEXBUFFER9 pUVs,
		LPDIRECT3DVERTEXBUFFER9 pBoneWeightAndIndices,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		DWORD dwFlag,
		short nLuminanceMapID,
		bool isEffect,
		D3DCOLOR dwColor);

	void DoDirectPushSurfaceSkeleton(		UINT nVertCount,
		UINT nTriangleCount,
		D3DXMATRIXA16* pBoneWorldMatrix,
		unsigned int nBoneMatrixCount  );

	void EndDirectPushSurfaceSkeleton();

	void DirectPushSurfaceSkeleton(	short nMainMapID,
		short nAddMapID,
		UINT nVertCount,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		LPDIRECT3DVERTEXBUFFER9 pNormals,
		LPDIRECT3DVERTEXBUFFER9 pColors,
		LPDIRECT3DVERTEXBUFFER9 pUVs,
		LPDIRECT3DVERTEXBUFFER9 pBoneWeightAndIndices,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		UINT nTriangleCount,
		DWORD dwFlag,
		short nLuminanceMapID,
		bool isEffect,
		D3DCOLOR dwColor,
		D3DXMATRIXA16* pBoneWorldMatrix,
		unsigned int nBoneMatrixCount );







	virtual void RenderTerrainWithShader(short nBaseTextureID,
		short nTexture1,
		short nTexture2,
		short nTexture3,
		ITexture* maskTexture,
		UINT nStride,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		WORD nVertCount,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		WORD nTriangleCount
		);

	virtual void RenderTerrainLOD2WithShader(UINT nStride,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		WORD nVertCount,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		WORD nTriangleCount 
		);

	virtual void InitTerrainTransform();
// 	virtual void PrepareModelShader();
	virtual void PrepareTerrainShader(bool bDepth);
	virtual void EndShader();
	virtual void PrepareTerrainLOD2Shader() ;	
	virtual void EndLOD2Shader();
	virtual void RenderLiquidWithShader(
		short nLiquidTextureID,
		UINT nStride,
		BYTE *pVertices,
		WORD nVertCount,
		BYTE *pIndeices,
		WORD nTriangleCount
		) ;

	virtual void RenderLiquidWithShader_High(
		short nLiquidTextureID,
		UINT nStride,
		BYTE *pVertices,
		WORD nVertCount,
		BYTE *pIndeices,
		WORD nTriangleCount);

	virtual void PrepareLiquidShader();
	virtual void PrepareLiquidShader_High();






	// Mex模型的快速渲染通道
// 	MexVertex* LockMexVB( int nVertCount, int& nBaseVertexIndex );
// 	void UnlockMexVB();

// 	void BeginFastRenderMex();
// 	void EndFastRenderMex();

// 	void FastRenderMex(	short nMainMapID,
// 						short nAddMapID,
// 						WORD nVertCount,
// 						BYTE *pIndeices,
// 						WORD nTriangleCount,
// 						DWORD dwFlag,
// 						D3DMATERIAL9* mtrl,
// 						INT nVBOffset = 0 );






	DWORD SetViewport ( VOID* pViewport);
	DWORD BeginScene();
	VOID  EndScene();
	DWORD Clear ( DWORD Count, DWORD Flags,DWORD Color,float Z,DWORD Stencil);
	void DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,	UINT PrimitiveCount);
	void DrawPrimitiveUP( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride );
	void DrawIndexedPrimitive( D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount );

// 	virtual void SetLOD2Color(float * color  );
	void SetLight( int nLightID, void* pLight );
	void GetLight( int nLightID, D3DLIGHT9* pLight );
	D3DXVECTOR3& GetLightDir(int nLightType){return m_lightDir[nLightType];}
	void SetLightDir( int nLightType, const D3DXVECTOR3& vDir ){ m_lightDir[nLightType] = vDir; }
	D3DXCOLOR& GetLightAmbient(int nLightType){return m_lightAmbient[nLightType];}
	void SetLightAmbient(int nLightType, const D3DXCOLOR& ambColor){ m_lightAmbient[nLightType] = ambColor; }
	D3DXCOLOR& GetLightDiffuse(int nLightType){return m_lightDiffuse[nLightType];}
	void SetLightDiffuse(int nLightType, const D3DXCOLOR& diffColor){ m_lightDiffuse[nLightType] = diffColor; }
	D3DXCOLOR& GetLightSpecular(int nLightType){return m_lightSpecular[nLightType];}
	void LightEnable( int nLightID, BOOL bEnable );
	void SetViewMatrix( float* pMatrix );
	void SetEyePt( float* pEyePt );
	D3DXVECTOR3& GetEyePt(){return m_vEyePt;}
	void SetLookatPt( float* pLookatPt );
	void Flush( DWORD dwFlag );
	void FlushShadow( DWORD dwFlag );

	
	bool SetTextures( DWORD dwFlag, int nMainMapID, int nAddMapID, LPDIRECT3DTEXTURE9 d3dBrightTex, int nLightmapID = -1 );
	void SetRenderStatesWithFlag( DWORD dwFlag, DWORD dwFVF, int nMainMapID, int nAddMapID, int nLightmapID = -1 );

	inline void SetGlobalTransparent( float t );
	float GetGlobalTransparent() { return m_fGlobalTransparent; }
	inline void SetGlobalDiffuse( float r, float g, float b );
	inline void SetGlobalUOffset( int nLayer, float u  );
	inline void SetGlobalVOffset( int nLayer, float v  );

	void SetGlobalTexture( short shTextureID );
	short GetGlobalTexture();

	//////////////////////////////////////////////////////////////////////////
    CHRRenderSurface* GetCurrentSurface()
    {
        guardfunc;
        //CSALocker locker(this);
        return &m_Surfaces[m_nSurfaceCount];
        unguard;
    }

	BOOL ResetToDefaultState();
	inline void Commit();
	inline void MexCommit();

// 	LPDIRECT3DVERTEXDECLARATION9	m_pMexDecl;
// 	LPDIRECT3DVERTEXBUFFER9			m_pMexVB;
// 
// 	LPDIRECT3DVERTEXDECLARATION9	m_pUIDecl;
// 	LPDIRECT3DVERTEXBUFFER9			m_pUIVB;
// 	LPDIRECT3DINDEXBUFFER9			m_pUIIB;

	LONG CreateVertexBuffer( UINT Length,DWORD Usage,DWORD FVF,	DWORD Pool,VOID** ppVertexBuffer);
    LONG CreateIndexBuffer( UINT Length,DWORD Usage, DWORD Format,DWORD Pool,VOID** ppIndexBuffer);

    // add [5/28/2008 whu]
    virtual void EnableUseShader( bool enable ) { m_bUseShader = enable; }
    virtual bool EnableUseShader()  { return m_bUseShader; }

    virtual void SetShader( const std::string& name );
    virtual void SetShaderParameter( const ShaderParameter& param, bool append = false );

    virtual void RestoreDeviceObjects( void* pDevice );

// 	LPDIRECT3DVERTEXDECLARATION9 GetUIDecl();
// 	LPDIRECT3DVERTEXDECLARATION9 GetMexDecl();
// 	LPDIRECT3DVERTEXBUFFER9 GetMexVB(  );
// 	LPDIRECT3DVERTEXBUFFER9 GetUIVB(  );
// 	LPDIRECT3DINDEXBUFFER9 GetUiIB(  );
	virtual void InvalidateDeviceObjects();

    virtual void SetMaterial( graphics::Material* pMaterial );

    virtual void SetCurrentMaterial( graphics::Material* pMtrl );

	virtual graphics::Material* TerrainMaterial() const { return m_pTerrainMaterial; }
	virtual void		SetTerrainMaterial(graphics::Material* val);

	D3DXMATRIX& GetWorldMatrix() {return m_world;}
	D3DXMATRIX& GetViewMatrix() {return m_view;}
	D3DXMATRIX& GetProjectMatrix() {return m_proj;}
	D3DXMATRIXA16& GetWorldViewProjection() { return m_worldViewProj; }

	void SetShaderLevel( unsigned int uiLevel ){ m_uiShaderLevel = uiLevel; }
	const char* GetCurrentShaderLevelName();
	virtual void  SetLightMapTEnble(bool _b){ m_RenderTLightMap = _b ;}

public:
#ifdef USE_MANUAL_RS_MANAGED
	CD3DDeferredState			DeferredState;
#endif

	// Direct3D device info.
	D3DCAPS9						DeviceCaps8;
#define MAX_STATESTACKDEPTH	128
	FD3DSavedState			SavedStates[MAX_STATESTACKDEPTH];
	FD3DSavedState*			CurrentState;
	INT						SavedStateIndex;

	class FD3DDynamicVertexStream*		DynamicVertexStream;
	class FD3DDynamicIndexBuffer*			DynamicIndexBuffer16;
	class FD3DDynamicIndexBuffer*			DynamicIndexBuffer32;

	// Resource management.
	class FD3DResource*					ResourceList;
	class FD3DResource*					ResourceHash[4096];

protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	D3DMATERIAL9		m_DefaultMaterial;
	int					m_nSurfaceCount;
	CHRRenderSurface	m_Surfaces[eMaxSurface];
	int					m_nSortedSurfaceCount;
	CHRRenderSurface	m_SortedSurfaces[eMaxSurface];
	int					m_nNumEffectBuffer;
// 	CHREffectBuffer		m_EffectBufferList[eMaxEffectBuffer];

	DWORD				m_dwPolyType;
	D3DXMATRIX			m_matView;
	D3DXVECTOR3			m_vEyePt;
	D3DXVECTOR3			m_vLookatPt;
	D3DVIEWPORT9		m_CurViewport;

// 	CHRRenderBuffer		m_RenderBuffers[eMaxRenderBuffer];


	DWORD				m_dwTerrainALPHABLENDENABLE;
	DWORD				m_dwTerrainTexture0COLOROP;
	DWORD				m_dwTerrainTexture1COLOROP;

private:
	short	m_shGlobalTextureID;
	float	m_fGlobalTransparent;
	float	m_fGlobalDiffuse[3];
	float	m_fGlobalUOffset[eMaxTextureStage];
	float	m_fGlobalVOffset[eMaxTextureStage];

private:
	unsigned int m_uiShaderLevel;
	int		m_nDynamicVertexOffset;
	int		m_nMexVertexOffset;

	short m_shSaveShaderID;
    DWORD m_dwSaveFlag;

    // add [5/26/2008 whu]
    bool                    m_bSupportShader;
    bool                    m_bUseShader;
    IDirect3DVertexShader9* m_pSpecularVS;
    IDirect3DPixelShader9*  m_pSpecularPS;
    IDirect3DPixelShader9*  m_pSpecularAndAnimPS;
    IDirect3DPixelShader9*  m_pBrightPS;
    ID3DXConstantTable*     m_pSpecularVSCT;
    ID3DXConstantTable*     m_pSpecularPSCT;
    ID3DXConstantTable*     m_pSpecularAndAnimPSCT;
    ID3DXConstantTable*     m_pBrightPSCT;
    IDirect3DVertexShader9* m_pCurrentVS;
    IDirect3DPixelShader9*  m_pCurrentPS;
    ID3DXConstantTable*     m_pCurrentVSCT;
    ID3DXConstantTable*     m_pCurrentPSCT;

    // transform.
    D3DXMATRIX m_world;
    D3DXMATRIX m_view;
    D3DXMATRIX m_proj;
	D3DXMATRIXA16 m_worldViewProj;
	D3DXMATRIXA16 m_ViewProj;

    // material.
    D3DXCOLOR m_globalAmbient;
    D3DXCOLOR m_ambient;
    D3DXCOLOR m_diffuse;
    D3DXCOLOR m_specular;

    // light.
    bool  m_bLighting;
	D3DXVECTOR3 m_lightDir[LIGHT_INDEX_COUNT];
    D3DXCOLOR m_lightAmbient[LIGHT_INDEX_COUNT];
    D3DXCOLOR m_lightDiffuse[LIGHT_INDEX_COUNT];
    D3DXCOLOR m_lightSpecular[LIGHT_INDEX_COUNT];

    // animation texture.
    IDirect3DTexture9* m_pAnimationTex;

    // shader
    std::string     m_shaderName;
    ShaderParameter m_shaderParam;

    graphics::Material* m_pCurrentMaterial;

	ID3DXEffect* m_d3dTerrainEffect;
	graphics::Material* m_pTerrainMaterial;

	graphics::Material* m_pMexMaterial;
	LPDIRECT3DINDEXBUFFER9 m_LastTerrainIndexBuffer ;

	//lyh++ lightMap shader render
	bool     m_RenderTLightMap;
};

extern FEngineState		GEngineState;

#include "RendererDX.inl"

//
//namespace ModelRenderHelper
//{
//	extern std::vector<IRenderer*>	m_HRRenderer;
//};
