//ս���������ļ��Ļ���
#pragma once
#include "BaseGameBattleManager.h"
class BaseGameBattleConfig
{
public:
	//BaseGameBattleConfig(){}
	//~BaseGameBattleConfig(){}
	virtual bool LoadGameBattleConfig(const char* FilePath) = 0;//���غ���
	BaseGameBattleManager* GetGameBattleManager(){return m_pManager;}
	void SetGameBattleManager(BaseGameBattleManager* GameBattleManager){m_pManager = GameBattleManager;}
protected:
	BaseGameBattleManager* m_pManager;//������
};