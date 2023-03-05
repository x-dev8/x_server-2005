#include "NpcFight.h"
#include "MonsterBase.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "GameWorld.h"
#include "AiNormalAttackTask.h"
#include "RouteManager.h"

void NpcFight::SetHPMax( uint32 hpMax ) 
{ 
    GetCharFightAttr()->hpMax.base = hpMax;
    GetCharFightAttr()->hpMax.UpdateFinal();
}

uint32 NpcFight::GetHPMax()
{ 
    return GetCharFightAttr()->hpMax.final;
}

void NpcFight::SetMPMax( uint32 mpMax )
{
    GetCharFightAttr()->mpMax.base = mpMax;
    GetCharFightAttr()->mpMax.UpdateFinal();
}

uint32 NpcFight::GetMPMax()
{
    return GetCharFightAttr()->mpMax.final;
}

uint32 NpcFight::Init()
{
    if ( NULL == _pNpcInfo)
    { return ER_Failed; }

    if ( _pNpcInfo->fightData.empty() )
    { return ER_Failed; }

    NpcInfo::FightInfo& fightInfo = _pNpcInfo->fightData[0];
    SetObjType       ( Object_NpcFight         ); // 设置类型
    SetCanSwitchStage( false                   ); // 设置为不可切换场所
    SetStatus        ( CS_IDLE                 ); // 设置初始化状态为空闲
    SetCharName      ( _pNpcInfo->name.c_str() );
    SetDisappearTime ( fightInfo.disappearTime );
    SetBodySize      ( fightInfo.bodyLength    ); // 设置身体大小
    SetDeadScript    ( fightInfo.deadScript.c_str() );
    SetLevel         ( fightInfo.level         ); // 设置等级
    SetMoveRange     ( fightInfo.maxRange      );
    SetChangePassive ( fightInfo.changePassive );
    SetEndPassiveTime( fightInfo.passiveTime   );
    SetBornPoint     ( SFPos2( GetFloatX(), GetFloatY()));
    SetBaseEnmityRange( fightInfo.baseEnmityRange );
    SetAttackRange   ( fightInfo.normalAttackMin, fightInfo.normalAttackMax );


    SetHPMax         ( fightInfo.hpMax  );
    SetMPMax         ( fightInfo.mpMax  );
    GetCharFightAttr()->attackPhysics    .base = fightInfo.attackPhysics;
    GetCharFightAttr()->attackMagic      .base = fightInfo.attackMagic;
    GetCharFightAttr()->defendPhysics    .base = fightInfo.defendPhysics;
    GetCharFightAttr()->defendMagic      .base = fightInfo.defendMagic;
    GetCharFightAttr()->attackSpeed      .base = fightInfo.attackSpeed;
    GetCharFightAttr()->hpRestore        .base = fightInfo.hpRestore;
    GetCharFightAttr()->mpRestore        .base = fightInfo.mpRestore;
    GetCharFightAttr()->exact            .base = fightInfo.exact;
    GetCharFightAttr()->dodge            .base = fightInfo.dodge;
    GetCharFightAttr()->critical         .base = fightInfo.critical;
    GetCharFightAttr()->tenacity         .base = fightInfo.tenacity;
    GetCharFightAttr()->criticalIntensity.base = fightInfo.criticalIntensity;
    GetCharFightAttr()->backStrike       .base = fightInfo.backStrike;
    GetCharFightAttr()->backStrikeResist .base = fightInfo.backStrikeResist;
    GetCharFightAttr()->breakStrike      .base = fightInfo.breakStrike;
    GetCharFightAttr()->stabStrike       .base = fightInfo.stabStrike;
    GetCharFightAttr()->elementStrike    .base = fightInfo.elementStrike;
    GetCharFightAttr()->toxinStrike      .base = fightInfo.toxinStrike;
    GetCharFightAttr()->spiritStrike     .base = fightInfo.spiritStrike;
    GetCharFightAttr()->breakResist      .base = fightInfo.breakResist;
    GetCharFightAttr()->stabResist       .base = fightInfo.stabResist;
    GetCharFightAttr()->elementResist    .base = fightInfo.elementResist;
    GetCharFightAttr()->toxinResist      .base = fightInfo.toxinResist;
    GetCharFightAttr()->spiritResist     .base = fightInfo.spiritResist;

    SetViewSight        ( fightInfo.view      );
    SetIdleMoveViewSight( fightInfo.view      );
    SetFightViewSight   ( fightInfo.fightView );

    // 移动速度
    if( fightInfo.idleMoveSpeed > 1.5f )
    { GetCharFightAttr()->moveSpeed.base = 1.5f; }
    else
    { GetCharFightAttr()->moveSpeed.base = fightInfo.idleMoveSpeed; }

    SetNormalMoveSpeed   ( fightInfo.moveSpeed      );
    SetIdleMoveSpeed     ( fightInfo.idleMoveSpeed  );
    SetLastMovingSpeed   ( GetMoveSpeed()           );

    UpdateCharAllAttibute();

    SetHP                ( fightInfo.hpMax );
    SetMP                ( fightInfo.mpMax );

    for ( int i=0; i<NpcInfo::FightInfo::ECD_SkillCount; ++i )
    {
        skillInfo[ i ].m_iSkillId     = fightInfo.skills[i].skillId;
        skillInfo[ i ].m_stSkillLevel = fightInfo.skills[i].skillLevel;
        skillInfo[ i ].m_stSkillRate  = fightInfo.skills[i].skillRate;
    }

    SetSkillRateTotal();
    
    // 如果不为主动怪
    bPassiveConfig = fightInfo.isInitiative == 0 ? true : false;
    SetPassiveAttack( bPassiveConfig );     
    SetEnmityRate   ( fightInfo.enmityDecRate );
    SetViewEnmity   ( fightInfo.enmityView    );
    
    SetSkillColdDown();    
    SetDead( false );
    // 得到Npc的路点信息,因为有的Npc没有路点，所以不需要判断返回值是否为True
    NpcInfo::Npc* pNpc = theNpcInfo.GetNpc( GetNpcID(), GetMapID() );
    uint16 routeId = pNpc->fightData[0].routeId;
    bool bResult = theRouteManager.GetRouteInfo( GetMapID(), routeId, _route );
    _routeId = routeId; // 设置路点Id

    if ( _bAIRun )
    { StartUpAI(); }
    return ER_Success;
}

