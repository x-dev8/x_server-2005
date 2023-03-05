#ifndef __MONSTERPETILLUSION_H__
#define __MONSTERPETILLUSION_H__

/********************************************************************
            �����, ���ƶ�, �ɹ���
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

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // ����ֲ��ɿ���
    virtual bool IsSummonPet() { return false; }

protected:

    // ����������
    virtual void ProcessDeathDromItem(){}

    // ��Ӫ��������
    virtual void ProcessCampMonsterDeath(){}


};

#endif