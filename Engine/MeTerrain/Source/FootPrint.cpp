/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	FootPrint.cpp
* Create: 	10/06/2006
* Desc:		数据资源基类
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/FootPrint.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine\rendererdx.h"
////////////////////////////////////////////////////////////////////////////////
DWORD CFootPrint::m_timeInterval = 200;
bool CFootPrint::m_intialize = false;
char* CFootPrint::m_TypeIdentify[TotalPlayerPrintType] =
{
	"xue_",
	"sha_"
};
int CFootPrint::m_texId[TotalPlayerPrintType][2] = {-1};

CFootPrint::CFootPrint(bool val)
:
m_bRightOrFront(true)
,m_footPrintType(eTwoFoot)
,m_fdeltaForBody(0.11)
,m_stepLength(0.9)
,m_scale(0.22)
{
	m_oldTime = ::GetTickCount();
	m_isMonster = val;
	m_leftOrBackFootId =  -1;
	m_rightOrFrontFootId = -1;
	if (!m_intialize)
	{
		m_intialize = true;
		char filename[MAX_PATH];
		sprintf(filename, "%s\\Data\\TEXTURE\\Effect\\leftFootOnSnow.tga", GetRootPath());
		m_texId[SnowPrint][0] = 	GetEngine()->GetTextureManager()->RegisterTexture( filename, false ,FALSE);
		sprintf(filename, "%s\\Data\\TEXTURE\\Effect\\rightFootOnSnow.tga", GetRootPath());
		m_texId[SnowPrint][1] = 	GetEngine()->GetTextureManager()->RegisterTexture( filename, false ,FALSE);
		
		sprintf(filename, "%s\\Data\\TEXTURE\\Effect\\leftFootOnSand.tga", GetRootPath());
		m_texId[SandPrint][0] = 	GetEngine()->GetTextureManager()->RegisterTexture( filename, false ,FALSE);
		sprintf(filename, "%s\\Data\\TEXTURE\\Effect\\rightFootOnSand.tga", GetRootPath());
		m_texId[SandPrint][1] = 	GetEngine()->GetTextureManager()->RegisterTexture( filename, false ,FALSE);
	}
}

CFootPrint::~CFootPrint()
{
	Reset();
}

