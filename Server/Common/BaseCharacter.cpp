#include "BaseCharacter.h"
//#include "DataReport.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "GamePlayer.h"
#include "FuncPerformanceLog.h"
#include "MsgQueueProxy.h"
#include "ExpStage.h"
#include "EffectChar.h"
#include "ApplyCenter.h"
#include "MonsterBaseEx.h"
#include "SystemConfig.h"
#include "Configure.h"
#include "CountryConfig.h"
#include "ErrorLog.h"
#include "NpcBaseEx.h"
#include "DuelHandler.h"
#include "ThreadBuffer.h"
#include "XmlStringLanguage.h"
#include "AntiAddictionSystem.h"
#include "ResourcePath.h"
#include "TeamManager.h"
#include "KillMonsterCountConfig.h"
#include "GameDefinePlayer.h"
#include "AchieveServerManager.h"
#include "GamePlayer.h"
#include "CampBattleMessage.h"
#include "NpcNormalEx.h"
#include "UserLoger.h"


extern CExpStage theExpStage;

static MeMsgQueueProxy<NetControl::const_iInSize> gCharacterProxyIn;
static MeMsgQueueProxy<NetControl::const_iOutSize> gCharacterProxyOut;

//int ICharacter::GetRand( int i )
//{
//    if ( 0 > i ) i = 0;
//    stRandCount = stRandCount + i;
//    if ( 39 < stRandCount )
//    {
//        stRandCount = stRandCount - 40;
//    }
//    return RandNumber[ stRandCount ];
//}
//
//int ICharacter::GetRandNumberToClient()
//{
//    stRandCountToClient++;
//    if ( 39 < stRandCountToClient )
//    {
//        stRandCountToClient = 0;
//    }
//    RandNumber[ stRandCountToClient ] = theRand.rand32();
//    return RandNumber[ stRandCountToClient ];
//}

// 记录消息的开关
//#define LOG_ALL_MSG
void LogMsg( NetControlEx* pCrtl, Msg* pMsg );

BaseCharacter::BaseCharacter(): IBaseCharControl() 
{
    SetWeaponAttackRange( 0 );
    m_bCanSwitchStage = true;
    SetObjType( Object_Dump );
    SetStatus( CS_START );    
    SetCurArea( -1 );
    m_dwLastRefreshCharDataTime = HQ_TimeGetTime();
    m_dwLastRefreshStatusTime = m_dwLastRefreshCharDataTime;
    SetBodyType( BODYTYPE_MIDDLE );
    m_restoretime.dwLastHPRestoreTime   = HQ_TimeGetTime();
    m_restoretime.dwLastMPRestoreTime   = HQ_TimeGetTime();
    m_restoretime.dwLastXPRestoreTime   = HQ_TimeGetTime();
    m_restoretime.dwLastPassOnlineTime  = HQ_TimeGetTime() - ONE_MIN;
    m_restoretime.dwLastDoubleExpTime   = 0;

    SetMapID( 0 );
    SetCountry( 0 );
    m_bDeadFlag = false;

    //m_bIsNormalAtkBufFull = false;    
    //m_CorrectTime = 0;
    //m_InputAtkBufTime = 0;

    m_fLastMovingSpeed            = 0;
    m_dwShowFlag                  = 0;
    m_dwFightFlag                 = 0;
    m_iAttackHand                 = HT_RightHand;
    m_fBodySize                   = 0;
    m_nNormalAttSkillId0          = ConstSkillId_NormalAttack_Combat;
    m_nNormalAttSkillId1          = ConstSkillId_NormalAttack_Combat;
    m_ucHaveEmission              = 0;

    m_nLockID                 = -1;
    m_bMask                   = false;
    m_pBelongKiller           = NULL;
    m_dwLastMapID             = 0;
    m_dwLastEctypeMapID       = 0;
    m_bBeCSed                 = false;
    m_bIllusionChar           = FALSE;
    m_bySubAction             = CS_SubAction_Normal;
    m_nCompoundRateAddTemp    = 0;
    m_nIntensifyRateAddTemp   = 0;
    _SkillTaskManager.SetOwner( this );

	

    m_dwProcessLogicCostTime = 0;
    m_uchFightCamp = 0;
    _moveStatus = CS_IDLE;

	m_byReliveBuff = 0;

    m_xRefeshEnmityTimer.StartTimer( HQ_TimeGetTime(), AiDefine::RefeshEnmitySpaceTime );

	m_IsGameBattle = false;
};

void BaseCharacter::CriticalError(char* szFun, char* szFile, int nLine, unsigned char exitType /*= ET_ExitGame*/)
{
    // 如果是玩家则记录退出的位置
    if( IsPlayer() ) 
    {
        GamePlayer* pPlayer = (GamePlayer*)this;
        if ( pPlayer->GetOfflineTime() == 0 )
        {   
            //pPlayer->Log("调用函数 %s [%s:%d] 退出", szFun, szFile, nLine );
			pPlayer->Log(theXmlString.GetString(eServerLog_FunExit), szFun, szFile, nLine );
            pPlayer->SetOffline();
            pPlayer->SetOfflineType( exitType );
        }
    }
    else
    {
        ExitWorldByPushMsg();
        //ExitWorld();           // 怪物不能直接OnExit
    }
}

void BaseCharacter::ExitWorld(char* szFun, char* szFile, int nLine,unsigned char exitType)
{
    CriticalError(szFun, szFile, nLine,exitType);
}

void BaseCharacter::ExitWorldByPushMsg()
{
    MsgExit xMsg;
    xMsg.header.stID = GetID();
    GetControl()->Push2In( &xMsg );
}

void BaseCharacter::ExitWorld()
{
    MsgExit xMsg;
    xMsg.header.stID = GetID();
    OnExit( &xMsg );
}

void BaseCharacter::CaluStepCost(BYTE byDir)
{
    float fCost;
    float fMoveRate;
    const float fCost2 = ONESTEPCOST * 1.414f;
    //
    if (Object_Player == GetObjType())
        int k = 0;
    //
    switch( byDir )
    {
    case DIR_0:
    case DIR_90:
    case DIR_180:
    case DIR_270:        
        fCost = ONESTEPCOST;        
        break;
        //
    default:        
        fCost = fCost2;
        break;
    }

    if( Object_Player == GetObjType() )
    {
        fCost -= 50;
        if( fCost < 0 )
            fCost = 1;
    }
    //
    fMoveRate = GetMoveSpeed();
    //if (fMoveRate > 0.01f)
    //{
    //    //计算
    //    fCost /= fMoveRate;
    //    m_aMovePath.dwTimeStepOver = HQ_TimeGetTime();// + 1000.0f/MOVEVELOCITY;
    //    m_aMovePath.dwTimeStepOver += (DWORD)fCost;
    //}
    //else
    //{
    //    m_aMovePath.dwTimeStepOver = ErrorDWORDID;
    //}

    //if ( IsMonster() )
    //{
    //    BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByName( "ffff" );
    //    if (pChar)
    //    {
    //        int ntemp = fCost;  
    //        pChar->TellClient( "fCost = %d", ntemp );
    //    }
    //}
}

void BaseCharacter::SetDirectiron( float fDir )
{
    float fDirX = 0.0f, fDirY = 0.0f;
    if( fDir < 0 || fDir > 360 )
    { fDir = 0; }

    fDir = fDir/180*D3DX_PI;
    float fxtoy = tan(fDir);
    float fPosXOff = 0;
    float fPosYOff = 0;

    if( fxtoy == 0 )
    {
        fPosXOff = 1;
    }
    else
    {
        fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
        fPosYOff = fabs(fxtoy*fPosXOff);
    }
    if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
    { // 第一象限
        fDirX = fPosXOff;
        fDirY = fPosYOff;
    }
    else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
    { // 第二象限
        fDirX = -fPosXOff;
        fDirY = fPosYOff;
    }
    else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
    { // 第三象限
        fDirX = -fPosXOff;
        fDirY = -fPosYOff;
    }
    else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
    { // 第四象限
        fDirX = fPosXOff;
        fDirY = -fPosYOff;
    }

    SetDirX( fDirX );
    SetDirY( fDirY );
    SetDir( 0 );
}

void BaseCharacter::StatusActionIdle()
{  
    _SkillTaskManager.IdleUpdate();
}

void BaseCharacter::StatusActionAttack()
{   
    _SkillTaskManager.AttackUpdate();
}

//使用特殊技能
void BaseCharacter::StatusActionUseSpecialSkill()
{
    SetStatus( CS_IDLE );
}

// 准备使用特殊技能
void BaseCharacter::StatusActionReadyToUseSpecialSkill()
{
    if( GetNextStatus() != CS_READYTOUSESPEICALSKILL )
    {
        m_ExtendStatus.m_fsExtend = m_ExtendStatus.efs_Normal;
        SetStatus( CS_IDLE );
        return;
    }

    if (!m_ExtendStatus.IsActionTime())
    {
        MsgAgreeUseSpecialSkill agreeusespcialskillmsg;

        GettheServer().SendMsgToSingle( &agreeusespcialskillmsg, this );

        SetStatus( CS_IDLE );

        ////根据技能判断是否维持技能，如果是维持技能
        //if (!_SkillTaskManager.IsCurTaskDone())
        //{
        //    //吟唱结束
        //    Msg_IntonateEnd end;
        //    end.header.stID = GetControl()->GetID();
        //    GettheServer().SendMsg( this, &end, sendrange_view );

        //    //SAttackTarget target;
        //    //target.bIsCharTarget = true;
        //    //target.data.pChar = ( BaseCharacter* )theRunTimeData.GetCharacterByIDAndLifecode( m_ContinuousSkill.ustTargetChar
        //    //    ,m_ContinuousSkill.ustTargetLifeCode );
        //    //
        //    ItemDefine::SItemSkill *pSkill = m_ContinuousSkill.pSkill;

        //    if( pSkill->bHoldSkill )
        //    {
        //        //m_ExtendStatus.EnterActionStatus( pSkill->iDurationTime );
        //        //m_holdskill.pSkill = pSkill;
        //        //m_ContinuousSkill.pEffectChar = 0;
        //        //
        //        //{                
        //        //    //m_holdskill.bEffectSkill = false;
        //        //    m_ContinuousSkill.dwTimeNextDoAttack = 0;
        //        //    m_ContinuousSkill.dwTimeSkillHoldingEnd = HQ_TimeGetTime() + pSkill->iDurationTime;
        //        //    m_ContinuousSkill.dwAttackInterval = pSkill->iDamageBalanceDelay;
        //        //}
        //        BeginHoldSkill();

        //        //变成HoldSkill状态
        //        SetStatus( CS_HOLDSKILL );
        //    }
        //    else
        //    {
        //        //改变到攻击状态
        //        SetStatus(CS_ATTACK);
        //    }
        //}        
        //else
        //{
        //    //当前又没有任务
        //    SetStatus( CS_IDLE );
        //}
    }
}

bool BaseCharacter::CheckContinuousSkillCost()
{
    bool bCanContinue = true;

    if( m_ContinuousSkill.bCharTarget )
    { // 判断技能是否可以继续吟唱
        BaseCharacter* pDst = (BaseCharacter*)theRunTimeData.GetCharacterByIDAndLifecode( m_ContinuousSkill.ustTargetChar, m_ContinuousSkill.ustTargetLifeCode );
        if( !pDst )
        {
            //错误的攻击目标
            // 加非法信息
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = GetID();
            HintMsg.shHintId = MsgUseSkillHintMessage::eSkillTargetNotExist;
            GettheServer().SendMsgToSingle( &HintMsg, this );
            bCanContinue = false;
        }
        else if( !IsInAttackRange( pDst,m_ContinuousSkill.pSkill ) )
        {
            //超出攻击范围
            // 加非法信息
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = GetID();
            HintMsg.shHintId = MsgUseSkillHintMessage::eOutAttackRangeHint;
            GettheServer().SendMsgToSingle( &HintMsg, this );
            bCanContinue = false;
        }
        //else if( m_ContinuousSkill.pSkill && m_ContinuousSkill.pSkill->bNeedTestAngle )
        //{
        //    if( pDst != this && !IsTargetInFront( pDst, m_ContinuousSkill.pSkill->fAngle ) )
        //    {
        //        // 没有正对着施法目标
        //        MsgUseSkillHintMessage HintMsg;
        //        HintMsg.header.stID = GetControl()->GetID();
        //        HintMsg.shHintId = MsgUseSkillHintMessage::eUnfaceToTarget;
        //        GettheServer().SendMsgToSingle( &HintMsg, this );
        //        bCanContinue = false;
        //    }
        //}
    }

    if( !bCanContinue )
    { CancelSkill(); }

    return bCanContinue;
}

void BaseCharacter::BeginHoldSkill()
{
    ItemDefine::SItemSkill* pSkill = m_ContinuousSkill.pSkill;
    if ( !pSkill)
        return;

    Msg_IntonateStart start;
    start.header.stID = GetID();
    start.ustSkillID  = pSkill->ustItemID;
    start.cSkillLevel = pSkill->ustLevel;
    start.bCharTarget = m_ContinuousSkill.bCharTarget;

    if ( start.bCharTarget )
    {
        start.target.ustTargetID = m_ContinuousSkill.ustTargetChar;
    }
    else
    {
        start.target.pos.x = GetTileX();
        start.target.pos.y = GetTileY();
    }

    start.usType = 1;
    GettheServer().SendMsgToView( &start, GetID(), false );

    m_ContinuousSkill.pEffectChar = NULL;
    //m_holdskill.bEffectSkill = false;
    m_ContinuousSkill.dwTimeNextDoAttack = 0;
    m_ContinuousSkill.dwTimeSkillHoldingEnd = HQ_TimeGetTime() + pSkill->iDurationTime;
    m_ContinuousSkill.dwAttackInterval = pSkill->iDamageBalanceDelay;
    m_ContinuousSkill.bMoveInterrupt = pSkill->bMoveInterrupt;
}

void BaseCharacter::StatusActionIntonate()
{
    //如果是不出在ActionTime的状态，表示以吟唱结束了,改变状态到，攻击
    if( !CheckContinuousSkillCost() )
    { return; }

    // 吟唱还没完成
    if ( !m_ExtendStatus.IsActionDone() )
    { return; }

    //当前又没有任务
    if (_SkillTaskManager.IsCurTaskDone())
    {
        SetStatus( CS_IDLE );

        if( IsPlayer() )
        {
            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
        }

        return;
    }

    ItemDefine::SItemSkill* pSkill = m_ContinuousSkill.pSkill;
    if ( !pSkill)
    {   
        int nSkillID = _SkillTaskManager.DoneCurTask();
        if( IsPlayer() )
        {
            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            IntonateInterrupt_msg.nSkillID = nSkillID;
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
        }

        SetStatus( CS_IDLE );
    }

    if( MsgUseSkillHintMessage::eNormal != ApplySkillCost( pSkill ) )
    {
        int nSkillID = _SkillTaskManager.DoneCurTask();
        if( IsPlayer() )
        {
            Msg_IntonateInterrupt IntonateInterrupt_msg;
            IntonateInterrupt_msg.header.stID = GetID();
            IntonateInterrupt_msg.nSkillID = nSkillID;
            GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
        }

        SetStatus( CS_IDLE );
        return;
    }

    // 吟唱结束要1秒后才可普通攻击
    m_ExtendStatus.EnterCanNotNormalAttack(1000);
    DWORD dwEmissionFlyTime = GetEmissionFlyTime(_SkillTaskManager.m_nTargetId);

    // 吟唱结束
    Msg_IntonateEnd end;
    end.header.stID         = GetID();
	end.nTargetCount        = 1;
    end.ustSkillID          = pSkill->ustItemID;
    end.ustSkillLevel       = pSkill->ustLevel;
    end.targetList[0].target.ustTargetID = _SkillTaskManager.m_nTargetId;
    end.targetList[0].dwEmissionFlyTime  = dwEmissionFlyTime + 0;

    // 开始ColdDown 开始技能ColdDown    
    if( IsPlayer() )
    {
        GamePlayer *pPlayer = (GamePlayer *)this;

        if ( IsNormalAttack( pSkill->ustItemID ))
        {
        }
        else
        {
            pPlayer->StartSkillCoolDown( pSkill );
        }
    }

    if( pSkill->bHoldSkill )
    {
        BeginHoldSkill();
        //变成HoldSkill状态
        SetStatus( CS_HOLDSKILL );
    }
    else
    {
        if( pSkill->bEmissionSkill )
        {
            BOOL bEmissisonFull = TRUE;

            if ( pSkill->shMaxTargetNum == 1 )
            {// 只有一个目标的发射技能
                 for( int i=0; i<MAXEMISSIONNUM; ++i)
                 {
                     if( m_Emission[i].bDead )
                     {
                         bEmissisonFull              = FALSE;                    
                         ++m_ucHaveEmission;
                         m_Emission[i].bDead         = FALSE;
                         m_Emission[i].dwStartTime   = HQ_TimeGetTime();
                         m_Emission[i].dwLifeTime    = dwEmissionFlyTime + 0;//SPELLACTION_CASTTIME;
                         m_Emission[i].ustTargetID   = _SkillTaskManager.m_nTargetId;
                         m_Emission[i].ustSkillID    = pSkill->ustItemID;
                         m_Emission[i].ustSkillLevel = pSkill->ustLevel;
                         break;
                     }
                 }
            }
            else
            {//有多个目标的发射技能
			    		
                BaseCharacter * pDst = (BaseCharacter*)theRunTimeData.GetCharacterByID( _SkillTaskManager.m_nTargetId );
                if ( pDst == NULL )
                {
                    _SkillTaskManager.DoneCurTask();
                    SetStatus( CS_IDLE );
                    return;
                }

			    SAttackTarget target;
			    target.bIsCharTarget = true;
			    target.nCharID = pDst->GetID();
			    target.vPos = pDst->GetPos();

                std::vector< BaseCharacter* > vecTargetList;
			    FindAttackTarget( &target, pSkill, vecTargetList );

			    end.nTargetCount = vecTargetList.size();
			    for ( int i = 0 ; i < end.nTargetCount ; ++i )
			    {
                    if ( i >= MAXEMISSIONNUM )
                    { break; }

                    BaseCharacter* pTarget = vecTargetList[i];
                    if ( pTarget == NULL )
                    { continue; }

                    DWORD dwEmissionFlyTime = GetEmissionFlyTime( pTarget->GetID() );

				    end.targetList[i].target.ustTargetID = pTarget->GetID();
				    end.targetList[i].dwEmissionFlyTime = dwEmissionFlyTime + 0;

                    if( m_Emission[i].bDead )
                    {
                        bEmissisonFull              = FALSE;                    
                        ++m_ucHaveEmission;
                        m_Emission[i].bDead         = FALSE;
                        m_Emission[i].dwStartTime   = HQ_TimeGetTime();
                        m_Emission[i].dwLifeTime    = dwEmissionFlyTime + 0;//SPELLACTION_CASTTIME;
                        m_Emission[i].ustTargetID   = pTarget->GetID();
                        m_Emission[i].ustSkillID    = pSkill->ustItemID;
                        m_Emission[i].ustSkillLevel = pSkill->ustLevel;
                    }
			    }
            }

            if( bEmissisonFull )
            {
                //改变到攻击状态
                SetStatus( CS_ATTACK );
            }
            else
            {
                _SkillTaskManager.DoneCurTask();
                SetStatus( CS_IDLE );
            }
        }
        else
        {
            //改变到攻击状态
            SetStatus(CS_ATTACK);
        }
    }

	GettheServer().SendMsgToView( &end, GetID(), false );
}

void BaseCharacter::StatusActionHoldSkill()
{
    if( !CheckContinuousSkillCost() )
    { return; }

    DWORD dwTime = HQ_TimeGetTime();
    if( dwTime >= m_ContinuousSkill.dwTimeSkillHoldingEnd )
    {
        //技能结束
        //表示当前任务完成了
        _SkillTaskManager.DoneCurTask();

        //close effectchar
        if( m_ContinuousSkill.pEffectChar )
        {
            m_ContinuousSkill.pEffectChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
            m_ContinuousSkill.pEffectChar = 0;
        }

        Msg_HoldSkillEnd holdend;
        holdend.header.stID = GetID();
        GettheServer().SendMsgToView( &holdend, GetID(), false );

        SetStatus( CS_IDLE );
        return;
    }

    //作结算
    //维持npc技能，这个结算间隔一定要大于结束时间
    //保证只调用一次TryAttack创建技能角色
    if( dwTime >= m_ContinuousSkill.dwTimeNextDoAttack )
    {
        m_ContinuousSkill.dwTimeNextDoAttack = dwTime;
        m_ContinuousSkill.dwTimeNextDoAttack += m_ContinuousSkill.dwAttackInterval;

        SAttackTarget target;

        if( _SkillTaskManager.m_bCharTarget )
        {        
            target.bIsCharTarget = true;
            target.nCharID       = _SkillTaskManager.m_nTargetId;
        }
        else
        {
            target.bIsCharTarget = false;
            target.vPos = _SkillTaskManager.m_vTargetPos;
        }

        // 攻击目标死亡后
        // 要么必须明确的知道攻击目标死亡，然后取消技能么将所有的持续技能转变为攻击某个位置
        DWORD dwState = TryAttack(&target,m_ContinuousSkill.pSkill,_SkillTaskManager.GetCurTask()->id, _SkillTaskManager.GetCurTask()->level );

        if( _HAS_FLAG( dwState,eFIGHT_ERROR ) || 
            _HAS_FLAG( dwState,eFIGHT_CANCEL ) ||
            _HAS_FLAG( dwState,eFIGHT_BEKILLED ) /*||_HAS_FLAG( dwState,eFIGHT_POWNOTENOUGH ) */)
        {
            //维持技能结束
            m_ContinuousSkill.dwTimeSkillHoldingEnd = 0;            
        }
        else
        {
        }
    }
}

void BaseCharacter::StatusActionDieing()
{
    return;
}

void BaseCharacter::StatusActionDoAction()
{
    //如果是不出在ActionTime的状态，表示以吟唱结束了,改变状态到，攻击
    if (!m_ExtendStatus.IsActionTime())
    {
        //改变到攻击状态
        SetStatus(CS_IDLE);
    }
}

void BaseCharacter::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bContinue = true;
}

bool BaseCharacter::ProcessMsg( Msg* pMsg )
{
    if( MSG_EXIT == pMsg->GetType() )
    {
        OnExit( pMsg );         
        return false; // 不处理后续的消息
    }
    return true;    
}

void BaseCharacter::ProcessLogicAfterProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bContinue = true;
}

