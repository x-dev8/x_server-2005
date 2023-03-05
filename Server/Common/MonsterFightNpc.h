#ifndef __MONSTERFIGHTNPC_H__
#define __MONSTERFIGHTNPC_H__

/************************************************************************
        战斗npc类, 也是一类怪物
        Filename:     MonsterFightNpc.h
        MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MonsterActive.h"

class MonsterFightNpc : public MonsterActive, INHERIT_POOL_PARAM( MonsterFightNpc, 50 )
{
public:

    DECLARE_POOL_FUNC( MonsterFightNpc )

    MonsterFightNpc();
    virtual ~MonsterFightNpc(){};

    virtual void Initialize( CItemDetail::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // 可以执行脚本
    virtual bool CanQueryScriptTypeStatus() { return true; }

protected:

    // 处理怪物死亡后, 退出游戏世界
    virtual void ProcessMonsterDeathExitWorld();

    // 处理怪物复活
    virtual void ProcessMosnterRelive();

protected:
    GameTimerEx m_xReliveTime;  // 被杀死之后多久复活
};


#endif