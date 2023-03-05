#include "ApplyCenter.h"
#include "ShareData.h"
#include "BaseCharacter.h"
#include "MonsterBaseEx.h"
#include "GamePlayer.h"
#include "DuelHandler.h"
#include "XmlStringLanguage.h"
#include "Configure.h"

bool ApplyCenter::Restore( EnumRestoreType type, BaseCharacter* pChar, int iRestore )
{
    if (!pChar)
    { return false; }

    if( pChar->IsDead() )
    { return false; }

    switch( type )
    {
    case ERT_HP:
        { pChar->OperateHP( EOT_Add, iRestore );  }
        break;
    case ERT_MP:
        { pChar->OperateMP( EOT_Add, iRestore );  }
        break;
    default:
        return false;
    }
    return true;
}

bool ApplyCenter::ApplyHPRestore( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker )
{
    if ( NULL == pChar || NULL == pResult || NULL == pClientResult )
    { return false; }

    int nHpRestore = pResult->m_iHPRestore + pResult->m_nExtraHp;

    if( 0 == nHpRestore )
    { return false; }

    Restore( ERT_HP, pChar, nHpRestore );

    // 设置客户端恢复HP (hp为负数表示是恢复)
    if ( bAttacker)
    {
        pClientResult->stSrcHpNum += -1 * nHpRestore;
    }
    else
    {
        pClientResult->stTagHpNum += -1 * nHpRestore;
    }

    if ( pChar->IsPlayer() )
    {
        GamePlayer* pGamePlayer = static_cast< GamePlayer* >( pChar );
        if (pGamePlayer != NULL)
        { pGamePlayer->ChangeAttr( CharAttr_HP, pGamePlayer->GetHP() ); }
    }

    return true;
}

bool ApplyCenter::ApplyMPRestore( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker )
{
    if ( NULL == pChar || NULL == pResult || NULL == pClientResult )
    { return false; }

    int nMpRestore = pResult->m_iMPRestore;

    if( 0 == nMpRestore )
    { return false; }

    Restore( ERT_MP, pChar, nMpRestore ); 

    if ( bAttacker)
    {   
        pClientResult->stSrcMpNum += -1 * nMpRestore;
    }
    else
    {
        pClientResult->stTagMpNum += -1 * nMpRestore;
    }

    if ( pChar->IsPlayer() )
    {
        GamePlayer* pGamePlayer = static_cast< GamePlayer* >( pChar );
        if (pGamePlayer != NULL)
        { pGamePlayer->ChangeAttr( CharAttr_MP, pGamePlayer->GetMP() ); }
    }

    return true;
}

bool ApplyCenter::ApplyXPRestore( BaseCharacter* pTarget, CFormula::SResult* pResult, bool bAttacker  )
{
    if ( !pResult || !pTarget || !pTarget->IsPlayer())
    { return false; }

    if ( pTarget->_buffManager.IsInvincible() )           // 无敌状态也不加怒气
    {
        if ( pResult->m_iXPRestore > 0 )
            pResult->m_iXPRestore = 0;
    }

    if ( pResult->m_iXPRestore == 0)
    { return false; }

    GamePlayer* pGamePlayer = (GamePlayer* )pTarget;
    if ( !pGamePlayer )
    { return false; }

    pGamePlayer->SetXP( pGamePlayer->GetXP() + pResult->m_iXPRestore);
    pGamePlayer->ChangeAttr( CharAttr_XPValue, pGamePlayer->GetXP() );

    return true;
};

bool ApplyCenter::ApplyPhysicDamage( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker )
{
    if ( NULL == pChar || NULL == pResult || NULL == pClientResult )
    { return false; }

    BaseCharacter* pAttack = theRunTimeData.GetCharacterByID( pClientResult->stAttackerWho );

    int iDamage = pResult->m_iDamage ;

    if ( pChar->_buffManager.IsInvincible() ) // 无敌状态不扣血
    { 
        if ( iDamage > 0 )
        { iDamage = 0; }
    }

    if( 0 == iDamage )
    { return false; }

    pChar->OperateHP( EOT_Sub, iDamage );

    if ( bAttacker )
    { // 是攻击者
        pClientResult->stSrcHpNum += pResult->m_iDamage;
    }
    else
    { 
        pClientResult->stTagHpNum  += pResult->m_iDamage - pResult->m_nBackAttackDamage;
        pClientResult->nBackAttack += pResult->m_nBackAttackDamage;
    }

    return true;
}

