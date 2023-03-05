#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include <windows.h>
#include <assert.h>
#include "Me3d/include.h"
#include "Me3d/AnimTimeLine.h"
#include "Me3d/Model/MexConfig.h"
//#include "Me3d/Model/stdcharskeleton.h"
#include "Me3d/Model/mtlanim.h"
#include "Me3d/MathLib.h"
#include "Me3d/Model/MexRes.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/effect/MexEffectCtrl.h"
#include "FuncPerformanceLog.h"
#include "Me3d/engine/Engine.h"
#include "FilePath.h"
//#include "Me3d/Model/Avatar.h"
#include "Dxsdk/d3d9types.h"

extern int GetVertexStride( DWORD dwFvf );
//////////////////////////////////////////////////////////////////////////
CMexEffectCtrl::CMexEffectCtrl():
m_nFrameCount(0),
m_pMex( NULL ),
m_pMexCfg( NULL ),
m_pSequence( NULL ),
m_nFrameId( 0 ),
m_nModelId(-1),
m_pAvatarSetting(NULL),
m_nNumPlayTask(0),
m_matrices(NULL),
m_matBones(NULL),
m_matSrcBones(NULL)
{
	guardfunc;
	int i = 0;

	for( i = 0; i < eMaxParticleEmitter; i++ )
	{
		m_pParticleEmitters[i] = NULL;
	}
	for( i = 0; i < eMaxRibbonEmitter; i++ )
	{
		m_pRibbonEmitters[i] = NULL;
	}

	m_timeLine.Reset();

	m_vPosition = Vector( 0, 0, 0 );
	m_fRotTheta = 0;
	m_fXRotTheta = 0;
	m_fScale = 1.0f;
	unguard;
}

CMexEffectCtrl::~CMexEffectCtrl()
{
	guardfunc;
	for ( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if ( m_pParticleEmitters[i] != NULL )
		{
			assert( false && "mex anim ctrl, particle emitter not release" );
		}
	}
	for ( int i = 0; i < eMaxRibbonEmitter; i++ )
	{
		if ( m_pRibbonEmitters[i] != NULL )
		{
			assert( false && "mex anim ctrl, ribbon emitter not release" );
		}
	}
	unguard;
}

void CMexEffectCtrl::Destroy()
{
	guardfunc;
	if( m_pAvatarSetting )
	{
		CloseAvatarSetting( m_pAvatarSetting );
		m_pAvatarSetting = NULL;
	}
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->Release();
			m_pParticleEmitters[i] = NULL;
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

	ReleaseLastModel();
	if( m_matrices )
	{
		delete[] m_matrices;
		m_matrices = NULL;
		m_matSrcBones = NULL;
		m_matBones = NULL;
	}
	m_pMex		= NULL;
	m_pMexCfg	= NULL;
	unguard;
}


DWORD CMexEffectCtrl::GetAnimTimeLength( const char* pszActionname )
{
	guardfunc;
	if( !m_pMexCfg )
	{
		assert( false && "get anim time length MEX cfg is NULL" );
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

void CMexEffectCtrl::ResetPlayTask( SPlayTask* pTask )
{
	guardfunc;
	strcpy( pTask->szActionname, "idle" );
	pTask->dwTimeOut = eMaxTimeout;
	pTask->dwStartTime = 0;
	pTask->dwPlayMode = eNormalPlay;
	pTask->dwOneLoopTime = 0;
	pTask->dwLoopTimes = eMaxLoopTimes;
	pTask->dwNeedBlendingTime = 0;
	unguard;
}

void CMexEffectCtrl::ClearAnims()
{
	guardfunc;
	m_nNumPlayTask = 0;
	m_nFrameId = 0;
	m_pSequence = NULL;
	unguard;
}

void CMexEffectCtrl::SetMex( IMex* pMex, MexCfg* pMexCfg )
{
	guardfunc;
	guard( test1 );
	m_pMex = pMex;
	m_pMexCfg = pMexCfg;
	if( !m_pMex || !m_pMexCfg )
	{
		return;
	}
	unguard;

	//if( m_pMex->GetSequences()->GetSequenceCount() == 0 )
	//{
	//	return;
	//}

	ChangeAvatarSetting( DEFAULT_AVATARSETTING_NAME );

	guard( test2 );
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->Release();
			m_pParticleEmitters[i] = NULL;
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
			}
		}
	}
	unguard;

	m_nFrameId = 0;
	//ClearAnims();
	//PushAnim( NULL );
	unguard;
}

