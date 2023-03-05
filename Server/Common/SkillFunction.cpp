#include "ShareData.h"
#include "GamePlayer.h"
#include "ApplyCenter.h"
#include "MonsterBaseEx.h"
#include "Configure.h"
#include "XmlStringLanguage.h"
#include "GameWorld.h"
#include "TeamManager.h"
#include "DuelHandler.h"
#include "MonsterCreater.h"

void BaseCharacter::CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int Damage )
{   
    // 吟唱
    if( pCharTarget->GetStatus() == CS_INTONATE )
    {
        //发动干扰吟唱的几率
        int nInterruptIntonateRate = 0; // pSkillConfig->nInterruptIntonateRate - pCharTarget->GetCharFightAttr()->resistInterrupt.final;
        if( theRand.rand16() % RAND_NUM < nInterruptIntonateRate )
        {
            //干扰吟唱的能力
            int nInterruptIntonatingAbility = pSkillConfig->nInterruptIntonatingAbility;
            pCharTarget->IntonatingInterrupt( nInterruptIntonatingAbility );
        }
    }
	if(IsPlayer())
	{
		GamePlayer* pPlayerAttacker = static_cast<GamePlayer*>(this);
		pPlayerAttacker->AttactOrAssistChar(pCharTarget);
	}
    ////给对方的附加状态 
    //ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatusBySkill( pSkillConfig );
    //int stEnmity = pSkillConfig->stEnmity;
    //if ( stEnmity == 0 /*|| pCharTarget->GetID() == GetID() */)
    //{  return ER_Success; }

    //if( pCharTarget->IsPlayer() && IsPlayer() )
    //{ // 人 对 人 (包括自己对自己 ???)
    //    GamePlayer* pPlayerAttacker = static_cast<GamePlayer*>(this);

    //    // 吟唱
    //    if( pCharTarget->GetStatus() == CS_INTONATE )
    //    {
    //        //发动干扰吟唱的几率
    //        int nInterruptIntonateRate = 0; // pSkillConfig->nInterruptIntonateRate - pCharTarget->GetCharFightAttr()->resistInterrupt.final;
    //        if( theRand.rand32() % RAND_NUM < nInterruptIntonateRate )
    //        {
    //            //干扰吟唱的能力
    //            int nInterruptIntonatingAbility = pSkillConfig->nInterruptIntonatingAbility;
    //            pCharTarget->IntonatingInterrupt( nInterruptIntonatingAbility );
    //        }
    //    }

    //    // PK攻击判断
    //    if ( IsNormalAttack( pSkillConfig->ustItemID ) || ( pItemStatus != NULL && !pItemStatus->bAvail && !pSkillConfig->bIsRelive ) )
    //    { pPlayerAttacker->AttackChar( pCharTarget ); }

    //    // 仇恨值
    //    if (stEnmity < MIN_ENMINYVALUE)
    //    { stEnmity = MIN_ENMINYVALUE; }

    //    if ( pItemStatus )
    //    {
    //        if ( pItemStatus->bAvail )
    //        { // 如果是有利的
    //            // 遍历对方的仇恨列表
    //            for(int n=0; n <pCharTarget->GetEnmitySize(); ++n)
    //            { // 把对手吸引的仇恨全部带给我自己
    //                // 不存在 仇恨为0 刚好是自己 都Continue
    //                if ( pCharTarget->EnmityList(n).nID == NULLID || pCharTarget->EnmityList(n).nEnmity == 0 || pCharTarget->EnmityList(n).nID == GetID())
    //                { continue; }

    //                if( !AddEnmityList( pCharTarget->EnmityList(n).nID , stEnmity) )
    //                { AddEnmity( pCharTarget->EnmityList(n).nID , stEnmity); }

    //                UpdateDecEnmityRate( pCharTarget->EnmityList(n).nID );
    //            }                    
    //        }
    //        else
    //        { // 如果是不利的
    //            if( !pCharTarget->AddEnmityList( GetID(), stEnmity) )
    //            { pCharTarget->AddEnmity( GetID(), stEnmity); }

    //            pCharTarget->UpdateDecEnmityRate(GetID());

    //            if( !AddEnmityList( pCharTarget->GetID(), stEnmity ) )
    //            { AddEnmity( pCharTarget->GetID(), stEnmity ); }

    //            UpdateDecEnmityRate( pCharTarget->GetID() );
    //        }
    //    }
    //    else
    //    {
    //        if( !pCharTarget->AddEnmityList(GetID(), stEnmity) )
    //        { pCharTarget->AddEnmity(GetID(), stEnmity); }

    //        pCharTarget->UpdateDecEnmityRate(GetID());

    //        if( !AddEnmityList(pCharTarget->GetID(), stEnmity) )
    //        { AddEnmity(pCharTarget->GetID(), stEnmity); }

    //        UpdateDecEnmityRate(pCharTarget->GetID());
    //    }
    //}
    //else
    //{ // 人打怪 怪打人 怪打怪
    //    if( pCharTarget->IsPlayer() && IsMonster() )
    //    { // 怪打人
    //        if( pCharTarget->GetStatus() == CS_INTONATE )
    //        {
    //            //发动干扰吟唱的几率
    //            int nInterruptIntonateRate = 0;// pSkillConfig->nInterruptIntonateRate - GetCharFightAttr()->resistInterrupt.final;
    //            if( theRand.rand32() % RAND_NUM < nInterruptIntonateRate )
    //            {
    //                //干扰吟唱的能力
    //                int nInterruptIntonatingAbility = pSkillConfig->nInterruptIntonatingAbility;
    //                pCharTarget->IntonatingInterrupt( nInterruptIntonatingAbility );
    //            }
    //        }

    //        MonsterBase* pAiMonster = (MonsterBase*) this;    
    //        if( pAiMonster->IsSummonMonster() )
    //        {
    //            if (stEnmity < MIN_ENMINYVALUE)
    //                stEnmity = MIN_ENMINYVALUE;

    //            GameCharID MasterID = pAiMonster->GetSummonMasterID();
    //            BaseCharacter* pMaster = theRunTimeData.GetCharacterByID(MasterID);
    //            if( pMaster != NULL )
    //            {
    //                if( pMaster->IsPlayer() )  // 如果是玩家
    //                { 
    //                    GamePlayer* pPlayerChar2 = (GamePlayer*)pMaster;
    //                    if ( IsNormalAttack( pSkillConfig->ustItemID ) || ( pItemStatus != NULL && !pItemStatus->bAvail ) )
    //                    {                                
    //                        pPlayerChar2->AttackChar(pCharTarget);
    //                    }
    //                }

    //                if(!pCharTarget->AddEnmityList(pMaster->GetID(), stEnmity))
    //                    pCharTarget->AddEnmity(pMaster->GetID(), stEnmity);

    //                pCharTarget->UpdateDecEnmityRate(pMaster->GetID());

    //                if(!pMaster->AddEnmityList(pCharTarget->GetID(), stEnmity))
    //                    pMaster->AddEnmity(pCharTarget->GetID(), stEnmity);

    //                pMaster->UpdateDecEnmityRate(pCharTarget->GetID());
    //            } 
    //        }
    //        else
    //        { // 其他怪
    //            int nEnmity = pResult->m_iDamage * 10+stEnmity;
    //            // 在这里加上伤害造成的仇恨(此仇恨只作为DPS数据计算参考)
    //            int nDamageEnmity = pResult->m_iDamage * 10;
    //            AddDamageEnmity(pCharTarget->GetID(), nDamageEnmity);

    //            if (nEnmity > 0)
    //            { AddEnmity(pCharTarget->GetID(), nEnmity); }
    //            else
    //            {
    //                unsigned int unEnmity = abs(nEnmity);  // 这里将nEnmity转成正数
    //                DecEnmity(pCharTarget->GetID(), unEnmity); 
    //                AddEnmity(pCharTarget->GetID(), 1);
    //            }

    //            UpdateDecEnmityRate(pCharTarget->GetID());
    //        }
    //    }
    //    else if( pCharTarget->IsMonster() && IsPlayer() )
    //    { // 人打怪
    //        if ( pItemStatus && pItemStatus->nStandingEnmity > 0)
    //        { stEnmity += pItemStatus->nStandingEnmity; }

    //        GamePlayer* pPlayerChar2 = (GamePlayer*)this;
    //        ItemDefine::SItemStatus* pDstItemStatus = GettheItemDetail().GetStatus(pSkillConfig->ustDstAddStatusID,pSkillConfig->ustDstAddStatusLevel);
    //        if (IsNormalAttack( pSkillConfig->ustItemID ))
    //        {
    //            pPlayerChar2->AttackChar(pCharTarget);
    //        }
    //        else
    //        {
    //            if (pDstItemStatus && !pDstItemStatus->bAvail)
    //            {
    //                pPlayerChar2->AttackChar(pCharTarget);
    //            }
    //        }

    //        MonsterBase* pAiMonsterTarget = (MonsterBase*)pCharTarget;

    //        if( pAiMonsterTarget->IsSummonMonster() )
    //        { // 目标是宠物怪
    //            if (stEnmity < MIN_ENMINYVALUE)
    //            { stEnmity = MIN_ENMINYVALUE; }

    //            BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( pAiMonsterTarget->GetSummonMasterID() );
    //            if( pMaster != NULL && pDstItemStatus && !pItemStatus->bAvail && pMaster->GetID() != GetID())
    //            {
    //                if(!AddEnmityList(pMaster->GetID(), stEnmity))
    //                { AddEnmity(pMaster->GetID(), stEnmity); }

    //                UpdateDecEnmityRate(pMaster->GetID());

    //                if(!pMaster->AddEnmityList(GetID(), stEnmity))
    //                { pMaster->AddEnmity(GetID(), stEnmity); }

    //                pMaster->UpdateDecEnmityRate( GetID() );
    //            }
    //        }
    //        else
    //        { // 一般怪
    //            int nEnmity = pResult->m_iDamage * MULTIPLE_ENMINY + stEnmity;

    //            //在这里加上伤害造成的仇恨(此仇恨只作为DPS数据计算参考)
    //            int nDamageEnmity = pResult->m_iDamage * MULTIPLE_ENMINY;
    //            AddDamageEnmity(pCharTarget->GetID(), nDamageEnmity);

    //            if (nEnmity > 0)
    //            {
    //                AddEnmity(pCharTarget->GetID(), nEnmity);
    //            }
    //            else
    //            {
    //                unsigned int unEnmity = abs(nEnmity);    //这里将nEnmity转成正数
    //                DecEnmity(pCharTarget->GetID(), unEnmity); 
    //                AddEnmity(pCharTarget->GetID(), 1);
    //            }

    //            UpdateDecEnmityRate( pCharTarget->GetID() );
    //        }
    //    }
    //    else
    //    { // 怪打怪 人打Npc Npc打人

    //        MonsterBase* pAiMonster = (MonsterBase*) this; 
    //        switch ( pAiMonster->GetObjType() )
    //        {
    //        case Object_MonsterTrap:    // 机关陷阱怪
    //            {
    //                if (stEnmity < MIN_ENMINYVALUE)
    //                    stEnmity = MIN_ENMINYVALUE;

    //                GameCharID MasterID = pAiMonster->GetSummonMasterID();
    //                BaseCharacter* pMaster = theRunTimeData.GetCharacterByID(MasterID);
    //                if( pMaster != NULL )
    //                {
    //                    if( pMaster->IsPlayer() )  // 如果是玩家
    //                    { 
    //                        GamePlayer* pPlayerChar2 = (GamePlayer*)pMaster;
    //                        if ( IsNormalAttack( pSkillConfig->ustItemID ) || ( pItemStatus != NULL && !pItemStatus->bAvail ) )
    //                        {                                
    //                            pPlayerChar2->AttackChar(pCharTarget);
    //                        }
    //                    }

    //                    if(!pCharTarget->AddEnmityList(pMaster->GetID(), stEnmity))
    //                        pCharTarget->AddEnmity(pMaster->GetID(), stEnmity);

    //                    pCharTarget->UpdateDecEnmityRate(pMaster->GetID());

    //                    if(!pMaster->AddEnmityList(pCharTarget->GetID(), stEnmity))
    //                        pMaster->AddEnmity(pCharTarget->GetID(), stEnmity);

    //                    pMaster->UpdateDecEnmityRate(pCharTarget->GetID());
    //                } 
    //            }
    //            break;
    //        default:
    //            {
    //                int nEnmity = pResult->m_iDamage * MULTIPLE_ENMINY + stEnmity;
    //                //在这里加上伤害造成的仇恨(此仇恨只作为DPS数据计算参考)
    //                int nDamageEnmity = pResult->m_iDamage * MULTIPLE_ENMINY;
    //                AddDamageEnmity( pCharTarget->GetID(), nDamageEnmity );

    //                if (nEnmity > 0)
    //                {
    //                    AddEnmity( pCharTarget->GetID(), nEnmity );
    //                }
    //                else
    //                {
    //                    unsigned int unEnmity = abs(nEnmity);    //这里将nEnmity转成正数
    //                    DecEnmity( pCharTarget->GetID(), unEnmity );
    //                    AddEnmity( pCharTarget->GetID(), 1        );
    //                }

    //                UpdateDecEnmityRate(pCharTarget->GetID());
    //            }
    //            break;
    //        }
    //    }
    //}
    //return ER_Success;
}

