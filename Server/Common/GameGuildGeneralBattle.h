#pragma once
//公会约战战场
#include "BaseGameBattle.h"
#include "Memory_Pool.h"
#include "MonsterBaseEx.h"
#include "GameGuildGeneralBattleManager.h"
#include "GamePlayer.h"
class GameGuildGeneralBattleManager;
class GameGuildGeneralBattle : public BaseGameBattle, INHERIT_POOL_PARAM( GameGuildGeneralBattle, 25 )
{
public:
    GameGuildGeneralBattle();
	~GameGuildGeneralBattle(){}

	virtual unsigned char  RunUpdate( unsigned int nCurrentTime );

	unsigned int GetBattleIndexID(){return m_ID;}
	void SetData(unsigned int ID,unsigned int nMoneySum,unsigned int nGuildMoneySum,unsigned int nGuildMission);

	// 创建阵营战场
    template< class T > 
    static GameGuildGeneralBattle* CreateGameGuildGeneralBattle() { return CNewWithDebug< T >::Alloc( 1, "创建CreateBattle实例" ); }

    // 释放阵营战场
    template< class T > 
    void ReleaseGameGuildGeneralBattle( T* pGameBattle ) { CNewWithDebug< T >::Free( pGameBattle ); }

    // 副本地图ID
    unsigned int GetBattleMapID() const;
    void SetBattleMapID( unsigned int nValue );

    // 状态
    unsigned char GetStatus() const;
    void SetStatus( unsigned char uchValue );

    // 一血
    bool GetFirstKill() const;
    void SetFirstKill( bool bValue );

    // 红方ID
    unsigned int GetRedID() const;
    void SetRedID( unsigned int nValue );

    // 蓝方ID
    unsigned int GetBlueID() const;
    void SetBlueID( unsigned int nValue );

    // 红方资源分
    unsigned int GetRedResource() ;
    void SetRedResource( unsigned int nValue );
    void AddRedResource( unsigned int nValue );

    // 蓝方资源分
    unsigned int GetBlueResource() ;
    void SetBlueResource( unsigned int nValue );
    void AddBlueResource( unsigned int nValue );

    unsigned int GetGameBattleResource( unsigned char uchFight );

    // 胜利资源分
    unsigned int GetWinResource() const;
    void SetWinResource( unsigned int nValue );

    // 战场玩家
    void AddBattlePlayer( unsigned int nPlayerID, GameBattleDefine::BattlePlayer& xPlayer );
    GameBattleDefine::BattlePlayer* GetBattlePlayer( unsigned int nPlayerID );
    int GetBattlePlayerCount( unsigned char uchFight );

    // 获得复活点索引
    virtual unsigned int GetReliveIndex( GamePlayer* pPlayer );

    // 发送阵营信息
    void SendGameBattleMessage( Msg* pMessage, unsigned char uchFight );

    // 处理战场杀人
    virtual void ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill );

    // 处理战场积分
    void ProcessAddGameBattleResource( unsigned char uchFight, unsigned int nAddResource );

    // 处理战场状态改变
    void ProcessStatusChange( unsigned char uchStatus );

    // 发送战场玩家信息
    void SendBattlePlayerMessage( GamePlayer* pPlayer, unsigned char uchFight );

    // 发送战场状态消息
    void SendBattleStatusMessage( GamePlayer* pPlayer = NULL );

    // 发送对阵双方消息
    void SendGameBattleMatchMessage( GamePlayer* pPlayer );

    // 获得阵营信息
    unsigned char GetGameBattleFight( unsigned int nUnitID );

    // 处理玩家掉线, 退出游戏逻辑
    virtual void ProcessBattlePlayerOutLine( GamePlayer* pPlayer ){};

	virtual void Release();
    virtual void SendEnterGameBattleMessage();

    virtual void KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID );
	
	void SetGuildGameBattleTimeMap();

	virtual void Init();
	virtual void Destroy();

	GameGuildGeneralBattleManager* GetGameBattleManager() {return m_pManager;}
	void SetGameBattleManager(GameGuildGeneralBattleManager* nGameBattleManager){m_pManager = nGameBattleManager;}
protected:
	class RefreshIndex
    {
    public:
        RefreshIndex() : nRedIndex( 0 ), nBlueIndex( 0 ), nMaxRedIndex( 0 ), nMaxBlueIndex( 0 ){}

        int GetRedIndex() { return nRedIndex; }
        int GetBlueIndex() { return nBlueIndex; }
        int GetMaxRedIndex() { return nMaxRedIndex; }
        int GetMaxBlueIndex() { return nMaxBlueIndex; }

        void SetRedIndex( int nValue ) { nRedIndex = nValue; }
        void SetBlueIndex( int nValue ) { nBlueIndex = nValue; }
        void SetMaxRedIndex( int nValue ) { nMaxRedIndex = nValue; }
        void SetMaxBlueIndex( int nValue ) { nMaxBlueIndex = nValue; }
    private:
        int nRedIndex;
        int nMaxRedIndex;
        int nBlueIndex;
        int nMaxBlueIndex;
    };
    virtual void ProcessGameBattleEnterStatus();
    void ProcessRefreshNormalMonster();
	void ProcessBoss();
    void SendGameBattleResourceMessage();


    void ProcessRefreshGameBattleMonster();
    // 处理战场战斗状态
    virtual void ProcessGameBattleFightStatus();

    // 处理战场结束状态
    virtual void ProcessGameBattleEndStatus();

    // 处理改变到战场战斗状态
    virtual void ProcessChangeToFightStatus();

    // 处理改变到战场结束状态
    virtual void ProcessChangeToEndStatus();

    // 计算战场结果
    void ProcessCalcGameBattleWinner();

    // 处理战场结果
    virtual void ProcessGameBattleResult( unsigned char uchFight );

    // 处理第一次杀人
    void PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName );

    // 处理连续杀人
    void ProcessKeepKillPlayer( const char* szKillerName, int nKillCount, const char* szBeKillName );

    // 处理被杀
    void ProcessBeKillByPlayer( const char* szKillerName, GameBattleDefine::BattlePlayer* pBeKillBattlePlayer );

    // 处理全世界杀人
    void ProcessTotalKillPlayer( GameBattleDefine::BattlePlayer* pKillerBattlePlayer, GameBattleDefine::BattlePlayer* pBeKillBattlePlayer );