BOOL CMexEffectCtrl::ChangeAvatarSetting( const char* pszName )
{
	guardfunc;
	if( !pszName || !m_pMexCfg )
	{
		return FALSE;
	}

	if( m_pAvatarSetting )
	{
		CloseAvatarSetting( m_pAvatarSetting );
		m_pAvatarSetting = NULL;
	}

	m_pAvatarSetting = m_pMexCfg->m_AvatarSettings.FindByName( pszName );

	if( !m_pAvatarSetting )
	{
		return FALSE;
	}

	m_ReplaceableTextureProj.SetTextureCount( m_pAvatarSetting->m_vectorReplaceableTexture.size() );

	for( int nTexture = 0; nTexture < m_pAvatarSetting->m_vectorReplaceableTexture.size(); nTexture++ )
	{
		MexCfgAvatarSetting::ReplaceableTexture* rt = &m_pAvatarSetting->m_vectorReplaceableTexture[nTexture];
		int nRenderTextureID = m_ReplaceableTextureProj.RegisterTexture( m_pMex->GetFilename(), rt->szFileName, TRUE );
		m_ReplaceableTextureProj.SetRenderTextureID( nTexture, nRenderTextureID );
	}

	m_ReplaceableTextureProj.Loaded( TRUE );

	return TRUE;
	unguard;
}

BOOL CMexEffectCtrl::CloseAvatarSetting( MexCfgAvatarSetting* pSetting )
{
	guardfunc;
	if( !pSetting )
	{
		return FALSE;
	}

	if( !m_ReplaceableTextureProj.IsLoaded() )
	{
		return TRUE;
	}

	m_ReplaceableTextureProj.UnRegisterTextures();
	m_ReplaceableTextureProj.Loaded( FALSE );
	return TRUE;
	unguard;
}

