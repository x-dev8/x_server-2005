#ifndef __AICHARACTER_H__
#define __AICHARACTER_H__

/************************************************************************
                            ����AI�Ľ�ɫ

                            Filename:     AiCharacter.h
                            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "BaseCharacter.h"
#include "GameTimer.h"
#include "Dxsdk/d3dx9math.h"
#include "LuaPlus/LuaPlus.h"
#include "CharacterFindParth.h"
#include "MonsterGroupManager.h"


class AiCharacter : public BaseCharacter, public AICharAttribute
{
public:
	typedef std::map< GameObjectId, SPlayerScore > MapIdScoreContainer;
	typedef MapIdScoreContainer::iterator          ItrMapIdScoreContainer;

    AiCharacter();

    virtual ~AiCharacter();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ return &_baseProperty.fightAttr; }
    virtual uint32          GetHPMax(){ return GetCharFightAttr()->hpMax.final; }
    virtual uint32          GetMPMax() { return GetCharFightAttr()->mpMax.final; }
    virtual int             GetMP() { return _nMp; }
    virtual void            SetHPMax( uint32 hpMax );
    virtual void            SetMPMax( uint32 mpMax );
    virtual void            SetMP( int nMp );
    virtual float           GetMoveSpeed() { return GetCharFightAttr()->moveSpeed.final; }
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // ִ��AI�߼�
    virtual void Run( uint32 nCostTime );

    // �ڴ�����Ϣǰ����
    virtual void ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); 

    // ������Ϣ
    virtual bool ProcessMsg( Msg* pMessage );

    // ������Ұ
    virtual void EnterMySight( BaseCharacter* pTarget );

    // �뿪��Ұ
    virtual void ExitMySight( BaseCharacter* pTarget );

    // ������
    virtual void OnBeAttacked( BaseCharacter* pAttacker,const ItemDefine::SItemSkill* pSkillConfig );

    // �Ƿ�һ��Ҫmiss����
    virtual bool IsMustMiss();

    // ����
    virtual void OnDeath();     

    // �����˳���Ϣ
    virtual void OnExit( Msg* pMessage, uint8 nExitType = ET_ExitGame );       

    // Ӧ��BUFF
    virtual long ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue );

    // �ж��ܷ񱻹���
    virtual bool CheckCanBeAttack();

    // ˼��ʱ��
    int GetThinkingTime() { return m_nThinkingTime; }
    void SetThinkingTime( int nValue ) { m_nThinkingTime = nValue; }

    // ���ó�����
    void SetBornPoint( float fX, float fY, float fZ );

    // ����Ai״̬
	void SetAiStatus( uint8 nValue ) { m_nAiStatus = nValue; }
    uint8 GetAiStatus() const { return m_nAiStatus; }

    // ����Ai����
    virtual void AddAiSkill( uint8 nIndex, AiSkill& xSkill );
    virtual AiSkill* GetAiSkillByIndex( uint8 nIndex );
    virtual AiSkill* GetAiSkillByID( uint16 nSkillID, uint8 nSkillLevel );

    // ���õ�ǰʹ�õļ���
    virtual void SetUseSkill( uint16 nSkillID, uint16 nSkillLevel );

    // ��ù���ʹ�õļ���
    virtual AiSkill* GetCanUseSkill( uint32 nCurrentTime );

    // ������������Ŀ��
   virtual void ProcessLockTarget( int nTargetID );

    // ��ӹ���Task
    void AddAiTask( GameObjectId nAttackID, uint16 nSkillID, uint8 nSkillLevel, uint8 nTaskPriority = AiDefine::NormalAiTaskPriority );

    // 9�������������
    void AddAreaPlayerCount( int nValue = 1 ) { m_n9AreaPlayerCount += nValue; }
    void SubAreaPlayerCount( int nValue = 1 );
    bool HaveAreaPlayer() { return m_n9AreaPlayerCount > 0; }

    // ��Ұ
    void SetViewSight( int nValue ) { m_nViewSight = nValue; }
    int GetViewSight() const { return m_nViewSight; }

    // ���ƶ���Χ
    void SetCanMoveZone( const RECT& zone ); 

    // �ı��ƶ��ٶ�
    void ChangeMoveSpeed( float fValue );

    // ��ʼ��Ұ��ʱ��
    void StartIdleViewTimer( uint32 nCurrentTime );

    // �����ƶ��ٶ�
    virtual float GetIdleMoveSpeed() { return 0.0f; }

    // ׷�����ܻ��ƶ��ٶ�
    virtual float GetAttackMoveSpeed() { return 0.0f; }

    // ������ɱ
    virtual void CharacterMurder();

    // �����Ұ���
    virtual int GetViewEnmity() { return 100; }

    // �ҵ�����
    virtual GamePlayer* GetMasterPlayer();

    // �ƶ�����
    void SetMoveStep( float fValue ) { m_fMoveStep = fValue; }
    float GetMoveStep() { return m_fMoveStep; }

    // ��ʼ�Ի�
    void StartTalk();

    // �����Ի�
    void EndTalk();

    // ���ڳ���ƶ�
    virtual void DoAssaultMoving( float fDistance, int nInstantMovingType ); 

    // �����˺����
    virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

    //////////////////////////////////////////////////////////////////////////
    //Ѱ·
    typedef std::vector< swVec2f >	FindParth;
    typedef FindParth::iterator		ItrFindParth;

    void		InitFindParth( GameObjectId nID, bool blIsFindParth, bool blIsDynamicBlock );	// ��ʼ��Ѱ·��Ϣ
	void		OnFindParthConfigChanged( bool blNewIsFindParth, bool blNewIsDynamicBlock );	// ���ⲿѰ·���ñ仯ʱ����
    bool		FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange );	// Ѱ����һ��Ŀ��λ��,�ȴ��߳�Ѱ·ʱ����false
    void		AfterMoveToPos();												// �ƶ���
    bool		CheckReachPos();												// ����Ƿ�Ѱ·����
    CharacterFindParth& GetCharFindParth() { return _charFindParth; }

	// Ѳ����
	friend class MonsterGroup;
	// ��ù������߼�
	MonsterGroupLogic& GetMonsterGroupLogic() { return m_xMonsterGroupLogic; }

	// �³��Ŀ��ӿ�
	virtual void OnNewEnmityTarget( GameObjectId nID ) { m_xMonsterGroupLogic.OnNewEnmityTarget( nID ); }

	/////////////////////////////////////////////////////////////////////////
	//������� by cloud
	virtual void UpdatePlayerScore( GameObjectId stID, int iDamage );	// ��¼�����ߵ�ս����Ϣ*

	virtual void CheckClearAttackerScore();								// ��������Ч���˺��÷�
	virtual void ClearAttackerScoreById( GameObjectId nId );			// ����ָ�������
	virtual void ClearAllAttackerScore();								// �������е����

	virtual GameObjectId GetBestAttacker();								// ˭���������Ĺ�����
	virtual GameObjectId GetFirstValidAttacker();						// �õ���һ����Ч�Ĺ�����
protected:

    // ����Ŀ�궪ʧ
    uint8 ProcessLostLockTarget( BaseCharacter* pTarget );

    // �ж��Ƿ��ܹ���
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // ����������Ұ���
    void ProcessViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // �ж��Ƿ�Ҫˢ����Ұ���
    virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // ������Ұ�ӳ���б�
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget ){};

    // �������ս��״̬
    virtual void ProcessEndAttackStatus();

    // ���Ai����
    virtual void ClearAiVariable();

    // �������˼��
    virtual void ProcessAiThinking( uint32 nCurrentTime );

    // ����˼���߼�
    virtual uint8 AiThinking( uint32 nCurrentTime );

    // �������˥����Ľ��
    virtual void ProcessClearEnmityResult( GameObjectId nTargetID );

    // ִ�й���AiTask
    virtual void ProcessAiTask( AiTask* pAiTask );

    // ˢ�¹�����
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // ������︴��
    virtual void ProcessAiRelive();

    // ��ù���˼��ʱ��
    virtual int GetThinkingSpaceTime();

    // �����������������ű�
    void ProcessDeathCallScript();

    // �������
    void ReleaseAiTask();

    // �������AI�߼�
    virtual void ProcessAiLogic( uint32 nCostTime );

    // �Ƿ���Դ���AiTask
    bool CheckCanAiTask();

    // �������AiTask
    void ProcessAiTask();

    // ������ʧ
    bool ProcessDisappear();

    // ����˼��ʱ��
    void SetThinkingSpaceTime( uint32 nThinkingTime );

    // �Ƿ����ƶ�����
    bool HaveMoveAbility();

    // ��������ƶ�
    virtual void ProcessAiMoving( uint32 nCostTime );

    // ���ÿ�ʼ������������
    void SetLastIdlePoint( float fX, float fY, float fZ );

    // �Ƿ���Ҫ�ƶ�����ʼ������������
    bool NeedMoveToLastIdlePoint();

    // ����ϴα�����������
    void ClearLastIdlePoint();

    // �����ƶ�����Ŀ��λ��
    void SetMoveTargetPoint( float fX, float fY, float fZ );

    void SetMovePoint( float fX, float fY, float fZ );

    // �Ƿ���Ҫ�ƶ�
    bool NeedMovingToTargetPoint();

    // ����ƶ�Ŀ���
    void ClearMoveTargetPoint();

    // �ж��Ƿ�����ͬ��ͬ��λ�õ�
    bool CheckSameVerifyPoint( float fX, float fY, float fZ );

    // �ж��Ƿ��ڿ��ƶ���Χ��
    bool CheckInCanMoveZone();

    // �ж��Ƿ��ڻ�����޷�Χ
    bool CheckInBaseEnmityRange();

    // �ж��Ƿ���Ҫ�ƶ�����һ��·��
    bool NeedMoveToNextRoute() { return m_nRouteStep != -1; }

    // �����ƶ���������Ϣ
    void SendMoveToTargetPointMessage( GamePlayer* pTarget = NULL);

    // ���Ϳ���Ŀ����Ϣ
    void SendClosingToTargetMessage();

    // ����ͬ������λ����Ϣ
    void SendVerifyPointMessage();

    // �����������ս������Ұ�仯
    void ProcessIdleViewSightChange();

    // ������Ѫ��ħ��ʱ��
    void StartRestoreTimer( uint32 nCurrentTime );

    // ��������Ѫ, ��ħ
    void ProcessRestore( uint32 nCurrentTime );

    // ������ʱ�ƶ��ٶ�
    void ProcessAttackMoveSpeed( float fModulus = 1.0f );

    // �������ʱ���ƶ��ٶ�
    void ProcessIdleMoveSpeed();

    // �����ƶ���������
    void ProcessMoveToBornPoint();

    // �����ƶ���ĳ��
    void ProcessMoveToPoint();

    bool CheckInMaxAttackRange( uint32 nMapID, float fX, float fY, float fZ );

    // �����ƶ���Ŀ���
    void ProcessMoveToAttackTarget();

    // �����ƶ���Ŀ�����
    void ProcessMoveArriveResult();

    // �����ƶ�·������
    void SetMoveRoutePoint();

    // ������·��
    virtual void ProcessArriveRoute();

    // �����򹥻�Ŀ��
    void ProcessChangeDirToTarget();

    // �������漴�ƶ�
    void ProcessMoveAround();

    // �ƶ����ϴο�ʼ�������������
    void ProcessMoveToLastIdlePoint();

    // �漴����
    void ProcessRandRun();

    // ��������
    virtual void ProcessFollowMaster();

    // �ƶ����������
    virtual void ProcessMoveToMaster();

    // ����
    virtual void ProcessIdle();

    // �ƶ�����һ��·��
    void ProcessMoveToRoute();

    // ����ͣ��������ҶԻ�
    void ProcessStopToTalk();

    // ��������״̬���
    virtual void ProcessBufferStatus();

    // ���ҹ���Ŀ��
    virtual void ProcessFindAttackTarget();

    // �������Ĺ���Ŀ��
    int GetMinDistanceAttackTarget();

    // �������޹���Ŀ��
    int GetMaxEnmityAttackTarget();

    // ����Ŀ��
    void ProcessAttackTarget();

    // �Ƿ���Կ���AI˼����״̬
    virtual bool CheckAiThinkingMonsterStatus() { return true; }

    // ˼������Ŀ��
    uint8 ThinkingAttackTarget( uint32 nCurrentTime );

    // ˼���ƶ�������Ŀ��
    uint8 ThinkingMoveToTarget();

    // ˼���ƶ���������
    uint8 ThinkingMoveToBorn();

    // ˼���ƶ�����ʼ�������ĵص�
    uint8 ThinkingMoveToLastIdle();

    // ˼���ƶ�����һ��·��
    uint8 ThinkingMoveToRoute();

    // ˼���ƶ�����һ����
    uint8 ThinkingMoveToPoint();

    // ˼����Χ����ƶ�
    uint8 ThinkingMoveAround();

    // ˼��ͣ�����Ի�
    uint8 ThinkingStopToTalk();

    // ˼���漴�ƶ�
    uint8 ThinkRandRun();

    // �ж��Ƿ����ü���
    bool CheckCanUseSkill( uint16 nSkillID );

    // �жϵ�ǰ�ܷ񹥻�������
    bool CheckCanAttackTargetDistance( BaseCharacter* pTarget, int nSkillID, int nSkillLevel );

    // �����Թ���Ŀ��( �ı�ս��״̬�� )
    void ProcessTryAttackTarget( BaseCharacter* pTarget );

    // �ж��Ƿ����ִ�������ű�
    bool CheckDeathCallScript();

    // ����������������״̬�ĸı�
    virtual void ProcessDeathChangeStatus();

    // �������������, �˳���Ϸ����
    virtual void ProcessDeathExitWorld();

    // ��ǰ����ʹ�ü��ܵ�����
    void SetUseSkillIndex( int8 nValue ) { m_nUseSkillIndex = nValue; }
    int8 GetUseSkillIndex() const { return m_nUseSkillIndex; }
    bool HaveUseSkill() { return m_nUseSkillIndex != -1; }

    void StartReliveTimer( unsigned int nCurrenrTime, unsigned int nSpaceTime );

    // �ж��Ƿ����ƶ�
    virtual bool CheckCanAiMoving();

    void InitRoute( uint32 nMapID, int nRouteID );

    // ����ͬ��һ������
    void SetVerifyPointAtOnce();

    //////////////////////////////////////////////////////////////////////////////
    // ��ûظ����ʱ��
    virtual uint32 GetRestoreSpaceTime() { return 5000; }

    // �����Ѫ��ֵ
    virtual int GetRestoreHP() { return 10000; }

    // �����ħ��ֵ
    virtual int GetRestoreMP() { return 10000; }

    // ���������Ұ��Χ
    virtual int GetIdleViewSight() { return AiDefine::MinEnmityViewSight; }

    // ����ս����Ұ��Χ
    virtual int GetFightViewSight() { return 10; }

    // ��ù���Idle״̬���漴�ƶ�����
    virtual int GetIdleMoveRate() { return 0; }

    // ��󹥻���Χ
    virtual int GetMaxAttackRange() { return -1; }

    // ��������޷�Χ
    virtual int GetBaseEnmityRange() { return -1; }

    // ���׷��ʱ��
    virtual uint32 GetKeepAttakTime() { return 0; }

    // ����������
    virtual void ProcessDropItemPackage( int nDropPackIndex ) { return; };

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // ��ʼ����
    virtual float GetBornDir() { return 0.0f; }

    virtual const char* GetAILuaScript() const { return ""; }

#include "AiLuaScript.h"

protected:

    // ����������
    D3DXVECTOR3 m_xBornPoint;

    // ��һ��δ������������
    D3DXVECTOR3 m_xLastIdlePoint;

    // ָ������
    D3DXVECTOR3 m_xMovePoint;

    // ָ���ƶ�����Ŀ��λ��
    D3DXVECTOR3 m_xMoveTargetPoint; 

    // ������ƶ���Χ
    RECT m_xCanMoveZone;

    // �����Ai״̬
    uint8 m_nAiStatus;

    // ��ǰʹ�ü��ܵ�����
    int8 m_nUseSkillIndex;

    // ʹ��AI���ܵ��ܸ���
    uint32 m_nUseSkillTotalRate;

    // ���＼��
    AiSkill m_xAiSkill[ AiDefine::MonsterMaxSkillCount ];

    // �����AI�������
    typedef std::vector< AiTask* > AiTaskVector;
    typedef AiTaskVector::iterator AiTaskVectorIter;
    AiTaskVector m_vecAiTask;

    // 9�������������
    int16 m_n9AreaPlayerCount;

    // ������Ұ����( �ǿɱ��, ��ս����Ұ, �Ϳ�����Ұ )
    int m_nViewSight;

    // AI˼��ʱ��
    int m_nThinkingTime;

    // AI��ʱ��
    GameTimerEx m_xTimer[ AiDefine::AiTimer_MaxCount ];
	bool m_bKeepAttackTimeFlag;

    // ͣ�����Ի���ʱ��
    GameTimerEx m_xTalkTimer;

    // �Ƿ�ͬ������
    bool m_bNeedVerifyPoint;

    // �����·����Ϣ
    SRoute* m_pRoute;

    // ��ǰ�ƶ���·������һ����
    int16 m_nRouteStep; 

    // �ƶ�����
    float m_fMoveStep; 
    
    // �Ի��˵�����
    int m_nTalkCount;

    // �ű�ID
    int m_nDeathScriptVMID;

    // Ѱ·
    CharacterFindParth	_charFindParth;
	bool	_blIsFindParthConfig;
	bool	_blIsDynamicBlockConfig;

	// �������߼�
	MonsterGroupLogic m_xMonsterGroupLogic;

	// ��¼�����ҵĵ�λ�ĵ÷����  
	MapIdScoreContainer m_mapPlayerScore;				
};


///////////////////////////////////////////////////////////////////////////////////////
inline void AiCharacter::SetHPMax( uint32 hpMax )
{
    GetCharFightAttr()->hpMax.base = hpMax;
    GetCharFightAttr()->hpMax.UpdateFinal();
}

inline void AiCharacter::SetMPMax( uint32 mpMax )
{
    GetCharFightAttr()->mpMax.base = mpMax;
    GetCharFightAttr()->mpMax.UpdateFinal();
}

inline void AiCharacter::SetMP( int nMp )
{
    if ( nMp> GetMPMax() )
    { _nMp = GetMPMax(); }
    else
    { _nMp = nMp; }
}

inline void AiCharacter::SetThinkingSpaceTime( uint32 nThinkingTime )
{
    m_xTimer[ AiDefine::AiTimer_Thinking ].SetSpaceTime( nThinkingTime );
}

inline void AiCharacter::SetBornPoint( float fX, float fY, float fZ )
{
    m_xBornPoint.x = fX;
    m_xBornPoint.y = fY;
    m_xBornPoint.z = fZ;
}

inline void AiCharacter::SetLastIdlePoint( float fX, float fY, float fZ )
{
    m_xLastIdlePoint.x = fX;
    m_xLastIdlePoint.y = fY;
    m_xLastIdlePoint.z = fZ;
}

inline bool AiCharacter::NeedMoveToLastIdlePoint()
{
    return m_xLastIdlePoint.x != 0.f;
}

inline void AiCharacter::ClearLastIdlePoint()
{
    m_xLastIdlePoint.x = 0.f;
    m_xLastIdlePoint.y = 0.f;
    m_xLastIdlePoint.z = 0.f;
}

inline bool AiCharacter::NeedMovingToTargetPoint()
{
    return m_xMoveTargetPoint.x != 0.f;
}

inline void AiCharacter::ClearMoveTargetPoint()
{
    // ���ϸ���һ������
    if ( NeedMovingToTargetPoint() )
    { SetVerifyPointAtOnce(); }

    m_xMoveTargetPoint.x = 0.f;
    m_xMoveTargetPoint.y = 0.f;
    m_xMoveTargetPoint.z = 0.f;
}

inline void AiCharacter::SubAreaPlayerCount( int nValue )
{
    m_n9AreaPlayerCount -= nValue;
    if ( m_n9AreaPlayerCount < 0 )
    { m_n9AreaPlayerCount = 0; }
}

// ���ƶ���Χ
inline void AiCharacter::SetCanMoveZone( const RECT& zone )
{
    m_xCanMoveZone = zone;
}

inline bool AiCharacter::CheckInCanMoveZone()
{
    if ( GetTileX() < m_xCanMoveZone.left )
    { return false; }

    if ( GetTileX() > m_xCanMoveZone.right )
    { return false; }

    if ( GetTileY() < m_xCanMoveZone.top )
    { return false; }

    if ( GetTileY() > m_xCanMoveZone.bottom )
    { return false; }

    return true;
}   

inline bool AiCharacter::CheckInBaseEnmityRange()
{
    if ( GetBaseEnmityRange() == -1 )
    { return true; }

    if ( abs( m_xBornPoint.x - GetFloatX() ) > GetBaseEnmityRange() ||
         abs( m_xBornPoint.y - GetFloatY() ) > GetBaseEnmityRange() /*||
         abs( m_xBornPoint.z - GetFloatZ() ) > GetBaseEnmityRange()*/ )
    {
        return false;
    }

    return true;
}

inline void AiCharacter::StartReliveTimer( unsigned int nCurrenrTime, unsigned int nSpaceTime )
{
    m_xTimer[ AiDefine::AiTimer_Relive ].StartTimer( nCurrenrTime, nSpaceTime );
}

inline void AiCharacter::SetVerifyPointAtOnce()
{
    m_xTimer[ AiDefine::AiTimer_Move ].NextTimer( 1 );
    m_bNeedVerifyPoint = true;
}

#endif