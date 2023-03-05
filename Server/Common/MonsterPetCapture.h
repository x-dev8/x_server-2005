#ifndef __MONSTERPETCAPTURE_H__
#define __MONSTERPETCAPTURE_H__

/********************************************************************
            ��׽��, ���ƶ�, �ɹ���
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

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    virtual bool IsSummonPet() { return true; }

protected:

    // ����������
    virtual void ProcessDeathDromItem(){}

    // ��Ӫ��������
    virtual void ProcessCampMonsterDeath(){}

    // �����������, ��ʧ��������˵���Ϣ
    virtual void ProcessPetDeath( int deathType );
};

#endif