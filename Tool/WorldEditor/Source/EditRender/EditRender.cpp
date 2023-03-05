/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NDLRender.cpp
* Date: 	01/09/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldEntry.h"
#include "EditCamera.h"
//#include "EditAccumulator.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "EditRender.h"
#include "Me3d/Engine\RendererDX.h"
#include "Edit/ToolLayer.h"
#include "Edit/ToolManager.h"
#include "ui/Custom/ReachableMapGenerate.h"
//added by zilong. 2011-01-10
#include "Me3d/Engine/MeRenderManager.h"
CEditRender*	g_render = NULL;

////////////////////////////////////////////////////////////////////////////////
CEditRender::CEditRender()
{
	m_isMesh = false;
	m_isBoundWireframe	= false;
	m_isDisplayEnv		= false;
	m_isDisplayZone		= false;
	m_isDisplayAnimation= true;
	m_isDisplayModel	= true;
	m_isDisplayMonster  = false;
	m_vctRenderChunkList.clear();
	m_vctRenderLiquidChunkList.clear();

	m_curEnv			= RES_INVALID_ID;
	m_curZone			= RES_INVALID_ID;

	m_selModelInfo = NULL;
	m_isDisplaySlopeCheck = false;

	m_pCameraModel = NULL;
}

CEditRender::~CEditRender()
{
	Destroy();
	m_vctRenderChunkList.clear();
	m_vctRenderLiquidChunkList.clear();
}

bool CEditRender::CreateZoneShape()
{

	return true;
}

void CEditRender::Destroy()
{
}

void CEditRender::SetBgndColor( const NiColor& color )
{
}

bool CEditRender::IsWireframe()
{
	return m_isWireFrame;
}


void CEditRender::RenderEnv( CWorldChunk* worldChunk, sInt32 envId )
{
	if (worldChunk->m_envId != RES_INVALID_ID && worldChunk->m_envId == envId)
	{
		DrawTri(worldChunk,0xFFFF0000);
	}
}
void CEditRender::SetSelModel( TObjectEditInfo* modelInfo )
{
	m_selModelInfo	= modelInfo;
}

void CEditRender::SetShowEnv( bool isShowZone )
{
	m_isDisplayEnv	= isShowZone;
}

void CEditRender::SetShowEnvId( sInt32 zoneId )
{
	m_curEnv = zoneId;
}

void CEditRender::RenderStaticModel(sInt32 index_, int &vertex_num, int &face_num, int &submodel_num)
{
	ASSERT(index_ >= 0 && index_ < m_vctRenderModelList.size());

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	if( m_selModelInfo && m_selModelInfo == m_vctRenderModelList[index_] )
	{
		GetMe3dConfig()->SetRenderModelSelected(TRUE);

		if( view->IsUseDynamicLight() )
			m_vctRenderModelList[index_]->model->Render(1.f, NULL, &vertex_num, &face_num, &submodel_num);
		else
			m_vctRenderModelList[index_]->Render( 1.f );		
		GetMe3dConfig()->SetRenderModelSelected(FALSE);
		GetEngine()->GetRenderer()->SetLight(LIGHT_INDEX_TERRAIN, &m_kD9Light);
	}
	else
	{
		if( view->IsUseDynamicLight() )
			m_vctRenderModelList[index_]->model->Render(1.f, NULL, &vertex_num, &face_num, &submodel_num);
		else
			m_vctRenderModelList[index_]->Render( 1.f );
		if( GetMe3dConfig()->m_RenderHelper )
			GetEngine()->GetRenderer()->SetLight(LIGHT_INDEX_TERRAIN, &m_kD9Light);
	}
}

