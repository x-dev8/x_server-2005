#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include <assert.h>
#include "Me3d/include.h"
#include "Me3d/AnimTimeLine.h"
#include "Me3d/Model/MexConfig.h"
//#include "Stdcharskeleton.h"
#include "Me3d/Model/MtlAnim.h"
#include "Me3d/MathLib.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "FuncPerformanceLog.h"
#include "Me3d/engine/Engine.h"
#include "FilePath.h"
//#include "Me3d/Model/Avatar.h"
#include "Me3d/MoreAction.h"
#include "Dxsdk/d3d9types.h"
// #include "Scene/TerrainBlend.h"
#include "Me3d/Model/Mex2.h"

#include "Me3d/engine/RendererDx.h"

// add [6/4/2008 whu]
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Model/BowStringBindingConfig.h"
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
//extern DWORD g_dwSceneObjLoopTime;
extern void ConvertMatrixToTranslationAndRotation( MeMatrix& m, Vector& v, Quaternion& q );
BOOL	g_bMirrorX = FALSE;
#include "logmgr.h"
#include "Me3d/Effect/BladeRibbon.h"
int g_MainThreadId = -1;
//DWORD	g_dwAnimBlendingStep = 200;

static DWORD g_dwUpdateComponentsUsedTime = 0;
static DWORD g_dwUpdateComponentTimes = 0;

#define LIGHTTRACKDEADRENDERTIME 618

//class CSmart
//{
//public:
//	~CSmart()
//	{
//		FILE* fp = fopen( "smart.log", "w" );
//		if( fp )
//		{
//			fprintf( fp, "use time = %ld\n", g_dwUpdateComponentsUsedTime );
//			fprintf( fp, "times = %ld\n", g_dwUpdateComponentTimes );
//			fprintf( fp, "average %f", ((float)g_dwUpdateComponentsUsedTime)/g_dwUpdateComponentTimes );
//		}
//		fclose( fp );
//	}
//};
//CSmart s;

MexAnimCtrlSkeleton::MexAnimCtrlSkeleton():
m_pSkeleton(NULL),
m_nNumBone(0),
m_pBones(NULL)
{
	guardfunc;
	unguard;
}

MexAnimCtrlSkeleton::~MexAnimCtrlSkeleton()
{
	guardfunc;
	Destroy();
	unguard;
}

BOOL MexAnimCtrlSkeleton::Create( IMexSkeleton* pSkeleton )
{
	guardfunc;
	Destroy();
	m_pSkeleton = pSkeleton;
	m_nNumBone = m_pSkeleton->GetBoneCount();
	m_pBones = MeNew Bone[m_nNumBone];
	for( int nBone = 0; nBone < m_nNumBone; nBone++ )
	{
		IMexBone* pSrcBone = m_pSkeleton->GetBone( nBone );
		Bone* pBone = &m_pBones[nBone];
		pBone->pBone = pSrcBone;

		pBone->matFrame0Inv = *(D3DXMATRIX*)pSrcBone->GetFrame0Inv();
		pBone->pMatrices = (D3DXMATRIX*)pSrcBone->GetMatrices( 0 );
	}

	return TRUE;
	unguard;
}

void MexAnimCtrlSkeleton::Destroy()
{
	guardfunc;
	if( m_pBones )
	{
		delete[] m_pBones;
		m_pBones = NULL;
	}
	m_pSkeleton = NULL;
	m_nNumBone = 0;
	unguard;
}

int GetVertexStride( DWORD dwFvf )
{
	guardfunc;
	int nStride = 0;
	if( dwFvf & D3DFVF_XYZ )
		nStride += 3*sizeof(float);
	if( dwFvf & D3DFVF_NORMAL )
		nStride += 3*sizeof(float);
	if( dwFvf & D3DFVF_DIFFUSE )
		nStride += sizeof(DWORD);
	if( dwFvf & D3DFVF_TEX1 )
		nStride += sizeof(float)*2;
	if( dwFvf & D3DFVF_TEX2 )
		nStride += sizeof(float)*4;
	if( nStride == 0 )
	{
		assert( false );
	}

	return nStride;
	unguard;
}

//////////////////////////////////////////////////////////////////////////
DWORD MexAnimCtrl::m_dwGameTime = 0;
void MexAnimCtrl::SetGameTime( DWORD dwTime )
{
	guardfunc;
	m_dwGameTime = dwTime;
	unguard;
}
DWORD MexAnimCtrl::GetGameTime()
{
	guardfunc;
	return m_dwGameTime;
	unguard;
}

MexAnimCtrl::MexAnimCtrl():
m_nFrameCount(0),
m_pMex( NULL ),
m_pMexCfg( NULL ),
m_pSeqUpperBody( NULL ),
m_pSeqLowerBody( NULL ),
m_nFrameId( 0 ),
//m_bRenderMesh(TRUE),
m_bNeedLimitLocalBBox(FALSE),
m_nModelId(-1),
m_bSelect( false ),
m_pAvatarSetting(NULL),
m_bHasEnvLight(FALSE),
m_nHitPointFrameID(-1),
m_nNumPlayTask(0),
m_nNumUpperBodyPlayTask(0),
m_nNumLowerBodyPlayTask(0),
m_amatBoneInWorldSpace(NULL),
m_amatBoneInModelSpace(NULL),
m_matSrcBones(NULL),
m_dwRenderFlag(0),
m_bAni(TRUE),
m_bIsComponent(FALSE),
m_bMirrorX(FALSE),
_enableChildren( true )
,m_bBindingBowString(false)
,m_bNeedCheckBindingBowString(false)
,weaponModelId(-1)
,m_bRenderRibbon(true)
,m_pKeyTimeOfBoneMatrices(NULL)
,m_amatBoneMatricesFromKeyTime(NULL)
,m_pTargetKeyTimeOfBoneMatrices(NULL)
,m_amatBoneMatricesTargetKeyTime(NULL)
,m_bIsInThread( false )
{
	guardfunc;
	int i = 0;
	//	D3DUtil_InitMaterial
//	D3DUtil_InitMaterial(m_Mtl, 0.2f, 0.2f, 0.2f, 0.2f );

	for( i = 0; i < eMaxParticleEmitter; i++ )
	{
		m_pParticleEmitters[i] = NULL;
	}
	for( i = 0; i < eMaxRibbonEmitter; i++ )
	{
		m_pRibbonEmitters[i] = NULL;
	}

	m_UpperBodyAnimTimeLine.Reset();
	m_LowerBodyAnimTimeLine.Reset();

	m_bUpperBodyAndLowerBodyMode = FALSE;
	m_bNeedInitUpperBodyAndLowerBody = FALSE;

	m_vUpperBodyRootBonePos.clear();
	m_vLowerBodyRootBonePos.clear();
	m_vSpineBonePosOffset.clear();

	m_bUpperBodyPlayOver = TRUE;
	m_bLowerBodyIdle = FALSE;
	m_bUpperBodyIdle = FALSE;

	m_bUpperBodyBackBlending = FALSE;
	m_dwUpperBodyStartBackBlendingTime = 0;

	m_bLowerBodyBackBlending = FALSE;
	m_dwLowerBodyStartBackBlendingTime = 0;

	m_fUpperBodyFactor = 0;
	m_fLowerBodyFactor = 0;

	m_fUpperBodyRot = 0.0f;
	m_fLowerBodyRot = 0.0f;

	m_bUpperBodyBlending = FALSE;
	m_bLowerBodyBlending = FALSE;
	m_bBodyLastBlend	= FALSE;
    m_vctBlendTransQuats.clear();

	m_dwUpperBodyStartBlendingTime = 0;
	m_dwLowerBodyStartBlendingTime = 0;

	m_dwUpperBodyBlendingStep = 0;
	m_dwLowerBodyBlendingStep = 0;

	m_fCurUpperBodyFrame = 0.0;
	m_fCurLowerBodyFrame = 0.0;

	m_bUpdateComponents = FALSE;

	m_fCurBodyFrame = 0;
	m_bEffectAnim = FALSE;

	m_nBipBoneID = -1;
	m_nUpperBodyRootBoneID = -1;

	//   added 2004.08.06
	//for( i = 0; i < eMaxLight; i++ )
	//{
	//	m_pLights[i] = NULL;
	//}
	//   added 2004.06.15

	//m_pBindPlayer = NULL;

	m_vPosition = Vector( 0.f, 0.f, 0.f );
	m_fZRotTheta = 0;
	m_fYRotTheta = 0;
	m_fXRotTheta = 0;
	m_fScaleX = Config::m_fMdlSpaceScale;
	m_fScaleY = Config::m_fMdlSpaceScale;
	m_fScaleZ = Config::m_fMdlSpaceScale;

	m_vPrePosition = Vector( 0.f, 0.f, 0.f );
	m_vPreRotation = Vector( 0.f, 0.f, 0.f );
	m_vPreScale = Vector(m_fScaleX, m_fScaleY, m_fScaleZ);
	float *fM = (float*)m_vPreTransformMatrix.m;
	for(int i=0; i<16; i++)
	{
		fM[i] = 0.f;
	}

	m_dwHairColor[0] = 255;
	m_dwHairColor[1] = 255;
	m_dwHairColor[2] = 255;

	m_bNotTexture = FALSE;

	m_dwLightTrackDeadTime = 0;
	m_fLightTrackAlpha = 0;

	m_nUpperBodyAnimType = -1;
	m_nLowerBodyAnimType = -1;

	m_bCanBlending = FALSE;
	m_HasEmitter = FALSE;
	m_HasBillboard = false;
	m_bUpdatedBillboardBBox = false;

	m_bUseSkinMesh = TRUE;
	m_bUpperBodyPlayingComAnim = FALSE;
	m_bPlayingWholeBodyAnim = FALSE;
	m_bRenderFirstPart = false;

	PartOffset = 0;
	m_SpecularTexID = -1;

    m_pUseTextureProj = NULL;
	m_pUseShimmerGrayTextureProj = NULL;
    m_pUseLuminanceTexProj = NULL;

    m_pMaterial = NULL;

	m_bIsTerrainModel = FALSE;

	m_LuminanceTextureProj.Loaded(FALSE);

 	unguard;
}
MexAnimCtrl::~MexAnimCtrl()
{
	guardfunc;
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			assert( false && "mex anim ctrl, particle emitter not release" );
		}
	}
	for( int i = 0; i < eMaxRibbonEmitter; i++ )
	{
		if( m_pRibbonEmitters[i] )
		{
			assert( false && "mex anim ctrl, ribbon emitter not release" );
		}
	}

// 	if( m_pAvatar )
// 	{
// 		assert( false );
// 	}
	
// 	if( m_bIsTerrainModel && m_pMex )
// 		m_pMex->Release();
// 	m_pMex = NULL;
// 	if( m_bIsTerrainModel && m_pMexCfg )
// 	{
// 		m_pMexCfg->Destroy();
// 		delete m_pMexCfg;
// 	}
	m_pMexCfg = NULL;

    detachAllChild();

	unguard;
}

void MexAnimCtrl::Destroy()
{
	guardfunc;
	m_SpecularTexID = -1;
	m_HasEmitter = FALSE;
	m_HasBillboard = false;
	guard(test1);
	if( m_pAvatarSetting )
	{
		CloseAvatarSetting( m_pAvatarSetting );
		m_pAvatarSetting = NULL;
	}
	unguard;

	guard(test2);
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->Release();
			m_pParticleEmitters[i] = NULL;
		}
	}
	unguard;



	//ClearMtlAnims();

	//   added 2004.08.06
	//for(int i = 0; i < eMaxLight; i++ )
	//{
	//	if( m_pLights[i] )
	//	{
	//		//g_Me3dLightMgr.UnRegisterLight( m_pLights[i]->nLightId );
	//		//delete m_pLights[i];
	//		m_pLights[i]->Release();
	//		m_pLights[i] = NULL;
	//	}
	//}

	guard(test4);
	ReleaseLastModel();
	unguard;
	


	guard(test5);
// 	if( m_pAvatar )
// 	{
// 		//m_pAvatar->ReleaseAllComponents();
// 		delete m_pAvatar;
// 		m_pAvatar = NULL;
// 	}
	if( m_amatBoneInWorldSpace )
	{
		delete[] m_amatBoneInWorldSpace;
		m_amatBoneInWorldSpace = NULL;
		m_matSrcBones = NULL;
		m_amatBoneInModelSpace = NULL;
	}
	if( m_pKeyTimeOfBoneMatrices )
	{
		delete[] m_pKeyTimeOfBoneMatrices;
		m_pKeyTimeOfBoneMatrices = NULL;
	}
	if( m_amatBoneMatricesFromKeyTime )
	{
		delete[] m_amatBoneMatricesFromKeyTime;
		m_amatBoneMatricesFromKeyTime = NULL;
	}

	if( m_pTargetKeyTimeOfBoneMatrices )
	{
		delete[] m_pTargetKeyTimeOfBoneMatrices;
		m_pTargetKeyTimeOfBoneMatrices = NULL;
	}
	if( m_amatBoneMatricesTargetKeyTime )
	{
		delete[] m_amatBoneMatricesTargetKeyTime;
		m_amatBoneMatricesTargetKeyTime = NULL;
	}
	unguard;

	guard(test3);
	for( int i = 0; i < eMaxRibbonEmitter; i++ )
	{
		if( m_pRibbonEmitters[i] )
		{
			m_pRibbonEmitters[i]->Release();
			m_pRibbonEmitters[i] = NULL;
		}
	}
	unguard;

	m_pMex		= NULL;
	m_pMexCfg	= NULL;

    m_vctBlendTransQuats.clear();

	unguard;
}

DWORD MexAnimCtrl::GetAnimTimeLength( const char* pszActionname )
{
	guardfunc;
	if( !m_pMexCfg )
	{
	//	assert( false && "get anim time length mex cfg is NULL" );
		return 0;
	}
	MexCfgSequence* pSequence;
	pSequence = m_pMexCfg->GetSequence( pszActionname );
	
	// not found
	if( pSequence == NULL )
	{
		return 0;
	}
	int nStartFrameId = pSequence->m_npStartFrameId.GetNumber();
	int nEndFrameId = pSequence->m_npEndFrameId.GetNumber();
	int nFrameCount =	nEndFrameId-nStartFrameId+1;

	// 现在的动画都是每秒30帧
	return 	nFrameCount*ONEFRAMEINTERVAL;

	unguard;
}

void MexAnimCtrl::ResetPlayTask( SPlayTask* pTask )
{
	guardfunc;
	strcpy( pTask->szActionname, "idle" );
	pTask->dwTimeOut = eMaxTimeout;
	pTask->dwStartTime = 0;
	pTask->dwPlayMode = eNormalPlay;
	pTask->dwOneLoopTime = 0;
	pTask->dwLoopTimes = eMaxLoopTimes;
	pTask->dwNeedBlendingTime = 0;
	pTask->bWholeBodyAnim = FALSE;
	unguard;
}

void MexAnimCtrl::ClearAnims()
{
	guardfunc;
	//m_nNumUpperBodyPlayTask = 0;
	//m_nNumLowerBodyPlayTask = 0;
	m_nNumPlayTask = 0;
	m_nFrameId = 0;
	m_pSeqUpperBody = NULL;
	unguard;
}

void MexAnimCtrl::ClearUpperBodyAnims()
{
	guardfunc;
	m_nNumUpperBodyPlayTask = 0;
	//m_pSeqUpperBody = NULL;
	unguard;
}

void MexAnimCtrl::ClearLowerBodyAnims()
{
	guardfunc;
	m_nNumLowerBodyPlayTask = 0;
	//m_pSeqLowerBody = NULL;
	unguard;
}

// void MexAnimCtrl::SetAvatar( CAvatar* pAvatar )
// {
// 	m_pAvatar = pAvatar;
// 	//m_pAvatar->BindAttachments( this );
// }

void MexAnimCtrl::SetMex( IMex* pMex, MexCfg* pMexCfg ,const char* pszSkin)
{
	guardfunc;
	m_pMex = pMex;
	m_pMexCfg = pMexCfg;

	m_HasEmitter = FALSE;
	m_HasBillboard = false;
	if( !m_pMex )
	{
		return;
	}
	if( !m_pMexCfg )
	{
		return;
	}
	//if( m_pMex->GetSequences()->GetSequenceCount() == 0 )
	//{
	//	return;
	//}

	assert( m_pMex != NULL && "mex is null" );
	assert( m_pMexCfg != NULL && "mex cfg is null" );
	//assert( m_pMex->GetSequences()->GetSequenceCount() > 0 && "mex has no sequence" );

	//if( m_pMex->GetGeometry() )
	//{
	//	m_vectorSubsetDisplayFlag.clear();
	//	m_vectorSubsetDisplayFlag.reserve( m_pMex->GetGeometry()->GetChunkCount() );
	//	m_vectorSubsetDisplayFlag.resize( m_pMex->GetGeometry()->GetChunkCount() );
	//	memset( &m_vectorSubsetDisplayFlag[0], 0x01, m_pMex->GetGeometry()->GetChunkCount() );
	//}
	std::string strSkin = DEFAULT_AVATARSETTING_NAME;
	if (pszSkin && strcmp( pszSkin, "" ) != 0)
	{
		strSkin = pszSkin;
	}
	ChangeAvatarSetting( strSkin.c_str() );
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->Release();
			m_pParticleEmitters[i] = NULL;
		}
	}

	// added, jiayi, [2009.4.20]
	if(m_pMex->GetGeometry())
	{
		for( int i = 0; i < m_pMex->GetGeometry()->GetChunkCount(); i++ )
		{
			Mex2GeoChunk* pChunk = (Mex2GeoChunk*)m_pMex->GetGeometry()->GetChunk(i);
			if(pChunk->IsBillboard())
			{
				m_HasBillboard = true;
				break;
			}
		}
	}	

	if( m_pMex->GetParticleEmitters() )
	{
		int nEmitterCount = m_pMex->GetParticleEmitters()->GetEmitterCount();
		if( nEmitterCount > 0 )
		{
			for( int i = 0; i < nEmitterCount && i < eMaxParticleEmitter; i++ )
			{
				m_pParticleEmitters[i] = m_pMex->GetParticleEmitters()->GetEmitter(i)->Clone();
				m_HasEmitter = TRUE;
			}
		}
	}
	
	for( int i = 0; i < eMaxRibbonEmitter; i++ )
	{
		if( m_pRibbonEmitters[i] )
		{
			m_pRibbonEmitters[i]->Release();
			m_pRibbonEmitters[i] = NULL;
		}
	}
	if( m_pMex->GetRibbonEmitters() )
	{ 
		int nEmitterCount = m_pMex->GetRibbonEmitters()->GetEmitterCount();
		if( nEmitterCount > 0 )
		{
			for( int i = 0; i < nEmitterCount && i < eMaxRibbonEmitter ; i++ )
			{
				m_pRibbonEmitters[i] = m_pMex->GetRibbonEmitters()->GetEmitter(i)->Clone();
				m_HasEmitter = TRUE;
			}
		}
	}
	//if( m_pMex->GetLights() )
	//{
	//	int nLightCount = m_pMex->GetLights()->GetLightCount();
	//	if( nLightCount > 0 )
	//	{
	//		//Mex2Light* lights = &m_pMex->GetLights()->vectorLight[0];
	//		for( int i = 0; i < nLightCount; i++ )
	//		{
	//			IMexLight* pSrcLight = m_pMex->GetLights()->GetLight( i );
	//			IMexLight* l = pSrcLight->Clone();
	//			//*l = lights[i];
	//		
	//			m_pLights[i] = l;
	//		}
	//	}
	//}

	m_nFrameId = 0;

	if( m_bUpperBodyAndLowerBodyMode )
	{
		ClearUpperBodyAnims();
		ClearLowerBodyAnims();
		PushUpperBodyAnim( NULL );
		PushLowerBodyAnim( NULL );
	}
	else
	{
		ClearAnims();
		PushAnim( NULL );
	}
	unguard;
}
int MexAnimCtrl::GetFrameCount()
{
	guardfunc;
	return m_nFrameCount;
	unguard;
}
BOOL MexAnimCtrl::PlayAnimByName( const char* pszActionname, DWORD dwOneLoopTime, BOOL bLoopPlay/* = TRUE*/ )
{
	guardfunc;
	SPlayTask task;
	ResetPlayTask( &task );
	strcpy( task.szActionname, pszActionname );

	task.dwOneLoopTime = dwOneLoopTime;
	task.dwStartTime = HQ_TimeGetTime();
	task.bLoopPlay = bLoopPlay;
	if( m_bUpperBodyAndLowerBodyMode )
	{
		ClearUpperBodyAnims();
		ClearLowerBodyAnims();
		PushUpperBodyAnim( &task );
		PushLowerBodyAnim( &task );
	}
	else
	{
		ClearAnims();
		PushAnim( &task );
	}
	return TRUE;
	unguard;
}
BOOL MexAnimCtrl::PlayAnim( int nStartFrameID, int nEndFrameID, DWORD dwOneLoopTime )
{
	guardfunc;
	m_TmpSequence.m_npStartFrameId.SetNumber( nStartFrameID );
	m_TmpSequence.m_npEndFrameId.SetNumber( nEndFrameID );
	m_TmpSequence.m_spAnimName.SetString( "temp2006" );
	m_TmpSequence.m_npHasLightTrack.SetNumber( 1 );

	PlayAnimByName( "temp2006", dwOneLoopTime );
	return FALSE;
	unguard;
}
// BOOL MexAnimCtrl::CloneAndMirrorX( MexAnimCtrl* pMexAnim )
// {
// 	if( !pMexAnim )
// 	{
// 		assert( false );
// 		return FALSE;
// 	}
// 	if( !pMexAnim->GetMex() )
// 	{
// 		assert( false );
// 		return FALSE;
// 	}
// 	IMex* pCloneMex = pMexAnim->GetMex()->Clone( eCloneMirrorXAxis );
// 	if( !pCloneMex )
// 		return FALSE;
// 	SetMex( pCloneMex, pMexAnim->GetMexCfg() );
// 	return TRUE;
// }


BOOL MexAnimCtrl::PlayAnim( SPlayTask* pTask )
{
	guardfunc;
	assert( pTask != NULL && "anim play task is null" );
	assert( pTask->szActionname[0] != 0 && "anim play task action name is NULL" );
	assert( pTask->dwTimeOut != 0 && "anim play task time out is 0" );
	assert( pTask->dwStartTime != 0 && "anim play task start time is 0" );

	//int nStartFrameId = 0;
	//int nEndFrameId = 0;
	int nFrameCount = 0;

	if( pTask->pMex )
		m_pMex = pTask->pMex;
	if( pTask->pMexCfg )
		m_pMexCfg = pTask->pMexCfg;

	//assert( m_pMexCfg != NULL );
	if( m_pMexCfg == NULL )
		return TRUE;

	bool bNoSequence = false;
	MexCfgSequence* pNewSequence = m_pMexCfg->GetSequence( pTask->szActionname );
    //printf_s("动画:%s\n", pTask->szActionname);
	if( !pNewSequence )
	{
		bNoSequence = true;
		pNewSequence = &m_TmpSequence;
	}

	int nHitPoint = -1;

	if( m_bUpperBodyAndLowerBodyMode )
	{
		//if( strstr( m_pMex->GetFilename(), "male" ))
		//{
		//	char msg[MAX_PATH];
		//	sprintf(msg, "PlayAnim: %s\n", pNewSequence->m_spAnimName.GetString());
		//	OutputDebugString(msg);
		//}

		if( pTask->bUpperBody )
		{
			m_bPlayingWholeBodyAnim = pTask->bWholeBodyAnim;
			if( pNewSequence->m_hitpoints.m_vectorHitPoint.size() > 0 )
			{
				m_nHitPointFrameID = pNewSequence->m_hitpoints.m_vectorHitPoint[0]->m_npFrameId.GetNumber();
			}
			else
			{
				m_nHitPointFrameID = -1;
			}

			if( m_pSeqUpperBody )
			{
				if( IsComSequence( m_pSeqUpperBody ) )
				{
					m_nStartFrameId = pNewSequence->m_npStartFrameId.GetNumber();
					m_nEndFrameId = pNewSequence->m_npEndFrameId.GetNumber();
					return TRUE;
				}
			}

			m_bBodyLastBlend = FALSE;
			if( m_bUpperBodyBlending )
			{
				if( m_pSeqUpperBody )
				{
					m_fCurUpperBodyFrame = m_pSeqUpperBody->GetBlendFrame( 1 );
					/* 切换动画之前已经是blending状态，m_fCurLowerBodyFrame设置无用，
					用Mex2Bone里的kLastBlendTrans和kLastBlendQuats进行运算*/
					m_bBodyLastBlend = TRUE;
				}
			}

			m_pSeqUpperBody = pNewSequence;

			if( bNoSequence )
				m_nUpperBodyAnimType = -1;
			else
				m_nUpperBodyAnimType = MoreAction::FindIdByName( m_pSeqUpperBody->m_spAnimName.GetString() );

			m_nStartFrameId = pNewSequence->m_npStartFrameId.GetNumber();
			m_nEndFrameId = pNewSequence->m_npEndFrameId.GetNumber();

			if( pTask->dwOneLoopTime == 0 )
			{
				nFrameCount = m_nEndFrameId-m_nStartFrameId+1;
				m_dwOneLoopTime = nFrameCount*ONEFRAMEINTERVAL;
			}
			else
			{
				m_dwOneLoopTime = pTask->dwOneLoopTime;
			}
		}
		else
		{
			/////////////////////// NoNeed
			m_bBodyLastBlend = FALSE;
			if( m_bLowerBodyBlending )
			{
				if( m_pSeqLowerBody )
				{
					m_fCurLowerBodyFrame = m_pSeqLowerBody->GetBlendFrame( 1 );
					/* 切换动画之前已经是blending状态，m_fCurLowerBodyFrame设置无用，
					用Mex2Bone里的kLastBlendTrans和kLastBlendQuats进行运算*/
					m_bBodyLastBlend = TRUE;
				}
			}

			m_pSeqLowerBody = pNewSequence;

			if( bNoSequence )
				m_nLowerBodyAnimType = -1;
			else
				m_nLowerBodyAnimType = MoreAction::FindIdByName( m_pSeqLowerBody->m_spAnimName.GetString() );

			m_nStartFrameId = pNewSequence->m_npStartFrameId.GetNumber();
			m_nEndFrameId = pNewSequence->m_npEndFrameId.GetNumber();

			if( pTask->dwOneLoopTime == 0 )
			{
				nFrameCount = m_nEndFrameId - m_nStartFrameId + 1;
				m_dwOneLoopTime = nFrameCount*ONEFRAMEINTERVAL;
			}
			else
			{
				m_dwOneLoopTime = pTask->dwOneLoopTime;
			}
		}
	}
	else
	{
		if( m_bUpperBodyBlending )
		{
			if( m_pSeqUpperBody )
			{
				m_fCurUpperBodyFrame = m_pSeqUpperBody->GetBlendFrame( 1 );
			}
		}

		if( pNewSequence->m_hitpoints.m_vectorHitPoint.size() > 0 )
		{
			m_nHitPointFrameID = pNewSequence->m_hitpoints.m_vectorHitPoint[0]->m_npFrameId.GetNumber();
		}
		else
		{
			m_nHitPointFrameID = -1;
		}

		m_pSeqUpperBody = pNewSequence;

		//if( m_pSeqUpperBody == NULL )
		//{
		//	m_pSeqUpperBody = m_pMexCfg->m_sequences.m_vectorSequence[0];
		//}

		if( bNoSequence )
			m_nUpperBodyAnimType = -1;
		else
			m_nUpperBodyAnimType = MoreAction::FindIdByName( m_pSeqUpperBody->m_spAnimName.GetString() );

		m_nStartFrameId = pNewSequence->m_npStartFrameId.GetNumber();
		m_nEndFrameId = pNewSequence->m_npEndFrameId.GetNumber();

		if( pTask->dwOneLoopTime == 0 )
		{
			nFrameCount = m_nEndFrameId-m_nStartFrameId+1;
			m_dwOneLoopTime = nFrameCount*ONEFRAMEINTERVAL;
		}
		else
		{
			m_dwOneLoopTime = pTask->dwOneLoopTime;
		}
	}

	if( m_bUpperBodyAndLowerBodyMode )
	{
		if( pTask->bUpperBody )
		{
			m_UpperBodyAnimTimeLine.Reset();
			m_bUpperBodyBlending = TRUE;
			m_dwUpperBodyStartBlendingTime = HQ_TimeGetTime();
			m_dwUpperBodyBlendingStep = pTask->dwNeedBlendingTime;
			m_bUpperBodyPlayOver = FALSE;
			m_bUpperBodyBackBlending = FALSE;
			m_dwUpperBodyStartBackBlendingTime = 0;

			if( m_dwUpperBodyBlendingStep == 0 || !m_bCanBlending )
			{
				m_bUpperBodyBlending = FALSE;
				m_dwUpperBodyStartBlendingTime = 0;
				m_dwUpperBodyBlendingStep = 0;
			}

			//char szBuf[256];
			//_snprintf( szBuf, 256, "m_dwUpperBodyBlendingStep = %d m_dwOneLoopTime = %d", m_dwUpperBodyBlendingStep, m_dwOneLoopTime );
			//OutputDebugString( szBuf );

			m_UpperBodyAnimTimeLine.Play(
				HQ_TimeGetTime() + m_dwUpperBodyBlendingStep,
				m_nStartFrameId,
				m_nEndFrameId,
				m_nHitPointFrameID,
				m_dwOneLoopTime );

			if( pTask->bLoopPlay )
			{
				m_UpperBodyAnimTimeLine.SetLoopPlay();
			}
		}
		else
		{
			m_LowerBodyAnimTimeLine.Reset();
			m_bLowerBodyBlending = TRUE;
			m_dwLowerBodyStartBlendingTime = HQ_TimeGetTime();
			m_dwLowerBodyBlendingStep = pTask->dwNeedBlendingTime;
			m_bLowerBodyBackBlending = FALSE;
			m_dwLowerBodyStartBackBlendingTime = 0;

			if( m_dwLowerBodyBlendingStep == 0 || !m_bCanBlending )
			{
				m_bLowerBodyBlending = FALSE;
				m_dwLowerBodyStartBlendingTime = 0;
				m_dwLowerBodyBlendingStep = 0;
			}

			m_LowerBodyAnimTimeLine.Play(
				HQ_TimeGetTime() + m_dwLowerBodyBlendingStep,
				m_nStartFrameId,
				m_nEndFrameId,
				-1,
				m_dwOneLoopTime );

			if( pTask->bLoopPlay )
			{
				m_LowerBodyAnimTimeLine.SetLoopPlay();
			}
		}
	}
	else
	{
		m_UpperBodyAnimTimeLine.Reset();
		m_bUpperBodyBlending = TRUE;
		m_dwUpperBodyStartBlendingTime = HQ_TimeGetTime();
		m_dwUpperBodyBlendingStep = pTask->dwNeedBlendingTime;
		m_bUpperBodyBackBlending = FALSE;
		m_dwUpperBodyStartBackBlendingTime = 0;

		if( m_dwUpperBodyBlendingStep == 0 || !m_bCanBlending )
		{
			m_bUpperBodyBlending = FALSE;
			m_dwUpperBodyStartBlendingTime = 0;
			m_dwUpperBodyBlendingStep = 0;
		}

		//char szBuf[256];
		//_snprintf( szBuf, 256, "m_dwUpperBodyBlendingStep2 = %d m_dwOneLoopTime2 = %d", m_dwUpperBodyBlendingStep, m_dwOneLoopTime );
		//OutputDebugString( szBuf );

		m_UpperBodyAnimTimeLine.Play( 
			HQ_TimeGetTime() + m_dwUpperBodyBlendingStep,
			m_nStartFrameId,
			m_nEndFrameId,
			m_nHitPointFrameID,
			m_dwOneLoopTime );

		if( pTask->bLoopPlay )
		{
			m_UpperBodyAnimTimeLine.SetLoopPlay();
		}
	}

	//if( pTask->dwPlayMode == MexAnimCtrl::eHoldOnLastFrame )
	//	m_nFrameId = m_nEndFrameId;
	//else
	//	m_nFrameId = m_nStartFrameId;

	if( m_pSeqUpperBody && m_pSeqUpperBody->m_npHasLightTrack.GetNumber() )
	{
		ApplyBladeRibbon();
	}

	m_nLoopTimes = 0;
	return TRUE;
	unguard;
}

