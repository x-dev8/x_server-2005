#ifndef __CAMPBATTLE_H__
#define __CAMPBATTLE_H__

/************************************************************************
                阵营战场的基类, 各类阵营战场都可继承此类
                Filename:     CampBattle.h 
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <map>
#include "CampBattleDefine.h"
#include "GameTimer.h"
#include "Memory_Pool.h"

struct Msg;
class GamePlayer;
class BaseCharacter;
class CampBattleManager;

class CampBattle
{
public:
    CampBattle();
    virtual ~CampBattle(){};

    // 创建阵营战场
    template< class T > 
    static CampBattle* CreateBattle() { return CNewWithDebug< T >::Alloc( 1, "创建CreateBattle实例" ); }

    // 释放阵营战场
    template< class T > 
    void ReleaseBattle( T* pCampBattle ) { CNewWithDebug< T >::Free( pCampBattle ); }
    virtual void Release() = 0;

    // 副本地图ID
    unsigned int GetBattleMapID() const;
    void SetBattleMapID( unsigned int nValue );

    // 战场设定
    const CampBattleManager* GetBattleManager() const;
    void SetBattleManager( CampBattleManager* pManager );

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

    unsigned int GetCampBattleResource( unsigned char uchFightCamp );

    // 胜利资源分
    unsigned int GetWinResource() const;
    void SetWinResource( unsigned int nValue );

    // 战场玩家
    void AddBattlePlayer( unsigned int nPlayerID, BattlePlayer& xPlayer );
    BattlePlayer* GetBattlePlayer( unsigned int nPlayerID );
    int GetBattlePlayerCount( unsigned char uchFightCamp );

    // 获得复活点索引
    virtual unsigned int GetReliveIndex( GamePlayer* pPlayer );
    
     // 执行更新
    unsigned char RunUpdate( unsigned int nCurrentTime );

    // 发送阵营信息
    void SendCampMessage( Msg* pMessage, unsigned char uchFightCamp );

    // 处理战场杀人
    virtual void ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill );

    // 处理战场积分
    void ProcessAddCampResource( unsigned char uchFightCamp, unsigned int nAddResource );

    // 处理战场状态改变
    void ProcessStatusChange( unsigned char uchStatus );

    // 发送战场玩家信息
    void SendBattlePlayerMessage( GamePlayer* pPlayer, unsigned char uchFightCamp );

    // 发送是否参加阵营战场消息
    virtual void SendEnterCampBattleMessage() = 0;

    // 处理杀死怪物
    virtual void KillCampBattleMonster( unsigned char uchFightCamp, unsigned int nPlayerID, int nMonsterID );

    // 发送战场状态消息
    void SendBattleStatusMessage( GamePlayer* pPlayer = NULL );

    // 发送对阵双方消息
    void SendCampBattleMatchMessage( GamePlayer* pPlayer );

    // 获得阵营信息
    unsigned char GetBattleFightCamp( unsigned int nUnitID );

    // 处理玩家掉线, 退出游戏逻辑
    virtual void ProcessBattlePlayerOutLine( GamePlayer* pPlayer ){};
protected:

    // 处理战场进入状态
    virtual void ProcessCampBattleEnterStatus(){};

    // 处理战场战斗状态
    virtual void ProcessCampBattleFightStatus();

    // 处理战场结束状态
    virtual void ProcessCampBattleEndStatus();

    // 处理改变到战场战斗状态
    virtual void ProcessChangeToFightStatus();

    // 处理改变到战场结束状态
    virtual void ProcessChangeToEndStatus();

    // 计算战场结果
    void ProcessCalcCampBattleWinner();

    // 处理战场结果
    virtual void ProcessCampBattleResult( unsigned char uchFightCamp ) = 0;

    // 处理第一次杀人
    void PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName );

    // 处理连续杀人
    void ProcessKeepKillPlayer( const char* szKillerName, int nKillCount, const char* szBeKillName );

    // 处理被杀
    void ProcessBeKillByPlayer( const char* szKillerName, BattlePlayer* pBeKillBattlePlayer );

    // 处理全世界杀人
    void ProcessTotalKillPlayer( BattlePlayer* pKillerBattlePlayer, BattlePlayer* pBeKillBattlePlayer );

protected:
    typedef std::map< unsigned int, BattlePlayer > BattlePlayerMap;
    typedef BattlePlayerMap::iterator BattlePlayerMapIter;

    // 配置设定
    CampBattleManager* m_pBattleManager;

    // 设定胜利的积分
    unsigned int m_nWinResource;

    // 开启的副本地图ID
    unsigned int m_nEctypeMapID;

    // 战场状态
    unsigned char m_uchStatus;

    // 是否第一次杀人( 传说中的一血 )
    bool m_bFirstKill;      

    // 战场对阵双方ID
    unsigned int m_nRedID;
    unsigned int m_nBlueID;

    // 保存的战场玩家列表
    BattlePlayerMap m_mapBattlePlayer;
    
    // 积分
    unsigned int m_nRedResource;
    unsigned int m_nBlueResource;

	unsigned int m_RedTotleKillSum;
	unsigned int m_BlueTotleKillSum;


    // 战场销毁定时器
    GameTimerEx m_xReleaseTimer;
};

inline unsigned int CampBattle::GetBattleMapID() const
{
    return m_nEctypeMapID;
}

inline void CampBattle::SetBattleMapID( unsigned int nValue )
{
    m_nEctypeMapID = nValue;
}

inline const CampBattleManager* CampBattle::GetBattleManager() const
{
    return m_pBattleManager;
}

inline void CampBattle::SetBattleManager( CampBattleManager* pManager )
{
    m_pBattleManager = pManager;
}

inline unsigned char CampBattle::GetStatus() const
{
    return m_uchStatus;
}

inline void CampBattle::SetStatus( unsigned char uchValue )
{
    m_uchStatus = uchValue;
}

inline bool CampBattle::GetFirstKill() const
{
    return m_bFirstKill;
}

inline void CampBattle::SetFirstKill( bool bValue )
{
    m_bFirstKill = bValue;
}

inline unsigned int CampBattle::GetRedID() const
{
    return m_nRedID;
}

inline void CampBattle::SetRedID( unsigned int nValue )
{
    m_nRedID = nValue;
}

inline unsigned int CampBattle::GetBlueID() const
{
    return m_nBlueID;
}

inline void CampBattle::SetBlueID( unsigned int nValue )
{
    m_nBlueID = nValue;
}

inline unsigned int CampBattle::GetRedResource() 
{
    return m_nRedResource;
}

inline void CampBattle::SetRedResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue <0)
		ChangeValue = 0;
    m_nRedResource = ChangeValue;
}


inline void CampBattle::AddRedResource( unsigned int nValue )
{
    m_nRedResource += nValue;
}

inline unsigned int CampBattle::GetBlueResource() 
{
    return m_nBlueResource;
}

inline void CampBattle::SetBlueResource( unsigned int nValue )
{
	int ChangeValue = static_cast<int>(nValue);
	if(ChangeValue <0)
		ChangeValue = 0;
    m_nBlueResource = ChangeValue;
}

inline void CampBattle::AddBlueResource( unsigned int nValue )
{
    m_nBlueResource += nValue;
}


inline unsigned int CampBattle::GetWinResource() const
{
    return m_nWinResource;
}

inline void CampBattle::SetWinResource( unsigned int nValue )
{
    m_nWinResource = nValue;
}

#endif