void BaseCharacter::Run(DWORD dwCostTime)
{
    IBaseControl* pCtrl = GetControl();
    if ( !pCtrl )
    { return; }
    
    bool bContinue = false;
    ProcessLogicBeforeProcessMsg( dwCostTime, bContinue );
    if ( !bContinue)
    { return; }
    
    ApplyNextStatus(); // 应用下一个状态

    ProcessEmission(); // 处理发射延迟

    if( abs( m_fLastMovingSpeed - GetMoveSpeed()) >= 0.0001)
    {
        m_fLastMovingSpeed = GetMoveSpeed();
        ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );
    }

    Msg* pMsg = NULL;
    // 如果找不到pCtrl，估计是掉线后被Release掉了，直接调用OnExit
    // 注意！在任何消息循环的地方调用OnExit后，返回都应该是false
    // 否则将会执行后面的消息。而被Release的Character类再次执行将会崩溃！
    GameObjectId dwID = GetID();
    if ( pCtrl == NULL )
    { return; }

    while( theRunTimeData.theCharacters[dwID] != NULL && (pMsg = pCtrl->GetMsg()) != NULL)
    {
        if (MSG_EXIT != pMsg->GetType())
        {
            if (!ProcessMsg(pMsg))
            { return; }
        }
        else
        {
            ProcessMsg(pMsg);
            return;
        }
    }
}

void BaseCharacter::ChangeSubAction( BYTE bySubAction, GameObjectId sTargetCharId )
{
    if( !IsPlayer() )
        return;
    // 告诉周边玩家状态改变
    m_bySubAction = bySubAction;

    MsgRetChangeSubAction msg;
    msg.stID1  = GetID();
    msg.stID2  = sTargetCharId;
    msg.action = GetSubAction();
    GettheServer().SendMsgToView( &msg, GetID(), false );
}

Msg* BaseCharacter::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{    
    if (nBuffSize < sizeof(MsgNPCEnterMySight))
    { return NULL; }

    //直接在已有BUFFER内new (这里new是为了引发构造，如果不需要引发析构可以不要delete)
    //MsgNPCEnterMySight* pMsg = (MsgNPCEnterMySight*)szMsgBuffer;

    MsgNPCEnterMySight* pMsg = new(szMsgBuffer)MsgNPCEnterMySight;
    pMsg->Reset();
    pMsg->header.stID		= GetID();
    pMsg->nMapID            = GetMapID();
    pMsg->stMonsterType		= -1;
    pMsg->stMasterId		= -1;
    pMsg->fX				= GetFloatX();
    pMsg->fY				= GetFloatY();
    pMsg->fZ                = GetFloatZ();
    pMsg->fDirX				= GetDirX();
    pMsg->fDirY				= GetDirY();
    pMsg->byDir				= GetDir();
    pMsg->ucCountry			= GetCountry();
    pMsg->stCharType		= GetObjType();
    pMsg->dwShowFlag        = GetShowFlag();
    pMsg->bySubAction       = GetSubAction();
    pMsg->fMoveRate         = GetMoveSpeed();    
    pMsg->fNormalAttackRate = GetCharFightAttr()->attackSpeed.final;
    pMsg->nHp               = GetHP();
    pMsg->nHpMax            = GetCharFightAttr()->hpMax.final;
    pMsg->stPhysicDef       = GetCharFightAttr()->defendPhysics.final;
    pMsg->stDodge           = GetCharFightAttr()->dodge.final;
    pMsg->stLevel           = GetLevel();
    pMsg->bMask				= IsMask();
    pMsg->influence			= GetFightCamp();
	pMsg->BelongID			= GetKiller()?GetKiller()->GetID():0;
    return pMsg;
}

int GetUpgradeExp( int iLevel )
{
    if( iLevel < 0 ) 
        iLevel = 1;
    return iLevel*iLevel*1000;
}

// 单位被杀死了
void BaseCharacter::WasKilled( BaseCharacter* pKiller )
{
    switch( GetStatus() )    
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        CancelSkill();
        break;
    }

    // 这里先注释掉, 具体逻辑不清除
    //if (pKiller)
    //{
    //    switch( pKiller->GetObjType() )
    //    {
    //    case Object_Effect:
    //        { // 将killer变换成发出者（注意，保证存在）
    //            // CEffectChar*pEffect = (CEffectChar*)pKiller;
    //            BaseCharacter* pRealKiller = theRunTimeData.GetCharacterByID(GetFirstValidAttacker());
    //            SetKiller( pRealKiller );
    //        }
    //        break;
    //    default:
    //        {
    //            SetKiller( pKiller );
    //        }        
    //        break;
    //    }  
    //}
    // 现在按第一个攻击该外物的计算
    if ( IsPlayer() ) 
    { // 如果是玩家, 算最后一下
        SetKiller( pKiller );
    }
  //  else
  //  {	
		////AiCharacter::WasKilled(pKiller);
		////1.修改配置文件 
		////2.伤害最高的获取拾取权限
		////3.第一次攻击的获取拾取权限

		//// 如果是怪, 需要考虑第一个
  //      /*BaseCharacter* pRealKiller = theRunTimeData.GetCharacterByID( GetFirstValidAttacker() );
  //      if ( pRealKiller != NULL )
  //      {
  //          SetKiller( pRealKiller );
  //      }
  //      else
  //      {
  //          SetKiller( pKiller );
  //      }*/
  //  }

    if ( m_pBelongKiller != NULL )
    {
        GamePlayer* pMaster = m_pBelongKiller->GetMasterPlayer();
        if ( pMaster != NULL )
        { SetKiller( pMaster ); }
    }

    OnDeath();
}

//bool BaseCharacter::IsCanBeAttacked()
//{   
//    switch( GetStatus() )
//    { //一些特别的状态下是不可以被攻击的
//    case CS_START:
//    case CS_CHECK:
//    case CS_LOGIN:
//    case CS_LOGINTODB:
//    case CS_WAITDBRET:
//    case CS_DBLOGINED:
//    case CS_LOADINGMAP:
//        return false;
//        break;
//    }
//    //
//    if( IsDead() )
//        return false;
//    //
//    switch( GetObjType() )
//    {
//    case Object_Effect:
//    case Object_Item:
//    case Object_Npc:
//        return false;
//    }
//    return true;
//}

uint8 BaseCharacter::CheckCanAttackResult( BaseCharacter* pTarget )
{
    if ( pTarget == NULL || pTarget->GetID() == GetID() || !pTarget->CheckCanBeAttack() )
    { return CheckAttack::CanNotAttack; }

    // 无敌状态不能攻击
    if ( _buffManager.IsInvincible() )
    { return CheckAttack::CanNotAttack; }   

    // 自身中了状态不能攻击
    if ( _buffManager.IsRandRun() )
    { return CheckAttack::CanNotAttack; }

    // 对方隐身
    if ( pTarget->_buffManager.IsHide() )
    { return CheckAttack::CanNotAttack; }

    // 阵营怪, 阵营不同的才可以攻击
    if ( HaveFightCamp() && pTarget->HaveFightCamp() )
    { 
        if ( GetFightCamp() != pTarget->GetFightCamp() )
        { return CheckAttack::EnmityFightCamp; }

        // 相同阵营不能攻击
        return CheckAttack::CanNotAttack;
    }

    // 判断是否是仇恨势力
    if ( ForceDefine::CheckEnmityForce( GetForce(), pTarget->GetForce() ) )
    { return CheckAttack::EnmityForce; }

    // 国家怪, 国家不同的才可以攻击
    if ( CountryDefine::CheckEnmityCountry( GetCountry(), pTarget->GetCountry() ) )
    { return CheckAttack::EnmityCountry; }

    return CheckAttack::AttackUnknow;
}


bool BaseCharacter::CheckCanAttackTarget( BaseCharacter* pTarget )
{
    uint8 nResult = CheckCanAttackResult( pTarget );
    switch ( nResult )
    {
    case CheckAttack::CanNotAttack:
        return false;
        break;
    case CheckAttack::EnmityFightCamp:
    case CheckAttack::EnmityCountry:
    case CheckAttack::EnmityForce:
    case CheckAttack::EnmityTarget:
        return true;
        break;
    default:
        break;
    }

    return false;
}

bool BaseCharacter::CheckCanBeAttack()
{
    if ( IsDead() )
    { return false; }

    if ( _buffManager.IsInvincible() )
    { return false; }   // 无敌状态不能攻击


    return true;
}

bool BaseCharacter::CheckWalkPreconditionState()
{
    //判断是否处在一些不可以移动的状态
    if (!_buffManager.IsCanMove())
    {
        TellClient(  theXmlString.GetString(eClient_AddInfo_2slk_78) );
        return false;
    }

    //if (!IsPlayer())
    //{
    //    if ( _buffManager.IsRandRun() )
    //    {
    //        TellClient(  theXmlString.GetString(eClient_AddInfo_2slk_78) );
    //        return false;
    //    }
    //}

    //判断当前的状态
    switch ( GetStatus() )
    {
    case CS_IDLE:
    case CS_WALK:
    case CS_INTONATE:
    case CS_DOACTION:
        {
            return true;
        }
        break;
    default:
        break;
    }

    return false;
}

bool BaseCharacter::IsCanDoAction()
{
    //判断当前的动作可否被打断
    if ( IsDead() || m_ExtendStatus.IsCannotNormalAttack() || HaveFighteFlag( eFighting ) )
    { return false; }

    switch ( GetStatus() )
    {
    case CS_IDLE:        //待机
    case CS_WALK:        //行走
    case CS_DOACTION:    //
        //只有在这几个状态下才可以使用技能
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool BaseCharacter::CheckUseSkillPreconditionState()
{
    // 判断当前的动作可否被打断
    if (m_ExtendStatus.IsCannotNormalAttack())
    { return false; }

    switch ( GetStatus())
    {
    case CS_IDLE:     // 待机
    case CS_WALK:     // 行走
    case CS_DOACTION: // 在做动作
        return true;
        break;
    }
    return false;
}

short BaseCharacter::IsSkillCanUse(int skill_no, int skill_level)
{
    // 得到status的信息
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(skill_no, skill_level);    
    if (!pSkill)
    { return MsgUseSkillHintMessage::eServerCannotFindSkill; }

    // 状态判断
    if (pSkill->ustDamageBalanceType == ItemDefine::balancetype_damagemagicdefend)
    {
        if (!_buffManager.IsCanUsePhysicsSkill())
        { return MsgUseSkillHintMessage::eCannotUsePhysicsSkill; }
    }
    else
    {
        if (!_buffManager.IsCanUseMagicSkill())
        {
			if (IsCollectSkill(pSkill->ustItemID))
			{
				if (_buffManager.IsHaveNegativeStatus(SNT_GIDDY)
					||_buffManager.IsHaveNegativeStatus(SNT_STAND)
					||_buffManager.IsHaveNegativeStatus(SNT_AFRAID)
					||_buffManager.IsHaveNegativeStatus(SNT_SLEEP)
					||_buffManager.IsHaveNegativeStatus(SNT_DISTORTION)
					||_buffManager.IsHaveNegativeStatus(SNT_ALLURE)
					||_buffManager.IsHaveNegativeStatus(SNT_FROST))
				{
					return MsgUseSkillHintMessage::eCannotUseMagicSkill; 
				}
			}
			else
				return MsgUseSkillHintMessage::eCannotUseMagicSkill; 
		}
    }

    // 检测是否HP不足
    if ( GetHP() < pSkill->ustCostHP + 1 )
    { 
        return MsgUseSkillHintMessage::eNoEnoughHpToUseSkill;
    }

    // 检测是否MP不足
    if ( GetMP() < pSkill->ustCostMP )
    {
        return MsgUseSkillHintMessage::eNoEnoughMpToUseSkill;
    }

    return MsgUseSkillHintMessage::eNormal;
}

bool BaseCharacter::IsCastTargetRight( const ItemDefine::SItemSkill *pSkill,int x,int y )
{
    switch ( pSkill->ustCastTarget )
    {
    case ItemDefine::casttarget_pos:
        return true;
        break;
    default:
        break;
    }

    return false;
}

bool BaseCharacter::IsCastTargetRight( const ItemDefine::SItemSkill* pSkill, BaseCharacter* pTarget )
{
    if ( NULL == pSkill || NULL == pTarget )
    { return false; }

    if ( !pSkill->bIsRelive )
    {// 非复活技能判断是否可攻击
        if ( !pTarget->CheckCanBeAttack() )
        { return false; }
    }

	if(pTarget->IsMonster()&&!pTarget->HaveMaster())
	{
		if(pTarget->GetCountry() != CountryDefine::Country_Init && pTarget->GetCountry() == GetCountry() && pTarget != this)
		{
			//同一国家不可以攻击
			return false;
		}
	}

    //物理免疫
    if ( !pTarget->_buffManager.IsCanBePhyAttack() && pSkill->ustDamageBalanceType != ItemDefine::balancetype_damagemagicdefend )
    { return false; }

    //魔法免疫
    if ( !pTarget->_buffManager.IsCanBeMagAttack() && pSkill->ustDamageBalanceType != ItemDefine::balancetype_damagephysicaldefend )
    { return false; }

    switch( pSkill->ustCastTarget )
    {
    case ItemDefine::casttarget_me:    // 对自己
        {
            return pTarget->GetID() == GetID();
        }
        break;
    case ItemDefine::casttarget_friendlive:
        {
            if ( IsPlayer() )
            {
                if ( !pTarget->IsPlayer() )
                { return false; }
                
                GamePlayer* pGamePlayer   = static_cast< GamePlayer* >( this );
                GamePlayer* pTargetPlayer = static_cast< GamePlayer* >( pTarget );
                return pGamePlayer->IsFriend( pTargetPlayer );
            }
            else
            {
                GamePlayer* pMaster = pTarget->GetMasterPlayer();
                if ( pMaster != NULL )
                { return pMaster->GetID() == GetID(); }
            }
            
            return false;
        }
        break;
    case ItemDefine::casttarget_enemylive:
        {
            // 如果是Aoe技能, 不能攻击采集物
            if ( pTarget->IsResourceMonster() )
            { return false; }

            return CheckCanAttackTarget( pTarget );
        }
        break;
    case ItemDefine::casttarget_live:
		{
			if(!pTarget || !pTarget->IsPlayer() || pTarget->IsDead())
				return false;
			return true;
		}
        break;
    case ItemDefine::casttarget_friendcorpse:
        {
            return ( pTarget->IsPlayer() && pTarget->IsDead() );
        }
        break;
    case ItemDefine::casttarget_enemycorpse:
        break;
    case ItemDefine::casttarget_corpse:
        break;
    case ItemDefine::casttarget_treasure:
        {
            return ( pTarget->GetMonsterType() == eMT_Treasure && pSkill->ustLevel >= pTarget->GetLevel() );
        }
        break;
    case ItemDefine::casttarget_herb:
        {
            return ( pTarget->GetMonsterType() == eMT_Herb && pSkill->ustLevel >= pTarget->GetLevel() );
        }
        break;
    case ItemDefine::casttarget_mount:       
        {
            return ( pTarget->GetMonsterType() == eMT_Mount );
        }
        break;
    case ItemDefine::casttarget_insect:   
        {
            return ( pTarget->GetMonsterType() == eMT_Insect );
        }
        break;
    case ItemDefine::casttarget_mine:
        {
            return ( pTarget->GetMonsterType() == eMT_Mine && pSkill->ustLevel >= pTarget->GetLevel() );
        }
        break;
    case ItemDefine::casttarget_wood:
        {
            return ( pTarget->GetMonsterType() == eMT_Wood && pSkill->ustLevel >= pTarget->GetLevel() );
        }
        break;
    case ItemDefine::casttarget_pet:
        {
            GamePlayer* pMaster = pTarget->GetMasterPlayer();
            if ( pMaster == NULL )
            { return false; }

            // 自己宠物为目标
            return pMaster->GetID() == GetID();
        }
        break;
    case ItemDefine::casttarget_team:
        {
            if ( pTarget->IsMonster() )
            {
                GamePlayer* pMaster = pTarget->GetMasterPlayer();
                return IsTeamMember( pMaster );
            }

            return IsTeamMember( pTarget );
        }
        break;
    case ItemDefine::casttarget_guild:
        {
            if ( pTarget->IsMonster() )
            {
                GamePlayer* pMaster = pTarget->GetMasterPlayer();
                if ( pMaster == NULL )
                { return false; }

                return IsGuildMember( pMaster );
            }

            return IsGuildMember( pTarget );
        }
        break;
    case ItemDefine::casttarget_campforce:
        {
            // 如果是Aoe技能, 不能攻击采集物
            if ( pTarget->IsResourceMonster() )
            { return false; }

            if ( CheckCanAttackTarget( pTarget ) ) 
            { return false; }

            return ( GetFightCamp() == pTarget->GetFightCamp() ) || ( GetForce() == pTarget->GetForce() );
        }
        break;
    default:
        break;
    }

    return false;
}

//bool BaseCharacter::IsCastTargetRight( const ItemDefine::SItemSkill* pSkill , BaseCharacter* pTagChar)
//{
//    if (NULL == pSkill)
//    { return false; }
//
//    if ( !pTagChar->IsCanBeAttackedObject() )
//    { return false; }
//
//    bool bRight = true;
//    switch( pSkill->stTargetType )
//    {
//    case CItemDetail::target_myself:
//        {
//            if ( this == pTagChar )
//            { return true;}
//        }
//        break;
//    case ItemDefine::target_friend:
//        {
//            if( pTagChar->GetCountry() != GetCountry() )
//            { return false; }
//        }
//        break;
//    case CItemDetail::target_enemy:
//        {
//            if (pTagChar->IsMonster())
//            {
//                MonsterBaseEx * pMonster = static_cast< MonsterBaseEx * >(pTagChar);
//                if (!pMonster->IsNeedFightMonster())
//                { return false; }
//            }
//
//            if (pTagChar == this)
//            {
//                if (pSkill->shCastType != ItemDefine::casttype_singletarget)
//                { return false; }
//            }
//
//            return IsCanAttack(pTagChar);
//        }
//        break;
//    case CItemDetail::target_treasure:
//        if( pTagChar->IsMonster() )
//        {
//            MonsterBaseEx* pAIChar = (MonsterBaseEx*)pTagChar;
//            if( pAIChar->GetMonsterType() != eMT_Treasure || pSkill->ustLevel < pTagChar->GetLevel() )
//            { return false; }
//        }
//        else
//        { return false; }
//
//        break;
//    case CItemDetail::target_herb:
//        if( pTagChar->IsMonster() )
//        {
//            MonsterBaseEx* pAIChar = (MonsterBaseEx*)pTagChar;
//            if( pAIChar->GetMonsterType() != eMT_Herb || pSkill->ustLevel < pTagChar->GetLevel() )
//            { return false; }
//        }
//        else
//        { return false; }
//        break;
//    case CItemDetail::target_mount:
//        {
//            if( pTagChar->IsMonster() )
//            {
//                MonsterBaseEx* pAIChar = (MonsterBaseEx*)pTagChar;
//                if( pAIChar->GetMonsterType() != eMT_Mount )
//                { return false; }
//            }
//            else
//            { return false; }
//        }
//        break;
//    case CItemDetail::target_insect:
//        {
//            if( pTagChar->IsMonster() )
//            {
//                MonsterBaseEx* pAIChar = (MonsterBaseEx*)pTagChar;
//                if( pAIChar->GetMonsterType() != eMT_Insect )
//                { return false; }
//            }
//            else
//            { return false; }
//        }
//        break;
//    case CItemDetail::target_mine:
//        {
//            if( pTagChar->IsMonster() )
//            {
//                MonsterBaseEx* pAIChar = (MonsterBaseEx*)pTagChar;
//                if( pAIChar->GetMonsterType() != eMT_Mine || pSkill->ustLevel < pTagChar->GetLevel() )
//                { return false;}
//            }
//            else
//            { return false;}
//        }
//        break;
//    case CItemDetail::target_wood:
//        {
//            if (pTagChar->IsMonster())
//            {
//                MonsterBaseEx* pAIChar = (MonsterBaseEx*)pTagChar;
//                if (pAIChar->GetMonsterType() != eMT_Wood || pSkill->ustLevel < pTagChar->GetLevel())
//                { return false; }
//            }
//            else
//            { return false;}
//        }
//        break;
//    case CItemDetail::target_dead:
//        {
//            if (pTagChar->IsPlayer()&&pTagChar->IsDead() )
//            { return true;  }
//            else
//            { return false; }
//        }
//        break;
//    case ItemDefine::target_team:
//        {
//            if (pTagChar->IsMonster() )
//            {
//                MonsterBaseEx* pAiChar = (MonsterBaseEx* )pTagChar;
//                GameObjectId masterId = pAiChar->GetSummonMasterID();
//                if ( masterId < 0)
//                { return false; }
//                else
//                { // 有主人
//                    // 主人不是自己 同时也不是队友
//                    BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( masterId );
//                    if ( pMaster == NULL)
//                    { return false; }
//
//                    if ( pMaster != this && !IsTeamMember( pMaster ))
//                    { return false; }
//                }
//            }
//            else if (pTagChar->IsPlayer() )
//            {
//                if ( pTagChar != this && !IsTeamMember(pTagChar))
//                { return false;}
//            }
//        }
//        break;
//    case CItemDetail::target_pet:
//        {
//            if (!pTagChar->IsMonster())
//            { return false; }
//            else
//            {
//                if ( IsPlayer() )
//                {
//                    GamePlayer* pPlayer = static_cast<GamePlayer*>( this );
//                    if ( pPlayer->IsSelfSummonPet( pTagChar->GetID() ) || pPlayer->_petManager.IsSelfPet( pTagChar->GetID() ) )
//                    { return false; }
//                }
//            }
//        }
//        break;
//    case ItemDefine::target_guild:
//        {
//            if (pTagChar->IsMonster() )
//            { return false; }
//            else if (pTagChar->IsPlayer() )
//            {
//                if ( GetGuildID() == GuildDefine::InitID )
//                { return false; }
//
//                if ( GetGuildID() == pTagChar->GetGuildID() )
//                { return true; }
//            }
//        }
//        break;
//    default:
//        return false;
//        break;
//    }    
//    return true;
//}

// 判断是否在范围内
BOOL BaseCharacter::IsPosInRange( float x, float y, float fRange )
{
    float xoff = 0;
    float yoff = 0;
    float fDist = 0; //距离

    xoff = x - GetFloatX();
    yoff = y - GetFloatY();
    fDist = sqrtf( xoff*xoff + yoff*yoff );

    if( fDist < fRange )
    {
        return TRUE;
    }
    return FALSE;
}

//BOOL BaseCharacter::IsInAttackRange( float x, float y, float fDstBodySize, ItemDefine::SItemSkill *pSkill, float fRangeCorrect )
//{ // 判断某个技能攻击距离
//    float fRange = 0;   // 可攻击距离    
//    float fMinRange = 0;// 最小攻击距离
//
//    fRange += m_fBodySize;
//    fRange += fDstBodySize;
//
//    if ( pSkill )
//    { // 技能存在
//        if ( IsNormalAttack( pSkill->ustItemID ))
//        { // 普通攻击技能 只算武器距离 
//            fRange += GetWeaponAttackRange(); 
//        }
//        else
//        { // 常规技能 只算技能距离
//            fRange    += pSkill->fRangeCanCast;
//            fMinRange += pSkill->fRangeCanCastMin;
//
//            if (IsMonster() && static_cast<MonsterBase*>(this)->IsPassiveAttack() && (GetHP() == GetCharFightAttr()->hpMax.final) )
//            {
//                // fRange += 1;
//            }
//            else if( IsPlayer() && pSkill->fRangeCanCast > 0)
//            {
//                // fRange += 1;
//            }
//        }
//    }
//    else
//    { // 技能不存在 只算武器距离
//        fRange += GetWeaponAttackRange(); 
//    }
//
//    fRange += fRangeCorrect;
//
//    float xoff = x - GetFloatX();
//    float yoff = y - GetFloatY();
//
//    float fDis = xoff*xoff + yoff*yoff ;
//
//    if( fDis < fRange * fRange)
//        return TRUE;
//
//    return FALSE;
//}

bool BaseCharacter::IsInValidCastRange( float x, float y, ItemDefine::SItemSkill* pSkill )
{
    if ( !pSkill)
        return false;

    float fDistanceX = x - GetFloatX();
    float fDistanceY = y - GetFloatY();

    float fDistance = fDistanceX * fDistanceX + fDistanceY * fDistanceY;
    if ( pSkill->fRangeCanCast * pSkill->fRangeCanCast >= fDistance )
    {
        return true;
    }
    return false;
}

BOOL BaseCharacter::IsInAttackRange(BaseCharacter *pDst,ItemDefine::SItemSkill *pSkill, float fRangeCorrect)
{
    return AttackFunction::InAttackRange( pSkill, GetPos(), pDst->GetPos(), GetBodySize(), pDst->GetBodySize(), GetWeaponAttackRange(), fRangeCorrect);
}

BaseCharacter* BaseCharacter::GetLockChar()
{
    return theRunTimeData.GetCharacterByID( GetLockID() );
}

bool BaseCharacter::FindAttackTarget( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkill, OUT CFormula& formula  )
{
    if( !pSkill || !pTarget )
    { return false; }

    GameStage* pStage = NULL;
    static const int iMaxEnemy = dr_MaxAttackTarget * 2;
    GameObjectId nAttackTargetID[iMaxEnemy];
    int iEnemyNum = 0, iEnemyLoop = 0;
    RECT rc;
    GameObjectId stCharID;    
    short stTargetX,stTargetY;
    unsigned short ustSkillID = pSkill->ustItemID;

    switch( pSkill->shCastType )
    {
    case ItemDefine::casttype_singletarget:
        if( !pTarget->bIsCharTarget )
        { return false; }

        iEnemyNum = 1;
        nAttackTargetID[0] = pTarget->nCharID;
        break;
    case ItemDefine::casttype_AOEPointCircleArea:
        {   
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pTarget->vPos, pSkill, nAttackTargetID, iMaxEnemy );
            if ( iEnemyNum <= 0)
                return false;
        }
        break;
    case ItemDefine::casttype_AOEcircleself:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, GetPos(), pSkill, nAttackTargetID, iMaxEnemy );

            if( iEnemyNum <= 0 )
            { return false; }
        }
        break;
    case ItemDefine::casttype_AOEhalfcirclefrontage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI, TRUE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOEquartercirlcefrontage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI * 0.5f, TRUE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOEhalfcirclebackage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI, FALSE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOEquartercirlcebackage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI*0.5f, FALSE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOETargetcirclearea:
        {

			if (this->IsEffectChar()) //特效怪只关心目标位置
			{
				pStage = theGameWorld.GetStageById( GetMapID() );
				if( !pStage )
					return false;

				iEnemyNum = pStage->GetTargetInCircle( this, pTarget->vPos, pSkill, nAttackTargetID, iMaxEnemy );
				if ( iEnemyNum <= 0)
					return false;
			}else
			{
				if( !pTarget->bIsCharTarget )
				{ return false; }

				BaseCharacter* pTargetChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( pTarget->nCharID );
				if ( !pTargetChar)
				{ return false; }

				pStage = theGameWorld.GetStageById( pTargetChar->GetMapID() );
				if( !pStage )
				{ return false; }

				iEnemyNum = pStage->GetTargetInCircle( this, pTargetChar->GetPos(), pSkill, nAttackTargetID, iMaxEnemy );

				if( iEnemyNum <= 0 )
				{ return false; }
			}  
        }
        break;
    default:
        return false;
        break;
    }

    // 扣掉不要的ID
    int nMaxTargetNum = pSkill->shMaxTargetNum;
    if ( IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast<GamePlayer*> ( this );
        nMaxTargetNum += pPlayer->GetXinFaSkillEffectValue( pSkill, SkillAttr_AOECharNum );
    }

	GameObjectId NearMeTarget = -1;
    float  MinDistance = 10000.f;
    for( iEnemyLoop = 0 ; iEnemyLoop < iEnemyNum ; ++iEnemyLoop )
    {
        stCharID = nAttackTargetID[ iEnemyLoop ];
        BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( stCharID );
        if( !pChar )
            continue;

        if( pChar == this && pSkill->shCastType == ItemDefine::casttype_AOEcircleself )
        { // 自己
            if (pSkill->stTargetType == ItemDefine::target_friend || pSkill->stTargetType == ItemDefine::target_team)
            {
                //ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID,pSkill->ustDstAddStatusLevel);
                //if (!pStatus/*||!pStatus->bAvail*/)
                //{
                //    continue;
                //}
            }
        }

        // 如果技能不是复活技能并且目标已死
        if ( !pSkill->bIsRelive && pChar->IsDead() )
        { continue; }

        if ( !pChar->IsCanBeAttackedObject() )
        { continue; }

        // 是怪或者角色
        // 如果是群体加BUFF技能，不是对友不给加
        ItemDefine::SItemStatus* pDstStatusConfig = GettheItemDetail().GetStatus( pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0] );
        if ( pDstStatusConfig != NULL && pDstStatusConfig->bAvail && pSkill->shCastType == ItemDefine::casttype_AOEcircleself )
        {
            if ( pChar->IsPlayer() )
            { // 如果是人
                if ( pChar != this )
                { 
                    switch ( pSkill->stTargetType )
                    {
                    case ItemDefine::target_guild:
                        {
                            if ( GetGuildID() == GuildDefine::InitID || pChar->GetGuildID() == GuildDefine::InitID )
                            { continue; }

                            if ( GetGuildID() != pChar->GetGuildID() )
                            { continue; }
                        }
                        break;
                    case ItemDefine::target_campforce:
                        {
                            if ( CheckCanAttackTarget( pChar ) ) 
                            { continue; }

                            if ( ( GetFightCamp() != pChar->GetFightCamp() ) && ( GetForce() != pChar->GetForce() ) )
                            { continue; }
                        }
                        break;
                    default:
                        if ( !IsTeamMember(pChar)  )
                        { continue; }
                        break;
                    }
                }
            }
            else if ( pChar->IsMonster() )
            {// 如果是宠物 队友的宠物也要加buff
                MonsterBaseEx* pMonster = static_cast<MonsterBaseEx*>( pChar );
                GamePlayer* pMaster = pMonster->GetMasterPlayer();
                if ( pMaster != NULL && pMaster != this )
                {
                    switch ( pSkill->stTargetType )
                    {
                    case ItemDefine::target_guild:
                        {
                            if ( GetGuildID() == GuildDefine::InitID || pMaster->GetGuildID() == GuildDefine::InitID )
                            { continue; }

                            if ( GetGuildID() != pMaster->GetGuildID() )
                            { continue; }
                        }
                        break;
                    case ItemDefine::target_campforce:
                        {
                            if ( CheckCanAttackTarget( pChar ) ) 
                            { continue; }

                            if ( ( GetFightCamp() != pChar->GetFightCamp() ) && ( GetForce() != pChar->GetForce() ) )
                            { continue; }
                        }
                        break;
                    default:
                        if ( !IsTeamMember( pMaster ) )
                        { continue; }
                        break;
                    }
                }
            }
            else if ( pChar->GetObjType() == Object_MonsterNurturePet )
            {// 如果是宠物 队友的宠物也要加buff
                MonsterBaseEx* pPet = static_cast<MonsterBaseEx*>( pChar );
                GamePlayer * pSummonMaster = pPet->GetMasterPlayer();
                if ( pSummonMaster->GetID() != GetID() )
                {
                    switch ( pSkill->stTargetType )
                    {
                    case ItemDefine::target_guild:
                        {
                            if ( GetGuildID() == GuildDefine::InitID || pSummonMaster->GetGuildID() == GuildDefine::InitID )
                            { continue; }

                            if ( GetGuildID() != pSummonMaster->GetGuildID() )
                            { continue; }
                        }
                        break;
                    case ItemDefine::target_campforce:
                        {
                            if ( CheckCanAttackTarget( pChar ) ) 
                            { continue; }

                            if ( ( GetFightCamp() != pChar->GetFightCamp() ) && ( GetForce() != pChar->GetForce() ) )
                            { continue; }
                        }
                        break;
                    default:
                        if ( !IsTeamMember( pSummonMaster ) )
                        { continue; }
                        break;
                    }
                }
            }
            else
            { // Monster NpcFight
                continue;
            }
        }

        bool bAddTarget = true;
        if ( IsPlayer() )
        {
            GamePlayer* pPlayer = static_cast<GamePlayer*>( this );
            if ( pPlayer->HaveSummonPet() && pChar->_buffManager.IsPetSupport())
            {
                for ( int i=0;i<CharSummonPetMaxCount; ++i)
                {
                    SSummonPet* pPetMonster = pPlayer->GetSummonPet( i );
                    if ( NULL == pPetMonster )
                    { continue;  }

                    BaseCharacter* pAiChar = theRunTimeData.GetCharacterByID( pPetMonster->petId );
                    if ( pAiChar && static_cast<MonsterBaseEx*>(pAiChar)->IsPet() )
                    {
                        bAddTarget = formula.AddTarget( pAiChar );
                    }
                }
            }
            else
            {
                bAddTarget = formula.AddTarget( pChar );
            }
        }
        else
        {
            bAddTarget = formula.AddTarget( pChar );
        }
        
		//特效怪
		if (this->IsEffectChar() && pChar != this)
		{
		      float distance =  0;
			  D3DXVECTOR3 MePos = D3DXVECTOR3(GetPos().x,GetPos().y,0);
			  D3DXVECTOR3 TargetPos = D3DXVECTOR3(pChar->GetPos().x,pChar->GetPos().y,0);
			  distance = D3DXVec3Length(&(MePos - TargetPos));

			   if( distance < MinDistance )
			   {
				  MinDistance = distance;
				  NearMeTarget = pChar->GetID();
			   }
		}

        if( !bAddTarget || formula.GetTargetNum() >= nMaxTargetNum )
        { break; }
    }

	if (NearMeTarget != -1)
	{
		((CEffectChar*)this)->SetAttackTarget(NearMeTarget);
	}

    return ( formula.GetTargetNum() > 0 );
}