void MexAnimCtrl::PushUpperBodyAnim( SPlayTask* pTask )
{
	if( m_bUpperBodyAndLowerBodyMode )
	{
		if( !pTask )
		{
			//assert( false && "Push a Null Anim Task" );
			SPlayTask task;
			ResetPlayTask( &task );
			task.dwOneLoopTime = 0;
			task.dwStartTime = HQ_TimeGetTime();
			m_UpperBodyPlayTask[m_nNumUpperBodyPlayTask++] = task;
		}
		else
		{
			m_UpperBodyPlayTask[m_nNumUpperBodyPlayTask++] = *pTask;
		}

		if( m_nNumUpperBodyPlayTask == 1 )
			PlayAnim( &m_UpperBodyPlayTask[0] );

		if( m_nNumUpperBodyPlayTask > 3 )
		{
			assert( false );
		}
	}
}

void MexAnimCtrl::PushLowerBodyAnim( SPlayTask* pTask )
{
	if( m_bUpperBodyAndLowerBodyMode )
	{
		if( !pTask )
		{
			//assert( false && "Push a Null Anim Task" );
			SPlayTask task;
			ResetPlayTask( &task );
			task.dwOneLoopTime = 0;
			task.dwStartTime = HQ_TimeGetTime();
			task.dwNeedBlendingTime=0;
			m_LowerBodyPlayTask[m_nNumLowerBodyPlayTask++] = task;
		}
		else
		{
			m_LowerBodyPlayTask[m_nNumLowerBodyPlayTask++] = *pTask;
		}

		if( m_nNumLowerBodyPlayTask == 1 )
			PlayAnim( &m_LowerBodyPlayTask[0] );

		if( m_nNumLowerBodyPlayTask > 3 )
		{
			assert( false );
		}
	}
}

void MexAnimCtrl::PushAnim( SPlayTask* pTask )
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
	{
		if( !pTask )
		{
			//assert( false && "Push a Null Anim Task" );
			SPlayTask task;
			ResetPlayTask( &task );
			task.dwOneLoopTime = 0;
			task.dwStartTime = HQ_TimeGetTime();
			task.dwNeedBlendingTime=0;
			task.bLoopPlay=TRUE;
			m_PlayTasks[m_nNumPlayTask++] = task;
		}
		else
		{
			m_PlayTasks[m_nNumPlayTask++] = *pTask;
		}

		if( m_nNumPlayTask == 1 )
			PlayAnim( &m_PlayTasks[0] );

		if( m_nNumPlayTask > 3 )
		{
			assert( false );
		}
	}
	unguard;
}

Vector MexAnimCtrl::GetBoneWorldPos( int nBoneId, BOOL *bRetOk/* = NULL*/ )
{
	guardfunc;
	Mex2Bone* pBone = NULL;
	guard(pMex);
	if( !m_pMex )
	{
        if( bRetOk )
            *bRetOk = FALSE;
		return Vector( 0, 0, 0 );
	}
	unguard;

	guard( m_pMex->GetSkeleton() );
	if( !m_pMex->GetSkeleton() )
	{
        if( bRetOk )
            *bRetOk = FALSE;
		return Vector( 0, 0, 0 );
	}
	unguard;

	guard(test1);
	pBone = (Mex2Bone*)m_pMex->GetSkeleton()->GetBone(nBoneId);

	if( !pBone )
	{
		//assert( false );
		//MessageBox( 0, "找不到骨骼", "错误", MB_OK );
        if( bRetOk )
            *bRetOk = FALSE;
		return Vector( 0, 0, 0 );
	}
	unguard;

	MeMatrix* pMatrix;
	Vector pos;

	guard(test2);
	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !pSkeleton->m_bSpecialModel && !pBone->m_bFullFrame );
	if( pBone->HasKeyFrame() && bNewKeyFrameFormat )
	{
		MeMatrix matFrame0;
		D3DXMatrixInverse( (D3DXMATRIX*)&matFrame0, NULL, (D3DXMATRIX*)pBone->GetFrame0Inv() );
		pos.x = matFrame0.m[3][0];
		pos.y = matFrame0.m[3][1];
		pos.z = matFrame0.m[3][2];
	}
	else
	{
		pMatrix = (MeMatrix*)pBone->GetMatricesFromKeyTime(0, FRAMEPERSEC );
		pos.x = pMatrix->m[3][0];
		pos.y = pMatrix->m[3][1];
		pos.z = pMatrix->m[3][2];
	}
	unguard;

	guard(test3);
	D3DXVec3TransformCoord( (D3DXVECTOR3*)&pos, 
		(D3DXVECTOR3*)&pos,	
		(D3DXMATRIX*)&m_amatBoneInWorldSpace[nBoneId] );
	unguard;

    if( bRetOk )
        *bRetOk = TRUE;

	return pos;
	unguard;
}

D3DXMATRIX MexAnimCtrl::GetBoneMatrices( int nBoneId, BOOL *bRetOk/* = NULL*/ )
{
	guardfunc;
	guard(test1);
	MeMatrix kMatrix;
	memset( &kMatrix, 0x00, sizeof(kMatrix) );

	if( nBoneId < 0 )
	{
		//assert( false );
        if( bRetOk )
            *bRetOk = FALSE;

		return *(D3DXMATRIX*)&kMatrix;
	}

	Mex2Bone* pBone = NULL;
	guard(pMex);
	if( !m_pMex )
	{
        if( bRetOk )
            *bRetOk = FALSE;

		return *(D3DXMATRIX*)&kMatrix;
	}
	unguard;

	guard( m_pMex->GetSkeleton() );
	if( !m_pMex->GetSkeleton() )
	{
        if( bRetOk )
            *bRetOk = FALSE;

		return *(D3DXMATRIX*)&kMatrix;
	}
	unguard;

	pBone = (Mex2Bone*)m_pMex->GetSkeleton()->GetBone(nBoneId);
	if( !pBone )
	{
		//assert( false );
        if( bRetOk )
            *bRetOk = FALSE;

		return *(D3DXMATRIX*)&kMatrix;
	}

	guard(test2);
	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !pSkeleton->m_bSpecialModel && !pBone->m_bFullFrame );
	if( pBone->HasKeyFrame() && bNewKeyFrameFormat )
		D3DXMatrixInverse( (D3DXMATRIX*)&kMatrix, NULL, (D3DXMATRIX*)pBone->GetFrame0Inv() );
	else
		kMatrix = *((MeMatrix*)pBone->GetMatricesFromKeyTime(0,FRAMEPERSEC));

	Vector pos;
	pos.x = kMatrix.m[3][0];
	pos.y = kMatrix.m[3][1];
	pos.z = kMatrix.m[3][2];

	kMatrix.m[3][0] = 0;
	kMatrix.m[3][1] = 0;
	kMatrix.m[3][2] = 0;

	D3DXMatrixRotationAxis( (D3DXMATRIX*)&kMatrix, &D3DXVECTOR3( 0, -1, 0 ), 0 );

	kMatrix.m[0][0] *= -1;
	kMatrix.m[1][0] *= -1;
	kMatrix.m[2][0] *= -1;
	kMatrix.m[3][0] *= -1;

	kMatrix.m[3][0] = pos.x;
	kMatrix.m[3][1] = pos.y;
	kMatrix.m[3][2] = pos.z;

	D3DXMatrixMultiply(	(D3DXMATRIX*)&kMatrix, (D3DXMATRIX*)&kMatrix,	(D3DXMATRIX*)&m_amatBoneInWorldSpace[nBoneId] );

    if( bRetOk )
        *bRetOk = TRUE;

	return *(D3DXMATRIX*)&kMatrix;
	unguard;
	unguard;
	unguard;
}

BOOL IsParentBone( IMexSkeleton* pSkeleton, int nTryBoneID, int nBoneID )
{
	if( nTryBoneID == nBoneID )
		return FALSE;
	IMexBone* pBone = pSkeleton->GetBone( nBoneID );
    if( !pBone )
        return FALSE;
	int nParentID = pBone->GetParentId();
	if( nParentID == -1 )
		return FALSE;
	if( nParentID == nTryBoneID )
		return TRUE;
	return IsParentBone( pSkeleton, nTryBoneID, nParentID );

}
BOOL MexAnimCtrl::InitUpperBodyAndLowerBody()
{
	guardfunc;
	if( !m_pMex )
		return FALSE;

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();

	if( !pSkeleton )
	{
		assert( false );
		return FALSE;
	}

	m_nBipBoneID = pSkeleton->FindBone( "Bip01" );
	m_nUpperBodyRootBoneID = pSkeleton->FindBone( "Bip01 Spine1" );
	if( m_nUpperBodyRootBoneID == -1 )
	{
		m_bUpperBodyAndLowerBodyMode = FALSE;
		return FALSE;
	}
	else
	{
		m_bUpperBodyAndLowerBodyMode = TRUE;
	}

	int nNumBone = pSkeleton->GetBoneCount();
	int nWeaponBone = pSkeleton->FindBone( "WeaponBone" );
	int nWeaponBone1 = pSkeleton->FindBone( "WeaponBone1" );
	int nWeaponBone2 = pSkeleton->FindBone( "WeaponBone2" );

	m_vectorBodyBoneFlag.reserve( nNumBone );
	m_vectorBodyBoneFlag.resize( nNumBone );
	for( int nBone = 0; nBone < nNumBone; nBone++ )
	{
		if( nBone == m_nUpperBodyRootBoneID || IsParentBone( pSkeleton, m_nUpperBodyRootBoneID, nBone ) )
		{
			m_vectorBodyBoneFlag[nBone] = true;
		}
		else
		{
			m_vectorBodyBoneFlag[nBone] = false;
		}

		if( nBone == nWeaponBone || nBone == nWeaponBone1 || nBone == nWeaponBone2 )
		{
			m_vectorBodyBoneFlag[nBone] = true;
		}
	}
	return TRUE;
	unguard;
}

void MexAnimCtrl::UpdateBody( float x, 
							   float y, 
							   float z,				// 位置
							   float fScaleX,			// 缩放
							   float fScaleY,			// 缩放
							   float fScaleZ,			// 缩放
							   float fUpperBodyRot,	// 上半身朝向
							   float fLowerBodyRot,	// 下半身朝向
							   MexCfgSequence* pSeqUpperBody,
							   float fUpperBodyFactor,
							   BOOL bUpperBodyBlending,
							   MexCfgSequence* pSeqLowerBody,
							   float fLowerBodyFactor,
							   BOOL bLowerBodyBlending )
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
		return;

	if( !pSeqUpperBody || !pSeqLowerBody )
		return;

	if( m_nUpperBodyRootBoneID == -1 )
	{
		assert( false );
		return;
	}

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();
	if( !pSkeleton )
		return;

	MeMatrix matUpperBody;
	MeMatrix matLowerBody;

	int nBoneCount = pSkeleton->GetBoneCount();

	float fTargetUpperBodyFrame = 0;
	float fTargetLowerBodyFrame = 0;

	if( bUpperBodyBlending )
	{
		fTargetUpperBodyFrame = pSeqUpperBody->GetBlendFrame( 0 );
		//TODO::Aren的临时方案
		if( fUpperBodyFactor > 1 )
		{
			fUpperBodyFactor = 0;
		}
	}
	else
	{
		if( m_bUpperBodyBackBlending )
		{
			DWORD dwStep = HQ_TimeGetTime() - m_dwUpperBodyStartBackBlendingTime;
			if( dwStep < (eDefaultBlendingTime*2/*4*/) )
			{
				bUpperBodyBlending = TRUE;
				fTargetUpperBodyFrame = pSeqUpperBody->GetBlendFrame( fUpperBodyFactor );
				fUpperBodyFactor = (float)dwStep/(eDefaultBlendingTime*2/*4*/);
			}
			else
			{
				m_bUpperBodyBackBlending = FALSE;
				m_fCurUpperBodyFrame = pSeqUpperBody->GetBlendFrame( fUpperBodyFactor );
			}
		}
		else
		{
			m_fCurUpperBodyFrame = pSeqUpperBody->GetBlendFrame( fUpperBodyFactor );
		}
	}

	if( bLowerBodyBlending )
	{
		fTargetLowerBodyFrame = pSeqLowerBody->GetBlendFrame( 0 );
		//TODO::Aren的临时方案
		if( fLowerBodyFactor > 1 )
		{
			fLowerBodyFactor = 0;
		}
	}
	else
	{
		if( m_bLowerBodyBackBlending)
		{
			DWORD dwStep = HQ_TimeGetTime() - m_dwLowerBodyStartBackBlendingTime;
			if( dwStep < (eDefaultBlendingTime*2) )
			{
				bLowerBodyBlending = TRUE;
				fTargetLowerBodyFrame = pSeqLowerBody->GetBlendFrame( fLowerBodyFactor );
				fLowerBodyFactor = (float)dwStep/(eDefaultBlendingTime*2);
			}
			else
			{
				m_bLowerBodyBackBlending = FALSE;
				m_fCurLowerBodyFrame = pSeqLowerBody->GetBlendFrame( fLowerBodyFactor );
			}
		}
		else
		{
			m_fCurLowerBodyFrame = pSeqLowerBody->GetBlendFrame( fLowerBodyFactor );
		}
	}

	//char szBuf[256];
	//_snprintf( szBuf, 256, "fTargetUpperBodyFrame = %f fTargetLowerBodyFrame = %f", fTargetUpperBodyFrame, fTargetLowerBodyFrame );
	//OutputDebugString( szBuf );
	//_snprintf( szBuf, 256, "m_fCurUpperBodyFrame = %f m_fCurLowerBodyFrame = %f", m_fCurUpperBodyFrame, m_fCurLowerBodyFrame );
	//OutputDebugString( szBuf );
	//_snprintf( szBuf, 256, "UpperFrame = %s", 	pSeqUpperBody->m_spAnimName.GetString() );
	//OutputDebugString( szBuf );

	IMexBone* pBone = pSkeleton->GetBone(m_nUpperBodyRootBoneID);
	if( !pBone )
		return;

	if( pSeqUpperBody != pSeqLowerBody )
	{
		float fUpperRotation = pBone->GetRotation( m_fCurUpperBodyFrame, FRAMEPERSEC );
		float fLowerRotation = pBone->GetRotation( m_fCurLowerBodyFrame, FRAMEPERSEC );
		float fUpperLowerAngle = fUpperRotation - fLowerRotation;

		if( fUpperLowerAngle > D3DX_PI )
		{
			fUpperLowerAngle = fUpperLowerAngle - D3DX_PI*2;
		}

		if( fUpperLowerAngle < -D3DX_PI )
		{
			fUpperLowerAngle = fUpperLowerAngle + D3DX_PI*2;
		}

		if( fUpperLowerAngle > D3DX_PI/180.f*61.8f )
		{
			fUpperLowerAngle -= D3DX_PI/180.f*61.8f;
		}
		else if( fUpperLowerAngle < -D3DX_PI/180.f*61.8f )
		{
			fUpperLowerAngle += D3DX_PI/180.f*61.8f;
		}
		else
		{
			fUpperLowerAngle = 0;
		}

		fUpperBodyRot -= fUpperLowerAngle;

		//char szBuf[256];
		//_snprintf( szBuf, 256, "fUpper%f - fLower%f = %f\n",fUpperRotation/D3DX_PI*180,fLowerRotation/D3DX_PI*180, fUpperLowerAngle/D3DX_PI*180 );
		//OutputDebugString( szBuf );

		//fUpperBodyRot = fmodf( fUpperBodyRot, D3DX_PI*2 );
		//if( fUpperBodyRot < 0 )
		//{
		//	fUpperBodyRot += D3DX_PI*2;
		//}
	}

	///////// 1
	{
		CalcTransformMatrix( x, y, z, fUpperBodyRot, fScaleX, fScaleY, fScaleZ, &matUpperBody );
		matLowerBody = *(MeMatrix*)GetTransform();
	}

	///////////// 2
	//{
	//	matUpperBody = *(MeMatrix*)GetTransform();
	//	matLowerBody = *(MeMatrix*)GetTransform();
	//}

	//CalcTransformMatrix( matLowerBody.m[3][0], matLowerBody.m[3][1], matLowerBody.m[3][2], fUpperBodyRot, fScale, &matUpperBody );

	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel);
	if( bLowerBodyBlending && pBone->HasKeyFrame() )
	{
		MeMatrix* pMatrix = (MeMatrix*)GetKeyFrameBlendedMatrices(pBone, fLowerBodyFactor, m_fCurLowerBodyFrame, fTargetLowerBodyFrame, FRAMEPERSEC, m_bBodyLastBlend, 
			&m_vctBlendTransQuats[m_nUpperBodyRootBoneID].kLastBlendTrans, &m_vctBlendTransQuats[m_nUpperBodyRootBoneID].kLastBlendQuats);
		if( pMatrix )
		{
			D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], (D3DXMATRIX*)pBone->GetFrame0Inv(), (D3DXMATRIX*)pMatrix );
		}

		IMexBone* pBipBone = pSkeleton->GetBone(m_nBipBoneID);
		if( pBipBone && pBipBone->HasKeyFrame() )
		{
			MeMatrix BipBoneMatrices;
			MeMatrix LowerBodyMatrices = matLowerBody;
			MeMatrix* pTempMatrix;
			pTempMatrix = (MeMatrix*)GetKeyFrameBlendedMatrices(pBipBone, fLowerBodyFactor, m_fCurLowerBodyFrame, fTargetLowerBodyFrame, FRAMEPERSEC, 
				m_bBodyLastBlend, &m_vctBlendTransQuats[m_nBipBoneID].kLastBlendTrans, &m_vctBlendTransQuats[m_nBipBoneID].kLastBlendQuats );

			if( pTempMatrix )
			{
				D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nBipBoneID], (D3DXMATRIX*)pBipBone->GetFrame0Inv(), (D3DXMATRIX*)pTempMatrix );


				BipBoneMatrices = *pTempMatrix;

				BipBoneMatrices.m[0][0] *= -1;
				BipBoneMatrices.m[1][0] *= -1;
				BipBoneMatrices.m[2][0] *= -1;
				BipBoneMatrices.m[3][0] *= -1;

				LowerBodyMatrices.m[3][0] = 0;
				LowerBodyMatrices.m[3][1] = 0;
				LowerBodyMatrices.m[3][2] = 0;

				D3DXMatrixMultiply( 
					(D3DXMATRIX*)&BipBoneMatrices, 
					(D3DXMATRIX*)&BipBoneMatrices,
					(D3DXMATRIX*)&LowerBodyMatrices );

				m_vSpineBonePosOffset.x = BipBoneMatrices.m[3][0];
				m_vSpineBonePosOffset.y = BipBoneMatrices.m[3][1];
				m_vSpineBonePosOffset.z = BipBoneMatrices.m[3][2];

			}
		}
	}
	else
	{
		if( pBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧动画, pBone->m_bFullFrame为true也可以走这段
		{
			BOOL bGetParentMat = FALSE;
			if( pBone->GetParentId() >= 0 )
				bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurLowerBodyFrame, pBone->GetParentId());

			float* pMatrix = NULL;
			if( bGetParentMat )
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
			else
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC);

			SetBoneMatricesAtTime(m_fCurLowerBodyFrame, m_nUpperBodyRootBoneID, pMatrix);

			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pMatrix );
		}
		else
			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC) );

		Mex2Bone* pBipBone = (Mex2Bone*)pSkeleton->GetBone(m_nBipBoneID);
		if( pBipBone )
		{
			BOOL bGetParentMat = FALSE;
			if( pBipBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧动画, pBone->m_bFullFrame为true也可以走这段
			{
				if( pBone->GetParentId() >= 0 )
					bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurLowerBodyFrame, pBipBone->GetParentId());
			}

			MeMatrix BipBoneMatrices;
			MeMatrix LowerBodyMatrices = matLowerBody;
			if( bGetParentMat )
				BipBoneMatrices = *(MeMatrix*)pBipBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBipBone->GetParentId()]);
			else
				BipBoneMatrices = *(MeMatrix*)pBipBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC);

			if( pBipBone->HasKeyFrame() && bNewKeyFrameFormat && !pBipBone->m_bFullFrame )	// 关键帧动画
				SetBoneMatricesAtTime(m_fCurLowerBodyFrame, m_nBipBoneID, (float*)&BipBoneMatrices);

			BipBoneMatrices.m[0][0] *= -1;
			BipBoneMatrices.m[1][0] *= -1;
			BipBoneMatrices.m[2][0] *= -1;
			BipBoneMatrices.m[3][0] *= -1;

			LowerBodyMatrices.m[3][0] = 0;
			LowerBodyMatrices.m[3][1] = 0;
			LowerBodyMatrices.m[3][2] = 0;

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&BipBoneMatrices, 
				(D3DXMATRIX*)&BipBoneMatrices,
				(D3DXMATRIX*)&LowerBodyMatrices );

			m_vSpineBonePosOffset.x = BipBoneMatrices.m[3][0];
			m_vSpineBonePosOffset.y = BipBoneMatrices.m[3][1];
			m_vSpineBonePosOffset.z = BipBoneMatrices.m[3][2];
		}
	}

	// 在模型空间中的变换
	memcpy( &m_amatBoneInModelSpace[m_nUpperBodyRootBoneID], &m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], sizeof( MeMatrix ) );

	// 镜像
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[0][0] *= -1;
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[1][0] *= -1;
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[2][0] *= -1;
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[3][0] *= -1;

	D3DXMatrixMultiply( 
		(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
		(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID],
		(D3DXMATRIX*)&matLowerBody );

	////////////////////////////////////////////////////
	m_vLowerBodyRootBonePos = GetBoneWorldPos(m_nUpperBodyRootBoneID);

	//D3DXMATRIX matTransform = GetBoneMatrices( m_nUpperBodyRootBoneID );
	//matUpperBody = *(MeMatrix*)&matTransform;

	if( bUpperBodyBlending && pBone->HasKeyFrame() )
	{
		float *pBlendMatrix = GetKeyFrameBlendedMatrices( pBone,
			fUpperBodyFactor,
			m_fCurUpperBodyFrame,
			fTargetUpperBodyFrame,
			FRAMEPERSEC,
			m_bBodyLastBlend,
			&m_vctBlendTransQuats[m_nUpperBodyRootBoneID].kLastBlendTrans,
			&m_vctBlendTransQuats[m_nUpperBodyRootBoneID].kLastBlendQuats );

		D3DXMatrixMultiply( 
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
			(D3DXMATRIX*)pBone->GetFrame0Inv(),
			(D3DXMATRIX*)pBlendMatrix );
	}
	else
	{
		if( pBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧
		{
			BOOL bGetParentMat = FALSE;
			if( pBone->GetParentId() >= 0 )
				bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurUpperBodyFrame, pBone->GetParentId());

			float* pMatrix = NULL;
			if( bGetParentMat )
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
			else
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame,FRAMEPERSEC);

			SetBoneMatricesAtTime(m_fCurUpperBodyFrame, m_nUpperBodyRootBoneID, pMatrix);

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pMatrix );
		}
		else
			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame,FRAMEPERSEC) );
	}

	// 在模型空间中的变换
	memcpy( &m_amatBoneInModelSpace[m_nUpperBodyRootBoneID], &m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], sizeof( MeMatrix ) );

	// 镜像
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[0][0] *= -1;
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[1][0] *= -1;
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[2][0] *= -1;
	//m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID].m[3][0] *= -1;

	D3DXMatrixMultiply( 
		(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
		(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID],
		(D3DXMATRIX*)&matUpperBody );

	m_vUpperBodyRootBonePos = GetBoneWorldPos(m_nUpperBodyRootBoneID);



	/////////// 1 下面有问题，朝向不一至的时候偏差是不对的！
	{
		Vector	vUpperBodyLowerBodyOffset = m_vLowerBodyRootBonePos - m_vUpperBodyRootBonePos;
		CalcTransformMatrix( matLowerBody.m[3][0] + vUpperBodyLowerBodyOffset.x,
			matLowerBody.m[3][1] + vUpperBodyLowerBodyOffset.y,
			matLowerBody.m[3][2] + vUpperBodyLowerBodyOffset.z,
			fUpperBodyRot, fScaleX, fScaleY, fScaleZ, &matUpperBody );
	}


	///////// 2 保持上下身的朝向一至
	//{
	//	Vector	vUpperBodyLowerBodyOffset = m_vLowerBodyRootBonePos - m_vUpperBodyRootBonePos;
	//	matUpperBody.m[3][0] += vUpperBodyLowerBodyOffset.x;
	//	matUpperBody.m[3][1] += vUpperBodyLowerBodyOffset.y;
	//	matUpperBody.m[3][2] += vUpperBodyLowerBodyOffset.z;
	//}


	//D3DXMATRIX matTransform = GetBoneMatrices( m_nUpperBodyRootBoneID );
	//matUpperBody = *(MeMatrix*)&matTransform;

	//matUpperBody.m[3][0] = matLowerBody.m[3][0];
	//matUpperBody.m[3][1] = matLowerBody.m[3][1];
	//matUpperBody.m[3][2] = matLowerBody.m[3][2];

	bool		vecUpdateState[g_MaxBoneNum] = {false};
	assert(nBoneCount < g_MaxBoneNum);
	if (nBoneCount >= g_MaxBoneNum)
	{
		return;
	}
// 	std::vector<BOOL> vecUpdateState;
// 	vecUpdateState.reserve(nBoneCount);
// 	vecUpdateState.resize(nBoneCount);
// 	for(int i=0; i<vecUpdateState.size(); ++i )
// 		vecUpdateState[i] = FALSE;

	int iRootBone = m_nBipBoneID;
	if( iRootBone < 0 )
		iRootBone = 0;
	vecUpdateState[iRootBone] = UpdateBodyBone(iRootBone, vecUpdateState, &matUpperBody, &matLowerBody, fUpperBodyFactor, bUpperBodyBlending,
											fTargetUpperBodyFrame, fLowerBodyFactor, bLowerBodyBlending, fTargetLowerBodyFrame );

	for(int i=0; i<nBoneCount; ++i )
	{
		if( !vecUpdateState[i] )
			vecUpdateState[i] = UpdateBodyBone(i, vecUpdateState, &matUpperBody, &matLowerBody, fUpperBodyFactor, bUpperBodyBlending,
											fTargetUpperBodyFrame, fLowerBodyFactor, bLowerBodyBlending, fTargetLowerBodyFrame, FALSE);
	}


	//if( m_pAvatar )
	//	UpdateAvatar( HQ_TimeGetTime(), (float*)&matUpperBody, m_pAvatar );

	unguard;
}


