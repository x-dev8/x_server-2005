/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CWSRender.h
* Create: 	10/07/06
* Desc:		ʵ����Ⱦ����
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
#define CHUNK_LEVEL_STEP 0.0625f // ����1/16.f��ÿ���������16��
struct swDecalShapeVertex;

class CWSRender/*	: public NiRefObject*/ : public SwRender
{
public:
	CWSRender();
	CWSRender(int nScreenWidth, int nScreenHeight);

	virtual void				Initialize( int nScreenWidth, int nScreenHeight );
	virtual				~CWSRender();

	// ��Ⱦ��Ϸ����
	virtual void		RenderWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 CameraPos, float totalTime, float deltaTime,bool isRenderEffect = true );	// ��Ⱦ��Ϸ�������庯��

	// Light
	virtual void				UpdateFarFog( float fFarPlane );	// ���far plane�޸ģ����������Ӧ����
	virtual float				GetModelCullFar();

	virtual void				OnDeviceLost();
	virtual void				OnDeviceReset();
	virtual float				GetRealDoodadShowInstance();

protected:
	// ��Ⱦ��Ϸ����
	virtual void		CullingWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 cameraPos );						// ��CWorld���пɼ��жϲ���Ⱦ

	virtual void		RenderModel( CWorldChunk*  chunk, CWorldTile*  cachTile, FrustumEx& frustum, D3DXVECTOR3 cameraPos );
	// ��ͬ��ͼ��ģ�ͺϲ�
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
    // �ϲ�Ӱ������ǰ��Lock Vertex Buffer��Index Buffer
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