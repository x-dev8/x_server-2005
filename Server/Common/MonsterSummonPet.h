/********************************************************************
    Filename:    MonsterSummonPet.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERSUMMONPET_H__
#define __GAMESERVER_MONSTERSUMMONPET_H__

#pragma once

#include "MonsterPetEx.h"

const uint32 gMonsterPetPoolBatchSize = 10;

class MonsterSummonPet : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterSummonPet, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterSummonPet )

    MonsterSummonPet();
    virtual ~MonsterSummonPet(){};

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    virtual bool IsSummonPet() { return true; }

protected:

    // ����������
    virtual void ProcessDeathDromItem(){}

    // ��Ӫ��������
    virtual void ProcessCampMonsterDeath(){}

    // �����������, ��ʧ��������˵���Ϣ
    virtual void ProcessPetDeath( int deathType ) ;
};

#endif // __GAMESERVER_MONSTERSUMMONPET_H__