bool BaseCharacter::FindAttackTarget( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkill, OUT std::vector< BaseCharacter* >& vecTargetList )
{
    if( !pSkill || !pTarget )
    { return false; }

    GameStage* pStage = NULL;
    static const int iMaxEnemy = dr_MaxAttackTarget * 2;
    GameObjectId nAttackTargetID[iMaxEnemy];
    int iEnemyNum = 0, iEnemyLoop = 0;
    RECT rc;
    GameObjectId stCharID;    
    short stTargetX,stTargetY;
    unsigned short ustSkillID = pSkill->ustItemID;

    switch( pSkill->shCastType )
    {
    case ItemDefine::casttype_singletarget:
        if( !pTarget->bIsCharTarget )
        { return false; }

        iEnemyNum = 1;
        nAttackTargetID[0] = pTarget->nCharID;
        break;
    case ItemDefine::casttype_AOEPointCircleArea:
        {   
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pTarget->vPos, pSkill, nAttackTargetID, iMaxEnemy );
            if ( iEnemyNum <= 0)
                return false;
        }
        break;
    case ItemDefine::casttype_AOEcircleself:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, GetPos(), pSkill, nAttackTargetID, iMaxEnemy );

            if( iEnemyNum <= 0 )
            { return false; }
        }
        break;
    case ItemDefine::casttype_AOEhalfcirclefrontage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI, TRUE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOEquartercirlcefrontage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI * 0.5f, TRUE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOEhalfcirclebackage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI, FALSE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOEquartercirlcebackage:
        {
            pStage = theGameWorld.GetStageById( GetMapID() );
            if( !pStage )
                return false;

            iEnemyNum = pStage->GetTargetInCircle( this, pSkill, nAttackTargetID, iMaxEnemy, D3DX_PI*0.5f, FALSE );

            if( iEnemyNum <= 0 )
                return false;
        }
        break;
    case ItemDefine::casttype_AOETargetcirclearea:
        {
            if( !pTarget->bIsCharTarget )
            { return false; }

            BaseCharacter* pTargetChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( pTarget->nCharID );
            if ( !pTargetChar)
            { return false; }

            pStage = theGameWorld.GetStageById( pTargetChar->GetMapID() );
            if( !pStage )
            { return false; }

            iEnemyNum = pStage->GetTargetInCircle( this, pTargetChar->GetPos(), pSkill, nAttackTargetID, iMaxEnemy );

            if( iEnemyNum <= 0 )
            { return false; }
        }
        break;
    default:
        return false;
        break;
    }

    // 扣掉不要的ID
    int nMaxTargetNum = pSkill->shMaxTargetNum;
    if ( IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast<GamePlayer*> ( this );
        nMaxTargetNum += pPlayer->GetXinFaSkillEffectValue( pSkill, SkillAttr_AOECharNum );
    }

    for( iEnemyLoop = 0 ; iEnemyLoop < iEnemyNum ; ++iEnemyLoop )
    {
        stCharID = nAttackTargetID[ iEnemyLoop ];
        BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( stCharID );
        if( !pChar )
            continue;

        if( pChar == this && pSkill->shCastType == ItemDefine::casttype_AOEcircleself )
        { // 自己
            if (pSkill->stTargetType == ItemDefine::target_friend || pSkill->stTargetType == ItemDefine::target_team)
            {
                //ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(pSkill->ustDstAddStatusID,pSkill->ustDstAddStatusLevel);
                //if (!pStatus/*||!pStatus->bAvail*/)
                //{
                //    continue;
                //}
            }
        }

        // 如果技能不是复活技能并且目标已死
        if ( !pSkill->bIsRelive && pChar->IsDead() )
        { continue; }

        if ( !pChar->IsCanBeAttackedObject() )
        { continue; }

        // 是怪或则角色
        // 如果是群体加BUFF技能，不是对友不给加
        ItemDefine::SItemStatus* pDstStatusConfig = GettheItemDetail().GetStatus( pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0] );
        if ( pDstStatusConfig != NULL && pDstStatusConfig->bAvail && pSkill->shCastType == ItemDefine::casttype_AOEcircleself )
        {
            if ( pChar->IsPlayer() )
            { // 如果是人
                if ( pChar != this )
                { 
                    switch ( pSkill->stTargetType )
                    {
                    case ItemDefine::target_guild:
                        {
                            if ( GetGuildID() == GuildDefine::InitID || pChar->GetGuildID() == GuildDefine::InitID )
                            { continue; }

                            if ( GetGuildID() != pChar->GetGuildID() )
                            { continue; }
                        }
                        break;
                    case ItemDefine::target_campforce:
                        {
                            if ( CheckCanAttackTarget( pChar ) ) 
                            { continue; }

                            if ( ( GetFightCamp() != pChar->GetFightCamp() ) && ( GetForce() != pChar->GetForce() ) )
                            { continue; }
                        }
                        break;
                    default:
                        if ( !IsTeamMember(pChar)  )
                        { continue; }
                        break;
                    }
                }
            }
            else if ( pChar->GetObjType() == Object_MonsterPet )
            {// 如果是宠物 队友的宠物也要加buff
                MonsterBaseEx* pPet = static_cast<MonsterBaseEx*>( pChar );
                BaseCharacter * pSummonMaster = pPet->GetMasterPlayer();
                if ( pSummonMaster != this )
                {
                    switch ( pSkill->stTargetType )
                    {
                    case ItemDefine::target_guild:
                        {
                            if ( GetGuildID() == GuildDefine::InitID || pSummonMaster->GetGuildID() == GuildDefine::InitID )
                            { continue; }

                            if ( GetGuildID() != pSummonMaster->GetGuildID() )
                            { continue; }
                        }
                        break;
                    case ItemDefine::target_campforce:
                        {
                            if ( CheckCanAttackTarget( pChar ) ) 
                            { continue; }

                            if ( ( GetFightCamp() != pChar->GetFightCamp() ) && ( GetForce() != pChar->GetForce() ) )
                            { continue; }
                        }
                        break;
                    default:
                        if ( !IsTeamMember( pSummonMaster ) )
                        { continue; }
                        break;
                    }
                }
            }
            else
            { // Monster NpcFight
                continue;
            }
        }

        if ( IsPlayer() )
        {
            GamePlayer* pPlayer = static_cast<GamePlayer*>( this );
            if ( pPlayer->HaveSummonPet() && pChar->_buffManager.IsPetSupport())
            {
                for ( int i=0;i<CharSummonPetMaxCount; ++i)
                {
                    SSummonPet* pPetMonster = pPlayer->GetSummonPet( i );
                    if ( NULL == pPetMonster )
                    { continue;  }

                    BaseCharacter* pAiChar = theRunTimeData.GetCharacterByID( pPetMonster->petId );
                    if ( pAiChar && static_cast<MonsterBaseEx*>(pAiChar)->IsPet() )
                    {
                        vecTargetList.push_back(pAiChar);
                    }
                }
            }
            else
            {
                vecTargetList.push_back(pChar);
            }
        }
        else
        {
             vecTargetList.push_back(pChar);
        }

        if( vecTargetList.size() >= nMaxTargetNum )
        { break; }
    }

    return ( vecTargetList.size() > 0 );
}


bool BaseCharacter::OnSetMonsterBelong(BaseCharacter * pTarget)
{
	//设置怪物的归属 就是说这个怪物的掉落归谁
	if(IsPlayer())
		return false;

	if(pTarget == NULL)
	{
		//清空怪物的归属
		if(m_pBelongKiller == NULL)
		{
			return false;
		}
		SetKiller(pTarget);
		//发送命令到九宫格去
		MsgMonsterBeLongID msg;
		msg.MonsterID = GetID();
		msg.BeLongID = 0;
		GettheServer().SendMsgToView( &msg, GetID(),false);
		return true;
	}
	else
	{
		/*if(m_pKiller)
			return false;*/
		if(IsPet()) return false;//宠物无法设置归属

		if(pTarget->IsPlayer())
		{
			if(m_pBelongKiller == pTarget)
				return false;
			SetKiller(pTarget);//设置归属
			//发送命令道九宫格去 告诉附近的玩家 怪物的归属 设置怪物头像为灰色
			MsgMonsterBeLongID msg;
			msg.MonsterID = GetID();
			msg.BeLongID = pTarget->GetID();
			GettheServer().SendMsgToView( &msg, GetID(),false);
			return true;
		}
		else if(pTarget->IsPet())
		{
			GamePlayer* pMaster = m_pBelongKiller->GetMasterPlayer();
			if(!pMaster)
				return false;
			if(m_pBelongKiller == pMaster)
				return false;
			SetKiller(pMaster);
			MsgMonsterBeLongID msg;
			msg.MonsterID = GetID();
			msg.BeLongID = pMaster->GetID();
			GettheServer().SendMsgToView( &msg, GetID(),false);
			return true;
		}
		else
			return false;
	}
}

void BaseCharacter::OnBeAttacked( BaseCharacter* pAttacker, const ItemDefine::SItemSkill* pSkillConfig )
{ // 受到攻击的时候
    if (!pAttacker)
    { return; }

    bool bBuffHaveChange = false;

    // 清被攻击时候需要清除的buff
    if ( _buffManager.IsClearStatusInAttack() && _buffManager.UpdateOnBeAttack( pSkillConfig ) )
    {
        //_buffManager.LogAndClearBufferClearIdArray();
        //_buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );
        bBuffHaveChange = true;
    }

    // 被暴击时候带的buff
    bool bBeCritical = GetIsBeCriticaled();
    if ( bBeCritical && _buffManager.IsBeCriticaledNeedAddBuffer())
    {        
        if(_buffManager.UpdateStatusIsInCriticaled( bBeCritical ))
        {
            long nResult = ApplyBufferStatus(_buffManager.GetBeCriticaledBufferId(),_buffManager.GetBeCriticaledBuffedLevel(), GetID(),SCharBuff::StatusEventType_Skill,pSkillConfig->ustDamageBalanceType);
            if ( nResult == GLR_Success)
            {
                SetIsBeCriticaled( false );
                bBuffHaveChange = true;
            }
        }
    }

    // 被攻击
    if ( UpdateBuffOnBeAttacked() )
    { bBuffHaveChange = true; }

    // 是否有buff改变
    if ( bBuffHaveChange )
    { OnBuffStatusChanged( true ); }

    TryChangeFightState( HaveEnmity(), eFighting );
}

void BaseCharacter::OnHaveStatusDisplacement()
{
    // 取消移动是需要结束的buff
    if ( _buffManager.IsHaveMoveDispelBuff() && _buffManager.UpdateOnMove())
    { OnBuffStatusChanged( true ); }
}

void BaseCharacter::OnBeBackAttack()
{
    if ( _buffManager.IsHaveBackAttackDispelBuff() && _buffManager.UpdateOnBackAttack())
    {
        OnBuffStatusChanged( true );
    }
}

void BaseCharacter::OnBuffStatusChanged( bool bSendMessage )
{
    _buffManager.LogAndClearBufferClearIdArray();
    ApplyBuffStatusToCharAttr();
    
    if ( bSendMessage)
    {
        SendBuffChanged( NULL );
        //SendBuffs( ErrorUnsignedShortID, true );
    }
}