NpcFight::NpcFight()
{
    SetObjType( Object_NpcFight );
    _buffManager.CreateFromData( _buffs, BodyStatusType_Max);
    _bAIRun = true;
    _disableControlThinkTime = false;
    m_dwLastThinkingTime     = 0;
    m_dwFightViewEndTime     = 0;
    m_iViewSight             = 0;
    m_stIdleMoveViewSight    = 1;
    m_stFightViewSight       = 1;
    _tryToAttackCharEnmity   = 0;
    _tryToAttackCharId       = InvalidGameObjectId;
    m_AttackCharacterCnt     = 0;
    nMaxRange                = 0;
    lastIdleX                = 0.0f;
    lastIdleY                = 0.0f;
    m_bIsFighting            = false;
    changePassiveConfig      = 0;
    m_bPassive               = false;
    canAttackCharId          = InvalidGameObjectId;
    m_bClosingToTarget       = false;
    m_bMoving                = false;
    _isNeedMove              = false;
    m_stSkillRateTotal       = 0;
    _bFinalArrive            = false;

    memset( &skillInfo,            0, sizeof(skillInfo)            );
    memset( &m_vLastSendTargetPos, 0, sizeof(m_vLastSendTargetPos) );
    m_iCurSkillId             = ErrorUnsignedShortID;
    m_stCurSkillLevel         = -1;
    m_nCurSkillIndex          = 0;
    m_pCurSkill               = NULL;
    m_stCurAttackRange        = 0;
    m_stCurAiTactic           = EAISelectTaskType_None;
    m_fNormalMoveSpeed        = 0.0f;
    m_fIdleMoveSpeed          = 0.0f;
    endPassiveTimeConfig      = -1;
    bPassiveConfig            = false; // 是否被动怪
    memset( &_moveTargetPos, 0, sizeof(_moveTargetPos) );
    _bOutOfRoute              = false;
    m_dwSendMoveMessageTime   = 0;
    m_noMoveSendVerifyPosTime = 0;
    m_nVMId                   = -1;
    m_nBaseEnmityRange        = 0;
    m_nAiValueWave            = 0;
    normalAttackMin           = 0;
    normalAttackMax           = 0;
    m_nEnmityRate             = 0;            
    _nViewEnmity              = 0;
}

void NpcFight::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bool bCostTime = false;    // 是否已经使用了累积时间
    m_dwProcessLogicCostTime += dwCostTime; // 累积时间 有的地方不是每个逻辑帧都调用的
    m_ExtendStatus.Process();
    switch ( GetStatus() )
    {
    case CS_IDLE:
        StatusActionIdle();
        break;
    case CS_ATTACK:// 角色处在攻击的状态
        StatusActionAttack();
        break;
    case CS_HOLDSKILL:// 持续技能
        StatusActionHoldSkill();
        break;
    case CS_INTONATE:// 吟唱
        StatusActionIntonate();
        break;
    case CS_HURT:
        break;
    case CS_DIEING:// 死亡状态，用于等待重生
        StatusActionDieing();
        break;
    default:
        break;
    }

    if( !IsDead() )
    { // 非死亡状态
        // 且距上次检查有1秒的间隔
        if( GameTime::IsPassCurrentTime( m_dwLastRefreshCharDataTime, CHAR_REFRESHTIME ) )
        {    
            m_dwLastRefreshCharDataTime = HQ_TimeGetTime();
            RefreshCharData( m_dwProcessLogicCostTime );
            bCostTime = true;
        }
    }

    if ( bCostTime )
    { m_dwProcessLogicCostTime = 0; }
    bContinue = true;
}

void NpcFight::EnterMySight( BaseCharacter* pWho )
{
    if( !pWho)
    { return; }

    if( IsDead() )
    { return;}

    if (pWho->IsPlayer())
    {
        if ( !AreaHavePlayer())
        { StartUpAI();}
        ++m_n9AreaPlayerCnt;
#ifdef _DEBUG
        if ( m_n9AreaPlayerCnt>= 2 )
        { int a = 0; }
#endif
    }
    else if ( pWho->IsMonster() )
    {
        MonsterBase* pAIChar = (MonsterBase*)pWho;
        if ( pAIChar->IsSummonMonster() )
        {
            if ( !AreaHavePlayer() )
            { StartUpAI(); }
            ++m_n9AreaPlayerCnt;
        }
        else
        {
            bool bCanAddEnmity = true;
            if ( !pAIChar->IsNeedFightMonster() )
            {
                bCanAddEnmity = false; 
            }

            if(bCanAddEnmity)
            { AddEnmityList(pWho->GetID());}
        }
    }
}

void NpcFight::ExitMySight( BaseCharacter* pWho )
{
    bool bReset = false;
    if (pWho->IsPlayer())
    {
        if (  AreaHavePlayer() )
        { --m_n9AreaPlayerCnt; }

        if ( !AreaHavePlayer() )
        { bReset = true; }
    }
    else if (pWho->IsMonster())
    {
        MonsterBase* pAIChar = (MonsterBase*)pWho;
        if ( pAIChar->IsSummonMonster() )
        {
            if ( AreaHavePlayer() )
            { --m_n9AreaPlayerCnt; }

            if ( !AreaHavePlayer() )
            { bReset = true; }
        }

        RemoveEnmityList(pWho->GetID());
        pWho->ClearAttackerById( GetID());
    }

    if ( bReset )
    {
        //在此回满血
        if ( !IsDead() )
        {
            if( GetHP() != GetHPMax() )
            { RestoreHPInstant(GetHPMax()); }

            if( GetMP() != GetMPMax() )
            { RestoreMPInstant(GetMPMax()); }
        }
        // _bAIRun = false;
    }
}

