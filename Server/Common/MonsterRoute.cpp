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
const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // ��޼���ˢ��ʱ��

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

//���/�Ƴ�����б��ж���
bool MonsterRoute::AddEnmityList(GameObjectId nID, unsigned int nEnmity)
{   
    BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID(nID);
    if (pChar == NULL)
    { return false; }

    // �����Ƿ��Ѿ����б���
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


//���/���ٳ��
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
                        //�һ���֤������Ϊ���Ҳʩ���˼���,�Լ���ս��ʱ��
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
                pChar->ClearTryToAttackCharEnmity();// �����ﵱǰ���Ŀ���ID���
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

//ˢ�³��
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
        { // ������治��·���� ���������Լ��ĳ��
            m_enmityList[i].nID = NULLID;
            continue;
        }

        // ��Ϊ���涼����AIBaseCharacterǿתpChar,�����ж�
        if( !pChar->IsMonster() )
        { continue; }

        MonsterBase* pCharAI = (MonsterBase*)pChar;

        unsigned int lastEnmity = m_enmityList[i].nEnmity;
        unsigned int nViewEnmity = pCharAI->GetViewEnmity();
        unsigned int nEnmityRate = pCharAI->GetEnmityRate();

        if ( GameTime::IsPassCurrentTime( dwCurrTime, m_dwLastDecEnmityTime, MONSTERENMITY_REFRESHTIME ) )
        {
            bUpdateDecEnmityTime = true;

            // �����
            if ( m_enmityList[i].nEnmity > 0 )
            {
                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate * nEnmityRate * 0.001f;
                if (nDecEnmity < 1)
                { nDecEnmity = 1; }

                //�������ȡ�������޵���ֵ
                if (m_enmityList[i].nEnmity > nDecEnmity)
                { m_enmityList[i].nEnmity -= nDecEnmity; }
                else
                { m_enmityList[i].nEnmity = 0; }
            }
        }

        if (m_enmityList[i].nEnmity == 0 && lastEnmity == 0)
        {   
            if ( !pCharAI->IsPassiveAttack() )
            { // ������Ǳ������������Ұ�������
                UpdateViewEnmity( i, pCharAI );
            }
        }
        else
        {
            if ( m_enmityList[i].nEnmity < nViewEnmity )
            {
                if ( !pCharAI->IsPassiveAttack() || ( pCharAI->IsPassiveAttack() && pCharAI->IsInBaseEnmityRange()) )
                { //����Ѿ��������ж��Ƿ񱻶��֣�ֻҪ����Ұ�ھͱ�֤������nEnmityֵ
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
    { // �Լ�������Ӫ ����
        return;
    }

    // ͬ��Ӫ�Ĳ��ӳ��
    if ( pTargetMonster->GetFightCamp() == GetFightCamp() )
    { return;}

    int nViewSight = pTargetMonster->GetViewSight() + ( pTargetMonster->GetLevel() - GetLevel() ) * ENMITY_RATE;
    if ( nViewSight < ENMITY_MIN_VIEWSIGHT )
    { nViewSight = ENMITY_MIN_VIEWSIGHT;}

    //�������Ұ�ڲ��ҳ��Ϊ0�������100;
    if ( IsDistanceLess( pTargetMonster->GetTileX(), pTargetMonster->GetTileY(), GetTileX(), GetTileY(), nViewSight ) )
    { // �ָ����
        m_enmityList[ index ].nEnmity        = pTargetMonster->GetViewEnmity();
        m_enmityList[ index ].nDecEnmityRate = pTargetMonster->GetViewEnmity(); // ȡ���İٷ�ʮ��˥����
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
    // ��û�����ÿ�ʼ�ƶ��� û���յ�
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
    { // ���Բ���������Ϊ
        ThinkAttack();
    }
    else
    { // ���Բ���Idle��̬��Ϊ �ӹ���̬���� һֱ��û�й���̬
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
    // ��ʼ��ͬ������ƶ�
    if( HaveCanAttackCharId() )
    { MoveAttackMoving( lapseTime ); }
    else
    { MovePosMoving( lapseTime ); }
    return true;
}

bool MonsterRoute::OnSuccessLockTarget()
{
    //��¼����һ��δ������ǰ�Ŀ���λ��
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
        //���óɱ�����
        if (changePassiveConfig != 0)
        { SetPassiveAttack( true ); }

        m_bIsFighting = true;
        TryChangeFightState( m_bIsFighting, eFighting );
        MAlarmWhenBeAttack();
    }

    // �����ǰ����Ŀ���Ҳ����ˣ�������ȥ
    if ( theRunTimeData.GetCharacterByID(GetTryToAttackCharId()) == NULL)
    {
        DecAttackCharacter( GetTryToAttackCharId());
        SetAttackCharEnmity(0);
        LostAttackTarget();
        return;
    }

    // ˼�����Թ�����Char
    LockTarget( GetTryToAttackCharId() );

    // ��Ŀ���óɵ�һ������������
    short stFirstAttackId = GetFirstValidAttacker();
    if ( stFirstAttackId != -1 && stFirstAttackId != GetTryToAttackCharId() )
    { // ��һ�����������Object����,�Һ����ڹ��������Object��һ��
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( stFirstAttackId );
        if ( pChar != NULL && pChar->IsPlayer() )
        {
            GamePlayer* pPlayer = (GamePlayer*)pChar;
            uint32 enmity = pPlayer->GetEnmity(GetID());
            if ( enmity == 0|| enmity == ENMITY_NOTINLIST)
            { UpdateFirstAttack( GetTryToAttackCharId() ); }
        }
    }

    // �����ȷ�Ͽ��Թ�����Ŀ��
    if( HaveCanAttackCharId() )
    {
        BaseCharacter* pTarget = GetCanAttackChar();

        if( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() )
        {
            LostAttackTarget();
            return;
        }

        _isNeedMove  = false;  // ����׷����¼
        _bOutOfRoute = true;

        if (!_SkillTaskManager.IsTaskEmpty())
        { return; }

        int iLevel = 1;
        int cSel = 0;
        int SelectRateRandNum = 0;
        int nCount = 0;
        CItemDetail::SItemSkill* pSkill = NULL;

        // ѭ�����ҿ��õļ���
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

            // �����ܲ��ܴ�
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
    { // û�й���������� ���� ����������

        // �����ǰ�����г�޵���ң���ѾŹ���ĳ�����
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
                        //����ǹ��ﲢ�����Լ�4������
                        //�򽫹�����Ұ��Ϊ������Ұ
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
            { // ��ʱ�����
                _endPassiveTimeRecord = HQ_TimeGetTime(); 
            }
            else
            { // ûʱ�����
                _endPassiveTimeRecord = 0;                 
                SetPassiveAttack( bPassiveConfig ); // ���ϻָ�
            }

            // ���LUA�ű�����
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
//            //���úù���ս����Ұ�Լ�ս����Ұ����ʱ��(Ŀǰ������д��2�����Ұ�ָ�)
//            pAiChar->SetViewSight( pAiChar->GetFightViewSight() );
//            pAiChar->SetFightViewEndTime( HQ_TimeGetTime() );
//        }
//    }
//}

void MonsterRoute::ThinkRouteMove()
{
    // û���ƶ�����
    if ( !IsHaveMoveAbility() )
    { return; }

    if (_endPassiveTimeRecord != 0 && GameTime::IsPassCurrentTime( _endPassiveTimeRecord, endPassiveTimeConfig ) )
    {
        _endPassiveTimeRecord = 0;
        SetPassiveAttack(bPassiveConfig);
    }

    bool bNeedCallMove = false;
    
    if ( IsBeginPosMove() )
    {  // ���û��Ŀ���
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
    { // �������Ŀ���������һ��Ŀ���
        if ( !_bFinalArrive )
        { // ��û�е����յ�
            // ������һ�ֵĽ�g��
            SMovePos* pMovePos = NULL; 
            if ( GetAiData()->lastIdleX != 0 )
            { // ׷��ǰ��λ�ò�Ϊ0 ��ʾ����׷��ǰ��λ��
                ClearOutOfRouteRecord();
                pMovePos = GetMovePos( 0 );
            }
            else
            {
                pMovePos = GetMovePos( 1 );
            }
            
            // ��ʼ��һ�ֵ�����
            if ( pMovePos == NULL )
            { // �����յ�
                _bFinalArrive = true;
                return; 
            }
            _moveTargetPos.x = pMovePos->fX + _posXOff;
            _moveTargetPos.y = pMovePos->fY + _posYOff;
            _moveTargetPos.z = pMovePos->fZ;

            bNeedCallMove = true;            
        }
        else
        { // ���յ�
            if ( _bOutOfRoute )
            { // ������ȥ��
                // ������Ϊ
                _moveTargetPos.x = GetAiData()->lastIdleX;
                _moveTargetPos.y = GetAiData()->lastIdleY;
                _moveTargetPos.z = GetFloatZ();

                _bOutOfRoute  = false;
                bNeedCallMove = true;
            }
            else
            { // �ص��յ���
                // ������һ�ֽ��
                if ( GetAiData()->lastIdleX != 0 )
                { ClearOutOfRouteRecord(); }
            }
        }
    }
    else if ( !_bArriveTargetPos )
    { // �����û�� ͬʱ�뿪��ָ��·�� (��������ȥ) �õ�ǰ�ĵ�
        if ( _bOutOfRoute )
        {
            if ( !_bFinalArrive)
            { // ��û�е��յ�
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

                    // �����µı��ֵ�
                    GetAiData()->lastIdleX = pMovePos->fX;
                    GetAiData()->lastIdleY = pMovePos->fY;
                }
            }
            else
            { // ֱ�Ӹ�IdleX��λ��
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

    // ȷ����������Ҳŷ���,���������
    if ( AreaHavePlayer() )
    {
        MsgUnPlayerMovingToPos msg;
        msg.SetLevel( level_normal ); // �����е����ȼ�
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
        { // ��Ҫ����Ŀ��
            float fRange = pTarget->GetBodySize() + GetBodySize();
            float fMoveStep = GetMoveSpeed()*((float)lapseTime * 0.001);
            if( fRange <= 0.001f )
            { fRange = 0.001f; }

            if( fDist > fRange )
            { // �Ƿ���Ҫ�ƶ�
                if( fMoveStep >= (fDist - fRange) )
                { // ����ƶ�������Ҫ�ƶ��ľ���
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
        { // ����Ҫ����Ŀ��
            m_bMoving = false;
        }
    }

    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime,1000 ) )
    {
        if( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001  )
        { ChangeMoveSpeed( m_fNormalMoveSpeed ); }   

        theGameWorld.OnRefreshNewArea( GetID() );

        if( m_bMoving )
        { // �ƶ���
            m_ushDirUnChangedCount = 0;
            D3DXVECTOR3 vCusPos( GetFloatX(), GetFloatY(), WORLD_HEIGHT );                                
            SendClosingToTarget( pTarget->GetID(), vCusPos );
        }
        else
        { // ������ʱ��
            if ( IsHaveMoveAbility() )
            { // ���ƶ������Ĳ�ת��
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
    // û�й���Ŀ��
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
        { // ��ǰ��
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
    { // �ƶ���ϢƵ�� ������ ����GateServer����
        if ( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001 )
        { ChangeMoveSpeed( m_fNormalMoveSpeed ); }

        theGameWorld.OnRefreshNewArea( GetID() );

        if ( AreaHavePlayer() )
        {
            if ( m_bMoving )
            {
                // ���ƶ���
                MsgUnPlayerMovingToPos msg;                    
                msg.header.stID = GetID();
                msg.vStartPos.x = GetFloatX();
                msg.vStartPos.y = GetFloatY();
                msg.vStartPos.z = WORLD_HEIGHT;
                msg.vEndPos     = _moveTargetPos;
                GettheServer().SendMsgToView( &msg, GetID(), true );
            }
            else
            { // ����������
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