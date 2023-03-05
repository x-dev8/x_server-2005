///////////////////////////////////////////////////////////////////
//
// SkyBox by huihui 2007-3-28
//
///////////////////////////////////////////////////////////////////

#include "MeTerrain/stdafx.h"
#include "MeTerrain/STSkyBox.h"
#include "Me3d/Engine/EngineInstance.h"
#include "FuncPerformanceLog.h"
#include "Me3d/MathLib.h"
#include <math.h>
#include "TimeClock.h"
#include "3dsmax/gfloat.h"
#include "Me3d/Engine/RendererDx.h"
#include "MeTerrain/WorldBuffer.h"
#include "Me3d/Md5Manager.h"
// #include "Scene/DayLightAnim.h"
#include "MeTerrain/SwRender.h"
#include "Me3d/Engine/MeRenderManager.h"

#define D3DFVF_SKYBOXVERTEX ( D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define D3DFVF_CLOUDSVERTEX ( D3DFVF_XYZ  | D3DFVF_DIFFUSE )

struct SKYBOXVERTEX
{
	D3DXVECTOR3		pos;
	DWORD			color;
	float			u,v;
};



CSTSkyBox* GetSTSkyBox()
{
	guardfunc;
	static CSTSkyBox g_SkyBox;
	return &g_SkyBox;
	unguard;
};

CSTSkyBox::CSTSkyBox() : CSkyBox()
{
	guardfunc;
	m_fSkyBoxAlpha = 1.f;

	m_pSkybox = NULL;
	m_pSrcSkybox = NULL;
	m_pDestSkybox = NULL;
// 	m_pDayLightAnim = NULL;
// 	m_pLightChange = NULL;
	m_nSkyBoxModelID = -1;

// 	if( m_pSkybox == NULL )
	{
		CHAR szPath[MAX_PATH] = {0};
		sprintf( szPath, "%s%s", CWorld::GetAppDataCharDir(), "\\data\\SceneObject\\Common\\skybox\\common.mex");		

		MexAnimCtrl* pAnim = MeNew MexAnimCtrl;
		m_nSkyBoxModelID = GetMexResMgr()->AddExternalFile( szPath );
		pAnim->ChangeModel( m_nSkyBoxModelID,FALSE,NULL );
		if( !m_SkyBoxBuf.insert( std::map<std::string, MexAnimCtrl*>::value_type(szPath, pAnim) ).second )
		{
			pAnim->Destroy();
			delete pAnim;
			pAnim = NULL;
		}
		m_pSkybox = FindSkyBox( szPath );
	}		

	unguard;

}

CSTSkyBox::~CSTSkyBox()
{
	guardfunc;
	ClearDayLightAnim();
	unguard;
}

void CSTSkyBox::Release()
{
	ClearDayLightAnim();
}

void CSTSkyBox::RenderSkyBox(D3DXVECTOR3& vPos, const char* pszSkyboxPath /* = 0 */)
{
	guardfunc;
	
	if( !IsDisable() && m_bCanRender )
	{
		SetSkybox(pszSkyboxPath);
		
		RendererDx* pRender = (RendererDx*)GetEngine()->GetRenderer();
		SetSunPosition(pRender->GetLightDir(LIGHT_INDEX_TERRAIN));
		m_dwTopColor = 9024500;

		IRenderer* RI = GetEngine()->GetRenderer();
// 
// 		BOOL bChangeMode = FALSE;
// 		if( m_pLightChange )
// 		{
// 			bChangeMode = m_pLightChange->IsBeginChange();
// 		}
		static float s_fScale = 0.1f;
		static float s_fZ = -1000.f;
		if( m_pSkybox )
		{
			//m_pSkybox->UseSkinMesh( FALSE );
			m_pSkybox->SetPosition( vPos.x, vPos.y, /*GetSkyBoxHeight()*GetMe3dConfig()->m_fMdlSpaceScale*/ s_fZ);
			if( m_pSkybox->IsAni() )
				m_pSkybox->UpdateByParam( HQ_TimeGetTime() );
			else
				m_pSkybox->UpdateTransform();
			//m_pSkybox->SetRotationZ( 0 );
			LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
			RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
			{
				RI->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
				//RI->SetRenderState( D3DRS_ZENABLE, FALSE );
				//m_pSkybox->SetRenderFlag( eTwoSided | eLightingDisable | eOpModulate2X | eAlphaBlend | eZWriteDisable | eZDisable & ~eAlphaTest);
				//m_pSkybox->SetScale( GetSkyBoxScale()*GetMe3dConfig()->m_fMdlSpaceScale );
				m_pSkybox->SetRenderFlag( eRenderSkyBox | eAlphaBlend | eLightingDisable );				
				m_pSkybox->SetScale( s_fScale );				
				//m_pSkybox->PartOffset = 1;
				m_pSkybox->Render( 1.0 );
				m_pSkybox->PartOffset = 0;
			}
			MeRenderManager::Instance()->DoRender(true);
			RI->SetRenderState( D3DRS_LIGHTING, TRUE );
			RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
			RI->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
		}
		Render(vPos);
		return;
	}
	unguard;
}

