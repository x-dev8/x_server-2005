#ifndef __MONSTERPROTECTED_H__
#define __MONSTERPROTECTED_H__

/********************************************************************
            ������, ���ɹ���, ���ƶ�
            Filename:     MonsterProtected.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterProtectedEx : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterProtectedEx, 10 )
{
public:
    DECLARE_POOL_FUNC( MonsterProtectedEx )

    MonsterProtectedEx();
    virtual ~MonsterProtectedEx();

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    GameObjectId GetMasterID() { return m_nMasterID; }
    void SetMasterID( GameObjectId nValue ) { m_nMasterID = nValue; }

	bool IsCanRide() const { return mIsCanRide; }
	void SetIsCanRide(bool b) { mIsCanRide = b; }

    int GetVarID() { return m_nVarID; }
    void SetVarID( int nValue ) { m_nVarID = nValue; }

    // ��������ɱ
    void CharacterMurder();

    // ��һ��ӡ��
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    // ����
    virtual void OnDeath();       

protected:
    // ����˼���߼�
    virtual uint8 AiThinking( uint32 nCurrentTime );

    // ��ù���˼��ʱ��
    virtual int GetThinkingSpaceTime();

    // ������������, ��ʧ��������˵���Ϣ
    void ProcessProtectedDeath();

    // �ж��Ƿ��ܹ���
    uint8 CheckCanAttackResult( BaseCharacter* pTarget ) { return CheckAttack::CanNotAttack; }

    // �Ƿ��ܼ���Ұ���
    virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // ��������Ŀ��
    void ProcessFindAttackTarget(){};

    // ����ս��״̬
    void ProcessEndAttackStatus();

private:
    // ���˵�ID
    GameObjectId m_nMasterID;

	// �ܷ���
	bool mIsCanRide;

    // �󶨵ļ�������ID
    int m_nVarID;
};

#endif