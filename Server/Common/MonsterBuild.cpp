#include "MonsterBuild.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"
#include "DropItemManager.h"

MonsterBuild::MonsterBuild()
{
}

MonsterBuild::~MonsterBuild()
{

}

void MonsterBuild::Run( DWORD dwCostTime )
{
    if ( m_xDisappearTimer.DoneTimer() )
    { Exit(); }

    RefreshEnmity();

    BaseCharacter::Run(dwCostTime);
}

void MonsterBuild::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bool bCostTime = false;    // 是否已经使用了累积时间
    m_dwProcessLogicCostTime += dwCostTime; // 累积时间 有的地方不是每个逻辑帧都调用的
    m_ExtendStatus.Process();
 
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

void MonsterBuild::OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig )
{
    if( !pAttacker)
    { return; }
}

void MonsterBuild::OnDeath()
{
    MsgSawSomeoneDead msg;
    msg.header.stID = GetID();

    if ( AreaHavePlayer() )
    { GettheServer().SendMsgToView( &msg, GetID(), true );}

    // 清空所有仇恨列表
    RemoveAllEnmityList( GetID() );

    // 如果不是召唤物 或者 是召唤物是(骠车)同时是被敌人杀死
    if ( !IsSummonMonster() || ( GetPetType() == EPT_Protect && GetKiller() != NULL && GetKiller()->GetID() != GetSummonMasterID() ) )
    {
        GetDropItemManager().MonsterDeath( this, GetKiller() );
    }

    // 调用死亡脚本
    CallDeadScript();

    ProcessCampMonsterDeath();

    // 设置死亡
    SetStatus( CS_DIEING );

    // 不能直接调用exit函数 否则怪物死亡不能播放死亡动作
    ExitWorldByPushMsg();
}

//////////////////////////////////////////////////////////////////////////
const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // 仇恨减少刷新时间

SEnmity& MonsterBuild::EnmityList(int nNum)
{
    return m_enmityList[nNum];
}

unsigned int MonsterBuild::GetEnmity(GameObjectId nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        { return m_enmityList[i].nEnmity; }
    }
    return ENMITY_NOTINLIST;
}

bool MonsterBuild::SetEnmity(GameObjectId nID, unsigned int nEnmity)
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
bool MonsterBuild::AddEnmityList(GameObjectId nID, unsigned int nEnmity)
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

    if (nEnmity > 0 && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
    { pChar->AddAttackCharacter( GetID() );}

    OnEnmityNumChange();

    return true;
}

bool MonsterBuild::RemoveEnmityList(GameObjectId nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        {
            m_enmityList[i].nID = NULLID;
            if (m_enmityList[i].nEnmity > 0)
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nID );
                if ( pChar == NULL || (!pChar->IsMonster() && pChar->GetObjType() != Object_NpcFight ))
                { return false; }

                pChar->DecAttackCharacter( GetID() );
            }
            return true;
        }
    }
    return false;
}

void MonsterBuild::RemoveAllEnmityList(GameObjectId nId)
{
    for (int i=0; i<EnmityNum; ++i)
    {
        if (m_enmityList[i].nEnmity > 0)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );            
            m_enmityList[i].nID = NULLID;
            if (pChar == NULL || (!pChar->IsMonster() && pChar->GetObjType() != Object_NpcFight ))
            { continue; }

            pChar->DecAttackCharacter( GetID() );
            pChar->ClearTryToAttackCharEnmity();
            pChar->ClearAttackerById(nId);
        }
    }
}

bool MonsterBuild::UpdateDecEnmityRate(GameObjectId nID)
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
bool MonsterBuild::AddEnmity(GameObjectId nID, unsigned int nEnmity)
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
                BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
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

bool MonsterBuild::DecEnmity(GameObjectId nID, unsigned int nEnmity)
{
    if (nEnmity == 0 || nID == NULLID)
    {
        return false;
    }

    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        {
            if (m_enmityList[i].nEnmity >= nEnmity)
            {
                m_enmityList[i].nEnmity -= nEnmity;
            }
            else
            {
                if (m_enmityList[i].nEnmity > 0)
                {
                    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
                    if (pChar != NULL && ( pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
                    { pChar->DecAttackCharacter( GetID() ); }
                }
                m_enmityList[i].nEnmity = 0;
            }
            return true;
        }
    }
    return false;
}



unsigned int MonsterBuild::GetDamageEnmity(GameObjectId nID)
{
    return ENMITY_NOTINLIST;
}

bool MonsterBuild::SetDamageEnmity(GameObjectId nID, unsigned int nEnmity)
{
    return true;
}

bool MonsterBuild::AddDamageEnmity(GameObjectId nID, unsigned int nEnmity)
{
    return true;
}

bool MonsterBuild::DecDamageEnmity(GameObjectId nID, unsigned int nEnmity)
{
    return true;
}

void MonsterBuild::ClearAllEnmity()
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID != NULLID && m_enmityList[i].nEnmity > 0)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
            if ( pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight) )
            {
                pChar->DecAttackCharacter( GetID() );
                pChar->ClearTryToAttackCharEnmity();// 将怪物当前仇恨目标的ID清除
            }
        }
        m_enmityList[i].nEnmity = 0;
    }
}

