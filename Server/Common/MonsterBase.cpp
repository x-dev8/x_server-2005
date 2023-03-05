#include "MonsterBase.h"
#include "GlobalDef.h"
#include "GameWorld.h"
#include "ShareData.h"
#include "ScriptVM.h"
#include "FuncPerformanceLog.h"
#include "Configure.h"
#include "ItemCharacter.h"
#include "ErrorLog.h"
#include "DropItemManager.h"
#include "AiBaseTask.h"
#include "AiNormalAttackTask.h"
#include "XmlStringLanguage.h"
#include "TeamManager.h"
#include "GamePlayer.h"
#include "RouteManager.h"
#include "CampBattleDefine.h"
#include "NpcFight.h"
#include "CampBattleControl.h"
#include "CampBattle.h"
#include "GameParthFinder.h"
#include "D3DFunction.h"

const DWORD dwVerifyPosTimeDelay = 1000;        //每次更新位置时间

SProcessTime aiusetime[200];

int SAiInfo::GetCurrentSelectSkillIndex()
{
    // 宠物默认都是使用0下标的技能[普通攻击]。特别指定的技能用1下标位    
    if ( m_bMustUseSkill[1] )
    { return 1; }

    if ( m_bMustUseSkill[2] )
    { return 2; }

    return 0;
}

int32 SAiInfo::GetCurrentSelectSkillId()
{
    return m_iSkillId[ GetCurrentSelectSkillIndex() ];
}

int32 SAiInfo::GetCurrentSelectSkillLevel()
{
    return m_stSkillLevel[ GetCurrentSelectSkillIndex() ];
}
//////////////////////////////////////////////////////////////////////////
// class MonsterBase
MonsterBase::MonsterBase() : m_LuaScript( false )
{   
    _buffManager.CreateFromData( _buffs, BodyStatusType_Max );
    bPassiveConfig            = false; // 是否被动怪
    changePassiveConfig       = 0;     // 战斗时是否被动怪
    endPassiveTimeConfig      = -1;    // 战斗结束被动持续时间
    m_nBaseEnmityRange        = -1;    // 基础仇恨持续范围
    m_dwFightViewEndTime      = 0;
    m_bIsFighting             = false;
    m_nVMId                   = -1;
    m_bAIStartUp              = false;
    m_stCurAiTactic           = EAISelectTaskType_None;
    m_nThinkingTime           = 0;
    m_nAiValueWave            = 0;    
    _isNeedMove               = false;
    m_fNormalMoveSpeed        = 0.0f;
    m_fIdleMoveSpeed          = 0.0f;    
    m_stCurAttackRange        = 1;
    _disableControlThinkTime  = false;
    m_pCurSkill               = NULL;
    m_ustSkill2HPLowerLimit   = 0;
    m_ustSkill2MPLowerLimit   = 0;
    m_ustSkill3HPLowerLimit   = 0;
    m_ustSkill3MPLowerLimit   = 0;
    m_bSkill2Restore          = false;
    m_bSkill3Restore          = false;
    m_stIdleMoveRate          = 1;
    m_stFightViewSight        = 1;
    m_stIdleMoveViewSight     = 0;
    m_stMonsterType           = 0;
    m_bLuaScriptLoaded        = false;
    m_iCurSkillId             = ErrorUnsignedShortID;
    m_nCurSkillIndex          = 0;
    m_stCurSkillLevel         = -1;
    m_nMonsterId              = -1;
    m_shProfession            = 0;
    m_dwStartTime             = 0;
    m_dwTimeStep              = 0;
    m_bTimerActive            = false;
    m_dwSendMoveMessageTime   = 0;
    m_noMoveSendVerifyPosTime = 0;
    _tryToAttackCharEnmity    = 0;
    _tryToAttackCharId        = InvalidGameObjectId;
    m_vLastSendTargetPos      = D3DXVECTOR3(0,0,0);
    _summonMasterId          = -1;
    ClearAskToAttackTargetId();
    m_bClosingToTarget        = false;
    m_ushDirUnChangedCount    = 0;
    m_n9AreaPlayerCnt         = 0;
    _protectCharId            = -1;
    _protectCharVarId         = -1;    
    m_dwSpecialID             = 0;
    _bPet                     = false;
    _fAttackPhysicsMod        = 0.0f;
    _fDefendPhysicsMod        = 0.0f;
    _fAttackMagicMod          = 0.0f;
    _fDefendMagicMod          = 0.0f;
    m_bCityDefMonster         = false;
    m_bCityMonster            = false;
    _bNeedFollowSummonMaster  = true;
    m_bMoving                 = false;
    m_nCashMoney              = 0;

    memset( m_nArray        , 0, sizeof(m_nArray)        );
    memset( m_bArray        , 0, sizeof(m_bArray)        );
    memset( m_Timer         , 0, sizeof(m_Timer)         );
    memset( &_moveTargetPos,  0, sizeof(_moveTargetPos ) );
}                             
                              
MonsterBase::~MonsterBase()
{ 
    ClearTask();
    try
    { m_LuaScript->PushNil(); }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "Monster %s AI Failed: %s", GetCharName(), e.GetErrorMessage());
        m_bLuaScriptLoaded = false;
    }
}

void MonsterBase::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
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

bool MonsterBase::ProcessMsg( Msg* pMsg )
{
    // 基本消息处理
    DWORD dwType = pMsg->GetType();

    // 如果接到了自己被销毁，那就再也不能执行任何任务
    if( dwType == MSG_EXIT )
    {
        OnExit( pMsg );
        return false;
    }
    return true;
}

void MonsterBase::OnExit( Msg* pMsg, unsigned char exitType )
{
    GameObjectId stID = GetID();

    // 确保附近有玩家才发送,以提高性能
    if ( AreaHavePlayer())
    { GettheServer().SendMsgToView( pMsg, GetID(), false ); }

    theGameWorld.OnDelCharacter ( stID ); // 从场景中删掉
    theRunTimeData.ReleaseObject( stID ); // 从释放回内存池
}

void MonsterBase::OnDeath()
{
	// 检测寻路配置变化
	CheckFindParthConfigChange();

    MsgSawSomeoneDead msg;
    msg.header.stID = GetID();

    if (IsMonster() && AreaHavePlayer() )
    { GettheServer().SendMsgToView( &msg, GetID(), true );}

    // 清空所有仇恨列表
    RemoveAllEnmityList( GetID() );

    // 掉落物品 如果是召唤怪, 只有被别人杀死才能掉落物品
    //!( IsSummonMonster() && GetKiller() != NULL && GetKiller()->GetID() == m_SummonMasterID )

    // 如果不是召唤物 或者 是召唤物是(骠车)同时是被敌人杀死
    if ( !IsSummonMonster() || ( GetPetType() == EPT_Protect && GetKiller() != NULL && GetKiller()->GetID() != GetSummonMasterID() ) )
    {
        GetDropItemManager().MonsterDeath( this, GetKiller() );
    }

    if ( IsSummonMonster() && IsPet() ) 
    { // 有召唤主人
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( pMaster && pMaster->IsPlayer() )
        {
            GamePlayer* pGamePlayerMaster = (GamePlayer*)pMaster;
            switch( GetPetType() )
            {
            case EPT_Skill:                
                pGamePlayerMaster->LostSummonPet( GetID() );
                break;
            case EPT_Capture:
                pGamePlayerMaster->LostCapturePet();
                break;
            case EPT_Nurture:
                pGamePlayerMaster->_petManager.LostActivePet( true );
                break;
            }
        }
    }

    if( HaveProtectChar() && !IsPet() )
    { // 如果是被保护的对象
        BaseCharacter* pProtectChar = theRunTimeData.GetCharacterByID( _protectCharId );
        if( pProtectChar && pProtectChar->IsPlayer())
        {
            GamePlayer* pProtectPlayer = (GamePlayer*)pProtectChar;
            pProtectPlayer->LostProtectChar();

            if ( _protectCharVarId != -1)
            { pProtectPlayer->SetVar( _protectCharVarId, 0 ); }
        }
    }

    // 调用死亡脚本 捕抓怪不掉脚本
    if ( !IsSummonMonster() || GetPetType() != EPT_Capture ) 
    { CallDeadScript(); }       

    ProcessCampMonsterDeath();

    // 设置死亡
    SetStatus( CS_DIEING );

    // 不能直接调用exit函数 否则怪物死亡不能播放死亡动作
    ExitWorldByPushMsg();
    //ExitWorld();
}

void MonsterBase::BeattackedCallBack(GameObjectId nAttackerID, int nSkillID, int nSkillLevel, int nDamage)
{
    if( m_bLuaScriptLoaded )
    {
        try
        {
            LuaObject luaobject = m_LuaScript->GetGlobal("Event_Beattacked");
            if(luaobject.IsFunction())
            {
                GetGlobalFun("Event_Beattacked")(nAttackerID, nSkillID, nSkillLevel, nDamage);
            }
        }
        catch (LuaPlus::LuaException &e)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI Script Event_Beattacked Failed: %s", GetCharName(), e.GetErrorMessage());
            m_bLuaScriptLoaded = false;
        }
    }
}

void MonsterBase::EnterMySight( BaseCharacter* pWho )
{ // 以九工格为准的视野(进入九工格就表示进入怪物的视野)
    if( !pWho || IsDead())
    { return; }
    
    if ( pWho->IsPlayer() )
    {
        if ( !AreaHavePlayer())
        { StartUpAI();}
        ++m_n9AreaPlayerCnt;
#ifdef _DEBUG
        if ( m_n9AreaPlayerCnt>= 2)
        { int a = 0; }
#endif
    }
    else if ( pWho->IsMonster() )
    {
        MonsterBase* pMonsterBase = (MonsterBase*)pWho;
        if ( pMonsterBase->IsSummonMonster() )
        {
            if ( !AreaHavePlayer() )
            { StartUpAI(); }
            ++m_n9AreaPlayerCnt;
        }
        else
        {
            bool bCanAddEnmity = true;

            // 不吸无战斗属性的怪
            if ( !pMonsterBase->IsNeedFightMonster() )
            { bCanAddEnmity = false;  }

            // 当有阵营的时候 不吸同阵营仇恨
            if ( ( pMonsterBase->HaveFightCamp()|| HaveFightCamp() ) && pMonsterBase->GetFightCamp() == GetFightCamp() )
            { bCanAddEnmity = false; }

            if( bCanAddEnmity )
            { AddEnmityList(pWho->GetID());}
        }
    }
}

void MonsterBase::ExitMySight( BaseCharacter* pWho )
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
        OnExitMySightNoPlayer();
    }
}

