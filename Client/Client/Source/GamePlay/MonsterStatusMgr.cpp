	
#include "Me3d\include.h"
#include "Me3d/MoreAction.h"
#include "Me3d/AnimTimeline.h"
#include "Stdcharskeleton.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "actionqueue.h"
#include "player.h"
#include "playerrole.h"
#include "PlayerMgr.h"
#include "playeranimctrl.h"
#include "gamemain.h"
#include "effect.h"
#include <assert.h>
#include "MeAudio/MeAudio.h"
#include "Me3d/Effect/EffectManager.h"
#include "MonsterStatusMgr.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "core/Name.h"
#include "MonsterDefine.h"
extern int PlayEffect (const char* pEffectName, 
					   CPlayer* pSrcPlayer = NULL, 
					   float fScale = 0 ,
					   DWORD dwFlyTime = 0,
					   CPlayer* pDestPlayer = NULL,
					   int nSlot = 0 ,
					   bool bCalDist = true);

extern const char* GetRootPath();


void MonsterStatusMgr::ChangeMonsterStatus( GameObjectId nPlayerId,int nMonsterId,uint8 nTypeStatus )
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(nPlayerId);
	if (!pPlayer)
	{
		return;
	}
	MonsterStatusIter iter = m_mapMonsterStatus.find(nPlayerId);
	if (iter == m_mapMonsterStatus.end())
	{
		SMonsterStatus status;
		status.m_PlayerId = nPlayerId;
		status.m_StatusData = theMonsterStatusConfig.GetStatusData(nMonsterId);
		if (status.m_StatusData == NULL)
		{
			return;
		}
		m_mapMonsterStatus.insert(make_pair(nPlayerId,status));
	}
	iter = m_mapMonsterStatus.find(nPlayerId);
	SMonsterStatus& status = iter->second;
	status.m_StatusSetting = status.m_StatusData->GetStatusSetting(nTypeStatus);
	status.m_dwCurrStatusBeginTime = HQ_TimeGetTime();
	if (status.m_StatusSetting)
	{
		ReleaseLastAndPlayStatusEffect(status, status.m_StatusSetting->GetEffect());
		if (status.m_StatusSetting->GetModelID() != -1)
		{
			pPlayer->MorphMonster(status.m_StatusSetting->GetModelID());
		}
		if (nTypeStatus == MonsterDefine::StatusMonsterDeath)
		{
			pPlayer->SwitchDieAnim();
		}
		//设置初始偏移，初始通道值，初始缩放值
		if (status.m_StatusSetting->GetStartScale() != 1.0f)
		{
			pPlayer->SetPlayerScale(status.m_StatusSetting->GetStartScale());
		}
		if (status.m_StatusSetting->GetStartAlpha() != 1.0f)
		{
			pPlayer->SetCurRenderAlpha((float)status.m_StatusSetting->GetStartAlpha());
		}
		if (status.m_StatusSetting->GetStartOffsetX() !=0.0f || status.m_StatusSetting->GetStartOffsetY() !=0.0f || status.m_StatusSetting->GetStartOffsetZ() !=0.0f)
		{
			D3DXVECTOR3 v = pPlayer->GetPos();
			status.m_vRealPosition = v;
			v.x += status.m_StatusSetting->GetStartOffsetX();
			v.y += status.m_StatusSetting->GetStartOffsetY();
			v.z += status.m_StatusSetting->GetStartOffsetZ();
			pPlayer->SetPos(v.x, v.y, v.z);
		}
		if (status.m_StatusSetting->GetArrStatusSect().size() > 0)
		{
			status.m_nStatusSect = 0;
			ProcessStatusSect(status);
		}
	}

}
void MonsterStatusMgr::ProcessStatus(SMonsterStatus &status)
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(status.m_PlayerId);
	if (!pPlayer)
	{
		return;
	}
	if( !status.m_StatusSetting )
		return;

	
    if(status.m_StatusSetting->GetStatus() == status.m_StatusData->GetInitStatus()) //当前状态为初始化状态 
		return ;
		

	//取得alpha值并加上
	DWORD dwCurrentTime = HQ_TimeGetTime();
	float fCurrentAlpha = pPlayer->GetCurRenderAlpha();
	if (fCurrentAlpha <= status.m_StatusSetting->GetEndAlpha())
	{
		fCurrentAlpha = status.m_StatusSetting->GetStartAlpha() + (dwCurrentTime - status.m_dwCurrStatusBeginTime) * (status.m_StatusSetting->GetEndAlpha() - status.m_StatusSetting->GetStartAlpha()) / status.m_StatusSetting->GetSpaceTime();
		pPlayer->SetCurRenderAlpha(fCurrentAlpha);
	}	
	float fCurrentScale = pPlayer->GetPlayerScale();
	if (fCurrentScale <= status.m_StatusSetting->GetEndScale())
	{
		fCurrentScale = status.m_StatusSetting->GetStartScale() + (dwCurrentTime - status.m_dwCurrStatusBeginTime) * (status.m_StatusSetting->GetEndScale() - status.m_StatusSetting->GetStartScale()) / status.m_StatusSetting->GetSpaceTime();
		pPlayer->SetPlayerScale(fCurrentScale);
	}
	//D3DXVECTOR3 v = pPlayer->GetPos();
	//if (v.x != status.m_StatusSetting->GetEndOffsetX() + status.m_vRealPosition.x
	//	|| v.x != status.m_StatusSetting->GetEndOffsetY() + status.m_vRealPosition.y
	//	|| v.z != status.m_StatusSetting->GetEndOffsetZ() + status.m_vRealPosition.z)
	//{
	//	v.x = status.m_vRealPosition.x + (dwCurrentTime - status.m_dwCurrStatusBeginTime) * (status.m_StatusSetting->GetEndOffsetX() - status.m_StatusSetting->GetStartOffsetX()) / status.m_StatusSetting->GetSpaceTime();
	//	v.y = status.m_vRealPosition.y + (dwCurrentTime - status.m_dwCurrStatusBeginTime) * (status.m_StatusSetting->GetEndOffsetY() - status.m_StatusSetting->GetStartOffsetY()) / status.m_StatusSetting->GetSpaceTime();
	//	v.z = status.m_vRealPosition.z + (dwCurrentTime - status.m_dwCurrStatusBeginTime) * (status.m_StatusSetting->GetEndOffsetZ() - status.m_StatusSetting->GetStartOffsetZ()) / status.m_StatusSetting->GetSpaceTime();

	//	pPlayer->SetPos(v.x, v.y, v.z);
	//}
}
void MonsterStatusMgr::ProcessStatusSect( SMonsterStatus& status )
{
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID(status.m_PlayerId);
	if (!pPlayer)
	{
		return;
	}
	if( !status.m_StatusSetting )
		return;

	status.m_dwCurrStatusSectBeginTime = HQ_TimeGetTime();

	const MonsterStatusConfig::StatusSect* pSect = &status.m_StatusSetting->GetArrStatusSect()[status.m_nStatusSect];
	std::string strTemp = theXmlString.GetString(pSect->m_StringId); 
	pPlayer->SetChatInfo(strTemp,pSect->m_nKeepTime);
	if (!pSect->m_strEffect.empty())
	{
		ReleaseLastAndPlayStatusEffect(status,pSect->m_strEffect.c_str());
	}

	if (pSect->m_strAction.size() > 0)
	{
		if (pPlayer->GetAnim())
		{
			pPlayer->GetAnim()->PlayLowerAnim(pSect->m_strAction.c_str(),
				MexAnimCtrl::eNormalPlay,
				0,
				1,
				MexAnimCtrl::eMaxTimeout,
				MexAnimCtrl::eDefaultBlendingTime,
				"idle",
				MexAnimCtrl::eNormalPlay 
				);
		}
	}

}

