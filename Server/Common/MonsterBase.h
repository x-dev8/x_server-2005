/********************************************************************
    Filename:     MonsterBase.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_AICHARACTER_H__
#define __GAMESERVER_AICHARACTER_H__

#include "BaseCharacter.h"
#include "FuncPerformanceLog.h"
#include "LuaPlus/LuaPlus.h"
#include "Dxsdk/d3dx9math.h"
#include "AiTaskManager.h"
#include "NetControl.h"
#include "SwMap.h"
#include "CharacterFindParth.h"

#define ENMITY_RATE           0.2f // �ȼ���޲����
#define ENMITY_MIN_VIEWSIGHT  3    // ��С��Ұ

#define AI_ARRAY_SIZE         10
#define AI_BOOLARRAY_SIZE     10
#define AI_MONSTERMAXSKILLNUM 3
#define AI_MAXTIMER           10

#define ProjectCharDis           10    // 10 ��ʾ
#define ProtectCharStopDistance  20   // 20 ֹͣ
#define TellClientDisPerTime     5000 // 5s ��ʾʱ������͵Ľ�ɫ����

extern SProcessTime aiusetime[200];

enum EAISelectTaskType
{ // ��ǰAi�Ĵ������
    EAISelectTaskType_None           ,
    EAISelectTaskType_IdleMove       , // �����ƶ�
    EAISelectTaskType_TryAttackTarget, // ���Թ���Ŀ��
    EAISelectTaskType_TryUseSkill    , // ʹ�ü���
};

struct SAiInfo
{ // �˹����ܽ�ɫ�����ݽṹ
    enum EConstDefine
    {
        constDefaultTaskListSize = 10, // Ĭ�����񻺳��С
    };

    SAiInfo()
    {
        m_iProduceIndex         = -1;
        m_dwLastThinkingTime    = 0;
        m_sizeTaskList          = constDefaultTaskListSize;
        m_iViewSight            = 10;

        canAttackCharId         = InvalidGameObjectId;
        lastIdleX            = 0.0;
        lastIdleY            = 0.0;
        m_strDeadScriptName.clear();
        m_bPassive              = false;
        m_strItemDropTemplate   = "<void>";
        m_fItemDropMultipleRate = 0.0f;

        memset( &m_CanMoveZone , NULL, sizeof( m_CanMoveZone  ));
        memset( m_bMustUseSkill, 0,    sizeof( m_bMustUseSkill));
        memset( m_iSkillId     , 0,    sizeof( m_iSkillId     ));
        memset( m_stSkillLevel , 0,    sizeof( m_stSkillLevel ));

        m_stSkillRateTotal = 0;
    }

    int   GetCurrentSelectSkillIndex();
    int32 GetCurrentSelectSkillId();
    int32 GetCurrentSelectSkillLevel();

    int         m_iProduceIndex                                  ; // �������к�(ÿ��ˢ���Ǹ�������������ʱ����)
    SFPos2      m_ptBornPoint                                    ; // ������
    float       lastIdleX                                        ; // ��һ��δ������ʱλ��X
    float       lastIdleY                                        ; // ��һ��δ������ʱλ��Y
    uint32      m_dwLastThinkingTime                             ; // ��һ��˼��ʱ��
    uint8       m_sizeTaskList                                   ; // ������г���
    uint16      m_iSkillId[AI_MONSTERMAXSKILLNUM]                ; // ����Id
    int8        m_stSkillLevel[AI_MONSTERMAXSKILLNUM]            ; // ���ܵȼ�
    uint8       m_stSkillRate[AI_MONSTERMAXSKILLNUM]             ; // ÿ�����ܵĸ���
    short       m_stSkillRateTotal                               ; // �ܸ���
    uint32      m_dwSkillStartColdDownTime[AI_MONSTERMAXSKILLNUM]; // ������Ŀ�ʼColdDownʱ��
    uint32      m_dwSkillColdDownTime[AI_MONSTERMAXSKILLNUM]     ; // �������ColdDownʱ��    
    bool        m_bMustUseSkill[AI_MONSTERMAXSKILLNUM]           ; // run��ʱ���Ƿ����ʹ�ôμ���
    int         m_iViewSight                                     ; // ��Ұ(�ɹ�����Χ)
    GameObjectId      canAttackCharId                                  ; // ����Ŀ��
    RECT        m_CanMoveZone                                    ; // �����ƶ���Χ
    bool        m_bPassive                                       ; // ��ǰ���Ƿ񱻶���״̬
    std::string m_strDeadScriptName                              ; // �����ű�(����������ʱ����һ���ű�)
    std::string m_strItemDropTemplate                            ; // ��Ʒ����ģ��
    float       m_fItemDropMultipleRate                          ; // ��Ʒ���䱶��
};

// ProcessThinking->
// ProcessAiTimer->
// ProcessSelectTask->
// ProcessAIMove->
// ProcessAITask->
class MonsterBase : public BaseCharacter, 
                    public DMonsterAIChar
{ // �˹����ܽ�ɫ��
private:
    struct SAITimer
    {
        DWORD dwStartTime; // ��ʱ��������ʼʱ��
        DWORD dwDelay;     // ��ʱ���������
        WORD wCount;       // ��ʱ���������� 0xFFFFΪ���޴�
    };

public:
	//Ѱ·״̬
	enum FindParthState
	{
		FPS_None,		// ����Ѱ·
		FPS_Line,		// ֱ��Ѱ·
		FPS_AStar,		// A*Ѱ·
		FPS_Pos,		// Ѱ·����λ�ò���Ŀ��λ��,��������ΪĿ��λ�ò��ɴ�
	};

	// ��̬�赲״̬
	enum DynamicBlockState
	{
		DBS_Close,		// �رն�̬�赲
		DBS_Open,		// ������̬�赲
		DBS_TempClose,	// ��ʱ�رն�̬�赲
	};

    MonsterBase();
    virtual ~MonsterBase();
    
    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ return &_baseProperty.fightAttr; }
    virtual void            SetHPMax( uint32 hpMax );
    virtual uint32          GetHPMax();
    virtual void            SetMPMax( uint32 mpMax );
    virtual uint32          GetMPMax();
    virtual void            SetMP( int nMp );
    virtual int             GetMP();
    virtual float           GetMoveSpeed()              { return GetCharFightAttr()->moveSpeed.final; }
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }

    // ��������
    virtual void  SetRewardReputation( int32 value) { _rewardReputation = value; }
    virtual int32 GetRewardReputation() { return _rewardReputation; }

    //  ��������
    virtual void  SetRewardExpolit( int32 value) { _rewardExpolit = value; }
    virtual int32 GetRewardExpolit() { return _rewardExpolit; }

    // ���ѶȽ���
    virtual void   SetRewardFriendly( uint32 value ) { _rewardFriendly = value; }
    virtual uint32 GetRewardFriendly() { return _rewardFriendly; }

    // �����ĵ���
    void  SetRewardDaoxing( int32 daoxing ) { _rewardDaoxing = daoxing; }
    int32 GetRewardDaoxing() { return _rewardDaoxing ; }

    virtual void  SetResistBeMove( int16 value ){ _resistBeMove = value; }
    virtual int16 GetResistBeMove(){ return _resistBeMove;}

    virtual void  SetResistBeAtt( int16 value ){ _resistBeAtt = value; }
    virtual int16 GetResistBeAtt(){ return _resistBeAtt; }

    virtual void  SetResistBeMagic( int16 value ){ _resistBeMagic = value; }
    virtual int16 GetResistBeMagic(){ return _resistBeMagic;}

    virtual void  SetResistBeTools( int16 value ){ _resistBeTools = value; }
    virtual int16 GetResistBeTools(){ return _resistBeTools;}

    //virtual void Initialize( const CItemDetail::SMonster* pConfig );

    //////////////////////////////////////////////////////////////////////////

    virtual void  ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // �ڴ�����Ϣǰ����
    virtual bool  ProcessMsg( Msg* pMsg );                                           // ������Ϣִ��
    virtual void  Run( DWORD dwCostTime );                                           // ����ִ��,������

    virtual void  OnExit( Msg*pMsg, unsigned char exitType = ET_ExitGame );                                      // �˳�
    virtual Msg*  FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);                                     // ��һ��ӡ��
    virtual void  EnterMySight( BaseCharacter* pWho );                                                           // �����ҵ���Ұ
    virtual void  ExitMySight( BaseCharacter* pWho );                                                            // �뿪�ҵ���Ұ
    virtual void  OnExitMySightNoPlayer();

    virtual void  RefreshEnmity() = 0;                                                                           // ˢ�³��
    virtual void  OnDeath();                                                                                     // ����
    virtual void  OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig ){}         // ���˴���
    virtual void  BeattackedCallBack(GameObjectId nAttackerID, int nSkillID, int nSkillLevel, int nDamage);     // ��������LUA�ص�����֧�� ����LUA�ű������ߵ�ID��ʩ�ŵļ���ID����ɵ��˺�
    virtual void  CallDeadScript();                                                                              // ִ�������ű�
    virtual bool  MustOpenAI() { return false;}                                                                  // Ĭ��AI���Ǳ���򿪵�
    virtual short GetProfession() { return m_shProfession; }                                                     // �����ְҵ
    virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue); // Ӧ��buff
    virtual bool  IsCanAttack( BaseCharacter* pTarget );
    virtual unsigned int AddAttackCharacter( GameObjectId charId );
    virtual unsigned int DecAttackCharacter( GameObjectId charId );
    virtual unsigned int GetEnmityRate() { return m_nEnmityRate; }
    virtual unsigned int GetViewEnmity()  { return _nViewEnmity;  }
    virtual bool         IsPassiveAttack(){ return GetAiData()->m_bPassive; } // �Ƿ��Ǳ�������
    virtual int          GetViewSight()   { return GetAiData()->m_iViewSight;  } // �����Ұ
    virtual GameObjectId       GetTryToAttackCharId()               { return _tryToAttackCharId;        }
    virtual void         SetTryToAttackCharId( GameObjectId nID )   { _tryToAttackCharId = nID;         }
    virtual void         SetAttackCharEnmity( uint32 nEnmity) { _tryToAttackCharEnmity = nEnmity; }
    virtual uint32       GetTryAttackCharEnmity()             { return _tryToAttackCharEnmity;    }


    //////////////////////////////////////////////////////////////////////////
    size_t   GetAttackCharCount() { return attackCharIds.size(); }
    bool     AreaHavePlayer() { return m_n9AreaPlayerCnt > 0; }
    SAiInfo* GetAiData(){ return &_coreAiData; }

    bool  IsAIStartUp(){ return m_bAIStartUp; }
    void  StartUpAI()  { m_bAIStartUp = true; } // ��������AI

    void  SetThinkTime( uint32 iValue ){ m_nThinkingTime = iValue; }

    void  SetFightModulus( float fAttackPhysicsMod, float fDefendPhysicsMod, float fAttackMagicMod, float fDefendMagicMod ); // ����ս��ϵ��
    float GetAttackPhysicsMod() { return _fAttackPhysicsMod; }
    float GetDefendPhysicsMod() { return _fDefendPhysicsMod; }
    float GetAttackMagicMod()   { return _fAttackMagicMod;   }
    float GetDefendMagicMod()   { return _fDefendMagicMod;   }

    void  SetAttackFloatMin( short sAttackFloating  ) { m_nAttackFloatMin = sAttackFloating; }
    void  SetAttackFloatMax( short sAttackFloating  ) { m_nAttackFloatMax = sAttackFloating; }
    short GetAttackFloat();
    
    void  SetCityMonster(bool bRet){ m_bCityMonster = bRet ;}      // �����Ƿ���й���
    bool  IsCityMonster(){ return m_bCityMonster; }
    void  SetCityDefMonster(bool bRet){ m_bCityDefMonster = bRet;} // ���з��ع�ֻ�������ǵ�
    BOOL  IsCityDefMonster(){ return m_bCityDefMonster; }

    bool  IsPet()            { return _bPet;}
    void  SetIsPet(bool bRet){ _bPet = bRet;}

    void  SetPetType( uint8 petType ) { _petType = petType;}
    uint8 GetPetType(){ return _petType; }

    void  SetNormalMoveSpeed( float fNormalMoveSpeed ){ m_fNormalMoveSpeed = fNormalMoveSpeed; }
    void  SetIdleMoveSpeed(float fIdleMoveSpeed) {m_fIdleMoveSpeed = fIdleMoveSpeed;}
    
    void  SetProfession( short shProfession ){ m_shProfession = shProfession; } // ���ù����ְҵ
    
    void  SetMonsterType( short stType );            // ���ù�������
    short GetMonsterType(){ return m_stMonsterType;} // ��ù�������
    bool  IsNeedFightMonster();                      // �Ƿ��ǳ�ʱ��򶷵Ĺ� ������ɱ�͵� ֲ����Դ    

    void SetProduceIndex(int index) { _coreAiData.m_iProduceIndex = index; } // ���ò������к�
    int  GetProduceIndex() { return _coreAiData.m_iProduceIndex; }           // ��ò������к�
    
    void SetBornPoint( SFPos2 ptBorn ); // ���ó�����
    
    void SetSkill(int index,int skill_id);              // ���ü���
    void SetSkillLevel( int index, short skilllevel );  // ���ü��ܵȼ�
    void SetSkillRate( int index, short skillrate );    // ���ü���ʹ�ø���
    
    void  SetSkillRateTotal();              // ���������Ҫ�õ��ܼ��ܸ���

    int   GetCurSkill()      { return m_iCurSkillId;     } // ��õ�ǰ����
    short GetCurSkillLevel() { return m_stCurSkillLevel; } // ��õ�ǰ���ܵĵȼ�

    void  SetCurSkillIndex( int i );       // ���õ�ǰʹ�ü�����
    int   GetCurSkillIndex();              // ��ȡ��ǰʹ�ü��ܵ�����
    void  SetCurSkillLevel( uint8 index ); // ���õ�ǰʹ�õļ��ܵȼ�

    // ���/���ù���slk�е�ID
    int   GetMonsterId(){ return m_nMonsterId; }
    void  SetMonsterId( int n ){ m_nMonsterId = n; }
    
    void  SetViewSight( int sight ){ GetAiData()->m_iViewSight = sight; } // ������Ұ
    
    
    void  SetIdleMoveViewSight( short sight ){ m_stIdleMoveViewSight = sight; } // ���ÿ����ƶ�ʱ����Ұ
    short GetIdleMoveViewSight()             { return m_stIdleMoveViewSight;  } // ��ÿ����ƶ�ʱ����Ұ

    void  SetFightViewSight(short sight) { m_stFightViewSight = sight; }
    short GetFightViewSight()            { return m_stFightViewSight; }
    
    void SetCanMoveZone( RECT zone ); // ���ƶ���Χ
    
    void SetSkill2LowLimit(); // ���ü���2��HP,MP����
    void SetSkill3LowLimit(); // ���ü���3��HP,MP����

    // ���ü��ܵ�ColdDown
    void SetSkillColdDown();    
    bool IsSkill2CanUse();
    bool IsSkill3CanUse();

    // ��ȡ���ƶ���Χ
    RECT GetCanMoveZone();
    bool HaveTask();                            // ��ǰ�Ƿ�������
    int  GetAttackTargetPro();                  // ��ȡ����Ŀ���ְҵ��Ϣ ����-1���ʾ�����ڵ�ǰ����Ŀ��    
    bool IsSkillAttack( BaseCharacter* pChar ); // �Ƿ���õ�ǰ���ܹ���
    bool IsAICanAttack( BaseCharacter* pChar ); // Ŀ���Ƿ�ɹ���

    // ��������״̬
    void SetTypeStatus( int nValue ) { m_nTypeStatus = nValue; }
    int GetTypeStatus() { return m_nTypeStatus; }

    // ������Ʒ����ģ��
    void SetItemDropTemplate( const char *szDropTemplate );

    // �����Ʒ����ģ��
    const char *GetItemDropTemplate();

    // ������Ʒ���䱶��
    void SetItemDropMultiple( float fm );
    
    // �����Ʒ���䱶��
    float GetItemDropMultiple();

    float GetPercentHP();

    void SetCurSkillByIDAndLev(unsigned short skillid,unsigned short skilllevel);

    void SetMustUsingSkill(int index,bool ismust);

    // ����Lua�ű�
    void LoadLuaScript( const char* LuaFileName );

    // ����Ʒ
    void DropItem( int ItemID, float x, float y );

    // ������Ʒ
    void DropItemRand( int ItemID, float fRate );    
    
    void AIAttack( int iTarget, int iSkill, int iLevel ); // ��������ָ��
    
    void TryUseSkill( int nSkillID, int nSkillLevel );       // ʹ�ýű�����
    void TryUseSkillByID(int nID, int nSkillID, int nLevel); // ָ��IDʹ���ض�����

    // �ı��ƶ��ٶ�
    void        ChangeMoveSpeed( float speed );
    
    void        SetDeadScript( const char *szScriptName ); // ���������ű���
    const char* GetDeadScript();                           // ��������ű���

    float DropRnd();
    float Rnd();
    
    void AddTask( AiBaseTask * pTask ); // ��������
    void ClearTask();                   // �������

    bool IsInRange();    // �����׷����Χ
    bool IsInMoveZone(); // �Ƿ����ƶ�Zone��
    bool IsInBaseEnmityRange();

    void SetFightViewEndTime( DWORD dwTime ){ m_dwFightViewEndTime = dwTime;}    
    void RestoreHPInstant( int nRestoreHP ); // ˲���Ѫ
    void RestoreMPInstant( int nRestoreMP ); // ˲���ħ

    void LoseHPInstant( int nLoseHP ); // ˲��ȥѪ
    void LoseMPInstant( int nLoseMP ); // ˲��ȥħ
    
    //////////////////////////////////////////////////////////////////////////
    // ForLua
    LuaFunction<int> GetGlobalFun( LPSTR cFuncName ){ return m_LuaScript->GetGlobal(cFuncName); }
    uint16 LuaGetLevel(){ return GetLevel();  }
    int    LuaGetHP()    { return IBaseCharProperty::GetHP(); }   
    void   Say( const char* pBuf );                              // ˵һ�仰
    void   SayAdvance( const char* pBuf, int nCount, int nPos ); // ˵��ϵͳ��Ϣ�Ļ�
    int    GetRand( int n ); // �õ�һ��0��n�������
    int    GetTargetHP();    // ���Ŀ���HP
    int    GetTargetMP();    // ���Ŀ���MP
    int    GetTargetHPMax(); // ���Ŀ������HP
    int    GetTargetMPMax(); // ���Ŀ������MP
    int    GetTargetLevel(); // ���Ŀ��ĵȼ�

    //�����ĸ�����������������ɫ������ĳ�ޣ�
    //�ͻ���CEnmity�еĲ�ͬ������CEnmityֻ���������������ɫ�ĳ��
    int GetTargetEnmity();                     // ��ö�Ŀ�������ĳ��
    int SetTargetEnmity(unsigned int nEnmity); // ���õ�ǰĿ�������ĳ��

    // ��ȡ����Ŀ�������ĳ�� �������򷵻�-1
    int GetEnmityByID(GameObjectId nID);

    // ��������Ŀ�������ĳ�� ʧ�ܷ���-1
    int SetEnmityByID(GameObjectId nID, unsigned int nEnmity);

    int GetDamageEnmityByID(GameObjectId nID);

    // ������Ұ������Ŀ�������ĳ�����(��û����ɳ�޵�Ŀ����Ч)
    void RandEnmity(unsigned int nMin, unsigned int nMax);

    // ����ӾŹ����ڻ�ȡһ���г�޵�ID
    int GetRandTarget();

    // ��ȡ��ǰĿ��ľ���
    int GetTargetDistance();

    // ��Ϊ
    void Murder(); // ��ɱ
    void Exit();   // �˳�

    // ���������������(�޵���Ч��)
    void UpgradePhysicsAttDamMax( int nValue );

    // �����������(�޵���Ч��)
    void UpgradePhysicsDef( int nValue );
    
    void         SetEnmityRate(unsigned int nEnmity) { m_nEnmityRate = nEnmity; }
    void         SetEnmity( unsigned int nEnmity) { _nViewEnmity = nEnmity; }

    //����
    GameObjectId  FindPersonKillerToAttack(int nSightRate);
    GameObjectId  FindPersonNormalToAttack(int nSightRate);
    GameObjectId  FindPersonPoliceToAttack(int nSightRate);
    GameObjectId  FindPersonAttackerToAttack(int nSightRate);

    void          SetSummonMasterID( GameObjectId stID ){ _summonMasterId = stID;} // �����ٻ�����ID
    BOOL		  IsSummonMonster()  { return _summonMasterId >= 0; } // �Ƿ��ٻ�����
    GameObjectId  GetSummonMasterID(){ return _summonMasterId; }      // ��ȡ�ٻ�����ID

    void       SetProtectChar( GameObjectId ProtectCharID ); // ���ñ���������
    bool       HaveProtectChar(){ return _protectCharId != -1; }

    BOOL       IsAttackTargetIsProtectChar(); // �Ƿ񹥻���Ŀ���Ǳ���������

    void       SetBindProtectCharVarId( int varId ){ _protectCharVarId = varId; }
    int        GetBindProtectCharVarId() { return _protectCharVarId; }

    void       SetDisappearTime( DWORD dwTime );   // ������ʧʱ��
    void       AskToAttackTarget();                // ������﹥��Ŀ��
    void       AskToFollowMaster();                // ��������������

    void       SetSpecialTarget( DWORD dwValue );
    DWORD      GetSpecialTarget() const { return m_dwSpecialID; }
    bool       IsHaveSpecialTarget() const { return m_dwSpecialID != 0; }
    bool       IsSpecialTarget( DWORD dwValue ) const { return m_dwSpecialID == dwValue; } 

    bool       MasterOutOfTarget(BaseCharacter* Master,BaseCharacter *Target, float distance);
                
    bool       IsHaveMoveAbility(); // �Ƿ����ƶ�������
    bool       GetNeedFollowSummonMaster() { return _bNeedFollowSummonMaster; }

	//////////////////////////////////////////////////////////////////////////
	//Ѱ·
	typedef std::vector< swVec2f >	FindParth;
	typedef FindParth::iterator		ItrFindParth;

	void		InitFindParth();												// ��ʼ��Ѱ·��Ϣ
	void		CheckFindParthConfigChange();									// ���Ѱ·���ñ仯
	bool		FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange );	// Ѱ����һ��Ŀ��λ��,�ȴ��߳�Ѱ·ʱ����false
	void		AfterMoveToPos();												// �ƶ���
	void		CheckReachPos();												// ����Ƿ�Ѱ·����
	bool		IsFindParth()		{ return _charFindParth.IsFindParth(); }	// �Ƿ���Ѱ·
	CharacterFindParth& GetCharFindParth() { return _charFindParth; }

    //////////////////////////////////////////////////////////////////////////
    // �����Բ���
    void           SetPassiveAttack( bool bPassive ) { GetAiData()->m_bPassive = bPassive; } // ����Ϊ��������
              
    void           SetIdleMoveRate(int16 nValue)     { m_stIdleMoveRate = nValue;  }
              
    void           SetCashMoney(int nValue)          { m_nCashMoney = nValue;      }
    int            GetCashMoney()                    { return m_nCashMoney;        }
              
    void           SetRewardStatusID( uint16 nValue) { m_nRewardStatusID = nValue; }
    uint16         GetRewardStatusID()               { return m_nRewardStatusID;   }
              
    void           SetRewardMulType ( uint16 nValue) { m_nRewardMulType  = nValue; }
    uint16         GetRewardMulType()                { return m_nRewardMulType;    }
              
    void           SetRewardMulValue( uint16 nValue) { m_nRewardMulValue = nValue; }    
    uint16         GetRewardMulValue()               { return m_nRewardMulValue;   }

    //////////////////////////////////////////////////////////////////////////
    // ��Ŀ��Ĳ���
    bool           HaveAskToAttackTargetId()            { return m_AskToAttackTargetID >= 0;}
    void           ClearAskToAttackTargetId()           { m_AskToAttackTargetID = -1; }

    bool           HaveTryToAttackCharId()              { return _tryToAttackCharId != InvalidGameObjectId;}
    
    void           ClearTryToAttackCharId();
    void           ClearTryToAttackCharEnmity();

    void           LockTarget( GameObjectId nMaxEnmityCharId );  // ����Ŀ��
    void           LostAttackTarget();                  // ��ʧ����Ŀ��

    void           SetCanAttackCharId( GameObjectId charId ) { _coreAiData.canAttackCharId = charId;                       } // ���ù���Ŀ��
    void           ClearCanAttackCharId()              { _coreAiData.canAttackCharId = InvalidGameObjectId;         }
    GameObjectId         GetCanAttackCharId()                { return _coreAiData.canAttackCharId;                         } // ��ȡ����Ŀ��
    bool           HaveCanAttackCharId()               { return _coreAiData.canAttackCharId != InvalidGameObjectId; } // �Ƿ��й���Ŀ��
    BaseCharacter* GetCanAttackChar(); // ��ù���Ŀ��  

protected:
    // һ�ֵ�AI
    void ProcessAIThink()                 ; // ˼��
    void ProcessAITimer()                 ; // ʱ�䴥�����
    void ProcessAISelectTask()            ; // ѡ��AITask
    void ProcessAIMove( DWORD dwCostTime ); // ����AI�ƶ�    
    void ProcessAIDoTask()                ; // ����AItask

protected:
    virtual bool OnThink()                  = 0;       // ��˼��ʱ��
    virtual bool OnMove( uint32 lapseTime ) = 0;       // ���ƶ�ʱ��
    virtual bool OnSuccessLockTarget(){ return true; } // �ڳɹ�����Ŀ��ʱ��

    //////////////////////////////////////////////////////////////////////////
    // �ٻ�����
    void FollowTheSummonMaster( BaseCharacter* pSummoner ); // �����ٻ����ƶ�
    void FlyToTheSummonMaster();                            // ˲���ƶ����ٻ��������

    // ����Ŀ��    
    void AITryAttack();   // ������ͨ����
    void AITryUseSkill(); // �ü��ܹ���

    // ��ʱ��
    void AddTimer( DWORD dwTime ); // ��һ��ʱ���ʱ��
    bool GetTimer();               // ��ʱ���Ƿ񵽵�

    void SetTimer(unsigned int nIndex, DWORD dwDelay, WORD wCount);
    void DelTimer(unsigned int nIndex);
    
    void SetArray( int nIndex, int nValue );      // ���ýű���Ҫ�洢�ı���
    int  GetArray( int nIndex );                  // ��ȡ�洢�ı���
    
    void SetBoolArray( int nIndex, bool bValue ); // ���ýű��в���ֵ�Ĵ洢
    bool GetBoolArray( int nIndex );              // ��ȡ�ű��еĲ���ֵ
    
    bool SummonMonster         ( int nMonsterIndex, int nMonsterAmount, int nRadius, int nSummonType );
    bool SummonInfluenceMonster( int nMonsterIndex, int nMonsterAmount, int nRadius, int nSummonType, int nInfluence );

    void SendVerifyPos( float x, float y );
    void SendClosingToTarget( GameObjectId nTargetID, D3DXVECTOR3 vNextPos );

    // ������Ӫ������
    void ProcessCampMonsterDeath();
    virtual void MAlarmWhenBeAttack();

public:
    friend class GamePlayer;
    int   nSuperfluitySkillExp; // ����ļ��ܾ���
    int   nMaxRange           ; // ���Χ
    int   m_nBaseEnmityRange  ; // ������޳�����Χ 
    uint8 changePassiveConfig ; // ս��ʱ�Ƿ��Ϊ�����ֱ�����
    int   endPassiveTimeConfig; // ս��������������ʱ��
    bool  bPassiveConfig      ; // �Ƿ񱻶�������

protected:
    // �����Զ���
    AITaskContainer m_vecHighTask;
    AITaskContainer m_vecNormalTask;
    AITaskContainer m_vecLowTask;

    SAiInfo     _coreAiData                         ; // AI����
    int         m_nVMId                             ; // �����ű��ű���
    bool        m_bAIStartUp                        ; // AI�Ƿ���
    uint32      m_n9AreaPlayerCnt                   ; // 9�������������    
    DWORD       m_dwFightViewEndTime                ; // FightView����ʱ��
    uint32      m_nThinkingTime                     ; // �����˼��ʱ��
    int         m_nAiValueWave                      ; // �����˼������
    short       m_nAttackFloatMin                   ; // ������Сϵ��
    short       m_nAttackFloatMax                   ; // �������ϵ�� 
    DWORD       m_dwTimeStep                        ; // Timer��������ʱ��
    DWORD       m_dwStartTime                       ; // Timer�Ŀ�ʼʱ��
    bool        m_bTimerActive                      ; // Timer�Ƿ���
    bool        _bPet                               ; // �Ƿ�pet
    uint8       _petType                            ; // ��������
    GameObjectId      _tryToAttackCharId           ; // ����ȥ����Ŀ���Id
    uint32      _tryToAttackCharEnmity              ; // ����ȥ����Ŀ���Id��Ӧ�ĳ��

    typedef std::set<uint16>              AttackCharContainer;
    typedef AttackCharContainer::iterator ItrAttackCharContainer;
    AttackCharContainer attackCharIds               ; // ��ǰ������г�޵Ľ�ɫ�б�

    uint8       m_nTypeStatus;                      ; // ��������״̬( npc�Ի�״̬, ����ɹ���״̬��... )

    bool        m_bMoving                           ; // ���ƶ���
    uint32      m_nEnmityRate                       ;            
    uint32      _nViewEnmity                        ; // ���������Ұ�����ĳ�޳�ֵ
    bool        m_bIsFighting                       ; // ��ս��״̬
    short       m_shProfession                      ; // �����ְҵ
    bool        m_bLuaScriptLoaded                  ; // Lua�ű��Ƿ�������
    short       m_stMonsterType                     ; // ��������
    short       m_stIdleMoveViewSight               ; // �����ƶ��е���Ұ
    short       m_stFightViewSight                  ; // ս��ʱ����Ұ
    short       m_stIdleMoveRate                    ; // ���ƿ����ƶ���Ƶ��ֵ
    uint16      m_ustSkill2HPLowerLimit             ; // ����2��HP��С����
    uint16      m_ustSkill2MPLowerLimit             ; // ����2��MP��С����
    uint16      m_ustSkill3HPLowerLimit             ; // ����3��HP��С����
    uint16      m_ustSkill3MPLowerLimit             ; // ����3��MP��С����
    bool        m_bSkill2Restore                    ; // ����2�Ƿ�ָ��Լ���
    bool        m_bSkill3Restore                    ; // ����3�Ƿ�ָ��Լ���    
    bool        _disableControlThinkTime            ; // ��Ҫ����˼��ʱ�� 
    short       m_stCurAttackRange                  ; // ��¼��ǰ�Ĺ�������
    uint8       m_stCurAiTactic                     ; // ��ǰ��AI����
    bool        _isNeedMove                         ; // �Ƿ���Ҫ�ƶ�
    float       m_fNormalMoveSpeed                  ; // ƽʱ���ƶ��ٶ�
    float       m_fIdleMoveSpeed                    ; // �����ƶ��ٶ�
    uint16      m_iCurSkillId                       ; // ��ǰ����
    uint8       m_nCurSkillIndex                    ; // ��ǰ���ܵ�����
    short       m_stCurSkillLevel                   ; // ��ǰ���ܵȼ�
    int         m_nMonsterId                        ; // ����monster.slk�е�ID    
    D3DXVECTOR3 m_vLastSendTargetPos                ; // ���һ�η��͵��ƶ�Ŀ���
    uint32      m_dwSendMoveMessageTime             ; // ���һ�η��ƶ�����Ϣ��ʱ��
    uint32      m_noMoveSendVerifyPosTime           ; // ���һ���ڲ��ƶ�������·�����λ�õ�ʱ��
    uint16      m_ushDirUnChangedCount              ; // ���﷽��δ�ı�ļ�����
    bool        m_bClosingToTarget                  ; // ����Ŀ��
    bool        m_bCityMonster                      ; // ��ս�����FLAG��ֻ�ܱ������سǵĹ���
    bool        m_bCityDefMonster                   ; // ���з��ع�ֻ�������ǵ�
    D3DXVECTOR3 _moveTargetPos                      ; // �ƶ���Ŀ��λ��
    DWORD       m_dwSpecialID                       ; // ����ĳ�����
    GameObjectId  _summonMasterId                  ; // �ٻ�����ID
    GameObjectId  _protectCharId                   ; // �����ߵ�ID
    int         _protectCharVarId                   ; // �󶨵ı����˵Ļ�������
    GameObjectId  m_AskToAttackTargetID            ; // Ҫ�󹥻���Ŀ��ID
    float       _fAttackPhysicsMod                  ; // ������ϵ��
    float       _fDefendPhysicsMod                  ; // �������ϵ��
    float       _fAttackMagicMod                    ; // ��������ϵ��
    float       _fDefendMagicMod                    ; // ��������ϵ��
    int         m_nCashMoney                        ; // �����Ǯ
    uint16      m_nRewardStatusID                   ; // ����״̬
    uint16      m_nRewardMulType                    ; // ������������
    uint16      m_nRewardMulValue                   ; // ��������ֵ    
    bool        _bNeedFollowSummonMaster            ; // �Ƿ���Ҫ��������
    CItemDetail::SItemSkill* m_pCurSkill            ; // ��ǰѡ��ʹ�õļ���
    LuaStateOwner m_LuaScript                       ; // ����Lua������
    SAITimer      m_Timer[AI_MAXTIMER]              ;
    AiTaskManager _AiTaskManager                    ;
    int           m_nArray[AI_ARRAY_SIZE]           ;
    bool          m_bArray[AI_BOOLARRAY_SIZE]       ;
    uint32        _endPassiveTimeRecord             ; // ս��������������ʱ���¼
    GameTimerEx   m_xDisappearTimer                 ; // ��ʧ��ʱ��

	CharacterFindParth	_charFindParth;
};

inline void MonsterBase::SetFightModulus( float fAttackPhysicsMod, float fDefendPhysicsMod, float fAttackMagicMod, float fDefendMagicMod )
{ 
    _fAttackPhysicsMod = fAttackPhysicsMod; 
    _fDefendPhysicsMod = fDefendPhysicsMod;
    _fAttackMagicMod   = fAttackMagicMod;
    _fDefendMagicMod   = fDefendMagicMod; 
}

inline short MonsterBase::GetAttackFloat()  // �õ���������ֵ
{ 
    return 0;
}

inline void MonsterBase::SetMonsterType( short stType)
{
    if( stType < 0 )
    {
        m_stMonsterType = eMT_NormalMonster;
    }
    else
    {
        m_stMonsterType = stType;
    }
}

// ��Ҫ��ʱ��ս���Ĺ���
inline bool MonsterBase::IsNeedFightMonster()
{
    switch( m_stMonsterType )
    {
    case eMT_NormalMonster:
    case eMT_LeaderMonster:
    case eMT_BossMonster:
    case eMT_GodMonster:
    case eMT_Trap:
    case eMT_Pet:
    case eMT_IllusionMonster:
    case eMT_Protect:
        return true;
        break;
    default:
        break;
    }
    
    return false;
}

inline void MonsterBase::SetBornPoint( SFPos2 ptBorn )
{
	_coreAiData.m_ptBornPoint = ptBorn;
	_coreAiData.lastIdleX = ptBorn.x;
	_coreAiData.lastIdleY = ptBorn.y;
}

#endif // __GAMESERVER_AICHARACTER_H__