void MonsterBase::OnExitMySightNoPlayer()
{
    // 在此回满血
    if ( !IsDead())
    {
        if( GetHP() != GetHPMax() )
        { RestoreHPInstant(GetHPMax()); }

        if( GetMP() != GetMPMax() )
        { RestoreMPInstant(GetMPMax()); }
    }
    
    m_bAIStartUp = false;
}

Msg* MonsterBase::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{
    BaseCharacter::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pMsg = (MsgNPCEnterMySight*)szMsgBuffer;

    pMsg->stCharType    = Object_Monster;
    pMsg->stMonsterType = GetMonsterType();
    if( IsSummonMonster() )
    {
        pMsg->stMasterId = GetSummonMasterID();
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( pMaster != NULL && pMaster->IsPlayer() )
        { strncpy_s( pMsg->szDisplayName, pMaster->GetCharName(), sizeof( pMsg->szDisplayName ) - 1); }

        if ( Object_MonsterNurturePet == GetObjType() )
        {
            MonsterNurturePet* pNurturePet = static_cast< MonsterNurturePet * > ( this ) ;
            strncpy_s( pMsg->szTitleName, pNurturePet->GetTitleName(), sizeof( pMsg->szTitleName ) - 1);
        }
    }
    pMsg->stId = GetMonsterId();
    return pMsg;
}

void MonsterBase::CallDeadScript() 
{
    BaseCharacter* pKiller = GetKiller();
    if ( !pKiller || !pKiller->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pKiller;
    const char *szScriptName = GetDeadScript();

    if( !szScriptName || szScriptName[0] == 0 )
    { return; }

    if ( m_nVMId == -1 )
    { m_nVMId = GetScriptMgr()->CreateVM( ST_MONSTER_DEAD, szScriptName, GetMonsterId() ); }

    if ( m_nVMId == -1 )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Call monster dead script failed: %s", szScriptName );
        return;
    }
    GetScriptMgr()->StartupVM( ST_MONSTER_DEAD, GetMonsterId(), pPlayer , false, 1, GetID() );
}

void MonsterBase::Run(DWORD dwCostTime)
{
    aiusetime[0].szFunctionName = "MonsterBase::Run";
    __int64 time = HelperFunc::GetCPUTime();
    
    if ( !IsNeedFightMonster() )
    { // 植物建筑物
        // 处理消失
        if ( m_xDisappearTimer.DoneTimer() )
        { Exit(); }

        aiusetime[1].szFunctionName = "BaseCharacter::Run";
        __int64 funtime = HelperFunc::GetCPUTime();
        BaseCharacter::Run( dwCostTime );

        aiusetime[1].nTime += (HelperFunc::GetCPUTime() - funtime);
    }
    else
    {
        __int64 funtime = 0;

        // 如果Ai没有启动 同时不是一定要开AI 同时不是所有AI都要开启
        if ( m_bAIStartUp || MustOpenAI() || g_Cfg.iAllAIOpen )
        {
            if ( !IsDead() )
            { // 没有死的的时候
                // 思考与Timer
                aiusetime[2].szFunctionName = "MonsterBase->Thinking";
                funtime = HelperFunc::GetCPUTime();
                ProcessAIThink();
                ProcessAITimer();
                aiusetime[2].nTime += (HelperFunc::GetCPUTime() - funtime);

                // 行动选择
                aiusetime[3].szFunctionName = "MonsterBase->Doing";
                funtime = HelperFunc::GetCPUTime();
                ProcessAISelectTask();
                aiusetime[3].nTime += (HelperFunc::GetCPUTime() - funtime);

                // 处理AI移动
                aiusetime[4].szFunctionName = "MonsterBase->AIMove";
                funtime = HelperFunc::GetCPUTime();
                ProcessAIMove(dwCostTime);
                aiusetime[4].nTime += (HelperFunc::GetCPUTime() - funtime);

                // AI状态处理（根据人物进行等待还是做已经下发的的任务）
                aiusetime[5].szFunctionName = "MonsterBase->Process";
                funtime = HelperFunc::GetCPUTime();
                ProcessAIDoTask();
                aiusetime[5].nTime += (HelperFunc::GetCPUTime() - funtime);

                // 宠物的仇恨吸引刷新
                aiusetime[6].szFunctionName = "MonsterBase->RefreshEnmity";
                funtime = HelperFunc::GetCPUTime();
                switch ( GetObjType())
                {
                case Object_MonsterPet:
                case Object_MonsterRoute:
                case Object_MonsterNurturePet:
                    {
                        RefreshEnmity(); 
                    }
                    break;
                }
                aiusetime[6].nTime += (HelperFunc::GetCPUTime() - funtime);
            }
        }
        
        aiusetime[1].szFunctionName = "BaseCharacter::Run";
        funtime = HelperFunc::GetCPUTime();
        BaseCharacter::Run(dwCostTime);        
        aiusetime[1].nTime += (HelperFunc::GetCPUTime() - funtime);

        funtime = HelperFunc::GetCPUTime();
        aiusetime[0].nTime += (HelperFunc::GetCPUTime() - time);
    }
}

bool MonsterBase::MasterOutOfTarget(BaseCharacter* Master,BaseCharacter *Target, float distance)
{
    if (NULL == Master|| NULL == Target)
        return true;

    float Xoff = Master->GetFloatX() - Target->GetFloatX();
    float Yoff = Master->GetFloatY() - Target->GetFloatY();

    float fDis = Xoff*Xoff + Yoff*Yoff ;

    if( fDis > distance*distance)
        return true;

    return false;
}

void MonsterBase::MAlarmWhenBeAttack()
{
    int nAreaID = GetCurArea();
    GameStage* pGameStage = theGameWorld.GetStageById( GetMapID() );
    if ( pGameStage == NULL )
    { return; }

    AreaIndexTPL(Area9) list;
    pGameStage->Get9AreaList(list, nAreaID);
    int nCount = list.Count();
    for (int i=0; i<nCount; i++)
    {
        GameArea* pArea = pGameStage->GetArea(list[i]);
        if ( pArea == NULL )
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if ( pChar == NULL || !pChar->IsMonster() || !IsDistanceLess(GetTileX(), GetTileY(), pChar->GetTileX(), pChar->GetTileY(), GetIdleMoveViewSight()) )
            { continue; }

            MonsterBase* pAiChar = static_cast<MonsterBase*>(pChar);

            //设置好怪物战斗视野以及战斗视野结束时间(目前程序内写死2秒后视野恢复)
            pAiChar->SetViewSight( pAiChar->GetFightViewSight() );
            pAiChar->SetFightViewEndTime( HQ_TimeGetTime() );
        }
    }
}
void MonsterBase::ProcessAIThink()
{
    if ( !_disableControlThinkTime )
    { // 需要控制思考频率
        if ( IsSummonMonster() )
        {
            if( !GameTime::IsPassCurrentTime( GetAiData()->m_dwLastThinkingTime, m_nAiValueWave)  )
            { return; }
            m_nAiValueWave = 200; 
        }
        else
        {
            if( !GameTime::IsPassCurrentTime( GetAiData()->m_dwLastThinkingTime, m_nThinkingTime + m_nAiValueWave) )
            { return; }
            m_nAiValueWave = theRand.rand32() % 1000; 
        }        
        GetAiData()->m_dwLastThinkingTime = HQ_TimeGetTime();
    }
    else
    {
        _disableControlThinkTime = false;
        GetAiData()->m_dwLastThinkingTime = HQ_TimeGetTime();
    }

    if ( m_xDisappearTimer.DoneTimer() )
    { // 消失逻辑
        Exit();
        return;
    }

    // 可视距离
    if (m_dwFightViewEndTime != 0 && GameTime::IsPassCurrentTime( m_dwFightViewEndTime, 2000 ) )
    {
        SetViewSight( GetIdleMoveViewSight());
        m_dwFightViewEndTime = 0;
    }

    // 回调
    OnThink();
}

void MonsterBase::ProcessAITimer()
{
    //如果没有载入Lua脚本则不需要执行这个函数
    if (!m_bLuaScriptLoaded)
    { return; }

    for ( uint32 i=0; i<AI_MAXTIMER; ++i)
    {
        if (m_Timer[i].dwStartTime != 0 && m_Timer[i].wCount != 0 && GameTime::IsPassCurrentTime( m_Timer[i].dwStartTime, m_Timer[i].dwDelay ))
        {
            m_Timer[i].dwStartTime = HQ_TimeGetTime();
            if (m_Timer[i].wCount != 0xFFFF)
            { m_Timer[i].wCount--; }

            if (m_Timer[i].wCount == 0)
            { m_Timer[i].dwStartTime = 0; }

            try
            {
                LuaObject luaobject = m_LuaScript->GetGlobal("Event_OnTimer");
                if(luaobject.IsFunction())
                { 
                    LuaFunction<int> fun(luaobject);
                    fun(i, m_Timer[i].wCount);
                }
            }
            catch (LuaPlus::LuaException &e)
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script Event_OnTimer failed: %s", GetCharName(), e.GetErrorMessage() );
                m_bLuaScriptLoaded = false;
            }
        }
    }
}

void MonsterBase::ProcessAISelectTask()
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

void MonsterBase::ProcessAIDoTask()
{
    //先执行优先级高的任务
    while (!m_vecHighTask.empty())
    {
        AiBaseTask* pTask = m_vecHighTask.back();
        m_vecHighTask.pop_back();

        pTask->ExecuteTask( this );
        pTask->Release();
    }

    while (!m_vecNormalTask.empty())
    {
        AiBaseTask* pTask = m_vecNormalTask.back();
        m_vecNormalTask.pop_back();

        pTask->ExecuteTask( this );
        pTask->Release();
    }

    while (!m_vecLowTask.empty())
    {
        AiBaseTask* pTask = m_vecLowTask.back();
        m_vecLowTask.pop_back();

        pTask->ExecuteTask( this );
        pTask->Release();
    }
}

void MonsterBase::ProcessAIMove( DWORD dwCostTime )
{
    short shMonsterType = GetMonsterType();
    if( shMonsterType == eMT_Building || IsDead() || !_buffManager.IsCanMove() )
    { return; }

    OnMove( dwCostTime );
}

void MonsterBase::AddTask( AiBaseTask *pTask )
{
    if( (m_vecLowTask.size() + m_vecNormalTask.size() + m_vecHighTask.size()) >= GetAiData()->m_sizeTaskList )
    { return; }

    switch (pTask->PL())
    {
    case AiBaseTask::EPL_LOW:
        m_vecLowTask.push_back(pTask);
        break;
    case AiBaseTask::EPL_NORMAL:
        m_vecNormalTask.push_back(pTask);
        break;
    case AiBaseTask::EPL_HIGH:
        m_vecHighTask.push_back(pTask);
        break;
    }
}

