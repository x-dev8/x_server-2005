/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwRender.cpp
* Create: 	10/07/06
* Desc:		实现渲染功能
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/SwRender.h"
// #include "GameCamera.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "MeTerrain/STSkyBox.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/engine/RendererDx.h"
#include "Me3d/Model/mex2.h"
#include "MeTerrain/NdlRes.h"
////////////////////////////////////////////////////////////////////////////////
//const float WORLD_FAR				= 130;				// 地形绘制的最远距离
// const float WORLD_LOD1_FAR_MAX		= 70;				// 一级地形LOD最远绘制的距离
//const float WORLD_LOD2_FAR			= 100;				// 二级地形LOD开始绘制的距离 
//const float MODEL_FAR				= 120.f;			// 模型绘制的最远距离
//const float DOODAD_FAR				= 60.f;				// 草皮离人DOODAD_FAR米以外，不显示
const float WUJIAN_FARSQ				= 60*60;				// 物件模型离人的渲染距离40米
////////////////////////////////////////////////////////////////////////////////
 INT NEAR_CHUNK = 4;
 INT MAX_FAR_CHUNK = 14;
 extern int SCREEN_WIDTH;
 extern int SCREEN_HEIGHT;
extern float g_fCamerFOV;
SwRender::SwRender():
	m_bHardwareInstancing(true)
{
	Initialize(1024,768);
}

SwRender::SwRender( int nScreenWidth, int nScreenHeight ):
	m_bHardwareInstancing(true)
{
	Initialize(nScreenWidth, nScreenHeight);
}

SwRender::~SwRender()
{
	Destroy();
}

void SwRender::Destroy()
{
	if (m_bDoodadRenderFlag)
	{
		delete [] m_bDoodadRenderFlag;
		m_bDoodadRenderFlag = NULL;
		m_nDoodadRenderFlagNumber = -1;
	}
}

// Light
void SwRender::SetDefaultLight()
{
	InitDefaultLight();

	UpdateLight();
}

void SwRender::UpdateLight()
{
	IRenderer* RI = GetEngine()->GetRenderer();

	if(m_bLightDiffer &&  RI )
	{
		RI->SetLight( 0, &m_kD9Light );
		RI->LightEnable( 0, TRUE );
		RI->SetRenderState( D3DRS_LIGHTING, TRUE );
		m_bLightDiffer = false;
	}
}

void SwRender::SetLightDir( const Vector& dir )
{
	m_kD9Light.Direction.x = dir.x;
	m_kD9Light.Direction.y = dir.y;
	m_kD9Light.Direction.z = dir.z;
	m_bLightDiffer = true;

	UpdateLight();
}

void SwRender::SetLightAmbientColor( const NiColor& ambient )
{
	m_kD9Light.Ambient.a = 1.0f;
	m_kD9Light.Ambient.r = ambient.r;
	m_kD9Light.Ambient.g = ambient.g;
	m_kD9Light.Ambient.b = ambient.b;
	m_bLightDiffer = true;
	UpdateLight();
}

void SwRender::SetLightDiffuseColor( const NiColor& diffuse )
{
	m_kD9Light.Diffuse.a = 1.0f;
	m_kD9Light.Diffuse.r = diffuse.r;
	m_kD9Light.Diffuse.g = diffuse.g;
	m_kD9Light.Diffuse.b = diffuse.b;
	m_bLightDiffer = true;

	UpdateLight();
}

void SwRender::SetLightSpecularColor( const NiColor& specular )
{
	m_kD9Light.Specular.a = 0.0f;
	m_kD9Light.Specular.r = specular.r;
	m_kD9Light.Specular.g = specular.g;
	m_kD9Light.Specular.b = specular.b;
	m_bLightDiffer = true;
	UpdateLight();
}

void SwRender::SetFogColor( const NiColor& fogColor )
{
	m_fogProp.kFogColor.r = fogColor.r;
	m_fogProp.kFogColor.g = fogColor.g;
	m_fogProp.kFogColor.b = fogColor.b;
	m_fogProp.bShowFog = true;
	DWORD dColor = D3DCOLOR_ARGB( 255,
		(int)(fogColor.r * 255.f),
		(int)(fogColor.g * 255.f),
		(int)(fogColor.b * 255.f) );
	GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGCOLOR,  dColor );
	IRenderer* RI = GetEngine()->GetRenderer();
	D3DXCOLOR dxColor;
	dxColor.a = 1.0;
	dxColor.r = fogColor.r;
	dxColor.g = fogColor.g;
	dxColor.b = fogColor.b;	
// 	RI->SetLOD2Color((float*)&dxColor);
	GetSTSkyBox()->SetAmbientColor(dColor);
}

float SwRender::GetRealDoodadShowInstance()
{
	return 30.f;
}


void SwRender::RenderSkyBox( CWorld* world, D3DXVECTOR3& vPos )
{
	CWorldTile* worldTile = world->GetWorldBuffer()->GetActiveTile();
	if(worldTile)
		GetSTSkyBox()->RenderSkyBox( vPos, worldTile->GetSkyBoxPath() );
}

void SwRender::RenderSkyBoxWithZ( CWorld* world, D3DXVECTOR3& vPos )
{
	CWorldTile* worldTile = world->GetWorldBuffer()->GetActiveTile();
	if(worldTile)
		GetSTSkyBox()->RenderSkyBoxWithZ( vPos, worldTile->GetSkyBoxPath() );
}

void SwRender::RenderWorld( CWorld* world, FrustumEx& FrustumEx, D3DXVECTOR3 CameraPos, float totalTime, float deltaTime ,bool isRenderEffect)
{
	m_fLiquidHeight = 0.f;

	m_curTime = totalTime;
	m_deltaTime = deltaTime;
	// 递增m_renderCounter
	m_renderCounter++;
	if( m_renderCounter >= 0xFFFF )
		m_renderCounter = 0;

	m_bRenderEffect = isRenderEffect;
	CullingWorld( world, FrustumEx, CameraPos );
}