void CSTSkyBox::RenderSkyBoxWithZ(D3DXVECTOR3& vPos, const char* pszSkyboxPath /* = 0 */)
{
	guardfunc;

	if( !IsDisable() && m_bCanRender )
	{
		SetSkybox(pszSkyboxPath);

		IRenderer* RI = GetEngine()->GetRenderer();
		RendererDx* pRender = (RendererDx*)RI;
		SetSunPosition(pRender->GetLightDir(LIGHT_INDEX_TERRAIN));
		m_dwTopColor = 9024500;

		if( m_pSkybox )
		{
			m_pSkybox->SetPosition( vPos.x, vPos.y,  0.f);
			LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
			RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
			{

				RI->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
				RI->SetRenderState( D3DRS_ZENABLE, TRUE );
				m_pSkybox->SetRenderFlag( /*eTwoSided | */eLightingDisable | eOpModulate2X | eAlphaBlend | eZWriteDisable & ~eAlphaTest);
				//m_pSkybox->SetScale( GetSkyBoxScale()*GetMe3dConfig()->m_fMdlSpaceScale );
				//m_pSkybox->SetRenderFlag( eRenderSkyBox );
				m_pSkybox->SetScale(1.f);

				m_pSkybox->UpdateTransform();
				//m_pSkybox->PartOffset = 1;
				m_pSkybox->Render( 1.0 );
				m_pSkybox->PartOffset = 0;
				MeRenderManager::Instance()->DoRender(false);
			}
			RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
		}
		return;
	}
	unguard;
}

void CSTSkyBox::FastAlphaRenderSky( MexAnimCtrl *SrcSkybox, 
									MexAnimCtrl *DestSkybox,
									Vector& vPos,
									FLOAT fCurAlpha,
									FLOAT fMaxDestAlpha, 
									FLOAT fMaxSrcAlpha)
{
	guardfunc;

	FLOAT fScale = 0.0f;
	D3DXMATRIX m;
	D3DXMATRIX mSrc;
	FLOAT fAlpha = fCurAlpha;

	DWORD dwTime = HQ_TimeGetTime();
	fScale = GetSkyBoxScale()*GetMe3dConfig()->m_fMdlSpaceScale;

	if( DestSkybox )
	{
		DestSkybox->SetRenderFlag( eLightingDisable | eOpModulate1X | eAlphaBlend );
		DestSkybox->SetScale( fScale*1.1f );
		DestSkybox->CalcTransformMatrix( (MeMatrix*)&m );			
		DestSkybox->Update( dwTime, (MeMatrix*)&m );
		//Vector vPos = m_Skybox.GetPosition();
		DestSkybox->SetPosition( vPos.x, vPos.y, vPos.z );
		DestSkybox->SetRotationX( 0 );
		DestSkybox->m_bRenderFirstPart = true;

		//FLOAT fAlpha = 1.0 - fCurAlpha;
		//fAlpha = fAlpha > fMaxDestAlpha ? fMaxDestAlpha :fAlpha;
		DestSkybox->Render( 1.0 - fCurAlpha );
		DestSkybox->m_bRenderFirstPart = false;
	}

	if( fCurAlpha > 0.0f )
	{
		if( SrcSkybox )
		{
			SrcSkybox->SetRenderFlag( eLightingDisable | eOpModulate1X | eAlphaBlend );
			SrcSkybox->SetRotationX( 0 );
			SrcSkybox->SetScale( fScale );
			SrcSkybox->CalcTransformMatrix( (MeMatrix*)&mSrc );			
			SrcSkybox->Update( dwTime, (MeMatrix*)&mSrc );
			SrcSkybox->SetPosition( vPos.x, vPos.y, vPos.z );
			SrcSkybox->Render( fCurAlpha );	
		}
	}

	unguard;
}
// BOOL CSTSkyBox::LoadDayNightAnim( char *szFile )
// {
// 	guardfunc;
// 	//	CSALocker locker(this);
// 	std::string strFile = szFile;
// // 	m_CurSaveDayNightPath = szFile;
// 	if( !szFile )
// 		return false;
// 
// 	if( m_pDayLightAnim && m_pLightChange )
// 	{
// 		m_pLightChange->SetSrcDayLight( m_pDayLightAnim );
// 	}
// 	if( m_pLightChange == NULL )
// 	{
// 		m_pLightChange = MeNew CDayLightChange;
// 	}
// 
// 	std::string szCmp = strFile.substr( strFile.size()-4, 4 );
// 	if( szCmp == ".config" )
// 	{
// 		m_pDayLightAnim = FindDayNight(strFile.c_str());
// 
// 	}
// 	if( m_pDayLightAnim  && m_pLightChange )
// 	{
// 		m_pLightChange->SetDestDayLight( m_pDayLightAnim );
// 		//theTimeChange.SetCurrentTime( 0 );
// 	}
// 	//	theTimeClock.SetCurrentTime( 0 );
// 	return TRUE;
// 	unguard;
// }
BOOL CSTSkyBox::ClearDayLightAnim()
{
	guardfunc;


// 	//for( )
// 	std::map<std::string, DayLightAnim*>::iterator iLoop;
// 	//SWalkMask *pWalkMask;
// 	DayLightAnim* pAnim = NULL;
// 	for( iLoop = m_mapDayLightAnim.begin() ; iLoop != m_mapDayLightAnim.end() ; iLoop ++ )
// 	{
// 		pAnim = iLoop->second;
// 		delete pAnim;
// 		pAnim = NULL;
// 	}
// 
// 	m_mapDayLightAnim.clear();

	std :: map<std::string, MexAnimCtrl*>::iterator iMexLoop;
	//SWalkMask *pWalkMask;
	MexAnimCtrl* pMex = NULL;
	for( iMexLoop = m_SkyBoxBuf.begin() ; iMexLoop != m_SkyBoxBuf.end() ; iMexLoop ++ )
	{
		pMex = iMexLoop->second;
		pMex->Destroy();
		delete pMex;
		pMex = NULL;
	}
	m_SkyBoxBuf.clear();

	m_pSkybox = 0;

	return TRUE;

	unguard;
}