BOOL MexAnimCtrl::UpdateBodyBone( int boneId,
								bool* vecUpdateState,
								const MeMatrix* pmatUpperBody,
								const MeMatrix* pmatLowerBody,
								float fUpperBodyFactor,
								BOOL bUpperBodyBlending,
								float fTargetUpperBodyFrame,
								float fLowerBodyFactor,
								BOOL bLowerBodyBlending,
								float fTargetLowerBodyFrame,
								BOOL bUpdateChild/* = TRUE*/ )
{
	if( boneId < 0 )
		return FALSE;

	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !pSkeleton->m_bSpecialModel);
	BOOL bInUpperBody = m_vectorBodyBoneFlag[boneId];
	IMexBone* pBone = m_pMex->GetSkeleton()->GetBone(boneId);
	float fBlendFactor = 0;

	if( bInUpperBody )
	{
		fBlendFactor = m_fCurUpperBodyFrame;
		if( bUpperBodyBlending && pBone->HasKeyFrame() )
		{
			float *pBlendMatrix = GetKeyFrameBlendedMatrices( pBone,
				fUpperBodyFactor,
				fBlendFactor,
				fTargetUpperBodyFrame,
				FRAMEPERSEC,
				m_bBodyLastBlend,
				&m_vctBlendTransQuats[boneId].kLastBlendTrans,
				&m_vctBlendTransQuats[boneId].kLastBlendQuats );

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBlendMatrix );
		}
		else
		{
			if( pBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧
			{
				BOOL bGetParentMat = FALSE;
				if( pBone->GetParentId() >= 0 )
					bGetParentMat = CanGetBoneMatricesBackupAtTime(fBlendFactor, pBone->GetParentId());

				float* pMatrix = NULL;
				if( bGetParentMat )
					pMatrix = pBone->GetMatricesFromKeyTime(fBlendFactor,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
				else
					pMatrix = pBone->GetMatricesFromKeyTime(fBlendFactor,FRAMEPERSEC);

				SetBoneMatricesAtTime(fBlendFactor, boneId, pMatrix);

				D3DXMatrixMultiply( 
					(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
					(D3DXMATRIX*)pBone->GetFrame0Inv(),
					(D3DXMATRIX*)pMatrix );
			}
			else
				D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(fBlendFactor,FRAMEPERSEC) );
		}
	}
	else
	{
		fBlendFactor = m_fCurLowerBodyFrame;
		if( bLowerBodyBlending && pBone->HasKeyFrame() )
		{
			float *pBlendMatrix = GetKeyFrameBlendedMatrices( pBone,
				fLowerBodyFactor,
				fBlendFactor,
				fTargetLowerBodyFrame,
				FRAMEPERSEC,
				m_bBodyLastBlend,
				&m_vctBlendTransQuats[boneId].kLastBlendTrans,
				&m_vctBlendTransQuats[boneId].kLastBlendQuats );

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBlendMatrix );
		}
		else
		{
			if( pBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧
			{
				BOOL bGetParentMat = FALSE;
				if( pBone->GetParentId() >= 0 )
					bGetParentMat = CanGetBoneMatricesBackupAtTime(fBlendFactor, pBone->GetParentId());

				float* pMatrix = NULL;
				if( bGetParentMat )
					pMatrix = pBone->GetMatricesFromKeyTime(fBlendFactor,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
				else
					pMatrix = pBone->GetMatricesFromKeyTime(fBlendFactor,FRAMEPERSEC);

				SetBoneMatricesAtTime(fBlendFactor, boneId, pMatrix);

				D3DXMatrixMultiply( 
					(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
					(D3DXMATRIX*)pBone->GetFrame0Inv(),
					(D3DXMATRIX*)pMatrix );
			}
			else
				D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(fBlendFactor,FRAMEPERSEC) );
		}
	}

	// 在模型空间中的变换
	//memcpy( &m_amatBoneInModelSpace[boneId], &m_amatBoneInWorldSpace[boneId], sizeof( MeMatrix ) );

	// 镜像
	//m_amatBoneInWorldSpace[i].m[0][0] *= -1;
	//m_amatBoneInWorldSpace[i].m[1][0] *= -1;
	//m_amatBoneInWorldSpace[i].m[2][0] *= -1;
	//m_amatBoneInWorldSpace[i].m[3][0] *= -1;

	if( bInUpperBody )
	{
		D3DXMatrixMultiply( 
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[boneId], 
			(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId],
			(D3DXMATRIX*)pmatUpperBody );
	}
	else
	{
		D3DXMatrixMultiply( 
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[boneId], 
			(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId],
			(D3DXMATRIX*)pmatLowerBody );
	}

	// 更新子骨骼
	if( pBone->GetChildCount() )
	{
		for( int i=0; i<pBone->GetChildCount(); ++i )
		{
			if( pBone->GetChildId(i) >= 0 && !vecUpdateState[pBone->GetChildId(i)] )
				vecUpdateState[pBone->GetChildId(i)] = UpdateBodyBone(pBone->GetChildId(i), vecUpdateState, pmatUpperBody, pmatLowerBody, fUpperBodyFactor,
												bUpperBodyBlending,	fTargetUpperBodyFrame, fLowerBodyFactor, bLowerBodyBlending, fTargetLowerBodyFrame);
		}
	}
	return TRUE;
}
void MexAnimCtrl::UpdateEffects( DWORD dwTime, float* pfBonesForEffect, float* pfMatrix )
{
	guardfunc;
	guard(ParticleEmitter);
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->Update( 
				dwTime,
				m_fScaleZ/*m_fScale*/,/*Config::m_fMdlSpaceScale,*/
				//(float*)m_amatBoneInModelSpace,
				(float*)pfBonesForEffect,
				(float*)pfMatrix ,m_nFrameId);
		}
	}
	unguard;

	{
		guard(RibbonEmitter);
		for(int i = 0; i < eMaxRibbonEmitter; i++ )
		{
			IMexRibbonEmitter* pEmitter = m_pRibbonEmitters[i];
			if( !pEmitter )
				continue;

			pEmitter->Update( dwTime, 
				m_nFrameId, 
				//(float*)m_amatBoneInModelSpace, 
				(float*)pfBonesForEffect,
				(float*)pfMatrix );

		}
		unguard;
	}
	unguard;
}
void MexAnimCtrl::UpdateAsComponent( DWORD dwTime, 
									 MexAnimCtrl* pBindAnim, 
									 int nBindBoneID,
									 float* pfHelperMatrixInit 
									 ,int nBoneIndex )
{
	if(nBindBoneID < 0)
		return;
	if( !m_pMex )
	{
		return;
	}

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();
	if( !pSkeleton )
		return;

	int nBoneCount = pSkeleton->GetBoneCount();
	
	int nFrameID = dwTime/ONEFRAMEINTERVAL;
	if( GetFrameCount() == 0 )
		nFrameID = 0;
	else
		nFrameID %= GetFrameCount();

	SetFrameID( nFrameID );
// 	m_pMex->SetFrameId( nFrameID );

	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel);
	for( int i = nBoneIndex; i < nBoneCount; i++ )
	{
		IMexBone* pBone = pSkeleton->GetBone(i);

		// 经过这段运算,模型已经在自己的空间中带有了动作,
		// 每个点都变换到模型空间中，
		if( pBone->HasKeyFrame() && bNewKeyFrameFormat )
		{
			float* pMatrix = NULL;
			if( pBone->GetParentId() >= 0 )
			{
				BOOL bGetParentMat = CanGetBoneMatricesBackupAtTime(nFrameID*ONEFRAMEINTERVAL, pBone->GetParentId());
				if( bGetParentMat )
					pMatrix = pBone->GetMatricesFromKeyTime(nFrameID*ONEFRAMEINTERVAL, FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
				else
					pMatrix = pBone->GetMatricesFromKeyTime(nFrameID*ONEFRAMEINTERVAL, FRAMEPERSEC);
				SetBoneMatricesAtTime(nFrameID*ONEFRAMEINTERVAL, i, pMatrix);
			}
			else
				pMatrix = pBone->GetMatricesFromKeyTime(nFrameID*ONEFRAMEINTERVAL, FRAMEPERSEC);

			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_matSrcBones[i], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pMatrix );
		}
		else
			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_matSrcBones[i], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatrices(nFrameID) );

// 		memcpy( &m_matSrcBones[i], &m_amatBoneInWorldSpace[i], sizeof(MeMatrix) );

		// 我们进入父模型空间中，
		// 接下来，我们需要把自己从原点变换到helper上，
		// 例如一把刀需要放到角色的手上去，
		D3DXMatrixMultiply(
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[i], 
			(D3DXMATRIX*)&m_matSrcBones[i],
			(D3DXMATRIX*)pfHelperMatrixInit );

		memcpy( &m_amatBoneInModelSpace[i], &m_amatBoneInWorldSpace[i], sizeof(MeMatrix) );
		// 放到父模型空间后,就和普通的模型一样转换
		D3DXMatrixMultiply(
			(D3DXMATRIX*)&m_amatBoneInModelSpace[i], 
			(D3DXMATRIX*)&m_amatBoneInModelSpace[i],
			(D3DXMATRIX*)&pBindAnim->m_amatBoneInModelSpace[nBindBoneID] );


		// 放到父模型空间后,就和普通的模型一样转换
		D3DXMatrixMultiply(
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[i], 
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[i],
			(D3DXMATRIX*)&pBindAnim->m_amatBoneInWorldSpace[nBindBoneID] );

	}

	D3DXMatrixMultiply( (D3DXMATRIX*)&m_matModel, 
		(D3DXMATRIX*)pfHelperMatrixInit, 
		(D3DXMATRIX*)&pBindAnim->m_amatBoneInWorldSpace[nBindBoneID] );

	//m_matModel = pBindAnim->m_matModel;
	//m_matModelInv = pBindAnim->m_matModelInv;
	UpdateEffects( dwTime, (float*)m_matSrcBones, (float*)&m_matModel );
}


bool MexAnimCtrl::UpdateComponents( DWORD dwTime, MeMatrix* pMatrix )
{
	guardfunc;

	if( !m_amatBoneInWorldSpace )
	{
		return false;
	}

	// pMatrix
	// 模型整体在世界空间中的变换
	if( !pMatrix )return false;
	if( !m_pMex )
	{
		//assert( false );
		return false;
	}
	
	SetTransform( (float*)pMatrix );

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();
	if( !pSkeleton )
		return false;

	int nBoneCount = pSkeleton->GetBoneCount();

	// 因为在调试期间出现异常，
	// 这里做一个保护措施
	int nFrameId = m_nFrameId;

	if( nFrameId < 0 )
	{
		assert( false && "frame id < 0 " );
		nFrameId = 0;
	}

	//m_pMex->SetFrameId( m_nFrameId );

	DWORD dwStart = dwTime;
	//if( m_nFrameId != m_nLastFrameID )
	SPlayTask* pTask = &m_PlayTasks[0];
	
	guard( UpperBodyAndLowerBodyMode );
	if( m_bUpperBodyAndLowerBodyMode )
	{
		//char szBuf[256];
		//_snprintf( szBuf, 256, "m_fUpperBody = %s %f %d m_fLowerBody = %s %f %d %f", m_pSeqUpperBody->m_spAnimName.GetString(), m_fUpperBodyFactor, m_bUpperBodyBlending, m_pSeqLowerBody->m_spAnimName.GetString(), m_fLowerBodyFactor,m_bLowerBodyBlending, m_fCurLowerBodyFrame );
		//OutputDebugString( szBuf );

		if( IsIdleSequence( m_pSeqLowerBody ) || IsComSequence( m_pSeqUpperBody ) || m_bPlayingWholeBodyAnim )
		{
			if( IsComSequence( m_pSeqUpperBody ) )
				m_bUpperBodyPlayingComAnim = TRUE;
			else
				m_bUpperBodyPlayingComAnim = FALSE;

			UpdateBody( m_vPosition.x, m_vPosition.y, m_vPosition.z,
				m_fScaleX, m_fScaleY, m_fScaleZ, m_fUpperBodyRot, m_fZRotTheta + m_fLowerBodyRot,
				m_pSeqUpperBody, m_fUpperBodyFactor, m_bUpperBodyBlending,
				m_pSeqUpperBody, m_fUpperBodyFactor, m_bUpperBodyBlending );
		}
		else
		{
			m_bUpperBodyPlayingComAnim = FALSE;

			UpdateBody( m_vPosition.x, m_vPosition.y, m_vPosition.z,
				m_fScaleX, m_fScaleY, m_fScaleZ, m_fUpperBodyRot, m_fZRotTheta + m_fLowerBodyRot,
				m_pSeqUpperBody, m_fUpperBodyFactor, m_bUpperBodyBlending,
				m_pSeqLowerBody, m_fLowerBodyFactor, m_bLowerBodyBlending );
		}
		if( m_pSeqLowerBody )
		{
			float fCurLowerBodyFrame = m_pSeqLowerBody->GetBlendFrame( m_fLowerBodyFactor );
			m_nFrameId = fCurLowerBodyFrame/ONEFRAMEINTERVAL;
// 			m_pMex->SetFrameId( m_nFrameId );
		}
	}
	else
	{
		bool		vecUpdateState[g_MaxBoneNum] = {false};
		assert(nBoneCount < g_MaxBoneNum);
		if (nBoneCount >= g_MaxBoneNum)
		{
			return false;
		}
// 		std::vector<BOOL> vecUpdateState;
// 		vecUpdateState.reserve(nBoneCount);
// 		vecUpdateState.resize(nBoneCount);
// 		for(int i=0; i<vecUpdateState.size(); ++i )
// 			vecUpdateState[i] = FALSE;

		int iRootBone = m_nBipBoneID;
		if( iRootBone < 0 )
			iRootBone = 0;
		vecUpdateState[iRootBone] = UpdateComponentBone(iRootBone, vecUpdateState, pMatrix);

		for(int i=0; i<nBoneCount; ++i )
		{
			if( !vecUpdateState[i] )
				vecUpdateState[i] = UpdateComponentBone(i, vecUpdateState, pMatrix, FALSE);
		}
	}

	guard(test1);
	//g_dwUpdateComponentsUsedTime += HQ_TimeGetTime()-dwStart;
	//g_dwUpdateComponentTimes++;

	static D3DXMATRIX smatModel( 1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);
	
	D3DXMATRIX matModel = smatModel;
	//D3DXMatrixIdentity( &matModel );

	//MirrorMatrix( 0, (MeMatrix*)&matModel );	

	// matModel的意义
	// 物体先左右镜像，
	// 然后变换到世界空间中
	D3DXMatrixMultiply( (D3DXMATRIX*)&matModel, 
		(D3DXMATRIX*)&matModel,
		(D3DXMATRIX*)pMatrix );

	//   added 2004.06.29
	m_matModel = *(MeMatrix*)&matModel;
	D3DXMatrixInverse( (D3DXMATRIX*)&m_matModelInv, NULL, (D3DXMATRIX*)&m_matModel );

	UpdateEffects( dwTime, (float*)m_amatBoneInModelSpace, (float*)&matModel );

	//guard(ParticleEmitter);
	//for( int i = 0; i < eMaxParticleEmitter; i++ )
	//{
	//	if( m_pParticleEmitters[i] )
	//	{
	//		m_pParticleEmitters[i]->Update( 
	//			dwTime, 
	//			m_fScale,
	//			(float*)m_amatBoneInModelSpace,
	//			(float*)&matModel );
	//	}
	//}
	//unguard;

	//{
	//	guard(RibbonEmitter);
	//	for(int i = 0; i < eMaxRibbonEmitter; i++ )
	//	{
	//		IMexRibbonEmitter* pEmitter = m_pRibbonEmitters[i];
	//		if( !pEmitter )
	//			continue;

	//		pEmitter->Update( dwTime, m_nFrameId, (float*)m_amatBoneInModelSpace, (float*)&matModel );

	//	}
	//	unguard;
	//}

// 	if( m_pAvatar )
// 		UpdateAvatar( dwTime, matModel, m_pAvatar );

	unguard;

	//for( int nEff = 0; nEff < )
	//for( int i = 0; i < eMaxLight; i++ )
	//{
	//	if( m_pLights[i] )
	//	{
	//		m_pLights[i]->Update(
	//			dwTime,
	//			(float*)m_amatBoneInModelSpace,
	//			(float*)&matModel );
	//	}
	//}

	m_bUpdateComponents = TRUE;

	return true;
}

BOOL MexAnimCtrl::UpdateComponentBone( int boneId, bool* vecUpdateState, MeMatrix* pMatrix, BOOL bUpdateChild/* = TRUE*/ )
{
	if( boneId < 0 )
		return FALSE;

	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !pSkeleton->m_bSpecialModel);

	// 首先通过pBones[i].matFrame0Inv，
	// 模型空间还原到骨骼空间，
	// 然后，通过pBones[i].pMatrices[nFrameId]
	// 变换到模型空间的当前帧

	if( !m_pSeqUpperBody )
		return FALSE;

	if( !m_bUpperBodyBlending )
	{
		m_fCurUpperBodyFrame = m_pSeqUpperBody->GetBlendFrame( m_fUpperBodyFactor );
	}

	float fTargetUpperBodyFrame = 0;

	m_nFrameId = m_fCurUpperBodyFrame/ONEFRAMEINTERVAL;
	if( m_bUpperBodyBlending )
	{
		fTargetUpperBodyFrame = m_pSeqUpperBody->GetBlendFrame( 0 );
		if( m_fUpperBodyFactor > 1 )
		{
			m_fUpperBodyFactor = 0;
		}
	}

	IMexBone* pBone = m_pMex->GetSkeleton()->GetBone(boneId);
	if( !pBone )
		return FALSE;
	SPlayTask* pTask = &m_PlayTasks[0];

	if( pTask->dwPlayMode == eBlendFrame &&	pBone->HasKeyFrame() )
	{
		if( !bNewKeyFrameFormat )	// 逐帧
		{
			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)GetKeyFrameBlendedMatrices( pBone,
				pTask->fBlendFactor,
				pTask->nBlendFrame0*ONEFRAMEINTERVAL,
				pTask->nBlendFrame1*ONEFRAMEINTERVAL,
				FRAMEPERSEC ) );
		}
		else	// 关键帧
		{
			float t = pTask->fBlendFactor;
			float T0 = pTask->nBlendFrame0*ONEFRAMEINTERVAL;
			float T1 = pTask->nBlendFrame1*ONEFRAMEINTERVAL;
			D3DXMATRIX* pBlendedMatrix = (D3DXMATRIX*)GetKeyFrameBlendedMatrices( pBone,
				t,
				T0,
				T1,
				FRAMEPERSEC );

			if( pBlendedMatrix )
			{
				D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], (D3DXMATRIX*)pBone->GetFrame0Inv(), pBlendedMatrix);
			}
		}
	}
	else
	{
		if( m_bUpperBodyBlending &&	pBone->HasKeyFrame() )
		{
			if( !bNewKeyFrameFormat )	// 逐帧
			{
				D3DXMATRIX* pBlendedMatrix = (D3DXMATRIX*)GetKeyFrameBlendedMatrices( pBone,
					m_fUpperBodyFactor, m_fCurUpperBodyFrame, fTargetUpperBodyFrame, FRAMEPERSEC );
				if( pBlendedMatrix )
					D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], (D3DXMATRIX*)pBone->GetFrame0Inv(), pBlendedMatrix );
			}
			else	// 关键帧
			{
				D3DXMATRIX* pBlendedMatrix = (D3DXMATRIX*)GetKeyFrameBlendedMatrices( pBone,
					m_fUpperBodyFactor, m_fCurUpperBodyFrame, fTargetUpperBodyFrame, FRAMEPERSEC );

				if( pBlendedMatrix )
				{
					D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], (D3DXMATRIX*)pBone->GetFrame0Inv(), pBlendedMatrix);
				}
			}
		}
		else
		{
			if( pBone->HasKeyFrame() )
			{
				if( !bNewKeyFrameFormat )	// 逐帧
				{
					D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
						(D3DXMATRIX*)pBone->GetFrame0Inv(),
						(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame,FRAMEPERSEC) );
				}
				else	// 关键帧
				{
					BOOL bGetParentMat = FALSE;
					if( pBone->GetParentId() >= 0 )
						bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurUpperBodyFrame, pBone->GetParentId());

					float* pMat = NULL;
					if( bGetParentMat )
						pMat = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
					else
						pMat = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame,FRAMEPERSEC);

					SetBoneMatricesAtTime(m_fCurUpperBodyFrame, boneId, pMat);

					D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
						(D3DXMATRIX*)pBone->GetFrame0Inv(),
						(D3DXMATRIX*)pMat);
				}
			}
			else
			{
				D3DXMatrixMultiply( (D3DXMATRIX*)&m_amatBoneInModelSpace[boneId], 
					(D3DXMATRIX*)pBone->GetFrame0Inv(),
					(D3DXMATRIX*)pBone->GetMatrices( m_nFrameId ) );
			}
		}
	}


	// 在模型空间中的变换
// 	memcpy( &m_amatBoneInModelSpace[boneId], &m_amatBoneInWorldSpace[boneId], sizeof( MeMatrix ) );

	// 镜像
	//m_amatBoneInWorldSpace[i].m[0][0] *= -1;
	//m_amatBoneInWorldSpace[i].m[1][0] *= -1;
	//m_amatBoneInWorldSpace[i].m[2][0] *= -1;
	//m_amatBoneInWorldSpace[i].m[3][0] *= -1;

	// 到世界中去
	D3DXMatrixMultiply( 
		(D3DXMATRIX*)&m_amatBoneInWorldSpace[boneId], 
		(D3DXMATRIX*)&m_amatBoneInModelSpace[boneId],
		(D3DXMATRIX*)pMatrix );

	// 更新子骨骼
	if( pBone->GetChildCount() )
	{
		for( int i=0; i<pBone->GetChildCount(); ++i )
		{
			if( pBone->GetChildId(i) >= 0 && !vecUpdateState[pBone->GetChildId(i)] )
				vecUpdateState[pBone->GetChildId(i)] = UpdateComponentBone(pBone->GetChildId(i), vecUpdateState, pMatrix);
		}
	}
	return TRUE;
}

void MexAnimCtrl::UpdateLocalBBox()
{
	guardfunc;
	if( !m_pMex )
		return;

	if( m_pMexCfg )
	{
		if( m_pMexCfg->m_BObj.m_npBBoxWidth.GetNumber() != 0 &&
			m_pMexCfg->m_BObj.m_npBBoxHeight.GetNumber() != 0 )
		{
			int nWidth = m_pMexCfg->m_BObj.m_npBBoxWidth.GetNumber();
			int nLength = m_pMexCfg->m_BObj.m_npBBoxLength.GetNumber();
			int nHeight = m_pMexCfg->m_BObj.m_npBBoxHeight.GetNumber();
			int nLift = m_pMexCfg->m_BObj.m_npBBoxLift.GetNumber();
			m_vMin = Vector( -nWidth/2, -nLength/2, nLift );
			m_vMax = Vector( nWidth/2, nLength/2, nLift+nHeight );
			return;
		}
	}
	m_vMin = *((Mex2*)m_pMex)->GetMin();
	m_vMax = *((Mex2*)m_pMex)->GetMax();
 	const float MAX_FLOAT = 10000.0f;

// 	if( m_pAvatar )
// 	{
// 		for( int nComponent = 0; nComponent < m_pAvatar->GetComponentCount(); nComponent++ )
// 		{
// 			CAvatar::Component* pComponent = m_pAvatar->GetComponent( nComponent );
// 			if( !pComponent )
// 				continue;
// 			for( int nChunk = 0; nChunk < pComponent->vectorChunk.size(); nChunk++ )
// 			{
// 				CMexChunkBase* pBase = (CMexChunkBase*)pComponent->vectorChunk[nChunk];
// 				m_vMin.x = min(m_vMin.x, pBase->GetMin()->x);
// 				m_vMin.y = min(m_vMin.y, pBase->GetMin()->y);
// 				m_vMin.z = min(m_vMin.z, pBase->GetMin()->z);
// 				m_vMax.x = max(m_vMax.x, pBase->GetMax()->x);
// 				m_vMax.y = max(m_vMax.y, pBase->GetMax()->y);
// 				m_vMax.z = max(m_vMax.z, pBase->GetMax()->z);
// // 				vectorChunk.push_back( pChunk );
// 			}
// 		}
// 	}

	if( m_vMin[0] == MAX_FLOAT )
		m_vMin[0] = 20.f;
	if( m_vMin[1] == MAX_FLOAT )
		m_vMin[1] = 20.f;
	if( m_vMin[2] == MAX_FLOAT )
		m_vMin[2] = 20.f;
	if( m_vMax[0] == -MAX_FLOAT )
		m_vMax[0] = -20.f;
	if( m_vMax[1] == -MAX_FLOAT )
		m_vMax[1] = -20.f;
	if( m_vMax[2] == -MAX_FLOAT )
		m_vMax[2] = -20.f;

	//if( m_bNeedLimitLocalBBox )
	//	LimitLocalBBox( 40, 100, 0, 0 );
	unguard;
}
void MexAnimCtrl::LimitLocalBBox( float fMinRadius, float fMaxRadius, float fMinHeight, float fMaxHeight )
{
	guardfunc;
	// 最小不能低于
	if( m_vMin.x > -fMinRadius )
		m_vMin.x = -fMinRadius;
	if( m_vMax.x < fMinRadius )
		m_vMax.x = fMinRadius;
	if( m_vMin.y > -fMinRadius )
		m_vMin.y = -fMinRadius;
	if( m_vMax.y < fMinRadius )
		m_vMax.y = fMinRadius;
	// 最大不能超过
	if( m_vMin.x < -fMaxRadius )
		m_vMin.x = -fMaxRadius;
	if( m_vMax.x > fMaxRadius )
		m_vMax.x = fMaxRadius;
	if( m_vMin.y < -fMaxRadius )
		m_vMin.y = -fMaxRadius;
	if( m_vMax.y > fMaxRadius )
		m_vMax.y = fMaxRadius;
	unguard;
}

