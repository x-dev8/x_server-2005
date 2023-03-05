#include "MonsterCountry.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"
#include "NpcFight.h"

//void MonsterCountry::OnBeAttacked( BaseCharacter* pAttacker, const CItemDetail::SItemSkill* pSkillConfig )
//{
//    if ( pAttacker == NULL || pSkillConfig == NULL )
//    { return; }
//
//    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig );
//
//    StartUpAI();
//    if ( !HaveCanAttackCharId() )
//    {
//        MAlarmWhenBeAttack();
//        _disableControlThinkTime = true;
//    }
//    // ��¼�ϴ�δ�������Ŀ���λ��
//    if ( GetAiData()->lastIdleX == 0 )
//    {
//        GetAiData()->lastIdleX = GetFloatX();
//        GetAiData()->lastIdleY = GetFloatY();
//    }
//}
//
//bool MonsterCountry::OnThink()
//{
//    if ( !MonsterBase::OnThink() )
//    { return true; }
//
//    if ( HaveTryToAttackCharId() && GetTryAttackCharEnmity() > 0 && IsInRange() )
//    {// ����п��Թ�����Ŀ�꣬�����г�ޣ������ڹ�����Χ,�򹥻�
//        ThinkAttack();
//    }
//    else
//    {// �����ǿ���
//        ThinkIdle();
//    }
//
//    if ( m_bLuaScriptLoaded )
//    {
//        try
//        {
//            LuaObject luaObject = m_LuaScript->GetGlobal("Event_Thinking");
//            if ( luaObject.IsFunction() )
//            { GetGlobalFun("Event_Thinking")(); }
//        }
//        catch (LuaPlus::LuaException& e)
//        {
//            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Monster %s AI Script Event_Thinking failed: %s", GetCharName(), e.GetErrorMessage() );
//            m_bLuaScriptLoaded = false;
//        }
//    }
//    return true;
//}
//
//bool MonsterCountry::OnMove( uint32 lapseTime )
//{
//    if ( HaveCanAttackCharId() )
//    { MoveAttackMoving( lapseTime); }
//    else
//    { MovePosMoving(lapseTime); }
//
//    return true;
//}
//
//void MonsterCountry::ThinkAttack()
//{
//    if ( !m_bIsFighting )
//    {// ���������ս��״̬
//        // ���óɱ�����
//        if ( changePassiveConfig != 0 )
//        { SetPassiveAttack(true); }
//
//        //m_bIsFighting = true;
//        //TryChangeFightState(m_bIsFighting, eFighting);
//        //MAlarmWhenBeAttack();
//    }
//
//    // �����ǰ�Ĺ���Ŀ���Ҳ�����
//    if ( theRunTimeData.GetCharacterByID(GetTryAttackCharEnmity()) == NULL )
//    {
//        if ( GetAttackCharCount() > 0 )
//        { DecAttackCharacter(GetTryToAttackCharId()); } // �ӹ�����������ɾ���ù�����
//        // �������Ϊ0����������Ŀ��
//        SetAttackCharEnmity(0);
//        LostAttackTarget();
//        return;
//    }
//
//    // ˼���õ���һ�����Թ�������
//    LockTarget( GetTryToAttackCharId() );
//    // ���ɹ������еĵ�һ������Ϊ�����Լ�����
//    short stFirstAttackId = GetFirstValidAttacker();
//    if ( stFirstAttackId != -1 && stFirstAttackId != GetTryToAttackCharId() )
//    {
//        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( stFirstAttackId );
//        if ( pChar != NULL && pChar->IsPlayer() )
//        {
//            GamePlayer* pPlayer = static_cast<GamePlayer*>(pChar);
//            uint32 enmity = pPlayer->GetEnmity(GetID());
//            if ( enmity == 0 || enmity == ENMITY_NOTINLIST )
//            { UpdateFirstAttack(GetTryToAttackCharId()); }
//        }
//    }
//
//    // ��ȷ���Ŀɹ���Ŀ��
//    if ( HaveCanAttackCharId() )
//    {
//        BaseCharacter* pTarget = GetCanAttackChar();
//        if ( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() )
//        {// ���Ŀ�겻���ˣ����ߺ��Լ�����һ��ͼ����
//            LostAttackTarget();
//            return;
//        }
//
//        _isNeedMove = false; // ���Թ����ˣ�����Ҫ�ƶ�
//        if ( !_SkillTaskManager.IsTaskEmpty() )  // �жϼ���
//        { return; }
//
//        int nLevel = 1;
//        int nSel = 0;
//        int nSelectRateRandNum = 0;
//        int nCount = 0;
//        CItemDetail::SItemSkill* pSkill = NULL;
//
//        // ѭ�����ҿ����õļ���
//        while (pSkill == NULL && nCount < 5)
//        {
//            nCount++;
//            if ( GetAiData()->m_stSkillRateTotal > 0 )
//            { nSelectRateRandNum = theRand.rand32() % GetAiData()->m_stSkillRateTotal; }
//
//            if ( nSelectRateRandNum < GetAiData()->m_stSkillRate[0] )
//            { nSel = 0;}    // ����õ��ĸ������С�ڼ���1�ĸ��ʣ���Ĭ��Ϊ����1
//            else if ( nSelectRateRandNum < GetAiData()->m_stSkillRate[1] )
//            {
//                if ( IsSkill2CanUse() )
//                { nSel = 1; }
//                else
//                { nSel = 0; }
//            }
//            else if ( nSelectRateRandNum < GetAiData()->m_stSkillRate[2] )
//            {
//                if ( IsSkill3CanUse() )
//                { nSel = 2; }
//                else
//                { nSel = 0; }
//            }
//
//            if ( IsNormalAttack(GetAiData()->m_iSkillId[nSel]) )
//            {
//                if ( !_buffManager.IsCanUsePhysicsSkill() )
//                { continue; }
//            }
//            else
//            {
//                if ( !_buffManager.IsCanUseMagicSkill() )
//                { continue; }
//            }
//
//            SetCurSkillIndex( nSel );
//            SetCurSkillLevel( nLevel ); // �ȼ�����Ϊ1��
//
//            pSkill = GettheItemDetail().GetSkillByID( GetCurSkill(), GetCurSkillLevel() );
//        }
//
//        m_pCurSkill = pSkill;   // ֻ�Ǽ�¼��ǰ�ļ���
//        if ( pSkill )
//        {
//            SetStatus(CS_IDLE);
//            return;
//        }
//
//        m_stCurAttackRange = pSkill->fRangeCanCast;
//        float fRangeCorrect = monsterCastCorrect;   // = 0.2f
//
//        if ( pSkill != NULL && pSkill->fRangeCanCast == 0 && m_bMoving )
//        {
//            m_bClosingToTarget = false;
//            if ( nSel > 0 && nSel < AI_MONSTERMAXSKILLNUM ) // ������˼��ܣ���tryUseSkill
//            { m_stCurAiTactic = EAISelectTaskType_TryUseSkill; }
//            else
//            { m_stCurAiTactic = EAISelectTaskType_TryAttackTarget; }
//        }
//        else
//        {
//            if ( IsHaveMoveAbility() )
//            { m_bClosingToTarget = false; }
//        }
//    }
//    else
//    {// û�пɹ���Ŀ�꣬������ƶ�
//        ThinkIdleMove();
//    }
//}
//
//void MonsterCountry::ThinkIdle()
//{// ����˼��
//    if ( HaveCanAttackCharId() || HaveTryToAttackCharId() )
//    { LostAttackTarget(); }
//
//    if ( GetAttackCharCount() == 0 || !IsInRange() )
//    {// û�е��� || ����������
//        if ( GetAttackCharCount() != 0 )
//        {// �����ǰ�������г�޵Ľ�ɫ����ѾŹ����ڵĳ�޶����
//            int nAreaID = GetCurArea();
//            GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
//            if ( pStage == NULL )
//            { return; }
//
//            IDListTPL<9> list;
//            pStage->Get9AreaList(list, nAreaID);
//            int nCount = list.Count();
//            for ( int i = 0; i < nCount; ++i )
//            {
//                GameArea* pGameArea = pStage->GetArea(list[i]);
//                if ( pGameArea == NULL )
//                { continue; }
// 
//                TGameObjectBId objectId = InvalidObjectId;
//                for ( uint32 currentIndex = 0; ( objectId = pGameArea->GetNextObjectBId( 0 == currentIndex ) ) != InvalidObjectId; ++currentIndex )
//                {
//                    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
//                    if ( pChar != NULL )
//                    {
//                        if ( pChar->IsMonster() )
//                        { static_cast<MonsterBase*>(pChar)->DecEnmity( GetID(), 0xFFFFFFFF ); }
//                        else
//                        { static_cast<GamePlayer*>(pChar)->DecEnmity( GetID(), 0xFFFFFFFF ); }
//                    }
//                }
//            }
//        }
//
//        // ������֮��������HP,MP
//        if ( GetHP() != GetHPMax() )
//        { RestoreHPInstant(GetHPMax()); }
//
//        if ( GetMP() != GetMPMax() )
//        { RestoreMPInstant(GetMPMax()); }
//
//        if ( m_bIsFighting )
//        {
//            if ( endPassiveTimeConfig != -1 )   // ս��������������ʱ��
//            { _endPassiveTimeRecord = HQ_TimeGetTime(); }
//            else
//            {
//                _endPassiveTimeRecord = 0;
//                SetPassiveAttack( bPassiveConfig ); // �ָ�����ģʽ
//            }
//            // ���Lua�ű�����
//            memset( m_nArray, 0, sizeof(m_nArray) );
//            memset( m_bArray, 0, sizeof(m_bArray) );
//
//            m_bIsFighting = false;
//            TryChangeFightState( m_bIsFighting, eFighting );
//        }
//
//        ThinkIdleMove();
//    }
//}
//
//void MonsterCountry::ThinkIdleMove()
//{// ����ʱ���ƶ��ĵ�
//     if ( !IsHaveMoveAbility() )
//     { return; }
//
//     int nMoveDiceValue = theRand.rand32() % 10000;
//     if ( !IsInRange() )
//     {//��������ƶ�������(�����Ǳ�������ȥ�ˡ�������ص������)
//         _isNeedMove = true;
//         m_bMoving = true;
//         _disableControlThinkTime = true;
//         nMoveDiceValue = -1;
//
//         SetFloatX( GetAiData()->m_ptBornPoint.x );
//         SetFloatY( GetAiData()->m_ptBornPoint.y );
//
//         SendVerifyPos( GetFloatX(), GetFloatY() );
//
//         // ���Ŀ��㲻�ڳ�����
//         if ( abs(_moveTargetPos.x - _coreAiData.m_ptBornPoint.x ) >= 0.0001 ||
//              abs(_moveTargetPos.y - _coreAiData.m_ptBornPoint.y ) >= 0.0001 ||
//              abs(_moveTargetPos.z - 0                           ) >= 0.0001  )
//         {
//             _moveTargetPos.x = _coreAiData.m_ptBornPoint.x;
//             _moveTargetPos.y = _coreAiData.m_ptBornPoint.y;
//             _moveTargetPos.z = 0;
//             // �Ա�����Ҳŷ����ƶ���Ϣ�����������
//             if ( AreaHavePlayer() )
//             {
//                 MsgUnPlayerMovingToPos msg;
//                 msg.SetLevel(level_normal);
//                 msg.header.stID = GetID();
//                 msg.vStartPos.x = GetFloatX();
//                 msg.vStartPos.y = GetFloatY();
//                 msg.vEndPos = _moveTargetPos;
//                 GettheServer().SendMsgToView( &msg, GetID(), true );
//             }
//
//             m_vLastSendTargetPos.x = GetFloatX();
//             m_vLastSendTargetPos.y = GetFloatY();
//         }
//     }
//     else
//     {// ��������
//         if ( !IsInMoveZone() )
//         {// �����ƶ�Zone��
//             if ( _endPassiveTimeRecord != 0 && GameTime::IsPassCurrentTime( _endPassiveTimeRecord, endPassiveTimeConfig) )
//             {
//                 _endPassiveTimeRecord = 0;
//                 SetPassiveAttack( bPassiveConfig );
//             }
//
//             m_bMoving = true;
//             _disableControlThinkTime = true;
//             nMoveDiceValue = -1;
//
//             if ( (GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed) >= 0.0001 )
//             { ChangeMoveSpeed( m_fNormalMoveSpeed); }
//
//             // ���Ŀ��㲻�ڳ�����
//             if ( abs(_moveTargetPos.x - _coreAiData.m_ptBornPoint.x ) >= 0.0001 ||
//                 abs(_moveTargetPos.y - _coreAiData.m_ptBornPoint.y ) >= 0.0001 ||
//                 abs(_moveTargetPos.z - 0                           ) >= 0.0001  )
//             {
//                 _moveTargetPos.x = _coreAiData.m_ptBornPoint.x;
//                 _moveTargetPos.y = _coreAiData.m_ptBornPoint.y;
//                 _moveTargetPos.z = 0;
//                 // �Ա�����Ҳŷ����ƶ���Ϣ�����������
//                 if ( AreaHavePlayer() )
//                 {
//                     MsgUnPlayerMovingToPos msg;
//                     msg.SetLevel(level_normal);
//                     msg.header.stID = GetID();
//                     msg.vStartPos.x = GetFloatX();
//                     msg.vStartPos.y = GetFloatY();
//                     msg.vEndPos = _moveTargetPos;
//                     GettheServer().SendMsgToView( &msg, GetID(), true );
//                 }
//
//                 m_vLastSendTargetPos.x = GetFloatX();
//                 m_vLastSendTargetPos.y = GetFloatY();
//             }
//
//             _isNeedMove = true;
//         }
//         else
//         {// ��Zone��
//             if ( (GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed) >= 0.0001 )
//             { ChangeMoveSpeed( m_fIdleMoveSpeed); }
//
//             if (_endPassiveTimeRecord != 0 && GameTime::IsPassCurrentTime(_endPassiveTimeRecord, endPassiveTimeConfig) )
//             {
//                 _endPassiveTimeRecord = 0; 
//                 SetPassiveAttack(bPassiveConfig);
//             }
//         }
//     }
//
//     // �Ƿ񴥷�һ��Idle�ƶ�
//     if ( nMoveDiceValue >= m_stIdleMoveRate )
//     { return; }
//
//     if ( !m_bMoving )
//     {
//         SendVerifyPos( GetFloatX(), GetFloatY() );
//         int r = 6; // ��6Ϊ�뾶��Ȧ�����������
//         int nx = GetTileX() + theRand.rand32() % ( r * 2 ) - r;
//         int ny = GetTileY() + theRand.rand32() % ( r * 2 ) - r;
//
//         if ( nx < GetCanMoveZone().left )
//         { nx = GetCanMoveZone().left; }
//         if ( nx > GetCanMoveZone().right )
//         { nx = GetCanMoveZone().right; }
//         if ( ny < GetCanMoveZone().top )
//         { ny = GetCanMoveZone().top; }
//         if ( ny > GetCanMoveZone().bottom )
//         { ny = GetCanMoveZone().bottom; }
//
//         _moveTargetPos.x = TileToFloat(nx);
//         _moveTargetPos.y = TileToFloat(ny);
//         _moveTargetPos.z = 0;
//
//         if ( AreaHavePlayer() )
//         {
//             MsgUnPlayerMovingToPos msg;
//             msg.SetLevel( level_normal ); // �����е����ȼ�
//             msg.header.stID = GetID();
//             msg.vStartPos.x = GetFloatX();
//             msg.vStartPos.y = GetFloatY();
//             msg.vStartPos.z = 0;
//             msg.vEndPos = _moveTargetPos;
//             GettheServer().SendMsgToView(&msg, GetID(), true);
//         }
//         m_vLastSendTargetPos.x = GetFloatX();
//         m_vLastSendTargetPos.y = GetFloatY();
//     }
//
//     _isNeedMove = true;
//}
//
//void MonsterCountry::MoveAttackMoving( uint32 lapseTime )
//{
//    BaseCharacter* pTarget = GetCanAttackChar();
//    if ( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() )
//    {
//        LostAttackTarget();
//        return;
//    }
//
//    D3DXVECTOR3 dir; // ����
//    if ( IsHaveMoveAbility() )
//    {// ������ƶ�����
//        D3DXVECTOR3 vTargetPos;
//        if ( _buffManager.IsRafferty() || _buffManager.IsRandRun() )
//        {// ����״̬�������
//            float fX = rand() % 20;
//            float fY = rand() % 20;
//
//            int op = rand() % 4;
//            switch (op)
//            {
//            case 0:
//                {
//                    vTargetPos.x = GetFloatX() + fX;
//                    vTargetPos.y = GetFloatY() + fY;
//                    vTargetPos.z = 0;
//                }
//            	break;
//            case 1:
//                {
//                    vTargetPos.x = GetFloatX() - fX;
//                    vTargetPos.y = GetFloatY() + fY;
//                    vTargetPos.z = 0;
//                }
//                break;
//            case 2:
//                {
//                    vTargetPos.x = GetFloatX() + fX;
//                    vTargetPos.y = GetFloatY() - fY;
//                    vTargetPos.z = 0;
//                }
//                break;
//            case 3:
//                {
//                    vTargetPos.x = GetFloatX() - fX;
//                    vTargetPos.y = GetFloatY() - fY;
//                    vTargetPos.z = 0;
//                }
//                break;
//            default:
//                {
//                    vTargetPos.x = GetFloatX();
//                    vTargetPos.y = GetFloatY();
//                    vTargetPos.z = 0;
//                }
//            }
//        }
//        else
//        {// û���ƶ�����
//            vTargetPos.x = GetFloatX();
//            vTargetPos.y = GetFloatY();
//            vTargetPos.z = 0;
//        }
//
//        D3DXVECTOR3 vecDistance( vTargetPos.x - GetFloatX(), vTargetPos.y - GetFloatY(), 0 );
//        float fDistance = D3DXVec3Length( &vecDistance );
//        D3DXVec3Normalize( &dir, &vecDistance );
//
//        if ( m_bClosingToTarget )
//        {// ��Ҫ��Ŀ���ƶ�
//            float fRange = pTarget->GetBodySize() + GetBodySize();  // �������ʹ�С
//            float fMoveStep = GetMoveSpeed() * ( (float)lapseTime * 0.001 ); // ����
//            if ( fRange <= 0.001f )
//            { fRange = 0.001f; }
//
//            if ( fDistance > fRange )
//            {// ���ڣ���Ҫ��Ŀ���ƶ�
//                if ( fMoveStep >= ( fDistance - fRange ) )
//                {// ��������Ҫ�ƶ��ľ����
//                    fMoveStep = fDistance - fRange;
//                    m_bMoving = true;
//                }
//                else
//                { m_bMoving = true; }
//
//                SetFloatXF( GetFloatX() + fMoveStep * dir.x );
//                SetFloatYF( GetFloatY() + fMoveStep * dir.y );
//                SetDirX( dir.x );
//                SetDirY( dir.y );
//            }
//            else // С�ڣ�����Ҫ�ƶ�
//            { m_bMoving = false; }
//        }
//        else
//        { // ����Ҫ��Ŀ���ƶ�
//            m_bMoving = false;
//        }
//    }
//
//    if ( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 1000) )  // 1�뷢һ��
//    {
//        if ( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001 )
//        { ChangeMoveSpeed(m_fNormalMoveSpeed); }
//
//        theGameWorld.OnRefreshNewArea( GetID() );
//
//        if ( m_bMoving )
//        {// �ƶ���
//            m_ushDirUnChangedCount = 0;
//            D3DXVECTOR3 vCurPos( GetFloatX(), GetFloatY(), WORLD_HEIGHT );
//            SendClosingToTarget( pTarget->GetID(), vCurPos );
//        }
//        else
//        {// ����
//            if ( IsHaveMoveAbility() )
//            {
//                SetDirX( dir.x );
//                SetDirY( dir.y );
//            }
//            SendVerifyPos( GetFloatX(), GetFloatY() );
//        }
//
//        m_dwSendMoveMessageTime = theGameWorld.g_dwLastWorldProcessTime;
//    }
//}
//
//void MonsterCountry::MovePosMoving( uint32 lapseTime )
//{
//    if ( _isNeedMove )
//    {// ��Ҫ�ƶ�
//        D3DXVECTOR3 vecDistance( _moveTargetPos.x - GetFloatX(), _moveTargetPos.y - GetFloatY(), 0 );
//        float fDistance = D3DXVec3Length( &vecDistance );
//
//        D3DXVECTOR3 vDir;
//        D3DXVec3Normalize( &vDir, &vecDistance );
//
//        float fActualMoveDist = GetMoveSpeed() * ( lapseTime * 0.001 );
//        if ( fActualMoveDist >= fDistance )
//        {
//            fActualMoveDist = fDistance;
//            m_bMoving = false;
//            _isNeedMove = false;
//        }
//        else
//        { m_bMoving = true; }
//
//        SetFloatXF( GetFloatX() + fActualMoveDist * vDir.x );
//        SetFloatYF( GetFloatY() + fActualMoveDist * vDir.y );
//        SetDirX( vDir.x );
//        SetDirY( vDir.y );
//    }
//    else
//    {
//        m_bMoving = false;
//    }
//
//    if ( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 2000 ) ) // 2�뷢һ��
//    {
//        if ( abs( GetCharFightAttr()->moveSpeed.base - m_fIdleMoveSpeed ) >= 0.0001 && IsInMoveZone() )
//        { ChangeMoveSpeed(m_fIdleMoveSpeed); }
//
//        theGameWorld.OnRefreshNewArea( GetID() );
//
//        if ( AreaHavePlayer() )
//        {
//            MsgUnPlayerMovingToPos msg;
//            msg.header.stID = GetID();
//            msg.vStartPos.x = GetFloatX();
//            msg.vStartPos.y = GetFloatY();
//            msg.vStartPos.z = WORLD_HEIGHT;
//            msg.vEndPos     = _moveTargetPos;
//            GettheServer().SendMsgToView( &msg, GetID(), true );
//        }
//        else
//        {
//            if ( GameTime::IsPassCurrentTime( m_noMoveSendVerifyPosTime, 4000 ) )
//            {
//                SendVerifyPos( GetFloatX(), GetFloatY() );
//                m_noMoveSendVerifyPosTime = HQ_TimeGetTime();
//            }
//        }
//
//        m_dwSendMoveMessageTime = HQ_TimeGetTime();
//    }
//}
//
//const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // ��޼���ˢ��ʱ��

