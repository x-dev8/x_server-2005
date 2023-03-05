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

	// �Զ�����
	void RunUpdate( unsigned int nCurrentTime );

	void UpdataData( CreateMonsterConfig::VecMonster& data );

	static CreateMonsterManager& Instance()
	{
		static CreateMonsterManager s_xCreateMonsteManager;
		return s_xCreateMonsteManager;
	}

private:
	// ���¶�ʱ��
	GameTimerEx m_xUpdateTimer;

	//�±ߴ��浱��Ҫ��
	CreateMonsterConfig::VecMonster m_vecMonster; 
};

#define theCreateMonsterManager CreateMonsterManager::Instance()

#endif //_CREATEMONSTERMANAGER_