// 判断Char对象是不是在自己的前面
BOOL BaseCharacter::IsTargetInFront( BaseCharacter* pChar, float fMaxAngle )
{
    float fAngle = 0;//fDir1和fDir2的夹角
    float x = 0;
    float y1 = 0;
    float y2 = 0;
    float c = 0;
    D3DXVECTOR3 vSelfDir;
    D3DXVECTOR3 vTargetDir;

    vSelfDir.x = GetDirX();
    vSelfDir.y = GetDirY();
    vSelfDir.z = 0;
    vTargetDir.x = pChar->GetFloatX() - GetFloatX();
    vTargetDir.y = pChar->GetFloatY() - GetFloatY();
    vTargetDir.z = 0;
    //vTargetDir.x = GetFloatX() - pChar->GetFloatX();
    //vTargetDir.y = GetFloatY() - pChar->GetFloatY();
    //vTargetDir.z = 0;
    x = vSelfDir.x*vTargetDir.x + vSelfDir.y*vTargetDir.y + vSelfDir.z*vTargetDir.z;
    y1 = sqrtf(vSelfDir.x*vSelfDir.x + vSelfDir.y*vSelfDir.y + vSelfDir.z*vSelfDir.z);
    y2 = sqrtf(vTargetDir.x*vTargetDir.x + vTargetDir.y*vTargetDir.y + vTargetDir.z*vTargetDir.z);
    if( y1*y2 <= 0 )
    {
        if( x > 0 )
        {
            c = 1.0f;
        }

        if( x < 0 )
        {
            c = -1.0f;
        }

        if( x == 0 )
        {
            c = 0;
        }
    }
    else
    {
        c = x/(y1*y2);
    }

    if( c > 1.0f )
    {
        c = 1.0f;
    }

    if( c < -1.0f )
    {
        c = -1.0f;
    }

    fAngle = acos( c );

    if( fAngle < fMaxAngle*0.5f )
    {
        return TRUE;
    }

    return FALSE;
}

// 判断Char对象是不是在自己的后面
BOOL BaseCharacter::IsTargetInBack( BaseCharacter* pChar, float fMaxAngle )
{
    float fAngle = 0;//fDir1和fDir2的夹角
    float x = 0;
    float y1 = 0;
    float y2 = 0;
    float c = 0;
    D3DXVECTOR3 vSelfDir;
    D3DXVECTOR3 vTargetDir;

    vSelfDir.x = -GetDirX();
    vSelfDir.y = -GetDirY();
    vSelfDir.z = 0;
    vTargetDir.x = pChar->GetFloatX() - GetFloatX();
    vTargetDir.y = pChar->GetFloatY() - GetFloatY();
    vTargetDir.z = 0;
    x = vSelfDir.x*vTargetDir.x + vSelfDir.y*vTargetDir.y + vSelfDir.z*vTargetDir.z;
    y1 = sqrtf(vSelfDir.x*vSelfDir.x + vSelfDir.y*vSelfDir.y + vSelfDir.z*vSelfDir.z);
    y2 = sqrtf(vTargetDir.x*vTargetDir.x + vTargetDir.y*vTargetDir.y + vTargetDir.z*vTargetDir.z);
    if( y1*y2 <= 0 )
    {
        if( x > 0 )
        {
            c = 1.0f;
        }

        if( x < 0 )
        {
            c = -1.0f;
        }

        if( x == 0 )
        {
            c = 0;
        }
    }
    else
    {
        c = x/(y1*y2);
    }

    if( c > 1.0f )
    {
        c = 1.0f;
    }

    if( c < -1.0f )
    {
        c = -1.0f;
    }

    fAngle = acos( c );

    if( fAngle < fMaxAngle*0.5f )
    {
        return TRUE;
    }

    return FALSE;
}

//判断自己是否在某个返回之内
bool BaseCharacter::IsInMapArea(uint32 nMapID, float fX, float fY, float fLimit )
{
    if (GetMapID() != nMapID)
    { return false; }

    D3DXVECTOR3 vDistance( fX - GetFloatX(), fY - GetFloatY(), 0);

    float fDistance = D3DXVec3Length( &vDistance);
    return ( fDistance<= fLimit );
}

// 判断自己是不是在Char对象的后面
BOOL BaseCharacter::IsInTargetBack( BaseCharacter* pChar, float fMaxAngle )
{
    //if( !IsTargetInFront( pChar, fMaxAngle*2 ) )
    //{
    //    return FALSE;
    //}

    float fAngle = 0;//fDir1和fDir2的夹角
    float x = 0;
    float y1 = 0;
    float y2 = 0;
    float c = 0;
    D3DXVECTOR3 vSelfDir;
    D3DXVECTOR3 vTargetDir;

    //vSelfDir.x = GetDirX();
    //vSelfDir.y = GetDirY();
    //vSelfDir.z = 0;
    //vTargetDir.x = pChar->GetDirX();
    //vTargetDir.y = pChar->GetDirY();
    //vTargetDir.z = 0;

    vSelfDir.x = GetFloatX() - pChar->GetFloatX();
    vSelfDir.y = GetFloatY() - pChar->GetFloatY();
    vSelfDir.z = 0;
    vTargetDir.x = -pChar->GetDirX();
    vTargetDir.y = -pChar->GetDirY();
    vTargetDir.z = 0;

    x = vSelfDir.x*vTargetDir.x + vSelfDir.y*vTargetDir.y + vSelfDir.z*vTargetDir.z;
    y1 = sqrtf(vSelfDir.x*vSelfDir.x + vSelfDir.y*vSelfDir.y + vSelfDir.z*vSelfDir.z);
    y2 = sqrtf(vTargetDir.x*vTargetDir.x + vTargetDir.y*vTargetDir.y + vTargetDir.z*vTargetDir.z);

    if( y1*y2 <= 0 )
    {
        if( x > 0 )
        {
            c = 1.0f;
        }
        else if( x < 0 )
        {
            c = -1.0f;
        }
        else if( x == 0 )
        {
            c = 0;
        }
    }
    else
    {
        c = x/(y1*y2);
    }

    if( c > 1.0f )
    {
        c = 1.0f;
    }
    else if( c < -1.0f )
    {
        c = -1.0f;
    }

    fAngle = acos( c );

    if( fAngle < fMaxAngle*0.5 )
        return TRUE;

    return FALSE;
}

// 真正技能释放的代码入口，
// 所有的一切攻击 全部都是状态.
// 物理攻击 是一种伤害状态
// 魔法攻击 是元素伤害
// 附加状态 本来就是状态
DWORD BaseCharacter::SkillDischarge( SAttackTarget *pTarget, unsigned short ustSkillID, unsigned short ustSkillLevel, BaseCharacter *pMaster, int nTargetCount /* = 0 */ )
{   
    if ( NULL == pTarget )
    { // 判定合法性
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetNotExist;
        GettheServer().SendMsgToSingle( &HintMsg, this );
        return eFIGHT_ERROR; 
    }

    const ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(ustSkillID, ustSkillLevel);
    if( pSkillConfig == NULL )
    { // 技能不存在
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eServerCannotFindSkill;
        GettheServer().SendMsgToSingle( &HintMsg, this );
        return eFIGHT_ERROR; 
    }

    if (( pTarget->bIsCharTarget ) && ( pTarget->nCharID < 0 ) )
    { //如果技能是针对npc得并且，目标npc为空，不结算退出
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetWrong;
        GettheServer().SendMsgToSingle( &HintMsg, this );
        return eFIGHT_ERROR; 
    }

    //处理非发射技能攻击僵硬时间
    if( !pSkillConfig->bEmissionSkill )
    {
        long nResult   = ProcessAttackSpeed( pSkillConfig );
        if ( RESULT_FAILED( nResult ) )
        { return eFIGHT_ERROR; }

		//lyh++ 如果在吟唱中，同时使用了其他技能则不接受处理
		//if ( GetStatus() == CS_INTONATE || GetStatus() == CS_HOLDSKILL )
		//{
		//	return eFIGHT_ERROR;
		//}
    }

    switch ( pSkillConfig->specialSkillType )
    {
    case ItemDefine::ESST_Normal:
    case ItemDefine::ESST_Other:
    case ItemDefine::ESST_Team:
        return ProcessNormalSkill       ( pTarget, pSkillConfig, pMaster, nTargetCount );
        break;
    case ItemDefine::ESST_Capture:
        return ProcessCaptureSkill      ( pTarget, pSkillConfig, pMaster);
        break;
    case ItemDefine::ESST_SuckFetch:
        return ProcessSuckFetchSkill    ( pTarget, pSkillConfig, pMaster );
        break;
    case ItemDefine::ESST_BreakOut:
        return ProcessBreakOutSkill     ( pSkillConfig, pMaster );
        break;
    case ItemDefine::ESST_CallGraphic:
        return ProcessCallGraphicSkill  ( pSkillConfig );
        break;
    case ItemDefine::ESST_TeamRelive:
        return ProcessTeamRelive        ( pSkillConfig );
        break;
    case ItemDefine::ESST_TeamFly:
        return ProcessTeamFlyToHeader   ( pSkillConfig );
        break;
    case ItemDefine::ESST_XPSkill:
        return ProcessXPSkill           ( pSkillConfig, pMaster );
        break;
    case ItemDefine::ESST_PetActive:
        return ProcessPetActive         ( pSkillConfig );
        break;
    }
    return eFIGHT_NOFLAG;
}

//是否有足够的MP,HP,TP支持技能
short BaseCharacter::ApplySkillCost( ItemDefine::SItemSkill *pSkill )
{
    if ( pSkill == NULL)
    { return MsgUseSkillHintMessage::eServerCannotFindSkill; }

    if(  IsMonster() )
    {
        MonsterBaseEx* pMonsterBase = (MonsterBaseEx*)this;
        if ( pMonsterBase->IsResourceMonster() )
        {
            //HP消耗
            int nValue;
            if( pSkill->ustCostHP > 0 )
            {
                nValue = GetHP();
                nValue -= pSkill->ustCostHP;
                nValue += pSkill->nSuckHpAtt;
                SetHP( nValue );
            }

            //MP消耗
            if( pSkill->ustCostMP > 0 )
            {
                nValue = GetMP();
                nValue -= pSkill->ustCostMP;
                nValue += pSkill->nSuckMpAtt;
                SetMP( nValue );
            }
        }
    }

    return MsgUseSkillHintMessage::eNormal;
}

DWORD BaseCharacter::TryAttack( SAttackTarget* pTarget,ItemDefine::SItemSkill *pSkill,unsigned short ustSkillID, unsigned short ustSkillLevel, int nTargetCount /* = 0 */ )
{
    if( !pTarget || !pSkill )
    { return eFIGHT_ERROR; }

    if ( _buffManager.IsRandRun() )
    { return eFIGHT_ERROR; }

    if( pTarget->bIsCharTarget )
    {
        BaseCharacter *pTargetChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( pTarget->nCharID );
        if( pTargetChar == NULL || ( !pSkill->bIsRelive && pTargetChar->IsDead()) )
        { return eFIGHT_ERROR; }

        if ( !pTargetChar->_buffManager.IsCanBePhyAttack() && pSkill->ustDamageBalanceType != ItemDefine::balancetype_damagemagicdefend )
        { return eFIGHT_ERROR; }

        if ( !pTargetChar->_buffManager.IsCanBeMagAttack() && pSkill->ustDamageBalanceType != ItemDefine::balancetype_damagephysicaldefend )
        { return eFIGHT_ERROR; }
    }

    //如果技能是普通攻击并且不能使用物理技能则退出
    if (IsNormalAttack(ustSkillID) && !_buffManager.IsCanUsePhysicsSkill())
        return eFIGHT_ERROR;

    //坐骑技能需要判断人物职业
    if (pSkill->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl)
    {
		if (GetProfession() >= EArmType_MaxSize)
			return eFIGHT_ERROR;//防止策划乱配置技能
        if (!pSkill->arrayProfessionReq[GetProfession()])
            return eFIGHT_ERROR;
    }

    //如果技能不是普通攻击并且不能使用魔法技能则退出
    //if (!IsNormalAttack(ustSkillID) && !m_cFightStatus.IsCanUseMagicSkill() )
    //    return eFIGHT_ERROR;

    //处理脚本技能
    if ( pSkill->bScriptRunSkill && IsPlayer())
    {
        OnScriptSkill( pSkill );
        return eFIGHT_NOFLAG;
    }

    DWORD state = eFIGHT_ERROR;
    switch (pSkill->stSkillType)
    {
    case ItemDefine::skilltype_action:
        {
            state = SkillDischarge(pTarget, ustSkillID, ustSkillLevel, this, nTargetCount );
            //if ( state == eFIGHT_NOFLAG && !IsCollectSkill(ustSkillID) )
            //{  TryPassivenessTriggerAttack();}

            return state;
        }
        break;
    case ItemDefine::skilltype_magic_hit:
        {
            if (!pSkill->bGiddyDischarge)
            {
                if (!_buffManager.IsCanUseMagicSkill())
                    return eFIGHT_ERROR;
            }

            state = SkillDischarge(pTarget, ustSkillID, ustSkillLevel, this, nTargetCount );
            //if ( state == eFIGHT_NOFLAG && !IsCollectSkill(ustSkillID) )
            //{  TryPassivenessTriggerAttack();}

            return state ;
        }
        break;
    case ItemDefine::skilltype_magic_npc:
        {
			if (!_buffManager.IsCanUseMagicSkill())
				return eFIGHT_ERROR;

			ItemDefine::SItemSkill* pSkillItem = GettheItemDetail().GetSkillByID( ustSkillID, ustSkillLevel );
			if ( !pSkillItem )
				return eFIGHT_ERROR;

			float stTargetX = 0.f, stTargetY = 0.f;
			float fTargetDirX = 0.f ,fTargetDirY = 0.f;

			switch(pSkillItem->shCastType)
			{
			case ItemDefine::casttype_AOEcircleself: // 以自己为中心的圆形范围技能 *
				{
					stTargetX = GetFloatX();
					stTargetY=	GetFloatY();
					fTargetDirX = GetDirX();
					fTargetDirY = GetDirY();
				}
				break;
			case ItemDefine::casttype_AOEPointCircleArea: // 目标地点的圆形范围
				{
					stTargetX = _SkillTaskManager.m_vTargetPos.x;
					stTargetY=	_SkillTaskManager.m_vTargetPos.y;
				}
				break;
			case ItemDefine::casttype_AOETargetcirclearea:// 以选定目标为中心的圆形范围技能
				{
					stTargetX = GetFloatX();
					stTargetY=	GetFloatY();
					fTargetDirX = GetDirX();
					fTargetDirY = GetDirY();
					BaseCharacter* pDst = (BaseCharacter*)theRunTimeData.GetCharacterByID( pTarget->nCharID );
					if(pDst)
					{
						stTargetX = pDst->GetFloatX();
						stTargetY = pDst->GetFloatY();
						fTargetDirX = pDst->GetDirX();
						fTargetDirY = pDst->GetDirY();
					}
				}
				break;
			}		 

			pTarget->vPos.x = stTargetX;
			pTarget->vPos.y = stTargetY;
			//============================================================

			EFFECTCHARCONFIG _config;
			//查找失败只召唤一个
			if(!theEffectCharConfig.FindEffectCharConfigBySkillID(_config,ustSkillID))
			{
				state = MagicObjectAttack(pTarget, ustSkillID, ustSkillLevel);
			}else
			{
				if (_config.SummonCnt <= 1)
				{
					state = MagicObjectAttack(pTarget, ustSkillID, ustSkillLevel);
				}
				else
				{
					float _angle = 0.f;
					if(_config.SummonCnt > 1)
						_angle = D3DX_PI*2 / (float)_config.SummonCnt;

					for (int i = 0 ; i < _config.SummonCnt ; i++)
					{
						pTarget->vPos.x = cos((_angle) * i) * _config.SummonDistince + stTargetX;
						pTarget->vPos.y = sin((_angle) * i) * _config.SummonDistince + stTargetY;
						state = MagicObjectAttack(pTarget, ustSkillID, ustSkillLevel);
					}				
				}	
			}


			//if ( state == eFIGHT_NOFLAG && !IsCollectSkill(ustSkillID) )
			//{  TryPassivenessTriggerAttack();}
			return state; 
		}
		break;
    }
    return state;
}


DWORD BaseCharacter::MagicObjectAttack(SAttackTarget* pTarget, DWORD ustSkillID, DWORD ustSkillLevel)
{ //释放出一个出现在地图上的法术效果
    if ( !pTarget )
        return eFIGHT_ERROR;

    //维持技能只能创建一个CEffectChar
    if(( CS_HOLDSKILL == GetStatus() ) && ( m_ContinuousSkill.pEffectChar ) )
        return eFIGHT_ERROR;

	ItemDefine::SItemSkill* pSkillItem = GettheItemDetail().GetSkillByID( ustSkillID, ustSkillLevel );
	if ( !pSkillItem )
		return eFIGHT_ERROR;
	
		CEffectChar* pEffect = theGameWorld.CreateEffectChar(this, "EffCharacter", GetMapID(), ustSkillID, ustSkillLevel, pTarget->vPos.x, pTarget->vPos.y);
		if ( !pEffect)
			return eFIGHT_ERROR;

    //如果处于维持技能状态，保存CEffectChar
    m_ContinuousSkill.pEffectChar = pEffect;

    return eFIGHT_NOFLAG;
}

bool BaseCharacter::IsNextStepMoveable( int iDir )
{   
    GameStage *pStage = theGameWorld.GetStageById( GetMapID() );
    if (NULL == pStage)
    { return false; }

    short stXOff,stYOff;
    GetOffsetByDir( iDir,stXOff,stYOff );

    short stNextX = GetTileX() + stXOff;
    short stNextY = GetTileY() + stYOff;

    if ( IsMonster() )
    { return true; }

    if( !pStage->Moveable( this,stNextX,stNextY ) )
    { return false; }
    return true;
}

bool BaseCharacter::MoveToNextStep(BYTE byDir)
{    
    //到这里一定需要确定，能够移动到这步

    //BYTE byDir = m_aMovePath.byzPath [ m_aMovePath.iCurPos ];
    //计算每步行走的消耗

    short stXOff,stYOff;
    GetOffsetByDir( byDir,stXOff,stYOff );
    short stNewX = GetTileX() + stXOff;
    short stNewY = GetTileY() + stYOff;

    SetTileX(stNewX);
    SetTileY(stNewY);

    CaluStepCost(byDir);

    MsgMoveAStep move;
    move.sNpcID      = GetID();
    move.header.stID = GetID();
    move.byDir = byDir;
    //move.stX = stNewX;
    //move.stY = stNewY;
    //发送行走命令给旁观者
    GettheServer().SendMsgToView( &move, GetID(), true );
    SetDir( byDir );
    //ChangeMapMask( stNewX,stNewY );    
    return true;
}

void BaseCharacter::RefreshCharData( DWORD dwCostTime )
{ // 时间性的数据

    // 所以步骤是 伤害 -> Update清理 ->

    UpdateBuffDamage(); // buff伤害Update 对存在的buff进行使用 

    UpdateBuff();       // buffUpdate     会有buff的变更 清除

    // 清除仇恨
    for ( int i = 0; i < BodyStatusType_Max; ++i )
    {
        SCharBuff* pBufferStatus = _buffManager.GetBuffClearRecord( i );
        if ( pBufferStatus == NULL )
        { continue; }

        // 清除仇恨, 后来注释掉 不用清除仇恨了
        //ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pBufferStatus->StatusID ,pBufferStatus->iLevel );
        //if ( pItemStatus == NULL || pItemStatus->nStandingEnmity <= 0 )
        //{ continue; }

        //BaseCharacter* pCharAttacker = theRunTimeData.GetCharacterByID( pBufferStatus->stMasterID );
        //if ( pCharAttacker == NULL )
        //{ continue; }

        pBufferStatus->StatusID = 0;
        pBufferStatus->iLevel   = 0;
    }
}

// 调试信息输出。
void LogMsg( NetControlEx* pCrtl, Msg* pMsg )
{

#ifdef MSG_DBG
    int size = pMsg->GetLength();    
#else
    char *pszChar = (char*)&pMsg->header.dwType;    
#endif // MSG_DBG
    //
    DWORD dwType = pMsg->GetType();
    if (MSG_LOGIN == dwType)                    //= TAG('qlog')
    {
        MsgLogin* p = (MsgLogin*)pMsg;
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "szUserName = [%s]", p->szUserName);
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "szPassword = [%s]", p->szPassword );
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "stModelID  = [%d]", p->stModelID );
    }
    else if (MSG_ACKLOGIN == dwType)
    {
        MsgAckLogin* p = (MsgAckLogin*)pMsg;        
    }
    else if (MSG_EXIT == dwType)
    {
        MsgExit* p = (MsgExit*)pMsg;
    }
    else if (MSG_QUERYMOVE == dwType)
    {
        MsgQueryMove* p = (MsgQueryMove*)pMsg;
    }
    else if (MSG_ACKMOVE == dwType)
    {
        MsgAckMove* p = (MsgAckMove*)pMsg;
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "pos(x,y) = [%d,%d]",   p->x,p->y );
    }
    else if (MSG_MOVEPATH == dwType)                //= TAG('mpth')
    {
        MsgMovePath* p = (MsgMovePath*)pMsg;
        char szTmp[MsgMovePath::const_iMaxPath+1];       
    }
    else if (MSG_MOVETOTARGET == dwType)            //= TAG('movt')
    {
        MsgMoveToTarget* p = (MsgMoveToTarget*)pMsg;
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "Target(x,y) = [%d,%d]", p->stTargetX,p->stTargetY );
    }
    //case MSG_ENTERMYSIGHT            //= TAG('esig')
    //    {
    //        MsgEnterMySight* p = (MsgEnterMySight*)pMsg;
    //    }
    //    break;
    else if (MSG_EXITMYSIGHT == dwType) 
    {
        MsgExitMySight* p = (MsgExitMySight*)pMsg;
    }
    //else if (MSG_CHANGEMAP == dwType)
    //{
    //    MsgChangeMap* p = (MsgChangeMap*)pMsg;
    //}
    else if (MSG_MAPLOADED == dwType)
    {
        MsgMapLoaded* p = (MsgMapLoaded*)pMsg;
    }
    else if (MSG_QUERYDISPLAYNAME == dwType)
    {
        MsgQueryDisplayName* p = (MsgQueryDisplayName*)pMsg;
    }
    else if (MSG_ACKDISPLAYNAME == dwType)
    {
        MsgAckDisplayName* p = (MsgAckDisplayName*)pMsg;
    }
    /*case MSG_ENTERMYSIGHTMOVING
    {
    MsgEnterMySightMoving* p = (MsgEnterMySightMoving*)pMsg;
    }*/
    else if (MSG_ACKATTACK == dwType)
    {
        MsgAckAttack* p = (MsgAckAttack*)pMsg;;
    }
    else if (MSG_SEEATTACK == dwType)
    {
        MsgSeeAttack* p = (MsgSeeAttack*)pMsg;
    }
    else if (MSG_WHODIE == dwType)
    {
    }
    else if (MSG_QUERYGAMEPROPERTY == dwType)
    {
        MsgQueryGameProperty* p = (MsgQueryGameProperty*)pMsg;
    }
    else if (MSG_ACKGAMEPROPERTY == dwType)
    {
        MsgAckGameProperty* p = (MsgAckGameProperty*)pMsg;
    }
    else if (MSG_QUERYALLGAMEPROPERTY == dwType)
    {
        MsgQueryAllGameProperty* p = (MsgQueryAllGameProperty*)pMsg;
    }
    else if (MSG_ACKALLGAMEPROPERTY == dwType)
    {
        MsgAckAllGameProperty* p = (MsgAckAllGameProperty*)pMsg;
    }
    else if (MSG_EVENTRANGE == dwType)
    {
        MsgEventRange* p = (MsgEventRange*)pMsg;
    }
    else if (MSG_CHAT == dwType)
    {
        MsgChat* p = (MsgChat*)pMsg;
    }
    else if (MSG_ACKCHAR == dwType)
    {
    }
    else if (MSG_ENTERWORLD == dwType)
    {
    }
    else if (MSG_ACKENTERWORLD == dwType)
    {
    }
    else if (MSG_CREATECHAR == dwType)
    {
    }
    else if (MSG_ACKCREATECHAR == dwType) 
    {
    }
    else if (MSG_DELETECHAR == dwType)
    {
    }
    else if (MSG_ACKDELETECHAR == dwType)
    {
    }
    ////数据库相关
    //else if (DBMSG_LOGIN == dwType)     
    //{
    //}
    //else if (DBMSG_ACKLOGIN == dwType)  
    //{
    //}
    //else if (DBMSG_ACKCHAR == dwType)   
    //{
    //}
    //else if (DBMSG_SAVECHAR == dwType)  
    //{
    //}
    //else if (DBMSG_CREATECHAR == dwType)
    //{
    //}
    //else if (DBMSG_DELETECHAR == dwType)
    //{
    //}
}

