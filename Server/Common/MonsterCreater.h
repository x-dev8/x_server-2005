#ifndef __MONSTERCREATER_H__
#define __MONSTERCREATER_H__

/********************************************************************
            ���ﴴ����
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

    // ������ͨ����
    static MonsterBaseEx* CreateNormalMonster( MonsterCreateData& xCreateData );

    // ����������
    static MonsterBaseEx* CreateBuildMonster( MonsterCreateData& xCreateData );

    // �������汣����
    static MonsterBaseEx* CreateProtectedMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // ����ר����
    static MonsterBaseEx* CreateSpecialMonster( MonsterCreateData& xCreateData );

    // ������׽�����
    static MonsterBaseEx* CreatePetCaptureMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // �������������
    static MonsterBaseEx* CreatePetTrapMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // �����ٻ�����
    static MonsterBaseEx* CreatePetSummonMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // ������������
    static MonsterBaseEx* CreatePetNurtureMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // �������ܾ����
    static MonsterBaseEx* CreatePetIllusionMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer );

    // ����ս��npc��
    static MonsterBaseEx* CreateFightNpcMosnter( MonsterCreateData& xCreateData );

    // �����������ͨ����
    static void ProcessCreateNormalMonster( MonsterCreateData& xCreateData );
    
    // ���������ר����
    static void ProcessCreateSpecialMonster( MonsterCreateData& xCreateData );

protected:
     // ��ⴴ���������Ч��
     static ItemDefine::SMonster* CheckCreateMonster( MonsterCreateData& xCreateData );

     static void SetDirectiron( MonsterCreateData& xCreateData );

     // ��������
     static MonsterBaseEx* CreateMonster( MonsterCreateData& xCreateData, int nMonsterType, GamePlayer* pPlayer = NULL );

     // �ֲ���������
     static void SetNormalTypeRadiusPosition( MonsterCreateData& xCreateData, float fPosX, float fPosY, float fRadius );
     ////////////////////////////////////////////////////////////////////////////////////////////////////////
     // ��ͨ��ʽ��������
     static void ProcessNormalTypeCreateMonster( MonsterCreateData& xCreateData );

     // �������ר����
     static void ProcessNormalTypeCreateSpecialMonster( MonsterCreateData& xCreateData );
};

#endif