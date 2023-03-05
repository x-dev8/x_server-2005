#ifndef __MONSTERDEFINE_H__
#define __MONSTERDEFINE_H__

/************************************************************************
                �������Զ���

************************************************************************/

namespace MonsterDefine
{
    enum EConstDefine
    {
        ////////////////////// ����״̬
        StatusNormal = 0,   // ��ͨ״̬( һ��Ĺ��� )
        StatusMoveNpc,      // ���ƶ���npc״̬( ���ɹ��� )
        StatusUnMoveNpc,    // �������ƶ���npc״̬
        StatusMonster,      // Monster״̬( �˽׶οɹ��� )
        StatusMonsterDeath, // Monster����״̬���ɹ�����( ���������ѹ�������, ��Ϊ���滹�����߼�, �����˵�� )

        StatusMonsterBorn = 100,  // �������״̬( �ͻ�����Ҫ���ų���������, �Ľ׶β��ܹ���, ���ܶԻ� )
        /////////////////////////////////////////////////////
        // ר������
        SpecialNone = 0,
        SpecialPlayerAttack,  // ר����ҹ���( ֻ��ר����Ҳſ��Թ��� )
        SpecialPlayerVar,     // ר����Ҽ�������( �����˶����Թ��� )
        SpecialTeamAttack,    // ר����ҹ���( ֻ��ר������ſ��Թ��� )
        SpecialTeamVar,       // ר�������������( �����˶����Թ��� )  
    };
}

#endif