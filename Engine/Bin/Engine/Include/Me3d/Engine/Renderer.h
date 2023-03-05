#pragma once
#include "Dxsdk/D3D9.h"
#include "Dxsdk/d3d9types.h"
#include "Me3d/Vector.h"
#include <string>
#include <map>

// add [6/4/2008 whu]
namespace graphics
{
    class Material;
}
class ITexture;
class CHRRenderSurface;
struct MexVertex
{
	float x,y,z;
	float nx,ny,nz;
	DWORD diff;
	float u,v;
};

struct UIVertex
{
	float x,y,z,w;
	float diff;
	float u,v;
};

enum eDirectPushSurfaceType
{
	eDPST_MexVertex = 1,
	eDPST_UIVertex = 2,
	eDPST_TerrainVertex = 3,
};

enum eRenderFlag
{
	eWireFrame		= 1<<0,
	eAlphaBlend		= 1<<1,
	eLinearFilter	= 1<<2,
	eSortByFarZ		= 1<<3,

	eDstBlendOne	= 1<<4,
	eUseTextureColor= 1<<5,
	eZFunLess		= 1<<6,
	eNotUseSkinMesh	= 1<<7,

	eOpModulate1X	= 1<<8,
	eOpModulate2X	= 1<<9,
	eOpModulate4X	= 1<<10,
	eOpAdd			= 1<<11,

	eGlobalTransparent = 1<<12,
	eNeetNotDraw	= 1<<13,

	eRenderTreeLeaf = 1<<14,
	eRenderSkyBox	= 1<<15,

	//eNeedNotSetIB	= 1<<14,
	//eNeedNotSetVB	= 1<<15,
	eUseVB			= 1<<16,
	eUseIB			= 1<<17,
	eShimmer		= 1<<18,// modified, jiayi, [2010/6/18],eIsTerrain
	eNeedNotSetTexture = 1<<19,
	eSpecularEnable = 1<<20,

// 	eOpBlendTexutrueAlpha = 1<<21,
// 
// 	eMipmapShiftForBlur = 1<<22,
	eUClamp			= 1<<21,
	eVClamp		    = 1<<22,
	eZDisable		= 1<<23,
	eZWriteDisable	= 1<<24,
	ePointFilter	= 1<<25,
	eAlphaTest		= 1<<26,
	eCullCCW		= 1<<27,
	eTwoSided		= 1<<28,
	//eLightingEnable	= 1<<29,
	eLightingDisable = 1<<29,
	eMipmapLinear	= 1<<30,
	eNoMipmap		= 1<<31,
	
};
enum
{


	//terrain shader
	TERRAIN_NORMAL,
	TERRAIN_BLEND,
	TERRAIN_GRID,
	TERRAIN_LIGHTMAP,

	TERRAIN_BASEGROUND,
	TERRAIN_SPLATTING,

	TERRAIN_SKYBOX,

	// ui shader
// 	UI_SHADER,
	OBJECT2D_SHADER,

	//   added 2003.08.28
	MEX2_SHADER,
	WALKMASK_RENDER,

	// Human
// 	TERRAIN_NOTTEXTURE,

	// coli., floor.
	HELP_COLI_FLOOR,

	// particle
	MEX2_PARTICLE,

	SHADER_MAX
};

// Primitive types for DrawPrimitive.
enum EPrimitiveType
{
	PT_TriangleList,
	PT_TriangleStrip,
	PT_TriangleFan,
	PT_PointList,
	PT_LineList
};

class IRenderer
{
protected:
    void* m_device;

public:
    IRenderer() : m_device(0) {}
	virtual ~IRenderer(){};

