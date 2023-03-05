#ifndef __ECTYPTESTAGE_H__
#define __ECTYPTESTAGE_H__

#include "GameStage.h"
#include "LuaPlus/LuaPlus.h"

class EctypeStage : public GameStage
{
public:
    EctypeStage();
    virtual ~EctypeStage();

    virtual void Release() = 0;

	// 判断是否将要销毁 更新检测是否要设置销毁
    virtual void CheckStageValid();

	// 初始化场景
    virtual bool Initialize( MapConfig::MapData* pMapData, uint32 nStageID, uint32 nMapLevel );

	// 执行更新
    virtual void RunUpdate();

	// 设置让副本销毁 并不是立刻销毁默认是3分钟,在3分钟期间是可以重新恢复的
    virtual void SetStageWaitRelease( bool bRelease ,bool bNow = false);

	// 是否等待销毁
    virtual bool IsStageWaitingRelease();

	// 是否要销毁
    virtual bool IsStageRelease();

	// 检测要剔除的玩家
    virtual void CheckKickOutPlayer( BaseCharacter* pChar );

    // 场景的等级
    void SetStageLevel( int nValue ) { m_nStageLevel = nValue; }
    virtual int GetStageLevel() { return m_nStageLevel; }

    // 副本时间
    void SetStageKeepTime( uint32 nValue );

    // 场景剩余时间
    uint32 GetStageRemainTime();

	uint32 GetStageCreateTime();
    
    virtual void RecordPlayerDeath ( GamePlayer* pPlayer );
    virtual uint16 GetPlayerDeathCount( GamePlayer* pPlayer );

    // 副本专属ID
    void SetSpecialID( uint32 dwFirstID, uint32 dwSecondID );
    bool IsSpecialID( uint32 dwID );

    virtual bool CheckCanEnterStage( GamePlayer* pPlayer );

    // 设置分段下怪的下个阶段
    void SetNextRefreshStage( int nValue ) { m_nNextRefreshStage = nValue; }

    // 初始化脚本 LuaInit
    uint32 InitLuaScript(); 

    // 开始lua定时器
    void LuaStartTimer( uint8 id, uint32 interval );

    // 停止lua定时器
    void LuaStopTimer( uint8 id );

    // 更新lua定时器
    void UpdateLuaTimer();

    // 多人副本, 多队伍副本, 多帮派副本预约列表
    void AddReserve( uint32 nID );
    void RemoveReserve( uint32 nID );
    bool HaveReserve( uint32 nID );

protected:
    virtual bool 			ProcessEnterStage( GamePlayer* pPlayer );
    virtual void 			ProcessLeaveStage( GamePlayer* pPlayer );
    virtual eEctypeKickType WhyKickOutPlayer ( GamePlayer* pPlayer );

    // 是否有预约
    bool HaveReserve();

    // 分段刷怪物
    void RefreshMonsterByStage();

    // 清除玩家离开的时间
    void ClearPlayerLeaveTime();

    // 更新预约列表
    void UpdateReserve();

protected:

    typedef std::map< uint32, uint16 > DeathCountMap;
    typedef DeathCountMap::iterator DeathCountMapIter;

    typedef std::map< uint32, uint32 > PlayerLeaveTime;
    typedef PlayerLeaveTime::iterator PlayerLeaveTimeIter;

    typedef std::map< uint32, uint32 > ReserveMap;
    typedef ReserveMap::iterator ReserveMapIter;

    // 场景等级( 这个等级是队伍的平均等级 或者 多人副本的等级, 默认为0, 不限制等级 )
    int m_nStageLevel;

    // 副本创建时间
    uint32 m_nStageCreateTime;

    // 副本时间
    uint32 m_nStageKeepTime;

    // 预约列表
    ReserveMap m_mapReserve;

    // 副本销毁定时器
    GameTimerEx m_xReleaseTimer;

    // 记录玩家副本死亡次数
    DeathCountMap m_mapPlayerDeath; 

    // 副本按阶段刷怪的第几阶段
    int m_nNextRefreshStage; 

    // 下一次刷新还剩多少时间
    int m_dwNextRefreshTime; 

    // 上次刷新时间
    int m_dwLastRefreshTime;

    // 结婚场景等专用场景归属
    std::pair< uint32, uint32 > m_pairSpecialID; 

    // 玩家离开副本时间
    PlayerLeaveTime m_mapPlayerLeaveTime;

    // 场景lua解释器
    LuaStateOwner _luaScript; 

    // 是否有脚本
    bool _bHaveScript; 

    // 给定时器 不new动态给，怕策划瞎来
    GameTimerEx _timers[ StageDefine::ETimerType_Max ]; 
};

//////////////////////////////////////////////////////////////////////////////////////////
inline void EctypeStage::SetStageKeepTime(  uint32 nValue )
{
    m_nStageKeepTime = nValue;
}

inline uint32 EctypeStage::GetStageRemainTime()
{
    return m_nStageKeepTime - GameTime::GetPassTime( HQ_TimeGetTime(), m_nStageCreateTime );
}

inline uint32 EctypeStage::GetStageCreateTime()
{
	return m_nStageCreateTime;
}

inline bool EctypeStage::IsStageWaitingRelease()
{
    return m_xReleaseTimer.IsStart();
}

inline bool EctypeStage::IsStageRelease()
{
    return m_xReleaseTimer.DoneTimer();
}

inline void EctypeStage::SetSpecialID( uint32 dwFirstID, uint32 dwSecondID )
{
    m_pairSpecialID.first  = dwFirstID; 
    m_pairSpecialID.second = dwSecondID; 
}

inline bool EctypeStage::IsSpecialID( uint32 dwID )
{
    return m_pairSpecialID.first == dwID || m_pairSpecialID.second == dwID;
}

inline void EctypeStage::AddReserve( uint32 nID )
{
    m_mapReserve[ nID ] = HQ_TimeGetTime(); 
}

inline void EctypeStage::RemoveReserve( uint32 nID )
{
    m_mapReserve.erase( nID );
}

inline bool EctypeStage::HaveReserve()
{
    return !m_mapReserve.empty();
}

inline bool EctypeStage::HaveReserve( uint32 nID )
{
    ReserveMapIter iter = m_mapReserve.find( nID );

    return iter != m_mapReserve.end();
}

#endif
