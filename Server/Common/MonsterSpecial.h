#ifndef __MONSTERSPECIAL_H__
#define __MONSTERSPECIAL_H__

/********************************************************************
            ר����, ���ƶ�, �ɹ���
            Filename:     MonsterSpecial.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterSpecial : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterSpecial, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterSpecial )

    MonsterSpecial();
    virtual ~MonsterSpecial(){};

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // �ж��Ƿ��ܹ���
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    void SetSpecialType( int nValue ) { m_nSpceialType = nValue; }
    int GetSpecialType() const { return m_nSpceialType; }

    void SetSpecialValue ( uint32 nValue ) { m_nSpecialValue = nValue; }
    uint32 GetSpecialValue() const { return m_nSpecialValue; }

    bool CheckSpecialTarget( int nSpecialType, GamePlayer* pTarget );

protected:

    // ˢ�³��
    void ProcessRefreshEnmity( uint32 nCurrentTime );

    // ���������ű�
    void ProcessDeathCallScript();

    // ����������
    virtual void ProcessDeathDromItem();

protected:
    // ר������
    int m_nSpceialType;

    // ר��ֵ
    uint32 m_nSpecialValue;
};

#endif