#include "Me3d/Engine/Engine.h"
#include "Me3d/Model/MexGeoChunk.h"
#include "FilePath.h"
#include "Stdcharskeleton.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Avatar.h"
//#include "Me3d/Effect/EffectHollywood.h"
#include "Me3d/Effect/BladeRibbon.h"
#include "FuncPerformanceLog.h"
//#include "GlobalDef.h"
#include "script_manager.h"
#include "LogFileObjectNameEx.h"
#include "PlayerAnimCtrl.h"
#include "IntensifyEquipEffect.h"

#define MAXINTENSIFYLEVEL 19
#define INTENSIFY_FILENAME_PREFIX "Intensify_Star_"
static const char* g_szStarFilename[MAXINTENSIFYLEVEL] = {
	"Data/Texture/Intensify/Intensify_Star_0.tga",
	"Data/Texture/Intensify/Intensify_Star_1.tga",
	"Data/Texture/Intensify/Intensify_Star_2.tga",
	"Data/Texture/Intensify/Intensify_Star_3.tga",
	"Data/Texture/Intensify/Intensify_Star_4.tga",
	"Data/Texture/Intensify/Intensify_Star_5.tga",
	"Data/Texture/Intensify/Intensify_Star_6.tga",
	"Data/Texture/Intensify/Intensify_Star_7.tga",
	"Data/Texture/Intensify/Intensify_Star_8.tga",
	"Data/Texture/Intensify/Intensify_Star_9.tga"
};

class TextureListener : public ITextureListener
{
public:
    TextureListener( CAvatar::Component* com, const std::string& paramName ) :
        _com( com ), _paramName( paramName )
    {
    }

    virtual void loadFinished( ITexture* tex )
    {
        LPDIRECT3DTEXTURE9 pDxTex = (LPDIRECT3DTEXTURE9)tex->GetData();
        if ( pDxTex )
        {
            _com->material.setParameter( _paramName, pDxTex );
        }
    }

protected:
    CAvatar::Component* _com;
    std::string         _paramName;
};

const char* gs_AttachmentName[CAvatar::MAX_AVATAR_ATTACHMENT] = 
{
	"attc.RightHand",
	"attc.LeftHand",
	"attc.RightShoulder",
	"attc.LeftShoulder",
	"attc.RightBack",
	"attc.LeftBack",
	//"attc.RightWaist",
	//"attc.LeftWaist",
	"attc.Shield",
	"attc.Helmet",
	"attc.BackShield",
};

// add, jiayi, [2009.4.17], 定义与More.h中调用顺序一样
// 值是attachment的偏移数
//int gs_AttachmentOffset[EA_ArmsMaxSize];


DWORD g_RoleMultRegTexgture = FALSE;

int g_nCharacterDBID = -1;

