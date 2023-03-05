/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CWSRender.h
* Create: 	10/07/06
* Desc:		实现渲染功能
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __WS_RENDER_H__
#define __WS_RENDER_H__

#include <vector>
//#include <NiRenderer.h>
#include "MeTerrain/SwType.h"
#include "MeTerrain/SwRender.h"
#include "Me3d/Engine/Frustum.h"
//#include "SwAccumulator.h"
#include "Array.h"

class CWorld;
class CWorldTile;
class CWorldChunk;
class TObjectInfo;
class Mex2GeoChunk;
// struct CombineModelData;
struct Mex2Face;
#define CHUNK_LEVEL_MAX	150
#define CHUNK_LEVEL_STEP 0.0625f // 等于1/16.f，每级间隔距离16米
struct swDecalShapeVertex;

class CWSRender/*	: public NiRefObject*/ : public SwRender
{
public:
	CWSRender();
	CWSRender(int nScreenWidth, int nScreenHeight);

	virtual void				Initialize( int nScreenWidth, int nScreenHeight );
	virtual				~CWSRender();

	// 渲染游戏场景
	virtual void		RenderWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 CameraPos, float totalTime, float deltaTime,bool isRenderEffect = true );	// 渲染游戏场景主体函数

	// Light
	virtual void				UpdateFarFog( float fFarPlane );	// 相机far plane修改，雾距离做相应调整
	virtual float				GetModelCullFar();

	virtual void				OnDeviceLost();
	virtual void				OnDeviceReset();
	virtual float				GetRealDoodadShowInstance();

protected:
	// 渲染游戏场景
	virtual void		CullingWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 cameraPos );						// 对CWorld进行可见判断并渲染

	virtual void		RenderModel( CWorldChunk*  chunk, CWorldTile*  cachTile, FrustumEx& frustum, D3DXVECTOR3 cameraPos );
	// 相同贴图子模型合并
public:
	virtual void                CombineShadowDecal( swDecalShapeVertex* pVertex, int iVertexCount, unsigned short* pIndex, int iFaceCount, int iTexId );
    void                StartCombineShadowDecal();
    void                EndCombineShadowDecal();
    void                RenderCombineShadowDecal();
protected:
	void				InitCombineBuff();
	bool				AllocCombineBuff( long lVertexNum, long lFaceNum );
	void				ReleaseCombineBuff();
	bool				m_bNeedInitCombineBuff;
	UINT				MAX_VERTEX;
	UINT				MAX_FACES;
	LPDIRECT3DVERTEXBUFFER9 m_pCombineVB;
	LPDIRECT3DINDEXBUFFER9 m_pCombineIB;
    // 合并影子贴花前先Lock Vertex Buffer和Index Buffer
    MexVertex*          m_pLockVBVertex;
    short*              m_shLockIBFace;
    long                m_lCombineShadowVertexCount;
    long                m_lCombineShadowFaceCount;
    int                 m_iCombineShadowTexId;
	float				m_fDoodadShowDistance;

	virtual	bool		IsNeedCull(CWorldTile* worldTile,FrustumEx& FrustumEx);
	virtual void		AddLiquidChunk( CWorldChunk * chunk, D3DXVECTOR3 &cameraPos, float fLiquidFar, float fMinLiquidHeightToCamera );
	virtual void		CheckLODAndDoodad( CWorldChunk* chunk, D3DXVECTOR3 cameraPos, CWorldTile* worldTile);
};

#endif //__WS_RENDER_H__