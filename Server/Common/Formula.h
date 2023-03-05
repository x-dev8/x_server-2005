/********************************************************************
    Filename:     Formula.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_FORMULA_H__
#define __GAMESERVER_FORMULA_H__

#pragma once

#include "MeRTLibsServer.h"
#include "ItemDetail.h"

class BaseCharacter;

class CFormula
{
public:
    enum eAttackHand
    {
        e_Rhand = HT_RightHand,
        e_Lhand = HT_LeftHand,
        e_Max
    };
    
    enum
    { //����
        e_Exact = 0,
        e_Attack,
        e_BeAttack,
        e_PowerMax
    };

    enum eDaoxingEffect
    {
        e_None   = 0,
        e_Resist = 1,    // �����ֿ�
        e_Stifle = 2,    // ����ѹ��
    };
    
    struct SResult
    { // ���Ľ�������ʾ�ṹ
        SResult()
        { 
            memset( this, 0, sizeof(SResult) );
            memset( m_nDispelNegativeType, -1, sizeof(m_nDispelNegativeType));
        }
        void Reset(); // ��������

        short m_stBalanceType;                                  // ��������

        short m_ustMeAddStatusID[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize];    // ����״̬���(���ҵ�)
        short m_ustMeAddStatusLevel[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize]; // ����״̬�ȼ�(���ҵ�)

        short m_ustDstAddStatusID[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize];   // ����״̬���(���Է���)
        short m_ustDstAddStatusLevel[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize];// ����״̬�ȼ�(���Է���)

        short m_ustMeAddStatusIDFromEquip    [ EEquipPartType_MaxEquitPart ]; // ����װ��״̬���(���ҵ�) 
        short m_ustMeAddStatusLevelFromEquip [ EEquipPartType_MaxEquitPart ]; // ����װ��״̬�ȼ�(���ҵ�)
        short m_ustDstAddStatusIDFromEquip   [ EEquipPartType_MaxEquitPart ]; // ����װ��״̬���(���Է���)
        short m_ustDstAddStatusLevelFromEquip[ EEquipPartType_MaxEquitPart ]; // ����װ��״̬�ȼ�(���Է���)

        DWORD m_dwSubComboStatus;                               // ���״̬λ��
        DWORD m_dwClearStatus[ItemDefine::CLEAR_MAX_STATUS];   // ���״̬ID

        bool  m_bMiss;                                          // �����ɹ�ʧ�ܱ�־
        int   m_iDamage;                                        // HP�˺�ֵ
        int   m_nDamageMp;                                      // MP�˺�
        int   m_iHPRestore;                                     // HP�Ļָ�ֵ        
        int   m_iMPRestore;                                     // MP�Ļָ�
        int   m_iXPRestore;                                     // XP�Ļָ�ֵ
        int   m_nExtraHp  ;                                     // ˲������HP
        int   m_nShieldHp ;                                     // ��������HP
        
        bool  m_bBackHit    ;                                   // �Ƿ񱳻�
        bool  m_bCriticalHit;                                   // �Ƿ񱩻�
        bool  m_bRelive     ;                                   // �Ƿ񸴻�
        int8  m_nDaoxingEffect;                                 // ����Ӱ�� �ֿ� ���� ѹ��
        bool  m_bHurtImmunity;                                  // �˺����� �۹�
        
        int   m_nBackAttackDamage;                              // �����˺�
        short m_stBackStrikeAddMeStatus;                        // �������ҵ�״̬
        short m_stBackStrikeAddMeStatusLevel;
        short m_stBackStrikeAddDstStatus;                       // �������Է���״̬
        short m_stBackStrikeAddDstStatusLevel;

        int8  m_nDispelNegativeType[ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize];  // �������״̬����
    };

public:
    CFormula();

    // ���ò�������ӿ�
    void  Reset();                                 // ���ý�����
    void  ResetAttacker();                         // ���ù�����
    void  ResetTarget();                           // �����ܹ�������
    void  SetAttacker( BaseCharacter* pAttacker ); // ���ù�����
    bool  AddTarget  ( BaseCharacter* pTarget );     // ����һ���ܹ�����
    void  SetSkill   ( ItemDefine::SItemSkill* pSkill) { m_pSkill = pSkill; }
    bool  IsAttackable();                          // �Ƿ��ڿɹ���������״̬    
    void  BalanceAttackHero( int iAttackHand );
    
    int  CalcReliveRestoreHP( int nWhich );  // ���㸴���ָ�HP����ֵ

    // �й�״̬
    void SetStatusTarget( BaseCharacter *pTarget ){ m_pStatusTarget = pTarget; }
    void SetStatusSrc( BaseCharacter *pSrc)       { m_pStatusSrc = pSrc;       }
    void SetStatusBuff( SCharBuff* pBuff)       { m_pBuff = pBuff;       }
    void SetStatusInfo( unsigned short ustStatusID, unsigned short ustStatusLevel );

    void BalanceStatusHero();               // ״̬�˺�����
    void CalcStatusBalanceTypeNone();       // ״̬�˺����͹�ʽ
    void CalcStatusBalanceTypeRestore();    // ״̬�ظ����͹�ʽ
    
    // ���״̬�Ľ�����
    SResult* GetTargetStatusResult(){ return &m_TargetStatusResult; }
    SResult* GetSrcStatusResult()   { return &m_SrcStatusResult;    }

    // ��ý�����
    SResult* GetTargetLastResult(int nWhich);
    SResult* GetSrcLastResult(int nWhich);

    // ��ù���Ŀ��ָ��
    BaseCharacter* GetTarget( int nWhich );
    int  GetTargetNum(){ return m_iTotalTarget; }
    void InitPlayerAttackerAttr( int iStrength,int iMagic,short stMinBonusDamageRange,short stMaxBonusDamageRange );

protected:
    bool InitBalanceDamageData( SResult*& pResult, SResult*& pSrcResult, int nWhich ); // ��ʼ����������
    bool CheckingStatus ( int nTargetIndex );
    void BalanceMissHero( int nTargetIndex );                                          // ����ʧ�ܽ���
    void BalanceDamageHero( int nWhich,int iAttackHand );                              // �˺�����
    void BalanceRestoreHero( int nWhich );                                             // �ظ�����
    void BalanceAddStatusHero( SResult* pResult, BaseCharacter* pTarget );             // ����״̬����
    void BalanceAddDstStatusHero( SResult* pResult, BaseCharacter* pTarget, uint8 index );
    
    void CallCustomBanalanceHero    ( SResult*& pResult, SResult*& pSrcResult, int nWhich ,int iAttackHand);    // �����Զ��幫ʽ
    void CallByBalanceTypeNoneHero  ( SResult* pResult, SResult* pSrcResult, int nWhich );                      // �����㹫ʽ���� û���˺��κν���
    void CallByBalanceTypePhyDamageHero ( SResult* pResult, SResult* pSrcResult, int nWhich,int iAttackHand);   // �����㹫ʽ���� �����˺�����
    void CallByBalanceTypeMagDamageHero ( SResult* pResult, SResult* pSrcResult, int nWhich );                  // �����㹫ʽ���� ħ���˺�����
    void CallByBalanceTypeBothDamageHero( SResult* pResult, SResult* pSrcResult, int nWhich,int iAttackHand);   // �����㹫ʽ���� ����ħ���˺�����
    void CallByBalanceTypeRestoreHpMp   ( SResult* pResult, int nWhich  );                                      // �����㹫ʽ���� ��HP MP����
    void CallByBalanceTypeRelive        ( SResult* pResult, int nWhich );                                       // �����㹫ʽ���� �������

    //void BalanceAddStatus( SResult* pResult, BaseCharacter* pTarget, BaseCharacter* pSrc = NULL );           // ����״̬����

    int  CalcNormalDamage( uint8 damageType, int nWhich, SResult* pResult, SResult* pSrcResult );   // ������ͨ�˺�
    int  CalcAdditionalDamage (int nWhich, SResult* pResult, SResult* pSrcResult );                 // ���㸽���˺�
    bool TryBackStrikeDamage  (int nWhich, SResult* pResult, SResult* pSrcResult );                 // ���㱳��
    bool TryCriticalDamageHero(int nWhich, SResult* pResult, SResult* pSrcResult );                 // ���㱩��

    void CalcTargetSuckDamage ( BaseCharacter* pDst, SResult* pResult );   
    int  CalcSuckHp( int iDamage );
    int  CalcDamageReflect( BaseCharacter* pTarget, int iDamage );
    bool IsHaveDamageToHp( BaseCharacter* pTarget );
    int  CalcDamageToHp( BaseCharacter* pTarget, int iDamage );                                     // �����˺�ת��

	void CalcBeDamagePerHP(BaseCharacter* pDst, SResult* pResult );									//�ܵ��˺���ס�ٷֱȼ���
public:
    //״̬�����ö���,��״̬�������Ϣ
    BaseCharacter* m_pStatusTarget;
    BaseCharacter* m_pStatusSrc;
    
    SCharBuff* m_pBuff;
    ItemDefine::SItemStatus* m_pStatus;
    unsigned short            m_ustTargetStatusID;
    unsigned short            m_ustTargetStatusLevel;    
    SResult m_TargetStatusResult;                     // ״̬�ļ�����..���ͷ��ߵ����ݣ����ǹ���Ŀ��
    SResult m_SrcStatusResult;                        //���ͷ��ߵ�Ӱ������,���Ǽ��ܵ��ͷ��ߣ�������
    
private:
    BaseCharacter* m_pAttacker;                            // ������
    int            m_iAttackerStrength;                    // �����ߵ�����
    int            m_iAttackerMagic;                       // �����ߵ�ħ��
    short          m_stMinBonusDamageRange;
    short          m_stMaxBonusDamageRange;
    BaseCharacter* m_pTarget[dr_MaxAttackTarget];          // ����Ŀ����    
    int            m_iTotalTarget;                         // ����Ŀ����    
    SResult        m_TargetLastResult[dr_MaxAttackTarget]; // ����������
    SResult        m_SrcLastResult[dr_MaxAttackTarget];    // 
    ItemDefine::SItemSkill* m_pSkill;                     // ��ǰ��������
};

//////////////////////////////////////////////////////////////////////////
// inline
inline CFormula::SResult* CFormula::GetTargetLastResult( int nWhich )
{
    if( nWhich < 0 || nWhich >= dr_MaxAttackTarget )
        return NULL;
    return &m_TargetLastResult[nWhich];
}

inline CFormula::SResult* CFormula::GetSrcLastResult(int nWhich)
{
    if( nWhich < 0 || nWhich >= dr_MaxAttackTarget )
        return NULL;
    return &m_SrcLastResult[nWhich];
}

inline BaseCharacter* CFormula::GetTarget( int nWhich ) 
{
    if(nWhich < 0 || nWhich>=m_iTotalTarget)
    { return NULL; }
    return m_pTarget[nWhich];
}

#endif // __GAMESERVER_FORMULA_H__
