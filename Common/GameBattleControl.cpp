#include "GameBattleControl.h"
#include "GameBattleDefine.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattleConfig.h"
GameBattleControl::GameBattleControl()
{
	Init();
}
GameBattleControl::~GameBattleControl()
{
	Destroy();
}
void GameBattleControl::RunUpdate(unsigned int nCurrentTime)
{
	if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) || GameBattleVec.empty())
		return;
	std::vector<BaseGameBattleManager*>::iterator Iter = GameBattleVec.begin();
	for(;Iter != GameBattleVec.end();++Iter)
	{
		BaseGameBattleManager* pManager = *Iter;
		pManager->RunUpdate(nCurrentTime);//管理器的更新操作
	}
}
void GameBattleControl::Init()//初始化
{
	//初始化函数 在控制权创建的时候 我们需要做的一些事情
	GameBattleVec.clear();
    m_xUpdateTimer.StartTimer( 1, GameBattleDefine::GameBattle_Control_UpdateSpace );
}
void GameBattleControl::Destroy()//销毁函数
{
	//回收内存
	if(GameBattleVec.empty())
		return;
	std::vector<BaseGameBattleManager*>::iterator Iter = GameBattleVec.begin();
	for(;Iter != GameBattleVec.end();++Iter)
	{
		BaseGameBattleManager* pManager = *Iter;
		pManager->Destroy();
		delete pManager;
	}
	GameBattleVec.clear();
}
BaseGameBattleManager* GameBattleControl::GetGameBattleManager(unsigned int GameBattleType)
{
	std::vector<BaseGameBattleManager*>::iterator Iter = GameBattleVec.begin();
	for(;Iter != GameBattleVec.end();++Iter)
	{
		BaseGameBattleManager* pManager = *Iter;
		if(pManager->GetGameBattleType() == GameBattleType)
		{
			return pManager;
		}
	}
	return NULL;
}
bool GameBattleControl::DestroyGameBattleManagerByType(unsigned int GameBattleType)
{
	std::vector<BaseGameBattleManager*>::iterator Iter = GameBattleVec.begin();
	for(;Iter != GameBattleVec.end();)
	{
		BaseGameBattleManager* pManager = *Iter;
		if(pManager->GetGameBattleType() == GameBattleType)
		{
			pManager->Destroy();
			Iter=GameBattleVec.erase(Iter);
			return true;
		}
		else
			++Iter;
	}
	return false;
}
bool GameBattleControl::RegisterGuildGeneralBattleManger()//直接创建的战场
{
	//创建新的管理器 基于战场的管理器
	//2.创建管理器的身体对象
	GameGuildGeneralBattleManager* pManager = new GameGuildGeneralBattleManager();
	pManager->GetBattleConfig()->LoadGameBattleConfig(GAMEGUILDGENERALBATTLE_FILEPATH);//加载配置文件
	int MapID = pManager->GetBattleConfig()->GetMapSetting()->GetMapID();
	MapTypeList.insert(std::map<unsigned int,unsigned int>::value_type(GameBattleDefine::GameBattle_Type_GuildGeneral,MapID));
	MapTypeMaxTime.insert(std::map<unsigned int,int>::value_type(GameBattleDefine::GameBattle_Type_GuildGeneral,pManager->GetBattleConfig()->GetMaxGameGuildGeneralBattleMaxTime()));
	MapTypeDiffTime.insert(std::map<unsigned int,int>::value_type(GameBattleDefine::GameBattle_Type_GuildGeneral,pManager->GetBattleConfig()->GetGameGuildGeneralBattleDiffTime()));
	if ( !g_Cfg.IsMapRun( MapID) )
	{
		delete pManager;
		return false;
	}
	//3.设置管理器对象 的 地图ID 和 战场类型 和 战场参战值 设置地图ID
	unsigned int BattleType = GameBattleDefine::GameBattle_Type_GuildGeneral;
	pManager->SetGameBattleType(BattleType);
	pManager->SetGameBattleMapID(MapID);
	//5.加入到集合里面去
	GameBattleVec.push_back(static_cast<BaseGameBattleManager*>(pManager));
	return true;
}
unsigned int GameBattleControl::GetMapIDByType(unsigned int Type)
{
	if(MapTypeList.count(Type) != 1)
		return 0;
	else
		return MapTypeList[Type];
}
int GameBattleControl::GetMapMaxTimeByType(unsigned int Type)
{
	if(MapTypeMaxTime.count(Type) != 1)
		return 0;
	else
		return MapTypeMaxTime[Type];
}
int GameBattleControl::GetMapDiffTimeByType(unsigned int Type)
{
	if(MapTypeDiffTime.count(Type) != 1)
		return 0;
	else
		return MapTypeDiffTime[Type];
}