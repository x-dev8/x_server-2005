/********************************************************************
    Filename:     BaseCharacter.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_CHARACTER_H__
#define __GAMESERVER_CHARACTER_H__

#pragma once

#include "GlobalDef.h"
#include "MessageDefine.h"
#include "DataBuffer.h"
#include "ScriptVM.h"
#include "ScriptMgr.h"
#include "CharacterTimeStatus.h"
#include "Helper.h"
#include "Formula.h"
#include "ItemDetail.h"
#include "BuffStatusManager.h"
#include "ContinuousTime.h"
#include "GameServer.h"
#include "GameArea.h"
#include "GameStage.h"
#include "Enmity.h"
#include "NewWithDebug.h"
#include "SkillTaskManager.h"
#include "IBaseCharControl.h"
#include "IBaseControl.h"
#include "NetControl.h"
#include "ItemSkillSpecialAttr.h"
#include "MountManager.h"
#include "RecipeManager.h"
#include "AttackFunction.h"
#include "IBaseCharProperty.h"
#include "GameDefinePet.h"
#include "AiDefine.h"
#include "GameBattleMessage.h"

// �Ƿ��������ֵǿ���������
//const bool KICK_CREDIT = false;

class GamePlayer;
class CEffectChar;
class GameStage;

enum EGameLogicResult
{
    GLR_Success = ER_Success,
    GLR_StatusNotExist,
    GLR_InDeadNotUseStatus,
    GLR_StatusSourceNotExist,
    GLR_StatusApplyFail,
};

enum EPlayerStatus
{ //��Ϸ�������߼��е�״̬
    CS_START,                  // ��Character::����Ĭ������ֵ
    CS_CHECK,                  // PlayerChar��Ĭ�ϸı䵽�����ֵ�ȴ��ͻ��˷��͹�����֤��Ϣ..(˵������Ŀͻ���)
    CS_LOGIN,                  // �յ���¼
    CS_LOGINTODB,              // ����Ϣת�������ݿ�
    CS_WAITDBRET,              // �ȴ������ݿ��ȡPlayer��ɫ����
    CS_DBLOGINED,              // ����Ϣת�������ݿ�    

    //��Ϸ����
    CS_LOADINGMAP            , // �û����������ͼ�������ƶ������ܱ�����
    CS_IDLE                  , // ����
    CS_WALK                  , // ����
    CS_ATTACK                , // ����
    CS_INTONATE              , // ����
    CS_HURT                  , // ����
    CS_DIEING                , // ����״̬�����ڵȴ�����
    CS_DOACTION              , // ������״̬
    CS_HOLDSKILL             , // ά�ּ���״̬
    CS_READYTOUSESPEICALSKILL, // ׼��ʹ�����⼼��
    CS_USESPEICALSKILL       , // �������⼼��
    CS_ONSHIP                , // ��ת������
    CS_WAITRETURNTOCHARACTER , // �ȴ��ص�ѡ�˽���
};

const float monsterCastCorrect = 0.2f;

//////////////////////////////////////////////////////////////////////////
class BaseCharacter : public IBaseCharControl, 
                      public IBaseCharProperty,
                      public AiEnmity
{ // ������ɫ��
public:   
    struct SContinuousSkillData
    { //�������ж�
        //�Ƿ��Ǵ�����Ч����ɫ�ļ���        
        //Ч����ɫ���ܵĽ�����Ч����ɫ����
        //bool bEffectSkill;
        //unsigned short ustSkillEffectID;

        bool  bMoveInterrupt;        // �ƶ��Ƿ���
        
        DWORD dwTimeNextDoAttack;    // �´ν���ʱ��
        DWORD dwAttackInterval;      // �������
        DWORD dwTimeSkillHoldingEnd; // ά�ּ��ܽ�����ʱ��

        ItemDefine::SItemSkill* pSkill;

        //ά�ּ��ܴ�����EffectChar
        //��ά�ּ��ܽ���ǰ��EffectCharһֱ������
        CEffectChar* pEffectChar;

        bool bCharTarget;

        //��ǰ�Ĺ���Ŀ���LifeCode
        GameObjectId  ustTargetChar;
        unsigned short ustTargetLifeCode;

        D3DXVECTOR3    vTargetPos;
    };
    
    struct SEmission
    { // ��ɫ������ħ����
        BOOL  bDead;        // �Ƿ�����
        DWORD dwStartTime;
        DWORD dwLifeTime;
		GameObjectId  ustTargetID;
        unsigned short ustSkillID;
        unsigned short ustSkillLevel;

        SEmission()
        {
            bDead = TRUE;
        }
    };

    struct SRestoreTime
    {
        DWORD dwLastHPRestoreTime;     // �´�HP�ָ����ʱ��
        DWORD dwLastMPRestoreTime;     // �´�MP�ָ����ʱ��
        DWORD dwLastXPRestoreTime;     // �´�XP�ָ����ʱ��
        DWORD dwLastPassOnlineTime;    // �´μ������ʱ��
        DWORD dwLastDoubleExpTime;     // �´μ��˫������
    };

    struct SPlayerScore
    { // ��¼�����ߵ���Ϣ
        SPlayerScore()
        {
            stID    = -1;
            iDamage = 0;
			dwLastDamageTime = 0;
        }
        GameObjectId stID;
        int			 iDamage;
		DWORD dwLastDamageTime;
    };

    struct PlayerExtraDamage
    { // ��¼ʣ�๥����(��Ϊ������̫��,����ȡ�þ���)
        PlayerExtraDamage()
        {
            stID = -1;
            iDamage = 0;
        }
        GameObjectId stID;
        int			  iDamage;
    };

    struct SDaoxingEffect
    {
        SDaoxingEffect()
        {
            nStatusID = 0;
            nDurationTime = 0;
        }
        
        void Reset()
        {
            nStatusID = 0;
            nDurationTime = 0;
        }

        uint16 nStatusID;
        uint32 nDurationTime;
    };
	
//////////////////////////////////////////////////////////////////////////
// ����
public:
    BaseCharacter();
    virtual ~BaseCharacter() {};

    virtual void  OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame ) = 0;
    virtual void  OnDeath()                                                 = 0;     // ����

    virtual void  ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // �ڴ�����Ϣǰ����
    virtual bool  ProcessMsg( Msg* pMsg );                                           // ������Ϣ
    virtual void  ProcessLogicAfterProcessMsg( DWORD dwCostTime, bool& bContinue );  // �ڴ�����Ϣ�����
    virtual void  Run( DWORD dwCostTime );                                           // �����߼�֡Run

    virtual void  RefreshEnmity(){}
    virtual Msg*  FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize); // ��һ��ӡ��
    virtual void  EnterMySight( BaseCharacter* pWho ){}
    virtual void  ExitMySight( BaseCharacter* pWho ){}
    virtual void  SendVerifyPos(){}    
    virtual short GetProfession() { return EArmType_Monster; }
    virtual short IsSkillCanUse(int skill_no, int skill_level);    // �ж��Ƿ���ô˼���
    virtual void  RefreshCharData( DWORD dwCostTime );             // ˢ����������[����Ƶ��1��һ��]
    virtual bool  IsCanSwitchStage() { return m_bCanSwitchStage; } // ����Ƿ�����л�����
    virtual bool  CheckWalkPreconditionState();                    // �жϿɷ��ƶ�
    virtual bool  CheckUseSkillPreconditionState();                // �ж�NPC�Ƿ���һ������ʹ��һ�����ܵ�״̬

    virtual DWORD SkillDischarge( SAttackTarget *pTarget, unsigned short ustSkillID, unsigned short ustSkillLevel, BaseCharacter *pMaster, int nTargetCount = 0 );
    virtual void  OnBeAttacked( BaseCharacter* pAttacker, const ItemDefine::SItemSkill* pSkillConfig );
    virtual void  OnHaveStatusDisplacement();
    virtual void  OnBeBackAttack();
    virtual void  OnBuffStatusChanged( bool bSendMessage );

    virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue){ return GLR_Success; }// Ӧ��buffer

    virtual bool  OnScriptSkill( ItemDefine::SItemSkill* pItemSkill ){ return true; }
    virtual short ApplySkillCost( ItemDefine::SItemSkill *pSkill ); // Ӧ�ü�������
    virtual void  OnEnterFightState(){};                             // ��ս��״̬
    virtual void  OnOutFightState(){};                               // ��ս��״̬
    virtual void  OnIncreaseExp( int exp ){}                         // ��Ӿ���
    
    virtual CScriptVM* GetVM(){ return NULL; } // ���ö�Ӧ�ű�

    virtual void TellClient( const char* string, ... ){} // ���ͻ��˷���һ�仰
    virtual void TellClient( unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 ){}
    virtual void ShowInfo( bool bTile, DWORD type, const char* string, ... ){}
    virtual void ShowInfo( bool bTile, DWORD type, unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 ){}

    virtual void Log( const char* szFormat, ... ){}

    virtual DWORD GetTeamID() { return 0; }
    virtual void  SetTeamID(DWORD dwSessionId) {}
    virtual bool  HaveTeam() { return false; }
    virtual bool  IsTeamMember( BaseCharacter* pChar ) { return false; }

    virtual DWORD GetGuildID() const { return 0; }
    virtual bool  HaveGuild() const { return false; } 
    virtual bool  IsGuildMember( BaseCharacter* pChar ) { return false; }

    virtual void PunishWhenDeath( BaseCharacter* pAttacker ) {};

    //��Ʒ�ĺͼ��ܵ�
    //pChangeECS ÿ���˶��ܿ����ĸı�
    //�磺�����ٶȣ��ƶ��ٱ仯�ȵ�
    //bApplyEquip�Ƿ���װ���ĸ�������
    virtual void ApplySpecialAttr( int iWhichAttr,USpecialAttrValue *pValue , bool bAdd,MsgCharAttrChanged *pChangeECS = 0,bool bApplyEquip = false );

    virtual bool TryPassivenessTriggerAttack() { return true; } // ���Ա�����������

    virtual void OnEnterStage(){}
    virtual void OnLeaveStage(){}

    virtual unsigned int GetEnmityRate()  { return 100; }

    //TODO: ��Ҫ�Ƴ��ķ���
    //virtual unsigned int AddAttackCharacter( GameObjectId charId ){ return 0; }
    //virtual unsigned int DecAttackCharacter( GameObjectId charId ){ return 0; }
    //virtual void         ClearTryToAttackCharId(){}
    //virtual void         ClearTryToAttackCharEnmity(){}
    //virtual unsigned int GetViewEnmity()  { return 10;  }
    //virtual bool         IsPassiveAttack(){ return true; }  // �Ƿ��Ǳ�������
    //virtual int          GetViewSight()   { return 1;  }    // �����Ұ
    //virtual bool         IsInBaseEnmityRange(){ return false; }
    //virtual GameObjectId       GetTryToAttackCharId()  { return InvalidGameObjectId; }
    //virtual void         SetTryToAttackCharId( GameObjectId nID )   { }
    //virtual void         SetAttackCharEnmity( uint32 nEnmity) { }
    //virtual uint32       GetTryAttackCharEnmity()             { return 0; }
    //virtual uint32       GetGuildID()                         { return 0; }


    //////////////////////////////////////////////////////////////////////////
    // ��ɫ�����ж�
    virtual bool IsNpc() { return false; }
    virtual bool IsItem() { return false; }
    virtual bool IsPlayer() { return false; }
    virtual bool IsMonster() { return false; }
    virtual bool IsFightNpc() { return false; }
	virtual bool IsEffectChar() { return false; }
    virtual bool IsPet() { return false; }
    virtual bool IsResourceMonster();

    // ��ù�������
    virtual uint8 GetMonsterType() const { return eMT_MaxCount; }

    virtual void SetMasterID( GameObjectId nValue ) {}
    virtual GameObjectId GetMasterID() { return InvalidGameObjectId; }
    bool HaveMaster() { return GetMasterID() != InvalidGameObjectId; }
    virtual GamePlayer* GetMasterPlayer() { return NULL; }

    // ��ù���ID
    virtual int GetMonsterID() { return 0; }

    // ��ù���ר������
    virtual int GetSpecialType() const { return MonsterDefine::SpecialNone; }
    virtual uint32 GetSpecialValue() const { return 0; }
    virtual bool CheckSpecialTarget( int nSpecialType, GamePlayer* pTarget ) { return false; }
    
    void CriticalError(char* szFun, char* szFile, int nLine, unsigned char exitType = ET_ExitGame); // ���ش��󣬽�ɫ���������� ���봦��MSG_EXIT��Ϣ
    
    void ExitWorld(char* szFun, char* szFile, int nLine,unsigned char exitType = ET_ExitGame);     // �����˳�����
    void ExitWorld();
    void ExitWorldByPushMsg();

    unsigned short GetPlayerEctypeMapLevel( uint32 nMapID, float fX, float fY, bool bConsultTeam = true );
    
    void   CalcEquipHp( BaseCharacter* pTarget );    // ����װ���;ö�
    
    // ������
    virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );
    
    void  SetFightCamp( uint8 uchValue, bool bSendMessge = false );
	void  SetFightGame( uint8 uchValue, bool bSendMessge = false );
	uint8 GetFightCamp() const { return m_uchFightCamp; }
    bool  HaveFightCamp(){ return m_uchFightCamp != 0; }

    void SetCanSwitchStage( bool bCan = true ) { m_bCanSwitchStage = bCan; }    // �����Ƿ�����л�������Ĭ��Ϊ���л���
    bool CheckPos( DWORD *pdwMapId, int *pnX, int *pnY, bool bCorrect );        // ��鲢�����������

    // iGate==-1��ʾ������Gate����
    // ���򣬾�����Gate���룬��������
    void SendSyncCharPosToGate( int iGate = -1 );
    void SendNPCExit();

    float GetLevelDistanceExpModulus(short stSrcLevel,short stTargetLevel);    

	
    
    void  SetDirectiron (float fDir);
    void  CaluStepCost  (BYTE byDir);				//�ж��ߵ�ǰһ����Ҫ��ʱ��..�����ƶ���Ҫ��ʱ��
    bool  MoveToNextStep(BYTE byDir);
    bool  IsNextStepMoveable( int iDir );

    bool  UseRestoreItem( ItemDefine::SItemRestore *pRestore);
    
    void  SendSkillStatusTo( BaseCharacter* pTarget );
    //void  UpdateTeamScore( GamePlayer *pCharMember, int iScore );   //��������ɼ�  ������...

    // ���ܴ����
    bool CheckContinuousSkillCost();    // �����������Ƿ���Լ���
    void CancelSkill();                 // ȡ����ǰ����״̬
    virtual void DoAssaultMoving( float fDistance, int nInstantMovingType ){};  // ��漼��

    // ����Ŀ��
    void SetLockID( GameObjectId nValue ) { m_nLockID = nValue; }
    GameObjectId GetLockID() const { return m_nLockID; }
    void ClearLockID() { m_nLockID = InvalidGameObjectId; }
    bool HaveLockTarget() { return m_nLockID != InvalidGameObjectId; }
    BaseCharacter* GetLockChar();

    bool FindAttackTarget ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkill, OUT CFormula& formula );   
    bool FindAttackTarget ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkill, OUT std::vector< BaseCharacter* >& vecTargetList );

    // ����
    bool  IsCurrentTaskCanBeInterrupt( uint8 interruptType );
    void  IntonatingInterrupt( int nInterruptValue );                   //����ʱ����
    //float GetActualIntonateTime( unsigned short ustSkillIntonateTime )  //�õ�ʵ�ʵ�����ʱ��(�뼼���й�)
    //{ return ustSkillIntonateTime - ustSkillIntonateTime*GetCharFightAttr()->intonate.final/250;} 

    DWORD TryAttack( SAttackTarget* pTarget,ItemDefine::SItemSkill *pSkill,unsigned short ustSkillID, unsigned short  ustSkillLevel, int nTargetCount = 0 ); // ���Թ���    
    BOOL  IsPosInRange( float x, float y, float fDist );                 //�Ƿ��ڷ�Χ��    
    
    BOOL  IsInAttackRange( BaseCharacter *pDst, ItemDefine::SItemSkill* pSkill, float fRangeCorrect = monsterCastCorrect); // �Ƿ��ڹ�����Χ֮��
    bool  IsInValidCastRange( float x, float y, ItemDefine::SItemSkill* pSkill );

    DWORD MagicObjectAttack(SAttackTarget *pTarget, DWORD ustSkillID, DWORD ustSkillLevel); // �ͷų�һ�������ڵ�ͼ�ϵķ���Ч��

    BYTE  GetSubAction() { return m_bySubAction; } 
    void  ChangeSubAction( BYTE bySubAction, GameObjectId sTargetCharId );

    float GetWeaponAttackRange(){ return m_fWeaponAttackRange; }
    void  SetWeaponAttackRange( float fRange ){ m_fWeaponAttackRange = fRange; }
    
    virtual SCharBaseAttr* GetCharBaseAttr() { return NULL; }
    
    void ClearAllBaseAttrByPart  ( ECustomDataPart part );
    void ClearAllFightAttrByPart ( ECustomDataPart part );

    void UpdateCharAllAttibute();       // ���¼�����������

    BuffStatusManager* GetBuffManager() { return &_buffManager; }    
    bool IsCanDoAction();               // �ж��ܷ���ĳ����Ϊ����

    void           SetKiller( BaseCharacter* pBelongKiller ){ m_pBelongKiller = pBelongKiller; }
    BaseCharacter* GetKiller( void ){ return m_pBelongKiller; }

    bool TryChangeFightState( bool bAdd, EActionFlag flag, bool bSendMessage = true );         // �ı���Ϊ״̬
    bool HaveFighteFlag( EActionFlag flag ){ return _HAS_FLAG(m_dwFightFlag, flag); }   // �Ƿ���ĳ����Ϊ״̬   
    
    void AddDeBufferAttack(GameObjectId nTargetCharID); // ��������״̬      ����Ŀ���Լ� ���˵�ʱ��
    
    void SetIsBeCriticaled(bool bIsCsed) { m_bBeCSed = bIsCsed;}
    bool GetIsBeCriticaled()             { return m_bBeCSed;} // �Ƿ񱻱���

    // ����״̬
    uint8 GetStatus() { return _bodyStatus;}        // ȡ�õ�ǰ��״̬
    void  SetStatus( uint8 bodyStatus );            // ����״̬
    uint8 GetMoveStatus() { return _moveStatus; }   // ȡ���ƶ�״̬
    void  SetMoveStatus( uint8 moveStatus );

    int  GetNextStatus() { return _bodystatusOld;; }// �����һ��״̬
    void ApplyNextStatus();                         // Ӧ����һ��״̬

    //����״̬������ֵ������һ����������
    virtual void ApplyBuffStatusToCharAttr() { _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() ); }
    
    // BuffManager
    void SendBuffs      ( GamePlayer* pPlayer, bool bNeedKnowLast );    // ͬ��Buff list -1 true
    void SendBuffChanged( GamePlayer* pPlayer );                        // ���иı��Buff
        
    void UpdateBuff();             // ����Ŀ��״̬ ʱ����� �˺����
    void UpdateBuffDamage();       // ����״̬���˺�Update
    bool UpdateBuffOnAttack();     // �����ڹ�����ʱ���Ƿ���Ҫ���״̬
    bool UpdateBuffOnBeAttacked(){ return false; }

    // ��ʵ״̬
    void  SetCauseStatusID( short ustStatusID )      { m_ustCauseStatusID = ustStatusID;}
    void  SetCauseStatusLevel( short ustStatusLevel ){ m_stCauseStatusLevel = ustStatusLevel;}
    void  SetCauseStatusRate( short ustStatusRate )  { m_ustCauseStatusRate = ustStatusRate;}
    short GetCauseStatusID()    { return m_ustCauseStatusID; }
    short GetCauseStatusLevel() { return m_stCauseStatusLevel;}
    short GetCauseStatusRate()  { return m_ustCauseStatusRate;}
    
    // �жϿɷ񱻹��� �жϿɷ�PK �ж������ͷŶ����Ƿ����
    //bool IsCastTargetRight( const ItemDefine::SItemSkill*pSkill, BaseCharacter* pTagChar); // ������������Ƿ����            
    bool IsCastTargetRight( const ItemDefine::SItemSkill* pSkill, BaseCharacter* pTagChar);
    bool IsCastTargetRight( const ItemDefine::SItemSkill* pSkill, int x, int y );    
    //bool IsCanBeAttacked();
    bool IsCanBeAttackedObject(); // �Ƿ��ǿɱ������Ķ�������
    bool IsHaveHpObject();        // �Ƿ�����HP���� 

    bool CheckCanAttackTarget( BaseCharacter* pTarget );
    virtual bool CheckCanBeAttack();// �ж��Ƿ��ܱ�����

    BOOL IsInTargetBack ( BaseCharacter* pChar, float fMaxAngle );
    BOOL IsTargetInFront( BaseCharacter* pChar, float fMaxAngle );
    BOOL IsTargetInBack ( BaseCharacter* pChar, float fMaxAngle );
    
    virtual void IncreaseSingleSkillExp( int nSkillExp ){}
    virtual void IncreaseTotalSkillExp( int nSkillExp ){}

    void  SetIllusionChar( BOOL bIllusionChar ){ m_bIllusionChar = bIllusionChar;}
    BOOL  IsIllusionChar(){ return m_bIllusionChar; }

    uint32 GetLastMapID()              { return m_dwLastMapID; }
    void   SetLastMapID( uint32 dwID ) { m_dwLastMapID = dwID; }

    uint32 GetLastEctypeMapID()             { return m_dwLastEctypeMapID; }
    void   SetLastEctypeMapID( uint32 dwID) { m_dwLastEctypeMapID = dwID; }
    
    bool ChangeAttr( unsigned short ustWhichAttr, float fValue,   bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, DWORD dwValue,  bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, short stValue,  bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, int nValue,     bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, __int64 nValue, bool OnlyMe = false );

    virtual void Say( int nType, const char* szValue );
    virtual bool HaveAreaPlayer() { return false; }

    // ��ɱ���ˣ����һЩ���������ǰ��һЩ���񣬴���
    // �磺����������������Ӧ�����������״̬
    virtual void WasKilled( BaseCharacter* pKiller );// ��λ��ɱ���� ע������

    // ����
    void SetDead( bool bDead = true ) { m_bDeadFlag = bDead; } // ����������־
    bool IsDead() { return m_bDeadFlag; }                      // �Ƿ�Ϊ��Ѫ����״̬

    float GetBodySize(){ return m_fBodySize; }
    void  SetBodySize( float fBodySize ){ m_fBodySize = fBodySize; }
    
    void  SetMask( bool bMask ){ m_bMask = bMask; }
    BOOL  IsMask()             { return m_bMask; }

    bool  IsInMapArea(uint32 nMapID, float fX, float fY, float fDistance);

    void  SetCountry( int iCountry ){ m_iCountry = iCountry; }
    int   GetCountry( void ){ return m_iCountry; }

    void  SetForce( uint8 nValue ) { m_nForce = nValue; }
    uint8 GetForce() const { return m_nForce; }
    bool  HaveForce() const { return m_nForce != 0; }

    DWORD GetShowFlag(){ return m_dwShowFlag; }
    void  AddShowFlag( ENpcShowType flag ){ _SET_FLAG(m_dwShowFlag, flag); }

    void  SetLastMovingSpeed( float fMovingRate ){ m_fLastMovingSpeed = fMovingRate; }
    
    virtual long ProcessReliveModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget );        // �������ģ��

    void  ResetDaoxingEffect();
    void  SetDaoxingEffect( uint16 nStatusID, uint32 nDurationTime );

	uint32 GetLastMapID_BeforeTPHJ()              { return m_dwLastMapID_BeforeTPHJ; }
	void   SetLastMapID_BeforeTPHJ( uint32 dwID ) { m_dwLastMapID_BeforeTPHJ = dwID; }
	float GetLastX_BeforeTPHJ()              { return m_fLastX_BeforeTPHJ; }
	void   SetLastX_BeforeTPHJ( float fx ) { m_fLastX_BeforeTPHJ = fx; }
	float GetLastY_BeforeTPHJ()              { return m_fLastY_BeforeTPHJ; }
	void   SetLastY_BeforeTPHJ( float fy ) { m_fLastY_BeforeTPHJ = fy; }
	BYTE GetReliveBuff(){return m_byReliveBuff;}
	void SetReliveBuff(BYTE buff){m_byReliveBuff = buff;}

	////////////////////////////////////////////////////////////////////////////////////////
	// ������� by cloud
	virtual bool OnSetMonsterBelong(BaseCharacter * pTarget = NULL);	// ���û����������Ĺ���
	virtual void UpdateMonsterBeLong(BaseCharacter * pKiller = NULL){}	// ���¹���Ĺ��� ���ȥʵ��

	virtual void UpdatePlayerScore( GameObjectId stID, int iDamage ){}	// ��¼�����ߵ�ս����Ϣ �ڽ���ӿ��е���
	virtual void CheckClearAttackerScore(){}							// �����Ч���˺��÷�
	virtual void ClearAttackerScoreById( GameObjectId nId ){}			// ����ָ�������
	virtual void ClearAllAttackerScore(){}								// �������е����

	virtual GameObjectId GetBestAttacker(){return -1;}					// ˭���������Ĺ�����
	virtual GameObjectId GetFirstValidAttacker(){return -1;}			// �õ���һ����Ч�Ĺ�����

protected:
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime ){}
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // ���似�ܴ���
    void ProcessEmission();    

    // ��Ϊ״̬
    void  AddFightFlag( EActionFlag flag );    
    void  ClearFightFlag( EActionFlag flag, bool bSendMessage = true );

    // ����
    virtual uint32 ProcessNormalSkill ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster, int nConformedTargetCount = 0 );
    virtual uint32 ProcessCaptureSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessSuckFetchSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessBreakOutSkill( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessCallGraphicSkill( const ItemDefine::SItemSkill* pSkillConfig ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessXPSkill       ( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessPetActive     ( const ItemDefine::SItemSkill* pSkillConfig ){ return eFIGHT_NOFLAG; }

    virtual long ProcessAssaultModule      ( const ItemDefine::SItemSkill* pSkill ); // �����漼��ģ��
    virtual long ProcessAttackSpeed        ( const ItemDefine::SItemSkill* pSkill ); // �����ܹ����ٶ�

    virtual uint32 ProcessTeamRelive( const ItemDefine::SItemSkill* pSkill ) { return eFIGHT_NOFLAG; }
    virtual uint32 ProcessTeamFlyToHeader( const ItemDefine::SItemSkill* pSkill ) { return eFIGHT_NOFLAG; }

    // ״̬��Ϊ
    void StatusActionIdle();                        // ���пɿ�״̬
    void StatusActionAttack();
    void StatusActionReadyToUseSpecialSkill();
    void StatusActionUseSpecialSkill();
    void StatusActionIntonate();
    void BeginHoldSkill();
    void StatusActionHoldSkill();    
    void StatusActionDieing();                      // ����״̬ʱ�Ĵ���
    void StatusActionDoAction();
    
    DWORD GetEmissionFlyTime( GameObjectId shTargetID ); // �õ����м��ܴ�Ŀ���ʱ��
	bool IsGameBattleFigh(){return m_IsGameBattle;}
//////////////////////////////////////////////////////////////////////////
// ����
public:
    friend class SkillTaskManager;
    friend class BuffStatusManager;

    BuffStatusManager    _buffManager;                  // ����ս��״̬��
    SkillTaskManager     _SkillTaskManager;             // �������������
    CharacterTimeStatus  m_ExtendStatus;                // ��չ״̬��Ϣ(��Ҫ�õ�ս���е�Ӱ��״̬����)
    
    SContinuousSkillData m_ContinuousSkill;

protected:    
    BaseCharacter*  m_pBelongKiller;                    // �����λ�Ĺ�����˭ 
    GameObjectId    m_nLockID;                          // ������Ŀ��
	uint8			m_uchFightCamp;		                // ��Ӫ
    int             m_iCountry;                         // �����Ĺ���
    uint8           m_nForce;                           // ����������
    float           m_fBodySize;                        // ����
    float           m_fWeaponAttackRange;               // ������ͨ������Χ
    int             m_iAttackHand;
    int             m_nNormalAttSkillId0;               // ����
    int             m_nNormalAttSkillId1;               // ����
    bool            m_bBeCSed;                          // �Ƿ񱻱���
    SEmission       m_Emission[MAXEMISSIONNUM];
    unsigned char   m_ucHaveEmission;                   // �Ƿ��з��似��
    DWORD           m_dwShowFlag;                       // ��ʾ���,���Ƿ��ת��,�Ƿ�����Ӱ��
    DWORD           m_dwFightFlag;                      // ս��״̬
    SRestoreTime    m_restoretime;
    bool            m_bDeadFlag;                        // ������־
    uint8           _bodyStatus;                        // ��ǰ��������״̬ [�ϰ���״̬ ����״̬]
    uint8           _moveStatus;                        // �ƶ�״̬ [�°���״̬ С��״̬]
    int             _bodystatusOld;;                    // ��һ��״̬
    BYTE            m_bySubAction;                      // ���ڵĶ���
	 
    DWORD           m_dwLastMapID;                      // ��ҵ��ϴγ���ID
    DWORD           m_dwLastEctypeMapID;                // ��ҵı�����ǰ�ĵ�ͼID
    bool            m_bMask;                            // �Ƿ��赲
    DWORD           m_dwLastRefreshCharDataTime;        // ��¼�ϴε���RefreshCharData,��ʱ��
    DWORD           m_dwLastRefreshStatusTime;          // ˢ��ʱ��
    BOOL            m_bIllusionChar;                    // �Ƿ����ɫ
    int             m_nCompoundRateAddTemp;
    int             m_nIntensifyRateAddTemp;
    DWORD           m_dwStatusStartTime;                // �л�����״̬�Ŀ�ʼʱ��
    int             m_nNextStatus;                      // ��һ��״̬������
    bool            m_bCanSwitchStage;                  // �жϿɷ��л�,��ͼ
    short           m_ustCauseStatusID;                 // ���µ�״̬ID
    short           m_stCauseStatusLevel;               // ���µ�״̬Level
    short           m_ustCauseStatusRate;               // ���µ�״̬����    
    uint32          m_dwProcessLogicCostTime;           // �߼����û��ѵ�ʱ��
    float           m_fLastMovingSpeed;                 // �����ƶ��ٶ�

    SDaoxingEffect  m_DaoxingEffect;                    // ����Ӱ��
    GameTimerEx     m_xRefeshEnmityTimer;               // ���ˢ�¶�ʱ��
	DWORD           m_dwLastMapID_BeforeTPHJ;                      // ��ҵĽ���̫ƽ�þ�֮ǰ�ĵ�ͼID
	float           m_fLastX_BeforeTPHJ;                      // ��ҵĽ���̫ƽ�þ�֮ǰ�ĵ�ͼX
	float           m_fLastY_BeforeTPHJ;                      // ��ҵĽ���̫ƽ�þ�֮ǰ�ĵ�ͼY

	BYTE			m_byReliveBuff;								//��Ҹ�������������buff

	bool			m_IsGameBattle;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void BaseCharacter::SetStatus( uint8 bodyStatus )
{
    _bodystatusOld = bodyStatus;
    _bodyStatus   = bodyStatus;
}

inline void BaseCharacter::SetMoveStatus( uint8 moveStatus )
{   
    _moveStatus = moveStatus;
}

inline void BaseCharacter::ApplyNextStatus()
{
    _bodyStatus = _bodystatusOld;;
    m_dwStatusStartTime = HQ_TimeGetTime();
}

inline bool BaseCharacter::IsCanBeAttackedObject()
{
    if ( IsPlayer() || IsMonster() || IsFightNpc())
    { return true; }

	//lyhtexiaoguai++
	if(IsEffectChar())
		return true;

    return false;
}

inline bool BaseCharacter::IsHaveHpObject()
{
    if ( IsPlayer() || IsFightNpc() )
    { return true; }

    if ( IsMonster() && !IsResourceMonster() )
    { return true; }

    return false;
}

inline bool BaseCharacter::IsResourceMonster()
{
    switch ( GetMonsterType() )
    {
    case eMT_Treasure:
    case eMT_Herb:
    case eMT_Mount:
    case eMT_Insect:
    case eMT_Mine:
    case eMT_Wood:
        return true;
        break;
    default:
        break;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////
// ����
inline void GetOffsetByDir( int iDir,short &stXOff, short &stYOff )
{
    stXOff = 0;
    stYOff = 0;
    switch( iDir )
    {
    case DIR_0:
        stXOff = 1;
        break;
    case DIR_45:            
        stXOff = 1,stYOff = 1;
        break;
    case DIR_90:
        stYOff = 1;
        break;
    case DIR_135:
        stXOff = - 1,stYOff = 1;
        break;
    case DIR_180:            
        stXOff = - 1;
        break;
    case DIR_225:            
        stXOff = - 1,stYOff = - 1 ;
        break;
    case DIR_270:            
        stYOff = - 1;
        break;
    case DIR_315:
        stXOff = 1,stYOff = - 1;
        break;
    }
}

inline int GetDirByOffset( int dx, int dy )
{
    int nDir = DIR_0;
    if( dx > 0 && dy == 0 )
        nDir = DIR_0;
    else if( dx > 0 && dy < 0 )
        nDir = DIR_45;
    else if( dx == 0 && dy < 0 )
        nDir = DIR_90;
    else if( dx < 0 && dy < 0 )
        nDir = DIR_135;
    else if( dx < 0 && dy == 0 )
        nDir = DIR_180;
    else if( dx < 0 && dy > 0 )
        nDir = DIR_225;
    else if( dx == 0 && dy > 0 )
        nDir = DIR_270;
    else if( dx > 0 && dy > 0 )
        nDir = DIR_315;
    return nDir;
}

inline bool IsDistanceLess( int x1, int y1, int x2, int y2, int d )
{
    return ( abs( (x1)-(x2) ) < (d) && abs( (y1)-(y2) ) < (d) );
}

inline int CalcDistance( int x1, int y1, int x2, int y2 )
{
    return ( abs( (x1)-(x2) ) + abs( (y1)-(y2) ) );
}

#endif