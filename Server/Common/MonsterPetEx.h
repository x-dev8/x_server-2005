#ifndef __MONSTERPET_H__
#define __MONSTERPET_H__

/********************************************************************
            �������
            Filename:     MonsterPetEx.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterPetEx : public MonsterBaseEx
{
public:
    enum EPetDeathType
    {
        EPetDeathType_BeKilled, // ��ɱ
        EPetDeathType_Murder,   // ��ɱ
    };

public:
    MonsterPetEx();
    virtual ~MonsterPetEx(){};
    
    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    virtual bool IsPet() { return true; }

    uint8 GetPetType() const { return m_nPetType; }

    GameObjectId GetMasterID() { return m_nMasterID; }
    void SetMasterID( GameObjectId nValue ) { m_nMasterID = nValue; }

    // �����ƶ��ٶ�
    virtual float GetIdleMoveSpeed() { return m_fIdleMoveSpeed; }
    void SetIdleMoveSpeed(float fValue) { m_fIdleMoveSpeed = fValue; }

    // ׷�����ܻ��ƶ��ٶ�
    void SettAttackMoveSpeed( float fValue ){ m_fAttackMoveSpeed = fValue; }
    virtual float GetAttackMoveSpeed() { return m_fAttackMoveSpeed; }

    // �������ɱ
    virtual void CharacterMurder();

    // ��һ��ӡ��
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    // ����
    virtual void OnDeath();      

    virtual void CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

protected:

    // ˢ�¹�����
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // ���ҹ���Ŀ��
    virtual void ProcessFindAttackTarget();

    // �ж��Ƿ��ܹ���
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // ������Ұ�������б�
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget );

    // ��ù���˼��ʱ��
    virtual int GetThinkingSpaceTime();

    // ����˼���߼�
    virtual uint8 AiThinking( uint32 nCurrentTime );

    // �����������, ��ʧ��������˵���Ϣ
    virtual void ProcessPetDeath( int deathType ) ;

    // ����ս��״̬
    virtual void ProcessEndAttackStatus();

    // ����
    virtual void ProcessIdle();

protected:
    uint8 m_nPetType;

    // ���˵�ID
    GameObjectId m_nMasterID;

    // ����,ƽʱ���ƶ��ٶ�
    float m_fAttackMoveSpeed; 

    // �����ƶ��ٶ�
    float m_fIdleMoveSpeed; 
};

#endif