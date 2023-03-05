#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/effect/MexEffectCtrl.h"
#include "Me3d/effect/ModelEffect.h"
#include "Me3d/effect/effectmanager.h"
#include "FuncPerformanceLog.h"
#include "Me3d/MathLib.h"
#include "DataChunkWriter.h"
#include "FilePath.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#include "Me3d/Config.h"
// #include "CfgXmlFileLoader.h"

#include "Me3d/effect/CharEffectContainer.h"

#define MAX_INSTANCE_COUNT eMaxInstance

//#include "../../client/GameLogic.h"

//攻击动作的播放时间
#define SPELLACTION_CASTTIME 200
/////////////////////////
extern D3DXVECTOR3		g_vCurSelectNpcPos;			//当前选中的Npc位置
extern BOOL				g_bHaveSelectNpc;			//是否有选中的Npc


CModelEffect::Instance::Instance():
nMode(eTerminateMode_Loop),
//nModelID(-1),
dwBornTime(0),
dwLife(0),
bVisible(TRUE),
bDead(FALSE),
bPlayOver(FALSE),
nNumLoop(1),
bLoopForever(FALSE),
fScale(1.0),
fBornScale(1.0),
fXOffset(0),
fYOffset(0),
fZOffset(0),
fRotCorrect(D3DX_PI*0.5f),
dwDeadTime(0),
dwPlayOverRenderTime(0),
fRot(0.0f),
bUpdateBornPos(FALSE),
fAlpha(1.0f),
//fBindRot(0.0f),
nBindWhere(eEffectBindPart_Body),
dwVisibleChangeTime(0),
nTargetBindWhere(eEffectBindPart_Body),
nAction(eActionFollow),
nActionTime(0),
bRotateTogether(FALSE),
bDisapearAfterAction(FALSE),
bOutOfLookerView(FALSE),
fParabolaHeight(0.0f),
fFallHeight(0.0f),
fGroundZ(0.0f),
nFrameID(0),
fFrameFactor(0),
pMaster(NULL),
pTarget(NULL),
nCarryNumber(0),
pEffectCtrl(NULL),
fDelay(0),
bOriginalSize(false),
fParabolaTime( 0.0f ),
fParabolaAngle( 0.0f ),
fRotX( 0.0f ),
fZVelocity0( 0.0f ),
fZAcceleration( 0.0f ),
bOriginalAlpha( false )
{
	guardfunc;
	szModel[0] = 0;
    szHitEffect[0] = 0;
    pParabolaEndFun = NULL;
	unguard;
}

void CModelEffect::Instance::SetParabolaEndCallBack( FunParabolaEndCallBack pFun )
{
    pParabolaEndFun = pFun;
}

CModelEffect::CModelEffect(void):
//m_pAnimCtrl(NULL),
m_dwBornTime(0),
m_dwLife(0),
m_dwFlyTime(0),
m_fScale(1.0f),
m_nNumInstance(0),
m_nMaxInstance(0),
m_fRadius(0),
m_dwDelay(0),
m_nOneLoopTime( 0 ),
m_nTerminateMode(eTerminateMode_Life),
m_bMexLoaded(FALSE)
{
	guardfunc;
	m_szModel[0] = 0;
	m_szMaleSound[0] = 0;
	m_szFemaleSound[0] = 0;
	m_nCameraShakeType = eNoCameraStunt;	//摄象机的振动类型
	m_fMaxShakeWaveRange = 0;				//震波影响最弱的范围
	m_fMinShakeWaveRange = 0;				//震波影响最强的范围
	m_fMaxShakeRange = 0;					//最大振幅
	m_fMinShakeRange = 0;					//最小振幅
	m_dwShakeKeepTime = 0;					//震动维持时间
	m_dwShakeStartTime = 0;					//震动开始时间
	m_isDead = false;
	m_pEffectQuoter = NULL;
	unguard;
}

CModelEffect::~CModelEffect(void)
{
	guardfunc;
	unguard;
	//assert( m_pAnimCtrl == NULL );
}

void CModelEffect::SetDead()
{
	guardfunc;
	for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
	{
		guard(test1);
		Instance* pInstance = &m_Instances[nInstance];

		guard(test1.1)
		if( !pInstance->bDead )
		{
			if( !pInstance->bPlayOver )
			{
				pInstance->bPlayOver = TRUE;
				pInstance->dwPlayOverTime = HQ_TimeGetTime();
			}
		}
		unguard;
		unguard;
	}
	m_isDead = true;

	CCharEffectContainer* pContainer = GetEffectMgr()->GetCharEffectContainer( m_nEffectQuoterId );
	if (pContainer)
	{
		pContainer->ClearEffectNotDestroy(GetID());
		m_nEffectQuoterId = -1;
		m_pEffectQuoter = 0;
	}

	unguard;
}

BOOL CModelEffect::IsDead( DWORD dwTime )
{
	guardfunc;
	////////这里不用加是否多线程加载的判定
	//if( !m_bMexLoaded )
	//	return FALSE;

	///////以下的死亡判定是必须每个循环都执行到的（因为略过回造成 pMaster 和 pTarget指向的资源被删）
	for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
	{
		Instance* pInstance = &m_Instances[nInstance];
		if( !pInstance->bDead )
		{
			if( pInstance->pMaster )
			{
				if( pInstance->pMaster->IsDestroy() )
				{
					pInstance->bDead = TRUE;
					pInstance->dwDeadTime = HQ_TimeGetTime();
					//pInstance->dwDeadTime = dwTime;
					///////////
					pInstance->pMaster = NULL;
				}
			}

			if( pInstance->pTarget )
			{
				if( pInstance->pTarget->IsDestroy() )
				{
					pInstance->bDead = TRUE;
					pInstance->dwDeadTime = HQ_TimeGetTime();
					//pInstance->dwDeadTime = dwTime;
					///////////
					pInstance->pTarget = NULL;
				}
			}
		}
	}

	switch( m_nTerminateMode )
	{
	case eTerminateMode_Life:
		{
			if( dwTime > m_dwBornTime )
			{
				BOOL bAllInstance = TRUE;
				for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
				{
					Instance* pInstance = &m_Instances[nInstance];
					if( !pInstance->bDead )
					{
						bAllInstance = FALSE;
					}
				}

				if( bAllInstance )
				{
					return TRUE;
				}

				return dwTime - m_dwBornTime > m_dwLife;
			}
			else
			{
				return FALSE;
			}
		}
		break;
	case eTerminateMode_WaitAllInstanceDead:
		{
			// 如果有任意1个instance没有完，就不算dead
			for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
			{
				Instance* pInstance = &m_Instances[nInstance];
				if( !pInstance->bDead )
				{
					return FALSE;
				}
			}
		}
		break;
	case eTerminateMode_WaitParentDelete:
		return m_isDead;
		break;
	default:
		assert( false );
	}
	return TRUE;
	unguard;
}

BOOL CModelEffect::IsInstanceDead( DWORD dwTime, Instance* pInstance )
{
	guardfunc;
	if( !pInstance )
		return TRUE;

	if( pInstance->bDead )
		return TRUE;

	if( pInstance->bPlayOver )
	{
		if( pInstance->dwPlayOverTime + pInstance->dwPlayOverRenderTime < dwTime )
			return TRUE;
	}

	return FALSE;

	//switch( pInstance->nMode )
	//{
	//case eTerminateMode_Life:
	//	if( pInstance->bPlayOver )
	//	{
	//		if( pInstance->dwPlayOverTime + pInstance->dwPlayOverRenderTime < dwTime )
	//			return TRUE;
	//	}
	//	break;
	//case eTerminateMode_Loop:
	//	{
	//		if( pInstance->bLoopForever )
	//		{
	//			if( pInstance->bPlayOver )
	//			{
	//				if( pInstance->dwPlayOverTime + pInstance->dwPlayOverRenderTime < dwTime )
	//				{
	//					return TRUE;
	//				}
	//			}
	//			return FALSE;
	//		}
	//	}
	//	break;
	//default:
	//	return TRUE;
	//}
	//return FALSE;
	unguard;
}

BOOL CModelEffect::IsInstancePlayOver( DWORD dwTime, Instance* pInstance )
{
	guardfunc;
	if( !pInstance )
		return TRUE;

	if( pInstance->bDead )
		return TRUE;

	switch( pInstance->nMode )
	{
	case eTerminateMode_Life:
		if( pInstance->dwBornTime + pInstance->dwLife < dwTime )
			return TRUE;
		break;
	case eTerminateMode_Loop:
		{
			if( pInstance->bLoopForever )
				return FALSE;

			DWORD dwPassed = dwTime - pInstance->dwBornTime;
			int nLooped = 0;
			if( m_nOneLoopTime == 0 )
			{
				nLooped = 0xffffffff;
			}
			else
			{
				nLooped = dwPassed/m_nOneLoopTime;
			}

			if( nLooped >= pInstance->nNumLoop )
			{
				return TRUE;
			}
		}
		break;
	default:
		return TRUE;
	}

	return FALSE;
	unguard;
}