bool CEditRender::UpdateChaseCamera( D3DXVECTOR3& cameraPos, D3DXVECTOR3& lookAtPt )
{
#define SELECT_CAMERA_MODEL		"selectcamera"
#define SELECT_CAMERA_TARGET	"selecttarget"

	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
	if( pTile && m_pCameraModel == NULL )
	{
		CResMgr* pResMgr = pTile->GetCResMgr();
		assert( pResMgr );
		if( pResMgr )
		{
			char pszName[MAX_PATH] = {0};
			for (size_t i = 0; i < pResMgr->GetStaticModelList().size(); ++i )
			{
				TObjectInfo* pInfo = pResMgr->GetStaticModel(i);
				if( pInfo->model && pInfo->model->GetMex() )
				{
						strncpy(pszName, pInfo->model->GetMex()->GetFilename(), sizeof(pszName)-1);
						strlwr(pszName);
						if( strstr(pszName, mCameraFollowMex.c_str()) )
						{
							m_pCameraModel = pInfo->model;
						}
				}
			}
		}
	}

	{
		BOOL bUpdateCamera = FALSE;
		BOOL bUpdateTarget = FALSE;
		D3DXVECTOR3 vNewCameraPos = D3DXVECTOR3(0,0,0);
		D3DXVECTOR3 vNewTargetPos = D3DXVECTOR3(0,0,0);
		if( m_pCameraModel && m_pCameraModel->GetMex() )
		{
			m_pCameraModel->UpdateByParam( HQ_TimeGetTime() );
			for( int nChunk = 0; nChunk < m_pCameraModel->GetMex()->GetGeometry()->GetChunkCount(); nChunk++ )
			{
				Mex2GeoChunk* pChunk = (Mex2GeoChunk*)m_pCameraModel->GetMex()->GetGeometry()->GetChunk(nChunk);
				Vector* vertices = (Vector*)pChunk->GetWorldVertices();
				int nVertexCount = pChunk->GetVertexCount();
				char lwrName[MAX_PATH] = {0};
				const char* pszName = pChunk->GetName();
				strncpy( lwrName, pszName, MAX_PATH-1 );
				strlwr(lwrName);
				if (strstr(lwrName, SELECT_CAMERA_MODEL) )
				{
					pChunk->BlendVertex( m_pCameraModel->GetMex(), (float*)m_pCameraModel->GetMatrices());
					if( nVertexCount > 0 )
					{
						for(int j=0; j<nVertexCount; ++j)
						{
							vNewCameraPos.x += vertices[j].x;
							vNewCameraPos.y += vertices[j].y;
							vNewCameraPos.z += vertices[j].z;
						}
						vNewCameraPos.x /= nVertexCount;
						vNewCameraPos.y /= nVertexCount;
						vNewCameraPos.z /= nVertexCount;
					}
					bUpdateCamera = TRUE;
				}
				else if (strstr(lwrName, SELECT_CAMERA_TARGET) )
				{
					pChunk->BlendVertex( m_pCameraModel->GetMex(), (float*)m_pCameraModel->GetMatrices());
					if( nVertexCount > 0 )
					{
						for(int j=0; j<nVertexCount; ++j)
						{
							vNewTargetPos.x += vertices[j].x;
							vNewTargetPos.y += vertices[j].y;
							vNewTargetPos.z += vertices[j].z;
						}
						vNewTargetPos.x /= nVertexCount;
						vNewTargetPos.y /= nVertexCount;
						vNewTargetPos.z /= nVertexCount;
					}
					bUpdateTarget = TRUE;
				}
				if( bUpdateCamera && bUpdateTarget )
					break;
			}

			//m_vEye = vNewCameraPos;
			//m_vLookat = vNewTargetPos;
			//camera->CaluEyeAndLookat(
			//	*(D3DXVECTOR3*)&vNewCameraPos,
			//	*(D3DXVECTOR3*)&vNewTargetPos );

			//camera->SetPos( Vector(vNewCameraPos.x, vNewCameraPos.y, vNewCameraPos.z) );
			cameraPos = vNewCameraPos;
			lookAtPt = vNewTargetPos;
			return true;
		}		
	}
	return false;
}