void BaseCharacter::ApplySpecialAttr( int iWhichAttr,USpecialAttrValue *pValue,bool bAdd,MsgCharAttrChanged *pChangeECS,bool bApplyEquip )
{ //ToCheck
    //将变化下发 或者客户端自己处理
    int iValue;
    float fValue;    
    switch( iWhichAttr ) 
    {
        //case SpecialAttr_AddPhysicAtt:
        //    /*{
        //        iValue = GetPhysicAtt()->final;

        //        APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

        //        SetPhysicAtt( iValue );
        //    }        */
        //    break;
    case SpecialAttr_AddPhysicDef:
        //{
        //    iValue = GetPhysicDef()->final;

        //    //iValue += pValue->iValue;
        //    APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

        //    SetPhysicDef( iValue );
        //}
        break;
    case SpecialAttr_AddMagicAtt:
        //{
        //    iValue = GetMagicAtt()->final;
        //    //iValue += pValue->iValue;
        //    APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );
        //    SetMagicAtt( iValue );
        //}
        break;
    case SpecialAttr_AddMagicDef:
        //{
        //    iValue = GetMagicDef()->final;
        //    //iValue += pValue->iValue;
        //    APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );
        //    SetMagicDef( iValue );
        //}
        break;
    case SpecialAttr_AddBonusDamageRange:        
        {
            //iValue = GetMinBonusDamageRange();
            //APPLY_SPECIALATTR(bAdd,iValue,pValue->short2.stValue0 );
            //SetMinBonusDamageRange( iValue );

            //iValue = GetMaxBonusDamageRange();
            //APPLY_SPECIALATTR(bAdd,iValue,pValue->short2.stValue0 );
            //SetMaxBonusDamageRange( iValue );
        }
        break;
    case SpecialAttr_AddCriticalAttackFactor:
        {
            //        fValue = GetCriticalAttackFactor();
            //fValue += pValue->fValue;
            //        APPLY_SPECIALATTR(bAdd,fValue,pValue->fValue );
            //        SetCriticalAttackFactor( fValue );
        }
        break;
    case SpecialAttr_AddNormalAttackRate:
        {
            fValue = GetCharFightAttr()->attackSpeed.final;
            //fValue += pValue->fValue;
            APPLY_SPECIALATTR(bAdd,fValue,pValue->fValue );

            GetCharFightAttr()->attackSpeed.final = fValue;

            if( pChangeECS )
                pChangeECS->AddAttrFloatChange( CharAttr_AttackSpeed,fValue );
        }
        break;
    case SpecialAttr_AddMoveRate:
        {
            fValue = GetMoveSpeed();
            //fValue += pValue->fValue;
            APPLY_SPECIALATTR(bAdd,fValue,pValue->fValue );
            GetCharFightAttr()->moveSpeed.base=fValue;
            GetCharFightAttr()->moveSpeed.UpdateFinal();
            if( pChangeECS )
            { pChangeECS->AddAttrFloatChange( CharAttr_MoveSpeed,fValue ); }
        }
        break;
    case SpecialAttr_AddHPRestoreRate:
        {
            iValue = GetCharFightAttr()->hpRestore.final;
            APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );
            GetCharFightAttr()->hpRestore.base = iValue;
        }
        break;
    case SpecialAttr_AddMagicCastRate:
        break;
    case SpecialAttr_DecTPCost:
        break;
    case SpecialAttr_AddPosionResist:
        break;
    case SpecialAttr_DispelPoison:
        break;
    case SpecialAttr_DispelSilence:
        break;
    case SpecialAttr_NormalRelive:
        break;
    case SpecialAttr_FullRelive:
        break;
    case SpecialAttr_DispelStone:
        break;
    case SpecialAttr_Identify:
        break;
    case SpecialAttr_MagicImmunity:
        break;
    case SpecialAttr_PhysicImmunity:
        break;
    case SpecialAttr_HPHeal:
        {
            //没有反向操作
            if( bAdd && GetHP() < GetCharFightAttr()->hpMax.final && !IsDead() )
            {            
                OperateHP( EOT_Add, pValue->iValue );

                if( pChangeECS )
                { pChangeECS->AddAttrShortChange( CharAttr_HPHeal, GetHP()); }
            }
        }
        break;
    case SpecialAttr_PoisonRate:
        {
            //装备的时候，不计算
            if( bApplyEquip )
                break;
            int iRand = theRand.rand32() % 100;
            if( iRand >= pValue->short3.stValue0 )
                break;
            DWORD dwDuration = pValue->short3.stValue2;
            dwDuration *= 100;
        }
        break;
    case SpecialAttr_FrostRate:
    case SpecialAttr_StoneRate:
    case SpecialAttr_SleepRate:
        {
            //装备的时候，不计算
            if( bApplyEquip )
                break;
            int iRand = theRand.rand32() % 100;
            if( iRand >= pValue->short2.stValue0 )
                break;
            DWORD dwDuration = pValue->short2.stValue1;
            dwDuration *= 100;
            int iBodyStatus = 0;
            switch( iWhichAttr )
            {
            case SpecialAttr_FrostRate:
                //                iBodyStatus = BodyStatus_Frost;
                break;
            case SpecialAttr_StoneRate:
                //                iBodyStatus = BodyStatus_Stone;
                break;
            case SpecialAttr_SleepRate:
                //                iBodyStatus = BodyStatus_Sleep;
                break;                
            }
        }
        break;
    case SpecialAttr_AddPhysicAtt:
        {
            iValue = GetCharFightAttr()->attackPhysics.final;

            APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

            GetCharFightAttr()->attackPhysics.final = iValue;
            /*SetPhysicAttMax( iValue );*/

        }
        break;
        //case SpecialAttr_AddPhysicAttMin:
        //    {
        //        iValue = GetPhysicAtt()->final;

        //        APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

        //        SetPhysicAtt(iValue);
        //        /*SetPhysicAttMin( iValue );*/

        //    }
        //    break;
    case SpecialAttr_AddMagicAttMax:
        {/*
         iValue = GetMagicAttMax()->final;

         APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

         SetMagicAttMax( iValue );*/

        }
        break;
        //case SpecialAttr_AddMagicAttMin:
        //    {
        //        iValue = GetMagicAttMin()->final;
        //        APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue);
        //        SetMagicAttMin(iValue);
        //    }
        //    break;
    case SpecialAttr_AddPhysicDefMax:
        {/*
         iValue = GetPhysicDefMax()->final;

         APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

         SetPhysicDefMax( iValue );*/
        }
        break;
        //case SpecialAttr_AddPhysicDefMin:
        //    {
        //        iValue = GetPhysicDefMin()->final;

        //        APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

        //        SetPhysicDefMin( iValue );
        //    }
        //    break;
    case SpecialAttr_AddMagicDefMax:
        {
            //APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );
        }
        break;
        //case SpecialAttr_AddMagicDefMin:
        //    {
        //        iValue = GetMagicDefMin()->final;

        //        APPLY_SPECIALATTR(bAdd,iValue,pValue->iValue );

        //        SetMagicDefMin( iValue );
        //    }
        //    break;
    }
}

int CompareSkill( char *lpData0,char *lpData1 )
{
    return (int)(*(ItemDefine::SItemSkill**)lpData0 - *(ItemDefine::SItemSkill**)lpData1);
}

int CompareBodyStatus( char *lpData0,char *lpData1 )
{
    return *(short*)lpData0 - *(short*)lpData1;
}

void BaseCharacter::SendSyncCharPosToGate( int iGate )
{
    Msg_GW2G_SyncCharPos sync;

    // 如果还没有进入游戏世界
    if( 0== GetMapID() )
    { return; }

    sync.header.stID = GetID();
    sync.stAreaID    = GetCurArea();
    sync.dwMapID     = GetMapID();

    //发给所有Gate
    if( -1 == iGate )
    { GettheServer().SendMsgToGates( &sync ); }
    else
    { GettheServer().SendMsgToGate( &sync,iGate ); }// 初始化，不单独处理
}

void BaseCharacter::SendNPCExit()
{
    Msg_GW2G_NPCExit npcexit;
    npcexit.header.stID = GetID();
    GettheServer().SendMsgToGates( &npcexit );
}

void BaseCharacter::UpdateBuffDamage()
{
    if ( _buffManager.GetEnableStatusNum() <= 0 )
    {
		return;
	}

    bool bSrcSendMsgFlag = false;
    bool bSendMsgFlag    = false;

    MsgSeeDamage SrcSeeDamage;

    MsgSeeDamage SeeDamage;
    SeeDamage.header.stID = GetID();

    CFormula formula;

    bool bIsBuffStatusChangeTotal = false;

    for( int i=0; i<_buffManager.GetBufferStatusCount(); ++i )
    {
        SCharBuff* pStatusBuff = _buffManager.GetBuff(i);
        if ( pStatusBuff == NULL )
        { continue; }

        if ( pStatusBuff->StatusID <= 0 || pStatusBuff->iLevel <= 0)
        { continue; }

        // 伤害
        ItemDefine::SItemStatus* pStateConfig = GettheItemDetail().GetStatus(pStatusBuff->StatusID, pStatusBuff->iLevel);
        if ( pStateConfig == NULL )
        { continue; }

        if ( !pStateConfig->IsHaveContinueValueChange())
        { continue;}

        if ( pStatusBuff->bStop )
        { continue; }

        if (pStateConfig->iBalanceDelayTime <= 0)
        { continue; }

        if ( GameTime::IsPassCurrentTime( pStatusBuff->dwPreDamage, pStateConfig->iBalanceDelayTime))
        {
            switch( pStateConfig->stBalanceType )
            {
            case ItemDefine::balance_status_type_timeexp: // 时间经验
                {
                    if ( !IsPlayer() )
                    { continue;}

                    GamePlayer* pGamePlayer = (GamePlayer*)this;
                    // 等级为lv的玩家IntervalTime获得经验值
                    // = Modulus1 / (( lv+Modulus2 ) * Modulus3 ) ^ ( Modulus4 / ( lv + Modulus5 ))
                    //int exp = pStateConfig->timeExpModulus[0] / pow( ( GetLevel() + pStateConfig->timeExpModulus[1]) * pStateConfig->timeExpModulus[2] ,
                    //    pStateConfig->timeExpModulus[3] / ( GetLevel() + pStateConfig->timeExpModulus[4]));

                    //exp = exp * ( 1 + _buffManager.GetTimeExpMul() );

                    if(pStateConfig->timeExpModulus[1] == 0)
                    { pStateConfig->timeExpModulus[1] = 1; }

                    int exp =  GetLevel() * pStateConfig->timeExpModulus[0] / pStateConfig->timeExpModulus[1] + pStateConfig->timeExpModulus[2];

                    if ( _buffManager.GetTimeExpMul() > 0)
                    { exp = exp * ( 1 * _buffManager.GetTimeExpMul() ); }

                    if ( exp > 0 )
                    { 
                        pGamePlayer->IncreaseExp( exp, 0 );
						
                        Log(theXmlString.GetString(eLog_Buffer_AddExp),pStateConfig->GetItemName(),exp);
                    }

                    int32 addMoney = _buffManager.GetAddMoney();   
                    if ( addMoney > 0 )
                    {
                        pGamePlayer->OperateJiaoZi( EOT_Add, addMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_BuffAdd);
                    }

                    int32 addReputation = _buffManager.GetAddReputation(); 
                    if ( addReputation > 0 )
                    {
                        pGamePlayer->OperateReputation( EOT_Add, addReputation, __FUNCTION__, __LINE__,ePlayerMoneySourceType_BuffAdd );
                    }

                    int32 addExploit = _buffManager.GetAddExploit(); 
                    if ( addExploit > 0 )
                    {
                        pGamePlayer->OperateExploit( EOT_Add, addExploit, __FUNCTION__, __LINE__,ePlayerMoneySourceType_BuffAdd );
                    }

                    int32 addHonour = _buffManager.GetAddHonour(); 
                    if ( addHonour > 0 )
                    {
                        pGamePlayer->OperateHonour( EOT_Add, addHonour, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_BuffAdd);
                    }

                    int32 addMasterValue = _buffManager.GetAddMasterValue(); 
                    if ( addMasterValue > 0 )
                    {
                        pGamePlayer->OperateMasterValue( EOT_Add, addMasterValue );
                    }

                    int32 addBattleScore = _buffManager.GetAddBattleScore(); 
                    if( addBattleScore > 0 )
                    {
                        pGamePlayer->OperateEctypeScore( EOT_Add, addBattleScore );
                    }

                }
                break;
            default:
                { // 普通结算
                    BaseCharacter* pSrcChar = theRunTimeData.GetCharacterByID(pStatusBuff->masterId);
                    if ( pSrcChar == NULL )
                    { // 攻击者没有了，就把状态清掉
                        pSrcChar = theRunTimeData.GetGamePlayerByDBID( pStatusBuff->dwPlayerDBID );
                        if ( pSrcChar == NULL ) // 攻击者没有了
                        {
                            _buffManager.ClearBuff(i);                
                            bIsBuffStatusChangeTotal = true;
                            continue;
                        }
                    }

                    if ( pSrcChar->IsPlayer() )
                    {
                        GamePlayer* pGamePlayer = (GamePlayer*)pSrcChar;
                        if ( !pGamePlayer || pGamePlayer->GetDBCharacterID() != pStatusBuff->dwPlayerDBID )
                        {                    
                            _buffManager.ClearBuff(i);
                            bIsBuffStatusChangeTotal = true;
                            continue;
                        }
                    }

                    // 新加 ( 现在切换地图有无敌状态,所以持续伤害都不能有了 )
                    // 不是有利状态, 攻击者地图和自己不一样了 ( 2010-1-8 ) 
                    if ( !pStateConfig->bAvail && pSrcChar->GetMapID() != GetMapID() )
                    {
                        _buffManager.ClearBuff(i);                
                        bIsBuffStatusChangeTotal = true;
                        continue;
                    }

                    // 设置状态初始信息
                    formula.SetStatusTarget(this);
                    formula.SetStatusSrc(pSrcChar);
                    formula.SetStatusBuff(pStatusBuff);
                    formula.SetStatusInfo(pStatusBuff->StatusID, pStatusBuff->iLevel);

                    // 状态伤害结算
                    formula.BalanceStatusHero();

                    // 取得伤害结果
                    CFormula::SResult* pTagResult = formula.GetTargetStatusResult();
                    CFormula::SResult* pSrcResult = formula.GetSrcStatusResult();
                    MsgSeeDamage::TargetResult result;
                    result.stStatusID = pStatusBuff->StatusID;
                    result.stLevel    = pStatusBuff->iLevel;

                    bool bAttackBuffHaveChanged = false;
                    bool bSingleBuffIsCallStatusChange = false;
                    if (!IsDead())
                    { // 中状态者的数值结算
                        if ( ApplyCenter::ApplyTargetFormule( this, pSrcChar, 1, pStatusBuff->eventValue, pTagResult, pSrcResult, &result.xResult, bSingleBuffIsCallStatusChange, bAttackBuffHaveChanged) )
                        {
                            if ( bSingleBuffIsCallStatusChange && !bIsBuffStatusChangeTotal)
                            { bIsBuffStatusChangeTotal = true; }
                            // 客户端的通知
                            SeeDamage.AddResult( &result );
                            bSendMsgFlag = true;
                        }
					}
                    if ( pSrcChar )
                    { // 对状态释放者的数值
                        SrcSeeDamage.header.stID = pSrcChar->GetID();
                        if ( !pSrcChar->IsDead() )
                        {
                            if (ApplyCenter::ApplySourceFormule( this, pSrcChar, 1, pSrcResult, &result.xResult, bSingleBuffIsCallStatusChange, bAttackBuffHaveChanged))
                            {
                                if ( bSingleBuffIsCallStatusChange && !bIsBuffStatusChangeTotal)
                                { bIsBuffStatusChangeTotal = true; }

                                if ( bAttackBuffHaveChanged )
                                { pSrcChar->OnBuffStatusChanged( true ); }

                                SrcSeeDamage.AddResult( &result );
                                bSrcSendMsgFlag = true;
                            }
                        }
                    }                   
                }
                break;
            }			
            pStatusBuff->dwPreDamage = HQ_TimeGetTime();
        }
    }

	// 发结算的结果给客户端
	if ( bSendMsgFlag )
	{
		SeeDamage.CaluLength();
		GettheServer().SendMsgToView( &SeeDamage, GetID(), false );
	}

	if ( bSrcSendMsgFlag )
	{
		SrcSeeDamage.CaluLength();
		GettheServer().SendMsgToView( &SrcSeeDamage, GetID(), false );
	}

    if ( bIsBuffStatusChangeTotal )
    { OnBuffStatusChanged( true ); }
}

bool BaseCharacter::UpdateBuffOnAttack()
{ //检查在攻击的时候是否需要清掉状态
    if (_buffManager.IsAttackClearStatus())
    {
        if (_buffManager.UpdateOnAttack())
        {
            _buffManager.LogAndClearBufferClearIdArray();
            return true;
        }
    }
    return false;
}

void BaseCharacter::UpdateBuff()
{ //目标状态的清除设定
    bool bUpdateByTime  = _buffManager.UpdateDurationTime();
    bool bUpdateByValue = _buffManager.UpdateCounterValue();
    if( !bUpdateByTime && !bUpdateByValue)
    { return; }

    _buffManager.LogAndClearBufferClearIdArray();
    _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );
    
    if ( IsPlayer() )
    {
        GamePlayer* pGamePlayer = (GamePlayer*)this;
        if ( pGamePlayer )
        { 
            pGamePlayer->UpdateCharAllAttibute();
            pGamePlayer->SendCharAttibuteToClient(); 
        }
    }

    SendBuffChanged( NULL );
    //SendBuffs( ErrorUnsignedShortID, true );
}

void BaseCharacter::SendBuffs( GamePlayer* pPlayer, bool bNeedKnowLast )
{
    MsgBuffsUpdate xUpdate;
    xUpdate.header.stID    = GetID();
    int nBufferStatusCount = _buffManager.GetBufferStatusCount();
    int nLastStatusNum     = -1;
    uint32 startTime       = 0;

    for ( int i=0; i<nBufferStatusCount; ++i )
    { // 找到最后添加的Status
        SCharBuff* pBodyStatus = _buffManager.GetBuff( i );
        if ( NULL == pBodyStatus )
        { continue; }

        xUpdate.AddStatus( i, pBodyStatus->iLevel, pBodyStatus->StatusID, nLastStatusNum == i, pBodyStatus->dwDurationTime, pBodyStatus->bStop, pBodyStatus->lapoverNum );

        if ( bNeedKnowLast )
        {
            if ( nLastStatusNum == -1)
            { 
                nLastStatusNum = i; 
                startTime = pBodyStatus->dwStartTime;
            }
            else
            {   
                if ( startTime < pBodyStatus->dwStartTime )
                {
                    nLastStatusNum = i; 
                    startTime = pBodyStatus->dwStartTime;
                }
            }
        }
    }

    if ( pPlayer != NULL )
    {
       pPlayer->SendMessageToClient( &xUpdate );
    }
    else
    {
        GettheServer().SendMsgToView( &xUpdate, GetID(), false );
    }
}

//更新清除的角色的数据
void BaseCharacter::SendBuffChanged( GamePlayer* pPlayer  )
{
    MsgBuffsChanged xChanged;
    xChanged.header.stID = GetID();

    for ( int i=0; i<BodyStatusType_Max; ++i )
    { 
        // 是否对应的Index buff 有改变过
        bool bChange = _buffManager.GetBuffChangeRecord( i );
        if ( !bChange )
        { continue; }

        // 有改变
        SCharBuff* pCharBuff = _buffManager.GetBuff( i );
        if ( NULL == pCharBuff)
        { // 被删除了
            xChanged.AddStatus( i, 0, 0, false, 0, 0, 0 );
        }
        else
        {
            xChanged.AddStatus(i, pCharBuff->iLevel, pCharBuff->StatusID, false, pCharBuff->dwDurationTime, pCharBuff->bStop, pCharBuff->lapoverNum );
        }
    }

    if ( pPlayer != NULL )
    {
        pPlayer->SendMessageToClient( &xChanged );
    }
    else
    {
        GettheServer().SendMsgToView( &xChanged, GetID(), false );
    }

    // 清除发送
    _buffManager.ClearBuffChangedRecords();
}

