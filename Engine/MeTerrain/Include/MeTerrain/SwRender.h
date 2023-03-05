/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwRender.h
* Create: 	10/07/06
* Desc:		实现渲染功能
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWRENDER_H__
#define __SWRENDER_H__

#include <vector>
//#include <NiRenderer.h>
#include "MeTerrain/SwType.h"
#include "Me3d/Engine/Frustum.h"
//#include "SwAccumulator.h"
//#include "Core/Array.h"

class CWorld;
class CWorldTile;
class CWorldChunk;
class TObjectInfo;
class Mex2GeoChunk;
struct CombineModelData;
struct Mex2Face;
#define CHUNK_LEVEL_MAX	150
#define CHUNK_LEVEL_STEP 0.0625f // 等于1/16.f，每级间隔距离16米
struct swDecalShapeVertex;

typedef void ( *ShadowMapShaderSetCallBack )( bool bTerrainShadow );

class SwRender
{
public:
	SwRender();
	SwRender(int nScreenWidth, int nScreenHeight);

	virtual void				Initialize( int nScreenWidth, int nScreenHeight );
	virtual				~SwRender();
	void				Destroy();
	void				AdjustWindowSize( int width, int height );

	// 渲染游戏场景
	void				RenderSkyBox( CWorld* world, D3DXVECTOR3& vPos );	
	void				RenderSkyBoxWithZ( CWorld* world, D3DXVECTOR3& vPos );	
	virtual void				RenderWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 CameraPos, float totalTime, float deltaTime,bool isRenderEffect = true );	// 渲染游戏场景主体函数
	void				RenderLiquid_High( );
	void				RenderLiquid( );
	void				RenderLiquidReflect(MeCamera* pCamera, float fFov, D3DXVECTOR3& vPos, CWorld* world, float totalTime, float deltaTime);
	void				RenderLiquidRefract(MeCamera* pCamera, float fFov, D3DXVECTOR3& vPos, CWorld* world, float totalTime, float deltaTime);
	void				RenderEffect( bool bOverUI = false );//add by jiayi,[09.03.16]

	void				UnlockModelRes();
	bool				IsModelResUnlock();

	/*
	 * 2012.6.26 wangshuai
	 * saveToFile为false时, 直接渲染
	 */
	void				GenerateMinimap( CWorldTile *worldTile, sInt32 size, const char *fileName, bool saveToFile = true );
	void                GenerateLightView( CWorldTile *worldTile, sInt32 size, D3DMATRIX &outMat_LightWVP, bool saveToFile , bool OnlyCal = false );
	

	// added, jiayi, [2009.4.21]
	void				RenderTerrainShadow(const D3DXVECTOR3& cameraPos, float renderDistance = 100.0f);
	void				RenderModelShadow();

	// Light
	void				SetDefaultLight();
	D3DLIGHT9			GetD9Light() const { return m_kD9Light; }

	void				InitDefaultLight();
	void				SetLightDir( const Vector& dir );
	void				SetLightAmbientColor( const NiColor& ambient );
	void				SetLightDiffuseColor( const NiColor& diffuse );
	void				SetLightSpecularColor( const NiColor& specular );
	void				SetFogColor( const NiColor& fogColor );
	void				SetFogDepthByCommand( flt32 fogNear, flt32 fogFar );
	void				SetFogDepth( flt32 fogNear, flt32 fogFar );

	void				SetRenderFog( flt32 fogNear, flt32 fogFar );

	bool				IsDisplayAnimation() const { return m_isDisplayAnimation; }
	bool				GetRenderDoodad() const {return m_isDisplayDoodad;};
	void				SetRenderDoodad( bool isDisplayDoodad = true )		{ m_isDisplayDoodad = isDisplayDoodad; };	
	void				SetShowAnimation( bool isShowZone );

	void				SetViewblockAlpha(float alpha) {if(alpha>=0.f && alpha<=1.f) m_fViewblockAlpha = alpha;};

	int					GetFrames()					{ return m_nFrames; }
	bool				IsHardwareInstancing() const { return m_bHardwareInstancing; }

	// 获取渲染统计数据
	int					GetModelCount(){ return m_nModelCount; };
	int					GetSubmodelCount() { return m_nSubmodelCount; };
	int					GetModelVertexCount(){ return m_nModelVertexCount; };
	int					GetModelFaceCount(){ return m_nModelFaceCount; };
	int					GetChunkCount(){ return m_nChunkCount; };
	int					GetChunkVertexCount(){ return m_nChunkVertexCount; };
	int					GetChunkFaceCount(){ return m_nChunkFaceCount; };
	WORD				GetModelRenderTime(){ return m_dModelRenderTime; };
	WORD                GetSceneModeRealRenderTime(){return m_SceneModeRealRenderTime;}
	WORD				GetTotalRenderTime(){ return m_dTotalRenderTime; };
	WORD				GetChunkRenderTime(){ return m_dChunkRenderTime; };
	WORD				GetDoodadRenderTime(){ return m_dDoodadRenderTime; };
	int					GetEffectCount() { return m_nEffectCount; }
	WORD				GetEffectRenderTime() { return m_dEffectRenderTime; }
	void				SetWireFrame(bool val) { m_isWireFrame = val; }
	float				GetFarPlane() const;
	void				SetFarChunk(	float nFarChunk );
	float				GetFarChunk() const ;
	float				GetNearPlane() const { return m_fNearPlane; }
	FogProperty*		GetFogProperty() {return &m_fogProp;};
	void				EnableFog(bool bEnable) { m_fogProp.bShowFog = bEnable; };
	virtual void				UpdateFarFog( float fFarPlane );	// 相机far plane修改，雾距离做相应调整
	virtual float				GetModelCullFar();
	float				GetNearestLiquidHeight() { return m_fLiquidHeight; }
	void				ResetFarplane();

	virtual void				OnDeviceLost();
	virtual void				OnDeviceReset();
	void				SetCulledEnable(bool bFlag) {m_bCulledEnable = bFlag;}
	void				SetNeedFade( bool bFade ){ m_bNeedFade = bFade ; }
	virtual float				GetRealDoodadShowInstance();
	void				SetLockMaxTime( DWORD dwMaxTime ){ m_dwLockMaxTime = dwMaxTime ; }
	virtual void        CombineShadowDecal( swDecalShapeVertex* pVertex, int iVertexCount, unsigned short* pIndex, int iFaceCount, int iTexId );
	void				RenderDoodad();
	bool                m_BRenderDepth;  //lyh+++ 是否绘制深度

		ShadowMapShaderSetCallBack m_ShadowMapShaderSetCallBack; 
	