void CEditRender::CullingWorld( CWorld* world, FrustumEx& frustum, D3DXVECTOR3 CameraPos )
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	SwRender::CullingWorld(world,frustum,CameraPos);
	if(0 == m_vctRenderEffect.size() )
	{
		//提前手动解锁CWorldChunk::eModel
		UnlockModelRes();
	}
	IRenderer* RI = GetEngine()->GetRenderer();

	CWorldTile* worldTile = world->GetWorldBuffer()->GetActiveTile();
	if( NULL == worldTile )
	{
		return;
	}

	if( !worldTile->IsLoad() )
		return;


	// 渲染模型
	if( m_vctRenderModelList.size() )
	{
		WORD dBeforeRenderModel = HQ_TimeGetTime();
		for(UINT i=0; i<m_vctRenderModelList.size(); i++)
		{
			int vertex_num = 0;
			int face_num = 0;
			int submodel_num = 0;
			if( m_vctRenderModelList[i]->model->IsAni() )
				m_vctRenderModelList[i]->model->UpdateByParam( HQ_TimeGetTime() );
			m_vctRenderModelList[i]->model->UseTexture();

			if( GetMe3dConfig()->IsRenderBBox() )
			{
				DWORD dwColor;
				if( i%4 == 0 )
					dwColor = 0xff0000ff;
				else if( i%4 == 1 )
					dwColor = 0xff00ff00;
				else if( i%4 == 2 )
					dwColor = 0xffff0000;
				else
					dwColor = 0xffffffff;
				GetDrawer()->DrawBox3D( m_vctRenderModelList[i]->model->GetWorldBBox(), dwColor );
			}

			if( m_vctRenderModelList[i]->model->HasEmitter())
			{
				m_vctRenderEffect.push_back(m_vctRenderModelList[i]->model);
				continue;
			}

			// Pick的模型改变颜色
			RenderStaticModel(i, vertex_num, face_num, submodel_num);


			// 统计
			m_nModelCount++;
			m_nSubmodelCount += submodel_num;
			m_nModelVertexCount += vertex_num;
			m_nModelFaceCount += face_num;
		}
		WORD dAfterRenderModel = HQ_TimeGetTime();
		m_dModelRenderTime += dAfterRenderModel - dBeforeRenderModel;
	}

	/*
	 * 2012.6.26 wangshuai
	 * 统计当前可视Chunk数
	 */
	mCurTileVisibleChunkCount = 0;
	for( sInt32 i = 0; i < worldTile->GetChunkTotal(); i++ )	
	{
		CWorldChunk* chunk = worldTile->m_chunckTable[i];
		Assert( NULL != chunk );
		CNdlShapeRes* shape = worldTile->GetCResMgr()->Shape( chunk->GetShape() );
		Assert( NULL != shape );

		if( !IsObjectVisible( shape->m_MMBox, frustum) )
			continue;

		++mCurTileVisibleChunkCount;
		// 网格线
		if ( m_isBoundWireframe )
		{
			// 渲染地表网格
			((CResEditMgr *) worldTile->GetCResMgr())->Line( chunk->m_shape )->setColor(0xffffff00);
			((CResEditMgr *) worldTile->GetCResMgr())->Line( chunk->m_shape )->Render();
		}

		if ( m_isMesh )
			((CResEditMgr *) worldTile->GetCResMgr())->GetMesh()->Render();
		
		if ( m_isDisplayEnv )
			RenderEnv( chunk, m_curEnv );
		
		if ( m_isDisplayZone )
			RenderZone( chunk, m_curZone );
		
		if ( m_isDisplaySlopeCheck )
			RenderSlopeCheck(chunk);
	}

	//CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolLayer* toolLayer =  (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

	for( int i=0;i<toolLayer->m_vecWorldChunk.size();++i)
	{
		CWorldChunk* chunk = toolLayer->m_vecWorldChunk[i];

		//worldTile->GetCResMgr()->Line( chunk->m_shape )->setColor(0xffff0000);
		//worldTile->GetCResMgr()->Line( chunk->m_shape )->Render();
		chunk->RenderWireFrame();
	}
	//added by zilong. 2010-01-10
		MeRenderManager::Instance()->DoRender( false );
		RenderDoodad();
}


