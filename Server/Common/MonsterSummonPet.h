/********************************************************************
    Filename:    MonsterSummonPet.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERSUMMONPET_H__
#define __GAMESERVER_MONSTERSUMMONPET_H__

#pragma once

#include "MonsterPetEx.h"

const uint32 gMonsterPetPoolBatchSize = 10;

class MonsterSummonPet : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterSummonPet, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterSummonPet )

    MonsterSummonPet();
    virtual ~MonsterSummonPet(){};

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    virtual bool IsSummonPet() { return true; }

protected:

    // 处理怪物掉落
    virtual void ProcessDeathDromItem(){}

    // 阵营怪物死亡
    virtual void ProcessCampMonsterDeath(){}

    // 处理宠物死亡, 消失后清除主人的信息
    virtual void ProcessPetDeath( int deathType ) ;
};

#endif // __GAMESERVER_MONSTERSUMMONPET_H__