void CModelEffect::UpdateInstance( DWORD dwTime, Instance* pInstance )
{
	guardfunc;
	if( !m_bMexLoaded )
		return ;

	if( pInstance->bDead )
	{
		assert( false );
		return;
	}

	if( !pInstance->pEffectCtrl )
		return;

	DWORD dwPassed = dwTime - pInstance->dwBornTime;

	pInstance->nFrameID = dwPassed/ONEFRAMEINTERVAL;

	if( pInstance->pEffectCtrl->GetFrameCount() == 0 )
		pInstance->nFrameID =  0;
	else
		pInstance->nFrameID %= pInstance->pEffectCtrl->GetFrameCount();

	if( pInstance->bPlayOver )
	{
		pInstance->nFrameID = pInstance->pEffectCtrl->GetFrameCount() - 1;
	}

	switch( pInstance->nAction )
	{
	case eActionStand:
		if( pInstance->pMaster )
		{
			pInstance->pMaster->GetPos( (float*)&pInstance->vPos );
			if( pInstance->bRotateTogether )
				pInstance->fRot = pInstance->pMaster->GetRot();
		}
		break;
	case eActionFollow:
		if( pInstance->pMaster )
		{
			pInstance->pMaster->GetPos( (float*)&pInstance->vPos );
			if( pInstance->bRotateTogether )
				pInstance->fRot = pInstance->pMaster->GetRot();

			//World3Screen( 200, 200, pInstance->vPos.z, pInstance->vPos );
		}
		break;
	case eActionFollowPoint:
		if( pInstance->pMaster )
		{
			pInstance->pMaster->GetPos( (float*)&pInstance->vPos );
			if( pInstance->bRotateTogether )
				pInstance->fRot = pInstance->pMaster->GetRot();								
			D3DXVECTOR3 vAxis = ( pInstance->vTargetPos - pInstance->vPos );
			D3DXVECTOR3 vDir = vAxis;
			D3DXVECTOR3 vHor( vAxis.x, vAxis.y, 0 );
			D3DXVECTOR3 vVer( 0, 0, vAxis.z );
			D3DXVec3Cross( &vAxis, &vHor, &vVer );			
			pInstance->vAxisOfZRotation = vAxis;
			D3DXVec3Normalize( &vDir, &vDir );				
			pInstance->fRotZ = atan2( vDir.z, sqrt( vDir.x * vDir.x + vDir.y * vDir.y ) );		
		}
		break;
	case eActionFollowPos:
		if( pInstance->pMaster )
		{
			pInstance->pMaster->GetPos( (float*)&pInstance->vPos );
		}
		break;
	case eActionPointToNpc:
		{
			if( g_bHaveSelectNpc )
			{
				pInstance->bVisible = TRUE;
				pInstance->pMaster->GetPos( (float*)&pInstance->vPos );
				pInstance->fRot = atan2( g_vCurSelectNpcPos.y - pInstance->vPos.y, g_vCurSelectNpcPos.x - pInstance->vPos.x );
				pInstance->fRot += D3DX_PI*0.5f;
			}
			else
			{
				pInstance->bVisible = FALSE;
			}
		}
		break;		
	case eActionTrace:
		{
			if( pInstance->bPlayOver )
			{
				return;
			}

			switch( pInstance->nTrackType )
			{
			case eTrackTypeLine:
				{
                    pInstance->bVisible = FALSE;

                    if( pInstance->pTarget )
                    {
                        pInstance->pTarget->GetPos( (float*)&pInstance->vTargetPos );
                    }

                    //World3Screen( 780, 200, pInstance->vTargetPos.z, pInstance->vTargetPos );
                    //OutputDebugString( "eActionTrace" );

                    pInstance->fRot = atan2( pInstance->vTargetPos.y - pInstance->vPos.y, pInstance->vTargetPos.x - pInstance->vPos.x );
                    //pInstance->fRot += pInstance->fRotCorrect;
                    pInstance->fRot += D3DX_PI*0.5f;

                    float t = 0.0;

                    if( dwPassed > SPELLACTION_CASTTIME )
                    {
                        pInstance->bVisible = TRUE;
                        t = ((float)dwPassed - SPELLACTION_CASTTIME)/pInstance->nActionTime;

                        if( t > 1.0f || t < 0.f )
                        {
                            t = 1.0f;
                            pInstance->bPlayOver = TRUE;
                            pInstance->dwPlayOverTime = HQ_TimeGetTime();
                            pInstance->fRot = atan2( pInstance->vTargetPos.y - pInstance->vBornPos.y, pInstance->vTargetPos.x - pInstance->vBornPos.x );
                            pInstance->fRot += D3DX_PI*0.5f;

                            //if( pInstance->bDisapearAfterAction )
                            //{
                            //	pInstance->bVisible = FALSE;
                            //}
                        }
                    }
                    else
                    {
                        if( pInstance->pMaster )
                        {
                            //if( !pInstance->bUpdateBornPos )
                            {
                                pInstance->pMaster->GetPos( (float*)&pInstance->vBornPos );
                                //pInstance->fRot = pInstance->pMaster->GetRot();
                                //pInstance->pMaster->GetPos( (float*)&pInstance->vBornPos );
                                //pInstance->bUpdateBornPos = TRUE;
                            }
                        }
                    }

					pInstance->vPos = pInstance->vBornPos + t*(pInstance->vTargetPos - pInstance->vBornPos);
					
					if( pInstance->fParabolaHeight != 0 )
                    {
						// 有抛物高度的可以配置角度 (类似WOW的奥术飞弹)     modified by zhuomeng.hu		[3/21/2011]
                        D3DXVECTOR3 vOffset = D3DXVECTOR3( 0.0f, 0.0f, sinf( t * D3DX_PI ) * pInstance->fParabolaHeight );
                        D3DXVECTOR3 vAxis = pInstance->vTargetPos - pInstance->vBornPos;
                        D3DXMATRIX M;
                        D3DXMatrixRotationAxis( &M, &vAxis, pInstance->fParabolaAngle * D3DX_PI / 180.0f );
                        D3DXVec3TransformNormal( &vOffset, &vOffset, &M );
                        pInstance->vPos += vOffset;
                    }
				}
				break;
            case eTrackTypeParabola:
                {
                    // added by zhuomeng.hu		[3/7/2011]
                    DWORD dwPassedTime = dwTime - pInstance->dwBornTime;
                    float fT = ( double )dwPassedTime / 1000.0f;

                    if( pInstance->fParabolaTime > 0.0f && fT <= pInstance->fParabolaTime )
                    {
                        if( dwPassedTime < SPELLACTION_CASTTIME )
                        {
                            pInstance->bVisible = FALSE;
                        }
                        else
                        {
                            pInstance->bVisible = TRUE;
                        }

                        // 计算XY
                        pInstance->vPos = pInstance->vBornPos + fT / pInstance->fParabolaTime * ( pInstance->vTargetGroundPos - pInstance->vBornPos );

                        // 计算Z
                        if( pInstance->fZVelocity0 > 0.0f && pInstance->fZAcceleration > 0.0f )
                        {
                            pInstance->vPos.z = pInstance->vBornPos.z + pInstance->fZVelocity0 * fT - 0.5f * pInstance->fZAcceleration * fT * fT;
                        }

                        // 水平方向的旋转，使特效朝向与发射方向相同
                        pInstance->fRot = atan2( pInstance->vTargetGroundPos.y - pInstance->vBornPos.y, pInstance->vTargetGroundPos.x - pInstance->vBornPos.x );
                        pInstance->fRot += D3DX_PI * 0.5f;

                        // 竖直方向的旋转，使特效朝向与当前速度方向相同
                        float fDelX = pInstance->vTargetGroundPos.x - pInstance->vBornPos.x;
                        float fDelY = pInstance->vTargetGroundPos.y - pInstance->vBornPos.y;
                        float fVxy = sqrtf( fDelX * fDelX + fDelY * fDelY ) / pInstance->fParabolaTime;
                        pInstance->fRotX = - atan2( pInstance->fZVelocity0 - pInstance->fZAcceleration * fT, fVxy );
                    }
                    else
                    {
                        pInstance->bVisible = FALSE;
                        pInstance->bPlayOver = TRUE;
                        pInstance->dwPlayOverTime = HQ_TimeGetTime();

                        // 刚播完轨迹特效 需要播放落地特效
                        if( pInstance->pParabolaEndFun && pInstance->szHitEffect && pInstance->szHitEffect[0] )
                        {
                            pInstance->pParabolaEndFun( pInstance->szHitEffect, pInstance->vTargetGroundPos );
                        }
                    }
                }
                break;
            default:
                break;
			}
		}
		break;
	case eActionFall:
		{
			float t = (float)dwPassed/pInstance->nActionTime;
			if( t > 1.0f )
			{
				t = 1.0f;
				pInstance->bVisible = TRUE;
			}

			//pInstance->vPos = pInstance->vBornPos+t*(pInstance->vTargetPos-pInstance->vBornPos);
			pInstance->vPos = pInstance->vBornPos;
			pInstance->vPos.z = pInstance->vBornPos.z+t*(pInstance->fGroundZ-pInstance->vBornPos.z);
		}
		break;
	case eActionFollowSpray:
		if( pInstance->pMaster )
		{
			D3DXVECTOR3 vMasterPos;
			pInstance->pMaster->GetPos( (float*)&vMasterPos );
			pInstance->vPos.x = vMasterPos.x;
			pInstance->vPos.y = vMasterPos.y;
			pInstance->vPos.z = pInstance->pMaster->GetTerrainZ();

			if( pInstance->bRotateTogether )
				pInstance->fRot = pInstance->pMaster->GetRot();
		}
		break;
	case eActionSkillBarCollect:
		{
			//if( pInstance->bPlayOver )
			//{
			//	return;
			//}

			pInstance->bVisible = FALSE;

			if( pInstance->pTarget )
			{
				pInstance->pTarget->GetPos( (float*)&pInstance->vTargetPos );
			}

			//World3Screen( 400, 300, pInstance->vTargetPos.z, pInstance->vTargetPos );
			//pInstance->fRot += pInstance->fRotCorrect;
			pInstance->fRot = D3DX_PI*0.5f;

			float t = 0.0;

			static int nTest = 200;
			if( dwPassed > nTest )
			{
				pInstance->bVisible = TRUE;
				t = (float)(dwPassed - nTest)/ ( pInstance->nActionTime  );

				//if( t > 0.8f )
				{
					//if( !pInstance->bPlayOver &&
					//	pInstance->nActionTime > dwPassed &&
					//	pInstance->nActionTime - dwPassed < 1500 )
					//{
					//	pInstance->bPlayOver = TRUE;
					//	pInstance->dwPlayOverTime = HQ_TimeGetTime();
					//}

					if( !pInstance->bPlayOver )
					{
						if( ( pInstance->nActionTime  ) > (dwPassed - nTest) )
						{
							if( ( pInstance->nActionTime  ) - (dwPassed - nTest) < nTest )
							{
								pInstance->bPlayOver = TRUE;
								pInstance->dwPlayOverTime = HQ_TimeGetTime();
							}
						}
						else
						{
							pInstance->bPlayOver = TRUE;
							pInstance->dwPlayOverTime = HQ_TimeGetTime();
						}
					}

					//if( t > 1.0f )
					//{
					//	t = 1.0f;
					//}
				}
			}

			if( !pInstance->bVisible )
				break;

			//出生
			if( t < 0.3f )
			{
				float k = t/0.3f;
				pInstance->pEffectCtrl->SetRotationZ( -D3DX_PI*0.5 );
				pInstance->vPos = pInstance->vBornPos;
				pInstance->vPos.z += k*pInstance->fFallHeight;
				pInstance->fScale = pInstance->fBornScale*0.6;
				pInstance->fAlpha = k;
			}
			else if( t >= 0.3f && t < 0.65f )
			{
				pInstance->fAlpha = 1.0f;
				//pInstance->fScale *= 0.99f;
			}
			else if( t >= 0.65f && t < 0.7f )
			{
				float k = (0.7f-t)/0.05f;
				pInstance->fScale = pInstance->fBornScale*k*0.6;
				pInstance->fAlpha = 1.0f;
			}
			else
			{
				float k;
				if( t > 1.0f )
				{
					k = 1;
					if( t > 1.3f )
						t = 1.3f;

					pInstance->fScale = pInstance->fBornScale*( 1.3f - t )/0.3f;
				}
				else
				{
					k = ( t - 0.7f )/0.3f;
					pInstance->fScale = pInstance->fBornScale*k;
				}

				D3DXVECTOR3 vStartAbsorbPos = pInstance->vBornPos;
				vStartAbsorbPos.z += pInstance->fFallHeight;
				pInstance->vPos = vStartAbsorbPos + k*(pInstance->vTargetPos - vStartAbsorbPos);

				pInstance->vPos.x += sinf( k*D3DX_PI )*pInstance->fXOffset;
				pInstance->vPos.y += sinf( k*D3DX_PI )*pInstance->fYOffset;
				pInstance->vPos.z += sinf( k*D3DX_PI )*pInstance->fZOffset;

				pInstance->fRot = atan2( pInstance->vTargetPos.y - pInstance->vPos.y, pInstance->vTargetPos.x - pInstance->vPos.x );
				pInstance->fRot += D3DX_PI*0.5f;

				pInstance->pEffectCtrl->SetRotationZ( 0 );

			}
		}
		break;

		/*增加case eActionFollowCamera
		说明：在特校中增加整个特效始终朝向摄像机功能
		add by yanli 2010-6-30*/
		//------------------------------------------------------------------------------
	case eActionFollowCamera:
		if( pInstance->pMaster )
		{
			pInstance->pMaster->GetPos( (float*)&pInstance->vPos );
			MeCamera* pCamera = Config::GetCamera();
			if( !pCamera )
				return;
			pInstance->fRot =  -pCamera->GetRot();	
		}
		break;
		//------------------------------------------------------------------------------
	}
	// added, jiayi, [2009/10/19]
	if( pInstance->bOriginalSize )// 不进行缩放
	{
		MeCamera* pCamera = Config::GetCamera();
		if( !pCamera )
			return;
		D3DXVECTOR3 vCameraPos = pCamera->GetEyePt();	
		//
		// 在不同距离上调整缩放，来保证不进行缩放
		//
		D3DXVECTOR3 vEffectPos = pInstance->vPos;
		// 取方向
		D3DXVECTOR3 vDir = vEffectPos - vCameraPos; 
		float fScale = D3DXVec3Length( &vDir );
		float fovScale = ( pCamera->GetFOV() - D3DXToRadian(45) ) / ( D3DXToRadian(70) - D3DXToRadian(45) );
		static float fTemp = 0.1f;
		static float fTempFov = 0.001f;
		fScale *= ( fTemp * GetMe3dConfig()->m_fMdlSpaceScale + fTempFov * fovScale );
		pInstance->fScale = fScale;		
	}
	unguard;
}

