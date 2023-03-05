#ifndef __NPCFIGHTEX_H__
#define __NPCFIGHTEX_H__
/************************************************************************
                ս��NPC
                Filename:    NpcFightEx.h
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "NpcBaseEx.h"

class NpcFightEx : public NpcBaseEx, INHERIT_POOL_PARAM( NpcFightEx, 10 )
{
public:
    DECLARE_POOL_FUNC( NpcFightEx )

	enum FightType
	{
		FT_Player, // ֻ����
		FT_Monster,// ������֣�����������
		FT_Both,   // ����
	};

    NpcFightEx();
	virtual ~NpcFightEx(){};

    virtual bool IsFightNpc() { return true; }

	//virtual void OnDeath();


    // �ж��ܷ񱻹���
    virtual bool CheckCanBeAttack();  

    virtual void Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn = false );

	int GetFightType() { return m_pNpcInfo->fightData[0].fightType; }

    ////////////////////////////////////////////////////////////////////////
protected:
    // ˢ���
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // ����Ŀ��
    virtual void ProcessFindAttackTarget();

    // �ж��ܷ񹥻�Ŀ����
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // ���������Ұ���
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget );

    ///////////////////////////////////////////////////////////////////////////////////
    virtual int GetMaxAttackRange() { return m_pNpcInfo->fightData[0].maxRange; }

    virtual int GetBaseEnmityRange() { return m_pNpcInfo->fightData[0].baseEnmityRange; }

    // ���������Ұ��Χ
    virtual int GetIdleViewSight() { return m_pNpcInfo->fightData[0].view; }

    // ����ս����Ұ��Χ
    virtual int GetFightViewSight() { return m_pNpcInfo->fightData[0].fightView; }

    // �����ƶ��ٶ�
    virtual float GetIdleMoveSpeed() { return m_pNpcInfo->fightData[0].idleMoveSpeed; }

    // ׷�����ܻ��ƶ��ٶ�
    virtual float GetAttackMoveSpeed() { return m_pNpcInfo->fightData[0].moveSpeed; }

    // ���˥������
    virtual unsigned int GetEnmityRate() { return m_pNpcInfo->fightData[0].enmityDecRate; }

    // �����Ұ���
    virtual int GetViewEnmity() { return m_pNpcInfo->fightData[0].enmityView; }

    // ��ʼ����
    virtual float GetBornDir() { return m_pNpcInfo->direction; }

	// ���׷��ʱ��
	virtual uint32 GetKeepAttakTime() { return m_pNpcInfo->fightData[0].catchTime; }

	//virtual void OnDeath();
	bool CheckMonsterTpye(int type);

	// ������Ұ���
	virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

};


#endif