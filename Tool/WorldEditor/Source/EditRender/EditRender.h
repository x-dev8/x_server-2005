#ifndef __EDIT_RENDER_H__
#define __EDIT_RENDER_H__
#include "MeTerrain/SwRender.h"
class CWorld;
class CWorldChunk;
class CEditCamera;
class SwCamera;
////////////////////////////////////////////////////////////////////////////////
class CEditRender	: public SwRender
{
public:
						CEditRender();
	virtual				~CEditRender();
						
	void				Destroy();

	//void				RenderBgndNode( NiNode* pNode );

	void				RenderLiquidReflect(SwCamera* pCamera, float fFov, D3DXVECTOR3& vPos, CWorld* world, float totalTime, float deltaTime);
						// 渲染 NiNode, pCamera 为空表示采用默认摄像机
	void				SetBgndColor( const NiColor& color );
						
	void				SetVertFrame( bool isVertframe = true );
	bool				IsWireframe();
	void				SetMesh( bool isMesh = true )	{ m_isMesh = isMesh; };
	void				SetBoundWireframe( bool isBoundWireframe = true )	{ m_isBoundWireframe = isBoundWireframe; };
	void				SetRenderLiquid( bool isDisplayLiquid = true )		{ m_isDisplayLiquid = isDisplayLiquid; };
	void				SetRenderModel( bool isDisplayModel = true )		{ m_isDisplayModel = isDisplayModel; };	

	void				SetSelModel( TObjectEditInfo* modelInfo );
	void				SetShowEnv( bool isShowZone );
	void				SetShowEnvId( sInt32 zoneId );
	void				SetShowZone( bool isShowZone )
	{
		m_isDisplayZone = isShowZone;
	}
	void				SetShowZoneId( sInt32 zoneId )
	{
		m_curZone = zoneId;
	}

	void				SetRenderAABBAndRadius(bool render) { mRenderAABBAndRadius = render; }

	void				ToggleDisplayMonster();;

	bool				IsDisplayMonster() const { return m_isDisplayMonster; }

	int					GetScreenWidth() {return m_screenWidth;};
	int					GetScreenHeight() {return m_screenHeight;};

	void				SetDisplaySlopeCheck(bool val) { m_isDisplaySlopeCheck = val; }

	bool				UpdateChaseCamera( D3DXVECTOR3& cameraPos, D3DXVECTOR3& lookAtPt );
	void				ResetCameraModel(){ m_pCameraModel = NULL; }

	int					GetCurTileChunkCount() { if (CURRENTTILE == NULL) return 0; else return CURRENTTILE->GetChunkTotal(); }
	int					GetCurTileVisibleChunkCount() const { return mCurTileVisibleChunkCount; }

	void				SetCameraFollowMex(const char *mex) { mCameraFollowMex = mex; }

protected:
	virtual void		CullingWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 CameraPos );						// 对CWorld进行可见判断并渲染
	virtual void		RenderModel( CWorldChunk* chunk, CWorldTile* cachTile, FrustumEx& frustum , D3DXVECTOR3 cameraPos);
	bool				CreateZoneShape();
	void				RenderEnv( CWorldChunk* worldChunk, sInt32 zoneId );

	void				DrawTri( CWorldChunk* worldChunk,DWORD color );
	void				RenderZone( CWorldChunk* worldChunk, sInt32 zoneId );
	void				RenderSlopeCheck( CWorldChunk* worldChunk);

protected:
	virtual void RenderStaticModel(sInt32 index_, int &vertex_num, int &face_num, int &submodel_num);

protected:

	bool				m_isDisplayModel;
	bool				m_isDisplayEnv;
	sInt32				m_curEnv;
	bool				m_isDisplayZone;
	sInt32				m_curZone;
	bool				m_isBoundWireframe;
	bool				m_isMesh;
	
	sInt32			m_nMeshLength;
	TObjectEditInfo*		m_selModelInfo;

	bool				m_isDisplayMonster;
	void				CreateSnapCamera();

	bool				m_isDisplaySlopeCheck;

	MexAnimCtrl*		m_pCameraModel;

	// 当前可视Chunk数
	int					mCurTileVisibleChunkCount;

	// 是否渲染包围盒
	bool				mRenderAABBAndRadius;

	// 相机模型名
	std::string        mCameraFollowMex;
};

/*----------------------------------------------------------
desc	: 扩展的CEditRener类，增加选择多个目标的功能，以及更改某些函数的访问属性。
author	: zilong
version	: 1.0
date	: 2011-01-14

revision:

----------------------------------------------------------*/
class CEditRender_M: public CEditRender
{
public:
	CEditRender_M();
	virtual ~CEditRender_M();

	void PushSelModel(TObjectEditInfo *pModel_);
	void PopModel(TObjectEditInfo *pModel_);
	void ClearSelModel(void);
	bool IsObjectVisible( SBBox& Box, FrustumEx& kFrustumEx)
	{
		return SwRender::IsObjectVisible(Box, kFrustumEx);
	}

	D3DLIGHT9 *GetLight(void){return &m_kD9Light;}

private:
	bool IsSelectingModel(const TObjectEditInfo *pModel);

	virtual void RenderStaticModel(sInt32 index_, int &vertex_num, int &face_num, int &submodel_num);

private:
	typedef std::vector<TObjectEditInfo *> TSelModels;
	TSelModels m_selModels;

};

extern CEditRender*		g_render;

#endif //__EDIT_RENDER_H__