bool ApplyCenter::ApplyMagicDamage( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker )
{
    if ( NULL == pChar || NULL == pResult || NULL == pClientResult )
    { return false; }
    
    // 背击加成
    int iDamage   = pResult->m_iDamage ;
    int nMPDamage = pResult->m_nDamageMp;

    if ( pChar->_buffManager.IsInvincible() )     // 无敌状态不扣血, 不扣篮
    {
        if ( iDamage > 0 )
        { iDamage = 0; }

        if ( nMPDamage > 0 )
        { nMPDamage = 0; }
    }

    if( iDamage == 0 && nMPDamage == 0  )
        return false;

    // 把一部份攻击力转化为MP
    float TranMPRatio = pChar->_buffManager.GetDamageChange2MpRatioPer();
    float TranMPCost  = pChar->_buffManager.GetDamageChange2MpRatio();

    TranMPCost = TranMPCost < 1 ? 1 : TranMPCost;

    if( 0 != TranMPRatio )
    {
        float mp = iDamage * (TranMPRatio / 100) / TranMPCost;
        int nCostMP = pChar->GetMP() - mp;
        if( nCostMP < 0 )
        {
            //魔法值不够
            pChar->SetMP( 0 );
            pClientResult->nTagMp = 0;
            int unMp2Huge = abs(nCostMP) * TranMPCost;
            iDamage -= iDamage * (TranMPRatio / 100);
            iDamage += unMp2Huge;
        }
        else
        {
            pChar->SetMP( nCostMP );
            pClientResult->nTagMp = nCostMP;
            iDamage -= iDamage * (TranMPRatio / 100);
        }


        iDamage = iDamage < 0 ? 0 : iDamage;
    }

    pChar->OperateHP( EOT_Sub, iDamage   );
    pChar->OperateMP( EOT_Sub, nMPDamage );

    if ( bAttacker )
    {
        pClientResult->stSrcHpNum += pResult->m_iDamage;        
        pClientResult->nSrcMp = pChar->GetMP();    
    }
    else
    {
        pClientResult->stTagHpNum  += pResult->m_iDamage - pResult->m_nBackAttackDamage;
        pClientResult->nBackAttack += pResult->m_nBackAttackDamage;
        pClientResult->nTagMp = pChar->GetMP();
    }

    return true;
}

bool ApplyCenter::ApplyBalanceTypeNone( BaseCharacter* pChar, CFormula::SResult* pResult, SAttTargetResult* pClientResult, bool bAttacker )
{
    if ( NULL == pChar || NULL == pResult || NULL == pClientResult )
    { return false; }

    BaseCharacter* pAttack = theRunTimeData.GetCharacterByID( pClientResult->stAttackerWho );

    int iDamageHP = pResult->m_iDamage;
    int iDamageMP = pResult->m_nDamageMp;

    if ( pChar->_buffManager.IsInvincible() ) // 无敌状态不扣血
    { 
        if ( iDamageHP > 0 )
        { iDamageHP = 0; }

        if ( iDamageMP > 0 )
        { iDamageMP = 0; }
    }

    if ( iDamageHP != 0 )
    {
        // 如果 iDamageHP 小于 0 则是回血
        pChar->OperateHP( EOT_Sub,  iDamageHP );

        if ( bAttacker )
        { // 是攻击者
            pClientResult->stSrcHpNum += iDamageHP;
        }
        else
        { 
            pClientResult->stTagHpNum += iDamageHP;
        }
    }

    if ( iDamageMP != 0 )
    {
        pChar->OperateMP( EOT_Sub,  iDamageMP );

        if ( bAttacker )
        { // 是攻击者
            pClientResult->stSrcMpNum += iDamageMP;
        }
        else
        { 
            pClientResult->stTagMpNum += iDamageMP;
        }
    }

    return true;
}

