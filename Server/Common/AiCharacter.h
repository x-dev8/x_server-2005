#ifndef __AICHARACTER_H__
#define __AICHARACTER_H__

/************************************************************************
                            具有AI的角色

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

    // 执行AI逻辑
    virtual void Run( uint32 nCostTime );

    // 在处理消息前调用
    virtual void ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); 

    // 处理消息
    virtual bool ProcessMsg( Msg* pMessage );

    // 进入视野
    virtual void EnterMySight( BaseCharacter* pTarget );

    // 离开视野
    virtual void ExitMySight( BaseCharacter* pTarget );

    // 被攻击
    virtual void OnBeAttacked( BaseCharacter* pAttacker,const ItemDefine::SItemSkill* pSkillConfig );

    // 是否一定要miss攻击
    virtual bool IsMustMiss();

    // 死亡
    virtual void OnDeath();     

    // 处理退出消息
    virtual void OnExit( Msg* pMessage, uint8 nExitType = ET_ExitGame );       

    // 应用BUFF
    virtual long ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue );

    // 判断能否被攻击
    virtual bool CheckCanBeAttack();

    // 思考时间
    int GetThinkingTime() { return m_nThinkingTime; }
    void SetThinkingTime( int nValue ) { m_nThinkingTime = nValue; }

    // 设置出生点
    void SetBornPoint( float fX, float fY, float fZ );

    // 怪物Ai状态
	void SetAiStatus( uint8 nValue ) { m_nAiStatus = nValue; }
    uint8 GetAiStatus() const { return m_nAiStatus; }

    // 怪物Ai技能
    virtual void AddAiSkill( uint8 nIndex, AiSkill& xSkill );
    virtual AiSkill* GetAiSkillByIndex( uint8 nIndex );
    virtual AiSkill* GetAiSkillByID( uint16 nSkillID, uint8 nSkillLevel );

    // 设置当前使用的技能
    virtual void SetUseSkill( uint16 nSkillID, uint16 nSkillLevel );

    // 获得怪物使用的技能
    virtual AiSkill* GetCanUseSkill( uint32 nCurrentTime );

    // 处理锁定攻击目标
   virtual void ProcessLockTarget( int nTargetID );

    // 添加怪物Task
    void AddAiTask( GameObjectId nAttackID, uint16 nSkillID, uint8 nSkillLevel, uint8 nTaskPriority = AiDefine::NormalAiTaskPriority );

    // 9宫格内玩家数量
    void AddAreaPlayerCount( int nValue = 1 ) { m_n9AreaPlayerCount += nValue; }
    void SubAreaPlayerCount( int nValue = 1 );
    bool HaveAreaPlayer() { return m_n9AreaPlayerCount > 0; }

    // 视野
    void SetViewSight( int nValue ) { m_nViewSight = nValue; }
    int GetViewSight() const { return m_nViewSight; }

    // 可移动范围
    void SetCanMoveZone( const RECT& zone ); 

    // 改变移动速度
    void ChangeMoveSpeed( float fValue );

    // 开始视野定时器
    void StartIdleViewTimer( uint32 nCurrentTime );

    // 待机移动速度
    virtual float GetIdleMoveSpeed() { return 0.0f; }

    // 追击或跑回移动速度
    virtual float GetAttackMoveSpeed() { return 0.0f; }

    // 怪物自杀
    virtual void CharacterMurder();

    // 获得视野仇恨
    virtual int GetViewEnmity() { return 100; }

    // 找到主人
    virtual GamePlayer* GetMasterPlayer();

    // 移动步长
    void SetMoveStep( float fValue ) { m_fMoveStep = fValue; }
    float GetMoveStep() { return m_fMoveStep; }

    // 开始对话
    void StartTalk();

    // 结束对话
    void EndTalk();

    // 正在冲锋移动
    virtual void DoAssaultMoving( float fDistance, int nInstantMovingType ); 

    // 计算伤害仇恨
    virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

    //////////////////////////////////////////////////////////////////////////
    //寻路
    typedef std::vector< swVec2f >	FindParth;
    typedef FindParth::iterator		ItrFindParth;

    void		InitFindParth( GameObjectId nID, bool blIsFindParth, bool blIsDynamicBlock );	// 初始化寻路信息
	void		OnFindParthConfigChanged( bool blNewIsFindParth, bool blNewIsDynamicBlock );	// 供外部寻路配置变化时调用
    bool		FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange );	// 寻找下一个目标位置,等待线程寻路时返回false
    void		AfterMoveToPos();												// 移动后
    bool		CheckReachPos();												// 检查是否寻路结束
    CharacterFindParth& GetCharFindParth() { return _charFindParth; }

	// 巡逻组
	friend class MonsterGroup;
	// 获得怪物组逻辑
	MonsterGroupLogic& GetMonsterGroupLogic() { return m_xMonsterGroupLogic; }

	// 新仇恨目标接口
	virtual void OnNewEnmityTarget( GameObjectId nID ) { m_xMonsterGroupLogic.OnNewEnmityTarget( nID ); }

	/////////////////////////////////////////////////////////////////////////
	//归属相关 by cloud
	virtual void UpdatePlayerScore( GameObjectId stID, int iDamage );	// 记录攻击者的战绩信息*

	virtual void CheckClearAttackerScore();								// 检查清除无效的伤害得分
	virtual void ClearAttackerScoreById( GameObjectId nId );			// 清理指定的玩家
	virtual void ClearAllAttackerScore();								// 清理所有的玩家

	virtual GameObjectId GetBestAttacker();								// 谁是最厉害的攻击者
	virtual GameObjectId GetFirstValidAttacker();						// 得到第一个有效的攻击者
protected:

    // 处理目标丢失
    uint8 ProcessLostLockTarget( BaseCharacter* pTarget );

    // 判断是否能攻击
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // 处理怪物的视野仇恨
    void ProcessViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // 判断是否要刷新视野仇恨
    virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // 进入视野加仇恨列表
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget ){};

    // 处理结束战斗状态
    virtual void ProcessEndAttackStatus();

    // 清除Ai变量
    virtual void ClearAiVariable();

    // 处理怪物思考
    virtual void ProcessAiThinking( uint32 nCurrentTime );

    // 怪物思考逻辑
    virtual uint8 AiThinking( uint32 nCurrentTime );

    // 处理怪物衰减后的结果
    virtual void ProcessClearEnmityResult( GameObjectId nTargetID );

    // 执行怪物AiTask
    virtual void ProcessAiTask( AiTask* pAiTask );

    // 刷新怪物仇恨
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // 处理怪物复活
    virtual void ProcessAiRelive();

    // 获得怪物思考时间
    virtual int GetThinkingSpaceTime();

    // 处理死亡调用死亡脚本
    void ProcessDeathCallScript();

    // 清空任务
    void ReleaseAiTask();

    // 处理怪物AI逻辑
    virtual void ProcessAiLogic( uint32 nCostTime );

    // 是否可以处理AiTask
    bool CheckCanAiTask();

    // 处理怪物AiTask
    void ProcessAiTask();

    // 处理消失
    bool ProcessDisappear();

    // 设置思考时间
    void SetThinkingSpaceTime( uint32 nThinkingTime );

    // 是否有移动能力
    bool HaveMoveAbility();

    // 处理怪物移动
    virtual void ProcessAiMoving( uint32 nCostTime );

    // 设置开始被攻击的坐标
    void SetLastIdlePoint( float fX, float fY, float fZ );

    // 是否需要移动到开始被攻击的坐标
    bool NeedMoveToLastIdlePoint();

    // 清除上次被攻击的坐标
    void ClearLastIdlePoint();

    // 设置移动到的目标位置
    void SetMoveTargetPoint( float fX, float fY, float fZ );

    void SetMovePoint( float fX, float fY, float fZ );

    // 是否需要移动
    bool NeedMovingToTargetPoint();

    // 清除移动目标点
    void ClearMoveTargetPoint();

    // 判断是否是相同的同步位置点
    bool CheckSameVerifyPoint( float fX, float fY, float fZ );

    // 判断是否在可移动范围内
    bool CheckInCanMoveZone();

    // 判断是否在基础仇恨范围
    bool CheckInBaseEnmityRange();

    // 判断是否需要移动到下一个路点
    bool NeedMoveToNextRoute() { return m_nRouteStep != -1; }

    // 发送移动到坐标消息
    void SendMoveToTargetPointMessage( GamePlayer* pTarget = NULL);

    // 发送靠近目标消息
    void SendClosingToTargetMessage();

    // 发送同步坐标位置消息
    void SendVerifyPointMessage();

    // 处理怪物脱离战斗后视野变化
    void ProcessIdleViewSightChange();

    // 开启回血回魔定时器
    void StartRestoreTimer( uint32 nCurrentTime );

    // 处理怪物回血, 回魔
    void ProcessRestore( uint32 nCurrentTime );

    // 处理攻击时移动速度
    void ProcessAttackMoveSpeed( float fModulus = 1.0f );

    // 处理空闲时的移动速度
    void ProcessIdleMoveSpeed();

    // 处理移动到出生点
    void ProcessMoveToBornPoint();

    // 处理移动到某点
    void ProcessMoveToPoint();

    bool CheckInMaxAttackRange( uint32 nMapID, float fX, float fY, float fZ );

    // 处理移动到目标点
    void ProcessMoveToAttackTarget();

    // 处理移动到目标点结果
    void ProcessMoveArriveResult();

    // 设置移动路点坐标
    void SetMoveRoutePoint();

    // 处理到达路点
    virtual void ProcessArriveRoute();

    // 处理朝向攻击目标
    void ProcessChangeDirToTarget();

    // 处理附近随即移动
    void ProcessMoveAround();

    // 移动到上次开始被攻击的坐标点
    void ProcessMoveToLastIdlePoint();

    // 随即乱跑
    void ProcessRandRun();

    // 跟随主人
    virtual void ProcessFollowMaster();

    // 移动到主人身边
    virtual void ProcessMoveToMaster();

    // 待机
    virtual void ProcessIdle();

    // 移动到下一个路点
    void ProcessMoveToRoute();

    // 处理停下来与玩家对话
    void ProcessStopToTalk();

    // 处理中了状态结果
    virtual void ProcessBufferStatus();

    // 查找攻击目标
    virtual void ProcessFindAttackTarget();

    // 获得最近的攻击目标
    int GetMinDistanceAttackTarget();

    // 获得最大仇恨攻击目标
    int GetMaxEnmityAttackTarget();

    // 攻击目标
    void ProcessAttackTarget();

    // 是否除以可以AI思考的状态
    virtual bool CheckAiThinkingMonsterStatus() { return true; }

    // 思考攻击目标
    uint8 ThinkingAttackTarget( uint32 nCurrentTime );

    // 思考移动到攻击目标
    uint8 ThinkingMoveToTarget();

    // 思考移动到出生点
    uint8 ThinkingMoveToBorn();

    // 思考移动到开始被攻击的地点
    uint8 ThinkingMoveToLastIdle();

    // 思考移动到下一个路点
    uint8 ThinkingMoveToRoute();

    // 思考移动到下一个点
    uint8 ThinkingMoveToPoint();

    // 思考周围随机移动
    uint8 ThinkingMoveAround();

    // 思考停下来对话
    uint8 ThinkingStopToTalk();

    // 思考随即移动
    uint8 ThinkRandRun();

    // 判断是否能用技能
    bool CheckCanUseSkill( uint16 nSkillID );

    // 判断当前能否攻击到怪物
    bool CheckCanAttackTargetDistance( BaseCharacter* pTarget, int nSkillID, int nSkillLevel );

    // 处理尝试攻击目标( 改变战斗状态等 )
    void ProcessTryAttackTarget( BaseCharacter* pTarget );

    // 判断是否可以执行死亡脚本
    bool CheckDeathCallScript();

    // 处理怪物死亡后怪物状态的改变
    virtual void ProcessDeathChangeStatus();

    // 处理怪物死亡后, 退出游戏世界
    virtual void ProcessDeathExitWorld();

    // 当前怪物使用技能的索引
    void SetUseSkillIndex( int8 nValue ) { m_nUseSkillIndex = nValue; }
    int8 GetUseSkillIndex() const { return m_nUseSkillIndex; }
    bool HaveUseSkill() { return m_nUseSkillIndex != -1; }

    void StartReliveTimer( unsigned int nCurrenrTime, unsigned int nSpaceTime );

    // 判断是否能移动
    virtual bool CheckCanAiMoving();

    void InitRoute( uint32 nMapID, int nRouteID );

    // 马上同步一次坐标
    void SetVerifyPointAtOnce();

    //////////////////////////////////////////////////////////////////////////////
    // 获得回复间隔时间
    virtual uint32 GetRestoreSpaceTime() { return 5000; }

    // 怪物回血数值
    virtual int GetRestoreHP() { return 10000; }

    // 怪物回魔数值
    virtual int GetRestoreMP() { return 10000; }

    // 怪物空闲视野范围
    virtual int GetIdleViewSight() { return AiDefine::MinEnmityViewSight; }

    // 怪物战斗视野范围
    virtual int GetFightViewSight() { return 10; }

    // 获得怪物Idle状态下随即移动概率
    virtual int GetIdleMoveRate() { return 0; }

    // 最大攻击范围
    virtual int GetMaxAttackRange() { return -1; }

    // 最大基础仇恨范围
    virtual int GetBaseEnmityRange() { return -1; }

    // 获得追击时间
    virtual uint32 GetKeepAttakTime() { return 0; }

    // 处理怪物掉落
    virtual void ProcessDropItemPackage( int nDropPackIndex ) { return; };

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // 初始朝向
    virtual float GetBornDir() { return 0.0f; }

    virtual const char* GetAILuaScript() const { return ""; }

#include "AiLuaScript.h"

protected:

    // 出生点坐标
    D3DXVECTOR3 m_xBornPoint;

    // 上一次未被攻击的坐标
    D3DXVECTOR3 m_xLastIdlePoint;

    // 指定坐标
    D3DXVECTOR3 m_xMovePoint;

    // 指定移动到的目标位置
    D3DXVECTOR3 m_xMoveTargetPoint; 

    // 怪物可移动范围
    RECT m_xCanMoveZone;

    // 怪物的Ai状态
    uint8 m_nAiStatus;

    // 当前使用技能的索引
    int8 m_nUseSkillIndex;

    // 使用AI技能的总概率
    uint32 m_nUseSkillTotalRate;

    // 怪物技能
    AiSkill m_xAiSkill[ AiDefine::MonsterMaxSkillCount ];

    // 怪物的AI任务队列
    typedef std::vector< AiTask* > AiTaskVector;
    typedef AiTaskVector::iterator AiTaskVectorIter;
    AiTaskVector m_vecAiTask;

    // 9宫格内玩家数量
    int16 m_n9AreaPlayerCount;

    // 怪物视野返回( 是可变的, 有战斗视野, 和空闲视野 )
    int m_nViewSight;

    // AI思考时间
    int m_nThinkingTime;

    // AI定时器
    GameTimerEx m_xTimer[ AiDefine::AiTimer_MaxCount ];
	bool m_bKeepAttackTimeFlag;

    // 停下来对话定时器
    GameTimerEx m_xTalkTimer;

    // 是否同步坐标
    bool m_bNeedVerifyPoint;

    // 怪物的路点信息
    SRoute* m_pRoute;

    // 当前移动到路径的那一个点
    int16 m_nRouteStep; 

    // 移动步长
    float m_fMoveStep; 
    
    // 对话人的数量
    int m_nTalkCount;

    // 脚本ID
    int m_nDeathScriptVMID;

    // 寻路
    CharacterFindParth	_charFindParth;
	bool	_blIsFindParthConfig;
	bool	_blIsDynamicBlockConfig;

	// 怪物组逻辑
	MonsterGroupLogic m_xMonsterGroupLogic;

	// 记录攻击我的单位的得分情况  
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
    // 马上更新一次坐标
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

// 可移动范围
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