void SwRender::CullingWorld( CWorld* world, FrustumEx& FrustumEx, D3DXVECTOR3 cameraPos )
{
	CWorldTile* worldTile = world->GetWorldBuffer()->GetActiveTile();
	if( NULL == worldTile || !worldTile->IsLoad() )
	{
		m_vctRenderChunkList.clear();
		m_vctRenderLiquidChunkList.clear();
		m_vctRenderModelList.clear();
		m_vctRenderDoodadChunkList.clear();
		m_vctRenderEffect.clear();
		return;
	}


	IRenderer* RI = GetEngine()->GetRenderer();
	ClearStatistic();
	m_vctRenderEffect.clear();

	WORD dBeforeRender = HQ_TimeGetTime();
	m_bNeedUpdateModel = false;
	WORD curTime = HQ_TimeGetTime();

	// 四叉树进行可视剪裁
	if ( IsNeedCull(worldTile, FrustumEx) )
	{
		m_vctRenderChunkList.clear();
		m_vctRenderLiquidChunkList.clear();
		m_vctRenderModelList.clear();
		m_vctRenderDoodadChunkList.clear();
		//for(UINT n=0; n<CHUNK_LEVEL_MAX; n++)
		//{
		//	m_arrRenderChunks[n].clear();
		//	m_arrRenderModels[n].clear();
		//}
		//m_arrRenderChunks.Clear();
		//m_arrRenderModels.Clear();

		UnlockModelRes();
        vctChunkList.reserve(worldTile->GetChunkTotal());
		worldTile->m_tileQuadTree.ClearVisible();
        if ( m_bCulledEnable && worldTile->m_tileQuadTree.GetRootNode() != NULL)
        {
            worldTile->m_tileQuadTree.Cull(&FrustumEx,worldTile->m_tileQuadTree.GetRootNode());
            for( UINT i=0; i < worldTile->m_tileQuadTree.GetVisible().size(); i++ )
            {
                CWorldChunk* chunk = worldTile->m_tileQuadTree.GetVisible()[i];
                if( chunk )
                    vctChunkList.push_back(chunk);
            }
        }
        else
        {
            for(UINT i=0; i<worldTile->GetChunkTotal(); i++)
            {
            	CWorldChunk* chunk = worldTile->GetChunk(i);
                if( chunk )
                    vctChunkList.push_back(chunk);
            }
        }

		static float fRate = 1.5f;

        float fLiquidFar = m_fogProp.fFogFar*fRate;

		float fMinLiquidHeightToCamera = abs(cameraPos.z - m_fLiquidHeight);
        for(UINT i=0; i<vctChunkList.size(); i++)
        {
            CWorldChunk* chunk = vctChunkList[i];
			Assert( NULL != chunk );
			CNdlShapeRes* shape = worldTile->GetCResMgr()->Shape( chunk->GetShape() );
			Assert( NULL != shape );

			if( RES_INVALID_ID != chunk->GetLiquidId() ) 
			{
				// 渲染水面
                if( IsObjectVisible( shape->m_LiquidMMBox, FrustumEx) )
				{
					AddLiquidChunk(chunk, cameraPos, fLiquidFar, fMinLiquidHeightToCamera);
				}
			}

			// 渲染模型//lyh时间检测
			//WORD dBeforeRenderModel = HQ_TimeGetTime();
			RenderModel(chunk, worldTile, FrustumEx, cameraPos);
			//WORD dAfterRenderModel = HQ_TimeGetTime();
			//m_dModelRenderTime += dAfterRenderModel - dBeforeRenderModel;

			// 地表可视剪裁
			if( !IsObjectVisible( shape->m_MMBox, FrustumEx) )
				continue;

			// 注册需要渲染的地表
			if (!m_bCulledEnable || !chunk->IsCulled())
			{
				CheckLODAndDoodad(chunk, cameraPos,  worldTile);
				m_vctRenderChunkList.push_back(chunk);
				
			}
		}
	}
	else
	{
		m_bNeedUpdateModel = true;
	}
	//绘制草皮
	//RenderDoodad();
// 	if( m_vctRenderDoodadChunkList.size() )
// 	{
// 		WORD dBeforeRenderModel = HQ_TimeGetTime();
// 		for(UINT i=0; i<m_vctRenderDoodadChunkList.size(); i++)
// 		{
// 			RenderDoodad(m_vctRenderDoodadChunkList[i]);
// 		}
// 		WORD dAfterRenderModel = HQ_TimeGetTime();
// 		m_dDoodadRenderTime += dAfterRenderModel - dBeforeRenderModel;
// 	}

	// 渲染地表
	if( m_vctRenderChunkList.size() )
	{
		WORD dBeforeRendeChunk = HQ_TimeGetTime();
		RI->PrepareTerrainShader(m_BRenderDepth);
		if(m_ShadowMapShaderSetCallBack)
			m_ShadowMapShaderSetCallBack;
		for(UINT i=0; i<m_vctRenderChunkList.size(); i++)
		{
			int vertex_num = 0;
			int face_num = 0;
			if (m_vctRenderChunkList[i]->GetLoadLevel() >= CWorldChunk::eTerrainLoaded)
			{
				CWorldChunkDataLock datalock(m_vctRenderChunkList[i],CWorldChunk::eTerrain);
				try
				{
					m_vctRenderChunkList[i]->Render(&vertex_num, &face_num);//这里面进行了绘制
				}
				catch (...)
				{
#ifdef _DEBUG
					char temp[1024];
					sprintf_s(temp,1024,"严重错误，请速与客户端开发人员联系，或者记录下面的数据，ChunkLoadLevel:%d，LockStatus:%d!!!",m_vctRenderChunkList[i]->GetLoadLevel(),m_vctRenderChunkList[i]->IsDataInUsing(CWorldChunk::eTerrain));
					MessageBox(NULL,temp,"严重错误",MB_OK);
#endif					
				}
			}
			else if(!SwGlobal::s_SimpleMapLoadMode)
			{//如果地表数据还未创建完全，降低该chunk的lod等级进行绘制，防止破洞
				worldTile->GetCResMgr()->SetLODLevel(m_vctRenderChunkList[i],2);
			}

			// 统计
			if( vertex_num )
			{
				m_nChunkCount++;
				m_nChunkVertexCount += vertex_num;
				m_nChunkFaceCount += face_num;
			}
		}
		RI->EndShader();
		if (!SwGlobal::s_SimpleMapLoadMode ) //lyh++
		{
			RI->PrepareTerrainLOD2Shader();
			for(UINT i=0; i<m_vctRenderChunkList.size(); i++)
			{
				int vertex_num = 0;
				int face_num = 0;
				CWorldChunkDataLock datalock(m_vctRenderChunkList[i],CWorldChunk::eTerrainLOD);
				if (m_vctRenderChunkList[i]->GetLoadLevel() >= CWorldChunk::eTerrainLODLoaded)
				{
					m_vctRenderChunkList[i]->RenderLod2(&vertex_num, &face_num);
				}

				// 统计
				if( vertex_num )
				{
					m_nChunkCount++;
					m_nChunkVertexCount += vertex_num;
					m_nChunkFaceCount += face_num;
				}
			}
			RI->EndLOD2Shader();
		}
		WORD dAfterRendeChunk = HQ_TimeGetTime();
		m_dChunkRenderTime = dAfterRendeChunk - dBeforeRendeChunk;
		if (m_isWireFrame)
		{
			for(UINT i=0; i<m_vctRenderChunkList.size(); i++)
			{
				m_vctRenderChunkList[i]->RenderWireFrame();
			}
		}
	}
	WORD dAfterRender = HQ_TimeGetTime();
	m_dTotalRenderTime = dAfterRender - dBeforeRender ;
}


void SwRender::RenderTerrainShadow(const D3DXVECTOR3& cameraPos, float renderDistance)
{
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	pDev->SetFVF(FTerrainVertexSpecial::eFVF);

    for(UINT i=0; i<m_vctRenderChunkList.size(); i++)
    {
        int vertex_num = 0;
        int face_num = 0;

        // 计算相机到chunk中心点距离
        D3DXVECTOR3 chunkCenter;
        chunkCenter.x = m_vctRenderChunkList[i]->Origin()[0];
        chunkCenter.y = m_vctRenderChunkList[i]->Origin()[1];
        flt32* pHeight = m_vctRenderChunkList[i]->GetHeight();
        chunkCenter.z = (pHeight[0]+pHeight[1])*0.5f;

        D3DXVECTOR3 camera2chunk = chunkCenter;
        camera2chunk -= cameraPos;
        float dis = D3DXVec3Length(&camera2chunk);
        float radius = sqrt(0.5f*WORLD_CHUNKSIZE*WORLD_CHUNKSIZE 
            + (pHeight[1]-pHeight[0])*(pHeight[1]-pHeight[0])*0.25f);

        if( dis > renderDistance + radius )
            continue;

        m_vctRenderChunkList[i]->RenderShadow(&vertex_num, &face_num);

        // 统计
        m_nChunkCount++;
        m_nChunkVertexCount += vertex_num;
        m_nChunkFaceCount += face_num;
    }

	GetEngine()->GetRenderer()->SetFVF(FTerrainVertexSpecial::eFVF);
	GetEngine()->GetRenderer()->Commit();
}

