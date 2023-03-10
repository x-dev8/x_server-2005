/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CWSRender.cpp
* Create: 	10/07/06
* Desc:		实现渲染功能
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "WSRender.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "MeTerrain/STSkyBox.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/Engine/RendererDx.h"
#include "Cfg.h"
#include "Me3d/Model/Mex2.h"
#include "MeTerrain/NdlRes.h"
#include "GameMain.h"
#include "wsCamera.h"
#include "Me3d/ShaderManager.h"

////////////////////////////////////////////////////////////////////////////////
extern INT MAX_FAR_CHUNK ;

const float WORLD_LOD1_FAR_MAX		= 70;				// 一级地形LOD最远绘制的距离
const float WUJIAN_FARSQ				= 60*60;				// 物件模型离人的渲染距离40米
////////////////////////////////////////////////////////////////////////////////
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float g_fCamerFOV;

CWSRender::CWSRender()
{
    m_bNeedInitCombineBuff = true;
	m_pCombineIB = NULL;
	m_pCombineVB = NULL;
}

CWSRender::CWSRender( int nScreenWidth, int nScreenHeight ):
	SwRender(nScreenWidth,nScreenHeight)
{
	m_bNeedInitCombineBuff = true;
	m_pCombineIB = NULL;
	m_pCombineVB = NULL;
}

CWSRender::~CWSRender()
{
	ReleaseCombineBuff();
}


float CWSRender::GetRealDoodadShowInstance()
{
	return gCfg.m_fDoodadShowDistance*(m_farChunk*2/MAX_FAR_CHUNK);
}



void CWSRender::RenderWorld( CWorld* world, FrustumEx& FrustumEx, D3DXVECTOR3 CameraPos, float totalTime, float deltaTime ,bool isRenderEffect)
{

	SwRender::RenderWorld(world,FrustumEx,CameraPos,totalTime,deltaTime,isRenderEffect);
}
#ifdef _DEBUG
#define LOAD_COST_TIME_DEBUG 0
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG

void CWSRender::CullingWorld( CWorld* world, FrustumEx& FrustumEx, D3DXVECTOR3 cameraPos )
{
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = HQ_TimeGetTime();
#endif
	SwRender::CullingWorld(world,FrustumEx,cameraPos);
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nSwRender::CullingWorld:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif

	CWorldTile* worldTile = world->GetWorldBuffer()->GetActiveTile();
	if( NULL == worldTile || !worldTile->IsLoad() )
	{
		return;
	}
#if LOAD_COST_TIME_DEBUG
	DWORD nModelUpdate = 0;
#endif

	WORD dBeforeRenderModel = HQ_TimeGetTime();
	// 渲染模型
	if( m_vctRenderModelList.size() )
	{
		
        char tilename[MAX_PATH] = {0};
        strcpy(tilename, worldTile->GetPathName());
		for(UINT i=0; i<m_vctRenderModelList.size(); i++)
		{
#if LOAD_COST_TIME_DEBUG
			DWORD nModelUpdataPlus = HQ_TimeGetTime();
#endif
			// added, jiayi, [2009/12/9]
			if( !m_vctRenderModelList[i]->model || !m_vctRenderModelList[i]->model->GetMex() )
				continue;

            bool bNeedUpdate = true;
            if( strstr(tilename, gCfg.m_pszSelectSceneName) && gCfg.m_strSelectSceneModelNotUpdate.size() )
            {
                for(size_t j=0; j<gCfg.m_strSelectSceneModelNotUpdate.size(); ++j)
                {
                    char modelname[MAX_PATH] = {0};
                    strcpy(modelname, m_vctRenderModelList[i]->model->GetMex()->GetFilename());
                    strlwr(modelname);
                    if( strstr(modelname, gCfg.m_strSelectSceneModelNotUpdate[j].c_str()) )
                    {
                        bNeedUpdate = false;
                        break;
                    }
                }
            }
			int vertex_num = 0;
			int face_num = 0;
			int submodel_num = 0;
			if( m_bNeedUpdateModel ) 
			{
                if( m_vctRenderModelList[i]->model->IsAni() && bNeedUpdate )
					m_vctRenderModelList[i]->model->UpdateByParam( HQ_TimeGetTime() );
				m_vctRenderModelList[i]->model->UseTexture();
				m_vctRenderModelList[i]->UpdateAlpha(HQ_TimeGetTime());
			}
#if LOAD_COST_TIME_DEBUG
			nModelUpdate += HQ_TimeGetTime() - nModelUpdataPlus;
#endif
			if(m_bRenderEffect &&  m_vctRenderModelList[i]->model->HasEmitter())
			{
				m_vctRenderEffect.push_back(m_vctRenderModelList[i]->model);
				continue;
			}

			//添加的时候已经是这两个状态,故删除
			{
				if( graphics::ShaderManager::instance()->isUseShader() )
					m_vctRenderModelList[i]->Render(m_vctRenderModelList[i]->GetAlpha(),true,NULL,NULL,&submodel_num);
				else
					m_vctRenderModelList[i]->model->Render(m_vctRenderModelList[i]->GetAlpha(), NULL, &vertex_num, &face_num, &submodel_num);

				if( GetMe3dConfig()->IsRenderBBox() )
				{
					GetDrawer()->DrawBox3D( m_vctRenderModelList[i]->model->GetWorldBBox(), 0xffffffff );
				}
				// 统计
				m_nModelCount++;
				m_nSubmodelCount += submodel_num;
				m_nModelVertexCount += vertex_num;
				m_nModelFaceCount += face_num;
			}
		}

		WORD dAfterRenderModel = HQ_TimeGetTime();
		m_dModelRenderTime = dAfterRenderModel - dBeforeRenderModel; //LYH时间检测 场景模型的更新时间	
	}
// #if LOAD_COST_TIME_DEBUG
// 	time_cost = HQ_TimeGetTime() - time_cost;
// 	if(time_cost != 0)
// 	{
// 		char cOutputString[2048];
// 		sprintf_s( cOutputString, 2048, "\nCullingWorldModelRender:%d ModelUpdate:%d\n", time_cost - nModelUpdate,nModelUpdate);
// 		OutputDebugStr(cOutputString);
// 	}
// 	time_cost = HQ_TimeGetTime();
// #endif

	dBeforeRenderModel = HQ_TimeGetTime();

	if(GetMe3dConfig()->IsRenderObjs())
		MeRenderManager::Instance()->DoRender( false );
	
	WORD dAfterRenderModel = HQ_TimeGetTime();
	m_SceneModeRealRenderTime = dAfterRenderModel - dBeforeRenderModel; //LYH时间检测 场景模型的渲染时间	



// #if LOAD_COST_TIME_DEBUG
// 	time_cost = HQ_TimeGetTime() - time_cost;
// 	if(time_cost != 0)
// 	{
// 		char cOutputString[2048];
// 		sprintf_s( cOutputString, 2048, "\nCullingWorldDoRender:%d\n", time_cost );
// 		OutputDebugStr(cOutputString);
// 	}
// 	time_cost = HQ_TimeGetTime();
// #endif
}