void NpcFight::Run( DWORD dwCostTime )
{
    if ( !_bAIRun )
    { return; }

    if ( !IsDead() )
    { // 没有死的的时候
        // 思考与Timer        
        ProcessAIThink();

        // 行动选择
        ProcessAISelectTask();

        // 处理AI移动
        ProcessAIMove(dwCostTime);

        // AI状态处理（根据人物进行等待还是做已经下发的的任务）
        ProcessAIDoTask();
    }
    else
    {
        if ( m_xReliveTimer.DoneTimer() )
        { Relive(); }
    }
    BaseCharacter::Run( dwCostTime );
}

void NpcFight::Relive()
{       
    if( !IsDead() )
    { return; }

    SetStatus( CS_IDLE );
    SetDead( false );
        
    SetHP( GetHPMax() );
    SetMP( GetMPMax() );

    // 清空人物身上的状态
    bool bResult = _buffManager.UpdateOnDead();
    if ( bResult )
    {
        //_buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );  
        ApplyBuffStatusToCharAttr();
        SendBuffChanged( NULL );
    }

    MsgCharAttrChanged Change;
    Change.iChangeCount = 0;
    Change.header.stID = GetID();
    Change.AddAttrShortChange( CharAttr_Relive, false );
    Change.AddAttrIntChange( CharAttr_HP, GetHP() );
    Change.AddAttrIntChange( CharAttr_MP, GetMP() );
    Change.CaluLength();
    GettheServer().SendMsgToView( &Change, GetID(), false );

    // 拉到出生点
    SetFloatXF( m_ptBornPoint.x );
    SetFloatYF( m_ptBornPoint.y );
    SendVerifyPos( GetFloatX(), GetFloatY() );
}

void NpcFight::RestoreHPInstant( int nRestoreHP )
{
    int nHp = GetHP();
    nHp += nRestoreHP;

    if( nHp > GetHPMax() )
    { nHp = GetHPMax(); }

    SetHP( nHp );
    ChangeAttr( CharAttr_HP, nHp );
}

void NpcFight::RestoreMPInstant( int nRestoreMP )
{
    int nMp = GetMP();
    nMp += nRestoreMP;

    if( nMp > GetMPMax() )
    { nMp = GetMPMax(); }

    SetMP( nMp );
    ChangeAttr(CharAttr_MP, nMp );
}

void NpcFight::ClearTryToAttackCharId()
{
    m_AttackCharacterCnt = 0;
    _tryToAttackCharId = InvalidGameObjectId;
    _tryToAttackCharEnmity = 0;
}

void NpcFight::ClearTryToAttackCharEnmity()
{
    _tryToAttackCharId = InvalidGameObjectId;
    _tryToAttackCharEnmity = 0;
}

void NpcFight::LockTarget( GameObjectId nMaxEnmityCharId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nMaxEnmityCharId );
    if ( NULL == pChar)
    { return ; }

    if ( pChar->GetID() == GetCanAttackCharId() )
    { return; }

    if ( IsAICanAttack( pChar ) )
    {
        SetCanAttackCharId( nMaxEnmityCharId ); 

        // 记录下上一次未被攻击前的空闲位置
        if ( lastIdleX == 0)
        {
            lastIdleX = GetFloatX();
            lastIdleY = GetFloatY();
        }
    }
}

void NpcFight::LostAttackTarget()
{
    // 如果是第一次失去目标，则清除AI脚本变量
    if( HaveCanAttackCharId() )
    { SendVerifyPos(GetFloatX(), GetFloatY()); }

    ClearCanAttackCharId();
    m_bClosingToTarget = false;
}

BaseCharacter* NpcFight::GetCanAttackChar() 
{
    if ( !HaveCanAttackCharId() )
    { return NULL; }
    return theRunTimeData.GetCharacterByID( canAttackCharId );
}

bool NpcFight::IsInRange()
{
    //如果nMaxRange为-1则不限制
    if (nMaxRange == -1)
    { return true; }

    // 未设置表示都在区域内
    if ( lastIdleX == 0 && lastIdleY == 0)
    { return true; }

    if (abs( lastIdleX - GetFloatX()) > nMaxRange || abs( lastIdleY - GetFloatY()) > nMaxRange)
    { return false; }

    return true;
}

bool NpcFight::IsInBaseEnmityRange()
{
    //如果nBaseEnmityRange为-1则不限制
    if ( m_nBaseEnmityRange == -1)
    { return false; }

    if (abs( m_ptBornPoint.x - GetFloatX()) > m_nBaseEnmityRange || abs( m_ptBornPoint.y - GetFloatY()) > m_nBaseEnmityRange)
    {
        return false;
    }

    return true;
}

bool NpcFight::IsCanAttack( BaseCharacter* pTarget )
{ // 是否是永久的不能攻击此目标 bForeverCanntAttack 表示
    // 自身中了状态不能攻击
    //if ( _buffManager.IsRandRun() )
    //{ return false; }

    if ( !pTarget->IsCanBeAttackedObject())
    { return false; }
    // 自己是普通怪物

    if ( pTarget->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pTarget );
        if ( pPlayer->GetProtectTime() > 0 )
        { // 玩家在保护时间 也怪物攻击不能他 但不是永久的
            return false; 
        }

        return true;
    }
    else if ( pTarget->IsMonster() )
    {
        MonsterBase* pAITarget = static_cast< MonsterBase* >( pTarget );
        if ( pAITarget->IsSummonMonster() || pAITarget->IsIllusionChar() )
        {
            BaseCharacter* pMaster  = theRunTimeData.GetCharacterByID( pAITarget->GetSummonMasterID() );
            if ( pMaster == NULL || !pMaster->IsPlayer() )
            { return false; };
        }

        return true;
    }

    return false;
}

