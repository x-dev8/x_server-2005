/********************************************************************
    Filename:    MonsterTrap.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERTRAP_H__
#define __GAMESERVER_MONSTERTRAP_H__

#pragma once

#include "MonsterBaseEx.h"

const uint32 gMonsterTrapPoolBatchSize = 10;

class MonsterPetTrap : public MonsterBaseEx,
                    INHERIT_POOL_PARAM( MonsterPetTrap, gMonsterTrapPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterPetTrap )

    MonsterPetTrap();
    virtual ~MonsterPetTrap();

    virtual void  OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig );
    virtual bool  OnThink();
    virtual bool  OnMove( uint32 lapseTime );
    
    virtual bool  MustOpenAI(){ return true; }
    virtual void  RefreshEnmity(){}
    
    uint8 IncreaseSkillUseCount() { _skillUseCount += 1; return _skillUseCount; } // 陷阱怪专用
protected:
    void  MoveAttackMoving( uint32 lapseTime ); // 有攻击目标的移动
    void  MovePosMoving   ( uint32 lapseTime ); // 一般的点目标的移动    

protected:
    uint8 _skillUseCount; // 技能释放的成功次数
};

#endif // __GAMESERVER_MONSTERTRAP_H__