void CFootPrint::Update()
{
	DWORD nowTime = ::GetTickCount();
	if (nowTime - m_oldTime > m_timeInterval)
	{
		m_oldTime = nowTime;

		if (CFootPrintMgr::Instance()->Empty())
			m_renderRes.clear();

		for (decalResArr::iterator iter = m_renderRes.begin(); iter != m_renderRes.end();)
		{
			CFootDecalRes* res = (*iter);
			res->DecreaseAlpha();
			if (res->m_bEnble == false)
			{
				CFootPrintMgr::Instance()->AddToCache(res);
				iter = m_renderRes.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CFootPrint::Render()
{
	if (CFootPrintMgr::Instance()->Empty())
		m_renderRes.clear();

	for (decalResArr::iterator iter = m_renderRes.begin(); iter != m_renderRes.end();++iter)
	{
		CFootDecalRes* res = (*iter);
		assert(res->m_bEnble);
		res->m_pRes->Render();
	}

}

void CFootPrint::AddFootPrint( D3DVECTOR pos,flt32 angle)
{
	CWorldTile* pTile = CURRENTTILE;
	if(NULL == pTile)
		return;
	if (m_bRightOrFront)
	{
		if (eTwoFoot == m_footPrintType)
		{
			pos.x -= cos(angle-D3DX_PI/2)*m_fdeltaForBody;
			pos.y -= sin(angle-D3DX_PI/2)*m_fdeltaForBody;
		}
		else
		{
			pos.x -= cos(angle)*m_fdeltaForBody;
			pos.y -= sin(angle)*m_fdeltaForBody;
		}
	}
	else
	{
		if (eTwoFoot == m_footPrintType)
		{
			pos.x += cos(angle-D3DX_PI/2)*m_fdeltaForBody;
			pos.y += sin(angle-D3DX_PI/2)*m_fdeltaForBody;
		}
		else
		{
			pos.x += cos(angle)*m_fdeltaForBody;
			pos.y += sin(angle)*m_fdeltaForBody;
		}

	}
	CWorldChunk* pChunk = pTile->GetChunkFromPos(pos.x,pos.y);
	if (pChunk == NULL || pChunk->IsCulled())
	{
		return;
	}
	CResMgr* pMgr = pTile->GetCResMgr(); 
	int layoutCount = pChunk->GetLayerCount();
	int printType = SnowPrint;
	int printLevel= layoutCount;
	bool bPrintExistArr[TextureLayerFlight] = {false};
	if(!GetPrintInfo(pChunk, pMgr, printType, printLevel,bPrintExistArr))
	{
		return;
	}
	assert(printLevel != layoutCount);
	int texture  = GetCurrTexture(printType);
	if (texture == -1)
	{
		return;
	}
	sInt32 nX = AtomFromPos(pos.x - WORLD_CHUNK_ORIGIN) % WORLD_TILE_CHUNK_ATOM_NUM;
	sInt32 nY = AtomFromPos(pos.y - WORLD_CHUNK_ORIGIN) % WORLD_TILE_CHUNK_ATOM_NUM;
	int nIndex = nX + nY * WORLD_TILE_CHUNK_ATOM_NUM;

	TextureDx8* pMask = (TextureDx8*)pMgr->Mask( pChunk->GetMaskId() );
	if (pMask == NULL)
	{
		return;
	}

	LPDIRECT3DTEXTURE9 m_pd3dTexture = pMask->GetTexture();
	D3DLOCKED_RECT rect;
	if( FAILED( m_pd3dTexture->LockRect( 0, &rect, 0, 0 ) ) )
	{
		return ;
	}
	int* p = (int*)rect.pBits;
	BYTE btAlpha[TextureLayerFlight];
	btAlpha[0] = 0xFF;
	if( p != 0 )
	{
		for (int i = layoutCount - 1; i >= max(printLevel,1);--i )
		{
			btAlpha[i]  = 0xff - ((p[nIndex] >> ((3 - i)*8)) & 0xff);
		}
	}
	m_pd3dTexture->UnlockRect(0);

	for (int i = printLevel+1; i < layoutCount ;++i )
	{
		if (bPrintExistArr[i])
		{
			btAlpha[printLevel] = btAlpha[printLevel] + btAlpha[i]*(int)(0xFF - btAlpha[printLevel])/0xFF;
		}
		else
		{
			btAlpha[printLevel] = btAlpha[printLevel]*(int)(0xFF - btAlpha[i])/0xFF;
		}
	}

	if (btAlpha[printLevel] == 0)
	{
		return;
	}
	CFootDecalRes* pRes = CFootPrintMgr::Instance()->RetriveFootDecelByTextureId(texture);
	assert(pRes);
  	angle += D3DX_PI/2;
	pRes->m_pRes->SetScale(m_scale);
	pRes->m_pRes->SetPos((flt32*)(&pos),&angle);
	pRes->m_bEnble = true;
	pRes->mcAlpha = btAlpha[printLevel];
	m_renderRes.push_back(pRes);

}

bool CFootPrint::GetPrintInfo( CWorldChunk* pChunk, CResMgr* pMgr, int &printType, int &printLevel,bool* bPrintExistArr )
{
	int layoutCount = pChunk->GetLayerCount();
	printType = layoutCount;
	for (int i = layoutCount - 1; i >= 0; --i)
	{
		CNdlTextureRes* pRes = pMgr->GetTexture(pChunk->GetTexture(i));
		for (int ty = 0; ty < TotalPlayerPrintType; ++ty)
		{
			//if(strstr(pRes->GetName(),m_TypeIdentify[ty]))
			{
				printType = ty;
				printLevel = i;
				bPrintExistArr[i] = true;
				continue;
			}
		}
	}
	return (printType != layoutCount);
}

int CFootPrint::GetCurrTexture( int printType )
{
	if (!m_isMonster && eTwoFoot == m_footPrintType)
	{
		m_leftOrBackFootId = m_texId[printType][0];
		m_rightOrFrontFootId = m_texId[printType][1];
	}
	int texture = m_leftOrBackFootId;
	if (m_bRightOrFront)
	{
		texture = m_rightOrFrontFootId;
	}
	m_bRightOrFront = !m_bRightOrFront;
	return texture;
}

void CFootPrint::Reset()
{	
	if (CFootPrintMgr::Instance()->Empty())
		m_renderRes.clear();

	for (decalResArr::iterator iter = m_renderRes.begin(); iter != m_renderRes.end();++iter)
	{
		(*iter)->m_bEnble = false;
	}
	m_renderRes.clear();
}
BYTE CFootDecalRes::alphaDelta = 10;
CFootDecalRes::CFootDecalRes( int texture )
{
	m_pRes	 = MeNew CNdlDecalRes();
	m_pRes->Create(texture,1.0,false);
	m_pRes->SetFloorDecalEnable(false);
	mcAlpha	 = 0;
	m_bEnble = false;
}

CFootDecalRes::~CFootDecalRes()
{
	delete m_pRes;
}

void CFootDecalRes::DecreaseAlpha()
{
	if (m_pRes == NULL)
	{
		return;
	}
	mcAlpha -= alphaDelta;
	if (mcAlpha/alphaDelta == 0)
	{
		mcAlpha = 0;
		m_bEnble = false;
	}
	else
	{
		m_pRes->SetAlpha(mcAlpha);
	}
}

CFootDecalRes* CFootPrintMgr::RetriveFootDecelByTextureId( int texture )
{
	bool bFound = false;
	for (std::vector<int>::iterator iter = m_TextureTypeArr.begin(); iter != m_TextureTypeArr.end(); ++iter)
	{
		if (*iter == texture)
		{
			bFound = true;
			break;
		}
	}
	if (!bFound)
	{
		m_TextureTypeArr.push_back(texture);
	}
	CFootDecalRes* pRet = NULL;
	if (m_ResCachePool.size() > 0)
	{
		pRet= * m_ResCachePool.begin();
		m_ResCachePool.pop_front();
		pRet->m_pRes->SetDecalTexID(texture);
	}
	if (pRet == NULL)
	{
		pRet = MeNew CFootDecalRes(texture);
		m_ResPool.push_back(pRet);
	}
	return pRet;
}

bool CFootPrintMgr::Empty() const
{
	return m_ResPool.empty();
}

CFootPrintMgr::~CFootPrintMgr()
{
	clear();
}

CFootPrintMgr::CFootPrintMgr()
{

}

void CFootPrintMgr::Render()
{
			IRenderer* r = GetEngine()->GetRenderer();
			//TRUETIMEFUNC();
 			CSALocker locker((RendererDx*)r);
	for (std::vector<int>::iterator iter = m_TextureTypeArr.begin(); iter != m_TextureTypeArr.end(); ++iter)
	{
		int nMainMapID = *iter;
// 		DWORD dwFlag = eUClamp | eVClamp | eNoMipmap;
		{
			guardfunc;

// 			int nBaseVertexIndex = 0;


			LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;
// 			LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;

				ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
				if( pTexture )
				{
					d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
					if ( d3dBaseTex )
					{
						r->SetTexture( 0, d3dBaseTex );
					}
				}

// 			{
// 				r->SetTexture( 1, NULL );
// 				r->SetTexture( 2, NULL );
// 			}


			DWORD dwVertexShader = swDecalShapeVertex::eFVF;
			DWORD dwColorOp = D3DTOP_SELECTARG1;
			DWORD dwColorArg1 = D3DTA_TEXTURE;
			DWORD dwColorArg2 = D3DTA_DIFFUSE;
			DWORD dwAlphaOp = D3DTOP_DISABLE;
			DWORD dwAlphaArg1 = D3DTA_TEXTURE;
			DWORD dwAlphaArg2 = D3DTA_DIFFUSE;
			DWORD dwZEnable = TRUE;
			DWORD dwZWriteEnable = TRUE;
			DWORD dwCullMode = D3DCULL_NONE;

			DWORD dwAlphaBlendEnable = FALSE;
			//DWORD dwAlphaBlendEnable = TRUE;

			DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
			DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
			DWORD dwFillMode = D3DFILL_SOLID;
			DWORD dwShadeMode = D3DSHADE_GOURAUD;
			DWORD dwZFun = D3DCMP_LESSEQUAL;
			DWORD dwAlphaTestEnable = FALSE;

			//DWORD dwAlphaRef = 0x00000080;
			DWORD dwAlphaRef = 0x00000080;

			DWORD dwAlphaFunc = D3DCMP_GREATER;
			DWORD dwMinFilter = D3DTEXF_LINEAR;
			DWORD dwMagFilter = D3DTEXF_LINEAR;

			r->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
			r->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

			r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

			r->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );


			r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
			r->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			r->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

// 			float fBias = -1.0f;

				dwZWriteEnable = false;
				dwAlphaBlendEnable = TRUE;
				// 		dwColorOp = D3DTOP_MODULATE2X;
				// 		dwColorArg1 = D3DTA_TEXTURE;
				// 		dwColorArg2 = D3DTA_DIFFUSE;
				dwAlphaOp = D3DTOP_MODULATE;
				dwAlphaArg1 = D3DTA_TEXTURE;
				dwAlphaArg2 = D3DTA_DIFFUSE;
// 				if ( dwFlag & eUClamp )
				{
					r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
					r->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
				}
// 				if ( dwFlag & eVClamp )
				{
					r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
					r->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
				}
				dwZEnable = TRUE;

				dwZWriteEnable = TRUE;

				r->SetRenderState( D3DRS_LIGHTING, TRUE );

			{
				r->SetRenderState( D3DRS_SPECULARENABLE,FALSE );
				//	r->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2 );
			}

			//
			r->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2 );
			r->SetRenderState( D3DRS_ZENABLE, dwZEnable );
			r->SetRenderState( D3DRS_ZWRITEENABLE, dwZWriteEnable );
			r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
			r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
			r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

			r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColorArg1 );
			r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColorArg2 );
			r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );

			r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
			r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );
			r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );

				r->SetFVF( dwVertexShader );

			r->SetRenderState( D3DRS_SHADEMODE, dwShadeMode );
			r->SetRenderState( D3DRS_FILLMODE, dwFillMode );
			r->SetRenderState( D3DRS_CULLMODE, dwCullMode );
			r->SetRenderState( D3DRS_ZFUNC, dwZFun );

			r->SetRenderState( D3DRS_ALPHATESTENABLE, dwAlphaTestEnable );
			r->SetRenderState( D3DRS_ALPHAREF, dwAlphaRef );
			r->SetRenderState( D3DRS_ALPHAFUNC, dwAlphaFunc );

			r->SetSamplerState( 0, D3DSAMP_MINFILTER, dwMinFilter );
			r->SetSamplerState( 0, D3DSAMP_MAGFILTER, dwMagFilter );


				r->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

				r->SetRenderState( D3DRS_CULLMODE, dwCullMode );


			r->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );

			r->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, GetMe3dConfig()->GetFullSceneAntialiasing() );

			if ( GetMe3dConfig()->m_bAlwayseWireFrameRendering )
				r->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

			{
				r->SetStreamSource( 0, NULL, 0 );
				r->SetIndices( NULL, 0 );	
				r->Commit();

// 				graphics::Material* material = 0;
// 				if (m_pCurrentMaterial)
// 					material = m_pCurrentMaterial;
// 				else
// 					material = m_pMexMaterial;
// 
// 				if (!material->getShader())
// 				{
// 					material->setShader("MexShader");
// 				}

// 				graphics::ShaderEffect* pShaderEffect = 0;
// 				ID3DXEffect* pd3dEffect = 0;
// 				if (material && (pShaderEffect = (graphics::ShaderEffect*)material->getShader()) &&
// 					(pd3dEffect = pShaderEffect->getID3DXEffect()))
// 				{
// 					pd3dEffect->SetTexture( "baseTex", d3dBaseTex );
// 					if (d3dBrightTex)
// 					{
// 						pd3dEffect->SetTexture( "brightTex", d3dBrightTex );
// 						pd3dEffect->SetFloat( "specular", 1.0f );
// 					}
// 					else
// 						pd3dEffect->SetFloat( "specular", 0.0f );
// 
// 					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
// 					pd3dEffect->SetMatrix( "world", &m_world );
// 					pd3dEffect->SetMatrix( "worldViewProj", &wvp );
// 					pd3dEffect->SetValue( "eye", &GetMe3dConfig()->GetCamera()->GetEyePt(), sizeof(D3DXVECTOR3) );
// 					pd3dEffect->SetValue( "lightDir", &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]) );
// 					pd3dEffect->SetValue( "lightAmbient", &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]) );
// 					pd3dEffect->SetValue( "lightDiffuse", &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]) );
// 					pd3dEffect->SetValue( "lightColor", &m_lightDiffuse[LIGHT_INDEX_COLLISION], sizeof(m_lightDiffuse[LIGHT_INDEX_COLLISION]) );
// 					pd3dEffect->SetFloat( "g_FarPlane", Config::GetCamera()->GetFarPlane() );
// 					pd3dEffect->SetFloat( "alpha", m_fGlobalTransparent );
// 					pd3dEffect->CommitChanges();
				}

			for (decalResArr::iterator resIter = m_ResPool.begin(); resIter != m_ResPool.end();++resIter)
			{
				CFootDecalRes* res = *resIter;
				if (!res->m_bEnble || res->m_pRes->GetDecalTexID() != nMainMapID)
				{
					continue;
				}
				res->m_pRes->FastRenderDecal((LPDIRECT3DDEVICE9)r->GetRealDevice());
			}

			unguard;


		}
	}
}

void CFootPrintMgr::clear()
{
	for (decalResArr::iterator iter = m_ResPool.begin(); iter != m_ResPool.end(); ++iter)
	{
		delete (*iter);
	}
	m_ResPool.clear();
	m_ResCachePool.clear();
	m_TextureTypeArr.clear();
}