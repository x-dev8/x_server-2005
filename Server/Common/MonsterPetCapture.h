#ifndef __MONSTERPETCAPTURE_H__
#define __MONSTERPETCAPTURE_H__

/********************************************************************
            捕捉怪, 可移动, 可攻击
            Filename:     MonsterPetCapture.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterPetEx.h"

class MonsterPetCapture : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterPetCapture, 50 )
{
public:
    DECLARE_POOL_FUNC( MonsterPetCapture )

    MonsterPetCapture();
    virtual ~MonsterPetCapture(){};

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    virtual bool IsSummonPet() { return true; }

protected:

    // 处理怪物掉落
    virtual void ProcessDeathDromItem(){}

    // 阵营怪物死亡
    virtual void ProcessCampMonsterDeath(){}

    // 处理宠物死亡, 消失后清除主人的信息
    virtual void ProcessPetDeath( int deathType );
};

#endif