void CModelEffect::Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance )
{
	guardfunc;
	if( m_nCameraShakeType != eNoCameraStunt && dwTime - m_dwBornTime > m_dwShakeStartTime )
	{
		m_dwShakeStartTime = 0xffffffff;
		switch( m_nCameraShakeType )
		{
		case eNormalShake:
			break;
		case eHorizontalShake:
			break;
		case eVerticalShake:
			break;
		}
	}

	for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
	{
		Instance* pInstance = &m_Instances[nInstance];
		// added, jiayi, [2009/10/19]
		if( pInstance->bOriginalSize )
		{
			// 这里的数值取自m_fNameShowDistance变量，参考cfg.cpp
			fDistance = 35.f;
		}
		if( D3DXVec3Length( &( pInstance->vPos - vPos ) ) > fDistance )
		{
			pInstance->bOutOfLookerView = TRUE;
		}
		else
		{
			pInstance->bOutOfLookerView = FALSE;
		}

		if( pInstance->dwBornTime > dwTime )
		{
			continue;
		}

		// 已经死亡的instance不用更新
		if( pInstance->bDead  )
		{
			continue;
		}

		// 是否播放结束
		if( !pInstance->bPlayOver )
		{
			if( IsInstancePlayOver( dwTime, pInstance ) )
			{
				pInstance->bPlayOver = TRUE;
				//pInstance->dwPlayOverTime = dwTime;
				pInstance->dwPlayOverTime = HQ_TimeGetTime();
			}
		}

		// 判定是否死亡
		if( IsInstanceDead( dwTime, pInstance ) )
		{
			pInstance->bDead = TRUE;
			//pInstance->dwDeadTime = dwTime;
			pInstance->dwDeadTime = HQ_TimeGetTime();
			continue;
		}
		UpdateInstance( dwTime, pInstance );
	}
	unguard;

}
void CModelEffect::Render()
{
	guardfunc;

	if( !m_bMexLoaded )
		return;

	DWORD dwTime = HQ_TimeGetTime();
	MeMatrix m;

	guard(test2);
	for( int nInstance = 0; nInstance < m_nNumInstance; nInstance++ )
	{
		Instance* pInstance = &m_Instances[nInstance];

		if( !pInstance->pEffectCtrl )
			continue;

		guard(test2.1);
		/////////////////////////
		if( pInstance->bOutOfLookerView )
			continue;
		//////////////////////

		if( pInstance->dwBornTime > dwTime )
			continue;

		if( pInstance->bDead )
			continue;

		//if( !pInstance->bVisible && dwTime - pInstance->dwVisibleChangeTime > 500 )
		//	continue;
		unguard;

		float fAlpha = pInstance->fAlpha;

		///////////////////////
		if( !pInstance->bVisible )
		{
			if( dwTime - pInstance->dwVisibleChangeTime > 500 )
			{
				continue;
			}
			else
			{
				fAlpha = (float)(500 - (dwTime - pInstance->dwVisibleChangeTime))/500;
			}
		}
		///////////////////////////////

		guard(test2.2);
		if( pInstance->bPlayOver )
		{
			if( pInstance->dwPlayOverRenderTime > 0 )
			{
				if( pInstance->dwPlayOverRenderTime > dwTime - pInstance->dwPlayOverTime )
				{
					float fPassedTime = (float)( pInstance->dwPlayOverRenderTime - ( dwTime - pInstance->dwPlayOverTime ) );
					float fFinalRenderAlpha = 1.0;
					if( !(pInstance->nAction == eActionSpray || pInstance->nAction == eActionFollowSpray) )
					{
                        // modified by zhuomeng.hu    [5/17/2011]
                        if( pInstance->pMaster && !pInstance->bOriginalAlpha )
                        {
                            fFinalRenderAlpha = pInstance->pMaster->GetFinalRenderAlpha();
                        }
					}
					fAlpha = fFinalRenderAlpha * fPassedTime/pInstance->dwPlayOverRenderTime;
				}
				else
				{
					fAlpha = 0;
				}
			}
		}
		else
		{
			if( !(pInstance->nAction == eActionSpray || pInstance->nAction == eActionFollowSpray) )
			{
                // modified by zhuomeng.hu    [5/17/2011]
				if( pInstance->pMaster && !pInstance->bOriginalAlpha )
				{
					float fFinalRenderAlpha = pInstance->pMaster->GetFinalRenderAlpha();
					if( fAlpha > fFinalRenderAlpha )
					{
						fAlpha = fFinalRenderAlpha;
					}
				}
			}
		}
		unguard;

		//char szBuf[512];
		//_snprintf( szBuf, 512, "fAlpha = %f %f nFrameID = %d bDead = %d %d %d PlayOverPassedTime %d", fAlpha, pInstance->fRot, pInstance->nFrameID, pInstance->bDead,
		//	dwTime - pInstance->dwDeadTime, pInstance->dwPlayOverRenderTime, dwTime - pInstance->dwPlayOverTime );
		//OutputDebugString( szBuf );

		guard(test2.4);
		pInstance->pEffectCtrl->SetFrameID( pInstance->nFrameID );
		float fOffsetZ = 0.f;
		static float fTemp = -0.004f;
		static float fTemp2 = 8.f;
		static float fMin = -0.4;
		if( pInstance->bOriginalSize )
		{
			MeCamera* pCamera = Config::GetCamera();
			if( pCamera )
			{
				static float fTempFov = 0.02f;
				float fovScale = ( pCamera->GetFOV() - D3DXToRadian(45) ) / ( D3DXToRadian(70) - D3DXToRadian(45) );
				fOffsetZ += ( pInstance->fScale + fovScale * fTempFov ) * fTemp2;
				fOffsetZ += max( fMin, 1 /  pInstance->fScale * fTemp );
			}				
		}
		pInstance->pEffectCtrl->SetPosition( pInstance->vPos.x, pInstance->vPos.y, pInstance->vPos.z + fOffsetZ );
		pInstance->pEffectCtrl->SetScale( pInstance->fScale );
		pInstance->pEffectCtrl->SetRotationZ( pInstance->fRot );
        pInstance->pEffectCtrl->SetRotationX( pInstance->fRotX );
		pInstance->pEffectCtrl->CalcTransformMatrix( &m );
		if( pInstance->nAction == eActionFollowPoint || pInstance->nAction == eActionStand )
		{
			pInstance->pEffectCtrl->SetRotation( pInstance->fRotZ, pInstance->vAxisOfZRotation, &m );
		}
		pInstance->pEffectCtrl->UpdateComponents( dwTime, &m );
		pInstance->pEffectCtrl->Render3( fAlpha );
		unguard;
	}
	unguard;
	unguard;
}