void CMexEffectCtrl::PushAnim( SPlayTask* pTask )
{
	guardfunc;
	if( !pTask )
	{
		SPlayTask task;
		ResetPlayTask( &task );
		task.dwOneLoopTime = 0;
		task.dwStartTime = HQ_TimeGetTime();
		task.dwNeedBlendingTime=0;
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
	unguard;
}


int CMexEffectCtrl::GetFrameCount()
{
	guardfunc;
	return m_nFrameCount;
	unguard;
}

BOOL CMexEffectCtrl::PlayAnim( const char* pszActionname, DWORD dwOneLoopTime )
{
	guardfunc;
	SPlayTask task;
	ResetPlayTask( &task );
	strcpy( task.szActionname, pszActionname );
	task.dwOneLoopTime = dwOneLoopTime;
	task.dwStartTime = HQ_TimeGetTime();
	ClearAnims();
	PushAnim( &task );
	return TRUE;
	unguard;
}

BOOL CMexEffectCtrl::PlayAnim( int nStartFrameID, int nEndFrameID, DWORD dwOneLoopTime )
{
	guardfunc;
	m_TmpSequence.m_npStartFrameId.SetNumber( nStartFrameID );
	m_TmpSequence.m_npEndFrameId.SetNumber( nEndFrameID );
	m_TmpSequence.m_spAnimName.SetString( "temp2006" );
	m_TmpSequence.m_npHasLightTrack.SetNumber( 1 );
	PlayAnim( "temp2006", dwOneLoopTime );
	return FALSE;
	unguard;
}

BOOL CMexEffectCtrl::PlayAnim( SPlayTask* pTask )
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

	//   added 2004.09.25
	MexCfgSequence* pNewSequence = m_pMexCfg->GetSequence( pTask->szActionname );
	if( !pNewSequence )
		pNewSequence = &m_TmpSequence;

	//char szBuf[256];
	//_snprintf( szBuf, 256, "pNewSequence = %s time = %d", pNewSequence->m_spAnimName.GetString(), pTask->dwOneLoopTime );
	//OutputDebugString( szBuf );
	//m_pSequence = pNewSequence;

	int nHitPoint = -1;

	{
		m_pSequence = pNewSequence;

		if( m_pSequence == NULL )
		{
			m_pSequence = m_pMexCfg->m_sequences.m_vectorSequence[0];
		}

		m_nStartFrameId = pNewSequence->m_npStartFrameId.GetNumber();
		m_nEndFrameId = pNewSequence->m_npEndFrameId.GetNumber();
	}

	//assert( nFrameCount > 0 && "frame count must > 0" );

	if( pTask->dwOneLoopTime == 0 )
	{
		nFrameCount = m_nEndFrameId-m_nStartFrameId+1;
		m_dwOneLoopTime = nFrameCount*ONEFRAMEINTERVAL;
	}
	else
	{
		m_dwOneLoopTime = pTask->dwOneLoopTime;
	}

	{
		m_timeLine.Reset();
		m_timeLine.Play( 
			HQ_TimeGetTime() + eDefaultBlendingTime,
			m_nStartFrameId,
			m_nEndFrameId,
			-1,
			m_dwOneLoopTime );


		if( pTask->bLoopPlay )
		{
			m_timeLine.SetLoopPlay();
		}

	}

	//if( pTask->dwPlayMode == MexAnimCtrl::eHoldOnLastFrame )
	//	m_nFrameId = m_nEndFrameId;
	//else
	//	m_nFrameId = m_nStartFrameId;

	m_nLoopTimes = 0;
	return TRUE;
	unguard;
}

//BOOL IsParentBone( IMexSkeleton* pSkeleton, int nTryBoneID, int nBoneID )
//{
//	if( nTryBoneID == nBoneID )
//		return FALSE;
//	IMexBone* pBone = pSkeleton->GetBone( nBoneID );
//	int nParentID = pBone->GetParentId();
//	if( nParentID == -1 )
//		return FALSE;
//	if( nParentID == nTryBoneID )
//		return TRUE;
//	return IsParentBone( pSkeleton, nTryBoneID, nParentID );
//
//}

