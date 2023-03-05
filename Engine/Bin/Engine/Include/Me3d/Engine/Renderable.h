#pragma once
#include "Dxsdk/d3dx9.h"
#include "Me3d/Vector.h"
#include "MeFoundation/MeAllocatedObject.h"
//#include "Me3d/Engine/MeRenderObject.h"
#include "Me3d/Engine/RenderParam.h"

class IMex;
class IReplaceableTextureProj;
class Mex2GeoChunk;
class MexReplaceableTextureProj;
#define Simple2DVertex_FVF (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
struct Simple2DVertex
{
	D3DXVECTOR4 p;
	DWORD		color;
	float		u, v;
};
// struct ModelVertex
// {
// 	D3DXVECTOR3	p;			// 12byte
// 	D3DXVECTOR3 n;			// 12byte
// 	DWORD		color;		// 4 byte
// 	float		u, v;		// 8 byte
// 	float		u1,v1;		// 8 byte
// };
struct Mex2Face : public MeCommonAllocObj<Mex2Face>
{
	short nId[3];
};

// struct CombineModelData
// {
// 	Mex2GeoChunk* pSubmodel;
// 	float fu;
// 	float fv;
// 	DWORD dwFlag;			// 渲染flag必须一致
// 	short stUseLuminanceTexId;	// 流光图一致
// 	DWORD dwColor;
// 	int nTileFrameId;
// 	int nUTiles;
// 	int nVTiles;
// 	INT nSpecularTexID;
// 	graphics::Material* material;
// 	float* pMatrix;
// 	IMex* pMex;
// };

// struct RenderParams
// {
// 	IMex* pMex;
// 	float* pMatrices;
// 	IRenderer* pRenderer;
// 	IReplaceableTextureProj* pReplaceableTextureProj; 
// 	float fAlpha;
// 	bool bMustUseAlphaBlend;
// 	bool useAnim;	
// 	INT nSpecularTexID;
// // 	std::map<int, std::vector<CombineModelData>>* mapCombineSubmodel;
// 	graphics::Material* material;
// 	int nFrameId;
// 	// added, jiayi, [2010/6/10]
// 	DWORD dwFlag;
// 	short stUseTexId;
// 	short stUseLuminanceTexId;
// 	float fGlobalAlpha;
// 	float fDistanceToEye;
// 	bool m_bIsRenderModelSelected;//added yd
// 	bool m_bNoSort;//added yd
// 	RenderParams() : pMex(0), pMatrices(0),
// 		pRenderer(0),pReplaceableTextureProj(0), fAlpha(1),
// 		bMustUseAlphaBlend(0),useAnim(0),nSpecularTexID(-1),
// 		material(0), nFrameId(-1),
// 		dwFlag(0), stUseTexId(-1), stUseLuminanceTexId(-1),
// 	fGlobalAlpha(1),m_bIsRenderModelSelected(false),fDistanceToEye(0.f),m_bNoSort(false)
// 	{}
// 
// 	// 保存_Render信息
// 	typedef std::vector<RenderParams> OtherInfos;
// 	typedef OtherInfos::iterator OtherInfosIter;
// 	typedef OtherInfos::const_iterator OtherInfosConstIter;
// };


class IRenderable
{
public:
	IRenderable(){};
	virtual ~IRenderable(){};

// 	virtual IRenderable*	Clone( DWORD dwFlag ) = 0;

	virtual bool Render( RenderParams* params,
        DWORD dwFlag = 0,
        IReplaceableTextureProj* pLuminanceTextureProj = NULL,
		int* pVertexCount=NULL,
		int* pFaceCount=NULL) = 0;

// 	virtual void FastRender( IMex* pMex,
// 		float* pfMatrices,
// 		IRenderer* pRenderer,
// 		IReplaceableTextureProj* pReplaceableTextureProj,
// 		float fAlpha,
// 		bool bMustUseAlphaBlend,int nFrameId,
// 		DWORD dwFlag = 0 ) = 0;

	virtual void	RenderShadow( IMex* pMex, 
		float* pfMatrices,
		IRenderer* pRenderer, 
		IReplaceableTextureProj* pReplaceableTextureProj, 
		float fAlpha, 
		bool bMustUseAlphaBlend,int nFrameId,
		DWORD dwFlag = 0 ) = 0;

	virtual bool	BlendVertex(IMex* pMex, float* pMatrices) = 0;	// 模型local坐标转换为世界坐标
	virtual bool	BlendVertex( float* pBlendedVertices, float* pBlendedNormals, int nMaxVertexCount, IMex* pMex, float* pMatrices ,MeMatrix* pTmpMatrices) = 0;

	virtual int		GetVertexCount() = 0;
	virtual void	SetVertexCount( int nVertexCount ) = 0;
	virtual int		GetFaceCount() = 0;
	virtual void	SetFaceCount( int nFaceCount ) = 0;
 	virtual Vector*	GetVerticesLocked() = 0;
	virtual void	UnlockVertices() = 0;
	virtual void	SetVertices( float* pfVertices ) = 0;
// 	virtual Vector*	GetNormalsLocked() = 0;
	virtual void	SetNormals( float* pfNormals ) = 0;
 	virtual Vector2*	GetUVsLocked( int nLayer ) = 0;
	virtual void	UnlockUVs(int nLayer) = 0;
	virtual void	SetUVs( int nLayer, float* pfUVs ) = 0;
	virtual Vector2* GetUVs( int nLayer = 0 ) = 0;
// 	virtual DWORD*	GetDiffuse() = 0;
	virtual void	SetDiffuse( DWORD* pdwDiffuse ) = 0;
    virtual Mex2Face*	GetIndicesLocked() = 0;
	virtual void	UnlockIndices() = 0;
	virtual void	SetIndices( WORD* pwIndices ) = 0;
	virtual BYTE*	GetBoneGroupIndices() = 0;
	virtual void	SetBoneGroupIndices( BYTE* pbyBoneGroupIndices ) = 0;
	virtual int		GetMtlId() = 0;
	virtual DWORD	GetType() = 0;
	//virtual int		GetRenderTextureID() = 0;

	virtual void	SetUVLayerCount( short nLayerCount ) = 0;
	virtual short	GetUVLayerCount() = 0;

	virtual void	SetLightmapLayer( short layer ) = 0;
	virtual short	GetLightmapLayer() = 0;

	virtual bool	IntersectQuick( Vector* pvStart, Vector* pvDir, MexReplaceableTextureProj* replaceableTexture, D3DXMATRIX* pModelInverseMatrix ) = 0;


	virtual const char* GetName() = 0;

	// added, jiayi, [2010/5/14]
	// 判断是否具有相同贴图
	virtual bool	HaveSameTextures( const IRenderable* pObject ) const = 0;

	//virtual void	SetRenderSetting( IRenderableSetting* pSetting ) = 0;
	//virtual void	GetRenderSetting( IRenderableSetting* pSetting ) = 0;
	virtual void	SetAvatarComponent() = 0;
	virtual bool	IsAvatarComponent() = 0;
};