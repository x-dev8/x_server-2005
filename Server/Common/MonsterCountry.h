/************************************************************************/
/*      FileName:MonsterCountry.h                                       */
/*      Author:eliteYang                                                */
/*      Desc:���ҹ�                                              */
/************************************************************************/
#ifndef __MONSTERCOUNTRY_H__
#define __MONSTERCOUNTRY_H__

#pragma once

#include "MonsterNormal.h"

const uint32 gMonsterCountryPoolBatchSize = 10;

// ���ҹ֣�������ս��NPC��ֻ���������
class MonsterCountry : public MonsterNormal
{
public:
    DECLARE_POOL_FUNC( MonsterCountry )

    MonsterCountry(){ }
    ~MonsterCountry(){}
};

    //virtual void RefreshEnmity();

//    virtual void OnBeAttacked( BaseCharacter* pAttacker, const CItemDetail::SItemSkill* pSkillConfig ); // ������
//    virtual bool OnThink();
//    virtual bool OnMove( uint32 lapseTime );
//    //virtual bool IsAICanAttack( BaseCharacter* pChar );
//    // TODO:ʣ����Ҫ�ĺ���
//protected:
//    //void UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster ); // ���ָ���Ŀ��ĳ��ֵ
//    void ThinkAttack(); // ���Բ�����������Ϊ
//    void ThinkIdle();   // ���Բ���Idle����Ϊ
//    void ThinkIdleMove();   // �����ƶ�
//
//    void MoveAttackMoving( uint32 lapseTime );  // �й���Ŀ����ƶ�
//    void MovePosMoving( uint32 lapseTime );     // һ�����ƶ�


#endif  // __MonsterCountry_h__