void CWSRender::RenderModel( CWorldChunk* chunk, CWorldTile* cachTile, 
						   FrustumEx& frustum, D3DXVECTOR3 cameraPos )
{
	chunk->LockFlag(true);
	if (chunk->GetLoadLevel() < CWorldChunk::eModelLoaded)
	{
		chunk->LockFlag(false);
		return;
	}
	float cullfar = GetModelCullFar();
	float cullfarSq = cullfar * cullfar;
    char tilename[MAX_PATH] = {0};
    strcpy(tilename, cachTile->GetPathName());
    strlwr(tilename);
    bool bLoginSelect =  strstr(tilename, gCfg.m_pszSelectSceneName);
	//手动锁CWorldChunk::eModel
	chunk->MarkDataUsing(CWorldChunk::eModel,true);
	chunk->LockFlag(false);
	for( size_t i=0; i<chunk->GetStaticModelList().size(); i++ )
	{
		sInt32 id = chunk->GetStaticModelList()[i];
		TObjectInfo* objInfo = cachTile->GetCResMgr()->GetStaticModel( id );
		if( NULL != objInfo && objInfo->model && objInfo->UpdateRenderCounter(m_renderCounter)) 
		{
			// 绘制模型.
			WORD curTime	= HQ_TimeGetTime();
            bool bNeedUpdate = true;
			// 登录和选人界面，相机轨迹动画不用更新
            if( bLoginSelect && gCfg.m_strSelectSceneModelNotUpdate.size() )
            {
                for(size_t j=0; j<gCfg.m_strSelectSceneModelNotUpdate.size(); ++j)
                {
                    if (objInfo->model->GetMex())
                    {
                        char modelname[MAX_PATH] = {0};
                        strcpy(modelname, objInfo->model->GetMex()->GetFilename());
                        strlwr(modelname);
                        if( strstr(modelname, gCfg.m_strSelectSceneModelNotUpdate[j].c_str()) )
                        {
                            bNeedUpdate = false;
                            break;
                        }
                    }
                }
            }

            if( objInfo->model->IsAni() && bNeedUpdate )
				objInfo->model->UpdateByParam( HQ_TimeGetTime() );
			objInfo->model->UseTexture();

			// 判断模型与相机距离
			Vector camera2Obj = *((Vector*)&cameraPos);
			camera2Obj -= objInfo->model->GetCenter();

			float fDisSq = camera2Obj.lengthsq();
			fDisSq -= objInfo->model->GetRadius() * objInfo->model->GetRadius();

			bool bIsCullByFar = objInfo->WasInCullFar();
            float fWujianFar = getwsCamera()->GetFreeCameraMode()? 150*150 : WUJIAN_FARSQ;

			if( m_bNeedFade )
			{
				if( fDisSq > cullfarSq || (!bLoginSelect && objInfo->IsWuJian() && fDisSq > fWujianFar ) )
				{
					if( objInfo->GetFadeMode() == TObjectInfo::ModelFirstRender )
					{
						// 第一次渲染，Alpha直接设为0
						objInfo->m_FadeMode = TObjectInfo::ModelNormal;
						objInfo->m_fAlpha = 0.f;
						objInfo->SetInCullFar(false);
					}
					else if( objInfo->WasInCullFar() && objInfo->GetFadeMode() != TObjectInfo::ModelFadeOut )
					{
						// 模型淡出
						objInfo->SetFadeMode(TObjectInfo::ModelFadeOut, HQ_TimeGetTime(), 1500);
					}
					else if( objInfo->GetFadeMode() == TObjectInfo::ModelFadeOut )
					{
						// 更新Alpha
						objInfo->UpdateAlpha(HQ_TimeGetTime());
					}				
				}
				else if( !objInfo->WasInCullFar() // 之前不在渲染范围内
					&& (fDisSq < cullfarSq - 100.f || (!bLoginSelect && objInfo->IsWuJian() && fDisSq < fWujianFar - 100.f) )	// 当前在渲染范围内
					&& objInfo->GetFadeMode() != TObjectInfo::ModelFadeIn )	// 当前不是淡入状态
				{
					// 模型淡入
					objInfo->SetInCullFar(true);
					objInfo->SetFadeMode(TObjectInfo::ModelFadeIn, HQ_TimeGetTime(), 3500);
				}
				else	// 更新Alpha
					objInfo->UpdateAlpha(HQ_TimeGetTime());
			}
			else
			{
 				if( fDisSq > cullfarSq || (!bLoginSelect && objInfo->IsWuJian() && fDisSq > fWujianFar ))
 					objInfo->SetInCullFar( false );
 				else
 					objInfo->SetInCullFar( true );
			}
			

			// 可视剪裁
			SBBox kMMBox;	// 记录世界坐标系的最大和最小值
			kMMBox.vecMin = *((D3DXVECTOR3*)&objInfo->model->GetWorldMin());
			kMMBox.vecMax = *((D3DXVECTOR3*)&objInfo->model->GetWorldMax());
			if( !IsObjectVisible( kMMBox, frustum) )
				objInfo->SetIsCulled(true);
			else
				objInfo->SetIsCulled(false);

			// 渲染模型
			if( objInfo->WasInCullFar() && !objInfo->IsCulled() )
				m_vctRenderModelList.push_back(objInfo);
			// 恢复标志位
			if( !m_bNeedFade )//用在画水
				objInfo->SetInCullFar( bIsCullByFar );
		}
	}
}



