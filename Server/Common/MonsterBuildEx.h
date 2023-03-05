#ifndef __MONSTERBUILD_H__
#define __MONSTERBUILD_H__

/********************************************************************
            ������, ���ܹ���Ŀ��, �����ƶ�
            Filename:     MonsterBuildEx.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterBuildEx : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterBuildEx, 20 )
{
public:
    DECLARE_POOL_FUNC( MonsterBuildEx )

    MonsterBuildEx();
    virtual ~MonsterBuildEx(){};

protected:

    // �����ֲ����ƶ�
    virtual void ProcessAiMoving( uint32 nCostTime ){};

    // �ж��Ƿ��ܹ���
    uint8 CheckCanAttackResult( BaseCharacter* pTarget ) { return CheckAttack::CanNotAttack; }

    // �������˼��
    void ProcessFindAttackTarget(){};

    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );
};

#endif