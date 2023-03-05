#include "MonsterPet.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"

//////////////////////////////////////////////////////////////////////////
const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // ��޼���ˢ��ʱ��

SEnmity& MonsterPet::EnmityList(int nNum)
{
    return m_enmityList[nNum];
}

unsigned int MonsterPet::GetEnmity(unsigned int nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        { return m_enmityList[i].nEnmity; }
    }
    return ENMITY_NOTINLIST;
}

bool MonsterPet::SetEnmity(unsigned int nID, unsigned int nEnmity)
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
bool MonsterPet::AddEnmityList(unsigned int nID, unsigned int nEnmity)
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

    if (nEnmity > 0 && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight) )
    { pChar->AddAttackCharacter( GetID() );}

    OnEnmityNumChange();

    return true;
}

bool MonsterPet::RemoveEnmityList(unsigned int nID)
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID == nID)
        {
            m_enmityList[i].nID = NULLID;
            if (m_enmityList[i].nEnmity > 0)
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nID );
                if (pChar == NULL || (!pChar->IsMonster() && pChar->GetObjType() != Object_NpcFight))
                { return false; }

                pChar->DecAttackCharacter( GetID() );
            }
            return true;
        }
    }
    return false;
}

void MonsterPet::RemoveAllEnmityList(unsigned int nId)
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

bool MonsterPet::UpdateDecEnmityRate(unsigned int nID)
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
bool MonsterPet::AddEnmity(unsigned int nID, unsigned int nEnmity)
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

bool MonsterPet::DecEnmity(unsigned int nID, unsigned int nEnmity)
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
                    BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
                    if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ))
                    { pChar->DecAttackCharacter( GetID() ); }
                }
                m_enmityList[i].nEnmity = 0;
            }
            return true;
        }
    }
    return false;
}



unsigned int MonsterPet::GetDamageEnmity(unsigned int nID)
{
    return ENMITY_NOTINLIST;
}

bool MonsterPet::SetDamageEnmity(unsigned int nID, unsigned int nEnmity)
{
    return true;
}

bool MonsterPet::AddDamageEnmity(unsigned int nID, unsigned int nEnmity)
{
    return true;
}

bool MonsterPet::DecDamageEnmity(unsigned int nID, unsigned int nEnmity)
{
    return true;
}

void MonsterPet::ClearAllEnmity()
{
    for (int i=0; i<EnmityNum; i++)
    {
        if (m_enmityList[i].nID != NULLID && m_enmityList[i].nEnmity > 0)
        {
            BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
            if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ) )
            {
                pChar->DecAttackCharacter( GetID() );
                pChar->ClearTryToAttackCharEnmity();// �����ﵱǰ���Ŀ���ID���
            }
        }
        m_enmityList[i].nEnmity = 0;
    }
}

void MonsterPet::AddAllEnmity(unsigned int nEnmity)
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
            BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
            if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight))
            { pChar->AddAttackCharacter( GetID() ); }
        }
    }
}

void MonsterPet::DecAllEnmity(unsigned int nEnmity)
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
                BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
                if (pChar != NULL && (pChar->IsMonster() || pChar->GetObjType() == Object_NpcFight ) )
                {
                    pChar->DecAttackCharacter( GetID() );
                }
            }
            m_enmityList[i].nEnmity = 0;
        }
    }
}

bool MonsterPet::IsHaveEnmity()
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