bool ApplyCenter::ApplyAttack(  BaseCharacter* pCharTarget, BaseCharacter* pCharAttacker, const ItemDefine::SItemSkill* pSkillConfig, 
                                CFormula::SResult* pTargetFormula, CFormula::SResult* pAttackFormula, OUT SAttTargetResult* pAttTargetResult)
{
    if ( NULL == pCharTarget || NULL == pCharAttacker || NULL == pSkillConfig || NULL == pTargetFormula || NULL == pAttackFormula|| NULL == pAttTargetResult)
    { return false; }
    
    ::memset( pAttTargetResult, 0, sizeof(SAttTargetResult));
    
    bool bResult                = false;
    bool bTargetBuffHaveChanged = false;
    bool bSourceBuffHaveChanged = false;
    
    if ( pCharAttacker->UpdateBuffOnAttack() )
    { bSourceBuffHaveChanged = true; }
    
    pAttTargetResult->cBalanceType = pTargetFormula->m_stBalanceType;

    if( pTargetFormula->m_bMiss )
    {
        _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_MISS );    
        pAttTargetResult->stTargetWho   = pCharTarget->GetID();
        pAttTargetResult->nTagHp        = pCharTarget->GetHP();
        pAttTargetResult->nTagMp        = pCharTarget->GetMP();
        pAttTargetResult->stAttackerWho = pCharAttacker->GetID();
        pAttTargetResult->nSrcHp        = pCharAttacker->GetHP();
        pAttTargetResult->nSrcMp        = pCharAttacker->GetMP();

        if ( pTargetFormula->m_bHurtImmunity )
        {
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = pCharAttacker->GetID();
            HintMsg.TargetID = pCharTarget->GetID();   
            HintMsg.shHintId = MsgUseSkillHintMessage::eHurtImmunity;
            GettheServer().SendMsgToView( &HintMsg, pCharAttacker->GetID() );
        }
    }    
    else
    { // 命中
        // 被攻击者逻辑        
        if (!pCharTarget->IsDead())
        {   
            if ( pCharAttacker != pCharTarget )
            {
                pCharTarget->OnBeAttacked( pCharAttacker, pSkillConfig );
                pCharAttacker->AddDeBufferAttack(pCharTarget->GetID());
            }

            bResult = ApplyTargetFormule( pCharTarget, pCharAttacker, pSkillConfig->fBackStrikePlus, pSkillConfig->ustItemID, 
                                          pTargetFormula, pAttackFormula,
                                          pAttTargetResult, bTargetBuffHaveChanged, bSourceBuffHaveChanged);            

            if ( bTargetBuffHaveChanged )
            { pCharTarget->OnBuffStatusChanged( true ); }
        }
    }

    // 攻击者逻辑
    bResult = ApplySourceFormule( pCharTarget, pCharAttacker, pSkillConfig->fBackStrikePlus, 
                                  pAttackFormula, 
                                  pAttTargetResult,bTargetBuffHaveChanged, bSourceBuffHaveChanged );

    if ( bSourceBuffHaveChanged )
    { pCharAttacker->OnBuffStatusChanged( true ); }

    return bResult;
}