protected:
	// 渲染游戏场景
	virtual void		CullingWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 cameraPos );						// 对CWorld进行可见判断并渲染

	virtual void		CheckLODAndDoodad( CWorldChunk* chunk, D3DXVECTOR3 cameraPos, CWorldTile* worldTile);
	virtual void		AddLiquidChunk( CWorldChunk * chunk, D3DXVECTOR3 &cameraPos, float fLiquidFar, float fMinLiquidHeightToCamera );
	virtual void		RenderModel( CWorldChunk*  chunk, CWorldTile*  cachTile, FrustumEx& frustum, D3DXVECTOR3 cameraPos );


	void				UpdateLight();
	void				ClearStatistic();
	bool				IsObjectVisible( SBBox& Box, FrustumEx& kFrustumEx );
	void				CalTextureLOD(CWorldChunk* pChunk,float camera2chunk);
	void				RenderDoodad(CWorldChunk*  chunk);
	//void				RenderDoodad();
	D3DLIGHT9			m_kD9Light;
	bool				m_bLightDiffer;
	int					m_screenWidth;
	int					m_screenHeight;

	uInt16				m_renderCounter;		//渲染Id，每过一帧自动+1，用以和model->renderCounter判断，取消重复渲染

	flt32				m_curTime;
	flt32				m_deltaTime;

	bool				m_isDisplayAnimation;
	bool				m_isDisplayDoodad;
	DWORD				m_dwLockMaxTime;

	float				m_fViewblockAlpha;		// 模型遮挡人物时，半透alpha值，从配置文件读取

	int					m_nFrames;				// 记录当前帧，用于绘制时重复物体检查

	bool				m_bHardwareInstancing;
	bool				m_bCulledEnable;
	std::vector<CWorldChunk*> m_vctRenderChunkList;
	std::vector<CWorldChunk*> m_vctRenderLiquidChunkList;
	std::vector<TObjectInfo*> m_vctRenderModelList;
	std::vector<MexAnimCtrl*> m_vctRenderEffect;
	std::vector<CWorldChunk*> m_vctRenderDoodadChunkList;


	std::vector<CWorldChunk*> vctChunkList;
	bool						m_bRenderEffect;

	//typedef std::vector<CWorldChunk*> vectorChunk;
	//Array<vectorChunk, CHUNK_LEVEL_MAX> m_arrRenderChunks;

	//typedef std::vector<TObjectInfo*> vectorModel;
	//Array<vectorModel, CHUNK_LEVEL_MAX> m_arrRenderModels;

	int					m_nModelCount;
	int					m_nEffectCount;
	int					m_nSubmodelCount;
	int					m_nModelFaceCount;
	int					m_nModelVertexCount;
	int					m_nChunkCount;
	int					m_nChunkFaceCount;
	int					m_nChunkVertexCount;
	WORD				m_dModelRenderTime;
	WORD				m_dEffectRenderTime;
	WORD				m_dDoodadRenderTime;
	WORD				m_dChunkRenderTime;
	WORD				m_dTotalRenderTime;
	bool				m_isDisplayLiquid;
	bool				m_isWireFrame;
	float				m_fNearPlane;
	// 雾信息
	FogProperty			m_fogProp;
	float				m_farChunk;
	// 渲染的水高度
	float				m_fLiquidHeight;
	// 是否渐变渲染
	bool				m_bNeedFade;

	bool				m_bNeedUpdateModel ;

	virtual		bool		IsNeedCull(CWorldTile* worldTile,FrustumEx& FrustumEx){return true;}

	bool*				m_bDoodadRenderFlag;
	int					m_nDoodadRenderFlagNumber;
    WORD               m_SceneModeRealRenderTime; //LYH++ 场景mode渲染时间

};

#endif //__SWRENDER_H__