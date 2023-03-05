#include "MonsterRoute.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"
#include "RouteManager.h"

MonsterRoute::MonsterRoute()
{
    _routeId          = ErrorUnsignedShortID;
    _routeStep        = 0;
    _bArriveTargetPos = true;
    _bFinalArrive     = false;
    _bOutOfRoute      = false;
    _posXOff          = 0.0f;
    _posYOff          = 0.0f;
}

MonsterRoute::~MonsterRoute()
{

}
//////////////////////////////////////////////////////////////////////////
const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // 仇恨减少刷新时间

SEnmity& MonsterRoute::EnmityList(int nNum)
{
    return m_enmityList[nNum];
}

unsigned int MonsterRoute::GetEnmity(GameObjectId nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        { return m_enmityList[i].nEnmity; }
    }
    return ENMITY_NOTINLIST;
}

bool MonsterRoute::SetEnmity(GameObjectId nID, unsigned int nEnmity)
{
    for (int i=0; i<EnmityNum; ++i)
    {
        if ( m_enmityList[i].nID == nID)
        {
            m_enmityList[i].nEnmity = nEnmity;
            return true;
        }
    }
    return false;
}

//添加/移除仇恨列表中对象
bool MonsterRoute::AddEnmityList(GameObjectId nID, unsigned int nEnmity)
{   
    BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(nID);
    if (pChar == NULL)
    { return false; }

    // 查找是否已经在列表里
    int nPos = -1;
    for (int i=0; i<EnmityNum; ++i)
    {
        if ( m_enmityList[i].nID == nID)
        {  return false; }

        if ( m_enmityList[i].nID == NULLID && nPos == -1)
        {
            nPos = i;
        }
    }

    if ( nPos == -1 )
    { return false; }

    m_enmityList[nPos].nID            = nID;
    m_enmityList[nPos].nEnmity        = nEnmity;
    m_enmityList[nPos].nDecEnmityRate = nEnmity;

    if (nEnmity > 0 && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight))
    { pChar->AddAttackCharacter( GetID() );}

    OnEnmityNumChange();

    return true;
}

bool MonsterRoute::RemoveEnmityList(GameObjectId nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if ( m_enmityList[i].nID != nID)
        { continue; }
        
        m_enmityList[i].nID = NULLID;
        if (m_enmityList[i].nEnmity > 0)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nID);
            if (pChar == NULL || (!pChar->IsMonster() && pChar->GetObjType() != Object_NpcFight ))
            { return false; }

            pChar->DecAttackCharacter( GetID() );
        }
        return true;
    }
    return false;
}

void MonsterRoute::RemoveAllEnmityList(GameObjectId nId)
{
    for (int i=0; i<EnmityNum; ++i)
    {
        if (m_enmityList[i].nEnmity > 0)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );            
            m_enmityList[i].nID = NULLID;
            if (pChar == NULL || (!pChar->IsMonster() && pChar->GetObjType() != Object_NpcFight) )
            { continue; }

            pChar->DecAttackCharacter( GetID() );
            pChar->ClearTryToAttackCharEnmity();
            pChar->ClearAttackerById(nId);
        }
    }
}

bool MonsterRoute::UpdateDecEnmityRate(GameObjectId nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        {
            m_enmityList[i].nDecEnmityRate = m_enmityList[i].nEnmity;
            return true;
        }
    }
    return false;
}