	virtual void SetDevice( void* pDevice ) = 0;
	virtual void* GetDevice() = 0;
    void* GetRealDevice() { return m_device; }
	virtual void SetTexture( DWORD dwStage, void* pTexture ) = 0;
	virtual void SetTextureHardware( DWORD dwStage, void* pTexture ) = 0;
	virtual void SetFVF( DWORD dwShader ) = 0;
	virtual void SetRenderState( DWORD dwState, DWORD dwValue ) = 0;
	virtual void SetTextureStageState( DWORD dwStage, DWORD dwType, DWORD dwValue ) = 0;
    virtual void  SetLightMapTEnble(bool _b) = 0;
	
#ifndef NEW_RESMGR
	virtual void SetIndices( void* IndexData, DWORD BaseVertexIndex ) = 0;
	virtual void SetStreamSource( DWORD StreamNumber, void* StreamData, DWORD StreamStride ) = 0;
#else
	virtual void SetIndices(FIndexBuffer* IndexBuffer,INT BaseVertexIndex);
	virtual void SetStreamSource( DWORD StreamNumber, class FVertexStream* StreamData, DWORD StreamStride ) = 0;
#endif
	// 设置顶点
	virtual void SetVertices( void* pVertices ) = 0;
	// 设置法线
	virtual void SetNormals( void* pNormals ) = 0;
	// 设置顶点色
	virtual void SetDiffuse( void* pDiffuse ) = 0;
	// 设置面索引
	virtual void SetIndices( void* pIndices ) = 0;
	// 设置顶点索引
	virtual void SetIB( LPDIRECT3DINDEXBUFFER9 pIB ) = 0;
	// 设置贴图坐标，
	virtual void SetUVs( void* pUVs, int nLayer ) = 0;
	//
	virtual void SetLayerCount( int nLayerCount ) = 0;
	//
	virtual void SetShaderId( short shShaderId ) = 0;

	// 设置贴图
	virtual void SetTextureId( short shTextureId, int nLayer ) = 0;
	// 设置顶点格式
	virtual void SetSurfaceFVF( DWORD dwFVF ) = 0;
	// 设置顶点跨踞
	virtual void SetVertexStride( int nStride ) = 0;
	// 设置材质
	virtual void SetMaterial( BYTE* pbyMtl ) = 0;
	//
	virtual void SetDefaultMaterial( BYTE* pbyMtl ) = 0;

	virtual void GetDefaultMaterial( BYTE* pbyMtl ) = 0;
	// 
	virtual void SetMtlSpecular( float power, float a, float r, float g, float b ) = 0;
	//
	virtual void EnableSpecular( BOOL bEnable ) = 0;
	// 绘图
// 	virtual void Push( int nVertexCount, int nFaceCount, DWORD dwFlag ) = 0;
// 	// 直接Push一个Surface
// 	virtual void PushSurface(	short nMainMapID, 
// 								short nAddMapID, 
// 								short nShaderID,			// 贴图/Shader
// 								DWORD dwFvf,
// 								UINT nStride, 
// 								BYTE *pVertices, 
// 								WORD nVertCount,	// 顶点信息
// 								BYTE * pIndeices, 
// 								WORD nTriangleCount, 
// 								DWORD dwFlag,
// 								DWORD dwPolyType = D3DPT_TRIANGLELIST
// 								) = 0;


	virtual bool BeginDirectPushSurface(short nMainMapID,
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
		Vector2* pvLightmapUVOffset = NULL
		) = 0;


	virtual void DoDirectPushSurface(UINT nVertCount,
		UINT nTriangleCount,
		DWORD dwPolyType = D3DPT_TRIANGLELIST,
		INT nIBOffset = 0)= 0;

	virtual void EndDirectPushSurface()= 0;

	virtual void DirectPushSurface(	short nMainMapID,
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
                                    short nLuminanceMapID = -1 ) = 0;


// 	virtual void SetLOD2Color(float * color  ) = 0;
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
		) = 0;
	virtual void RenderTerrainLOD2WithShader(UINT nStride,
		LPDIRECT3DVERTEXBUFFER9 pVertices,
		WORD nVertCount,
		LPDIRECT3DINDEXBUFFER9 pIndeices,
		WORD nTriangleCount 
		) = 0;
// 	virtual void PrepareModelShader() = 0 ; 
	virtual void PrepareTerrainShader(bool bDepth) = 0;
	virtual void EndShader() = 0;
	virtual void PrepareTerrainLOD2Shader() = 0;
	virtual void EndLOD2Shader() = 0;
	virtual void RenderLiquidWithShader(
		short nLiquidTextureID,
		UINT nStride,
		BYTE *pVertices,
		WORD nVertCount,
		BYTE *pIndeices,
		WORD nTriangleCount
		) = 0;

	virtual void RenderLiquidWithShader_High(
		short nLiquidTextureID,
		UINT nStride,
		BYTE *pVertices,
		WORD nVertCount,
		BYTE *pIndeices,
		WORD nTriangleCount) = 0;

	virtual void PrepareLiquidShader() = 0;
	virtual void PrepareLiquidShader_High() = 0;


// 	virtual MexVertex* LockMexVB( int nVertCount, int& nBaseVertexIndex ) = 0;
// 	virtual void UnlockMexVB() = 0;

