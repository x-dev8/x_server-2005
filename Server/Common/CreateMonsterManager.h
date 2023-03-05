#ifndef _CREATEMONSTERMANAGER_
#define _CREATEMONSTERMANAGER_

#include "MeRTLibs.h"
#include "GameTimer.h"
#include "CreateMonsterConfig.h"

class CreateMonsterManager
{
public:
	CreateMonsterManager();
	virtual ~CreateMonsterManager();

	// 自动更新
	void RunUpdate( unsigned int nCurrentTime );

	void UpdataData( CreateMonsterConfig::VecMonster& data );

	static CreateMonsterManager& Instance()
	{
		static CreateMonsterManager s_xCreateMonsteManager;
		return s_xCreateMonsteManager;
	}

private:
	// 更新定时器
	GameTimerEx m_xUpdateTimer;

	//下边储存当天要的
	CreateMonsterConfig::VecMonster m_vecMonster; 
};

#define theCreateMonsterManager CreateMonsterManager::Instance()

#endif //_CREATEMONSTERMANAGER_