void MexAnimCtrl::UpdateBillboardBBox()
{
	guardfunc;
	
	if( !m_bUpdatedBillboardBBox && m_HasBillboard && m_pMex &&
		m_pMex->GetGeometry() )
	{
// 		m_vWorldMin = Vector(10000.f, 10000.f, 10000.f);
// 		m_vWorldMax = Vector(-10000.f, -10000.f, -10000.f);
// 
// 		std::vector<IRenderable*> vectorChunk;
// 
// 		for( int i = 0; i < m_pMex->GetGeometry()->GetChunkCount(); i++ )
// 			vectorChunk.push_back( m_pMex->GetGeometry()->GetChunk(i) );
// 
// 		for( int i = 0; i < vectorChunk.size(); i++ )
// 		{
// 			Mex2GeoChunk* pChunk = (Mex2GeoChunk*)vectorChunk[i];
// 			Vector ChunkMin = Vector(10000.f, 10000.f, 10000.f);
// 			Vector ChunkMax = Vector(-10000.f, -10000.f, -10000.f);
// 
// 			if(pChunk->IsBillboard())
// 				((CBillboardGeoChunk*)pChunk)->UpdateBillboard();
// 
// 			for( int j = 0; j < pChunk->GetVertexCount(); j++ )
// 			{
// 				Vector v;
// 				if(pChunk->IsBillboard())// added, jiayi, [2009.4.20]
// 				{					
// 					v = *(Vector*)&(((CBillboardGeoChunk*)pChunk)->GetWorldBillboardVertices()[j]);					
// 				}
// 				else
// 					v = *(Vector*)&(pChunk->GetWorldVertices()[j]);	
// 
// 				ChunkMin.x = min(ChunkMin.x, v.x);
// 				ChunkMin.y = min(ChunkMin.y, v.y);
// 				ChunkMin.z = min(ChunkMin.z, v.z);
// 				ChunkMax.x = max(ChunkMax.x, v.x);
// 				ChunkMax.y = max(ChunkMax.y, v.y);
// 				ChunkMax.z = max(ChunkMax.z, v.z);
// 			}
// // 			pChunk->GetWorldBBox()->BuildAABB(ChunkMax, ChunkMin);
// 
// 			m_vWorldMin.x = min(m_vWorldMin.x, ChunkMin.x);
// 			m_vWorldMin.y = min(m_vWorldMin.y, ChunkMin.y);
// 			m_vWorldMin.z = min(m_vWorldMin.z, ChunkMin.z);
// 			m_vWorldMax.x = max(m_vWorldMax.x, ChunkMax.x);
// 			m_vWorldMax.y = max(m_vWorldMax.y, ChunkMax.y);
// 			m_vWorldMax.z = max(m_vWorldMax.z, ChunkMax.z);
// 		}
// 		m_worldBBox.BuildAABB(m_vWorldMax, m_vWorldMin);

 		for( int i = 0; i < m_pMex->GetGeometry()->GetChunkCount(); i++ )
		{
 			Mex2GeoChunk* pChunk = (Mex2GeoChunk*)m_pMex->GetGeometry()->GetChunk(i);
 			if(pChunk->IsBillboard())
 				((CBillboardGeoChunk*)pChunk)->UpdateBillboard((float*)&m_matModel);
		}

		((Mex2*)m_pMex)->GetLocalBBox()->Transform(m_matModel,m_worldBBox);
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&m_vWorldMax, 
			(D3DXVECTOR3*)((Mex2*)m_pMex)->GetMax(),	
			(D3DXMATRIX*)&m_matModel );
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&m_vWorldMin, 
			(D3DXVECTOR3*)((Mex2*)m_pMex)->GetMin(),	
			(D3DXMATRIX*)&m_matModel );

		m_vCenter = (m_vWorldMax + m_vWorldMin) * 0.5;
		m_fRadius = (m_vWorldMax - m_vWorldMin).length() * 0.5;
		SetUpdatedBillboardBBox( true );
	}	

	
	unguard;
 }
bool	MexAnimCtrl::UpdateWorldBBoxByChunk( MeMatrix* pMatrix ,IRenderable* pRenderable)
{
	Mex2GeoChunk* pChunk = (Mex2GeoChunk*)pRenderable;
	if(pChunk->IsFloor() || pChunk->IsCollision())
		return false;

	// added, jiayi, [2009.4.20]
	if(pChunk->IsBillboard())
		((CBillboardGeoChunk*)pChunk)->UpdateBillboard(NULL);

	Vector ChunkMin = Vector(10000.f, 10000.f, 10000.f);
	Vector ChunkMax = Vector(-10000.f, -10000.f, -10000.f);
	for( int j = 0; j < pChunk->GetVertexCount(); j++ )
	{
		Vector v;
		if(pChunk->IsBillboard())// added, jiayi, [2009.4.20]
		{					
			v = *(Vector*)&(((CBillboardGeoChunk*)pChunk)->GetWorldBillboardVertices()[j]);					
		}
		else
			v = *(Vector*)&(pChunk->GetWorldVertices()[j]);

		ChunkMin.x = min(ChunkMin.x, v.x);
		ChunkMin.y = min(ChunkMin.y, v.y);
		ChunkMin.z = min(ChunkMin.z, v.z);
		ChunkMax.x = max(ChunkMax.x, v.x);
		ChunkMax.y = max(ChunkMax.y, v.y);
		ChunkMax.z = max(ChunkMax.z, v.z);
	}
	// 			pChunk->GetWorldBBox()->BuildAABB(ChunkMax, ChunkMin);

	m_vWorldMin.x = min(m_vWorldMin.x, ChunkMin.x);
	m_vWorldMin.y = min(m_vWorldMin.y, ChunkMin.y);
	m_vWorldMin.z = min(m_vWorldMin.z, ChunkMin.z);
	m_vWorldMax.x = max(m_vWorldMax.x, ChunkMax.x);
	m_vWorldMax.y = max(m_vWorldMax.y, ChunkMax.y);
	m_vWorldMax.z = max(m_vWorldMax.z, ChunkMax.z);
	return true;
}

void MexAnimCtrl::BuildWorldBBox()
{
	m_worldBBox.BuildAABB(m_vWorldMax, m_vWorldMin);
	m_vCenter = (m_vWorldMax + m_vWorldMin) * 0.5;
	m_fRadius = (m_vWorldMax - m_vWorldMin).length() * 0.5;
}

void MexAnimCtrl::UpdateWorldBBox( MeMatrix* pMatrix )
{
	guardfunc;


	m_vWorldMin = Vector(10000.f, 10000.f, 10000.f);
	m_vWorldMax = Vector(-10000.f, -10000.f, -10000.f);
	if( !IsAni() && m_pMex &&
		m_pMex->GetGeometry() )
	{

// 		D3DXVECTOR3 vMax,vMin;
// 		D3DXVec3TransformCoord( &vMax, 
// 			(D3DXVECTOR3*)&GetMax(),	
// 			(D3DXMATRIX*)pMatrix );
// 		D3DXVec3TransformCoord( &vMin, 
// 			(D3DXVECTOR3*)&GetMin(),	
// 			(D3DXMATRIX*)pMatrix );
// 
// 		m_vWorldMax.x = max(vMax.x,vMin.x);
// 		m_vWorldMax.y = max(vMax.y,vMin.y);
// 		m_vWorldMax.z = max(vMax.z,vMin.z);
// 		m_vWorldMin.x = min(vMax.x,vMin.x);
// 		m_vWorldMin.y = min(vMax.y,vMin.y);
// 		m_vWorldMin.z = min(vMax.z,vMin.z);
// 		m_worldBBox.BuildAABB(m_vWorldMax, m_vWorldMin);
		((Mex2*)m_pMex)->GetLocalBBox()->Transform(*pMatrix,m_worldBBox);
	}
	else
	{
		float fMexScale = 1.0f;
		Vector vMin = m_vMin*fMexScale;
		Vector vMax = m_vMax*fMexScale;

		/*deleted by zhuomeng.hu		[8/17/2010]
		float t = vMax.x;
		vMax.x = -vMin.x;
		vMin.x = -t;	*/

		m_worldBBox.Build(*pMatrix,vMax, vMin);

	}

	for(int i=0; i<8; i++)
	{
		m_vWorldMin.x = min(m_vWorldMin.x, m_worldBBox.v[i].x);
		m_vWorldMin.y = min(m_vWorldMin.y, m_worldBBox.v[i].y);
		m_vWorldMin.z = min(m_vWorldMin.z, m_worldBBox.v[i].z);
		m_vWorldMax.x = max(m_vWorldMax.x, m_worldBBox.v[i].x);
		m_vWorldMax.y = max(m_vWorldMax.y, m_worldBBox.v[i].y);
		m_vWorldMax.z = max(m_vWorldMax.z, m_worldBBox.v[i].z);
	}

	m_vCenter = (m_vWorldMax + m_vWorldMin) * 0.5;
	m_fRadius = (m_vWorldMax - m_vWorldMin).length() * 0.5;
	unguard;
}

MexAnimCtrl::SPlayTask* MexAnimCtrl::GetPlayTask( int nTask )
{
	guardfunc;
	if( nTask < 0 || nTask >= eMaxPlayTask )
	{
		assert( false );
		return NULL;
	}
	return &m_PlayTasks[nTask];
	unguard;
}