//添加/减少仇恨
bool MonsterRoute::AddEnmity(GameObjectId nID, unsigned int nEnmity)
{
    if (nEnmity == 0 || nID == NULLID)
    {
        return false;
    }

    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        {
            m_enmityList[i].nEnmity += nEnmity;

            if (m_enmityList[i].nEnmity == nEnmity && nEnmity > 0)
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
                if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
                { pChar->AddAttackCharacter( GetID() ); }
            }

            if(IsSummonMonster()&&IsPet())
            {
                BaseCharacter *pChar = theRunTimeData.GetCharacterByID(GetSummonMasterID());
                if (pChar != NULL)
                {
                    nEnmity = max(10, nEnmity/10);
                    if( !pChar->AddEnmityList(nID, nEnmity) )
                    {
                        pChar->AddEnmity(nID, nEnmity);
                    }
                    pChar->UpdateDecEnmityRate(nID);

                    if (pChar->IsPlayer())
                    {
                        //挂机验证程序视为玩家也施放了技能,以计算战斗时间
                        static_cast<GamePlayer*>(pChar)->m_graphiccodecheck.OnSkill();
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool MonsterRoute::DecEnmity(GameObjectId nID, unsigned int nEnmity)
{
    if ( nEnmity == 0 || nID == NULLID )
    { return false; }

    for (int i=0; i<EnmityNum; i++)
    {
        if ( m_enmityList[i].nID != nID)
        { continue; }

        if (m_enmityList[i].nEnmity >= nEnmity)
        { m_enmityList[i].nEnmity -= nEnmity;}
        else
        {
            if (m_enmityList[i].nEnmity > 0)
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
                if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
                { pChar->DecAttackCharacter( GetID() ); }
            }
            m_enmityList[i].nEnmity = 0;
        }
        return true;
    }
    return false;
}

unsigned int MonsterRoute::GetDamageEnmity(GameObjectId nID)
{
    return ENMITY_NOTINLIST;
}

bool MonsterRoute::SetDamageEnmity(GameObjectId nID, unsigned int nEnmity)
{
    return true;
}

bool MonsterRoute::AddDamageEnmity(GameObjectId nID, unsigned int nEnmity)
{
    return true;
}

bool MonsterRoute::DecDamageEnmity(GameObjectId nID, unsigned int nEnmity)
{
    return true;
}

void MonsterRoute::ClearAllEnmity()
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID != NULLID && m_enmityList[i].nEnmity > 0)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
            if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
            {
                pChar->DecAttackCharacter( GetID() );
                pChar->ClearTryToAttackCharEnmity();// 将怪物当前仇恨目标的ID清除
            }
        }
        m_enmityList[i].nEnmity = 0;
    }
}

void MonsterRoute::AddAllEnmity(unsigned int nEnmity)
{
    if (nEnmity == 0)
    {
        return;
    }

    for (int i=0; i<EnmityNum; i++)
    {
        m_enmityList[i].nEnmity += nEnmity;
        if (m_enmityList[i].nEnmity == nEnmity)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
            if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
            { pChar->AddAttackCharacter( GetID() ); }
        }
    }
}

void MonsterRoute::DecAllEnmity(unsigned int nEnmity)
{
    if (nEnmity == 0)
    {
        return;
    }

    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nEnmity > nEnmity)
        {
            m_enmityList[i].nEnmity += nEnmity;
        }
        else
        {
            if (m_enmityList[i].nEnmity == nEnmity)
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
                if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight) )
                {
                    pChar->DecAttackCharacter( GetID() );
                }
            }
            m_enmityList[i].nEnmity = 0;
        }
    }
}

bool MonsterRoute::IsHaveEnmity()
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nEnmity > 0 && m_enmityList[i].nID != NULLID)
        {
            return true;
        }
    }
    return false;
}

GameObjectId MonsterRoute::GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry )
{
    GameObjectId NearestEnmityCharID = -1;
    float fMinDistance = 20;
    vSelfPos.z = 0;

    for (int i=0; i<EnmityNum; i++)
    {
        if ( m_enmityList[i].nID != NULLID )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(m_enmityList[i].nID);
            if( pChar )
            {
                if( pChar->GetCountry() == nSelfCountry )
                    continue;

                if(pChar->IsMonster())
                {
                    MonsterRoute* pAiChar = static_cast<MonsterRoute*>( pChar );
                    if ( !pAiChar->IsNeedFightMonster() )
                    { continue; }
                }

                D3DXVECTOR3 vCharPos = pChar->GetPos();
                vCharPos.z = 0;

                float fDistance = D3DXVec3Length(&(vCharPos - vSelfPos));
                if( fDistance < fMinDistance )
                {
                    fMinDistance = fDistance;
                    NearestEnmityCharID = m_enmityList[i].nID;
                }
            }
            else
            {
                m_enmityList[i].nID = NULLID;
                m_enmityList[i].nEnmity = 0;
            }
        }
    }
    return NearestEnmityCharID;
}