void MonsterBase::ClearTask()
{
    while (!m_vecHighTask.empty())
    {
        AiBaseTask *pTask = m_vecHighTask.back();
        m_vecHighTask.pop_back();
        pTask->Release();
        pTask = NULL;;
    }

    while (!m_vecNormalTask.empty())
    {
        AiBaseTask *pTask = m_vecNormalTask.back();
        m_vecNormalTask.pop_back();
        pTask->Release();
        pTask = NULL;;
    }

    while (!m_vecLowTask.empty())
    {
        AiBaseTask *pTask = m_vecLowTask.back();
        m_vecLowTask.pop_back();
        pTask->Release();
        pTask = NULL;;
    }
}

BaseCharacter* MonsterBase::GetCanAttackChar() 
{
    if ( !HaveCanAttackCharId() )
    { return NULL; }
    return theRunTimeData.GetCharacterByID( _coreAiData.canAttackCharId );
}

// 设置技能
void MonsterBase::SetSkill(int index, int skill_id) 
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d下标越界", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_iSkillId[index] = skill_id;
}

// 设置技能等级
void MonsterBase::SetSkillLevel( int index, short skilllevel )
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d下标越界", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_stSkillLevel[index] = skilllevel;
}

// 设置技能使用概率
void MonsterBase::SetSkillRate( int index, short skillrate )
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d下标越界", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_stSkillRate[index] = skillrate;
}

// 设置随机会要用的总技能概率
void MonsterBase::SetSkillRateTotal()
{
    GetAiData()->m_stSkillRateTotal = GetAiData()->m_stSkillRate[0] + GetAiData()->m_stSkillRate[1] + GetAiData()->m_stSkillRate[2];
    GetAiData()->m_stSkillRate[1] = GetAiData()->m_stSkillRate[1] + GetAiData()->m_stSkillRate[0];
    GetAiData()->m_stSkillRate[2] = GetAiData()->m_stSkillRate[2] + GetAiData()->m_stSkillRate[1];
}

void MonsterBase::SetCurSkillIndex( int i )
{
    m_iCurSkillId = GetAiData()->m_iSkillId[i];
    m_nCurSkillIndex = i;
}

int MonsterBase::GetCurSkillIndex()
{
    if( m_nCurSkillIndex >= 0 && m_nCurSkillIndex < 3 )
    { return m_nCurSkillIndex; }

    return 0;
}

// 设置当前使用的技能等级
void MonsterBase::SetCurSkillLevel( uint8 index )
{
    m_stCurSkillLevel = GetAiData()->m_stSkillLevel[index];
}

// 可移动范围
void MonsterBase::SetCanMoveZone( RECT zone )
{
    GetAiData()->m_CanMoveZone = zone;
}

// 设置技能2的HP,MP下限
void MonsterBase::SetSkill2LowLimit()
{
    CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( GetAiData()->m_iSkillId[1], GetAiData()->m_stSkillLevel[1] );

    if(!pSkill)
        return;

    m_ustSkill2HPLowerLimit = pSkill->ustCostHP + pSkill->ustCostHPPer * GetCharFightAttr()->hpMax.final + 1;
    m_ustSkill2MPLowerLimit = pSkill->ustCostMP + pSkill->ustCostMPPer * GetCharFightAttr()->mpMax.final ;

    if ( pSkill->ustDamageBalanceType == CItemDetail::balancetype_restorehpmp )
    { m_bSkill2Restore = true;  }
    else
    { m_bSkill2Restore = false; }

    pSkill = NULL;
}

// 设置技能3的HP,MP下限
void MonsterBase::SetSkill3LowLimit()
{
    CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( GetAiData()->m_iSkillId[2], GetAiData()->m_stSkillLevel[2] );

    if(!pSkill)
        return;

    m_ustSkill3HPLowerLimit = pSkill->ustCostHP + ( pSkill->ustCostHPPer * GetCharFightAttr()->hpMax.final ) + 1;
    m_ustSkill3MPLowerLimit = pSkill->ustCostMP + ( pSkill->ustCostMPPer * GetCharFightAttr()->mpMax.final );

    if ( pSkill->ustDamageBalanceType == CItemDetail::balancetype_restorehpmp )
    {
        m_bSkill3Restore = true;
    }
    else
    {
        m_bSkill3Restore = false;
    }

    pSkill = NULL;
}

void MonsterBase::SetSkillColdDown()
{
    for( int i = 0; i < AI_MONSTERMAXSKILLNUM; i++ )
    {
        CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( GetAiData()->m_iSkillId[i], GetAiData()->m_stSkillLevel[i] );

        if(!pSkill)
            continue;

        GetAiData()->m_dwSkillStartColdDownTime[i] = 0;
        GetAiData()->m_dwSkillColdDownTime[i] = pSkill->dwSkillCoolDownTime;
    }
}