private:
	// 战场对阵双方ID
	unsigned int m_ID;
    unsigned int m_nRedID;
    unsigned int m_nBlueID;
	unsigned int MoneySum;
	unsigned int GuildMoneySum;
	unsigned int GuildMession;

	typedef std::map< unsigned int, GameBattleDefine::BattlePlayer > BattlePlayerMap;
    typedef BattlePlayerMap::iterator BattlePlayerMapIter;

    // 设定胜利的积分
    unsigned int m_nWinResource;

    // 开启的副本地图ID
    unsigned int m_nEctypeMapID;

    // 战场状态
    unsigned char m_uchStatus;

    // 是否第一次杀人( 传说中的一血 )
    bool m_bFirstKill;      

    

    // 保存的战场玩家列表
    BattlePlayerMap m_mapBattlePlayer;
    
    // 积分
    unsigned int m_nRedResource;
    unsigned int m_nBlueResource;

	unsigned int m_RedTotleKillSum;
	unsigned int m_BlueTotleKillSum;

    // 战场销毁定时器
    GameTimerEx m_xReleaseTimer;

	GameTimerEx m_xRefreshTimer; // 刷怪定时器
	std::map<int,GameTimerEx> m_xNormalTimer ; // Normal怪刷新

    typedef std::map< int, RefreshIndex > RefreshIndexMap;
    typedef RefreshIndexMap::iterator RefreshIndexMapIter;
   
    RefreshIndexMap m_mapRefreshIndex; // 刷怪设定

	vector<GameObjectId> m_RedBarracks;
	MonsterBaseEx* m_RedBoss;
	vector<GameObjectId> m_BlueBarracks;
	MonsterBaseEx* m_BlueBoss;
	int m_RedBarracksDeadSum;
	int m_BlueBarracksDeadSum;

	GameGuildGeneralBattleManager* m_pManager;//管理器
};
inline void GameGuildGeneralBattle::SetData(unsigned int ID,unsigned int nMoneySum,unsigned int nGuildMoneySum,unsigned int nGuildMission)
{
	m_ID = ID;
	MoneySum = nMoneySum;
	GuildMoneySum = nGuildMoneySum;
	GuildMession= nGuildMission;
}
inline unsigned int GameGuildGeneralBattle::GetBattleMapID() const
{
    return m_nEctypeMapID;
}

inline void GameGuildGeneralBattle::SetBattleMapID( unsigned int nValue )
{
    m_nEctypeMapID = nValue;
}

inline unsigned char GameGuildGeneralBattle::GetStatus() const
{
    return m_uchStatus;
}

inline bool GameGuildGeneralBattle::GetFirstKill() const
{
    return m_bFirstKill;
}

inline void GameGuildGeneralBattle::SetFirstKill( bool bValue )
{
    m_bFirstKill = bValue;
}

inline unsigned int GameGuildGeneralBattle::GetRedID() const
{
    return m_nRedID;
}

inline void GameGuildGeneralBattle::SetRedID( unsigned int nValue )
{
    m_nRedID = nValue;
}

inline unsigned int GameGuildGeneralBattle::GetBlueID() const
{
    return m_nBlueID;
}

inline void GameGuildGeneralBattle::SetBlueID( unsigned int nValue )
{
    m_nBlueID = nValue;
}

inline unsigned int GameGuildGeneralBattle::GetRedResource() 
{
    return m_nRedResource;
}

inline void GameGuildGeneralBattle::SetRedResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue<0)
		ChangeValue = 0;
    m_nRedResource = ChangeValue;
}


inline void GameGuildGeneralBattle::AddRedResource( unsigned int nValue )
{
    m_nRedResource += nValue;
}

inline unsigned int GameGuildGeneralBattle::GetBlueResource() 
{
    return m_nBlueResource;
}

inline void GameGuildGeneralBattle::SetBlueResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue<0)
		ChangeValue = 0;
    m_nBlueResource = ChangeValue;
}

inline void GameGuildGeneralBattle::AddBlueResource( unsigned int nValue )
{
    m_nBlueResource += nValue;
}


inline unsigned int GameGuildGeneralBattle::GetWinResource() const
{
    return m_nWinResource;
}

inline void GameGuildGeneralBattle::SetWinResource( unsigned int nValue )
{
    m_nWinResource = nValue;
}