/************************************************************************/
/*      FileName:MonsterCountry.h                                       */
/*      Author:eliteYang                                                */
/*      Desc:国家怪                                              */
/************************************************************************/
#ifndef __MONSTERCOUNTRY_H__
#define __MONSTERCOUNTRY_H__

#pragma once

#include "MonsterNormal.h"

const uint32 gMonsterCountryPoolBatchSize = 10;

// 国家怪，类似于战斗NPC，只攻击别国人
class MonsterCountry : public MonsterNormal
{
public:
    DECLARE_POOL_FUNC( MonsterCountry )

    MonsterCountry(){ }
    ~MonsterCountry(){}
};

    //virtual void RefreshEnmity();

//    virtual void OnBeAttacked( BaseCharacter* pAttacker, const CItemDetail::SItemSkill* pSkillConfig ); // 被攻击
//    virtual bool OnThink();
//    virtual bool OnMove( uint32 lapseTime );
//    //virtual bool IsAICanAttack( BaseCharacter* pChar );
//    // TODO:剩下需要的函数
//protected:
//    //void UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster ); // 保持更新目标的仇恨值
//    void ThinkAttack(); // 可以产生攻击的行为
//    void ThinkIdle();   // 可以产生Idle的行为
//    void ThinkIdleMove();   // 空闲移动
//
//    void MoveAttackMoving( uint32 lapseTime );  // 有攻击目标的移动
//    void MovePosMoving( uint32 lapseTime );     // 一般点的移动


#endif  // __MonsterCountry_h__