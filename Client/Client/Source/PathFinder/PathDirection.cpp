/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	CPathDirection.cpp
* Create: 	10/14/06
* Desc:		地图类
* Author:	yuanding
*
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "GameMain.h"
#include "PathDirection.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "WSModelEffect.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "Cfg.h"
extern CHeroGame* theApp;
extern CCfg gCfg;
CPathDirection::CPathDirection()
{
	Reset();
	m_fMaxStep = gCfg.m_fPathDirectionMaxStep;
	m_fMinStep = gCfg.m_fPathDirectionMinStep;
}

CPathDirection::~CPathDirection()
{
	for (int i = 0; i < mDecalArr.size();++i)
	{
		SAFE_DELETE(mDecalArr[i].m_effect);

		if (mDecalArr[i].nEffectContainerID != -1)	
		{	
			CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( mDecalArr[i].nEffectContainerID );	
			if( pEffectContainer )	
				pEffectContainer->FlagDestroy();	
		}	
	}
	mDecalArr.clear();
	mVecArr.clear();
}
extern DWORD g_dwLastFrameBeginTime;
void CPathDirection::Reset()
{
	m_bActive = false;
	m_effectNum = 0;
	m_movingStep = 0;
	mVecArr.clear();
	SetVisible(false);
}

void CPathDirection::CreateEffectArr(const std::vector<swVec2f>& path)
{
	Reset();
	int pathCorner = path.size();
	for(int i = 1; i < pathCorner; ++i )
	{
		swVec2f direct(path[i].x- path[i - 1].x,path[i].y- path[i - 1].y);
		float len = sqrt(direct.x*direct.x + direct.y*direct.y);
		if (len < m_fMinStep)
		{
			continue;
		}
		int nCount = 1;
		while(len - (nCount - 1)*m_fMaxStep > m_fMaxStep)
		{
			++nCount;
		}
		for (int j = 0; j < nCount;++j)
		{
			D3DXVECTOR3 pos;
			pos.x = path[i - 1].x + j*direct.x/nCount;
			pos.y = path[i - 1].y + j*direct.y/nCount;
//这个调用可能引起多线程冲突（GetZByXY里面使用静态数组作为返回值，多线程不安全），现在这个z值不需要，所以可以注掉，如果以后有新的需求，要把这个z值计算放在线程外面做。
// 			BOOL bInFloor = FALSE;
// 			pos.z = SwGlobal::GetWorldPicker()->GetZByXY( WORLD_HEIGHT,  pos.x, pos.y, 0 ,&bInFloor) + 0.2;
			SetEffectInstance(pos,swVec2f(direct.x/len,direct.y/len));
		}
	}
	//函数体最后对m_bActive赋值
	m_bActive = true;
	SetVisible(true);
}

CPathDirection::SPathEffect CPathDirection::CreateEffect( )
{
	CPathDirection::SPathEffect effect;

	effect.m_effect = MeNew CWSModelEffect;
	char filename[MAX_PATH] = {0};
	_snprintf( filename, MAX_PATH-1, "%s\\data\\effect\\Common\\PathDirection.ini" , GetRootPath());
	if( effect.m_effect->LoadSetting( filename ) )
	{
		int nEffectId = GetEffectMgr()->RegisterEffect( effect.m_effect );
		if( nEffectId == -1 )
		{
			effect.m_effect->Release();
			effect.m_effect = NULL;
		}
		else
		{
			effect.m_effect->m_dwBornTime = HQ_TimeGetTime();

			effect.nEffectContainerID = GetEffectMgr()->RegisterCharEffectContainer();
			CCharEffectContainer* pEffectContainer = GetEffectMgr()->GetCharEffectContainer( effect.nEffectContainerID );

			if( pEffectContainer )
			{
				effect.m_effect->SetEffectQuoter( pEffectContainer );
				pEffectContainer->ApplyEffect( 0, effect.m_effect->GetID() );
			}
		}
	}
	else
	{
		effect.m_effect->Release();
		effect.m_effect = NULL;
	}
	return effect;
}