void SwRender::RenderModelShadow()
{
	for(UINT i=0; i<m_vctRenderModelList.size(); i++)
	{
		int vertex_num = 0;
		int face_num = 0;
		int submodel_num = 0;
		if(!m_vctRenderModelList[i]->model || m_vctRenderModelList[i]->model->HasEmitter())
		{			
			continue;
		}

		m_vctRenderModelList[i]->model->RenderShadow();

		// 统计
		m_nModelCount++;
		m_nSubmodelCount+=submodel_num;
		m_nModelVertexCount += vertex_num;
		m_nModelFaceCount += face_num;
	}
}
void SwRender::UnlockModelRes()
{
	//手动解锁CWorldChunk::eModel
	for(UINT i=0; i<vctChunkList.size(); i++)
	{
		CWorldChunk* chunk = vctChunkList[i];
		chunk->LockFlag(true);
		chunk->MarkDataUsing(CWorldChunk::eModel,false);
		chunk->LockFlag(false);
	}
	vctChunkList.clear();
}
bool SwRender::IsModelResUnlock()
{
	return vctChunkList.size() == 0;
}

void SwRender::RenderEffect( bool bOverUI /* = false */ )
{
	m_nEffectCount = 0;
	m_dEffectRenderTime = 0;
	m_dEffectRenderTime = HQ_TimeGetTime();
	if( m_vctRenderEffect.size() )
	{
		for(UINT i=0; i<m_vctRenderEffect.size(); i++)
		{
			int vertex_num = 0;
			int face_num = 0;
			int submodel_num = 0;
			m_vctRenderEffect[i]->Render(1.f, 0, &vertex_num, &face_num, &submodel_num,  0, 0, true, bOverUI );

			// 统计
			m_nEffectCount++;
		}
	}
	m_dEffectRenderTime = HQ_TimeGetTime() - m_dEffectRenderTime;
}

void SwRender::RenderModel( CWorldChunk* chunk, CWorldTile* cachTile, 
						   FrustumEx& frustum, D3DXVECTOR3 cameraPos )
{
}

void SwRender::AdjustWindowSize( int width, int height )
{
}
void SwRender::SetShowAnimation( bool isShow )
{
	m_isDisplayAnimation	= isShow;
}
// void SwRender::RenderDoodad(CWorldChunk* chunk)
// {
// 	if( m_isDisplayDoodad ) 
// 	{		
// 		CWorldChunkDataLock lock(chunk,CWorldChunk::eDoodad);
// 		if (chunk->GetLoadLevel() < CWorldChunk::eDoodadLoaded)
// 		{
// 			return;
// 		}
// 		MexInstanceMan::BeginRender();
// 		Assert( NULL != chunk );
// 		std::vector<TDoodadLevelInfo*>& doodadList = chunk->GetDoodadList();
// 		for( size_t d=0; d<doodadList.size();++d ) 
// 		{
// 			// Start the batch
// 			TDoodadLevelInfo*	pInfo = doodadList[d];
// 			pInfo->Render();
// 
// 		}
// 		MexInstanceMan::EndRender();
// 	}
// }

void SwRender::RenderDoodad()
{
	if(! m_isDisplayDoodad ) 
	{
		return;
	}
	WORD dBeforeRenderModel = HQ_TimeGetTime();
	MexInstanceMan::BeginRender();
	CWorldTile* worldTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
	CResMgr* resMgr = worldTile->GetCResMgr();
	DWORD dwFlag = 0;
	if (worldTile->IsGrassDestBlendOne())
	{
		dwFlag |= eDstBlendOne;
	}
	if (m_nDoodadRenderFlagNumber != resMgr->GetDoodadCount())
	{
		m_nDoodadRenderFlagNumber = resMgr->GetDoodadCount();
		if (m_bDoodadRenderFlag != NULL)
		{
			delete [] m_bDoodadRenderFlag;
		}
		m_bDoodadRenderFlag = new bool[m_nDoodadRenderFlagNumber];
	}
	memset(m_bDoodadRenderFlag,0,m_nDoodadRenderFlagNumber);
	for (int nDoodad = 0; nDoodad < resMgr->GetDoodadCount(); ++nDoodad)
	{
		for(UINT nDoodadChunk=0; nDoodadChunk<m_vctRenderDoodadChunkList.size(); nDoodadChunk++)
		{
			CWorldChunk* DoodadChunk = m_vctRenderDoodadChunkList[nDoodadChunk];
			CWorldChunkDataLock lock(DoodadChunk,CWorldChunk::eDoodad);
			if (DoodadChunk->GetLoadLevel() < CWorldChunk::eDoodadLoaded)
			{
				continue;
			}
			std::vector<TDoodadLevelInfo*>& doodadList0 = DoodadChunk->GetDoodadList();
			for( size_t d0=0; d0<doodadList0.size();++d0 ) 
			{
				// Start the batch
				TDoodadLevelInfo*	pDoodadInfo = doodadList0[d0];
				if (nDoodad != pDoodadInfo->mdoodadId)
				{
					continue;
				}
				if (m_bDoodadRenderFlag[nDoodad] == false)
				{
					m_bDoodadRenderFlag[nDoodad] = true;
					CDoodadRes* pRes = resMgr->GetDoodadRes(nDoodad);
					for (int nPartIndex = 0; nPartIndex < pRes->GetPartCount(); ++nPartIndex)
					{
						bool bFirst = true;					
						for(UINT nChunk=0; nChunk<m_vctRenderDoodadChunkList.size(); nChunk++)
						{
							CWorldChunk* chunk = m_vctRenderDoodadChunkList[nChunk];
							if (nChunk != nDoodadChunk)
							{
								chunk->MarkDataUsing(CWorldChunk::eDoodad,true);
								if (chunk->GetLoadLevel() < CWorldChunk::eDoodadLoaded)
								{
									chunk->MarkDataUsing(CWorldChunk::eDoodad,false);
									continue;
								}
							}
							std::vector<TDoodadLevelInfo*>& doodadList = chunk->GetDoodadList();
							for( size_t d=0; d<doodadList.size();++d ) 
							{
								// Start the batch
								TDoodadLevelInfo*	pInfo = doodadList[d];
								if (pInfo->mdoodadId == nDoodad)
								{
									if (bFirst == true)
									{
										if (pInfo->BeginRender(nPartIndex,dwFlag))
										{
											bFirst = false;
										}
									}
									pInfo->DoRender(nPartIndex);						
								}
							}
							if (nChunk != nDoodadChunk)
							{
								chunk->MarkDataUsing(CWorldChunk::eDoodad,false);
							}
						}
					}
				}
			}
		}
	}
	MexInstanceMan::EndRender();
	WORD dAfterRenderModel = HQ_TimeGetTime();
	m_dDoodadRenderTime += dAfterRenderModel - dBeforeRenderModel;


}