CAvatarHairStyle::Mesh*	CAvatarHairStyle::GetMesh( int nMesh )
{
	guardfunc;
	if( nMesh < 0 || nMesh >= eMaxPart )
		return NULL;
	return &m_Meshes[nMesh];
	unguard;
}
BOOL CAvatarHairStyle::Build( IMex* pMex )
{
	guardfunc;
	if( !pMex )
	{
		assert( false );
		return FALSE;
	}
	if( !pMex->GetGeometry() )
	{
		assert( false );
		return FALSE;
	}
	IMexGeometry* pGeom = pMex->GetGeometry();
	for( int nMesh = 0; nMesh < m_Meshes.size(); nMesh++ )
	{

	}
	
	for( int nChunk = 0; nChunk < pGeom->GetChunkCount(); nChunk++ )
	{

	}
	return TRUE;
	unguard;
}
CAvatar::Component::Component():
pMex(NULL),
nModelID(-1),
dwItemFlag(0),
bIsAttachment(FALSE),
//nNumAttachBone(0),
//nAttachBoneID(-1),
pMtlEffect(NULL),
nAttachment(0),
m_bLeftHand(FALSE),
bCanSee(TRUE),
bCanSeeAfterBlend(FALSE)
//pMexAnim(NULL)
//pAttachment(NULL)
{
	guardfunc;
	for( int nAnim = 0; nAnim < eMaxPartAnim; nAnim++ )
	{
		pMexAnims[nAnim] = NULL;
	}
	Clear();
	unguard;
}
void CAvatar::Component::Clear()
{
	guardfunc;
	pMex = NULL;
	nModelID = -1;
	stSex = -1;
	m_nSpecularTexID = -1;

//	for
	//if( !m_ReplaceableTextureProj.IsLoaded() )
	//	return TRUE;
	//m_ReplaceableTextureProj.UnRegisterTextures();
	//m_ReplaceableTextureProj.Loaded( FALSE );
	
	//for( int nAtt = 0; nAtt < eMaxAttachBone; nAtt++)
	//{
	//	pAttachment[nAtt] = NULL;
	//}
	//nNumAttachBone = 0;
	//pAttachment = NULL;

	m_pAvatarSetting = NULL;
	
	dwItemFlag = 0;
	vectorChunk.clear();
	flags.clear();
	pMtlEffect = NULL;
	//bIsAttachment = FALSE;
	
	//nNumAttachBone = 0;
	if ( ReplaceableTextureProj.IsLoaded() )
	{
		ReplaceableTextureProj.UnRegisterTextures();
		ReplaceableTextureProj.Loaded( FALSE );
	}

    if ( ShimmerGrayTextureProj.IsLoaded() )
	{
		ShimmerGrayTextureProj.UnRegisterTextures();
		ShimmerGrayTextureProj.Loaded( FALSE );
	}

    if ( LuminanceTextureProj.IsLoaded() )
    {
        LuminanceTextureProj.UnRegisterTextures();
        LuminanceTextureProj.Loaded( FALSE );
    }

	m_EffectContainer.Destroy();

	m_bLeftHand = TRUE;
	SetAttachment( FALSE );
	for( int nAnim = 0; nAnim < eMaxPartAnim; nAnim++ )
	{
		if( pMexAnims[nAnim] )
		{
			pMexAnims[nAnim]->Destroy();
			delete pMexAnims[nAnim];
			pMexAnims[nAnim] = NULL;
		}
	}
	//char* p = MeNew char;
	unguard;
}

void CAvatar::Component::SetMexAnim( int nSlot, MexAnimCtrl* pMexAnim )
{
	if( nSlot < 0 || nSlot >= eMaxPartAnim )
		return;
	pMexAnims[nSlot] = pMexAnim;
}

void CAvatar::Component::SetCollectibleType(SortRenderable::ECollectibleType type)
{
	for (int i = 0; i < vectorChunk.size(); ++i)
	{
		((CMexChunkBase *)vectorChunk[i])->SetCollectibleType(type);
	}
}

MexAnimCtrl* CAvatar::Component::GetMexAnim( int nSlot )
{
	if( nSlot < 0 || nSlot >= eMaxPartAnim )
		return NULL;
	return pMexAnims[nSlot];
}

CAvatar::CreateParam::CreateParam():
nComponentCount(0),
ppszComponentNames(NULL)
{
	guardfunc;
	unguard;
}
CAvatar::Effect::Effect():
part(NULL),
ribb(NULL),
bbrd(NULL),
pWeaponBladeRibbon(NULL),
nType(0),
dwFlag(0)
{
	guardfunc;
	unguard;
}
void CAvatar::EffectContainer::Destroy()
{
	guardfunc;
	for( int nEffect = 0; nEffect < effects.size(); nEffect++ )
	{
		Effect* pEffect = &effects[nEffect];
		if( pEffect->part )
		{
			pEffect->part->Release();
			pEffect->part = NULL;
		}
		if( pEffect->ribb )
		{
			pEffect->ribb->Release();
			pEffect->ribb = NULL;
		}
		if( pEffect->pWeaponBladeRibbon )
		{
			delete pEffect->pWeaponBladeRibbon;
			pEffect->pWeaponBladeRibbon = NULL;
		}

	}
	effects.clear();
	unguard;
}
CAvatar::CAvatar():
m_dwEnableItemFlag(0),
m_bHasHairStyle(FALSE)
{
	guardfunc;
	memset( m_pAttachments, 0x00, sizeof( m_pAttachments ) );

	// add, jiayi, [2009.4.17]
// 	gs_AttachmentOffset[Profession_Warrior] = 2;
// 	gs_AttachmentOffset[Profession_robber] = 4;
// 	gs_AttachmentOffset[Profession_Taoist] = 6;
	unguard;
}

