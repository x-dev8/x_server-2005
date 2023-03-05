/********************************************************************
    Filename:    NpcFight.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_NPCFIGHT_H__
#define __COMMON_NPCFIGHT_H__

#pragma once

#include "NpcBase.h"
#include "AiBaseTask.h"

class NpcFight : public NpcBase, public DNpcFightChar,
                 INHERIT_POOL_PARAM( NpcFight, gNpcPoolBatchSize )
{
public:
    enum EConstDefine
    {
        ECD_SkillInfoMaxSize = 3,
    };

    struct SSkillInfo
    {
        uint16 m_iSkillId                ; // ����Id
        int8   m_stSkillLevel            ; // ���ܵȼ�
        uint8  m_stSkillRate             ; // ÿ�����ܵĸ���
        uint32 m_dwSkillStartColdDownTime; // ������Ŀ�ʼColdDownʱ��
        uint32 m_dwSkillColdDownTime     ; // �������ColdDownʱ��
    };

public:
    DECLARE_POOL_FUNC( NpcFight )

    NpcFight();
    virtual ~NpcFight(){}

    virtual uint32 Init();

    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ return &_baseProperty.fightAttr; }
    virtual void            SetHPMax( uint32 hpMax );
    virtual uint32          GetHPMax();
    virtual void            SetMPMax( uint32 mpMax );
    virtual uint32          GetMPMax();
    virtual float           GetMoveSpeed()              { return GetCharFightAttr()->moveSpeed.final; }
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }

    //////////////////////////////////////////////////////////////////////////
    // NpcBase    
    virtual void         EnterMySight( BaseCharacter* pWho );   // ��ҽ���FightNpc��Ұ
    virtual void         ExitMySight ( BaseCharacter* pWho );   // ����뿪FightNpc��Ұ
    virtual void         ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // �ڴ�����Ϣǰ����
    virtual void         Run( DWORD dwCostTime );
    virtual bool         IsCanAttack( BaseCharacter* pTarget );
    virtual void         OnDeath();
    virtual void         CallDeadScript(); // ִ�������ű�
    virtual void         ClearTryToAttackCharId();
    virtual void         ClearTryToAttackCharEnmity();
    virtual unsigned int AddAttackCharacter( GameObjectId charId );
    virtual unsigned int DecAttackCharacter( GameObjectId charId );
    virtual unsigned int GetEnmityRate(){ return m_nEnmityRate;}
    virtual unsigned int GetViewEnmity()  { return _nViewEnmity; }
    virtual bool         IsPassiveAttack(){ return m_bPassive; } // �Ƿ��Ǳ�������
    virtual int          GetViewSight() { return m_iViewSight; } // ��õ�ǰ��Ұ
    virtual bool         IsInBaseEnmityRange();
    virtual GameObjectId       GetTryToAttackCharId()        { return _tryToAttackCharId;        }
    virtual void				SetTryToAttackCharId( GameObjectId nID )   { _tryToAttackCharId = nID;         }    
    virtual uint32       GetTryAttackCharEnmity()             { return _tryToAttackCharEnmity;    }
    virtual void         SetAttackCharEnmity( uint32 nEnmity) { _tryToAttackCharEnmity = nEnmity; }

    //////////////////////////////////////////////////////////////////////////
    // AI
    void           ChangeMoveSpeed( float speed );
    bool           IsAIStartUp(){ return _bAIRun; }
    void           StartUpAI()  { _bAIRun = true; } // ��������AI
    void           RestoreHPInstant( int nRestoreHP ); // ˲���Ѫ
    void           RestoreMPInstant( int nRestoreMP ); // ˲���ħ    
    void           Relive();

    void           SetIdleMoveViewSight( short sight ){ m_stIdleMoveViewSight = sight; } // ���ÿ����ƶ�ʱ����Ұ
    short          GetIdleMoveViewSight()             { return m_stIdleMoveViewSight;  } // ��ÿ����ƶ�ʱ����Ұ
    void           SetFightViewSight( short sight )   { m_stFightViewSight = sight;    }
    short          GetFightViewSight()                { return m_stFightViewSight;     }
    void           SetViewSight( int sight )          { m_iViewSight = sight;          } // ���õ�ǰ��Ұ

    bool           HaveTryToAttackCharId()              { return _tryToAttackCharId != InvalidGameObjectId;}

    void           LockTarget( GameObjectId nMaxEnmityCharId );  // ����Ŀ��
    void           LostAttackTarget();  // ��ʧ����Ŀ��

    void           SetCanAttackCharId( GameObjectId charId ) { canAttackCharId = charId;                       } // ���ù���Ŀ��
    void           ClearCanAttackCharId()              { canAttackCharId = InvalidGameObjectId;         }
    uint16         GetCanAttackCharId()                { return canAttackCharId;                         } // ��ȡ����Ŀ��
    bool           HaveCanAttackCharId()               { return canAttackCharId != InvalidGameObjectId; } // �Ƿ��й���Ŀ��
    BaseCharacter* GetCanAttackChar(); // ��ù���Ŀ��  

    bool           IsInRange(); // �����׷����Χ

    bool           IsAICanAttack( BaseCharacter* pChar ); // Ŀ���Ƿ�ɹ���

    void           SetPassiveAttack( bool bPassive ) { m_bPassive = bPassive; } // ����Ϊ��������

    void           SendVerifyPos( float x, float y );
    void           SendClosingToTarget( GameObjectId nTargetID, D3DXVECTOR3 vNextPos );

    int            GetCurSkill()             { return m_iCurSkillId;     } // ��õ�ǰ����
    short          GetCurSkillLevel()        { return m_stCurSkillLevel; } // ��õ�ǰ���ܵĵȼ�
    int            GetCurSkillIndex();              // ��ȡ��ǰʹ�ü��ܵ�����    

    void           SetCurSkillIndex( int i );       // ���õ�ǰʹ�ü�����
    void           SetCurSkillLevel( uint8 index ); // ���õ�ǰʹ�õļ��ܵȼ�

    bool           IsHaveMoveAbility(); // �Ƿ����ƶ�������
    bool           IsBeginPosMove(); // �Ƿ���Ŀ���

    void           SetDeadScript( const char* szScriptName ){ m_strDeadScriptName = szScriptName; } // ���������ű���
    const char*    GetDeadScript(){ return m_strDeadScriptName.c_str(); }              // ��������ű���

    void           SetMoveRange     ( int maxRange )                   { nMaxRange = maxRange;                  }
    void           SetChangePassive ( uint8 nChangePassive )           { changePassiveConfig = nChangePassive;  }
    void           SetEndPassiveTime( uint32 nEndPassiveTime )         { endPassiveTimeConfig = nEndPassiveTime;}
    void           SetBornPoint( SFPos2 ptBorn )                       { m_ptBornPoint = ptBorn;                }
    void           SetBaseEnmityRange( int nBaseEnmityRange )          { m_nBaseEnmityRange = nBaseEnmityRange; }
    void           SetAttackRange( uint16 attackMin, uint16 attackMax ){ normalAttackMin = attackMin; normalAttackMax = attackMax; }
    void           SetNormalMoveSpeed( float fNormalMoveSpeed )        { m_fNormalMoveSpeed = fNormalMoveSpeed; }
    void           SetIdleMoveSpeed  ( float fIdleMoveSpeed   )        { m_fIdleMoveSpeed = fIdleMoveSpeed; }    
    void           SetSkillRateTotal();              // ���������Ҫ�õ��ܼ��ܸ���
    void           SetEnmityRate( unsigned int nEnmity) { m_nEnmityRate = nEnmity;}
    void           SetViewEnmity( unsigned int nEnmity) { _nViewEnmity = nEnmity; }
    void           SetSkillColdDown();

    // ·���߼�
    void           ClearOutOfRouteRecord();
    SMovePos*      GetBeginPos();
    SMovePos*      GetMovePos( uint8 step = 1);

protected:
    void           ProcessAIThink()                 ; // ˼��
    void           ProcessAISelectTask()            ; // ѡ��AITask
    void           ProcessAIMove( DWORD dwCostTime ); // ����AI�ƶ�    
    void           ProcessAIDoTask()                ; // ����AItask
         
    void           ThinkAttack()   ; // ���Բ���������Ϊ
    void           ThinkIdle()     ; // ���Բ���Idle��̬��Ϊ
    void           ThinkRouteMove(); // ·���ƶ�

    void           MoveAttackMoving( uint32 lapseTime ); // �й���Ŀ����ƶ�
    void           MovePosMoving   ( uint32 lapseTime ); // һ��ĵ�Ŀ����ƶ�

    bool           HaveTask(){ return !m_vecNormalTask.empty(); } // ��ǰ�Ƿ�������
    void           AddTask( AiBaseTask* pTask );                  // ��������
    void           ClearTask();                                   // �������

    // ����Ŀ��
    void           AITryAttack();   // ������ͨ����
    void           AITryUseSkill(); // �ü��ܹ���
    void           AIAttack( int iTarget, int iSkill, int iLevel ); // ��������ָ��

private:
    AITaskContainer m_vecNormalTask;

    bool          _bAIRun                 ; // AI�Ƿ���
    bool          _disableControlThinkTime; // ��Ҫ����˼��ʱ��
    uint32        m_dwLastThinkingTime    ; // ��һ��Npc˼��ʱ��
    int           m_nAiValueWave          ; // �����˼������
    uint32        m_dwFightViewEndTime    ; // FightView����ʱ��
    int           m_iViewSight            ; // ��Ұ(�ɹ�����Χ)
    short         m_stIdleMoveViewSight   ; // �����ƶ��е���Ұ
    short         m_stFightViewSight      ; // ս��ʱ����Ұ
    GameObjectId _tryToAttackCharId      ; // ����ȥ����Ŀ���Id
    uint32        _tryToAttackCharEnmity  ; // ����ȥ����Ŀ���Id��Ӧ�ĳ��
    uint32        m_AttackCharacterCnt    ; // ��ǰ������г�޵Ľ�ɫ����
    int           nMaxRange               ; // ���Χ
    float         lastIdleX               ; // ��һ��δ������ʱλ��X
    float         lastIdleY               ; // ��һ��δ������ʱλ��Y
    bool          m_bIsFighting           ; // ��ս��״̬
    uint8         changePassiveConfig     ; // ս��ʱ�Ƿ��Ϊ�����ֱ�����
    bool          bPassiveConfig           ; // �Ƿ񱻶�������
    bool          m_bPassive              ; // ��ǰ���Ƿ񱻶���״̬
    GameObjectId canAttackCharId         ; // ����Ŀ��
    bool          m_bClosingToTarget      ; // ����Ŀ��
    bool          _isNeedMove             ; // �Ƿ���Ҫ�ƶ�
    bool          m_bMoving               ; // �Ƿ����ƶ�
    short         m_stSkillRateTotal      ; // �ܸ���
    SSkillInfo    skillInfo[ECD_SkillInfoMaxSize]; // ӵ�еļ�����Ϣ
    D3DXVECTOR3   m_vLastSendTargetPos    ; // ���һ�η��͵��ƶ�Ŀ���
    uint16        m_iCurSkillId           ; // ��ǰ����
    short         m_stCurSkillLevel       ; // ��ǰ���ܵȼ�
    uint8         m_nCurSkillIndex        ; // ��ǰ���ܵ�����
    CItemDetail::SItemSkill* m_pCurSkill  ; // ��ǰѡ��ʹ�õļ���
    short         m_stCurAttackRange       ; // ��¼��ǰ�Ĺ�������
    uint8         m_stCurAiTactic          ; // ��ǰ��AI����
    float         m_fNormalMoveSpeed       ; // ƽʱ���ƶ��ٶ�
    float         m_fIdleMoveSpeed         ; // �����ƶ��ٶ�
    int           endPassiveTimeConfig     ; // ս��������������ʱ��
    uint32        _endPassiveTimeRecord    ; // ս��������������ʱ���¼    
    D3DXVECTOR3   _moveTargetPos           ; // �ƶ���Ŀ��λ��
    uint32        m_dwSendMoveMessageTime  ; // ���һ�η��ƶ�����Ϣ��ʱ��
    uint32        m_noMoveSendVerifyPosTime; // ���һ���ڲ��ƶ�������·�����λ�õ�ʱ��
    std::string   m_strDeadScriptName      ; // �����ű�����
    int           m_nVMId                  ; // �����ű��ű���
    int           m_nBaseEnmityRange       ; // ������޳�����Χ
    SFPos2        m_ptBornPoint            ; // ������
    SFDir3        _bornDir                 ; // �����ĳ���
    uint16        normalAttackMin          ; // ��ͨ������Сϵ��
    uint16        normalAttackMax          ; // ��ͨ�������ϵ��
    uint32        m_nEnmityRate            ;            
    uint32        _nViewEnmity             ; // ��Ұ�����ĳ�޳�ֵ
    GameTimerEx   m_xReliveTimer           ; // �������ʱ��
    // route
    uint16       _routeId                 ; // routeId
    uint16       _routeStep               ; // ��ǰ����һ��
    SRoute       _route                   ; // ·����Ϣ
    bool         _bArriveTargetPos        ; // �Ƿ�ﵽĿ���
    bool         _bFinalArrive            ; // ���յ���Ŀ�ĵ�

    bool         _bOutOfRoute             ; // �Ƿ��뿪��ָ����ǰ��·����������ȥ��
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void NpcFight::ClearOutOfRouteRecord()
{
    lastIdleX = 0;
    lastIdleY = 0;
}

inline void NpcFight::SetSkillRateTotal()
{
    m_stSkillRateTotal = skillInfo[0].m_stSkillRate + skillInfo[1].m_stSkillRate + skillInfo[2].m_stSkillRate;
    skillInfo[1].m_stSkillRate = skillInfo[1].m_stSkillRate + skillInfo[0].m_stSkillRate;
    skillInfo[2].m_stSkillRate = skillInfo[2].m_stSkillRate  + skillInfo[1].m_stSkillRate;
}

#endif // __COMMON_NPCFIGHT_H__