bool MonsterBase::IsSkill2CanUse()
{
    if( theGameWorld.g_dwLastWorldProcessTime - GetAiData()->m_dwSkillStartColdDownTime[1] < GetAiData()->m_dwSkillColdDownTime[1] )
        return false;

    if( GetHP() >= m_ustSkill2HPLowerLimit && GetMP() >= m_ustSkill2MPLowerLimit )
    {
        if( m_bSkill2Restore )
        {
            if( GetHP() < GetCharFightAttr()->hpMax.final / 2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool MonsterBase::IsSkill3CanUse()
{
    if( theGameWorld.g_dwLastWorldProcessTime - GetAiData()->m_dwSkillStartColdDownTime[2] < GetAiData()->m_dwSkillColdDownTime[2] )
        return false;

    if( GetHP() >= m_ustSkill3HPLowerLimit && GetMP() >= m_ustSkill3MPLowerLimit )
    {
        if( m_bSkill3Restore )
        {
            if( GetHP() < GetCharFightAttr()->hpMax.final / 2 )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

//获取可移动范围
RECT MonsterBase::GetCanMoveZone()
{
    return GetAiData()->m_CanMoveZone;
}

// 当前有任务吗？
bool MonsterBase::HaveTask() 
{
    return !( m_vecHighTask.empty() && m_vecNormalTask.empty() && m_vecLowTask.empty() ); 
}

// 如果当前没有目标或是目标不具备职业特征，则返回-1
int MonsterBase::GetAttackTargetPro()
{
    GameObjectId nTargetId = GetCanAttackCharId();
    if (nTargetId != -1)
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nTargetId);
        if (pChar != NULL && pChar->IsPlayer())
        {
            return static_cast<GamePlayer*>(pChar)->GetProfession();
        }
    }
    return -1;
}

bool MonsterBase::IsSkillAttack( BaseCharacter *pChar )
{
    if( pChar == NULL )
        return false;

    int x1 = GetTileX();
    int y1 = GetTileY();
    int x2 = pChar->GetTileX();
    int y2 = pChar->GetTileY();

    CItemDetail::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( GetCurSkill(), GetCurSkillLevel() );
    if( pSkill == NULL )
        return false;

    return IsDistanceLess( x1, y1, x2, y2, pSkill->stDamageEffectDistance );
}

bool MonsterBase::IsAICanAttack( BaseCharacter* pChar )
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

void MonsterBase::DropItemRand( int ItemID, float fRate )
{
    if( theRand.rand32()%100 < fRate )
    {
        DropItem( ItemID, GetFloatX()+theRand.rand32()%3-1, GetFloatY()+theRand.rand32()%3-1 );
    }
}

void MonsterBase::DropItem( int ItemID, float x, float y )
{
    SCharItem item;    
    theRunTimeData.CreateItem( this, ItemID, 1, HelperFunc::CreateID(), item );

    //创建物品
    CItemDetail::SItemCommon* pitem = GettheItemDetail().GetItemByID(ItemID);
    if (!pitem)
        return;

    theGameWorld.CreateItemNpc(pitem->GetItemName(),
        GetMapID(), x, y, 0,
        item, -1, 0, false);
}

void GetOffsetByDir2( int iDir,short &stXOff,short &stYOff )
{
    stXOff = 0;
    stYOff = 0;
    switch( iDir )
    {
    case DIR_0:
        stYOff = - 1;
        break;
    case DIR_45:            
        stXOff = 1,stYOff = - 1;
        break;
    case DIR_90:
        stXOff = 1;
        break;
    case DIR_135:
        stXOff = 1,stYOff = 1;
        break;
    case DIR_180:            
        stYOff = 1;
        break;
    case DIR_225:            
        stXOff = - 1,stYOff = 1 ;
        break;
    case DIR_270:            
        stXOff = - 1;
        break;
    case DIR_315:
        stXOff = - 1,stYOff = - 1;
        break;
    }
}

int GetDirByOffset2( int dx, int dy )
{
    int nDir = DIR_0;
    if( dy < 0 && dx == 0 )
        nDir = DIR_0;
    else if( dx > 0 && dy < 0 )
        nDir = DIR_45;
    else if( dy == 0 && dx > 0 )
        nDir = DIR_90;
    else if( dx > 0 && dy > 0 )
        nDir = DIR_135;
    else if( dx == 0 && dy > 0 )
        nDir = DIR_180;
    else if( dx < 0 && dy > 0 )
        nDir = DIR_225;
    else if( dx < 0 && dy == 0 )
        nDir = DIR_270;
    else if( dx < 0 && dy < 0 )
        nDir = DIR_315;
    return nDir;
}

void MonsterBase::AIAttack( int iTarget, int iSkill, int iLevel )
{
    AiNormalAttackTask* pAttack = AiNormalAttackTask::CreateInstance();
    if ( pAttack )
    {
        pAttack->PL( 1 );
        pAttack->SetAttackTarget( iTarget );
        pAttack->SetSkill( iSkill, iLevel );
        AddTask( pAttack );
    }
}

void MonsterBase::AITryUseSkill()
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

    // 重新置成不需要一定使用的状态
    SetMustUsingSkill( nSkillIndex, false );    

    if( theGameWorld.g_dwLastWorldProcessTime - GetAiData()->m_dwSkillStartColdDownTime[nSkillIndex] > GetAiData()->m_dwSkillColdDownTime[nSkillIndex] && IsInAttackRange( pTarget,  m_pCurSkill ) )
    {
        GetAiData()->m_dwSkillStartColdDownTime[nSkillIndex] = theGameWorld.g_dwLastWorldProcessTime;
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

void MonsterBase::TryUseSkill( int nSkillID, int nSkillLevel )
{
    if( !HaveCanAttackCharId() )
    {
        return;
    }

    BaseCharacter *pTarget = GetCanAttackChar();

    if( pTarget == NULL )
    {
        return;
    }

    if( pTarget->IsDead() )
    {
        return;
    }

    //if( !CheckUseSkillPreconditionState() )
    //{
    //    return;
    //    pTarget = NULL;
    //}

    CItemDetail::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );

    if ( !pSkill )
        return;

    if( IsInAttackRange( pTarget, pSkill ) )
    {
        AIAttack( GetCanAttackCharId(), nSkillID, nSkillLevel );
    }
}

void MonsterBase::AITryAttack()
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

    if ( IsSummonMonster() )        // 自己是召唤物
    {
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( pMaster != NULL && pMaster->IsPlayer() )
        {
            GamePlayer* pMasterPlayer = (GamePlayer*) pMaster;
            if ( !pMasterPlayer->IsCanAttack( pTarget ) )           // 不能攻击
            {
                LostAttackTarget();
                pTarget = NULL;
                _disableControlThinkTime = true;
                return;
            }
        }
    }

    if( !CheckUseSkillPreconditionState() )
    {
        return;
    }

    int nSkillIndex = GetCurSkillIndex();
    SetMustUsingSkill(nSkillIndex,false);
    if (nSkillIndex < 0 || nSkillIndex >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d 下标越界", __FILE__, __LINE__);
        return;
    }

    if( theGameWorld.g_dwLastWorldProcessTime - GetAiData()->m_dwSkillStartColdDownTime[nSkillIndex] > GetAiData()->m_dwSkillColdDownTime[nSkillIndex] && IsInAttackRange( pTarget,  m_pCurSkill ) )
    {
        GetAiData()->m_dwSkillStartColdDownTime[nSkillIndex] = theGameWorld.g_dwLastWorldProcessTime;
        AIAttack( GetCanAttackCharId(), GetCurSkill(),  GetCurSkillLevel() );
    }
    else
    {
        _disableControlThinkTime = true;
    }

    pTarget = NULL;
}

void MonsterBase::LostAttackTarget()
{
    //如果是第一次失去目标，则清除AI脚本变量
    if( HaveCanAttackCharId() )
    { SendVerifyPos(GetFloatX(), GetFloatY()); }

    ClearCanAttackCharId();
    m_bClosingToTarget = false;
}

void MonsterBase::ChangeMoveSpeed( float speed )
{
    SetMoveSpeed( speed );
    SetLastMovingSpeed ( speed );
    ChangeAttr( CharAttr_MoveSpeed, speed );
}

void MonsterBase::SetDeadScript( const char* szScriptName )
{
    GetAiData()->m_strDeadScriptName = szScriptName;
}

const char *MonsterBase::GetDeadScript() 
{
    return GetAiData()->m_strDeadScriptName.c_str();
}

// 设置物品掉落模板
void MonsterBase::SetItemDropTemplate( const char* szDropTemplate )
{
    GetAiData()->m_strItemDropTemplate = szDropTemplate;
}

// 获得物品掉落模板
const char *MonsterBase::GetItemDropTemplate()
{
    return GetAiData()->m_strItemDropTemplate.c_str();
}

// 设置物品掉落倍率
void MonsterBase::SetItemDropMultiple( float fm )
{
    GetAiData()->m_fItemDropMultipleRate = fm;
}

// 获得物品掉落倍率
float MonsterBase::GetItemDropMultiple()
{
    return GetAiData()->m_fItemDropMultipleRate;
}

float MonsterBase::GetPercentHP()
{
    float fMax = GetCharFightAttr()->hpMax.final;
    if( fMax <= 0.0f )
    { fMax = 0.00001f; }

    float fHp = GetHP();

    return fHp / fMax;
}

float MonsterBase::DropRnd()
{
    DWORD dwTotal = (theRand.rand32()%10000)*10000 + theRand.rand32()%10000;
    float m = 10000.0f * 10000.0f;
    float r = dwTotal / m;
    return r;
}

float MonsterBase::Rnd()
{
    return theRand.rand32()/(float)RAND_MAX;
}

bool MonsterBase::IsInMoveZone()
{
    if ( GetTileX() >= GetCanMoveZone().left
        && GetTileX() <= GetCanMoveZone().right
        && GetTileY() >= GetCanMoveZone().top
        && GetTileY() <= GetCanMoveZone().bottom )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MonsterBase::LockTarget( GameObjectId nMaxEnmityCharId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nMaxEnmityCharId );
    if ( NULL == pChar)
    { return ; }

    if ( pChar->GetID() == GetCanAttackCharId() )
    { return; }

    if ( IsAICanAttack( pChar ) )
    {
        SetCanAttackCharId( nMaxEnmityCharId ); 
        OnSuccessLockTarget(); // 回调成功锁定
    }
}

void MonsterBase::FollowTheSummonMaster( BaseCharacter* pSummoner  )
{ // 跟随召唤主移动
    // 不在同一个地图了。就不跟随了
    if ( pSummoner == NULL )
    { return; }

    if ( pSummoner->GetMapID() != GetMapID() )
    { return; }

    D3DXVECTOR3 vMasterPos = pSummoner->GetPos();
    D3DXVECTOR3 vCurPos    = GetPos();

    // 只判断平面位置
    D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    float distanceBeginFollow = m_fBodySize + pSummoner->GetBodySize() + 2;
    
    // 是否超出最低距离
    if( m_fBodySize > 0 && fDistance > distanceBeginFollow)
    { // 开始跟随
        D3DXVECTOR3 vecDir;
        D3DXVec3Normalize( &vecDir, &vecDistance );
        
        // 镖车超出太远停止不跟
        if ( HaveProtectChar() && fDistance > ProtectCharStopDistance)
        { // 距离太远
            _bNeedFollowSummonMaster = false;
            return;
        }
        
        _bNeedFollowSummonMaster = true;

        // 宠物分散在玩家身后120°左右两侧
        const float fAngle = D3DX_PI / 1.5f;
        // 主人朝向
        D3DXVECTOR3 vSummonerDir = D3DXVECTOR3( pSummoner->GetDirX(), pSummoner->GetDirY(), 0 );
        float fCorrect = pSummoner->GetBodySize() + m_fBodySize + 0.5;

        switch ( GetObjType() )
        {
        case Object_MonsterPet:
            vCurPos = GetTargetPos( pSummoner->GetPos(), vSummonerDir,  -fAngle, fCorrect);
            break;
        case Object_MonsterNurturePet:
            vCurPos = GetTargetPos( pSummoner->GetPos(), vSummonerDir,   fAngle, fCorrect);
            break;
        default:
            vCurPos = GetTargetPos( pSummoner->GetPos(), vSummonerDir,  -fAngle, fCorrect);
            break;
        }

        _moveTargetPos.x = vCurPos.x;
        _moveTargetPos.y = vCurPos.y;
        _moveTargetPos.z = 0;
        _isNeedMove = true;            
        //确保附近有玩家才发送，以提高性能
        if ( AreaHavePlayer() )
        {
            MsgUnPlayerMovingToPos msg;
            msg.header.stID = GetID();
            msg.vStartPos.x = GetFloatX();
            msg.vStartPos.y = GetFloatY();
            msg.vStartPos.z = 0;
            msg.vEndPos     = _moveTargetPos;
            GettheServer().SendMsgToView(&msg, GetID(), true);
        }
        m_vLastSendTargetPos.x = GetFloatX();
        m_vLastSendTargetPos.y = GetFloatY();
    }
}

//瞬间移动到召唤主的身边
void MonsterBase::FlyToTheSummonMaster()
{ // 只有Pet
    BaseCharacter* pMasterChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
    if ( NULL == pMasterChar)
    {
        Murder();
        return; 
    }

    if ( pMasterChar->GetStatus() == CS_LOADINGMAP )
    { return; }

    if( pMasterChar->GetMapID() != GetMapID() )
    { 
        Murder();
        return; 
    }

    D3DXVECTOR3 vMasterPos = pMasterChar->GetPos();
    D3DXVECTOR3 vCurPos = GetPos();
    D3DXVECTOR3 vDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
    float fDistToSummonMaster = D3DXVec3Length( &vDistance );
    if( fDistToSummonMaster > 20 )
    { // 超过15米马上瞬间移动回来
        float fDistanceLimit = m_fBodySize + 0.5;
        if( fDistToSummonMaster > fDistanceLimit )
        {
            D3DXVECTOR3 vecDir;
            D3DXVec3Normalize( &vecDir, &vDistance );
            float fActualDistance = fDistToSummonMaster - fDistanceLimit;
            vCurPos.x += fActualDistance * vecDir.x;
            vCurPos.y += fActualDistance * vecDir.y;
            SetDirX( vecDir.x );
            SetDirY( vecDir.y );
            SetFloatXF( vCurPos.x );
            SetFloatYF( vCurPos.y );
            SendVerifyPos( GetFloatX(), GetFloatY() );
            m_bMoving = false;
        }

        ClearAllEnmity();
        ClearAskToAttackTargetId();
        LostAttackTarget();
    }
}

void MonsterBase::LoadLuaScript( const char* LuaFileName )
{
    try
    {
        //LuaScript->GetGlobals().RegisterDirect( "Thinking", *this, &MonsterBase::Thinking );
        //////////////////////////////////////////////////////////////////////////
        LuaObject metaTableObj;
        metaTableObj = m_LuaScript->GetGlobals().CreateTable("MultiObjectMetaTable");
        metaTableObj.SetObject("__index", metaTableObj);

        metaTableObj.RegisterObjectDirect( "LoseHPInstant",              (MonsterBase*)0, &MonsterBase::LoseHPInstant              );
        metaTableObj.RegisterObjectDirect( "LoseMPInstant",              (MonsterBase*)0, &MonsterBase::LoseMPInstant              );
        metaTableObj.RegisterObjectDirect( "RestoreHPInstant",           (MonsterBase*)0, &MonsterBase::RestoreHPInstant           );
        metaTableObj.RegisterObjectDirect( "RestoreMPInstant",           (MonsterBase*)0, &MonsterBase::RestoreMPInstant           );
        metaTableObj.RegisterObjectDirect( "GetHP",                      (MonsterBase*)0, &MonsterBase::LuaGetHP                   );
        metaTableObj.RegisterObjectDirect( "GetMP",                      (MonsterBase*)0, &MonsterBase::GetMP                      );
        metaTableObj.RegisterObjectDirect( "GetHPMax",                   (MonsterBase*)0, &MonsterBase::GetHPMax                   );
        metaTableObj.RegisterObjectDirect( "GetMPMax",                   (MonsterBase*)0, &MonsterBase::GetMPMax                   );
        metaTableObj.RegisterObjectDirect( "UseSkill",                   (MonsterBase*)0, &MonsterBase::TryUseSkill                );
        metaTableObj.RegisterObjectDirect( "UseSkillByID",               (MonsterBase*)0, &MonsterBase::TryUseSkillByID            );
        metaTableObj.RegisterObjectDirect( "Say",                        (MonsterBase*)0, &MonsterBase::Say                        );
        metaTableObj.RegisterObjectDirect( "SayAdvance",                 (MonsterBase*)0, &MonsterBase::SayAdvance                 );
        metaTableObj.RegisterObjectDirect( "GetRand",                    (MonsterBase*)0, &MonsterBase::GetRand                    );
        metaTableObj.RegisterObjectDirect( "GetLevel",                   (MonsterBase*)0, &MonsterBase::LuaGetLevel                );
        metaTableObj.RegisterObjectDirect( "DropItemRand",               (MonsterBase*)0, &MonsterBase::DropItemRand               );
        metaTableObj.RegisterObjectDirect( "AddTimer",                   (MonsterBase*)0, &MonsterBase::AddTimer                   );
        metaTableObj.RegisterObjectDirect( "GetTimer",                   (MonsterBase*)0, &MonsterBase::GetTimer                   );
        metaTableObj.RegisterObjectDirect( "SetTimer",                   (MonsterBase*)0, &MonsterBase::SetTimer                   );
        metaTableObj.RegisterObjectDirect( "DelTimer",                   (MonsterBase*)0, &MonsterBase::DelTimer                   );
        metaTableObj.RegisterObjectDirect( "GetTargetHP",                (MonsterBase*)0, &MonsterBase::GetTargetHP                );
        metaTableObj.RegisterObjectDirect( "GetTargetMP",                (MonsterBase*)0, &MonsterBase::GetTargetMP                );
        metaTableObj.RegisterObjectDirect( "GetTargetHPMax",             (MonsterBase*)0, &MonsterBase::GetTargetHPMax             );
        metaTableObj.RegisterObjectDirect( "GetTargetMPMax",             (MonsterBase*)0, &MonsterBase::GetTargetMPMax             );
        metaTableObj.RegisterObjectDirect( "GetTargetLevel",             (MonsterBase*)0, &MonsterBase::GetTargetLevel             );
        metaTableObj.RegisterObjectDirect( "GetTargetEnmity",            (MonsterBase*)0, &MonsterBase::GetTargetEnmity            );
        metaTableObj.RegisterObjectDirect( "SetTargetEnmity",            (MonsterBase*)0, &MonsterBase::SetTargetEnmity            );
        metaTableObj.RegisterObjectDirect( "GetEnmityByID",              (MonsterBase*)0, &MonsterBase::GetEnmityByID              );
        metaTableObj.RegisterObjectDirect( "SetEnmityByID",              (MonsterBase*)0, &MonsterBase::SetEnmityByID              );
        metaTableObj.RegisterObjectDirect( "GetDamageEnmityByID",        (MonsterBase*)0, &MonsterBase::GetDamageEnmityByID        );
        metaTableObj.RegisterObjectDirect( "GetTargetID",                (MonsterBase*)0, &MonsterBase::GetTryToAttackCharId       );
        metaTableObj.RegisterObjectDirect( "SetTargetID",                (MonsterBase*)0, &MonsterBase::SetTryToAttackCharId       );
        metaTableObj.RegisterObjectDirect( "RandEnmity",                 (MonsterBase*)0, &MonsterBase::RandEnmity                 );
        metaTableObj.RegisterObjectDirect( "GetTargetDistance",          (MonsterBase*)0, &MonsterBase::GetTargetDistance          );
        metaTableObj.RegisterObjectDirect( "SetArray",                   (MonsterBase*)0, &MonsterBase::SetArray                   );
        metaTableObj.RegisterObjectDirect( "GetArray",                   (MonsterBase*)0, &MonsterBase::GetArray                   );
        metaTableObj.RegisterObjectDirect( "SetBoolArray",               (MonsterBase*)0, &MonsterBase::SetBoolArray               );
        metaTableObj.RegisterObjectDirect( "GetBoolArray",               (MonsterBase*)0, &MonsterBase::GetBoolArray               );
        metaTableObj.RegisterObjectDirect( "Murder",                     (MonsterBase*)0, &MonsterBase::Murder                     );
        metaTableObj.RegisterObjectDirect( "SummonMonster",              (MonsterBase*)0, &MonsterBase::SummonMonster              );
        metaTableObj.RegisterObjectDirect( "SummonInfluenceMonster",     (MonsterBase*)0, &MonsterBase::SummonInfluenceMonster     );        
        metaTableObj.RegisterObjectDirect( "FindPersonKillerToAttack",   (MonsterBase*)0, &MonsterBase::FindPersonKillerToAttack   );
        metaTableObj.RegisterObjectDirect( "FindPersonAttackerToAttack", (MonsterBase*)0, &MonsterBase::FindPersonAttackerToAttack );
        metaTableObj.RegisterObjectDirect( "FindPersonNormalToAttack",   (MonsterBase*)0, &MonsterBase::FindPersonNormalToAttack   );
        metaTableObj.RegisterObjectDirect( "FindPersonPoliceToAttack",   (MonsterBase*)0, &MonsterBase::FindPersonPoliceToAttack   );
        metaTableObj.RegisterObjectDirect( "HaveAttackTarget",           (MonsterBase*)0, &MonsterBase::HaveCanAttackCharId        );
        metaTableObj.RegisterObjectDirect( "GetAttackTargetPro",         (MonsterBase*)0, &MonsterBase::GetAttackTargetPro         );
        metaTableObj.RegisterObjectDirect( "GetRandTarget",              (MonsterBase*)0, &MonsterBase::GetRandTarget              );
        metaTableObj.RegisterObjectDirect( "Exit",                       (MonsterBase*)0, &MonsterBase::Exit                       );

        LuaObject CAICharacterCoreObj = m_LuaScript->BoxPointer(this);
        CAICharacterCoreObj.SetMetaTable(metaTableObj);
        m_LuaScript->GetGlobals().SetObject( "AI", CAICharacterCoreObj );
        // 追加注册函数
        //metaTableObj.RegisterObjectDirect( "MyFunc", (MonsterBase*)0, &MonsterBase::MyFunc1                                        );
        //CAICharacterCoreObj.SetMetaTable(metaTableObj);
        //m_LuaScript->GetGlobals().SetObject( "AI", CAICharacterCoreObj );

        if( !m_LuaScript->LoadFile( LuaFileName ) )
        {
            m_bLuaScriptLoaded = true;
            m_LuaScript->Call( 0, 0 );
        }
    }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script failed:%s", GetCharName(), e.GetErrorMessage() );
        m_bLuaScriptLoaded = false;
    }
}

void MonsterBase::RestoreHPInstant( int nRestoreHP )
{
    int nHp = GetHP();
    nHp += nRestoreHP;

    if( nHp > GetHPMax() )
    {
        nHp = GetHPMax();
    }

    SetHP( nHp );
    ChangeAttr( CharAttr_HP, nHp );
}

void MonsterBase::RestoreMPInstant( int nRestoreMP )
{
    int nMp = GetMP();
    nMp += nRestoreMP;

    if( nMp > GetMPMax() )
    {
        nMp = GetMPMax();
    }

    SetMP( nMp );
    ChangeAttr(CharAttr_MP, nMp );
}

// 瞬间去血
void MonsterBase::LoseHPInstant( int nLoseHP )
{
    int nHp = GetHP();
    nHp -= nLoseHP;

    if( nHp < 1 )
    {
        nHp = 1;
    }

    SetHP( nHp );
}

// 瞬间去魔
void MonsterBase::LoseMPInstant( int nLoseMP )
{
    int nMp = GetMP();
    nMp -= nLoseMP;

    if( nMp < 1 )
    {
        nMp = 1;
    }

    SetMP( nMp );
}

// 提升最大物理攻击力(无叠加效果)
void MonsterBase::UpgradePhysicsAttDamMax( int nValue )
{
    GetCharFightAttr()->attackPhysics.UpdateFinal();
    int nAttDamMax = GetCharFightAttr()->attackPhysics.final;
    nAttDamMax +=nValue;
    GetCharFightAttr()->attackPhysics.final = nAttDamMax;
}

// 提升物理防御(无叠加效果)
//void MonsterBase::UpgradePhysicsDef( int nValue )
//{
//    GetPhysicDef()->UpdateFinal();
//    int nDef = GetPhysicDef()->final;
//    nDef +=nValue;
//    BaseCharacter::SetPhysicAttMax( nDef );
//}

void MonsterBase::TryUseSkillByID(int nID, int nSkillID, int nLevel)
{
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(nID);
    if( pTarget == NULL )
    { return; }

    if( pTarget->IsDead() )
    { return; }

    CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillID, nLevel );
    if ( !pSkill )
    { return; }

    if( IsInAttackRange( pTarget, pSkill ) )
    { AIAttack(nID, nSkillID, nLevel); }
}

#include "StringLanguageTranslator.h"

// 说话句话
void MonsterBase::Say( const char* pBuf )
{
    if (pBuf == NULL || !AreaHavePlayer() )
    { return; }

    MsgChat msgChat;
    msgChat.header.stID = GetID();
    HelperFunc::SafeNCpy( msgChat.chatHeader.szSpeakName, GetCharName(), sizeof( msgChat.chatHeader.szSpeakName ) );
    msgChat.SetString( pBuf );
    GettheServer().SendMsgToView( &msgChat, GetID(), true );
}

// 说带系统信息的话
void MonsterBase::SayAdvance( const char* pBuf, int nCount, int nPos )
{
    if (pBuf == NULL || !AreaHavePlayer() )
    { return; }

    MsgChat msgChat;
    msgChat.header.stID = GetID();
    HelperFunc::SafeNCpy( msgChat.chatHeader.szSpeakName, GetCharName(), sizeof( msgChat.chatHeader.szSpeakName ) );
    msgChat.SetString( pBuf );
    GettheServer().SendMsgToView( &msgChat, GetID(), true );
}

// 得到一个0到n的随机数
int MonsterBase::GetRand( int n )
{
    int nRand = 0;
    ++n;
    if( n > 1 )
    { nRand = theRand.rand32()%n; }

    return nRand;
}

int MonsterBase::GetTargetHP()
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if (pTarget != NULL)
    {
        return pTarget->GetHP();
    }
    else
    {
        return -1;
    }
}

int MonsterBase::GetTargetMP()
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if (pTarget != NULL)
    {
        return pTarget->GetMP();
    }
    else
    {
        return -1;
    }
}

