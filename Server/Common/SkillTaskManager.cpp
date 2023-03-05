#include "SkillTaskManager.h"
#include "FuncPerformanceLog.h"
#include "BaseCharacter.h"
#include "ShareData.h"
#include "GamePlayer.h"

void SkillTaskManager::Clear()
{
    for( int i = 0; i < More_iSkillCountPerLinkedSkills; ++i)
    {
        m_skillTasks[i].id      = InvalidLogicNumber;
        m_skillTasks[i].isDone  = false;
        m_skillTasks[i].state   = 0;

        m_skillTasks[i].startTime   = 0;
        m_skillTasks[i].holdTime    = 0;
        m_skillTasks[i].balanceTime = 0;
    }
    m_nTargetId       = InvalidGameObjectId;
    m_nSkillTaskIndex = -1;
    m_nSkillTaskCount =  0;
}

void SkillTaskManager::IdleUpdate()
{   
    if ( _pOwner == NULL )
    { return; }

    bool  IsCanBeginUseSkill = false;		//初始状态不可攻击
    short shHintId = 0;
    // 能进入这里，一定是出于可以控制状态 需要上一个状态ok或者是从第一个状态开始
    if( IsCurTaskDone() || WaitFirstTaskStart() )
    {
        // 取得下一个，技能动作
        if ( !GetNextTask())
        { return; }

        SSkillTask* pSkillTask  = GetCurTask();
        if ( !pSkillTask)
        { return; }

        switch ( pSkillTask->type )
        {
        case SSkillTask::STT_SingleSkill: // 使用技能
            {
                unsigned short ustSkillID       = pSkillTask->id;
                short stSkillLevel              = pSkillTask->level;
                ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, stSkillLevel );
                
                if (pSkill == NULL)
                {
                    if( _pOwner->IsPlayer() )
                    {
						SendSkillMsgToSingle(MsgUseSkillHintMessage::eServerCannotFindSkill);
                    }
                    goto BeginUseSkill;
                }
                
                BaseCharacter* pTarget = NULL;
                if( m_bCharTarget )
                { 
                    pTarget = theRunTimeData.GetCharacterByID( m_nTargetId );
					
					//攻击目标不存在
                    if (pTarget == NULL)			
                    {
                        if( _pOwner->IsPlayer() )
                        {
							SendSkillMsgToSingle(MsgUseSkillHintMessage::eSkillTargetNotExist);
                        }
                        goto BeginUseSkill;
                    }
                    
					// 目标是否死亡
                    if ( pTarget->IsDead() )
                    { 
                        if (!pSkill->bIsRelive)
                        {
                            if( _pOwner->IsPlayer() )
                            { SendSkillMsgToSingle(MsgUseSkillHintMessage::eSkillTargetWrong); }
                           goto BeginUseSkill;    
                        }                                                    
                    }
                    
					//是否在攻击范围内
                    if( !_pOwner->IsInAttackRange( pTarget,pSkill ) )		
                    { 
                        if( _pOwner->IsPlayer() )
                        { SendSkillMsgToSingle(MsgUseSkillHintMessage::eOutAttackRangeHint); }                            
                        goto BeginUseSkill;
                    }    
					
					// 目标是否能被攻击
                    if( !_pOwner->IsCastTargetRight( pSkill,pTarget ) )
                    {
                        if( _pOwner->IsPlayer() )
                        { SendSkillMsgToSingle(MsgUseSkillHintMessage::eSkillTargetWrong); }
                        goto BeginUseSkill;
                    }	
                }

				IsCanBeginUseSkill = true;			//设置状态可攻击
				
BeginUseSkill:
                if ( !IsCanBeginUseSkill )
                {
					SendSkillMsgToSingle(MsgUseSkillHintMessage::eCancelSkill, ustSkillID, stSkillLevel);

                    Clear();
                    _pOwner->SetStatus( CS_IDLE );
                    return;
                }
                
                if ( pSkill->ustPrepTime > 0 )
                { // 需要吟唱
                    if (_pOwner->IsPlayer())
                    {
                        GamePlayer* pPlayer = static_cast<GamePlayer*> ( _pOwner );
                        bool bIsHandAttack = ( pSkill->ustItemID == pPlayer->GetNormalAttackSkillId( HT_RightHand ) ) ;
                        if ( !bIsHandAttack && _pOwner->_buffManager.GetNextNotIntonate() )
                        {
                            if ( _pOwner->_buffManager.GetNextNotIntonateNum() == 0 )
                            {
                                _pOwner->_buffManager.SetNextNotIntonate( false );
                                _BeginIntonateTask( pSkillTask );
                            }
                            else
                            { //  如果不是

                                int nNextNotIntonateNum = _pOwner->_buffManager.GetNextNotIntonateNum();
                                _pOwner->_buffManager.SetNextNotIntonateNum( nNextNotIntonateNum - 1 );
                                _BeginNotIntonateTask( pSkillTask );
                            }
                        }
                        else
                        {
                            _BeginIntonateTask( pSkillTask );
                        }
                    }
                    else
                    {
                        _BeginIntonateTask( pSkillTask );
                    }
                }
                else
                { // 不需要吟唱技能
                    _BeginNotIntonateTask( pSkillTask );
                }
                
            }
            break;
        case SSkillTask::STT_Express://表情动作
            {
                //如果能使用技能，也就表示能够作表情动作了
                if ( _pOwner->IsCanDoAction() )
                {
                    ItemDefine::SItemAction* pAction = (ItemDefine::SItemAction*)GettheItemDetail().GetItemByID( pSkillTask->id );
                    if ( NULL != pAction )
                    {
                        //发消息通知客户端，作某个动作
                        _pOwner->SetStatus(CS_DOACTION);
                        _pOwner->m_ExtendStatus.EnterActionStatus(pAction->stLastingPlayTime);
                        //发消息通知客户端，作某个表情动作
                        //MsgAckExpression  AckExpression;

                        //AckExpression.header.stID = _pOwner->GetID();
                        //AckExpression.ustActionID = pSkillTask->id;
                        //AckExpression.stTargetID   = _pOwner->GetID();
                        //GettheServer().SendMsgToView( &AckExpression, _pOwner->GetID(), false );
                    }
                    else
                    {
                        //否则清空任务列表
                        Clear();
                        _pOwner->SetStatus( CS_IDLE );
                    }
                }
                else
                {
                    //否则清空任务列表
                    Clear();
                    _pOwner->SetStatus( CS_IDLE );
                }

            }
            break;
        }
    }
}