void NpcFight::CallDeadScript() 
{
    BaseCharacter* pKiller = GetKiller();
    if ( !pKiller || !pKiller->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pKiller;
    const char* szScriptName = GetDeadScript();

    if( !szScriptName || szScriptName[0] == 0 )
    { return; }

    if ( m_nVMId == -1 )
    { m_nVMId = GetScriptMgr()->CreateVM( ST_NPC_DEAD, szScriptName, GetNpcID() ); }

    if ( m_nVMId == -1 )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Call NpcFight dead script failed: %s", szScriptName );
        return;
    }
    GetScriptMgr()->StartupVM( ST_NPC_DEAD, GetNpcID(), pPlayer );
}

void NpcFight::OnDeath()
{
    MsgSawSomeoneDead msg;
    msg.header.stID = GetID();

    if ( AreaHavePlayer() )
    { GettheServer().SendMsgToView( &msg, GetID(), true );}

    // 清空所有仇恨列表
    RemoveAllEnmityList( GetID());

    // 调用死亡脚本
    CallDeadScript();

    // 设置死亡
    SetStatus( CS_DIEING );

    // 不要从场景中移除 只是躺地, 启动复活定时器
    m_xReliveTimer.StartTimer( HQ_TimeGetTime(), _pNpcInfo->fightData[0].reliveTime );
}

bool NpcFight::IsAICanAttack( BaseCharacter* pChar )
{
    if( pChar == NULL )
    { return false; }

    // 死亡了不能攻击
    if( IsDead() || pChar->IsDead() )
    { return false; }

    // 自身中了状态不能攻击
    //if ( _buffManager.IsRandRun() )
    //{ return false; }

    int country = pChar->GetCountry();

    // 可是范围外不能攻击
    //if( !IsDistanceLess( GetX(), GetY(), pChar->GetX(), pChar->GetY(), GetViewSight() ))
    //    return false;

    //// 无国家不能攻击
    //if( country == Hero::country_none )
    //    return false;

    //// 相同国家不能攻击
    //if( country == GetCountry() )
    //    return false;

    return IsCanAttack( pChar );
}

void NpcFight::SendVerifyPos( float x, float y )
{
    // 确保附近有玩家才发送，以提高性能
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerVerifyPos msg;

        msg.SetLevel( level_normal ); // 在这里设置中等优先级

        msg.header.stID = GetID();
        msg.vPos.x      = x;
        msg.vPos.y      = y;
        msg.vPos.z      = 0;
        msg.chDirX      = (char)(GetDirX()*127);
        msg.chDirY      = (char)(GetDirY()*127);
        msg.chDirZ      = 0;
        GettheServer().SendMsgToView( &msg, GetID(), true );
    }

    m_vLastSendTargetPos.x = x;
    m_vLastSendTargetPos.y = y;
}

void NpcFight::SendClosingToTarget( GameObjectId nTargetID, D3DXVECTOR3 vNextPos )
{
    // 确保附近有玩家才发送，以提高性能
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerClosingToLockTarget msg;
        msg.header.stID = GetControl()->GetID();
        msg.LockTargetID = nTargetID;
        msg.vPos = vNextPos;
        GettheServer().SendMsgToView(&msg, GetID(), true);
    }
}

void NpcFight::SetCurSkillIndex( int i )
{
    m_iCurSkillId = skillInfo[i].m_iSkillId;
    m_nCurSkillIndex = i;
}

int NpcFight::GetCurSkillIndex()
{
    if( m_nCurSkillIndex >= 0 && m_nCurSkillIndex < ECD_SkillInfoMaxSize )
    { return m_nCurSkillIndex; }

    return 0;
}

// 设置当前使用的技能等级
void NpcFight::SetCurSkillLevel( uint8 index )
{
    m_stCurSkillLevel = skillInfo[ index ].m_stSkillLevel;
}

bool NpcFight::IsHaveMoveAbility()
{
    if ( /*m_fIdleMoveSpeed == 0 ||*/ m_fNormalMoveSpeed == 0 )
    { return false; }

    return true;
}

bool NpcFight::IsBeginPosMove()
{
    if ( _moveTargetPos.x == 0 && _moveTargetPos.y == 0 && _moveTargetPos.z == 0 && !_bFinalArrive)
    { return false; }

    return true;
}

void NpcFight::ChangeMoveSpeed( float speed )
{
    SetMoveSpeed( speed );
    SetLastMovingSpeed( speed );
    ChangeAttr( CharAttr_MoveSpeed, speed );
}

unsigned int NpcFight::AddAttackCharacter( GameObjectId charId )
{
    m_AttackCharacterCnt++;
    return m_AttackCharacterCnt;
}

unsigned int NpcFight::DecAttackCharacter( GameObjectId charId )
{
    if (m_AttackCharacterCnt == 0)
    {
        ClearTryToAttackCharId();
        return 0;
    }
    m_AttackCharacterCnt--;
    return m_AttackCharacterCnt;
}