int MonsterBase::GetTargetHPMax()
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if (pTarget != NULL)
    {
        return pTarget->GetCharFightAttr()->hpMax.final;
    }
    else
    {
        return -1;
    }
}

int MonsterBase::GetTargetMPMax()
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if (pTarget != NULL)
    {
        return pTarget->GetCharFightAttr()->mpMax.final;
    }
    else
    {
        return -1;
    }
}

int MonsterBase::GetTargetLevel()
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if (pTarget != NULL)
    {
        return pTarget->GetLevel();
    }
    else
    {
        return -1;
    }
}

int MonsterBase::GetTargetEnmity()
{
    return GetEnmityByID(GetTryToAttackCharId());
}

int MonsterBase::SetTargetEnmity(unsigned int nEnmity)
{
    return SetEnmityByID(GetTryToAttackCharId(), nEnmity);
}

//获取其他目标对自身的仇恨 不存在则返回-1
int MonsterBase::GetEnmityByID(GameObjectId nID)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nID);
    if (pChar == NULL)
    {
        return -1;
    }

    return pChar->GetEnmity(GetID());
}

//设置其他目标对自身的仇恨
int MonsterBase::SetEnmityByID(GameObjectId nID, unsigned int nEnmity)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nID);
    if (pChar == NULL)
    {
        return -1;
    }

    return pChar->SetEnmity(GetID(), nEnmity);
}