void CMexEffectCtrl::UpdateComponents( DWORD dwTime, MeMatrix* pMatrix )
{
	guardfunc;

	guard(test1);
	if( !m_matrices || !pMatrix || !m_pMex )
	{
		return;
	}
	unguard;

	guard(test2);
	if( m_pMex->IsDestroying() )
	{
		GetMexResMgr()->LogError( "Use DestroyingFile = %s", m_pMex->GetFilename() );
		m_pMex = NULL;
		return;
	}

// 	m_pMex->SetTransform( (float*)pMatrix );

	IMexSkeleton* pSkeleton = m_pMex->GetSkeleton();

	if( !pSkeleton )
		return;

	int nBoneCount = pSkeleton->GetBoneCount();
	int nFrameId = m_nFrameId;

	//DWORD dwStart = HQ_TimeGetTime();
	//SPlayTask* pTask = &m_PlayTasks[0];

	guard(test2.1);
	if( nFrameId < 0 )
	{
		assert( false && "frame id < 0 " );
		nFrameId = 0;
	}
// 	m_pMex->SetFrameId( m_nFrameId );
	unguard;

	guard(test2.2);
	for( int i = 0; i < nBoneCount; i++ )
	{
		IMexBone* pBone = pSkeleton->GetBone(i);
		if( pBone && pMatrix )
		{
			if( pBone->HasKeyFrame() )
			{
				D3DXMatrixMultiply( 
					(D3DXMATRIX*)&m_matrices[i], 
					(D3DXMATRIX*)pBone->GetFrame0Inv(),
					(D3DXMATRIX*)pBone->GetMatricesFromKeyTime(nFrameId*ONEFRAMEINTERVAL,FRAMEPERSEC) );
			}
			else
			{
				D3DXMatrixMultiply( 
					(D3DXMATRIX*)&m_matrices[i], 
					(D3DXMATRIX*)pBone->GetFrame0Inv(),
					(D3DXMATRIX*)pBone->GetMatrices( nFrameId ) );
			}

			// 在模型空间中的变换
			memcpy( &m_matBones[i], &m_matrices[i], sizeof( MeMatrix ) );

			// 镜像
			if( GetEngine()->IsEffectMirror() )
			{
				m_matrices[i].m[0][0] *= -1;
				m_matrices[i].m[1][0] *= -1;
				m_matrices[i].m[2][0] *= -1;
				m_matrices[i].m[3][0] *= -1;
			}

			D3DXMatrixMultiply( 
				(D3DXMATRIX*)&m_matrices[i], 
				(D3DXMATRIX*)&m_matrices[i],
				(D3DXMATRIX*)pMatrix );
		}
	}
	unguard;

	guard(test2.3);
	D3DXMATRIX matModel;
	D3DXMatrixIdentity( &matModel );
	if( GetEngine()->IsEffectMirror() )
		MirrorMatrix( 0, (MeMatrix*)&matModel );

	// matModel的意义
	// 物体先左右镜像，
	// 然后变换到世界空间中
	D3DXMatrixMultiply( (D3DXMATRIX*)&matModel, 
		(D3DXMATRIX*)&matModel,
		(D3DXMATRIX*)pMatrix );

	m_matModel = *(MeMatrix*)&matModel;
	D3DXMatrixInverse( (D3DXMATRIX*)&m_matModelInv, NULL, (D3DXMATRIX*)&m_matModel );

	guard(test2.3.1);
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->Update( 
				dwTime, 
				m_fScale,
				(float*)m_matBones,
				(float*)&matModel ,m_nFrameId);
		}
	}
	unguard;

	guard(test2.3.2);
	for(int i = 0; i < eMaxRibbonEmitter; i++ )
	{
		IMexRibbonEmitter* pEmitter = m_pRibbonEmitters[i];
		if( !pEmitter )
			continue;

		pEmitter->Update( dwTime, 
			m_nFrameId, 
			(float*)m_matBones,
			(float*)&matModel );
	}
	unguard;
	unguard;
	unguard;
	unguard;
}

