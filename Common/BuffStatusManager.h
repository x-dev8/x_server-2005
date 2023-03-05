/********************************************************************
    Filename:     BuffStatusManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_BUFFSTATUSMANAGER_H__
#define __COMMON_BUFFSTATUSMANAGER_H__

#pragma once

#include "ItemDetail.h"

class MountManager;

class BuffEvent
{
public:
    BuffEvent() : bHide(false), bXinFa(false) {}

public:
    virtual void OnEnterHide() {};
    virtual void OnXinFaUpdate() {};

public:
    bool bHide  ;     // �������״̬
    bool bXinFa ;     // �ķ�Ӱ��״̬
};

class BuffStatusManager
{
public:
    enum EStatusAnim
    {
        eStatusAnim_None = 0, // û��״̬����
        eStatusAnim_Stun,     // ѣ�ζ���
        eStatusAnim_FallOver, // ˤ������
        eStatusAnim_Freeze,   // ��������
        eStatusAnim_Max,
    };

    //////////////////////////////////////////////////////////////////////////
    // �¼��ص�����
    BuffEvent* pBuffEvent;
    void CallBuffEvent() ;
    //////////////////////////////////////////////////////////////////////////

public:
    // ��ʼ��ϵ��
    BuffStatusManager();
    virtual ~BuffStatusManager();    
    void CreateFromData(SCharBuff* pData, int num);
    void CreateFromData(BuffEvent* pBuffEvent, SCharBuff* pData, int num);
    void AddStatusFromData( DWORD stageId, SCharBuff* pData, int num,DWORD dwCurTime, bool bFirstEnterWorld = false);

    // ���ϵ��
    bool  ClearBuff( int16 index, bool needUpdate = true);                      // ����������õ�buff
    bool  ClearAllBuff();                                                       // ������е�buff
    void  ClearBuffChangedRecords();                                            // ������е�buff�䶯��¼
    bool  ClearBuffByBuffIdLevel( int nStatusId,int nStatusLevel);              // ���buff����buffId�͵ȼ� 
    bool  ClearBuffByBuffId     ( int StatusID );                               // ���buff����buffId
    bool  ClearBuffByMasterCharID( GameObjectId shCharID, bool IsClearDebuff = true); // ���buff�����ͷ�����Id
    bool  ClearAllBuffByHaveAttack( bool bNeedUpdate = true );                  // ������е��к�״̬
    bool  ClearBuffByType( bool bIsAvail, int nType );
    void  ClearBuffClearIdRecords();                                            // ��� �����bufferId�Ķ���    
    void  ClearBuffWhenChangeMap();                                             // ������л���ͼ����Ҫȥ����Buff

    // ����ϵ��
    bool ApplyBuff( bool bStop, uint16 iStatusID, uint16 iStatusLevel, GameObjectId masterId, uint32 dwNowTime, bool bLastOne, uint32 dwDurationTime, uint32 dwMasterDbId, int eventType, int eventValue );       // Ӧ��buff    
    bool AddBuff( int16 nPos, bool bStop, uint16 iStatusId, int iStatusLevel, GameObjectId masterId, uint32 dwNowTime, bool bLastOne, uint32 dwDurationTime, uint32 dwMasterDBID, int eventType, int eventValue); // ����buff
    bool ApplyBuffsToChar( uint16 profession, SCharBaseAttr* pBase, SCharFightAttr* pFight ); // Buff��ֵ���õ���ɫһ������������

    void AddBuffIdToClearIdRecords( uint16 nID );                          // ���һ��ID��ClearStatusId����
    void AddBuffToClearRecords( const SCharBuff& rBufferStatus );          // ���һ��Buff��Clear Record����

    // ��ȡϵ��
    SCharBuff* GetBuff            ( int16 index );      // �õ��������е�buff
    SCharBuff* GetBuffByStatusID  ( int16 nStatusID );  // �õ��������е�buff
	bool IsBuffExist(int16 nStatusID);                  // StatusID��Ӧ��buff�Ƿ�������
    SCharBuff* GetBuffAddress     ( int16 index );      // �õ�buff���е�ַָ��
    SCharBuff* GetBuffClearRecord ( int16 index );      // �õ��������buff
    bool       GetBuffChangeRecord( int16 index );      // �õ�buff�ı��ʶλ

    int  GetClearIdArrayId(int nIndex);                 // �õ�nIndex�±��StatusId
    int  GetBufferStatusCount() { return buffMaxCount;} // �õ�Buff����    
    int  GetEnableStatusNum()   { return iEnableStatusNum;}
    int  HaveChangeChangeMonsterIDBuff();               // �õ�����״̬�ĸ���
    int  GetBufferStatusIndexById( int statusId );      // �õ��������е�buff�±�

    // ����ϵ��
    bool UpdateDurationTime();                          // ����Ҫ�����buffer ��������ʱ��Ƶ����һ��
    bool UpdateBufferOnEnterStage ( uint32 stageId  );  // ����buffer���볡����ʱ��
    bool UpdateOnBeAttack( const ItemDefine::SItemSkill* pSkillConfig ); // // �ܻ��ص�Update �����������ʱҪ�����״̬��
    bool UpdateOnBackAttack();  // �����ص�Update ���������(������ʱ��Ҫ�����״̬)
    bool UpdateOnMove();        // �ƶ��ص�Update �������ƶ����(�ƶ�ʱ��Ҫ)
    bool UpdateOnDead();        // �����ص�Update ������Buff�ļ������
    bool UpdateCounterValue();  // �ص�Update ������Buff�ļ������
    bool UpdateOnAttack();      // �����ص�Update ���buff
    void UpdateEffect();        // Update Buffer ��Ӱ��ı���

    // Logϵ��
    void  LogAndClearBufferClearIdArray();
    void  LogStatus( SCharBuff* pData = NULL);
    void  Log( int nFailLocation, int buffId, int buffLevel );
    
    // ��ȡ����ϵ��
    bool  IsHaveStatus(int iStatus);                                 // �ж�Ŀ���Ƿ���״̬   
    bool  IsHaveNegativeStatus( uint8 nNegativeType );               // �ж�Ŀ���Ƿ��и���״̬ 
    bool  IsRandRun()              { return bIsRandRun; }            // �������..(������)    
    //int   GetChangeSight()         { return iChangeSight;}         // �ı����� ������� < 0 ��ʾ���ı���Ұ
    int   GetCurStatusAnim()       { return nCurStatusAnim; }        // ��ȡ��ǰ��״̬����    
    //bool  IsCanBeFindByMonster()   { return bCanBeFindByMonster;}    // ���ܷ��֣����    
    //bool  IsAttackByMonsterFirst() { return bAttackByMonsterFirst; } // �ж������ȼ��𱻹��﹥��
    bool  IsCanMove()              { return bMoveFlag; }             // �жϿɷ��ƶ�
    bool  IsCanUsePhysicsSkill()   { return bUsePhysicsSkillFlag;}   // �ɷ�ʹ����������    
    bool  IsCanUseMagicSkill()     { return bUseMagicSkillFlag; }    // �ɷ�ʹ�÷�������
    bool  IsCanBePhyAttack()       { return bIsBePhyAttack; }
    bool  IsCanBeMagAttack()       { return bIsBeMagAttack; }
    bool  IsCanUseItem()           { return bUseItemFlag; }          // �ɷ�ʹ�õ���
    bool  IsHide()                 { return bHide; }                 // �Ƿ�����  
    bool  IsInvincible()           { return bInvincible; }           // �Ƿ��޵�
	bool  IsBuoy()                 { return bBuoy; }                 // �Ƿ񸡿�
	bool  IsCanRide()			   { return bCanRide;}				 // �ɷ�����

    uint8 GetDamageToHp() { return damagetohp; } // �˺�תΪѪ ͬʱ�����˺�
    void  SetCanMove( bool bCanMove ){ bMoveFlag = bCanMove; }
    
    //bool  IsIgnoreHedge()  { return bHedgeNull; } // �Ƿ���ӻر�    
    //bool  IsWeaponFormula(){ return bIsWeaponFormula; }        // �Ƿ����������˺�    
    bool  IsCanUseSkill( ItemDefine::SItemSkill* pSkill );     // ս��״̬���жϿɷ�ʹ��ĳ������
    bool  IsCanUseSkill( uint16 iSkillID, uint16 iSkillLevel);  // ս��״̬���жϿɷ�ʹ��ĳ������
    bool  IsClearStatusInAttack()     { return bClearStatusInAttack; }  // �ж��ܵ��˺���ʱ���Ƿ���Ҫ���״̬
    float GetDamageChange2MpRatioPer(){ return fDamage2MpRatioPer;}     // ȡ���˺���ת��Ϊmp�İٷ���
    int   GetDamageChange2MpRatio();

    float GetDamageReflectedRatio()   { return fDamageReflectRatio; }     // �˺���������
    uint8 GetDamageReflectProability(){ return nDamageReflectProability;} // �˺���������

    int   GetDamageChengedRate();                                  // �˺�����
    float GetDamageChengedRatePer();                               // �˺�����        
    
    //int   GetToPositonRate();  // �ж��Ļ���    
    //int   GetToPositonLevel(); // ��Ŀ���ж��ĵȼ�
    
    float GetSuckHpRate()       { return fSuckHpRate;        } // ��Ѫ�ı���
    int   GetSuckHpValue()      { return nSuckHpValue;       } // ��Ѫ��ֵ
    uint8 GetSuckHpProbability(){ return nSuckHpProbability; } // ��Ѫ�ļ���

    //float GetMPStoneRate(){ return fMPStolenRate;}
    //int   GetMPStoneVal(){ return iMPStolenVal; } // ͵MP��
    int   GetDamageMp();     // MP�˺�    
    
    bool  IsAttackClearStatus(){ return bAttackClearStatus; } //�жϹ���ʱ���Ƿ���Ҫ���״̬
    //short GetMagicShieldKid();
    //short GetPerDamageNeedMp();

    int   GetAddBaseAttr    ( int i ) { return nAddBaseAttr[i];     }
    int   GetAddBaseAttrPer ( int i ) { return nAddBaseAttrPer[i];  }

    //�˺�����
    float GetSuckDamgePer();
    short GetSuckDamgeMax() { return stSuckMax;} // �����˺����ֵ
    void  SetSuckDamgeMax(int nValue) { stSuckMax = nValue; }
    void  ClearSuckDamage();

    //float GetIncreaseMp(); //ҩˮЧ������
    //float GetIncreaseHp();

    float GetActionTimeMod();

    //�˺�����
    short GetHurtImmunity()  { return hurtImmunity; }
    void  SetHurtImmunity(int nValue) { hurtImmunity = nValue; }

    //short GetChangedSkill_Hurt( int i )
    //{
    //    if( i < eElement_Max && i > 0)
    //    { return stChangedSkill_Hurt[i]; }
    //    return 0;
    //}

    //short GetChangedSkill_HurtPer( int i )
    //{
    //    if( i < eElement_Max && i > 0)
    //    { return stChangedSkill_HurtPer[i]; }
    //    return 0;
    //}

    //short GetChangedPhy_Hurt()    { return stChangedPhy_Hurt; }
    //short GetChangedPhy_HurtPer() { return stChangedPhy_HurtPer;}

    void  SetBeCriticaledBufferId(short stBufferID)       { stAddBufferID = stBufferID;}
    void  SetBeCriticaledBufferLevel(short stBufferLevel) { stAddBufferLevel = stBufferLevel;}
    short GetBeCriticaledBufferId()                       { return stAddBufferID;}
    short GetBeCriticaledBuffedLevel()                    { return stAddBufferLevel;}

    bool  UpdateStatusIsInCriticaled( bool bIsBeCSed = false);
    bool  IsBeCriticaledNeedAddBuffer() { return bCsedAddBuffer; } // �Ƿ񱻱�����ʱ����Լ�buffer

    bool  CheckTargetIsHaveAddBufferFlag(float fAttackerHpPer);
    bool  CheckIsAddDeBuffer(){ return bAddDeBuffer;}

    void  SetDeBufferID(short stDeBufferID){stAddDeBufferID = stDeBufferID;}
    void  SetDeBufferLevel(short stDeBufferLevel){stAddDeBufferLevel = stDeBufferLevel;}
    short GetDeBufferID(){return stAddDeBufferID;}
    short GetDeBufferLevel(){return stAddDeBufferLevel;}

    float GetExpAddMul()   {  return fExpMulAdd + fExpMulAddByEquip; }
    
    void SetExpMulAddByEquip(uint16 expPer) 
    {
        fExpMulAddByEquip = 0.0f;
        fExpMulAddByEquip += static_cast<float>( expPer * DEF_PERCENT );
    }

    float GetSkillExpAddMul() { return fSkillExpMulAdd;  }
    //float GetAddIntonateRate(){ return fAddIntonateRate; }    
    //short GetCompoundRate()   { return stComposeOdds;    }
    //short GetIntensifyRate()  { return stIntensifyOdds;  }
    //float GetPkValueMulAdd()  { return fPkvalueMulAdd;        }
    //bool  IsCalcDailyPkValue(){ return bNeedCalcDailyPkValue; }
    //bool  IsUnControlRandRun(){ return bIsRandRun;            }
    bool  IsPetSupport(){return bIsPetSupport;}

    bool  IsHaveBackAttackDispelBuff() { return _nBackAttackDispelBuffCount > 0;}
    bool  IsHaveMoveDispelBuff()       { return _nMoveDispelBuffCount > 0; }
          
    void  SetCharName( const char* szName ){  _strCharacterName = szName; }
    float GetStatusLimitRatio( unsigned char ucType);

    void SetNextNotIntonate( bool bNextNotIntonate) { _bNextNotIntonate = bNextNotIntonate; }
    bool GetNextNotIntonate() { return _bNextNotIntonate; }

    void SetNextNotIntonateNum( int8 Num) { nNextNotIntonateNum = Num; }
    int8 GetNextNotIntonateNum() { return nNextNotIntonateNum; }

    float GetTimeExpMul()        { return _timeExpMul; }
    bool  IsDisableCallGraphic() { return _bDisableCallGraphic; }

    bool  IfConsumeEnergy() { return ifConsumeEnergy; }

    uint16 GetChangeSkillId(int index) { return changeSkillIds[index]; }
    uint32 GetChangeSkillTime(int index) { return changeSkillTimes[index]; }

    //int32  GetChangeActivityMax() { return changeActivityMax; }
    //float  GetActivityMul() { return activityMul; }

    //uint16 GetReduceTax() { return reduceTax; }
    uint16 GetDeathDurabilityPer() { return deathDurabilityPer; }
    uint16 GetDeathMountHPDropPer() { return deathMountHPDropPer; }

    int    GetAddCatchPetRate()  { return addCatchPetRate; }

    int32  GetAddMoney () { return addMoney; } 
    int32  GetAddReputation () { return addReputation; }
    int32  GetAddExploit () { return addExploit; }     
    int32  GetAddHonour  () { return addHonour;  }     
    int32  GetAddMasterValue () { return addMasterValue; } 
    int32  GetAddBattleScore () { return addBattleScore; } 
    float  GetReputationMul  () { return reputationMul ; } 
    float  GetExploitMul     () { return exploitMul; } 
    float  GetHonourMul      () { return honourMul;  } 
    float  GetMasterValueMul () { return masterValueMul; } 
    float  GetBattleScoreMul () { return battleScoreMul; } 

	uint16 GetBeDamagePerHPMax  () { return BeDamagePerHpMax; }
    //int16  GetAddMountBaseAttr(int nWitch)    {  return nAddMountBaseAttr[nWitch]; }
    //int16  GetAddMountBaseAttrPer(int nWitch) {  return nAddMountBaseAttrPer[nWitch]; }

    //int32  GetAddHonourLimit  () { return addHonourLimit;  } 
	bool   GetIsCanGetHonour(){return IsCanGetHonour;}
	bool   GetIsCanBeGetHonour(){return IsCanBeGetHonour;}
protected:
    void OnBuffHaveChanged( uint16 index );

private:
    SCharBuff* m_pstBodyStatus;                       // �����������е�״̬,��¼����
    SCharBuff  m_ClearBodyStatus[BodyStatusType_Max]; // ���������������״̬,��¼���� �����������߼�ʹ��
    uint16     m_nStatusClear   [BodyStatusType_Max]; // �������״̬Id
    bool       _buffChangeRecord[BodyStatusType_Max]; // ״̬��������λ�ñ�־

    int   iEnableStatusNum;       // ʵ�ʵ�buffer״̬������
    uint8 buffMaxCount;           // buff���������

    bool  bHide;                  // �Ƿ�����
	bool  bCanRide;				  // �ɷ�����
    bool  bMoveFlag;              // �ɷ��ƶ�
    bool  bUsePhysicsSkillFlag;   // �ɷ�ʹ�ü���
    bool  bUseMagicSkillFlag;     // �ɷ�ʹ�ü���
    bool  bIsBePhyAttack    ;     // �ɷ�������
    bool  bIsBeMagAttack    ;     // �ɷ�ħ������
    bool  bUseItemFlag;           // �ɷ�ʹ�õ���
    bool  bCanBeFindByMonster;    // �жϿɷ񱻹��﷢��
    bool  bAttackByMonsterFirst;  // �ж������ȼ��𱻹��﹥��
    bool  bClearStatusInAttack;   // �ж����ܵ��˺���ʱ���Ƿ���״̬
    bool  bAttackClearStatus;     // �ж��ڹ�����ʱ���Ƿ���״̬
	bool  bBuoy;                  // �Ƿ񸡿�
                                   
    int   iDamage2MpRatio;        // �����˺���mp
    float fDamage2MpRatioPer;     // �˺���mp��ת������
                                   
    int   iDamageChengedRate;     // �˺�����

    float fDamageReflectRatio;    // �˺���������
    uint8 nDamageReflectProability; // �˺���������
                                   
    float fDamageChengedRatePer;  // �˺����� ��%

    float fSuckHpRate;            // ��Ѫ����
    int   nSuckHpValue;           // ��Ѫֵ
    uint8 nSuckHpProbability;     // ��Ѫ����

    float fMPStolenRate;
    int   iMPStolenVal;

    int   iPhysicItemAttMinTemp;  // ��������BUFF
    int   iPhysicItemAttMaxTemp;  //

    bool  bIsWeaponFormula;       //�Ƿ������������˺�
    bool  bHedgeNull;             //�Ƿ���ӻر�
    short stStatusFree;                         //״̬����
    short stChangedSkill_Hurt[eElement_Max];    // �����˺�    
    short stChangedSkill_HurtPer[eElement_Max]; // �����˺�%

    // Phy Huge
    short stChangedPhy_Hurt;
    short stChangedPhy_HurtPer;
    int   iDamageMp;            // �˺�Ϊֱ�ӿ۳�MP
    short stMagicShieldKid;     // ħ���������˺�����
    float fSuckPer;             // �����˺�

	short stSuckBuffMax;		// ��ǰBUFF���˺�ֵ�������ֵ
    short stSuckMax;            // �����˺�ֵ
    //short stPerDamageNeedMp;    // ÿ���˺����ĵ�MP
    short hurtImmunity;         // �˺����ߴ���

    //��������
    //int32   changeActivityMax;    //�ı��������
    //float   activityMul      ;    //�����ָ�����

    //ҩˮЧ������
    //float fMpIncreasePer;
    //float fHpIncreasePer;

    float fActionTimeChangMod; //��������ʱ��ı�ϵ��

    //���������ӵ�״̬
    short stAddBufferID;
    short stAddBufferLevel;

    //���������ӵ�״̬
    short stAddDeBufferID;
    short stAddDeBufferLevel;

    bool bAddDeBuffer;
    bool bCsedAddBuffer;

    float fExpMulAdd;        // ���Ӿ���ʱ��ľ���ӳ� ״̬�����
    float fExpMulAddByEquip; // ���Ӿ���ʱ��ľ���ӳ� װ�������

    float fSkillExpMulAdd; // ���Ӽ��ܾ���ʱ��ļ��ܾ���ӳ�
    
    int   nCurStatusAnim;    // ��ǰ״̬����(�����ȼ�)
    //float fAddIntonateRate;
    int   nAddBaseAttr[EBaseAttr_MaxSize];      // һ�����Լӳ�
    int   nAddBaseAttrPer[EBaseAttr_MaxSize];   // һ�����Լӳɰٷֱ�

    //int   nAddMountBaseAttr[EBaseAttr_MaxSize];      // ����һ�����Լӳ�
    //int   nAddMountBaseAttrPer[EBaseAttr_MaxSize];   // ����һ�����Լӳɰٷֱ�

    //short stComposeOdds;
    //short stIntensifyOdds;

    //float fPkvalueMulAdd;

    //bool bNeedCalcDailyPkValue;

    bool bIsRandRun;                  // �Ƿ��������
    bool bIsPetSupport;               // �Ƕ���������˺�
    int  _nBackAttackDispelBuffCount; // �ܵ�����ʱ������buff����
    int  _nMoveDispelBuffCount;       // �ƶ�ʱ������buff����

    int nChangeMonsterID;             // �������ID

    float _fStatusLimitResistRatio[SNT_MaxCount];

    bool  _bNextNotIntonate;        // ��һ�μ����Ƿ�˲��
    int8  nNextNotIntonateNum;      // ˲������
    
    std::string _strCharacterName;  // ��ɫ����
    float _timeExpMul;              // ʱ�侭��ӳ�
    bool  bInvincible;              // �޵�״̬
    uint8 damagetohp;               // �˺�ת����Hpͬʱ����Ѫ
    
    bool  _bDisableCallGraphic;     // �Ƿ������֤��
    bool ifConsumeEnergy;           // �Ƿ���������MP

    uint16 changeSkillIds[ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize]      ;   //�ı���ȴʱ��ļ���
    uint32 changeSkillTimes[ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize]    ;   //�ı似����ȴʱ��

    //uint16 reduceTax;               //����˰�� 
    uint16 deathDurabilityPer;      //����װ���;öȽ��� 
    uint16 deathMountHPDropPer;     //����������������  

    int16  addCatchPetRate;         //���ӳ��ﲶ׽����

    int32     addMoney                ;   // ���ӽ�Ǯ
    int32     addReputation           ;   // ��������
    int32     addExploit              ;   // ���ӹ�ѫ
    int32     addHonour               ;   // ��������
    int32     addMasterValue          ;   // ��������
    int32     addBattleScore          ;   // ����ս������
    float     reputationMul           ;   // ��������
    float     exploitMul              ;   // ��ѫ����
    float     honourMul               ;   // ��������
    float     masterValueMul          ;   // ��������
    float     battleScoreMul          ;   // ս�����ֱ���

    int32     addHonourLimit          ;   // ������������

	uint16    BeDamagePerHpMax			  ;   // ���˺��󲻹ܶ���ֵ,ÿ�ζ�ֻ���ٷֱ�����

	bool	  IsCanGetHonour;
	bool	  IsCanBeGetHonour;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void BuffStatusManager::AddBuffIdToClearIdRecords( uint16  nID)
{
    for (int nLoop = 0; nLoop <BodyStatusType_Max; ++nLoop)
    {
        if (m_nStatusClear[nLoop] <= 0)
        {
            m_nStatusClear[nLoop] = nID;
            return;
        }
    }
}

inline void BuffStatusManager::AddBuffToClearRecords( const SCharBuff& rBufferStatus )
{
    for (int nLoop = 0; nLoop <BodyStatusType_Max; ++nLoop)
    {
        if (m_ClearBodyStatus[nLoop].StatusID <= 0 && m_ClearBodyStatus[nLoop].iLevel<= 0)
        {
            m_ClearBodyStatus[nLoop] = rBufferStatus;
            return;
        }
    }
}

inline int BuffStatusManager::GetClearIdArrayId(int nIndex)
{
    if (nIndex < 0||nIndex >= BodyStatusType_Max)
        return 0;
    return m_nStatusClear[nIndex];
}

inline void BuffStatusManager::ClearBuffWhenChangeMap()
{
    for ( int nLoop = 0; nLoop < buffMaxCount; ++nLoop )
    {// ״̬ID > 0 && �洢������ ESRT_OnlyInMap������Ҫ���
        if ( m_pstBodyStatus[nLoop].StatusID > InvalidLogicNumber && m_pstBodyStatus[nLoop].restoreType == ItemDefine::ESRT_OnlyInMap )
        {
            ClearBuff( nLoop, true );
        }
    }
}

inline void BuffStatusManager::ClearBuffClearIdRecords()
{
    for (int np = 0 ; np < BodyStatusType_Max; ++np)
    {
        m_nStatusClear[np] = 0;
    }
}

inline bool BuffStatusManager::IsBuffExist(int16 nStatusID)
{
	for (int i = 0; i < buffMaxCount; ++i)
	{
		if (m_pstBodyStatus[i].StatusID == nStatusID && m_pstBodyStatus[i].StatusID > 0 && m_pstBodyStatus[i].iLevel > 0)
		{
			return true;
		}
	}
	return false;
}

inline SCharBuff* BuffStatusManager::GetBuff( int16 index)
{
    if (index <0 || index >=buffMaxCount)
    { return NULL; }

    if ( m_pstBodyStatus[index].StatusID<=0 || m_pstBodyStatus[index].iLevel<=0)
    { return NULL; }
    
    return &m_pstBodyStatus[index];
}

inline SCharBuff* BuffStatusManager::GetBuffByStatusID( int16 nStatusID )
{
    for (int i = 0; i < buffMaxCount; ++i)
    {
        if (m_pstBodyStatus[i].StatusID == nStatusID && m_pstBodyStatus[i].StatusID > 0 && m_pstBodyStatus[i].iLevel > 0)
        {
            return &m_pstBodyStatus[i];
        }
    }

    return NULL;
}


inline SCharBuff* BuffStatusManager::GetBuffAddress( int16 index)
{
    if (index <0 || index >=buffMaxCount)
    { return NULL; }
    
    return &m_pstBodyStatus[index];
}

inline SCharBuff* BuffStatusManager::GetBuffClearRecord( int16 index )
{
    if ( index<0 || index >=BodyStatusType_Max)
    { return NULL; }

    if ( m_ClearBodyStatus[index].StatusID <= 0 || m_ClearBodyStatus[index].iLevel <= 0)
    { return NULL; }

    return &m_ClearBodyStatus[index];
}

inline bool BuffStatusManager::GetBuffChangeRecord( int16 index )
{
    if ( index<0 || index >=BodyStatusType_Max)
    { return NULL; }

    return _buffChangeRecord[index];
}

inline float BuffStatusManager::GetStatusLimitRatio( unsigned char ucType)
{
    if ( ucType > SNT_TORPID )
        return 0.0f;

    return _fStatusLimitResistRatio[ ucType ];
}

#endif // __COMMON_BUFFSTATUSMANAGER_H__
