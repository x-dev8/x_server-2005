//战场的配置文件的基类
#pragma once
#include "BaseGameBattleManager.h"
class BaseGameBattleConfig
{
public:
	//BaseGameBattleConfig(){}
	//~BaseGameBattleConfig(){}
	virtual bool LoadGameBattleConfig(const char* FilePath) = 0;//加载函数
	BaseGameBattleManager* GetGameBattleManager(){return m_pManager;}
	void SetGameBattleManager(BaseGameBattleManager* GameBattleManager){m_pManager = GameBattleManager;}
protected:
	BaseGameBattleManager* m_pManager;//管理器
};