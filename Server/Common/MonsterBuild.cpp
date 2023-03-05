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
    bool bCostTime = false;    // �Ƿ��Ѿ�ʹ�����ۻ�ʱ��
    m_dwProcessLogicCostTime += dwCostTime; // �ۻ�ʱ�� �еĵط�����ÿ���߼�֡�����õ�
    m_ExtendStatus.Process();
 
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

    // ������г���б�
    RemoveAllEnmityList( GetID() );

    // ��������ٻ��� ���� ���ٻ�����(����)ͬʱ�Ǳ�����ɱ��
    if ( !IsSummonMonster() || ( GetPetType() == EPT_Protect && GetKiller() != NULL && GetKiller()->GetID() != GetSummonMasterID() ) )
    {
        GetDropItemManager().MonsterDeath( this, GetKiller() );
    }

    // ���������ű�
    CallDeadScript();

    ProcessCampMonsterDeath();

    // ��������
    SetStatus( CS_DIEING );

    // ����ֱ�ӵ���exit���� ��������������ܲ�����������
    ExitWorldByPushMsg();
}

//////////////////////////////////////////////////////////////////////////
const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // ��޼���ˢ��ʱ��

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

//���/�Ƴ�����б��ж���
bool MonsterBuild::AddEnmityList(GameObjectId nID, unsigned int nEnmity)
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


//���/���ٳ��
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
                pChar->ClearTryToAttackCharEnmity();// �����ﵱǰ���Ŀ���ID���
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

//ˢ�³��
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

        // ��Ϊ���涼����AIBaseCharacterǿתpChar,�����ж�
        if( !pChar->IsMonster() )
        { continue; }

        MonsterBase* pCharAI = (MonsterBase*)pChar;
        unsigned int lastEnmity  = m_enmityList[i].nEnmity;
        unsigned int nViewEnmity = pCharAI->GetViewEnmity();
        unsigned int nEnmityRate = pCharAI->GetEnmityRate();

        if ( GameTime::IsPassCurrentTime( dwCurrTime, m_dwLastDecEnmityTime, MONSTERENMITY_REFRESHTIME ) )
        {   
            bUpdateDecEnmityTime = true;

            // �����
            if (m_enmityList[i].nEnmity > 0)
            {
                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate*nEnmityRate*0.001f;
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
            //������Ǳ������������Ұ�������
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