BOOL MexAnimCtrl::Update( DWORD dwTime, MeMatrix* pMatrix, BOOL bUpdateComponent )
{
	guardfunc;
	BOOL bChangeAnim = FALSE;

	if( m_bUpperBodyAndLowerBodyMode )
	{
		DWORD dwStart = HQ_TimeGetTime();
		BOOL bFinish = FALSE;

		if( m_nNumLowerBodyPlayTask > 0 )
		{
			if( m_bLowerBodyBlending )
			{
				DWORD dwBlendingTime = dwStart - m_dwLowerBodyStartBlendingTime;
				if( dwBlendingTime > m_dwLowerBodyBlendingStep )
				{
					m_bLowerBodyBlending = FALSE;
					CheckWeaponDisplay();
				}
				else
				{
					m_fLowerBodyFactor = (float)dwBlendingTime/m_dwLowerBodyBlendingStep;
				}
			}

			if( !m_bLowerBodyBlending )
			{
				SPlayTask* pTask = &m_LowerBodyPlayTask[0];

				switch( pTask->dwPlayMode )
				{
				case eHoldOnFirstFrame:
					m_fLowerBodyFactor = 0;
					break;
				case eHoldOnLastFrame:
					m_fLowerBodyFactor = 1;
					break;
				case eSingleFrame:
					break;
				case eBlendFrame:
					break;
				case eNormalPlay:
					{
						int nLoopTimes = m_LowerBodyAnimTimeLine.GetNumLooped( dwTime );
						DWORD dwStartTime = m_LowerBodyAnimTimeLine.GetStartTime();
						if ( dwTime < dwStartTime )
						{
							nLoopTimes = 0;
						}

						if( dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
							bFinish = TRUE;

						if( dwTime > dwStartTime &&	dwTime-dwStartTime >= pTask->dwTimeOut )
							bFinish = TRUE;

						if( m_LowerBodyAnimTimeLine.IsLoopPlaying() )
						{
							m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
						}
						else
						{
							m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
							//m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetCurPlayPercent( dwTime );
						}
						//char szBuf[256];
						//_snprintf( szBuf, 256, "UpperBodyFactor = %f LowerBodyFactor = %f", m_fUpperBodyFactor, m_fLowerBodyFactor );
						//OutputDebugString( szBuf );
					}
					break;
				}

				if( bFinish && m_nNumLowerBodyPlayTask > 1 )
				{
					assert( m_nNumLowerBodyPlayTask >= 2 && "task count must >=2" );

					memcpy( &m_LowerBodyPlayTask[0], &m_LowerBodyPlayTask[1], sizeof(SPlayTask) );

					m_nNumLowerBodyPlayTask--;

					assert( m_nNumLowerBodyPlayTask > 0 && "next task is null" );

					pTask = &m_LowerBodyPlayTask[0];

				//	assert( pTask->dwTimeOut > 2000 && "second task timeout too small" );
					// 动画切换
					bChangeAnim = PlayAnim( pTask );

					switch( pTask->dwPlayMode )
					{
					case eHoldOnFirstFrame:
						m_fLowerBodyFactor = 0;
						break;
					case eHoldOnLastFrame:
						m_fLowerBodyFactor = 1;
						break;
					}
				}
			}
		}

		if( m_bUpperBodyPlayOver )
		{
			m_bUpperBodyBlending = m_bLowerBodyBlending;
			m_pSeqUpperBody = m_pSeqLowerBody;
			m_fUpperBodyFactor = m_fLowerBodyFactor;
		}
		else
		{
			bFinish = FALSE;

			if( m_nNumUpperBodyPlayTask > 0 )
			{
				if( m_bUpperBodyBlending )
				{
					DWORD dwBlendingTime = dwStart - m_dwUpperBodyStartBlendingTime;
					if( dwBlendingTime > m_dwUpperBodyBlendingStep )
					{
						m_bUpperBodyBlending = FALSE;
						CheckWeaponDisplay();
					}
					else
					{
						m_fUpperBodyFactor = (float)dwBlendingTime/m_dwUpperBodyBlendingStep;
					}
				}

				if( !m_bUpperBodyBlending )
				{
					SPlayTask* pTask = &m_UpperBodyPlayTask[0];

					switch( pTask->dwPlayMode )
					{
					case eHoldOnFirstFrame:
						m_fUpperBodyFactor = 0;
						break;
					case eHoldOnLastFrame:
						m_fUpperBodyFactor = 1;
						break;
					case eSingleFrame:
						break;
					case eBlendFrame:
						break;
					case eNormalPlay:
						{
							int nLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( dwTime );
							DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
							if ( dwTime < dwStartTime )
							{
								nLoopTimes = 0;
							}

							if( !m_bUpperBodyPlayOver && dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
							{
								m_bUpperBodyPlayOver = TRUE;
								m_bPlayingWholeBodyAnim = FALSE;
							}

							if( !m_bUpperBodyPlayOver && dwTime > dwStartTime && dwTime-dwStartTime >= pTask->dwTimeOut )
							{
								m_bUpperBodyPlayOver = TRUE;
								m_bPlayingWholeBodyAnim = FALSE;
							}

							if( m_UpperBodyAnimTimeLine.IsLoopPlaying() )
							{
								m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
							}
							else
							{
								m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetCurPlayPercent( dwTime );
							}

							//char szBuf[256];
							//_snprintf( szBuf, 256, "m_fUpperBodyFactor=%f",m_fUpperBodyFactor );
							//GetErrorLog()->logString( szBuf );

							//if( m_fUpperBodyFactor > 1 )
							//{
							//	m_pSeqUpperBody = m_pSeqLowerBody;
							//	m_fUpperBodyFactor = m_fLowerBodyFactor;
							//}
						}
						break;
					}
				}
			}

			if( m_bUpperBodyPlayOver )
			{
				if( m_bCanBlending )
				{
					m_bUpperBodyBackBlending = TRUE;
					m_dwUpperBodyStartBackBlendingTime = HQ_TimeGetTime();
				}

				if( IsIdleSequence( m_pSeqLowerBody ) )
				{
					if( m_bCanBlending )
					{
						m_bLowerBodyBackBlending = TRUE;
						m_dwLowerBodyStartBackBlendingTime = HQ_TimeGetTime();
					}
				}

				m_bUpperBodyBlending = m_bLowerBodyBlending;
				m_pSeqUpperBody = m_pSeqLowerBody;
				m_fUpperBodyFactor = m_fLowerBodyFactor;
			}
		}
	}
	else
	{
		DWORD dwStart = HQ_TimeGetTime();

		BOOL bFinish = FALSE;

		if( m_nNumPlayTask == 0 )
		{
			return bChangeAnim;
		}

		if( m_bUpperBodyBlending )
		{
			DWORD dwBlendingTime = dwStart - m_dwUpperBodyStartBlendingTime;
			if( dwBlendingTime > m_dwUpperBodyBlendingStep )
			{
				m_bUpperBodyBlending = FALSE;
			}
			else
			{
				m_fUpperBodyFactor = (float)dwBlendingTime/m_dwUpperBodyBlendingStep;
			}
		}

		if( !m_bUpperBodyBlending )
		{
			SPlayTask* pTask = &m_PlayTasks[0];
			switch( pTask->dwPlayMode )
			{
			case eHoldOnFirstFrame:
				m_fUpperBodyFactor = 0;
				break;
			case eHoldOnLastFrame:
				m_fUpperBodyFactor = 1;
				break;
			case eSingleFrame:
				break;
			case eBlendFrame:
				break;
			case eNormalPlay:
				{
					int nLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( dwTime );
					DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
					if ( dwTime < dwStartTime )
					{
						nLoopTimes = 0;
					}

					if( dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
					{
						bFinish = TRUE;
					}

					if( dwTime > dwStartTime && dwTime-dwStartTime >= pTask->dwTimeOut )
					{
						bFinish = TRUE;
					}

					if( m_UpperBodyAnimTimeLine.IsLoopPlaying() )
					{
						m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
					}
					else
					{
						m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetCurPlayPercent( dwTime );
					}
				}
				break;
			}

			// 
			if( bFinish && m_nNumPlayTask > 1 )
			{
				assert( m_nNumPlayTask >= 2 && "task count must >=2" );
				//m_vectorPlayTask.erase( m_vectorPlayTask.begin() );
				memcpy( &m_PlayTasks[0], &m_PlayTasks[1], (m_nNumPlayTask-1)*sizeof(SPlayTask) );
				m_nNumPlayTask--;

				//OnNextPlayTask();
				//assert( m_vectorPlayTask.size() > 0 && "next task is null" );
				assert( m_nNumPlayTask > 0 && "next task is null" );

				//pTask = &m_vectorPlayTask[0];
				pTask = &m_PlayTasks[0];

				assert( pTask->dwTimeOut > 2000 && "second task timeout too small" );
				bChangeAnim = PlayAnim( pTask );
				switch( pTask->dwPlayMode )
				{
				case eHoldOnFirstFrame:
					m_fUpperBodyFactor = 0;
					break;
				case eHoldOnLastFrame:
					m_fUpperBodyFactor = 1;
					break;
				}
			}
		}
	}
	SetBindingBowString(false);
	if (m_bNeedCheckBindingBowString )
	{
		if (m_nNumPlayTask > 0)
		{
			SPlayTask* pTask = &m_PlayTasks[0];
			MexCfgSequence*  pSequence = m_pMexCfg->GetSequence( pTask->szActionname );
			if (pSequence && pSequence->m_npStartFrameId.GetNumber() > m_pMexCfg->GetFrameOffset())
			{
				int totalFrame = pSequence->m_npEndFrameId.GetNumber() - pSequence->m_npStartFrameId.GetNumber() + 1;
				int oneFrameInterVal = (DWORD)ONEFRAMEINTERVAL;
				if (pTask->bLoopPlay || (dwTime - pTask->dwStartTime < pTask->dwOneLoopTime))
				{
					int nFrame = pSequence->m_npStartFrameId.GetNumber() + ((dwTime - pTask->dwStartTime)%(oneFrameInterVal*totalFrame))/oneFrameInterVal - m_pMexCfg->GetFrameOffset();
					bool flag = CBowStringBindingMgr::Instance()->IsNeedBinding(weaponModelId,nFrame);
					SetBindingBowString(flag);
					// 				if (flag)
					// 				{
					// 					TCHAR buffer[256];
					// 					wsprintf( buffer, _T("\n%s ActionBegin:%d Frame:%d Binding:%d "), pTask->szActionname,pSequence->m_npStartFrameId.GetNumber()- m_pMexCfg->GetFrameOffset(),nFrame,flag );
					// 					OutputDebugString(buffer);
					// 				}
				}
			}
		}
		if (!GetBindingBowString() && m_nNumUpperBodyPlayTask > 0)
		{
			SPlayTask* pTask = &m_UpperBodyPlayTask[0];
			MexCfgSequence*  pSequence = m_pMexCfg->GetSequence( pTask->szActionname );
			if (pSequence && pSequence->m_npStartFrameId.GetNumber() > m_pMexCfg->GetFrameOffset())
			{
				int totalFrame = pSequence->m_npEndFrameId.GetNumber() - pSequence->m_npStartFrameId.GetNumber() + 1;
				int oneFrameInterVal = (DWORD)ONEFRAMEINTERVAL;
				if (pTask->bLoopPlay || (dwTime - pTask->dwStartTime < pTask->dwOneLoopTime))
				{
					int nFrame = pSequence->m_npStartFrameId.GetNumber() + ((dwTime - pTask->dwStartTime)%(oneFrameInterVal*totalFrame))/oneFrameInterVal - m_pMexCfg->GetFrameOffset();
					bool flag = CBowStringBindingMgr::Instance()->IsNeedBinding(weaponModelId,nFrame);
					SetBindingBowString(flag);
					// 				if (flag)
					// 				{
					// 					TCHAR buffer[256];
					// 					wsprintf( buffer, _T("\n%s ActionBegin:%d Frame:%d Binding:%d "), pTask->szActionname,pSequence->m_npStartFrameId.GetNumber()- m_pMexCfg->GetFrameOffset(),nFrame,flag );
					// 					OutputDebugString(buffer);
					// 				}
				}
			}
		}
		if (!GetBindingBowString() && m_nNumLowerBodyPlayTask > 0)
		{
			SPlayTask* pTask = &m_LowerBodyPlayTask[0];
			MexCfgSequence*  pSequence = m_pMexCfg->GetSequence( pTask->szActionname );
			if (pSequence && pSequence->m_npStartFrameId.GetNumber() > m_pMexCfg->GetFrameOffset())
			{
				int totalFrame = pSequence->m_npEndFrameId.GetNumber() - pSequence->m_npStartFrameId.GetNumber() + 1;
				int oneFrameInterVal = (DWORD)ONEFRAMEINTERVAL;
				if (pTask->bLoopPlay || (dwTime - pTask->dwStartTime < pTask->dwOneLoopTime))
				{
					int nFrame = pSequence->m_npStartFrameId.GetNumber() + ((dwTime - pTask->dwStartTime)%(oneFrameInterVal*totalFrame))/oneFrameInterVal - m_pMexCfg->GetFrameOffset();
					bool flag = CBowStringBindingMgr::Instance()->IsNeedBinding(weaponModelId,nFrame);
					SetBindingBowString(flag);
					// 				if (flag)
					// 				{
					// 					TCHAR buffer[256];
					// 					wsprintf( buffer, _T("\n%s ActionBegin:%d Frame:%d Binding:%d "), pTask->szActionname,pSequence->m_npStartFrameId.GetNumber()- m_pMexCfg->GetFrameOffset(),nFrame,flag );
					// 					OutputDebugString(buffer);
					// 				}
				}
			}
		}
	}

	UpdateWorldBBox( pMatrix );

	//if( !m_bUpdateComponents || rand()%100 == 0 )
	//if( !m_bUpdateComponents )
	{
		if( bUpdateComponent )
			UpdateComponents( dwTime, pMatrix );
	}

    //
    // update children
    //
    updateChildren( dwTime, pMatrix );

	return bChangeAnim;
	unguard;
}
void MexAnimCtrl::RenderWithShader( float fTransparent )
{
	// 设置vs常量，全局透明度
	// 如果有纸娃娃，渲染纸娃娃
	// vs渲染在这里不用flush，除非是透明网格
	// 渲染特效部分
}

BOOL MexAnimCtrl::Render( float fTransparent, LayerDataContainer* pMeshContainer,
						 int* pVertexCount, int* pFaceCount, int* pSubmodelCount,
						 BOOL bIsHairHelmetAlphaTest, BOOL bRenderShadow,
						 BOOL bRenderParticleEmitters, BOOL bOverUI, BOOL bRenderDecal )
{
	guardfunc;
    BOOL bRet = FALSE;
	if ( m_bIsTerrainModel )
	{
		m_bRenderRibbon = true;
	}

	if ( m_pMex == NULL )
		return bRet;

    guard( test.1 )
	IRenderer *pRenderer = GetEngine()->GetRenderer();
	if( pRenderer == NULL )
	{
		assert( false );
		return bRet;
	}
    unguard

    guard( test.2 )
	pRenderer->SetGlobalTransparent( fTransparent );
	pRenderer->SetGlobalDiffuse( 1, 1, 1 );
	pRenderer->SetGlobalUOffset( 0, 0.0f );
	pRenderer->SetGlobalVOffset( 0, 0.0f );
	pRenderer->SetGlobalUOffset( 1, 0.0f );
	pRenderer->SetGlobalVOffset( 1, 0.0f );
    unguard

    guard( test.3 )
	// 纸娃娃的渲染逻辑已分离到Client中
    unguard

    guard( test.4 )
	if ( m_pMex->GetGeometry() != NULL )
	{
		int nChunkCount = m_pMex->GetGeometry()->GetChunkCount();
		if ( m_bRenderFirstPart )
		{
			nChunkCount = 1;
		}

		DWORD dwFlag = m_dwRenderFlag;
		for ( int i = PartOffset; i < nChunkCount; i++ )
		{
			LayerData* pLayerData = 0;
			if ( pMeshContainer != NULL)
			{
				if ( pMeshContainer->find( i ) != pMeshContainer->end() )
					pLayerData = (*pMeshContainer)[i];
			}

			if ( !bRenderDecal )
			{
				IRenderable *ren = m_pMex->GetGeometry()->GetChunk(i);
				if ( ren != NULL && strnicmp(ren->GetName(), "decal.", 6 ) == 0 )
					continue;
			}
			
			int vertex_count = 0;
			int face_count = 0;
			BOOL bRendered;
			bRendered = RenderSubset( i, fTransparent, pLayerData, &vertex_count, &face_count, dwFlag,  bRenderShadow );

			if ( pSubmodelCount && bRendered )
				(*pSubmodelCount)++;
			if ( pVertexCount )
				*pVertexCount += vertex_count;
			if ( pFaceCount )
				*pFaceCount += face_count;
            bRet |= bRendered;
		} 
	}
    unguard

    guard( tset.5 )
    unguard

    guard( tset.6 )
	if ( m_bRenderRibbon && m_pRibbonEmitters )
	{
		for ( int i = 0; i < eMaxRibbonEmitter; i++ )
		{
			if ( m_pRibbonEmitters[i] )
			{
				BOOL bUseLightTrack = FALSE;

				if ( m_pSeqUpperBody )
					bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();

				DWORD dwCurTime = HQ_TimeGetTime();

				if ( bUseLightTrack )
				{
					m_dwLightTrackDeadTime = dwCurTime;
				}

				if ( bUseLightTrack || dwCurTime - m_dwLightTrackDeadTime < LIGHTTRACKDEADRENDERTIME )
				{
					float fAlpha = (float)( LIGHTTRACKDEADRENDERTIME - ( dwCurTime - m_dwLightTrackDeadTime ) )/LIGHTTRACKDEADRENDERTIME;
					if ( m_fLightTrackAlpha < fAlpha )
					{
						m_fLightTrackAlpha += 0.03f ;
					}
					else
					{
						m_fLightTrackAlpha = fAlpha;
					}

					int nLocalTextureId = m_pRibbonEmitters[i]->GetLocalTextureID();
					int nTextureId = m_ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
					m_pRibbonEmitters[i]->Render( NULL, nTextureId, fTransparent*m_fLightTrackAlpha, FALSE, false );
				}
			}
		}
	}
    unguard

    guard( tset.7 )
	if ( m_pParticleEmitters && !bRenderShadow && bRenderParticleEmitters)
	{
		for ( int i = 0; i < eMaxParticleEmitter; i++ )
		{
			if ( m_pParticleEmitters[i] )
			{
				int nLocalTextureId = m_pParticleEmitters[i]->GetLocalTextureID();
				int nTextureId = m_ReplaceableTextureProj.GetRenderTextureID( nLocalTextureId );
				m_pParticleEmitters[i]->Render( HQ_TimeGetTime(), nTextureId, fTransparent, bOverUI );
			}
		}
	}
    unguard

    // render children
    guard( tset.8 )
    unguard

	pRenderer = NULL;

	m_bRenderRibbon = false;

    return bRet;
	unguard;
}

// void MexAnimCtrl::FastRender( float fTransparent )
// {
// 	guardfunc;
// 	if( !m_pMex )
// 		return;
// 
// 	IRenderer* pRenderer = GetEngine()->GetRenderer();
// 
// 	if( !pRenderer )
// 	{
// 		return;
// 	}
// 
// 	pRenderer->SetGlobalTransparent( fTransparent );
// 	pRenderer->SetGlobalDiffuse( 1, 1, 1 );
// 	pRenderer->SetGlobalUOffset( 0, 0.0f );
// 	pRenderer->SetGlobalVOffset( 0, 0.0f );
// 	pRenderer->SetGlobalUOffset( 1, 0.0f );
// 	pRenderer->SetGlobalVOffset( 1, 0.0f );
// 
// 	//纸娃娃的Render
// 	if( m_pAvatar )
// 	{
// 		FastRenderAvatar( m_pAvatar, pRenderer, fTransparent );
// 		//RenderAvatar( m_pAvatar, pRenderer, fTransparent );
// 	}
// 
// 	//物件的Render
// 	if( m_pMex->GetGeometry() )
// 	{
// 		int nChunkCount = m_pMex->GetGeometry()->GetChunkCount();
// 
// 		if( m_bRenderFirstPart )
// 		{
// 			nChunkCount = 1;
// 		}
// 
// 		for( int i = PartOffset; i < nChunkCount; i++ )
// 		{
// 			//RenderSubset( i, pRenderer, fTransparent );
// 			FastRenderSubset( i, pRenderer, fTransparent );
// 		} 
// 	}
// 
// 	pRenderer->Flush( m_dwRenderFlag );
// 
// 	//TODO::
// 	//if( m_pRibbonEmitters )
// 	//{
// 	//	for( int i = 0; i < eMaxRibbonEmitter; i++ )
// 	//	{
// 	//		if( m_pRibbonEmitters[i] )
// 	//		{
// 	//			BOOL bUseLightTrack = FALSE;
// 
// 	//			if( m_pSeqUpperBody )
// 	//				bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();
// 
// 	//			DWORD dwCurTime = HQ_TimeGetTime();
// 
// 	//			if( bUseLightTrack )
// 	//			{
// 	//				m_dwLightTrackDeadTime = dwCurTime;
// 	//			}
// 
// 	//			if( bUseLightTrack || dwCurTime - m_dwLightTrackDeadTime < LIGHTTRACKDEADRENDERTIME )
// 	//			{
// 	//				float fAlpha = (float)( LIGHTTRACKDEADRENDERTIME - ( dwCurTime - m_dwLightTrackDeadTime ) )/LIGHTTRACKDEADRENDERTIME;
// 	//				if( m_fLightTrackAlpha < fAlpha )
// 	//				{
// 	//					m_fLightTrackAlpha += 0.03f ;
// 	//				}
// 	//				else
// 	//				{
// 	//					m_fLightTrackAlpha = fAlpha;
// 	//				}
// 
// 	//				int nLocalTextureId = m_pRibbonEmitters[i]->GetLocalTextureID();
// 	//				int nTextureId = m_ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
// 	//				m_pRibbonEmitters[i]->Render( NULL, nTextureId, fTransparent*m_fLightTrackAlpha, FALSE, false );
// 	//			}
// 	//		}
// 	//	}
// 	//}
// 
// 	//if( m_pParticleEmitters )
// 	//{
// 	//	for( int i = 0; i < eMaxParticleEmitter; i++ )
// 	//	{
// 	//		if( m_pParticleEmitters[i] )
// 	//		{
// 	//			int nLocalTextureId = m_pParticleEmitters[i]->GetLocalTextureID();
// 	//			int nTextureId = m_ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
// 	//			m_pParticleEmitters[i]->Render( HQ_TimeGetTime(), nTextureId, fTransparent, false );
// 	//		}
// 	//	}
// 	//}
// 
// 	pRenderer = NULL;
// 	unguard;
// }
// 

void MexAnimCtrl::RenderShadow( void )
{
	guardfunc;
	//TRUETIMEFUNC();
	if( !m_pMex )
		return;

	IRenderer* pRenderer = GetEngine()->GetRenderer();
	if( !pRenderer )
	{
		assert( false );
		return;
	}

	//纸娃娃的Render
// 	if( m_pAvatar )
// 	{
// 		RenderAvatarShadow( m_pAvatar, pRenderer );
// 	}

	//物件的Render
	if( m_pMex->GetGeometry() )
	{
		int nChunkCount = m_pMex->GetGeometry()->GetChunkCount();
		for( int i = 0; i < nChunkCount; i++ )
		{
			RenderSubsetShadow( i, pRenderer );
		} 
	}

// 	pRenderer->Flush( m_dwRenderFlag );
// 	pRenderer->FlushShadow( eSortByFarZ );

	pRenderer = NULL;
	unguard;
}

void MexAnimCtrl::Render2( MtlAnim* pMtlAnim )
{
	guardfunc;
	unguard;
}

BOOL MexAnimCtrl::CloseAvatarSetting( MexCfgAvatarSetting* pSetting )
{
	guardfunc;
	if( !pSetting )
	{
		assert( false );
		return FALSE;
	}
	if( m_ReplaceableTextureProj.IsLoaded() )
	{
		m_ReplaceableTextureProj.UnRegisterTextures();
		m_ReplaceableTextureProj.Loaded( FALSE );
	}

	if (m_LuminanceTextureProj.IsLoaded())
	{
		m_LuminanceTextureProj.UnRegisterTextures();
		m_LuminanceTextureProj.Loaded( FALSE );
	}

	return TRUE;
	unguard;
}
BOOL GNeedMult = FALSE;
BOOL MexAnimCtrl::ChangeAvatarSetting( const char* pszName )
{
	guardfunc;
	guard( test1 );
	if( !pszName )
	{
		assert( false );
		return FALSE;
	}

	if( !m_pMexCfg )
	{
		return FALSE;
	}

	if( m_pAvatarSetting )
	{
		CloseAvatarSetting( m_pAvatarSetting );
		m_pAvatarSetting = NULL;
	}
	unguard;

	guard( test2 )
	m_pAvatarSetting = m_pMexCfg->m_AvatarSettings.FindByName( pszName );

	if( !m_pAvatarSetting )
		return FALSE;
	unguard;
	
	//本身物件注册已经在Load线程里面了
	bool bMult = FALSE;
	guard( test3 );
// 	std::string szCmp = m_pMex->GetFilename();

	if( GNeedMult )
	{
		bMult = TRUE;
	}
	unguard;

	guard( test4 );
	m_ReplaceableTextureProj.SetTextureCount( m_pAvatarSetting->m_vectorReplaceableTexture.size() );
	m_LuminanceTextureProj.SetTextureCount( m_pAvatarSetting->m_vectorReplaceableTexture.size() );
	for( int nTexture = 0; nTexture < m_pAvatarSetting->m_vectorReplaceableTexture.size(); nTexture++ )
	{
		MexCfgAvatarSetting::ReplaceableTexture* rt =
			&m_pAvatarSetting->m_vectorReplaceableTexture[nTexture];

		int nRenderTextureID = 
			m_ReplaceableTextureProj.RegisterTexture( 
										m_pMex->GetFilename(), 
										rt->szFileName, bMult );
		m_ReplaceableTextureProj.SetRenderTextureID( nTexture, nRenderTextureID );

		if (strstr(m_pMex->GetFilename(),"avatar") || strstr(m_pMex->GetFilename(),"character") )
		{//避免大量的加载失败
			CFilePath path;
			path.Split( rt->szFileName );
			std::string strTemp( path.GetDirectory() );
			strTemp = strTemp + path.GetFileName() + "-lum.png";
			int nLuminanceTextureID = 
				m_LuminanceTextureProj.RegisterTexture( 
				m_pMex->GetFilename(), 
				strTemp.c_str(), bMult );
			m_LuminanceTextureProj.SetRenderTextureID( nTexture, nLuminanceTextureID );
		}
	}
	m_ReplaceableTextureProj.Loaded( TRUE );
	m_LuminanceTextureProj.Loaded( TRUE );
	return TRUE;
	unguard;
	unguard;
}

BOOL MexAnimCtrl::RenderSubset( int nSubset, float fAlpha, LayerData* pLayerData/* = NULL*/, int* pVertexCount/* =NULL */, int* pFaceCount/* =NULL */,
                               DWORD dwFlagEx /* = 0 */, BOOL bRenderShadow/*=FALSE*/ )
{
	guardfunc;
	MeScopeProfileMexAnimCtrlFun
	if ( !m_pMex->GetGeometry() )
		return FALSE;

	IRenderer *pRenderer = GetEngine()->GetRenderer();
	IRenderable *pSubset = m_pMex->GetGeometry()->GetChunk(nSubset);
	if( !pSubset )
        return FALSE;

    // add [6/4/2008 whu]
    pRenderer->SetMaterial( m_pMaterial );
	if ( m_pAvatarSetting )
	{
		if ( nSubset < m_pAvatarSetting->m_vectorSubsetFlag.size() )
		{
			DWORD dwFlag = m_pAvatarSetting->m_vectorSubsetFlag[nSubset];
			// 不渲染
			if ( ( dwFlag & eMexCfg_SubsetVisible ) == 0 )
			{
				return FALSE;
			}
		}
	}
	DWORD dwFvf = 0;
// 	if( pLayerData )
// 		dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2;
// 	else
		dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
	pRenderer->SetSurfaceFVF( dwFvf );
	pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
	float* pMatrix = (float *) m_amatBoneInWorldSpace;

	BOOL bRendered = FALSE;
	if ( m_bNotTexture )
	{
		RenderParams* params = CRenderParamsMgr::Instance()->RetriveRenderParams();
		if (params)
		{
			params->pMex = m_pMex;
			params->pMatrices = pMatrix;
// 			params->pRenderer = pRenderer;
			params->pReplaceableTextureProj = NULL;
			params->fAlpha = fAlpha;
			params->bMustUseAlphaBlend = false;
			params->useAnim = IsAni();			
			params->nSpecularTexID = m_SpecularTexID;
			params->stUseHeatShimmerTexId = -1;
			params->stUseShimmerGrayTexId = -1;
			params->material = m_pMaterial;
			params->nFrameId = m_nFrameId;			
			bRendered = pSubset->Render( params, 0, 0, pVertexCount, pFaceCount );
		}
	}
	else
	{
		if ( IsMirrorX() )
		{
			dwFlagEx |= eCullCCW;
		}
		if ( !IsUseSkinMesh() )
		{
			dwFlagEx |= eNotUseSkinMesh;
		}

		if ( m_SpecularTexID != -1 )
		{
			dwFlagEx |= eSpecularEnable;
			pRenderer->SetLayerCount( 2 );
			pRenderer->SetTextureId( m_SpecularTexID, 1 );
			pRenderer->EnableSpecular( TRUE );
		}

		if ( !m_pUseLuminanceTexProj )
		{
			m_pUseLuminanceTexProj = &m_LuminanceTextureProj;
		}

		RenderParams* params = CRenderParamsMgr::Instance()->RetriveRenderParams();
		if (params)
		{
			params->pMex = m_pMex;
			params->pMatrices = pMatrix;
// 			params->pRenderer = pRenderer;
			params->fAlpha = fAlpha;
			params->bMustUseAlphaBlend = false;
			params->useAnim = IsAni();			
			params->nSpecularTexID = m_SpecularTexID;
			params->material = m_pMaterial;
			params->nFrameId = m_nFrameId;
			if ( pLayerData ) // 有lightmap, 添加uv和贴图信息
			{
				params->m_nLightmapTexId = pLayerData->nTextureID;
				params->m_vLightmapUVScale = pLayerData->LightMapUVScale;
				params->m_vLightmapUVOffset = pLayerData->LightMapUVOffset;
			}
			if (m_pUseTextureProj)
			{
				params->pReplaceableTextureProj = m_pUseTextureProj;
			}
			else
			{
				params->pReplaceableTextureProj = &m_ReplaceableTextureProj;
			}
			params->stUseHeatShimmerTexId = -1;
			params->stUseShimmerGrayTexId = -1;
			params->pShimmerGrayTextureProj = m_pUseShimmerGrayTextureProj;

			bRendered = pSubset->Render( params, dwFlagEx,
				graphics::ShaderManager::instance()->isUseShader() ? m_pUseLuminanceTexProj : NULL, pVertexCount, pFaceCount);
		}
	}
	return bRendered;
	unguard;
}

// void MexAnimCtrl::FastRenderSubset( int nSubset, IRenderer* pRenderer, float fAlhpa )
// {
// 	guardfunc;
// 	if( !m_pMex->GetGeometry() )
// 		return;
// 
// 	IRenderable* pSubset = m_pMex->GetGeometry()->GetChunk(nSubset);
// 	if( !pSubset )
// 		return;
// 
// 	if( m_pAvatarSetting )
// 	{
// 		if( nSubset < m_pAvatarSetting->m_vectorSubsetFlag.size() )
// 		{
// 			DWORD dwFlag = m_pAvatarSetting->m_vectorSubsetFlag[nSubset];
// 			// 不渲染
// 			if( ( dwFlag & eMexCfg_SubsetVisible ) == 0 )
// 			{
// 				return;
// 			}
// 		}
// 	}
// 
// 	static DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
// 	pRenderer->SetSurfaceFVF( dwFvf );
// 	pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
// 
// 	float fSubsetAlhpa = fAlhpa;
// 	if( m_bNotTexture )
// 	{
// 		pSubset->FastRender( m_pMex, (float*)m_amatBoneInWorldSpace, pRenderer, NULL, fSubsetAlhpa, false ,m_nFrameId);
// 		//pSubset->Render( m_pMex, (float*)m_amatBoneInWorldSpace, pRenderer, NULL, fAlpha, false );
// 	}
// 	else
// 	{
// 		DWORD dwFlagEx = 0;
// 		if( IsMirrorX() )
// 		{
// 			dwFlagEx |= eCullCCW;
// 		}
// 
// 		if( !IsUseSkinMesh() )
// 		{
// 			dwFlagEx |= eNotUseSkinMesh;
// 		}
// 
// 		if( m_SpecularTexID != -1 )
// 		{
// 			dwFlagEx |= eSpecularEnable;
// 			pRenderer->SetLayerCount( 2 );
// 			pRenderer->SetTextureId( m_SpecularTexID, 1 );
// 			pRenderer->EnableSpecular( TRUE );
// 		}
// 
// 		if( m_pUseTextureProj )
// 		{
// 			pSubset->FastRender( m_pMex, 
// 				(float*)m_amatBoneInWorldSpace, 
// 				pRenderer, 
// 				m_pUseTextureProj, 
// 				fSubsetAlhpa, 
// 				false, dwFlagEx );
// 		}
// 		else
// 		{
// 			pSubset->FastRender( m_pMex, 
// 				(float*)m_amatBoneInWorldSpace, 
// 				pRenderer, 
// 				&m_ReplaceableTextureProj, 
// 				fSubsetAlhpa, 
// 				false, dwFlagEx );
// 		}
// 	}
// 	unguard;
// }
// 
void MexAnimCtrl::RenderSubsetShadow( int nSubset, IRenderer* pRenderer )
{
	guardfunc;
	MeScopeProfileMexAnimCtrlFun
	if( !m_pMex->GetGeometry() )
		return;

	IRenderable* pSubset = m_pMex->GetGeometry()->GetChunk(nSubset);
	if( !pSubset )
		return;

	if( m_pAvatarSetting )
	{
		if( nSubset < m_pAvatarSetting->m_vectorSubsetFlag.size() )
		{
			DWORD dwFlag = m_pAvatarSetting->m_vectorSubsetFlag[nSubset];
			// 不渲染
			if( ( dwFlag & eMexCfg_SubsetVisible ) == 0 )
			{
				return;
			}
		}
	}
	static DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
	pRenderer->SetSurfaceFVF( dwFvf );
	pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
	if( m_bNotTexture )
	{
		pSubset->RenderShadow( m_pMex, (float*)m_amatBoneInWorldSpace, pRenderer, NULL, 0, false ,m_nFrameId);
	}
	else
	{
		DWORD dwFlagEx = 0;
		if( IsMirrorX() )
		{
			dwFlagEx = eCullCCW;
		}
		pSubset->RenderShadow( m_pMex, 
			(float*)m_amatBoneInWorldSpace, 
			pRenderer, 
			&m_ReplaceableTextureProj, 
			0, 
			false, dwFlagEx );
	}
	unguard;
}

// 更换模型
BOOL MexAnimCtrl::_ChangeModel( IMex* pMex, MexCfg* pMexCfg,const char* pszSkin )
{
	guardfunc;

	
	if( pMex  == NULL )
		return FALSE;
	if( pMex->GetSkeleton() == NULL )
		return FALSE;
	if( pMexCfg == NULL )
		return FALSE;

	SetMex( pMex, pMexCfg,pszSkin );
	int nNumBone = pMex->GetSkeleton()->GetBoneCount();

	if( m_amatBoneInWorldSpace )
	{
		delete[] m_amatBoneInWorldSpace;
		m_amatBoneInWorldSpace = NULL;
		m_matSrcBones = NULL;
		m_amatBoneInModelSpace = NULL;
	}

    m_amatBoneInWorldSpace = MeNew MeMatrix[nNumBone*3];
	m_amatBoneInModelSpace = &m_amatBoneInWorldSpace[nNumBone];
	m_matSrcBones = &m_amatBoneInWorldSpace[nNumBone*2];
	IMexBone* pBone = pMex->GetSkeleton()->GetBone(0);
	if( pBone == NULL )
		return FALSE;
	m_nFrameCount = pBone->GetFrameCount();
	//if( /*nNumBone == 1 &&*/ m_nFrameCount == 1 )
	if( nNumBone == 1 && 2 == m_nFrameCount)
	{
		m_bAni = FALSE;
	}
	else
	{
		m_bAni = TRUE;
	}
	MexCfgSequence* pIdleSeq = pMexCfg->FindIdleSequence();

	if( pBone )
	{
		if( pBone->HasKeyFrame() )
			m_bCanBlending = TRUE;
		else
			m_bCanBlending = FALSE;
	}
	else
	{
		m_bCanBlending = FALSE;
	}

	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !pSkeleton->m_bSpecialModel);
	if( m_bCanBlending && bNewKeyFrameFormat )
	{
		if( m_pKeyTimeOfBoneMatrices )
		{
			delete[] m_pKeyTimeOfBoneMatrices;
			m_pKeyTimeOfBoneMatrices = NULL;
		}
		if( m_amatBoneMatricesFromKeyTime )
		{
			delete[] m_amatBoneMatricesFromKeyTime;
			m_amatBoneMatricesFromKeyTime = NULL;
		}

		m_pKeyTimeOfBoneMatrices = new int[nNumBone];
		for(int i=0; i<nNumBone; ++i)
		{
			m_pKeyTimeOfBoneMatrices[i] = -1;
		}
		m_amatBoneMatricesFromKeyTime = MeNew MeMatrix[nNumBone];
	}

	if( m_bNeedInitUpperBodyAndLowerBody )
	{
		InitUpperBodyAndLowerBody();
	}

	m_vctBlendTransQuats.clear();
    if( m_bUpperBodyAndLowerBodyMode )
    {
        for(int i=0; i<nNumBone; i++)
        {
            BlendTransQuatsData kBlendData;
            kBlendData.kLastBlendTrans = Vector(0,0,0);
            kBlendData.kLastBlendQuats = Quaternion(0,0,0,0);
            m_vctBlendTransQuats.push_back(kBlendData);
        }

		if( m_bCanBlending && bNewKeyFrameFormat )
		{
			if( m_pTargetKeyTimeOfBoneMatrices )
			{
				delete[] m_pTargetKeyTimeOfBoneMatrices;
				m_pTargetKeyTimeOfBoneMatrices = NULL;
			}
			if( m_amatBoneMatricesTargetKeyTime )
			{
				delete[] m_amatBoneMatricesTargetKeyTime;
				m_amatBoneMatricesTargetKeyTime = NULL;
			}

			m_pTargetKeyTimeOfBoneMatrices = new int[nNumBone];
			for(int i=0; i<nNumBone; ++i)
			{
				m_pTargetKeyTimeOfBoneMatrices[i] = -1;
			}
			m_amatBoneMatricesTargetKeyTime = MeNew MeMatrix[nNumBone];
		}
    }

	if( pIdleSeq )
	{
		PlayAnimByName( pIdleSeq->m_spAnimName.GetString(), 0 );
		m_TmpSequence.m_npStartFrameId.SetNumber( pIdleSeq->m_npStartFrameId.GetNumber() );
		m_TmpSequence.m_npEndFrameId.SetNumber( pIdleSeq->m_npEndFrameId.GetNumber() );
		m_TmpSequence.m_spAnimName.SetString( "idle" );
		m_TmpSequence.m_npHasLightTrack.SetNumber( pIdleSeq->m_npHasLightTrack.GetNumber() );
	}
	else
	{
		PlayAnim( 0, m_nFrameCount - 1, 0 );
	}

	UpdateLocalBBox();
// 	if( m_pAvatar )
// 	{
// 		m_pAvatar->BindAttachments( this );
// 	}


	return TRUE;
	unguard;
}
void MexAnimCtrl::ReleaseLastModel()
{
	guardfunc;
	/*ReleaseAllLastPartModel();*/
	//if( m_nModelId == 100000019 )
	//{
	//	int k = 0;
	//}
	GetMexResMgr()->DestroyModel( m_nModelId );
	m_nModelId = -1;
// 	if( m_nModelId != -1 )
// 	{
// 	}
// 	else
	{
// 		if( /*m_bIsTerrainModel &&*/ m_pMex )
// 		{
// 			m_pMex->Release();
// 			delete m_pMex;
// 		}
// 		if( /*m_bIsTerrainModel &&*/ m_pMexCfg )
// 		{
// 			m_pMexCfg->Destroy();
// 			delete m_pMexCfg;
// 		}
	}
	m_pMex		= NULL;
	m_pMexCfg	= NULL;
	if( m_pAvatarSetting )
	{
		CloseAvatarSetting( m_pAvatarSetting );
		m_pAvatarSetting = NULL;
	}
	m_pAvatarSetting = NULL;

	unguard;
	
}
//BOOL MexAnimCtrl::ChangeCloneModel( int nModelId )
//{
//	guardfunc;
//	if( GetMexResMgr()->GetModel(nModelId) )
//		ReleaseLastModel();
//	MexResMgr::Record* pRecord = GetMexResMgr()->GetRecord( nModelId, FALSE );
//
//	if( !pRecord )
//	{
//		return FALSE;
//	}
//	m_nModelId = nModelId;
//	if( !pRecord->res.pMex )
//		return FALSE;
//
//	MexAnimCtrl::ChangeModel( pRecord->res.pMex, pRecord->res.pMexCfg );
//
//	return TRUE;
//	unguard;
//}


BOOL MexAnimCtrl::ChangeModel( int nModelId , BOOL bIsTerrainModel,const char* pszSkin, BOOL bKeepOldData /*= FALSE*/)
{
	guardfunc;
	//if( GetMexResMgr()->GetModel(nModelId) )
	//	ReleaseLastModel();

	//if( GetMexResMgr()->GetModel( m_nModelId) )

	ReleaseLastModel();

	m_bIsTerrainModel = bIsTerrainModel;

	MexResMgr::Record* pRecord = GetMexResMgr()->CreateModel( nModelId, true, bKeepOldData );

	if( !pRecord || !pRecord->res.pMex )
	{
		return FALSE;
	}

	m_nModelId = nModelId;


	_ChangeModel( pRecord->res.pMex, pRecord->res.pMexCfg,pszSkin );

	return TRUE;
	unguard;
}



void MexAnimCtrl::SetHairColor( DWORD r, DWORD g, DWORD b )
{
	guardfunc;
	m_dwHairColor[0] = r;
	m_dwHairColor[1] = g;
	m_dwHairColor[2] = b;
	unguard;
}



void MexAnimCtrl::CalcTransformMatrix( float x, 
									   float y, 
									   float z, 
									   float rot,
									   float scaleX,
									   float scaleY,
									   float scaleZ,
									   MeMatrix* pmatTransform )
{
	guardfunc;
	D3DXMATRIX matRot; 
	D3DXMatrixRotationAxis( &matRot, &D3DXVECTOR3( 0, 0, 1 ), rot );

	D3DXMATRIX matScale;
	D3DXMatrixScaling( &matScale, scaleX, scaleY, scaleZ );

	D3DXMatrixMultiply( (D3DXMATRIX*)pmatTransform, &matRot, &matScale );

	pmatTransform->m[3][0] = x;
	pmatTransform->m[3][1] = y;
	pmatTransform->m[3][2] = z;
	unguard;
}

void MexAnimCtrl::CalcTransformMatrix( MeMatrix* pmatTransform )	
{
	guardfunc;

	if( !IsNeedCalcTransformMatrix() )
	{
		float* fT = (float*)pmatTransform->m;
		float* fM = (float*)m_vPreTransformMatrix.m;
		for(int i=0; i<16; i++)
		{
			fT[i] = fM[i];
		}
	}
	else
	{
		D3DXMATRIX matRot;
		D3DXMATRIX matRotZ;
		D3DXMatrixRotationAxis( &matRotZ, &D3DXVECTOR3( 0, 0, 1 ), m_fZRotTheta );
		D3DXMATRIX matRotY;
		D3DXMatrixRotationAxis( &matRotY, &D3DXVECTOR3( 0, 1, 0 ), m_fYRotTheta );
		D3DXMATRIX matRotX;
		D3DXMatrixRotationAxis( &matRotX, &D3DXVECTOR3( 1, 0, 0 ), m_fXRotTheta );
		D3DXMatrixMultiply( &matRot, &matRotY, &matRotZ );
		D3DXMatrixMultiply( &matRot, &matRotX, &matRot );

		D3DXMATRIX matScale;
		D3DXMatrixScaling( &matScale, m_fScaleX, m_fScaleY, m_fScaleZ );

		D3DXMatrixMultiply( (D3DXMATRIX*)pmatTransform, &matRot, &matScale );

		pmatTransform->m[3][0] = m_vPosition.x;
		pmatTransform->m[3][1] = m_vPosition.y;
		pmatTransform->m[3][2] = m_vPosition.z;

		// 保存当前计算数据
		float* fT = (float*)pmatTransform->m;
		float* fM = (float*)m_vPreTransformMatrix.m;
		for(int i=0; i<16; i++)
		{
			fM[i] = fT[i];
		}
		m_vPrePosition = m_vPosition;
		m_vPreRotation = Vector(m_fXRotTheta, m_fYRotTheta, m_fZRotTheta);
		m_vPreScale = Vector(m_fScaleX, m_fScaleY, m_fScaleZ);
	}
	unguard;
}

void MexAnimCtrl::UpdateByParam( DWORD dwTime )
{
	guardfunc;
	MeMatrix mat;
	CalcTransformMatrix( &mat );
	Update( dwTime, &mat );
	unguard;
}

bool MexAnimCtrl::IntersectRayQuick(Vector* pvStart, Vector* pvDir)
{
	guardfunc;

	Vector vStart = *pvStart;
	Vector vDir = *pvStart+*pvDir;

	D3DXVec3TransformCoord( (D3DXVECTOR3*)&vStart, (D3DXVECTOR3*)pvStart, (D3DXMATRIX*)&m_matModelInv );
	D3DXVec3TransformCoord( (D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&vDir, (D3DXMATRIX*)&m_matModelInv );

	vDir = vDir-vStart;
	vDir.normalize();

	if(m_pMex->IntersectQuick(&vStart, &vDir, &m_ReplaceableTextureProj, (D3DXMATRIX*)&m_matModelInv))
		return true;
	
	return false;
	unguard;
}

// BOOL MexAnimCtrl::IntersectRay( Vector* pvStart, Vector* pvDir, Vector* pvHit )
// {
// 	guardfunc;
// 	//LOGINFO("MexAnimCtrl::IntersectRay");
// 	//LOGSAVE;
// 	Vector vStart = *pvStart;
// 	Vector vDir = *pvStart+*pvDir;
// 
// 	D3DXVec3TransformCoord( (D3DXVECTOR3*)&vStart, (D3DXVECTOR3*)pvStart, (D3DXMATRIX*)&m_matModelInv );
// 	D3DXVec3TransformCoord( (D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&vDir, (D3DXMATRIX*)&m_matModelInv );
// 
// 	vDir = vDir-vStart;
// 	vDir.normalize();
// 
// 	if( !m_pMex->GetGeometry() )
// 	{
// 		long const MAX_INTERSECTION = 128;
// 		float hits[MAX_INTERSECTION];
// 		int nHit = 0;
// 
// 		if( m_pAvatar )
// 		{
// 			for( int nComponent = 0; nComponent < m_pAvatar->GetComponentCount(); nComponent++ )
// 			{
// 				CAvatar::Component* pComponent = m_pAvatar->GetComponent( nComponent );
// 				if( !pComponent )
// 					continue;
// 				for( int nChunk = 0; nChunk < pComponent->vectorChunk.size(); nChunk++ )
// 				{
// 					IRenderable* pChunk = pComponent->vectorChunk[nChunk];
// 					if( !pChunk )
// 						continue;
// 					pChunk->Intersect(&vStart, 
// 						&vDir,hits,MAX_INTERSECTION,nHit,eMex_HitAll);
// 				}
// 			}
// 		}
// 
// 		if( nHit == 0 )
// 			return FALSE;
// 		float fMinT = hits[0];
// 		for( int i = 1; i < nHit; i++ )
// 		{
// 			if( fMinT > hits[i] )
// 				fMinT = hits[i];
// 		}
// 		*pvHit = vStart+fMinT*vDir;
// 	}
// 	else if( !m_pMex->Intersect( (float*)&vStart, (float*)&vDir, (float*)pvHit, eMex_HitAll ) )
// 	{
// 		return FALSE;
// 	}
// 	D3DXVec3TransformCoord( (D3DXVECTOR3*)pvHit, (D3DXVECTOR3*)pvHit, (D3DXMATRIX*)&m_matModel );
// 	return TRUE;
// 	unguard;
// }
// BOOL MexAnimCtrl::IntersectVRay( Vector* pvStart, Vector* pvHit )
// {
// 	guardfunc;
// 	//LOGINFO("MexAnimCtrl::IntersectVRay");
// 	//LOGSAVE;
// 	Vector vStart;
// 	Vector vDir( 0, 0, -1 );
// 	if( !m_pMex )
// 		return FALSE;
// 	if( !m_pMex->GetGeometry() )
// 		return FALSE;
// 
// 	D3DXVec3TransformCoord( (D3DXVECTOR3*)&vStart, (D3DXVECTOR3*)pvStart, (D3DXMATRIX*)&m_matModelInv );
// 
// 	if( !m_pMex->Intersect( (float*)&vStart, (float*)&vDir, (float*)pvHit, eMex_HitFloor ) )
// 		return FALSE;
// 	D3DXVec3TransformCoord( (D3DXVECTOR3*)pvHit, (D3DXVECTOR3*)pvHit, (D3DXMATRIX*)&m_matModel );
// 
// 	return TRUE;
// 	unguard;
// }

void MexAnimCtrl::EnableAllEffects( BOOL bEnable )
{
	guardfunc;
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->SetActive( bEnable );
		}
	}
	unguard;
}


// void MexAnimCtrl::FastRenderAvatorComponent( CAvatar* pAvatar, CAvatar::Component* pComponent, IRenderer* pRenderer, float fAlpha, bool bMustUseAlphaBlend )
// {
// 	guardfunc;
// 	//static D3DXMATRIX		matMatrices[64];
// 	D3DXMATRIX* pBoneMatrices = NULL;
// 	DWORD dwItemEnableFlag = pAvatar->GetItemFlag();
// 	pBoneMatrices = (D3DXMATRIX*)m_amatBoneInWorldSpace;
// 
// 	BOOL bToolMode = GetMe3dConfig()->m_bToolMode;
// 	BOOL bLeftHand = pComponent->m_bLeftHand;
// 
// 	for( int nChunk = 0; nChunk < pComponent->vectorChunk.size(); nChunk++ )
// 	{
// 		IRenderable* pChunk = pComponent->vectorChunk[nChunk];
// 
// 		//char szBuf[256];
// 		//_snprintf( szBuf, 256, "%s", pChunk->GetName() );
// 		//OutputDebugString( szBuf );
// 
// 		if( !pChunk )
// 			continue;
// 
// 		DWORD dwFlag = pComponent->flags[nChunk];
// 		if( !bToolMode )
// 		{
// 			if( bLeftHand )
// 			{
// 				if( (dwFlag == CAvatar::eItem_RBack ) )
// 				{
// 					continue;
// 				}
// 				if( (dwFlag == CAvatar::eItem_RightHand ) )
// 				{
// 					continue;
// 				}
// 			}
// 			else
// 			{
// 				if( (dwFlag == CAvatar::eItem_LBack ) )
// 				{
// 					continue;
// 				}
// 				if( (dwFlag == CAvatar::eItem_LeftHand ) )
// 				{
// 					continue;
// 				}
// 			}
// 		}
// 
// 		if( !AvatarComponentTest( bLeftHand, dwFlag, dwItemEnableFlag ) )
// 			continue;
// 
// 		{
// 			pRenderer->SetLayerCount( 1 );
// 			DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
// 			pRenderer->SetSurfaceFVF( dwFvf );
// 			pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
// 			MtlAnim* pMtlEffect = pComponent->pMtlEffect;
// 			if( pMtlEffect )
// 			{
// 				if( pMtlEffect->m_bHasSpecular )
// 				{
// 					pRenderer->SetMtlSpecular( 
// 						pMtlEffect->m_fSpecularPower,
// 						1.0f,
// 						pMtlEffect->m_fSpecularRed,
// 						pMtlEffect->m_fSpecularGreen,
// 						pMtlEffect->m_fSpecularBlue );
// 					pRenderer->EnableSpecular( TRUE );
// 				}
// 				if( pMtlEffect->m_nLayerCount == 2 )
// 				{
// 					pRenderer->SetLayerCount( 2 );
// 					MtlAnim::SSetting setting;
// 
// 					pMtlEffect->GetSetting( HQ_TimeGetTime(), &setting );
// 					pRenderer->SetGlobalUOffset( 1, setting.fUOffset );
// 					pRenderer->SetGlobalVOffset( 1, setting.fVOffset );
// 
// 					pRenderer->SetTextureId( setting.nTextureId, 1 );
// 					dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2;
// 					pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
// 					pRenderer->SetSurfaceFVF( dwFvf );
// 				}
// 			}
// 
// 			if( pComponent->m_nSpecularTexID != -1 )
// 			{
// 				pRenderer->SetLayerCount( 2 );
// 				pRenderer->SetTextureId( pComponent->m_nSpecularTexID, 1 );
// 				dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX2;
// 				pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
// 				pRenderer->EnableSpecular( TRUE );
// 			}
// 
// 			pChunk->FastRender( m_pMex, 
// 				(float*)pBoneMatrices, 
// 				pRenderer, 
// 				&pComponent->ReplaceableTextureProj, 
// 				fAlpha,
// 				bMustUseAlphaBlend ,m_nFrameId);	
// 		}
// 	}
// 
// 
// 	//TODO
// 	//CAvatar::EffectContainer* ec = &pComponent->m_EffectContainer;
// 	//BOOL bUseLightTrack = FALSE;
// 	//if( m_pSeqUpperBody )
// 	//{
// 	//	bUseLightTrack = m_pSeqUpperBody->m_npHasLightTrack.GetNumber();
// 	//}
// 
// 	//for( int nEffect = 0; nEffect < ec->effects.size(); nEffect++ )
// 	//{
// 	//	CAvatar::Effect* pEffect = &ec->effects[nEffect];
// 
// 	//	if( !AvatarComponentTest( bLeftHand, pEffect->dwFlag, dwItemEnableFlag ) )
// 	//		continue;
// 
// 	//	if( pEffect->part )
// 	//	{
// 	//		int nLocalTextureId = pEffect->part->GetLocalTextureID();
// 	//		int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
// 	//		pEffect->part->Render( HQ_TimeGetTime(), nTextureId, fAlpha, false );
// 	//	}
// 
// 	//	DWORD dwCurTime = HQ_TimeGetTime();
// 
// 	//	if( 0 &&
// 	//		pEffect->pWeaponBladeRibbon &&
// 	//		pEffect->pWeaponBladeRibbon->IsEnable() )
// 	//	{
// 	//		int nLocalTextureId = pEffect->ribb->GetLocalTextureID();
// 	//		int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
// 	//		pEffect->pWeaponBladeRibbon->Render( nTextureId, 0xffffffff, 1.0f );
// 	//	}
// 
// 	//	//if( pEffect->ribb && ( bUseLightTrack || dwCurTime - m_dwLightTrackDeadTime < LIGHTTRACKDEADRENDERTIME ) )
// 	//	//{
// 	//	//	float fAlpha = (float)( LIGHTTRACKDEADRENDERTIME - ( dwCurTime - m_dwLightTrackDeadTime ) )/LIGHTTRACKDEADRENDERTIME;
// 	//	//	if( m_fLightTrackAlpha < fAlpha )
// 	//	//	{
// 	//	//		m_fLightTrackAlpha += 0.03f ;
// 	//	//	}
// 	//	//	else
// 	//	//	{
// 	//	//		m_fLightTrackAlpha = fAlpha;
// 	//	//	}
// 
// 	//	//	int nLocalTextureId = pEffect->ribb->GetLocalTextureID();
// 	//	//	int nTextureId = pComponent->ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
// 	//	//	pEffect->ribb->Render( NULL, nTextureId, m_fLightTrackAlpha, TRUE );
// 	//	//}
// 	//}	
// 	unguard;
// }




BOOL MexAnimCtrl::IsUpperBodyAndLowerBodyMode()
{
	guardfunc;
	return m_bUpperBodyAndLowerBodyMode;
	unguard;
}

void MexAnimCtrl::CancelUpperBodyAndLowerBodyMode()
{
	guardfunc;
	if( m_bUpperBodyAndLowerBodyMode )
	{
		m_bUpperBodyAndLowerBodyMode = FALSE;
	}
	unguard;
}

BOOL MexAnimCtrl::IsIdleSequence( MexCfgSequence* pSequence )
{
	guardfunc;
	if( pSequence )
	{
		const char* szString = pSequence->m_spAnimName.GetString();
		int nLen = strlen(szString);
		if ( nLen < 4 )
			return FALSE;

		if( _stricmp( &szString[nLen-4], "idle" ) == 0 )
		{
			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

BOOL MexAnimCtrl::IsComSequence( MexCfgSequence* pSequence )
{
	guardfunc;
	if( pSequence )
	{
		const char* szString = pSequence->m_spAnimName.GetString();
		int nLen = strlen(szString);
		if ( nLen < 3 )
			return FALSE;

		if( _stricmp( &szString[nLen-3], "com" ) == 0 )
		{
			return TRUE;
		}
	}
	return FALSE;
	unguard;
}

void MexAnimCtrl::SetUpperRot( float fRot )
{
	guardfunc;
	//fRot = fmodf( fRot, D3DX_PI*2 );
	//if( fRot < 0 )
	//{
	//	fRot += D3DX_PI*2;
	//}
	m_fUpperBodyRot = fRot;
	unguard;
}

void MexAnimCtrl::SetLowerRot( float fRot )
{
	guardfunc;
	//fRot = fmodf( fRot, D3DX_PI*2 );
	//if( fRot < 0 )
	//{
	//	fRot += D3DX_PI*2;
	//}
	m_fLowerBodyRot = fRot;
	unguard;
}

void MexAnimCtrl::NeedInitUpperBodyAndLowerBody()
{
	guardfunc;
	m_bNeedInitUpperBodyAndLowerBody = TRUE;
	unguard;
}

BOOL MexAnimCtrl::IsUpdateComponents()
{
	guardfunc;
	return m_bUpdateComponents;
	unguard;
}

//void MexAnimCtrl::SetUpperBodyFactor( float fFactor )
//{
//	guardfunc;
//	m_fCurBodyFrame = fFactor;
//	unguard;
//}

void MexAnimCtrl::SetEffectAnim( BOOL bEffectAnim )
{
	guardfunc;
	m_bEffectAnim = bEffectAnim;
	unguard;
}

void MexAnimCtrl::SetUpperBodyFactor( float fFactor )
{
	guardfunc;
	m_fUpperBodyFactor = fFactor;

    // 目前这个接口只有在查看器里用到       added by zhuomeng.hu		[3/22/2011]
    if( m_fUpperBodyFactor > 1.0f )
    {
        m_fUpperBodyFactor = 1.0f;
    }
    if( m_fUpperBodyFactor < 0.0f )
    {
        m_fUpperBodyFactor = 0.0f;
    }
	unguard;
}

// 获取当前上半身正在播放的动画
const char* MexAnimCtrl::GetCurUpperAnim()
{
	guardfunc;
	if( m_pSeqUpperBody )
	{
		return m_pSeqUpperBody->m_spAnimName.GetString();
	}
	return NULL;
	unguard;
}

int MexAnimCtrl::GetCurUpperAnimType()
{
	guardfunc;
	return m_nUpperBodyAnimType;
	unguard;
}

// 获取当前下半身正在播放的动画
const char* MexAnimCtrl::GetCurLowerAnim()
{
	guardfunc;
	if( m_pSeqLowerBody )
	{
		return m_pSeqLowerBody->m_spAnimName.GetString();
	}
	return NULL;
	unguard;
}

int MexAnimCtrl::GetCurLowerAnimType()
{
	guardfunc;
	return m_nLowerBodyAnimType;
	unguard;
}

// 获取当前上半身的动画播放进度
float MexAnimCtrl::GetUpperBodyFactor()
{
	guardfunc;
	return m_fUpperBodyFactor;
	unguard;
}

// 获取当前下半身的动画播放进度
float MexAnimCtrl::GetLowerBodyFactor()
{
	guardfunc;
	return m_fLowerBodyFactor;
	unguard;
}

BOOL MexAnimCtrl::IsUpperBodyBlending()
{
	guardfunc;
	return m_bUpperBodyBlending;
	unguard;
}

void MexAnimCtrl::RefreshParticleEmitters(IMex *pSourceMex)
{
	BOOL bMexHavePartEmitters = TRUE;
	if (pSourceMex != NULL)
		bMexHavePartEmitters = FALSE;
	
	int nEmitterCount = m_pMex->GetParticleEmitters()->GetEmitterCount();
	for (int i = 0; i < nEmitterCount && i < eMaxParticleEmitter; ++i)
	{
		if (m_pParticleEmitters[i] != NULL)
		{
			m_pParticleEmitters[i]->Release();
			m_pParticleEmitters[i] = NULL;
		}
		m_pParticleEmitters[i] = m_pMex->GetParticleEmitters()->GetEmitter(i)->Clone();
		m_HasEmitter = TRUE;
	}

	// 如果Mex没有粒子发射器, 则表明是运行时添加的
	if (!bMexHavePartEmitters)
	{
		std::vector<int> old_render_texids;
		int nTextureCount = m_ReplaceableTextureProj.GetTextureCount();
		for (int i = 0; i < nTextureCount; ++i)
			old_render_texids.push_back(m_ReplaceableTextureProj.GetRenderTextureID(i));

		m_ReplaceableTextureProj.SetTextureCount(nTextureCount + nEmitterCount);
		for (int i = 0, j = 0; i < m_ReplaceableTextureProj.GetTextureCount(); ++i)
		{
			if (i < old_render_texids.size())
			{
				m_ReplaceableTextureProj.SetRenderTextureID(i, old_render_texids[i]);
			}
			else
			{
				int nLocalTexID = pSourceMex->GetParticleEmitters()->GetEmitter(j)->GetLocalTextureID();

				m_pParticleEmitters[j++]->SetLocalTextureID(i);
				int nTexID = m_ReplaceableTextureProj.RegisterTexture(m_pMex->GetFilename(), pSourceMex->GetTextures()->GetTexture(nLocalTexID)->GetName(), TRUE);
				m_ReplaceableTextureProj.SetRenderTextureID(i, nTexID);
			}
		}
	}	
}

BOOL MexAnimCtrl::IsLowerBodyBlending()
{
	guardfunc;
	return m_bLowerBodyBlending;
	unguard;
}

DWORD MexAnimCtrl::FastPlayUpperAnim( float fSpeedX )
{
	guardfunc;
	return m_UpperBodyAnimTimeLine.FastPlay( HQ_TimeGetTime(), fSpeedX );
	unguard;
}

BOOL MexAnimCtrl::IsUpperAnimPlayOver()
{
	guardfunc;
	return m_bUpperBodyPlayOver;
	unguard;
}

BOOL MexAnimCtrl::IsUpperAnimHitPointPlayOver()
{
	guardfunc;
	return m_UpperBodyAnimTimeLine.TryHitPoint( HQ_TimeGetTime() );
	unguard;
}

BOOL MexAnimCtrl::UpdateSpineBonePosOffset( DWORD dwTime, MeMatrix* pMatrix )
{
	guardfunc;
	BOOL bChangeAnim = FALSE;
	if( m_bUpperBodyAndLowerBodyMode )
	{
		DWORD dwStart = HQ_TimeGetTime();
		BOOL bFinish = FALSE;

		if( m_nNumLowerBodyPlayTask > 0 )
		{
			if( m_bLowerBodyBlending )
			{
				DWORD dwBlendingTime = dwStart - m_dwLowerBodyStartBlendingTime;
				if( dwBlendingTime > m_dwLowerBodyBlendingStep )
				{
					m_bLowerBodyBlending = FALSE;
				}
				else
				{
					m_fLowerBodyFactor = (float)dwBlendingTime/m_dwLowerBodyBlendingStep;
				}
			}

			if( !m_bLowerBodyBlending )
			{
				SPlayTask* pTask = &m_LowerBodyPlayTask[0];

				switch( pTask->dwPlayMode )
				{
				case eHoldOnFirstFrame:
					m_fLowerBodyFactor = 0;
					break;
				case eHoldOnLastFrame:
					m_fLowerBodyFactor = 1;
					break;
				case eSingleFrame:
					break;
				case eBlendFrame:
					break;
				case eNormalPlay:
					{
						int nLoopTimes = m_LowerBodyAnimTimeLine.GetNumLooped( dwTime );
						DWORD dwStartTime = m_LowerBodyAnimTimeLine.GetStartTime();
						if ( dwTime < dwStartTime )
						{
							nLoopTimes = 0;
						}

						if( dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
							bFinish = TRUE;

						if( dwTime > dwStartTime &&	dwTime-dwStartTime >= pTask->dwTimeOut )
							bFinish = TRUE;

						if( m_LowerBodyAnimTimeLine.IsLoopPlaying() )
						{
							m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
						}
						else
						{
							m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
						}
					}
					break;
				}

				if( bFinish && m_nNumLowerBodyPlayTask > 1 )
				{
					assert( m_nNumLowerBodyPlayTask >= 2 && "task count must >=2" );

					memcpy( &m_LowerBodyPlayTask[0], &m_LowerBodyPlayTask[1], sizeof(SPlayTask) );

					m_nNumLowerBodyPlayTask--;

					assert( m_nNumLowerBodyPlayTask > 0 && "next task is null" );

					pTask = &m_LowerBodyPlayTask[0];

					bChangeAnim = PlayAnim( pTask );
					switch( pTask->dwPlayMode )
					{
					case eHoldOnFirstFrame:
						m_fLowerBodyFactor = 0;
						break;
					case eHoldOnLastFrame:
						m_fLowerBodyFactor = 1;
						break;
					}
				}
			}
		}

		if( m_bUpperBodyPlayOver )
		{
			m_bUpperBodyBlending = m_bLowerBodyBlending;
			m_pSeqUpperBody = m_pSeqLowerBody;
			m_fUpperBodyFactor = m_fLowerBodyFactor;
		}
		else
		{
			bFinish = FALSE;

			if( m_nNumUpperBodyPlayTask > 0 )
			{
				if( m_bUpperBodyBlending )
				{
					DWORD dwBlendingTime = dwStart - m_dwUpperBodyStartBlendingTime;
					if( dwBlendingTime > m_dwUpperBodyBlendingStep )
					{
						m_bUpperBodyBlending = FALSE;
					}
					else
					{
						m_fUpperBodyFactor = (float)dwBlendingTime/m_dwUpperBodyBlendingStep;
					}
				}

				if( !m_bUpperBodyBlending )
				{
					SPlayTask* pTask = &m_UpperBodyPlayTask[0];

					switch( pTask->dwPlayMode )
					{
					case eHoldOnFirstFrame:
						m_fUpperBodyFactor = 0;
						break;
					case eHoldOnLastFrame:
						m_fUpperBodyFactor = 1;
						break;
					case eSingleFrame:
						break;
					case eBlendFrame:
						break;
					case eNormalPlay:
						{
							int nLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( dwTime );
							DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
							if ( dwTime < dwStartTime )
							{
								nLoopTimes = 0;
							}

							if( !m_bUpperBodyPlayOver && dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
							{
								m_bUpperBodyPlayOver = TRUE;
								m_bPlayingWholeBodyAnim = FALSE;
							}

							if( !m_bUpperBodyPlayOver && dwTime > dwStartTime && dwTime-dwStartTime >= pTask->dwTimeOut )
							{
								m_bUpperBodyPlayOver = TRUE;
								m_bPlayingWholeBodyAnim = FALSE;
							}

							if( m_UpperBodyAnimTimeLine.IsLoopPlaying() )
							{
								m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
							}
							else
							{
								m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetCurPlayPercent( dwTime );
							}
						}
						break;
					}
				}
			}

			if( m_bUpperBodyPlayOver )
			{
				if( m_bCanBlending )
				{
					m_bUpperBodyBackBlending = TRUE;
					m_dwUpperBodyStartBackBlendingTime = HQ_TimeGetTime();
				}

				if( IsIdleSequence( m_pSeqLowerBody ) )
				{
					if( m_bCanBlending )
					{
						m_bLowerBodyBackBlending = TRUE;
						m_dwLowerBodyStartBackBlendingTime = HQ_TimeGetTime();
					}
				}

				m_bUpperBodyBlending = m_bLowerBodyBlending;
				m_pSeqUpperBody = m_pSeqLowerBody;
				m_fUpperBodyFactor = m_fLowerBodyFactor;
			}
		}
	}
	else
	{
		DWORD dwStart = HQ_TimeGetTime();

		BOOL bFinish = FALSE;

		if( m_nNumPlayTask == 0 )
		{
			return bChangeAnim;
		}

		if( m_bUpperBodyBlending )
		{
			DWORD dwBlendingTime = dwStart - m_dwUpperBodyStartBlendingTime;
			if( dwBlendingTime > m_dwUpperBodyBlendingStep )
			{
				m_bUpperBodyBlending = FALSE;
			}
			else
			{
				m_fUpperBodyFactor = (float)dwBlendingTime/m_dwUpperBodyBlendingStep;
			}
		}

		if( !m_bUpperBodyBlending )
		{
			SPlayTask* pTask = &m_PlayTasks[0];
			switch( pTask->dwPlayMode )
			{
			case eHoldOnFirstFrame:
				m_fUpperBodyFactor = 0;
				break;
			case eHoldOnLastFrame:
				m_fUpperBodyFactor = 1;
				break;
			case eSingleFrame:
				break;
			case eBlendFrame:
				break;
			case eNormalPlay:
				{
					int nLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( dwTime );
					DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
					if ( dwTime < dwStartTime )
					{
						nLoopTimes = 0;
					}

					if( dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
					{
						bFinish = TRUE;
					}

					if( dwTime > dwStartTime && dwTime-dwStartTime >= pTask->dwTimeOut )
					{
						bFinish = TRUE;
					}

					if( m_UpperBodyAnimTimeLine.IsLoopPlaying() )
					{
						m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
					}
					else
					{
						m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetCurPlayPercent( dwTime );
					}
				}
				break;
			}

			// 
			if( bFinish && m_nNumPlayTask > 1 )
			{
				assert( m_nNumPlayTask >= 2 && "task count must >=2" );
				//m_vectorPlayTask.erase( m_vectorPlayTask.begin() );
				memcpy( &m_PlayTasks[0], &m_PlayTasks[1], (m_nNumPlayTask-1)*sizeof(SPlayTask) );
				m_nNumPlayTask--;

				//OnNextPlayTask();
				//assert( m_vectorPlayTask.size() > 0 && "next task is null" );
				assert( m_nNumPlayTask > 0 && "next task is null" );

				//pTask = &m_vectorPlayTask[0];
				pTask = &m_PlayTasks[0];

				assert( pTask->dwTimeOut > 2000 && "second task timeout too small" );
				PlayAnim( pTask );
				switch( pTask->dwPlayMode )
				{
				case eHoldOnFirstFrame:
					m_fUpperBodyFactor = 0;
					break;
				case eHoldOnLastFrame:
					m_fUpperBodyFactor = 1;
					break;
				}
			}
		}
	}


	if( !m_amatBoneInWorldSpace )
	{
		return bChangeAnim;
	}

	if( !m_pMex )
	{
		return bChangeAnim;
	}

	// 模型整体在世界空间中的变换
	if( !pMatrix )
		return bChangeAnim;

	SetTransform( (float*)pMatrix );
	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();

	if( !pSkeleton )
		return bChangeAnim;

	//// 因为在调试期间出现异常，
	//int nFrameId = m_nFrameId;
	//if( nFrameId < 0 )
	//{
	//	assert( false && "frame id < 0 " );
	//	nFrameId = 0;
	//}

	if( m_bUpperBodyAndLowerBodyMode )
	{
		if(m_bPlayingWholeBodyAnim
            || (( IsIdleSequence( m_pSeqLowerBody ) || IsComSequence( m_pSeqUpperBody ) ) 
                && !m_bLowerBodyBlending ))
		{
			UpdateBodySpineBonePosOffset( m_vPosition.x, m_vPosition.y, m_vPosition.z,
				m_fScaleX, m_fScaleY, m_fScaleZ, m_fUpperBodyRot, m_fZRotTheta + m_fLowerBodyRot,
				m_pSeqUpperBody, m_fUpperBodyFactor, m_bUpperBodyBlending,
				m_pSeqUpperBody, m_fUpperBodyFactor, m_bUpperBodyBlending );
		}
		else
		{
			UpdateBodySpineBonePosOffset( m_vPosition.x, m_vPosition.y, m_vPosition.z,
				m_fScaleX, m_fScaleY, m_fScaleZ, m_fUpperBodyRot, m_fZRotTheta + m_fLowerBodyRot,
				m_pSeqUpperBody, m_fUpperBodyFactor, m_bUpperBodyBlending,
				m_pSeqLowerBody, m_fLowerBodyFactor, m_bLowerBodyBlending );
		}
	}
	return bChangeAnim;
	unguard;
}

void MexAnimCtrl::UpdateBodySpineBonePosOffset( float x, float y, float z, float fScaleX, float fScaleY, float fScaleZ, 
												float fUpperBodyRot, float fLowerBodyRot, 
												MexCfgSequence* pSeqUpperBody, float fUpperBodyFactor, BOOL bUpperBodyBlending, 
												MexCfgSequence* pSeqLowerBody, float fLowerBodyFactor, BOOL bLowerBodyBlending )
{
	guardfunc;
	if( !m_bUpperBodyAndLowerBodyMode )
		return;

	if( !pSeqUpperBody || !pSeqLowerBody )
		return;

	if( m_nUpperBodyRootBoneID == -1 )
	{
		return;
	}

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();
	if( !pSkeleton )
		return;

	MeMatrix matUpperBody;
	MeMatrix matLowerBody;

	int nBoneCount = pSkeleton->GetBoneCount();

	float fTargetUpperBodyFrame = 0;
	float fTargetLowerBodyFrame = 0;

	if( bUpperBodyBlending )
	{
		fTargetUpperBodyFrame = pSeqUpperBody->GetBlendFrame( 0 );
		//TODO::Aren的临时方案
		if( fUpperBodyFactor > 1 )
		{
			fUpperBodyFactor = 0;
		}
	}
	else
	{
		if( m_bUpperBodyBackBlending )
		{
			DWORD dwStep = HQ_TimeGetTime() - m_dwUpperBodyStartBackBlendingTime;
			if( dwStep < (eDefaultBlendingTime*4) )
			{
				bUpperBodyBlending = TRUE;
				fTargetUpperBodyFrame = pSeqUpperBody->GetBlendFrame( fUpperBodyFactor );
				fUpperBodyFactor = (float)dwStep/(eDefaultBlendingTime*4);
			}
			else
			{
				m_bUpperBodyBackBlending = FALSE;
				m_fCurUpperBodyFrame = pSeqUpperBody->GetBlendFrame( fUpperBodyFactor );
			}
		}
		else
		{
			m_fCurUpperBodyFrame = pSeqUpperBody->GetBlendFrame( fUpperBodyFactor );
		}
	}

	if( bLowerBodyBlending )
	{
		fTargetLowerBodyFrame = pSeqLowerBody->GetBlendFrame( 0 );
		//TODO::Aren的临时方案
		if( fLowerBodyFactor > 1 )
		{
			fLowerBodyFactor = 0;
		}
	}
	else
	{
		if( m_bLowerBodyBackBlending)
		{
			DWORD dwStep = HQ_TimeGetTime() - m_dwLowerBodyStartBackBlendingTime;
			if( dwStep < (eDefaultBlendingTime*2) )
			{
				bLowerBodyBlending = TRUE;
				fTargetLowerBodyFrame = pSeqLowerBody->GetBlendFrame( fLowerBodyFactor );
				fLowerBodyFactor = (float)dwStep/(eDefaultBlendingTime*2);
			}
			else
			{
				m_bLowerBodyBackBlending = FALSE;
				m_fCurLowerBodyFrame = pSeqLowerBody->GetBlendFrame( fLowerBodyFactor );
			}
		}
		else
		{
			m_fCurLowerBodyFrame = pSeqLowerBody->GetBlendFrame( fLowerBodyFactor );
		}
	}


	IMexBone* pBone = pSkeleton->GetBone(m_nUpperBodyRootBoneID);
	if( pSeqUpperBody != pSeqLowerBody )
	{
		float fUpperRotation = pBone->GetRotation( m_fCurUpperBodyFrame, FRAMEPERSEC );
		float fLowerRotation = pBone->GetRotation( m_fCurLowerBodyFrame, FRAMEPERSEC );
		float fUpperLowerAngle = fUpperRotation - fLowerRotation;

		if( fUpperLowerAngle > D3DX_PI )
		{
			fUpperLowerAngle = fUpperLowerAngle - D3DX_PI*2;
		}

		if( fUpperLowerAngle < -D3DX_PI )
		{
			fUpperLowerAngle = fUpperLowerAngle + D3DX_PI*2;
		}

		if( fUpperLowerAngle > D3DX_PI/180*61.8f )
		{
			fUpperLowerAngle -= D3DX_PI/180*61.8f;
		}
		else if( fUpperLowerAngle < -D3DX_PI/180*61.8f )
		{
			fUpperLowerAngle += D3DX_PI/180*61.8f;
		}
		else
		{
			fUpperLowerAngle = 0;
		}

		fUpperBodyRot -= fUpperLowerAngle;
	}

	///////// 1
	{
		CalcTransformMatrix( x, y, z, fUpperBodyRot, fScaleX, fScaleY, fScaleZ, &matUpperBody );
		matLowerBody = *(MeMatrix*)GetTransform();
	}

	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel);
	if( bLowerBodyBlending && pBone->HasKeyFrame() )
	{
		MeMatrix* pMatrix = (MeMatrix*)GetKeyFrameBlendedMatrices( pBone,
			fLowerBodyFactor, m_fCurLowerBodyFrame, fTargetLowerBodyFrame, FRAMEPERSEC );

		D3DXMatrixMultiply( 
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
			(D3DXMATRIX*)pBone->GetFrame0Inv(),
			(D3DXMATRIX*)pMatrix );

		IMexBone* pBipBone = pSkeleton->GetBone(m_nBipBoneID);
		if( pBipBone && pBipBone->HasKeyFrame() )
		{
			MeMatrix BipBoneMatrices;
			MeMatrix LowerBodyMatrices = matLowerBody;
			BipBoneMatrices = *(MeMatrix*)GetKeyFrameBlendedMatrices( pBipBone,
				fLowerBodyFactor, m_fCurLowerBodyFrame, fTargetLowerBodyFrame, FRAMEPERSEC );

			BipBoneMatrices.m[0][0] *= -1;
			BipBoneMatrices.m[1][0] *= -1;
			BipBoneMatrices.m[2][0] *= -1;
			BipBoneMatrices.m[3][0] *= -1;

			LowerBodyMatrices.m[3][0] = 0;
			LowerBodyMatrices.m[3][1] = 0;
			LowerBodyMatrices.m[3][2] = 0;

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&BipBoneMatrices, 
				(D3DXMATRIX*)&BipBoneMatrices,
				(D3DXMATRIX*)&LowerBodyMatrices );

			m_vSpineBonePosOffset.x = BipBoneMatrices.m[3][0];
			m_vSpineBonePosOffset.y = BipBoneMatrices.m[3][1];
			m_vSpineBonePosOffset.z = BipBoneMatrices.m[3][2];
		}
	}
	else
	{
		if( pBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧
		{
			BOOL bGetParentMat = FALSE;
			if( pBone->GetParentId() >= 0 )
				bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurLowerBodyFrame, pBone->GetParentId());

			float* pMatrix = NULL;
			if( bGetParentMat )
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
			else
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC);

			SetBoneMatricesAtTime(m_fCurLowerBodyFrame, m_nUpperBodyRootBoneID, pMatrix);

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pMatrix );
		}
		else
			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_amatBoneInWorldSpace[m_nUpperBodyRootBoneID], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC) );

		IMexBone* pBipBone = pSkeleton->GetBone(m_nBipBoneID);
		if( pBipBone )
		{
			MeMatrix BipBoneMatrices;
			MeMatrix LowerBodyMatrices = matLowerBody;
			if( pBipBone->HasKeyFrame() && bNewKeyFrameFormat )	// 关键帧
			{
				BOOL bGetParentMat = FALSE;
				if( pBipBone->GetParentId() >= 0 )
					bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurLowerBodyFrame, pBipBone->GetParentId());

				float* pMatrix = NULL;
				if( bGetParentMat )
					BipBoneMatrices = *(MeMatrix*)pBipBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBipBone->GetParentId()]);
				else
					BipBoneMatrices = *(MeMatrix*)pBipBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC);

				SetBoneMatricesAtTime(m_fCurLowerBodyFrame, m_nBipBoneID, (float*)&BipBoneMatrices);
			}
			else
			BipBoneMatrices = *(MeMatrix*)pBipBone->GetMatricesFromKeyTime(m_fCurLowerBodyFrame,FRAMEPERSEC);

			BipBoneMatrices.m[0][0] *= -1;
			BipBoneMatrices.m[1][0] *= -1;
			BipBoneMatrices.m[2][0] *= -1;
			BipBoneMatrices.m[3][0] *= -1;

			LowerBodyMatrices.m[3][0] = 0;
			LowerBodyMatrices.m[3][1] = 0;
			LowerBodyMatrices.m[3][2] = 0;

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&BipBoneMatrices, 
				(D3DXMATRIX*)&BipBoneMatrices,
				(D3DXMATRIX*)&LowerBodyMatrices );

			m_vSpineBonePosOffset.x = BipBoneMatrices.m[3][0];
			m_vSpineBonePosOffset.y = BipBoneMatrices.m[3][1];
			m_vSpineBonePosOffset.z = BipBoneMatrices.m[3][2];
		}
	}
	unguard;
}