// DayLightAnim* CSTSkyBox::FindDayNight( const char* szPath  )
// {
// 	guardfunc;
// 	//m_pSkybox = NULL;
// 	std :: map<std::string,  DayLightAnim*>::iterator It;
// 	It = DayLightAnim.find( szPath );
// 	if( It != DayLightAnim.end() )
// 	{
// 		return It->second;
// 	}
// 	return NULL;
// 
// 	unguard;
// }

FLOAT CSTSkyBox::GetSkyBoxScale( void )
{
	return 1.0f;
}

FLOAT CSTSkyBox::GetSkyBoxHeight()
{
	return 0.f;
}

MexAnimCtrl* CSTSkyBox::FindSkyBox( const char* szPath )
{
	guardfunc;
	//m_pSkybox = NULL;
	std :: map<std::string,  MexAnimCtrl*>::iterator It;
	It = m_SkyBoxBuf.find( szPath );
	if( It != m_SkyBoxBuf.end() )
	{
		return It->second;
	}
	return NULL;

	unguard;

}

void CSTSkyBox::RestoreFog()
{
	IRenderer* RI = GetEngine()->GetRenderer();
	FogProperty *pFogProp = SwGlobal::GetRender()->GetFogProperty();
	RI->SetRenderState( D3DRS_TEXTUREFACTOR, pFogProp->kFogColor);
	RI->DirectPushSurface(-1,-1,TERRAIN_SKYBOX, D3DFVF_CLOUDSVERTEX, sizeof( CloudsVB ),(BYTE*)m_pFogVB,m_nNumOfAV,(BYTE*)m_pFogIB,m_nNumOfAT,
		eUseVB|eUseIB|eLightingDisable|eZDisable|eZWriteDisable|eAlphaBlend, D3DPT_TRIANGLESTRIP );
}

void CSTSkyBox::SetSkybox( const char* pszSkyboxPath )
{
	if (pszSkyboxPath)
	{
		CHAR szPath[MAX_PATH] = {0};
		sprintf( szPath, "%s%s", CWorld::GetAppDataCharDir(), pszSkyboxPath);		
		MexAnimCtrl *	pNewSkybox = FindSkyBox( szPath );
		if (pNewSkybox != m_pSkybox)
		{
			if (pNewSkybox == NULL)
			{
				int nModelId = GetMexResMgr()->AddExternalFile( szPath );
				if (nModelId != -1)
				{
					pNewSkybox = MeNew MexAnimCtrl;
					pNewSkybox->ChangeModel( nModelId ,FALSE,NULL);
					m_SkyBoxBuf.insert( std::map<std::string, MexAnimCtrl*>::value_type(szPath, pNewSkybox) );
					m_nSkyBoxModelID = nModelId;
				}
			}
			if (pNewSkybox)
			{
				m_pSkybox = pNewSkybox;
			}
		}
	}

}