void CMexEffectCtrl::SetParticleEmitterPlaySpeed( float fPlaySpeed )
{
	guardfunc;
	for( int i = 0; i < eMaxParticleEmitter; i++ )
	{
		if( m_pParticleEmitters[i] )
		{
			m_pParticleEmitters[i]->SetPlaySpeed( fPlaySpeed );
		}
	}
	unguard;
}
void CMexEffectCtrl::Render3( float fTransparent )
{
	guardfunc;
	if ( !m_pMex )
		return;

	IRenderer* pRenderer = GetEngine()->GetRenderer();
	if ( !pRenderer )
	{
		assert( false );
		return;
	}

	pRenderer->SetGlobalTransparent( fTransparent );
	pRenderer->SetGlobalDiffuse( 1, 1, 1 );
	pRenderer->SetGlobalUOffset( 0, 0.0f );
	pRenderer->SetGlobalVOffset( 0, 0.0f );
	pRenderer->SetGlobalUOffset( 1, 0.0f );
	pRenderer->SetGlobalVOffset( 1, 0.0f );

	DWORD dwTime = HQ_TimeGetTime();
	if ( m_pMex->GetGeometry() )
	{
		int nChunkCount = m_pMex->GetGeometry()->GetChunkCount();
		for ( int i = 0; i < nChunkCount; i++ )
		{
			RenderSubset( i, pRenderer, fTransparent );
		}
	}
	pRenderer->Flush( FALSE );

	if ( m_pRibbonEmitters )
	{
		for ( int i = 0; i < eMaxRibbonEmitter; i++ )
		{
			if ( m_pRibbonEmitters[i] != NULL)
			{
				int nLocalTextureId = m_pRibbonEmitters[i]->GetLocalTextureID();
				short stTextureId = m_ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
				m_pRibbonEmitters[i]->Render( NULL, stTextureId, fTransparent, FALSE, false );
			}
		}
	}

	if ( m_pParticleEmitters )
	{
		for ( int i = 0; i < eMaxParticleEmitter; i++ )
		{
			if ( m_pParticleEmitters[i] != NULL )
			{
				int nLocalTextureId = m_pParticleEmitters[i]->GetLocalTextureID();
				short stTextureId = m_ReplaceableTextureProj.GetRenderTextureID(nLocalTextureId);
				m_pParticleEmitters[i]->Render( dwTime, stTextureId, fTransparent, false );
			}
		}
	}
	pRenderer = NULL;
	unguard;
}

void CMexEffectCtrl::RenderSubset( int nSubset, IRenderer* pRenderer, float fAlpha )
{
	guardfunc;
	if( !m_pMex->GetGeometry() )
		return;
	IRenderable* pSubset = m_pMex->GetGeometry()->GetChunk(nSubset);
	if( !pSubset )
		return;

	if ( m_pAvatarSetting != NULL)
	{
		if ( nSubset < m_pAvatarSetting->m_vectorSubsetFlag.size() )
		{
			DWORD dwFlag = m_pAvatarSetting->m_vectorSubsetFlag[nSubset];
			if ( ( dwFlag & eMexCfg_SubsetVisible ) == 0 )
			{
				return;
			}

		}
	}

	DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
	pRenderer->SetSurfaceFVF( dwFvf );
	pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );

	RenderParams* params = CRenderParamsMgr::Instance()->RetriveRenderParams();
	if (params)
	{
		params->pMex = m_pMex;
		params->pMatrices = (float*)m_matrices;
// 		params->pRenderer = pRenderer;
		params->pReplaceableTextureProj = &m_ReplaceableTextureProj;
		params->fAlpha = fAlpha;
		params->bMustUseAlphaBlend = false;
		params->nSpecularTexID = -1;
		params->nFrameId = m_nFrameId;
		pSubset->Render( params );
	}
	unguard;
}

void CMexEffectCtrl::ReleaseLastModel()
{
	guardfunc;
// 	if( m_nModelId != -1 )
	{
		GetMexResMgr()->DestroyModel( m_nModelId );
		m_nModelId = -1;
	}

	m_pMex		= NULL;
	m_pMexCfg	= NULL;
	m_pAvatarSetting = NULL;
	unguard;
}

BOOL CMexEffectCtrl::ChangeModel( int nModelId )
{
	guardfunc;
	ReleaseLastModel();

	MexResMgr::Record* pRecord = GetMexResMgr()->CreateModel( nModelId );

	if( !pRecord || !pRecord->res.pMex )
	{
		return FALSE;
	}

	m_nModelId = nModelId;

	CMexEffectCtrl::ChangeModel( pRecord->res.pMex, pRecord->res.pMexCfg );

	return TRUE;
	unguard;
}