void CWSRender::Initialize( int nScreenWidth, int nScreenHeight )
{
	SwRender::Initialize(nScreenWidth,nScreenHeight);
}

void CWSRender::UpdateFarFog( float fFarFog )
{
	SwRender::UpdateFarFog(fFarFog);
	if (SwGlobal::GetWorld())
	{
		CWorldTile* pTile = CURRENTTILE;
		if (pTile)
		{
			pTile->m_tileQuadTree.SetNeedSetFrustumEx(TRUE);
		}
	}
}


float CWSRender::GetModelCullFar()
{
// 	float model_far = 1000;
//     float factor = 0.9f;
//     if( m_fogProp.fFogFar - m_fogProp.fFogNear > 80 )
//         factor = 0.875;
//     else if( m_fogProp.fFogFar - m_fogProp.fFogNear > 150 )
//         factor = 0.85;
//     else if( m_fogProp.fFogFar - m_fogProp.fFogNear > 200 )
//         factor = 0.825;
//     else if( m_fogProp.fFogFar - m_fogProp.fFogNear > 250 )
//         factor = 0.8;
//     else if( m_fogProp.fFogFar - m_fogProp.fFogNear > 300 )
//         factor = 0.775;
//     else if( m_fogProp.fFogFar - m_fogProp.fFogNear > 350 )
//         factor = 0.75;
//     else if( m_fogProp.fFogFar - m_fogProp.fFogNear > 400 )
//         factor = 0.725;
// 	model_far = min( gCfg.m_fModelShowDistance, (m_fogProp.fFogFar - m_fogProp.fFogNear) * factor + m_fogProp.fFogNear );
	return GetFarPlane();
}


bool CWSRender::AllocCombineBuff( long lVertexNum, long lFaceNum )
{
	ReleaseCombineBuff();

	if( GetEngine() && GetEngine()->GetRenderer() )
	{
		HRESULT hr;
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
		if( !m_pCombineVB )
		{
			while(1)
			{
				hr = pDev->CreateVertexBuffer( MAX_VERTEX*sizeof(MexVertex), D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pCombineVB, NULL );
				if( SUCCEEDED(hr) ) break;
			}
		}
		if( !m_pCombineIB )
		{
			while(1)
			{
				hr = pDev->CreateIndexBuffer( MAX_FACES*3*sizeof(short), D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pCombineIB, NULL );
				if( SUCCEEDED(hr) ) break;
			}
		}

		return true;
	}

	return false;
}

void CWSRender::ReleaseCombineBuff()
{
	if( m_pCombineIB )
	{
		m_pCombineIB->Release();
		m_pCombineIB = NULL;
	}

	if( m_pCombineVB )
	{
		m_pCombineVB->Release();
		m_pCombineVB = NULL;
	}
}

extern int GetVertexStride( DWORD dwFvf );

void CWSRender::InitCombineBuff()
{
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	D3DCAPS9 d3dCaps;
	pDev->GetDeviceCaps(&d3dCaps);
	MAX_VERTEX = min(d3dCaps.MaxVertexIndex,5000);
	MAX_FACES = min(d3dCaps.MaxPrimitiveCount,2500);
	m_pCombineIB = NULL;
	m_pCombineVB = NULL;
	AllocCombineBuff(MAX_VERTEX, MAX_FACES);
}


