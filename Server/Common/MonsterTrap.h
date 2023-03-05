/********************************************************************
    Filename:    MonsterTrap.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERTRAP_H__
#define __GAMESERVER_MONSTERTRAP_H__

#pragma once

#include "MonsterBaseEx.h"

const uint32 gMonsterTrapPoolBatchSize = 10;

class MonsterPetTrap : public MonsterBaseEx,
                    INHERIT_POOL_PARAM( MonsterPetTrap, gMonsterTrapPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterPetTrap )

    MonsterPetTrap();
    virtual ~MonsterPetTrap();

    virtual void  OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig );
    virtual bool  OnThink();
    virtual bool  OnMove( uint32 lapseTime );
    
    virtual bool  MustOpenAI(){ return true; }
    virtual void  RefreshEnmity(){}
    
    uint8 IncreaseSkillUseCount() { _skillUseCount += 1; return _skillUseCount; } // �����ר��
protected:
    void  MoveAttackMoving( uint32 lapseTime ); // �й���Ŀ����ƶ�
    void  MovePosMoving   ( uint32 lapseTime ); // һ��ĵ�Ŀ����ƶ�    

protected:
    uint8 _skillUseCount; // �����ͷŵĳɹ�����
};

#endif // __GAMESERVER_MONSTERTRAP_H__
