#ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__

/********************************************************************
    Filename:     MonsterBaseEx.h
    MaintenanceMan Mail: lori227@live.cn
*********************************************************************/

#include "AiCharacter.h"
#include "ItemDetail.h"

class MonsterBaseEx : public AiCharacter
{
public:
    // ���캯��
    MonsterBaseEx();

    // ��������
    virtual ~MonsterBaseEx();

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // ִ�й����߼�
    virtual void Run( uint32 nCostTime );

    // ��һ��ӡ��
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    // ����
    virtual void OnDeath();        

    // �Ƿ��ǹ���
    virtual bool IsMonster() { return true; }    

    // �ж��Ƿ����ٻ��ͳ���
    virtual bool IsSummonPet() { return false; }

    // ���������ϰ󶨵ļ�������
    virtual void SetVarID( int nValue ) {}
    virtual int GetVarID() { return -1; }

    // �ж��ܷ񱻹���
    virtual bool CheckCanBeAttack();

    // ��������
    virtual uint8 GetMonsterType() const { return m_nMonsterType; }
    void SetMonsterType( uint8 nValue ) { m_nMonsterType = nValue; }

    // ����״̬����
    uint8 GetMonsterStatus() const { return m_nMonsterStatus; }
    void SetMonsterStatus( uint8 nValue ) { m_nMonsterStatus = nValue; }
    
    // ����������к�
    void SetProduceIndex( int nValue ) { m_nProduceIndex = nValue; } 
    int GetProduceIndex() { return m_nProduceIndex; }

    // �����������״̬�ı�( Ĭ�ϲ����ǰ��������ļ��䵽ĳ��״̬, ���򰴲߻�����ı� )
    void ProcessMonsterStatusChange( int nMonsterStatus );
    
    // �Ƿ��ܹ����Ĺ���״̬
    bool CanAttackMonsterStatus();

    // �Ƿ���ִ�нű��Ĺ���״̬
    virtual bool CanQueryScriptTypeStatus();

    virtual void OnEnterFightState();
	virtual void  OnOutFightState();                               // ��ս��״̬

    // ��õ�ǰ״̬�ű����
    int GetMonsterStatusScriptEnter();

    // ���ù�����ʧ
    void SetMonsterExit() { m_xTimer[ AiDefine::AiTimer_Disappear ].NextTimer( 1 ); }

    // ����
    uint32 GetDaoxing() { return m_pMonsterConfig->nDaoxing; }

    //////////////////////////////////////////////////////////////////////////
    // ����ID
    int GetMonsterID() { return m_pMonsterConfig->stMonsterId; }
    // ģ��ID
    int GetModelID() { return m_pMonsterConfig->iModelID; }
    // ���˥������
    unsigned int GetEnmityRate() { return m_pMonsterConfig->nEnmityRate; }
    // ��������
    int GetRewardExp() { return m_pMonsterConfig->nRewardExp; }
    // �������ܾ���
    int GetRewardSkillExp() { return m_pMonsterConfig->nSuperfluitySkillExp; }
    // ������Ǯ
    int GetRewardMoney() { return m_pMonsterConfig->nCashMoney; }
    // ��������
    int GetRewardReputation() { return m_pMonsterConfig->nRewardReputation; }
    // ������ѫ
    int GetRewardExpolit() { return m_pMonsterConfig->nRewardExploit; }
    // �������Ѷ�
    int GetRewardFriendly() { return m_pMonsterConfig->nRewardFriendly; }
    // ����״̬
    int GetRewardStatusID() { return m_pMonsterConfig->nRewardStatusID; }
    // ��������
    int GetRewardDaoxing()  { return m_pMonsterConfig->nRewardDaoxing;  }
    // ������������
    int GetRewardMulType() { return m_pMonsterConfig->nRewardMulType; }
    // ������ֵ
    int GetRewardMulValue() { return m_pMonsterConfig->nRewardMulValue; }
    // ���������Ұ��Χ
    int GetIdleViewSight() { return m_pMonsterConfig->stView; }
    // ����ս����Ұ��Χ
    int GetFightViewSight() { return m_pMonsterConfig->stFightView; }

    // �����Ѫ���
    uint32 GetRestoreSpaceTime() { return m_pMonsterConfig->dwRestoreSpaceTime; }

    // �����Ѫ��ֵ
    int GetRestoreHP() { return m_pMonsterConfig->stHPRestore; }

    // �����ħ��ֵ
    int GetRestoreMP() { return m_pMonsterConfig->stMPRestore; }

    // �����ƶ��ٶ�
    float GetIdleMoveSpeed() { return m_pMonsterConfig->fIdleMoveSpeed; }

    // ׷�����ܻ��ƶ��ٶ�
    float GetAttackMoveSpeed() { return m_pMonsterConfig->fMoveSpeed; }