BOOL	MexAnimCtrl::IsUpperBodyPlayingComAnim()
{
	return m_bUpperBodyPlayingComAnim;
}

//////////////////////////////////////////////////////////////
AnimTimeLine* MexAnimCtrl::GetUpperBodyAnimTimeLine()
{
	guardfunc;
	return &m_UpperBodyAnimTimeLine;
	unguard;
}

AnimTimeLine* MexAnimCtrl::GetLowerBodyAnimTimeLine()
{
	guardfunc;
	return &m_LowerBodyAnimTimeLine;
	unguard;
}

bool MexAnimCtrl::attachChild( const std::string name, MexAnimCtrl* pChild )
{
    guardfunc
    if ( !pChild )
        return false;
    return _mexChildren.insert( MexAnimCtrlChildrenSet::value_type(name, pChild) ).second;
    unguard
}

void MexAnimCtrl::detachAndDestroyChild(const std::string& name )
{
    guardfunc
    MexAnimCtrl* pChild = detachChild( name );
    if ( pChild )
    {
        pChild->Destroy();
        delete pChild;
    }
    unguard
}

void MexAnimCtrl::detachAndDestroyAllChild()
{
    guardfunc
    MexAnimCtrlChildrenSet::iterator it = _mexChildren.begin(),
        end = _mexChildren.end();
    for ( ; it != end; ++it )
    {
        it->second->Destroy();
        delete it->second;
    }
    _mexChildren.clear();
    unguard
}

