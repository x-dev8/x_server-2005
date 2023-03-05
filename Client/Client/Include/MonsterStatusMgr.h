#pragma once
#include <Windows.h>
#include <deque>
#include "GlobalDef.h"
#include "Singleton.h"
#include "MonsterStatusConfig.h"
class MonsterStatusMgr: public Singleton<MonsterStatusMgr>
{
	struct SMonsterStatus
	{
		SMonsterStatus()
			:m_nStatusEffectId(-1),m_StatusData(NULL),m_nStatusSect(0),m_dwCurrStatusSectBeginTime(0),m_StatusSetting(NULL),m_PlayerId(-1)
		{
           m_vRealPosition = D3DXVECTOR3(0,0,0);
		}
		const MonsterStatusConfig::StatusData*		m_StatusData;
		const MonsterStatusConfig::StatusSetting*   m_StatusSetting;
		GameObjectId								m_PlayerId;
		int											m_nStatusEffectId;
		int											m_nStatusSect;
		DWORD										m_dwCurrStatusBeginTime;
		DWORD										m_dwCurrStatusSectBeginTime;
		D3DXVECTOR3									m_vRealPosition;
	};
public:
	MonsterStatusMgr(){;}
	void		Update();
	void		ProcessStatusSect(SMonsterStatus &status);
	void		ProcessStatus(SMonsterStatus &status);
	void		ChangeMonsterStatus( GameObjectId nPlayerId, int nMonsterId,uint8 nTypeStatus);

	void		ReleaseLastAndPlayStatusEffect( SMonsterStatus &status, const char* pStatusSettingEffect );
	void		ReleasePlayer( GameObjectId nPlayerId );
private:
	typedef std::map<int,SMonsterStatus>	MapMonsterStatus;
	typedef MapMonsterStatus::iterator		MonsterStatusIter;

	MapMonsterStatus			m_mapMonsterStatus;
};