    // ��ù����׷����Χ
    int GetMaxAttackRange() { return m_pMonsterConfig->nMaxRange; }

    // ���׷��ʱ��
    virtual uint32 GetKeepAttakTime() { return m_pMonsterConfig->dwCatchTime; }

    // ��ù���Idle״̬���漴�ƶ�����
    int GetIdleMoveRate() { return m_pMonsterConfig->nIdleMoveRate; }

    // ��ù�����������Ұ��Χ
    int GetBaseEnmityRange() { return m_pMonsterConfig->nBaseEnmityRange; }

    // �����Ұ���
    int GetViewEnmity() { return m_pMonsterConfig->nEnmity; }

    // ��ù����Ƿ���������
    bool GetActiveMonster() { return m_pMonsterConfig->nIsInitiative != 0; }

    //  ����Ŀ���
    int16 GetResistBeMove() { return m_pMonsterConfig->nResistMove; }
    int16 GetResistBeAtt() { return m_pMonsterConfig->nResistAtt; }
    int16 GetResistBeMagic() { return m_pMonsterConfig->nResistMagic; }
    int16 GetResistBeTools() { return m_pMonsterConfig->nResistTools; }

    // ��������ϵ��
    float GetAttackPhysicsMod() { return m_pMonsterConfig->fAttackPhysicsMod; }
    float GetDefendPhysicsMod() { return m_pMonsterConfig->fDefendPhysicsMod; }
    float GetAttackMagicMod()   { return m_pMonsterConfig->fAttackMagicMod;   }
    float GetDefendMagicMod()   { return m_pMonsterConfig->fDefendMagicMod;   }

    virtual const char* GetAILuaScript() const { return m_pMonsterConfig->GetAILuaScript(); }

    void  SetMonsterConfig( ItemDefine::SMonster* pConfig) { m_pMonsterConfig = pConfig; }

    // ��������֮
    short GetAttackFloat() { return 0; }

    // �Ƿ��Ǳ�����
    bool  IsPassivity() { return m_bPassivity; }
    void  SetPassivity( bool bVal ){ m_bPassivity = bVal; }

    // ����������Ұ���
    virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // ������Ұ�ӳ���б�
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget );

	// ��ȡ���������
	virtual unsigned char GetPhyle() const { return m_pMonsterConfig->phyle; }

    // ��ȡ��������
    ItemDefine::SMonster* GetMonsterConfig() const { return m_pMonsterConfig; }

	virtual void WasKilled( BaseCharacter* pKiller );
	virtual void UpdateMonsterBeLong(BaseCharacter* pKiller = NULL);//���¹���Ĺ���
protected:

    // �ж��Ƿ��ܹ���
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // ���ҹ���Ŀ��
    virtual void ProcessFindAttackTarget();

    // ���������������
    virtual void ProcessDeathDromItem();

    // �����������������ű�
    void ProcessDeathCallScript();

    // �Ƿ���Կ���AI˼����״̬
    bool CheckAiThinkingMonsterStatus();

    // ��Ӫ��������
    virtual void ProcessCampMonsterDeath();

	virtual void ProcessGameBattleMonsterDeath();

    // ����������������״̬�ĸı�
    virtual void ProcessDeathChangeStatus();

    // �������״̬�ı�
    void ProcessMonsterStatusChange();
 
protected:
    // �������������
    ItemDefine::SMonster* m_pMonsterConfig;

    // ����������к�
    int m_nProduceIndex;

    // ��������
    uint8 m_nMonsterType;

    // ���������״̬( �������ת����npc֮�� )
    uint8 m_nMonsterStatus;

    // ��һ������״̬
    uint8 m_nNextMosntrStatus;

    // �Ƿ񱻶���
    bool m_bPassivity;

	//�ϴθ��¹�����ʱ��
	DWORD    m_dwLastBeLongTime;
};

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
inline bool MonsterBaseEx::CanAttackMonsterStatus()
{
    switch ( GetMonsterStatus() )
    {
    case MonsterDefine::StatusNormal:
    case MonsterDefine::StatusMonster:
        return true;
        break;
    default:
        break;
    }

    return false;
}

inline bool MonsterBaseEx::CanQueryScriptTypeStatus()
{
    switch ( m_nMonsterStatus )
    {
    case MonsterDefine::StatusMoveNpc:
    case MonsterDefine::StatusUnMoveNpc:
    case MonsterDefine::StatusMonsterDeath:
        return true;
        break;
    default:
        break;
    }

    return false;
}

inline bool MonsterBaseEx::CheckAiThinkingMonsterStatus()
{
    switch ( GetMonsterStatus() )
    {
    case MonsterDefine::StatusUnMoveNpc:
    case MonsterDefine::StatusMonsterBorn:
        return false;
        break;
    default:
        break;
    }

    return true;
}

#endif