GameObjectId MonsterRoute::GetMaxEnmityChar()
{
    GameObjectId MaxEnmityCharID = -1;
    unsigned int nMaxEnmity = 0;

    for (int i=0; i<EnmityNum; i++)
    {
        if ( m_enmityList[i].nID != NULLID )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(m_enmityList[i].nID);
            if( pChar )
            {
                if(pChar->IsMonster())
                {
                    MonsterRoute* pAiChar = static_cast<MonsterRoute*>( pChar );
                    if ( !pAiChar->IsNeedFightMonster() )
                    { continue; }
                }

                if( m_enmityList[i].nEnmity > nMaxEnmity )
                {
                    nMaxEnmity = m_enmityList[i].nEnmity;
                    MaxEnmityCharID = m_enmityList[i].nID;
                }
            }
            else
            {
                m_enmityList[i].nID = NULLID;
                m_enmityList[i].nEnmity = 0;
            }
        }
    }
    return MaxEnmityCharID;
}

bool MonsterRoute::AddTargetEnmityToMe(GameObjectId nID,unsigned int nEnmity)
{
    if (nEnmity == 0)
        return false;

    BaseCharacter *pTargetChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(nID);
    if (!pTargetChar)
        return false;

    short stret = -1;

    for (int nloop =0; nloop < EnmityNum;nloop++)
    {
        if (pTargetChar->EnmityList(nloop).nID == NULLID)
            continue;
        if (pTargetChar->EnmityList(nloop).nEnmity == 0)
            continue;		

        for (int n = 0; n < EnmityNum;n++)
        {
            if (this->m_enmityList[n].nID == NULLID)
                continue;

            if (this->m_enmityList[n].nID == pTargetChar->EnmityList(nloop).nID)
            {
                stret = n;
                break;
            }
        }

        if (stret != -1)
        {
            nEnmity += GetEnmity(m_enmityList[stret].nID);
            SetEnmity(m_enmityList[stret].nID,nEnmity);
        }
        else
        {
            AddEnmityList(pTargetChar->EnmityList(nloop).nID,nEnmity);
        }
    }
    return true;
}

//刷新仇恨
void MonsterRoute::RefreshEnmity()
{
    if ( IsDead() )
    { return; }

    unsigned long dwCurrTime = HQ_TimeGetTime();
    if (m_dwLastDecEnmityTime > dwCurrTime)
    { m_dwLastDecEnmityTime = 0; }

    bool bUpdateDecEnmityTime = false;

    for (int i=0; i<EnmityNum; i++)
    {
        if ( m_enmityList[i].nID == NULLID )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );

#ifdef _DEBUG
        static uint16 lookMonsterId = 0;
        if ( m_enmityList[i].nID == lookMonsterId && m_enmityList[i].nEnmity > 0 && m_enmityList[i].nDecEnmityRate > 0 )
        { int a = 0; }
#endif

        if ( pChar == NULL || pChar->GetObjType() != Object_MonsterRoute )
        { // 如果对面不是路径怪 不记他对自己的仇恨
            m_enmityList[i].nID = NULLID;
            continue;
        }

        // 因为下面都是用AIBaseCharacter强转pChar,必须判断
        if( !pChar->IsMonster() )
        { continue; }

        MonsterBase* pCharAI = (MonsterBase*)pChar;

        unsigned int lastEnmity = m_enmityList[i].nEnmity;
        unsigned int nViewEnmity = pCharAI->GetViewEnmity();
        unsigned int nEnmityRate = pCharAI->GetEnmityRate();

        if ( GameTime::IsPassCurrentTime( dwCurrTime, m_dwLastDecEnmityTime, MONSTERENMITY_REFRESHTIME ) )
        {
            bUpdateDecEnmityTime = true;

            // 减仇恨
            if ( m_enmityList[i].nEnmity > 0 )
            {
                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate * nEnmityRate * 0.001f;
                if (nDecEnmity < 1)
                { nDecEnmity = 1; }

                //在这里获取怪物减仇恨的数值
                if (m_enmityList[i].nEnmity > nDecEnmity)
                { m_enmityList[i].nEnmity -= nDecEnmity; }
                else
                { m_enmityList[i].nEnmity = 0; }
            }
        }

        if (m_enmityList[i].nEnmity == 0 && lastEnmity == 0)
        {   
            if ( !pCharAI->IsPassiveAttack() )
            { // 如果不是被动怪则进入视野触发仇恨
                UpdateViewEnmity( i, pCharAI );
            }
        }
        else
        {
            if ( m_enmityList[i].nEnmity < nViewEnmity )
            {
                if ( !pCharAI->IsPassiveAttack() || ( pCharAI->IsPassiveAttack() && pCharAI->IsInBaseEnmityRange()) )
                { //如果已经打怪物，则不判断是否被动怪，只要在视野内就保证不低于nEnmity值
                    UpdateViewEnmity( i, pCharAI );
                }
            }
        }

        if ( lastEnmity == 0 && m_enmityList[i].nEnmity > 0)
        {
            pCharAI->AddAttackCharacter( GetID() );
        }
        else if ( lastEnmity > 0 && m_enmityList[i].nEnmity == 0 )
        {
            pCharAI->DecAttackCharacter( GetID() );
        }

        if ( pCharAI->GetTryToAttackCharId() == GetID())
        { pCharAI->SetAttackCharEnmity( m_enmityList[i].nEnmity ); }
        else
        {
            if ( pCharAI->GetTryAttackCharEnmity() < m_enmityList[i].nEnmity )
            {
                pCharAI->SetAttackCharEnmity( m_enmityList[i].nEnmity );
                pCharAI->SetTryToAttackCharId( GetID());
            }
        }
    }

    if (bUpdateDecEnmityTime)
    { m_dwLastDecEnmityTime = HQ_TimeGetTime();}
}