CAvatar::~CAvatar()
{
	ReleaseAllComponents();
}

IMexAttachment* CAvatar::GetAttachment( int nPart )
{
	if( nPart < 0 || nPart > MAX_AVATAR_ATTACHMENT )
		return NULL;
	return m_pAttachments[nPart];
}
void CAvatar::EnableItem( DWORD dwFlag )
{
	guardfunc;
	m_dwEnableItemFlag |= dwFlag;
	unguard;
}
void CAvatar::DisableItem( DWORD dwFlag )
{
	guardfunc;
	m_dwEnableItemFlag &= ~dwFlag;
	unguard;
}
void CAvatar::ClearItem()
{
	guardfunc;
	m_dwEnableItemFlag = 0;
	unguard;
}
// BOOL CAvatar::IsValidComponentID( int nComponentID )
// {
// 	guardfunc;
// 	if( nComponentID < 0 || nComponentID >=  m_Components.size() )
// 	{
// 		return FALSE;
// 	}
// 	return TRUE;
// 	unguard;
// }

CAvatar::Component* CAvatar::GetComponent( int nComponentID )
{
	guardfunc;
	if( !IsValidComponentID( nComponentID ) )
	{
		assert( false );
		return NULL;
	}
	return &m_Components[nComponentID];
	unguard;
}

CAvatar::Component* CAvatar::GetComponent( const char* pszComponentName )
{
	guardfunc;
	if( !pszComponentName )
	{
		assert( false );
		return NULL;
	}
	for( int i = 0; i < m_Components.size(); i++ )
	{
		if( m_Components[i].strName.compare( pszComponentName ) == 0 )
			return &m_Components[i];
	}
	return NULL;
	unguard;
}


BOOL CAvatar::Create( CreateParam* pParam )
{
	guardfunc;
	if( !pParam )
	{
		assert( false );
		return FALSE;
	}
	if( !pParam->ppszComponentNames )
	{
		assert( false );
		return FALSE;
	}
	m_Components.reserve( pParam->nComponentCount );
	m_Components.resize( pParam->nComponentCount );
	for( int i = 0; i < pParam->nComponentCount; i++ )
	{
		m_Components[i].strName = pParam->ppszComponentNames[i];
	}
	return TRUE;
	unguard;
}
BOOL CAvatar::ChangeAttachment( /*MexAnimCtrl* pMaster,*/ 
							   MexAnimCtrl* pChild,
							   Component* pComponent, 
							   int nSlot
							   /*const char* pszHelperName*/ )
{

	guardfunc;
	//IMexAttachments* pAttachments = pMaster->GetMex()->GetAttachments();
	//if( !pAttachments )
	//	return FALSE;
	//pComponent->pAttachment = pAttachments->FindAttachment( pszHelperName );
	//if( !pComponent->pAttachment )
	//	return FALSE;
	pComponent->SetMexAnim( nSlot, pChild );// pMexAnims[nSlot] = pChild;

	pComponent->SetAttachment( TRUE );
	//pChild->SetScale( pChild->GetScale()*pMaster->GetScale() );
	return TRUE;
	unguard;
}

DWORD	CAvatar::GetEffectPart( const char* pszName )
{
	DWORD dwFlag = 0;
	if( stricmp( pszName, "LeftHand" ) == 0 )
		dwFlag |= eItem_LeftHand;
	else if( stricmp( pszName, "RightHand" ) == 0 )
		dwFlag |= eItem_RightHand;
	else if( stricmp( pszName, "LeftBack" ) == 0 )
		dwFlag |= eItem_LBack;
	else if( stricmp( pszName, "RightBack" ) == 0 )
		dwFlag |= eItem_RBack;

	return dwFlag;

	return 0;
}