void CWSRender::OnDeviceLost()
{
	SwRender::OnDeviceLost();
	if(!m_bNeedInitCombineBuff )
	{
		ReleaseCombineBuff();
		m_bNeedInitCombineBuff = true;
	}
}

void CWSRender::OnDeviceReset()
{
	SwRender::OnDeviceReset();
	SetFarChunk( GetFarChunk() );
}


void CWSRender::RenderCombineShadowDecal()
{
    IRenderer* pRenderer = GetEngine()->GetRenderer();
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	pRenderer->SetTransform( D3DTS_WORLD, (float*)&world );    
	pRenderer->DirectPushSurface( 
		m_iCombineShadowTexId,
		-1,
		TERRAIN_BLEND,
		D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1,
		sizeof( MexVertex ),
		(BYTE*)m_pCombineVB,
		m_lCombineShadowVertexCount,
		(BYTE*)m_pCombineIB,
		m_lCombineShadowFaceCount,
		eUseVB | eUseIB | eUClamp | eVClamp | eNoMipmap | eZWriteDisable);
    
}

void CWSRender::CombineShadowDecal( swDecalShapeVertex* pVertex, int iVertexCount, unsigned short* pIndex, int iFaceCount, int iTexId )
{
    if( !( pVertex && pIndex && iVertexCount > 0 && iFaceCount > 0 ) )
        return;

	if ((m_lCombineShadowFaceCount + iFaceCount > MAX_FACES) || (m_lCombineShadowVertexCount + iVertexCount >  MAX_VERTEX ))
	{
		return;
	}
    m_iCombineShadowTexId = iTexId;
    
	// 拷贝面索引
	if( m_lCombineShadowVertexCount == 0 )
	{
		memcpy((void*)&m_shLockIBFace[0], (void*)pIndex, iFaceCount*3*sizeof(unsigned short));
	}
	else
	{
		short* shIBFaceTemp = &m_shLockIBFace[m_lCombineShadowFaceCount*3];
		for(int i=0; i<iFaceCount*3; i++)
		{
			*shIBFaceTemp = pIndex[i] + m_lCombineShadowVertexCount;
			++shIBFaceTemp;
		}
	}
	m_lCombineShadowFaceCount += iFaceCount;
	// 拷贝顶点信息
	for(int i=0; i<iVertexCount; i++, m_lCombineShadowVertexCount++)
	{
		m_pLockVBVertex[m_lCombineShadowVertexCount].x = pVertex[i].p.x;
		m_pLockVBVertex[m_lCombineShadowVertexCount].y = pVertex[i].p.y;
		m_pLockVBVertex[m_lCombineShadowVertexCount].z = pVertex[i].p.z;
		m_pLockVBVertex[m_lCombineShadowVertexCount].diff = pVertex[i].color;
		m_pLockVBVertex[m_lCombineShadowVertexCount].u = pVertex[i].u;
		m_pLockVBVertex[m_lCombineShadowVertexCount].v = pVertex[i].v;
		m_pLockVBVertex[m_lCombineShadowVertexCount].nx = 0;
		m_pLockVBVertex[m_lCombineShadowVertexCount].ny = 0;
		m_pLockVBVertex[m_lCombineShadowVertexCount].nz = 1;
	}    
}

void CWSRender::StartCombineShadowDecal()
{
	if( m_bNeedInitCombineBuff )
	{
		m_bNeedInitCombineBuff = false;
		InitCombineBuff();
	}
    HRESULT hr;
    
	while(1)
	{
		hr = m_pCombineVB->Lock( 0, MAX_VERTEX*sizeof(MexVertex), (void**)&m_pLockVBVertex, D3DLOCK_DISCARD );
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = m_pCombineIB->Lock( 0, MAX_FACES*3*sizeof(short), (void**)&m_shLockIBFace, D3DLOCK_DISCARD );
		if( SUCCEEDED(hr) ) break;
	}
    
    m_lCombineShadowVertexCount = 0;
    m_lCombineShadowFaceCount = 0;
}