void SwRender::ClearStatistic()
{
	m_nModelCount = 0;
	m_nSubmodelCount = 0;
	m_nModelFaceCount = 0;
	m_nModelVertexCount = 0;
	m_nChunkCount = 0;
	m_nChunkFaceCount = 0;
	m_nChunkVertexCount = 0;
	m_dModelRenderTime = 0;
	m_dChunkRenderTime = 0;
	m_dDoodadRenderTime = 0;
}

void SwRender::AddLiquidChunk( CWorldChunk* chunk, D3DXVECTOR3 &cameraPos, float fLiquidFar, float fMinLiquidHeightToCamera )
{
		float fChunkLiquidHeight = chunk->GetLiquidHeight();
		float fLiquidDeltaHeight = abs(cameraPos.z - fChunkLiquidHeight);
		if( fLiquidDeltaHeight < fMinLiquidHeightToCamera )
		{
			m_fLiquidHeight = fChunkLiquidHeight;
			fMinLiquidHeightToCamera = fLiquidDeltaHeight;
		}
		m_vctRenderLiquidChunkList.push_back(chunk);
}

void SwRender::CheckLODAndDoodad( CWorldChunk*  chunk, D3DXVECTOR3 cameraPos, CWorldTile* worldTile )
{
	m_vctRenderDoodadChunkList.push_back(chunk);
}

void SwRender::CombineShadowDecal( swDecalShapeVertex* pVertex, int iVertexCount, unsigned short* pIndex, int iFaceCount, int iTexId )
{
	;
}
bool SwRender::IsObjectVisible( SBBox& Box, FrustumEx& kFrustumEx )
{
	guardfunc;
	if( kFrustumEx.BBoxCrossFrustum( Box, false ) != FrustumEx::cross_exclude )
	{
		return true;
	}

	return false;
	unguard;
}

void SwRender::InitDefaultLight()
{
	m_kD9Light.Type = D3DLIGHT_DIRECTIONAL;

	m_kD9Light.Diffuse.a = 1.0f;
	m_kD9Light.Diffuse.r = 1.0f;
	m_kD9Light.Diffuse.g = 1.0f;
	m_kD9Light.Diffuse.b = 1.0f;

	m_kD9Light.Ambient.a = 1.0f;
	m_kD9Light.Ambient.r = 0.5f;
	m_kD9Light.Ambient.g = 0.5f;
	m_kD9Light.Ambient.b = 0.5f;

	m_kD9Light.Specular.a = 0.0f;
	m_kD9Light.Specular.r = 0.3f;
	m_kD9Light.Specular.g = 0.3f;
	m_kD9Light.Specular.b = 0.3f;

	m_kD9Light.Position = D3DXVECTOR3( 6, -6, 6 );

	m_kD9Light.Direction = D3DXVECTOR3( -6.0f, 1, -1 );

	m_kD9Light.Range = 10000.0f;
	m_kD9Light.Falloff = 1.0f;

	m_kD9Light.Attenuation0 = 0.0f;
	m_kD9Light.Attenuation1 = 0.7f;
	m_kD9Light.Attenuation2 = 0.03f;
}

void SwRender::Initialize( int nScreenWidth, int nScreenHeight )
{
	m_screenWidth		= nScreenWidth /*- 2 * GetSystemMetrics(SM_CXBORDER)*/;
	m_screenHeight		= nScreenHeight/* -  GetSystemMetrics(SM_CYCAPTION) - 2 * GetSystemMetrics(SM_CXBORDER)*/;
	m_renderCounter			= 0;
	m_curTime			= 0.0f;
	m_deltaTime			= 0.0f;
	m_isDisplayAnimation= true;
	m_isDisplayDoodad	= true;
	m_isDisplayLiquid	= true;
	m_isWireFrame		= false;
	m_fNearPlane		= 0.25f;
	m_fogProp.bShowFog = false;
	m_fogProp.kFogColor = SwGlobal::s_globalDefaultFogColor;
	m_fogProp.fFogNear	= 20.f;
	m_fogProp.fFogFar	= 140.f;
	m_fogProp.fFarPlane = DEFAULT_FAR_PLANE;
	m_farChunk			= MAX_FAR_CHUNK/2;
	m_fLiquidHeight		= 0.f;
	m_bCulledEnable		= true;
	m_bNeedFade			= true;
	m_bRenderEffect		= true;
	m_dwLockMaxTime		= 100;
	m_bNeedUpdateModel	= false;
	m_bLightDiffer		= true;
	m_bDoodadRenderFlag	= NULL;
	m_nDoodadRenderFlagNumber = -1;
	//  jiayi, [2009.4.14]
	/*GetSTSkyBox()->m_bCanRender = true;*/
	InitDefaultLight();
	m_BRenderDepth = false;

	m_ShadowMapShaderSetCallBack = NULL;
	
}

void SwRender::RenderLiquid_High()
{	
	IRenderer* RI = GetEngine()->GetRenderer();
	if(m_isDisplayLiquid && m_vctRenderLiquidChunkList.size() )
	{
		RI->PrepareLiquidShader_High();
		//ShaderMgr->m_pWorldEffect->SetTexture( ShaderMgr->m_hTxReflect, ShaderMgr->m_pWaterRefTex);
		for(UINT i=0; i<m_vctRenderLiquidChunkList.size(); i++)
		{
			CWorldChunkDataLock datalock(m_vctRenderLiquidChunkList[i],CWorldChunk::eTerrain);
			if (m_vctRenderLiquidChunkList[i]->GetLoadLevel() >= CWorldChunk::eTerrainLoaded)
			{
				int vertex_num = 0;
				int face_num = 0;
				m_vctRenderLiquidChunkList[i]->RenderLiquid_High(&vertex_num, &face_num);

				// Í³¼Æ
				m_nChunkVertexCount += vertex_num;
				m_nChunkFaceCount += face_num;
			}
		}
		if (m_isWireFrame)
		{
			for(UINT i=0; i<m_vctRenderLiquidChunkList.size(); i++)
			{
				CWorldChunkDataLock datalock(m_vctRenderLiquidChunkList[i],CWorldChunk::eTerrain);
				if (m_vctRenderLiquidChunkList[i]->GetLoadLevel() >= CWorldChunk::eTerrainLoaded)
				{
					m_vctRenderLiquidChunkList[i]->RenderWireFrame(true);
				}
			}
		}
		RI->EndShader();
	}
}