int MonsterBase::GetDamageEnmityByID(GameObjectId nID)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nID);
    if (pChar == NULL)
    {
        return -1;
    }

    return pChar->GetDamageEnmity(GetID());
}

//随机设置周围目标对自己的仇恨（对未引发仇恨的目标无效）
void MonsterBase::RandEnmity(unsigned int nMin, unsigned int nMax)
{
    int nAreaID = GetCurArea();
    GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
    if ( NULL == pGameStage )
    { return; }

    AreaIndexTPL(Area9) list;
    pGameStage->Get9AreaList(list, nAreaID);
    int nCount = list.Count();
    for (int i=0; i<nCount; i++)
    {
        GameArea* pArea = pGameStage->GetArea(list[i]);
        if ( NULL == pArea )
        { return; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if ( pChar == NULL || ( !pChar->IsMonster() && !pChar->IsPlayer() ) )
            { continue; }

            unsigned int nEnmity = pChar->GetEnmity( GetID());
            if ( nEnmity == ENMITY_NOTINLIST || nEnmity <= 0 )
            { continue; }

            int nSize = nMax-nMin;
            int nRand = 0;
            if (nSize == 0)
            { continue;}

            nRand = theRand.rand32()%nSize;
            pChar->SetEnmity( GetID(), nRand+nMin);
        }
    }
}

int MonsterBase::GetRandTarget()
{
    if ( GetAttackCharCount() == 0)
    { return -1; }

    //对整个九宫格重复扫描三次。如果三次还未找到则返回-1
    for (int nLoop=1; nLoop<3; nLoop++)
    {
        int nAreaID = GetCurArea();
        GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
        if ( pGameStage == NULL )
        { continue; }

        AreaIndexTPL(Area9) list;
        pGameStage->Get9AreaList(list, nAreaID);
        int nCount = list.Count();
        for (int i=0; i<nCount; i++)
        {
            GameArea* pGameArea = pGameStage->GetArea(list[i]);
            if ( pGameArea == NULL)
            { continue; }

            GameObjectId objectId = InvalidGameObjectId;
            for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

                if (pChar != NULL && (pChar->IsMonster() || pChar->IsPlayer()))
                {
                    unsigned int nEnmity = pChar->GetEnmity( GetID());
                    if (nEnmity != ENMITY_NOTINLIST && nEnmity > 0)
                    {
                        if (theRand.rand32() % GetAttackCharCount() == 0)
                        { return pChar->GetID(); }
                    }
                }

            }
        }
    }
    return -1;
}


int MonsterBase::GetTargetDistance()
{
    GameObjectId nTargetID = GetTryToAttackCharId();
    if (nTargetID == -1)
    {
        return -1;
    }

    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID(GetTryToAttackCharId());
    if (pChar == NULL)
    {
        return -1;
    }
    int nDisX = abs(pChar->GetTileX()-GetTileX());
    int nDisY = abs(pChar->GetTileY()-GetTileY());
    return sqrt(double(nDisX*nDisX + nDisY*nDisY));
}

void MonsterBase::AddTimer( DWORD dwTime )
{
    if( !m_bTimerActive )
    {
        m_bTimerActive = true;
        m_dwStartTime = theGameWorld.g_dwLastWorldProcessTime;
        m_dwTimeStep = dwTime*1000;
    }
}

// 这是一个为Lua写的回调函数，而Lua中的True和False与C++的不一样
bool MonsterBase::GetTimer()
{
    if( m_bTimerActive )
    {
        if( m_dwTimeStep < (theGameWorld.g_dwLastWorldProcessTime - m_dwStartTime) )
        {
            m_bTimerActive = false;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

void MonsterBase::SetTimer(unsigned int nIndex, DWORD dwDelay, WORD wCount)
{
    if (nIndex >= AI_MAXTIMER||nIndex < 0)
    {
        return;
    }

    m_Timer[nIndex].dwDelay = dwDelay;
    m_Timer[nIndex].dwStartTime = HQ_TimeGetTime();
    m_Timer[nIndex].wCount = wCount;
}

void MonsterBase::DelTimer(unsigned int nIndex)
{
    if (nIndex >= AI_MAXTIMER||nIndex < 0)
    {
        return;
    }
    m_Timer[nIndex].dwStartTime = 0;
}

void MonsterBase::SetArray( int nIndex, int nValue )
{
    if( nIndex < AI_ARRAY_SIZE && nIndex > -1 )
    {
        m_nArray[nIndex] = nValue;
    }
}

int MonsterBase::GetArray( int nIndex )
{
    if( nIndex < AI_ARRAY_SIZE && nIndex > -1 )
    {
        return m_nArray[nIndex];
    }
    return 0;
}

void MonsterBase::SetBoolArray( int nIndex, bool bValue )
{
    if( nIndex < AI_BOOLARRAY_SIZE && nIndex > -1 )
    {
        m_bArray[nIndex] = bValue;
    }
}

bool MonsterBase::GetBoolArray( int nIndex )
{
    if( nIndex < AI_BOOLARRAY_SIZE && nIndex > -1 )
    {
        return m_bArray[nIndex];
    }
    return false;
}

void MonsterBase::Murder()
{
    if( HaveProtectChar() )
    {
        BaseCharacter* pProtectChar = theRunTimeData.GetCharacterByID( _protectCharId );
        if( pProtectChar && pProtectChar->IsPlayer())
        {
            GamePlayer* pProtectPlayer = (GamePlayer*)pProtectChar;
            pProtectPlayer->LostProtectChar();

            if ( _protectCharVarId > -1 )
            { pProtectPlayer->SetVar( _protectCharVarId, 0 );}
        }
    }

    if ( IsSummonMonster() && IsPet() )
    {
        BaseCharacter* pMasterChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if( pMasterChar != NULL && pMasterChar->IsPlayer())
        {
            GamePlayer* pGamePlayerMaster = (GamePlayer*)pMasterChar;            
            switch( GetPetType() )
            {
            case EPT_Skill:
                if ( GetMonsterType() != eMT_Pet )
                { pGamePlayerMaster->LostSummonPet( GetID() ); }
                break;
            case EPT_Capture:
                pGamePlayerMaster->LostCapturePet();
                break;
            case EPT_Nurture:
                {
                    MsgExit exit;
                    exit.header.stID = GetID();
                    OnExit(&exit);

                    pGamePlayerMaster->_petManager.LostActivePet();
                }
                break;
            }
        }
    }

    // 确保附近有玩家才发送，以提高性能
    if ( AreaHavePlayer() )
    {
        MsgSawSomeoneDead msg;
        msg.header.stID = GetID();
        GettheServer().SendMsgToView( &msg, GetID(), true );
    }

    CriticalError(__FUNCTION__, __FILE__, __LINE__);
}

void MonsterBase::SetProtectChar( GameObjectId ProtectCharID )
{
    if ( ProtectCharID<0 )
    { return;}

    _protectCharId = ProtectCharID;
}

BOOL MonsterBase::IsAttackTargetIsProtectChar()
{
    if ( HaveAskToAttackTargetId() && m_AskToAttackTargetID == _protectCharId)
    { return true;}

    return false;
}

void MonsterBase::Exit()
{
    if( HaveProtectChar() && !IsPet())
    {
        BaseCharacter* pProtectChar = theRunTimeData.GetCharacterByID( _protectCharId );
        if( pProtectChar && pProtectChar->IsPlayer())
        {
            GamePlayer* pProtectPlayer = (GamePlayer*)pProtectChar;
            pProtectPlayer->LostProtectChar();
        }
    }

    if ( IsSummonMonster() && IsPet() )
    {
        BaseCharacter* pMasterChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if( pMasterChar != NULL && pMasterChar->IsPlayer())
        {
            GamePlayer* pGamePlayerMaster = (GamePlayer*)pMasterChar;
            switch( GetPetType() )
            {
            case EPT_Skill:                
                pGamePlayerMaster->LostSummonPet( GetID() );
                break;
            case EPT_Capture:
                pGamePlayerMaster->LostCapturePet();
                break;
            }
        }
    }

    //确保附近有玩家才发送，以提高性能
    if ( AreaHavePlayer() )
    {
        MsgSawSomeoneDead msg;
        msg.bHaveDieAni = false;
        msg.header.stID = GetControl()->GetID();
        GettheServer().SendMsgToView( &msg, GetControl()->GetID(), true );
    }

    CriticalError(__FUNCTION__, __FILE__, __LINE__);
}

bool MonsterBase::SummonMonster(int nMonsterIndex, int nMonsterAmount, int nRadius, int nSummonType)
{
    return theGameWorld.SummonMonster(GetMapID(), GetFloatX(), GetFloatY(), GetDirX(), GetDirY(), GetBodySize(), nMonsterIndex, nMonsterAmount, (float)nRadius, nSummonType );
}

bool MonsterBase::SummonInfluenceMonster(int nMonsterIndex, int nMonsterAmount, int nRadius, int nSummonType, int nInfluence)
{
    return theGameWorld.SummonMonster(GetMapID(), GetFloatX(), GetFloatY(), GetDirX(), GetDirY(), GetBodySize(), nMonsterIndex, nMonsterAmount, (float)nRadius, nSummonType, 0, nInfluence );
}

unsigned int MonsterBase::AddAttackCharacter( GameObjectId charId )
{
    bool bResult = attackCharIds.insert( charId ).second;

#ifdef _DEBUG
    if ( !bResult )
    {
        int a = 0;
    }
#endif
    
    return GetAttackCharCount();
}

unsigned int MonsterBase::DecAttackCharacter( GameObjectId charId )
{
    ItrAttackCharContainer it = attackCharIds.find( charId );
    if ( it == attackCharIds.end() )
    { return GetAttackCharCount(); }

    attackCharIds.erase( it );

    if ( GetAttackCharCount() == 0)
    { ClearTryToAttackCharId(); }

    return GetAttackCharCount();
}

void MonsterBase::ClearTryToAttackCharEnmity()
{
    _tryToAttackCharId = InvalidGameObjectId;
    _tryToAttackCharEnmity = 0;
}

void MonsterBase::ClearTryToAttackCharId()
{
    attackCharIds.clear();
    _tryToAttackCharId = InvalidGameObjectId;
    _tryToAttackCharEnmity = 0;
}

GameObjectId MonsterBase::FindPersonKillerToAttack(int nSightRate)
{
    int nLevel = this->GetLevel();
    int nAreaID = this->GetCurArea();
    GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
    if (pGameStage == NULL)
    { return InvalidGameObjectId; }

    GameArea* pGameArea = pGameStage->GetArea(nAreaID);
    if ( pGameArea == NULL)
    { return InvalidGameObjectId; }

    GameObjectId objectId = InvalidGameObjectId;
    for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

        if (pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        if (!IsDistanceLess(pChar->GetTileX(), pChar->GetTileY(), this->GetTileX(), this->GetTileY(), nSightRate))
        { continue; }

        GamePlayer* pPlayer = static_cast<GamePlayer*>(pChar);
        if( pPlayer->GetPKValue() < 0 )
        {
            pPlayer->AddEnmityList(GetID(), 0);
            pPlayer->AddEnmity(GetID(), 100);
            return pPlayer->GetID();
        }
    }

    return InvalidGameObjectId;
}

GameObjectId MonsterBase::FindPersonAttackerToAttack(int nSightRate)
{
    int nLevel = this->GetLevel();
    int nAreaID = this->GetCurArea();
    GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
    if (pGameStage == NULL)
    { return InvalidGameObjectId; }

    GameArea* pGameArea = pGameStage->GetArea(nAreaID);
    if ( pGameArea == NULL)
    { return InvalidGameObjectId; }

    GameObjectId objectId = InvalidGameObjectId;
    for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        if (!IsDistanceLess(pChar->GetTileX(), pChar->GetTileY(), this->GetTileX(), this->GetTileY(), nSightRate))
        { continue; }

        GamePlayer* pPlayer = static_cast<GamePlayer*>(pChar);

        if ( pPlayer->GetPKMode() == PKMode_Critical )
        {
            pPlayer->AddEnmityList(GetID(), 0);
            pPlayer->AddEnmity(GetID(), 100);
            return pPlayer->GetID();
        }
    }

    return InvalidGameObjectId;
}

GameObjectId MonsterBase::FindPersonNormalToAttack(int nSightRate)
{
    int nLevel = GetLevel();
    int nAreaID = GetCurArea();
    GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
    if (pGameStage == NULL)
    { return InvalidGameObjectId; }

    GameArea* pGameArea = pGameStage->GetArea(nAreaID);
    if (pGameArea == NULL)
    { return InvalidGameObjectId; }

    GameObjectId objectId = InvalidGameObjectId;
    for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        if ( !IsDistanceLess(pChar->GetTileX(), pChar->GetTileY(), this->GetTileX(), this->GetTileY(), nSightRate) )
        { continue; }

        GamePlayer* pPlayer = static_cast<GamePlayer*>(pChar);

        //if(pPlayer->GetPersonState() == PersonKiller::PERSON_NORMAL)
        if ( pPlayer->GetPKValue() == 0 )
        {
            pPlayer->AddEnmityList(GetID(), 0);
            pPlayer->AddEnmity(GetID(), 100);
            return pPlayer->GetID();
        }
    }
    return InvalidGameObjectId;
}

GameObjectId MonsterBase::FindPersonPoliceToAttack(int nSightRate)
{
    int nLevel = this->GetLevel();
    int nAreaID = this->GetCurArea();
    GameStage* pGameStage = theGameWorld.GetStageById(this->GetMapID());
    if (pGameStage == NULL)
    { return InvalidGameObjectId; }

    GameArea* pGameArea = pGameStage->GetArea(nAreaID);
    if ( pGameArea == NULL)
    { return InvalidGameObjectId; }

    GameObjectId objectId = InvalidGameObjectId;
    for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

        if ( pChar == NULL || !pChar->IsPlayer())
        { continue; }

        if (!IsDistanceLess(pChar->GetTileX(), pChar->GetTileY(), this->GetTileX(), this->GetTileY(), nSightRate))
        { continue; }

        GamePlayer* pPlayer = static_cast<GamePlayer*>(pChar);

        //if(pPlayer->GetPersonState() == PersonKiller::PERSON_POLICE)
        if ( pPlayer->GetPKValue() > 0 )
        {
            pPlayer->AddEnmityList(GetID(), 0);
            pPlayer->AddEnmity(GetID(), 100);
            return pPlayer->GetID();
        }
    }
    return InvalidGameObjectId;
}