void BaseCharacter::CancelSkill()
{
    if( CS_HOLDSKILL == GetStatus() )
    { // 将维持技能创建的NPC去掉
        if( m_ContinuousSkill.pEffectChar )
        {
            m_ContinuousSkill.pEffectChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
            m_ContinuousSkill.pEffectChar = 0;
        }
        m_ContinuousSkill.dwTimeSkillHoldingEnd = 0; 
    }

    switch( GetStatus() )
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        {
            //取消当前的攻击状态
            SetStatus( CS_IDLE );
            
            //表示当前任务完成了
            int nSkillID = _SkillTaskManager.DoneCurTask();
            if( IsPlayer() )
            {
                Msg_IntonateInterrupt IntonateInterrupt_msg;
                IntonateInterrupt_msg.header.stID = GetID();
                IntonateInterrupt_msg.nSkillID = nSkillID;
                GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );
            }
        }
        break;
    default:
        return;
    }

    // 技能被取消
    Msg_SkillCanceld canceld;
    canceld.header.stID = GetControl()->GetID();
    GettheServer().SendMsgToView( &canceld, GetID(), false );  
}

void BaseCharacter::SendSkillStatusTo( BaseCharacter* pTarget )
{
    switch( GetStatus() )
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        break;
    default:
        return;
    }

    Msg_SkillStatus status;
    status.header.stID = GetID();
    if( CS_INTONATE == GetStatus() )
    { status.cSkillStatusType = Msg_SkillStatus::skillstatus_intonate; }
    else
    { status.cSkillStatusType = Msg_SkillStatus::skillstatus_hold; }
    status.ustSkillID = m_ContinuousSkill.pSkill->ustItemID;
    status.cSkillLevel = m_ContinuousSkill.pSkill->ustLevel;
    status.cPercent = 0;
    GettheServer().SendMsgToSingle( &status, pTarget );
}

bool BaseCharacter::TryChangeFightState( bool bAdd, EActionFlag flag, bool bSendMessage )
{
    if ( bAdd )
    {
        if( !HaveFighteFlag(flag) )
        {
            AddFightFlag( flag );
        }
    }
    else
    {
        if( HaveFighteFlag(flag) )
        {
            //if (IsPlayer() && flag == eFighting)
            //{
            //    GamePlayer* pPalyer = static_cast<GamePlayer*> (this);
            //    if ( pPalyer != NULL && !pPalyer->_SkillTaskManager.IsTaskEmpty())
            //    {
            //        //发送吟唱中断的信息
            //        Msg_IntonateInterrupt IntonateInterrupt_msg;
            //        IntonateInterrupt_msg.header.stID = GetID();
            //        IntonateInterrupt_msg.nSkillID    = _SkillTaskManager.DoneCurTask();
            //        GettheServer().SendMsgToSingle( &IntonateInterrupt_msg, this );

            //        Msg_SkillCanceld cancel;
            //        cancel.header.stID = GetID();
            //        GettheServer().SendMsgToView( &cancel, GetID(), false );
            //    }
            //}
            ClearFightFlag( flag, bSendMessage );
        }
    }
    return true;
}

void BaseCharacter::AddFightFlag( EActionFlag flag )
{
    _SET_FLAG(m_dwFightFlag, flag);

    switch( flag )
    {
    case eFighting:
        {
			if(IsDead() ) return; //lyh++ 死亡了就用再发送战斗状态了		
            m_iAttackHand = 0;

            OnEnterFightState();

            ChangeSubAction( CS_SubAction_FightAction, -1 );
            MsgChangeFightState msg;
            msg.header.stID = GetID();
            msg.playerId    = GetID();
            msg.bFight      = true;
            GettheServer().SendMsgToView( &msg, GetID(), false );
        }
        break;
    case eSitting:
        {
            if ( IsPlayer())
            {  
                MsgAckSwitchSitStatus ack;
                ack.header.stID = GetID();
                ack.cSitStatus  = 1;
                ack.NpcID       = GetID();
                GettheServer().SendMsgToView( &ack, GetID(), false );

                GamePlayer* pGamePlayer = (GamePlayer*)(this);
                if ( pGamePlayer )
                    pGamePlayer->OnSitDownRestore();//坐下的恢复速率
            }
        }
        break;
    case ePrepareFight:
        {
            if ( IsPlayer())
            {                
                MsgAckSwitchFightStatus  ack;
                ack.header.stID  = GetID();
                ack.cFightStatus = 1;
                ack.NpcID        = GetID();
                GettheServer().SendMsgToView(&ack, GetID(), false );
            }
        }
        break;
    }
}

void BaseCharacter::ClearFightFlag( EActionFlag flag, bool bSendMessage )
{
    _CLS_FLAG(m_dwFightFlag, flag);
    switch( flag )
    {
    case eFighting:
        {
            OnOutFightState();
            ChangeSubAction( CS_SubAction_Normal, -1 );

            if ( bSendMessage )
            {
                MsgChangeFightState msg;
                msg.header.stID = GetID();
                msg.playerId    = GetID();
                msg.bFight      = false;
                GettheServer().SendMsgToView( &msg, GetID(), false );
            }
        }
        break;
    case eSitting:
        {   
            if ( IsPlayer())
            {   
                MsgAckSwitchSitStatus ack;
                ack.header.stID = GetID();
                ack.cSitStatus  = 0;
                ack.NpcID       = GetID();
                GettheServer().SendMsgToView( &ack, GetID(), false );

                GamePlayer* pGamePlayer = (GamePlayer*)(this);
                if ( pGamePlayer )
                    pGamePlayer->OnStandUpRestore();//站起的恢复速率
            }
        }
        break;
    case ePrepareFight:
        {
            if ( IsPlayer())
            {                
                MsgAckSwitchFightStatus  ack;
                ack.header.stID  = GetID();
                ack.cFightStatus = 0;
                ack.NpcID        = GetID();
                GettheServer().SendMsgToView(&ack, GetID(), false );
            }
        }
        break;
    }
}

void BaseCharacter::ProcessEmission()
{
    if( m_ucHaveEmission == 0 )
        return;

    ItemDefine::SItemSkill* pSkill = NULL;
    std::vector< GameObjectId > vecTarget;
    SAttackTarget targetList[ MAXEMISSIONNUM ];

    for( int i=0; i<MAXEMISSIONNUM; ++i )
    {
        targetList[i].bIsCharTarget = false;
        targetList[i].nCharID       = -1;

        if( !m_Emission[i].bDead )
        {   
            DWORD dwPassTime = HQ_TimeGetTime() - m_Emission[i].dwStartTime;

            if( dwPassTime > m_Emission[i].dwLifeTime )
            {
                m_Emission[i].bDead = TRUE;

				//检查无效技能
				pSkill = GettheItemDetail().GetSkillByID( m_Emission[i].ustSkillID, m_Emission[i].ustSkillLevel );
				if ( pSkill == NULL )
				{ continue; }

                //验证目标ID是否还存在
                BaseCharacter * pDst = (BaseCharacter*)theRunTimeData.GetCharacterByID( m_Emission[i].ustTargetID );
                if ( !pDst )
                { continue; }

                vecTarget.push_back( m_Emission[i].ustTargetID );

                if ( m_ucHaveEmission != 0)
                { --m_ucHaveEmission; }
            }
        }
    }

    if ( !vecTarget.empty() && ( pSkill != NULL ) )
    {
        for ( int i = 0; i < vecTarget.size(); ++i )
        {
            targetList[i].bIsCharTarget = true;
            targetList[i].nCharID = vecTarget[i];
        }

        DWORD dwState = TryAttack( targetList, pSkill, pSkill->ustItemID, pSkill->ustLevel, vecTarget.size() );
    }
}

long BaseCharacter::ProcessAssaultModule( const ItemDefine::SItemSkill* pSkill )
{
    if ( !pSkill )
    { return ER_NullPointer; }

    if( ( pSkill->bAssaultSkill || pSkill->ustInstantMovingType != IMT_None ) )
    { // 加速技能
        DoAssaultMoving( pSkill->fRangeCanCast, pSkill->ustInstantMovingType );
    }

    return ER_Success;
}

long BaseCharacter::ProcessReliveModule( const ItemDefine::SItemSkill* pSkillConfig, SAttackTarget* pTarget )
{
    if ( pSkillConfig == NULL )
    { return ER_NullPointer; }

    BaseCharacter* pReliveChar = theRunTimeData.GetCharacterByID( pTarget->nCharID );
    if ( pReliveChar == NULL )
    { return ER_NullPointer; }

    if ( !pReliveChar->IsPlayer() || !pReliveChar->IsDead() )
    { return ER_Failed;}

    GamePlayer* pReliveGamePlayer = (GamePlayer*)pReliveChar;
    if ( pReliveGamePlayer->GetPKValue() < g_Cfg.beRelivePkValue )
    { 
        MsgAckResult msg;
        msg.result = ER_TargetPkValueFail;
        GettheServer().SendMsgToSingle( &msg, this);
        return ER_Failed; 
    }

    GamePlayer::SkillItemRelive& xRelive = pReliveGamePlayer->GetSkillItemRelive();
    xRelive.xTimer.StartTimer( HQ_TimeGetTime(), 70000 );
    xRelive.uchType = MsgAgRelive::useskill;
    xRelive.nItemID = pSkillConfig->ustItemID;
    xRelive.nValue  = pSkillConfig->ustLevel;

    MsgAgRelive msgRelive;
    msgRelive.sttype     = MsgAgRelive::useskill;
    msgRelive.activeid   = GetID();
    GettheServer().SendMsgToSingle( &msgRelive, pReliveChar );

    return ER_Success;
}

long BaseCharacter::ProcessAttackSpeed( const ItemDefine::SItemSkill* pSkill )
{ // 攻击成功了进入了攻击冷却时间
    if ( !pSkill )
    { return ER_NullPointer; } 

    uint32 iHoldTime = pSkill->ustHoldTime;

    if ( IsPlayer() )
    { // 是玩家
        int iItemHoldTime = GetCharFightAttr()->attackSpeed.item;
        if ( iItemHoldTime > 0 )
        { iHoldTime += iItemHoldTime - iItemHoldTime * GetCharFightAttr()->attackSpeed.statusPer * DEF_PERCENT; }
        else
        { iHoldTime += GetCharFightAttr()->attackSpeed.final; }

        if (IsNormalAttack(pSkill->ustItemID))
        { //是普通技能       

            if (iHoldTime < 0)
            { iHoldTime = 0; } 

            m_ExtendStatus.EnterCanNotNormalAttack(iHoldTime);
        }
    }
    else
    { // 怪物
        iHoldTime += GetCharFightAttr()->attackSpeed.final;

        if (iHoldTime < 0)
        { iHoldTime = 0; } 

        m_ExtendStatus.EnterCanNotNormalAttack(iHoldTime);
    }

    return ER_Success;
}

DWORD BaseCharacter::GetEmissionFlyTime( GameObjectId shTargetID )
{
    BaseCharacter *pDst = theRunTimeData.GetCharacterByID( shTargetID );
    if ( NULL == pDst )
    { return 0; }

    D3DXVECTOR3 vDistance( pDst->GetFloatX() - GetFloatX(), pDst->GetFloatY() - GetFloatY(), 0 );
    float fDistance = D3DXVec3Length( &vDistance );
    return fDistance * EMISSIONFLYCOST;
}

void BaseCharacter::CalcEquipHp( BaseCharacter* pTarget )
{
    if ( pTarget == NULL )
    { return; }

    float fWeaponDropHp = g_Cfg.nWeaponDropHp * DEF_THOUSANDTH ;        // 武器持久减少
    float fArmourDropHp = g_Cfg.nArmourDropHp * DEF_THOUSANDTH ;        // 其他装备持久减少

    if ( IsPlayer() )       // 自己是玩家
    {
        GamePlayer* pSelf = static_cast< GamePlayer* >( this ) ;

        bool bIsNeedRefresh = false;
        pSelf->SubEquipHp( EEquipPartType_Weapon, fWeaponDropHp, bIsNeedRefresh );
      
        if ( bIsNeedRefresh )
        {
            pSelf->UpdateAllEquipData();   
            pSelf->UpdateAllSuitData() ;
            pSelf->RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip );
        }
    }

    // 处理被攻击者
    if ( pTarget->IsPlayer() )
    {
        GamePlayer* pPlayerTargeter = (GamePlayer*)pTarget;
        bool bIsNeedRefresh = false;
        
        for ( int i=0; i<EEquipPartType_MaxEquitPart; ++i )
        {
            SCharItem* pEquip = pPlayerTargeter->GetVisualEquipItem( i );
            if ( pEquip == NULL )
            { continue; }

            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pEquip->itembaseinfo.ustItemID );
            if ( NULL==pItemCommon || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
            { continue; }

            pPlayerTargeter->SubEquipHp( i, fArmourDropHp, bIsNeedRefresh );

        }

        if( bIsNeedRefresh )
        {
            pPlayerTargeter->UpdateAllEquipData();        
            pPlayerTargeter->UpdateAllSuitData() ;
            pPlayerTargeter->RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip );
        }
    }
}

float BaseCharacter::GetLevelDistanceExpModulus(short stSrcLevel,short stTargetLevel)
{
    short sLevelDistance = stSrcLevel - stTargetLevel;
    short sSegmentCount = abs(sLevelDistance / LEVEL_DISTANCE_SEGMENT);

    if ( sLevelDistance < 0 )         // 低于怪物等级,稍微给点加成
    {
        //return (1 + PLUE_EXP_MODULUS * sSegmentCount);
    }
    else
    {
        //if ( sSegmentCount == 0)
        //    return 1.0f;

        //return pow( 0.5, sSegmentCount );
        
        if (sLevelDistance >= 15)       
        {
            return max( 0.01f, ( 1.0f - 0.2f - ( sLevelDistance - 14 ) * 0.1f ) ); 
        }    
        else if ( sLevelDistance > 10 && sLevelDistance < 15 ) 
        { 
            return 1.0f - ( sLevelDistance - 10 ) * 0.05f; 
        }
        else                            
        { return 1.00f; }
    }

    return 1.0f;
}

bool BaseCharacter::ChangeAttr( unsigned short ustWhichAttr, float fValue , bool OnlyMe )
{
    MsgCharAttrChanged msgChanged;
    msgChanged.iChangeCount = 0;

    msgChanged.header.stID = GetID();
    if (!msgChanged.AddAttrFloatChange( ustWhichAttr, fValue ) )
        return false;
    msgChanged.CaluLength();

    if ( OnlyMe )
        GettheServer().SendMsgToSingle( &msgChanged, this );
    else
        GettheServer().SendMsgToView( &msgChanged, GetID(), false );
    return true;
}

bool BaseCharacter::ChangeAttr( unsigned short ustWhichAttr, DWORD dwValue, bool OnlyMe )
{
    MsgCharAttrChanged msgChanged;    
    msgChanged.iChangeCount = 0;

    msgChanged.header.stID = GetID();
    if (!msgChanged.AddAttrDWORDChange( ustWhichAttr, dwValue ) )
        return false;
    msgChanged.CaluLength();

    if ( OnlyMe )
        GettheServer().SendMsgToSingle( &msgChanged, this  );
    else
        GettheServer().SendMsgToView( &msgChanged, GetID(), false );
    return true;
}

bool BaseCharacter::ChangeAttr( unsigned short ustWhichAttr, short stValue, bool OnlyMe )
{
    MsgCharAttrChanged msgChanged;
    msgChanged.iChangeCount = 0;

    msgChanged.header.stID = GetID();
    if (!msgChanged.AddAttrShortChange( ustWhichAttr, stValue ) )
        return false;
    msgChanged.CaluLength();

    if ( OnlyMe )
        GettheServer().SendMsgToSingle( &msgChanged, this  );
    else
        GettheServer().SendMsgToView( &msgChanged, GetID(), false );
    return true;
}

bool BaseCharacter::ChangeAttr( unsigned short ustWhichAttr, int nValue, bool OnlyMe )
{
    MsgCharAttrChanged msgChanged;
    msgChanged.iChangeCount = 0;

    msgChanged.header.stID = GetID();
    if (!msgChanged.AddAttrIntChange( ustWhichAttr, nValue ) )
        return false;

    msgChanged.CaluLength();

    if ( OnlyMe )
        GettheServer().SendMsgToSingle( &msgChanged, this );
    else
        GettheServer().SendMsgToView( &msgChanged, GetID(), false );
    return true;
}

bool BaseCharacter::ChangeAttr( unsigned short ustWhichAttr, __int64 nValue, bool OnlyMe )
{
    MsgCharAttrChanged msgChanged;
    msgChanged.iChangeCount = 0;

    msgChanged.header.stID = GetID();
    if (!msgChanged.AddAttrInt64Change( ustWhichAttr, nValue ) )
    { return false; }

    msgChanged.CaluLength();

    if ( OnlyMe )
        GettheServer().SendMsgToSingle( &msgChanged, this );
    else
        GettheServer().SendMsgToView( &msgChanged, GetID(), false );
    return true;
}

// 说话
void BaseCharacter::Say( int nType, const char* szValue )
{
    if ( szValue == NULL || szValue[0] == 0 )
    { return; }

    if ( !IsPlayer() && !HaveAreaPlayer() )
    { return; }

    MsgChat xChat;
    xChat.header.stID = GetID();
	if ( nType == 6 || nType == 7 || nType == 8 || nType == 9 ) //6 本服务器系统 7 全世界系统 8 本服务器国家玩家系统 9 所有国家玩家系统
	{
		xChat.chatHeader.stType = MsgChat::CHAT_TYPE_PROGRAM_SYSTEM;
	}
	if ( nType == 10 || nType == 11 || nType == 12 || nType == 13 ) //10 本服务器公告 11 全世界公告 12 本服务器国家玩家公告 13 所有国家玩家公告
	{
		xChat.chatHeader.stType = MsgChat::CHAT_TYPE_BULL;
	}
    HelperFunc::SafeNCpy( xChat.chatHeader.szSpeakName, GetCharName(), sizeof( xChat.chatHeader.szSpeakName ) );
    xChat.SetString( szValue );

    switch ( nType )
    {
    case 0:     // 周围
        GettheServer().SendMsgToView    ( &xChat, GetID()   );
        break;
    case 1:     // 本地图
        GettheServer().SendMsgToStage   ( &xChat, GetMapID() );
        break;
    case 2:     //  本服务器
	case 6:
	case 10:
        GettheServer().SendMsgToWorld   ( &xChat, false );
        break;
    case 3:     // 全世界
	case 7:
	case 11:
        GettheServer().SendMsgToWorld   ( &xChat, true  );
        break;
    case 4:     // 本服务器国家玩家
	case 8:
	case 12:
        {
            GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
            if ( pStage != NULL )
            { GettheServer().SendMsgToCountry( &xChat, pStage->GetMapData()->CountryID, false ); }
        }
        break;
    case 5:     // 所有国家玩家
	case 9:
	case 13:
        {
            GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
            if ( pStage != NULL )
            { GettheServer().SendMsgToCountry( &xChat, pStage->GetMapData()->CountryID, true ); }
        }
    default:
        break;
    }
}

void BaseCharacter::AddDeBufferAttack(GameObjectId nTargetCharID)
{
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID(nTargetCharID);
    if (!pTarget)
        return;

    if (pTarget->_buffManager.CheckIsAddDeBuffer())
    {
        float fHp = (float)pTarget->GetHP();
        float fHpMax = (float)pTarget->GetCharFightAttr()->hpMax.final;
        float fHpPer = fHp/fHpMax;

        if (pTarget->_buffManager.CheckTargetIsHaveAddBufferFlag(fHpPer))
        {
            if ( GLR_Success == ApplyBufferStatus(pTarget->_buffManager.GetDeBufferID(),pTarget->_buffManager.GetDeBufferLevel(),nTargetCharID, SCharBuff::StatusEventType_Other, 0))
            {
                OnBuffStatusChanged( true );
            }
        }
    }
}

bool BaseCharacter::UseRestoreItem( ItemDefine::SItemRestore* pRestore )
{
    MsgCharAttrChanged Change;
    MsgCharAttrChanged ChangeEveryBodyCanSee;

    // Add HP
    if( pRestore->dwAddHP > 0 )
    {
        // 计算可加的HP
        int nAddHp = GetCharFightAttr()->hpMax.final - GetHP();
        if ( nAddHp > pRestore->dwAddHP )
        { nAddHp = pRestore->dwAddHP; }
        pRestore->dwAddHP -= nAddHp; // 消耗HP

        if( GetHP() < GetCharFightAttr()->hpMax.final )
        {
            OperateHP( EOT_Add, nAddHp);
            ChangeEveryBodyCanSee.AddAttrIntChange( CharAttr_HP, GetHP() );
        }
    }

    // Add MP
    if( pRestore->dwAddMP > 0 )
    {
        // 计算可加的MP
        int nAddMp = GetCharFightAttr()->mpMax.final - GetMP();
        if ( nAddMp > pRestore->dwAddMP )
        { nAddMp = pRestore->dwAddMP; }
        pRestore->dwAddMP -= nAddMp; // 消耗MP

        if(  GetMP() < GetCharFightAttr()->mpMax.final )
        {
            OperateMP( EOT_Add, nAddMp);
            Change.AddAttrIntChange( CharAttr_MP, GetMP() );
        }
    }

    if( IsPlayer() && Change.iChangeCount > 0 )
    {    
        Change.header.stID = GetID();
        Change.CaluLength();
        GettheServer().SendMsgToSingle( &Change, this );
    }    

    if( ChangeEveryBodyCanSee.iChangeCount > 0 )
    {
        ChangeEveryBodyCanSee.header.stID = GetID();
        ChangeEveryBodyCanSee.CaluLength();
        GettheServer().SendMsgToView( &ChangeEveryBodyCanSee, GetID(), false );
    }

    return true;
}

void BaseCharacter::IntonatingInterrupt( int nInterruptValue )
{
    if( !m_ExtendStatus.IsActionDone() )
    {
        m_ExtendStatus.ExtendActionStatusTime( nInterruptValue );

        if( IsPlayer() )
        {
            Msg_IntonatingOverTime msg;
            msg.header.stID = GetID();
            msg.cInterruptPercent = (char)nInterruptValue;
            GettheServer().SendMsgToSingle( &msg, this );
        }
    }
}

bool BaseCharacter::IsCurrentTaskCanBeInterrupt( uint8 interruptType )
{ // 是否当前的技能任务可以被打断
    if ( _SkillTaskManager.IsTaskEmpty() )
    { return true; }

    switch( GetStatus() )
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        {
            SSkillTask* pSkillTask = _SkillTaskManager.GetCurTask();
            if ( pSkillTask == NULL )
            { return true; }

            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pSkillTask->id, pSkillTask->level);
            if( pSkill != NULL )
            {
                if ( !pSkill->bMoveInterrupt )
                { return false; }
            }

            return IsSkillCanBeInterrupt( interruptType, pSkillTask->id );

        }
        break;
    default:
        break;
    }
    return true;
}

