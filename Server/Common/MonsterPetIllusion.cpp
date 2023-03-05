#include "MonsterPetIllusion.h"
#include "GamePlayer.h"

MonsterPetIllusion::MonsterPetIllusion() : MonsterPetEx()
{
    SetObjType( Object_MonsterIllusion );

    // 默认在主人身边待命
    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}

void MonsterPetIllusion::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterPetEx::Initialize( pConfig, xCreateData, pPlayer );

    GetCharFightAttr()->hpMax    .base  = pPlayer->GetCharFightAttr()->hpMax.final;              // 设置怪物的最大HP
    GetCharFightAttr()->mpMax.base      = pPlayer->GetCharFightAttr()->mpMax.final;                  // 设置怪物的最大MP    
    GetCharFightAttr()->hpRestore.base  = pPlayer->GetCharFightAttr()->hpRestore.final;          // 设置怪物的HP恢复速度
    GetCharFightAttr()->mpRestore.base  = pPlayer->GetCharFightAttr()->mpRestore.final;          // 设置怪物的MP恢复速度
    GetCharFightAttr()->exact.base      = pPlayer->GetCharFightAttr()->exact.final;                  // 设置怪物的精确值
    GetCharFightAttr()->dodge.base      = pPlayer->GetCharFightAttr()->dodge.final;                  // 设置怪物的回避
    GetCharFightAttr()->attackPhysics.base = pPlayer->GetCharFightAttr()->attackPhysics.final;  // 设置怪物的物理攻击力
    GetCharFightAttr()->attackMagic.base = pPlayer->GetCharFightAttr()->attackMagic.final;      // 设置怪物的魔法攻击力
    GetCharFightAttr()->defendPhysics.base = pPlayer->GetCharFightAttr()->defendPhysics.final;  // 设置怪物的物理防御
    GetCharFightAttr()->defendMagic.base = pPlayer->GetCharFightAttr()->defendMagic.final;
    GetCharFightAttr()->attackSpeed.base = pPlayer->GetCharFightAttr()->attackSpeed.final;      // 设置怪物攻击频率

    UpdateCharAllAttibute();

    SetHP( pPlayer->GetHP() );
    SetMP( pPlayer->GetMP() );
}