// 	virtual void BeginFastRenderMex() = 0;
// 	virtual void EndFastRenderMex() = 0;


// 	virtual void FastRenderMex(	short nMainMapID,
// 		short nAddMapID,
// 		WORD nVertCount,
// 		BYTE *pIndeices,
// 		WORD nTriangleCount,
// 		DWORD dwFlag,
// 		D3DMATERIAL9* mtrl,
// 		INT nVBOffset = 0 ) = 0;




	virtual DWORD SetViewport ( VOID* pViewport) = 0;
	virtual DWORD BeginScene() = 0;
	virtual VOID  EndScene() = 0;
	virtual DWORD Clear ( DWORD Count, DWORD Flags,DWORD Color,float Z,DWORD Stencil) = 0;
	virtual void SetTransform( DWORD State,CONST FLOAT* pMatrix) = 0;
	virtual void DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,	UINT PrimitiveCount) = 0;
	virtual void DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) = 0;
	//
	virtual void SetLight( int nLightID, void* pLight ) = 0;
	virtual void LightEnable( int nLightID, BOOL bEnable ) = 0;

	//
	virtual void SetViewMatrix( float* pMatrix ) = 0;
	//
	virtual void SetEyePt( float* pEyePt ) = 0;
	virtual void SetLookatPt( float* pLookatPt ) = 0;
	// 真正绘图
	virtual void Flush( DWORD dwFlag ) = 0;
	virtual void FlushShadow( DWORD dwFlag ) = 0;

	virtual void SetGlobalTexture( short shTextureID ) = 0;
	virtual short GetGlobalTexture() = 0;
	// 功能性函数
	// 设置整体透明度
	virtual void SetGlobalTransparent( float t ) = 0;
	// 设置整体颜色
	virtual void SetGlobalDiffuse( float r, float g, float b ) = 0;
	// 设置整体uv偏移
	virtual void SetGlobalUOffset( int nLayer, float u ) = 0;
	virtual void SetGlobalVOffset( int nLayer, float v ) = 0;
	
	virtual LONG CreateVertexBuffer( UINT Length,DWORD Usage,DWORD FVF,	DWORD Pool,VOID** ppVertexBuffer) = 0;
	virtual LONG CreateIndexBuffer( UINT Length,DWORD Usage, DWORD Format,DWORD Pool,VOID** ppIndexBuffer) = 0;

	virtual void SetSamplerState( DWORD dwStage, DWORD dwType, DWORD dwValue ) = 0;
    virtual void Commit() = 0;
	virtual void MexCommit() = 0;

    // add [5/28/2008 whu]
    virtual void EnableUseShader( bool enable ) = 0;
    virtual bool EnableUseShader() = 0;

    typedef std::map< std::string, float > ShaderParameter;
    virtual void SetShader( const std::string& name ) = 0;
    virtual void SetShaderParameter( const ShaderParameter& param, bool append = false ) = 0;

    virtual void RestoreDeviceObjects( void* pDevice ) = 0;
    virtual void InvalidateDeviceObjects() = 0;

    virtual void SetMaterial( graphics::Material* pMaterial ) = 0;

	virtual graphics::Material* TerrainMaterial() const =0;
	virtual void		SetTerrainMaterial(graphics::Material* val)=0;

	virtual void SetShaderLevel( unsigned int uiLevel ) = 0;
	virtual const char* GetCurrentShaderLevelName() = 0;
};

//
//	FRenderResource
//	Abstract rendering resource interface.
//
class FRenderResource
{
public:

	virtual DWORD GetCacheId() = 0;
	virtual INT GetRevision() = 0;
};

//
//	FVertexStream
//	Abstract vertex stream interface.
//
class FVertexStream : public FRenderResource
{
public:

	virtual INT GetStride() = 0;
	virtual INT GetSize() = 0;

	//virtual INT GetComponents(DWORD Components) = 0;
	virtual DWORD GetFVF() = 0;

	virtual void GetStreamData(void* Dest) = 0;
	virtual void GetRawStreamData(void ** Dest, INT FirstVertex ) = 0;
};

//
//	FIndexBuffer
//	Abstract index buffer interface.
//
class FIndexBuffer : public FRenderResource
{
public:

	virtual INT GetSize() = 0;

	virtual void GetContents(void* Data) = 0;

	virtual INT GetIndexSize() = 0;
};