//void MonsterCountry::RefreshEnmity()
//{
//    if ( IsDead() )
//    { return; }
//
//    unsigned long dwCurrTime = HQ_TimeGetTime();
//    if (m_dwLastDecEnmityTime > dwCurrTime)
//    { m_dwLastDecEnmityTime = 0; }
//
//    bool bUpdateDecEnmityTime = false;
//
//    for (int i=0; i<EnmityNum; i++)
//    {
//        if ( m_enmityList[i].nID == NULLID)
//        { continue; }
//
//        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_enmityList[i].nID );
//
//        if ( pChar == NULL )
//        {
//            m_enmityList[i].nID = NULLID;
//            continue;
//        }
//        // TODO:��Ҫ��ս��NPCҲ�����жϣ�ս��NPCҲ���Ժ��������͵Ĺִ�
//
//        // ��Ϊ���涼����AIBaseCharacterǿתpChar,�����ж�
//        if( !pChar->IsMonster() )
//        { continue; }
//
//        MonsterBase* pCharAI = (MonsterBase*)pChar;
//        unsigned int lastEnmity  = m_enmityList[i].nEnmity;
//        unsigned int nViewEnmity = pCharAI->GetViewEnmity();
//        unsigned int nEnmityRate = pCharAI->GetEnmityRate();
//
//        if ( GameTime::IsPassCurrentTime( dwCurrTime, m_dwLastDecEnmityTime, MONSTERENMITY_REFRESHTIME ) )
//        {   
//            bUpdateDecEnmityTime = true;
//
//            // �����
//            if (m_enmityList[i].nEnmity > 0)
//            {
//                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate*nEnmityRate*0.001f;
//                if (nDecEnmity < 1)
//                { nDecEnmity = 1; }
//
//                //�������ȡ�������޵���ֵ
//                if (m_enmityList[i].nEnmity > nDecEnmity)
//                { m_enmityList[i].nEnmity -= nDecEnmity; }
//                else
//                { m_enmityList[i].nEnmity = 0; }
//            }
//        }
//
//        if (m_enmityList[i].nEnmity == 0 && lastEnmity == 0)
//        {
//            //������Ǳ������������Ұ�������
//            if ( !pCharAI->IsPassiveAttack())
//            {
//                UpdateViewEnmity( i, pCharAI );
//            }
//        }
//        else
//        {
//            if (m_enmityList[i].nEnmity < nViewEnmity)
//            {
//                if (!pCharAI->IsPassiveAttack() || ( pCharAI->IsPassiveAttack() && pCharAI->IsInBaseEnmityRange()))
//                {
//                    UpdateViewEnmity( i, pCharAI );
//                }
//            }
//        }
//
//        if ( lastEnmity == 0 && m_enmityList[i].nEnmity > 0 )
//        { pCharAI->AddAttackCharacter( GetID() ); }
//        else if ( lastEnmity > 0 && m_enmityList[i].nEnmity == 0 )
//        { pCharAI->DecAttackCharacter( GetID() ); }
//
//        if ( pCharAI->GetTryToAttackCharId() == GetID())
//        { pCharAI->SetAttackCharEnmity(m_enmityList[i].nEnmity); }
//        else
//        {
//            if ( pCharAI->GetTryAttackCharEnmity() < m_enmityList[i].nEnmity)
//            {
//                pCharAI->SetAttackCharEnmity( m_enmityList[i].nEnmity );
//                pCharAI->SetTryToAttackCharId( GetID() );
//            }
//        }
//    }
//
//    if (bUpdateDecEnmityTime)
//    { m_dwLastDecEnmityTime = HQ_TimeGetTime();}
//
//}
//void MonsterCountry::UpdateViewEnmity( uint8 index, MonsterBase* pTargetMonster )
//{
//    int nViewSight = pTargetMonster->GetViewSight() + ( pTargetMonster->GetLevel() - GetLevel() ) * ENMITY_RATE;
//    if ( nViewSight < ENMITY_MIN_VIEWSIGHT )
//    { nViewSight = ENMITY_MIN_VIEWSIGHT;}
//
//    //�������Ұ�ڲ��ҳ��Ϊ0�������100;
//    if ( IsDistanceLess( pTargetMonster->GetTileX(), pTargetMonster->GetTileY(), GetTileX(), GetTileY(), nViewSight ) )
//    { // �ָ����
//        m_enmityList[ index ].nEnmity        = pTargetMonster->GetViewEnmity();
//        m_enmityList[ index ].nDecEnmityRate = pTargetMonster->GetViewEnmity(); // ȡ���İٷ�ʮ��˥����
//    }
//}

//bool MonsterCountry::IsAICanAttack( BaseCharacter* pChar )
//{
//    if ( pChar == NULL )
//    { return false; }
//    // �Լ����������ܹ���������
//    if ( IsDead() || pChar->IsDead() )
//    { return false; }
//
//    // ��������״̬���ܹ���
//    if ( _buffManager.IsRafferty() || _buffManager.IsRandRun() )
//    { return false; }
//
//    // ������ͬ���ܹ���
//    if ( pChar->GetCountry() == GetCountry() )
//    { return false; }
//
//    if ( pChar->IsNpc() && pChar->GetObjType() == Object_NpcFight )
//    {
//        NpcFight* pNpcFight = (NpcFight*)pChar;
//        if ( pNpcFight->GetCountry() == GetCountry() )
//        { return false; }
//
//        return true;
//    }
//
//    return MonsterBase::IsAICanAttack( pChar );
//}