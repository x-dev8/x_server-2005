#include "Mex2LoadReq.h"
#include <vector>
#include "Me3d/Engine/Engine.h"
#include "WSModelEffect.h"
#include "MultithreadMexLoading.h"
#include "FuncPerformanceLog.h"
#include <process.h>
#include "player.h"
#include "MapContainer.h"
#include "Me3d/Model/mexconfig.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Font3DManager.h"
#include "wsCamera.h"
#include "FilePath.h"
#include "RTTFont.h"
#include <MeFoundation/MeLoopThreadMan.h>

void Mex2WithMexReq::Destroy()
{
	GetMexResMgr()->DestroyModel(m_nModelId);
	m_pMex = NULL;
	m_pMexCfg = NULL;
}
//////////////////////////////////////////////////////////////////////////
PlayerEquipReq::~PlayerEquipReq()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return ;

	if( m_pAnim )
		m_pAnim->SetInThread( false );
	//m_pPlayer->DecRef();
}
//////////////////////////////////////////////////////////////////////////
bool PlayerEquipReq::ProcessInThread( bool bFailed /*= false*/ )
{
	return true;
}
//////////////////////////////////////////////////////////////////////////
void PlayerEquipReq::Process()
{
	// �жϻ�װ�����Ƿ��������б�����һ�����[QL]
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return;

	m_pAnim = m_pPlayer->GetAnim();

	MexResMgr::Record* pRecord =  GetMexResMgr()->GetRecord( m_nModelId );	

	bool bFound = false;
	{
		bFound = MeLoopThreadMan::Instance()->FindPointer( m_pAnim );
	}
	if( m_pAnim && bFound )
	{
		if( pRecord == NULL ||  pRecord->res.pMex == NULL  )
		{// ����Ҳ����ü�¼���߸ü�¼û����Ч����Դ
			if( m_nType == eKeyAll_Max - 1 )
			{
				if( m_pAnim )
					m_pAnim->SetChangeAllEquipComplete( TRUE );				
			}
		}
		else
		{

			CPlayerAnimParam param;
			param.nModelId = m_nModelId;
			param.nPart = m_nType;
			param.szSkin = m_szSkin;
			param.nSpecularTextureID = m_nSpecularTexID;
			// added, jiayi, [2009/9/22]
			param.pEquips = m_pAnim->GetBackEquip();
			param.LowestIntensity = m_nLowestIntensity;
			m_pAnim->ChangePartModel( 
				param
				);			

			m_pPlayer->UpdateBones();

// 			if( !m_pPlayer->GetFontObject() )
// 			{
// 				RTTFont* pFontName = Font3DManager::Instance()->CreateFont3D(RTTFont::RTT_TEX_WIDTH,
// 					gCfg.m_szNameFontName, gCfg.m_nNameFontSize, false, gCfg.m_isNameFontBold);
// 				pFontName->SetCamera(getwsCamera()->GetMeCamera());
// 				pFontName->SetVisible( true );	
// 				m_pPlayer->SetFontObject( pFontName );
// 			}	

			//m_pPlayer->InitShadowDecal();

		}
	}	
}
//////////////////////////////////////////////////////////////////////////
MonsterModelReq::~MonsterModelReq()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return ;

	if( m_pAnim )
		m_pAnim->SetInThread( false );
	//m_pPlayer->DecRef();
}
//////////////////////////////////////////////////////////////////////////
void ModelEffectReq::Process()
{
	MexResMgr::Record* pRecord =  GetMexResMgr()->GetRecord( m_nModelId );

	bool bFound = false;
	{
		bFound = MeLoopThreadMan::Instance()->FindPointer( m_pModelEffect );
	}
	if( m_pModelEffect && bFound )
	{
		m_pModelEffect->SetModelID(m_nModelId);
		m_pModelEffect->Start();
	}

}
#ifdef _DEBUG
#define LOAD_COST_TIME_DEBUG 1
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////
void MonsterModelReq::Process()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return ;

	// modified by ZhuoMeng.Hu		[11/15/2010]
	if( m_pPlayer->IsMorphInThread() )
	{
		m_pPlayer->SetMorphInThread( false );
		if( m_pPlayer->GetMorphModelID() == -1 )//δ��������̣�����dismorph()������£���˴���
		{
			return;
		}
		m_pAnim = m_pPlayer->GetMorphAnim();
	}
	else
	{
		m_pAnim = m_pPlayer->GetAnim();	
	}

	MexResMgr::Record* pRecord =  GetMexResMgr()->GetRecord( m_nModelId );

	bool bFound = false;
	{
		bFound = MeLoopThreadMan::Instance()->FindPointer( m_pAnim );
	}
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = HQ_TimeGetTime() ;
#endif
	if( m_pAnim && bFound )
	{
		m_pAnim->MyChangeModel(m_nModelId, FALSE, m_szSkin );

		if( m_pPlayer->IsNpc() )
			m_pAnim->PlayDefaultAnimAfterChangeModel();

		m_pPlayer->UpdateBones();

		// ���������������������(���أ�
		if( m_pPlayer->IsDead() )
		{
			m_pPlayer->SwitchDieOverAnim();
		}

		if( !m_pPlayer->GetFontObject() )
		{
			RTTFont* pFontName = Font3DManager::Instance()->CreateFont3D(RTTFont::RTT_TEX_WIDTH,
				gCfg.m_szNameFontName, gCfg.m_nNameFontSize, false, gCfg.m_isNameFontBold);
			pFontName->SetCamera(getwsCamera()->GetMeCamera());
			pFontName->SetVisible( true );	
			m_pPlayer->SetFontObject( pFontName );
			/*if( pPlayer->IsNpc() )
			{
			pFontName->EnableCustomShadow( D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
			}*/
		}
		m_pPlayer->InitShadowDecal();
	}
}
//////////////////////////////////////////////////////////////////////////
void MountReq::Process()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return ;

 	if( !m_pPlayer->IsMountInThread() )
 		return;

	m_pPlayer->SetMountInThread( false );

 	if( m_pPlayer->GetMountModelID() == -1 )// ���ڶ��߳�loading�������Ѿ������ʱ��
 	{
 		return;
 	}
	
	m_pPlayer->PostMountMonster( m_nModelId, m_bPlayEffect, m_nDromeId );	
}
//////////////////////////////////////////////////////////////////////////
void PlayerNameReq::Process()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return ;

	RTTFont* pFontName = Font3DManager::Instance()->CreateFont3D(RTTFont::RTT_TEX_WIDTH,
		gCfg.m_szNameFontName, gCfg.m_nNameFontSize, false, gCfg.m_isNameFontBold);
	pFontName->SetCamera(getwsCamera()->GetMeCamera());
	pFontName->SetVisible( true );	
	m_pPlayer->SetFontObject( pFontName );
}
//////////////////////////////////////////////////////////////////////////
PlayerNameReq::~PlayerNameReq()
{
	if( !theHeroGame.GetPlayerMgr() )
		return;

	if( !m_pPlayer )
		return ;

	if( !theHeroGame.GetPlayerMgr()->IsPlayerValid(m_pPlayer) )	
		return ;

	//m_pPlayer->DecRef();
}
//////////////////////////////////////////////////////////////////////////
bool Mex2WithMexReq::ProcessInThread( bool bFailed /*= false*/ )
{
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool MonsterModelReq::ProcessInThread( bool bFailed /*= false*/ )
{
	if( bFailed )
	{
		return true;
	}	
	if( m_pMexCfg && GetEngine() && GetEngine()->GetTextureManager())
	{
		std::string strSkin = DEFAULT_AVATARSETTING_NAME;
		if (strcmp( m_szSkin, "" ) != 0)
		{
			strSkin = m_szSkin;
		}
		MexCfgAvatarSetting*	pAvatarSetting = m_pMexCfg->m_AvatarSettings.FindByName( strSkin.c_str() );

		if( pAvatarSetting )
		{
			for( int nTexture = 0; nTexture < pAvatarSetting->m_vectorReplaceableTexture.size(); nTexture++ )
			{
				MexCfgAvatarSetting::ReplaceableTexture* rt =
					&pAvatarSetting->m_vectorReplaceableTexture[nTexture];

				//ʹ����ͼ������ж���Ԥ���أ�������+1
				int nRenderTextureID = 
					MexReplaceableTextureProj::RegisterTexture( 
					m_pMex->GetFilename(), 
					rt->szFileName, false );
				//���̼�����һ
				if (nRenderTextureID != -1)
				{
					GetEngine()->GetTextureManager()->UnRegisterTexture( nRenderTextureID );
				}

				if (strstr(m_pMex->GetFilename(),"avatar") || strstr(m_pMex->GetFilename(),"character") )
				{//��������ļ���ʧ��
					//ʹ����ͼ������ж���Ԥ���أ�������+1
					CFilePath path;
					path.Split( rt->szFileName );
					std::string strTemp( path.GetDirectory() );
					strTemp = strTemp + path.GetFileName() + "-lum.png";
					int nLuminanceTextureID = 
						MexReplaceableTextureProj::RegisterTexture( 
						m_pMex->GetFilename(), 
						strTemp.c_str(),false );
					//���̼�����һ
					if(nLuminanceTextureID != -1 )
						GetEngine()->GetTextureManager()->UnRegisterTexture( nLuminanceTextureID );
				}
			}
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////