// 检查并纠正玩家坐标 格子坐标
bool BaseCharacter::CheckPos( DWORD *pdwMapId, int *pnX, int *pnY, bool bCorrect )
{ // 函数不负责发消息，必须在发位置消息前调用
    if ( pdwMapId == NULL || pnX == NULL || pnY == NULL )
        return false;

    DWORD dwMapDataId = EctypeId2MapId( *pdwMapId);
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwMapDataId );

    DWORD dwSafeMapId = Safe_Map_Id;
    int16 nSafeMapX   = FloatToTile(Safe_Map_PosX);
    int16 nSafeMapY   = FloatToTile(Safe_Map_PosY);
    if ( pMapData == NULL )
    {
        *pdwMapId = dwSafeMapId;
        *pnX      = nSafeMapX;
        *pnY      = nSafeMapY;
        if ( bCorrect )
        {
            SetMapID( dwSafeMapId );
            SetTileX( nSafeMapX );
            SetTileY( nSafeMapY );
            SetFloatZ( WORLD_HEIGHT );
        }
        return true;
    }

    if ( *pnX <= 0 || *pnY <= 0 || *pnX>= ChunckToTile( pMapData->Column )|| *pnY >= ChunckToTile( pMapData->Row ) )
    { // 出边界了
        MapConfig::RelivePosition* pRelivePostion = pMapData->GetRelivePositionByState(false);
        if ( pRelivePostion == NULL )
        {
            LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_ERROR, "没有复活点" );            
            *pdwMapId = dwSafeMapId;
            *pnX      = nSafeMapX;
            *pnY      = nSafeMapY;            
            if ( bCorrect )
            {
                SetMapID( dwSafeMapId );
                SetTileX( nSafeMapX );
                SetTileY( nSafeMapY );
                SetFloatZ( WORLD_HEIGHT );
            }
        }
        else
        {
            *pdwMapId = pRelivePostion->MapId;
            *pnX = FloatToTile(pRelivePostion->PositionX);
            *pnY = FloatToTile(pRelivePostion->PositionY);

            if ( bCorrect )
            {
                SetMapID(pRelivePostion->MapId);
                SetTileX( (int16)(*pnX) );
                SetTileY( (int16)(*pnY) );
                SetFloatZ( WORLD_HEIGHT );
            }
        }
    }
    return true;
}

unsigned short BaseCharacter::GetPlayerEctypeMapLevel( uint32 nMapID, float fX, float fY, bool bConsultTeam /*= true */)
{
    unsigned short ustLevel = 0;

    if ( bConsultTeam )
    { // 按照队伍
        GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
        if ( pTeam == NULL )
        {
            ustLevel = GetLevel();
        }
        else
        {
            int nTeamCount = pTeam->GetTeamMemberCountInMap( nMapID, fX, fY );
            int nMinLevel = 0;
            int nMaxLevel = 0;
            int nTeamTotalLevel = pTeam->GetTeamMemberLevelDistance( nMapID, fX, fY, nMinLevel, nMaxLevel );
            if ( nTeamCount != 0 )
            {
                ustLevel = nTeamTotalLevel / nTeamCount;
            }
        }
    }
    else
    { // 按照自己个人
        ustLevel = GetLevel();
    }

    ustLevel = ( ustLevel + MAPLEVELPERPLAYERLEVEL - 1 ) / MAPLEVELPERPLAYERLEVEL;
    if ( ustLevel > MAX_MAP_LEVEL )
        ustLevel = MAX_MAP_LEVEL;

    return ustLevel;
}

void BaseCharacter::ClearAllBaseAttrByPart ( ECustomDataPart part )
{
    GetCharBaseAttr()->ClearPart( part  );
}

void BaseCharacter::ClearAllFightAttrByPart ( ECustomDataPart part )
{
    switch( part )
    {
    case ECustomDataPart_base:
        {
            GetCharFightAttr()->hpMax               .base = 0;            
            GetCharFightAttr()->mpMax               .base = 0;
            GetCharFightAttr()->attackPhysics       .base = 0;
            GetCharFightAttr()->attackMagic         .base = 0;
            GetCharFightAttr()->defendPhysics       .base = 0;
            GetCharFightAttr()->defendMagic         .base = 0;
            GetCharFightAttr()->attackSpeed         .base = 0;
            GetCharFightAttr()->moveSpeed           .base = 0;
            GetCharFightAttr()->hpRestore           .base = 0;
            GetCharFightAttr()->mpRestore           .base = 0;
            GetCharFightAttr()->exact               .base = 0;
            GetCharFightAttr()->dodge               .base = 0;
            GetCharFightAttr()->critical            .base = 0;
            GetCharFightAttr()->tenacity            .base = 0;
            GetCharFightAttr()->criticalIntensity   .base = 0;
            GetCharFightAttr()->backStrike          .base = 0;
            GetCharFightAttr()->backStrikeResist    .base = 0;
            GetCharFightAttr()->breakStrike         .base = 0;
            GetCharFightAttr()->stabStrike          .base = 0;
            GetCharFightAttr()->elementStrike       .base = 0;
            GetCharFightAttr()->toxinStrike         .base = 0;
            GetCharFightAttr()->spiritStrike        .base = 0;
            GetCharFightAttr()->breakResist         .base = 0;
            GetCharFightAttr()->stabResist          .base = 0;
            GetCharFightAttr()->elementResist       .base = 0;
            GetCharFightAttr()->toxinResist         .base = 0;
            GetCharFightAttr()->spiritResist        .base = 0;
        }
        break;
    case ECustomDataPart_assign:
        {
            GetCharFightAttr()->hpMax               .assign = 0;            
            GetCharFightAttr()->mpMax               .assign = 0;
            GetCharFightAttr()->attackPhysics       .assign = 0;
            GetCharFightAttr()->attackMagic         .assign = 0;
            GetCharFightAttr()->defendPhysics       .assign = 0;
            GetCharFightAttr()->defendMagic         .assign = 0;
            GetCharFightAttr()->attackSpeed         .assign = 0;
            GetCharFightAttr()->moveSpeed           .assign = 0;
            GetCharFightAttr()->hpRestore           .assign = 0;
            GetCharFightAttr()->mpRestore           .assign = 0;
            GetCharFightAttr()->exact               .assign = 0;
            GetCharFightAttr()->dodge               .assign = 0;
            GetCharFightAttr()->critical            .assign = 0;
            GetCharFightAttr()->tenacity            .assign = 0;
            GetCharFightAttr()->criticalIntensity   .assign = 0;
            GetCharFightAttr()->backStrike          .assign = 0;
            GetCharFightAttr()->backStrikeResist    .assign = 0;
            GetCharFightAttr()->breakStrike         .assign = 0;
            GetCharFightAttr()->stabStrike          .assign = 0;
            GetCharFightAttr()->elementStrike       .assign = 0;
            GetCharFightAttr()->toxinStrike         .assign = 0;
            GetCharFightAttr()->spiritStrike        .assign = 0;
            GetCharFightAttr()->breakResist         .assign = 0;
            GetCharFightAttr()->stabResist          .assign = 0;
            GetCharFightAttr()->elementResist       .assign = 0;
            GetCharFightAttr()->toxinResist         .assign = 0;
            GetCharFightAttr()->spiritResist        .assign = 0;
        }
        break;
    case ECustomDataPart_item:
        {
            GetCharFightAttr()->hpMax               .item = 0;            
            GetCharFightAttr()->mpMax               .item = 0;
            GetCharFightAttr()->attackPhysics       .item = 0;
            GetCharFightAttr()->attackMagic         .item = 0;
            GetCharFightAttr()->defendPhysics       .item = 0;
            GetCharFightAttr()->defendMagic         .item = 0;
            GetCharFightAttr()->attackSpeed         .item = 0;
            GetCharFightAttr()->moveSpeed           .item = 0;
            GetCharFightAttr()->hpRestore           .item = 0;
            GetCharFightAttr()->mpRestore           .item = 0;
            GetCharFightAttr()->exact               .item = 0;
            GetCharFightAttr()->dodge               .item = 0;
            GetCharFightAttr()->critical            .item = 0;
            GetCharFightAttr()->tenacity            .item = 0;
            GetCharFightAttr()->criticalIntensity   .item = 0;
            GetCharFightAttr()->backStrike          .item = 0;
            GetCharFightAttr()->backStrikeResist    .item = 0;
            GetCharFightAttr()->breakStrike         .item = 0;
            GetCharFightAttr()->stabStrike          .item = 0;
            GetCharFightAttr()->elementStrike       .item = 0;
            GetCharFightAttr()->toxinStrike         .item = 0;
            GetCharFightAttr()->spiritStrike        .item = 0;
            GetCharFightAttr()->breakResist         .item = 0;
            GetCharFightAttr()->stabResist          .item = 0;
            GetCharFightAttr()->elementResist       .item = 0;
            GetCharFightAttr()->toxinResist         .item = 0;
            GetCharFightAttr()->spiritResist        .item = 0;
            GetCharFightAttr()->hpMax               .itemPer = 0;            
            GetCharFightAttr()->mpMax               .itemPer = 0;
            GetCharFightAttr()->attackPhysics       .itemPer = 0;
            GetCharFightAttr()->attackMagic         .itemPer = 0;
            GetCharFightAttr()->defendPhysics       .itemPer = 0;
            GetCharFightAttr()->defendMagic         .itemPer = 0;
            GetCharFightAttr()->attackSpeed         .itemPer = 0;
            GetCharFightAttr()->moveSpeed           .itemPer = 0;
            GetCharFightAttr()->hpRestore           .itemPer = 0;
            GetCharFightAttr()->mpRestore           .itemPer = 0;
            GetCharFightAttr()->exact               .itemPer = 0;
            GetCharFightAttr()->dodge               .itemPer = 0;
            GetCharFightAttr()->critical            .itemPer = 0;
            GetCharFightAttr()->tenacity            .itemPer = 0;

        }
        break;
    case ECustomDataPart_xinfa:
        {
            GetCharFightAttr()->hpMax               .xinfa = 0;            
            GetCharFightAttr()->mpMax               .xinfa = 0;
            GetCharFightAttr()->attackPhysics       .xinfa = 0;
            GetCharFightAttr()->attackMagic         .xinfa = 0;
            GetCharFightAttr()->defendPhysics       .xinfa = 0;
            GetCharFightAttr()->defendMagic         .xinfa = 0;
            GetCharFightAttr()->attackSpeed         .xinfa = 0;
            GetCharFightAttr()->moveSpeed           .xinfa = 0;
            GetCharFightAttr()->hpRestore           .xinfa = 0;
            GetCharFightAttr()->mpRestore           .xinfa = 0;
            GetCharFightAttr()->exact               .xinfa = 0;
            GetCharFightAttr()->dodge               .xinfa = 0;
            GetCharFightAttr()->critical            .xinfa = 0;
            GetCharFightAttr()->tenacity            .xinfa = 0;
            GetCharFightAttr()->criticalIntensity   .xinfa = 0;
            GetCharFightAttr()->backStrike          .xinfa = 0;
            GetCharFightAttr()->backStrikeResist    .xinfa = 0;
            GetCharFightAttr()->breakStrike         .xinfa = 0;
            GetCharFightAttr()->stabStrike          .xinfa = 0;
            GetCharFightAttr()->elementStrike       .xinfa = 0;
            GetCharFightAttr()->toxinStrike         .xinfa = 0;
            GetCharFightAttr()->spiritStrike        .xinfa = 0;
            GetCharFightAttr()->breakResist         .xinfa = 0;
            GetCharFightAttr()->stabResist          .xinfa = 0;
            GetCharFightAttr()->elementResist       .xinfa = 0;
            GetCharFightAttr()->toxinResist         .xinfa = 0;
            GetCharFightAttr()->spiritResist        .xinfa = 0;
            GetCharFightAttr()->hpMax               .xinfaPer = 0;            
            GetCharFightAttr()->mpMax               .xinfaPer = 0;
            GetCharFightAttr()->attackPhysics       .xinfaPer = 0;
            GetCharFightAttr()->attackMagic         .xinfaPer = 0;
            GetCharFightAttr()->defendPhysics       .xinfaPer = 0;
            GetCharFightAttr()->defendMagic         .xinfaPer = 0;
            GetCharFightAttr()->attackSpeed         .xinfaPer = 0;
            GetCharFightAttr()->moveSpeed           .xinfaPer = 0;
            GetCharFightAttr()->hpRestore           .xinfaPer = 0;
            GetCharFightAttr()->mpRestore           .xinfaPer = 0;
            GetCharFightAttr()->exact               .xinfaPer = 0;
            GetCharFightAttr()->dodge               .xinfaPer = 0;
            GetCharFightAttr()->critical            .xinfaPer = 0;
            GetCharFightAttr()->tenacity            .xinfaPer = 0;
        }
        break;
    case ECustomDataPart_status:
        {
            GetCharFightAttr()->hpMax               .status = 0;            
            GetCharFightAttr()->mpMax               .status = 0;
            GetCharFightAttr()->attackPhysics       .status = 0;
            GetCharFightAttr()->attackMagic         .status = 0;
            GetCharFightAttr()->defendPhysics       .status = 0;
            GetCharFightAttr()->defendMagic         .status = 0;
            GetCharFightAttr()->attackSpeed         .status = 0;
            GetCharFightAttr()->moveSpeed           .status = 0;
            GetCharFightAttr()->hpRestore           .status = 0;
            GetCharFightAttr()->mpRestore           .status = 0;
            GetCharFightAttr()->exact               .status = 0;
            GetCharFightAttr()->dodge               .status = 0;
            GetCharFightAttr()->critical            .status = 0;
            GetCharFightAttr()->tenacity            .status = 0;
            GetCharFightAttr()->criticalIntensity   .status = 0;
            GetCharFightAttr()->backStrike          .status = 0;
            GetCharFightAttr()->backStrikeResist    .status = 0;
            GetCharFightAttr()->breakStrike         .status = 0;
            GetCharFightAttr()->stabStrike          .status = 0;
            GetCharFightAttr()->elementStrike       .status = 0;
            GetCharFightAttr()->toxinStrike         .status = 0;
            GetCharFightAttr()->spiritStrike        .status = 0;
            GetCharFightAttr()->breakResist         .status = 0;
            GetCharFightAttr()->stabResist          .status = 0;
            GetCharFightAttr()->elementResist       .status = 0;
            GetCharFightAttr()->toxinResist         .status = 0;
            GetCharFightAttr()->spiritResist        .status = 0;
            GetCharFightAttr()->hpMax               .statusPer = 0;            
            GetCharFightAttr()->mpMax               .statusPer = 0;
            GetCharFightAttr()->attackPhysics       .statusPer = 0;
            GetCharFightAttr()->attackMagic         .statusPer = 0;
            GetCharFightAttr()->defendPhysics       .statusPer = 0;
            GetCharFightAttr()->defendMagic         .statusPer = 0;
            GetCharFightAttr()->attackSpeed         .statusPer = 0;
            GetCharFightAttr()->moveSpeed           .statusPer = 0;
            GetCharFightAttr()->hpRestore           .statusPer = 0;
            GetCharFightAttr()->mpRestore           .statusPer = 0;
            GetCharFightAttr()->exact               .statusPer = 0;
            GetCharFightAttr()->dodge               .statusPer = 0;
            GetCharFightAttr()->critical            .statusPer = 0;
            GetCharFightAttr()->tenacity            .statusPer = 0;
        }
        break;
    case ECustomDataPart_skill:
        {
            GetCharFightAttr()->hpMax               .skill = 0;            
            GetCharFightAttr()->mpMax               .skill = 0;
            GetCharFightAttr()->attackPhysics       .skill = 0;
            GetCharFightAttr()->attackMagic         .skill = 0;
            GetCharFightAttr()->defendPhysics       .skill = 0;
            GetCharFightAttr()->defendMagic         .skill = 0;
            GetCharFightAttr()->attackSpeed         .skill = 0;
            GetCharFightAttr()->moveSpeed           .skill = 0;
            GetCharFightAttr()->hpRestore           .skill = 0;
            GetCharFightAttr()->mpRestore           .skill = 0;
            GetCharFightAttr()->exact               .skill = 0;
            GetCharFightAttr()->dodge               .skill = 0;
            GetCharFightAttr()->critical            .skill = 0;
            GetCharFightAttr()->tenacity            .skill = 0;
            GetCharFightAttr()->criticalIntensity   .skill = 0;
            GetCharFightAttr()->backStrike          .skill = 0;
            GetCharFightAttr()->backStrikeResist    .skill = 0;
            GetCharFightAttr()->breakStrike         .skill = 0;
            GetCharFightAttr()->stabStrike          .skill = 0;
            GetCharFightAttr()->elementStrike       .skill = 0;
            GetCharFightAttr()->toxinStrike         .skill = 0;
            GetCharFightAttr()->spiritStrike        .skill = 0;
            GetCharFightAttr()->breakResist         .skill = 0;
            GetCharFightAttr()->stabResist          .skill = 0;
            GetCharFightAttr()->elementResist       .skill = 0;
            GetCharFightAttr()->toxinResist         .skill = 0;
            GetCharFightAttr()->spiritResist        .skill = 0;
            GetCharFightAttr()->hpMax               .skillPer = 0;            
            GetCharFightAttr()->mpMax               .skillPer = 0;
            GetCharFightAttr()->attackPhysics       .skillPer = 0;
            GetCharFightAttr()->attackMagic         .skillPer = 0;
            GetCharFightAttr()->defendPhysics       .skillPer = 0;
            GetCharFightAttr()->defendMagic         .skillPer = 0;
            GetCharFightAttr()->attackSpeed         .skillPer = 0;
            GetCharFightAttr()->moveSpeed           .skillPer = 0;
            GetCharFightAttr()->hpRestore           .skillPer = 0;
            GetCharFightAttr()->mpRestore           .skillPer = 0;
            GetCharFightAttr()->exact               .skillPer = 0;
            GetCharFightAttr()->dodge               .skillPer = 0;
            GetCharFightAttr()->critical            .skillPer = 0;
            GetCharFightAttr()->tenacity            .skillPer = 0;
        }
        break;
    case ECustomDataPart_title:
        {
            GetCharFightAttr()->hpMax               .title = 0;            
            GetCharFightAttr()->mpMax               .title = 0;
            GetCharFightAttr()->attackPhysics       .title = 0;
            GetCharFightAttr()->attackMagic         .title = 0;
            GetCharFightAttr()->defendPhysics       .title = 0;
            GetCharFightAttr()->defendMagic         .title = 0;
            GetCharFightAttr()->attackSpeed         .title = 0;
            GetCharFightAttr()->moveSpeed           .title = 0;
            GetCharFightAttr()->hpRestore           .title = 0;
            GetCharFightAttr()->mpRestore           .title = 0;
            GetCharFightAttr()->exact               .title = 0;
            GetCharFightAttr()->dodge               .title = 0;
            GetCharFightAttr()->critical            .title = 0;
            GetCharFightAttr()->tenacity            .title = 0;
            GetCharFightAttr()->criticalIntensity   .title = 0;
            GetCharFightAttr()->backStrike          .title = 0;
            GetCharFightAttr()->backStrikeResist    .title = 0;
            GetCharFightAttr()->breakStrike         .title = 0;
            GetCharFightAttr()->stabStrike          .title = 0;
            GetCharFightAttr()->elementStrike       .title = 0;
            GetCharFightAttr()->toxinStrike         .title = 0;
            GetCharFightAttr()->spiritStrike        .title = 0;
            GetCharFightAttr()->breakResist         .title = 0;
            GetCharFightAttr()->stabResist          .title = 0;
            GetCharFightAttr()->elementResist       .title = 0;
            GetCharFightAttr()->toxinResist         .title = 0;
            GetCharFightAttr()->spiritResist        .title = 0;
            GetCharFightAttr()->hpMax               .titlePer = 0;            
            GetCharFightAttr()->mpMax               .titlePer = 0;
            GetCharFightAttr()->attackPhysics       .titlePer = 0;
            GetCharFightAttr()->attackMagic         .titlePer = 0;
            GetCharFightAttr()->defendPhysics       .titlePer = 0;
            GetCharFightAttr()->defendMagic         .titlePer = 0;
            GetCharFightAttr()->attackSpeed         .titlePer = 0;
            GetCharFightAttr()->moveSpeed           .titlePer = 0;
            GetCharFightAttr()->hpRestore           .titlePer = 0;
            GetCharFightAttr()->mpRestore           .titlePer = 0;
            GetCharFightAttr()->exact               .titlePer = 0;
            GetCharFightAttr()->dodge               .titlePer = 0;
            GetCharFightAttr()->critical            .titlePer = 0;
            GetCharFightAttr()->tenacity            .titlePer = 0;
        }
        break;
    case ECustomDataPart_pet:
        {
            GetCharFightAttr()->hpMax               .pet = 0;            
            GetCharFightAttr()->mpMax               .pet = 0;
            GetCharFightAttr()->attackPhysics       .pet = 0;
            GetCharFightAttr()->attackMagic         .pet = 0;
            GetCharFightAttr()->defendPhysics       .pet = 0;
            GetCharFightAttr()->defendMagic         .pet = 0;
            GetCharFightAttr()->attackSpeed         .pet = 0;
            GetCharFightAttr()->moveSpeed           .pet = 0;
            GetCharFightAttr()->hpRestore           .pet = 0;
            GetCharFightAttr()->mpRestore           .pet = 0;
            GetCharFightAttr()->exact               .pet = 0;
            GetCharFightAttr()->dodge               .pet = 0;
            GetCharFightAttr()->critical            .pet = 0;
            GetCharFightAttr()->tenacity            .pet = 0;
            GetCharFightAttr()->criticalIntensity   .pet = 0;
            GetCharFightAttr()->backStrike          .pet = 0;
            GetCharFightAttr()->backStrikeResist    .pet = 0;
            GetCharFightAttr()->breakStrike         .pet = 0;
            GetCharFightAttr()->stabStrike          .pet = 0;
            GetCharFightAttr()->elementStrike       .pet = 0;
            GetCharFightAttr()->toxinStrike         .pet = 0;
            GetCharFightAttr()->spiritStrike        .pet = 0;
            GetCharFightAttr()->breakResist         .pet = 0;
            GetCharFightAttr()->stabResist          .pet = 0;
            GetCharFightAttr()->elementResist       .pet = 0;
            GetCharFightAttr()->toxinResist         .pet = 0;
            GetCharFightAttr()->spiritResist        .pet = 0;
            GetCharFightAttr()->hpMax               .petPer = 0;            
            GetCharFightAttr()->mpMax               .petPer = 0;
            GetCharFightAttr()->attackPhysics       .petPer = 0;
            GetCharFightAttr()->attackMagic         .petPer = 0;
            GetCharFightAttr()->defendPhysics       .petPer = 0;
            GetCharFightAttr()->defendMagic         .petPer = 0;
            GetCharFightAttr()->attackSpeed         .petPer = 0;
            GetCharFightAttr()->moveSpeed           .petPer = 0;
            GetCharFightAttr()->hpRestore           .petPer = 0;
            GetCharFightAttr()->mpRestore           .petPer = 0;
            GetCharFightAttr()->exact               .petPer = 0;
            GetCharFightAttr()->dodge               .petPer = 0;
            GetCharFightAttr()->critical            .petPer = 0;
            GetCharFightAttr()->tenacity            .petPer = 0;
        }
        break;
    case ECustomDataPart_suit:
        {
            GetCharFightAttr()->hpMax               .suit = 0;            
            GetCharFightAttr()->mpMax               .suit = 0;
            GetCharFightAttr()->attackPhysics       .suit = 0;
            GetCharFightAttr()->attackMagic         .suit = 0;
            GetCharFightAttr()->defendPhysics       .suit = 0;
            GetCharFightAttr()->defendMagic         .suit = 0;
            GetCharFightAttr()->attackSpeed         .suit = 0;
            GetCharFightAttr()->moveSpeed           .suit = 0;
            GetCharFightAttr()->hpRestore           .suit = 0;
            GetCharFightAttr()->mpRestore           .suit = 0;
            GetCharFightAttr()->exact               .suit = 0;
            GetCharFightAttr()->dodge               .suit = 0;
            GetCharFightAttr()->critical            .suit = 0;
            GetCharFightAttr()->tenacity            .suit = 0;
            GetCharFightAttr()->criticalIntensity   .suit = 0;
            GetCharFightAttr()->backStrike          .suit = 0;
            GetCharFightAttr()->backStrikeResist    .suit = 0;
            GetCharFightAttr()->breakStrike         .suit = 0;
            GetCharFightAttr()->stabStrike          .suit = 0;
            GetCharFightAttr()->elementStrike       .suit = 0;
            GetCharFightAttr()->toxinStrike         .suit = 0;
            GetCharFightAttr()->spiritStrike        .suit = 0;
            GetCharFightAttr()->breakResist         .suit = 0;
            GetCharFightAttr()->stabResist          .suit = 0;
            GetCharFightAttr()->elementResist       .suit = 0;
            GetCharFightAttr()->toxinResist         .suit = 0;
            GetCharFightAttr()->spiritResist        .suit = 0;
            GetCharFightAttr()->hpMax               .suitPer = 0;            
            GetCharFightAttr()->mpMax               .suitPer = 0;
            GetCharFightAttr()->attackPhysics       .suitPer = 0;
            GetCharFightAttr()->attackMagic         .suitPer = 0;
            GetCharFightAttr()->defendPhysics       .suitPer = 0;
            GetCharFightAttr()->defendMagic         .suitPer = 0;
            GetCharFightAttr()->attackSpeed         .suitPer = 0;
            GetCharFightAttr()->moveSpeed           .suitPer = 0;
            GetCharFightAttr()->hpRestore           .suitPer = 0;
            GetCharFightAttr()->mpRestore           .suitPer = 0;
            GetCharFightAttr()->exact               .suitPer = 0;
            GetCharFightAttr()->dodge               .suitPer = 0;
            GetCharFightAttr()->critical            .suitPer = 0;
            GetCharFightAttr()->tenacity            .suitPer = 0;
        }
        break;
	case ECustomDataPart_hero:
		{
			GetCharFightAttr()->hpMax               .hero = 0;            
			GetCharFightAttr()->mpMax               .hero = 0;
			GetCharFightAttr()->attackPhysics       .hero = 0;
			GetCharFightAttr()->attackMagic         .hero = 0;
			GetCharFightAttr()->defendPhysics       .hero = 0;
			GetCharFightAttr()->defendMagic         .hero = 0;
			GetCharFightAttr()->attackSpeed         .hero = 0;
			GetCharFightAttr()->moveSpeed           .hero = 0;
			GetCharFightAttr()->hpRestore           .hero = 0;
			GetCharFightAttr()->mpRestore           .hero = 0;
			GetCharFightAttr()->exact               .hero = 0;
			GetCharFightAttr()->dodge               .hero = 0;
			GetCharFightAttr()->critical            .hero = 0;
			GetCharFightAttr()->tenacity            .hero = 0;
			GetCharFightAttr()->criticalIntensity   .hero = 0;
			GetCharFightAttr()->backStrike          .hero = 0;
			GetCharFightAttr()->backStrikeResist    .hero = 0;
			GetCharFightAttr()->breakStrike         .hero = 0;
			GetCharFightAttr()->stabStrike          .hero = 0;
			GetCharFightAttr()->elementStrike       .hero = 0;
			GetCharFightAttr()->toxinStrike         .hero = 0;
			GetCharFightAttr()->spiritStrike        .hero = 0;
			GetCharFightAttr()->breakResist         .hero = 0;
			GetCharFightAttr()->stabResist          .hero = 0;
			GetCharFightAttr()->elementResist       .hero = 0;
			GetCharFightAttr()->toxinResist         .hero = 0;
			GetCharFightAttr()->spiritResist        .hero = 0;
			GetCharFightAttr()->hpMax               .heroPer = 0;            
			GetCharFightAttr()->mpMax               .heroPer = 0;
			GetCharFightAttr()->attackPhysics       .heroPer = 0;
			GetCharFightAttr()->attackMagic         .heroPer = 0;
			GetCharFightAttr()->defendPhysics       .heroPer = 0;
			GetCharFightAttr()->defendMagic         .heroPer = 0;
			GetCharFightAttr()->attackSpeed         .heroPer = 0;
			GetCharFightAttr()->moveSpeed           .heroPer = 0;
			GetCharFightAttr()->hpRestore           .heroPer = 0;
			GetCharFightAttr()->mpRestore           .heroPer = 0;
			GetCharFightAttr()->exact               .heroPer = 0;
			GetCharFightAttr()->dodge               .heroPer = 0;
			GetCharFightAttr()->critical            .heroPer = 0;
			GetCharFightAttr()->tenacity            .heroPer = 0;
		}
		break;
	case ECustomDataPart_lieutenant:
		{
			GetCharFightAttr()->hpMax               .lieutenant = 0;            
			GetCharFightAttr()->mpMax               .lieutenant = 0;
			GetCharFightAttr()->attackPhysics       .lieutenant = 0;
			GetCharFightAttr()->attackMagic         .lieutenant = 0;
			GetCharFightAttr()->defendPhysics       .lieutenant = 0;
			GetCharFightAttr()->defendMagic         .lieutenant = 0;
			GetCharFightAttr()->attackSpeed         .lieutenant = 0;
			GetCharFightAttr()->moveSpeed           .lieutenant = 0;
			GetCharFightAttr()->hpRestore           .lieutenant = 0;
			GetCharFightAttr()->mpRestore           .lieutenant = 0;
			GetCharFightAttr()->exact               .lieutenant = 0;
			GetCharFightAttr()->dodge               .lieutenant = 0;
			GetCharFightAttr()->critical            .lieutenant = 0;
			GetCharFightAttr()->tenacity            .lieutenant = 0;
			GetCharFightAttr()->criticalIntensity   .lieutenant = 0;
			GetCharFightAttr()->backStrike          .lieutenant = 0;
			GetCharFightAttr()->backStrikeResist    .lieutenant = 0;
			GetCharFightAttr()->breakStrike         .lieutenant = 0;
			GetCharFightAttr()->stabStrike          .lieutenant = 0;
			GetCharFightAttr()->elementStrike       .lieutenant = 0;
			GetCharFightAttr()->toxinStrike         .lieutenant = 0;
			GetCharFightAttr()->spiritStrike        .lieutenant = 0;
			GetCharFightAttr()->breakResist         .lieutenant = 0;
			GetCharFightAttr()->stabResist          .lieutenant = 0;
			GetCharFightAttr()->elementResist       .lieutenant = 0;
			GetCharFightAttr()->toxinResist         .lieutenant = 0;
			GetCharFightAttr()->spiritResist        .lieutenant = 0;
			GetCharFightAttr()->hpMax               .lieutenantPer = 0;            
			GetCharFightAttr()->mpMax               .lieutenantPer = 0;
			GetCharFightAttr()->attackPhysics       .lieutenantPer = 0;
			GetCharFightAttr()->attackMagic         .lieutenantPer = 0;
			GetCharFightAttr()->defendPhysics       .lieutenantPer = 0;
			GetCharFightAttr()->defendMagic         .lieutenantPer = 0;
			GetCharFightAttr()->attackSpeed         .lieutenantPer = 0;
			GetCharFightAttr()->moveSpeed           .lieutenantPer = 0;
			GetCharFightAttr()->hpRestore           .lieutenantPer = 0;
			GetCharFightAttr()->mpRestore           .lieutenantPer = 0;
			GetCharFightAttr()->exact               .lieutenantPer = 0;
			GetCharFightAttr()->dodge               .lieutenantPer = 0;
			GetCharFightAttr()->critical            .lieutenantPer = 0;
			GetCharFightAttr()->tenacity            .lieutenantPer = 0;
		}
		break;
    case ECustomDataPart_final:
        {
            GetCharFightAttr()->hpMax               .final = 0;            
            GetCharFightAttr()->mpMax               .final = 0;
            GetCharFightAttr()->attackPhysics       .final = 0;
            GetCharFightAttr()->attackMagic         .final = 0;
            GetCharFightAttr()->defendPhysics       .final = 0;
            GetCharFightAttr()->defendMagic         .final = 0;
            GetCharFightAttr()->attackSpeed         .final = 0;
            GetCharFightAttr()->moveSpeed           .final = 0;
            GetCharFightAttr()->hpRestore           .final = 0;
            GetCharFightAttr()->mpRestore           .final = 0;
            GetCharFightAttr()->exact               .final = 0;
            GetCharFightAttr()->dodge               .final = 0;
            GetCharFightAttr()->critical            .final = 0;
            GetCharFightAttr()->tenacity            .final = 0;
            GetCharFightAttr()->criticalIntensity   .final = 0;
            GetCharFightAttr()->backStrike          .final = 0;
            GetCharFightAttr()->backStrikeResist    .final = 0;
            GetCharFightAttr()->breakStrike         .final = 0;
            GetCharFightAttr()->stabStrike          .final = 0;
            GetCharFightAttr()->elementStrike       .final = 0;
            GetCharFightAttr()->toxinStrike         .final = 0;
            GetCharFightAttr()->spiritStrike        .final = 0;
            GetCharFightAttr()->breakResist         .final = 0;
            GetCharFightAttr()->stabResist          .final = 0;
            GetCharFightAttr()->elementResist       .final = 0;
            GetCharFightAttr()->toxinResist         .final = 0;
            GetCharFightAttr()->spiritResist        .final = 0;
        }
        break;
    }
}