void MonsterRoute::OnEnmityNumChange()
{
}

void MonsterRoute::OnEnmityValueChanged( GameObjectId id, unsigned int value)
{
}

void MonsterRoute::UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster )
{
    if ( !HaveFightCamp() )
    { // 自己是无阵营 不记
        return;
    }

    // 同阵营的不加仇恨
    if ( pTargetMonster->GetFightCamp() == GetFightCamp() )
    { return;}

    int nViewSight = pTargetMonster->GetViewSight() + ( pTargetMonster->GetLevel() - GetLevel() ) * ENMITY_RATE;
    if ( nViewSight < ENMITY_MIN_VIEWSIGHT )
    { nViewSight = ENMITY_MIN_VIEWSIGHT;}

    //如果在视野内并且仇恨为0，则加上100;
    if ( IsDistanceLess( pTargetMonster->GetTileX(), pTargetMonster->GetTileY(), GetTileX(), GetTileY(), nViewSight ) )
    { // 恢复仇恨
        m_enmityList[ index ].nEnmity        = pTargetMonster->GetViewEnmity();
        m_enmityList[ index ].nDecEnmityRate = pTargetMonster->GetViewEnmity(); // 取它的百分十的衰减率
    }
}
//////////////////////////////////////////////////////////////////////////

uint32 MonsterRoute::InitRoute( uint32 mapId, uint16 routeId )
{   
    bool bResult = theRouteManager.GetRouteInfo( EctypeId2MapId( mapId ), routeId, _route );
    if ( !bResult )
    { return ER_Failed; }

    _routeStep = 0;
    _routeId = routeId;
    return ER_Success;
}

bool MonsterRoute::IsBeginPosMove()
{
    // 还没有设置开始移动点 没到终点
    if ( _moveTargetPos.x == 0 && _moveTargetPos.y == 0 && _moveTargetPos.z == 0 && !_bFinalArrive )
    { return true; }
    
    return false;
}

SMovePos* MonsterRoute::GetBeginPos()
{
    _routeStep = 0;

    if ( _routeStep >= _route.allMovePos.size() )
    { return NULL; }

    return &_route.allMovePos[ _routeStep ];
}

SMovePos* MonsterRoute::GetMovePos( uint8 step )
{
    _routeStep += step;
    if ( _routeStep >= _route.allMovePos.size() )
    { return NULL; }

    return &_route.allMovePos[ _routeStep ];
}

void MonsterRoute::OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig )
{
    if( !pAttacker)
    { return; }

    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig);

    StartUpAI();
    if ( !HaveCanAttackCharId() )
    {
        MAlarmWhenBeAttack();
        _disableControlThinkTime = true;
    }
}

bool MonsterRoute::OnThink()
{
    if ( HaveTryToAttackCharId() && GetTryAttackCharEnmity() > 0 && IsInRange())
    { // 可以产生攻击行为
        ThinkAttack();
    }
    else
    { // 可以产生Idle常态行为 从攻击态回来 一直都没有攻击态
        ThinkIdle();
    }

    if( m_bLuaScriptLoaded )
    {
        try
        {
            LuaObject luaobject = m_LuaScript->GetGlobal("Event_Thinking");
            if(luaobject.IsFunction())
            { GetGlobalFun("Event_Thinking")(); }
        }
        catch (LuaPlus::LuaException &e)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI script Event_Thinking failed: %s", GetCharName(), e.GetErrorMessage() );
            m_bLuaScriptLoaded = false;
        }
    }
    return true;
}