void NpcFight::ProcessAIThink()
{
    if ( !_disableControlThinkTime )
    { // 需要控制思考频率
        if( m_dwLastThinkingTime != 0 && !GameTime::IsPassCurrentTime( m_dwLastThinkingTime, m_nAiValueWave) )
        { return; }
        m_nAiValueWave = theRand.rand32() % 1000; // 设置下一次思考波动
        m_dwLastThinkingTime = HQ_TimeGetTime();
    }
    else
    {
        _disableControlThinkTime = false;
        m_dwLastThinkingTime = HQ_TimeGetTime();
    }

    // 可视距离
    if ( m_dwFightViewEndTime != 0 && GameTime::IsPassCurrentTime( m_dwFightViewEndTime, 2000 ) )
    {
        SetViewSight( GetIdleMoveViewSight());
        m_dwFightViewEndTime = 0;
    }

    if ( HaveTryToAttackCharId() && GetTryAttackCharEnmity() > 0 && IsInRange())
    { // 可以产生攻击行为
        ThinkAttack();
    }
    else
    { // 可以产生Idle常态行为 从攻击态回来 一直都没有攻击态
        ThinkIdle();
    }
}

void NpcFight::ProcessAISelectTask()
{
    switch ( m_stCurAiTactic )
    {
    case EAISelectTaskType_IdleMove:
        break;
    case EAISelectTaskType_TryAttackTarget:
        AITryAttack();
        break;
    case EAISelectTaskType_TryUseSkill:
        AITryUseSkill();
        break;
    default:
        break;
    }
}

void NpcFight::ProcessAIMove( DWORD lapseTime )
{
    if( IsDead() || !_buffManager.IsCanMove() )
    { return; }

    if( HaveCanAttackCharId() )     // 如果有攻击目标，则向目标移动
    { MoveAttackMoving( lapseTime ); }
    else
    { MovePosMoving( lapseTime ); }
}

void NpcFight::ProcessAIDoTask()
{
    while (!m_vecNormalTask.empty())
    {
        AiBaseTask* pTask = m_vecNormalTask.back();
        m_vecNormalTask.pop_back();

        pTask->ExecuteTask( this );
        pTask->Release();
    }
}

void NpcFight::ThinkAttack()
{
    if (!m_bIsFighting)
    {
        //设置成被动怪
        if ( changePassiveConfig != 0 )
        { SetPassiveAttack( true ); }

        m_bIsFighting = true;
        TryChangeFightState( m_bIsFighting, eFighting );
    }

    // 如果当前攻击目标找不到了，则跳出去
    if ( theRunTimeData.GetCharacterByID(GetTryToAttackCharId()) == NULL)
    {
        if (m_AttackCharacterCnt > 0)
        { m_AttackCharacterCnt -= 1; }
        SetAttackCharEnmity(0);
        LostAttackTarget();
        return;
    }

    // 思考可以攻击的Char
    LockTarget( GetTryToAttackCharId() );

    // 把目标置成第一个攻击他的人
    short stFirstAttackId = GetFirstValidAttacker();
    if ( stFirstAttackId != -1 && stFirstAttackId != GetTryToAttackCharId() )
    { // 第一个攻击自身的Object存在,且和现在攻击自身的Object不一样
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( stFirstAttackId );
        if ( pChar != NULL && pChar->IsPlayer() )
        {
            GamePlayer* pPlayer = (GamePlayer*)pChar;
            uint32 enmity = pPlayer->GetEnmity(GetID());
            if ( enmity == 0|| enmity == ENMITY_NOTINLIST )
            { UpdateFirstAttack( GetTryToAttackCharId() ); }
        }
    }

    // 如果有确认可以攻击的目标
    if( HaveCanAttackCharId() )
    {
        BaseCharacter* pTarget = GetCanAttackChar();
        if( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() )
        {
            LostAttackTarget();
            return;
        }

        _isNeedMove = false;

        if (!_SkillTaskManager.IsTaskEmpty())
        { return; }

        int iLevel = 1;
        int cSel = 0;
        int SelectRateRandNum = 0;
        int nCount = 0;
        CItemDetail::SItemSkill* pSkill = NULL;

        // 循环查找可用的技能
        while (pSkill == NULL && nCount < 1)
        {
            ++nCount;
            if( m_stSkillRateTotal > 0 )
            { SelectRateRandNum = theRand.rand32() % m_stSkillRateTotal; }
            
            if( SelectRateRandNum < skillInfo[0].m_stSkillRate )
            { cSel = 0; }
            else if( SelectRateRandNum < skillInfo[1].m_stSkillRate )
            { cSel = 1; }
            else if( SelectRateRandNum < skillInfo[2].m_stSkillRate )
            { cSel = 2; }
            else
            { cSel = 0; }

            SetCurSkillIndex( cSel );
            SetCurSkillLevel( cSel );

            pSkill = GettheItemDetail().GetSkillByID( GetCurSkill(), GetCurSkillLevel() );

        }

        m_pCurSkill = pSkill;
        if ( !pSkill )
        {
            SetStatus(CS_IDLE);
            return;
        }

        m_stCurAttackRange = pSkill->fRangeCanCast;

        float fRangeCorrect = monsterCastCorrect;

        if (pSkill != NULL && pSkill->fRangeCanCast == 0 && m_bMoving)
        { fRangeCorrect = 0.1f; }

        if ( IsInAttackRange( pTarget, pSkill, fRangeCorrect ) )
        {
            m_bClosingToTarget = false;
            if( cSel > 0 )
            { m_stCurAiTactic = EAISelectTaskType_TryUseSkill; }
            else
            { m_stCurAiTactic = EAISelectTaskType_TryAttackTarget; }

            // 看看能不能打
            if (IsNormalAttack( skillInfo[cSel].m_iSkillId ))
            {
                if (!_buffManager.IsCanUsePhysicsSkill())
                { m_stCurAiTactic = EAISelectTaskType_IdleMove;; }
            }
            else
            {
                if (!_buffManager.IsCanUseMagicSkill())
                { m_stCurAiTactic = EAISelectTaskType_IdleMove; }
            }
        }
        else
        {
            if ( IsHaveMoveAbility() )
            { m_bClosingToTarget = true; }
        }

        // 设置追击纪录
        _bOutOfRoute = true;
    }
    else
    {
        ThinkRouteMove();
    }
}