uint32 BaseCharacter::ProcessNormalSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster, int nTargetCount /* = 0 */ )
{
    long nResult = ER_Success;

    if ( IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* > ( this ) ;
        // 处理镜像字段模块
        nResult = pPlayer->ProcessAfterIllusionModule( pSkillConfig, pTarget );
        if ( nResult == ER_SuccessBreak )
        { return eFIGHT_NOFLAG; }

        // 处理宠物字段模块
        nResult = pPlayer->ProcessSkillAboutPetModule( pSkillConfig, pTarget );
        if ( nResult == ER_SuccessBreak )
        { return eFIGHT_NOFLAG; }
    }
    
    if ( RESULT_FAILED( nResult ) )
    { return eFIGHT_ERROR;  }

    // 处理冲锋字段模块
    nResult = ProcessAssaultModule( pSkillConfig );
    if ( RESULT_FAILED( nResult ) )
    { return eFIGHT_ERROR; }

    // 得到目标对象
    CFormula formula;
	if ( nTargetCount > 0 )
	{//目标已经在之前技能启动时确定了的
		for ( int i = 0; i < nTargetCount; ++ i )
		{
			BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( pTarget[i].nCharID );
			if ( pTargetChar != NULL )
			{ formula.AddTarget( pTargetChar ); }
		}
	}
	else
	{
		if ( !FindAttackTarget( pTarget, pSkillConfig, formula ) && !pSkillConfig->bIsRelive)  
		{
            MsgCastInefficacySkill msg;
            msg.ustSkillID    = pSkillConfig->ustItemID;
            msg.ustSkillLevel = pSkillConfig->ustLevel;
            msg.header.stID   = GetID();                // 编号
            msg.bIsCharTarget = pTarget->bIsCharTarget; // 是否有攻击目标的技能
            if (msg.bIsCharTarget)
            {
                msg.target.stID = pTarget->nCharID;
            }
            else
            {
                msg.target.pos.x = pTarget->vPos.x;
                msg.target.pos.y = pTarget->vPos.y;
                msg.target.pos.z = pTarget->vPos.z;
            }
            GettheServer().SendMsgToView( &msg, GetID(), false );

			DWORD dwResult = eFIGHT_NOFLAG;
			if ( pTarget->bIsCharTarget )
			{ dwResult = eFIGHT_CANCEL; }
			return dwResult;
		}
	}

    // 复活
    if ( pSkillConfig->bIsRelive )
    {        
        nResult = ProcessReliveModule( pSkillConfig, pTarget );
        if ( RESULT_FAILED( nResult ) )
        { return eFIGHT_ERROR;  }
        else
        { return eFIGHT_NOFLAG; }
    }
    
    int targetNum = formula.GetTargetNum();
    if (targetNum <= 0)
    { //如果没有攻击目标，直接返回
        if ( IsPlayer() )
        {
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = GetID();
            HintMsg.shHintId    = MsgUseSkillHintMessage::eTargetNumIsZero;
            GettheServer().SendMsgToSingle( &HintMsg, this );
        }
        return eFIGHT_ERROR;
    }

    // 发消息通知客户端发现了 某人在使用技能
    MsgSeeAttack3 See3;
    See3.header.stID   = GetID();
    See3.ustSkillID    = pSkillConfig->ustItemID;
    See3.ustSkillLevel = pSkillConfig->ustLevel;
    See3.dwActionTime  = 0;
    See3.dwHoldTime    = m_ExtendStatus.GetNormalAttackHoldTime();        
    See3.stAttackerX   = GetTileX();
    See3.stAttackerY   = GetTileY();
    See3.bIsCharTarget = pTarget->bIsCharTarget;
    if (See3.bIsCharTarget)
    { // 有攻击目标的技能
        See3.target.stID = pTarget->nCharID;
    }
    else
    {
        See3.target.pos.x = pTarget->vPos.x;
        See3.target.pos.y = pTarget->vPos.y;
        See3.target.pos.z = pTarget->vPos.z;
    }

    See3.stAttackerHand = m_iAttackHand;    

    bool bSrcSendMsgFlag = false;

    // 伤害结算
    // 耐久计算
    if( pTarget->bIsCharTarget && !pSkillConfig->bIsRelive)
    {
        BaseCharacter* pTargetChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( pTarget->nCharID );
        if ( !pTargetChar )
        {
            if ( IsPlayer() )
            {
                MsgUseSkillHintMessage HintMsg;
                HintMsg.header.stID = GetID();
                HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetNotExist;
                GettheServer().SendMsgToSingle( &HintMsg, this );    
            }
            return eFIGHT_ERROR;
        }

        if ( pSkillConfig->easyusedata.bSkillWithDamage )           
        { // 有打到人,并且是伤害技能
            CalcEquipHp( pTargetChar );
        }
    }

    // 算出结果
    formula.SetAttacker( this );
    formula.SetSkill( const_cast<ItemDefine::SItemSkill*>(pSkillConfig) );
    formula.BalanceAttackHero( m_iAttackHand );

    SAttTargetResult   targetResult;
    CFormula::SResult* pResult     = NULL;
    CFormula::SResult* pSrcResult  = NULL;
    BaseCharacter*     pCharTarget = NULL;

    ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pSkillConfig->ustDstAddStatusID[0],pSkillConfig->ustDstAddStatusLevel[0] );
    for(int i=0 ; i<targetNum ; ++i )
    { //应用结果
        pCharTarget = formula.GetTarget( i );
        if( pCharTarget == NULL )
        { continue; }

        if ( pItemStatus != NULL && !pItemStatus->bAvail )  // 不是有利的状态
        {
            if ( IsPlayer() && pCharTarget->IsPlayer() && this != pCharTarget && !CheckCanAttackTarget( pCharTarget ) )
            { continue; }   // 不能攻击的时候不能给对方造成伤害
        }

        pResult    = formula.GetTargetLastResult( i );
        pSrcResult = formula.GetSrcLastResult( i );

        if ( NULL == pResult || NULL == pSrcResult )
        { continue; }

        // 结算怪物对角色的仇恨值
        CalcEnmity( pCharTarget, pSkillConfig, pResult->m_iDamage );

        bool bResult = ApplyCenter::ApplyAttack( pCharTarget, pMaster, pSkillConfig, pResult, pSrcResult, &targetResult );

        if (pCharTarget->IsMonster() && CheckCanAttackTarget( pCharTarget ))
        { // 如果目标是怪物，则触发回调的LUA脚本
            // 触发回调的LUA脚本
            MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* > ( pCharTarget );
            pAiChar->LuaBeAttackedCallBack( GetID(), pSkillConfig->ustItemID , pSkillConfig->ustLevel, pResult->m_iDamage );
        }

        // 因为在SEEATTACK消息前会发死亡消息！在这里再设置下HP为0！
        if (pCharTarget->IsDead() && pCharTarget->IsPlayer())
        {
            if (targetResult.nTagHp != 0)
            {
                targetResult.nTagHp = 0;
            }

            if (pSkillConfig->bIsRelive)
            {
                targetResult.stTargetWho = pCharTarget->GetID();
            }
        }

        if ( !IsDead() )
        { // 没死
            if (targetResult.nSrcHp == 0)
            {
                targetResult.nSrcHp = GetHP();
                targetResult.nSrcMp = GetMP();
            }
        }
		// 修正
		targetResult.nTagHp = pCharTarget->GetHP();
		targetResult.nTagMp = pCharTarget->GetMP();
        //客户端的通知
        See3.AddResult( &targetResult );

        //LOG_MESSAGE( FIGHTOBJECT, LOG_PRIORITY_DEBUG, )
    }

    // 计算消息包的长度
    See3.CaluLength();
    GettheServer().SendMsgToView( &See3, GetID(), false );

    // 清除决斗信息
    if ( IsPlayer() || IsMonster() )
    {
        GamePlayer* pPlayer = NULL ;
        if ( IsPlayer() )
        { pPlayer = static_cast< GamePlayer* > ( this ); }
        else
        { pPlayer = GetMasterPlayer(); }

        if ( pPlayer != NULL && pPlayer->GetClearDuelFight() )
        {
             theDuelHandler()->RemoveDuel( pPlayer->GetDuelFightLoser() );
             pPlayer->CancelSkill        ( );
             pPlayer->SetClearDuelFight  ( false );
             pPlayer->SetDuelFightLoser  ( InvalidGameObjectId );
        }
    }

    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessCaptureSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster )
{
    if ( pMaster == NULL )
    { return eFIGHT_ERROR; }

    if ( !pTarget->bIsCharTarget || pTarget->nCharID < dr_worldMaxPlayers )
    { return eFIGHT_ERROR; }

    if ( HaveCapturePet() )
    { // 只让抓一个
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eHaveCapturePet;
        GettheServer().SendMsgToSingle( &HintMsg, this );
        return eFIGHT_ERROR; 
    }

    // 得到目标对象
    BaseCharacter* pCharTarget = theRunTimeData.GetCharacterByID( pTarget->nCharID );    
    if ( pCharTarget == NULL )  
    { // 没有找到攻击目标
        MsgCastInefficacySkill msg;
        msg.ustSkillID    = pSkillConfig->ustItemID;
        msg.ustSkillLevel = pSkillConfig->ustLevel;
        msg.header.stID   = GetID();                // 编号
        msg.bIsCharTarget = pTarget->bIsCharTarget; // 是否有攻击目标的技能
        msg.target.stID   = pTarget->nCharID;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_CANCEL;
    }

    // 记录作用结果
    if( !pCharTarget->IsMonster() || pCharTarget->GetMonsterType() != eMT_NormalMonster )
    {
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetWrong;
        GettheServer().SendMsgToSingle( &HintMsg, this );    
        return eFIGHT_ERROR;
    }

    // 结果
    SAttTargetResult targetResult;
    targetResult.stAttackerWho = GetID();

    CFormula::SResult targetFormulaResult;
    targetFormulaResult.m_stBalanceType = ItemDefine::balancetype_none;
    targetFormulaResult.m_bMiss         = false;
    targetFormulaResult.m_iDamage       = pCharTarget->GetHP();

    CFormula::SResult sourceFormulaResult;
    bool bResult = ApplyCenter::ApplyAttack( pCharTarget, pMaster, pSkillConfig, &targetFormulaResult, &sourceFormulaResult, &targetResult);

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( GetMapID() );
    xCreateData.SetPostionX( GetFloatX() + 1.0f );
    xCreateData.SetPostionY( GetFloatY() + 1.0f );
    xCreateData.SetDirX( GetDirX() );
    xCreateData.SetDirY( GetDirY() );
    xCreateData.SetMonsterID( pCharTarget->GetMonsterID() );

    MonsterBaseEx* pCaptureMonster = MonsterCreater::CreatePetCaptureMonster( xCreateData, this );
    if ( pCaptureMonster == NULL )
    { 
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eCapturePetFail;
        GettheServer().SendMsgToSingle( &HintMsg, this );
        return eFIGHT_ERROR; 
    }

    MsgSeeAttack3 See3;
    See3.header.stID    = GetID();
    See3.ustSkillID     = pSkillConfig->ustItemID;
    See3.ustSkillLevel  = pSkillConfig->ustLevel;
    See3.dwActionTime   = 0;
    See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();
    See3.stAttackerX    = GetTileX();
    See3.stAttackerY    = GetTileY();
    See3.bIsCharTarget  = pTarget->bIsCharTarget;
    See3.target.stID    = pTarget->nCharID;
    See3.stAttackerHand = m_iAttackHand;
    See3.AddResult( &targetResult );
    See3.CaluLength();
    GettheServer().SendMsgToView( &See3, GetID(), false );

    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessSuckFetchSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster )
{
    // 得到目标对象
    BaseCharacter* pCharTarget = theRunTimeData.GetCharacterByID( pTarget->nCharID );    
    if ( pCharTarget == NULL )  
    { // 没有找到攻击目标
        MsgCastInefficacySkill msg;
        msg.ustSkillID    = pSkillConfig->ustItemID;
        msg.ustSkillLevel = pSkillConfig->ustLevel;
        msg.header.stID   = GetID();                // 编号
        msg.bIsCharTarget = pTarget->bIsCharTarget; // 是否有攻击目标的技能
        msg.target.stID   = pTarget->nCharID;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_CANCEL;
    }

    if ( !pCharTarget->IsMonster())
    {
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetWrong;
        GettheServer().SendMsgToSingle( &HintMsg, this );    
        return eFIGHT_ERROR;
    }
    
    MonsterBaseEx* pAICharTarget = (MonsterBaseEx*)pCharTarget;

    if ( pAICharTarget->GetMonsterType() != eMT_NormalMonster )
    { //如果没有攻击目标，直接返回
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetWrong;
        GettheServer().SendMsgToSingle( &HintMsg, this );    
        return eFIGHT_ERROR;
    }

    // 结果
    SAttTargetResult targetResult;
    targetResult.stAttackerWho = GetID();
    
    CFormula::SResult targetFormulaResult;
    targetFormulaResult.m_stBalanceType   = ItemDefine::balancetype_none;    
    targetFormulaResult.m_bMiss           = false;
    targetFormulaResult.m_iDamage = pAICharTarget->GetHP();

    CFormula::SResult sourceFormulaResult;    
    ItemDefine::SItemStatus* pStatusConfig = GettheItemDetail().GetStatusBySkill( pSkillConfig );
    if ( pStatusConfig )
    {
        sourceFormulaResult.m_iHPRestore = pStatusConfig->stChanged_HP;
        sourceFormulaResult.m_iMPRestore = pStatusConfig->stChanged_MP;
    }

    bool bResult = ApplyCenter::ApplyAttack( pCharTarget, pMaster, pSkillConfig, &targetFormulaResult, &sourceFormulaResult, &targetResult);
    
    MsgSeeAttack3 See3;
    See3.header.stID    = GetID();
    See3.ustSkillID     = pSkillConfig->ustItemID;
    See3.ustSkillLevel  = pSkillConfig->ustLevel;
    See3.dwActionTime   = 0;
    See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();        
    See3.stAttackerX    = GetTileX();
    See3.stAttackerY    = GetTileY();
    See3.bIsCharTarget  = pTarget->bIsCharTarget;
    See3.target.stID    = pTarget->nCharID;
    See3.stAttackerHand = m_iAttackHand;
    targetResult.stAttackerWho = GetID();
    See3.AddResult( &targetResult );
    See3.CaluLength();
    GettheServer().SendMsgToView( &See3, GetID(), false );
    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessBreakOutSkill( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster )
{
    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if( pStage == NULL )
    { return eFIGHT_ERROR; }

    GameObjectIdContainer objects;
    int iEnemyNum = pStage->GetMonsterInCircle( GetPos(), pSkillConfig->fAOEradius, objects, -1, true, this );
    if( iEnemyNum <= 0 )
    {   
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetCountError;
        GettheServer().SendMsgToSingle( &HintMsg, this );    
        return eFIGHT_ERROR;
    }
    
    //附加状态(给对方的)
    ItemDefine::SItemStatus* pStatusTarget = GettheItemDetail().GetDstStatusBySkill( pSkillConfig );
    int changeHP = 100;
    if ( pStatusTarget )
    { changeHP = pStatusTarget->stChanged_HP;}

    SAttTargetResult targetResult;    
    ItrGameObjectIdContainer it    = objects.begin();
    ItrGameObjectIdContainer itEnd = objects.end();

    MsgSeeAttack3 See3;
    See3.header.stID    = GetID();
    See3.ustSkillID     = pSkillConfig->ustItemID;
    See3.ustSkillLevel  = pSkillConfig->ustLevel;
    See3.dwActionTime   = 0;
    See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();
    See3.stAttackerX    = GetTileX();
    See3.stAttackerY    = GetTileY();
    See3.bIsCharTarget  = false;
    See3.target.stID    = -1;
    See3.stAttackerHand = m_iAttackHand;

    CFormula::SResult targetFormulaResult;
    targetFormulaResult.m_stBalanceType   = ItemDefine::balancetype_none;
    targetFormulaResult.m_iDamage          = changeHP;
    targetFormulaResult.m_bMiss           = false;
    CFormula::SResult sourceFormulaResult; 

    for ( ; it!=itEnd; ++it )
    {
        targetResult.Reset();
        targetResult.stAttackerWho = GetID();

        BaseCharacter* pCharTarget = theRunTimeData.GetCharacterByID( *it );
        if ( pCharTarget == NULL )
        { continue; }
        targetResult.stTargetWho = pCharTarget->GetID();
        
        CalcEnmity( pCharTarget, pSkillConfig, targetFormulaResult.m_iDamage );

        bool bResult = ApplyCenter::ApplyAttack( pCharTarget, pMaster, pSkillConfig, &targetFormulaResult, &sourceFormulaResult, &targetResult);

        // 触发回调的LUA脚本
        if ( pCharTarget->IsMonster() )
        {
            MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* > ( pCharTarget );
            pAiChar->LuaBeAttackedCallBack( GetID(), pSkillConfig->ustItemID , pSkillConfig->ustLevel, changeHP );
        }
        
        See3.AddResult( &targetResult );
    }
    
    See3.CaluLength();
    GettheServer().SendMsgToView( &See3, GetID(), false );

    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessCallGraphicSkill( const ItemDefine::SItemSkill* pSkillConfig  )
{
//     MsgReqGraphicCode msg;
//     bool bResult = _graphicCodeManager.MakeReqGraphicCode(msg);
//     if ( bResult )
//     { GettheServer().SendMsgToSingle(&msg, this);}
	GraphicCodeCheckCommunication::SCheckReqMsg msg;
	msg.checkType = GraphicCodeCheckCommunication::ECT_GraphicCode;
	msg.nIDNeedToCheck = GetDBCharacterID();
	theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
    
    // 结果
    SAttTargetResult targetResult;
    targetResult.stAttackerWho = GetID();
    targetResult.stTargetWho   = GetID();
    targetResult.nTagHp        = GetHP();
    targetResult.nSrcHp        = GetHP();
    targetResult.nTagMp        = GetMP();
    targetResult.nSrcMp        = GetMP();

    MsgSeeAttack3 See3;
    See3.header.stID    = GetID();
    See3.ustSkillID     = pSkillConfig->ustItemID;
    See3.ustSkillLevel  = pSkillConfig->ustLevel;
    See3.dwActionTime   = 0;
    See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();        
    See3.stAttackerX    = GetTileX();
    See3.stAttackerY    = GetTileY();
    See3.bIsCharTarget  = true;
    See3.target.stID    = GetID();
    See3.stAttackerHand = m_iAttackHand;
    targetResult.stAttackerWho = GetID();
    See3.AddResult( &targetResult );
    See3.CaluLength();
    GettheServer().SendMsgToView( &See3, GetID(), false );
    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessXPSkill( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster )
{
    GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
    if( pStage == NULL )
    { return eFIGHT_ERROR; }

    GameObjectIdContainer objects;
    int iEnemyNum = pStage->GetMonsterInCircle( GetPos(), pSkillConfig->fAOEradius, objects, pSkillConfig->shMaxTargetNum, true, this );
    if( iEnemyNum <= 0 )
    {   
        MsgUseSkillHintMessage HintMsg;
        HintMsg.header.stID = GetID();
        HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetCountError;
        GettheServer().SendMsgToSingle( &HintMsg, this );    
        return eFIGHT_ERROR;
    }

    //附加状态(给对方的)
    ItemDefine::SItemStatus* pStatusTarget = GettheItemDetail().GetDstStatusBySkill( pSkillConfig );
    int changeHP = 100;
    if ( pStatusTarget )
    { changeHP = pStatusTarget->stChanged_HP;}

    SAttTargetResult targetResult;    
    ItrGameObjectIdContainer it    = objects.begin();
    ItrGameObjectIdContainer itEnd = objects.end();

    MsgSeeAttack3 See3;
    See3.header.stID    = GetID();
    See3.ustSkillID     = pSkillConfig->ustItemID;
    See3.ustSkillLevel  = pSkillConfig->ustLevel;
    See3.dwActionTime   = 0;
    See3.dwHoldTime     = m_ExtendStatus.GetNormalAttackHoldTime();
    See3.stAttackerX    = GetTileX();
    See3.stAttackerY    = GetTileY();
    See3.bIsCharTarget  = false;
    See3.target.stID    = -1;
    See3.stAttackerHand = m_iAttackHand;

    CFormula::SResult targetFormulaResult;
    targetFormulaResult.m_stBalanceType   = ItemDefine::balancetype_damagemagicdefend;
    targetFormulaResult.m_iDamage          = ( -changeHP ) ;
    targetFormulaResult.m_bMiss           = false;
    CFormula::SResult sourceFormulaResult; 

    for ( ; it!=itEnd; ++it )
    {
        targetResult.Reset();
        targetResult.stAttackerWho = GetID();

        BaseCharacter* pCharTarget = theRunTimeData.GetCharacterByID( *it );
        if ( pCharTarget == NULL || pCharTarget->IsPlayer() || pCharTarget->IsDead() )
        { continue; }

        targetResult.stTargetWho = pCharTarget->GetID();

        CalcEnmity( pCharTarget, pSkillConfig, targetFormulaResult.m_iDamage );

        bool bResult = ApplyCenter::ApplyAttack( pCharTarget, pMaster, pSkillConfig, &targetFormulaResult, &sourceFormulaResult, &targetResult);

        if ( pCharTarget->IsMonster() )
        {
            MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* > ( pCharTarget );
            pAiChar->LuaBeAttackedCallBack( GetID(), pSkillConfig->ustItemID , pSkillConfig->ustLevel, changeHP );
        }

        See3.AddResult( &targetResult );
    }

    See3.CaluLength();
    GettheServer().SendMsgToView( &See3, GetID(), false );

    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessTeamRelive( const ItemDefine::SItemSkill* pSkillConfig )
{
    if ( pSkillConfig == NULL )
    { return eFIGHT_ERROR; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { return eFIGHT_ERROR; }

    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
        if ( pPlayer == NULL || !pPlayer->IsDead() )
        { continue; }

        if ( !pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), pSkillConfig->fAOEradius ) )
        { continue; }   // 不在范围内

        SAttackTarget xTarget;
        xTarget.bIsCharTarget = true;
        xTarget.nCharID = pPlayer->GetID();
        pPlayer->ProcessReliveModule( pSkillConfig, &xTarget );
    }

    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessTeamFlyToHeader( const ItemDefine::SItemSkill* pSkillConfig )
{
    if ( pSkillConfig == NULL )
    { return eFIGHT_ERROR; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { return eFIGHT_ERROR; }

    int nCount = pTeam->TeamMemberCount();
    if ( nCount == 0 )
    { return eFIGHT_ERROR; }

    float fStep = D3DX_PI * 2 / nCount;
    D3DXVECTOR3 vZAxis( 0, 0, 1 );
    D3DXVECTOR3 vDir( GetDirX(), GetDirY(), 0 );
    static const float fDistance = 2.0f;

    for ( int i = 0; i < nCount; ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
        if ( pPlayer == NULL || pPlayer->IsDead() )
        { continue; }

        if ( !pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), pSkillConfig->fAOEradius ) )
        { continue; }   // 不在技能作用范围内

        if ( pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), fDistance + 0.1f ) )
        { continue; }   // 2米之内的玩家不传送

        D3DXVECTOR3 vPlayerDir;
        D3DXMATRIX matRotZ;

        D3DXMatrixRotationAxis( &matRotZ, &vZAxis, fStep * i );
        D3DXVec3TransformCoord( &vPlayerDir, &vDir, &matRotZ );
        D3DXVec3Normalize( &vPlayerDir, &vPlayerDir );

        float fX = GetFloatX() + vPlayerDir.x * fDistance;
        float fY = GetFloatY() + vPlayerDir.y * fDistance;

        pPlayer->FlyToMapReq( GetMapID(), fX, fY, acos( vPlayerDir.x ) );
    }

    return eFIGHT_NOFLAG;
}