void SkillTaskManager::AttackUpdate()
{
    if ( !_pOwner)
        return;

    if (!IsCurTaskDone())
    { // 当前任务没做好
        SAttackTarget target;
        if( m_bCharTarget )
        {
            BaseCharacter* pDst = (BaseCharacter*)theRunTimeData.GetCharacterByID( m_nTargetId );
            if( pDst == NULL )
            {
                DoneCurTask(); // 目标不存在 当前任务完成了
                _pOwner->SetStatus( CS_IDLE );
                return;
            }

            target.bIsCharTarget = true;
            target.nCharID       = pDst->GetID();
        }
        else
        {
            target.bIsCharTarget = false;
            target.vPos          = m_vTargetPos;
        }

        SSkillTask* pSkillTask = GetCurTask();
        if ( !pSkillTask)
        {
            _pOwner->SetStatus( CS_IDLE );
            return;
        }

        unsigned short ustSkillID = pSkillTask->id;
        short  stSkillLevel       = pSkillTask->level;        

        if ( GameTime::IsPassCurrentTime( pSkillTask->startTime, pSkillTask->balanceTime) )
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( ustSkillID, stSkillLevel );
            DWORD dwState = _pOwner->TryAttack( &target, pSkill, ustSkillID, stSkillLevel );
        
            if (dwState != eFIGHT_NOFLAG)
            {
                if (_HAS_FLAG(dwState, eFIGHT_CANCEL) || _HAS_FLAG(dwState, eFIGHT_BEKILLED))
                { Clear(); }
            }
            else
            { // 成功
            }
            
            DoneCurTask(); // 表示当前任务完成了

            if ( _pOwner->GetStatus() != CS_LOADINGMAP && _pOwner->GetStatus() != CS_DIEING )
            { _pOwner->SetStatus( CS_IDLE ); }
        }
    }
    else
    {
        if (!_pOwner->m_ExtendStatus.IsCannotNormalAttack())//能使用下个技能了，切换状态到idle
        { 
            DoneCurTask();
            _pOwner->SetStatus( CS_IDLE ); 
        } 
    }
}

