//新的战场管理器  区别以前的战场
//控制权 负责 管理器的创建 销毁 Update 和 获取管理器 根据参数  不涉及到管理器的具体操作
//注意点
//1.一个类型的战场管理器 管理一个地图的多个战场 一个类型就一个管理器 不可以有多个管理器 
//2.如 以国家区分的3个战场 魏蜀吴 需要配置3个战场类型 分别代表魏蜀吴 每个管理器管理一块地图 地图ID可以相同
#pragma once
#include <vector>
#include "Singleton.h"
#include "BaseGameBattleManager.h"
#include "GameTimer.h"
class GameBattleControl:public ISingletion<GameBattleControl>
{
public:
	GameBattleControl();
	~GameBattleControl();
	void RunUpdate( unsigned int nCurrentTime );//Update函数 更新管理下所有的战场管理器
	//获取战场管理器 战场类型是可以知道的 地图是未知的  GamePlayer
	BaseGameBattleManager* GetGameBattleManager(unsigned int GameBattleType);
	bool DestroyGameBattleManagerByType(unsigned int GameBattleType);

	//各个类型的管理器的创建函数
	bool RegisterGuildGeneralBattleManger();//添加新的公会约战的战场管理器

	unsigned int GetMapIDByType(unsigned int Type);
	int GetMapMaxTimeByType(unsigned int Type);
	int GetMapDiffTimeByType(unsigned int Type);
private:
	void Init();//初始化函数
	void Destroy();
protected:
	GameTimerEx m_xUpdateTimer;//定时更新器
	std::vector<BaseGameBattleManager*> GameBattleVec;//全部的管理器的集合
	std::map<unsigned int,unsigned int> MapTypeList;
	std::map<unsigned int,int> MapTypeMaxTime;
	std::map<unsigned int,int> MapTypeDiffTime;
};
#define theGameBattleControl GameBattleControl::Instance()