MexAnimCtrl* MexAnimCtrl::detachChild(const std::string &name)
{
    guardfunc
    MexAnimCtrlChildrenSet::iterator it = _mexChildren.find( name );
    if ( it != _mexChildren.end() )
    {
        MexAnimCtrl* pChild = it->second;
        _mexChildren.erase( it );
        return pChild;
    }
    return NULL;
    unguard
}

void MexAnimCtrl::detachAllChild()
{
    guardfunc
    _mexChildren.clear();
    unguard
}

MexAnimCtrl* MexAnimCtrl::getChild(const std::string& name )
{
    guardfunc
    MexAnimCtrlChildrenSet::iterator it = _mexChildren.find( name );
    if ( it != _mexChildren.end() )
        return it->second;

    return NULL;
    unguard
}

void MexAnimCtrl::updateChildren( DWORD dwTime, const MeMatrix* pParentMatrix )
{
    guardfunc
    if ( !_enableChildren )
        return;

    MexAnimCtrlChildrenSet::iterator it = _mexChildren.begin(),
        end = _mexChildren.end();
    for ( ; it != end; ++it )
    {
        if ( !it->second )
            continue;

        MeMatrix mat;
        it->second->SetScale( 1.0f );
        it->second->CalcTransformMatrix( &mat );
        D3DXMatrixMultiply( (D3DXMATRIX*)(&mat),(const D3DXMATRIX*)&mat, (const D3DXMATRIX*)pParentMatrix );
        it->second->SetScale( GetScale() );
        it->second->Update( dwTime, &mat );
    }
    unguard
}

void MexAnimCtrl::renderChildren(float fTransparent )
{
    guardfunc
    if ( !_enableChildren )
        return;

    MexAnimCtrlChildrenSet::iterator it = _mexChildren.begin(),
        end = _mexChildren.end();
    for ( ; it != end; ++it )
    {
        if ( it->second )
            it->second->Render( fTransparent );
    }
    unguard
}

void MexAnimCtrl::EnableChildrenUpdateAndRender(bool enabled )
{
    guardfunc
    _enableChildren = enabled;
    unguard
}

BOOL MexAnimCtrl::Clone( MexAnimCtrl* pMexAnim, BOOL IsTerrainModel/*=FALSE*/ )
{
	if (!pMexAnim)
	{
		return FALSE;
	}
	if (!pMexAnim->GetMex())
	{
		return FALSE;
	}
// 	DWORD dwFlag = 0;
// 	IMex* pCloneMex = pMexAnim->GetMex()->Clone( dwFlag );
// 	if( !pCloneMex )
// 		return FALSE;
// 	MexCfg* pCloneCfg = MeNew MexCfg;
// 	if( pMexAnim->GetMexCfg()->GetMemory() )
// 		pCloneCfg->LoadFromMemory(pMexAnim->GetMexCfg()->GetMemory(),pMexAnim->GetMexCfg()->GetFileSize());
// 	else
// 	{
// 		MexCfgSequence* sequence = MeNew MexCfgSequence;
// 		sequence->m_spAnimName.SetString( "none" );
// 		sequence->m_npStartFrameId.SetNumber( pCloneMex->GetSequence()->GetStartFrameID() );
// 		sequence->m_npEndFrameId.SetNumber( pCloneMex->GetSequence()->GetEndFrameID() );
// 		sequence->m_npHasLightTrack.SetNumber( 1 );
// 		pCloneCfg->m_sequences.m_vectorSequence.push_back( sequence );
// 	}
// 
// 	int nVectorSequenceSize = pCloneCfg->m_sequences.m_vectorSequence.size();
// 	for( int i = 0; i < nVectorSequenceSize; i++ )
// 	{
// 		MexCfgSequence* sequence = pCloneCfg->m_sequences.m_vectorSequence[i];
// 
// 		int nFrameCount = 0;
// 		int nStartFrameID = sequence->m_npStartFrameId.GetNumber(); //动作的开始帧数
// 		int nEndFrameID = sequence->m_npEndFrameId.GetNumber(); //动作的结束帧数
// 
// 		if( pCloneMex->GetSkeleton() )
// 		{
// 			IMexBone* pBone = pCloneMex->GetSkeleton()->GetBone(0);
// 			if( pBone )
// 			{
// 				nFrameCount = pBone->GetFrameCount();
// 			}
// 		}
// 
// 		if( nFrameCount > 0 )
// 		{
// 			if( nStartFrameID > nFrameCount - 1 )
// 			{
// 				assert( "Very Terrible Error!!!!!!!!" && false );
// 				nStartFrameID = nFrameCount - 1;
// 			}
// 
// 			if( nStartFrameID < 0 )
// 			{
// 				assert( "Very Terrible Error!!!!!!!!" && false );
// 				nStartFrameID = 0;
// 			}
// 
// 			if( nEndFrameID > nFrameCount - 1 )
// 			{
// 				assert( "Very Terrible Error!!!!!!!!" && false );
// 				nEndFrameID = nFrameCount - 1;
// 			}
// 
// 			if( nEndFrameID < 0 )
// 			{
// 				assert( "Very Terrible Error!!!!!!!!" && false );
// 				nEndFrameID = 0;
// 			}
// 
// 			if( nStartFrameID > nEndFrameID )
// 			{
// 				assert( "Very Terrible Error!!!!!!!!" && false );
// 				nStartFrameID = nEndFrameID;
// 			}
// 		}
// 
// 		sequence->m_npStartFrameId.SetNumber( nStartFrameID );
// 		sequence->m_npEndFrameId.SetNumber( nEndFrameID );
// 	}
// 
// 
// 	IMexGeometry* pGeomtry = pCloneMex->GetGeometry();
// 	IMexTextures* pTextures = pCloneMex->GetTextures();
// 
// 	MexCfgAvatarSetting* pSetting = pCloneCfg->m_AvatarSettings.FindByName( DEFAULT_AVATARSETTING_NAME );
// 	if( pGeomtry )
// 	{
// 		DWORD dwFlag = eMexCfg_SubsetVisible;
// 		for( int nSubset = 0; nSubset < pGeomtry->GetChunkCount(); nSubset++  )
// 		{
// 			pSetting->m_vectorSubsetFlag.push_back( dwFlag );	
// 		}
// 	}
// 	if( pTextures )
// 	{
// 		for( int nTexture = 0; nTexture < pTextures->GetTextureCount(); nTexture++ )
// 		{
// 			MexCfgAvatarSetting::ReplaceableTexture rt;
// 			strcpy( rt.szFileName, pTextures->GetTexture(nTexture)->GetName() );
// 			pSetting->m_vectorReplaceableTexture.push_back( rt );
// 		}
// 
// 	}
	if (pMexAnim->m_bNeedInitUpperBodyAndLowerBody)
	{
		NeedInitUpperBodyAndLowerBody();
	}
	if (pMexAnim->m_bNeedInitUpperBodyAndLowerBody)
	{
		NeedInitUpperBodyAndLowerBody();
	}
	_ChangeModel( pMexAnim->GetMex(), pMexAnim->GetMexCfg(),NULL );
	m_bIsTerrainModel = IsTerrainModel;
	//MirrorX(TRUE);

	return TRUE;
}

void MexAnimCtrl::UpdateTransform()
{
	// 只适用于静态模型，无动画
// 	if( m_bAni )
// 		return;

	if( !m_pMex || !m_pMex->GetGeometry())
		return;

	MeMatrix mat;
	CalcTransformMatrix( &mat );

	DWORD dwTime = 0;
	UpdateComponents( dwTime, &mat );

	updateChildren( dwTime, &mat );


 	UpdateWorldBBox( &mat );
}

bool MexAnimCtrl::IsNeedCalcTransformMatrix()
{
	if( m_vPosition != m_vPrePosition )
		return true;

	if( m_fXRotTheta != m_vPreRotation.x
	 || m_fYRotTheta != m_vPreRotation.y
	 || m_fZRotTheta != m_vPreRotation.z )
		return true;

	if( m_fScaleX != m_vPreScale.x
	 || m_fScaleY != m_vPreScale.y
	 || m_fScaleZ != m_vPreScale.z )
		return true;

	return false;
}

void MexAnimCtrl::UpdateAsAnimComponent( DWORD dwTime, MexAnimCtrl* pBindAnim, int nBindBoneID, float* pfHelperMatrixInit,int nBoneIndex/* = 0*/ )
{
	if( !m_pMex )
	{
		return;
	}

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();
	if( !pSkeleton )
		return;

	BOOL bChangeAnim = FALSE;

	if( m_bUpperBodyAndLowerBodyMode )
	{
		DWORD dwStart = HQ_TimeGetTime();
		BOOL bFinish = FALSE;

		if( m_nNumLowerBodyPlayTask > 0 )
		{
			if( m_bLowerBodyBlending )
			{
				DWORD dwBlendingTime = dwStart - m_dwLowerBodyStartBlendingTime;
				if( dwBlendingTime > m_dwLowerBodyBlendingStep )
				{
					m_bLowerBodyBlending = FALSE;
					CheckWeaponDisplay();
				}
				else
				{
					m_fLowerBodyFactor = (float)dwBlendingTime/m_dwLowerBodyBlendingStep;
				}
			}

			if( !m_bLowerBodyBlending )
			{
				SPlayTask* pTask = &m_LowerBodyPlayTask[0];

				switch( pTask->dwPlayMode )
				{
				case eHoldOnFirstFrame:
					m_fLowerBodyFactor = 0;
					break;
				case eHoldOnLastFrame:
					m_fLowerBodyFactor = 1;
					break;
				case eSingleFrame:
					break;
				case eBlendFrame:
					break;
				case eNormalPlay:
					{
						int nLoopTimes = m_LowerBodyAnimTimeLine.GetNumLooped( dwTime );
						DWORD dwStartTime = m_LowerBodyAnimTimeLine.GetStartTime();
						if ( dwTime < dwStartTime )
						{
							nLoopTimes = 0;
						}

						if( dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
							bFinish = TRUE;

						if( dwTime > dwStartTime &&	dwTime-dwStartTime >= pTask->dwTimeOut )
							bFinish = TRUE;

						if( m_LowerBodyAnimTimeLine.IsLoopPlaying() )
						{
							m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
						}
						else
						{
							m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
							//m_fLowerBodyFactor = m_LowerBodyAnimTimeLine.GetCurPlayPercent( dwTime );
						}
						//char szBuf[256];
						//_snprintf( szBuf, 256, "UpperBodyFactor = %f LowerBodyFactor = %f", m_fUpperBodyFactor, m_fLowerBodyFactor );
						//OutputDebugString( szBuf );
					}
					break;
				}

				if( bFinish && m_nNumLowerBodyPlayTask > 1)
				{
					assert( m_nNumLowerBodyPlayTask >= 2 && "task count must >=2" );

					memcpy( &m_LowerBodyPlayTask[0], &m_LowerBodyPlayTask[1], sizeof(SPlayTask) );

					m_nNumLowerBodyPlayTask--;

					assert( m_nNumLowerBodyPlayTask > 0 && "next task is null" );

					pTask = &m_LowerBodyPlayTask[0];

					//	assert( pTask->dwTimeOut > 2000 && "second task timeout too small" );
					// 动画切换
					bChangeAnim = PlayAnim( pTask );

					switch( pTask->dwPlayMode )
					{
					case eHoldOnFirstFrame:
						m_fLowerBodyFactor = 0;
						break;
					case eHoldOnLastFrame:
						m_fLowerBodyFactor = 1;
						break;
					}
				}
			}
		}

		if( m_bUpperBodyPlayOver )
		{
			m_bUpperBodyBlending = m_bLowerBodyBlending;
			m_pSeqUpperBody = m_pSeqLowerBody;
			m_fUpperBodyFactor = m_fLowerBodyFactor;
		}
		else
		{
			bFinish = FALSE;

			if( m_nNumUpperBodyPlayTask > 0 )
			{
				if( m_bUpperBodyBlending )
				{
					DWORD dwBlendingTime = dwStart - m_dwUpperBodyStartBlendingTime;
					if( dwBlendingTime > m_dwUpperBodyBlendingStep )
					{
						m_bUpperBodyBlending = FALSE;
						CheckWeaponDisplay();
					}
					else
					{
						m_fUpperBodyFactor = (float)dwBlendingTime/m_dwUpperBodyBlendingStep;
					}
				}

				if( !m_bUpperBodyBlending )
				{
					SPlayTask* pTask = &m_UpperBodyPlayTask[0];

					switch( pTask->dwPlayMode )
					{
					case eHoldOnFirstFrame:
						m_fUpperBodyFactor = 0;
						break;
					case eHoldOnLastFrame:
						m_fUpperBodyFactor = 1;
						break;
					case eSingleFrame:
						break;
					case eBlendFrame:
						break;
					case eNormalPlay:
						{
							int nLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( dwTime );
							DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
							if ( dwTime < dwStartTime )
							{
								nLoopTimes = 0;
							}

							if( !m_bUpperBodyPlayOver && dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
							{
								m_bUpperBodyPlayOver = TRUE;
								m_bPlayingWholeBodyAnim = FALSE;
							}

							if( !m_bUpperBodyPlayOver && dwTime > dwStartTime && dwTime-dwStartTime >= pTask->dwTimeOut )
							{
								m_bUpperBodyPlayOver = TRUE;
								m_bPlayingWholeBodyAnim = FALSE;
							}

							if( m_UpperBodyAnimTimeLine.IsLoopPlaying() )
							{
								m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
							}
							else
							{
								m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetCurPlayPercent( dwTime );
							}

							//char szBuf[256];
							//_snprintf( szBuf, 256, "m_fUpperBodyFactor=%f",m_fUpperBodyFactor );
							//GetErrorLog()->logString( szBuf );

							//if( m_fUpperBodyFactor > 1 )
							//{
							//	m_pSeqUpperBody = m_pSeqLowerBody;
							//	m_fUpperBodyFactor = m_fLowerBodyFactor;
							//}
						}
						break;
					}
				}
			}

			if( m_bUpperBodyPlayOver )
			{
				if( m_bCanBlending )
				{
					m_bUpperBodyBackBlending = TRUE;
					m_dwUpperBodyStartBackBlendingTime = HQ_TimeGetTime();
				}

				if( IsIdleSequence( m_pSeqLowerBody ) )
				{
					if( m_bCanBlending )
					{
						m_bLowerBodyBackBlending = TRUE;
						m_dwLowerBodyStartBackBlendingTime = HQ_TimeGetTime();
					}
				}

				m_bUpperBodyBlending = m_bLowerBodyBlending;
				m_pSeqUpperBody = m_pSeqLowerBody;
				m_fUpperBodyFactor = m_fLowerBodyFactor;
			}
		}
	}
	else
	{
		DWORD dwStart = HQ_TimeGetTime();

		BOOL bFinish = FALSE;

		if( m_nNumPlayTask == 0 )
		{
			return;
		}

		if( m_bUpperBodyBlending )
		{
			DWORD dwBlendingTime = dwStart - m_dwUpperBodyStartBlendingTime;
			if( dwBlendingTime > m_dwUpperBodyBlendingStep )
			{
				m_bUpperBodyBlending = FALSE;
			}
			else
			{
				m_fUpperBodyFactor = (float)dwBlendingTime/m_dwUpperBodyBlendingStep;
			}
		}

		if( !m_bUpperBodyBlending )
		{
			SPlayTask* pTask = &m_PlayTasks[0];
			switch( pTask->dwPlayMode )
			{
			case eHoldOnFirstFrame:
				m_fUpperBodyFactor = 0;
				break;
			case eHoldOnLastFrame:
				m_fUpperBodyFactor = 1;
				break;
			case eSingleFrame:
				break;
			case eBlendFrame:
				break;
			case eNormalPlay:
				{
					int nLoopTimes = m_UpperBodyAnimTimeLine.GetNumLooped( dwTime );
					DWORD dwStartTime = m_UpperBodyAnimTimeLine.GetStartTime();
					if ( dwTime < dwStartTime )
					{
						nLoopTimes = 0;
					}

					if( dwTime > dwStartTime && nLoopTimes >= pTask->dwLoopTimes )
					{
						bFinish = TRUE;
					}

					if( dwTime > dwStartTime && dwTime-dwStartTime >= pTask->dwTimeOut )
					{
						bFinish = TRUE;
					}

					if( m_UpperBodyAnimTimeLine.IsLoopPlaying() )
					{
						m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetLoopPlayPercent( dwTime );
					}
					else
					{
						m_fUpperBodyFactor = m_UpperBodyAnimTimeLine.GetCurPlayPercent( dwTime );
					}
				}
				break;
			}

			// 
			if( bFinish && m_nNumPlayTask > 1 )
			{
				assert( m_nNumPlayTask >= 2 && "task count must >=2" );
				//m_vectorPlayTask.erase( m_vectorPlayTask.begin() );
				memcpy( &m_PlayTasks[0], &m_PlayTasks[1], (m_nNumPlayTask-1)*sizeof(SPlayTask) );
				m_nNumPlayTask--;

				//OnNextPlayTask();
				//assert( m_vectorPlayTask.size() > 0 && "next task is null" );
				assert( m_nNumPlayTask > 0 && "next task is null" );

				//pTask = &m_vectorPlayTask[0];
				pTask = &m_PlayTasks[0];

				assert( pTask->dwTimeOut > 2000 && "second task timeout too small" );
				bChangeAnim = PlayAnim( pTask );
				switch( pTask->dwPlayMode )
				{
				case eHoldOnFirstFrame:
					m_fUpperBodyFactor = 0;
					break;
				case eHoldOnLastFrame:
					m_fUpperBodyFactor = 1;
					break;
				}
			}
		}
	}

	int nBoneCount = pSkeleton->GetBoneCount();

	m_fCurUpperBodyFrame = m_pSeqUpperBody->GetBlendFrame( m_fUpperBodyFactor );
	m_nFrameId = m_fCurUpperBodyFrame/ONEFRAMEINTERVAL;
	//     m_pMex->SetFrameId( m_nFrameId );

	BOOL bNewKeyFrameFormat = (((Mex2*)GetMex())->GetVersion() >= 108 && !((Mex2Skeleton*)pSkeleton)->m_bSpecialModel);
	for( int i = nBoneIndex; i < nBoneCount; i++ )
	{
		IMexBone* pBone = pSkeleton->GetBone(i);

		// 经过这段运算,模型已经在自己的空间中带有了动作,
		// 每个点都变换到模型空间中，
		if( pBone->HasKeyFrame() && bNewKeyFrameFormat )
		{
			float* pMatrix = NULL;
			if( pBone->GetParentId() >= 0 )
			{
				BOOL bGetParentMat = CanGetBoneMatricesBackupAtTime(m_fCurUpperBodyFrame, pBone->GetParentId());
				if( bGetParentMat )
					pMatrix = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame, FRAMEPERSEC, (float*)&m_amatBoneMatricesFromKeyTime[pBone->GetParentId()]);
				else
					pMatrix = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame, FRAMEPERSEC);
				SetBoneMatricesAtTime(m_fCurUpperBodyFrame, i, pMatrix);
			}
			else
				pMatrix = pBone->GetMatricesFromKeyTime(m_fCurUpperBodyFrame, FRAMEPERSEC);

			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_matSrcBones[i], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pMatrix );
		}
		else
			D3DXMatrixMultiply(
				(D3DXMATRIX*)&m_matSrcBones[i], 
				(D3DXMATRIX*)pBone->GetFrame0Inv(),
				(D3DXMATRIX*)pBone->GetMatrices(m_nFrameId) );

// 		memcpy( &m_matSrcBones[i], &m_amatBoneInWorldSpace[i], sizeof(MeMatrix) );

		// 我们进入父模型空间中，
		// 接下来，我们需要把自己从原点变换到helper上，
		// 例如一把刀需要放到角色的手上去，
		D3DXMatrixMultiply(
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[i], 
			(D3DXMATRIX*)&m_matSrcBones[i],
			(D3DXMATRIX*)pfHelperMatrixInit );

		memcpy( &m_amatBoneInModelSpace[i], &m_amatBoneInWorldSpace[i], sizeof(MeMatrix) );
		// 放到父模型空间后,就和普通的模型一样转换
		D3DXMatrixMultiply(
			(D3DXMATRIX*)&m_amatBoneInModelSpace[i], 
			(D3DXMATRIX*)&m_amatBoneInModelSpace[i],
			(D3DXMATRIX*)&pBindAnim->GetBoneMatrices()[nBindBoneID] );


		// 放到父模型空间后,就和普通的模型一样转换
		D3DXMatrixMultiply(
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[i], 
			(D3DXMATRIX*)&m_amatBoneInWorldSpace[i],
			(D3DXMATRIX*)&pBindAnim->GetMatrices()[nBindBoneID] );

	}

	D3DXMatrixMultiply( (D3DXMATRIX*)&m_matModel, 
		(D3DXMATRIX*)pfHelperMatrixInit, 
		(D3DXMATRIX*)&pBindAnim->GetMatrices()[nBindBoneID] );

	//m_matModel = pBindAnim->m_matModel;
	//m_matModelInv = pBindAnim->m_matModelInv;
	UpdateEffects( dwTime, (float*)m_matSrcBones, (float*)&m_matModel );
}