short MonsterPet::GetNearestEnmityChar( D3DXVECTOR3 vSelfPos, int nSelfCountry )
{
    GameCharID NearestEnmityCharID = -1;
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
                    MonsterBaseEx* pAiChar = static_cast<MonsterBaseEx*>( pChar );
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

short MonsterPet::GetMaxEnmityChar()
{
    GameCharID MaxEnmityCharID = -1;
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
                    MonsterBaseEx* pAiChar = static_cast<MonsterBaseEx*>( pChar );
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

bool MonsterPet::AddTargetEnmityToMe(unsigned int nID,unsigned int nEnmity)
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
void MonsterPet::RefreshEnmity()
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

        if ( pChar->IsPlayer() && pChar->GetID() == GetSummonMasterID() )
        {// �����ɫ�����ˣ��򲻼������б�
            m_enmityList[i].nID = NULLID;
            continue;
        }

        // ��Ϊ���涼����AIBaseCharacterǿתpChar,�����ж�
        if( !pChar->IsMonster() )
        { continue; }

        MonsterBaseEx* pCharAI = (MonsterBaseEx*)pChar;
        unsigned int lastEnmity  = m_enmityList[i].nEnmity;
        unsigned int nViewEnmity = pCharAI->GetViewEnmity();
        unsigned int nEnmityRate = pCharAI->GetEnmityRate();

        if ( GameTime::IsPassCurrentTime( dwCurrTime, m_dwLastDecEnmityTime, MONSTERENMITY_REFRESHTIME ) )
        {   
            bUpdateDecEnmityTime = true;

            // �����
            if (m_enmityList[i].nEnmity > 0)
            {
                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate * nEnmityRate * DEF_THOUSANDTH;
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
            if ( !pCharAI->IsPassiveAttack() )
            {
                int nViewSight = pCharAI->GetViewSight() + ( pCharAI->GetLevel() - GetLevel()) * ENMITY_RATE ;
                if (nViewSight < ENMITY_MIN_VIEWSIGHT)
                {
                    nViewSight = ENMITY_MIN_VIEWSIGHT;
                }

                //�������Ұ�ڲ��ҳ��Ϊ0�������100;
                if ( IsDistanceLess(pChar->GetTileX(), pChar->GetTileY(), GetTileX(), GetTileY(), nViewSight))
                {
                    //if( pChar->GetCharacterFriend(this) < 1 )
                    {
                        m_enmityList[i].nEnmity = nViewEnmity;
                        m_enmityList[i].nDecEnmityRate = nViewEnmity;
                    }
                }
            }
        }
        else
        {
            if (m_enmityList[i].nEnmity < nViewEnmity)
            {
                if (!pCharAI->IsPassiveAttack() || ( pCharAI->IsPassiveAttack() && pCharAI->IsInBaseEnmityRange()))
                {
                    //����Ѿ��������ж��Ƿ񱻶��֣�ֻҪ����Ұ�ھͱ�֤������nEnmityֵ
                    int nViewSight = pCharAI->GetViewSight() + ( pCharAI->GetLevel() - GetLevel()) * ENMITY_RATE ;
                    if (nViewSight < ENMITY_MIN_VIEWSIGHT)
                    { nViewSight = ENMITY_MIN_VIEWSIGHT; }

                    //�������Ұ�ڲ��ҳ��Ϊ0�������100;
                    if ( IsDistanceLess(pChar->GetTileX(), pChar->GetTileY(), GetTileX(), GetTileY(), nViewSight))
                    {
                        m_enmityList[i].nEnmity = nViewEnmity;
                        m_enmityList[i].nDecEnmityRate = nViewEnmity;
                    }
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

void MonsterPet::OnEnmityNumChange()
{
}

void MonsterPet::OnEnmityValueChanged( unsigned short id, unsigned int value)
{
}

//////////////////////////////////////////////////////////////////////////
void MonsterPet::OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig )
{
    if( !pAttacker)
    { return; }

    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig);

    StartUpAI();
    if ( !HaveCanAttackCharId() )
    { _disableControlThinkTime = true; }

    //��¼����һ��δ������ǰ�Ŀ���λ��
    if (GetAiData()->lastIdleX == 0)
    {
        GetAiData()->lastIdleX = GetFloatX();
        GetAiData()->lastIdleY = GetFloatY();
    }
}

bool MonsterPet::OnThink()
{
    if ( !MonsterBaseEx::OnThink() )
    { return true; }

    BaseCharacter* pSummoner = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
    if( pSummoner && pSummoner->IsPlayer() && !pSummoner->IsDead() )
    {
        //������˱���֤������������ɱ
        //if (!static_cast<GamePlayer*>(pChar)->m_graphiccodecheck.IsCanMove())
        //{ Murder(); }

        GamePlayer* pPlayer = static_cast<GamePlayer*>( pSummoner );
        if ( IsPet() )
        { // ���� �����
            FlyToTheSummonMaster();

            if( HaveAskToAttackTargetId() )
            {   
                BaseCharacter* Target = theRunTimeData.GetCharacterByID( m_AskToAttackTargetID );
                if (!MasterOutOfTarget(pSummoner,Target,60))
                { LockTarget( m_AskToAttackTargetID ); }
                else
                { ClearCanAttackCharId(); }
            }
            else
            {
                short shPetType = ePetCommandAI;

                switch ( GetPetType())
                {
                case EPT_Skill:
                    { shPetType = pPlayer->GetSkillPetAIType( GetID() );}
                    break;
                case EPT_Capture:
                    { shPetType = pPlayer->GetCapturePetAIType();}
                    break;
                }

                switch ( shPetType )
                {
                case ePetAttackAI:
                    {
                        // ���� m_AskToAttackTargetID Ŀ��
                        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
                        if( pChar != NULL )
                        { m_AskToAttackTargetID = pChar->GetLockID();  }

                        if( HaveAskToAttackTargetId() )
                        { 
                            uint32 enmity = pChar->GetEnmity( m_AskToAttackTargetID );
                            if ( enmity != 0 && enmity != ENMITY_NOTINLIST )
                            { LockTarget( m_AskToAttackTargetID );  }
                            else
                            { ClearAskToAttackTargetId();}   
                        }
                        else
                        { // �������һ����
                            //m_AskToAttackTargetID = GetNearestEnmityChar( GetPos(), GetCountry() );
                            //if( m_AskToAttackTargetID >= 0 )
                            //{ LockTarget( m_AskToAttackTargetID ); }
                        }
                    }
                    break;
                case ePetDefendAI:
                    { // ����ģʽ �����κη�Ӧ���� ֻ������ 
                        //m_AskToAttackTargetID = pSummoner->GetMaxEnmityChar();
                        //if( m_AskToAttackTargetID >= 0 )
                        //{ LockTarget( m_AskToAttackTargetID ); }
                    }
                    break;
                }
            }
        }

        if( HaveCanAttackCharId() )
        {
            m_bIsFighting = true;
            TryChangeFightState( m_bIsFighting, eFighting );
            BaseCharacter* pTarget = GetCanAttackChar();

            if( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() || pTarget->GetBuffManager()->IsHide() )
            { // Ŀ�겻���� Ŀ�겻��һ����ͼ Ŀ���Ѿ����� Ŀ��������״̬
                LostAttackTarget();
                return false;
            }

            if (!IsPet())
            { // ���ǳ���
                LostAttackTarget();
                ClearAskToAttackTargetId();
                return false;
            }

            if( pTarget->IsPlayer() && IsAttackTargetIsProtectChar() )
            { // �������
                LostAttackTarget();
                return false;
            }

            _isNeedMove = false;

            if (!_SkillTaskManager.IsTaskEmpty())
            { return false; }

            uint16 skillId    = GetAiData()->GetCurrentSelectSkillId();
            uint8  skillLevel = GetAiData()->GetCurrentSelectSkillLevel();

            if ( skillId == 0)
            {
                SetStatus( CS_IDLE );
                return false;
            }

            // �õ���ǰѡ��ļ���
            if ( IsNormalAttack( skillId ) )
            {
                if ( !_buffManager.IsCanUsePhysicsSkill() )
                {
                    SetStatus( CS_IDLE );
                    return false;
                }
            }
            else
            {
                if ( !_buffManager.IsCanUseMagicSkill() )
                {
                    SetStatus( CS_IDLE );
                    return false;
                }
            }

            m_pCurSkill = GettheItemDetail().GetSkillByID( skillId, skillLevel );
            if ( NULL == m_pCurSkill )
            {
                SetStatus( CS_IDLE );
                return false;
            }

            SetCurSkillIndex( GetAiData()->GetCurrentSelectSkillIndex() );
            SetCurSkillLevel( GetAiData()->GetCurrentSelectSkillIndex() );
            m_stCurAttackRange = m_pCurSkill->fRangeCanCast;

            float fRangeCorrect = monsterCastCorrect;

            if ( IsInAttackRange( pTarget, m_pCurSkill, fRangeCorrect ) )
            { // �ڹ�����Χ��
                if( GetAiData()->GetCurrentSelectSkillIndex() > 0 )
                {
                    m_stCurAiTactic = EAISelectTaskType_TryUseSkill;
                }
                else
                {
                    m_stCurAiTactic = EAISelectTaskType_TryAttackTarget;
                }
                m_bClosingToTarget = false;
            }
            else
            {
                if (  m_fIdleMoveSpeed > 0.0 || m_fNormalMoveSpeed > 0.0 )
                { m_bClosingToTarget = true; }

                //SendClosingToTarget( pTarget->GetControl()->GetID() );
            }

            pTarget = NULL;
        }
        else
        {
            if( HaveAskToAttackTargetId() )
            { ClearAskToAttackTargetId(); }

            if( IsHaveMoveAbility())
            { FollowTheSummonMaster( pSummoner ); }

            m_bIsFighting = false;
            TryChangeFightState( m_bIsFighting, eFighting );
        }
    }
    else
    { //�Ҳ����ٻ���
        Murder();
    }
    return true;
}

bool MonsterPet::OnMove( uint32 lapseTime )
{
    // ��ʼ��ͬ������ƶ�
    if( HaveCanAttackCharId() )
    { MoveAttackMoving( lapseTime ); }
    else
    { MovePosMoving( lapseTime ); }
    return true;
}

void MonsterPet::MoveAttackMoving( uint32 lapseTime )
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
        if ( _buffManager.IsRafferty() || _buffManager.IsRandRun())
        { // ����״̬�������
            float rX = rand() % 20;
            float rY = rand() % 20;

            int op = rand() % 4 ;
            switch(op)
            {
            case 0:
                {
                    vTargetPos.x = GetFloatX() + rX;
                    vTargetPos.y = GetFloatY() + rY;
                    vTargetPos.z = 0;
                }
                break;
            case 1:
                {
                    vTargetPos.x = GetFloatX() - rX;
                    vTargetPos.y = GetFloatY() + rY;
                    vTargetPos.z = 0;
                }
                break;
            case 2:
                {
                    vTargetPos.x = GetFloatX() - rX;
                    vTargetPos.y = GetFloatY() - rY;
                    vTargetPos.z = 0;
                }
                break;
            case 3:
                {
                    vTargetPos.x = GetFloatX() + rX;
                    vTargetPos.y = GetFloatY() - rY;
                    vTargetPos.z = 0;
                }
                break;
            default:
                {
                    vTargetPos.x = GetFloatX();
                    vTargetPos.y = GetFloatY();
                    vTargetPos.z = 0;
                }
            }
        }
        else
        {
            vTargetPos.x = pTarget->GetFloatX();
            vTargetPos.y = pTarget->GetFloatY();
            vTargetPos.z = 0;
        }        

        D3DXVECTOR3 vecDistance( vTargetPos.x - GetFloatX(), vTargetPos.y - GetFloatY(), 0 );
        float fDist = D3DXVec3Length( &vecDistance );
        D3DXVec3Normalize( &dir, &vecDistance );

        if( m_bClosingToTarget )
        { // ��Ҫ����Ŀ��
            float fRange = pTarget->GetBodySize() + GetBodySize();
            float fMoveStep = GetMoveSpeed() * ( 0.001 * lapseTime );
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

    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 1000 ) )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
        if ( IsHaveMoveAbility() && abs( GetMoveSpeed() - pChar->GetMoveSpeed() ) >= 0.0001)
        { ChangeMoveSpeed( pChar->GetMoveSpeed() ); }

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
                int nRandNumber = theRand.rand32()%( 1 + m_ushDirUnChangedCount );
                if( nRandNumber > 1 )
                {
                    SetDirX( dir.x );
                    SetDirY( dir.y );
                    m_ushDirUnChangedCount = 0;
                }
                else
                {
                    m_ushDirUnChangedCount++;
                }
            }
            SendVerifyPos( GetFloatX(), GetFloatY() );
        }

        m_dwSendMoveMessageTime = theGameWorld.g_dwLastWorldProcessTime;
    }
}