void CEditRender::RenderModel( CWorldChunk*  chunk, CWorldTile*  cachTile, FrustumEx& frustum , D3DXVECTOR3 cameraPos)
{
	if ( m_isDisplayModel )
	{
		for ( size_t i=0; i<chunk->m_staticModelList.size(); i++ )
		{
			sInt32 id = chunk->m_staticModelList[i];
			TObjectEditInfo* objInfo = (TObjectEditInfo*)cachTile->GetCResMgr()->GetStaticModel( id );
			if ( NULL != objInfo && objInfo->UpdateRenderCounter(m_renderCounter)) 
			{
				// 绘制物件.
				DWORD curTime	= HQ_TimeGetTime();
				if( objInfo->model->IsAni() )
					objInfo->model->UpdateByParam( curTime );
				objInfo->model->UseTexture();
				// 可视剪裁
				Box* pWorldBBox = objInfo->model->GetWorldBBox();
				SBBox kMMBox;	// 记录世界坐标系的最大和最小值
				kMMBox.vecMin = D3DXVECTOR3(10000.f, 10000.f, 10000.f);
				kMMBox.vecMax = D3DXVECTOR3(-10000.f, -10000.f, -10000.f);
				for (int i = 0; i < 8; i++)
				{
					kMMBox.vecMin.x = min(kMMBox.vecMin.x, pWorldBBox->v[i].x);
					kMMBox.vecMin.y = min(kMMBox.vecMin.y, pWorldBBox->v[i].y);
					kMMBox.vecMin.z = min(kMMBox.vecMin.z, pWorldBBox->v[i].z);
					kMMBox.vecMax.x = max(kMMBox.vecMax.x, pWorldBBox->v[i].x);
					kMMBox.vecMax.y = max(kMMBox.vecMax.y, pWorldBBox->v[i].y);
					kMMBox.vecMax.z = max(kMMBox.vecMax.z, pWorldBBox->v[i].z);
				}
				//if ( !IsObjectVisible( kMMBox, frustum) )
				//	continue;

				// 渲染模型
				m_vctRenderModelList.push_back(objInfo);
			}
		}
	}
}
 
void CEditRender::CreateSnapCamera()
{
}


void CEditRender::ToggleDisplayMonster()
{
	m_isDisplayMonster = !m_isDisplayMonster;
	{
		CWorldTile* pTile = CURRENTTILE;
		if (pTile)
		{
			if (m_isDisplayMonster)
				((CResEditMgr*)pTile->GetCResMgr())->AttachAllMonsterQuad();
			else
				((CResEditMgr*)pTile->GetCResMgr())->DetachAllMonsterQuad();
		}

	}
}

void CEditRender::RenderZone( CWorldChunk* worldChunk, sInt32 zoneId )
{
	if (worldChunk->m_zoneId != RES_INVALID_ID && worldChunk->m_zoneId == zoneId)
	{
		DrawTri(worldChunk,0xFF00FF00);
	}

}



void CEditRender::RenderSlopeCheck( CWorldChunk* worldChunk )
{
	if (CReachableMapGenerate::Instance()->IsErrorSlope(worldChunk))
	{
		DrawTri(worldChunk,0xFFFFFF00);
	}
}

void CEditRender::DrawTri( CWorldChunk* worldChunk,DWORD color )
{
	D3DXVECTOR3 verts[3];
	float height = (worldChunk->m_height[1] +worldChunk->m_height[0]);

	BOOL bInFloor = false;
	if (worldChunk->m_liquidId != RES_INVALID_ID)
	{
		if (worldChunk->m_liquidHeight > height)
		{
			height = worldChunk->m_liquidHeight + 0.1;
		}
	}
	verts[0].x	= worldChunk->m_origin[0]-(WORLD_CHUNKSIZE*0.5f);
	verts[0].y	= worldChunk->m_origin[1]-(WORLD_CHUNKSIZE*0.5f);
	verts[0].z	= SwGlobal::GetWorldPicker()->GetZByXY(10000.f, verts[0].x, verts[0].y, 0, &bInFloor);

	verts[1].x	= worldChunk->m_origin[0]-(WORLD_CHUNKSIZE*0.5f);
	verts[1].y	= worldChunk->m_origin[1]+(WORLD_CHUNKSIZE*0.5f);
	verts[1].z	= SwGlobal::GetWorldPicker()->GetZByXY(10000.f, verts[2].x, verts[2].y, 0, &bInFloor);

	verts[2].x	= worldChunk->m_origin[0]+(WORLD_CHUNKSIZE*0.5f);
	verts[2].y	= worldChunk->m_origin[1]+(WORLD_CHUNKSIZE*0.5f);
	verts[2].z	= SwGlobal::GetWorldPicker()->GetZByXY(10000.f, verts[2].x, verts[2].y, 0, &bInFloor);

	GetDrawer()->FillTri( verts[0], verts[1], verts[2], color );
}

