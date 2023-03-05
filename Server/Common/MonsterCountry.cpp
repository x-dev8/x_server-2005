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
//    // 记录上次未被攻击的空闲位置
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
//    {// 如果有可以攻击的目标，而且有仇恨，并且在攻击范围,则攻击
//        ThinkAttack();
//    }
//    else
//    {// 否则是空闲
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
//    {// 如果不是在战斗状态
//        // 设置成被动怪
//        if ( changePassiveConfig != 0 )
//        { SetPassiveAttack(true); }
//
//        //m_bIsFighting = true;
//        //TryChangeFightState(m_bIsFighting, eFighting);
//        //MAlarmWhenBeAttack();
//    }
//
//    // 如果当前的攻击目标找不到了
//    if ( theRunTimeData.GetCharacterByID(GetTryAttackCharEnmity()) == NULL )
//    {
//        if ( GetAttackCharCount() > 0 )
//        { DecAttackCharacter(GetTryToAttackCharId()); } // 从攻击者容器中删除该攻击者
//        // 仇恨设置为0，放弃锁定目标
//        SetAttackCharEnmity(0);
//        LostAttackTarget();
//        return;
//    }
//
//    // 思考得到下一个可以攻击的人
//    LockTarget( GetTryToAttackCharId() );
//    // 将可攻击人中的第一个设置为攻击自己的人
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
//    // 有确定的可攻击目标
//    if ( HaveCanAttackCharId() )
//    {
//        BaseCharacter* pTarget = GetCanAttackChar();
//        if ( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() )
//        {// 如果目标不在了，或者和自己不在一张图上了
//            LostAttackTarget();
//            return;
//        }
//
//        _isNeedMove = false; // 可以攻击了，不需要移动
//        if ( !_SkillTaskManager.IsTaskEmpty() )  // 判断技能
//        { return; }
//
//        int nLevel = 1;
//        int nSel = 0;
//        int nSelectRateRandNum = 0;
//        int nCount = 0;
//        CItemDetail::SItemSkill* pSkill = NULL;
//
//        // 循环查找可以用的技能
//        while (pSkill == NULL && nCount < 5)
//        {
//            nCount++;
//            if ( GetAiData()->m_stSkillRateTotal > 0 )
//            { nSelectRateRandNum = theRand.rand32() % GetAiData()->m_stSkillRateTotal; }
//
//            if ( nSelectRateRandNum < GetAiData()->m_stSkillRate[0] )
//            { nSel = 0;}    // 随机得到的概率如果小于技能1的概率，则默认为技能1
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
//            SetCurSkillLevel( nLevel ); // 等级均设为1级
//
//            pSkill = GettheItemDetail().GetSkillByID( GetCurSkill(), GetCurSkillLevel() );
//        }
//
//        m_pCurSkill = pSkill;   // 只是记录当前的技能
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
//            if ( nSel > 0 && nSel < AI_MONSTERMAXSKILLNUM ) // 随机到了技能，则tryUseSkill
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
//    {// 没有可攻击目标，则空闲移动
//        ThinkIdleMove();
//    }
//}
//
//void MonsterCountry::ThinkIdle()
//{// 空闲思考
//    if ( HaveCanAttackCharId() || HaveTryToAttackCharId() )
//    { LostAttackTarget(); }
//
//    if ( GetAttackCharCount() == 0 || !IsInRange() )
//    {// 没有敌人 || 不在区域中
//        if ( GetAttackCharCount() != 0 )
//        {// 如果当前还存在有仇恨的角色，则把九宫格内的仇恨都清掉
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
//        // 仇恨清掉之后怪物回满HP,MP
//        if ( GetHP() != GetHPMax() )
//        { RestoreHPInstant(GetHPMax()); }
//
//        if ( GetMP() != GetMPMax() )
//        { RestoreMPInstant(GetMPMax()); }
//
//        if ( m_bIsFighting )
//        {
//            if ( endPassiveTimeConfig != -1 )   // 战斗结束被动持续时间
//            { _endPassiveTimeRecord = HQ_TimeGetTime(); }
//            else
//            {
//                _endPassiveTimeRecord = 0;
//                SetPassiveAttack( bPassiveConfig ); // 恢复攻击模式
//            }
//            // 清空Lua脚本变量
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
//{// 空闲时候移动的点
//     if ( !IsHaveMoveAbility() )
//     { return; }
//
//     int nMoveDiceValue = theRand.rand32() % 10000;
//     if ( !IsInRange() )
//     {//如果不在移动区域内(可能是被人引出去了。则立马回到复活点)
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
//         // 如果目标点不在出生点
//         if ( abs(_moveTargetPos.x - _coreAiData.m_ptBornPoint.x ) >= 0.0001 ||
//              abs(_moveTargetPos.y - _coreAiData.m_ptBornPoint.y ) >= 0.0001 ||
//              abs(_moveTargetPos.z - 0                           ) >= 0.0001  )
//         {
//             _moveTargetPos.x = _coreAiData.m_ptBornPoint.x;
//             _moveTargetPos.y = _coreAiData.m_ptBornPoint.y;
//             _moveTargetPos.z = 0;
//             // 旁边有玩家才发送移动消息，以提高性能
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
//     {// 在区域内
//         if ( !IsInMoveZone() )
//         {// 不在移动Zone内
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
//             // 如果目标点不在出生点
//             if ( abs(_moveTargetPos.x - _coreAiData.m_ptBornPoint.x ) >= 0.0001 ||
//                 abs(_moveTargetPos.y - _coreAiData.m_ptBornPoint.y ) >= 0.0001 ||
//                 abs(_moveTargetPos.z - 0                           ) >= 0.0001  )
//             {
//                 _moveTargetPos.x = _coreAiData.m_ptBornPoint.x;
//                 _moveTargetPos.y = _coreAiData.m_ptBornPoint.y;
//                 _moveTargetPos.z = 0;
//                 // 旁边有玩家才发送移动消息，以提高性能
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
//         {// 在Zone内
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
//     // 是否触发一次Idle移动
//     if ( nMoveDiceValue >= m_stIdleMoveRate )
//     { return; }
//
//     if ( !m_bMoving )
//     {
//         SendVerifyPos( GetFloatX(), GetFloatY() );
//         int r = 6; // 以6为半径的圈子内随机行走
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
//             msg.SetLevel( level_normal ); // 设置中等优先级
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
//    D3DXVECTOR3 dir; // 朝向
//    if ( IsHaveMoveAbility() )
//    {// 如果有移动能力
//        D3DXVECTOR3 vTargetPos;
//        if ( _buffManager.IsRafferty() || _buffManager.IsRandRun() )
//        {// 中了状态随机乱跑
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
//        {// 没有移动能力
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
//        {// 需要向目标移动
//            float fRange = pTarget->GetBodySize() + GetBodySize();  // 算上体型大小
//            float fMoveStep = GetMoveSpeed() * ( (float)lapseTime * 0.001 ); // 步长
//            if ( fRange <= 0.001f )
//            { fRange = 0.001f; }
//
//            if ( fDistance > fRange )
//            {// 大于，需要向目标移动
//                if ( fMoveStep >= ( fDistance - fRange ) )
//                {// 步长比需要移动的距离大
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
//            else // 小于，不需要移动
//            { m_bMoving = false; }
//        }
//        else
//        { // 不需要向目标移动
//            m_bMoving = false;
//        }
//    }
//
//    if ( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 1000) )  // 1秒发一次
//    {
//        if ( abs( GetCharFightAttr()->moveSpeed.base - m_fNormalMoveSpeed ) >= 0.0001 )
//        { ChangeMoveSpeed(m_fNormalMoveSpeed); }
//
//        theGameWorld.OnRefreshNewArea( GetID() );
//
//        if ( m_bMoving )
//        {// 移动中
//            m_ushDirUnChangedCount = 0;
//            D3DXVECTOR3 vCurPos( GetFloatX(), GetFloatY(), WORLD_HEIGHT );
//            SendClosingToTarget( pTarget->GetID(), vCurPos );
//        }
//        else
//        {// 不动
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
//    {// 需要移动
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
//    if ( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 2000 ) ) // 2秒发一次
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
//const unsigned long MONSTERENMITY_REFRESHTIME = 1000; // 仇恨减少刷新时间

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
//        // TODO:需要对战斗NPC也进行判断，战斗NPC也可以和特殊类型的怪打斗
//
//        // 因为下面都是用AIBaseCharacter强转pChar,必须判断
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
//            // 减仇恨
//            if (m_enmityList[i].nEnmity > 0)
//            {
//                unsigned int nDecEnmity = m_enmityList[i].nDecEnmityRate*nEnmityRate*0.001f;
//                if (nDecEnmity < 1)
//                { nDecEnmity = 1; }
//
//                //在这里获取怪物减仇恨的数值
//                if (m_enmityList[i].nEnmity > nDecEnmity)
//                { m_enmityList[i].nEnmity -= nDecEnmity; }
//                else
//                { m_enmityList[i].nEnmity = 0; }
//            }
//        }
//
//        if (m_enmityList[i].nEnmity == 0 && lastEnmity == 0)
//        {
//            //如果不是被动怪则进入视野触发仇恨
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
//    //如果在视野内并且仇恨为0，则加上100;
//    if ( IsDistanceLess( pTargetMonster->GetTileX(), pTargetMonster->GetTileY(), GetTileX(), GetTileY(), nViewSight ) )
//    { // 恢复仇恨
//        m_enmityList[ index ].nEnmity        = pTargetMonster->GetViewEnmity();
//        m_enmityList[ index ].nDecEnmityRate = pTargetMonster->GetViewEnmity(); // 取它的百分十的衰减率
//    }
//}

//bool MonsterCountry::IsAICanAttack( BaseCharacter* pChar )
//{
//    if ( pChar == NULL )
//    { return false; }
//    // 自己死亡或者受攻击者死亡
//    if ( IsDead() || pChar->IsDead() )
//    { return false; }
//
//    // 自身中了状态不能攻击
//    if ( _buffManager.IsRafferty() || _buffManager.IsRandRun() )
//    { return false; }
//
//    // 国家相同不能攻击
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