void CModelEffect::Release()
{
	guardfunc;

	{
		CCharEffectContainer* pContainer = GetEffectMgr()->GetCharEffectContainer( m_nEffectQuoterId );
		if (pContainer)
		{
			pContainer->ClearEffectNotDestroy(GetID());
			m_nEffectQuoterId = -1;
			m_pEffectQuoter = 0;
		}

		GetEffectMgr()->ReleaseEffectNotDestroy(GetID());
	}


	//if( m_pAnimCtrl )
	//{
	//	m_pAnimCtrl->Destroy();
	//	delete m_pAnimCtrl;
	//	m_pAnimCtrl = NULL;
	//}

	for( int nInst = 0; nInst < eMaxInstance; nInst++ )
	{
		Instance* pInstance = &m_Instances[nInst];
		if( pInstance->pEffectCtrl )
		{
			pInstance->pEffectCtrl->Destroy();
			delete pInstance->pEffectCtrl;
			pInstance->pEffectCtrl = NULL;
		}
	}

	delete this;

	unguard;
}

CModelEffect::Instance* CModelEffect::AllocInstance()
{
	guardfunc;
	if( m_nNumInstance >= eMaxInstance )
		return NULL;
	return &m_Instances[m_nNumInstance++];
	unguard;
}

CModelEffect::Instance* CModelEffect::GetInstance( int nInst )
{
	guardfunc;
	if( nInst < 0 || nInst >= eMaxInstance )
	{
		assert( false );
		return NULL;
	}
	return &m_Instances[nInst];
	unguard;

}
void CModelEffect::TryStart()
{
	guardfunc;
	{
		Start();
	}
	unguard;
}

void CModelEffect::Start()
{
	////////////////////////////MeNew project
	//if( g_bMultiThreadLoadingMex )
	//{
	//	if( !GetMeLoopThreadMan()->FindPointer( this ) )
	//	{
	//		GetMeLoopThreadMan()->RegisterPointer( this );
	//	}
	//}

	//int	nModelID =  GetMexResMgr()->AddExternalFile( m_szModel );
	//if( nModelID == -1 )
	//{
	//	assert( false );
	//	return;
	//}

	//if( g_bMultiThreadLoadingMex )
	//	TryChangePartModel( nType, iModelId, szSkin );
	//else 
	//	ChangePartModel( nType, iModelId, szSkin );
	//return;


	//////////////////////////////////old project
	int	nModelID = -1;
	if( m_szModel[0] != 0 )
	{
//		OutputDebugString("\n CModelEffect::Start ->GetIdByName \n");

        nModelID = GetMexResMgr()->GetIdByName( m_szModel );
//         if( nModelID == -1 )
// 		    nModelID = GetMexResMgr()->AddExternalFile( m_szModel );
		if( nModelID == -1 )
		{
			assert( false );
			return;
		}
		//GetMexResMgr()->CreateModel( nModelID );
		m_bMexLoaded = TRUE;
	}

	if( m_dwLife == 0 )
	{
		m_dwLife = m_dwFlyTime + SPELLACTION_CASTTIME;
	}

	float fGlobalScale = GetMe3dConfig()->m_fMdlSpaceScale;
	m_fRadius *= fGlobalScale;

	if( m_nMaxInstance > eMaxInstance )
		m_nMaxInstance = eMaxInstance;

	for( int nInst = 0; nInst < m_nMaxInstance; nInst++ )
	{
		/////////////////////old project
		Instance* pInstance = NULL;
		{
			pInstance = AllocInstance();
			pInstance->fScale *= fGlobalScale;
		}

		if( !pInstance )
			continue;

		if( pInstance->dwLife == 0 )
		{
			pInstance->dwLife = m_dwFlyTime + SPELLACTION_CASTTIME;
		}

		if( pInstance->nActionTime == 0 )
		{
			pInstance->nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
		}

		if( pInstance->pEffectCtrl )
			continue;

		pInstance->pEffectCtrl = MeNew CMexEffectCtrl;
		if( pInstance->pEffectCtrl->ChangeModel( nModelID ) )
		{
			int nNumFrame = pInstance->pEffectCtrl->GetFrameCount();
			m_nOneLoopTime = nNumFrame*ONE_FRAME_TIME;
		}
	}
	return ;
}