void CEditRender::RenderLiquidReflect(SwCamera* pCamera, float fFov, D3DXVECTOR3& vPos, CWorld* world, float totalTime, float deltaTime)
{
	if( !pCamera )
		return;

	MeCamera kCamera;
	kCamera.SetProjMatrix( pCamera->GetProjMatrix() );
	kCamera.SetViewMatrix( pCamera->GetViewMatrix() );
	kCamera.SetViewParams( pCamera->GetEye(), pCamera->GetLookAt(), D3DXVECTOR3( 0, 0 , 1 ) );
	SwRender::RenderLiquidReflect( &kCamera, fFov, vPos, world, totalTime, deltaTime );
}

CEditRender_M::CEditRender_M()
{

}

CEditRender_M::~CEditRender_M()
{
	ClearSelModel();
}

void CEditRender_M::PushSelModel(TObjectEditInfo *pModel_)
{
	m_selModels.push_back(pModel_);
}

void CEditRender_M::PopModel(TObjectEditInfo *pModel_)
{
	for(TSelModels::iterator it = m_selModels.begin(); it != m_selModels.end(); ++it)
	{
		if(pModel_ == *it)
		{
			m_selModels.erase(it);
			return;
		}
	}
}

void CEditRender_M::ClearSelModel(void)
{
	m_selModels.clear();
}

bool CEditRender_M::IsSelectingModel(const TObjectEditInfo *pModel)
{
	for(TSelModels::iterator it = m_selModels.begin(); it != m_selModels.end(); ++it)
	{
		if(pModel == *it)
			return true;
	}

	return false;
}

void CEditRender_M::RenderStaticModel(sInt32 index_, int &vertex_num, int &face_num, int &submodel_num)
{
	ASSERT(index_ >= 0 && index_ < m_vctRenderModelList.size());
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	if(IsSelectingModel((TObjectEditInfo *)m_vctRenderModelList[index_]))
	{
		GetMe3dConfig()->SetRenderModelSelected(TRUE);

		if( view->IsUseDynamicLight() )
			m_vctRenderModelList[index_]->model->Render(1.f, NULL, &vertex_num, &face_num, &submodel_num);
		else
			m_vctRenderModelList[index_]->Render( 1.f, TRUE, &vertex_num, &face_num, &submodel_num );
		GetMe3dConfig()->SetRenderModelSelected(FALSE);
		GetEngine()->GetRenderer()->SetLight(LIGHT_INDEX_TERRAIN, &m_kD9Light);
	}
	else
	{
		if( view->IsUseDynamicLight() )
			m_vctRenderModelList[index_]->model->Render(1.f, NULL, &vertex_num, &face_num, &submodel_num);
		else
			m_vctRenderModelList[index_]->Render( 1.f, TRUE, &vertex_num, &face_num, &submodel_num );
		if( GetMe3dConfig()->m_RenderHelper )
			GetEngine()->GetRenderer()->SetLight(LIGHT_INDEX_TERRAIN, &m_kD9Light);
	}

	if (mRenderAABBAndRadius && !(CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetDisplayFilter() & znDF_RenderMinimap))
		m_vctRenderModelList[index_]->RenderAABBAndRadius();
}