void NpcFight::ThinkIdle()
{
    if ( HaveCanAttackCharId() || HaveTryToAttackCharId() )
    { LostAttackTarget(); }

    if (m_AttackCharacterCnt == 0 || !IsInRange())
    { // 没有攻击自身的人 或者 不在区域内

        // 如果当前还有有仇恨的玩家，则把九宫格的仇恨清掉
        if (m_AttackCharacterCnt != 0)
        {
            int nAreaID = GetCurArea();
            GameStage* pGameStage = theGameWorld.GetStageById(GetMapID());            
            if ( pGameStage != NULL )
            {
                AreaIndexTPL(Area9) list;
                pGameStage->Get9AreaList(list, nAreaID);
                int nCount = list.Count();
                for ( int i=0; i<nCount; ++i)
                {
                    GameArea* pGameArea = pGameStage->GetArea(list[i]);
                    if ( NULL == pGameArea)
                    { continue; }

                    GameObjectId objectId = InvalidGameObjectId;
                    for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
                    {
                        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
                        //如果是怪物并且离自己4步以内
                        //则将怪物视野置为警戒视野
                        if ( pChar == NULL /*|| IsDistanceLess( GetTileX(), GetTileY(), pChar->GetTileX(), pChar->GetTileY(), 4) */)
                        { continue; }

                        if ( pChar->IsMonster() || pChar->IsPlayer() )
                        { pChar->DecEnmity( GetID(), 0xFFFFFFFF); }
                    }
                }
            }                    
        }

        //if( GetHP() != GetHPMax() )
        //{ RestoreHPInstant(GetHPMax()); }

        //if( GetMP() != GetMPMax() )
        //{ RestoreMPInstant(GetMPMax()); }

        if ( m_bIsFighting )
        {
            if ( endPassiveTimeConfig != -1)
            { // 有时间参数
                _endPassiveTimeRecord = HQ_TimeGetTime(); 
            }
            else
            { // 没时间参数
                _endPassiveTimeRecord = 0;                 
                SetPassiveAttack( bPassiveConfig ); // 马上恢复
            }

            m_bIsFighting = false;
            TryChangeFightState( m_bIsFighting, eFighting );
        }
        ThinkRouteMove();
    }
}

void NpcFight::ThinkRouteMove()
{
    // 没有移动能力
    if ( !IsHaveMoveAbility() )
    { return; }

    bool bNeedCallMove = false;
    SMovePos* pMovePos = NULL;  // 定义一个路点指针

    if ( !IsBeginPosMove() )
    {  // 如果没有到达目标点/目的地
        SMovePos* pMovePos = GetBeginPos(); // 得到初始路点
        if ( pMovePos == NULL )
        {
            _bFinalArrive = true;
            _bArriveTargetPos = true;
            return; 
        }

        _moveTargetPos.x = pMovePos->fX;
        _moveTargetPos.y = pMovePos->fY;
        _moveTargetPos.z = pMovePos->fZ;

        bNeedCallMove = true;
    }
    else if ( _bArriveTargetPos )
    { // 如果到了目标点设置下一个目标点
        if ( !_bFinalArrive )
        { // 还没有到达终点
            // 处理上一轮的结果
            if ( lastIdleX != 0 )   // 上一次未被攻击的位置
            { // 追击前的位置不为0 表示到达追击前的位置
                ClearOutOfRouteRecord();
                pMovePos = GetMovePos( 0 ); // 到达了追击的位置，则返回被引出去的初始点
            }
            else
            {
                pMovePos = GetMovePos( 1 ); // 得到下一个路点
            }

            // 开始下一轮的命令
            if ( pMovePos == NULL ) // 路点信息为空，表示已经到达了终点
            { // 到达终点
                _bFinalArrive = true;
                return; 
            }
            _moveTargetPos.x = pMovePos->fX;
            _moveTargetPos.y = pMovePos->fY;
            _moveTargetPos.z = pMovePos->fZ;

            bNeedCallMove = true;            
        }
        else
        { // 在终点
            if ( _bOutOfRoute )
            { // 被引出去了
                // 触发行为
                _moveTargetPos.x = lastIdleX;
                _moveTargetPos.y = lastIdleY;
                _moveTargetPos.z = GetFloatZ();

                _bOutOfRoute  = false;
                bNeedCallMove = true;
            }
            else
            { // 回到终点了
                // 处理上一轮结果
                if ( lastIdleX != 0 )
                { ClearOutOfRouteRecord(); }
            }
        }
    }
    else if ( !_bArriveTargetPos )
    { // 如果还没到设定的目标路点 同时离开过指定路线 (被人引出去) 拿当前的点
        if ( _bOutOfRoute )
        {
            if ( !_bFinalArrive)
            { // 还没有到终点
                SMovePos* pMovePos = GetMovePos( 0 );
                if ( pMovePos == NULL )
                { return; }

                D3DXVECTOR3 vAttackDistance( lastIdleX - GetFloatX(), lastIdleX - GetFloatY(), 0);
                D3DXVECTOR3 vRouteDistance( pMovePos->fX - GetFloatX(), pMovePos->fY - GetFloatY(), 0);
                float fAttackDistance = D3DXVec3Length( &vAttackDistance);
                float fRoutekDistance = D3DXVec3Length( &vRouteDistance);
                if ( fAttackDistance < fRoutekDistance )
                {
                    _moveTargetPos.x = lastIdleX;
                    _moveTargetPos.y = lastIdleY;
                    _moveTargetPos.z = GetFloatZ();
                }
                else
                {
                    _moveTargetPos.x = pMovePos->fX;
                    _moveTargetPos.y = pMovePos->fY;
                    _moveTargetPos.z = pMovePos->fZ;

                    // 置最新的保持点
                    lastIdleX = pMovePos->fX;
                    lastIdleY = pMovePos->fY;
                }
            }
            else
            { // 直接给IdleX的位置
                _moveTargetPos.x = lastIdleX;
                _moveTargetPos.y = lastIdleY;
                _moveTargetPos.z = GetFloatZ();
            }

            _bOutOfRoute = false;
            bNeedCallMove = true;
        }
    }

    if ( !bNeedCallMove )
    { return; }

    _bArriveTargetPos = false;
    _isNeedMove       = true;

    // 确保附近有玩家才发送,以提高性能
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerMovingToPos msg;
        msg.SetLevel( level_normal ); // 设置中等优先级
        msg.header.stID = GetID();
        msg.vStartPos.x = GetFloatX();
        msg.vStartPos.y = GetFloatY();
        msg.vStartPos.z = GetFloatZ();
        msg.vEndPos = _moveTargetPos;
        GettheServer().SendMsgToView( &msg, GetID(), true);
    }

    m_vLastSendTargetPos.x = GetFloatX();
    m_vLastSendTargetPos.y = GetFloatY();
}