BOOL CModelEffect::LoadSetting( const char* pszFilename, BOOL bCreate )
{
	guardfunc;
	if( GetEffectMgr()->IsFull() )
		return FALSE;

	CEffectManager::Cache* pCache = GetEffectMgr()->GetEffectSetting( pszFilename );

	guard(test1)
	if( !pCache )
	{
		BYTE* pbyBuffer = NULL;
		int nBufferSize = 0;

		if( Compile( pszFilename, &pbyBuffer, &nBufferSize ) )
		{
			GetEffectMgr()->AddEffectSetting( pszFilename, pbyBuffer, nBufferSize );
			pCache = GetEffectMgr()->GetEffectSetting( pszFilename );
		}
		else
		{
			return FALSE;
		}
	}

	if( !pCache )
		return FALSE;
	unguard;

	guard(test2)
	if( !LoadFromMemory( pCache->pbyBuffer, pCache->nSize ) )
	{
		return FALSE;
	}
	TryStart();
	unguard;
	
	return TRUE;
	unguard;
}

BOOL CModelEffect::Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize )
{
	guardfunc;	
// 	std::string strTemp;
	int nTemp = 0;
// 	DWORD nTemp = 0;
	float fTemp = 0.f;
	
	MeXmlDocument doc;
	Common::_tstring strtarget( pszFilename );
	strtarget.Replace( ".ini", ".effect" );
    Common::_tstring strtarget_cipher = strtarget;  // 加密文件
    strtarget_cipher += 'c';
    if( !CFilePath::IsExist( strtarget_cipher.c_str() ) && !CFilePath::IsExist( strtarget.c_str() ) )
        return false;
	bool bRet = doc.LoadFile( strtarget.c_str() );
	if( !bRet )
		return false;

	MeXmlElement* pRoot = doc.FirstChildElement( "Project" );
	if( !pRoot )
		return false;

	pRoot = pRoot->FirstChildElement( "EffectConfig" );
	MeXmlElement* pElement = pRoot;
	if( !pElement )
		return false;

// 	CCfgXmlFileLoader l;
	CDataChunkWriter w;

	const char* pszMode = pElement->Attribute("ModeType");
	if( pszMode )
	{
		int nTerminateMode = eTerminateMode_Life;
// 		const char* pszMode = strTemp.c_str();
		// 计时方式
		if( stricmp( pszMode, "Life" ) == 0 )
		{
			nTerminateMode = eTerminateMode_Life;
		}
		// 等待所有inst死亡
		else if( stricmp( pszMode, "WaitAllDead" ) == 0 )
		{
			nTerminateMode = eTerminateMode_WaitAllInstanceDead;
		}
		// 父对象删除，自己不主动结束
		else if( stricmp( pszMode, "WaitParent" ) == 0 )
		{
			nTerminateMode = eTerminateMode_WaitParentDelete;
		}
		else
		{
			nTerminateMode = eTerminateMode_Life;
		}
		w.WriteIntChunk( 'mode', nTerminateMode );
	}
	else
	{
		w.Destroy();
		return FALSE;
	}

    char szModel[MAX_PATH] = {0};
    std::string strTemp;
    const char* pszTemp = pElement->Attribute("ModelPath");
    if( pszTemp )
    {
        strTemp = pszTemp;
        // 	if( l.GetAttributeString( pElement, "ModelPath", strTemp ) )
        if( !strTemp.empty() )
        {
            strcpy( szModel, strTemp.c_str() );
            w.WriteBufferChunk( 'mdl0', (void*)szModel, MAX_PATH );
        }
    }

    char szSound[MAX_PATH] = {0};
    pszTemp = pElement->Attribute("SoundPath");
    if( pszTemp )
    {
        strTemp = pszTemp;
        // 	if( l.GetAttributeString( pElement, "SoundPath", strTemp ) )
        if( !strTemp.empty() )
        {
            strcpy( szSound, strTemp.c_str() );
            w.WriteBufferChunk( 'snd0', (void*)szSound, MAX_PATH );
            w.WriteBufferChunk( 'snd1', (void*)szSound, MAX_PATH );
        }
    }

    ZeroMemory( szSound, sizeof(szSound) );
    pszTemp = pElement->Attribute("MaleSoundPath");
    if( pszTemp )
    {
        strTemp = pszTemp;
        // 	if( l.GetAttributeString( pElement, "MaleSoundPath", strTemp ) )
        if( !strTemp.empty() )
        {
            strcpy( szSound, strTemp.c_str() );
            w.WriteBufferChunk( 'snd0', (void*)szSound, MAX_PATH );
        }
    }

    ZeroMemory( szSound, sizeof(szSound) );
    pszTemp = pElement->Attribute("FemaleSoundPath");
    if( pszTemp )
    {
        strTemp = pszTemp;
        // 	if( l.GetAttributeString( pElement, "FemaleSoundPath", strTemp ) )
        if( !strTemp.empty() )
        {
            strcpy( szSound, strTemp.c_str() );
            w.WriteBufferChunk( 'snd1', (void*)szSound, MAX_PATH );
        }
    }

 	if( pElement->Attribute("LifeTime",&nTemp) )
	{
		DWORD dwLife = nTemp;
		w.WriteDwordChunk( 'life', dwLife );
	}

	int nInstNum = 0;
 	if( pElement->Attribute("Count",&nTemp))
	{
		nInstNum = nTemp;
		w.WriteIntChunk( 'num0', nInstNum );
	}

	if(pElement->Attribute("DelayTime",&nTemp)  )
	{
		DWORD dwDelay = nTemp;
		w.WriteDwordChunk( 'dely', dwDelay );
	}

	if( pElement->Attribute("Radius",&fTemp))
	{
		w.WriteFloatChunk( 'rads', fTemp * GetMe3dConfig()->m_fMdlSpaceScale );
	}

	///////////////////////CameraShake
	pszMode = pElement->Attribute("ShakeType");
// 	if( l.GetAttributeString( pElement, "ShakeType", strTemp ) )
	if(pszMode)
	{
		int m_nCameraShakeType = eNoCameraStunt;
// 		const char* pszMode = strTemp.c_str();

		if( stricmp( pszMode, "Normal" ) == 0 )
		{
			m_nCameraShakeType = eNormalShake;
		}
		else if( stricmp( pszMode, "HorizontalShake" ) == 0 )
		{
			m_nCameraShakeType = eHorizontalShake;
		}
		else if( stricmp( pszMode, "VerticalShake" ) == 0 )
		{
			m_nCameraShakeType = eVerticalShake;
		}
		else if(stricmp(pszMode,"ViewDirShake") == 0)
		{
			m_nCameraShakeType = eViewDirShake;
		}
		else
		{
			m_nCameraShakeType = eNoCameraStunt;
		}

		w.WriteIntChunk( 'camt', m_nCameraShakeType );
	}

	if( pElement->Attribute("ShakeMaxWaveRange",&fTemp))
	{
		w.WriteFloatChunk( 'masw', fTemp );
	}

	if( pElement->Attribute("ShakeMinWaveRange",&fTemp))
	{
		w.WriteFloatChunk( 'misw', fTemp );
	}

	if( pElement->Attribute("ShakeMaxRange",&fTemp))
	{
		w.WriteFloatChunk( 'masr', fTemp );
	}

	if( pElement->Attribute("ShakeMinRange",&fTemp))
	{
		w.WriteFloatChunk( 'misr', fTemp );
	}

	if( pElement->Attribute("ShakeLifeTime",&nTemp))
	{
		w.WriteDwordChunk( 'skti', nTemp );
	}

	if( pElement->Attribute("ShakeStartTime",&nTemp))
	{
		w.WriteDwordChunk( 'ssti', nTemp );
	}




	//////////////////////////////////////////////////////////////////
	///////////////////////////////////Instance
	//char szInstanceIndex[20];
	DWORD dwIns[] = 
	{
		'ins0',
		'ins1',
		'ins2',
		'ins3',
		'ins4'
	};
	pElement = pRoot->FirstChildElement( "ElementConfig" );	
	for( int i = 0 ; i < MAX_INSTANCE_COUNT ; ++ i )
	{
		if( !pElement )
			break;

		//if( l.OpenSession( "Instance" ) )
		{
			Instance inst;
			const char* pszMode = pElement->Attribute("ModeType");
//			if( l.GetAttributeString( pElement, "ModeType", strTemp ) )
			if(pszMode)
			{
// 				const char* pszMode = strTemp.c_str();
				if( stricmp( pszMode, "Life" ) == 0 )
					inst.nMode = eTerminateMode_Life;
				else if( stricmp( pszMode, "Loop" ) == 0 )
					inst.nMode = eTerminateMode_Loop;
				else 
					inst.nMode = eTerminateMode_Loop;
			}
			else 
			{
				inst.nMode = eTerminateMode_Loop;
			}

			//ZeroMemory( szModel, sizeof(szModel) );
			const char* pszTemp = pElement->Attribute("ModelPath");
// 			if( l.GetAttributeString( pElement, "ModelPath", strTemp ) )
			if(pszTemp)
			{
				strcpy( inst.szModel, pszTemp );
			}

			if( pElement->Attribute("LifeTime",&nTemp))
			{
				inst.dwLife = nTemp;
			}
			else
			{
				inst.dwLife = SPELLACTION_CASTTIME;
			}
			const char* pszLoop = pElement->Attribute("LoopCount");
//			if( l.GetAttributeString( pElement, "LoopCount", strTemp ) )
			if(pszLoop)
			{
// 				const char* pszLoop = strTemp.c_str();
				if( stricmp( pszLoop, "Forever" ) == 0 )
					inst.bLoopForever = TRUE;
				else
				{
					pElement->Attribute("LoopCount",&nTemp);
					inst.nNumLoop = nTemp;
				}
			}
			else
			{
				inst.nNumLoop = 1;
			}

			if(pElement->Attribute("Scale",&fTemp) )
			{
				inst.fScale = fTemp;
			}
			else
			{
				inst.fScale = 0;
			}

			if(pElement->Attribute("RotateCorrect",&fTemp) )
			{
				inst.fRotCorrect = fTemp / 180 * D3DX_PI;
			} 
			else
			{
				inst.fRotCorrect = D3DX_PI*0.5f;
			}

			if(pElement->Attribute("KeepAfterDead",&nTemp))
			{
				inst.dwPlayOverRenderTime = nTemp;
			}
			else
			{
				inst.dwPlayOverRenderTime = 0;
			}
			const char* pszWhere = pElement->Attribute("BindNode");
			if( pszWhere)
			{
// 				const char* pszWhere = strTemp.c_str();
				if( stricmp( pszWhere, "Body" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_Body;
				}
				else if( stricmp( pszWhere, "Head" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_Head;
				}
				else if( stricmp( pszWhere, "LeftHand" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_LeftHand;
				}
				else if( stricmp( pszWhere, "RightHand" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_RightHand;
				}
				else if( stricmp( pszWhere, "Foot" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_Foot;
				}
				else if( stricmp( pszWhere, "Spray" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_Spray;
				}
				else if( stricmp( pszWhere, "Back" ) == 0 )
				{
					inst.nBindWhere = eEffectBindPart_Back;
				}
				else
				{
					inst.nBindWhere = eEffectBindPart_Body;
				}
			}
			else
			{
				inst.nBindWhere = eEffectBindPart_Body;
			}
			pszWhere = pElement->Attribute("TargetBindNode");
			if( pszWhere)
			{
// 				const char* pszWhere = strTemp.c_str();
				if( stricmp( pszWhere, "Body" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_Body;
				}
				else if( stricmp( pszWhere, "Head" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_Head;
				}
				else if( stricmp( pszWhere, "LeftHand" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_LeftHand;
				}
				else if( stricmp( pszWhere, "RightHand" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_RightHand;
				}
				else if( stricmp( pszWhere, "Foot" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_Foot;
				}
				else if( stricmp( pszWhere, "Spray" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_Spray;
				}
				else if( stricmp( pszWhere, "Back" ) == 0 )
				{
					inst.nTargetBindWhere = eEffectBindPart_Back;
				}
				else
				{
					inst.nTargetBindWhere = eEffectBindPart_Body;
				}
			}
			else
			{
				inst.nTargetBindWhere = eEffectBindPart_Body;
			}
			const char* pszAction = pElement->Attribute("ActionType");
			if( pszAction )
			{
// 				const char* pszAction = strTemp.c_str();
				if( stricmp( pszAction, "Follow" ) == 0 )
				{
					inst.nAction = eActionFollow;
				}
				else if( stricmp( pszAction, "FollowPos" ) == 0 )
				{
					inst.nAction = eActionFollowPos;
				}
				else if( stricmp( pszAction, "FollowPt" ) == 0 )
				{
					inst.nAction = eActionFollowPoint;
				}
				else if( stricmp( pszAction, "Trace" ) == 0 )
				{
					inst.nAction = eActionTrace;
				}
				else if( stricmp( pszAction, "PtNpc" ) == 0 )
				{
					inst.nAction = eActionPointToNpc;
				}
				else if( stricmp( pszAction, "Fall" ) == 0 )
				{
					inst.nAction = eActionFall;
				}
				else if( stricmp( pszAction, "Spray" ) == 0 )
				{
					inst.nAction = eActionSpray;
				}
				else if( stricmp( pszAction, "FollowSpray" ) == 0 )
				{
					inst.nAction = eActionFollowSpray;
				}
				else if( stricmp( pszAction, "SkillBarCollect" ) == 0 )
				{
					inst.nAction = eActionSkillBarCollect;
				}
				// added, jiayi, [2009/7/20], point aoe
				else if( stricmp( pszAction, "PointAoe" )  == 0 )
				{
					inst.nAction = eActionPointAoe;
				}
				//add by yanli 2010-6-30
				//--------------------------------------------------
				else if (stricmp( pszAction, "FollowCamera" )  == 0 )
				{
					inst.nAction = eActionFollowCamera;
				}
				//--------------------------------------------------
				else
				{
					inst.nAction = eActionStand;
				}
			}

			if( pElement->Attribute("RotateTogether",&nTemp))
			{
				inst.bRotateTogether = nTemp;
			}

			// added, jiayi, [2009/10/19]
			if(pElement->Attribute("OriginalSize",&nTemp) )
			{
				inst.bOriginalSize = nTemp;
			}

            // added by zhuomeng.hu    [5/17/2011]
            if( pElement->Attribute( "OriginalAlpha", &nTemp ) )
            {
                inst.bOriginalAlpha = nTemp;
            }

			if( pElement->Attribute("ActionTime",&nTemp))
			{
				inst.nActionTime = nTemp;
			}
			else
			{
				inst.nActionTime = -SPELLACTION_CASTTIME;
			}

			if(pElement->Attribute("InvisibleAfterAction",&nTemp) )
			{
				inst.bDisapearAfterAction = nTemp;
			}
			else
			{
				inst.bDisapearAfterAction = FALSE;
			}
			const char* pszType = pElement->Attribute("TrackType");
			if( pszType )
			{
// 				const char* pszType = strTemp.c_str();
				if( stricmp( pszType, "Line" ) == 0 )
				{
					inst.nTrackType = eTrackTypeLine;
				}
				else if( stricmp( pszType, "Para" ) == 0 )
				{
					inst.nTrackType = eTrackTypeParabola;
				}
				else if( stricmp( pszType, "Gravity" ) == 0 )
				{
					inst.nTrackType = eTrackTypeGravity;
				}
				else
				{
					inst.nTrackType = eTrackTypeLine;
				}
			}
			else
			{
				inst.nTrackType = eTrackTypeLine;
			}

			if(pElement->Attribute("ParHeight",&fTemp))
			{
				inst.fParabolaHeight = fTemp * GetMe3dConfig()->m_fMdlSpaceScale;
			}
			else
			{
				inst.fParabolaHeight = 0.0f;
			}

			if(pElement->Attribute("FallHeight",&fTemp) )
			{
				inst.fFallHeight = fTemp * GetMe3dConfig()->m_fMdlSpaceScale;
			}
			else
			{
				inst.fFallHeight = 0.0f;
			}

			// added, jiayi, [2009/6/2]
			if(pElement->Attribute("DelayTime",&fTemp) )
			{
				inst.fDelay = fTemp;
			}

            // 此字段仅在 Track 类型为抛物线 或 Line类型ParHeight大于0 时有效      added by zhuomeng.hu		[3/4/2011]
            if( pElement->Attribute( "ParabolaAngle", &fTemp ) )
            {
                inst.fParabolaAngle = fTemp;
            }

            pszTemp = pElement->Attribute( "HitEffectName" );
            if( pszTemp )
            {
                strcpy( inst.szHitEffect, pszTemp );
            }

			w.OpenChunk( dwIns[i] );
			{
				w.WriteIntChunk(	'mode', inst.nMode );
				w.WriteBufferChunk( 'modl', inst.szModel, sizeof(inst.szModel) );
				w.WriteDwordChunk(	'life', inst.dwLife );
				w.WriteIntChunk(	'nlop', inst.nNumLoop );
				w.WriteIntChunk(	'lfor', inst.bLoopForever );
				w.WriteFloatChunk(	'scal', inst.fScale );
				w.WriteFloatChunk(	'rcor', inst.fRotCorrect );
				w.WriteIntChunk(	'bwhe', inst.nBindWhere );
				w.WriteIntChunk(	'twhe', inst.nTargetBindWhere );
				w.WriteIntChunk(	'act0', inst.nAction );
				w.WriteIntChunk(	'actt', inst.nActionTime );
				w.WriteIntChunk(	'rott', inst.bRotateTogether );
				w.WriteIntChunk(	'dafa', inst.bDisapearAfterAction );
				w.WriteIntChunk(	'ttyp', inst.nTrackType );
				w.WriteFloatChunk(	'parh', inst.fParabolaHeight );
				w.WriteFloatChunk(	'falh', inst.fFallHeight );
				w.WriteDwordChunk(	'ddrt', inst.dwPlayOverRenderTime );
				w.WriteFloatChunk(  'dely', inst.fDelay );
				w.WriteIntChunk(    'osiz', inst.bOriginalSize );
                w.WriteIntChunk(    'oalp', inst.bOriginalAlpha );
                w.WriteFloatChunk(  'pagl', inst.fParabolaAngle );
                w.WriteBufferChunk( 'phef', inst.szHitEffect, sizeof( inst.szHitEffect ) );
			}
			w.CloseChunk( dwIns[i] );
		}
		pElement = pElement->NextSiblingElement( "ElementConfig" );
	}

	if( ppbyBuffer && pnBufferSize )
	{
		int nUsed = w.GetUsedSize();
		BYTE* pbyBuffer = MeDefaultNew BYTE[nUsed];
		memcpy( pbyBuffer, w.GetBuffer(), nUsed );
		*ppbyBuffer = pbyBuffer;
		*pnBufferSize = nUsed;
	}
	w.Destroy();
	return TRUE;
	unguard;
}


BOOL CModelEffect::LoadFromMemory( BYTE* pbyBuffer, int nBufferSize )
{
	CDataChunkLoader l( pbyBuffer, nBufferSize );
	while( !l.IsEndOfMemory() )
	{
		if( l.TryReadIntChunk( 'mode', m_nTerminateMode ) ){}
		else if( l.IsChunk( 'mdl0' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_szModel, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.IsChunk( 'snd0' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_szMaleSound, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.IsChunk( 'snd1' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_szFemaleSound, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.TryReadDwordChunk( 'life', m_dwLife ) ){}
		else if( l.TryReadIntChunk( 'num0', m_nMaxInstance ) ){}
		else if( l.TryReadDwordChunk( 'dely', m_dwDelay ) ){}
		else if( l.TryReadFloatChunk( 'rads', m_fRadius ) ){}
		else if( l.TryReadIntChunk( 'camt', m_nCameraShakeType ) ){}
		else if( l.TryReadFloatChunk( 'masw', m_fMaxShakeWaveRange ) ){}
		else if( l.TryReadFloatChunk( 'misw', m_fMinShakeWaveRange ) ){}
		else if( l.TryReadFloatChunk( 'masr', m_fMaxShakeRange ) ){}
		else if( l.TryReadFloatChunk( 'misr', m_fMinShakeRange ) ){}
		else if( l.TryReadDwordChunk( 'skti', m_dwShakeKeepTime ) ){}
		else if( l.TryReadDwordChunk( 'ssti', m_dwShakeStartTime ) ){}
		else if( l.IsChunk( 'ins0' ) )
		{
			l.OpenChunk();
			Instance& inst = m_Instances[0];
			while( !l.IsEndOfChunk() )
			{
				if( l.TryReadIntChunk(			'mode', inst.nMode ) ){}
				else if( l.IsChunk( 'modl' ) )
				{
					l.OpenChunk();
					l.ReadToBuffer( (BYTE*)inst.szModel, MAX_PATH );
					l.CloseChunk();
				}
				else if( l.TryReadDwordChunk(	'life', inst.dwLife ) ){}
				else if( l.TryReadIntChunk(		'nlop', inst.nNumLoop ) ){}
				else if( l.TryReadIntChunk(		'lfor', inst.bLoopForever ) ){}
				else if( l.TryReadFloatChunk(	'scal', inst.fScale ) ){}
				else if( l.TryReadFloatChunk(	'rcor', inst.fRotCorrect ) ){}
				else if( l.TryReadIntChunk(		'bwhe', inst.nBindWhere ) ){}
				else if( l.TryReadIntChunk(		'twhe', inst.nTargetBindWhere ) ){}
				else if( l.TryReadIntChunk(		'act0', inst.nAction ) ){}
				else if( l.TryReadIntChunk(		'actt', inst.nActionTime ) ){}
				else if( l.TryReadIntChunk(		'rott', inst.bRotateTogether ) ){}
				else if( l.TryReadIntChunk(		'dafa', inst.bDisapearAfterAction ) ){}
				else if( l.TryReadIntChunk(		'ttyp', inst.nTrackType ) ){}
				else if( l.TryReadFloatChunk(	'parh', inst.fParabolaHeight ) ){}
				else if( l.TryReadFloatChunk(	'falh', inst.fFallHeight ) ){}
				else if( l.TryReadDwordChunk(	'ddrt', inst.dwPlayOverRenderTime ) ){}
				else if( l.TryReadFloatChunk(	'dely', inst.fDelay ) ){}
				else if( l.TryReadIntChunk(	    'osiz', inst.bOriginalSize ) ){}
                else if( l.TryReadIntChunk(	    'oalp', inst.bOriginalAlpha ) ){}
                else if( l.TryReadFloatChunk(   'pagl', inst.fParabolaAngle ) ){}
                else if( l.IsChunk( 'phef' ) )
                {
                    l.OpenChunk();
                    l.ReadToBuffer( ( BYTE* )inst.szHitEffect, MAX_PATH );
                    l.CloseChunk();
                }
				else l.SkipChunk();
			}

			if( m_dwFlyTime > 0 )
			{
				// commented out,  jiayi, [2009/7/28]
				inst.nActionTime = m_dwFlyTime/* - SPELLACTION_CASTTIME*/;
			}

			if( inst.fScale == 0)
			{
				inst.fScale = m_fScale;
			}

			// 拷贝
			m_InstTemplate = inst;
			l.CloseChunk();
		}
		else if( l.IsChunk( 'ins1' ) )
		{
			l.OpenChunk();
			Instance& inst = m_Instances[1];
			while( !l.IsEndOfChunk() )
			{
				if( l.TryReadIntChunk(			'mode', inst.nMode ) ){}
				else if( l.IsChunk( 'modl' ) )
				{
					l.OpenChunk();
					l.ReadToBuffer( (BYTE*)inst.szModel, MAX_PATH );
					l.CloseChunk();
				}
				else if( l.TryReadDwordChunk(	'life', inst.dwLife ) ){}
				else if( l.TryReadIntChunk(		'nlop', inst.nNumLoop ) ){}
				else if( l.TryReadIntChunk(		'lfor', inst.bLoopForever ) ){}
				else if( l.TryReadFloatChunk(	'scal', inst.fScale ) ){}
				else if( l.TryReadFloatChunk(	'rcor', inst.fRotCorrect ) ){}
				else if( l.TryReadIntChunk(		'bwhe', inst.nBindWhere ) ){}
				else if( l.TryReadIntChunk(		'twhe', inst.nTargetBindWhere ) ){}
				else if( l.TryReadIntChunk(		'act0', inst.nAction ) ){}
				else if( l.TryReadIntChunk(		'actt', inst.nActionTime ) ){}
				else if( l.TryReadIntChunk(		'rott', inst.bRotateTogether ) ){}
				else if( l.TryReadIntChunk(		'dafa', inst.bDisapearAfterAction ) ){}
				else if( l.TryReadIntChunk(		'ttyp', inst.nTrackType ) ){}
				else if( l.TryReadFloatChunk(	'parh', inst.fParabolaHeight ) ){}
				else if( l.TryReadFloatChunk(	'falh', inst.fFallHeight ) ){}
				else if( l.TryReadDwordChunk(	'ddrt', inst.dwPlayOverRenderTime ) ){}
				else if( l.TryReadFloatChunk(	'dely', inst.fDelay ) ){}
				else if( l.TryReadIntChunk(	    'osiz', inst.bOriginalSize ) ){}
                else if( l.TryReadIntChunk(	    'oalp', inst.bOriginalAlpha ) ){}
                else if( l.TryReadFloatChunk(   'pagl', inst.fParabolaAngle ) ){}
                else if( l.IsChunk( 'phef' ) )
                {
                    l.OpenChunk();
                    l.ReadToBuffer( ( BYTE* )inst.szHitEffect, MAX_PATH );
                    l.CloseChunk();
                }
				else l.SkipChunk();
			}

			if( m_dwFlyTime > 0 )
			{
				// commented out, jiayi, [2009/7/28]
				inst.nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
			}

			if( inst.fScale == 0)
			{
				inst.fScale = m_fScale;
			}

			// 拷贝
			m_InstTemplate = inst;
			l.CloseChunk();
		}
		else if( l.IsChunk( 'ins2' ) )
		{
			l.OpenChunk();
			Instance& inst = m_Instances[2];
			while( !l.IsEndOfChunk() )
			{
				if( l.TryReadIntChunk(			'mode', inst.nMode ) ){}
				else if( l.IsChunk( 'modl' ) )
				{
					l.OpenChunk();
					l.ReadToBuffer( (BYTE*)inst.szModel, MAX_PATH );
					l.CloseChunk();
				}
				else if( l.TryReadDwordChunk(	'life', inst.dwLife ) ){}
				else if( l.TryReadIntChunk(		'nlop', inst.nNumLoop ) ){}
				else if( l.TryReadIntChunk(		'lfor', inst.bLoopForever ) ){}
				else if( l.TryReadFloatChunk(	'scal', inst.fScale ) ){}
				else if( l.TryReadFloatChunk(	'rcor', inst.fRotCorrect ) ){}
				else if( l.TryReadIntChunk(		'bwhe', inst.nBindWhere ) ){}
				else if( l.TryReadIntChunk(		'twhe', inst.nTargetBindWhere ) ){}
				else if( l.TryReadIntChunk(		'act0', inst.nAction ) ){}
				else if( l.TryReadIntChunk(		'actt', inst.nActionTime ) ){}
				else if( l.TryReadIntChunk(		'rott', inst.bRotateTogether ) ){}
				else if( l.TryReadIntChunk(		'dafa', inst.bDisapearAfterAction ) ){}
				else if( l.TryReadIntChunk(		'ttyp', inst.nTrackType ) ){}
				else if( l.TryReadFloatChunk(	'parh', inst.fParabolaHeight ) ){}
				else if( l.TryReadFloatChunk(	'falh', inst.fFallHeight ) ){}
				else if( l.TryReadDwordChunk(	'ddrt', inst.dwPlayOverRenderTime ) ){}
				else if( l.TryReadFloatChunk(	'dely', inst.fDelay ) ){}
				else if( l.TryReadIntChunk(	    'osiz', inst.bOriginalSize ) ){}
                else if( l.TryReadIntChunk(	    'oalp', inst.bOriginalAlpha ) ){}
                else if( l.TryReadFloatChunk(   'pagl', inst.fParabolaAngle ) ){}
                else if( l.IsChunk( 'phef' ) )
                {
                    l.OpenChunk();
                    l.ReadToBuffer( ( BYTE* )inst.szHitEffect, MAX_PATH );
                    l.CloseChunk();
                }
				else l.SkipChunk();
			}

			if( m_dwFlyTime > 0 )
			{
				// commented out, jiayi, [2009/7/28]
				inst.nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
			}

			if( inst.fScale == 0)
			{
				inst.fScale = m_fScale;
			}

			// 拷贝
			m_InstTemplate = inst;
			l.CloseChunk();
		}
		else if( l.IsChunk( 'ins3' ) )
		{
			l.OpenChunk();
			Instance& inst = m_Instances[3];
			while( !l.IsEndOfChunk() )
			{
				if( l.TryReadIntChunk(			'mode', inst.nMode ) ){}
				else if( l.IsChunk( 'modl' ) )
				{
					l.OpenChunk();
					l.ReadToBuffer( (BYTE*)inst.szModel, MAX_PATH );
					l.CloseChunk();
				}
				else if( l.TryReadDwordChunk(	'life', inst.dwLife ) ){}
				else if( l.TryReadIntChunk(		'nlop', inst.nNumLoop ) ){}
				else if( l.TryReadIntChunk(		'lfor', inst.bLoopForever ) ){}
				else if( l.TryReadFloatChunk(	'scal', inst.fScale ) ){}
				else if( l.TryReadFloatChunk(	'rcor', inst.fRotCorrect ) ){}
				else if( l.TryReadIntChunk(		'bwhe', inst.nBindWhere ) ){}
				else if( l.TryReadIntChunk(		'twhe', inst.nTargetBindWhere ) ){}
				else if( l.TryReadIntChunk(		'act0', inst.nAction ) ){}
				else if( l.TryReadIntChunk(		'actt', inst.nActionTime ) ){}
				else if( l.TryReadIntChunk(		'rott', inst.bRotateTogether ) ){}
				else if( l.TryReadIntChunk(		'dafa', inst.bDisapearAfterAction ) ){}
				else if( l.TryReadIntChunk(		'ttyp', inst.nTrackType ) ){}
				else if( l.TryReadFloatChunk(	'parh', inst.fParabolaHeight ) ){}
				else if( l.TryReadFloatChunk(	'falh', inst.fFallHeight ) ){}
				else if( l.TryReadDwordChunk(	'ddrt', inst.dwPlayOverRenderTime ) ){}
				else if( l.TryReadFloatChunk(	'dely', inst.fDelay ) ){}
				else if( l.TryReadIntChunk(	    'osiz', inst.bOriginalSize ) ){}
                else if( l.TryReadIntChunk(	    'oalp', inst.bOriginalAlpha ) ){}
                else if( l.TryReadFloatChunk(   'pagl', inst.fParabolaAngle ) ){}
                else if( l.IsChunk( 'phef' ) )
                {
                    l.OpenChunk();
                    l.ReadToBuffer( ( BYTE* )inst.szHitEffect, MAX_PATH );
                    l.CloseChunk();
                }
				else l.SkipChunk();
			}

			if( m_dwFlyTime > 0 )
			{
				// commented out, jiayi, [2009/7/28]
				inst.nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
			}

			if( inst.fScale == 0)
			{
				inst.fScale = m_fScale;
			}

			// 拷贝
			m_InstTemplate = inst;
			l.CloseChunk();
		}
		else if( l.IsChunk( 'ins4' ) )
		{
			l.OpenChunk();
			Instance& inst = m_Instances[4];
			while( !l.IsEndOfChunk() )
			{
				if( l.TryReadIntChunk(			'mode', inst.nMode ) ){}
				else if( l.IsChunk( 'modl' ) )
				{
					l.OpenChunk();
					l.ReadToBuffer( (BYTE*)inst.szModel, MAX_PATH );
					l.CloseChunk();
				}
				else if( l.TryReadDwordChunk(	'life', inst.dwLife ) ){}
				else if( l.TryReadIntChunk(		'nlop', inst.nNumLoop ) ){}
				else if( l.TryReadIntChunk(		'lfor', inst.bLoopForever ) ){}
				else if( l.TryReadFloatChunk(	'scal', inst.fScale ) ){}
				else if( l.TryReadFloatChunk(	'rcor', inst.fRotCorrect ) ){}
				else if( l.TryReadIntChunk(		'bwhe', inst.nBindWhere ) ){}
				else if( l.TryReadIntChunk(		'twhe', inst.nTargetBindWhere ) ){}
				else if( l.TryReadIntChunk(		'act0', inst.nAction ) ){}
				else if( l.TryReadIntChunk(		'actt', inst.nActionTime ) ){}
				else if( l.TryReadIntChunk(		'rott', inst.bRotateTogether ) ){}
				else if( l.TryReadIntChunk(		'dafa', inst.bDisapearAfterAction ) ){}
				else if( l.TryReadIntChunk(		'ttyp', inst.nTrackType ) ){}
				else if( l.TryReadFloatChunk(	'parh', inst.fParabolaHeight ) ){}
				else if( l.TryReadFloatChunk(	'falh', inst.fFallHeight ) ){}
				else if( l.TryReadDwordChunk(	'ddrt', inst.dwPlayOverRenderTime ) ){}
				else if( l.TryReadFloatChunk(	'dely', inst.fDelay ) ){}
				else if( l.TryReadIntChunk(	    'osiz', inst.bOriginalSize ) ){}
                else if( l.TryReadIntChunk(	    'oalp', inst.bOriginalAlpha ) ){}
                else if( l.TryReadFloatChunk(   'pagl', inst.fParabolaAngle ) ){}
                else if( l.IsChunk( 'phef' ) )
                {
                    l.OpenChunk();
                    l.ReadToBuffer( ( BYTE* )inst.szHitEffect, MAX_PATH );
                    l.CloseChunk();
                }
				else l.SkipChunk();
			}

			if( m_dwFlyTime > 0 )
			{
				// commented out, jiayi, [2009/7/28]
				inst.nActionTime = m_dwFlyTime - SPELLACTION_CASTTIME;
			}

			if( inst.fScale == 0)
			{
				inst.fScale = m_fScale;
			}

			// 拷贝
			m_InstTemplate = inst;
			l.CloseChunk();
		}
		else l.SkipChunk();
	}

	if( m_dwFlyTime > 0 )
	{
		m_dwLife = m_dwFlyTime + 6000;
	}
	return TRUE;
}

void CModelEffect::SetEffectQuoter(IEffectQuoter *pEffectQuoter)
{
	m_nEffectQuoterId = -1;
	m_pEffectQuoter = pEffectQuoter;
	if (m_pEffectQuoter)
	{
		CCharEffectContainer* pContainer = dynamic_cast<CCharEffectContainer*>(m_pEffectQuoter);
		if (pContainer)
		{
			m_nEffectQuoterId = pContainer->GetId();
		}
	}
}

//void CModelEffect::Cull( D3DXVECTOR3 vPos, float fDistance )
//{
//	guardfunc;
//
//	unguard;
//}