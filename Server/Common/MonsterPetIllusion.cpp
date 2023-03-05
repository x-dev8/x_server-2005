#include "MonsterPetIllusion.h"
#include "GamePlayer.h"

MonsterPetIllusion::MonsterPetIllusion() : MonsterPetEx()
{
    SetObjType( Object_MonsterIllusion );

    // Ĭ����������ߴ���
    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}

void MonsterPetIllusion::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterPetEx::Initialize( pConfig, xCreateData, pPlayer );

    GetCharFightAttr()->hpMax    .base  = pPlayer->GetCharFightAttr()->hpMax.final;              // ���ù�������HP
    GetCharFightAttr()->mpMax.base      = pPlayer->GetCharFightAttr()->mpMax.final;                  // ���ù�������MP    
    GetCharFightAttr()->hpRestore.base  = pPlayer->GetCharFightAttr()->hpRestore.final;          // ���ù����HP�ָ��ٶ�
    GetCharFightAttr()->mpRestore.base  = pPlayer->GetCharFightAttr()->mpRestore.final;          // ���ù����MP�ָ��ٶ�
    GetCharFightAttr()->exact.base      = pPlayer->GetCharFightAttr()->exact.final;                  // ���ù���ľ�ȷֵ
    GetCharFightAttr()->dodge.base      = pPlayer->GetCharFightAttr()->dodge.final;                  // ���ù���Ļر�
    GetCharFightAttr()->attackPhysics.base = pPlayer->GetCharFightAttr()->attackPhysics.final;  // ���ù������������
    GetCharFightAttr()->attackMagic.base = pPlayer->GetCharFightAttr()->attackMagic.final;      // ���ù����ħ��������
    GetCharFightAttr()->defendPhysics.base = pPlayer->GetCharFightAttr()->defendPhysics.final;  // ���ù�����������
    GetCharFightAttr()->defendMagic.base = pPlayer->GetCharFightAttr()->defendMagic.final;
    GetCharFightAttr()->attackSpeed.base = pPlayer->GetCharFightAttr()->attackSpeed.final;      // ���ù��﹥��Ƶ��

    UpdateCharAllAttibute();

    SetHP( pPlayer->GetHP() );
    SetMP( pPlayer->GetMP() );
}