void SwRender::RenderLiquid()
{	
	IRenderer* RI = GetEngine()->GetRenderer();
	if(m_isDisplayLiquid && m_vctRenderLiquidChunkList.size() )
	{
		RI->PrepareLiquidShader();		
		for(UINT i=0; i<m_vctRenderLiquidChunkList.size(); i++)
		{
			int vertex_num = 0;
			int face_num = 0;
			CWorldChunkDataLock datalock(m_vctRenderLiquidChunkList[i],CWorldChunk::eTerrain);
			if (m_vctRenderLiquidChunkList[i]->GetLoadLevel() >= CWorldChunk::eTerrainLoaded)
			{
				m_vctRenderLiquidChunkList[i]->RenderLiquid(&vertex_num, &face_num);
			}

			// 统计面数和顶点数
			m_nChunkVertexCount += vertex_num;
			m_nChunkFaceCount += face_num;
		}
		if (m_isWireFrame)
		{
			for(UINT i=0; i<m_vctRenderLiquidChunkList.size(); i++)
			{
				CWorldChunkDataLock datalock(m_vctRenderLiquidChunkList[i],CWorldChunk::eTerrain);
				if (m_vctRenderLiquidChunkList[i]->GetLoadLevel() >= CWorldChunk::eTerrainLoaded)
				{
					m_vctRenderLiquidChunkList[i]->RenderWireFrame(true);
				}
			}
		}
		RI->EndShader();
	}
}

void SwRender::RenderLiquidReflect(MeCamera* pCamera, float fFov, D3DXVECTOR3& vPos, CWorld* world, float totalTime, float deltaTime)
{
	if( m_vctRenderLiquidChunkList.empty( ) )
		return;

	CShaderMgr* ShaderMgr=GetShaderMgr();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	LPDIRECT3DSURFACE9 pRenderTarget;
	// 保存渲染表面
	pDev->GetRenderTarget(0 , &pRenderTarget);
	if( !pRenderTarget )
		return;

	SetNeedFade( false );
	//需要加在外面
// 	if( ShaderMgr->GetWaterType()<=1 || g_bNeedRenderSky || (!m_bCanSeeWater) )	
// 	{
// 		return ;
// 	}	
	RendererDx* RI = (RendererDx*)GetEngine()->GetRenderer();
	D3DXMATRIX mOldWorldView = RI->GetViewMatrix();
	D3DXVECTOR3 vLookAt = pCamera->GetLookatPt();
	D3DXVECTOR3 vEyeAt = pCamera->GetEyePt();
	D3DXVECTOR3 vUp = pCamera->GetUpVec();

	
		

	//定义一个翻转的参考平面，可根据需要自己定义位置及法线
	float fWaterHeight = m_fLiquidHeight;
	D3DXVECTOR3 vPoint(0,0,fWaterHeight);

	D3DXVECTOR3 vNormal(0,0,1);

	D3DXMATRIXA16 matView, matReflect;
	D3DXPLANE plane;		
	D3DXPlaneFromPointNormal( &plane, &vPoint, &vNormal ); //生成这个平面
	
	float fEyeZ = fWaterHeight - vEyeAt.z + fWaterHeight;
	float fLookAtZ = fWaterHeight - vLookAt.z + fWaterHeight;
 	D3DXVECTOR3 vNewEyeAt =  D3DXVECTOR3(vEyeAt.x, vEyeAt.y, fEyeZ);
	D3DXVECTOR3 vNewLookAt = D3DXVECTOR3(vLookAt.x, vLookAt.y, fLookAtZ);	

 	D3DXMatrixLookAtRH( &matView, &vNewEyeAt, &vNewLookAt, &(vUp) );
	
 	RI->SetTransform(D3DTS_VIEW, (float*)&matView);
	pCamera->SetViewParams(vNewEyeAt, vNewLookAt, vUp);

	FrustumEx FrustumEx;	
	FrustumEx.BuildFrustum( pCamera->GetProjMatrix(),pCamera->GetViewMatrix() );	

	
	// 设置我们的贴图表面
	pDev->SetRenderTarget(0 , ShaderMgr->m_pWaterRefSur);
	// 清空场景，渲染到贴图的背景是雾色的
	pDev->Clear( 0L, 0 ,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER ,
		D3DCOLOR_ARGB(255,(int)m_fogProp.kFogColor.r,
		(int)m_fogProp.kFogColor.g,
		(int)m_fogProp.kFogColor.b), 1.0f, 0L );
	// 开始渲染到贴图
	if(SUCCEEDED(pDev->BeginScene()))
	{		
		D3DXPlaneNormalize( &plane, &plane );

		D3DXMATRIXA16 mViewProjectionInvTrans;
		D3DXMatrixInverse( &mViewProjectionInvTrans, 0, &pCamera->GetViewXProj() );
		D3DXMatrixTranspose( &mViewProjectionInvTrans, &mViewProjectionInvTrans );
		D3DXPLANE waterPlaneW;
		D3DXPlaneTransform( &waterPlaneW, &plane, &mViewProjectionInvTrans );

		pDev->SetRenderState( D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0 );
		pDev->SetClipPlane( 0, (float*)waterPlaneW );			

		RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
		RI->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );

		FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;
		pCamera->SetProjParams( fFov, fAspect, 1.0f, 100000.0f );
		RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&pCamera->GetProjMatrix() );
		RenderSkyBox( world, vPos );	
		MeRenderManager::Instance()->DoRender(false);
		pCamera->SetProjParams( fFov, fAspect, GetNearPlane(), GetFarPlane() );
		RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&pCamera->GetProjMatrix() );
		
		RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
		RI->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
		RenderWorld(world, FrustumEx, vNewEyeAt, totalTime, deltaTime,false);		
		MeRenderManager::Instance()->DoRender(false);
		GetEngine()->GetRenderer()->Flush( 0 );		
		GetEngine()->GetRenderer()->Flush( eSortByFarZ );
		MeRenderManager::Instance()->Clear();
		pDev->EndScene();
		pDev->SetRenderState( D3DRS_CLIPPLANEENABLE, 0x00 );
	}
	// 恢复渲染表面为显示器
	pDev->SetRenderTarget(0 , pRenderTarget);
	SafeRelease(pRenderTarget);

	RI->SetTransform(D3DTS_VIEW, (float*)&mOldWorldView);
	pCamera->SetViewParams(vEyeAt, vLookAt, vUp);
	SetNeedFade( true );

	D3DXMATRIXA16 mworld;
	D3DXMatrixIdentity(&mworld);
	RI->SetTransform( D3DTS_WORLD, (float*)&mworld );

	//D3DXSaveSurfaceToFile("d:\\w.bmp", D3DXIFF_BMP,  ShaderMgr->m_pWaterRefSur, 0, 0);
	//pCamera->SetViewParams(vEyeAt, vLookAt, vUp);
}