void MonsterBuild::AddAllEnmity(unsigned int nEnmity)
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

void MonsterBuild::DecAllEnmity(unsigned int nEnmity)
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
                if (pChar != NULL && ( pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ) )
                { pChar->DecAttackCharacter( GetID() ); }
            }
            m_enmityList[i].nEnmity = 0;
        }
    }
}

bool MonsterBuild::IsHaveEnmity()
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

GameObjectId MonsterBuild::GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry )
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
                    MonsterBase* pAiChar = static_cast<MonsterBase*>( pChar );
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

GameObjectId MonsterBuild::GetMaxEnmityChar()
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
                    MonsterBase* pAiChar = static_cast<MonsterBase*>( pChar );
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

bool MonsterBuild::AddTargetEnmityToMe(GameObjectId nID,unsigned int nEnmity)
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
void MonsterBuild::RefreshEnmity()
{
    if ( IsDead() )
    { return; }

    unsigned long dwCurrTime = HQ_TimeGetTime();
    if (m_dwLastDecEnmityTime > dwCurrTime)
    { m_dwLastDecEnmityTime = 0; }

    bool bUpdateDecEnmityTime = false;

    for (int i=0; i<EnmityNum; i++)
    {
        if ( m_enmityList[i].nID == NULLID)
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID(m_enmityList[i].nID);

        if (pChar == NULL /*|| !pChar->IsMonster()*/)
        {
            m_enmityList[i].nID = NULLID;
            continue;
        }

        // 因为下面都是用AIBaseCharacter强转pChar,必须判断
        if( !pChar->IsMonster() )
        { continue; }

        MonsterBase* pCharAI = (MonsterBase*)pChar;
        unsigned int lastEnmity  = m_enmityList[i].nEnmity;
        unsigned int nViewEnmity = pCharAI->GetViewEnmity();
        unsigned int nEnmityRate = pCharAI->GetEnmityRate();

        if ( GameTime::IsPassCurrentTime( dwCurrTime, m_dwLastDecEnmityTime, MONSTERENMITY_REFRESHTIME ) )
        {   
            bUpdateDecEnmityTime = true;

            // 减仇恨
            if (m_enmityList[i].nEnmity > 0)
            {
                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate*nEnmityRate*0.001f;
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
            //如果不是被动怪则进入视野触发仇恨
            if ( !pCharAI->IsPassiveAttack())
            {
                UpdateViewEnmity( i, pCharAI );
            }
        }
        else
        {
            if (m_enmityList[i].nEnmity < nViewEnmity)
            {
                if (!pCharAI->IsPassiveAttack() || ( pCharAI->IsPassiveAttack() && pCharAI->IsInBaseEnmityRange()))
                {
                    UpdateViewEnmity( i, pCharAI );
                }
            }
        }

        if ( lastEnmity == 0 && m_enmityList[i].nEnmity > 0 )
        { pCharAI->AddAttackCharacter( GetID() ); }
        else if ( lastEnmity > 0 && m_enmityList[i].nEnmity == 0 )
        { pCharAI->DecAttackCharacter( GetID() ); }

        if ( pCharAI->GetTryToAttackCharId() == GetID())
        { pCharAI->SetAttackCharEnmity(m_enmityList[i].nEnmity); }
        else
        {
            if ( pCharAI->GetTryAttackCharEnmity() < m_enmityList[i].nEnmity)
            {
                pCharAI->SetAttackCharEnmity( m_enmityList[i].nEnmity );
                pCharAI->SetTryToAttackCharId( GetID() );
            }
        }
    }

    if (bUpdateDecEnmityTime)
    { m_dwLastDecEnmityTime = HQ_TimeGetTime();}
}

void MonsterBuild::OnEnmityNumChange()
{
}

void MonsterBuild::OnEnmityValueChanged( GameObjectId id, unsigned int value)
{
}

//////////////////////////////////////////////////////////////////////////
void MonsterBuild::UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster )
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