BOOL CAvatar::ChangeComponent( MexAnimCtrl* pMexAnimCtrl, 
							  int nComponentID, 
							  int nSlot,
							  MexResMgr::Record* pRecord,
							  MexAnimCtrl* pChild,
							  const char* szSkin,
							  INT nSpecular,
							  short stStar )
{
	guardfunc;
	if( !pRecord )
	{
		return FALSE;
	}
	if( !pMexAnimCtrl->GetMex() )
	{
		return FALSE;
	}
		
	IMex* pMex = pRecord->res.pMex;
	if( !pMex )
	{
		return FALSE;
	}

	MexCfg* pMexCfg = pRecord->res.pMexCfg;
	if( !pMexCfg )
	{
		return FALSE;
	}
	
	if( !IsValidComponentID( nComponentID ) )
	{
		assert( false );
		return FALSE;
	}

	if (!pMexCfg->m_AvatarSettings.FindByName( szSkin ))
	{
		return FALSE;
	}
	
	Component* pComponent = GetComponent( nComponentID );

	pComponent->pMex = NULL;
	pComponent->vectorChunk.clear();
	pComponent->nAttachment = 0;
	pComponent->SetAttachment( FALSE );
	pComponent->m_nSpecularTexID = nSpecular;

	/*
	for( int nAnim = 0; nAnim < eMaxPartAnim; nAnim++ )
	{
		MexAnimCtrl* pAnim = pComponent->GetMexAnim( nAnim );
		if( pAnim )
		{
			pAnim->Destroy();
			delete pAnim;
			pComponent->SetMexAnim( nAnim, NULL );
		}
	}
	*/

	if ( pComponent->ReplaceableTextureProj.IsLoaded() )
	{
		pComponent->ReplaceableTextureProj.UnRegisterTextures();
		pComponent->ReplaceableTextureProj.Loaded( FALSE );
	}

	if ( pComponent->ShimmerGrayTextureProj.IsLoaded() )
	{
		pComponent->ShimmerGrayTextureProj.UnRegisterTextures();
		pComponent->ShimmerGrayTextureProj.Loaded( FALSE );
	}

	if ( pComponent->LuminanceTextureProj.IsLoaded() )
	{
		pComponent->LuminanceTextureProj.UnRegisterTextures();
		pComponent->LuminanceTextureProj.Loaded( FALSE );
	}

	// 把特效销毁
	pComponent->m_EffectContainer.Destroy();

	if (pChild != NULL)
	{
		ChangeAttachment(pChild, pComponent, nSlot);		
	}
	else 
	{
		if (!pMexAnimCtrl->GetMex()->GetSkeleton()->IsSameFormat( pMex->GetSkeleton()))
		{
#ifdef _DEBUG
			OutputDebugString("骨骼不同，不能装备\n");
#endif
			return FALSE;
		}
	}
	pComponent->pMex = pMex;
	DWORD dwMexVersion = pMex->GetVersion();
	IMexGeometry* pGeometry = pMex->GetGeometry();

	if ( dwMexVersion >= 101 )
	{
		if ( pGeometry != NULL)
		{
			for ( int i = 0; i < pGeometry->GetChunkCount(); i++ )
			{
				IRenderable* pChunk = pGeometry->GetChunk( i );
				if ( pChunk == NULL )
					continue;

				pChunk->SetAvatarComponent();

				const char* pszName = pChunk->GetName();
				if ( !pszName )
					continue; 

				DWORD dwFlag = 0;
				if ( strnicmp( pszName, "rback.", 5 ) == 0 )
				{
					dwFlag |= eItem_RBack;
				}
				if ( strnicmp( pszName, "lback.", 5 ) == 0 )
				{
					dwFlag |= eItem_LBack;
				}
				else if ( strnicmp( pszName, "rh.", 3 ) == 0 )
				{
					dwFlag |= eItem_RightHand;
				}
				else if ( strnicmp( pszName, "lh.", 3 ) == 0 )
				{
					dwFlag |= eItem_LeftHand;
				}
				else if ( strnicmp( pszName, "ground.", 7 ) == 0 )
				{
					dwFlag |= eItem_Ground;
				}
				else if ( strnicmp( pszName, "lshield.", 8 ) == 0 )
				{
					dwFlag |= eItem_Shield;
				}
				else if ( strnicmp( pszName, "lbshield.", 9 ) == 0 )
				{
					dwFlag |= eItem_BackShield;
				}
				// billboard
				else if ( strnicmp( pszName, "bbrd.rback.", 11 ) == 0 )
				{
					dwFlag |= eItem_RBack;
				}
				else if ( strnicmp( pszName, "bbrd.lback.", 11 ) == 0 )
				{
					dwFlag |= eItem_LBack;
				}
				else if ( strnicmp( pszName, "bbrd.rh.", 8 ) == 0 )
				{
					dwFlag |= eItem_RightHand;
				}
				else if ( strnicmp( pszName, "bbrd.lh.", 8 ) == 0 )
				{
					dwFlag |= eItem_LeftHand;
				}

				pComponent->vectorChunk.push_back( pChunk );
				pComponent->flags.push_back( dwFlag );
			}
		}

		/*
		switch (nComponentID)
		{
		case eKeyAll_Armour:
		case eKeyAll_Glove:
		case eKeyAll_Shoe:
			{
				//pComponent->SetCollectibleType(SortRenderable::eCT_Shimmer);
				break;

				try
				{
					char szScriptFilename[MAX_PATH] = {0};
					sprintf_s(szScriptFilename, MAX_PATH - 1,"%s/Data/Config/Intensify.config", GetRootPath());
					LuaPlus::LuaStateOwner luaStateOwner;
					ScriptManager::instance().executeFile(szScriptFilename, luaStateOwner);

					LuaFunction<const char *> GetEquipIntensifyInfoFunc(luaStateOwner, "GetEquipIntensifyInfo");
					const char *szHeatShimmerTex = GetEquipIntensifyInfoFunc(stStar);
					if (strlen(szHeatShimmerTex) > 0)
						pComponent->HeatShimmerTexId = GetEngine()->GetTextureManager()->RegisterTexture(szHeatShimmerTex, FALSE ,TRUE);
					else
						pComponent->HeatShimmerTexId = -1;
				}
				catch (const LuaPlus::LuaException &e)
				{
					LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, e.GetErrorMessage());
				}
			}
			break;
		}
		*/

		/*
		if (pMex->GetParticleEmitters())
		{
			if (nComponentID == eKeyAll_RHandItem)
			{
				pMex->DestroyParticleEmitters();
			}
			
			//int nEmitterCount = pMex->GetParticleEmitters()->GetEmitterCount();
			//if( nEmitterCount > 0 )
			//{
			//	for( int i = 0; i < nEmitterCount && i < eMaxParticleEmitter; i++ )
			//	{
			//		Effect effect;
			//		effect.part = pMex->GetParticleEmitters()->GetEmitter(i)->Clone();
			//		effect.dwFlag = GetEffectPart( effect.part->GetBindPartName() );
			//		pComponent->m_EffectContainer.effects.push_back( effect );
			//	}
			//}
		}
		
		if (nComponentID == eKeyAll_RHandItem)
		{
			MexAnimCtrl *anim = pComponent->GetMexAnim(0);
			IMexSkeleton *skeleton = pComponent->pMex->GetSkeleton();
			int nEffectAttachBone = skeleton->FindBone("effect.Bone002");
			Vector attach_pos = anim->GetBoneWorldPos(nEffectAttachBone);

			pComponent->pMex->CreateParticleEmitters();

			static MexResMgr::Record* pRecord = GetMexResMgr()->CreateModel( 8888 );

			int nEmitterCount = pRecord->res.pMex->GetParticleEmitters()->GetEmitterCount();
			if (nEmitterCount > 0 && anim != NULL)
			{
				for (int i = 0; i < nEmitterCount; ++i)
				{
					IMexParticleEmitter *e = pRecord->res.pMex->GetParticleEmitters()->GetEmitter(i)->Clone();
					pComponent->pMex->GetParticleEmitters()->AppendEmitter(e);
				}
				anim->RefreshParticleEmitters(pRecord->res.pMex);
			}
		}
		*/

		if (pMex->GetRibbonEmitters())
		{
			int nEmitterCount = pMex->GetRibbonEmitters()->GetEmitterCount();
			if( nEmitterCount > 0 )
			{
				for( int i = 0; i < nEmitterCount && i < eMaxRibbonEmitter ; i++ )
				{
					Effect effect;
					effect.ribb = pMex->GetRibbonEmitters()->GetEmitter(i)->Clone();
					effect.dwFlag = GetEffectPart( effect.ribb->GetBindPartName() );
					// 武器刀光增强了,ribb对应一个blade ribbon
					effect.pWeaponBladeRibbon = MeNew BladeRibbonEffect;
					if( effect.pWeaponBladeRibbon )
					{
						effect.ribb->GetPoint( (float*)effect.pWeaponBladeRibbon->m_vPoints );
						pComponent->m_EffectContainer.effects.push_back( effect );
					}
				}
			}
		}
	}
	else if( dwMexVersion == 0 )
	{
		if( pGeometry )
		{
			IRenderable* pChunk = pGeometry->GetChunk( nComponentID );
			if( pChunk )
			{
				pComponent->vectorChunk.push_back( pChunk );
			}
		}
	}

	pComponent->m_pAvatarSetting = pMexCfg->m_AvatarSettings.FindByName( szSkin );
	if (pComponent->m_pAvatarSetting == NULL)
		return FALSE;

	/*
	if (nComponentID == eKeyAll_RHandItem)
	{
		MexResMgr::Record* pRecord = GetMexResMgr()->GetRecord( 8888 );
		if (pMex->GetParticleEmitters())
		{
			int nEmitterCount = pMex->GetParticleEmitters()->GetEmitterCount();
			if( nEmitterCount > 0 )
			{
				for( int i = 0; i < nEmitterCount && i < eMaxParticleEmitter; i++ )
				{
					IMexParticleEmitter *e = pRecord->res.pMex->GetParticleEmitters()->GetEmitter(i);
					int nLocalTexID = e->GetLocalTextureID();
					
					MexCfgAvatarSetting::ReplaceableTexture rt;
					rt.nRenderTextureID = -1;
					strcpy_s(rt.szFileName, MAX_PATH - 1, pRecord->res.pMex->GetTextures()->GetTexture(nLocalTexID)->GetName());

					BOOL bFound = FALSE;
					for (int x = 0; x < pComponent->m_pAvatarSetting->m_vectorReplaceableTexture.size(); ++x)
					{
						if (strcmp(pComponent->m_pAvatarSetting->m_vectorReplaceableTexture[x].szFileName, rt.szFileName) == 0)
						{
							bFound = TRUE;
							break;
						}
					}
					if (!bFound)
						pComponent->m_pAvatarSetting->m_vectorReplaceableTexture.push_back(rt);
				}
			}
		}
	}
	*/

	pComponent->LuminanceTextureProj.SetTextureCount( pComponent->m_pAvatarSetting->m_vectorReplaceableTexture.size() );
	pComponent->ShimmerGrayTextureProj.SetTextureCount( pComponent->m_pAvatarSetting->m_vectorReplaceableTexture.size() );
	pComponent->ReplaceableTextureProj.SetTextureCount( pComponent->m_pAvatarSetting->m_vectorReplaceableTexture.size() );
	for (int nTexture = 0; nTexture < pComponent->m_pAvatarSetting->m_vectorReplaceableTexture.size(); ++nTexture)
	{
		MexCfgAvatarSetting::ReplaceableTexture* rt = &pComponent->m_pAvatarSetting->m_vectorReplaceableTexture[nTexture];

		// modified, jiayi, [2009/9/17]
		int nRenderTextureID = -1;
		if ((nComponentID != eKeyAll_RHandItem && nComponentID != eKeyAll_LHandItem) || 
			( strncmp( rt->szFileName, INTENSIFY_FILENAME_PREFIX, sizeof( INTENSIFY_FILENAME_PREFIX ) / sizeof( char ) - 1 ) != 0 ) )
		{
			nRenderTextureID = pComponent->ReplaceableTextureProj.RegisterTexture( pMex->GetFilename(), rt->szFileName, TRUE );
		}
		/*else
		{
			char szStarFilename[MAX_PATH];			
			sprintf_s( szStarFilename, MAX_PATH, "%s/%s", GetRootPath(), g_szStarFilename[stStar] );
			nRenderTextureID = GetEngine()->GetTextureManager()->RegisterTexture( szStarFilename, TRUE ,FALSE);
		}*/
		pComponent->ReplaceableTextureProj.SetRenderTextureID( nTexture, nRenderTextureID );

		CFilePath path;
		path.Split(rt->szFileName);

		// 装备的Shimmer
		std::string strTemp( path.GetDirectory() );
		strTemp = strTemp + path.GetFileName() + "-s.dds";

		int nShimmerGrayTexId = pComponent->ShimmerGrayTextureProj.RegisterTexture( pMex->GetFilename(), strTemp.c_str(), TRUE);
		pComponent->ShimmerGrayTextureProj.SetRenderTextureID( nTexture, nShimmerGrayTexId );

		strTemp = std::string( path.GetDirectory() );
		strTemp = strTemp + path.GetFileName() + "-lum.png";
		int nLuminanceTextureID = pComponent->LuminanceTextureProj.RegisterTexture( pMex->GetFilename(), strTemp.c_str(), TRUE);
		pComponent->LuminanceTextureProj.SetRenderTextureID( nTexture, nLuminanceTextureID );
	}
	pComponent->ReplaceableTextureProj.Loaded( TRUE );
	pComponent->ShimmerGrayTextureProj.Loaded( TRUE );
	pComponent->LuminanceTextureProj.Loaded( TRUE );
	return TRUE;
	unguard;
}

