//战场管理器的基类 应该劲量少的行为
//一个战场管理器管理基于同一块地图的同一类型的多个战场对象
//无论战场是否存在 管理器是一定存在的 除非当前GameServer 上指定地图 不是活动状态
#pragma once
class BaseGameBattleManager
{
public:
	//BaseGameBattleManager();
	//~BaseGameBattleManager();
	virtual void RunUpdate( unsigned int nCurrentTime ) = 0;

	void SetGameBattleType(unsigned int Type){GameBattleType = Type;}
	void SetGameBattleMapID(unsigned int MapID){BattleMapID = MapID;}

	unsigned int GetGameBattleMapID(){return BattleMapID;}
	unsigned int GetGameBattleType(){return GameBattleType;}

	virtual void Init() =0;
	virtual void Destroy()=0;
protected:
	unsigned int GameBattleType;//战场类型 创建的时候设置的
	unsigned int BattleMapID;//战场的地图ID 配置文件里读取出来的
};
//inline BaseGameBattleManager::BaseGameBattleManager()
//{
//	Init();
//}
//inline BaseGameBattleManager::~BaseGameBattleManager()
//{
//	Destroy();
//}