void SwRender::RenderLiquidRefract(MeCamera* pCamera, float fFov, D3DXVECTOR3& vPos, CWorld* world, float totalTime, float deltaTime)
{
	CShaderMgr* ShaderMgr=GetShaderMgr();
	//需要加在外面
	// 	if( ShaderMgr->GetWaterType()<=1 || g_bNeedRenderSky || (!m_bCanSeeWater) )	
	// 	{
	// 		return ;
	// 	}	
	RendererDx* RI = (RendererDx*)GetEngine()->GetRenderer();
	D3DXMATRIX mOldWorldView = RI->GetViewMatrix();
	D3DXVECTOR3 vLookAt = pCamera->GetLookatPt();
	D3DXVECTOR3 vEyeAt = pCamera->GetEyePt();
	D3DXVECTOR3 vUp = pCamera->GetUpVec();
	//ShaderMgr->m_pWorldEffect->SetVector( "g_vEyePos",&D3DXVECTOR4(vEyeAt.x,vEyeAt.y,vEyeAt.z,0));

	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();


	//定义一个翻转的参考平面，可根据需要自己定义位置及法线
	float fWaterHeight = m_fLiquidHeight;
	D3DXVECTOR3 vPoint(0,0,fWaterHeight);

	D3DXVECTOR3 vNormal(0,0,-1);

	D3DXMATRIXA16 matView, matReflect;
	D3DXPLANE plane;
	D3DXPlaneFromPointNormal( &plane, &vPoint, &vNormal ); //生成这个平面
	FrustumEx FrustumEx;	
	FrustumEx.BuildFrustum( pCamera->GetProjMatrix(),pCamera->GetViewMatrix() );
	//pCamera->SetViewMatrix(mWorldView);

	LPDIRECT3DSURFACE9 pRenderTarget;
	// 保存渲染表面
	pDev->GetRenderTarget(0 , &pRenderTarget);
	// 设置我们的贴图表面
	// 水面反光暂时不用，先注掉[QL]
	//ShaderMgr->m_pWaterRefraTex->GetSurfaceLevel(0 , &ShaderMgr->m_pWaterRefraSur);//?
	pDev->SetRenderTarget(0 , ShaderMgr->m_pWaterRefraSur);
	// 清空场景，渲染到贴图的背景是雾色的
	pDev->Clear( 0L, 0 ,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER ,
		D3DCOLOR_ARGB(255,(int)m_fogProp.kFogColor.r,
		(int)m_fogProp.kFogColor.g,
		(int)m_fogProp.kFogColor.b), 1.0f, 0L );
	// 开始渲染到贴图
	if(SUCCEEDED(pDev->BeginScene()))
	{		
		D3DXPlaneNormalize( &plane, &plane );

		D3DXMATRIXA16 mViewProjectionInvTrans;
		D3DXMatrixInverse( &mViewProjectionInvTrans, 0, &pCamera->GetViewXProj() );
		D3DXMatrixTranspose( &mViewProjectionInvTrans, &mViewProjectionInvTrans );
		D3DXPLANE waterPlaneW;
		D3DXPlaneTransform( &waterPlaneW, &plane, &mViewProjectionInvTrans );

		pDev->SetRenderState( D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0 );
		pDev->SetClipPlane( 0, (float*)waterPlaneW );			

		RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
		RI->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
		
		RenderWorld(world, FrustumEx, vEyeAt, totalTime, deltaTime,false);				

		GetEngine()->GetRenderer()->Flush( 0 );
		GetEngine()->GetRenderer()->Flush( eSortByFarZ );
		MeRenderManager::Instance()->Clear();
		pDev->EndScene();
		pDev->SetRenderState( D3DRS_CLIPPLANEENABLE, 0x00 );
	}
	// 恢复渲染表面为显示器
	pDev->SetRenderTarget(0 , pRenderTarget);

	//D3DXSaveSurfaceToFile("d:\\w.bmp", D3DXIFF_BMP,  ShaderMgr->m_pWaterRefraSur, 0, 0);
	//pCamera->SetViewParams(vEyeAt, vLookAt, vUp);
}

void SwRender::SetFarChunk( float nFarChunk )
{
	//UpdateFarFog(m_fogProp.fFogFar *(nFarChunk/m_farChunk) );
	m_farChunk = nFarChunk;
}

float SwRender::GetFarChunk() const
{
	return m_farChunk;
}


float SwRender::GetFarPlane() const
{
	return m_fogProp.fFarPlane + m_farChunk * 8;// 向后延伸最远chunk的单位 [3/9/2011 zhangjiayi]
}


#define FtoDW(x) *((DWORD*)(&x))
void SwRender::SetFogDepth( flt32 fogNear, flt32 fogFar )
{
	flt32 fOldFogFar = m_fogProp.fFogFar;
	m_fogProp.fFogFar  = fogFar;//*(m_farChunk*2/MAX_FAR_CHUNK);
	m_fogProp.fFogNear = fogNear;
	m_fogProp.fFarPlane = m_fogProp.fFarPlane - fOldFogFar+ m_fogProp.fFogFar;
	m_fogProp.bShowFog = true;
	SetRenderFog(m_fogProp.fFogNear, m_fogProp.fFogFar);
}

void SwRender::SetFogDepthByCommand( flt32 fogNear, flt32 fogFar )
{
	float scale = fogFar/m_fogProp.fFogFar;
	m_fogProp.fFogFar  = fogFar;
	m_fogProp.fFogNear = fogNear;
	m_fogProp.bShowFog = true;
	// modified, jiayi, [2009.5.10]
	m_fogProp.fFarPlane = /*m_fogProp.fFarPlane - */m_fogProp.fFogFar + 80.f;// + m_fogProp.fFogFar*scale;
	SetRenderFog(fogNear, fogFar);
}

void SwRender::UpdateFarFog( float fFarFog )
{
	float scale = fFarFog/m_fogProp.fFogFar;
	m_fogProp.fFarPlane = m_fogProp.fFarPlane - m_fogProp.fFogFar + m_fogProp.fFogFar*scale;
	m_fogProp.fFogNear = m_fogProp.fFogNear/* * scale*/; 
	m_fogProp.fFogFar = m_fogProp.fFogFar * scale;
	SetRenderFog(m_fogProp.fFogNear,m_fogProp.fFogFar);
}

void SwRender::SetRenderFog( flt32 fogNear, flt32 fogFar )
{
	float fogN = fogNear;//(1-fogNear)*CULL_DISTANCE*0.8f;
	float fogF = fogFar;//CULL_DISTANCE*0.8f;
    if( GetEngine() && GetEngine()->GetRenderer() )
    {
	    GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGVERTEXMODE,  D3DFOG_NONE );
	    GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGTABLEMODE,   D3DFOG_LINEAR );
	    GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGSTART,   *(DWORD *)(&fogN));
	    GetEngine()->GetRenderer()->SetRenderState( D3DRS_FOGEND,     *(DWORD *)(&fogF));
    }
}

float SwRender::GetModelCullFar()
{
	return 0.f;
}

void SwRender::ResetFarplane()
{
	m_fogProp.fFarPlane = DEFAULT_FAR_PLANE;
	m_fogProp.fFogNear	= 20.f;
	m_fogProp.fFogFar	= 140.f;
}


void SwRender::OnDeviceLost()
{
}

void SwRender::OnDeviceReset()
{
}

void SwRender::CalTextureLOD( CWorldChunk* pChunk,float camera2chunk )
{
// 	pChunk->SetTextureLODLevel(2);
// 	return;
	int nChunk = ZnFloor2Int(camera2chunk + WORLD_CHUNKSIZE/2)/WORLD_CHUNKSIZE;

	if (nChunk < 2)
	{
		pChunk->SetTextureLODLevel(nChunk);
	}
// 	else if(nChunk < 5)
// 	{
// 		pChunk->SetTextureLODLevel(nChunk/2 + 1);
// 	}
	else 
	{
		pChunk->SetTextureLODLevel(2);
	}
}

