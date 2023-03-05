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

const DWORD dwVerifyPosTimeDelay = 1000;        //ÿ�θ���λ��ʱ��

SProcessTime aiusetime[200];

int SAiInfo::GetCurrentSelectSkillIndex()
{
    // ����Ĭ�϶���ʹ��0�±�ļ���[��ͨ����]���ر�ָ���ļ�����1�±�λ    
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
    bPassiveConfig            = false; // �Ƿ񱻶���
    changePassiveConfig       = 0;     // ս��ʱ�Ƿ񱻶���
    endPassiveTimeConfig      = -1;    // ս��������������ʱ��
    m_nBaseEnmityRange        = -1;    // ������޳�����Χ
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
    bool bCostTime = false;    // �Ƿ��Ѿ�ʹ�����ۻ�ʱ��
    m_dwProcessLogicCostTime += dwCostTime; // �ۻ�ʱ�� �еĵط�����ÿ���߼�֡�����õ�
    m_ExtendStatus.Process();
    switch ( GetStatus() )
    {
    case CS_IDLE:
        StatusActionIdle();
        break;
    case CS_ATTACK:// ��ɫ���ڹ�����״̬
        StatusActionAttack();
        break;
    case CS_HOLDSKILL:// ��������
        StatusActionHoldSkill();
        break;
    case CS_INTONATE:// ����
        StatusActionIntonate();
        break;
    case CS_HURT:
        break;
    case CS_DIEING:// ����״̬�����ڵȴ�����
        StatusActionDieing();
        break;
    default:
        break;
    }

    if( !IsDead() )
    { // ������״̬
        // �Ҿ��ϴμ����1��ļ��
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
    // ������Ϣ����
    DWORD dwType = pMsg->GetType();

    // ����ӵ����Լ������٣��Ǿ���Ҳ����ִ���κ�����
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

    // ȷ����������Ҳŷ���,���������
    if ( AreaHavePlayer())
    { GettheServer().SendMsgToView( pMsg, GetID(), false ); }

    theGameWorld.OnDelCharacter ( stID ); // �ӳ�����ɾ��
    theRunTimeData.ReleaseObject( stID ); // ���ͷŻ��ڴ��
}

void MonsterBase::OnDeath()
{
	// ���Ѱ·���ñ仯
	CheckFindParthConfigChange();

    MsgSawSomeoneDead msg;
    msg.header.stID = GetID();

    if (IsMonster() && AreaHavePlayer() )
    { GettheServer().SendMsgToView( &msg, GetID(), true );}

    // ������г���б�
    RemoveAllEnmityList( GetID() );

    // ������Ʒ ������ٻ���, ֻ�б�����ɱ�����ܵ�����Ʒ
    //!( IsSummonMonster() && GetKiller() != NULL && GetKiller()->GetID() == m_SummonMasterID )

    // ��������ٻ��� ���� ���ٻ�����(����)ͬʱ�Ǳ�����ɱ��
    if ( !IsSummonMonster() || ( GetPetType() == EPT_Protect && GetKiller() != NULL && GetKiller()->GetID() != GetSummonMasterID() ) )
    {
        GetDropItemManager().MonsterDeath( this, GetKiller() );
    }

    if ( IsSummonMonster() && IsPet() ) 
    { // ���ٻ�����
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
    { // ����Ǳ������Ķ���
        BaseCharacter* pProtectChar = theRunTimeData.GetCharacterByID( _protectCharId );
        if( pProtectChar && pProtectChar->IsPlayer())
        {
            GamePlayer* pProtectPlayer = (GamePlayer*)pProtectChar;
            pProtectPlayer->LostProtectChar();

            if ( _protectCharVarId != -1)
            { pProtectPlayer->SetVar( _protectCharVarId, 0 ); }
        }
    }

    // ���������ű� ��ץ�ֲ����ű�
    if ( !IsSummonMonster() || GetPetType() != EPT_Capture ) 
    { CallDeadScript(); }       

    ProcessCampMonsterDeath();

    // ��������
    SetStatus( CS_DIEING );

    // ����ֱ�ӵ���exit���� ��������������ܲ�����������
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
{ // �ԾŹ���Ϊ׼����Ұ(����Ź���ͱ�ʾ����������Ұ)
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

            // ������ս�����ԵĹ�
            if ( !pMonsterBase->IsNeedFightMonster() )
            { bCanAddEnmity = false;  }

            // ������Ӫ��ʱ�� ����ͬ��Ӫ���
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
    // �ڴ˻���Ѫ
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
    { // ֲ�ｨ����
        // ������ʧ
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

        // ���Aiû������ ͬʱ����һ��Ҫ��AI ͬʱ��������AI��Ҫ����
        if ( m_bAIStartUp || MustOpenAI() || g_Cfg.iAllAIOpen )
        {
            if ( !IsDead() )
            { // û�����ĵ�ʱ��
                // ˼����Timer
                aiusetime[2].szFunctionName = "MonsterBase->Thinking";
                funtime = HelperFunc::GetCPUTime();
                ProcessAIThink();
                ProcessAITimer();
                aiusetime[2].nTime += (HelperFunc::GetCPUTime() - funtime);

                // �ж�ѡ��
                aiusetime[3].szFunctionName = "MonsterBase->Doing";
                funtime = HelperFunc::GetCPUTime();
                ProcessAISelectTask();
                aiusetime[3].nTime += (HelperFunc::GetCPUTime() - funtime);

                // ����AI�ƶ�
                aiusetime[4].szFunctionName = "MonsterBase->AIMove";
                funtime = HelperFunc::GetCPUTime();
                ProcessAIMove(dwCostTime);
                aiusetime[4].nTime += (HelperFunc::GetCPUTime() - funtime);

                // AI״̬��������������еȴ��������Ѿ��·��ĵ�����
                aiusetime[5].szFunctionName = "MonsterBase->Process";
                funtime = HelperFunc::GetCPUTime();
                ProcessAIDoTask();
                aiusetime[5].nTime += (HelperFunc::GetCPUTime() - funtime);

                // ����ĳ������ˢ��
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

            //���úù���ս����Ұ�Լ�ս����Ұ����ʱ��(Ŀǰ������д��2�����Ұ�ָ�)
            pAiChar->SetViewSight( pAiChar->GetFightViewSight() );
            pAiChar->SetFightViewEndTime( HQ_TimeGetTime() );
        }
    }
}
void MonsterBase::ProcessAIThink()
{
    if ( !_disableControlThinkTime )
    { // ��Ҫ����˼��Ƶ��
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
    { // ��ʧ�߼�
        Exit();
        return;
    }

    // ���Ӿ���
    if (m_dwFightViewEndTime != 0 && GameTime::IsPassCurrentTime( m_dwFightViewEndTime, 2000 ) )
    {
        SetViewSight( GetIdleMoveViewSight());
        m_dwFightViewEndTime = 0;
    }

    // �ص�
    OnThink();
}

void MonsterBase::ProcessAITimer()
{
    //���û������Lua�ű�����Ҫִ���������
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
    //��ִ�����ȼ��ߵ�����
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

// ���ü���
void MonsterBase::SetSkill(int index, int skill_id) 
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d�±�Խ��", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_iSkillId[index] = skill_id;
}

// ���ü��ܵȼ�
void MonsterBase::SetSkillLevel( int index, short skilllevel )
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d�±�Խ��", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_stSkillLevel[index] = skilllevel;
}

// ���ü���ʹ�ø���
void MonsterBase::SetSkillRate( int index, short skillrate )
{
    if (index < 0 || index >= AI_MONSTERMAXSKILLNUM)
    {
        ::DebugLogout("%s : %d�±�Խ��", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_stSkillRate[index] = skillrate;
}

// ���������Ҫ�õ��ܼ��ܸ���
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

// ���õ�ǰʹ�õļ��ܵȼ�
void MonsterBase::SetCurSkillLevel( uint8 index )
{
    m_stCurSkillLevel = GetAiData()->m_stSkillLevel[index];
}

// ���ƶ���Χ
void MonsterBase::SetCanMoveZone( RECT zone )
{
    GetAiData()->m_CanMoveZone = zone;
}

// ���ü���2��HP,MP����
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

// ���ü���3��HP,MP����
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

//��ȡ���ƶ���Χ
RECT MonsterBase::GetCanMoveZone()
{
    return GetAiData()->m_CanMoveZone;
}

// ��ǰ��������
bool MonsterBase::HaveTask() 
{
    return !( m_vecHighTask.empty() && m_vecNormalTask.empty() && m_vecLowTask.empty() ); 
}

// �����ǰû��Ŀ�����Ŀ�겻�߱�ְҵ�������򷵻�-1
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

    // �����˲��ܹ���
    if( IsDead() || pChar->IsDead() )
    { return false; }

    // ��������״̬���ܹ���
    //if ( _buffManager.IsRandRun() )
    //{ return false; }

    int country = pChar->GetCountry();

    // ���Ƿ�Χ�ⲻ�ܹ���
    //if( !IsDistanceLess( GetX(), GetY(), pChar->GetX(), pChar->GetY(), GetViewSight() ))
    //    return false;

    //// �޹��Ҳ��ܹ���
    //if( country == Hero::country_none )
    //    return false;

    //// ��ͬ���Ҳ��ܹ���
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

    //������Ʒ
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

    // �����óɲ���Ҫһ��ʹ�õ�״̬
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

    if ( IsSummonMonster() )        // �Լ����ٻ���
    {
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( pMaster != NULL && pMaster->IsPlayer() )
        {
            GamePlayer* pMasterPlayer = (GamePlayer*) pMaster;
            if ( !pMasterPlayer->IsCanAttack( pTarget ) )           // ���ܹ���
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
        ::DebugLogout("%s : %d �±�Խ��", __FILE__, __LINE__);
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
    //����ǵ�һ��ʧȥĿ�꣬�����AI�ű�����
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

// ������Ʒ����ģ��
void MonsterBase::SetItemDropTemplate( const char* szDropTemplate )
{
    GetAiData()->m_strItemDropTemplate = szDropTemplate;
}

// �����Ʒ����ģ��
const char *MonsterBase::GetItemDropTemplate()
{
    return GetAiData()->m_strItemDropTemplate.c_str();
}

// ������Ʒ���䱶��
void MonsterBase::SetItemDropMultiple( float fm )
{
    GetAiData()->m_fItemDropMultipleRate = fm;
}

// �����Ʒ���䱶��
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
        OnSuccessLockTarget(); // �ص��ɹ�����
    }
}

void MonsterBase::FollowTheSummonMaster( BaseCharacter* pSummoner  )
{ // �����ٻ����ƶ�
    // ����ͬһ����ͼ�ˡ��Ͳ�������
    if ( pSummoner == NULL )
    { return; }

    if ( pSummoner->GetMapID() != GetMapID() )
    { return; }

    D3DXVECTOR3 vMasterPos = pSummoner->GetPos();
    D3DXVECTOR3 vCurPos    = GetPos();

    // ֻ�ж�ƽ��λ��
    D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    float distanceBeginFollow = m_fBodySize + pSummoner->GetBodySize() + 2;
    
    // �Ƿ񳬳���;���
    if( m_fBodySize > 0 && fDistance > distanceBeginFollow)
    { // ��ʼ����
        D3DXVECTOR3 vecDir;
        D3DXVec3Normalize( &vecDir, &vecDistance );
        
        // �ڳ�����̫Զֹͣ����
        if ( HaveProtectChar() && fDistance > ProtectCharStopDistance)
        { // ����̫Զ
            _bNeedFollowSummonMaster = false;
            return;
        }
        
        _bNeedFollowSummonMaster = true;

        // �����ɢ��������120����������
        const float fAngle = D3DX_PI / 1.5f;
        // ���˳���
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
        //ȷ����������Ҳŷ��ͣ����������
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

//˲���ƶ����ٻ��������
void MonsterBase::FlyToTheSummonMaster()
{ // ֻ��Pet
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
    { // ����15������˲���ƶ�����
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
        // ׷��ע�ắ��
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

// ˲��ȥѪ
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

// ˲��ȥħ
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

// ���������������(�޵���Ч��)
void MonsterBase::UpgradePhysicsAttDamMax( int nValue )
{
    GetCharFightAttr()->attackPhysics.UpdateFinal();
    int nAttDamMax = GetCharFightAttr()->attackPhysics.final;
    nAttDamMax +=nValue;
    GetCharFightAttr()->attackPhysics.final = nAttDamMax;
}

// �����������(�޵���Ч��)
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

// ˵���仰
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

// ˵��ϵͳ��Ϣ�Ļ�
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

// �õ�һ��0��n�������
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

//��ȡ����Ŀ�������ĳ�� �������򷵻�-1
int MonsterBase::GetEnmityByID(GameObjectId nID)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nID);
    if (pChar == NULL)
    {
        return -1;
    }

    return pChar->GetEnmity(GetID());
}

//��������Ŀ�������ĳ��
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

//���������ΧĿ����Լ��ĳ�ޣ���δ������޵�Ŀ����Ч��
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

    //�������Ź����ظ�ɨ�����Ρ�������λ�δ�ҵ��򷵻�-1
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

// ����һ��ΪLuaд�Ļص���������Lua�е�True��False��C++�Ĳ�һ��
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

    // ȷ����������Ҳŷ��ͣ����������
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

    //ȷ����������Ҳŷ��ͣ����������
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
    // ȷ����������Ҳŷ��ͣ����������
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerVerifyPos msg;

        msg.SetLevel(level_normal); // �����������е����ȼ�

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
    //ȷ����������Ҳŷ��ͣ����������
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
    //���nMaxRangeΪ-1������
    if (nMaxRange == -1)
    { return true; }

    if ( GetAiData()->lastIdleX == 0 && GetAiData()->lastIdleY == 0)
    { // δ���ñ�ʾ����������
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
    //���nBaseEnmityRangeΪ-1������
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
        ::DebugLogout("%s : %d�±�Խ��", __FILE__, __LINE__);
        return;
    }
    GetAiData()->m_bMustUseSkill[index] = ismust;
}

long MonsterBase::ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue )
{
    CItemDetail::SItemStatus* pStatusItem = (CItemDetail::SItemStatus *)GettheItemDetail().GetStatus(iStatusID, iStatusLevel);
    if( !pStatusItem )
        return GLR_StatusNotExist;

    if (IsDead()) //���˲��ܸ���״̬
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
                {// �ٻ������������ͷ�
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
    { // ����Ϣ֪ͨ�ͻ���
        //״̬�Ƿ��д��ʩ�����ԣ�����еĻ�
        if( pStatusItem->bIsUsingMagic )
        { CancelSkill(); }

        if (pStatusItem->bIsClearDamgeStatus)
        { _buffManager.ClearBuffByBuffIdLevel(pStatusItem->ustItemID,pStatusItem->ustLevel); }

        // �Ƿ��ǳ����
        if (IsPet())
        { ChangeAttr(CharAttr_HPMax,GetHPMax()); }

        return GLR_Success;
    }
    return GLR_StatusApplyFail;
}

bool MonsterBase::IsCanAttack( BaseCharacter* pTarget )
{ // �Ƿ������õĲ��ܹ�����Ŀ�� bForeverCanntAttack ��ʾ
    // ��������״̬���ܹ���
    //if ( _buffManager.IsRandRun() )
    //{ return false; }

    if ( !pTarget->IsCanBeAttackedObject())
    { return false; }

    // ���ж��Լ��ǲ�����ҳ���
    if ( IsSummonMonster() || IsIllusionChar() )
    {
        // �õ�����
        BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( pMaster == NULL || !pMaster->IsPlayer() )
        { return false; }

        GamePlayer* pMasterPlayer = static_cast< GamePlayer* >( pMaster );
        if ( pTarget->IsPlayer() )
        {
            if ( pMasterPlayer->_buffManager.IsInvincible() )
            { // �������޵�״̬
                return false; 
            } 

            GamePlayer* pTargetPlayer = static_cast< GamePlayer* >( pTarget );
            return pMasterPlayer->IsCanAttackPlayer( pTargetPlayer );
        }
        else if ( pTarget->IsMonster() )
        {
            MonsterBase* pAITarget = static_cast< MonsterBase* >( pTarget );
            if ( pAITarget->IsSummonMonster() ||  pAITarget->IsIllusionChar() )     // �������ҳ���
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
        // �Լ�����ͨ����
        if ( pTarget->IsPlayer() )
        {
            GamePlayer* pPlayer = static_cast< GamePlayer* >( pTarget );
            if ( pPlayer->GetProtectTime() > 0 )
            { // ����ڱ���ʱ�� Ҳ���﹥�������� ���������õ�
                return false; 
            }

            if ( GetFightCamp() != CampDefine::NoneCamp )
            {
                if ( GetFightCamp() == pPlayer->GetFightCamp() )
                { return false; }
            }

            if ( IsCityDefMonster() ||  IsCityMonster() )
            { return false;  }

            if ( IsHaveSpecialTarget() ) // �����ר����
            {
                if ( IsSpecialTarget( pPlayer->GetDBCharacterID() ) )
                { return true; }

                // �������, �ж��Ƿ���ר������
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

            // ͬһ��Ӫ���ﲻ�ܴ�Ŷ
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
	// ���Ѱ·��ؿ��ص�����
	CItemDetail::SMonster* pMonsterConfig = theItemDetailConfig.GetMonsterById( GetMonsterId() );
	if ( pMonsterConfig )
	{
		_charFindParth.InitFindParth( GetID(), pMonsterConfig->blIsFindParth, pMonsterConfig->blIsDynamicBlock );
	}
}

void MonsterBase::CheckFindParthConfigChange()
{
	// ���Ѱ·��ؿ��ص�����
	CItemDetail::SMonster* pMonsterConfig = theItemDetailConfig.GetMonsterById( GetMonsterId() );
	if ( pMonsterConfig )
	{
		_charFindParth.ReInitFindParth( pMonsterConfig->blIsFindParth, pMonsterConfig->blIsDynamicBlock );
	}
}

bool MonsterBase::FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange )
{
	if ( m_bClosingToTarget && _charFindParth.IsFindParth() )
	{// ��Ҫ����Ŀ�겢�ҿ���Ѱ·
		if ( _charFindParth.FindTheNextPosToMove( vTargetPos, GetPos(), GetMapID() ) == false )
		{ return false; }

		if ( _charFindParth.IsTheLastPointInParth() )
		{
			//Ŀ��λ�õ�ſ���ģ�ʹ�С
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
	{//�ѵ��ﵱǰ·��,ȡ��һ��·��
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
//        // ��ǰ״̬����
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
//    // ����״̬�ı�
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