void BaseCharacter::UpdateCharAllAttibute()
{
    GetCharFightAttr()->hpMax               .UpdateFinal();            
    GetCharFightAttr()->mpMax               .UpdateFinal();
    GetCharFightAttr()->attackPhysics       .UpdateFinal();
    GetCharFightAttr()->attackMagic         .UpdateFinal();
    GetCharFightAttr()->defendPhysics       .UpdateFinal();
    GetCharFightAttr()->defendMagic         .UpdateFinal();
    GetCharFightAttr()->attackSpeed         .UpdateFinal();
    GetCharFightAttr()->moveSpeed           .UpdateFinal();
    GetCharFightAttr()->hpRestore           .UpdateFinal();
    GetCharFightAttr()->mpRestore           .UpdateFinal();
    GetCharFightAttr()->exact               .UpdateFinal();
    GetCharFightAttr()->dodge               .UpdateFinal();
    GetCharFightAttr()->critical            .UpdateFinal();
    GetCharFightAttr()->tenacity            .UpdateFinal();
    GetCharFightAttr()->criticalIntensity   .UpdateFinal();
    GetCharFightAttr()->backStrike          .UpdateFinal();
    GetCharFightAttr()->backStrikeResist    .UpdateFinal();
    GetCharFightAttr()->breakStrike         .UpdateFinal();
    GetCharFightAttr()->stabStrike          .UpdateFinal();
    GetCharFightAttr()->elementStrike       .UpdateFinal();
    GetCharFightAttr()->toxinStrike         .UpdateFinal();
    GetCharFightAttr()->spiritStrike        .UpdateFinal();
    GetCharFightAttr()->breakResist         .UpdateFinal();
    GetCharFightAttr()->stabResist          .UpdateFinal();
    GetCharFightAttr()->elementResist       .UpdateFinal();
    GetCharFightAttr()->toxinResist         .UpdateFinal();
    GetCharFightAttr()->spiritResist        .UpdateFinal();

    if ( IsPlayer() )
    {
        GetCharBaseAttr()->UpdateFinal();

        GamePlayer* pGamePlayer = (GamePlayer*)this;
        SCharAttributeUpdate& fightLastRecord = pGamePlayer->lastFightAttr;

        if ( GetCharBaseAttr()->baseAttrValue[EBaseAttr_Strength].final     != fightLastRecord.strength )
        { pGamePlayer->fightAttrChangeRecord [EBaseAttr_Strength] = true; }

        if ( GetCharBaseAttr()->baseAttrValue[EBaseAttr_Agility].final      != fightLastRecord.agility )
        { pGamePlayer->fightAttrChangeRecord [EBaseAttr_Agility] = true; }

        if ( GetCharBaseAttr()->baseAttrValue[EBaseAttr_Stamina].final != fightLastRecord.stamina )
        { pGamePlayer->fightAttrChangeRecord [EBaseAttr_Stamina] = true; }

        if ( GetCharBaseAttr()->baseAttrValue[EBaseAttr_Intelligence].final != fightLastRecord.intelligence )
        { pGamePlayer->fightAttrChangeRecord [EBaseAttr_Intelligence] = true; }

        if ( GetCharFightAttr()->hpMax.final != fightLastRecord.hpMax)
        { 
            pGamePlayer->fightAttrChangeRecord[ CharAttr_HPMax ] = true; 

            int nHpChange = GetCharFightAttr()->hpMax.final - fightLastRecord.hpMax;
            if ( pGamePlayer->HasHPMaxChange() )
            { pGamePlayer->OperateHP( EOT_Add, nHpChange ); }
            else
            { pGamePlayer->OperateHP( EOT_Set, GetHP()  );  }
        }

        if ( GetCharFightAttr()->mpMax.final != fightLastRecord.mpMax)
        { 
            pGamePlayer->fightAttrChangeRecord[ CharAttr_MPMax ] = true; 

            int nMpChange = GetCharFightAttr()->mpMax.final - fightLastRecord.mpMax;
            if ( pGamePlayer->HasMPMaxChange() )
            { pGamePlayer->OperateMP( EOT_Add, nMpChange ); }
            else
            { pGamePlayer->OperateMP( EOT_Set, GetMP()   ); }
        }

        if ( GetCharFightAttr()->attackPhysics.final != fightLastRecord.attackPhysics )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_AttackPhysics ] = true; }

        if ( GetCharFightAttr()->attackMagic.final != fightLastRecord.attackMagic )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_AttackMagic ] = true; }

        if ( GetCharFightAttr()->defendPhysics.final != fightLastRecord.defendPhysics )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_DefendPhysics ] = true; }

        if ( GetCharFightAttr()->defendMagic.final != fightLastRecord.defendMagic )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_DefendMagic ] = true; }

        if ( GetCharFightAttr()->attackSpeed.final != fightLastRecord.attackSpeed )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_AttackSpeed ] = true; }

        if ( GetCharFightAttr()->moveSpeed.final != fightLastRecord.moveSpeed )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_MoveSpeed ] = true; }

        if ( GetCharFightAttr()->hpRestore.final != fightLastRecord.hpRestore )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_HPRestore ] = true; }

        if ( GetCharFightAttr()->mpRestore.final != fightLastRecord.mpRestore )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_MPRestore ] = true; }

        if ( GetCharFightAttr()->exact.final != fightLastRecord.exact )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_Exact ] = true; }

        if ( GetCharFightAttr()->dodge.final != fightLastRecord.dodge )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_Dodge ] = true; }

        if ( GetCharFightAttr()->critical.final != fightLastRecord.critical )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_Critical ] = true; }

        if ( GetCharFightAttr()->tenacity.final != fightLastRecord.tenacity )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_Tenacity ] = true; }

        if ( GetCharFightAttr()->criticalIntensity.final != fightLastRecord.criticalIntensity )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_CriticalIntensity ] = true; }

        if ( GetCharFightAttr()->backStrike.final != fightLastRecord.backStrike )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_BackStrike ] = true; }

        if ( GetCharFightAttr()->backStrikeResist.final != fightLastRecord.backStrikeResist )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_BackStrikeResist ] = true; }

        if ( GetCharFightAttr()->breakStrike.final != fightLastRecord.breakStrike )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_BreakStrike ] = true; }

        if ( GetCharFightAttr()->stabStrike.final != fightLastRecord.stabStrike )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_StabStrike ] = true; }

        if ( GetCharFightAttr()->elementStrike.final != fightLastRecord.elementStrike )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_ElementStrike ] = true; }

        if ( GetCharFightAttr()->toxinStrike.final != fightLastRecord.toxinStrike )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_ToxinStrike ] = true; }

        if ( GetCharFightAttr()->spiritStrike.final != fightLastRecord.spiritStrike )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_SpiritStrike ] = true; }

        if ( GetCharFightAttr()->breakResist.final != fightLastRecord.breakResist )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_BreakResist ] = true; }

        if ( GetCharFightAttr()->stabResist.final != fightLastRecord.stabResist )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_StabResist ] = true; }

        if ( GetCharFightAttr()->elementResist.final != fightLastRecord.elementResist )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_ElementResist ] = true; }

        if ( GetCharFightAttr()->toxinResist.final != fightLastRecord.toxinResist )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_ToxinResist ] = true; }

        if ( GetCharFightAttr()->spiritResist.final != fightLastRecord.spiritResist )
        { pGamePlayer->fightAttrChangeRecord[ CharAttr_SpiritResist ] = true; }


        fightLastRecord.strength          = GetCharBaseAttr()->baseAttrValue[EBaseAttr_Strength]        .final;
        fightLastRecord.agility           = GetCharBaseAttr()->baseAttrValue[EBaseAttr_Agility]         .final;
        fightLastRecord.stamina           = GetCharBaseAttr()->baseAttrValue[EBaseAttr_Stamina]         .final;
        fightLastRecord.intelligence      = GetCharBaseAttr()->baseAttrValue[EBaseAttr_Intelligence]    .final;

        fightLastRecord.hpMax             = GetCharFightAttr()->hpMax            .final;
        fightLastRecord.mpMax             = GetCharFightAttr()->mpMax            .final;
        fightLastRecord.attackPhysics     = GetCharFightAttr()->attackPhysics    .final;
        fightLastRecord.attackMagic       = GetCharFightAttr()->attackMagic      .final;
        fightLastRecord.defendPhysics     = GetCharFightAttr()->defendPhysics    .final;
        fightLastRecord.defendMagic       = GetCharFightAttr()->defendMagic      .final;
        fightLastRecord.attackSpeed       = GetCharFightAttr()->attackSpeed      .final;
        fightLastRecord.moveSpeed         = GetCharFightAttr()->moveSpeed        .final;
        fightLastRecord.hpRestore         = GetCharFightAttr()->hpRestore        .final;
        fightLastRecord.mpRestore         = GetCharFightAttr()->mpRestore        .final;
        fightLastRecord.exact             = GetCharFightAttr()->exact            .final;
        fightLastRecord.dodge             = GetCharFightAttr()->dodge            .final;
        fightLastRecord.critical          = GetCharFightAttr()->critical         .final;
        fightLastRecord.tenacity          = GetCharFightAttr()->tenacity         .final;
        fightLastRecord.criticalIntensity = GetCharFightAttr()->criticalIntensity.final;
        fightLastRecord.backStrike        = GetCharFightAttr()->backStrike       .final;
        fightLastRecord.backStrikeResist  = GetCharFightAttr()->backStrikeResist .final;
        fightLastRecord.breakStrike       = GetCharFightAttr()->breakStrike      .final;
        fightLastRecord.stabStrike        = GetCharFightAttr()->stabStrike       .final;
        fightLastRecord.elementStrike     = GetCharFightAttr()->elementStrike    .final;
        fightLastRecord.toxinStrike       = GetCharFightAttr()->toxinStrike      .final;
        fightLastRecord.spiritStrike      = GetCharFightAttr()->spiritStrike     .final;
        fightLastRecord.breakResist       = GetCharFightAttr()->breakResist      .final;
        fightLastRecord.stabResist        = GetCharFightAttr()->stabResist       .final;
        fightLastRecord.elementResist     = GetCharFightAttr()->elementResist    .final;
        fightLastRecord.toxinResist       = GetCharFightAttr()->toxinResist      .final;
        fightLastRecord.spiritResist      = GetCharFightAttr()->spiritResist     .final;
    }
}


void BaseCharacter::SetFightGame( uint8 uchValue, bool bSendMessage )
{
    m_uchFightCamp = uchValue;
	m_IsGameBattle = true;
    if ( bSendMessage )
    {
        MsgTellGameBattleFightCamp xTell;
        xTell.ustPlayerID  = GetID();
        xTell.uchFightCamp = GetFightCamp();
        GettheServer().SendMsgToView( &xTell, GetID(), false );
    }
}
void BaseCharacter::SetFightCamp( uint8 uchValue, bool bSendMessage )
{
	m_uchFightCamp = uchValue;
	m_IsGameBattle = false;
    if ( bSendMessage )
    {
        MsgTellCampBattleFightCamp xTell;
        xTell.ustPlayerID  = GetID();
        xTell.uchFightCamp = GetFightCamp();
        GettheServer().SendMsgToView( &xTell, GetID(), false );
    }
}
void BaseCharacter::ResetDaoxingEffect()
{
    m_DaoxingEffect.Reset();
}

void BaseCharacter::SetDaoxingEffect( uint16 nStatusID, uint32 nDurationTime )
{
    m_DaoxingEffect.nStatusID = nStatusID;
    m_DaoxingEffect.nDurationTime = nDurationTime;
}