void NpcFight::MoveAttackMoving( uint32 lapseTime )
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if( NULL == pTarget || GetMapID() != pTarget->GetMapID() || pTarget->IsDead())
    {
        LostAttackTarget();
        return;
    }

    D3DXVECTOR3 dir;
    if ( IsHaveMoveAbility() )
    {
        D3DXVECTOR3 vTargetPos;
        
        vTargetPos.x = pTarget->GetFloatX();
        vTargetPos.y = pTarget->GetFloatY();
        vTargetPos.z = 0;

        D3DXVECTOR3 vecDistance( vTargetPos.x - GetFloatX(), vTargetPos.y - GetFloatY(), 0 );
        float fDist = D3DXVec3Length( &vecDistance );
        D3DXVec3Normalize( &dir, &vecDistance );

        if( m_bClosingToTarget )
        { // 需要靠近目标
            float fRange = pTarget->GetBodySize() + GetBodySize();
            float fMoveStep = GetMoveSpeed()*((float)lapseTime * 0.001);
            if( fRange <= 0.001f )
            { fRange = 0.001f; }

            if( fDist > fRange )
            { // 是否需要移动
                if( fMoveStep >= (fDist - fRange) )
                { // 这次移动大于需要移动的距离
                    fMoveStep = fDist - fRange;
                    m_bMoving = false;
                }
                else
                {   
                    m_bMoving = true;
                }

                SetFloatXF( GetFloatX() + fMoveStep * dir.x );
                SetFloatYF( GetFloatY() + fMoveStep * dir.y );
                SetDirX( dir.x );
                SetDirY( dir.y );
            }
            else
            {
                m_bMoving = false;
            }
        }
        else
        { // 不需要靠近目标
            m_bMoving = false;
        }
    }

    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime,1000 ) )
    {
        if( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001  ) // 当前速度 != Normal速度
        { ChangeMoveSpeed( m_fNormalMoveSpeed ); }  // 设置移动速度为Normal速度

        theGameWorld.OnRefreshNewArea( GetID() );

        if( m_bMoving )
        { // 移动中
            D3DXVECTOR3 vCusPos( GetFloatX(), GetFloatY(), WORLD_HEIGHT );                                
            SendClosingToTarget( pTarget->GetID(), vCusPos );
        }
        else
        { // 不动的时候
            if ( IsHaveMoveAbility() )
            { // 有移动能力的才转向
                SetDirX( dir.x );
                SetDirY( dir.y );
            }
            SendVerifyPos( GetFloatX(), GetFloatY() );
        }

        m_dwSendMoveMessageTime = theGameWorld.g_dwLastWorldProcessTime;
    }
}

void NpcFight::MovePosMoving( uint32 lapseTime )
{
    // 没有攻击目标
    if( _isNeedMove )
    {
        D3DXVECTOR3 vecDistance( _moveTargetPos.x - GetFloatX(), _moveTargetPos.y - GetFloatY(), 0 );
        float fDist = D3DXVec3Length( &vecDistance );

        D3DXVECTOR3 vDir;
        D3DXVec3Normalize( &vDir, &vecDistance );

        float fActualMoveDist = GetMoveSpeed() * ( 0.001 * lapseTime );
        if( fActualMoveDist >= fDist )
        {
            fActualMoveDist   = fDist;
            m_bMoving         = false;
            _isNeedMove       = false;
            _bArriveTargetPos = true;
        }
        else
        {
            m_bMoving = true;
        }

        if ( fDist <= 1.f)  // 如果距离下一个点 < 1.0 ，认为已经到了下一个点，否则会动作顿一下
        { // 提前置
            _bArriveTargetPos = true;
        }

        SetDirX( vDir.x );
        SetDirY( vDir.y );
        SetFloatXF( GetFloatX() + fActualMoveDist * vDir.x );
        SetFloatYF( GetFloatY() + fActualMoveDist * vDir.y );
    }
    else
    {
        m_bMoving = false;
    }

    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 2000 ) )
    { // 移动消息频率 更新用 比如GateServer热起
        // 如果当前速度 != Idle速度， 同时已经回到了被引出去的点
        if ( abs( GetCharFightAttr()->moveSpeed.base - m_fIdleMoveSpeed ) >= 0.0001 && lastIdleX == 0 && lastIdleY == 0 )
        { ChangeMoveSpeed( m_fIdleMoveSpeed ); }

        theGameWorld.OnRefreshNewArea( GetID() );

        if ( AreaHavePlayer() )
        {
            if ( m_bMoving )
            {
                // 在移动中
                MsgUnPlayerMovingToPos msg;                    
                msg.header.stID = GetID();
                msg.vStartPos.x = GetFloatX();
                msg.vStartPos.y = GetFloatY();
                msg.vStartPos.z = WORLD_HEIGHT;
                msg.vEndPos     = _moveTargetPos;
                GettheServer().SendMsgToView( &msg, GetID(), true );
            }
            else
            { // 两秒再两秒
                if ( GameTime::IsPassCurrentTime( m_noMoveSendVerifyPosTime, 4000 ) )
                { 
                    SendVerifyPos( GetFloatX(), GetFloatY() ); 
                    m_noMoveSendVerifyPosTime = HQ_TimeGetTime();
                }
            }
        }
        m_dwSendMoveMessageTime = HQ_TimeGetTime();
    }
}

