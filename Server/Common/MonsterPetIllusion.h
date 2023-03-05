#ifndef __MONSTERPETILLUSION_H__
#define __MONSTERPETILLUSION_H__

/********************************************************************
            镜像怪, 可移动, 可攻击
            Filename:     MonsterPetIllusion.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterPetEx.h"

class MonsterPetIllusion : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterPetIllusion, 50 )
{
public:
    DECLARE_POOL_FUNC( MonsterPetIllusion )

    MonsterPetIllusion();
    virtual ~MonsterPetIllusion(){};

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // 镜像怪不可控制
    virtual bool IsSummonPet() { return false; }

protected:

    // 处理怪物掉落
    virtual void ProcessDeathDromItem(){}

    // 阵营怪物死亡
    virtual void ProcessCampMonsterDeath(){}


};

#endif