void MonsterBase::SendVerifyPos( float x, float y )
{
    // 确保附近有玩家才发送，以提高性能
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerVerifyPos msg;

        msg.SetLevel(level_normal); // 在这里设置中等优先级

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

void MonsterBase::SendClosingToTarget( GameObjectId nTargetID, D3DXVECTOR3 vNextPos )
{
    //确保附近有玩家才发送，以提高性能
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerClosingToLockTarget msg;
        msg.header.stID  = GetID();
        msg.LockTargetID = nTargetID;
        msg.vPos         = vNextPos;
        GettheServer().SendMsgToView(&msg, GetID(), true);
    }
}

void MonsterBase::SetDisappearTime( DWORD dwTime )
{
    m_xDisappearTimer.StartTimer( HQ_TimeGetTime(), dwTime );
}

void MonsterBase::AskToAttackTarget()
{
    if( IsSummonMonster() )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if( pChar != NULL )
        { m_AskToAttackTargetID = pChar->GetLockCharID(); }
    }
}

void MonsterBase::AskToFollowMaster()
{
    ClearAskToAttackTargetId();
    if( HaveCanAttackCharId() )
    { LostAttackTarget(); }
}

bool MonsterBase::IsInRange()
{
    //如果nMaxRange为-1则不限制
    if (nMaxRange == -1)
    { return true; }

    if ( GetAiData()->lastIdleX == 0 && GetAiData()->lastIdleY == 0)
    { // 未设置表示都在区域内
        return true;
    }

    if (abs(GetAiData()->lastIdleX - GetFloatX()) > nMaxRange || abs(GetAiData()->lastIdleY - GetFloatY()) > nMaxRange)
    {
        return false;
    }

    return true;
}

bool MonsterBase::IsInBaseEnmityRange()
{
    //如果nBaseEnmityRange为-1则不限制
    if ( m_nBaseEnmityRange == -1)
        return false;

    if (abs(GetAiData()->m_ptBornPoint.x - GetFloatX()) > m_nBaseEnmityRange ||
        abs(GetAiData()->m_ptBornPoint.y - GetFloatY()) > m_nBaseEnmityRange)
    {
        return false;
    }

    return true;
}

void MonsterBase::SetSpecialTarget( DWORD dwValue )
{
    m_dwSpecialID = dwValue;
}

void MonsterBase::SetCurSkillByIDAndLev(unsigned short skillid,unsigned short skilllevel)
{
    CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(skillid,skilllevel);
    if (pSkill)
    {
        m_iCurSkillId     = skillid;
        m_stCurSkillLevel = skilllevel;
        m_nCurSkillIndex  = AI_MONSTERMAXSKILLNUM - 1;

        _coreAiData.m_iSkillId[AI_MONSTERMAXSKILLNUM - 1]      = skillid;
        _coreAiData.m_stSkillLevel[AI_MONSTERMAXSKILLNUM - 1]  = skilllevel;
        _coreAiData.m_stSkillRate[AI_MONSTERMAXSKILLNUM - 1]   = 0;
        _coreAiData.m_bMustUseSkill[AI_MONSTERMAXSKILLNUM - 1] = true;
    }
}

void MonsterBase::SetMustUsingSkill(int index,bool ismust)
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d下标越界", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_bMustUseSkill[index] = ismust;
}

long MonsterBase::ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue )
{
    CItemDetail::SItemStatus* pStatusItem = (CItemDetail::SItemStatus *)GettheItemDetail().GetStatus(iStatusID, iStatusLevel);
    if( !pStatusItem )
        return GLR_StatusNotExist;

    if (IsDead()) //死人不能附加状态
        return GLR_InDeadNotUseStatus;

    bool bIsCanAddStatus = false;

    int nRand = theRand.rand32() % 100;
    if (pStatusItem->bIsMove)
    {
        if (nRand > GetResistBeMove())
        {
            bIsCanAddStatus = true;
        }
    }
    else if (pStatusItem->bIsAtt)
    {
        if (nRand > GetResistBeAtt())
        {
            bIsCanAddStatus = true;
        }
    }
    else if (pStatusItem->bIsUsingMagic)
    {
        if (nRand > GetResistBeMagic())
        {
            bIsCanAddStatus = true;
        }
    }
    else if (pStatusItem->bIsUsingTools)
    {
        if (nRand > GetResistBeTools())
        {
            bIsCanAddStatus = true;
        }
    }
    else
    {
        bIsCanAddStatus = true;
    }

    bool bHaveNewBufferAdd = false;
    if (bIsCanAddStatus)
    {
        DWORD dwDbId = 0;
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID(iMaster);
        if ( pMaster != NULL)
        {
            if (pMaster->IsPlayer())
            {
                GamePlayer* pPlayer = static_cast<GamePlayer*> ( pMaster );        
                dwDbId = pPlayer->GetDBCharacterID();
            }
            else if ( pMaster->IsMonster() )
            {
                MonsterBase* pMonster = static_cast<MonsterBase*>( pMaster );
                if ( pMonster->IsSummonMonster() )
                {// 召唤怪设置主人释放
                    BaseCharacter* pSummonMaster = theRunTimeData.GetCharacterByID( pMonster->GetSummonMasterID() );
                    if ( pSummonMaster != NULL && pSummonMaster->IsPlayer() )
                    {
                        GamePlayer* pPlayer = static_cast<GamePlayer*> ( pSummonMaster );  
                        dwDbId = pPlayer->GetDBCharacterID();
                    }
                }
            }
            
        }

        bool bStop = false;
        if ( pStatusItem->actionMapConfigId != InvalidLogicNumber && pStatusItem->actionMapConfigId != EctypeId2MapId(GetMapID()) )
        { bStop = true; }

        bHaveNewBufferAdd = _buffManager.ApplyBuff( bStop, iStatusID, iStatusLevel, iMaster, HQ_TimeGetTime(), false, 0, dwDbId, eventType, eventValue);
    } 

    if (bHaveNewBufferAdd)
    { // 发消息通知客户端
        //状态是否有打断施法属性，如果有的话
        if( pStatusItem->bIsUsingMagic )
        { CancelSkill(); }

        if (pStatusItem->bIsClearDamgeStatus)
        { _buffManager.ClearBuffByBuffIdLevel(pStatusItem->ustItemID,pStatusItem->ustLevel); }

        // 是否是宠物怪
        if (IsPet())
        { ChangeAttr(CharAttr_HPMax,GetHPMax()); }

        return GLR_Success;
    }
    return GLR_StatusApplyFail;
}