SSkillTask* SkillTaskManager::GetTask( int i )
{
    if ( i < 0 || i >= m_nSkillTaskCount  )
        return NULL;

    if( m_nSkillTaskIndex >= More_iSkillCountPerLinkedSkills )
        return NULL;

    return &m_skillTasks[i]; 
}

SSkillTask* SkillTaskManager::GetCurTask()
{
    if( m_nSkillTaskIndex < 0 )
    { return NULL; }

    if( m_nSkillTaskIndex >= More_iSkillCountPerLinkedSkills )
    { return NULL; }

    if ( m_skillTasks[m_nSkillTaskIndex].id == InvalidLogicNumber )
    { return NULL; }

    return &m_skillTasks[m_nSkillTaskIndex];
}

bool SkillTaskManager::SetTasks( short type, bool bCharTarget, GameObjectId stTargetId,  short xTarget, short yTarget, 
                                short stSkills[], short stSkillLevel[], int nSkillCount)
{
    //Clear();
    //m_bCharTarget = bCharTarget;
    //m_stTargetX = xTarget;
    //m_stTargetY = yTarget;
    //m_stTargetId = stTargetId;
    //m_nSkillTaskCount = nSkillCount;
    ////DWORD dwStartTime = GameTime::GetCurrentTime();
    ////DWORD dwAccHoldTime = 0;
    //m_nSkillTaskIndex = -1;
    //for( int i = 0; i < m_nSkillTaskCount; i++ )
    //{
    //    m_skillTasks[i].type = type;
    //    m_skillTasks[i].id = stSkills[i];
    //    m_skillTasks[i].level = stSkillLevel[i];
    //    m_skillTasks[i].isDone = false;
    //    //m_skillTasks[i].dwStartTime = dwStartTime+dwAccHoldTime;
    //    //m_skillTasks[i].dwHoldTime = GettheItemDetail().GetSkillHoldTime( 
    //    //                                m_skillTasks[i].id,
    //    //                                m_skillTasks[i].level);
    //    //
    //    //dwAccHoldTime += m_skillTasks[i].dwHoldTime;
    //}
    return true;
}

bool SkillTaskManager::SetTasks( short type, bool bCharTarget, GameObjectId nTargetId, D3DXVECTOR3 vTargetPos, int nSkillID, int nSkillLevel )
{   
    Clear();

    ItemDefine::SItemSkill* pSkillItem = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );
    if ( !pSkillItem )
        return false;

    m_bCharTarget     = bCharTarget;
    m_vTargetPos      = vTargetPos;
    m_nTargetId       = nTargetId;
    m_nSkillTaskIndex = -1;
    m_nSkillTaskCount = 1;

    for( int i = 0; i < m_nSkillTaskCount; ++i)
    {
        m_skillTasks[i].type        = type;
        m_skillTasks[i].id          = nSkillID;
        m_skillTasks[i].level       = nSkillLevel;
        m_skillTasks[i].isDone      = false;
        m_skillTasks[i].startTime   = HQ_TimeGetTime();
        m_skillTasks[i].balanceTime = pSkillItem->dwDamageDelayBalanceTime;
        m_skillTasks[i].holdTime    = pSkillItem->iDurationTime;
     }
		
	////当时需要吟唱的状态的时候 我们判断当前玩家是否已经处于吟唱状态 是的话 打断以前的
	//if(type ==  SSkillTask::STT_SingleSkill && _pOwner && _pOwner->IsPlayer())
	//{
	//	GamePlayer * pPlayer = (GamePlayer*)_pOwner;
	//	ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );
	//	if(pSkill && pSkill->ustPrepTime > 0 && pPlayer->GetStatus() == CS_INTONATE) 
	//	{
	//		Msg_IntonateInterrupt IntonateInterrupt_msg;
	//		IntonateInterrupt_msg.header.stID = pPlayer->GetID();
	//		GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, pPlayer );
	//		pPlayer->SetStatus(CS_IDLE);
	//	}
	//}
    return true;
}

bool SkillTaskManager::WaitFirstTaskStart()
{
    if( m_nSkillTaskCount > 0 &&  m_nSkillTaskIndex < 0 )
        return true;
    return false;
}