BOOL CAvatar::BindAttachments( MexAnimCtrl* pMexAnimCtrl )
{
	guardfunc;
	if( !pMexAnimCtrl )
	{
		assert( false );
		return FALSE;
	}
	if( !pMexAnimCtrl->GetMex() )
	{
		assert( false );
		return FALSE;
	}
	IMexAttachments* pAttachments = pMexAnimCtrl->GetMex()->GetAttachments();
	if( !pAttachments )
		return FALSE;
	for( int nAtt = 0; nAtt < MAX_AVATAR_ATTACHMENT; nAtt++ )
	{
		m_pAttachments[nAtt] = pAttachments->FindAttachment( gs_AttachmentName[nAtt] );
	}
	unguard;
	return TRUE;
}

BOOL CAvatar::ChangeComponent( MexAnimCtrl* pMexAnimCtrl, 
							  int nComponentID, 
							  int nModelID,
							  int nLocalModelId,
							  const char* szSkin, 
							  INT nSpecular,
							  short stStar )
{
	guardfunc;
	if( !IsValidComponentID( nComponentID ) )
	{
		assert( false );
		return FALSE;
	}

	ReleaseComponent( nComponentID );
	Component* pComponent = GetComponent( nComponentID );
	pComponent->nModelID = nModelID;

	MexResMgr::Record* pRecord = NULL;
	if( nModelID != -1 )
	{
		pRecord = GetMexResMgr()->CreateModel( nModelID );
	}
	else
		pRecord = GetMexResMgr()->GetRecord( nModelID );

	if( !pRecord )
	{
		return FALSE;
	}

	// 判断是否是动画装备
	CFilePath path;
	path.Split( pRecord->szFilename );
	// commented out, jiayi, [2009/8/17]
	// 策划需求，去掉这层判断，当是右手装备的时候
	// 默认是动画装备
	BOOL bIsAniEquipment = (nComponentID == eKeyAll_RHandItem || nComponentID == eKeyAll_LHandItem) ? true : false ;
	if (strnicmp( path.GetFileName(), "ani_", 4 ) == 0 || bIsAniEquipment)
	{
		// 如果是一下几个部位
		if (nComponentID == eKeyAll_RHandItem || nComponentID == eKeyAll_LHandItem)
		{	
			MexAnimCtrl* pChild = MeNew MexAnimCtrl;
			pChild->ChangeModel( nModelID ,FALSE, NULL );
			pChild->IAmComponent();
			if (!ChangeComponent( pMexAnimCtrl, nComponentID, 0, pRecord, pChild, szSkin, nSpecular, stStar ))
			{
				delete pChild;
				pChild = NULL;
			}

			// 武器强化
			int nIntensifyModelID = -1;
			try
			{
			/*
			  //lyh--
			   char szScriptFilename[MAX_PATH] = {0};
				sprintf_s(szScriptFilename, MAX_PATH - 1,"%s/Data/script/Intensify.lua", GetRootPath());
				LuaPlus::LuaStateOwner luaStateOwner;
				ScriptManager::instance().executeFile(szScriptFilename, luaStateOwner);

				LuaFunction<int> GetWeaponIntensifyEffectModelFunc(luaStateOwner, "GetWeaponIntensifyEffectModel");
				nIntensifyModelID = GetWeaponIntensifyEffectModelFunc(nLocalModelId, stStar);*/
   
				if(!theIntensifyEffect.FindWeaponEffectID(nIntensifyModelID,nLocalModelId,stStar))
					nIntensifyModelID = -1;

			}
			catch (const LuaPlus::LuaException &e)
			{
				//::MessageBox(NULL, e.GetErrorMessage(), "/Data/script/Intensify.lua脚本错误", MB_OK | MB_ICONERROR);
				//LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, e.GetErrorMessage());
			}

			if (nIntensifyModelID != -1)
			{
				pChild = MeNew MexAnimCtrl;
				pChild->ChangeModel( nIntensifyModelID ,FALSE, NULL);
				pChild->IAmComponent();
				if (!ChangeComponent( pMexAnimCtrl, nComponentID, 1, pRecord, pChild, szSkin, nSpecular, stStar ))
				{
					MeDelete pChild;
					pChild = NULL;
				}
			}
			return TRUE;
		}
		else if (nComponentID == eKeyAll_Helmet)		
		{
			MexAnimCtrl* pChild = MeNew MexAnimCtrl;
			pChild->ChangeModel( nModelID ,FALSE,NULL);
			pChild->IAmComponent();
			if (!ChangeComponent( pMexAnimCtrl, nComponentID, 0, pRecord, pChild, szSkin, nSpecular, stStar ))
			{
				delete pChild;
				pChild = NULL;
			}
			return TRUE;				
		}
	}
	else
	{
		if (nComponentID == eKeyAll_Armour)
		{
			CPlayerAnim *child_ptr = dynamic_cast<CPlayerAnim *>(pMexAnimCtrl);
			//child_ptr->setEquipEffect(eKeyAll_Armour, "Data//Effect/1.tga");
		}
	}

	ChangeComponent( pMexAnimCtrl, nComponentID, 0, pRecord, NULL, szSkin, nSpecular, stStar);
	return TRUE;
	unguard;
}

BOOL CAvatar::ReleaseComponent( int nComponentID )
{
	guardfunc;
	if( !IsValidComponentID( nComponentID ) )
	{
		assert( false );
		return FALSE;
	}

	Component* pComponent = GetComponent( nComponentID );

	if( pComponent == NULL )
		return FALSE;

	if( pComponent->nModelID != -1 )
	{
		GetMexResMgr()->DestroyModel( pComponent->nModelID );
		pComponent->Clear();
	}
	
	return TRUE;
	unguard;
}

BOOL CAvatar::ReleaseAllComponents()
{
	guardfunc;
	for( int i = 0; i < m_Components.size(); i++ )
	{
		ReleaseComponent( i );
	}
	return TRUE;
	unguard;
}