void SwRender::GenerateLightView( CWorldTile *worldTile, sInt32 size, D3DMATRIX &outMat_LightWVP, bool saveToFile ,bool OnlyCal )
{

	if (worldTile == NULL || !worldTile->IsLoad())
		return;

	RendererDx *RI = (RendererDx *) GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	flt32 worldWidth = worldTile->GetWidth();
	flt32 worldHeight = worldTile->GetDepth();

	flt32 maxDimension = worldWidth > worldHeight ? worldWidth : worldHeight ;
	maxDimension += 20;

	int texWidth = size;
	int texHeight = size;

	D3DVIEWPORT9 oldViewport;
	pd3dDevice->GetViewport(&oldViewport);
	D3DXMATRIX matOldView = RI->GetViewMatrix();
	D3DXMATRIX matOldProj = RI->GetProjectMatrix();

	float _cameraFar = Config::GetCamera()->GetFarPlane();
	
	D3DVIEWPORT9 newViewport;
	newViewport.X = 0;
	newViewport.Y = 0;
	newViewport.Width = texWidth;
	newViewport.Height = texHeight;
	newViewport.MinZ = 0.0f;
	newViewport.MaxZ = 1.0f;

	if(!OnlyCal)
	RI->SetViewport(&newViewport);

	LPDIRECT3DTEXTURE9 pRenderTex = 0;
	LPDIRECT3DSURFACE9 pRenderDepthSurface = 0;
	if(!OnlyCal)
	{
		if (FAILED(pd3dDevice->CreateTexture(texWidth, texHeight, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_R32F, D3DPOOL_DEFAULT, &pRenderTex, NULL )))
		{
			return;
		}

		if (FAILED(pd3dDevice->CreateDepthStencilSurface(texWidth, texHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE,
			0, TRUE, &pRenderDepthSurface, 0)))
		{
			pRenderTex->Release();
			return;
		}


	}

	LPDIRECT3DSURFACE9 pRenderSurface = NULL, pBackBuffer = NULL, pBackDS = NULL;
	if(!OnlyCal)
	{
		pRenderTex->GetSurfaceLevel(0, &pRenderSurface);
		pd3dDevice->GetRenderTarget(0, &pBackBuffer);
		pd3dDevice->GetDepthStencilSurface(&pBackDS);

		pd3dDevice->SetRenderTarget(0, pRenderSurface);
		pd3dDevice->SetDepthStencilSurface(pRenderDepthSurface);
	}



	int l = 400.0f;
	D3DXVECTOR3 vMin(0, 0, -l );
	D3DXVECTOR3 vMax(maxDimension, maxDimension, l*1.5f );

	D3DXVECTOR3 vEyePt( vMax.x/2.5, vMax.y/2, l  );
	RendererDx* pRender =  (RendererDx*)GetEngine()->GetRenderer();
	D3DXVECTOR3 lightDir = pRender->GetLightDir(LIGHT_INDEX_TERRAIN);
	
	
	//D3DXVec3Normalize(&lightDir,&lightDir);
	//vEyePt = vEyePt - lightDir * 50.f;	
	//vEyePt.z = 400;

	
	
	D3DXVECTOR3 vLookAt( vMax.x/1.5f, vMax.y/2, -l );
	D3DXVECTOR3 vUp( 0.0f, 1.0f, 0.0f );

	D3DXMATRIX matView, matProj;
	D3DXMatrixLookAtRH( &matView, &vEyePt, &vLookAt, &vUp );
   // D3DXMatrixPerspectiveFovRH( &matProj, D3DXToRadian(60.0f), 1, 1.0f, 1000.f );
	 D3DXMatrixOrthoRH( &matProj,vMax.x - vMin.x, vMax.y - vMin.y, vMin.z, vMax.z );

	Config::GetCamera()->SetViewParams(vEyePt,vLookAt,vUp);
	//Config::GetCamera()->SetProjParams(D3DX_PI/4,D3DXToRadian(60.0f),1,1000.f);
	Config::GetCamera()->SetOrthoLH(vMin,vMax);


  // matProj = matOldProj; //lyh临时加
  // matView = matOldView; //lyh临时加
	outMat_LightWVP = matView * matProj;

if(!OnlyCal)
{
	FrustumEx frustum;
	frustum.BuildFrustum(matProj, matView);
	RI->SetEyePt( (float *) &vEyePt );
	RI->SetLookatPt( (float *) &vLookAt );
	RI->SetTransform( D3DTS_PROJECTION, (CONST FLOAT *) &matProj );
	RI->SetTransform( D3DTS_VIEW, (CONST FLOAT *) &matView );
	RI->SetRenderState( D3DRS_FOGENABLE,  FALSE );
	RI->Clear( 0L, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xffffffff, 1.0f, 0 );
	RI->BeginScene();

	// Render World To Texture
	MeRenderManager::Instance()->Clear();
	MeRenderManager::Instance()->DoRender(false);

	bool isRenderDoodad = GetRenderDoodad();
	SetRenderDoodad(false);
	SetCulledEnable(false);

	RenderWorld( SwGlobal::GetWorld(), frustum, vEyePt, 0.0f, 0.0f);

	RenderLiquid();
	RenderEffect();
	SetRenderDoodad(isRenderDoodad);
	SetCulledEnable(true);

	RI->Flush( eSortByFarZ );
	MeRenderManager::Instance()->DoRender(true);
	RI->EndScene();

}
	

	


	



	


	if (saveToFile && !OnlyCal)
	{



		
		char szSubFolder[MAX_PATH] = {0};
		sprintf_s(szSubFolder, sizeof(szSubFolder)-1, "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), "ShowMap.dds");//lyh改路径光照图
		D3DXSaveSurfaceToFile( szSubFolder,D3DXIFF_DDS,pRenderSurface,NULL,NULL);


		//char szLightmapDDS[MAX_PATH] = {0};
		//sprintf_s(szLightmapDDS, sizeof(szLightmapDDS)-1, "%s\\ShowMap.dds",
		//	SwGlobal::GetWorld()->GetWorldPath());//lyh改路径 光照图

		//DeleteFile(szLightmapDDS);

		//PROCESS_INFORMATION pi;
		//STARTUPINFO si = {sizeof(si)};
		//char szCommand[1024] = {0};
		//char szExeFileName[128] = "DxTex.exe";
		//sprintf( szCommand, "%s %s -m A8R8G8B8 %s", szExeFileName, szSubFolder, szLightmapDDS );
		//BOOL ret = CreateProcess(
		//	szExeFileName,
		//	szCommand,
		//	NULL, 
		//	NULL, 
		//	FALSE, 
		//	0, 
		//	NULL, 
		//	NULL, 
		//	&si,
		//	&pi );
		//if(!ret) 
		//{
		//	MessageBox( NULL,"","缺少DxTex.exe",MB_OK );
		//	
		//}

      MessageBox( NULL,"生成成功","！",MB_OK );

	
	
		

	}

   if(!OnlyCal)
   {
	   pd3dDevice->SetRenderTarget( 0, pBackBuffer );
	   pd3dDevice->SetDepthStencilSurface(pBackDS);
	   pd3dDevice->StretchRect( pRenderSurface, NULL, pBackBuffer, NULL, D3DTEXF_LINEAR ); //缩小1


	   if( pBackBuffer )
		   pBackBuffer->Release();
	   if( pBackDS )
		   pBackDS->Release();
	   if( pRenderDepthSurface )
		   pRenderDepthSurface->Release();
	   if( pRenderSurface )
		   pRenderSurface->Release();
	   if( pRenderTex )
		   pRenderTex->Release();
	   RI->SetViewport(&oldViewport);
   }
	
	

   Config::GetCamera()->SetViewMatrix(matOldView);
   //Config::GetCamera()->SetProjParams(D3DX_PI/4,D3DXToRadian(60.0f),1,1000.f);
   Config::GetCamera()->SetProjMatrix(matOldProj);
	RI->SetTransform( D3DTS_VIEW, (float *) &matOldView);
	RI->SetTransform( D3DTS_PROJECTION, (float*)&matOldProj );
	RI->SetRenderState( D3DRS_FOGENABLE,  TRUE );

}

// TBD: 需要去除光照.
void SwRender::GenerateMinimap( CWorldTile *worldTile, sInt32 size, const char *fileName, bool saveToFile )
{
	if (worldTile == NULL || !worldTile->IsLoad())
		return;

	RendererDx *RI = (RendererDx *) GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	flt32 worldWidth = worldTile->GetWidth();
	flt32 worldHeight = worldTile->GetDepth();

	flt32 maxDimension = worldWidth > worldHeight ? worldWidth : worldHeight;

	int texWidth = size;
	int texHeight = size;

	D3DVIEWPORT9 oldViewport;
	pd3dDevice->GetViewport(&oldViewport);
	D3DXMATRIX matOldView = RI->GetViewMatrix();
	D3DXMATRIX matOldProj = RI->GetProjectMatrix();

	D3DVIEWPORT9 newViewport;
	newViewport.X = 0;
	newViewport.Y = 0;
	newViewport.Width = texWidth;
	newViewport.Height = texHeight;
	newViewport.MinZ = 0.0f;
	newViewport.MaxZ = 1.0f;
	RI->SetViewport(&newViewport);

	LPDIRECT3DTEXTURE9 pRenderTex = 0;
	LPDIRECT3DSURFACE9 pRenderDepthSurface = 0;
	if (saveToFile)
	{
		if (FAILED(pd3dDevice->CreateTexture(texWidth, texHeight, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pRenderTex, NULL )))
		{
			return;
		}

		if (FAILED(pd3dDevice->CreateDepthStencilSurface(texWidth, texHeight, D3DFMT_D24X8, D3DMULTISAMPLE_NONE,
			0, TRUE, &pRenderDepthSurface, 0)))
		{
			pRenderTex->Release();
			return;
		}
	}

	int l = 10000.0f;
	D3DXVECTOR3 vMin(0, 0, -l );
	D3DXVECTOR3 vMax(maxDimension, maxDimension, l );

	D3DXVECTOR3 vEyePt( vMax.x/2, vMax.y/2, l * 0.5f );
	D3DXVECTOR3 vLookAt( vMax.x/2, vMax.y/2, -l );
	D3DXVECTOR3 vUp( 0.0f, 1.0f, 0.0f );
	
	D3DXMATRIX matView, matProj;
	D3DXMatrixLookAtRH( &matView, &vEyePt, &vLookAt, &vUp );
	D3DXMatrixOrthoRH( &matProj,vMax.x - vMin.x, vMax.y - vMin.y, vMin.z, vMax.z );

	FrustumEx frustum;
	frustum.BuildFrustum(matProj, matView);

	RI->SetEyePt( (float *) &vEyePt );
	RI->SetLookatPt( (float *) &vLookAt );

	LPDIRECT3DSURFACE9 pRenderSurface = NULL, pBackBuffer = NULL, pBackDS = NULL;
	if (saveToFile)
	{
		pRenderTex->GetSurfaceLevel(0, &pRenderSurface);
		pd3dDevice->GetRenderTarget(0, &pBackBuffer);
		pd3dDevice->GetDepthStencilSurface(&pBackDS);

		pd3dDevice->SetRenderTarget(0, pRenderSurface);
		pd3dDevice->SetDepthStencilSurface(pRenderDepthSurface);
	}

	RI->SetTransform( D3DTS_PROJECTION, (CONST FLOAT *) &matProj );
	RI->SetTransform( D3DTS_VIEW, (CONST FLOAT *) &matView );

	RI->SetRenderState( D3DRS_FOGENABLE,  FALSE );
	RI->Clear( 0L, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255,
		255,
		255,
		255), 1.0f, 0 );
	RI->BeginScene();

	// Render World To Texture
	MeRenderManager::Instance()->Clear();
	MeRenderManager::Instance()->DoRender(false);

	bool isRenderDoodad = GetRenderDoodad();
	SetRenderDoodad(false);
	SetCulledEnable(false);
	RenderWorld( SwGlobal::GetWorld(), frustum, vEyePt, 0.0f, 0.0f);
	RenderLiquid();
	RenderEffect();
	SetRenderDoodad(isRenderDoodad);
	SetCulledEnable(true);

	RI->Flush( eSortByFarZ );
	MeRenderManager::Instance()->DoRender(true);
	RI->EndScene();

	if (saveToFile)
	{
		pd3dDevice->SetRenderTarget( 0, pBackBuffer );
		pd3dDevice->SetDepthStencilSurface(pBackDS);

		LPDIRECT3DTEXTURE9 pRenderXXTex = 0;
		LPDIRECT3DSURFACE9 pRenderXXSurface = NULL;
		{
			// 清空alpha
			if (FAILED(pd3dDevice->CreateTexture(
				texWidth,
				texHeight,
				1,
				0,
				D3DFMT_A8R8G8B8,
				D3DPOOL_SYSTEMMEM,
				&pRenderXXTex, NULL )))
				return;
			pRenderXXTex->GetSurfaceLevel(0, &pRenderXXSurface);
			pd3dDevice->GetRenderTargetData(pRenderSurface,pRenderXXSurface);
			D3DLOCKED_RECT X8rect;
			if( !FAILED( pRenderXXTex->LockRect( 0, &X8rect, 0, 0 ) ) )
			{
				int* p = (int*)X8rect.pBits;
				if( p != 0 )
				{
					for (int y = 0; y < texHeight;++y)
					{
						for(int x = 0; x < texWidth;++x)
						{
							int nIndex = x + y* texWidth;
							{
								p[nIndex] = 0xFF000000 | p[nIndex];
							}
						}
					}
				}
				pRenderXXTex->UnlockRect(0);
			}
		}

		if (fileName)
		{
			D3DXSaveTextureToFile( fileName, D3DXIFF_BMP, pRenderXXTex, NULL);
		}

		if( pBackBuffer )
			pBackBuffer->Release();
		if( pBackDS )
			pBackDS->Release();
		if( pRenderDepthSurface )
			pRenderDepthSurface->Release();
		if( pRenderSurface )
			pRenderSurface->Release();
		if( pRenderTex )
			pRenderTex->Release();
		if( pRenderXXSurface )
			pRenderXXSurface->Release();
		if( pRenderXXTex )
			pRenderXXTex->Release();
	}

	RI->SetViewport(&oldViewport);
	RI->SetTransform( D3DTS_VIEW, (float *) &matOldView);
	RI->SetTransform( D3DTS_PROJECTION, (float*)&matOldProj );
	RI->SetRenderState( D3DRS_FOGENABLE,  TRUE );
}