bool SkillTaskManager::IsCurTaskDone()
{
    SSkillTask* pSkillTask = GetCurTask();

    if ( pSkillTask == NULL )
    { return true; }

    if ( pSkillTask->isDone )
    { return true; }

    //DWORD dwCurTaskDoneTime = pSkillTask->holdTime + pSkillTask->balanceTime + ONE_SEC;
    //if( GameTime::IsPassCurrentTime( pSkillTask->startTime, dwCurTaskDoneTime ) )
    //{ return true; }

    return false;
}
int SkillTaskManager::DoneCurTask()
{
    int nSkillID = -1;
    SSkillTask* pSkillTask = GetCurTask();
    if ( NULL != pSkillTask )
    {
        pSkillTask->isDone = true;
        nSkillID = pSkillTask->id;
    }
    
    return nSkillID;
}

bool SkillTaskManager::IsTaskEmpty()
{
    if ((m_nSkillTaskIndex >= m_nSkillTaskCount) || (m_nSkillTaskCount<=0))
        return true;
    return false;
}

bool SkillTaskManager::GetNextTask()
{
    if ( m_nSkillTaskCount <= 0 )
        return false;
    
    if( m_nSkillTaskIndex < 0 )
        m_nSkillTaskIndex = 0; // 首次攻击
    else
        ++m_nSkillTaskIndex;

    if( m_nSkillTaskIndex >= m_nSkillTaskCount )
        return false;

    return true;
}

void SkillTaskManager::_BeginIntonateTask( SSkillTask* pSkillTask )
{
    if ( NULL == pSkillTask || NULL == _pOwner )
    { return; }

    ItemDefine::SItemSkill* pSkillItem = GettheItemDetail().GetSkillByID( pSkillTask->id, pSkillTask->level);
    if ( NULL == pSkillItem )
    { return; }

	if(_pOwner->IsPlayer())
	{
		GamePlayer * pPlayer = (GamePlayer *)_pOwner;
		if(pPlayer->GetCurActionPlayTime()>0)
		{
			//结束当前脚本
			pPlayer->CancelCurScript( __FILE__, __FUNCTION__ );
		}
	}
    //如果技能有Intonate呤唱时间，就进入呤唱状态
    _pOwner->SetStatus( CS_INTONATE );
    unsigned short ustCastTime = pSkillItem->ustPrepTime;
    //if (_pOwner->_buffManager.GetAddIntonateRate() != 0.0f)
    //{
    //    float fTemp = (1.0f - _pOwner->_buffManager.GetAddIntonateRate())*ustCastTime;
    //    ustCastTime = fTemp;
    //}

    _pOwner->m_ExtendStatus.EnterActionStatus( ustCastTime );
    ////进入一段作动作的时间
    ////发消息通知客户端，进入的吟唱的状态
    //MsgIntonate  msg;
    //msg.header.stID = GetControl()->GetID();
    //msg.stSkillID = _SkillTaskManager.GetCurTask()->id; //使用的技能
    //msg.stSkillLevel = _SkillTaskManager.GetCurTask()->level; //使用的技能级别
    //msg.stTagNpcID = _SkillTaskManager.m_nTargetId;        //技能的释放目标
    //msg.dwTime = pSkill->ustPrepTime;        //呤唱时间
    ////发消息..通知有人在呤唱
    //GettheServer().SendMsgToView( &msg, GetID(), false );

    // 吟唱开始
    Msg_IntonateStart start;
    start.header.stID = _pOwner->GetID();
    start.ustSkillID  = pSkillTask->id;
    start.cSkillLevel = pSkillTask->level;
    start.bCharTarget = true;
    start.target.ustTargetID = m_nTargetId;
    GettheServer().SendMsgToView( &start, _pOwner->GetID(), false );

    //保存目标数据
    if( m_bCharTarget )
    {
        BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_nTargetId );
        if( NULL == pTarget)
        { return; }

        _pOwner->m_ContinuousSkill.bCharTarget       = true;
        _pOwner->m_ContinuousSkill.ustTargetChar     = pTarget->GetID();
        _pOwner->m_ContinuousSkill.ustTargetLifeCode = pTarget->GetLifeCode();
    }
    else
    {
        _pOwner->m_ContinuousSkill.bCharTarget = false;
        _pOwner->m_ContinuousSkill.vTargetPos = m_vTargetPos;
    }
    _pOwner->m_ContinuousSkill.pSkill = pSkillItem;
}