bool ApplyCenter::ApplyTargetFormule( BaseCharacter* pTargetChar, BaseCharacter* pSourceChar, float fPercentPlus, uint16 eventValue,
                                     CFormula::SResult* pTargetFormulaResult, CFormula::SResult* pSourceFormulaResult, 
                                    OUT SAttTargetResult* pAttTargetResult, OUT bool& bTargetBuffHaveChanged, OUT bool& bSourceBuffHaveChanged )
{
    if ( !pTargetChar || !pSourceChar || !pTargetFormulaResult || !pAttTargetResult)
    { return false; }

    bool bResult     = false;
    bool bTargetDead = false;
    int  iFinlDamage = 0;
    
    pAttTargetResult->nStatusFlag = 0;
    pAttTargetResult->cBalanceType  = pTargetFormulaResult->m_stBalanceType;     
    pAttTargetResult->stTargetWho   = pTargetChar->GetID();
    pAttTargetResult->stAttackerWho = pSourceChar->GetID();

    if ( ApplyCenter::ApplyHPRestore( pTargetChar, pTargetFormulaResult, pAttTargetResult, false ) )
    { bResult = true; }
    if ( ApplyCenter::ApplyMPRestore( pTargetChar, pTargetFormulaResult, pAttTargetResult, false ) )
    { bResult = true; }
    //if ( ApplyCenter::ApplyXPRestore( pTargetChar, pTargetFormulaResult, false ) )
    //{ bResult = true; }


    switch ( pTargetFormulaResult->m_stBalanceType )
    {
    case ItemDefine::balancetype_damagephysicaldefend:
            if ( ApplyCenter::ApplyPhysicDamage( pTargetChar, pTargetFormulaResult, pAttTargetResult, false ) )
            { bResult = true; }
            break;
    case ItemDefine::balancetype_damagemagicdefend:
            if ( ApplyCenter::ApplyMagicDamage( pTargetChar, pTargetFormulaResult, pAttTargetResult,  false ))
            { bResult = true; }
            break;
    case ItemDefine::balancetype_none:
    case ItemDefine::balancetype_restorehpmp:
            if ( ApplyCenter::ApplyBalanceTypeNone( pTargetChar, pTargetFormulaResult, pAttTargetResult, false ))
            { bResult = true; }
            break;
    }

    // 自己附加状态1
    if( pTargetFormulaResult->m_ustMeAddStatusID[0] > 0 )
    {
        if ( GLR_Success == pSourceChar->ApplyBufferStatus(  pTargetFormulaResult->m_ustMeAddStatusID[0], pTargetFormulaResult->m_ustMeAddStatusLevel[0], pSourceChar->GetID(), SCharBuff::StatusEventType_Skill, eventValue))
        {
            bSourceBuffHaveChanged = true;
            bResult = true;
        }
    }

    // 自己附加状态2
    if( pTargetFormulaResult->m_ustMeAddStatusID[1] > 0 )
    {
        if ( GLR_Success == pSourceChar->ApplyBufferStatus(  pTargetFormulaResult->m_ustMeAddStatusID[1], pTargetFormulaResult->m_ustMeAddStatusLevel[1], pSourceChar->GetID(), SCharBuff::StatusEventType_Skill, eventValue))
        {
            bSourceBuffHaveChanged = true;
            bResult = true;
        }
    }
    
    // 目标附加状态1
    if( pTargetFormulaResult->m_ustDstAddStatusID[0] > 0 )
    {
        if ( GLR_Success == pTargetChar->ApplyBufferStatus(  pTargetFormulaResult->m_ustDstAddStatusID[0],  pTargetFormulaResult->m_ustDstAddStatusLevel[0], pSourceChar->GetID(), SCharBuff::StatusEventType_Skill, eventValue))
        {
            bTargetBuffHaveChanged = true;
            bResult = true;
        }
    }

    // 目标附加状态2
    if( pTargetFormulaResult->m_ustDstAddStatusID[1] > 0 )
    {
        if ( GLR_Success == pTargetChar->ApplyBufferStatus(  pTargetFormulaResult->m_ustDstAddStatusID[1],  pTargetFormulaResult->m_ustDstAddStatusLevel[1], pSourceChar->GetID(), SCharBuff::StatusEventType_Skill, eventValue))
        {
            bTargetBuffHaveChanged = true;
            bResult = true;
        }
    }

    // 背击附加状态
    if( pTargetFormulaResult->m_stBackStrikeAddMeStatus > 0 )
    {
        if ( GLR_Success == pSourceChar->ApplyBufferStatus( pTargetFormulaResult->m_stBackStrikeAddMeStatus, pTargetFormulaResult->m_stBackStrikeAddMeStatusLevel,  pSourceChar->GetID(), SCharBuff::StatusEventType_Skill, eventValue) )                        
        {
            bSourceBuffHaveChanged = true;
            bResult = true;
        }
    }

    if( pTargetFormulaResult->m_stBackStrikeAddDstStatus > 0 )
    {
        if ( GLR_Success == pTargetChar->ApplyBufferStatus( pTargetFormulaResult->m_stBackStrikeAddDstStatus, pTargetFormulaResult->m_stBackStrikeAddDstStatusLevel, pSourceChar->GetID(), SCharBuff::StatusEventType_Skill, eventValue) )
        {
            bTargetBuffHaveChanged = true;
            bResult = true;
        }
    }

    for( int i= 0; i<EEquipPartType_MaxEquitPart; i++ )
    {
        if( pTargetFormulaResult->m_ustMeAddStatusIDFromEquip[i] > 0)
        {
            if ( GLR_Success == pSourceChar->ApplyBufferStatus( pTargetFormulaResult->m_ustMeAddStatusIDFromEquip[i], pTargetFormulaResult->m_ustMeAddStatusLevelFromEquip[i], pSourceChar->GetID(), SCharBuff::StatusEventType_Other, 0))
            {
                bSourceBuffHaveChanged = true;
                bResult = true;
            }
        }

        if( pTargetFormulaResult->m_ustDstAddStatusIDFromEquip[i] > 0 )
        {
            //ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus( pTargetFormulaResult->m_ustDstAddStatusIDFrmWeapon[i], pTargetFormulaResult->m_ustDstAddStatusLevelFrmWeapon[i] );
            //if ( pItemStatus == NULL )
            //{ continue; }

            //bool bIsCanAttack = pSourceChar->CheckCanAttackTarget( pTargetChar );
            //// 如果是有利状态
            //if ( pItemStatus->bAvail && bIsCanAttack )
            //{ continue; }

            //// 如果是有害状态
            //if ( !pItemStatus->bAvail && !bIsCanAttack )
            //{ continue; }

            if ( GLR_Success == pTargetChar->ApplyBufferStatus( pTargetFormulaResult->m_ustDstAddStatusIDFromEquip[i], pTargetFormulaResult->m_ustDstAddStatusLevelFromEquip[i], pSourceChar->GetID(), SCharBuff::StatusEventType_Other, 0))
            {
                bTargetBuffHaveChanged = true;
                bResult = true;
            }
        }
    }

    bool bHaveBuffStatusBeClear = false;

    // 解除状态
    if( pTargetFormulaResult->m_dwSubComboStatus != 0  || pTargetFormulaResult->m_nDispelNegativeType[0] != -1 )
    {
        for( int index=0; index<pTargetChar->_buffManager.GetBufferStatusCount(); ++index )
        {
            SCharBuff* pBodyStatus = pTargetChar->_buffManager.GetBuff(index);
            if ( NULL == pBodyStatus)
            { continue; }

            ItemDefine::SItemStatus* pItemStatusConfig = GettheItemDetail().GetStatus( pBodyStatus->StatusID, pBodyStatus->iLevel);
            if ( NULL == pItemStatusConfig )
            { continue; }
            
            // pTargetFormulaResult->m_dwSubComboStatus & (int)(powf( 2, index )) 
            uint32 flag = 1 << pItemStatusConfig->negativeType;
            if( pTargetFormulaResult->m_dwSubComboStatus & flag )
            {
                pTargetChar->_buffManager.ClearBuff( index );
                bTargetBuffHaveChanged = true;
                bHaveBuffStatusBeClear = true;
                bResult = true;
            }

            // 解除负面状态类型
            for ( int i=0; i< ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize; ++i )
            {
                if ( pItemStatusConfig->negativeType == pTargetFormulaResult->m_nDispelNegativeType[i])
                {
                    pTargetChar->_buffManager.ClearBuff( index );
                    bTargetBuffHaveChanged = true;
                    bHaveBuffStatusBeClear = true;
                    bResult = true;
                }
            }
        }
    }
    
    for( int i=0; i< ItemDefine::CLEAR_MAX_STATUS; ++i )
    {
        if( pTargetFormulaResult->m_dwClearStatus[i] > 0)
        {
            pTargetChar->_buffManager.ClearBuffByBuffId( pTargetFormulaResult->m_dwClearStatus[i] );
            bTargetBuffHaveChanged = true;
            bHaveBuffStatusBeClear = true;
            bResult = true;
        }
    }

    if ( bHaveBuffStatusBeClear )
    {
        pTargetChar->_buffManager.LogAndClearBufferClearIdArray();
    }

    GamePlayer* pPlayerAttacker = NULL; 
    if(pSourceChar->IsPlayer())
    {
        pPlayerAttacker = static_cast<GamePlayer*>(pSourceChar);
    }
    else if(pSourceChar->IsMonster())
    {
        GamePlayer* pMaster = pSourceChar->GetMasterPlayer();
        if ( pMaster != NULL )
        { pPlayerAttacker = pMaster; }
    }

    if ( pPlayerAttacker != NULL )  // 先更新战绩
    {
        pTargetChar->UpdatePlayerScore( pPlayerAttacker->GetID(), pAttTargetResult->stTagHpNum );//玩家打pTargetChar
    }
    else
    {
        pTargetChar->UpdatePlayerScore( pSourceChar->GetID(), pAttTargetResult->stTagHpNum );//怪物(pet sysMonster)打pTargetChar
    }

    // 处理没血逻辑
    if( pTargetChar->GetHP() <= 0 && !pTargetChar->IsDead())
    { // 攻击死亡
        if ( pTargetChar->IsPlayer() 
			&& pPlayerAttacker != NULL 
			&& theDuelHandler()->IsDuelFight(pPlayerAttacker->GetID(), pTargetChar->GetID()))
        { // 两个都是玩家 而且在决斗
            int nDulEndHp = pTargetChar->GetCharFightAttr()->hpMax.final*(g_Cfg.nDulEndHpper/DEF_PER);
            pTargetChar->SetHP(nDulEndHp);

            // 比武结束,清除有害状态
            GamePlayer* pTargetPlayer = static_cast< GamePlayer* >( pTargetChar );
            if (pTargetPlayer != NULL)
            {
                bTargetBuffHaveChanged = true;
                pTargetPlayer->_buffManager.ClearAllBuffByHaveAttack();
                pTargetPlayer->UpdateCharAllAttibute();
                pTargetPlayer->SendCharAttibuteToClient(); 
            }

            GamePlayer* pSourcePlayer = static_cast< GamePlayer* >( pPlayerAttacker );
            if (pSourcePlayer != NULL)
            {
                bSourceBuffHaveChanged = true;
                pSourcePlayer->_buffManager.ClearAllBuffByHaveAttack();
                pSourcePlayer->UpdateCharAllAttibute();
                pSourcePlayer->SendCharAttibuteToClient(); 
            }

            pSourcePlayer->SetClearDuelFight( true );
            pSourcePlayer->SetDuelFightLoser( pTargetChar->GetID() );
            bTargetDead = false;
        }
        else
        { 
            bTargetDead = true;
            pTargetChar->SetDead();
        }
    }
    
    // 怪物是否被打死
    if( bTargetDead )
    {
        // 处理攻击者
        if ( pPlayerAttacker != NULL )
        {
            pPlayerAttacker->KillChar(pTargetChar);
        }

        // 处理被攻击者
        if( pTargetChar->IsPlayer() )
        {   
            if ( pPlayerAttacker != NULL )
            {
                pTargetChar->PunishWhenDeath( pPlayerAttacker );
                pTargetChar->WasKilled( pPlayerAttacker );
            }
            else
            {
                pTargetChar->PunishWhenDeath( pSourceChar );
                pTargetChar->WasKilled( pSourceChar );
            }

            // 清除目标战绩
            //pSourceChar->ClearAttackerById( pTargetChar->GetID() );
        }
        else if (pTargetChar->IsMonster() || pTargetChar->GetObjType() == Object_NpcFight )
        {
            BaseCharacter* pBestAttacker = theRunTimeData.GetCharacterByID( pTargetChar->GetBestAttacker() );
            if ( pBestAttacker != NULL )
            { pTargetChar->WasKilled( pBestAttacker ); }
            else
            { pTargetChar->WasKilled( pSourceChar ); }
        }

        // 添加经验 最棒的玩家（团队）获取额外的经验值  why为什么在这里添加经验呢
        BaseCharacter* pBestChar = theRunTimeData.GetCharacterByID(pTargetChar->GetBestAttacker());
        if ( pBestChar != NULL && pBestChar->IsPlayer() && pTargetChar->IsMonster() )
        {
            GamePlayer* pKillPlayer = static_cast< GamePlayer* >( pBestChar );
            pKillPlayer->IncreaseTeamExp( pTargetChar );                
        }
    }
    else
    { // 没死 必须死
        if( pTargetChar->IsMonster() )
        {
            MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pTargetChar );
            if ( pMonster->IsResourceMonster() )
            {
                pMonster->SetDead();
                pMonster->WasKilled( pSourceChar );
            }
        }
    }

    if( pTargetFormulaResult->m_bRelive )
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_RELIVE ); }

    if( pTargetFormulaResult->m_bCriticalHit )
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_CRITICALHIT ); }

    if ( pTargetFormulaResult->m_bBackHit )
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_BACKSTRIKE  ); }

    if( bTargetDead )
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_BEKILLED ); }

    if ( pTargetFormulaResult->m_nDaoxingEffect == CFormula::e_Resist)
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_DAOXINGRESIST ); }

    if ( pTargetFormulaResult->m_nDaoxingEffect == CFormula::e_Stifle)
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_DAOXINGSTIFLE ); }

    if ( pTargetFormulaResult->m_nShieldHp > 0 )
    { pAttTargetResult->nShieldHp = pTargetFormulaResult->m_nShieldHp; }

    pAttTargetResult->nTagHp = pTargetChar->GetHP();
    pAttTargetResult->nTagMp = pTargetChar->GetMP();
    
    pAttTargetResult->nSrcHp = pSourceChar->GetHP();
    pAttTargetResult->nSrcMp = pSourceChar->GetMP();

    return bResult;
}

