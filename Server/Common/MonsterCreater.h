#ifndef __MONSTERCREATER_H__
#define __MONSTERCREATER_H__

/********************************************************************
            怪物创建类
            Filename:     MonsterCreater.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterProducer.h"
#include "ItemDetail.h"
#include "MonsterBaseEx.h"

class GamePlayer;
class MonsterCreater
{
public:

    /////////////////////////////////////////////////////////////////////////
    static void FillMonsterCreateData( MonsterCreateData& xCreateDta, CMonsterProducer::TagMonsterData* pMonsterData );

    // 创建普通怪物
    static MonsterBaseEx* CreateNormalMonster( MonsterCreateData& xCreateData );

    // 创建建筑怪
    static MonsterBaseEx* CreateBuildMonster( MonsterCreateData& xCreateData );

    // 创建跟随保护怪
    static MonsterBaseEx* CreateProtectedMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // 创建专属怪
    static MonsterBaseEx* CreateSpecialMonster( MonsterCreateData& xCreateData );

    // 创建捕捉宠物怪
    static MonsterBaseEx* CreatePetCaptureMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // 创建技能陷阱怪
    static MonsterBaseEx* CreatePetTrapMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // 创建召唤宠物
    static MonsterBaseEx* CreatePetSummonMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // 创建培育宠物
    static MonsterBaseEx* CreatePetNurtureMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // 创建技能镜像怪
    static MonsterBaseEx* CreatePetIllusionMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // 创建战斗npc怪
    static MonsterBaseEx* CreateFightNpcMosnter( MonsterCreateData& xCreateData );

    // 处理创建多个普通怪物
    static void ProcessCreateNormalMonster( MonsterCreateData& xCreateData );
    
    // 处理创建多个专属怪
    static void ProcessCreateSpecialMonster( MonsterCreateData& xCreateData );

protected:
     // 检测创建怪物的有效性
     static ItemDefine::SMonster* CheckCreateMonster( MonsterCreateData& xCreateData );

     static void SetDirectiron( MonsterCreateData& xCreateData );

     // 创建怪物
     static MonsterBaseEx* CreateMonster( MonsterCreateData& xCreateData, int nMonsterType, GamePlayer* pPlayer = NULL );

     // 分布怪物坐标
     static void SetNormalTypeRadiusPosition( MonsterCreateData& xCreateData, float fPosX, float fPosY, float fRadius );
     ////////////////////////////////////////////////////////////////////////////////////////////////////////
     // 普通方式创建怪物
     static void ProcessNormalTypeCreateMonster( MonsterCreateData& xCreateData );

     // 创建多个专属怪
     static void ProcessNormalTypeCreateSpecialMonster( MonsterCreateData& xCreateData );
};

#endif