void SkillTaskManager::_BeginNotIntonateTask( SSkillTask* pSkillTask)
{   
    if ( NULL == pSkillTask)
    { return; }

    ItemDefine::SItemSkill* pSkillItem = GettheItemDetail().GetSkillByID( pSkillTask->id, pSkillTask->level);
    if ( NULL == pSkillItem )
    { return; }

    if( MsgUseSkillHintMessage::eNormal != _pOwner->ApplySkillCost( pSkillItem ) )
    { return; }

    if( _pOwner->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)_pOwner;  
		if(pPlayer->GetCurActionPlayTime()>0)
			pPlayer->CancelCurScript( __FILE__, __FUNCTION__ );
        if ( IsNormalAttack( pSkillTask->id ) )
        {// 普通攻击不走公共CD 取的是攻击速度
        }
        else
        {
            CDTIME cdResult = pPlayer->StartSkillCoolDown( pSkillItem );
            /*DWORD dwLefeTime = _pOwner->m_ExtendStatus.GetCannotNormalAttackLeftTime();
            if ( cdResult.second != 0 && (dwLefeTime == 0) || cdResult.second > _pOwner->m_ExtendStatus.GetCannotNormalAttackLeftTime() )
            {
            _pOwner->m_ExtendStatus.EnterCanNotNormalAttack(cdResult.second);
            }*/
        }
    }

    std::vector< BaseCharacter* > vecTargetList;

    // 如果是吟唱技能或者是发射技能, 结束吟唱 ( 有的状态可以让吟唱技能瞬发 )
    if ( pSkillItem->ustPrepTime > 0 || pSkillItem->bEmissionSkill )
    {
        Msg_IntonateEnd end;
        end.header.stID = _pOwner->GetID();
        DWORD dwEmissionFlyTime = _pOwner->GetEmissionFlyTime( m_nTargetId );

        if( pSkillItem->bAssaultSkill )
        { dwEmissionFlyTime = dwEmissionFlyTime * 0.5f; }

        if ( !IsCurTaskDone() )
        {
            end.ustSkillID         = pSkillTask->id;
            end.ustSkillLevel      = pSkillTask->level;

			if ( pSkillItem->bEmissionSkill && ( pSkillItem->shMaxTargetNum > 1 ) )
			{
                BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_nTargetId );
                if( pTarget == NULL )
                {  return; }   

				// 发射体技能在技能启动时确定目标,而不是在伤害结算的时候
				SAttackTarget target;
				target.bIsCharTarget = true;
				target.nCharID = pTarget->GetID();
				target.vPos = pTarget->GetPos();
				_pOwner->FindAttackTarget( &target, pSkillItem, vecTargetList );

				end.nTargetCount = vecTargetList.size();
                 
				//lyh++ 防止策划配表配错，导致end.targetList 越界，程序崩溃
				end.nTargetCount = end.nTargetCount <=MAXEMISSIONNUM ? end.nTargetCount : MAXEMISSIONNUM;

				for ( int i = 0; i < end.nTargetCount ; ++i )
				{
                    BaseCharacter* pDst = vecTargetList[i];

					end.targetList[i].target.ustTargetID = pDst->GetID();
					end.targetList[i].dwEmissionFlyTime = dwEmissionFlyTime + SPELLACTION_CASTTIME;
				}
			}
			else
			{
				end.nTargetCount = 1;
				end.targetList[0].target.ustTargetID = m_nTargetId;
				end.targetList[0].dwEmissionFlyTime = dwEmissionFlyTime + SPELLACTION_CASTTIME;
			}
        }

        GettheServer().SendMsgToView( &end, _pOwner->GetID(), false );
    }

    D3DXVECTOR3 pos;
    if( pSkillItem->bHoldSkill )
    { // 持续技能                        
        //保存目标数据
        if( m_bCharTarget )
        {
            BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_nTargetId );
            if( pTarget == NULL )
            {  return; }   

            _pOwner->m_ContinuousSkill.bCharTarget       = true;
            _pOwner->m_ContinuousSkill.ustTargetChar     = pTarget->GetID();
            _pOwner->m_ContinuousSkill.ustTargetLifeCode = pTarget->GetLifeCode();

            pos.x = pTarget->GetFloatX();
            pos.y = pTarget->GetFloatY();
        }
        else
        {
            _pOwner->m_ContinuousSkill.bCharTarget = false;
            _pOwner->m_ContinuousSkill.vTargetPos  = m_vTargetPos;

            pos = m_vTargetPos;
        }

        if ( pSkillItem->shCastType == ItemDefine::casttype_AOEPointCircleArea)
        {
            if ( !_pOwner->IsInValidCastRange( pos.x, pos.y, pSkillItem))
            {   
				SendSkillMsgToSingle(MsgUseSkillHintMessage::eOutAttackRangeHint);
				return;
            }
        }

        _pOwner->m_ContinuousSkill.pSkill = pSkillItem;

        _pOwner->BeginHoldSkill();
        _pOwner->SetStatus( CS_HOLDSKILL );
    }
    else
    { // 不是持续技能
        if( pSkillItem->bEmissionSkill )
        {
            ////开始技能ColdDown ColdDown
            //if( _pOwner->IsPlayer() )
            //{
            //    GamePlayer* pPlayer = (GamePlayer *)_pOwner;
            //    pPlayer->StartSkillCoolDown( ustSkillID,stSkillLevel );
            //}

            long nResult = _pOwner->ProcessAttackSpeed( pSkillItem );
            if ( RESULT_FAILED( nResult ) )
            { return; }

            DWORD dwEmissionFlyTime = _pOwner->GetEmissionFlyTime(m_nTargetId);
            if( pSkillItem->bAssaultSkill )
            { dwEmissionFlyTime = dwEmissionFlyTime * 0.5f; }

            BOOL bEmissisonFull = TRUE;
            if ( pSkillItem->shMaxTargetNum == 1 )
            {
                 for( int i=0; i<MAXEMISSIONNUM; ++i )
                 {
                     if( _pOwner->m_Emission[i].bDead )
                     {
                         bEmissisonFull                       = FALSE;
                         ++_pOwner->m_ucHaveEmission;
                         _pOwner->m_Emission[i].bDead         = FALSE;
                         _pOwner->m_Emission[i].dwStartTime   = HQ_TimeGetTime();
                         _pOwner->m_Emission[i].dwLifeTime    = dwEmissionFlyTime + SPELLACTION_CASTTIME;
                         _pOwner->m_Emission[i].ustTargetID   = m_nTargetId;
                         _pOwner->m_Emission[i].ustSkillID    = pSkillTask->id;
                         _pOwner->m_Emission[i].ustSkillLevel = pSkillTask->level;
                         break;
                     }
                 }
            }
            else
            {
                for ( int i = 0 ; i < vecTargetList.size() ; ++i )
                {
                    if ( i >= MAXEMISSIONNUM )
                    { break; }

                    BaseCharacter* pDst = vecTargetList[i];
                    if ( pDst == NULL )
                    { continue; }

                    DWORD dwEmissionFlyTime = _pOwner->GetEmissionFlyTime( pDst->GetID() );

                    if( _pOwner->m_Emission[i].bDead )
                    {
                        bEmissisonFull              = FALSE;                    
                        ++_pOwner->m_ucHaveEmission;
                        _pOwner->m_Emission[i].bDead         = FALSE;
                        _pOwner->m_Emission[i].dwStartTime   = HQ_TimeGetTime();
                        _pOwner->m_Emission[i].dwLifeTime    = dwEmissionFlyTime + 0;//SPELLACTION_CASTTIME;
                        _pOwner->m_Emission[i].ustTargetID   = pDst->GetID();
                        _pOwner->m_Emission[i].ustSkillID    = pSkillTask->id;
                        _pOwner->m_Emission[i].ustSkillLevel = pSkillTask->level;
                    }
                }
            }

            if( bEmissisonFull )
            { // 满了
                // 改变到攻击状态
                _pOwner->SetStatus( CS_ATTACK );
            }
            else
            { // 没满
                DoneCurTask();
                _pOwner->SetStatus( CS_IDLE );
            }
        }
        else
        { // 不是发射技能
            //改变到攻击状态
            _pOwner->SetStatus( CS_ATTACK );
            //最快速度产生攻击
            _pOwner->StatusActionAttack();
        }
	}
	
}



void SkillTaskManager::SendSkillMsgToSingle(short shHintId, int nSkillID /* = -1 */, int stSkillLevel /* = -1 */)
{
	MsgUseSkillHintMessage HintMsg;
	HintMsg.header.stID  = _pOwner->GetID();
	HintMsg.shHintId     = shHintId;
	HintMsg.TargetID     = m_nTargetId;
	HintMsg.nSkillID     = nSkillID;
	HintMsg.shSkillLevel = stSkillLevel;
	GettheServer().SendMsgToSingle( &HintMsg, _pOwner );
}