bool ApplyCenter::ApplySourceFormule( BaseCharacter* pTargetChar, BaseCharacter* pSourceChar, float fPercentPlus,
                                        CFormula::SResult* pSourceFormulaResult, 
                                        OUT SAttTargetResult* pAttTargetResult, OUT bool& bTargetBuffHaveChanged, OUT bool& bSourceBuffHaveChanged)
{    
    if ( !pTargetChar || !pSourceChar || !pSourceFormulaResult || !pAttTargetResult)
    { return false; }

    bool bResult     = false;
    bool bTargetDead = false;
    int  iFinlDamage = 0;
    
    if ( ApplyCenter::ApplyHPRestore( pSourceChar, pSourceFormulaResult, pAttTargetResult, true ) )
    { bResult = true; }
    if ( ApplyCenter::ApplyMPRestore( pSourceChar, pSourceFormulaResult, pAttTargetResult, true ) )
    { bResult = true; }
    //if ( ApplyCenter::ApplyXPRestore( pSourceChar, pSourceFormulaResult, true ) )
    //{ bResult = true; }

    switch ( pSourceFormulaResult->m_stBalanceType )
    {
    case ItemDefine::balancetype_damagephysicaldefend:
        if ( ApplyCenter::ApplyPhysicDamage( pSourceChar, pSourceFormulaResult, pAttTargetResult, true ) )
        { bResult = true; }
        break;
    case ItemDefine::balancetype_damagemagicdefend:
        if ( ApplyCenter::ApplyMagicDamage ( pSourceChar, pSourceFormulaResult, pAttTargetResult, true ) )
        { bResult = true; }
        break;
    }

    // 解除状态  ( 暂时不用 )
    //if( pSourceFormulaResult->m_dwSubComboStatus!=0 )
    //{
    //    for( int i=0;i<pSourceChar->m_cFightStatus.GetBufferStatusCount(); ++i )
    //    {
    //        if( pSourceFormulaResult->m_dwSubComboStatus & (int)(powf( 2, i )) )
    //        {
    //            pSourceChar->m_cFightStatus.ClearStatus( i );
    //            bSourceBuffHaveChanged = true;
    //            bResult = true;
    //        }
    //    }
    //}
    
    // 解除状态 
    for( int i=0; i< ItemDefine::CLEAR_MAX_STATUS; ++i )
    {
        if( pSourceFormulaResult->m_dwClearStatus[i] > 0)
        {
            pSourceChar->_buffManager.ClearBuffByBuffId( pSourceFormulaResult->m_dwClearStatus[i] );
            bSourceBuffHaveChanged = true;
            bResult = true;
        }
    }

    if ( bSourceBuffHaveChanged )
    { pSourceChar->_buffManager.LogAndClearBufferClearIdArray();}

    GamePlayer* pPlayerAttacker = NULL;
    if( pTargetChar->IsPlayer())
    {
        pPlayerAttacker = static_cast<GamePlayer*>(pTargetChar);
    }
    else if( pTargetChar->IsMonster())
    {
        GamePlayer* pMaster = pTargetChar->GetMasterPlayer();
        if ( pMaster != NULL )
        { pPlayerAttacker = pMaster; }
    }

    if( pSourceChar->GetHP() <= 0 && !pSourceChar->IsDead())
    { // 攻击死亡
        if ( pSourceChar->IsPlayer() && pPlayerAttacker != NULL && theDuelHandler()->IsDuelFight(pPlayerAttacker->GetID(), pSourceChar->GetID()) )
        { // 两个都是玩家 而且在决斗
            int nDulEndHp = pTargetChar->GetCharFightAttr()->hpMax.final*(g_Cfg.nDulEndHpper/DEF_PER);
            pSourceChar->SetHP(nDulEndHp);

            // 比武结束,清除有害状态
            GamePlayer* pSourcePlayer = static_cast< GamePlayer* >( pSourceChar );
            if (pSourcePlayer != NULL)
            {
                bSourceBuffHaveChanged = true;
                pSourcePlayer->_buffManager.ClearAllBuffByHaveAttack();
                pSourcePlayer->UpdateCharAllAttibute();
                pSourcePlayer->SendCharAttibuteToClient(); 
            }
            
            pSourcePlayer->SetClearDuelFight( true );
            pSourcePlayer->SetDuelFightLoser( pSourcePlayer->GetID() );
        }
        else
        { 
            bTargetDead = true;
            pSourceChar->SetDead();
        }
    }

    // 处理没血逻辑
    if( bTargetDead )
    { // 攻击死亡

        // 处理攻击者
        if ( pPlayerAttacker != NULL )
        { pPlayerAttacker->KillChar( pSourceChar );}

        pSourceChar->SetDead();

        if( pSourceChar->IsPlayer())
        {   
            if ( pPlayerAttacker != NULL )
            { // 是玩家
                pSourceChar->PunishWhenDeath( pPlayerAttacker );
                pSourceChar->WasKilled( pPlayerAttacker );
            }
            else
            {
                pSourceChar->PunishWhenDeath( pTargetChar );
                pSourceChar->WasKilled( pTargetChar );
            }
        }
        else if ( pSourceChar->IsMonster() )
        {
            BaseCharacter* pFirstChar1 = theRunTimeData.GetCharacterByID(pSourceChar->GetFirstValidAttacker());
            if (pFirstChar1)
            { pSourceChar->WasKilled( pFirstChar1 ); }
            else
            { pSourceChar->WasKilled( pTargetChar ); }
        }
    }

    if( pSourceFormulaResult->m_nExtraHp > 0 )
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_SUCKHP ); }

    if( pSourceFormulaResult->m_iDamage > 0 || pSourceFormulaResult->m_iDamage > 0)
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_DAMREFLECT ); }

    if ( bTargetDead ) 
    { _SET_FLAG( pAttTargetResult->nStatusFlag, eFIGHT_SELFBEKILLED );}

    pAttTargetResult->nSrcHp = pSourceChar->GetHP();
    pAttTargetResult->nSrcMp = pSourceChar->GetMP();

    return bResult;
}