bool MonsterRoute::OnMove( uint32 lapseTime )
{
    // 开始不同情况的移动
    if( HaveCanAttackCharId() )
    { MoveAttackMoving( lapseTime ); }
    else
    { MovePosMoving( lapseTime ); }
    return true;
}

bool MonsterRoute::OnSuccessLockTarget()
{
    //记录下上一次未被攻击前的空闲位置
    if (GetAiData()->lastIdleX == 0)
    {
        GetAiData()->lastIdleX = GetFloatX();
        GetAiData()->lastIdleY = GetFloatY();
    }
    return true;
}

void MonsterRoute::ThinkAttack()
{
    if ( !m_bIsFighting )
    {
        //设置成被动怪
        if (changePassiveConfig != 0)
        { SetPassiveAttack( true ); }

        m_bIsFighting = true;
        TryChangeFightState( m_bIsFighting, eFighting );
        MAlarmWhenBeAttack();
    }

    // 如果当前攻击目标找不到了，则跳出去
    if ( theRunTimeData.GetCharacterByID(GetTryToAttackCharId()) == NULL)
    {
        DecAttackCharacter( GetTryToAttackCharId());
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
            if ( enmity == 0|| enmity == ENMITY_NOTINLIST)
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

        _isNeedMove  = false;  // 设置追击纪录
        _bOutOfRoute = true;

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
            nCount++;
            if( GetAiData()->m_stSkillRateTotal > 0 )
            { SelectRateRandNum = theRand.rand32() % GetAiData()->m_stSkillRateTotal; }

            if( SelectRateRandNum < GetAiData()->m_stSkillRate[0] )
            { cSel = 0; }
            else if( SelectRateRandNum < GetAiData()->m_stSkillRate[1] )
            {
                if( IsSkill2CanUse() )
                { cSel = 1; }
                else
                { cSel = 0; }
            }
            else if( SelectRateRandNum < GetAiData()->m_stSkillRate[2] )
            {
                if( IsSkill3CanUse() )
                { cSel = 2; }
                else
                { cSel = 0; }
            }
            else
            {
                cSel = 0;
            }

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
            if (IsNormalAttack(GetAiData()->m_iSkillId[cSel]))
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
    }
    else
    {
        ThinkRouteMove();
    }
}

void MonsterRoute::ThinkIdle()
{
    if ( HaveCanAttackCharId() || HaveTryToAttackCharId() )
    { LostAttackTarget(); }

    if ( GetAttackCharCount() == 0 || !IsInRange())
    { // 没有攻击自身的人 或者 不在区域内

        // 如果当前还有有仇恨的玩家，则把九宫格的仇恨清掉
        if ( GetAttackCharCount() != 0)
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

            // 清空LUA脚本变量
            memset( m_nArray, 0, sizeof(m_nArray) );
            memset( m_bArray, 0, sizeof(m_bArray) );

            m_bIsFighting = false;
            TryChangeFightState( m_bIsFighting, eFighting );
        }

        ThinkRouteMove();
    }
}

//void MonsterRoute::MAlarmWhenBeAttack()
//{
//    return;
//    int nAreaID = GetCurArea();
//    GameStage* pGameStage = theGameWorld.GetStageById( GetMapID() );
//    if ( pGameStage == NULL )
//    { return; }
//
//    IDListTPL<9> list;
//    pGameStage->Get9AreaList(list, nAreaID);
//    int nCount = list.Count();
//    for (int i=0; i<nCount; i++)
//    {
//        GameArea* pArea = pGameStage->GetArea(list[i]);
//        if ( pArea == NULL )
//        { continue; }
//
//        IDListTPL<GameArea::constMaxCharacters>* pList = pArea->GetIDTable();
//        if ( pList == NULL )
//        { continue; }
//
//        int nCount = pList->Count();
//        for (int i=0; i<nCount; i++)
//        {
//            int nID = (*pList)[i];
//            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nID );
//            if ( pChar == NULL || !pChar->IsMonster() || !IsDistanceLess(GetTileX(), GetTileY(), pChar->GetTileX(), pChar->GetTileY(), GetIdleMoveViewSight()) )
//            { continue; }
//
//            MonsterRoute* pAiChar = static_cast<MonsterRoute*>(pChar);
//
//            //设置好怪物战斗视野以及战斗视野结束时间(目前程序内写死2秒后视野恢复)
//            pAiChar->SetViewSight( pAiChar->GetFightViewSight() );
//            pAiChar->SetFightViewEndTime( HQ_TimeGetTime() );
//        }
//    }
//}

