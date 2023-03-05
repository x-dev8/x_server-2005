#ifndef __GAMESERVER_MONSTERPICKUP_H__
#define __GAMESERVER_MONSTERPICKUP_H__

/********************************************************************
            拾遗小妖, 可移动, 可攻击
            Filename:     MonsterPickup.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"
#include "DropCommonItem.h"

class MonsterPickup : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterPickup, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterPickup )

    MonsterPickup();
    virtual ~MonsterPickup(){};

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL  );

    // 应用BUFF
    virtual long ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue );

    // 处理锁定攻击目标
    virtual void ProcessLockTarget( int nTargetID );

protected:

    // 处理怪物死亡掉落
    virtual void ProcessDeathDromItem();

    // 处理怪物掉落
    virtual void ProcessDropItemPackage( int nDropPackIndex );

    // 不清除Ai变量
    virtual void ClearAiVariable() { return; }

protected:
    DropCommonItem  m_CommonDropItem;
};

#endif