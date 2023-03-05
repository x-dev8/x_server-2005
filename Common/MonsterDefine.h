#ifndef __MONSTERDEFINE_H__
#define __MONSTERDEFINE_H__

/************************************************************************
                怪物属性定义

************************************************************************/

namespace MonsterDefine
{
    enum EConstDefine
    {
        ////////////////////// 怪物状态
        StatusNormal = 0,   // 普通状态( 一般的怪物 )
        StatusMoveNpc,      // 可移动的npc状态( 不可攻击 )
        StatusUnMoveNpc,    // 不可以移动的npc状态
        StatusMonster,      // Monster状态( 此阶段可攻击 )
        StatusMonsterDeath, // Monster死亡状态不可攻击了( 服务器不把怪物消除, 因为后面还会有逻辑, 怪物可说话 )

        StatusMonsterBorn = 100,  // 怪物出生状态( 客户端需要播放出生动作等, 改阶段不能攻击, 不能对话 )
        /////////////////////////////////////////////////////
        // 专属类型
        SpecialNone = 0,
        SpecialPlayerAttack,  // 专属玩家攻击( 只有专属玩家才可以攻击 )
        SpecialPlayerVar,     // 专属玩家记数变量( 其他人都可以攻击 )
        SpecialTeamAttack,    // 专属玩家攻击( 只有专属队伍才可以攻击 )
        SpecialTeamVar,       // 专属队伍记数变量( 其他人都可以攻击 )  
    };
}

#endif