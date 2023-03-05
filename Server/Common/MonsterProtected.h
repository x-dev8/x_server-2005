/********************************************************************
    Filename:    MonsterProtected.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERPROTECTED_H__
#define __GAMESERVER_MONSTERPROTECTED_H__

#pragma once

#include "MonsterBase.h"

const uint32 gMonsterPretectedPoolBatchSize = 10;

// 被保护怪 对应 Object_MonsterProtected
class MonsterProtected : public MonsterBase, 
                         INHERIT_POOL_PARAM( MonsterProtected, gMonsterPretectedPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterProtected )

    MonsterProtected() {}
    virtual ~MonsterProtected() {}
    
    virtual void RefreshEnmity() {}

    virtual void OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig ); // 被人打了
    virtual bool OnThink();
    virtual bool OnMove( uint32 lapseTime );

protected:    
    void MovePosMoving( uint32 lapseTime ); // 一般的点目标的移动
};

#endif // __GAMESERVER_MONSTERPROTECTED_H__