uint32 GamePlayer::ProcessPetActive ( const ItemDefine::SItemSkill* pSkillConfig )
{
    if ( pSkillConfig == NULL )
    { return eFIGHT_ERROR; }

    int nPetIndex = pSkillConfig->ustLevel - 1;
    SPetItem* pPet = _petManager.GetPetByIndex( nPetIndex );
    if ( pPet == NULL )
    {
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }

    if ( IsDead() )
    { // 死亡状态不能出战
        MsgAckResult msg;
        msg.result = ER_InDeadNotActivePet;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }

    if ( /*pPet->baseInfo.duration*/GetCharInfo().otherdata.PetDuration == 0 )
    { 
        MsgAckResult msg;
        msg.result = ER_LifeNotActivePet;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }

	//by liaojie
    /*if ( pPet->baseInfo.loyalty < 60 )
    { 
        MsgAckResult msg;
        msg.result = ER_LoyaltyNotActivePet;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }*/

	//不要重生时间
    /*if ( pPet->baseInfo.regenerateTime > HQ_TimeGetTime() )
    { 
        int nSecond = (pPet->baseInfo.regenerateTime - HQ_TimeGetTime()) / ONE_SEC ;
        MsgAckResult msg;
        msg.result = ER_PetRegenerateTime;
        msg.value  = nSecond ;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }*/

    //清除当前出战宠物状态
    _petManager.LostActivePetMonster()   ;
    //_petManager.ClearPassiveSkillAffect();

    // 得到当前要出战的马
    int currentIndex = _petManager.GetPetIndexByGuid( pPet->baseInfo.guid );
    if ( currentIndex == -1 )
    { 
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }

    int nResult = _petManager.ProcessSetPetActive( currentIndex );
    if ( RESULT_FAILED( nResult ) )
    {   
        MsgAckResult msg;
        msg.result = nResult;
        GettheServer().SendMsgToSingle( &msg, this );
        return eFIGHT_ERROR;
    }

	//这里判断一下出战的副将有没有给人物增加属性的被动技能，有的话就加上
	//if (pPet)
	//{
	//	for (int indexSkill=0; indexSkill<pPet->skillInfo.GetCurrentSkillCount(); indexSkill++)
	//	{
	//		ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPet->skillInfo.skills[indexSkill].ustSkillID, pPet->skillInfo.skills[indexSkill].stSkillLevel );
	//		if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
	//		{
	//			//有资质类的被动技能，增加属性到人物身上
	//			ApplyPetAttrToChar(pPetSkill,false);
	//		}
	//	}
	//}

    MsgChangePet changeAck;
    changeAck.header.stID = GetID();
    changeAck.ucOpType    = MsgChangePet::EOT_Active;
    changeAck.nIndex      = nPetIndex;
    changeAck.guid        = pPet->baseInfo.guid;
    GettheServer().SendMsgToSingle( &changeAck, this );

    return eFIGHT_NOFLAG;
}