// 更换模型
BOOL CMexEffectCtrl::ChangeModel( IMex* pMex, MexCfg* pMexCfg )
{
	guardfunc;
	if( pMex == NULL )
		return FALSE;

	if( pMex->GetSkeleton() == NULL )
		return FALSE;

	if( pMexCfg == NULL )
		return FALSE;
	SetMex( pMex, pMexCfg );
	int nNumBone = pMex->GetSkeleton()->GetBoneCount();

	if( m_matrices )
	{
		delete[] m_matrices;
		m_matrices = NULL;
		m_matSrcBones = NULL;
		m_matBones = NULL;
	}
	IMexBone* pBone = pMex->GetSkeleton()->GetBone(0);

	if( pBone == NULL )
		return FALSE;

	MexCfgSequence* pIdleSeq = pMexCfg->FindIdleSequence();
	m_matrices = MeNew MeMatrix[nNumBone*3];;
	m_matBones = &m_matrices[nNumBone];
	m_matSrcBones = &m_matrices[nNumBone*2];
	m_nFrameCount = pBone->GetFrameCount();

	PlayAnim( 0, m_nFrameCount-1, 0 );

	return TRUE;
	unguard;
}

void CMexEffectCtrl::CalcTransformMatrix( float x, 
									   float y, 
									   float z, 
									   float rot,
									   float scale,
									   MeMatrix* pmatTransform )
{
	guardfunc;
	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis( &matRot, &D3DXVECTOR3( 0, 0, 1 ), rot );
	//D3DXMatrixRotationAxis( &matRot, &D3DXVECTOR3( 0.1, 0.1, 0.9 ), rot );

	D3DXMATRIX matScale;
	D3DXMatrixScaling( &matScale, scale, scale, scale );


	D3DXMatrixMultiply( (D3DXMATRIX*)pmatTransform, &matRot, &matScale );

	pmatTransform->m[3][0] = x;
	pmatTransform->m[3][1] = y;
	pmatTransform->m[3][2] = z;
	unguard;
}

void CMexEffectCtrl::SetRotation( float theta, D3DXVECTOR3& vAxis, 
								 MeMatrix* pmatTransform )
{
	D3DXMATRIX matRotation;
	D3DXMatrixRotationAxis( &matRotation, &vAxis, theta );
	D3DXMatrixMultiply( (D3DXMATRIX*)pmatTransform, &matRotation, (D3DXMATRIX*)pmatTransform );
}

void CMexEffectCtrl::CalcTransformMatrix( MeMatrix* pmatTransform )	
{
	guardfunc;

 	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis( &matRot, &D3DXVECTOR3( 0, 0, 1 ), m_fRotTheta );

	if( m_fXRotTheta != 0 )
	{
		D3DXMATRIX matRot2;
		D3DXMatrixRotationAxis( &matRot2, &D3DXVECTOR3( 1, 0, 0 ), m_fXRotTheta );
		D3DXMatrixMultiply( &matRot, &matRot2, &matRot );
	}

	D3DXMATRIX matScale;
	D3DXMatrixScaling( &matScale, m_fScale, m_fScale, m_fScale );


	D3DXMatrixMultiply( (D3DXMATRIX*)pmatTransform, &matRot, &matScale );

	pmatTransform->m[3][0] = m_vPosition.x;
	pmatTransform->m[3][1] = m_vPosition.y;
	pmatTransform->m[3][2] = m_vPosition.z;

	unguard;
}

void CMexEffectCtrl::CalcTransformMatrix( MeMatrix* pmatTransform, 
										 float fRot, D3DXVECTOR3& vAxis )
{
	guardfunc;

	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis( &matRotZ, &D3DXVECTOR3( 0, 0, 1 ), m_fRotTheta );

	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis( &matRot, &vAxis, fRot );
	D3DXMatrixMultiply( &matRot, &matRotZ, &matRot );

	D3DXMATRIX matScale;
	D3DXMatrixScaling( &matScale, m_fScale, m_fScale, m_fScale );


	D3DXMatrixMultiply( (D3DXMATRIX*)pmatTransform, &matRot, &matScale );

	pmatTransform->m[3][0] = m_vPosition.x;
	pmatTransform->m[3][1] = m_vPosition.y;
	pmatTransform->m[3][2] = m_vPosition.z;

	unguard;
}