void MexAnimCtrl::UpdateFollowParent(DWORD dwTime, MexAnimCtrl *pParent, const char *szBindBone)
{
	assert(pParent != NULL);

	IMexSkeleton *skeleton = pParent->GetMex()->GetSkeleton();
	assert(skeleton != NULL);

	int nAttachBone = skeleton->FindBone(szBindBone);
	Mex2Bone *attachBone = (Mex2Bone *) skeleton->GetBone(nAttachBone);
	if (attachBone != NULL)
	{
		D3DXMATRIX matInit;
		D3DXMatrixInverse(&matInit, NULL, (D3DXMATRIX*) attachBone->GetFrame0Inv());

		D3DXMATRIX matTemp;
		D3DXMatrixIdentity(&matTemp);
		matTemp._41 = matInit._41; matTemp._42 = matInit._42; matTemp._43 = matInit._43;
		UpdateAsAnimComponent(dwTime, pParent, nAttachBone, (float *) &matTemp);
	}
}

extern void MakeMatrix( Vector& v, Quaternion& q, MeMatrix& m );
float* MexAnimCtrl::GetKeyFrameBlendedMatrices( IMexBone* pBone, float t, float fKeyTime0, float fKeyTime1, int nFps,
											   BOOL bIsLastBlend/* = FALSE*/,
											   Vector* pLastBlendTrans/* = NULL*/,
											   Quaternion* pLastBlendQuats/* = NULL*/ )
{
	if( !pBone )
		return NULL;

	Mex2Skeleton *pSkeleton = (Mex2Skeleton*)m_pMex->GetSkeleton();
	if( ((Mex2*)GetMex())->GetVersion() < 108 || pSkeleton->m_bSpecialModel || ((Mex2Bone*)pBone)->m_bFullFrame )
	{
		return pBone->GetBlendedMatrices( t, fKeyTime0, fKeyTime1, nFps, bIsLastBlend, pLastBlendTrans, pLastBlendQuats );
	}

	// 版本 >= 108，新关键帧机制
	static MeMatrix m;

	if( nFps <= 0 )
		nFps = 1;

	Mex2Bone* pMex2Bone = (Mex2Bone*)pBone;
	if( !pMex2Bone->GetTrack() )
	{
		assert(0);
		return NULL;
	}


	Vector v0, v1;
	Quaternion q0, q1;
	// 上一个动作是否blend状态
	if( !bIsLastBlend || pLastBlendTrans == NULL || pLastBlendQuats == NULL
		||( pLastBlendTrans->positionEquals(Vector(0,0,0)) && pLastBlendQuats->equals(Quaternion(0,0,0,0)) ))
	{
		// 计算fKeyTime0骨骼矩阵

		// 父骨骼矩阵
		BOOL bHasParent = FALSE;
		MeMatrix mParentMat;
		if( pMex2Bone->GetParentId() >=0 )	
		{
			bHasParent = TRUE;
			BOOL bGetParentMat = FALSE;
			float* pMatrix = NULL;

			bGetParentMat = CanGetBoneMatricesBackupAtTime(fKeyTime0, pMex2Bone->GetParentId());
			if( bGetParentMat )
			{
				memcpy( &mParentMat, &m_amatBoneMatricesFromKeyTime[pMex2Bone->GetParentId()], sizeof(MeMatrix));
			}
			else
			{
				IMexBone* pParentBone = pSkeleton->GetBone(pMex2Bone->GetParentId());
				float* mParent = pParentBone->GetMatricesFromKeyTime(fKeyTime0, nFps);

				if( mParent )
				{
					SetBoneMatricesAtTime(fKeyTime0, pMex2Bone->GetParentId(), mParent);	// 保存parent矩阵
					memcpy( &mParentMat, mParent, sizeof(MeMatrix) );
				}
			}
		}

		float* pmat = NULL;
		MeMatrix mat;
		pmat = pMex2Bone->GetMatricesFromKeyTime(fKeyTime0, nFps, (float*)&mParentMat);
		memcpy(&mat, pmat, sizeof(MeMatrix));
		ConvertMatrixToTranslationAndRotation(mat, v0, q0);
	}
	else if( pLastBlendTrans && pLastBlendQuats )
	{
		v0 = *pLastBlendTrans;
		q0 = *pLastBlendQuats;
	}

	// 计算fKeyTime1骨骼矩阵

	// 父骨骼矩阵
	BOOL bHasParent = FALSE;
	MeMatrix mParentMat;
	if( pMex2Bone->GetParentId() >=0 )	
	{
		bHasParent = TRUE;
		BOOL bGetParentMat = FALSE;
		float* pMatrix = NULL;

		bGetParentMat = CanGetBoneMatricesAtTargetTime(fKeyTime1, pMex2Bone->GetParentId());
		if( bGetParentMat )
		{
			memcpy( &mParentMat, &m_amatBoneMatricesTargetKeyTime[pMex2Bone->GetParentId()], sizeof(MeMatrix));
		}
		else
		{
			IMexBone* pParentBone = pSkeleton->GetBone(pMex2Bone->GetParentId());
			float* mParent = pParentBone->GetMatricesFromKeyTime(fKeyTime1, nFps);

			if( mParent )
			{
				SetBoneMatricesAtTargetTime(fKeyTime1, pMex2Bone->GetParentId(), mParent);	// 保存parent矩阵
				memcpy( &mParentMat, mParent, sizeof(MeMatrix) );
			}
		}
	}

	float* pmat = NULL;
	MeMatrix mat;
	pmat = pMex2Bone->GetMatricesFromKeyTime(fKeyTime1, nFps, (float*)&mParentMat);
	memcpy(&mat, pmat, sizeof(MeMatrix));
	ConvertMatrixToTranslationAndRotation(mat, v1, q1);

	// 插值
	v0 = v0+t*(v1-v0);

	if( FloatCmp( q0.x, q1.x ) == 0 &&
		FloatCmp( q0.y, q1.y ) == 0 &&
		FloatCmp( q0.z, q1.z ) == 0 &&
		FloatCmp( q0.w, q1.w ) == 0)
	{
	}
	else
		q0.blend( t, q1 );
	MakeMatrix( v0, q0, m );

	// 解决blend过程中切动画
	if( !bIsLastBlend )
	{
		if( pLastBlendTrans )
			*pLastBlendTrans = v0;
		if( pLastBlendQuats )
			*pLastBlendQuats = q0;
	}

	return (float*)&m;
}

BOOL MexAnimCtrl::CanGetBoneMatricesBackupAtTime(float time, int boneid)
{
	if( boneid < 0 || time < 0 )
		return FALSE;

	float fInterval = 1000.0f/FRAMEPERSEC;
	int nFrame = (int)(time/fInterval/*+0.001f*/);

	if( m_pKeyTimeOfBoneMatrices && m_amatBoneMatricesFromKeyTime )
	{
		if( m_pKeyTimeOfBoneMatrices[boneid] >= 0 && nFrame == m_pKeyTimeOfBoneMatrices[boneid] )
			return TRUE;
	}
	return FALSE;
}

void MexAnimCtrl::SetBoneMatricesAtTime(float time, int boneid, const float* mat)
{
	if( boneid < 0 || time < 0 || !mat )
		return;

	if( m_pKeyTimeOfBoneMatrices && m_amatBoneMatricesFromKeyTime )
	{
		float fInterval = 1000.0f/FRAMEPERSEC;
		int nFrame = (int)(time/fInterval/*+0.001f*/);

		memcpy( &m_amatBoneMatricesFromKeyTime[boneid], mat, sizeof(MeMatrix) );
		m_pKeyTimeOfBoneMatrices[boneid] = nFrame;
	}
}

BOOL MexAnimCtrl::CanGetBoneMatricesAtTargetTime(float time, int boneid)
{
	if( boneid < 0 || time < 0 )
		return FALSE;

	float fInterval = 1000.0f/FRAMEPERSEC;
	int nFrame = (int)(time/fInterval/*+0.001f*/);

	if( m_pTargetKeyTimeOfBoneMatrices && m_amatBoneMatricesTargetKeyTime )
	{
		if( m_pTargetKeyTimeOfBoneMatrices[boneid] >= 0 && nFrame == m_pTargetKeyTimeOfBoneMatrices[boneid] )
			return TRUE;
	}
	return FALSE;
}

void MexAnimCtrl::SetBoneMatricesAtTargetTime(float time, int boneid, const float* mat)
{
	if( boneid < 0 || time < 0 || !mat )
		return;

	if( m_pTargetKeyTimeOfBoneMatrices && m_amatBoneMatricesTargetKeyTime )
	{
		float fInterval = 1000.0f/FRAMEPERSEC;
		int nFrame = (int)(time/fInterval/*+0.001f*/);

		memcpy( &m_amatBoneMatricesTargetKeyTime[boneid], mat, sizeof(MeMatrix) );
		m_pTargetKeyTimeOfBoneMatrices[boneid] = nFrame;
	}
}
//--------------------------------------------------------
IDirect3DVertexDeclaration9 *MexInstanceMan::ms_pVertexDeclHardware = 0;
D3DXHANDLE MexInstanceMan::ms_HandleTechnique;
D3DVERTEXELEMENT9 MexInstanceMan::ms_VertexElemHardware[8] = {
	{ 0, 0,     D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION,  0 },
	{ 1, 0, D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,    0 },
	{ 2, 0, D3DDECLTYPE_D3DCOLOR,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_COLOR,  0 },
	{ 3, 0, D3DDECLTYPE_FLOAT2,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,  0 },
 	{ 4, 0,     D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_COLOR,     1 },
	{ 4, 4 * 4, D3DDECLTYPE_FLOAT1,	  D3DDECLMETHOD_DEFAULT,   D3DDECLUSAGE_COLOR,    2 },
	{ 4, 5 * 4, D3DDECLTYPE_FLOAT1,	  D3DDECLMETHOD_DEFAULT,   D3DDECLUSAGE_COLOR,    3 },
	D3DDECL_END()
};
D3DXHANDLE MexInstanceMan::ms_HandleWorld;
D3DXHANDLE MexInstanceMan::ms_HandleView;
D3DXHANDLE MexInstanceMan::ms_HandleProjection;
D3DXHANDLE MexInstanceMan::ms_HandleTexture;
ID3DXEffect* MexInstanceMan::ms_pEffect = 0;
LPDIRECT3DDEVICE9 MexInstanceMan::ms_pd3dDevice = 0;
bool MexInstanceMan::ms_bDynamicGrass = true;
//--------------------------------------------------------
void MexInstanceMan::GlobalInitialize(char* pszShaderFile)
{	
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	pd3dDevice->CreateVertexDeclaration( ms_VertexElemHardware, &ms_pVertexDeclHardware );
	//create effect
	if(FAILED(D3DXCreateEffectFromFile( pd3dDevice, pszShaderFile, NULL, NULL, D3DXFX_NOT_CLONEABLE, 
		NULL, &ms_pEffect, NULL )))
	{
// 		FILE	* fp = fopen(pszShaderFile,"rb");
// 		if (!fp)
		char * pData=NULL;size_t nSize;
		nSize=packet_namespace::LoadFile(pszShaderFile,pData,0);
		if(nSize<=0)
		{
			delete [] pData;
			return ;
		}
		HRESULT hr = D3DXCreateEffect( pd3dDevice, pData,nSize,//(LPCVOID)fp->_base,fp->_bufsiz,
			NULL, NULL, D3DXFX_NOT_CLONEABLE, 
			NULL, &ms_pEffect, NULL );
		delete [] pData;
	//	fclose(fp);
	}
	//assign handls
	ms_HandleTechnique = ms_pEffect->GetTechniqueByName( "THW_Instancing" );
	ms_HandleWorld = ms_pEffect->GetParameterBySemantic( NULL, "WORLD" );
	ms_HandleView = ms_pEffect->GetParameterBySemantic( NULL, "VIEW" );
	ms_HandleProjection = ms_pEffect->GetParameterBySemantic( NULL, "PROJECTION" );
	ms_HandleTexture = ms_pEffect->GetParameterBySemantic( NULL, "TEXTURE" );
	ms_pEffect->SetTechnique( ms_HandleTechnique );

	//set d3d device
	ms_pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	ms_bDynamicGrass = 1;

}
void MexInstanceMan::GlobalDestroy()
{
	if(ms_pEffect)
	{
		ms_pEffect->Release();
		ms_pEffect = 0;
	}
	if(ms_pVertexDeclHardware)
	{
		ms_pVertexDeclHardware->Release();
		ms_pVertexDeclHardware = 0;
	}	
}
void MexInstanceMan::OnResetDevice()
{
    if(ms_pEffect)
    {
        ms_pEffect->OnResetDevice();
    }
	ms_pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
}
void MexInstanceMan::OnLostDevice()
{
    if(ms_pEffect)
    {
        ms_pEffect->OnLostDevice();
    }
	ms_pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
}
//--------------------------------------------------------
MexInstanceMan::MexInstanceMan() :
m_pIPos(0),
m_pVBInstanceData(0),
m_nMaxInstance(-1),
// m_mex(0),
m_nCurrentInstance(-1)
{	
	memset( m_RenderObject, 0, ms_nRenderObjectTotal * sizeof( InstanceRenderObject ) );
}
//--------------------------------------------------------
MexInstanceMan::~MexInstanceMan()
{	
	if(m_pVBInstanceData)
	{
		m_pVBInstanceData->Release();
		m_pVBInstanceData = 0;
	}
}
//--------------------------------------------------------
HRESULT MexInstanceMan::EnableInstance(MexAnimCtrl* pkMexAnimCtrl, int nMaxInstance)
{
	if(m_pVBInstanceData /*&& m_mex*/)
		return 0;

	if(nMaxInstance == m_nMaxInstance)
		return 1;

	if( pkMexAnimCtrl == NULL )
		return -1;

	if( ms_pd3dDevice == NULL )
		return -1;
	
	HRESULT hr = ms_pd3dDevice->CreateVertexBuffer( 
		nMaxInstance * sizeof( CMexInstanceObject::InstanceVertexData ),
		0, 0, D3DPOOL_MANAGED, &m_pVBInstanceData, 0 );
	//set max instance number
	m_nMaxInstance = nMaxInstance;
	//set mex pointer
	Mex2* pMex = (Mex2*)pkMexAnimCtrl->GetMex();
	if( !pMex )
		return -1;

	int nIndex = 0;
	assert( pMex && "instance's mex is null");
	for(int i = 0 ; i < pMex->GetGeometry()->GetChunkCount(); ++i)
	{
		InstanceRenderObject object;
		//get the texture
		MexReplaceableTextureProj* replaceableTex = 
			(MexReplaceableTextureProj*)pkMexAnimCtrl->GetReplaceableTextureProj();		

		ITexture* pTexture = GetEngine()->GetTextureManager()->
			GetTextureNoLock( replaceableTex->GetRenderTextureID(i) );

		if(pTexture && pTexture->GetData())
			object.m_pTexture = (IDirect3DTexture9*)pTexture->GetData();
		else
		{
			//LOG_MESSAGE( "GrassError.log", LOG_PRIORITY_WARNING, "Cannot Find Textures Of %s", pMex->GetFilename() );
			return -1;
		}
		
		//set vertex&index count
		Mex2GeoChunk* pObject = (Mex2GeoChunk*)pMex->GetGeometry()->GetChunk(i);
//  		pObject->InitInstance();
		object.m_pGeoChunk = pObject;
		object.m_nVertexCount = pObject->GetVertexCount();
		object.m_nIndexCount = pObject->GetFaceCount();
		m_RenderObject[nIndex++] = object;		
	}
	if (nIndex != 0 )
	{
		m_nCurrentInstance = 0;
	}

	return hr;
}
//--------------------------------------------------------
void MexInstanceMan::DisableInstance()
{
	if(m_pVBInstanceData)
	{
		m_pVBInstanceData->Release();
		m_pVBInstanceData = 0;
	}
// 	m_mex = 0;
	m_nMaxInstance = -1;
	m_nCurrentInstance = -1;
	ZeroMemory( m_RenderObject, sizeof(InstanceRenderObject) * ms_nRenderObjectTotal);
}
//--------------------------------------------------------
void MexInstanceMan::AddInstance(CMexInstanceObject& instance)
{
	*m_pIPos = instance.GetInstanceData();
	m_pIPos++;
	m_nCurrentInstance++;
}
//--------------------------------------------------------
HRESULT MexInstanceMan::Lock()
{
	HRESULT hr = m_pVBInstanceData->Lock( 0, NULL,  (void**) &m_pIPos, 0 );
	return hr;
}
//--------------------------------------------------------
HRESULT MexInstanceMan::Unlock()
{
	HRESULT hr = m_pVBInstanceData->Unlock();
	return hr;
}
//--------------------------------------------------------
void MexInstanceMan::BeginRender()
{	
	RendererDx* pRender = (RendererDx*)GetEngine()->GetRenderer();
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	ms_pEffect->SetMatrix( ms_HandleWorld, &/*pRender->GetWorldMatrix()*/matWorld);
	ms_pEffect->SetMatrix( ms_HandleView, &pRender->GetViewMatrix());
	ms_pEffect->SetMatrix( ms_HandleProjection, &pRender->GetProjectMatrix());
	ms_pEffect->SetValue( "LightDirection", &pRender->GetLightDir(LIGHT_INDEX_TERRAIN), sizeof(D3DXVECTOR3) );
	ms_pEffect->SetValue( "LightAmbientColor", &pRender->GetLightAmbient(LIGHT_INDEX_TERRAIN), sizeof(D3DXCOLOR) );
	ms_pEffect->SetValue( "LightDiffuseColor", &pRender->GetLightDiffuse(LIGHT_INDEX_TERRAIN), sizeof(D3DXCOLOR) );
	ms_pEffect->SetValue( "LightSpecularColor", &pRender->GetLightSpecular(LIGHT_INDEX_TERRAIN), sizeof(D3DXCOLOR) );
	ms_pEffect->SetFloat( "g_FarPlane", Config::GetCamera()->GetFarPlane() );
	//ms_pEffect->SetValue( "g_vEyePt", &pRender->GetEyePt(), sizeof(D3DXVECTOR3));
	char szTechName[20];
	sprintf_s( szTechName, 20, "%s%s", "THW_Instancing", pRender->GetCurrentShaderLevelName() );
	ms_pEffect->SetTechnique( szTechName ) ;
	ms_pd3dDevice->SetVertexDeclaration( ms_pVertexDeclHardware );
	UINT cPasses;
	ms_pEffect->Begin( &cPasses, 0 ) ;
	ms_pEffect->BeginPass(0);
}
//--------------------------------------------------------
void MexInstanceMan::SetPlayerPos(D3DXVECTOR3* vPos)
{
	RendererDx* pRender = (RendererDx*)GetEngine()->GetRenderer();
	if(ms_pEffect && ms_bDynamicGrass)
		ms_pEffect->SetValue("g_PlayerPos", vPos, sizeof(D3DXVECTOR3));
}

bool MexInstanceMan::BeginMyRender(int nIndex,DWORD dwFlag)
{
// 	if( !m_mex )
// 		return;

	if (m_nCurrentInstance == -1 )
	{
		return false;
	}
	ms_pd3dDevice->SetStreamSource( 0 , m_RenderObject[nIndex].m_pGeoChunk->GetVerticesBuffer(), 0, 3*4);
	ms_pd3dDevice->SetStreamSource( 1 , m_RenderObject[nIndex].m_pGeoChunk->GetNormalsBuffer(), 0, 3*4);
	ms_pd3dDevice->SetStreamSource( 2 , m_RenderObject[nIndex].m_pGeoChunk->GetDiffusesBuffer(), 0, 4);
	ms_pd3dDevice->SetStreamSource( 3 , m_RenderObject[nIndex].m_pGeoChunk->GetUvsBuffer(), 0, 2*4);
	ms_pd3dDevice->SetIndices( m_RenderObject[nIndex].m_pGeoChunk->GetIB() );
	ms_pd3dDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	if( dwFlag & eDstBlendOne )
	{
		ms_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	}
	//set the texture					
	ms_pEffect->SetTexture( ms_HandleTexture, m_RenderObject[nIndex].m_pTexture );
	ms_pd3dDevice->SetStreamSourceFreq( 4, D3DSTREAMSOURCE_INSTANCEDATA | 1ul ) ;
	ms_pEffect->CommitChanges() ;
	return true;
}

void MexInstanceMan::DoMyRender(int nIndex)
{
	if( /*!m_mex ||*/ m_nCurrentInstance == -1)
		return;

	ms_pd3dDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | m_nCurrentInstance) ;
	// Stream one is the instancing buffer, so this advances to the next value
	// after each box instance has been drawn, so the divider is 1.
	ms_pd3dDevice->SetStreamSource( 4, m_pVBInstanceData, 0, sizeof( CMexInstanceObject::InstanceVertexData ) ) ;

	ms_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_RenderObject[nIndex].m_nVertexCount, 0, m_RenderObject[nIndex].m_nIndexCount ) ;
}

//--------------------------------------------------------
// void MexInstanceMan::Render()
// {
// 	if( !m_mex || m_nCurrentInstance == -1)
// 		return;
// 	RendererDx* pRender = (RendererDx*)GetEngine()->GetRenderer();
// 	//static LPDIRECT3DVERTEXDECLARATION9 s_oldDecl;
// 	//m_pd3dDevice->GetVertexDeclaration(&s_oldDecl);
// 	
// 
// 	//Mex2GeoChunk* pObject = (Mex2GeoChunk*)m_mex->GetGeometry()->GetChunk(0);
// 	//m_pd3dDevice->SetStreamSource( 0, pObject->GetVB(), 0, sizeof(MexVertex)) ;
// 	ms_pd3dDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | m_nCurrentInstance) ;
// 
// 	// Stream one is the instancing buffer, so this advances to the next value
// 	// after each box instance has been drawn, so the divider is 1.
// 	ms_pd3dDevice->SetStreamSource( 4, m_pVBInstanceData, 0, sizeof( CMexInstanceObject::InstanceVertexData ) ) ;
// 	ms_pd3dDevice->SetStreamSourceFreq( 4, D3DSTREAMSOURCE_INSTANCEDATA | 1ul ) ;
// 	//m_pd3dDevice->SetIndices( pObject->GetIB() ) ;
// 
// 	for( int i = 0 ; i < m_mex->GetGeometry()->GetChunkCount(); ++ i)
// 	{
// 		ms_pd3dDevice->SetStreamSource( 0 , m_RenderObject[i].m_pGeoChunk->GetVerticesBuffer(), 0, 3*4);
// 		ms_pd3dDevice->SetStreamSource( 1 , m_RenderObject[i].m_pGeoChunk->GetNormalsBuffer(), 0, 3*4);
// 		ms_pd3dDevice->SetStreamSource( 2 , m_RenderObject[i].m_pGeoChunk->GetDiffusesBuffer(), 0, 4);
// 		ms_pd3dDevice->SetStreamSource( 3 , m_RenderObject[i].m_pGeoChunk->GetUvsBuffer(), 0, 2*4);
// 		ms_pd3dDevice->SetIndices( m_RenderObject[i].m_pGeoChunk->GetIB() );
// 		//set the texture					
// 		ms_pEffect->SetTexture( ms_HandleTexture, m_RenderObject[i].m_pTexture );
// 		ms_pEffect->CommitChanges() ;
// 
// 		ms_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_RenderObject[i].m_nVertexCount, 0, m_RenderObject[i].m_nIndexCount ) ;
// 	}		
// 
//  	//m_pd3dDevice->SetVertexDeclaration( s_oldDecl );;
// // 	m_pd3dDevice->SetStreamSource(0,0,0,0);
// // 	m_pd3dDevice->SetStreamSource(1,0,0,0);
// // 	m_pd3dDevice->SetIndices(0);
// 	ms_pd3dDevice->SetStreamSourceFreq( 0, 1 );
// 	ms_pd3dDevice->SetStreamSourceFreq( 4, 1 );
// }
//--------------------------------------------------------
void MexInstanceMan::EndRender()
{
	ms_pd3dDevice->SetStreamSourceFreq( 0, 1 );
	ms_pd3dDevice->SetStreamSourceFreq( 4, 1 );
	ms_pEffect->EndPass() ;
	ms_pEffect->End() ;

}