void MonsterPet::MovePosMoving( uint32 lapseTime )
{
    // û�й���Ŀ��
    if( _isNeedMove )
    { // �����Ҫ�ƶ�

        D3DXVECTOR3 vecDistance( _moveTargetPos.x - GetFloatX(), _moveTargetPos.y - GetFloatY(), 0 );
        float fDist = D3DXVec3Length( &vecDistance );
        D3DXVECTOR3 vDir(0,0,0);
        D3DXVec3Normalize( &vDir, &vecDistance );

        float fActualMoveDist = GetMoveSpeed()*((float)lapseTime * 0.001);
        if( fActualMoveDist >= fDist )
        {
            fActualMoveDist = fDist;
            m_bMoving   = false;
            _isNeedMove = false;
        }
        else
        {
            m_bMoving = true;
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
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetSummonMasterID() );

        Assert(pChar);  // ���pCharΪ�գ�֤��ǰ���߼�����

        if ( pChar == NULL )
        { // �߻��� createmonster ����ᵼ������Ϊ��
            Murder();
            return;
        }

        float fCurrentNormalMoveSpeed = 0.0f;
        if ( pChar != NULL )
        { fCurrentNormalMoveSpeed = pChar->GetMoveSpeed(); }
        else
        { fCurrentNormalMoveSpeed = m_fNormalMoveSpeed; }

        if ( m_fNormalMoveSpeed !=0 && abs( GetCharFightAttr()->moveSpeed.base - fCurrentNormalMoveSpeed ) >= 0.0001)
        { ChangeMoveSpeed( fCurrentNormalMoveSpeed ); } 

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