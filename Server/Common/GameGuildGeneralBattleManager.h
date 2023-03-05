#pragma once
//同一类型的同一地图进行管理的战场管理器
#include "BaseGameBattleManager.h"
#include "GameBattleDefine.h"
#include "GameGuildGeneralBattleConfig.h"
#include "GameGuildGeneralBattle.h"
class GameGuildGeneralBattle;
struct GameGuildGeneralBattleOnceInfo
{
	GameGuildGeneralBattleOnceInfo()
	{
		m_nConfigMapID = 0xffffffff;
		m_nLeftTime = 0;
		m_uchBattleStatus = GameBattleDefine::StatusInit;
	}
	void SetData(unsigned int IndexID,unsigned int SrcGuildID,unsigned int DestGuildID,__int64 LogBeginTime,unsigned int MapID,unsigned int nMonrySum,unsigned int nGuildMoneySum,unsigned int nGuildMessionSum)
	{
		ID =IndexID;
		RedGuildID = SrcGuildID;
		BlueGuildID = DestGuildID;
		BeginTime = LogBeginTime;
		m_nConfigMapID=MapID;
		MoneySum = nMonrySum;
		GuildMoneySum=nGuildMoneySum;
		GuildMissionSum=nGuildMessionSum;
		m_nConfigMapID = MapID;
		m_uchBattleStatus = GameBattleDefine::StatusInit;
	}
	unsigned int ID;//唯一编号
	unsigned int RedGuildID;
	unsigned int BlueGuildID;

	__int64 BeginTime;
	//奖励
	unsigned int MoneySum;
	unsigned int GuildMoneySum;
	unsigned int GuildMissionSum;
	//战场
	// 战场的MapConfig ID
    unsigned int m_nConfigMapID;
    // 战场剩余时间( 单位: 毫秒 )
    unsigned int m_nLeftTime;
    unsigned int m_nLastUpdateTime;
	// 战场的状态
    unsigned char m_uchBattleStatus;
	// 战场状态剩余时间
    unsigned int GetLeftTime() const { return m_nLeftTime; }
    void SetLeftTime( unsigned int nValue ) { m_nLeftTime = nValue; }
    void SubLeftTime( unsigned int nValue );
	// 战场MapID
    unsigned int GetMapID() const { return m_nConfigMapID; }
    void SetMapID( unsigned int nValue ) { m_nConfigMapID = nValue; }
	// 状态
    unsigned char GetBattleStatus() const { return m_uchBattleStatus; }
    void SetBattleStatus( unsigned char uchValue ){ m_uchBattleStatus = uchValue; }

	void SetBeginTime(__int64 TimeLog){BeginTime = TimeLog;}
	void SetRedGuildID(unsigned int ID){RedGuildID =ID;}
	void SetBlueGuildID(unsigned int ID){BlueGuildID =ID;}

};
inline void GameGuildGeneralBattleOnceInfo::SubLeftTime( unsigned int nValue )
{
    if ( nValue >= m_nLeftTime )
    { m_nLeftTime = 0; }
    else
    { m_nLeftTime -= nValue; }
}
class GameGuildGeneralBattleManager : public BaseGameBattleManager
{
public:
    GameGuildGeneralBattleManager();
    virtual ~GameGuildGeneralBattleManager();

	void SetConfig(GameGuildGeneralBattleConfig& pConfig){m_pConfig = pConfig;}
	virtual void RunUpdate( unsigned int nCurrentTime );
	//设置国家主城
	void SetkingdomMapInfo(const int map_id,const float map_x,const float map_y);
	inline int  GetKingdomMapID(){return m_KingdomMapID;}
	inline float  GetKingdomMapX(){return m_X;}
	inline float  GetKingdomMapY(){return m_Y;}

    // 添加战场
    void AddGameBattle( GameGuildGeneralBattle* pGameBattle );

    // 查找战场
    GameGuildGeneralBattle* GetGameBattleByPlayerID( unsigned int nPlayerID );
    GameGuildGeneralBattle* GetGameBattleByUnitID( unsigned int nUnitID );
	GameGuildGeneralBattle* GetGameBattleByID(unsigned int ID);
	GameGuildGeneralBattle* GetGameBattleByOnlyMapID(unsigned int MapID);

    // 战场设定
    GameGuildGeneralBattleConfig* GetBattleConfig() { return &m_pConfig; }

    // 显示进入界面
    virtual bool ShowGameBattleEnter(GamePlayer* pPlayer );

    // 进入战场
    virtual bool EnterGameBattle( GamePlayer* pPlayer );

    // 处理战场状态改变
    virtual void ProcessChangeStatus(unsigned int ID, unsigned char uchStatus );

	GameGuildGeneralBattleOnceInfo* GetGameBattleOnceInfo(unsigned int ID);
	void AddGameGuildGeneralBattleOnceInfo(unsigned int ID,unsigned int MapID,unsigned int SrcGuildID,unsigned int DestGuildID,__int64 BeginTime,unsigned int MoneySum,unsigned int GuildMoney,unsigned int GuildMission);

	virtual void Init();
	virtual void Destroy();

	void HandleGameGuildGeneralBattleStates(unsigned int ID);

	void KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID ,unsigned int MapID);
protected:	
	// 处理战场初始化状态
    virtual void ProcessBattleInitStatus(unsigned int ID,__int64 NowTime);

    // 处理战场进入状态
    virtual void ProcessBattleEnterStatus(unsigned int ID,__int64 NowTime);

    // 处理战场战斗状态
    virtual void ProcessBattleFightStatus(unsigned int ID,__int64 NowTime);

    // 处理战场结束状态
    virtual void ProcessBattleEndStatus(unsigned int ID,__int64 NowTime);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // 处理转换到报名状态逻辑
    virtual void ProcessChangeToSignUpStatus(unsigned int ID);

    // 处理转换到准备状态逻辑
    virtual void ProcessChangeToPrepareStatus(unsigned int ID);

    // 处理转换到进入状态逻辑
    virtual void ProcessChangeToEnterStatus(unsigned int ID);

    // 处理转换到战斗状态逻辑
	virtual void ProcessChangeToFightStatus(unsigned int ID);

	// 处理转换到结束的状态逻辑
	virtual void ProcessChangeToEndStatus(unsigned int ID){};
    //////////////////////////////////////////////////////////////////////////////////////////////
    // 发送战场状态改变消息
    virtual void SendBattleStatusMessage(unsigned int ID, unsigned char uchStatus );

    // 处理战场剩余时间
    void ProcessBattleLeftTime( unsigned int ID,unsigned int nCurrentTime );
protected:
	typedef std::map< unsigned int, GameGuildGeneralBattle* > GameBattleMap;
    typedef GameBattleMap::iterator GameBattleMapIter;

    // 保存战场的map
    GameBattleMap m_mapGameBattle;

	// 对应国家的主城位置(主要用来飞地图,保证跨GAME SERVER飞入战场可以正确执行)
	int m_KingdomMapID;
	float m_X;
	float m_Y;

	int	m_BattleValue;//战场的进入值
	bool m_BattleValueIsOpen;

	std::map<unsigned int,GameGuildGeneralBattleOnceInfo> m_pInfoList;//数据的集合
	GameGuildGeneralBattleConfig m_pConfig;//配置文件的对象
};
inline GameGuildGeneralBattleOnceInfo* GameGuildGeneralBattleManager::GetGameBattleOnceInfo(unsigned int ID)
{
	if(m_pInfoList.count(ID) == 1)
		return &m_pInfoList[ID];
	else
		return NULL;
}