void NpcFight::AITryAttack()
{
    if( HaveTask() )
    { return; }

    if( !HaveCanAttackCharId() )
    {
        _disableControlThinkTime = true;
        return;
    }

    BaseCharacter *pTarget = GetCanAttackChar();
    if( pTarget == NULL || !IsCanAttack( pTarget ) )
    {
        LostAttackTarget();
        pTarget = NULL;
        _disableControlThinkTime = true;
        return;
    }

    if( pTarget->IsDead() )
    {
        LostAttackTarget();
        pTarget = NULL;
        _disableControlThinkTime = true;
        return;
    }

    
    if( !CheckUseSkillPreconditionState() )
    { return; }

    int nSkillIndex = GetCurSkillIndex();    
    if (nSkillIndex < 0 || nSkillIndex >= AI_MONSTERMAXSKILLNUM)
    { return; }

    if( theGameWorld.g_dwLastWorldProcessTime - skillInfo[nSkillIndex].m_dwSkillStartColdDownTime > skillInfo[nSkillIndex].m_dwSkillColdDownTime && IsInAttackRange( pTarget,  m_pCurSkill ) )
    {
        skillInfo[nSkillIndex].m_dwSkillStartColdDownTime = theGameWorld.g_dwLastWorldProcessTime;
        AIAttack( GetCanAttackCharId(), GetCurSkill(),  GetCurSkillLevel() );
    }
    else
    {
        _disableControlThinkTime = true;
    }

    pTarget = NULL;
}

void NpcFight::AddTask( AiBaseTask* pTask )
{
    if( m_vecNormalTask.size() >= 5 )
    { return; }

    switch (pTask->PL())
    {
    case AiBaseTask::EPL_LOW:
        break;
    case AiBaseTask::EPL_NORMAL:
        m_vecNormalTask.push_back(pTask);
        break;
    case AiBaseTask::EPL_HIGH:
        break;
    }
}

void NpcFight::ClearTask()
{
    while (!m_vecNormalTask.empty())
    {
        AiBaseTask *pTask = m_vecNormalTask.back();
        m_vecNormalTask.pop_back();
        pTask->Release();
        pTask = NULL;;
    }
}

void NpcFight::AIAttack( int iTarget, int iSkill, int iLevel )
{
    AiNormalAttackTask* pAttack = AiNormalAttackTask::CreateInstance();
    if ( pAttack )
    {
        pAttack->PL( AiBaseTask::EPL_NORMAL );
        pAttack->SetAttackTarget( iTarget );
        pAttack->SetSkill( iSkill, iLevel );
        AddTask( pAttack );
    }
}

void NpcFight::AITryUseSkill()
{
    if( !HaveCanAttackCharId() )
    { return; }

    BaseCharacter *pTarget = GetCanAttackChar();
    if( pTarget == NULL || pTarget->IsDead())
    { return; }

    if( !CheckUseSkillPreconditionState() )
    { return; }

    int nSkillIndex = GetCurSkillIndex();
    if (nSkillIndex < 0 || nSkillIndex >= AI_MONSTERMAXSKILLNUM)
    { return; }

    if( theGameWorld.g_dwLastWorldProcessTime - skillInfo[nSkillIndex].m_dwSkillStartColdDownTime > skillInfo[nSkillIndex].m_dwSkillColdDownTime && IsInAttackRange( pTarget,  m_pCurSkill ) )
    {
        skillInfo[nSkillIndex].m_dwSkillStartColdDownTime = theGameWorld.g_dwLastWorldProcessTime;
        AIAttack( GetCanAttackCharId(), GetCurSkill(),  GetCurSkillLevel() );
    }

    SetCurSkillIndex( 0 );
    SetCurSkillLevel( 0 );
    CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( GetCurSkill(), GetCurSkillLevel() );
    if ( !pSkill )
    { return; }

    m_pCurSkill        = pSkill;
    m_stCurAttackRange = pSkill->fRangeCanCast;

    m_stCurAiTactic = EAISelectTaskType_TryAttackTarget;
    pTarget = NULL;
}

SMovePos* NpcFight::GetBeginPos()
{
    _routeStep = 0;

    if ( _routeStep >= _route.allMovePos.size() )
    { return NULL; }

    return &_route.allMovePos[ _routeStep ];
}

SMovePos* NpcFight::GetMovePos( uint8 step )
{// 先从正方向，然后取负，从反方向取
    _routeStep += step;
    if ( _routeStep >= _route.allMovePos.size() )
    {
        //return NULL; 
        _routeStep = 0; // 清空步伐，策划配的路点是一个圈
    }
    return &_route.allMovePos[ _routeStep ];
}

void NpcFight::SetSkillColdDown()
{
    for( int i=0; i<ECD_SkillInfoMaxSize; ++i )
    {
        CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( skillInfo[i].m_iSkillId, skillInfo[i].m_stSkillLevel );
        if( NULL == pSkill)
        { continue; }

        skillInfo[i].m_dwSkillStartColdDownTime = 0;
        skillInfo[i].m_dwSkillColdDownTime = pSkill->dwSkillCoolDownTime;
    }
}