void CWSRender::EndCombineShadowDecal()
{
    HRESULT hr;

	while(1)
	{
		hr = m_pCombineVB->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = m_pCombineIB->Unlock();
		if( SUCCEEDED(hr) ) break;
	}

}

extern bool g_DynamicMapLoadOpenEvent;
bool CWSRender::IsNeedCull( CWorldTile* worldTile,FrustumEx& FrustumEx )
{
	return g_DynamicMapLoadOpenEvent || worldTile->m_tileQuadTree.IsNeedCull(&FrustumEx);
}

void CWSRender::AddLiquidChunk( CWorldChunk * chunk, D3DXVECTOR3 &cameraPos, float fLiquidFar, float fMinLiquidHeightToCamera )
{
	// 计算相机到chunk中心点距离
	D3DXVECTOR3 liquidCenter;
	liquidCenter.x = chunk->Origin()[0];
	liquidCenter.y = chunk->Origin()[1];
	liquidCenter.z = chunk->GetLiquidHeight();

	D3DXVECTOR3 camera2liquid = liquidCenter;
	camera2liquid -= cameraPos;
	float dis = D3DXVec3Length(&camera2liquid);
	if( dis < fLiquidFar )
	{
		SwRender::AddLiquidChunk(chunk,cameraPos,fLiquidFar,fMinLiquidHeightToCamera);
	}

}

void CWSRender::CheckLODAndDoodad( CWorldChunk*  chunk, D3DXVECTOR3 cameraPos, CWorldTile* worldTile )
{
	if (SwGlobal::s_SimpleMapLoadMode)
	{
// 		WORD dBeforeRenderModel = HQ_TimeGetTime();
// 		RenderDoodad(chunk);
		m_vctRenderDoodadChunkList.push_back(chunk);
// 		WORD dAfterRenderModel = HQ_TimeGetTime();
// 		m_dDoodadRenderTime += dAfterRenderModel - dBeforeRenderModel;
		return;
	}
	float WORLD_LOD1_FAR = min(m_fogProp.fFogFar * 0.6f, m_fogProp.fFarPlane * 0.5f);		// 一级地形LOD开始绘制的距离
	if( WORLD_LOD1_FAR > WORLD_LOD1_FAR_MAX )
		WORLD_LOD1_FAR = WORLD_LOD1_FAR_MAX;
	float WORLD_LOD2_FAR = m_fogProp.fFogFar * 1.0f;				// 二级地形LOD开始绘制的距离 
	// 计算相机到chunk中心点距离
	D3DXVECTOR3 chunkCenter;
	chunkCenter.x = chunk->Origin()[0];
	chunkCenter.y = chunk->Origin()[1];
	flt32* pHeight = chunk->GetHeight();
	chunkCenter.z = (pHeight[0]+pHeight[1])*0.5f;

	D3DXVECTOR3 camera2chunk = chunkCenter;
	camera2chunk -= cameraPos;
	float dis = D3DXVec3Length(&camera2chunk);
	float radius = sqrt(0.5f*WORLD_CHUNKSIZE*WORLD_CHUNKSIZE 
		+ (pHeight[1]-pHeight[0])*(pHeight[1]-pHeight[0])*0.25f);

	if( dis > WORLD_LOD2_FAR + radius )
		worldTile->GetCResMgr()->SetLODLevel(chunk,2);
	else if( dis > WORLD_LOD1_FAR + radius )
		worldTile->GetCResMgr()->SetLODLevel(chunk,1);
	else
		worldTile->GetCResMgr()->SetLODLevel(chunk,0);

	if( dis < GetRealDoodadShowInstance() + radius )
	{
// 		WORD dBeforeRenderModel = HQ_TimeGetTime();
// 		RenderDoodad(chunk);
		m_vctRenderDoodadChunkList.push_back(chunk);
// 		WORD dAfterRenderModel = HQ_TimeGetTime();
// 		m_dDoodadRenderTime += dAfterRenderModel - dBeforeRenderModel;
	}
}