bool CPathDirection::UpdatePathDirection()
{
	
	if (!IsActive() )
	{
		return false;
	}
	static bool sbReachable = false;
	if (m_movingStep == m_effectNum)
	{
		Reset();
		sbReachable = false;
		return false;
	}
	swVec2f v = mVecArr[m_movingStep];
	if( !theHeroGame.GetPlayerMgr()->GetMe() )
		return false;
	float posx,posy;
	theApp->GetPlayerMgr()->GetMe()->GetPos(&posx,&posy,NULL);
	float dis = (posx-v.x)*(posx-v.x)  + (posy-v.y)*(posy-v.y)  ;
	if (sbReachable)
	{
		if (dis> m_fMinStep/2)
		{
			sbReachable = false;
			++m_movingStep;
		}
	}
	else
	{
		if (dis< m_fMinStep/2)
		{
			sbReachable = true;
		}

	}
	return true;
}

bool CPathDirection::SetEffectInstance(D3DXVECTOR3& pos,swVec2f& dir)
{
	++m_effectNum;
	mVecArr.push_back(swVec2f(pos.x,pos.y));
	return true;
	int instanceIndex = 0;
	if (m_effectNum > mDecalArr.size())
	{
		Assert(m_effectNum - mDecalArr.size() == 1);
		{
			SPathEffect effect = CreateEffect();
			if (effect.m_effect)
			{
				mDecalArr.push_back(effect);
			}
			else
			{
				return false;
			}
		}
	}
	SPathEffect* pEffect = &mDecalArr[m_effectNum - 1];
	CWSModelEffect::Instance* pInstance = pEffect->m_effect->GetInstance(instanceIndex);
	if( !pInstance )
	{
		return false;
	}
	pEffect->m_effect->m_nNumInstance = instanceIndex + 1;
	pEffect->m_effect->m_nMaxInstance = instanceIndex + 1;
	pInstance->bDead = false;

	pInstance->dwBornTime = HQ_TimeGetTime() + pInstance->fDelay;


	pInstance->vBornPos = pos;
	pInstance->vPos = pInstance->vBornPos;
	pInstance->bVisible = true;
	pInstance->fRot = SwPublicFunc::NiFastATan2(dir.y,dir.x) + PI/2;

	CCharEffectContainer* pEffectContainer = (CCharEffectContainer*)pEffect->m_effect->GetEffectQuoter();
	// 把特效绑定
	if( pEffectContainer )
	{
		pInstance->pMaster = pEffectContainer->GetEffectHelper( eEffectBindPart_Body );
		pInstance->pMaster->SetPos( pos.x, pos.y, pos.z );
	}
	return true;
}

void CPathDirection::GetDirectionPos(int index,float& posx,float& posy )
{
	Assert(index >= m_movingStep && index < m_effectNum);
	posx = mVecArr[index].x;
	posy = mVecArr[index].y;
	return;
	CWSModelEffect* pEffect = mDecalArr[index].m_effect;
	CWSModelEffect::Instance* pInstance = pEffect->GetInstance(0);
	posx = pInstance->vPos.x;
	posy = pInstance->vPos.y;

}

void CPathDirection::SetVisible( bool val )
{
	return;
	if (m_visible && !val)
	{
		for (int i = m_movingStep; i < mDecalArr.size();++i)
		{
			CWSModelEffect* pEffect = mDecalArr[i].m_effect;
			for( int nInst = 0; nInst < pEffect->m_nNumInstance; nInst++ )
			{
				CWSModelEffect::Instance* pInstance = pEffect->GetInstance( nInst );
				if( !pInstance )
				{
					continue;
				}
				pInstance->bVisible = false;
				pInstance->dwVisibleChangeTime = g_dwLastFrameBeginTime;
			}
			pEffect->m_nNumInstance = 0;
			pEffect->m_nMaxInstance = 0;
		}
	}
	m_visible = val;
}