void MonsterStatusMgr::ReleaseLastAndPlayStatusEffect( SMonsterStatus &status, const char* pStatusSettingEffect )
{
	IEffect* pEffect = GetEffectMgr()->GetEffect(status.m_nStatusEffectId);
	if (pEffect)
	{
		pEffect->SetDead();
	}
	if (pStatusSettingEffect)
	{
		status.m_nStatusEffectId = PlayEffect(pStatusSettingEffect, theHeroGame.GetPlayerMgr()->FindByID(status.m_PlayerId), 0.5 );
	}
}

void MonsterStatusMgr::ReleasePlayer( GameObjectId nPlayerId )
{
	assert(-1 != nPlayerId);
	MonsterStatusIter iter = m_mapMonsterStatus.find(nPlayerId);
	if (iter != m_mapMonsterStatus.end())
	{
		SMonsterStatus& status = iter->second;
		ReleaseLastAndPlayStatusEffect(status,NULL);
		m_mapMonsterStatus.erase(iter);
	}
}

void MonsterStatusMgr::Update()
{
	DWORD time = HQ_TimeGetTime();
	for(MonsterStatusIter iter = m_mapMonsterStatus.begin(); iter != m_mapMonsterStatus.end();++iter)
	{
		SMonsterStatus& status = iter->second;
		ProcessStatus(status);
		if (status.m_StatusSetting && status.m_StatusSetting->GetArrStatusSect().size() > status.m_nStatusSect + 1)
		{
			const MonsterStatusConfig::StatusSect* pSect = &status.m_StatusSetting->GetArrStatusSect()[status.m_nStatusSect];
			if (time - status.m_dwCurrStatusSectBeginTime > pSect->m_nKeepTime)
			{
				++status.m_nStatusSect;
				ProcessStatusSect(status);
			}
		}
	}
}

