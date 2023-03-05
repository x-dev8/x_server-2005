#ifndef __MONSTERPETTRAP_H__
#define __MONSTERPETTRAP_H__

/********************************************************************
            �����, �����ƶ�, �ɹ���
            Filename:     MonsterPetTrap.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterPetEx.h"

class MonsterPetTrap : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterPetTrap, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterPetTrap )

    MonsterPetTrap();
    virtual ~MonsterPetTrap(){};

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // �ж��Ƿ��ܹ���
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

protected:
    // ˢ�³��
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // ���ҹ���Ŀ��
    virtual void ProcessFindAttackTarget();

    // ִ�й���AiTask
    virtual void ProcessAiTask( AiTask* pAiTask );

    // �������ս��״̬
    virtual void ProcessEndAttackStatus();

    // ������
    virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

    // ����������
    virtual void ProcessDeathDromItem(){};

};

#endif