bool MonsterBase::IsCanAttack( BaseCharacter* pTarget )
{ // 是否是永久的不能攻击此目标 bForeverCanntAttack 表示
    // 自身中了状态不能攻击
    //if ( _buffManager.IsRandRun() )
    //{ return false; }

    if ( !pTarget->IsCanBeAttackedObject())
    { return false; }

    // 先判断自己是不是玩家宠物
    if ( IsSummonMonster() || IsIllusionChar() )
    {
        // 得到主人
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( pMaster == NULL || !pMaster->IsPlayer() )
        { return false; }

        GamePlayer* pMasterPlayer = static_cast< GamePlayer* >( pMaster );
        if ( pTarget->IsPlayer() )
        {
            if ( pMasterPlayer->_buffManager.IsInvincible() )
            { // 主人是无敌状态
                return false; 
            } 

            GamePlayer* pTargetPlayer = static_cast< GamePlayer* >( pTarget );
            return pMasterPlayer->IsCanAttackPlayer( pTargetPlayer );
        }
        else if ( pTarget->IsMonster() )
        {
            MonsterBase* pAITarget = static_cast< MonsterBase* >( pTarget );
            if ( pAITarget->IsSummonMonster() ||  pAITarget->IsIllusionChar() )     // 如果是玩家宠物
            {
                if ( !pAITarget->IsNeedFightMonster() )
                { return false; }

                BaseCharacter* pTargetMaster = theRunTimeData.GetCharacterByID( pAITarget->GetSummonMasterID() );
                if ( pTargetMaster == NULL || !pTargetMaster->IsPlayer() )
                { return false; }

                GamePlayer* pTargetPlayer = static_cast< GamePlayer* >( pTargetMaster );
                return pMasterPlayer->IsCanAttackPlayer( pTargetPlayer );
            }

            if ( pMasterPlayer->GetFightCamp() != CampDefine::NoneCamp )
            {
                if ( GetFightCamp() == pAITarget->GetFightCamp() )
                { return false; }
            }

            return true;
        }
        else if ( pTarget->IsNpc() && pTarget->GetObjType() == Object_NpcFight )
        {
            NpcFight* pNpcFight = (NpcFight*)pTarget;
            if ( pNpcFight->GetCountry() == GetCountry() )
            { return false; }

            return true;
        }
    }
    else
    {
        // 自己是普通怪物
        if ( pTarget->IsPlayer() )
        {
            GamePlayer* pPlayer = static_cast< GamePlayer* >( pTarget );
            if ( pPlayer->GetProtectTime() > 0 )
            { // 玩家在保护时间 也怪物攻击不能他 但不是永久的
                return false; 
            }

            if ( GetFightCamp() != CampDefine::NoneCamp )
            {
                if ( GetFightCamp() == pPlayer->GetFightCamp() )
                { return false; }
            }

            if ( IsCityDefMonster() ||  IsCityMonster() )
            { return false;  }

            if ( IsHaveSpecialTarget() ) // 如果是专属怪
            {
                if ( IsSpecialTarget( pPlayer->GetDBCharacterID() ) )
                { return true; }

                // 如果不是, 判断是否在专属组里
                GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
                if ( pTeam == NULL || !pTeam->IsInTeam( GetSpecialTarget() ) )
                { return false; }

                return true;
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

                GamePlayer* pPlayer = static_cast< GamePlayer* >( pMaster );
                if ( GetFightCamp() != CampDefine::NoneCamp )
                {
                    if ( GetFightCamp() == pPlayer->GetFightCamp() )
                    { return false; }
                }
            }

            // 同一阵营怪物不能打哦
            if ( GetFightCamp() != CampDefine::NoneCamp )
            {
                if ( GetFightCamp() == pAITarget->GetFightCamp() )
                { return false; }
            }

            return true;
        }
    }

    return false;
}

bool MonsterBase::IsHaveMoveAbility()
{
    if ( /*m_fIdleMoveSpeed == 0 ||*/ m_fNormalMoveSpeed == 0 )
    { return false; }

    if ( GetMonsterType() == eMT_Building || GetMonsterType() == eMT_Wood || GetMonsterType() == eMT_Trap)
    { return false; }

    return true;
}

void MonsterBase::SetHPMax( uint32 hpMax )
{
    GetCharFightAttr()->hpMax.base = hpMax;
    GetCharFightAttr()->hpMax.UpdateFinal();
}

uint32 MonsterBase::GetHPMax()
{
    return GetCharFightAttr()->hpMax.final;
}

void MonsterBase::SetMPMax( uint32 mpMax )
{
    GetCharFightAttr()->mpMax.base = mpMax;
    GetCharFightAttr()->mpMax.UpdateFinal();
}

uint32 MonsterBase::GetMPMax()
{
    return GetCharFightAttr()->mpMax.final;
}

void MonsterBase::SetMP( int nMp )
{
    if ( nMp> GetMPMax() )
    { _nMp = GetMPMax(); }
    else
    { _nMp = nMp; }
}

int MonsterBase::GetMP()
{
    return _nMp;
}

void MonsterBase::ProcessCampMonsterDeath()
{
    BaseCharacter* pKiller = GetKiller();
    if ( pKiller == NULL )
    { return; }

    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() );
    if ( pCampBattle == NULL || pCampBattle->GetStatus() != CampDefine::StatusFight )
    { return; }

    unsigned int nPlayerID = 0;
    if ( pKiller->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pKiller );
        nPlayerID = pPlayer->GetDBCharacterID();
    }

    pCampBattle->KillCampBattleMonster( pKiller->GetFightCamp(), nPlayerID, GetMonsterId() );
}

void MonsterBase::InitFindParth()
{
	// 获得寻路相关开关的配置
	CItemDetail::SMonster* pMonsterConfig = theItemDetailConfig.GetMonsterById( GetMonsterId() );
	if ( pMonsterConfig )
	{
		_charFindParth.InitFindParth( GetID(), pMonsterConfig->blIsFindParth, pMonsterConfig->blIsDynamicBlock );
	}
}

void MonsterBase::CheckFindParthConfigChange()
{
	// 获得寻路相关开关的配置
	CItemDetail::SMonster* pMonsterConfig = theItemDetailConfig.GetMonsterById( GetMonsterId() );
	if ( pMonsterConfig )
	{
		_charFindParth.ReInitFindParth( pMonsterConfig->blIsFindParth, pMonsterConfig->blIsDynamicBlock );
	}
}

bool MonsterBase::FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange )
{
	if ( m_bClosingToTarget && _charFindParth.IsFindParth() )
	{// 需要靠近目标并且开启寻路
		if ( _charFindParth.FindTheNextPosToMove( vTargetPos, GetPos(), GetMapID() ) == false )
		{ return false; }

		if ( _charFindParth.IsTheLastPointInParth() )
		{
			//目标位置点才考虑模型大小
			BaseCharacter* pTarget = GetCanAttackChar();
			fRange = pTarget->GetBodySize() + GetBodySize();
		}
	}
	return true;
}

void MonsterBase::AfterMoveToPos()
{
	_charFindParth.AfterMoveToPos( GetPos(), GetMapID() );
}

void MonsterBase::CheckReachPos()
{
	if ( m_bClosingToTarget && false == m_bMoving && _charFindParth.IsFindParth() )
	{//已到达当前路点,取下一个路点
		if ( _charFindParth.CheckReachPos() )
		{ m_bMoving = true; }
	}
}

//void MonsterBase::ProcessChangeTypeStatus( int nTypeStatus )
//{
//    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterId() );
//    if ( pStatusData == NULL )
//    { return; }
//
//    const MonsterStatusConfig::StatusSetting* pChangeStatusSetting = NULL;
//    if ( nTypeStatus == 0 )
//    {
//        // 当前状态属性
//        const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetTypeStatus() );
//        if ( pNowSetting == NULL )
//        { return; }
//
//        pChangeStatusSetting = pStatusData->GetStatusSetting( pNowSetting->GetNextStatus() );
//    }
//    else
//    {
//        pChangeStatusSetting = pStatusData->GetStatusSetting( nTypeStatus );
//    }
//
//    if ( pChangeStatusSetting == NULL )
//    { return; }
//
//    // 怪物状态改变
//    SetTypeStatus( pChangeStatusSetting->GetStatus() );
//    if ( pChangeStatusSetting->GetModelID() != 0 )
//    {
//        SetModelId( pChangeStatusSetting->GetModelID() );
//    }
//
//    MsgMonsterTypeStatusChange xChange;
//    xChange.nMonsterID  = GetID();
//    xChange.nTypeStatus = GetTypeStatus();
//    GettheServer().SendMsgToView( &xChange, GetID(), true );
//}
//
//bool MonsterBase::CanAttackTypeStatus()
//{
//    switch ( m_nTypeStatus )
//    {
//    case MonsterDefine::StatusNormal:
//    case MonsterDefine::StatusMonster:
//        return true;
//        break;
//    default:
//        break;
//    }
//
//    return false;
//}
//
//
//bool MonsterBase::CanQueryScriptTypeStatus()
//{
//    switch ( m_nTypeStatus )
//    {
//    case MonsterDefine::StatusMoveNpc:
//    case MonsterDefine::StatusUnMoveNpc:
//    case MonsterDefine::StatusMonsterDeath:
//        return true;
//        break;
//    default:
//        break;
//    }
//
//    return false;
//}