void MonsterRoute::ThinkRouteMove()
{
    // 没有移动能力
    if ( !IsHaveMoveAbility() )
    { return; }

    if (_endPassiveTimeRecord != 0 && GameTime::IsPassCurrentTime( _endPassiveTimeRecord, endPassiveTimeConfig ) )
    {
        _endPassiveTimeRecord = 0;
        SetPassiveAttack(bPassiveConfig);
    }

    bool bNeedCallMove = false;
    
    if ( IsBeginPosMove() )
    {  // 如果没有目标点
        SMovePos* pMovePos = GetBeginPos();
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
            // 处理上一轮的结g过
            SMovePos* pMovePos = NULL; 
            if ( GetAiData()->lastIdleX != 0 )
            { // 追击前的位置不为0 表示到达追击前的位置
                ClearOutOfRouteRecord();
                pMovePos = GetMovePos( 0 );
            }
            else
            {
                pMovePos = GetMovePos( 1 );
            }
            
            // 开始下一轮的命令
            if ( pMovePos == NULL )
            { // 到达终点
                _bFinalArrive = true;
                return; 
            }
            _moveTargetPos.x = pMovePos->fX + _posXOff;
            _moveTargetPos.y = pMovePos->fY + _posYOff;
            _moveTargetPos.z = pMovePos->fZ;

            bNeedCallMove = true;            
        }
        else
        { // 在终点
            if ( _bOutOfRoute )
            { // 被引出去了
                // 触发行为
                _moveTargetPos.x = GetAiData()->lastIdleX;
                _moveTargetPos.y = GetAiData()->lastIdleY;
                _moveTargetPos.z = GetFloatZ();

                _bOutOfRoute  = false;
                bNeedCallMove = true;
            }
            else
            { // 回到终点了
                // 处理上一轮结果
                if ( GetAiData()->lastIdleX != 0 )
                { ClearOutOfRouteRecord(); }
            }
        }
    }
    else if ( !_bArriveTargetPos )
    { // 如果还没到 同时离开过指定路线 (被人引出去) 拿当前的点
        if ( _bOutOfRoute )
        {
            if ( !_bFinalArrive)
            { // 还没有到终点
                SMovePos* pMovePos = GetMovePos( 0 );
                if ( pMovePos == NULL )
                { 
                    assert( false );
                    return; 
                }

                D3DXVECTOR3 vAttackDistance( GetAiData()->lastIdleX - GetFloatX(), GetAiData()->lastIdleX - GetFloatY(), 0);
                D3DXVECTOR3 vRouteDistance( pMovePos->fX - GetFloatX(), pMovePos->fY - GetFloatY(), 0);
                float fAttackDistance = D3DXVec3Length( &vAttackDistance);
                float fRoutekDistance = D3DXVec3Length( &vRouteDistance);
                if ( fAttackDistance < fRoutekDistance )
                {
                    _moveTargetPos.x = GetAiData()->lastIdleX;
                    _moveTargetPos.y = GetAiData()->lastIdleY;
                    _moveTargetPos.z = GetFloatZ();
                }
                else
                {
                    _moveTargetPos.x = pMovePos->fX;
                    _moveTargetPos.y = pMovePos->fY;
                    _moveTargetPos.z = pMovePos->fZ;

                    // 置最新的保持点
                    GetAiData()->lastIdleX = pMovePos->fX;
                    GetAiData()->lastIdleY = pMovePos->fY;
                }
            }
            else
            { // 直接给IdleX的位置
                _moveTargetPos.x = GetAiData()->lastIdleX;
                _moveTargetPos.y = GetAiData()->lastIdleY;
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

void MonsterRoute::MoveAttackMoving( uint32 lapseTime )
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
        if( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001  )
        { ChangeMoveSpeed( m_fNormalMoveSpeed ); }   

        theGameWorld.OnRefreshNewArea( GetID() );

        if( m_bMoving )
        { // 移动中
            m_ushDirUnChangedCount = 0;
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

void MonsterRoute::MovePosMoving( uint32 lapseTime )
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

        if ( fDist <= 3.f)
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
        if ( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001 )
        { ChangeMoveSpeed( m_fNormalMoveSpeed ); }

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